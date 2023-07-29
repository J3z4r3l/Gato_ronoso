#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_WIDTH 82;
#define LOGO_HEIGHT 40;

//Imagen 1

// Arreglos para almacenar las frecuencias y duraciones de las notas
const int notes[] = {740, 831, 554, 622, 494, 587, 554, 494, 494, 554, 587, 587, 554, 494, 554, 622,  587, 494, 554, 622, 587, 554, 494, 554, 587, 494, 554, 587, 740, 554, 587};
const int durations[] = {214, 107, 107, 214, 54, 107, 107, 107, 107, 214, 107, 54, 54, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 214, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107};
int buzzerPin = 9; // Reemplaza 9 con el número de pin que estás utilizando
//boton
int boton_Pin= 7;
int estadoBoton=LOW;
int ultimoEstadoBoton=LOW;
  

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(boton_Pin, INPUT);
}

// Función para reproducir la canción
void playSong(int buzzerPin, int songLength) {
  for (int i = 0; i < songLength; i++) {
    tone(buzzerPin, notes[i]);
    delay(durations[i]);
    noTone(buzzerPin);
  }
}


void loop() {
  //escribimos para cambiar el estado del boton
  estadoBoton = digitalRead(boton_Pin);
  //Ahora le decimos que si su ultimo estado es "apagado" y recibe prendido active el bucle 
  if(estadoBoton== HIGH && ultimoEstadoBoton ==LOW){
    //para no obtener su longitud en bytes lo que hacemos es dividir entre la longitud en este caso de una nota, asi nos da la cantidad de elementos
    int songLength = sizeof(notes) / sizeof(notes[0]); // Calcular la longitud del arreglo
    playSong(buzzerPin, songLength);
    playSong(buzzerPin, songLength);
    
    }
  ultimoEstadoBoton = estadoBoton; 
}
