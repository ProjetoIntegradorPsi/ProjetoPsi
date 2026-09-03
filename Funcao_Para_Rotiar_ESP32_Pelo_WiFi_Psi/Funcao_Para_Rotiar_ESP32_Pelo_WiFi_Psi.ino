#include <WiFi.h>

// Acessar a rede do rotiador 
const char* ssd = "ENZO";
const char* pass = "Jato2000";

// Login do site
const char* usuario = "admin";
const char* senha = "BlobFish321";

const char* Login_page = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <title>Laboratório de Piscicultura - Login</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <style>
          body{
                margin: 0;
                height: 100vh;
                display: flex;
                justify-content: center;
                align-items: top;
                text-align: center;
                font-family: 'Franklin Gothic Medium', Arial, sans-serif;
            }
            img{
                color: rgb(44, 44, 44);
                border-radius:5px;
                height: 200px;
                width: 200px;
                padding: 10px;
                font-family:'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
            }
            h3{
                text-align: left;
            }
            input{
                width: 100%;
            }
            .mens{
                color: red;
                visibility: hidden;
            }
            .carre{
                color: aqua;
                font-size: 30px;
                -webkit-text-stroke: 1px black;
                visibility: hidden;
            }  
        </style>
    </head>
    <body>
        <div>
            <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTvaLJgS4oo2U_Bpz4YUFpbag38lIaI3WVHxlFSvVz4FnMK5W1Nq_NgQ8P3&s=10">
            <h3>Usuário:</h3>
            <input id="usuario" type="text">
            <h3>Senha:</h3>
            <input id="senha" type="password">
            <p class="mens" id="mensagem">Por favor, coloque o Usuário e a Senha !</p>
            <button onclick="Entrar()">Entrar</button>
            <p id="carregando" class="carre">Carregando...</p>
        </div>
        <script>
            function Entrar(){
                const usuario = document.getElementById("usuario").value;
                const senha = document.getElementById("senha").value;
                const mensagem = document.getElementById("mensagem");
                const carregando = document.getElementById("carregando");
                if(usuario == "" || senha == ""){
                    mensagem.style.visibility = "visible";
                }else{
                    carregando.style.visibility = "visible";
                    fetch("/login?usuario=" + encodeURIComponent(usuario) + "&senha=" + encodeURIComponent(senha))
                        .then(resposta => resposta.text())
                        .then(dados => {
                            document.open();
                            document.write(dados);
                            document.close();
                        });
                }
            }
        </script>
    </body>
</html>
)rawliteral"; 

const char* Home_page =  R"rawliteral(
<!DOCTYPE html>
<html >
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">

        <title>Laboratório de Piscicultura</title>

        <style>
            * {
                box-sizing: border-box;
            }

            body {
                margin: 0;
                min-height: 100vh;
                display: flex;
                justify-content: center;
                text-align: center;
                font-family: 'Franklin Gothic Medium', Arial, sans-serif;
                background-color: #f5f5f5;
            }

            .container {
                width: 100%;
                max-width: 900px;
                padding: 20px;
            }

            .titulo {
                position: relative;
                width: 100%;
                max-width: 700px;
                margin: 0 auto 20px;
            }

            .titulo img {
                display: block;
                width: 100%;
                height: 180px;
                object-fit: cover;
                border-radius: 15px;
            }

            .texto-sobreposto {
                position: absolute;
                inset: 0;
                display: flex;
                justify-content: center;
                align-items: center;
                color: white;
                font-weight: bold;
                font-size: 28px;
                background-color: rgba(0, 0, 0, 0.5);
                border-radius: 15px;
            }

            .pesquisa {
                display: flex;
                justify-content: center;
                gap: 8px;
                margin-bottom: 20px;
            }

            .pesquisa input {
                width: 300px;
                padding: 10px;
                border-radius: 5px;
                font-size: 16px;
            }

            button {
                padding: 10px 15px;
                color: black;
                font-weight: bold;
                border-radius: 5px;
                background-color: aquamarine;
                cursor: pointer;
            }

            button:hover {
                background-color: #66d9c0;
                transform: scale(1.05);
            }

            /* Caixa da tabela */
            .caixa {
                width: 100%;
                max-width: 900px;
                height: 45vh;
                margin: 0 auto;
                overflow-y: auto;
                overflow-x: auto;
                border: 2px solid black;
                background-color: white;
            }

            /* Tabela */
            table {
                width: 100%;
                border-collapse: collapse;
                min-width: 700px;
            }

            th {
                border: 2px solid black;
                padding: 10px;
                background-color: aquamarine;
                position: sticky;
                top: 0;
                z-index: 2;
            }

            td {
                border: 1px solid black;
                padding: 8px;
            }

            tbody tr:nth-child(even) {
                background-color: #f0f0f0;
            }

            /* Botões inferiores */
            .botoes {
                margin-top: 20px;
                display: flex;
                justify-content: center;
                gap: 15px;
            }

            /* Responsividade */
            @media (max-width: 600px) {

                .container {
                    padding: 10px;
                }

                .texto-sobreposto {
                    font-size: 20px;
                }

                .titulo img {
                    height: 130px;
                }

                .pesquisa {
                    flex-direction: column;
                    align-items: center;
                }

                .pesquisa input {
                    width: 100%;
                    max-width: 350px;
                }

                .botoes {
                    flex-direction: column;
                    align-items: center;
                }
            }
        </style>
    </head>

    <body>

        <div class="container">

            <!-- Cabeçalho -->
            <div class="titulo">
                <img src="https://www.ufsm.br/app/uploads/sites/668/2019/07/1170x308-crop-90-images_banner_3.jpg" alt="Laboratório de Piscicultura - UFSM">
                <div class="texto-sobreposto">Piscicultura - UFSM</div>
            </div>


            <!-- Pesquisa -->
            <div class="pesquisa">
                <input type="text" placeholder="Buscar..." id="campoBusca">
                <button type="button">Pesquisar</button>
            </div>


            <!-- Tabela -->
            <div class="caixa">

                <table id="mytabela">
                    <thead>
                        <tr>
                            <th>Nome</th>
                            <th>Data e Hora</th>
                            <th>Temperatura Interna [°C]</th>
                            <th>Temperatura Externa [°C]</th>
                            <th>pH</th>
                            <th>Oxigênio [mg/L]</th>
                            <th>Tensão [V]</th>
                            <th>Corrente [A]</th>
                            <th>Potência [W]</th>
                            <th>Condutividade Elétrica [μS/cm]</th>
                        </tr>
                    </thead>

                    <tbody>
                        <tr>
                            <td>Tanque 01</td>
                            <td>29/08/2026 18:00</td>
                            <td>25,4</td>
                            <td>24,8</td>
                            <td>7,2</td>
                            <td>6,5</td>
                            <td>12,0</td>
                            <td>0,45</td>
                            <td>2,0</td>
                            <td>50</td>
                        </tr>
                    </tbody>

                </table>

            </div>


            <!-- Botões -->
            <div class="botoes">

                <a href="/graphs"><button type="button">Mostrar Gráfico</button></a>

                <button type="button" onclick="baixarTabelaCSV()">Baixar</button>

            </div>

        </div>

        <script>
            function baixarTabelaCSV(){
                const tabela = document.getElementById('mytabela');
                let linhasCSV = [];
        
                for(let linhas of tabela.rows){
                    let dadosLinha = [];
                    for(let celula of linhas.cells){
                        let texto = celula.innerText.replace(/(\r\n|\n|\r)/gm, "").replace(/"/g, '""');
                        dadosLinha.push('"' + texto + '"');
                    }
                    linhasCSV.push(dadosLinha.join(';')); 
                }
                const conteudo = "\uFEFF" + linhasCSV.join('\n');
                const arquivo = new Blob([conteudo], { type: 'text/csv;charset=utf-8;' });
        
                const link = document.createElement('a');
                link.href = URL.createObjectURL(arquivo);
                link.download = 'dados-da-tabela.csv';

                document.body.appendChild(link);
                link.click();
                document.body.removeChild(link);
            }
        </script>

    </body>

</html>
)rawliteral";
 
const char* Graph_page = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <title>Laboratório de Piscicultura - Graph</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <script src="https://cdn.plot.ly/plotly-latest.min.js"></script>
        <style>
            body{
                margin: 0;
                min-height: 100vh;
                text-align: center;
                font-family: 'Franklin Gothic Medium', Arial, sans-serif;
            }

            h1{
                color: rgb(44, 44, 44);
                background-color: aquamarine;
                padding: 15px;
                margin: 0 0 25px 0;
                box-shadow: 0 2px 6px rgba(0,0,0,0.15);
                font-family:'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
            }

            select{
                background-color: aquamarine;
                margin: 0 0 25px 0;
                font-size: 20px;
                border-radius: 5px;
                font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
                color: darkcyan;
            }

            .graficos{
                display: flex;
                justify-content: center;
                gap: 20px;
                flex-wrap: wrap;
                padding: 0 20px;
            }

            .grafico{
                width: 600px;
                height: 400px;
                background-color: white;
                border: 1px solid #d5d5d5;
                border-radius: 12px;
                box-shadow: 0 3px 10px rgba(0,0,0,0.10);
                overflow: hidden;
            }
            button{
                color: white;
                margin: 25px 0;
                border: none;
                cursor: pointer;
                transition: 0.2s;
                background-color: rgb(235, 74, 74);
                font-family:'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
                border-radius:10px;
                font-weight: bold;
                width: 80px;
                height: 40px;
            }

            button:hover{
                background-color: rgb(210, 55, 55);
                transform: scale(1.05);
            }

        </style>
    </head>
    <body>
        
        <h1>Gráficos</h1>

        <select id="selecionar">
            <option>--- Selecione um tanque ---</option>
        </select>
        
        <div class="graficos">
                <div id= "tempera_in_temp" class="grafico"></div>
                <div id= "tempera_out_temp" class="grafico"></div>
                <div id= "ph_temp" class="grafico"></div>
                <div id= "oxi_temp" class="grafico" ></div>
                <div id= "corrent_temp" class="grafico"></div>
                <div id= "volt_temp" class="grafico"></div>
                <div id= "poten_temp" class="grafico" ></div>
                <div id= "cond_temp" class="grafico" ></div>
        </div>
        <br>
        <a href="/home"><button>Voltar</button></a>
        <script>
            const xArray = [1, 2, 3, 4, 5 ];
            const yArray = [1, 2, 3, 4, 5];

            function criarTrace(cor){
                return{
                    x: xArray,
                    y: yArray,
                    mode: 'lines+markers',
                    marker: {size: 8, color: cor},
                    line: {color: cor, width: 3}
                };
            }

            const config = {
                responsive: true,
                displayModeBar: false
            };

            function Layout(titulo, eixo_x, eixo_y){
                const layout = {
                    title: {text : titulo, font:{ size : 20}},
                    xaxis: {range: [0,6], title: eixo_x},
                    yaxis: {range: [0,6], title: eixo_y},
                };
                return layout;
            }

            Plotly.newPlot("tempera_in_temp", [criarTrace('red')], Layout("Temperatura Interna X Tempo", "Tempo [s]", "Temperatura Interna [°C]"),config);
            Plotly.newPlot("tempera_out_temp", [criarTrace('blue')], Layout("Temperatura Externa X Tempo", "Tempo [s]", "Temperatura Externa [°C]"),config);
            Plotly.newPlot("ph_temp", [criarTrace('42F32B')], Layout("pH X Tempo", "Tempo [s]", "pH"),config);
            Plotly.newPlot("corrent_temp", [criarTrace('FF391F')], Layout("Corrente X Tempo", "Tempo [s]", "Corrente [A]"),config);
            Plotly.newPlot("volt_temp", [criarTrace('4B6EBE')], Layout("Tensão X Tempo", "Tempo [s]", "Tensão [V]"),config);
            Plotly.newPlot("poten_temp", [criarTrace('AD4FCF')], Layout("Potência  X Tempo", "Tempo [s]", "Potência [W]"),config);
            Plotly.newPlot("oxi_temp", [criarTrace('#00a6c7')], Layout("Oxigênio  X Tempo", "Tempo [s]", "Oxigênio [mg/L]"),config);
            Plotly.newPlot("cond_temp", [criarTrace('yellow')], Layout("Condutividade Elétrica  X Tempo", "Tempo [s]", "Condutividade Elétrica [μS/cm]"),config);
        </script>

    </body>
</html>
)rawliteral"; 

NetworkServer server(80);

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssd, pass); // ajustar quando chegar no lab.
  Serial.begin(115200);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  Serial.print("MAC: ");
  Serial.print(WiFi.macAddress());
  Serial.println();
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
  
  //pinMode(x, OUTPUT);
  server.begin();
}

void loop() {
    NetworkClient client = server.accept();
    
    if(client){
      String currentLine = "";
      String request = "";
      while(client.connected()){
        if(client.available()){
          char cr = client.read();
          if(cr == '\n'){
            if(currentLine.length() == 0){
              
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();
              

              // Aqui coloca o .HTML
              if(request.indexOf("GET /home") >= 0){
                client.print(Home_page);
              }else if(request.indexOf("GET /graphs")>= 0){
                client.print(Graph_page);
              }else if(request.indexOf("GET /login")>= 0){
                int inicioUsuario = request.indexOf("usuario=") + 8;
                int inicioSenha = request.indexOf("senha=") + 6;

                String usuarioRecebido = request.substring( inicioUsuario, request.indexOf("&senha=") );
                
                int fimSenha = request.indexOf(" ", inicioSenha);

                String senhaRecebida = request.substring( inicioSenha, fimSenha );

                Serial.println("Usuario recebido: " + usuarioRecebido);
                Serial.println("Senha recebida: " + senhaRecebida);

                if(usuarioRecebido == usuario && senhaRecebida == senha){
                  client.print(Home_page);
                }else{
                  client.print(Login_page);
                }
                
              }else{
                client.print(Login_page);
              }
              //client.print(Login_page);
              
              client.println();
              break;
            }else{

              if(request.length() == 0){
                request = currentLine;
              }
              
              currentLine = "";
            }  
          }else if(cr != '\r'){
            currentLine += cr;
          }

          // Aqui coloca a funcao de cada click do botao.
          /*
          if(currentLine.endsWith("GET /home")){
                client.print(Home_page);
          }
          */
        }
      }
      client.stop();
    }
}
