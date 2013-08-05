
void led(String command, int pin, String param1, String param2)
{
  if(debug == 1){
    Serial.println("led hit");
    Serial.println(param2);
  }
  
  if (command.equals("blink")) {
    if(debug == 1){
      Serial.println("blink hit");
    }
    led_blinkIt(pin, param1, param2); 
  }
  if (command.equals("customBlink")) {
    if(debug == 1){
      Serial.println("custom blink hit");
    }
    led_customBlink(pin, param1, param2); 
  }
  if (command.equals("togglePins")) {
    if(debug == 1){
      Serial.println("toggle pin hit");
    }
    led_togglePins(param1, param2); 
  }  
  
}


//Blinks LED based onPin, Blink Count, and Blink Speed
void led_blinkIt(int pin, String param1, String param2)
{
  pinMode(pin, OUTPUT); // set ping 13 as output

  if(debug == 1){
    Serial.println("blink it hit");
  }
  
  int count =  param1.toInt();
  int blinkSpeed =  param2.toInt();
     
  if(debug == 1){
    Serial.println(count);
    Serial.println(blinkSpeed);
  }

  for(int i=0;i < count; i++) {    
    digitalWrite(pin, HIGH);
    delay(blinkSpeed);
    digitalWrite(pin, LOW);
    delay(blinkSpeed);
  }
}

void led_customBlink(int pin, String param1, String param2)
{
  if(debug == 1){
    Serial.println("Inside Custom Blink");
  }
  
  String  message = param2; // holds text not yet split
  int     commaPosition;  // the position of the next comma in the string
          
  do
  {
      commaPosition = message.indexOf('-');
      if(commaPosition != -1)
      {
          if(debug == 1){
            Serial.println( message.substring(0,commaPosition));
          }
          
          led_blinkIt(pin, param1, message.substring(0,commaPosition));           
          
          message = message.substring(commaPosition+1, message.length());
      }
      else
      {  // here after the last comma is found
         if(message.length() > 0)
           led_blinkIt(pin, param1, message.substring(0,commaPosition));           
      }
   }
   while(commaPosition >=0);
}

void led_togglePins(String pins, String toggleState)
{
  if(debug == 1){
    Serial.println("Inside toggle Pins");
  }
  
  String  message = pins; // holds text not yet split
  int     commaPosition;  // the position of the next comma in the string
   
  do
  {
      commaPosition = message.indexOf('-');
      if(commaPosition != -1)
      {
       // Serial.println(state);
        
          //Serial.println( message.substring(0,commaPosition));
          int pin =  message.substring(0,commaPosition).toInt();
           if (toggleState.equals("on")) {
              if(debug == 1){
                Serial.println("HEREEE");
              }
              digitalWrite(pin, HIGH);
            }
            if (toggleState.equals("off")) {
              digitalWrite(pin, LOW);
            }

          message = message.substring(commaPosition+1, message.length());
      }
      else
      {
      }
   }
   while(commaPosition >=0);
}

