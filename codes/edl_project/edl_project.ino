
//int analogPin = A0;
int val = 0;
int val1 = 0;
int output = 3;
int output1 = 4;
float voltage = 1.0, voltage1 = 1.0,prev_voltage = 1.0, prev_voltage1 = 1.0;
int n=0, i=0;
float sum_freq=0, sum_phase=0;
float avg_freq=0, instant_avg=0;
float avg_phase=0, instant_avg_phase=0;
float start_time=512,start_time1=5, stop_time=610; 
float freq, phase_degree=0, phase_degree2=0; 

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
 
pinMode(output, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:


 val = analogRead(A0);    // read the input pin
  val1 = analogRead(A1);    // read the input pin
voltage = (val/1023.0)*5.0;
voltage1 = (val1/1023.0)*5.0;
n+=1;
//sum+=voltage;
//avg = sum/n;

int output_voltage = (voltage/5.0)*255;
int output_voltage1 = (voltage1/5.0)*255;
if (output_voltage>=127)
analogWrite(output, 255);
else if (output_voltage<127)
analogWrite(output, 0);

if (output_voltage1>=127)
analogWrite(output1, 255);
else if (output_voltage1<127)
analogWrite(output1, 0);

if (output_voltage>127 && prev_voltage<127)
//if (voltage>127)
{
  start_time= millis();

}

if (output_voltage<127&&prev_voltage>127)
{
  stop_time= millis();
// Serial.print("inside loop 2 ");             // debug value

  freq = 500/(stop_time-start_time);
}


if (output_voltage1>127&&prev_voltage1<127)
{
  start_time1= millis();
// Serial.print("inside loop 2 ");             // debug value
  phase_degree = 0.36*avg_freq*(start_time1 - start_time);
  phase_degree2 = 360-phase_degree; 
}
  
prev_voltage = output_voltage; 
prev_voltage1 = output_voltage1; 
//analogWrite(output, output_voltage);
//
//Serial.print(" the current value is : ");             // debug value
//
//  Serial.print(voltage );             // debug value
//  Serial.print(" the output value is : ");             // debug value
//
//  Serial.println(output_voltage );             // debug value
//digitalWrite(output, HIGH);
//Serial.print(" the avg voltage is : ");             // debug value
//
//Serial.print(avg);             // debug value
if (n==1000){
  
//Serial.print(" output_voltage is : ");             // debug value
////
//  Serial.print(output_voltage );             // debug value
////  
//Serial.print(" the value of n : ");             // debug value
//Serial.print(n);             // debug value
//Serial.print(" ");             // debug value
//Serial.print("start_time : ");             // debug value
//Serial.print(start_time);             // debug value
//Serial.print(" ");             // debug value
//Serial.print("stop_time : ");             // debug value
//Serial.print(stop_time);             // debug value
//Serial.print(n);             // debug value
//Serial.print("  freq : ");             // debug value
//Serial.print(freq);             // debug value
//Serial.print("  phase diff : ");             // debug value
//Serial.print(phase_degree);             // debug value
//Serial.print("  phase diff2 : ");             // debug value
//Serial.print(phase_degree2);             // debug value
//Serial.print("  instant avg : ");             // debug value
//Serial.print(instant_avg);             // debug value
//Serial.print("  i : ");             // debug value
//Serial.print(i);             // debug value
//Serial.print("  sum freq : ");             // debug value
//Serial.print(sum_freq);             // debug value

//Serial.print(" the time is : ");             // debug value
//
//Serial.println(millis());             // debug value
n=0;
    if (i<10)
  {
  sum_freq+=freq; 
  if (phase_degree<phase_degree2)
  sum_phase+=phase_degree; 
  else
  sum_phase+=phase_degree2;
  i+=1;
  instant_avg = sum_freq/i; 
   
    }
else 
{
  avg_freq = sum_freq/10;
  avg_phase = sum_phase/10;
  i=0;
  sum_freq=0;
  sum_phase=0;
  Serial.print("  avg freq : ");             // debug value
Serial.print(avg_freq);             // debug value
  Serial.print("  avg phase : ");             // debug value
Serial.println(avg_phase);             // debug value
  }

  }
//  Serial.println("hello");             // debug value
//delay(3);
}

