#include <iostream>
#include <queue>
#include <algorithm>
#include <cctype>
#include <string>
#include <map>
#include <set>
#include <ctime>

using namespace std;

const int MASA_PINJAM = 7;

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
void pinjamBuku(string user);
buku* cariPtrBuku(const string& keyword);


int main(){
    int pilihan;
    string user;
    tambahBuku("Bumi", "Tere Liye", 1);
    tambahBuku("Bumi Manusia", "Pramoedya Ananta Toer", 1);
    tambahBuku("Dunia Anna", "Jostein Gaarden", 2);
    tambahBuku("Dunia Sophie", "Jostein Gaarden", 3);
    tambahBuku("Gagal Menjadi Manusia", "Osamu Dazai", 1);
    tambahBuku("Ngarang Aja Lah", "Sobat Bumi", 1);
    tambahBuku("Pulang-Pergi", "Tere Liye", 4);
    tambahBuku("Si Anak Cahaya", "Tere Liye", 3);
    
    //tampilkanKoleksiBuku();
    cariBuku();
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

void pinjamBuku(string user){
    string keyword;
    cout << "Masukkan keyword buku yang ingin dipinjam: ";
    cin.ignore(); getline(cin, keyword); 

    buku* temp = cariPtrBuku(keyword);
    if (temp)
    {
        temp->antrianPinjam.push(user);
        int posisi = temp->antrianPinjam.size();
        int estimasiHari = 0;

        if (posisi <= temp->jumlahCopy)
        {
            estimasiHari = 0;
            pinjamanUser[user].insert(temp->judul);
            temp->waktuUnduh[user] = time(nullptr);
        }else
        {
            estimasiHari = ((posisi - temp->jumlahCopy) /temp->jumlahCopy +1) * MASA_PINJAM;
        }
        cout << "Berhasil mendaftar antiran" << endl;
        cout << "Posisi antrian: " << posisi << endl;
        cout << "Estimasi tunggu: " << estimasiHari << " hari." << endl; 
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