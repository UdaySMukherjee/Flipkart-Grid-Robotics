#include<cvzone.h>
// Define the pins for the relays
const int relayPins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
int currentRelay = 0; // Initialize the current relay index

SerialData serialData(2, 2); //(numOfValsRec,digitsPerValRec)
int valsRec[2];

void setup() {
  // Set the relay pins as OUTPUT
  for (int i = 0; i < 13; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Initialize relays to OFF
  }
  serialData.begin();
}
  
void loop() {
  serialData.Get(valsRec);
  int value = valsRec[0];
  switch(value){
    if(value == 1){
      rotatingplateCW();
    }
    if(value == 2){
      rotatingplateCCW();
    }
    if(value == 3){
      baseCW();
    }
    if(value == 4){
      baseCCW();
    }
    if(value == 5){
      arm1DOWN();
    }
    if(value == 6){
      arm1UP();
    }
    if(value == 7){
      arm2DOWN();
    }
    if(value == 8){
      arm2UP();
    }
    if(value == 9){
      arm3DOWN();
    }
    if(value == 10){
      arm3UP();
    }
    if(value == 11){
      flipperCW();
    }
    if(value == 12){
      flipperCCW();
    }
  }    
}

void rotatingplateCW(){//90 deg rotation
  digitalWrite(relayPins[1],LOW);
  digitalWrite(relayPins[0],HIGH);
  delay(1280);
  digitalWrite(relayPins[0],LOW);
  delay(1280);
}
void rotatingplateCCW(){//90 deg rotation
  digitalWrite(relayPins[0],LOW);
  digitalWrite(relayPins[1],HIGH);
  delay(1280);
  digitalWrite(relayPins[1],LOW);
  delay(1280);
}

void baseCW(){//90 deg rotation
  digitalWrite(relayPins[3],LOW);
  digitalWrite(relayPins[2],HIGH);
  delay(1400);
  digitalWrite(relayPins[2],LOW);
  delay(1400);
}
void baseCCW(){//90 deg rotation
  digitalWrite(relayPins[2],LOW);
  digitalWrite(relayPins[3],HIGH);
  delay(1400);
  digitalWrite(relayPins[3],LOW);
  delay(1400);
}

void arm1DOWN(){//90 deg rotation
  digitalWrite(relayPins[5],LOW);
  digitalWrite(relayPins[4],HIGH);
  delay(1200);
  digitalWrite(relayPins[4],LOW);
  delay(1200);
}
void arm1UP(){//90 deg rotation
  digitalWrite(relayPins[4],LOW);
  digitalWrite(relayPins[5],HIGH);
  delay(1500);
  digitalWrite(relayPins[5],LOW);
  delay(1500);
}


void arm2DOWN(){//90 deg rotation
  digitalWrite(relayPins[7],LOW);
  digitalWrite(relayPins[6],HIGH);
  delay(1100);
  digitalWrite(relayPins[6],LOW);
  delay(1100);
}
void arm2UP(){//90 deg rotation
  digitalWrite(relayPins[6],LOW);
  digitalWrite(relayPins[7],HIGH);
  delay(1400);
  digitalWrite(relayPins[7],LOW);
  delay(1400);
}


void arm3DOWN(){//90 deg rotation
  digitalWrite(relayPins[9],LOW);
  digitalWrite(relayPins[8],HIGH);
  delay(1100);
  digitalWrite(relayPins[8],LOW);
  delay(1100);
}
void arm3UP(){//90 deg rotation
  digitalWrite(relayPins[8],LOW);
  digitalWrite(relayPins[9],HIGH);
  delay(1300);
  digitalWrite(relayPins[9],LOW);
  delay(1300);
}


void flipperCW(){//90 deg rotation
  digitalWrite(relayPins[11],LOW);
  digitalWrite(relayPins[10],HIGH);
  delay(1000);
  digitalWrite(relayPins[10],LOW);
  delay(1000);
}
void flipperCCW(){//90 deg rotation
  digitalWrite(relayPins[10],LOW);
  digitalWrite(relayPins[11],HIGH);
  delay(1000);
  digitalWrite(relayPins[11],LOW);
  delay(1000);
}
