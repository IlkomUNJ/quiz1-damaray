#include <iostream>
#include <vector>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"

using namespace std;

vector<Buyer> buyers;
vector<seller> sellers;
vector<BankCustomer> customers;

void registerUser() {
    int id = buyers.size() + 1;
    string name;
    double initialDeposit;

    cout << "=== Register ===\n";
    cout << "Masukkan nama (Jangan menggunakan spasi): ";
    cin >> name;
    cout << "Setor awal: ";
    cin >> initialDeposit;

    BankCustomer cust(id, name, initialDeposit);
    customers.push_back(cust);

    Buyer b(id, name, customers.back());
    buyers.push_back(b);

    cout << "Akun Buyer berhasil dibuat dengan ID: " << id << endl;
}

Buyer* loginUser() {
    int id;
    cout << "=== Login ===\n";
    cout << "Masukkan ID akun (Jangan menggunakan spasi) : ";
    cin >> id;

    for (auto &b : buyers) {
        if (b.getId() == id) {
            cout << "Login berhasil. Halo, " << b.getName() << endl;
            return &b;
        }
    }
    cout << "Akun tidak ditemukan.\n";
    return nullptr;
}

void buyerMenu(Buyer* b) {
    int choice;
    do {
        cout << "\n=== Buyer Menu ===\n";
        cout << "1. Cek Akun Bank\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Upgrade jadi Seller\n";
        cout << "5. Logout\n";
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == 1) {
            b->getAccount().printInfo();
        } else if (choice == 2) {
            double amt; cout << "Jumlah: "; cin >> amt;
            b->getAccount().addBalance(amt);
        } else if (choice == 3) {
            double amt; cout << "Jumlah: "; cin >> amt;
            b->getAccount().withdrawBalance(amt);
        } else if (choice == 4) {
            int sid = sellers.size() + 1;
            string storeName;
            cout << "Masukkan nama toko (Jangan menggunakan spasi): ";
            cin >> storeName;
            seller s(*b, sid, storeName);
            sellers.push_back(s);
            cout << "Akun Seller berhasil dibuat!\n";
        }
    } while (choice != 5);
}

int main() {
    int choice;
    do {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            Buyer* b = loginUser();
            if (b) buyerMenu(b);
        }
    } while (choice != 3);

    cout << "Exiting program..." << endl;
    return 0;
}
