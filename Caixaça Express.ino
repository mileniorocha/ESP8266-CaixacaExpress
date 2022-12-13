#include <ESP8266WiFi.h>
// Nome da Rede
const char* ssid = "TI"; 
// Senha da Rede
const char* senha = "12345678"; 

// Porta 80 - Servidor Web
WiFiServer server(80); 

// RELE PINO 2
int rele = 5;

unsigned long millisReleLigado = millis();

void setup() {

  Serial.begin(115200);

  delay(10);

  // Define o rele (pino 2) como saída
  pinMode(rele, OUTPUT); 

  // Rele inicia desligado
  digitalWrite(rele, LOW); 

  // Comunicação com a rede WiFi
  Serial.println();
  Serial.println();

  // Frases que aparecem no Monitor Serial
  Serial.print("Conectando no Wi-Fi ");
  Serial.print(ssid);
  Serial.print(" ... ");

  // Inicia a ligação a rede
  WiFi.begin(ssid, senha); 

  // Se a conexão falhar entra
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); 
  }

  Serial.println("");

  // Se obter conexão irá aparecer a mensagem 
  Serial.println("Wi-Fi Conectado"); 

  // Inicia comunicação com o servidor
  server.begin();
  Serial.println("Servidor iniciado");

  // IP Para conexão
  Serial.print("Use o seguinte URL para a comunicação: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

  void loop() {

    // Verificação se o cliente está conectado
    WiFiClient client = server.available();
    // Se o cliente estiver conectado na rede o mesmo irá continuar o loop
    if (!client) { 

    return;
  }

  //Apresenta esta mensagem quando o cliente se liga ao servidor
  Serial.println("Servidor - Novo Cliente"); 
  while(!client.available()){
  delay(1);

}

  // Ler a primeira linha do pedido
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

// Operação do pedido
 
  int value = LOW;

  if (request.indexOf("/LED=ON") != -1)  {

    digitalWrite(rele, HIGH); // Se o pedido no LedPin for LED=ON, acende o LED
    delay(10000);
    digitalWrite(rele, LOW);
    value = LOW;
  }
  
  if (request.indexOf("/LED=OFF") != -1)  {

  digitalWrite(rele, LOW); // Se o pedido no LedPin for LED=OFF, apaga o LED

  value = LOW;
  }
  
// Inicialização da página HTML
// Retorno do resposta
client.println("HTTP/1.1 200 OK");

client.println("Content-Type: text/html");

client.println(""); //  do not forget this one

client.println("<!DOCTYPE HTML>");

client.println("<html lang='pt'>");

client.print("<head>");
  client.print("<meta charset='UTF-8'>");
  client.print("<meta http-equiv='X-UA-Compatible' content='IE=edge'>");
  client.print("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
      client.print("<style>");
        client.print("article { background: #f2f2f2; padding: 1.3em; }");
        client.print("body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }");
        client.print("div { padding: 0.5em; }");
        client.print("h1 { margin: 0.5em 0 0 0; padding: 0.5em; }");
        client.print("input { width: 100%; padding: 9px 10px; margin: 8px 0; box-sizing: border-box; border-radius: 0; border: 1px solid #8886865c; border-radius: 5px; background-color: #918f8f11;}");
        client.print("label { color: #333; display: block; font-style: italic; font-weight: bold; }");
        client.print("nav { display: block; font-size: 1.3em; padding: 1em; text-align: center;}");
        client.print("nav b { display: block; font-size: 1.5em; margin-bottom: 0.5em; }");
        client.print("nav p {font-size: 0.8em;}");
        client.print("textarea { width: 100%; }");
        client.print("button { width: 150px; height: 150px; font-size: 40px; text-align: center; text-decoration: none; }");
        client.print("button a { font-size: 40px; text-align: center; text-decoration: none; }");
      client.print("</style>");
client.print("</head>");
client.print("<nav><img src='data:image/jpeg;base64,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'></nav>");
client.print("<br><br>");
client.print("<nav>");
client.println("<a href=\"/LED=ON\"\"><center><button>Servir </button></center></a>");
client.println("</nav>");
client.println("<br><br><br><br><br>");
client.println("<nav><img src='data:image/png;base64, iVBORw0KGgoAAAANSUhEUgAAAUYAAABICAMAAAC9dKwGAAAHF2lUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNi4wLWMwMDIgNzkuMTY0NDYwLCAyMDIwLzA1LzEyLTE2OjA0OjE3ICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOmRjPSJodHRwOi8vcHVybC5vcmcvZGMvZWxlbWVudHMvMS4xLyIgeG1sbnM6cGhvdG9zaG9wPSJodHRwOi8vbnMuYWRvYmUuY29tL3Bob3Rvc2hvcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RFdnQ9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZUV2ZW50IyIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgMjEuMiAoV2luZG93cykiIHhtcDpDcmVhdGVEYXRlPSIyMDIxLTA4LTI3VDE5OjM3OjMxLTAzOjAwIiB4bXA6TW9kaWZ5RGF0ZT0iMjAyMS0wOC0zMVQyMDo0NzozMC0wMzowMCIgeG1wOk1ldGFkYXRhRGF0ZT0iMjAyMS0wOC0zMVQyMDo0NzozMC0wMzowMCIgZGM6Zm9ybWF0PSJpbWFnZS9wbmciIHBob3Rvc2hvcDpDb2xvck1vZGU9IjMiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6ZTRkZmM4MTQtNDk0ZS05MTQ0LWJlMDMtZmUyMTgwYWI3OWYxIiB4bXBNTTpEb2N1bWVudElEPSJ4bXAuZGlkOmQ5ZTFjNmQ5LWJjYjAtM2M0ZS04ZTk2LTliMTBmZWZhZjQ4ZiIgeG1wTU06T3JpZ2luYWxEb2N1bWVudElEPSJ4bXAuZGlkOmQ5ZTFjNmQ5LWJjYjAtM2M0ZS04ZTk2LTliMTBmZWZhZjQ4ZiI+IDxwaG90b3Nob3A6RG9jdW1lbnRBbmNlc3RvcnM+IDxyZGY6QmFnPiA8cmRmOmxpPnhtcC5kaWQ6NTYyMjlkY2EtMzUxYy0xMjQzLWExZWItNjU5MWEzNjFlMzYzPC9yZGY6bGk+IDwvcmRmOkJhZz4gPC9waG90b3Nob3A6RG9jdW1lbnRBbmNlc3RvcnM+IDx4bXBNTTpIaXN0b3J5PiA8cmRmOlNlcT4gPHJkZjpsaSBzdEV2dDphY3Rpb249ImNyZWF0ZWQiIHN0RXZ0Omluc3RhbmNlSUQ9InhtcC5paWQ6ZDllMWM2ZDktYmNiMC0zYzRlLThlOTYtOWIxMGZlZmFmNDhmIiBzdEV2dDp3aGVuPSIyMDIxLTA4LTI3VDE5OjM3OjMxLTAzOjAwIiBzdEV2dDpzb2Z0d2FyZUFnZW50PSJBZG9iZSBQaG90b3Nob3AgMjEuMiAoV2luZG93cykiLz4gPHJkZjpsaSBzdEV2dDphY3Rpb249InNhdmVkIiBzdEV2dDppbnN0YW5jZUlEPSJ4bXAuaWlkOmU4ODQ3OTFkLTkzMDktMzI0ZC1hODg3LTNlMzZhNjBkOTY3YSIgc3RFdnQ6d2hlbj0iMjAyMS0wOC0zMVQyMDo0MzozNS0wMzowMCIgc3RFdnQ6c29mdHdhcmVBZ2VudD0iQWRvYmUgUGhvdG9zaG9wIDIxLjIgKFdpbmRvd3MpIiBzdEV2dDpjaGFuZ2VkPSIvIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJzYXZlZCIgc3RFdnQ6aW5zdGFuY2VJRD0ieG1wLmlpZDplNGRmYzgxNC00OTRlLTkxNDQtYmUwMy1mZTIxODBhYjc5ZjEiIHN0RXZ0OndoZW49IjIwMjEtMDgtMzFUMjA6NDc6MzAtMDM6MDAiIHN0RXZ0OnNvZnR3YXJlQWdlbnQ9IkFkb2JlIFBob3Rvc2hvcCAyMS4yIChXaW5kb3dzKSIgc3RFdnQ6Y2hhbmdlZD0iLyIvPiA8L3JkZjpTZXE+IDwveG1wTU06SGlzdG9yeT4gPC9yZGY6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'/></nav>");
client.println("</html>");

delay(1);

Serial.println("Servidor - Cliente Desconectado"); // Depois do cliente efectuar o pedido apresenta esta mensagem no monitor série

Serial.println("");
}