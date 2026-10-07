#include <pthread.h>
#include <iostream>
#include <string>
#include <algorithm>


using namespace std;


// ---------- DATA BERSAMA ----------
int jumlah_selesai = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


// Dipanggil tiap thread setelah selesai kerja
void lapor_selesai(const string& pesan) {
   pthread_mutex_lock(&mtx);
   jumlah_selesai++;
   cout << pesan << endl;
   pthread_mutex_unlock(&mtx);
}


// ---------- THREAD 1: jumlahkan angka 1 sampai 100 ----------
void* tugas_jumlah(void* arg) {
   int total = 0;
   for (int i = 1; i <= 100; i++) total += i;
   lapor_selesai("Thread 1: jumlah 1..100 = " + to_string(total));
   return NULL;
}


// ------- THREAD 2: hitung bilangan prima dari 1 sampai 50 ------
void* tugas_prima(void* arg) {
   int banyak_prima = 0;
   for (int n = 2; n <= 50; n++) {
       bool prima = true;
       for (int d = 2; d < n; d++) {
           if (n % d == 0) { prima = false; break; }
       }
       if (prima) banyak_prima++;
   }
   lapor_selesai("Thread 2: ada " + to_string(banyak_prima) + " bilangan prima dari 1..50");
   return NULL;
}


// ---------- THREAD 3: balik sebuah teks ----------
void* tugas_balik_teks(void* arg) {
   string teks = "belajar pthread";
   reverse(teks.begin(), teks.end());
   lapor_selesai("Thread 3: teks dibalik = " + teks);
   return NULL;
}


// ---------- MAIN ----------
int main() {
   pthread_t t1, t2, t3;


   pthread_create(&t1, NULL, tugas_jumlah, NULL);
   pthread_create(&t2, NULL, tugas_prima, NULL);
   pthread_create(&t3, NULL, tugas_balik_teks, NULL);


   pthread_join(t1, NULL);
   pthread_join(t2, NULL);
   pthread_join(t3, NULL);


   cout << "Semua selesai. jumlah_selesai = " << jumlah_selesai << endl;
       return 0;
}
