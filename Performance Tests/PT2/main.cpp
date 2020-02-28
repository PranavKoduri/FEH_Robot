#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHSD.h>

#define sleepcheck 0.1
#define power 20

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0, 9.0);
FEHMotor left_motor(FEHMotor::Motor1, 9.0);

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void check_x_minus(float x_coordinate) //using RPS while robot is in the -x direction
{
    //check if receiving proper RPS coordinates
    if (RPS.X()>=0)
    {
        //check whether the robot is within an acceptable range
        while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
        {
            if(RPS.X() > x_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(power);
                right_motor.SetPercent(power);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
            else if(RPS.X() < x_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(-power);
                right_motor.SetPercent(-power);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
        }
    }
}

void check_y_minus(float y_coordinate) //using RPS while robot is in the -y direction
{
    //check if receiving proper RPS coordinates
    if (RPS.Y()>=0)
    {
        //check whether the robot is within an acceptable range
        while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
        {
            if(RPS.Y() > y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(power);
                right_motor.SetPercent(power);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
            else if(RPS.Y() < y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(-power);
                right_motor.SetPercent(-power);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
        }
    }
}

void check_y_plus(float y_coordinate) //using RPS while robot is in the +y direction
{
    //check if receiving proper RPS coordinates
    if (RPS.Y()>=0)
    {
        //check whether the robot is within an acceptable range
        while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
        {
            if(RPS.Y() > y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(-power);
                right_motor.SetPercent(-power);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
            else if(RPS.Y() < y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(power);
                right_motor.SetPercent(power);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
        }
    }
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

                    left_motor.SetPercent(power);
                    right_motor.SetPercent(-power);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
                else if(RPS.Heading() >= 180)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(-power);
                    right_motor.SetPercent(power);
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

                    left_motor.SetPercent(power);
                    right_motor.SetPercent(-power);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
                else if(RPS.Heading() < heading)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(-power);
                    right_motor.SetPercent(power);
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
    float touch_x,touch_y;
        float A_x, A_y, B_x, B_y, C_x, C_y, D_x, D_y;
        float A_heading, B_heading, C_heading, D_heading;
        int powers, B_C_counts, C_D_counts, turn_90_counts;

    RPS.InitializeTouchMenu();

    LCD.WriteLine("RPS & Data Logging Test");
    LCD.WriteLine("Press Screen To Start");
    while(!LCD.Touch(&touch_x,&touch_y));
    while(LCD.Touch(&touch_x,&touch_y));

    FEHFile *fptr = SD.FOpen("RPS_Test.txt","r");
    SD.FScanf(fptr,"%f%f",&A_x,&A_y);
    SD.FScanf(fptr,"%f%f",&B_x,&B_y);
    SD.FScanf(fptr,"%f%f",&C_x,&C_y);
    SD.FScanf(fptr,"%f%f",&D_x,&D_y);
    SD.FClose(fptr);

    powers=25;
    B_C_counts=324;
    C_D_counts=202;
    turn_90_counts=110;

    A_heading=90;
    B_heading=180;
    C_heading=270;
    D_heading=0;


    //A --> B
    check_y_plus(B_y);
    check_heading(B_heading);

    //B --> C
    move_forward(powers, B_C_counts);
    check_x_minus(C_x);
    turn_left(powers, turn_90_counts);
    check_heading(C_heading);

    //C --> D
    move_forward(powers, C_D_counts);
    check_y_minus(D_y);
    turn_left(powers, turn_90_counts);
    check_heading(D_heading);

    return 0;
}
