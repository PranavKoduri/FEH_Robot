#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>

#define sleepcheck 0.1
#define powercheck 18

DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_2);
FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor0,9.0);
AnalogInputPin cds(FEHIO::P3_7);
FEHServo servo(FEHServo::Servo0);

FEHIcon::Icon startstop[1];

void check_heading(float heading, float x, float y) //using RPS
{
    //check if receiving proper RPS coordinates
    if (RPS.Heading()>=0)
    {
        if (heading<1 || heading>=359){
            float lower;
            float upper;
            if (heading<3){
                upper=heading-1+360;
                lower=heading+1;
            } else {
                upper=heading-1;
                lower=heading+1-360;
            }
            while(RPS.Heading() < upper && RPS.Heading() > lower)
            {
                if (startstop[0].Pressed(x,y,1)){
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(1.0);
                    LCD.ClearBuffer();
                    break;
                }
                if(RPS.Heading() < 180)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(powercheck);
                    right_motor.SetPercent(-powercheck);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
                else if(RPS.Heading() >= 180)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(-powercheck);
                    right_motor.SetPercent(powercheck);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
            }
        }
        //check whether the robot is within an acceptable range
        else{
            while(RPS.Heading() < heading - 1 || RPS.Heading() > heading + 1)
            {
                if (startstop[0].Pressed(x,y,1)){
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(1.0);
                    LCD.ClearBuffer();
                    break;
                }
                if(RPS.Heading() > heading)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(powercheck);
                    right_motor.SetPercent(-powercheck);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
                else if(RPS.Heading() < heading)
                {
                    //pulse the motors for a short duration in the correct direction

                    left_motor.SetPercent(-powercheck);
                    right_motor.SetPercent(powercheck);
                    Sleep(sleepcheck);
                    left_motor.Stop();
                    right_motor.Stop();
                    Sleep(sleepcheck);
                }
            }
        }
    }
}

void check_x_minus(float x_coordinate, float x, float y) //using RPS while robot is in the -x direction
{
    //check if receiving proper RPS coordinates
    if (RPS.X()>=0)
    {
        //check whether the robot is within an acceptable range
        while(RPS.X() < x_coordinate - 0.2 || RPS.X() > x_coordinate + 0.2)
        {
            if (startstop[0].Pressed(x,y,1)){
                left_motor.Stop();
                right_motor.Stop();
                Sleep(1.0);
                LCD.ClearBuffer();
                break;
            }
            if(RPS.X() > x_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(powercheck);
                right_motor.SetPercent(powercheck);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
            else if(RPS.X() < x_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(-powercheck);
                right_motor.SetPercent(-powercheck);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
        }
    }
}

void check_x_plus(float x_coordinate, float x, float y) //using RPS while robot is in the -x direction
{
    //check if receiving proper RPS coordinates
    if (RPS.X()>=0)
    {
        //check whether the robot is within an acceptable range
        while(RPS.X() < x_coordinate - 0.2 || RPS.X() > x_coordinate + 0.2)
        {
            if (startstop[0].Pressed(x,y,1)){
                left_motor.Stop();
                right_motor.Stop();
                Sleep(1.0);
                LCD.ClearBuffer();
                break;
            }
            if(RPS.X() > x_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(-powercheck);
                right_motor.SetPercent(-powercheck);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
            else if(RPS.X() < x_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(powercheck);
                right_motor.SetPercent(powercheck);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
        }
    }
}

void check_y_minus(float y_coordinate, float x, float y) //using RPS while robot is in the -y direction
{
    //check if receiving proper RPS coordinates
    if (RPS.Y()>=0)
    {
        //check whether the robot is within an acceptable range
        while(RPS.Y() < y_coordinate - 0.2 || RPS.Y() > y_coordinate + 0.2)
        {
            if (startstop[0].Pressed(x,y,1)){
                left_motor.Stop();
                right_motor.Stop();
                Sleep(1.0);
                LCD.ClearBuffer();
                break;
            }
            if(RPS.Y() > y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(powercheck);
                right_motor.SetPercent(powercheck);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
            else if(RPS.Y() < y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(-powercheck);
                right_motor.SetPercent(-powercheck);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
        }
    }
}

void check_y_plus(float y_coordinate, float x, float y) //using RPS while robot is in the +y direction
{
    //check if receiving proper RPS coordinates
    if (RPS.Y()>=0)
    {
        //check whether the robot is within an acceptable range
        while(RPS.Y() < y_coordinate - 0.2 || RPS.Y() > y_coordinate + 0.2)
        {
            if (startstop[0].Pressed(x,y,1)){
                left_motor.Stop();
                right_motor.Stop();
                Sleep(1.0);
                LCD.ClearBuffer();
                break;
            }
            if(RPS.Y() > y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(-powercheck);
                right_motor.SetPercent(-powercheck);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
            else if(RPS.Y() < y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction

                left_motor.SetPercent(powercheck);
                right_motor.SetPercent(powercheck);
                Sleep(sleepcheck);
                left_motor.Stop();
                right_motor.Stop();
                Sleep(sleepcheck);
            }
        }
    }
}

int main(void)
{
    LCD.Clear();
    //RPS.InitializeTouchMenu();

    /** -----------       Create icons for first multipurpose menu ------------        */
    FEHIcon::Icon Reset[1];
    char back_label[1][20] = {"Reset"};

    FEHIcon::Icon SV[6];
    char sv_labels[6][20] = {"Left:", "0", "Right:", "0","CDS:","0"};

    FEHIcon::Icon LM[6];
    char lm_labels[6][20] = {"25", "^", "40", "v","60","25"};

    FEHIcon::Icon RM[6];
    char rm_labels[6][20] = {"25", "^", "40", "v","60","25"};

    FEHIcon::Icon Run[8];
    char run_labels[8][20] = {"F", "B" ,"TLP","TRP","TLF","TRF","TLB","TRB"};

    FEHIcon::Icon Serv[3];
    char s_labels[3][20] = {"v","^","0"};
    /** -------------------            Create icons for RPS menu -------------------         */
    FEHIcon::Icon XC[15];
    char xcl[15][20]={"","^","^","","^","X","0","0",".","0","","v","v","","v"};

    FEHIcon::Icon YC[15];
    char ycl[15][20]={"","^","^","","^","Y","0","0",".","0","","v","v","","v"};

    FEHIcon::Icon HC[18];
    char hcl[18][20]={"","^","^","^","","^","H","0","0","0",".","0","","v","v","v","","v"};

    FEHIcon::Icon rpsdisp[6];
    char rpsl[6][20]={"X:","","Y:","","H:",""};

    //declared above
    char ssl[1][20]={"Start"};

    //also uses reset from multipurpose
    char toshaft[1][20]={"Shaft"};
    /** ------------------------        Create icons for shaft encoder menu -----------------        */
    FEHIcon::Icon EC[12];
    char ecl[12][20]={"^","^","^","^","0","0","0","0","v","v","v","v"};

    //declared above, also uses startstop from rps
    char sl[1][20]={"Stop"};

    //also uses Run from multipurpose

    //also uses SV from multipurpose
    char sh_labels[6][20] = {"Left:", "0", "Right:", "0","Avg:","0"};

    //also uses reset from multipurpose
    char tohome[1][20]={"Home"};
    /** ----------------------------------             DONE              ---------------------------------- */

    float x, y;

    //multipurpose vars
    servo.SetDegree(0);
    int deg=0;
    bool ec=true; //also for shaft
    int lpower=25;
    int rpower=25;

    //rps vars
    int xrps[3]={0,0,0};
    int yrps[3]={0,0,0};
    int hrps[4]={0,0,0,0};

    //shaft vars
    int sh[4]={0,0,0,0};

    while(true)
    {
        FEHIcon::DrawIconArray(Reset, 1, 1, 205, 5, 1, 256, back_label, WHITE, WHITE);
        FEHIcon::DrawIconArray(SV, 3, 2, 1, 150, 1, 150, sv_labels, WHITE, WHITE);
        FEHIcon::DrawIconArray(LM, 3, 2, 97,53,20, 220, lm_labels, BLUE, BLUE);
        FEHIcon::DrawIconArray(RM, 3, 2, 97, 53, 100,140 , rm_labels, RED, RED);
        FEHIcon::DrawIconArray(Run, 4, 2, 10, 21, 201, 1, run_labels, WHITE, WHITE);
        FEHIcon::DrawIconArray(Serv, 1, 3, 205, 5, 72, 128, s_labels, WHITE, WHITE);
        ec=true;
        SV[1].ChangeLabelInt(left_encoder.Counts());
        SV[3].ChangeLabelInt(right_encoder.Counts());
        LM[5].ChangeLabelInt(lpower);
        RM[5].ChangeLabelInt(rpower);
        Serv[2].ChangeLabelInt(deg);

        while(true){
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
                else if (Reset[0].Pressed(x, y, 0))
                {
                    Reset[0].WhilePressed(x, y);
                    SV[1].ChangeLabelInt(0);
                    SV[3].ChangeLabelInt(0);
                    left_encoder.ResetCounts();
                    right_encoder.ResetCounts();
                    Reset[0].Deselect();
                }
                else if (SV[0].Pressed(x, y, 0)){
                    LCD.Clear();
                    break;
                }
            }
        }

        FEHIcon::DrawIconArray(XC, 3, 5, 5, 145, 5, 215, xcl, BLUE, WHITE);
        FEHIcon::DrawIconArray(YC, 3, 5, 5, 145, 150, 70, ycl, BLUE, WHITE);
        FEHIcon::DrawIconArray(HC, 3, 6, 105, 45, 5, 185, hcl, BLUE, WHITE);
        FEHIcon::DrawIconArray(rpsdisp, 3, 2, 105, 45, 150, 10, rpsl, WHITE, WHITE);
        FEHIcon::DrawIconArray(startstop, 1, 1, 205, 5, 20, 230, ssl, BLUE, WHITE);
        FEHIcon::DrawIconArray(Reset, 1, 1, 205, 5, 150, 100, toshaft, BLUE, WHITE);
        XC[6].ChangeLabelInt(xrps[0]);
        XC[7].ChangeLabelInt(xrps[1]);
        XC[9].ChangeLabelInt(xrps[2]);
        YC[6].ChangeLabelInt(yrps[0]);
        YC[7].ChangeLabelInt(yrps[1]);
        YC[9].ChangeLabelInt(yrps[2]);
        HC[7].ChangeLabelInt(hrps[0]);
        HC[8].ChangeLabelInt(hrps[1]);
        HC[9].ChangeLabelInt(hrps[2]);
        HC[11].ChangeLabelInt(hrps[3]);

        while (true){
            rpsdisp[1].ChangeLabelFloat(RPS.X());
            rpsdisp[3].ChangeLabelFloat(RPS.Y());
            rpsdisp[5].ChangeLabelFloat(RPS.Heading());
            if (LCD.Touch(&x, &y)){
                if (XC[1].Pressed(x, y, 0))
                {
                    xrps[0]++;
                    if (xrps[0]>=3){
                        if (xrps[1]>5){
                            xrps[1]=5;
                            XC[7].ChangeLabelInt(5);
                        }
                        xrps[0]=3;
                    }
                    XC[6].ChangeLabelInt(xrps[0]);
                    XC[1].Deselect();
                } else if (XC[2].Pressed(x, y, 0)) {
                    xrps[1]++;
                    if (xrps[0]==3 && xrps[1]>5) xrps[1]=5;
                    else if (xrps[1]>9) xrps[1]=9;
                    XC[7].ChangeLabelInt(xrps[1]);
                    XC[2].Deselect();
                } else if (XC[4].Pressed(x, y, 0)) {
                    xrps[2]++;
                    if (xrps[2]>9) xrps[2]=9;
                    XC[9].ChangeLabelInt(xrps[2]);
                    XC[4].Deselect();
                } else if (XC[11].Pressed(x, y, 0)) {
                    xrps[0]--;
                    if (xrps[0]<0) xrps[0]=0;
                    XC[6].ChangeLabelInt(xrps[0]);
                    XC[11].Deselect();
                } else if (XC[12].Pressed(x, y, 0)) {
                    xrps[1]--;
                    if (xrps[1]<0) xrps[1]=0;
                    XC[7].ChangeLabelInt(xrps[1]);
                    XC[12].Deselect();
                } else if (XC[14].Pressed(x, y, 0)) {
                    xrps[2]--;
                    if (xrps[2]<0) xrps[2]=0;
                    XC[9].ChangeLabelInt(xrps[2]);
                    XC[14].Deselect();
                } else if (YC[1].Pressed(x, y, 0))
                {
                    yrps[0]++;
                    if (yrps[0]>=7){
                        if (yrps[1]>1){
                            yrps[1]=1;
                            YC[7].ChangeLabelInt(1);
                        }
                        yrps[0]=7;
                    }
                    YC[6].ChangeLabelInt(yrps[0]);
                    YC[1].Deselect();
                } else if (YC[2].Pressed(x, y, 0)) {
                    yrps[1]++;
                    if (yrps[0]==7 && yrps[1]>1) yrps[1]=1;
                    else if (yrps[1]>9) yrps[1]=9;
                    YC[7].ChangeLabelInt(yrps[1]);
                    YC[2].Deselect();
                } else if (YC[4].Pressed(x, y, 0)) {
                    yrps[2]++;
                    if (yrps[2]>9) yrps[2]=9;
                    YC[9].ChangeLabelInt(yrps[2]);
                    YC[4].Deselect();
                } else if (YC[11].Pressed(x, y, 0)) {
                    yrps[0]--;
                    if (yrps[0]<0) yrps[0]=0;
                    YC[6].ChangeLabelInt(yrps[0]);
                    YC[11].Deselect();
                } else if (YC[12].Pressed(x, y, 0)) {
                    yrps[1]--;
                    if (yrps[1]<0) yrps[1]=0;
                    YC[7].ChangeLabelInt(yrps[1]);
                    YC[12].Deselect();
                } else if (YC[14].Pressed(x, y, 0)) {
                    yrps[2]--;
                    if (yrps[2]<0) yrps[2]=0;
                    YC[9].ChangeLabelInt(yrps[2]);
                    YC[14].Deselect();
                } else if (HC[1].Pressed(x, y, 0))
                {
                    hrps[0]++;
                    if (hrps[0]>=3){
                        if (hrps[1]>5){
                            hrps[1]=5;
                            HC[8].ChangeLabelInt(5);
                        }
                        hrps[0]=3;
                    }
                    HC[7].ChangeLabelInt(hrps[0]);
                    HC[1].Deselect();
                } else if (HC[2].Pressed(x, y, 0)) {
                    hrps[1]++;
                    if (hrps[0]==3 && hrps[1]>5) hrps[1]=5;
                    else if (hrps[1]>9) hrps[1]=9;
                    HC[8].ChangeLabelInt(hrps[1]);
                    HC[2].Deselect();
                } else if (HC[3].Pressed(x, y, 0)) {
                    hrps[2]++;
                    if (hrps[2]>9) hrps[2]=9;
                    HC[9].ChangeLabelInt(hrps[2]);
                    HC[3].Deselect();
                } else if (HC[5].Pressed(x, y, 0)) {
                    hrps[3]++;
                    if (hrps[3]>9) hrps[3]=9;
                    HC[11].ChangeLabelInt(hrps[3]);
                    HC[5].Deselect();
                } else if (HC[13].Pressed(x, y, 0)) {
                    hrps[0]--;
                    if (hrps[0]<0) hrps[0]=0;
                    HC[7].ChangeLabelInt(hrps[0]);
                    HC[13].Deselect();
                } else if (HC[14].Pressed(x, y, 0)) {
                    hrps[1]--;
                    if (hrps[1]<0) hrps[1]=0;
                    HC[8].ChangeLabelInt(hrps[1]);
                    HC[14].Deselect();
                } else if (HC[15].Pressed(x, y, 0)) {
                    hrps[2]--;
                    if (hrps[2]<0) hrps[2]=0;
                    HC[9].ChangeLabelInt(hrps[2]);
                    HC[15].Deselect();
                } else if (HC[17].Pressed(x, y, 0)) {
                    hrps[3]--;
                    if (hrps[3]<0) hrps[3]=0;
                    HC[11].ChangeLabelInt(hrps[3]);
                    HC[17].Deselect();
                } else if (startstop[0].Pressed(x,y,0)){
                    float xt=xrps[0]*10+xrps[1]+xrps[2]*0.1;
                    float yt=yrps[0]*10+yrps[1]+yrps[2]*0.1;
                    startstop[0].ChangeLabelString("Stop");
                    if (xt<RPS.X()){
                        check_heading(180.0,x,y);
                        check_x_minus(xt,x,y);
                    } else {
                        check_heading(0.0,x,y);
                        check_x_plus(xt,x,y);
                    }
                    if (yt<RPS.Y()){
                        check_heading(270.0,x,y);
                        check_y_minus(yt,x,y);
                    } else {
                        check_heading(90.0,x,y);
                        check_y_plus(yt,x,y);
                    }
                    check_heading(hrps[0]*100+hrps[1]*10+hrps[2]+hrps[3]*0.1,x,y);
                    startstop[0].ChangeLabelString("Start");
                }
                else if (Reset[0].Pressed(x, y, 0)){
                    LCD.Clear();
                    break;
                }
            }
        }

        FEHIcon::DrawIconArray(EC, 3, 4, 5, 145, 5, 215, ecl, BLUE, WHITE);
        FEHIcon::DrawIconArray(Run, 4, 2, 10, 21, 201, 1, run_labels, WHITE, WHITE);
        FEHIcon::DrawIconArray(SV, 3, 2, 105, 45, 1, 150, sh_labels, WHITE, WHITE);
        FEHIcon::DrawIconArray(startstop, 1, 1, 205, 5, 20, 230, sl, BLUE, WHITE);
        FEHIcon::DrawIconArray(Reset, 1, 1, 205, 5, 120, 140, tohome, BLUE, WHITE);
        EC[4].ChangeLabelInt(sh[0]);
        EC[5].ChangeLabelInt(sh[1]);
        EC[6].ChangeLabelInt(sh[2]);
        EC[7].ChangeLabelInt(sh[3]);
        ec=true;
        SV[1].ChangeLabelInt(0);
        SV[3].ChangeLabelInt(0);
        SV[5].ChangeLabelInt(0);

        while(true){
            if (!ec){
                SV[1].ChangeLabelFloat(RPS.X());
                SV[3].ChangeLabelFloat(RPS.Y());
                SV[5].ChangeLabelFloat(RPS.Heading());
            }
            if (LCD.Touch(&x, &y))
            {
                if (EC[0].Pressed(x, y, 0))
                {
                    sh[0]=1;
                    EC[4].ChangeLabelInt(1);
                    EC[0].Deselect();
                } else if (EC[1].Pressed(x, y, 0)) {
                    sh[1]++;
                    if (sh[1]>9) sh[1]=9;
                    EC[5].ChangeLabelInt(sh[1]);
                    EC[1].Deselect();
                } else if (EC[2].Pressed(x, y, 0)) {
                    sh[2]++;
                    if (sh[2]>9) sh[2]=9;
                    EC[6].ChangeLabelInt(sh[2]);
                    EC[2].Deselect();
                } else if (EC[3].Pressed(x, y, 0)) {
                    sh[3]++;
                    if (sh[3]>9) sh[3]=9;
                    EC[7].ChangeLabelInt(sh[3]);
                    EC[3].Deselect();
                } else if (EC[8].Pressed(x, y, 0)){
                    sh[0]=0;
                    EC[4].ChangeLabelInt(0);
                    EC[8].Deselect();
                } else if (EC[9].Pressed(x, y, 0)) {
                    sh[1]--;
                    if (sh[1]<0) sh[1]=0;
                    EC[5].ChangeLabelInt(sh[1]);
                    EC[9].Deselect();
                } else if (EC[10].Pressed(x, y, 0)) {
                    sh[2]--;
                    if (sh[2]<0) sh[2]=0;
                    EC[6].ChangeLabelInt(sh[2]);
                    EC[10].Deselect();
                } else if (EC[11].Pressed(x, y, 0)) {
                    sh[3]--;
                    if (sh[3]<0) sh[3]=0;
                    EC[7].ChangeLabelInt(sh[3]);
                    EC[11].Deselect();
                } else if (SV[5].Pressed(x, y, 0)) {
                    if (ec){
                        ec=false;
                        SV[0].ChangeLabelString("X:");
                        SV[2].ChangeLabelString("Y:");
                        SV[4].ChangeLabelString("Head:");
                    } else {
                        ec=true;
                        SV[0].ChangeLabelString("Left:");
                        SV[2].ChangeLabelString("Right:");
                        SV[4].ChangeLabelString("Avg:");
                        SV[1].ChangeLabelInt(left_encoder.Counts());
                        SV[3].ChangeLabelInt(right_encoder.Counts());
                        SV[5].ChangeLabelInt((left_encoder.Counts()+right_encoder.Counts())/2.0);
                    }
                    SV[5].Deselect();
                } else if (Run[0].Pressed(x, y, 0)) {
                    right_encoder.ResetCounts();
                    left_encoder.ResetCounts();
                    int counts=1000*sh[0]+100*sh[1]+sh[2]*10+sh[3];
                    left_motor.SetPercent(lpower);
                    right_motor.SetPercent(rpower);
                    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
                    {
                        if(ec){
                            SV[1].ChangeLabelInt(left_encoder.Counts());
                            SV[3].ChangeLabelInt(right_encoder.Counts());
                            SV[5].ChangeLabelInt((left_encoder.Counts() + right_encoder.Counts()) / 2.);
                        }
                        if (LCD.Touch(&x, &y) && startstop[0].Pressed(x,y,0)){
                            break;
                        }
                    }
                    left_motor.Stop();
                    right_motor.Stop();
                    Run[0].Deselect();
                }
                else if (Run[1].Pressed(x, y, 0))
                {
                    right_encoder.ResetCounts();
                    left_encoder.ResetCounts();
                    int counts=1000*sh[0]+100*sh[1]+sh[2]*10+sh[3];
                    left_motor.SetPercent(-lpower);
                    right_motor.SetPercent(-rpower);
                    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
                    {
                        if(ec){
                            SV[1].ChangeLabelInt(left_encoder.Counts());
                            SV[3].ChangeLabelInt(right_encoder.Counts());
                            SV[5].ChangeLabelInt((left_encoder.Counts() + right_encoder.Counts()) / 2.);
                        }
                        if (LCD.Touch(&x, &y) && startstop[0].Pressed(x,y,0)){
                            break;
                        }
                    }
                    left_motor.Stop();
                    right_motor.Stop();
                    Run[1].Deselect();
                }
                else if (Run[2].Pressed(x, y, 0))
                {
                    right_encoder.ResetCounts();
                    left_encoder.ResetCounts();
                    int counts=1000*sh[0]+100*sh[1]+sh[2]*10+sh[3];
                    left_motor.SetPercent(-lpower);
                    right_motor.SetPercent(rpower);
                    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
                    {
                        if(ec){
                            SV[1].ChangeLabelInt(left_encoder.Counts());
                            SV[3].ChangeLabelInt(right_encoder.Counts());
                            SV[5].ChangeLabelInt((left_encoder.Counts() + right_encoder.Counts()) / 2.);
                        }
                        if (LCD.Touch(&x, &y) && startstop[0].Pressed(x,y,0)){
                            break;
                        }
                    }
                    left_motor.Stop();
                    right_motor.Stop();
                    Run[2].Deselect();
                }
                else if (Run[3].Pressed(x, y, 0))
                {
                    right_encoder.ResetCounts();
                    left_encoder.ResetCounts();
                    int counts=1000*sh[0]+100*sh[1]+sh[2]*10+sh[3];
                    left_motor.SetPercent(lpower);
                    right_motor.SetPercent(-rpower);
                    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
                    {
                        if(ec){
                            SV[1].ChangeLabelInt(left_encoder.Counts());
                            SV[3].ChangeLabelInt(right_encoder.Counts());
                            SV[5].ChangeLabelInt((left_encoder.Counts() + right_encoder.Counts()) / 2.);
                        }
                        if (LCD.Touch(&x, &y) && startstop[0].Pressed(x,y,0)){
                            break;
                        }
                    }
                    left_motor.Stop();
                    right_motor.Stop();
                    Run[3].Deselect();
                }
                else if (Run[4].Pressed(x, y, 0))
                {
                    right_encoder.ResetCounts();
                    left_encoder.ResetCounts();
                    int counts=1000*sh[0]+100*sh[1]+sh[2]*10+sh[3];
                    left_motor.SetPercent(0);
                    right_motor.SetPercent(rpower);
                    while(right_encoder.Counts() < counts)
                    {
                        if(ec){
                            SV[1].ChangeLabelInt(left_encoder.Counts());
                            SV[3].ChangeLabelInt(right_encoder.Counts());
                            SV[5].ChangeLabelInt((left_encoder.Counts() + right_encoder.Counts()) / 2.);
                        }
                        if (LCD.Touch(&x, &y) && startstop[0].Pressed(x,y,0)){
                            break;
                        }
                    }
                    left_motor.Stop();
                    right_motor.Stop();
                    Run[4].Deselect();
                }
                else if (Run[5].Pressed(x, y, 0))
                {
                    right_encoder.ResetCounts();
                    left_encoder.ResetCounts();
                    int counts=1000*sh[0]+100*sh[1]+sh[2]*10+sh[3];
                    left_motor.SetPercent(lpower);
                    right_motor.SetPercent(0);
                    while(left_encoder.Counts() < counts)
                    {
                        if(ec){
                            SV[1].ChangeLabelInt(left_encoder.Counts());
                            SV[3].ChangeLabelInt(right_encoder.Counts());
                            SV[5].ChangeLabelInt((left_encoder.Counts() + right_encoder.Counts()) / 2.);
                        }
                        if (LCD.Touch(&x, &y) && startstop[0].Pressed(x,y,0)){
                            break;
                        }
                    }
                    left_motor.Stop();
                    right_motor.Stop();
                    Run[5].Deselect();
                }
                else if (Run[6].Pressed(x, y, 0))
                {
                    right_encoder.ResetCounts();
                    left_encoder.ResetCounts();
                    int counts=1000*sh[0]+100*sh[1]+sh[2]*10+sh[3];
                    left_motor.SetPercent(0);
                    right_motor.SetPercent(-rpower);
                    while(right_encoder.Counts() < counts)
                    {
                        if(ec){
                            SV[1].ChangeLabelInt(left_encoder.Counts());
                            SV[3].ChangeLabelInt(right_encoder.Counts());
                            SV[5].ChangeLabelInt((left_encoder.Counts() + right_encoder.Counts()) / 2.);
                        }
                        if (LCD.Touch(&x, &y) && startstop[0].Pressed(x,y,0)){
                            break;
                        }
                    }
                    left_motor.Stop();
                    right_motor.Stop();
                    Run[6].Deselect();
                }
                else if (Run[7].Pressed(x, y, 0))
                {
                    right_encoder.ResetCounts();
                    left_encoder.ResetCounts();
                    int counts=1000*sh[0]+100*sh[1]+sh[2]*10+sh[3];
                    left_motor.SetPercent(-lpower);
                    right_motor.SetPercent(0);
                    while(left_encoder.Counts() < counts)
                    {
                        if(ec){
                            SV[1].ChangeLabelInt(left_encoder.Counts());
                            SV[3].ChangeLabelInt(right_encoder.Counts());
                            SV[5].ChangeLabelInt((left_encoder.Counts() + right_encoder.Counts()) / 2.);
                        }
                        if (LCD.Touch(&x, &y) && startstop[0].Pressed(x,y,0)){
                            break;
                        }
                    }
                    left_motor.Stop();
                    right_motor.Stop();
                    Run[7].Deselect();
                } else if (Reset[0].Pressed(x, y, 0)){
                    LCD.Clear();
                    break;
                }
            }
        }

    }
    return 0;
}
