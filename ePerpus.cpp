#include <iostream>
#include <queue>
#include <algorithm>
#include <cctype>
#include <string>
#include <map>
#include <set>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const int MASA_PINJAM = 7;//hari
const int BATAS_WAKTU_UNDUH = 60; //detik

struct buku
{
    string judul, penulis;
    int jumlahCopy;
    queue<string> antrianPinjam;
    map<string, time_t> waktuUnduh;
    buku* next;
};

buku* head = nullptr;
map<string, set<string>> pinjamanUser;

void tambahBuku(string judul, string penulis, int jumlahCopy);
void tampilkanKoleksiBuku();
void cariBuku();
void pinjamBuku(string username);
void returnBuku(string username, string judulBuku);
buku* cariPtrBuku(const string& keyword);
void autoReturnBuku(string username, string judul);
void unduhBuku(string username);
void rakPinjam(string username);


int main(){
    int pilihan;
    string username;
    tambahBuku("Bumi", "Tere Liye", 1);
    tambahBuku("Bumi Manusia", "Pramoedya Ananta Toer", 1);
    tambahBuku("Dunia Anna", "Jostein Gaarden", 2);
    tambahBuku("Dunia Sophie", "Jostein Gaarden", 3);
    tambahBuku("Gagal Menjadi Manusia", "Osamu Dazai", 1);
    tambahBuku("Ngarang Aja Lah", "Sobat Bumi", 1);
    tambahBuku("Pulang-Pergi", "Tere Liye", 4);
    tambahBuku("Si Anak Cahaya", "Tere Liye", 3);
    
    cout << "Masukkan username Anda: ";
    getline(cin, username);
    do
    {
        cout << "\n========== Daftar Buku ==========\n";
        tampilkanKoleksiBuku();
        cout << "\n========== Menu ===========\n"
             << "1. Pinjam Buku\n"
             << "2. Cari Buku\n"
             << "3. Sort Buku\n"
             << "4. Rak Pinjam\n"
             << "5. Keluar\n"
             << "Pilihan: ";
             cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            pinjamBuku(username);
            break;
        case 2:
            cariBuku();
            break;
        case 3:
           
            break;
        case 4:
            rakPinjam(username);
            break;
        case 5:
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 5);
    

    return 0;
}

void tambahBuku(string judul, string penulis, int jumlahCopy){
    buku* baru = new buku{judul, penulis, jumlahCopy};
    baru -> next = nullptr;
    if (head == nullptr)
    {
        head = baru;
    }else
    {
        buku* temp = head;
        while (temp -> next != nullptr)
        {
            temp = temp -> next;
        }
        temp -> next = baru;
    }
}
void tampilkanKoleksiBuku(){
    buku* temp = head;
    while (temp != nullptr)
    {
        cout << "\nJudul: " << temp -> judul
        << "\nPenulis: " << temp -> penulis
        << "\nJumlah Copy: " << temp -> jumlahCopy
        << "\nAntrian: " << temp -> antrianPinjam.size() << "\n\n";
        temp = temp -> next;
    }
}
void cariBuku(){
    string keyword;
    cout << "Masukkan Keyword: ";
    cin.ignore(); getline(cin, keyword);
    
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
    
    buku* temp = head;
    bool found = false;
    
    while (temp != nullptr)
    {
        string judulLower = temp->judul;
        string penulisLower = temp->penulis;
        
        transform(judulLower.begin(), judulLower.end(), judulLower.begin(), ::tolower);
        transform(penulisLower.begin(), penulisLower.end(), penulisLower.begin(), ::tolower);
        
        if (judulLower.find(keyword) != string::npos || penulisLower.find(keyword) != string::npos)
        {
            cout<< "\nJudul: " << temp->judul
            << "\nPenulis: " << temp->penulis
            << "\nJumlah Copy: " << temp->jumlahCopy
            << "\nAntrian: " << temp->antrianPinjam.size() << "\n\n";
            found = true;
        }   
        temp = temp->next;
    }
    if (!found)
    {
        cout << "Tidak ditmukan buku yang cocok dengan keyword \""<< keyword << "\"\n";
    }
    
}
void pinjamBuku(string username){
    string keyword;
    cout << "Masukkan keyword buku yang ingin dipinjam: ";
    cin.ignore(); getline(cin, keyword); 
    
    buku* temp = cariPtrBuku(keyword);
    if (temp)
    {
        temp->antrianPinjam.push(username);
        int posisi = temp->antrianPinjam.size();
        int estimasiHari = 0;
        
        if (posisi <= temp->jumlahCopy)
        {
            estimasiHari = 0;
            pinjamanUser[username].insert(temp->judul);
            temp->waktuUnduh[username] = time(nullptr);
        }else
        {
            estimasiHari = ((posisi - temp->jumlahCopy) /temp->jumlahCopy +1) * MASA_PINJAM;
        }
        cout << "Berhasil mendaftar antiran" << endl;
        cout << "Posisi antrian: " << posisi << endl;
        cout << "Estimasi tunggu: " << estimasiHari << " hari." << endl; 
        if (estimasiHari = 0)
        {
            cout << "\n[!!] Jika buku tidak diunduh dalam rentang waktu " << BATAS_WAKTU_UNDUH/60 << " menit, buku otomatis dikembalikan [!!]" << endl;
        }
        
    }else
    {
        cout << "Buku tidak ditemukan" << endl;
    }
    
    
}
buku* cariPtrBuku(const string& keyword){
    buku* temp = head;
    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(),::tolower);
    
    while (temp != nullptr)
    {
        string judulLower = temp->judul;
        string penulisLower = temp->penulis;
        transform(judulLower.begin(), judulLower.end(), judulLower.begin(),::tolower);
        transform(penulisLower.begin(), penulisLower.end(), penulisLower.begin(),::tolower);
        
        if (judulLower.find(lowerKeyword) != string::npos || penulisLower.find(lowerKeyword) != string::npos)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
void returnBuku(string username, string judulBuku){
    buku* temp = head;
    while (temp != nullptr)
    {
        string judulLower = temp->judul;
        transform(judulLower.begin(), judulLower.end(), judulLower.begin(), ::tolower);
        if (judulLower == judulBuku)
        {
            if (!temp->antrianPinjam.empty() && temp->antrianPinjam.front() == username)
            {
                temp->antrianPinjam.pop();
                pinjamanUser[username].erase(judulBuku);
                temp->waktuUnduh.erase(username);
                cout << "Buku berhasil dikembalikan." << endl;
            }else
            {
                cout << "Kamu bukan peminjam aktif buku ini atau belum giliranmu " << endl;
            }
            return;
        }
        temp = temp->next;
    }
    cout << "Buku tidak ditemukan" << endl;
}
void autoReturnBuku(string username, string judul){
    this_thread::sleep_for(chrono::seconds(BATAS_WAKTU_UNDUH));
    buku* temp = head;
    while (temp)
    {
        if (temp -> judul == judul && temp->waktuUnduh.count(username))
        {
            time_t unduhTime = temp->waktuUnduh[username];
            if (difftime(time(nullptr), unduhTime) >= BATAS_WAKTU_UNDUH )
            {
                if (!temp->antrianPinjam.empty() && temp->antrianPinjam.front() == username)
                {
                    cout << "\n\n[!!] Buku \"" << judul << "\" otomatis dikembalikan [!!]" << endl;
                    temp->antrianPinjam.pop();
                    pinjamanUser[username].erase(judul);
                    temp->waktuUnduh.erase(username);
                }
            }
        }
    }
}
void unduhBuku(string username){
    for (buku* temp = head; temp != nullptr; temp = temp->next)
    {
        if (pinjamanUser[username].count(temp->judul))
        {
            temp->waktuUnduh[username] = time(nullptr);
            cout << "Buku \"" << temp->judul << "\" berhasil diunduh" << endl;
            return;
        }
    }
    cout << "Tidak ada buku untuk diunduh" << endl;
}
void rakPinjam(string username){
    int pilihan;
    do
    {
        cout << "\n========== Rak Pinjam ==========" << endl
             << "1. Buku yang Dipinjam" << endl
             << "2. Antrian Buku" << endl
             << "3. Return Buku" << endl
             << "4. Kembali ke Menu Utama" << endl
             << "Pilihan: ";
        cin >> pilihan; 
        switch (pilihan)
        {
        case 1:
            cout << "\n ========== Buku yang Dipinjam ==========" << endl;
            if (pinjamanUser[username].empty())
            {
                cout << "Tidak ada buku yang sedang dipinjam" << endl;
            }else
            {
                for (const string& judul : pinjamanUser[username])
                {
                    buku* temp = head;
                    while (temp && temp->judul != judul) temp = temp -> next;
                    if (temp)
                    {
                        time_t unduh = temp->waktuUnduh[username];
                        double sisa = BATAS_WAKTU_UNDUH - difftime(time(nullptr), unduh);
                        sisa = max(0.0, sisa);
                        cout << "\n\n[!!] Buku " << judul << "otomatis dikembalikan dalam " << int(sisa) << " detik [!!]" << endl;
                    }
                }
                cout << "Ingin unduh buku sekarang? (y/n): ";
                char p; cin >> p;
                if (p == 'y') unduhBuku(username);
            }
            break;
        case 2: 
            buku* temp = head;
            while (temp != nullptr)
            {
                int antrian = temp->antrianPinjam.size();
                if (antrian > 0)
                {
                    int estimasiHari = (antrian > temp->jumlahCopy) ? ((antrian - temp->jumlahCopy) / temp->jumlahCopy +1) * MASA_PINJAM : 0;
                    cout << "\nJudul: " << temp->judul 
                         << "\nJumlah Antrian: " << antrian
                         << "\nEstimasi waktu: " << estimasiHari << " hari" << endl << endl;
                }
                temp = temp->next;
            }
            break;
        case 3:
            cin.ignore();{ 
            string judul;
            cout << "Masukkan judul buku yang ingin dikembalikan: ";
            getline(cin, judul);
            transform(judul.begin(), judul.end(), judul.begin(), ::tolower);
            returnBuku(username, judul);}
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 4);
}