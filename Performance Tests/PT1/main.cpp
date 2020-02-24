#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

#define pi 3.14159265358979 //pi
#define power 25 //motor power %
#define ramppower 60 //motor power % up ramp
#define turnpower 32 //motor power % during turns

/* -----------         CDS CELL/ROBOT CONSTANTS           ---------------      */
#define cdsl 4.55 //distance from left side of robot to middle of cds cell
#define cdsr 4.875 //distance from right side of robot to middle of cds cell
#define cdsf 2.75 //distance from front of robot to middle of cds cell

#define width cdsl+cdsr //distance between same pair of wheels //8.34375 direct measurement
#define length 7.5 //distance between wheels on same side

#define cdsc (length/2)-cdsf //distance between line in center of robot parallel to width and cds cell
#define cdsm (width/2)-cdsl //distance between line in center of robot parallel to length and cds cell
    //-cdsl if cdsl<cdsr, else -cdsr

/* -----------         SHAFT ENCODER COUNT CONSTANTS           ---------------      */
#define cpr 318.0 //encoder counts per rotation
//#define diamete 2.5 //diameter of the wheel

//#define cpi cpr/(2.5*pi); //pi counts per inch

#define degrees 90.0 //degrees turning for next constant
//#define turne  cpi*5.0/2.0*degrees/360.0 //degree turns in counts

/* -----------         MOVEMENT DISTANCE CONSTANTS (INCHES)           ---------------      */
#define first  (width/2)+(length/2)-2-cdsm  //starting spot to off starting spot, in line with jukebox light
#define second 18.25-cdsc  //drive onto directly over jukebox light
#define thirdf   7 //move forward a little to be in line with red button
#define thirdb 1 //move backward a little to be in line with blue button
#define fourth  5 //move forward to hit button
#define fifth   5 //move backward after hitting button
#define sixth   5 //drive parallel to bottom part of ramp until in the middle of the ramp
#define seventh 26 //drive up the ramp
#define eighth  30 //drive down the ramp

/* -----------         MOVEMENT DISTANCE CONSTANTS (COUNT)           ---------------      */
#define i  first*cpi  //starting spot to off starting spot, in line with jukebox light
#define ii second*cpi  //drive onto directly over jukebox light
#define iiif thirdf*cpi //move forward a little to be in line with red button
#define iiib thirdb*cpi //move backward a little to be in line with blue button
#define iv  fourth*cpi //move forward to hit button
#define v  fifth*cpi //move backward after hitting button
#define vi  sixth*cpi //drive parallel to bottom part of ramp until in the middle of the ramp
#define vii seventh*cpi //drive up the ramp
#define viii  eighth*cpi //drive down the ramp

/* -----------         CDS CELL COLOR READING RANGES           ---------------      */
#define blue 0.448 //approximate cds cell value of blue light
#define red 0.213 //approximate cds cell value of blue light
#define none 2.292 //approximate cds cell value of blue light

#define error 0.1//approximate range of values of cds cell readings for that light above and below

/* -----------         Declarations for encoders & motors & cds cell          ---------------      */
DigitalEncoder right_encoder(FEHIO::P2_0);
DigitalEncoder left_encoder(FEHIO::P1_0);
AnalogInputPin cds(FEHIO::P0_0);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);

/** -----------      FUNCTIONS ------------ **/
void move_forward(int lpercent, int rper, int counts) //using encoders
{
    LCD.Write("up: ");
    LCD.WriteLine(counts);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(rper);
    left_motor.SetPercent(lpercent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void move_backward(int lpercent, int rper, int counts) //using encoders
{
    LCD.Write("back: ");
    LCD.WriteLine(counts);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-rper);
    left_motor.SetPercent(-lpercent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int lpercent, int rper, int counts) //using encoders
{
    LCD.Write("left: ");
    LCD.WriteLine(counts);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(rper);
    left_motor.SetPercent(-lpercent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_right(int lpercent, int rper, int counts) //using encoders
{
    LCD.Write("right: ");
    LCD.WriteLine(counts);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-rper);
    left_motor.SetPercent(lpercent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

int main(void)
{
    LCD.Clear();

    float cpi=cpr/(5*pi);

    int m1=(int) 8*cpi;
    int m2=(int) 15*cpi;
    int m3f=(int) thirdf*cpi;
    int m3b=(int) thirdb*cpi;
    int m4=(int) fourth*cpi;
    int m5=(int) fifth*cpi;
    int m6=(int) sixth*cpi;
    int m7=(int) seventh*cpi;
    int m8=(int) eighth*cpi;
    int m9=(int) 4*cpi;

    float x,y;

    float beb=blue-error;
    float bea=blue+error;
    float reb=red-error;
    float rea=red+error;

    //double turne=  90.0/360.0*cpi*length*pi;
    int t=120;

    float v1=cds.Value();
    while((v1<reb || v1>rea) && !LCD.Touch(&x,&y)){
        LCD.WriteLine(v1);
        v1=cds.Value();
    }

    LCD.WriteLine(cpi);
    LCD.WriteLine(m1);
    move_forward(power,power,m1); //m1
    Sleep(1.0);

    turn_left(power,turnpower,t);
    Sleep(4.0);


    move_forward(power,power,m2);
    Sleep(4.0);


  //  turn_left(power,turnpower,t);
   // Sleep(1.0);

    //move_forward(power,power,m9);
   // Sleep(1.0);

    float val=cds.Value();
    LCD.WriteLine(val);

    int lef= 1.75*0.5*cpi;
    int rig=(int) 0.5*3.75*cpi;

    LCD.WriteLine("move");
    if (val>beb && val<bea){
           //move_forward(power,power,m3b);
           LCD.SetBackgroundColor(FEHLCD::Blue);

           move_backward(power,power,cpi*0.8);
           Sleep(1.0);

           turn_left(power,turnpower,t);
           Sleep(1.0);

           //move_forward(power,power,lef);
          // Sleep(1.0);

          // turn_right(power,turnpower,t);
           //Sleep(1.0);

       } else{ //if (val>reb && val<rea)
          // move_forward(power,power,m3f);
           LCD.SetBackgroundColor(FEHLCD::Red);

           move_forward(power,power,cpi*0.8);
           Sleep(1.0);

           turn_left(power,turnpower,t);
           Sleep(1.0);

           //move_forward(power,power,rig);
          // Sleep(1.0);

           //turn_right(power,turnpower,t);
          // Sleep(1.0);

       }
    Sleep(1.0);

    //move_forward(power,power,m4);
    left_motor.SetPercent(25);
    right_motor.SetPercent(25);
    Sleep(0.8);
    left_motor.SetPercent(0);
    right_motor.SetPercent(0);
    Sleep(1.0);

    move_backward(power,power,m5);
    Sleep(1.0);

    turn_left(power,turnpower,t);
    Sleep(1.0);

    move_forward(power,power,m6);
    Sleep(1.0);

    if (val>beb && val<bea){
        move_forward(power,power,0.2*cpi);
    }
    Sleep(1.0);

    turn_left(power,turnpower,t);
    Sleep(1.0);

    move_forward(ramppower,ramppower,m7);
    Sleep(1.0);

    move_backward(power,power,m8);
    Sleep(1.0);

    //12 counts
}
