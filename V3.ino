//4294967295
// 965318983 бластер

#define start_switch 12
#define final_switch 14
#define door_switch 11

#define drive 9
#define reverse 10

#define buzzer 8

int n=0;

unsigned long last_shot=0;
unsigned long delta_shot=52;

bool flag_false=0;
bool final_flag=0;
bool flag_shot[]={0,0,0,0,0,0,0,0};

#include <IRremote.h>
IRrecv irrecv(2);         
decode_results results; 


#include <IRstD.h>
IRrecvstd irrecvstd(3);  
decode_resultsstd res_std;



void setup() 
{
   Serial.begin(57600);
  for (int i=4;i<=7;i++)
  {
    pinMode(i,INPUT);
  }
     
   pinMode(start_switch,INPUT);
   pinMode(final_switch,INPUT);
   pinMode(door_switch,INPUT);

   pinMode(drive,OUTPUT);
   pinMode(reverse,OUTPUT);

   digitalWrite(drive,HIGH);
   digitalWrite(reverse,HIGH);

   pinMode(buzzer,OUTPUT);
   digitalWrite(buzzer,LOW);
  
   irrecv.enableIRIn();       
   irrecvstd.enableIRInstd(); 
   start();
}

void loop()
{
  if(irrecv.decode(&results)) 
    {
       if ((results.value==965318983)&&(flag_shot[1]==0)&&(flag_false==false))
        {
           flag_shot[1]=true;
           n++;
           music();
        }
       Serial.print("1:");
       Serial.println(results.value);
       results.value = 0;
       irrecv.resume();
    }
     
    
  if(irrecvstd.decodestd(&res_std)) 
    {
       if ((res_std.valuestd==965318983)&&(flag_shot[2]==0))
        {
           flag_shot[2]=true;
           music();
           n++;
        }
       Serial.print("2:");
       Serial.println(res_std.valuestd);
       irrecvstd.resumestd();
       res_std.valuestd = 0; 
    }
  run_privid(); 
  for (int i=4;i<=7;i++)
  {
    if ((digitalRead(i)==1)&&(flag_shot [i]==false))
    {
      music();
      flag_shot [i]=true;
      n++;
      Serial.print("pin:");
      Serial.print(i);
      Serial.print(" n=");
      Serial.println(n);
      Serial.print("flag_shot [");
      Serial.print(i);
      Serial.print("]=");
      Serial.println(flag_shot [i]);
    }
   
  }
  final_music();
}
void start()
{
  if (digitalRead(start_switch)==HIGH)
  {
    while (digitalRead(start_switch)==HIGH)
    {
      digitalWrite(drive,HIGH);
      digitalWrite(reverse,LOW);
      //Serial.print("digitalRead(start_switch)==HIGH ");
      //Serial.println(digitalRead(start_switch));
    }
    digitalWrite(drive,HIGH);
    digitalWrite(reverse,HIGH);
  }
  while (digitalRead(door_switch)==LOW){}//поки не зачинились двері
  while (digitalRead(door_switch)==HIGH){}//поки не відчинились двері
  delay(1000);
}
void run_privid()
{
      if ((digitalRead(final_switch)==LOW)||(flag_shot [1]==1))
      {
        digitalWrite(drive,HIGH);
        digitalWrite(reverse,HIGH);
        flag_shot [1]=1;
        if (digitalRead(final_switch)==LOW)
        {
          flag_false=true;
        }
      }
      else
      {
        digitalWrite(drive,LOW);
        digitalWrite(reverse,HIGH);
      }
}
void music()
{
  digitalWrite(buzzer,HIGH);
  delay(200);//1000;
  digitalWrite(buzzer,LOW);
  //озвучка після попадання
}
void final_music()
{
  if ((final_flag==0)&&(n>=6)&&(flag_false==0))
  {
    // озвучка після вбивства усіх мішеней
    for (int i=15;i>=5;i--)
    {
        digitalWrite(buzzer,HIGH);
        delay(25*i);
        digitalWrite(buzzer,LOW);
        delay(25*i);
    }
    final_flag=1; 
  }    
}

