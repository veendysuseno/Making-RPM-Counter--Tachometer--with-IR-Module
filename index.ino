volatile byte rpmcount;
unsigned int rpm;
unsigned long timeold;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void rpm_fun(){
  rpmcount++;
}

void setup(){
  lcd.init ();
  lcd.setBacklight(HIGH);

   //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
   //Triggers on FALLING (change from HIGH to LOW)
  attachInterrupt(0, rpm_fun, FALLING);

   //Turn on IR LED

  rpmcount = 0;
  rpm = 0;
  timeold = 0;
}

void loop(){
  //Update RPM every second
  delay(1000);
  //Don't process interrupts during calculations
  detachInterrupt(0);
  //Note that this would be 60*1000/(millis() - timeold)*rpmcount if the interrupt
  //happened once per revolution instead of twice. Other multiples could be used
  //for multi-bladed propellers or fans
  rpm = 30*1000/(millis() - timeold)*rpmcount;
  timeold = millis();
  rpmcount = 0;
   //Print out result to lcd
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kecepatan");
  lcd.setCursor(0,1);
  lcd.print(rpm);
  lcd.print(" rpm");
   //Restart the interrupt processing
  attachInterrupt(0, rpm_fun, FALLING);
}
