#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>

#define sleepcheck 0.1
#define lpower 20
#define rpower 20
#define lmove 25
#define rmove 25

/* -----------         CDS CELL COLOR READING RANGES           ---------------      */
#define red 0.213 //approximate cds cell value of blue light
#define error 0.1 //approximate range of values of cds cell readings for that light above and below

DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_2);
FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor0,9.0);
AnalogInputPin cds(FEHIO::P3_7);
FEHServo servo(FEHServo::Servo0);

void move_forward(int lpercent, int rper, int counts) //using encoders
{
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

    Sleep(1.0);
}

void move_backward(int lpercent, int rper, int counts) //using encoders
{
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

    Sleep(1.0);
}

void turn_left(int lpercent, int rper, int counts) //using encoders
{
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

    Sleep(1.0);
}

void turn_right(int lpercent, int rper, int counts) //using encoders
{
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

    Sleep(1.0);
}

void tlf(int rper, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(rper);
    left_motor.SetPercent(0);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while(right_encoder.Counts() < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

    Sleep(1.0);
}

void trf(int lper, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(0);
    left_motor.SetPercent(lper);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while(left_encoder.Counts() < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

    Sleep(1.0);
}

void tlb(int rper, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-rper);
    left_motor.SetPercent(0);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while(right_encoder.Counts() < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

    Sleep(1.0);
}

void trb(int lper, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(0);
    left_motor.SetPercent(-lper);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while(left_encoder.Counts() < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

    Sleep(1.0);
}

void check_heading(float heading) //using RPS
{
    //check if receiving proper RPS coordinates
    if (RPS.Heading()>=0)
    {
        if (heading<3 || heading>=357){
            float lower;
            float upper;
            if (heading<3){
                upper=heading-3+360;
                lower=heading+3;
            } else {
                upper=heading-3;
                lower=heading+3-360;
            }
            while(RPS.Heading() < upper && RPS.Heading() > lower)
            {
                if(RPS.Heading() < 180)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(lpower);
                    right_motor.SetPercent(-rpower);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
                else if(RPS.Heading() >= 180)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(-lpower);
                    right_motor.SetPercent(rpower);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
            }
        }
        //check whether the robot is within an acceptable range
        else{
            while(RPS.Heading() < heading - 3 || RPS.Heading() > heading + 3)
            {
                LCD.WriteLine(RPS.Heading());
                if(RPS.Heading() > heading)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(lpower);
                    right_motor.SetPercent(-rpower);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
                else if(RPS.Heading() < heading)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(-lpower);
                    right_motor.SetPercent(rpower);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
            }
        }
    }
}

int main(void)
{
    float x,y;

 //   RPS.InitializeTouchMenu();

    float reb=red-error;
    float rea=red+error;

    float s=1.0;
    float t=s;

    LCD.Clear();

    servo.SetDegree(30);

    float v1=cds.Value();
    while((v1<reb || v1>rea) && !LCD.Touch(&x,&y)){
        LCD.WriteLine(v1);
        v1=cds.Value();
    }

    //deposit tray
    move_forward(lmove,rmove,602);
  //  check_heading(135.0);
    turn_left(lmove,rmove,390*t);
  //  check_heading(270.0);
    move_backward(40,40,1125); //up ramp
  //  check_heading(270.0);
    servo.SetDegree(118);
    Sleep(2.5);
    servo.SetDegree(30);
    Sleep(2.5);

//    //slide ticket
    move_forward(lmove,rmove,5);
    turn_left(lmove,rmove,250*t);
 //   check_heading(0.0);
    move_forward(lmove,rmove,445);
    //check_heading(0.0);
    trb(lmove,255*s);
    tlb(rmove,93*s);
    servo.SetDegree(135);
    Sleep(2.5);
    tlb(rmove,150*s);
    //check_heading(0.0);
    move_forward(lmove,rmove,167);
    //check_heading(0.0);
    servo.SetDegree(120);
    Sleep(1.0);
    move_backward(lmove,rmove,230);

    //hit stove
    move_forward(lmove,rmove,20);
    turn_left(lmove,rmove,86*t);
    servo.SetDegree(30);
    Sleep(2.5);
    move_forward(lmove,rmove,155);
    turn_left(lmove,rmove,160*t);
//    check_heading(90.0);
    move_forward(lmove,rmove,685);



}
