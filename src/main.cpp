#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <time.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <AsyncElegantOTA.h>


#define TIMELOOP 15000 // Temps de traitement 3 sec
#define SEALEVELPRESSURE_HPA (1013.25)
#define sensorPin  33 //Broche capteur de lumiere
#define ledPin 13 //Broche LED
#define pinWind 4 //Broche du capteur de vent 
#define sensorPluie 32 //Broche du capteur de pluie

//Declaration des constantes

const float PERIOD_MES = TIMELOOP / 1000;
const float MILE_TO_KILO = 1.60934;

//Declaration des variables

unsigned long presentMillis = 0 ;



const char* ssid = "lathytharma";
const char* password = "theking5";

// const char* ssid = "UNIFI_IDO1";
// const char* password = "42Bidules!";


const char* FILE_NAME = "/data.json"; // Dossier des donnees 




AsyncWebServer server(80);
Adafruit_BME280 bme;



void setup() {

  Serial.begin(115200);
  
  // Check BME280 sensor
	if (!bme.begin(0x76)) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
		while (1);
	}

  // Se connecter au WiFi vec (ssid, password) 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {   // Wait for connection
    delay(500);
    Serial.print("-");
  }
  
  // Print ESP Local IP Address 
  Serial.println();
  Serial.println();
  Serial.println(WiFi.localIP());
  Serial.println("Connecté au WiFi.");


  // Configration de time Zone et rechuprer la date et heure courant

  configTime(0, 0, "ca.pool.ntp.org", "time.nist.gov");
  time_t timestamp = time(NULL);

  
  // Vérification  de la Biblio SPIFFS

  if(!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Si le fichier n'existe pas, crée un nouveau tableau JSON
  if(!SPIFFS.exists(FILE_NAME)) {
    DynamicJsonDocument doc(90000);
    JsonArray array = doc.to<JsonArray>();
    File file = SPIFFS.open(FILE_NAME, FILE_WRITE);
    serializeJson(doc, file);
    file.close();
  }


  // Servir les fichiers HTML, CSS et JS depuis le système de fichiers SPIFFS (index.html)
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Start ElegantOTA To update project 
  AsyncElegantOTA.begin(&server);    

  // Lancer le serveur
  server.begin();
}



void loop() {
// ---------------------------------------
// ------- TRAINTEMENT DES DONNEES -------
// ---------------------------------------



  // Obtenir le temps actuel en timestamp
  presentMillis = millis();
  time_t timestamp = time(NULL);
  
  

// ------------------------------------------
// --------- STOCKAGE DES DONNEES -----------
// ------------------------------------------

  
  // Ouvre le fichier JSON en mode lecture-écriture
  File file = SPIFFS.open(FILE_NAME, "r+");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  // Parse le contenu du fichier JSON en un tableau d'objets JSON

  DynamicJsonDocument doc(1024);
  //deserializeJson(doc, file);

  // Ajoute un nouvel objet JSON au tableau

  JsonObject obj = doc.createNestedObject();
  obj["date"] = timestamp; // Ajouter la date
  obj["temperature"] = round(bme.readTemperature() * 100.0) / 100.0; // Ajouter la temperature
  obj["pressure"] = round((bme.readPressure() / 100.0F) * 100.0) / 100.0; // Ajouter le pressure
  obj["humidity"] = round(bme.readHumidity() * 100.0) / 100.0; // Ajouter l'humidite
  // obj["luminosity"] = round(sensorValue * 100.0) / 100.0; // Ajouter luminosite
  // obj["wind"] = windSpeed; // Ajouter luminosite
  // obj["rain"] = sensorValeurPluie; // Ajouter luminosite

  // Écrit le contenu du tableau dans le fichier JSON

  file.seek(0); 
  serializeJson(doc, file);
  file.close();

  delay(TIMELOOP);
}