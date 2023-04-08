//============================================================================
// Name        : 518H0398.c
// Author      : Nguyen Khac Minh Luan - 518H0398
// Version     : 1.0
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
/**********************************************************************
 * Ham: read_File
 * Sinh vien can hoan chinh ham doc_File de thuc hien viec doc gia tri file input.inp
**********************************************************************/
int doc_File(int *hp, int *d, int *s, char t[])
{
    //sinh vien viet code de thuc hien viec doc cac gia tri tu file output.out tai thu muc lam viec
    FILE *f = fopen("input.inp", "rb");
    if (!f)
    {
    	fclose(f);
    	return 0;
	}
    fscanf(f, "%d %d %d %s", *&hp, *&d, *&s, t);
    fclose(f);

    return 1;
}

/**********************************************************************
 * Ham: ghi_File
 * Sinh vien can hoan chinh ham ghi_file de thuc hien viec ghi ket qua p vao file output.out tai thu muc lam viec
**********************************************************************/
void ghi_File(float p)
{
    //sinh vien viet code de thuc hien viec ghi ket qua p vao file output.out tai thu muc lam viec
    FILE *f = fopen("output.out", "wb");
    if (p >=1.0)
        fprintf(f,"1.000");
    else if (p<=0)
        fprintf(f, "0.000");
    else
        fprintf(f, "%.3f", p);
    fclose(f);
}

int is_prime(int n)
{
    if (n < 2)
        return 0;
    else
        for (int i = 2; i <= sqrt(n); ++i)
            if (n % i == 0)
                return 0;
    return 1;
}

bool is_perfectSquare(int x)
{
    int s = sqrt(x);
    return (s*s == x);
}


bool is_fibonacci(int n)
{

    return is_perfectSquare(5*n*n + 4) ||
           is_perfectSquare(5*n*n - 4);
}



float productivity(int s, char t[])
{
    const float Flood[6] = {-0.1, -0.15, -0.2, -0.25, -0.05, 0.0};
    const float Storm[6] = {-0.05, -0.1, -0.15, -0.2, 0.0, 0.05};
    const float Rain[6] = {0.0, -0.05, -0.1, -0.15, 0.05, 0.1};
    const float Shower[6] = {0.05, 0.0, -0.05, -0.1, 0.1, 0.15};
    const float Drizzle[6] = {0.1, 0.5, 0.0, -0.05, 0.15, 0.2};
    const float Cloudy[6] = {0.15 , 0.10, 0.05, 0.0, 0.2, 0.25};
    if (strcmp(t, "Flood") == 0)
        return Flood[s%6];
    else if (strcmp(t, "Storm") == 0)
        return Storm[s%6];
    else if (strcmp(t, "Rain") == 0)
        return Rain[s%6];
    else if (strcmp(t, "Shower") == 0)
        return Shower[s%6];
    else if (strcmp(t, "Drizzle") == 0)
        return Drizzle[s%6];
    else
        return Cloudy[s%6];
}

int T(int s)
{
    int n = (s%5)+5.0;
    return n*(n+1)/2;
}

float g(int s)
{
    if (s%6==0)
        return s*1.0/2;
    else if (s%6==1)
        return 2.0*s;
    else if (s%6==2)
        return (-pow((s%9)*1.0, 3)/5.0);
    else if (s%6==3)
        return -(pow((s%30)*1.0, 2)) + 3*s;
    else if (s%6==4)
        return -s*1.0;
    else if(s%6==5)
        return -T(s)*1.0;
    
}


float probability(float P1, float P2, float f)
{
    float numerator, denominator, p;
    numerator = P1 + (P2 * f) ;
    denominator = 1000 + abs((P2 * f));
    p = numerator/denominator;
    return p;
}

void set_P1_P2(float *P1, float *P2, int hp, int s, int d)
{
	if (is_prime(hp))
    {
        *P1 = 1000.0;
        *P2 = ((hp+s)%1000)*1.0;
    }
    if (!is_prime(hp))
    {
        *P1 = hp*1.0;
        *P2 = ((hp+d)%100)*1.0;
    }
}
/**********************************************************************
 * Name: main
 * Target: Implements your application
 **********************************************************************/
int main()
{
    int hp = 0, d = 0, s = 0;
    char t[100];
    float P1 = 0, P2 = 0, p = -1, snake=0, f;
    if(doc_File(&hp, &d, &s, t))
    {
        //sinh vien viet code thuc hien tinh theo yeu cau de bai
        if (d < 200 && !is_fibonacci(d+s) && is_prime(hp))
            p = 1;
        
        if (d<200 && !is_fibonacci(d+s) && !is_prime(hp)){
            set_P1_P2(&P1, &P2, hp, s, d);
            p = P1/1000;
           
        }
        else if (d<200 && is_fibonacci(d+s) && !is_prime(hp))
        {
            set_P1_P2(&P1, &P2, hp, s, d);
            f = (40 - (float)(abs(d-500))/20 + g(s)) * (1+ productivity(s, t));
            p = probability(P1, P2, f);
        }

        else if (200<=d && d<300)
        {
            set_P1_P2(&P1, &P2, hp, s, d);
            snake = (d+P1+P2)*1.0/1000;
            if (0<snake && snake<=0.2)
            {
                set_P1_P2(&P1, &P2, hp, s, d);
                f = (40 - (float)(abs(d-500))/20 + g(s)) * (1+ productivity(s, t));
                p = probability(P1, P2, f);
            }
            else if (0.2<snake && snake<=0.4)
            {
                hp -= 20;
                set_P1_P2(&P1, &P2, hp, s, d);
                f = (40 - (float)(abs(d-500))/20 + g(s)) * (1+ productivity(s, t));
                p = probability(P1, P2, f);
            }
            else if (0.4<snake && snake<=0.6)
            {
                hp -= 30;
                set_P1_P2(&P1, &P2, hp, s, d);
                f = (40 - (float)(abs(d-500))/20 + g(s)) * (1+ productivity(s, t));
                p = probability(P1, P2, f);
            }
            else if (0.6<snake && snake<=0.8)
            {
                hp -= 50;
                set_P1_P2(&P1, &P2, hp, s, d);

                f = (40 - (float)(abs(d-500))/20 + g(s)) * (1+ productivity(s, t));
                p = probability(P1, P2, f);
            }
            else
                 p = 0;
        }
        else if (d>=200 && d<=800)
        {
            set_P1_P2(&P1, &P2, hp, s, d);
            f = (40 - (float)(abs(d-500))/20 + g(s)) * (1+ productivity(s, t));
            p = probability(P1, P2, f);

        }
        else if (d > 800)
        {
            set_P1_P2(&P1, &P2, hp, s, d);
          	f = ((-d*s))*1.0/1000;
            
          	p = probability(P1, P2, f);
        }
    }
    printf("%.3f", p);
    ghi_File(p);

    return 1;
}
