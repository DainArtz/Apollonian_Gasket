#include <iostream>
#include <cmath>
#include "graphics2.h"
#include <windows.h>

using namespace std;

HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);

struct cerc ///definirea unui cerc prin struct
{
    int x, y, R;
    double curve;
};
cerc Cc; ///cercul cu raza cea mai mare (circumscris celorlalte)

int INPUT;
int midx, midy; ///mijloace
int minR; ///raza minima permisa

void menu();
void Apollo(cerc C1, cerc C2, cerc C3); ///determinarea unui cerc tangent cu 3 cercuri tangente
void ApolloMargine(cerc C1, cerc C2); ///determinarea unui cerc tangent cu 2 cercuri tangente si cu cercul circumscris

int main()
{
    menu(); ///desenarea meniului si introducerea datelor

    ///initializari
    int driver, mod;
    initgraph(&driver, &mod, "", 1920, 1080);
    midx = getmaxx()/2; ///determinarea mijloacelor ferestrei
    midy = getmaxy()/2;
    setcolor(WHITE);

    ///definirea cercului circumscris
    Cc.R=INPUT;
    Cc.x=midx;
    Cc.y=midy;
    Cc.curve=(1.0/Cc.R);
    circle(Cc.x, Cc.y, Cc.R);
    Sleep(100);

    ///definirea celor 3 cercuri tangente de la inceput
    cerc C1, C2, C3;
    double L; ///latura trunghiului echilateral
    L=6.0*Cc.R/(2.0*sqrt(3.0)+3.0);
    C1.R=L/2+1;
    C2.R=L/2+1;
    C3.R=L/2+1;
    C1.curve=(1.0/C1.R);
    C2.curve=(1.0/C2.R);
    C3.curve=(1.0/C3.R);
    C1.x=Cc.x;
    C1.y=Cc.y-L*double(sqrt(3.0)/3.0);
    C2.x=Cc.x-L/2;
    C2.y=Cc.y+L*double(sqrt(3.0)/6.0);
    C3.x=Cc.x+L/2;
    C3.y=Cc.y+L*double(sqrt(3.0)/6.0);
    circle(C1.x, C1.y, C1.R);
    Sleep(100);
    circle(C2.x, C2.y, C2.R);
    Sleep(100);
    circle(C3.x, C3.y, C3.R);
    Sleep(100);

    ///apelarea functiilor recursive
    Apollo(C1, C2, C3);
    setcolor(RED);
    ApolloMargine(C1, C2);
    setcolor(GREEN);
    ApolloMargine(C1, C3);
    setcolor(BLUE);
    ApolloMargine(C2, C3);
    setcolor(WHITE);

    ///incheiere
    while( !kbhit() );
    closegraph();

    return 0;
}
void Apollo(cerc C1, cerc C2, cerc C3)
{
    cerc C4;
    int a, b, c, d, ap, bp, cp, dp, x, y;
    C4.curve=C1.curve + C2.curve + C3.curve + 2*sqrt(C1.curve*C2.curve + C1.curve*C3.curve + C2.curve*C3.curve); ///descartes
    C4.R=int(1.0/C4.curve);
    if (C4.R>minR)
    {
        a=2*(C1.x-C2.x);
        b=2*(C1.y-C2.y);
        c=2*abs(C1.R-C2.R);
        d=(C1.x * C1.x + C1.y * C1.y - C1.R * C1.R)-(C2.x * C2.x + C2.y * C2.y - C2.R * C2.R);
        ap=2*(C1.x-C3.x);
        bp=2*(C1.y-C3.y);
        cp=2*abs(C1.R-C3.R);
        dp=(C1.x * C1.x + C1.y * C1.y - C1.R * C1.R)-(C3.x * C3.x + C3.y * C3.y - C3.R * C3.R);

        ///calculul coordonatelor centrului
        x=(bp*d-b*dp-bp*c*C4.R+b*cp*C4.R)/(a*bp-b*ap);
        y=(a*dp-ap*d+ap*c*C4.R-a*cp*C4.R)/(a*bp-ap*b);

        C4.x=x;
        C4.y=y;

        circle(C4.x, C4.y, C4.R);
        Sleep(100);

        ///apeluri recursive
        Apollo(C1, C2, C4);
        Apollo(C1, C3, C4);
        Apollo(C2, C3, C4);
    }
}
void ApolloMargine(cerc C1, cerc C2)
{
    cerc C4;
    int a, b, c, d, ap, bp, cp, dp, x, y;
    C4.curve=C1.curve + C2.curve - Cc.curve + 2*sqrt(C1.curve*C2.curve - C1.curve*Cc.curve - C2.curve*Cc.curve); ///descartes
    C4.R=int(1.0/C4.curve);
    if (C4.R>minR)
    {
        a=2*(C1.x-Cc.x);
        b=2*(C1.y-Cc.y);
        c=2*abs(C1.R+Cc.R);
        d=(C1.x * C1.x + C1.y * C1.y - C1.R * C1.R)-(Cc.x * Cc.x + Cc.y * Cc.y - Cc.R * Cc.R);
        ap=2*(C2.x-Cc.x);
        bp=2*(C2.y-Cc.y);
        cp=2*abs(C2.R+Cc.R);
        dp=(C2.x * C2.x + C2.y * C2.y - C2.R * C2.R)-(Cc.x * Cc.x + Cc.y * Cc.y - Cc.R * Cc.R);

        ///calculul coordonatelor centrului
        x=(bp*d-b*dp-bp*c*C4.R+b*cp*C4.R)/(a*bp-b*ap);
        y=(a*dp-ap*d+ap*c*C4.R-a*cp*C4.R)/(a*bp-ap*b);

        C4.x=x;
        C4.y=y;

        circle(C4.x, C4.y, C4.R);
        Sleep(10);

        ///apeluri recursive
        ApolloMargine(C1, C4);
        ApolloMargine(C2, C4);
        Apollo(C1, C2, C4);
    }
}
void menu()
{
    ///titlu
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<"                                              ";
    SetConsoleTextAttribute(color, 15);
    cout<<"Welcome to ";
    SetConsoleTextAttribute(color, 13);
    cout<<"The Apollonian Gasket"<<'\n';

    ///primul input
    Sleep(2000);
    system("CLS");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<"                                          ";
    SetConsoleTextAttribute(color, 15);
    cout<<"Enter the ";
    SetConsoleTextAttribute(color, 11);
    cout<<"starting ";
    SetConsoleTextAttribute(color, 13);
    cout<<"radius (<= 400)";
    SetConsoleTextAttribute(color, 15);
    cout<<": ";
    SetConsoleTextAttribute(color, 13);
    cin>>INPUT;
    SetConsoleTextAttribute(color, 15);

    ///al doilea input
    Sleep(2000);
    system("CLS");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<"                                          ";
    SetConsoleTextAttribute(color, 15);
    cout<<"Enter the ";
    SetConsoleTextAttribute(color, 11);
    cout<<"minimum ";
    SetConsoleTextAttribute(color, 13);
    cout<<"radius ";
    SetConsoleTextAttribute(color, 15);
    cout<<"allowed (>=1): ";
    SetConsoleTextAttribute(color, 13);
    cin>>minR;
    SetConsoleTextAttribute(color, 15);

    ///incheiere
    Sleep(1000);
    system("CLS");

}
