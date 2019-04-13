//4294967295
// 965318983 бластер

#define pin_output_reciver1 4 
#include <IRremote.h>
IRrecv irrecv(2);                     
decode_results results; 

#define pin_output_reciver2 5
#include <IRstD.h>
IRrecvstd irrecvstd(3);
decode_resultsstd res_std;


void setup() 
{
   Serial.begin(57600);
   irrecv.enableIRIn();       
   irrecvstd.enableIRInstd();
   pinMode(pin_output_reciver1,OUTPUT);
   pinMode(pin_output_reciver2,OUTPUT);
   digitalWrite(pin_output_reciver1,LOW); 
   digitalWrite(pin_output_reciver2,LOW); 
}

void loop()
{
  if(irrecv.decode(&results)) 
    {
       if (results.value==965318983)
       {
          Serial.println("ok_1");
          digitalWrite(pin_output_reciver1,HIGH);
          delay(50);
          digitalWrite(pin_output_reciver1,LOW);
       }
        
       Serial.print("1:");
       Serial.println(results.value);
       results.value = 0;
       irrecv.resume(); 
    }
     
    
  if(irrecvstd.decodestd(&res_std)) 
    {
       if (res_std.valuestd==965318983)
       {
          Serial.println("ok_2");
          digitalWrite(pin_output_reciver2,HIGH);
          delay(50);
          digitalWrite(pin_output_reciver2,LOW);  
       }
       
       Serial.print("2:");
       Serial.println(res_std.valuestd);
       irrecvstd.resumestd();
       res_std.valuestd = 0;
       delay(50);
       digitalWrite(pin_output_reciver2,LOW);  
    }
   

   
  
}  
