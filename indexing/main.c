// 210201113 ZEYNEP DUVARCI
#include <stdio.h>
#include <stdlib.h>

struct kayit
{
    int ogrno;
    int derskodu;
    int puan;
    int bosluk;
};
void MenuGoster();
void indeksDosyasiOlustur();
void kayitEkle();
void veriDosyasiniGoster();
void kayitBul();
void indeksDosyasiSil();
void indeksDosyasiGoster();
void kayitSil();
void kayitGuncelle();
int main()
{
    MenuGoster();
}
void MenuGoster()
{
    int secim;
    printf("\n\t\tMENU\t\t");
    printf("\n1- Kayit Ekle");
    printf("\n2- Kayit Bul");
    printf("\n3- Kayit Sil");
    printf("\n4- Kayit Guncelle");
    printf("\n5- Veri Dosyasini Goster");
    printf("\n6- Indeks Dosyasini Goster");
    printf("\n7- Indeks Dosyasi Olustur");
    printf("\n8- Indeks Dosyasi Sil");
    printf("\n Seciminizin numarasini giriniz : ");
    scanf("%d", &secim);

    switch (secim)
    {
    case 1:
        kayitEkle();
        break;
    case 2:
        kayitBul();
        break;
    case 3:
        kayitSil();
        break;
    case 4:
        kayitGuncelle();
        break;
    case 5:
        veriDosyasiniGoster();
        break;
    case 6:
        indeksDosyasiGoster();
        break;
    case 7:
        indeksDosyasiOlustur();
        int i;
        printf("Baska bir islem yapmak isterseniz 1 e basiniz : ");
        scanf("%d", &i);
        if (i == 1)
            MenuGoster();
        break;
    case 8:
        indeksDosyasiSil();
        break;
    default:
        printf("\n\t!!!Gecerli bir secim yapmadiniz lutfen tekrar secim yapiniz!!!");
        MenuGoster();
        break;
    }
}
void indeksDosyasiOlustur()
{
    struct kayit ogr;
    FILE *fptr;
    fptr = fopen("veri.bin", "rb");
    int count = 0;
    int j, a;
    int i = 0;

    while (fread(&ogr, sizeof(struct kayit), 1, fptr) != 0)
    {
        count++;
    }
    int *ptr;
    ptr = malloc(count * sizeof(int));

    int *ptr1;
    ptr1 = malloc(count * sizeof(int));

    rewind(fptr);

    while (fread(&ogr, sizeof(struct kayit), 1, fptr) != 0)
    {
        ptr[i] = ogr.ogrno;
        ptr1[i] = (ftell(fptr) - 16);
        i++;
    };

    for (i = 0; i < count; ++i)
    {
        for (j = i + 1; j < count; ++j)
        {
            if (ptr[i] > ptr[j])
            {
                a = ptr[i];
                ptr[i] = ptr[j];
                ptr[j] = a;

                a = ptr1[i];
                ptr1[i] = ptr1[j];
                ptr1[j] = a;
            }
        }
    }

    fclose(fptr);
    fptr = fopen("indeks.txt", "w");

    for (i = 0; i < count; i++)
        fprintf(fptr, "%d\t%x\n", ptr[i], ptr1[i]);

    fclose(fptr);
    free(ptr);
    free(ptr1);
}
void kayitEkle()
{
    struct kayit ogr;

    printf("Ogrencinin numarasini giriniz : ");
    scanf("%d", &ogr.ogrno);
    printf("Ogrencinin aldigi dersin kodunu giriniz : ");
    scanf("%d", &ogr.derskodu);
    printf("Ogrencinin bu dersten aldigi puani giriniz :");
    scanf("%d", &ogr.puan);
    ogr.bosluk = 0;

    FILE *fptr;
    fptr = fopen("veri.bin", "ab");
    fwrite(&ogr, sizeof(struct kayit), 1, fptr);
    fclose(fptr);
    indeksDosyasiOlustur();

    int i;
    printf("Baska bir islem yapmak isterseniz 1 e basiniz : ");
    scanf("%d", &i);

    if (i == 1)
        MenuGoster();
}
void veriDosyasiniGoster()
{

    struct kayit ogr;
    FILE *fptr;
    fptr = fopen("veri.bin", "rb");
    int i = 0;
    printf("\nOffset\tOgrenci numarasi\tDers kodu\tPuan\n");
    while (fread(&ogr, sizeof(struct kayit), 1, fptr) != 0)
    {
        printf("\n%x\t%d\t\t%d\t\t%d", ftell(fptr) - 16, ogr.ogrno, ogr.derskodu, ogr.puan);
    }
    fclose(fptr);

    printf("\nBaska bir islem yapmak isterseniz 1 e basiniz : ");
    scanf("%d", &i);

    if (i == 1)
        MenuGoster();
}
void kayitBul()
{
    int ogrnumarasi1;
    int ogrnumarasi2;
    int offset;
    FILE *fptr,*fptr1;
    int i=0;

    fptr = fopen("indeks.txt", "r");
    fptr1 = fopen("veri.bin","rb");
    rewind(fptr1);
    struct kayit ogr;

    printf("Kayitlari Bulunacak Ogrencinin Numarasini Giriniz :");
    scanf("%d", &ogrnumarasi1);
    printf("\nOgrenci Numarasi\tDers Kodu\tPuan");

    while (1)
    {
        fscanf(fptr, "%d\t%x", &ogrnumarasi2, &offset);

        if (feof(fptr) != 0)
            break;

        if(ogrnumarasi1==ogrnumarasi2)
        {
            while(i<=offset)
            {
                fread(&ogr, sizeof(struct kayit), 1, fptr1);
                i=i+16;
            }   
            

            printf("\n%d\t\t%d\t\t%d", ogr.ogrno, ogr.derskodu, ogr.puan);
            
        }
        i=0;
        rewind(fptr1);

        
        
        
    }

    
    
    fclose(fptr1);
    fclose(fptr);
    
    printf("\nBaska bir islem yapmak isterseniz 1 e basiniz : ");
    scanf("%d", &i);

    if (i == 1)
        MenuGoster();
}
void indeksDosyasiSil()
{
    int i;
    if (remove("indeks.txt") == 0)
    {
        printf("Indeks Dosyasi Silinmistir");
    }
    else
    {
        printf("Indeks Dosyasi Silinemedi");
    }

    printf("\nBaska bir islem yapmak isterseniz 1 e basiniz : ");
    scanf("%d", &i);

    if (i == 1)
        MenuGoster();
}
void indeksDosyasiGoster()
{
    FILE *fptr;
    fptr = fopen("indeks.txt", "r");
    int ogrnumarasi, offset, i;
    printf("\nOgrenci Numarasi\tOffset\n");

    while (1)
    {
        fscanf(fptr, "%d\t%x", &ogrnumarasi, &offset);
        if (feof(fptr) != 0)
            break;

        printf("\n%d\t%x", ogrnumarasi, offset);
    }
    fclose(fptr);

    printf("\nBaska bir islem yapmak isterseniz 1 e basiniz : ");
    scanf("%d", &i);

    if (i == 1)
        MenuGoster();
}
void kayitSil()
{
    int ogrnumarasi1;
    int ogrnumarasi2;
    int derskodu;
    int puan;
    int offset;

    printf("Kaydini silmek istediginiz ogrencinin numarasini giriniz :");
    scanf("%d", &ogrnumarasi1);
    printf("Ders kodunu giriniz :");
    scanf("%d", &derskodu);
    

    FILE *fptr;
    FILE *fptr1;
    fptr = fopen("indeks.txt", "r");
    struct kayit ogr;
    int count = 0, i = 0;

    while (1)
    {
        fscanf(fptr, "%d\t%x", &ogrnumarasi2, &offset);
        if (feof(fptr) != 0)
            break;
        if (ogrnumarasi2 == ogrnumarasi1)
        {
            count++;
        }
    }

    int *ptr;
    ptr = malloc(count * sizeof(int));
    rewind(fptr);

    while (1)
    {
        fscanf(fptr, "%d\t%x", &ogrnumarasi2, &offset);
        if (feof(fptr) != 0)
            break;

        if (ogrnumarasi2 == ogrnumarasi1)
        {
            ptr[i] = offset;
            i++;
        }
    }
    rewind(fptr);
    fptr = fopen("veri.bin", "rb");
    fptr1 = fopen("temp.bin", "wb");

    offset = 0;
    int j = 0;

    while (fread(&ogr, sizeof(struct kayit), 1, fptr) != 0)
    {
        if (offset == ptr[j])
        {
            if (ogr.ogrno == ogrnumarasi1 && ogr.derskodu != derskodu)
            {
                fwrite(&ogr, sizeof(struct kayit), 1, fptr1);
            }

            j++;
        }
        else
        {
            fwrite(&ogr, sizeof(struct kayit), 1, fptr1);
        }
        offset = offset + 16;
    }
    fclose(fptr);
    fclose(fptr1);
    remove("veri.bin");
    rename("temp.bin", "veri.bin");

    indeksDosyasiOlustur();

    printf("Baska bir islem yapmak isterseniz 1 e basiniz : ");
    scanf("%d", &i);

    if (i == 1)
        MenuGoster();
}
void kayitGuncelle()
{
    int ogrnumarasi1;
    int ogrnumarasi2;
    int derskodu;
    int puan;
    int offset;

    printf("Kaydini guncellemek istediginiz ogrencinin numarasini giriniz :");
    scanf("%d", &ogrnumarasi1);
    printf("Ders kodunu giriniz :");
    scanf("%d", &derskodu);
    printf("Guncel puanini giriniz: ");
    scanf("%d", &puan);

    FILE *fptr;
    FILE *fptr1;
    fptr = fopen("indeks.txt", "r");
    struct kayit ogr;
    int count = 0, i = 0;

    while (1)
    {
        fscanf(fptr, "%d\t%x", &ogrnumarasi2, &offset);
        if (feof(fptr) != 0)
            break;
        if (ogrnumarasi2 == ogrnumarasi1)
        {
            count++;
        }
    }

    int *ptr;
    ptr = malloc(count * sizeof(int));
    rewind(fptr);

    while (1)
    {
        fscanf(fptr, "%d\t%x", &ogrnumarasi2, &offset);
        if (feof(fptr) != 0)
            break;

        if (ogrnumarasi2 == ogrnumarasi1)
        {
            ptr[i] = offset;
            i++;
        }
    }
    rewind(fptr);
    fptr = fopen("veri.bin", "rb");
    fptr1 = fopen("temp.bin", "wb");

    offset = 0;
    int j = 0;

    while (fread(&ogr, sizeof(struct kayit), 1, fptr) != 0)
    {
        if (offset == ptr[j])
        {
            if (ogr.ogrno == ogrnumarasi1 && ogr.derskodu != derskodu)
            {
                fwrite(&ogr, sizeof(struct kayit), 1, fptr1);
            }
            else
            {
                fwrite(&ogrnumarasi1, sizeof(int), 1, fptr1);
                fwrite(&derskodu, sizeof(int), 1, fptr1);
                fwrite(&puan, sizeof(int), 1, fptr1);
                fwrite(&ogr.bosluk, sizeof(int), 1, fptr1);
            }
            j++;
        }
        else
        {
            fwrite(&ogr, sizeof(struct kayit), 1, fptr1);
        }
        offset = offset + 16;
    }
    fclose(fptr);
    fclose(fptr1);
    remove("veri.bin");
    rename("temp.bin", "veri.bin");
    indeksDosyasiOlustur();

    printf("Baska bir islem yapmak isterseniz 1 e basiniz : ");
    scanf("%d", &i);

    if (i == 1)
        MenuGoster();
}