#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define INFLUXDB_URL "http://192.168.3.6:8086"
#define INFLUXDB_TOKEN "uVVN6MRVPWHRapofF8Jz5RxuLXWwnVtwh7TqBmU3_9lQMz0e9WGfqxTZwGu1P_oYi7jboO9WWuVMTcXCcKpJeA=="
#define INFLUXDB_ORG "8bfbf630cc2ed879"
#define INFLUXDB_BUCKET "psidb"

#define TZ_INFO "UTC-3"

InfluxDBClient influxClient(
    INFLUXDB_URL,
    INFLUXDB_ORG,
    INFLUXDB_BUCKET,
    INFLUXDB_TOKEN
);

void gravarInfluxDB(float tempInterna, float tempExterna, float ph, float oxigenio, float tensao, float corrente,float potencia, float condutividade){
    Point ponto("medicoes");

    ponto.addTag("tanque", "Tanque 01");

    ponto.addField("temperatura_interna", tempInterna);
    ponto.addField("temperatura_externa", tempExterna);
    ponto.addField("ph", ph);
    ponto.addField("oxigenio", oxigenio);
    ponto.addField("tensao", tensao);
    ponto.addField("corrente", corrente);
    ponto.addField("potencia", potencia);
    ponto.addField("condutividade", condutividade);

    if (influxClient.writePoint(ponto)) {
        //Serial.println("Dados enviados ao InfluxDB!");
    } else {
        Serial.print("Erro no InfluxDB: ");
        Serial.println(influxClient.getLastErrorMessage());
    }
}

// Verifica a conexão com o InfluxDB
void verifyConnectionDB(){
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
    if (influxClient.validateConnection()) {
        Serial.print("InfluxDB conectado: ");
        Serial.println(influxClient.getServerUrl());
    } else {
        Serial.print("Falha no InfluxDB: ");
        Serial.println(influxClient.getLastErrorMessage());
    }
}

//Formatar Data Horario

String formatarHoraLocal(String raw){
  // raw vem assim: 2026-11-25T15:00:00.123Z (UTC)
  int a, m, d, h, mi, s;
  if(sscanf(raw.c_str(), "%d-%d-%dT%d:%d:%d", &a, &m, &d, &h, &mi, &s) != 6) return raw;

  struct tm t = {};
  t.tm_year  = a - 1900;
  t.tm_mon   = m - 1;
  t.tm_mday  = d;
  t.tm_hour  = h - 3;      
  t.tm_min   = mi;
  t.tm_sec   = s;
  t.tm_isdst = 0;
  mktime(&t);

  char buf[20];
  strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", &t);
  return String(buf);
}

// Ler histórico do InfluxoDB

String lerHistoricoDB() {
  String query =
    "from(bucket: \"" INFLUXDB_BUCKET "\") "
    "|> range(start: -24h) "
    "|> filter(fn: (r) => r._measurement == \"medicoes\") "
    "|> pivot(rowKey:[\"_time\"], columnKey:[\"_field\"], valueColumn:\"_value\") "
    "|> sort(columns:[\"_time\"], desc:true) "
    "|> limit(n:50)";

  FluxQueryResult result = influxClient.query(query);   // 'client' = seu InfluxDBClient
  String json = "[";
  bool primeiro = true;

  while (result.next()) {
    if (!primeiro) json += ",";
    primeiro = false;
    json += "{";
    json += "\"nome\":\"" + result.getValueByName("tanque").getString() + "\",";
    json += "\"hora\":\"" + formatarHoraLocal(result.getValueByName("_time").getRawValue()) + "\",";
    json += "\"temperatura_interna\":" + String(result.getValueByName("temperatura_interna").getDouble()) + ",";
    json += "\"temperatura_externa\":" + String(result.getValueByName("temperatura_externa").getDouble()) + ",";
    json += "\"ph\":" + String(result.getValueByName("ph").getDouble()) + ",";
    json += "\"oxigenio\":" + String(result.getValueByName("oxigenio").getDouble()) + ",";
    json += "\"tensao\":" + String(result.getValueByName("tensao").getDouble()) + ",";
    json += "\"corrente\":" + String(result.getValueByName("corrente").getDouble()) + ",";
    json += "\"potencia\":" + String(result.getValueByName("potencia").getDouble()) + ",";
    json += "\"condutividade\":" + String(result.getValueByName("condutividade").getDouble());
    json += "}";
  }
  json += "]";
  result.close();
  return json;
}
