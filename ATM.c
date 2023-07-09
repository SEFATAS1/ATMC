#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char isim[50];
    int hesapNo;
    double bakiye;
} Kullanici;

Kullanici *kullanicilar;
int toplamKullanici = 0;

const char *KULLANICI_DOSYASI = "kullanicilar.txt";

void menuGoster();
void kullaniciKayit();
void kullaniciGiris();
void kullaniciHesapBilgisi();
void paraYatir();
void paraCek();
void dosyayaKaydet();
void dosyadanYukle();
void cikis();

int main() {
    dosyadanYukle();

    int secim;

    do {
        menuGoster();

        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                kullaniciKayit();
                break;
            case 2:
                kullaniciGiris();
                break;
            case 3:
                kullaniciHesapBilgisi();
                break;
            case 4:
                paraYatir();
                break;
            case 5:
                paraCek();
                break;
            case 6:
                dosyayaKaydet();
                break;
            case 7:
                cikis();
                break;
            default:
                printf("Gecersiz secim. Lutfen tekrar deneyin.\n");
                break;
        }
    } while (secim != 7);

    return 0;
}

void menuGoster() {
    printf("\n--- Banka Hesap Yonetimi Sistemi ---\n");
    printf("1. Yeni Hesap Olustur\n");
    printf("2. Hesaba Giris Yap\n");
    printf("3. Hesap Bilgilerini Goster\n");
    printf("4. Para Yatir\n");
    printf("5. Para Cek\n");
    printf("6. Verileri Kaydet\n");
    printf("7. Cikis\n");
}

void kullaniciKayit() {
    toplamKullanici++;
    kullanicilar = (Kullanici *) realloc(kullanicilar, toplamKullanici * sizeof(Kullanici));

    Kullanici *kullanici = &kullanicilar[toplamKullanici - 1];

    printf("--- Yeni Hesap Olustur ---\n");

    printf("Isim: ");
    scanf("%s", kullanici->isim);

    printf("Hesap No: ");
    scanf("%d", &(kullanici->hesapNo));

    printf("Baslangic Bakiye: ");
    scanf("%lf", &(kullanici->bakiye));

    printf("Hesap olusturuldu!\n");
}

void kullaniciGiris() {
    int hesapNo;
    printf("--- Hesaba Giris Yap ---\n");
    printf("Hesap No: ");
    scanf("%d", &hesapNo);

    int i;
    for (i = 0; i < toplamKullanici; i++) {
        if (kullanicilar[i].hesapNo == hesapNo) {
            printf("Giris Basarili. Hosgeldiniz, %s!\n", kullanicilar[i].isim);
            return;
        }
    }

    printf("Hesap bulunamadi. Lutfen tekrar deneyin.\n");
}

void kullaniciHesapBilgisi() {
    int hesapNo;
    printf("--- Hesap Bilgilerini Goster ---\n");
    printf("Hesap No: ");
    scanf("%d", &hesapNo);

    int i;
    for (i = 0; i < toplamKullanici; i++) {
        if (kullanicilar[i].hesapNo == hesapNo) {
            printf("--- Hesap Bilgileri ---\n");
            printf("Isim: %s\n", kullanicilar[i].isim);
            printf("Hesap No: %d\n", kullanicilar[i].hesapNo);
            printf("Bakiye: %.2lf\n", kullanicilar[i].bakiye);
            return;
        }
    }

    printf("Hesap bulunamadi. Lutfen tekrar deneyin.\n");
}

void paraYatir() {
    int hesapNo;
    double miktar;

    printf("--- Para Yatir ---\n");
    printf("Hesap No: ");
    scanf("%d", &hesapNo);

    int i;
    for (i = 0; i < toplamKullanici; i++) {
        if (kullanicilar[i].hesapNo == hesapNo) {
            printf("Yatirilacak Miktar: ");
            scanf("%lf", &miktar);

            kullanicilar[i].bakiye += miktar;

            printf("Para yatirildi. Guncel Bakiye: %.2lf\n", kullanicilar[i].bakiye);
            return;
        }
    }

    printf("Hesap bulunamadi. Lutfen tekrar deneyin.\n");
}

void paraCek() {
    int hesapNo;
    double miktar;

    printf("--- Para Cek ---\n");
    printf("Hesap No: ");
    scanf("%d", &hesapNo);

    int i;
    for (i = 0; i < toplamKullanici; i++) {
        if (kullanicilar[i].hesapNo == hesapNo) {
            printf("Cekilecek Miktar: ");
            scanf("%lf", &miktar);


            if (miktar > kullanicilar[i].bakiye) {
                printf("Yetersiz bakiye. Islem iptal edildi.\n");
                return;
            }

            kullanicilar[i].bakiye -= miktar;

            printf("Para cekildi. Guncel Bakiye: %.2lf\n", kullanicilar[i].bakiye);
            return;
        }
    }

    printf("Hesap bulunamadi. Lutfen tekrar deneyin.\n");
}

void dosyayaKaydet() {
    FILE *dosya = fopen(KULLANICI_DOSYASI, "w");
    if (dosya == NULL) {
        printf("Dosya olusturulamadi!\n");
        return;
    }

    int i;
    for (i = 0; i < toplamKullanici; i++) {
        fprintf(dosya, "%s %d %.2lf\n", kullanicilar[i].isim, kullanicilar[i].hesapNo, kullanicilar[i].bakiye);
    }

    fclose(dosya);

    printf("Veriler dosyaya kaydedildi.\n");
}

void dosyadanYukle() {
    FILE *dosya = fopen(KULLANICI_DOSYASI, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    Kullanici kullanici;
    while (fscanf(dosya, "%s %d %lf", kullanici.isim, &(kullanici.hesapNo), &(kullanici.bakiye)) != EOF) {
        toplamKullanici++;
        kullanicilar = (Kullanici *) realloc(kullanicilar, toplamKullanici * sizeof(Kullanici));
        kullanicilar[toplamKullanici - 1] = kullanici;
    }

    fclose(dosya);

    printf("Veriler dosyadan yuklendi.\n");
}

void cikis() {
    dosyayaKaydet();
    printf("Programdan cikiliyor...\n");
    exit(0);
}
