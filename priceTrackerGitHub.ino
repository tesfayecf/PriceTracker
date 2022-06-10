#include "MARKET_DATA_ENDPOINTS.h"
#include <WiFiClientSecure.h> 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <math.h>
#include "Request.h"
#include <Dictionary.h>

LiquidCrystal lcd(D6, D7, D2, D3, D4, D5);
Dictionary &dades = *(new Dictionary());

//enter the crypto ticker to track
String assets[9] = {"BTC", "ETH", "MATIC", 
                    "BNB", "ADA", "DOT", 
                    "LINK", "LTC", "XLM"};
                
//Balances must have a 10 digit length including the decimal point. 
//Balances should have the same order than the tickers.
double balances[9] = {};

int assetIndex = 0;
int prevAssetIndex= 0;
int assetNumber = sizeof(balances)/sizeof(balances[0]) - 1;
int counter = 0;

// function to change the cryptocurrency displayed with the shield buttons.
void position() {
  int val=analogRead(A0);
  if(val>=0&&val<=250)  {
    assetIndex -= 1;  }
  else if(val>=250&&val<=650) {
    assetIndex += 1;  }
  if(assetIndex<0) { assetIndex = assetNumber;}
  if(assetIndex>assetNumber) { assetIndex = 0;}
}

 void lcdPrintDouble( double val, byte precision, bool dollar = false){
  // prints val on a ver 0012 text lcd with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimial places
  // example: printDouble( 3.1415, 2); // prints 3.14 (two decimal places)
 
  if(val < 0.0){
    lcd.print('-');
    val = -val;
  }

  lcd.print (int(val));  //prints the int part
  if( precision > 0) {
    lcd.print("."); // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *=10;
 
    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
      unsigned long frac1 = frac;
      while( frac1 /= 10 )
        padding--;
      while(  padding--)
        lcd.print("0");
        lcd.print(frac,DEC) ;
  }
  if (dollar) 
    lcd.print("$");
}

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  lcd.begin(16, 2);
  
  lcd.setCursor(3,0);
  lcd.print("Connecting");
  lcd.setCursor(1,1);
  lcd.print("to the network");
 
  wifiConnect();
}

void loop() {
  position();
  
  if ((counter + 30)%30 == 0) { // every 30 seconds
    if (counter >= 31) {
      lcd.setCursor(15,2); //change position
      lcd.print("·"); }
    dades.jload(Symbol_Price_Ticker(String(assets[assetIndex])+"USDT")); 
    if (counter >= 31) {
      lcd.setCursor(15,2); //change position
      lcd.print(" "); }
  }

  lcd.clear();
  double balance = balances[assetIndex];
  lcd.setCursor(2,0);
  lcdPrintDouble(balance, 6);
  
  lcd.setCursor(11,0);
  lcd.print(assets[assetIndex]);
  
  if (prevAssetIndex != assetIndex){
    lcd.setCursor(0,1);
    lcd.write("||||||||||||||||");
    dades.jload(Symbol_Price_Ticker(String(assets[assetIndex])+"USDT")); 
  }
  
  String price = String(dades["price"]); 
  lcd.setCursor(0,1);
  lcd.print(price.substring(0,7) + "$");

  double money = price.toDouble()*balance;
  lcd.setCursor(9,1);
  lcdPrintDouble(money, 1, true);
    
  prevAssetIndex = assetIndex;
  counter += 1;
  delay(1000);
}
