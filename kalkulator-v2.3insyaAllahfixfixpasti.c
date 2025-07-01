#include <stdio.h>
#include <math.h> // untuk fungsi matematika seperti pow, sqrt, sin, cos, tan dan deklarasi M_PI
#include <stdlib.h>
#include <string.h>

// =================================================================================
// DEKLARASI STRUCT
// =================================================================================

// Struct untuk data statistik tunggal
typedef struct {
    double* data;
    int n; // Jumlah data
} Stat_DataTunggal;

// Struct untuk kelas interval pada data kelompok
typedef struct {
    double batasBawah;
    double batasAtas;
    int frekuensi;
} KelasInterval;

// Struct untuk data statistik kelompok
typedef struct {
    KelasInterval* kelas;
    int jumlahKelas;
} Stat_DataKelompok;

// Struct untuk matriks
typedef struct {
    double** data;
    int baris;
    int kolom;
} Matriks;

struct Konversi {
    float nilai;
    char satuan[20];
};

// =================================================================================
// PROTOTYPE FUNGSI
// =================================================================================

// Fungsi utilitas & UI
int tampilkanMenu(const char* judul, const char* opsi[], int jumlahOpsi);
double inputAngka(const char* pesan);
void tungguEnter();
int compareDoubles(const void* a, const void* b);

//Fungsi clr screen
void clsr(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi Kalkulator Utama
void hitungSederhana();
void hitungLanjutan();
void hitungStatistika();
void hitungGeometri();
void hitungTrigonometri();
void hitungMatriks();
void konversiSatuan(); 

// Fungsi Konversi Satuan
void konversiPanjang();
void konversiMassa();
void konversiWaktu();
void konversiSuhu();
void konversiVolume();

// Fungsi Geometri
void geoLuas();
void geoVolume();
void geoKeliling();
void geoPermukaan();

// Fungsi Faktorial
long long faktorial_rekursif(int n);

// Fungsi Matriks (2x2)
Matriks* matriks_buat(int baris, int kolom);
void matriks_hapus(Matriks* m);
void matriks_isi(Matriks* m, const char* nama);
void matriks_tampilkan(const Matriks* m, const char* nama);
Matriks* matriks_tambah(const Matriks* A, const Matriks* B);
Matriks* matriks_kurang(const Matriks* A, const Matriks* B);
Matriks* matriks_kali(const Matriks* A, const Matriks* B);
Matriks* matriks_transpose(const Matriks* A);
double matriks_determinan(const Matriks* A);
Matriks* matriks_invers(const Matriks* A);

// Fungsi Statistik Data Tunggal
void statistikDataTunggal();
void inputDataTunggal(Stat_DataTunggal* dataSet);
void tampilkanDataTunggal(const Stat_DataTunggal* dataSet);
void editDataTunggal(Stat_DataTunggal* dataSet);
double rataRataTunggal(const Stat_DataTunggal* dataSet);
double medianTunggal(const Stat_DataTunggal* dataSet);
double modusTunggal(const Stat_DataTunggal* dataSet);
double variansiTunggal(const Stat_DataTunggal* dataSet);
double stdDeviasiTunggal(const Stat_DataTunggal* dataSet);
double rentangTunggal(const Stat_DataTunggal* dataSet);
double kuartilTunggal(const Stat_DataTunggal* dataSet, int Q);
double desilTunggal(const Stat_DataTunggal* dataSet, int D);
double persentilTunggal(const Stat_DataTunggal* dataSet, int P);


// Fungsi Statistik Data Kelompok
void statistikDataKelompok();
void inputDataKelompok(Stat_DataKelompok* dataSet);
void tampilkanDataKelompok(const Stat_DataKelompok* dataSet);
void editDataKelompok(Stat_DataKelompok* dataSet);
double rataRataKelompok(const Stat_DataKelompok* dataSet);
double medianKelompok(const Stat_DataKelompok* dataSet);
double modusKelompok(const Stat_DataKelompok* dataSet);
double rentangKelompok(const Stat_DataKelompok* dataSet);
double kuartilKelompok(const Stat_DataKelompok* dataSet, int Q);
double desilKelompok(const Stat_DataKelompok* dataSet, int D);
double persentilKelompok(const Stat_DataKelompok* dataSet, int P);
double variansiKelompok(const Stat_DataKelompok* dataSet);
double stdDeviasiKelompok(const Stat_DataKelompok* dataSet);


// =================================================================================
// FUNGSI MAIN
// =================================================================================

int main() {
    const char* menuUtama[] = {
        "Perhitungan Sederhana",
        "Perhitungan Lanjutan",
        "Perhitungan Statistika",
        "Perhitungan Geometri",
        "Perhitungan Matriks",
        "Perhitungan Trigonometri",
        "Konversi Satuan",
        "Keluar"
    };

    int jumlahOpsi = sizeof(menuUtama) / sizeof(menuUtama[0]);
    int pilihan;

    do {
        pilihan = tampilkanMenu("KALKULATOR ILMIAH", menuUtama, jumlahOpsi);
        switch (pilihan) {
            case 1: hitungSederhana(); break;
            case 2: hitungLanjutan(); break;
            case 3: hitungStatistika(); break;
            case 4: hitungGeometri(); break;
            case 5: hitungMatriks(); break;
            case 6: hitungTrigonometri(); break;
            case 7: konversiSatuan(); break;
            case 8: printf("\nTerima kasih telah menggunakan kalkulator ini!\n"); break;
            default: printf("Pilihan tidak valid.\n"); tungguEnter(); break;
        }
    } while (pilihan != 8);

    return 0;
}

// =================================================================================
// IMPLEMENTASI FUNGSI UTILITAS & UI
// =================================================================================

void tampilkanJudul(const char* judul) {
    printf("\n===========================================\n");
    printf("              %s\n", judul);
    printf("===========================================\n");
}

int tampilkanMenu(const char* judul, const char* opsi[], int jumlahOpsi) {
    clsr();
    int pilihan = 0;
    tampilkanJudul(judul);
    for (int i = 0; i < jumlahOpsi; i++) {
        printf("%d. %s\n", i + 1, opsi[i]);
    }
    printf("-------------------------------------------\n");
    printf("Masukkan Pilihan Anda: ");
    // Memastikan input adalah integer
    while (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid. Masukkan angka: ");
        while (getchar() != '\n'); // Membersihkan buffer input
    }
    while (getchar() != '\n'); 
    return pilihan;
}

double inputAngka(const char* pesan) {
    double angka;
    printf("%s", pesan);
    while (scanf("%lf", &angka) != 1) { //jika pengguna memasukkan input yang bukan angka maka akan false
        printf("Input tidak valid. Masukkan angka: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return angka;
}

void tungguEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}

// Fungsi pembanding untuk qsort
int compareDoubles(const void* a, const void* b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// =================================================================================
// IMPLEMENTASI FUNGSI KALKULATOR
// =================================================================================

void hitungSederhana() {
    const char* menuSederhana[] = {"Penjumlahan", "Pengurangan", "Perkalian", "Pembagian", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN SEDERHANA", menuSederhana, 5);
        double a, b, hasil;
        if (pilihan >= 1 && pilihan <= 4) {
            a = inputAngka("Masukkan angka pertama: ");
            b = inputAngka("Masukkan angka kedua: ");
        }
        switch (pilihan) {
            case 1: hasil = a + b; printf("%.2lf + %.2lf = %.2lf\n", a, b, hasil); break;
            case 2: hasil = a - b; printf("%.2lf - %.2lf = %.2lf\n", a, b, hasil); break;
            case 3: hasil = a * b; printf("%.2lf * %.2lf = %.2lf\n", a, b, hasil); break;
            case 4:
                if (b == 0) printf("Error: Pembagian dengan nol tidak terdefinisi.\n");
                else { hasil = a / b; printf("%.2lf / %.2lf = %.2lf\n", a, b, hasil); }
                break;
            case 5: return;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if (pilihan >= 1 && pilihan <= 4) tungguEnter();
    } while (pilihan != 5);
}

void hitungLanjutan() {
    const char* menuLanjutan[] = {"Pangkat", "Akar Pangkat n", "Faktorial", "Logaritma", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN LANJUTAN", menuLanjutan, 5);
        double a, b, hasil;
        switch (pilihan) {
            case 1:
                a = inputAngka("Masukkan basis: ");
                b = inputAngka("Masukkan pangkat: ");
                hasil = pow(a, b);
                printf("%.2lf ^ %.2lf = %.2lf\n", a, b, hasil);
                break;
            case 2:
                a = inputAngka("Masukkan angka: ");
                b = inputAngka("Masukkan akar pangkat: ");
                if (a < 0 && fmod(b, 2.0) == 0) printf("Error: Akar pangkat genap dari angka negatif tak terdefinisi dalam bil real.\n");
                else if (b < 0) printf("Error: Akar pangkat harus > 0.\n");
                else { hasil = pow(a, 1.0 / b); printf("Akar pangkat %.2lf dari %.2lf = %.2lf\n", b, a, hasil); }
                break;
            case 3:
                a = inputAngka("Masukkan angka (bilangan bulat non-negatif): ");
                if (a < 0 || fmod(a, 1) != 0) printf("Error: Faktorial hanya untuk bilangan bulat non-negatif.\n");
                else { hasil = (double)faktorial_rekursif((int)a); printf("%.0lf! = %.0lf\n", a, hasil); }
                break;
            case 4:
                a = inputAngka("Masukkan basis (log): ");
                b = inputAngka("Masukkan numerus: ");
                if (a <= 0 || a == 1 || b <= 0) printf("Error: Basis harus > 0 dan != 1, numerus harus > 0.\n");
                else { hasil = log(b) / log(a); printf("Logaritma basis %.2lf dari %.2lf = %.2lf\n", a, b, hasil); }
                break;
            case 5: return;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if (pilihan >= 1 && pilihan <= 4) tungguEnter();
    } while (pilihan != 5);
}

void hitungStatistika() {
    const char* menuStatistika[] = {"Statistik Data Tunggal", "Statistik Data Kelompok", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN STATISTIKA", menuStatistika, 3);
        switch (pilihan) {
            case 1: statistikDataTunggal(); break;
            case 2: statistikDataKelompok(); break;
            case 3: return;
            default: printf("Pilihan tidak valid.\n"); tungguEnter(); break;
        }
    } while (pilihan != 3);
}

void hitungGeometri() {
    const char* menuGeometri[] = {"Luas", "Volume", "Keliling", "Luas Permukaan", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN GEOMETRI", menuGeometri, 5);
        switch (pilihan) {
            case 1: geoLuas(); break;
            case 2: geoVolume(); break;
            case 3: geoKeliling(); break;
            case 4: geoPermukaan(); break;
            case 5: return;
            default: printf("Pilihan tidak valid.\n"); tungguEnter(); break;
        }
    } while (pilihan != 5);
}

void hitungTrigonometri() {
    const char* menuTrigonometri[] = {"Sinus", "Cosinus", "Tangen", "Cosecan", "Secan", "Cotangen", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN TRIGONOMETRI", menuTrigonometri, 7);
        double sudut, radian, hasil;
        if (pilihan >= 1 && pilihan <= 6) {
            sudut = inputAngka("Masukkan sudut dalam derajat: ");
            radian = sudut * M_PI / 180.0;
        }
        switch (pilihan) {
            case 1: hasil = sin(radian); printf("Hasil Sinus: %.4lf\n", hasil); break;
            case 2: hasil = cos(radian); printf("Hasil Cosinus: %.4lf\n", hasil); break;
            case 3: hasil = tan(radian); printf("Hasil Tangen: %.4lf\n", hasil); break;
            case 4:
                if(sin(radian)==0) printf("Error: Cosecan tidak terdefinisi.\n");
                else { hasil = 1 / sin(radian); printf("Hasil Cosecan: %.4lf\n", hasil); }
                break;
            case 5:
                if(cos(radian)==0) printf("Error: Secan tidak terdefinisi.\n");
                else { hasil = 1 / cos(radian); printf("Hasil Secan: %.4lf\n", hasil); }
                break;
            case 6:
                if(tan(radian)==0) printf("Error: Cotangen tidak terdefinisi.\n");
                else { hasil = 1 / tan(radian); printf("Hasil Cotangen: %.4lf\n", hasil); }
                break;
            case 7: return;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if (pilihan >= 1 && pilihan <= 6) tungguEnter();
    } while (pilihan != 7);
}

void konversiSatuan() {
    int pilih;
    do {
        printf("\n=== MENU KONVERSI SATUAN ===\n");
        printf("1. Panjang\n");
        printf("2. Massa/Berat\n");
        printf("3. Waktu\n");
        printf("4. Suhu\n");
        printf("5. Volume\n");
        printf("6. Keluar\n");
        printf("Pilih kategori: ");
        scanf("%d", &pilih);
        while (getchar() != '\n'); 

        switch(pilih) {
            case 1: konversiPanjang(); break;
            case 2: konversiMassa(); break;
            case 3: konversiWaktu(); break;
            case 4: konversiSuhu(); break;
            case 5: konversiVolume(); break;
            case 6: printf("Keluar dari konversi.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        } tungguEnter();
    } while (pilih != 6);
}

void konversiPanjang() {
    struct Konversi k;
    int pilih;

    do {
        printf("\n-- Konversi Panjang --\n");
        printf("1. Meter ke Kilometer\n");
        printf("2. Meter ke Centimeter\n");
        printf("3. Meter ke Inci\n");
        printf("4. Meter ke Kaki\n");
        printf("5. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &pilih);
        while (getchar() != '\n'); 

        if (pilih >= 1 && pilih <= 4) {
            printf("Masukkan nilai dalam meter: ");
            scanf("%f", &k.nilai);

            switch(pilih) {
                case 1: printf("= %.3f km\n", k.nilai / 1000); break;
                case 2: printf("= %.1f cm\n", k.nilai * 100); break;
                case 3: printf("= %.2f inci\n", k.nilai * 39.3701); break;
                case 4: printf("= %.2f kaki\n", k.nilai * 3.28084); break;
            }
        }tungguEnter();
    } while (pilih != 5);
}

void konversiMassa() {
    struct Konversi k;
    int pilih;

    do {
        printf("\n-- Konversi Massa --\n");
        printf("1. Kilogram ke Gram\n");
        printf("2. Kilogram ke Pon\n");
        printf("3. Kilogram ke Ons\n");
        printf("4. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &pilih);
        while (getchar() != '\n');

        if (pilih >= 1 && pilih <= 3) {
            printf("Masukkan nilai dalam kilogram: ");
            scanf("%f", &k.nilai);

            switch(pilih) {
                case 1: printf("= %.2f gram\n", k.nilai * 1000); break;
                case 2: printf("= %.2f pon\n", k.nilai * 2.20462); break;
                case 3: printf("= %.2f ons\n", k.nilai * 10); break;
            }
        } tungguEnter();
    } while (pilih != 4);
}

void konversiWaktu() {
    struct Konversi k;
    int pilih;

    do {
        printf("\n-- Konversi Waktu --\n");
        printf("1. Detik ke Menit\n");
        printf("2. Menit ke Jam\n");
        printf("3. Jam ke Hari\n");
        printf("4. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &pilih);
        while (getchar() != '\n');

        if (pilih >= 1 && pilih <= 3) {
            printf("Masukkan nilai: ");
            scanf("%f", &k.nilai);

            switch(pilih) {
                case 1: printf("= %.2f menit\n", k.nilai / 60); break;
                case 2: printf("= %.2f jam\n", k.nilai / 60); break;
                case 3: printf("= %.2f hari\n", k.nilai / 24); break;
            }
        } tungguEnter();
    } while (pilih != 4);
}

void konversiSuhu() {
    struct Konversi k;
    int pilih;

    do {
        printf("\n-- Konversi Suhu --\n");
        printf("1. Celcius ke Fahrenheit\n");
        printf("2. Celcius ke Kelvin\n");
        printf("3. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &pilih);
        while (getchar() != '\n');

        if (pilih == 1 || pilih == 2) {
            printf("Masukkan nilai dalam Celcius: ");
            scanf("%f", &k.nilai);

            if (pilih == 1)
                printf("= %.2f Fahrenheit\n", (k.nilai * 9/5) + 32);
            else
                printf("= %.2f Kelvin\n", k.nilai + 273.15);
        } tungguEnter();
    } while (pilih != 3);
}

void konversiVolume() {
    struct Konversi k;
    int pilih;

    do {
        printf("\n-- Konversi Volume --\n");
        printf("1. Liter ke Mililiter\n");
        printf("2. Liter ke Galon\n");
        printf("3. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &pilih);
        while (getchar() != '\n');

        if (pilih == 1 || pilih == 2) {
            printf("Masukkan nilai dalam liter: ");
            scanf("%f", &k.nilai);

            if (pilih == 1)
                printf("= %.2f ml\n", k.nilai * 1000);
            else
                printf("= %.2f galon\n", k.nilai / 3.785);
        } tungguEnter();
    } while (pilih != 3);
}

long long faktorial_rekursif(int n) {
    if (n > 20) return -1; // Menghindari overflow untuk long long
    if (n == 0 || n == 1) return 1;
    return n * faktorial_rekursif(n - 1);
}

// =================================================================================
// IMPLEMENTASI FUNGSI MATRIKS
// =================================================================================

void hitungMatriks() {
    const char* menuMatriks[] = {
        "Penjumlahan Matriks 2x2", "Pengurangan Matriks 2x2", "Perkalian Matriks 2x2",
        "Determinan Matriks 2x2", "Transpose Matriks 2x2", "Invers Matriks 2x2", "Kembali"
    };
    int pilihan;
    Matriks *A = NULL, *B = NULL, *C = NULL;

    do {
        pilihan = tampilkanMenu("PERHITUNGAN MATRIKS 2x2", menuMatriks, 7);
        if (pilihan >= 1 && pilihan <= 3) {
            A = matriks_buat(2, 2); B = matriks_buat(2, 2);
            matriks_isi(A, "Matriks A"); matriks_isi(B, "Matriks B");
        } else if (pilihan >= 4 && pilihan <= 6) {
            A = matriks_buat(2, 2); matriks_isi(A, "Matriks");
        }

        switch (pilihan) {
            case 1: C = matriks_tambah(A, B); matriks_tampilkan(C, "Hasil Penjumlahan (A + B)"); break;
            case 2: C = matriks_kurang(A, B); matriks_tampilkan(C, "Hasil Pengurangan (A - B)"); break;
            case 3: C = matriks_kali(A, B); matriks_tampilkan(C, "Hasil Perkalian (A * B)"); break;
            case 4: printf("Determinan: %.2lf\n", matriks_determinan(A)); break;
            case 5: C = matriks_transpose(A); matriks_tampilkan(C, "Hasil Transpose"); break;
            case 6: C = matriks_invers(A); if (C != NULL) matriks_tampilkan(C, "Hasil Invers"); break;
            case 7: break;
            default: printf("Pilihan tidak valid.\n"); break;
        }

        if (A) matriks_hapus(A); A = NULL;
        if (B) matriks_hapus(B); B = NULL;
        if (C) matriks_hapus(C); C = NULL;
        if (pilihan != 7) tungguEnter();
    } while (pilihan != 7);
}


Matriks* matriks_buat(int baris, int kolom) {
    Matriks* m = (Matriks*)malloc(sizeof(Matriks)); //malloc unutuk mengalokasikan memori untuk struct Matriks  
    m->baris = baris; m->kolom = kolom;
    m->data = (double**)malloc(baris * sizeof(double*)); //calloc untuk mengalokasikan memori untuk array of pointers   
    for (int i = 0; i < baris; i++) {
        m->data[i] = (double*)calloc(kolom, sizeof(double));
    }
    return m;
}

void matriks_hapus(Matriks* m) {
    if (m == NULL) return;
    for (int i = 0; i < m->baris; i++) free(m->data[i]); // free untuk membebaskan memori yang dialokasikan untuk setiap baris
    free(m->data); free(m);
}// pasangan malloc dan m dta, pasangan malloc dan m

void matriks_isi(Matriks* m, const char* nama) {
    printf("\nInput Elemen untuk %s:\n", nama);
    for (int i = 0; i < m->baris; i++) {
        for (int j = 0; j < m->kolom; j++) {
            char pesan[50];
            sprintf(pesan, "Elemen baris %d, kolom %d: ", i + 1, j + 1);
            m->data[i][j] = inputAngka(pesan);
        }
    }
}

void matriks_tampilkan(const Matriks* m, const char* nama) {
    printf("\n%s:\n", nama);
    for (int i = 0; i < m->baris; i++) {
        printf("| ");
        for (int j = 0; j < m->kolom; j++) printf("%8.2lf ", m->data[i][j]);
        printf("|\n");
    }
}


Matriks* matriks_tambah(const Matriks* A, const Matriks* B) {
    Matriks* C = matriks_buat(A->baris, A->kolom);
    for (int i = 0; i < A->baris; i++) for (int j = 0; j < A->kolom; j++) C->data[i][j] = A->data[i][j] + B->data[i][j];
    return C;
}

Matriks* matriks_kurang(const Matriks* A, const Matriks* B) {
    Matriks* C = matriks_buat(A->baris, A->kolom);
    for (int i = 0; i < A->baris; i++) for (int j = 0; j < A->kolom; j++) C->data[i][j] = A->data[i][j] - B->data[i][j];
    return C;
}

Matriks* matriks_kali(const Matriks* A, const Matriks* B) {
    Matriks* C = matriks_buat(A->baris, B->kolom);
    C->data[0][0] = A->data[0][0] * B->data[0][0] + A->data[0][1] * B->data[1][0];
    C->data[0][1] = A->data[0][0] * B->data[0][1] + A->data[0][1] * B->data[1][1];
    C->data[1][0] = A->data[1][0] * B->data[0][0] + A->data[1][1] * B->data[1][0];
    C->data[1][1] = A->data[1][0] * B->data[0][1] + A->data[1][1] * B->data[1][1];
    return C;
}

double matriks_determinan(const Matriks* A) {
    return A->data[0][0] * A->data[1][1] - A->data[0][1] * A->data[1][0];
}

Matriks* matriks_transpose(const Matriks* A) {
    Matriks* T = matriks_buat(A->kolom, A->baris);
    for (int i = 0; i < A->baris; i++) for (int j = 0; j < A->kolom; j++) T->data[j][i] = A->data[i][j];
    return T;
}

Matriks* matriks_invers(const Matriks* A) {
    double det = matriks_determinan(A);
    if (det == 0) { printf("Error: Matriks tidak memiliki invers (determinan = 0).\n"); return NULL; }
    Matriks* I = matriks_buat(2, 2);
    double det_inv = 1.0 / det;
    I->data[0][0] = A->data[1][1] * det_inv; 
    I->data[0][1] = -A->data[0][1] * det_inv;
    I->data[1][0] = -A->data[1][0] * det_inv; 
    I->data[1][1] = A->data[0][0] * det_inv;
    return I;
}

// =================================================================================
// IMPLEMENTASI FUNGSI STATISTIK DATA TUNGGAL
// =================================================================================

void statistikDataTunggal() {
    Stat_DataTunggal dataSet = {NULL, 0};
    const char* menuTunggal[] = {
        "Input/Ganti Data", "Tampilkan Data", "Edit Data", "Hitung Rata-rata (Mean)", "Hitung Median", 
        "Hitung Modus", "Hitung Rentang (Range)", "Hitung Variansi", "Hitung Standar Deviasi", 
        "Hitung Kuartil", "Hitung Desil", "Hitung Persentil", "Kembali"
    };
    int pilihan;

    do {
        pilihan = tampilkanMenu("STATISTIK DATA TUNGGAL", menuTunggal, 13);
        if (pilihan >= 4 && pilihan <= 12 && dataSet.n == 0) {
            printf("Data masih kosong. Silakan input data terlebih dahulu.\n");
            tungguEnter(); continue;
        }

        switch (pilihan) {
            case 1: inputDataTunggal(&dataSet); break;
            case 2: tampilkanDataTunggal(&dataSet); break;
            case 3: editDataTunggal(&dataSet); break;
            case 4: printf("Rata-rata (Mean): %.2f\n", rataRataTunggal(&dataSet)); break;
            case 5: printf("Median: %.2f\n", medianTunggal(&dataSet)); break;
            case 6: {
                double modus = modusTunggal(&dataSet);
                if (isnan(modus)) printf("Tidak ada modus yang unik.\n");
                else printf("Modus: %.2f\n", modus);
                break;
            }
            case 7: printf("Rentang (Range): %.2f\n", rentangTunggal(&dataSet)); break;
            case 8: printf("Variansi (Sampel): %.2f\n", variansiTunggal(&dataSet)); break;
            case 9: printf("Standar Deviasi (Sampel): %.2f\n", stdDeviasiTunggal(&dataSet)); break;
            case 10: {
                int q = (int)inputAngka("Masukkan Kuartil yang dicari (1, 2, atau 3): ");
                if (q >= 1 && q <= 3) printf("Kuartil %d: %.2f\n", q, kuartilTunggal(&dataSet, q));
                else printf("Pilihan kuartil tidak valid.\n");
                break;
            }
            case 11: {
                int d = (int)inputAngka("Masukkan Desil yang dicari (1-9): ");
                if (d >= 1 && d <= 9) printf("Desil %d: %.2f\n", d, desilTunggal(&dataSet, d));
                else printf("Pilihan desil tidak valid.\n");
                break;
            }
            case 12: {
                int p = (int)inputAngka("Masukkan Persentil yang dicari (1-99): ");
                if (p >= 1 && p <= 99) printf("Persentil %d: %.2f\n", p, persentilTunggal(&dataSet, p));
                else printf("Pilihan persentil tidak valid.\n");
                break;
            }
            case 13: break;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if (pilihan != 13) tungguEnter();
    } while (pilihan != 13);
    free(dataSet.data);
}

void inputDataTunggal(Stat_DataTunggal* dataSet) {
    if (dataSet->data != NULL) free(dataSet->data);
    dataSet->n = (int)inputAngka("Masukkan jumlah data: ");
    if (dataSet->n <= 0) { printf("Jumlah data harus positif.\n"); dataSet->n = 0; return; }
    dataSet->data = (double*)malloc(dataSet->n * sizeof(double));
    if(dataSet->data == NULL){ printf("Gagal alokasi memori.\n"); dataSet->n = 0; return; }

    printf("Masukkan %d data:\n", dataSet->n);
    for (int i = 0; i < dataSet->n; i++) {
        char pesan[30];
        sprintf(pesan, "Data ke-%d: ", i + 1);
        dataSet->data[i] = inputAngka(pesan);
    }
    printf("Data berhasil diinput.\n");
}

void tampilkanDataTunggal(const Stat_DataTunggal* dataSet) {
    if (dataSet->n == 0) { printf("Data kosong.\n"); return; }
    printf("\nData Saat Ini (diurutkan):\n");
    double* sortedData = (double*)malloc(dataSet->n * sizeof(double));
    memcpy(sortedData, dataSet->data, dataSet->n * sizeof(double));
    qsort(sortedData, dataSet->n, sizeof(double), compareDoubles);
    for (int i = 0; i < dataSet->n; i++) printf("%.2f  ", sortedData[i]);
    printf("\nJumlah Data: %d\n", dataSet->n);
    free(sortedData);
}

void editDataTunggal(Stat_DataTunggal* dataSet) {
    if (dataSet->n == 0) { printf("Data kosong. Tidak ada yang bisa diedit.\n"); return; }
    const char* menuEdit[] = {"Tambah Data", "Hapus Data", "Ubah Data", "Kembali"};
    int pilihan;
    do {
        tampilkanDataTunggal(dataSet);
        pilihan = tampilkanMenu("EDIT DATA TUNGGAL", menuEdit, 4);
        switch(pilihan){
            case 1: {
                double nilaiBaru = inputAngka("Masukkan data baru: ");
                dataSet->n++;
                double* temp = realloc(dataSet->data, dataSet->n * sizeof(double));
                if (temp == NULL) { printf("Gagal menambah data.\n"); dataSet->n--; return; }
                dataSet->data = temp; dataSet->data[dataSet->n - 1] = nilaiBaru;
                printf("Data berhasil ditambahkan.\n"); break;
            }
            case 2: {
                int indeks = (int)inputAngka("Masukkan nomor urut data (sesuai urutan input asli) yang ingin dihapus: ");
                if (indeks < 1 || indeks > dataSet->n) { printf("Nomor urut tidak valid.\n"); break; }
                for (int i = indeks - 1; i < dataSet->n - 1; i++) dataSet->data[i] = dataSet->data[i + 1];
                dataSet->n--;
                if (dataSet->n == 0) { free(dataSet->data); dataSet->data = NULL; }
                else {
                    double* temp = realloc(dataSet->data, dataSet->n * sizeof(double));
                    if (temp == NULL && dataSet->n > 0) { printf("Gagal re-alokasi memori.\n"); return; }
                    dataSet->data = temp;
                }
                printf("Data berhasil dihapus.\n"); break;
            }
            case 3: {
                int indeks = (int)inputAngka("Masukkan nomor urut data (sesuai urutan input asli) yang ingin diubah: ");
                if (indeks < 1 || indeks > dataSet->n) { printf("Nomor urut tidak valid.\n"); break; }
                double nilaiBaru = inputAngka("Masukkan nilai baru: ");
                dataSet->data[indeks - 1] = nilaiBaru;
                printf("Data berhasil diubah.\n"); break;
            }
            case 4: return;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if (pilihan != 4) tungguEnter();
    } while (pilihan != 4);
}

double rataRataTunggal(const Stat_DataTunggal* dataSet) {
    double sum = 0;
    for (int i = 0; i < dataSet->n; i++) sum += dataSet->data[i];
    return sum / dataSet->n;
}

double medianTunggal(const Stat_DataTunggal* dataSet) {
    return kuartilTunggal(dataSet, 2);
}

double modusTunggal(const Stat_DataTunggal* dataSet) {
    if (dataSet->n == 0) return NAN;
    double* sortedData = (double*)malloc(dataSet->n * sizeof(double));
    memcpy(sortedData, dataSet->data, dataSet->n * sizeof(double));
    qsort(sortedData, dataSet->n, sizeof(double), compareDoubles);

    double modus = sortedData[0];
    int maxCount = 1;
    int currentCount = 1;

    for (int i = 1; i < dataSet->n; i++) {
        if (sortedData[i] == sortedData[i - 1]) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                modus = sortedData[i-1];
            }
            currentCount = 1;
        }
    }
    if (currentCount > maxCount) {
        maxCount = currentCount;
        modus = sortedData[dataSet->n-1];
    }
    
    free(sortedData);
    if (maxCount <= 1) return NAN; // Tidak ada modus
    return modus;
}

double variansiTunggal(const Stat_DataTunggal* dataSet) {
    if (dataSet->n <= 1) return 0.0;
    double mean = rataRataTunggal(dataSet);
    double sumSqDiff = 0;
    for (int i = 0; i < dataSet->n; i++) sumSqDiff += pow(dataSet->data[i] - mean, 2);
    return sumSqDiff / (dataSet->n - 1);
}

double stdDeviasiTunggal(const Stat_DataTunggal* dataSet) {
    return sqrt(variansiTunggal(dataSet));
}

double rentangTunggal(const Stat_DataTunggal* dataSet){
    if (dataSet->n == 0) return 0.0;
    double minVal = dataSet->data[0], maxVal = dataSet->data[0];
    for(int i=1; i<dataSet->n; i++){
        if(dataSet->data[i] < minVal) minVal = dataSet->data[i];
        if(dataSet->data[i] > maxVal) maxVal = dataSet->data[i];
    }
    return maxVal - minVal;
}

// Fungsi umum untuk menghitung nilai persentil (termasuk kuartil dan desil)
double nilaiBerdasarkanPosisi(const double* sortedData, int n, double pos) {
    int k = (int)pos;
    double d = pos - k;
    double hasil;
    if (k == 0) return sortedData[0];
    if (k >= n) return sortedData[n-1];
    hasil = sortedData[k - 1] + d * (sortedData[k] - sortedData[k - 1]);
    return hasil;
}

double kuartilTunggal(const Stat_DataTunggal* dataSet, int Q) {
    double* sortedData = (double*)malloc(dataSet->n * sizeof(double));
    memcpy(sortedData, dataSet->data, dataSet->n * sizeof(double));
    qsort(sortedData, dataSet->n, sizeof(double), compareDoubles);
    double pos = (double)Q * (dataSet->n + 1) / 4.0;
    double hasil = nilaiBerdasarkanPosisi(sortedData, dataSet->n, pos);
    free(sortedData);
    return hasil;
}

double desilTunggal(const Stat_DataTunggal* dataSet, int D) {
    double* sortedData = (double*)malloc(dataSet->n * sizeof(double));
    memcpy(sortedData, dataSet->data, dataSet->n * sizeof(double));
    qsort(sortedData, dataSet->n, sizeof(double), compareDoubles);
    double pos = (double)D * (dataSet->n + 1) / 10.0;
    double hasil = nilaiBerdasarkanPosisi(sortedData, dataSet->n, pos);
    free(sortedData);
    return hasil;
}

double persentilTunggal(const Stat_DataTunggal* dataSet, int P) {
    double* sortedData = (double*)malloc(dataSet->n * sizeof(double));
    memcpy(sortedData, dataSet->data, dataSet->n * sizeof(double));
    qsort(sortedData, dataSet->n, sizeof(double), compareDoubles);
    double pos = (double)P * (dataSet->n + 1) / 100.0;
    double hasil = nilaiBerdasarkanPosisi(sortedData, dataSet->n, pos);
    free(sortedData);
    return hasil;
}


// =================================================================================
// IMPLEMENTASI FUNGSI STATISTIK DATA KELOMPOK
// =================================================================================

void statistikDataKelompok() {
    Stat_DataKelompok dataSet = {NULL, 0};
    const char* menuKelompok[] = {
        "Input/Ganti Data", "Tampilkan Data", "Edit Data", "Hitung Rata-rata (Mean)", "Hitung Median", 
        "Hitung Modus", "Hitung Rentang (Range)", "Hitung Variansi", "Hitung Standar Deviasi", 
        "Hitung Kuartil", "Hitung Desil", "Hitung Persentil", "Kembali"
    };
    int pilihan;
    
    do {
        pilihan = tampilkanMenu("STATISTIK DATA KELOMPOK", menuKelompok, 13);
        if (pilihan >= 4 && pilihan <= 12 && dataSet.jumlahKelas == 0) {
            printf("Data masih kosong. Silakan input data terlebih dahulu.\n");
            tungguEnter(); continue;
        }
        
        switch(pilihan) {
            case 1: inputDataKelompok(&dataSet); break;
            case 2: tampilkanDataKelompok(&dataSet); break;
            case 3: editDataKelompok(&dataSet); break;
            case 4: printf("Rata-rata Kelompok: %.2f\n", rataRataKelompok(&dataSet)); break;
            case 5: printf("Median Kelompok: %.2f\n", medianKelompok(&dataSet)); break;
            case 6: printf("Modus Kelompok: %.2f\n", modusKelompok(&dataSet)); break;
            case 7: printf("Rentang Kelompok: %.2f\n", rentangKelompok(&dataSet)); break;
            case 8: printf("Variansi Kelompok: %.2f\n", variansiKelompok(&dataSet)); break;
            case 9: printf("Standar Deviasi Kelompok: %.2f\n", stdDeviasiKelompok(&dataSet)); break;
            case 10: {
                int q = (int)inputAngka("Masukkan Kuartil yang dicari (1, 2, atau 3): ");
                if (q >= 1 && q <= 3) printf("Kuartil %d: %.2f\n", q, kuartilKelompok(&dataSet, q));
                else printf("Pilihan kuartil tidak valid.\n");
                break;
            }
            case 11: {
                int d = (int)inputAngka("Masukkan Desil yang dicari (1-9): ");
                if (d >= 1 && d <= 9) printf("Desil %d: %.2f\n", d, desilKelompok(&dataSet, d));
                else printf("Pilihan desil tidak valid.\n");
                break;
            }
            case 12: {
                int p = (int)inputAngka("Masukkan Persentil yang dicari (1-99): ");
                if (p >= 1 && p <= 99) printf("Persentil %d: %.2f\n", p, persentilKelompok(&dataSet, p));
                else printf("Pilihan persentil tidak valid.\n");
                break;
            }
            case 13: break;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if (pilihan != 13) tungguEnter();
    } while (pilihan != 13);
    
    if (dataSet.kelas) free(dataSet.kelas);
}

void inputDataKelompok(Stat_DataKelompok* dataSet) {
    if (dataSet->kelas != NULL) free(dataSet->kelas);
    dataSet->jumlahKelas = (int)inputAngka("Masukkan jumlah kelas interval: ");
    if (dataSet->jumlahKelas <= 0) { printf("Jumlah kelas harus positif.\n"); dataSet->jumlahKelas = 0; return; }
    dataSet->kelas = (KelasInterval*)malloc(dataSet->jumlahKelas * sizeof(KelasInterval));
    if (dataSet->kelas == NULL) { printf("Gagal alokasi memori.\n"); dataSet->jumlahKelas = 0; return; }

    for (int i = 0; i < dataSet->jumlahKelas; i++) {
        printf("\n--- Kelas ke-%d ---\n", i + 1);
        char pesan_bawah[50], pesan_atas[50], pesan_freq[50];
        sprintf(pesan_bawah, "Batas Bawah Kelas %d: ", i+1);
        sprintf(pesan_atas, "Batas Atas Kelas %d: ", i+1);
        sprintf(pesan_freq, "Frekuensi Kelas %d: ", i+1);
        dataSet->kelas[i].batasBawah = inputAngka(pesan_bawah);
        dataSet->kelas[i].batasAtas = inputAngka(pesan_atas);
        dataSet->kelas[i].frekuensi = (int)inputAngka(pesan_freq);
    }
    printf("Data berhasil diinput.\n");
}

void tampilkanDataKelompok(const Stat_DataKelompok* dataSet) {
     if (dataSet->jumlahKelas == 0) { printf("Data kelompok kosong.\n"); return; }
    printf("\nData Kelompok Saat Ini:\n");
    printf("-------------------------------------------\n");
    printf("| No. |    Interval Kelas    | Frekuensi |\n");
    printf("-------------------------------------------\n");
    int totalFreq = 0;
    for (int i = 0; i < dataSet->jumlahKelas; i++) {
        printf("| %-3d | %8.2f - %-8.2f | %-9d |\n", 
               i + 1, dataSet->kelas[i].batasBawah, dataSet->kelas[i].batasAtas, dataSet->kelas[i].frekuensi);
        totalFreq += dataSet->kelas[i].frekuensi;
    }
    printf("-------------------------------------------\n");
    printf("Jumlah Kelas: %d, Total Frekuensi: %d\n", dataSet->jumlahKelas, totalFreq);
}


void editDataKelompok(Stat_DataKelompok* dataSet) {
    if (dataSet->jumlahKelas == 0) { printf("Data kosong. Tidak ada yang bisa diedit.\n"); return; }
    tampilkanDataKelompok(dataSet);
    int no_kelas = (int)inputAngka("Masukkan nomor kelas yang ingin diubah (mulai dari 1): ");
    if (no_kelas < 1 || no_kelas > dataSet->jumlahKelas) { printf("Nomor kelas tidak valid.\n"); return; }
    int i = no_kelas - 1;
    printf("\nMengubah data untuk kelas %d (%.2f - %.2f)\n", no_kelas, dataSet->kelas[i].batasBawah, dataSet->kelas[i].batasAtas);

    const char* menuEdit[] = {"Ubah Batas Bawah", "Ubah Batas Atas", "Ubah Frekuensi", "Kembali"};
    int pilihan = tampilkanMenu("PILIH DATA YANG AKAN DIUBAH", menuEdit, 4);
    switch(pilihan) {
        case 1: dataSet->kelas[i].batasBawah = inputAngka("Masukkan batas bawah baru: "); break;
        case 2: dataSet->kelas[i].batasAtas = inputAngka("Masukkan batas atas baru: "); break;
        case 3: dataSet->kelas[i].frekuensi = (int)inputAngka("Masukkan frekuensi baru: "); break;
        case 4: return;
        default: printf("Pilihan tidak valid.\n"); break;
    }
    printf("Data kelas %d berhasil diubah.\n", no_kelas);
}

double rataRataKelompok(const Stat_DataKelompok* dataSet) {
    double total_fx = 0, total_f = 0;
    for (int i = 0; i < dataSet->jumlahKelas; i++) {
        double titikTengah = (dataSet->kelas[i].batasBawah + dataSet->kelas[i].batasAtas) / 2.0;
        total_fx += titikTengah * dataSet->kelas[i].frekuensi;
        total_f += dataSet->kelas[i].frekuensi;
    }
    return total_f == 0 ? 0 : total_fx / total_f;
}

// Fungsi umum untuk mencari nilai persentil/kuartil/desil kelompok
double nilaiPosisiKelompok(const Stat_DataKelompok* dataSet, double posisiData) {
    double f_kumulatif = 0, total_f = 0;
    for(int i=0; i<dataSet->jumlahKelas; i++) total_f += dataSet->kelas[i].frekuensi;
    
    int kelas_idx = 0;
    for (int i = 0; i < dataSet->jumlahKelas; i++) {
        f_kumulatif += dataSet->kelas[i].frekuensi;
        if (f_kumulatif >= posisiData) {
            kelas_idx = i;
            break;
        }
    }
    
    double f_sebelum = 0;
    if (kelas_idx > 0) {
        for (int i = 0; i < kelas_idx; i++) f_sebelum += dataSet->kelas[i].frekuensi;
    }

    double tepi_bawah = dataSet->kelas[kelas_idx].batasBawah - 0.5;
    double frekuensi_kelas = dataSet->kelas[kelas_idx].frekuensi;
    double panjang_kelas = dataSet->kelas[kelas_idx].batasAtas - dataSet->kelas[kelas_idx].batasBawah + 1;

    if (frekuensi_kelas == 0) return tepi_bawah; // Hindari pembagian dengan nol
    return tepi_bawah + ((posisiData - f_sebelum) / frekuensi_kelas) * panjang_kelas;
}


double medianKelompok(const Stat_DataKelompok* dataSet) {
    double total_f = 0;
    for (int i = 0; i < dataSet->jumlahKelas; i++) total_f += dataSet->kelas[i].frekuensi;
    return nilaiPosisiKelompok(dataSet, total_f / 2.0);
}

double kuartilKelompok(const Stat_DataKelompok* dataSet, int Q) {
    double total_f = 0;
    for (int i = 0; i < dataSet->jumlahKelas; i++) total_f += dataSet->kelas[i].frekuensi;
    return nilaiPosisiKelompok(dataSet, (double)Q * total_f / 4.0);
}

double desilKelompok(const Stat_DataKelompok* dataSet, int D) {
    double total_f = 0;
    for (int i = 0; i < dataSet->jumlahKelas; i++) total_f += dataSet->kelas[i].frekuensi;
    return nilaiPosisiKelompok(dataSet, (double)D * total_f / 10.0);
}

double persentilKelompok(const Stat_DataKelompok* dataSet, int P) {
    double total_f = 0;
    for (int i = 0; i < dataSet->jumlahKelas; i++) total_f += dataSet->kelas[i].frekuensi;
    return nilaiPosisiKelompok(dataSet, (double)P * total_f / 100.0);
}


double modusKelompok(const Stat_DataKelompok* dataSet) {
    int max_freq = 0, kelas_modus_idx = 0;
    for (int i = 0; i < dataSet->jumlahKelas; i++) {
        if (dataSet->kelas[i].frekuensi > max_freq) {
            max_freq = dataSet->kelas[i].frekuensi;
            kelas_modus_idx = i;
        }
    }
    
    double tepi_bawah = dataSet->kelas[kelas_modus_idx].batasBawah - 0.5;
    double d1 = (double)max_freq - (kelas_modus_idx > 0 ? dataSet->kelas[kelas_modus_idx - 1].frekuensi : 0);
    double d2 = (double)max_freq - (kelas_modus_idx < dataSet->jumlahKelas - 1 ? dataSet->kelas[kelas_modus_idx + 1].frekuensi : 0);
    double panjang_kelas = dataSet->kelas[kelas_modus_idx].batasAtas - dataSet->kelas[kelas_modus_idx].batasBawah + 1;

    if ((d1 + d2) == 0) return tepi_bawah; // Hindari pembagian nol
    return tepi_bawah + (d1 / (d1 + d2)) * panjang_kelas;
}

double rentangKelompok(const Stat_DataKelompok* dataSet) {
    if (dataSet->jumlahKelas == 0) return 0;
    return dataSet->kelas[dataSet->jumlahKelas - 1].batasAtas - dataSet->kelas[0].batasBawah;
}

double variansiKelompok(const Stat_DataKelompok* dataSet) {
    double mean = rataRataKelompok(dataSet);
    double total_f = 0;
    double sum_sq_diff = 0;
    for(int i=0; i<dataSet->jumlahKelas; i++) {
        double titikTengah = (dataSet->kelas[i].batasBawah + dataSet->kelas[i].batasAtas) / 2.0;
        sum_sq_diff += dataSet->kelas[i].frekuensi * pow(titikTengah - mean, 2);
        total_f += dataSet->kelas[i].frekuensi;
    }
    if (total_f <= 1) return 0;
    return sum_sq_diff / (total_f - 1); // Variansi sampel
}

double stdDeviasiKelompok(const Stat_DataKelompok* dataSet) {
    return sqrt(variansiKelompok(dataSet));
}

// =================================================================================
// IMPLEMENTASI FUNGSI GEOMETRI
// =================================================================================

void geoLuas() {
    const char* menuLuas[] = { "Luas Persegi", "Luas Persegi Panjang", "Luas Segitiga", "Luas Lingkaran", "Luas Jajar Genjang", "Luas Trapesium", "Luas Layang-layang", "Luas Belah Ketupat", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN LUAS", menuLuas, 9);
        double s1, s2, hasil;
        switch (pilihan) {
            case 1: s1 = inputAngka("Masukkan sisi: "); hasil = s1 * s1; printf("Luas Persegi: %.2lf\n", hasil); break;
            case 2: s1 = inputAngka("Masukkan panjang: "); s2 = inputAngka("Masukkan lebar: "); hasil = s1 * s2; printf("Luas Persegi Panjang: %.2lf\n", hasil); break;
            case 3: s1 = inputAngka("Masukkan alas: "); s2 = inputAngka("Masukkan tinggi: "); hasil = 0.5 * s1 * s2; printf("Luas Segitiga: %.2lf\n", hasil); break;
            case 4: s1 = inputAngka("Masukkan jari-jari: "); hasil = M_PI * s1 * s1; printf("Luas Lingkaran: %.2lf\n", hasil); break;
            case 5: s1 = inputAngka("Masukkan alas: "); s2 = inputAngka("Masukkan tinggi: "); hasil = s1 * s2; printf("Luas Jajar Genjang: %.2lf\n", hasil); break;
            case 6: s1 = inputAngka("Masukkan alas 1: "); s2 = inputAngka("Masukkan alas 2: "); double s3 = inputAngka("Masukkan tinggi: "); hasil = 0.5 * (s1 + s2) * s3; printf("Luas Trapesium: %.2lf\n", hasil); break;
            case 7: s1 = inputAngka("Masukkan diagonal 1: "); s2 = inputAngka("Masukkan diagonal 2: "); hasil = 0.5 * s1 * s2; printf("Luas Layang-layang: %.2lf\n", hasil); break;
            case 8: s1 = inputAngka("Masukkan diagonal 1: "); s2 = inputAngka("Masukkan diagonal 2: "); hasil = 0.5 * s1 * s2; printf("Luas Belah Ketupat: %.2lf\n", hasil); break;
            case 9: return;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if(pilihan >= 1 && pilihan <= 9) tungguEnter();
    } while (pilihan != 9);
}

void geoVolume() {
    const char* menuVolume[] = {"Volume Kubus", "Volume Balok", "Volume Tabung", "Volume Kerucut", "Volume Bola", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN VOLUME", menuVolume, 6);
        double s1, s2, s3, hasil;
        switch (pilihan) {
            case 1: s1 = inputAngka("Masukkan sisi: "); hasil = pow(s1, 3); printf("Volume Kubus: %.2lf\n", hasil); break;
            case 2: s1 = inputAngka("Masukkan panjang: "); s2 = inputAngka("Masukkan lebar: "); s3 = inputAngka("Masukkan tinggi: "); hasil = s1 * s2 * s3; printf("Volume Balok: %.2lf\n", hasil); break;
            case 3: s1 = inputAngka("Masukkan jari-jari: "); s2 = inputAngka("Masukkan tinggi: "); hasil = M_PI * pow(s1, 2) * s2; printf("Volume Tabung: %.2lf\n", hasil); break;
            case 4: s1 = inputAngka("Masukkan jari-jari: "); s2 = inputAngka("Masukkan tinggi: "); hasil = (1.0/3) * M_PI * pow(s1, 2) * s2; printf("Volume Kerucut: %.2lf\n", hasil); break;
            case 5: s1 = inputAngka("Masukkan jari-jari: "); hasil = (4.0/3) * M_PI * pow(s1, 3); printf("Volume Bola: %.2lf\n", hasil); break;
            case 6: return;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if(pilihan >= 1 && pilihan <= 6) tungguEnter();
    } while (pilihan != 6);
}

void geoKeliling() {
     const char* menuKeliling[] = {"Keliling Persegi", "Keliling Persegi Panjang", "Keliling Lingkaran", "Keliling Jajar Genjang", "Keliling Trapesium", "Keliling Layang-layang", "Keliling Belah Ketupat", "Keliling Segitiga", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN KELILING", menuKeliling, 9);
        double s1, s2, hasil;
        switch (pilihan) {
            case 1: s1 = inputAngka("Masukkan sisi: "); hasil = 4 * s1; printf("Keliling Persegi: %.2lf\n", hasil); break;
            case 2: s1 = inputAngka("Masukkan panjang: "); s2 = inputAngka("Masukkan lebar: "); hasil = 2 * (s1 + s2); printf("Keliling Persegi Panjang: %.2lf\n", hasil); break;
            case 3: s1 = inputAngka("Masukkan jari-jari: "); hasil = 2 * M_PI * s1; printf("Keliling Lingkaran: %.2lf\n", hasil); break;
            case 4: s1 = inputAngka("Masukkan sisi alas: "); s2 = inputAngka("Masukkan sisi miring: "); hasil = 2 * (s1 + s2); printf("Keliling Jajar Genjang: %.2lf\n", hasil); break;
            case 5: s1 = inputAngka("Masukkan sisi 1: "); s2 = inputAngka("Masukkan sisi 2: "); double s3 = inputAngka("Masukkan sisi 3: "); double s4 = inputAngka("Masukkan sisi 4: "); hasil = s1 + s2 + s3 + s4; printf("Keliling Trapesium: %.2lf\n", hasil); break;
            case 6: s1 = inputAngka("Masukkan sisi 1: "); s2 = inputAngka("Masukkan sisi 2: "); double s3_layang = inputAngka("Masukkan sisi 3: "); double s4_layang = inputAngka("Masukkan sisi 4: "); hasil = s1 + s2 + s3_layang + s4_layang; printf("Keliling Layang-layang: %.2lf\n", hasil); break;
            case 7: s1 = inputAngka("Masukkan sisi: "); hasil = 4 * s1; printf("Keliling Belah Ketupat: %.2lf\n", hasil); break;
            case 8: s1 = inputAngka("Masukkan sisi 1: "); s2 = inputAngka("Masukkan sisi 2: "); double s3_segitiga = inputAngka("Masukkan sisi 3: "); hasil = s1 + s2 + s3_segitiga; printf("Keliling Segitiga: %.2lf\n", hasil); break;
            case 9: return;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if(pilihan >= 1 && pilihan <= 9) tungguEnter();
    } while (pilihan != 9);
}

void geoPermukaan() {
    const char* menuPermukaan[] = {"Luas Permukaan Kubus", "Luas Permukaan Balok", "Luas Permukaan Tabung", "Luas Permukaan Kerucut", "Luas Permukaan Bola", "Kembali"};
    int pilihan;
    do {
        pilihan = tampilkanMenu("PERHITUNGAN LUAS PERMUKAAN", menuPermukaan, 6);
        double s1, s2, s3, hasil;
        switch (pilihan) {
            case 1: s1 = inputAngka("Masukkan sisi: "); hasil = 6 * pow(s1, 2); printf("Luas Permukaan Kubus: %.2lf\n", hasil); break;
            case 2: s1 = inputAngka("Masukkan panjang: "); s2 = inputAngka("Masukkan lebar: "); s3 = inputAngka("Masukkan tinggi: "); hasil = 2 * (s1 * s2 + s1 * s3 + s2 * s3); printf("Luas Permukaan Balok: %.2lf\n", hasil); break;
            case 3: s1 = inputAngka("Masukkan jari-jari: "); s2 = inputAngka("Masukkan tinggi: "); hasil = 2 * M_PI * s1 * (s1 + s2); printf("Luas Permukaan Tabung: %.2lf\n", hasil); break;
            case 4: s1 = inputAngka("Masukkan jari-jari: "); s2 = inputAngka("Masukkan tinggi: "); s3 = sqrt(pow(s1, 2)) + pow(s2, 2); hasil = M_PI * s1 * (s1 + s3); printf("Luas Permukaan Kerucut: %.2lf\n", hasil); break;
            case 5: s1 = inputAngka("Masukkan jari-jari: "); hasil = 4 * M_PI * pow(s1, 2); printf("Luas Permukaan Bola: %.2lf\n", hasil); break;
            case 6: return;
            default: printf("Pilihan tidak valid.\n"); break;
        }
        if(pilihan >= 1 && pilihan <= 6) tungguEnter();
    } while (pilihan != 6);
}