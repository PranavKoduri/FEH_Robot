#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

#define pi 3.14159265358979 //pi
#define power 25 //motor power %

/* -----------         CDS CELL/ROBOT CONSTANTS           ---------------      */
#define cdsl 4.96875 //distance from left side of robot to middle of cds cell
#define cdsr 4.5625 //distance from right side of robot to middle of cds cell
#define cdsf 1.125 //distance from front of robot to middle of cds cell

#define width cdsl+cdsr //distance between same pair of wheels //8.34375 direct measurement
#define length 7.25 //distance between wheels on same side

#define cdsc (length/2)-cdsf //distance between line in center of robot parallel to width and cds cell
#define cdsm (width/2)-cdsr //distance between line in center of robot parallel to length and cds cell

/* -----------         SHAFT ENCODER COUNT CONSTANTS           ---------------      */
#define cpr 318 //encoder counts per rotation
#define diameter 2.5 //diameter of the wheel

#define cpi cpr/(diameter*pi); //pi counts per inch

#define degrees 90 //degrees turning for next constant
#define turn  cpi*diameter*degrees/360 //degree turns in counts

/* -----------         MOVEMENT DISTANCE CONSTANTS (INCHES)           ---------------      */
#define first  (width/2)+(length/2)-1-cdsm  //starting spot to off starting spot, in line with jukebox light
#define second 18.5-cdsc  //drive onto directly over jukebox light
#define thirdf   7 //move forward a little to be in line with red button
#define thirdb 1 //move backward a little to be in line with blue button
#define fourth  13 //move forward to hit button
#define fifth   5 //move backward after hitting button
#define sixth   11 //drive parallel to bottom part of ramp until in the middle of the ramp
#define seventh 30 //drive up the ramp
#define eighth  20 //drive down the ramp

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
#define blue //approximate cds cell value of blue light
#define red //approximate cds cell value of blue light
#define none //approximate cds cell value of blue light

#define error //approximate range of values of cds cell readings for that light above and below

/* -----------         Declarations for encoders & motors & cds cell          ---------------      */
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
DigitalInputPin cds(FEHIO::P0_2);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);

/** -----------      FUNCTIONS ------------ **/
void move_forward(int percent, int counts) //using encoders
{
    LCD.WriteLine(counts);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void move_backward(int percent, int counts) //using encoders
{
    LCD.WriteLine(counts);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(-percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int percent, int counts) //using encoders
{
    LCD.WriteLine(counts);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_right(int percent, int counts) //using encoders
{
    LCD.WriteLine(counts);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

int main(void)
{
    int t=(int) turn;

    move_forward(power,i);
    Sleep(1.0);

    turn_left(power,t);
    Sleep(1.0);

    move_forward(power,ii);
    Sleep(1.0);

    if (v>(blue-error) && v<(blue+error)){
       move_forward(power,iiib);

       } else if (v>(red-error) && v<(red+error)){
           move_forward(power,iiif);

       }
    Sleep(1.0);

    turn_left(power,t);
    Sleep(1.0);

    move_forward(power,iv);
    Sleep(1.0);

    move_backward(power,v);
    Sleep(1.0);

    turn_left(power,t);
    Sleep(1.0);

    move_forward(power,vi);
    Sleep(1.0);

    turn_left(power,t);
    Sleep(1.0);

    move_forward(power,vii);
    Sleep(1.0);

    move_backward(power,viii);
    Sleep(1.0);

    //12 counts
}
