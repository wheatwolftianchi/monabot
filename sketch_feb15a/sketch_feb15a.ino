#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include <vector>
#include <string>
#include "Mona_ESP_lib.h"

void flash(){
  Set_LED(1, 255, 0, 0);
  Set_LED(2, 0, 0, 255);
  delay(1000);
  Set_LED(1, 0, 0, 255);
  Set_LED(2, 255, 0, 0);
  delay(1000);
  Set_LED(1, 255, 0, 0);
  Set_LED(2, 0, 0, 255);
  delay(1000);
  Set_LED(1, 0, 0, 255);
  Set_LED(2, 255, 0, 0);
  delay(1000);
  Set_LED(1, 255, 0, 0);
  Set_LED(2, 0, 0, 255);
  delay(1000);
  Set_LED(1, 0, 0, 255);
  Set_LED(2, 255, 0, 0);
  delay(1000);
  Set_LED(1, 255, 0, 0);
  Set_LED(2, 0, 0, 255);
  delay(1000);
  Set_LED(1, 0, 0, 255);
  Set_LED(2, 255, 0, 0);
  delay(1000);
  Set_LED(1, 255, 0, 0);
  Set_LED(2, 0, 0, 255);
  delay(1000);
  Set_LED(1, 0, 0, 255);
  Set_LED(2, 255, 0, 0);
  delay(1000);
  Set_LED(1, 255, 0, 0);
  Set_LED(2, 0, 0, 255);
  delay(1000);
  Set_LED(1, 0, 0, 255);
  Set_LED(2, 255, 0, 0);
  delay(1000);
  Set_LED(1, 255, 0, 0);
  Set_LED(2, 0, 0, 255);
  delay(1000);
  Set_LED(1, 0, 0, 255);
  Set_LED(2, 255, 0, 0);
  delay(1000);
  Set_LED(1, 255, 0, 0);
  Set_LED(2, 0, 0, 255);
  delay(1000);
  Set_LED(1, 0, 255, 0);
  Set_LED(2, 0, 255, 0);
}

std::vector<std::string> separate_string(const std::string& input_str) {
  std::vector<std::string> output_list;
  std::string temp;

  for (size_t i = 0; i < input_str.length(); ++i) {
    char c = input_str[i];

    if (isdigit(c)) {
      temp += c;
    } else {
      if (!temp.empty()) {
        output_list.push_back(temp);
        temp.clear();
      }
      output_list.push_back(std::string(1, c));
    }
  }

  if (!temp.empty()) {
    output_list.push_back(temp);
  }

  return output_list;
}


int initialize_left = 100;
int initialize_right = 93;
int state = 0;
void setup() {
  // put your setup code here, to run once:
  // read from the serial port, wait for the port to open:
  
  //Serial.println("hi");
  Mona_ESP_init();
  Serial.begin(9600);
  // initialize left and right motors
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    state = Serial.parseInt();
    Serial.println(state);
    if (Serial.read() == '\n'){
      //do nothing
    }
  }
  if(state == 0){
    Motors_stop();
  }
    
  if(state == 1){
  // Start moving Forward but using initialize_left and initialize_right to make it stright
  // use multi thread to make it move forward use the left and right motor seperate conmtrol
    Right_mot_forward(initialize_right);
    Left_mot_forward(initialize_left);
  
  }
  if(state == 2){
  //Spin to the left
    Motors_spin_left(60);
  }
  if(state == 3){
  //Spin to the right
    Motors_spin_right(60*initialize_left/initialize_right);
  }
  if(state == 4){
    flash();
    delay(1000);
    Set_LED(1, 0, 255, 0);
    Set_LED(2, 0, 255, 0);
    Right_mot_forward(initialize_right);
    Left_mot_forward(initialize_left);
    delay(20000);
    Motors_stop();
    Motors_spin_left(60);
    delay(1000);
    Motors_stop();
    Right_mot_forward(initialize_right);
    Left_mot_forward(initialize_left);
    delay(10000);
    Motors_stop();
    Set_LED(1, 0, 0, 0);
    Set_LED(2, 0, 0, 0);
    state = 0;
  }
  if(state == 5){
    Set_LED(1, 0, 255, 255);
    Set_LED(2, 0, 255, 255);
    delay(1000);
    //wair untill Serial.available() > 0
    //read the input
    while (Serial.available() == 0)
    {
      delay(1000);
    }
    if (Serial.available() > 0) {
      std::string input_str = "";
      while (Serial.available() > 0) {
        Set_LED(1, 0, 255, 0);
        Set_LED(2, 0, 255, 0);
        char c = (char)Serial.read();
        input_str += c;
        delay(10);  // Short delay for stability
      }
      flash();
      std::vector<std::string> output_list = separate_string(input_str);
      for (const auto& elem : output_list) {
        Serial.println(elem.c_str());
        if (elem == "f")
        {
          Serial.println("fffffffff");
          Right_mot_forward(initialize_right);
          Left_mot_forward(initialize_left);
        }
        if (elem == "b")
        {
          Serial.println("bbbbbbbbb");
          Right_mot_backward(initialize_right);
          Left_mot_backward(initialize_left);
        }
        if (elem == "l")
        {
          Serial.println("llllllllll");
          Motors_spin_left(60);
        }
        if (elem == "r")
        {
          Serial.println("rrrrrrrrrrrr");
          Motors_spin_right(60*initialize_left/initialize_right);
        }
        if (elem == "s")
        {
          Serial.println("ssssssssss");
          Motors_stop();
        }
        //if its a number
        if (isdigit(elem[0]))
        {
          delay(std::stoi(elem)*1000);
          Serial.println(elem.c_str());
          Motors_stop();
        }
      }
    }
  delay(100);
  state = 0;
  Set_LED(1, 0, 0, 0);
  Set_LED(2, 0, 0, 0);
  }
  
}
