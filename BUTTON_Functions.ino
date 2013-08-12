
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

int pressed = 0;

char pressArray[0];



void button(String command, int pin, String param1, String param2)
{
  if(debug == 1)
  {
    Serial.println("led hit");
    Serial.println(param2);
  }
  
  if (command.equals("setup")) 
  {
    if(debug == 1)
    {
      Serial.println("setup hit");
    }
    button_setup(pin, param1, param2); 
  }
}


void button_setup(int pin, String param1, String param2)
{
  if(debug == 1){
    Serial.println("Inside Button Setup");
  }
  
  String  message = param2; // holds text not yet split
  int     commaPosition;  // the position of the next comma in the string
          
  pins = String(pin);//.toString();                
  pressed = 0;
  
  do
  {
      commaPosition = message.indexOf('-');
      if(commaPosition != -1)
      {
          if(debug == 1){
            Serial.println("Setup Pin 1");
            Serial.println( message.substring(0,commaPosition));
          }
                    
          int buttonPin = message.substring(0,commaPosition).toInt();
          pinMode(buttonPin, INPUT);     
          message = message.substring(commaPosition+1, message.length());
      }
      else 
      { 
        if(debug == 1)
        {                
          Serial.println("Setup Pin 2");
          //Serial.println( message.substring(0,commaPosition));
          Serial.println(pin); 
        }
       
        int buttonPin = pin;//essage.substring(0,commaPosition).toInt();
        pinMode(pin, INPUT);   
       
        message = message.substring(pin, message.length());
      }
   }
   while(commaPosition >=0);
}


void button_checkState()
{
  String  pinStore = pins; // holds text not yet split
  int     sepPosition;  // the position of the next comma in the string
  do
  {
      sepPosition = pinStore.indexOf('-');
      if(sepPosition != -1)
      {                    
          int buttonPin = pinStore.substring(0,sepPosition).toInt();
           buttonState = digitalRead(buttonPin);

          if (buttonState == HIGH) 
          {   
            if(pressArray[buttonPin] < 1)
            {
                  String output = "b";
                  output.concat(buttonPin);
                  Serial.println(output);
                pressArray[buttonPin]++;
            }
          }
          if(buttonState == LOW) 
          {
            pressArray[buttonPin] = 0;
          }
          pinStore = pinStore.substring(sepPosition+1, pinStore.length());
      }
      else
      { 
        //Serial.println("Pin Store");
        //Serial.println(pinStore);
         int buttonPin = pinStore.substring(0,sepPosition).toInt();
           buttonState = digitalRead(buttonPin);

          if (buttonState == HIGH) 
          {   
              
            if(pressArray[buttonPin] < 1)
            {
                  String output = apiKey;
                  output.concat("-");
                  output.concat(appName);
                  output.concat("-b-");
                  output.concat(buttonPin);
                  Serial.println(output);
                pressed++;
                pressArray[buttonPin]++; 
            }
          }
          if(buttonState == LOW) 
          {
            pressArray[buttonPin] = 0;
          }
          pinStore = pinStore.substring(sepPosition+1, pinStore.length());
      }
   }
   while(sepPosition >=0);

}
