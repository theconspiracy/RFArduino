
// Buffer for the incoming data
char inData[100];

// Buffer for the parsed data chunks
char *inParse[100];

// Storage for data as string
String inString = "";

// Incoming data id
int index = 0;

// Read state of incoming data
boolean stringComplete = false;

String pins = "";

//Debug mode
int debug = 1;

void setup()  
{  
  // Initialise the serial port
  Serial.begin(9600);
  Serial.println("Rd");
}

void loop() 
{
  if(pins != ""){
    button_checkState();
  }

  if (stringComplete) 
  {
    // Parse the recieved data
    ParseSerialData();
    // Reset inString to empty
    inString = "";    
    // Reset the system for further 
    // input of data   
    stringComplete = false; 
  }  
  serialEvent();
}

void ParseSerialData()
{
  // The data to be parsed
  char *p = inData;
  // Temp store for each data chunk
  char *str;   
  // Id ref for each chunk 
  int count = 0;
    
  //Serial.write("HEY");
    
    
  // Loop through the data and seperate it into
  // chunks at each "," delimeter
  while ((str = strtok_r(p, ",", &p)) != NULL)
  { 
    // Add chunk to array  
    inParse[count] = str;

    // Increment data count
    count++;      
  }

  // If the data has 5 values then..  
  if(count == 5)
  {
    // Define value 1 as a function identifier
    String module = inParse[0];
    String command = inParse[1];
    int pin = atoi(inParse[2]);
    String param1 = inParse[3];
    String param2 = inParse[4];
    
    if(debug == 1)
    {
      Serial.println(module);
    }
    
    if (module.equals("led")) 
    {
      led(command, pin, param1, param2);
    }
    
    if (module.equals("button")) 
    {
      Serial.println("PIN");
      Serial.println(pin);
      button(command, pin, param1, param2);
    }

  }
}

void serialEvent() 
{
  // Read while we have data
  while (Serial.available() && stringComplete == false) 
  {
    // Read a character
    char inChar = Serial.read(); 
    // Store it in char array
    inData[index] = inChar; 
    // Increment where to write next
    index++;     
    // Also add it to string storage just
    // in case, not used yet :)
    inString += inChar;
    // Check for termination character
    if (inChar == '\n') 
    {
      // Reset the index
      index = 0;
      //Serial.println(inString);
      // Set completion of read to true
      stringComplete = true;
    }
  }
}
