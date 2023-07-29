const int botonPin = 9;   // Pin del botón
const int ledPin = 10;    // Pin del LED

int estadoBoton = LOW;    // Variable para almacenar el estado del botón
int estadoLED = LOW;      // Variable para almacenar el estado del LED
int ultimoEstadoBoton = LOW;  // Variable para almacenar el último estado del botón

void setup() {
  pinMode(botonPin, INPUT);   // Configurar el pin del botón como entrada
  pinMode(ledPin, OUTPUT);    // Configurar el pin del LED como salida
}

void loop() {
//leemos el estado del boton si esta apachurrado es low y solo esta high mientas se apachurra
//
  estadoBoton = digitalRead(botonPin);   // Leer el estado actual del botón

  // Verificar si se ha producido un flanco de subida
  if (estadoBoton == HIGH && ultimoEstadoBoton == LOW) {
    // Cambiar el estado del LED
    if (estadoLED == LOW) {
      estadoLED = HIGH;
    } else {
      estadoLED = LOW;
    }

    digitalWrite(ledPin, estadoLED);   // Encender o apagar el LED según el estado
  }

  ultimoEstadoBoton = estadoBoton;  // Almacenar el estado actual del botón como último estado
}
