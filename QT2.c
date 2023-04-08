//============================================================================
// Name        : maiantiem.c
// Author      : Nguyen Khac Minh Luan - 518H0398
// Version     : 1.0
//============================================================================
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
/**********************************************************************
 * Ham: read_File
 * Sinh vien can hoan chinh ham doc_File de thuc hien viec doc gia tri file input.inp
**********************************************************************/
int doc_File(int *d,int *s, char t[])
{
	    //sinh vien viet code de thuc hien viec doc cac gia tri tu file output.out tai thu muc lam viec
    FILE *f = fopen("input.inp", "rb");
    if (!f)
    {
    	fclose(f);
    	return 0;
	}
    fscanf(f, "%d %d %s", *&d,*&s, t);
    fclose(f);

    return 1;
	//sinh vien viet code de thuc hien viec doc cac gia tri tu file input.inp tai thu muc lam viec
}

/**********************************************************************
 * Ham: ghi_File
 * Sinh vien can hoan chinh ham ghi_file de thuc hien viec ghi ket qua p vao file output.out tai thu muc lam viec
**********************************************************************/
void ghi_File(char p[])
{
	FILE *f = fopen("output.out", "wb");
    fprintf(f, "%s", p);
    fclose(f);
	//sinh vien viet code de thuc hien viec ghi ket qua p vao file output.out tai thu muc lam viec
	//%.3f de write du lieu p vao file
}
void substring(char s[], char sub[], int p, int l) {
   int c = 0;
   
   while (c < l-1) {
      sub[c] = s[p+c];
      c++;
   }
   sub[c] = '\0';
}
/**********************************************************************
 * Name: main
 * Target: Implements your application
 **********************************************************************/
int main(int argc, char *argv[]) 
{
	int s = 0,d=0;
	char t[100],n[100],p[100];

	if(doc_File(&d,&s, t))
	{	printf("%d %d %s",d,s,t);
        int i, j, count = 0;
    
        while (t[count] != '\0')
        {
            count++;
        }
            j = count - 1;


        for (i = 0; i < count; i++)
        {
        n[i] = t[j];
        j--;
        
		//sinh vien viet code thuc hien tinh theo yeu cau de bai
	}
    int c=0;
    substring(t,p,d,strlen(t));
    //printf("\nKí tự được lấy: %s",  p);
    strcat(p,t);
    for(i=1;i<=s;i++){
        substring(t,p,d,strlen(t));
        //printf("\nKí tự được lấy: %s",  p);
        strcat(p,t);
        strcpy(t,p);

    }

    printf("\nKết quả: %s",p);

    ghi_File(p);

    return 0;
}
}
