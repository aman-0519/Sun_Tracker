 #include <Servo.h>

int top_servo=9;
int bottom_servo=10;
int ldr_tr,ldr_tl,ldr_br,ldr_bl;
int spd_top,spd_bottom;
int mini;
int s1=80,s2=80;

Servo servo_top,servo_bottom;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(top_servo,OUTPUT);
  pinMode(bottom_servo,OUTPUT);
  servo_top.attach(top_servo);
  servo_bottom.attach(bottom_servo);
  servo_top.write(80);
  servo_bottom.write(80);
  delay(2000);
}

void read_ldr(){
  ldr_tr=analogRead(A0);
  ldr_tl=analogRead(A1);
  ldr_br=analogRead(A2);
  ldr_bl=analogRead(A3);
  
  ldr_tr=map(ldr_tr,0,750,0,300);
  ldr_tl=map(ldr_tl,0,750,50,300);
  ldr_br=map(ldr_br,0,750,0,300);
  ldr_bl=map(ldr_bl,0,750,0,300);
  
  mini=min(min(ldr_tr,ldr_tl),min(ldr_br,ldr_bl));
}

void move_right(){
 if(s2<160){
  s2++; 
  servo_bottom.write(s2);
 }
}

void move_left(){
  s2--;
  servo_bottom.write(s2);
}

void move_up(){
  if(s1<160){
   s1++;
   servo_top.write(s1);
  }
}

void move_down(){
  s1--;
  servo_top.write(s1);
}

void move_upleft(){
  if(s1<160){
   s1++;
  }
  s2--;
  servo_bottom.write(s2);
  servo_top.write(s1);
}

void move_upright(){
  if(s1<160){
   s1++; 
  }
  if(s2<160){
   s2++;
  }
  servo_top.write(s1);
  servo_bottom.write(s2);
}

void move_downleft(){
  s1--; 
  s2--;
  servo_top.write(s1);
  servo_bottom.write(s2);
}

void move_downright(){
  s1--; 
  if(s2<160){
   s2++;
  }
  servo_top.write(s1);
  servo_bottom.write(s2); 
}

void printldr(){
  Serial.print("ldr_tr = ");
  Serial.print(ldr_tr);
  Serial.print("    ldr_tl = ");
  Serial.print(ldr_tl);
  Serial.print("    ldr_br = ");
  Serial.print(ldr_br);
  Serial.print("    ldr_bl = ");
  Serial.println(ldr_bl);
  Serial.print("           MIN = ");
  Serial.print(mini);
  if(mini==ldr_tr)
  Serial.println("   ldr_tr");
  else if(mini==ldr_tl)
  Serial.println("   ldr_tl");
  else if(mini==ldr_br)
  Serial.println("   ldr_br");
  else if(mini==ldr_bl)
  Serial.println("   ldr_bl");
}

int diff=20;

void loop() {
  read_ldr();
  printldr();
  /*
  servo_top.write(160);
  servo_bottom.write(160);
  */
  //move_left();
  
  if(mini==ldr_tr && mini==ldr_tl && mini==ldr_br && mini==ldr_bl);
  else if((ldr_tr-mini)<=diff && (ldr_tl-mini)<=diff)
    move_down();
  else if((ldr_tr-mini)<=diff && (ldr_br-mini)<=diff)
    move_downright();
  else if((ldr_br-mini)<=diff && (ldr_bl-mini)<=diff) 
    move_up();
  else if((ldr_tl-mini)<=diff && (ldr_bl-mini)<=diff)
    move_downleft();
  else if((ldr_tr-mini)<=diff) 
    move_downright();
  else if((ldr_tl-mini)<=diff)
    move_downleft();
  else if((ldr_br-mini)<=diff) 
    move_upleft();
  else if((ldr_bl-mini)<=diff) 
    move_upright();
  else;
  
  delay(100);
}
