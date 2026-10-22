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
        Serial.println("Dados enviados ao InfluxDB!");
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
