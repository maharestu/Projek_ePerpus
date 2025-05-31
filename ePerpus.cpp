#include <iostream>
#include <queue>
#include <algorithm>
// #include <cctype>
//#include <string>

using namespace std;

const int MASA_PINJAM = 7;

struct buku
{
    string judul, penulis;
    int jumlahCopy;
    queue<int> antrianPinjam;
    buku* next;
};

buku* head = nullptr;

void tambahBuku(string judul, string penulis, int jumlahCopy);
void tampilkanKoleksiBuku();
void cariBuku();


int main(){
    int pilihan;
    string user;
    tambahBuku("Dunia Anna", "Jostein Gaarden", 2);
    tambahBuku("Dunia Sophie", "Jostein Gaarden", 3);
    tambahBuku("Pulang-Pergi", "Tere Liye", 4);
    tambahBuku("Si Anak Cahaya", "Tere Liye", 3);
    tambahBuku("Gagal Menjadi Manusia", "Osamu Dazai", 1);
    tambahBuku("Bumi", "Tere Liye", 1);
    tambahBuku("Bumi Manusia", "Pramoedya Ananta Toer", 1);
    tambahBuku("Bumi Manusia", "Pramoedya Ananta Toer", 1);
    tambahBuku("Ngarang Aja Lah", "Sobat Bumi", 1);

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
    // if (!temp)
    // {
    //     cout << "Belum ada buku. \n";
    //     return;
    // }
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