// Poniżej przedstawiono proste procedury sterowania silnikiem krokowym
# define EN 8 // Aktywacja silników krokowych, aktywny stan niski
# define X_DIR 5 // Sterowanie kierunkiem silnika krokowego w osi X.
# define Y_DIR 6 // Sterowanie kierunkiem silnika krokowego w osi Y.
# define Z_DIR 7 // Sterowanie kierunkiem silnika krokowego w osi Z.
# define X_STP 2 // Sterowanie krokowe, impulsowe x-osi
# define Y_STP 3 // Sterowanie krokowe, impulsowe y-osi
# define Z_STP 4 // Sterowanie krokowe, impulsowe x-osi

#include <Servo.h> //Biblioteka odpowiedzialna za serwa
#define serw 11 // Nazwanie pinu pod kontrolowanie serwa
Servo serwomechanizm;  //Tworzymy obiekt, dzięki któremu możemy odwołać się do serwa

char state;// Utworzenie zmiennej do odczytywania przesyłanych znaków

String message; // ciąg, który przechowuje wiadomość przychodzącą
#include <Wire.h> //
#include <LiquidCrystal_I2C.h> // biblioteki niezbędne do obsługi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);//Informacja o podłączeniu nowego wyświetlacza

#define pwmMotorA A0 // Sterowanie PWM silnikiem DC A (odpowiada z prędkość obrotów silnik A)
#define pwmMotorB A1 // Sterowanie PWM silnikiem DC B (odpowiada z prędkość obrotów silnik B)
#define ForwardA 9
#define BackA 10
#define ForwardB 12
#define BackB 13

// Funkcja: step. funkcja: do sterowania kierunkiem silnika krokowego, liczba kroków.
//Parametry: dir-sterowanie kierunkiem jazdy, dirPin-pin pod kierunek jazdy, 
//steps-liczba kroków, stepperPin- pin pod liczbę kroków

void step (boolean dir, byte dirPin, byte stepperPin, int steps)
{ digitalWrite (EN, LOW);
    digitalWrite (dirPin, dir);
    delay (30);
    for (int i = 0; i <steps; i++) 
    {
        digitalWrite (stepperPin, HIGH);
        delayMicroseconds (700);
        digitalWrite (stepperPin, LOW);
        delayMicroseconds (700);
    }
}
void ster (boolean dir, byte dirPin, byte stepperPin)
{for (int i = 0; i <15; i++)
  {digitalWrite (EN, LOW);
  digitalWrite (dirPin, dir);
    digitalWrite (stepperPin, HIGH);
        delayMicroseconds (700);
        digitalWrite (stepperPin, LOW);
        delayMicroseconds (700);}
    
}
//funkcja skręt w lewo
void Left(){
  //Ustawienie kierunku obrotów A
  digitalWrite(ForwardA, LOW); 
  digitalWrite(BackA, HIGH);
  //Ustawienie kierunku obrotów B
  digitalWrite(ForwardB, HIGH); 
  digitalWrite(BackB, LOW);
  //delay(1000);
}

//skręt w prawo
void Right(){
  //Ustawienie kierunku obrotów A
  digitalWrite(ForwardA, HIGH); 
  digitalWrite(BackA, LOW);
  //Ustawienie kierunku obrotów B
  digitalWrite(ForwardB, LOW); 
  digitalWrite(BackB, HIGH);
  
  //delay(1000);
}

//jazda prosto
void Forward(){
  //Ustawienie kierunku obrotów A
  digitalWrite(ForwardA, HIGH); 
  digitalWrite(BackA, LOW);
  
  //Ustawienie kierunku obrotów B
  digitalWrite(ForwardB, HIGH); 
  digitalWrite(BackB, LOW);
}

//cofanie
void Back(){
  //Ustawienie kierunku obrotów A
  digitalWrite(ForwardA, LOW); 
  digitalWrite(BackA, HIGH);
  
  //Ustawienie kierunku obrotów B
  digitalWrite(ForwardB, LOW); 
  digitalWrite(BackB, HIGH);
  
}
//zatrzymanie
void Stop(){
  //Ustawienie kierunku obrotów A
  digitalWrite(ForwardA, LOW); 
  digitalWrite(BackA, LOW);
  
  //Ustawienie kierunku obrotów B
  digitalWrite(ForwardB, LOW); 
  digitalWrite(BackB, LOW);
}

void setup () {   // Ustawienie pinów jako wyjścia
    pinMode (X_DIR, OUTPUT); pinMode (X_STP, OUTPUT);
    pinMode (Y_DIR, OUTPUT); pinMode (Y_STP, OUTPUT);
    pinMode (Z_DIR, OUTPUT); pinMode (Z_STP, OUTPUT);
    pinMode (EN, OUTPUT);
    serwomechanizm.attach(serw); //Serwomechanizm podłączony do pinu 11
    digitalWrite (EN, HIGH);
    Serial.begin(9600); //Uruchamiamy transmisję
    lcd.begin();//Deklaracja typu  
    lcd.print("Witaj");// Komenda powitalna
    
     //Wyjście PWM kanału A
  pinMode(pwmMotorA, OUTPUT); 
  
  //Wyjście cyfrowe AIN1
  pinMode(ForwardA, OUTPUT); 
  //Wyjście cyfrowe AIN2
  pinMode(BackA, OUTPUT);   
  
  //Wyjście PWM kanału B
  pinMode(pwmMotorA, OUTPUT);
  
  //Wyjście cyfrowe BIN1
  pinMode(ForwardB, OUTPUT); 
  //Wyjście cyfrowe BIN2
  pinMode(BackB, OUTPUT); 
  
  
  //ustawienie prędkości obrotowej silników
 digitalWrite(pwmMotorA, HIGH);//ustawienie maksymalnej prędkości
 digitalWrite(pwmMotorB, HIGH);
   
}

void loop () {
    if(Serial.available() > 0){ //Czy Arduino odebrało dane    
      state = Serial.read();}//Jeśli tak, to odczytaj je i zapisz w zmiennej state
    //lub while
    switch(state){
    case '0':
    Stop();
    break;
    case '1':
    lcd.clear();// czyszczenie ekranu LCD
     while(Serial.available()){     
       message+=char(Serial.read());// przechowuj ciąg od polecenia szeregowego
     }
      if(message!="")// jeśli dane istnieją
    {lcd.print(message);// pojawienie się wysłanej wiadomości na ekranie LCD
      delay(1100);//
      message=""; //czyszczenie danych
    }
    state='0';
    break;
     case '2':
     for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // przewiń o jedną pozycję w lewo:
    lcd.scrollDisplayLeft();
    // czekaj chwilę:
    delay(200);
  } 
    break;
    case '3':
    ster (false, X_DIR, X_STP); // Obrót osi silnika X w tył
    case '4':
    ster (true, X_DIR, X_STP); // Obrót osi silnika X w przód
    break;
     case '5':
       ster (false, Y_DIR, Y_STP); 
    break;
    case '6':
    ster (true, Y_DIR, Y_STP); 
    break;
     case '7':
       ster (false, Z_DIR, Z_STP); 
    break;
    case '8':
    ster (true, Z_DIR, Z_STP); // X axis motor reverse 1 ring, the 200 step is a circle.
    break;
     case '9':
    serwomechanizm.write(60);//Szczęki otwarte
    break;
    case 'a':
    serwomechanizm.write(0);//Sczęki zamknięte
    break;
    case'b':
    Forward();
    break;
    case 'c':
    Back();
    break;
    case'd':
    Right();
    break;
    case 'e':
    Left();
    break;
    case 'f':
    Forward();
    delay(350);
    Right();
    delay(300);
    Left();
    delay(300);
    Back();
    delay(350);
    break;
    case 'g':
    step (false, X_DIR, X_STP, 50); //Obrót osi silnika X w tył o 50 kroków
    step (false, Y_DIR, Y_STP, 50); 
    step (false, Z_DIR, Z_STP, 50); 
    serwomechanizm.write(0);//Sczęki zamknięte
    step (true, X_DIR, X_STP, 50); //Obrót osi silnika X w przód o 50 kroków
    step (true, Y_DIR, Y_STP, 50); 
    step (true, Z_DIR, Z_STP, 50); 
    serwomechanizm.write(60);//Szczęki otwarte
    state='0';
    break;
    default :
    Stop();
    break;
    }
    
     delay(35);   
   
     digitalWrite (EN, HIGH);// silniki krokowe wyłączone
   
}

