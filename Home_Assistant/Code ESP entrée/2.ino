#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

#define DHT11_PIN 2
DHT dht11(DHT11_PIN, DHT11);

#define TRIG_PIN 5
#define ECHO_PIN 4

long duree;
float distance;

int sensorValue;

bool inside = true;
bool activate = true;

const int PIN_TO_SENSOR = 13;
int pinStateCurrent = LOW;
int pinStatePrevious = LOW;

const int TILT_PIN = 13;
int lastState = -1;

#define RST_PIN 0
#define SS_PIN 15

MFRC522 mfrc522(SS_PIN, RST_PIN);

const int PIR_PIN = 14;

// --- CONFIGURATION ---
const char* ssid = "Freebox-444B2E";
const char* password = "deletor&-disuasum74-saltatrix73-fluctuum2";
const char* mqtt_server = "192.168.1.111";

WiFiClient esp;
PubSubClient client(esp);

const char* mqtt_user = "esp_entree";
const char* mqtt_mdp = "grlu8RTYn";

void setup_wifi() {
  delay(10);
  Serial.print("\nConnexion a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connecte !");
  Serial.println("adresse ip: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    const char* willTopic = "entree/status";
    const char* willMessage = "offline";
    bool willRetain = true;
    int willQos = 1;

    if (client.connect("esp_entree", mqtt_user, mqtt_mdp, willTopic, willQos, willRetain, willMessage)) {
      Serial.println("Connecté au Broker !");      
      client.publish(willTopic, "online", true); 
    } 
    else {
      Serial.print("Echec, code d'erreur = ");
      Serial.print(client.state());
      Serial.println(" Réessai dans 5 secondes");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht11.begin();
  Wire.begin(4, 5);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Lecteur RFID RC522 Prêt !");
  pinMode(PIN_TO_SENSOR, INPUT);
  pinMode(TILT_PIN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  statusCap();
  defDist();
}

void recupDonnees() {
  int envoie = 0;
  //capteur d'humidité
  float humi  = dht11.readHumidity();
  float temp = dht11.readTemperature();

  if (isnan(humi) || isnan(temp)) {
    Serial.println("Echec de lecture du capteur DHT11");
  } 
  else {
    String tempStr = String(temp);
    String humiStr = String(humi);

    client.publish("entree/temp", tempStr.c_str(), true);
    client.publish("entree/humi", humiStr.c_str(), true);
  }

  /*--------------capteurs à peut-être rajouter dans le futur-----------------------------
//capteur qualité de l'air
  sensorValue = analogRead(A0);
  Serial.print("Qualité de l'air= ");
  Serial.println(sensorValue);

  //qualité de l'air
  char gaz[10];
  snprintf(gaz, 10, "%d", sensorValue);
  Serial.println(gaz);
  client.publish("coeur/fumee", gaz, true);
*/
}

void defDist() {
  int distanceN;
  distance = securite();
  distanceN = distance;
}

void statutCap() {
  if ()
}

void securite() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duree = pulseIn(ECHO_PIN, HIGH);
  distance = (duree * 0.034) / 2;
  
  if (distance < distanceN -1) {
    Serial.println("la porte est ouverte");
    client.publish("entree/porte", true);//à vérifier
    if (distanceN - 1 < distance < distanceN + 1) {
      Serial.println("dans les normes de distance");
      if (distance > distanceN + 1) {
        Serial.println("la porte est ouverte")
        client.publish("entree/porte", "true");//à vérifier 
      }
    }
  }

/*-------------------------------------------*/

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("Badge RFID trouvé ! UID: ");
    
    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      if (mfrc522.uid.uidByte[i] < 0x10) uidString += "0";
      uidString += String(mfrc522.uid.uidByte[i], HEX);
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println("");
    
    uidString.toUpperCase();
    client.publish("entree/RFID", uidString.c_str(), true);
    
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

/*-------------capteurs à peut-être rajouter dans le futur--------------------------------

//capteur de vibrassion
  int currentState = digitalRead(TILT_PIN);
  if (currentState != lastState) {
    if (currentState == LOW) {
      Serial.println("Statut : Capteur activé (Inclinaison/Humide)");
      client.publish("coeur/vibr", "1", true);
    } else {
      Serial.println("Statut : Capteur au repos (Vertical/Sec)");
      client.publish("coeur/vibr", "0", true);
    }
    lastState = currentState;
  }

/*-------------------------------------------

//capteur de mouvement
  int val = digitalRead(PIR_PIN);
  if (val == HIGH) {
    Serial.println(">>> MOUVEMENT DÉTECTÉ !");
    client.publish("coeur/mouv", "MOUVEMENT DÉTECTÉ !");
    
  } else {
    Serial.println("RAS");
    client.publish("coeur/mouv", "RAS", true);
  }
-------------------------------------------*/
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  recupDonnees();
  securite();
  delay(60000)
