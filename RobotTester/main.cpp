#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>

DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_2);
FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor0,9.0);
AnalogInputPin cds(FEHIO::P3_7);
FEHServo servo(FEHServo::Servo0);

int main(void)
{
    LCD.Clear();
    RPS.InitializeTouchMenu();

    bool ec=true;

    int lpower=25;
    int rpower=25;

    /* Create icons for servo motors menu */

    FEHIcon::Icon Reset[1];
    char back_label[1][20] = {"Reset"};
    FEHIcon::DrawIconArray(Reset, 1, 1, 205, 5, 0, 260, back_label, WHITE, WHITE);

    FEHIcon::Icon SV[6];
    char sv_labels[6][20] = {"Left:", "0", "Right:", "0","CDS:","0"};
    FEHIcon::DrawIconArray(SV, 3, 2, 0, 150, 1, 150, sv_labels, WHITE, WHITE);

    FEHIcon::Icon LM[6];
    char lm_labels[6][20] = {"25", "^", "40", "v","60","25"};
    FEHIcon::DrawIconArray(LM, 3, 2, 97,53,20, 220, lm_labels, BLUE, BLUE);

    FEHIcon::Icon RM[6];
    char rm_labels[6][20] = {"25", "^", "40", "v","60","25"};
    FEHIcon::DrawIconArray(RM, 3, 2, 97, 53, 100,140 , rm_labels, RED, RED);

    FEHIcon::Icon Run[8];
    char run_labels[8][20] = {"F", "B" ,"TLP","TRP","TLF","TRF","TLB","TRB"};
    FEHIcon::DrawIconArray(Run, 4, 2, 10, 21, 201, 1, run_labels, WHITE, WHITE);

    FEHIcon::Icon Serv[3];
    char s_labels[3][20] = {"v","^","0"};
    FEHIcon::DrawIconArray(Serv, 1, 3, 205, 5, 70, 130, s_labels, WHITE, WHITE);

    float x, y;

    servo.SetDegree(0);
    int deg=0;

    while(true)
    {
        if (ec) SV[5].ChangeLabelFloat(cds.Value());
        else{
            SV[1].ChangeLabelFloat(RPS.X());
            SV[3].ChangeLabelFloat(RPS.Y());
            SV[5].ChangeLabelFloat(RPS.Heading());
        }
        if (LCD.Touch(&x, &y))
        {
            /* Check to see if the forward or backward run icons have been touched */
            if (Run[0].Pressed(x, y, 0))
            {
                left_motor.SetPercent(lpower);
                right_motor.SetPercent(rpower);
                while(Run[0].Pressed(x, y, 1))
                {
                    if(ec){
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                    }
                }
                left_motor.Stop();
                right_motor.Stop();
                Run[0].Deselect();
            }
            else if (Run[1].Pressed(x, y, 0))
            {
                left_motor.SetPercent(-lpower);
                right_motor.SetPercent(-rpower);
                while(Run[1].Pressed(x, y, 1))
                {
                    if(ec){
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                    }
                }
                left_motor.Stop();
                right_motor.Stop();
                Run[1].Deselect();
            }
            else if (Run[2].Pressed(x, y, 0))
            {
                left_motor.SetPercent(-lpower);
                right_motor.SetPercent(rpower);
                while(Run[2].Pressed(x, y, 1))
                {
                    if(ec){
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                    }
                }
                left_motor.Stop();
                right_motor.Stop();
                Run[2].Deselect();
            }
            else if (Run[3].Pressed(x, y, 0))
            {
                left_motor.SetPercent(lpower);
                right_motor.SetPercent(-rpower);
                while(Run[3].Pressed(x, y, 1))
                {
                    if(ec){
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                    }
                }
                left_motor.Stop();
                right_motor.Stop();
                Run[3].Deselect();
            }
            else if (Run[4].Pressed(x, y, 0))
            {
                left_motor.SetPercent(0);
                right_motor.SetPercent(rpower);
                while(Run[4].Pressed(x, y, 1))
                {
                    if(ec){
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                    }
                }
                left_motor.Stop();
                right_motor.Stop();
                Run[4].Deselect();
            }
            else if (Run[5].Pressed(x, y, 0))
            {
                left_motor.SetPercent(lpower);
                right_motor.SetPercent(0);
                while(Run[5].Pressed(x, y, 1))
                {
                    if(ec){
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                    }
                }
                left_motor.Stop();
                right_motor.Stop();
                Run[5].Deselect();
            }
            else if (Run[6].Pressed(x, y, 0))
            {
                left_motor.SetPercent(0);
                right_motor.SetPercent(-rpower);
                while(Run[6].Pressed(x, y, 1))
                {
                    if(ec){
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                    }
                }
                left_motor.Stop();
                right_motor.Stop();
                Run[6].Deselect();
            }
            else if (Run[7].Pressed(x, y, 0))
            {
                left_motor.SetPercent(-lpower);
                right_motor.SetPercent(0);
                while(Run[7].Pressed(x, y, 1))
                {
                    if(ec){
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                    }
                }
                left_motor.Stop();
                right_motor.Stop();
                Run[7].Deselect();
            }
            else if (SV[5].Pressed(x, y, 0))
            {
                if (ec){
                    ec=false;
                    SV[0].ChangeLabelString("X:");
                    SV[2].ChangeLabelString("Y:");
                    SV[4].ChangeLabelString("Head:");
                } else {
                    ec=true;
                    SV[0].ChangeLabelString("Left:");
                    SV[2].ChangeLabelString("Right:");
                    SV[4].ChangeLabelString("CDS:");
                    SV[1].ChangeLabelInt(left_encoder.Counts());
                    SV[3].ChangeLabelInt(right_encoder.Counts());
                }
                SV[5].Deselect();
            }
            else if (Serv[0].Pressed(x, y, 0))
            {
                while(Serv[0].Pressed(x, y, 1))
                {
                    /* While the run button is being touched, increase or decrease the servo angle within the limits */
                    LCD.Touch(&x, &y);
                    deg++;
                    if (deg>135)
                    {
                        deg = 135;
                    }
                    Serv[2].ChangeLabelInt(deg);
                    servo.SetDegree(deg);
                }
                Serv[0].Deselect();
            }
            else if (Serv[1].Pressed(x, y, 0))
            {
                while(Serv[1].Pressed(x, y, 1))
                {
                    /* While the run button is being touched, increase or decrease the servo angle within the limits */
                    LCD.Touch(&x, &y);
                    deg--;
                    if (deg<0)
                    {
                        deg = 0;
                    }
                    Serv[2].ChangeLabelInt(deg);
                    servo.SetDegree(deg);
                }
                Serv[1].Deselect();
            }
            else if (LM[1].Pressed(x, y, 0))
            {
                while(LM[1].Pressed(x, y, 1))
                {
                    /* While the run button is being touched, increase or decrease the servo angle within the limits */
                    LCD.Touch(&x, &y);
                    lpower++;
                    if (lpower>60)
                    {
                        lpower = 60;
                    }
                    LM[5].ChangeLabelInt(lpower);
                }
                LM[1].Deselect();
            }
            else if (LM[3].Pressed(x, y, 0))
            {
                while(LM[3].Pressed(x, y, 1))
                {
                    /* While the run button is being touched, increase or decrease the servo angle within the limits */
                    LCD.Touch(&x, &y);
                    lpower--;
                    if (lpower<10)
                    {
                        lpower = 10;
                    }
                    LM[5].ChangeLabelInt(lpower);
                }
                LM[3].Deselect();
            }
            else if (RM[1].Pressed(x, y, 0))
            {
                while(RM[1].Pressed(x, y, 1))
                {
                    /* While the run button is being touched, increase or decrease the servo angle within the limits */
                    LCD.Touch(&x, &y);
                    rpower++;
                    if (rpower>60)
                    {
                        rpower = 60;
                    }
                    RM[5].ChangeLabelInt(rpower);
                }
                RM[1].Deselect();
            }
            else if (RM[3].Pressed(x, y, 0))
            {
                while(RM[3].Pressed(x, y, 1))
                {
                    /* While the run button is being touched, increase or decrease the servo angle within the limits */
                    LCD.Touch(&x, &y);
                    rpower--;
                    if (rpower<10)
                    {
                        rpower = 10;
                    }
                    RM[5].ChangeLabelInt(rpower);
                }
                RM[3].Deselect();
            }
            else if (LM[0].Pressed(x,y,0)){
                lpower=25;
                LM[5].ChangeLabelInt(lpower);
                LM[0].Deselect();
            }
            else if (LM[2].Pressed(x,y,0)){
                lpower=40;
                LM[5].ChangeLabelInt(lpower);
                LM[2].Deselect();
            }
            else if (LM[4].Pressed(x,y,0)){
                lpower=60;
                LM[5].ChangeLabelInt(lpower);
                LM[4].Deselect();
            }
            else if (RM[0].Pressed(x,y,0)){
                rpower=25;
                RM[5].ChangeLabelInt(rpower);
                RM[0].Deselect();
            }
            else if (RM[2].Pressed(x,y,0)){
                rpower=40;
                RM[5].ChangeLabelInt(rpower);
                RM[2].Deselect();
            }
            else if (RM[4].Pressed(x,y,0)){
                rpower=60;
                RM[5].ChangeLabelInt(rpower);
                RM[4].Deselect();
            }


            /* If back button has been touched, go to main menu */
            if (Reset[0].Pressed(x, y, 0))
            {
                Reset[0].WhilePressed(x, y);
                SV[1].ChangeLabelInt(0);
                SV[3].ChangeLabelInt(0);
                left_encoder.ResetCounts();
                right_encoder.ResetCounts();
                Reset[0].Deselect();
            }
        }
    }
    return 0;
}
