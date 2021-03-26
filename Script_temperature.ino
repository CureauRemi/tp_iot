#include <OneWire.h>

// ---------- Initialisation des variables ---------------------

// Variables propres au DS18B20
const int PIN_SONDE =10;
const int PIN_LED = 2;
const int SONDE_ID=0x28;
// Déclaration de l'objet ds
OneWire ds(PIN_SONDE); // DS18B20_PIN (Une résistance 4.7k est nécessaire)

// Variables générales
float DS18B20_temperature;
const int SERIAL_PORT=9600;
int timer=0;

// Inversion des clignotements
bool message = false;

void setup() {
// Initialisation du port de communication avec le PC
Serial.begin(SERIAL_PORT);
pinMode(PIN_LED, OUTPUT);
}

void loop() { 
  
  
  // Récupération de la température
  DS18B20_temperature = getTemperatureDS18b20();
   
  message = Serial.read();
  if(message == true){
    digitalWrite(PIN_LED, LOW);
    delay(200);
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, HIGH);
    delay(200);
    digitalWrite(PIN_LED, LOW);
  }

  // on affiche la température
  Serial.println(DS18B20_temperature);
  
}


float getTemperatureDS18b20(){
  byte i;
  byte data[12];
  byte addr[8];
  float temp =0.0;

  ds.search(addr);
  if (OneWire::crc8( addr, 7) != addr[7]) {
    Serial.println("Sonde : <!> ERREUR INVALIDE <!>");
    return false;
  }

  // On vérifie que l'élément trouvé est bien un DS18B20
  if (addr[0] != SONDE_ID) {
    Serial.println("L'équipement trouvé n'est pas un DS18B20");
    return false;
  }

  // Demander au capteur de mémoriser la température et lui laisser 800ms pour le faire
  ds.reset();
  ds.select(addr);
  ds.write(0x44);
  
  // Délai de 800ms car le capteur n'a pas le temps de récupérer les valeurs si on met une valeur plus basse en ms 
  delay(800);
  
  // Demander au capteur de nous envoyer la température
  ds.reset();
  ds.select(addr);
  ds.write(0xBE);

  // Le MOT reçu du capteur fait 9 octets, on les charge donc un par un dans le tableau data[]
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  // Puis on convertit la température (*0.0625 car la température est stockée sur 12 bits)
  temp = ( (data[1] << 8) + data[0] )*0.0625;
  
  return temp;
}
