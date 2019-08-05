const int IN1 = 9, IN2 = 6, IN3 = 5, IN4 = 3, ldrPin = 0, LED = 10;
float reg = 0, prerror = 0, error = 0, sM = 0, kp = 0.65, ki = 0.0001, kd = 0.1,  x = 0;
int ldrValor = 0, vbase = 35;

void Off(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void setup(){
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);

 pinMode(LED,OUTPUT);

 digitalWrite(LED, HIGH);

 //Serial.begin(9600);
}
 
void loop(){

  ldrValor = analogRead(ldrPin);
  //Serial.println(ldrValor);

      error = (682 - ldrValor);
      // 682 é a referência,     (leitura no preto + leitura no branco)/2  ---> Calibrar
      
      reg = reg + error;
      if(prerror > 0 && error <= 0) reg = 0;
      if(prerror < 0 && error >= 0) reg = 0;
      
      sM = (kp*error + ki*(reg) + kd*(error - prerror));
      Serial.print(ldrValor);
      Serial.print(" | ");
      Serial.print(x);
      Serial.print(" | ");
     
      if(sM > 255) sM = 200;
      if(sM < -255) sM = -200;

      Serial.println(sM);

      if(sM < 0){
          
          analogWrite(IN2,vbase-1*sM);
          analogWrite(IN1,0); // Motor direito
          
      }
      else{
          
          analogWrite(IN3,vbase+sM);
          analogWrite(IN4,0); // Motor esquerdo
      }
      prerror = error;
      delay(1);
}
