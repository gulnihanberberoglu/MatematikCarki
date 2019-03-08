//140202014 Sevgi ALKAN, 160202097 Gülnihan BERBEROĞLU
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define randnum(min, max) \
((rand() % (int)(((max) + 1) - (min))) + (min))   // bu rastgele sayi ureten kod parcasi internettten alinmistir!

int determ(int a[][3], int n)
{
    int det = 0, p, h, k, i, j, temp[3][3];
    if (n == 1)
    {
        return a[0][0];
    }
    else if (n == 2)
    {
        det = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
        return det;
    }
    else
    {
        for (p = 0; p<n; p++)
        {
            h = 0;
            k = 0;
            for (i = 1; i<n; i++)
            {
                for (j = 0; j<n; j++)
                {
                    if (j == p)
                    {
                        continue;
                    }
                    temp[h][k] = a[i][j];
                    k++;
                    if (k == n - 1)
                    {
                        h++;
                        k = 0;
                    }
                }
            }
            det = det + a[0][p] * pow(-1, p)*determ(temp, n - 1);
        }
        return det;
    }
}
int *ozdegerbul()
{
    int n;
    printf("\nmatris boyutunu giriniz:");
    scanf("%d",&n);

    int m[n][n];
    int i,j;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("[%d][%d].eleman:",i,j);
            scanf("%d",&m[i][j]);
        }
    }

    int q=NULL;

    int birim[n][n];
    int detMatrix[n][n];

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i==j)
            {
                birim[i][j] = q;
                detMatrix[i][j] = q + (-1*m[i][j]);
            }
            else
            {
                birim[i][j] = 0;
                detMatrix[i][j] = m[i][j];
            }
        }
    }

    int dizi[20];
    //burada q ya değer vermeden null olarak determinantı hesapladıgımızda, hesaplanacak a değeri bizim matematiksel
    //olarak determinant hesaplarken en son olusan lambdalı fonksiyonun sonundaki lambdasız kısım olacaktır.
    //yani carpanlara ayırdığımız tam kısım.
    //eger bu a negatif ise bunu pozitife cevirip bunun tüm bolenlerini(carpan) bulalım.
    int a = determ(detMatrix, n);
    if (a < 0) a = a*(-1);
    int sayac = 0;

    for ( i = 1; i<=a; i++)
    {
        if (a%i == 0)
        {
            dizi[sayac] = i;
            sayac++;
        }
    }
    //burda ise bolenlerini bulduktan sonra birde onların negatiflerini onceden bolenleri koymak icin
    //olusturdugumuz dizinin sonuna ekleyelim.
    for ( j = 0; j < sayac; j++)
    {
        dizi[sayac + j] = -(dizi[j]);
    }

    //burada bizim sonuc olarak diziye eklediğimiz tum elemanlar aday özdegerler oluyor.bunları c değiskenine
    //atayarak yeniden birim matrisi olusturuyoruz ve ana matrisi bundan cıkartıp determinantı yenıden
    //hesaplayacagız.
    //yalnız c degerlerinin herbirini atadıktan sonra determinantı hesaplayıp bakıyoruz sonra bir sonraki
    //c degerini atayıp devam ediyoruz.

    int h;

    FILE*fp;

    fp=fopen("ozdeger.txt","w");
    printf("Ozdegerler \n:");
    fprintf(fp,"ozdegerler: \n");

    int *ozDegerler = malloc(sizeof(int) * 20);  // 20 tane integer deger boyutundan bellekten yer ayırıyoruz.

    int dd = 0; // gecici degisken

    for ( h = 0; h < 2 * sayac; h++)
    {
        int c = dizi[h];
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                if (i == j)birim[i][j] = c;
            }
        }

        for ( i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                detMatrix[i][j] = birim[i][j] - m[i][j];
            }
        }

        int b = determ(detMatrix, 3);

        //simdi aday özdegerleri (c) yerine koyup cıkardıktan sonra olusan matrisin determinantı (b) 0 ise bu demektirki
        //bizim o c degerimiz öz değer oluyor.
        if (b == 0)
        {
            ozDegerler[dd] = dizi[h];
            printf("%d \n",dizi[h]);
            fprintf(fp,"%d\n", dizi[h]);
            dd++;
        }
    }

    int matrisKareToplami = 0;  /** schur ozelliginde kullanılmak uzere degisken olusturduk.*/

    fprintf(fp,"girilen kare matris\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            fprintf(fp,"%d  ", m[i][j]);
            matrisKareToplami += pow(m[i][j],2);  /** matris kare toplami icin matrisin her degerinin karesini alip topluyoruz.*/
        }
        fprintf(fp,"\n");

    }

    ozDegerler[4] = matrisKareToplami; /**schur  icin ozdegerler dizisisinin 4.degeri olarak matris kare toplamini verdik.*/


    fprintf(fp,"\n\nOlusun ara matris\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if(i==j)
            {
                if(((-1)*m[i][j]) > 0)
                {
                    fprintf(fp,"q+%d ",((-1)*m[i][j]));
                }
                else
                {
                    fprintf(fp,"q%d ", ((-1)*m[i][j]));
                }

            }
            else
            {
                fprintf(fp,"%d  ", ((-1)*m[i][j]));
            }

        }
        fprintf(fp,"\n");

    }


    fclose(fp);

    return ozDegerler;
}
void schur()
{
    int *x  = ozdegerbul();

    int i;
    int schurOzdegerlerKareToplami = 0;

    for(i=0; i<3; i++)
    {
        schurOzdegerlerKareToplami += pow(x[i],2);
    }

    int matrisDegerleriKareToplami = x[4];
    printf("matris kareleri toplami : %d\n",matrisDegerleriKareToplami);
    printf("ozdegerlerin kareleri toplami : %d ",schurOzdegerlerKareToplami);
    printf("\nSchur sinir degeri : %d < %d elde edilir.\n",schurOzdegerlerKareToplami,matrisDegerleriKareToplami);

    FILE *fp;

    fp=fopen("schur.txt","w");
    fprintf(fp,"matris kareleri toplami : %d\n",x[4]);
    fprintf(fp,"ozdegerlerin kareleri toplami : %d ",schurOzdegerlerKareToplami);
    fprintf(fp,"\nSchur sinir degeri : %d < %d elde edilir.\n",schurOzdegerlerKareToplami,matrisDegerleriKareToplami);
    fclose(fp);

    free(x);
    x=NULL;
}
void ozvektorbul()
{
    int n;
    printf("\nmatris boyutunu giriniz:");
    scanf("%d",&n);

    int m[n][n];
    int i,j;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("[%d][%d].eleman:",i,j);
            scanf("%d",&m[i][j]);
        }
    }
    int q=NULL;

    int birim[n][n];
    int detMatrix[n][n];

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i==j)
            {
                birim[i][j] = q;
                detMatrix[i][j] = q + (-1*m[i][j]);
            }
            else
            {
                birim[i][j] = 0;
                detMatrix[i][j] = m[i][j];
            }
        }
    }

    int dizi[20];
    //burada q ya değer vermeden null olarak determinantı hesapladıgımızda, hesaplanacak a değeri bizim matematiksel
    //olarak determinant hesaplarken en son olusan lambdalı fonksiyonun sonundaki lambdasız kısım olacaktır.
    //yani carpanlara ayırdığımız tam kısım.
    //eger bu a negatif ise bunu pozitife cevirip bunun tüm bolenlerini(carpan) bulalım.
    int a = determ(detMatrix, 3);
    if (a < 0) a = a*(-1);
    int sayac = 0;

    for ( i = 1; i<=a; i++)
    {
        if (a%i == 0)
        {
            dizi[sayac] = i;
            sayac++;
        }
    }
    //burda ise bolenlerini bulduktan sonra birde onların negatiflerini onceden bolenleri koymak icin
    //olusturdugumuz dizinin sonuna ekleyelim.
    for ( j = 0; j < sayac; j++)
    {
        dizi[sayac + j] = -(dizi[j]);
    }

    //burada bizim sonuc olarak diziye eklediğimiz tum elemanlar aday özdegerler oluyor.bunları c değiskenine
    //atayarak yeniden birim matrisi olusturuyoruz ve ana matrisi bundan cıkartıp determinantı yenıden
    //hesaplayacagız.
    //yalnız c degerlerinin herbirini atadıktan sonra determinantı hesaplayıp bakıyoruz sonra bir sonraki
    //c degerini atayıp devam ediyoruz.
    int h;

    FILE*fp;

    fp=fopen("ozvektor.txt","w");
    printf("Ozdegerler \n:");
    fprintf(fp,"ozdegerler: \n");

    int *ozDegerler = malloc(sizeof(int) * 20);
    int dd = 0;
    for ( h = 0; h < 2 * sayac; h++)
    {
        int c = dizi[h];
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                if (i == j)birim[i][j] = c;
            }
        }

        for ( i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                detMatrix[i][j] = birim[i][j] - m[i][j];
            }
        }

        int b = determ(detMatrix, 3);

        //simdi aday özdegerleri (c) yerine koyup cıkardıktan sonra olusan matrisin determinantı (b) 0 ise bu demektirki
        //bizim o c degerimiz öz değer oluyor.
        if (b == 0)
        {
            ozDegerler[dd] = dizi[h];
            printf("%d \n",dizi[h]);
            fprintf(fp,"\t %d\n", dizi[h]);
            dd++;

        }
    }


    fprintf(fp,"girilen kare matris\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            fprintf(fp,"%d  ", m[i][j]);
        }
        fprintf(fp,"\n");

    }


    fprintf(fp,"\n\nOluşan ara matris\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if(i==j)
            {
                if(((-1)*m[i][j]) > 0)
                {
                    fprintf(fp,"q+%d ",((-1)*m[i][j]));
                }
                else
                {
                    fprintf(fp,"q%d ", ((-1)*m[i][j]));
                }
            }
            else
            {
                fprintf(fp,"%d  ", ((-1)*m[i][j]));

            }

        }
        fprintf(fp,"\n\n");

    }

    fprintf(fp,"--------------------------------------------\n");

int k;
    for(k=0; k<3; k++)
    {
        fprintf(fp,"%d icin \n\n",ozDegerler[k]);

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {

                if(i==j)
                {
                    fprintf(fp,"%d ",ozDegerler[k]+((-1)*m[i][j]));
                }
                else
                {
                    fprintf(fp,"%d  ", ((-1)*m[i][j]));
                }

            }

            if((i+1) == 2)
            {
                fprintf(fp,"\tX%d  = 0 ",(i+1));
            }
            else
            {
                fprintf(fp,"\tX%d  = %d ",(i+1) );
            }

            fprintf(fp,"\n");

        }
        fprintf(fp,"--------------------------------------------\n\n");

    }


    fclose(fp);
}
void nilpotent()
{
    int a;
    int i,j;
    printf("\nmatris boyutunu giriniz:");
    scanf("%d",&a);

    int rastgele[a][a];


    /** Matrisi -15 ve +15 de?erleri arasynda olu?turulmasy */
    for(i=0; i<a; i++)
    {
        for(j=0; j<a; j++)
        {
            rastgele[i][j]=randnum(-15,15);
            printf("[%d][%d].eleman:%d\n",i,j,rastgele[i][j]);
        }

    }

    printf("Matris :\n");
    for(i=0; i<a; i++)
    {
        for(j=0; j<a; j++)
        {
            printf("%d  ",rastgele[i][j]);
        }
        printf("\n");
    }



    /** Matrisin karesinin hesaplanmasy */
    int C[a][a];
    int k;

    for (i = 0; i < a; i++)
    {
        for (j = 0; j < a; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < a; k++)
                C[i][j] += rastgele[i][k]*rastgele[k][j];
        }
    }

    printf("matrislerin karesi: \n");
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < a; j++)
            printf("%d ", C[i][j]);
        printf("\n");

    }


    /* Kare matrisin nilpotent olup olmadygynyn kontrolu */
    int nilpotentMi=0;

    for (i = 0; i < a; i++)
    {
        for (j = 0; j < a; j++)
        {
            if(C[i][j]!=0)
            {
                nilpotentMi++;
            }
        }
    }



    /* Dosyaya yazma i?lemi */

    FILE*fp;

    fp=fopen("nilpotent.txt","w");
    fprintf(fp,"matrislerin karesi: \n\n");

    for (i = 0; i < a; i++)
    {
        for (j = 0; j < a; j++)
        {
            fprintf(fp,"%d  ", C[i][j]);
        }
        fprintf(fp,"\n");

    }

    if(nilpotentMi!=0)
    {
        printf("\nMatris nilpotent degildir.\n");
        fprintf(fp,"\nMatris nilpotent degildir.\n");
    }
    else
    {
        printf("\nMatris nilpotenttir.\n");
        fprintf(fp,"\nMatris nilpotentir.\n");
    }

    fclose(fp);

}
void cark()
{
    int N;
    int i;
    int carki_dondur;

    time_t t ;
    srand (( unsigned)time(&t)) ;

    printf("kac sayi ureteceksiniz : ");
    scanf("%d",&N);

    for(i=1; i<=N; i++)
    {

        carki_dondur=rand()%241;
        printf("%d\n",carki_dondur);
    }

    printf("son sayi:%d\n",carki_dondur);


    if(carki_dondur%4==1)
    {
        printf("Secilen Islem Ozdeger bul\n\n");

        int *x = ozdegerbul();
        free(x);
        x=NULL;

    }
    if(carki_dondur%4==2)
    {
        printf("Secilen Islem Schur Sinir degeri hesaplama\n\n");

        schur();
    }
    if(carki_dondur%4==3)
    {
        printf("Secilen Islem Ozvektor bul\n\n");

        ozvektorbul();
    }
    if(carki_dondur%4==0)
    {
        printf("Secilen Islem Nilpotent matris\n\n");

        nilpotent();
    }

}
int main()
{
    cark();

    return 0;
}
