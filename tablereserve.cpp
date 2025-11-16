#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

typedef vector<int> vecInt;
typedef vector<string> vecStr;

struct Table {
    int number;
    int capacity;
    bool reserved;
    string reservedBy;

    Table(int n=0, int c=0) {
        number = n;
        capacity = c;
        reserved = false;
        reservedBy = "None";
    }

    void show() {
        cout << "Table " << number << " (Capacity: " << capacity << ") - ";
        if (reserved) cout << "Reserved by " << reservedBy << endl;
        else cout << "Available" << endl;
    }
};

class Restaurant {
    typedef vector<Table> vecTable;
    vecTable tables;

 public:
    Restaurant() {
        ifstream fin;
        fin.open("reservations.txt");
        int n, c, r;
        string name;
        while(fin >> n >> c >> r) {
            fin.ignore();
            getline(fin, name);
            Table t(n, c);
            t.reserved = (r==1);
            t.reservedBy = name;
            tables.push_back(t);
        }
        fin.close();

        if (tables.empty()) {
            tables = { {1,2}, {2,4}, {3,4}, {4,6}, {5,8} };
        }
    }

    void showTables() {
        for (auto &t : tables) t.show();
    }

    void reserveTable(int num, string name) {
        ofstream fout;
        for (auto &t : tables) {
            if (t.number == num) {
                if (!t.reserved) {
                    t.reserved = true;
                    t.reservedBy = name;
                    cout << "Table " << num << " reserved by " << name << endl;
                } else {
                    cout << "Table " << num << " already reserved by " << t.reservedBy << endl;
                }

                // Update file
                fout.open("reservations.txt");
                for (auto &tt : tables)
                    fout << tt.number << " " << tt.capacity << " " << tt.reserved << " " << tt.reservedBy << endl;
                fout.close();
                return;
            }
        }
        cout << "Table not found!" << endl;
    }

    void cancelReservation(int num) {
        ofstream fout;
        for (auto &t : tables) {
            if (t.number == num) {
                if (t.reserved) {
                    cout << "Reservation cancelled for Table " << num << " (was by " << t.reservedBy << ")" << endl;
                    t.reserved = false;
                    t.reservedBy = "None";
                } else
                    {
                    cout << "Table " << num << " is not reserved." << endl;
                }

                fout.open("reservations.txt");
                for (auto &tt : tables)
                    fout << tt.number << " " << tt.capacity << " " << tt.reserved << " " << tt.reservedBy << endl;
                fout.close();
                return;
            }
        }
        cout << "Table not found!" << endl;
    }
};

int main() {
    Restaurant r;
    int choice, tnum;
    string name;

    cout << "=== Welcome to the Restaurant Reservation System ===" << endl;

    while(true) {
        cout << "\n1. Show all tables" << endl;
        cout << "2. Reserve a table" << endl;
        cout << "3. Cancel reservation" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: r.showTables(); break;
            case 2:
                cout << "Enter table number: "; cin >> tnum;
                cout << "Enter your name: "; cin >> name;
                r.reserveTable(tnum, name);
                break;
            case 3:
                cout << "Enter table number: "; cin >> tnum;
                r.cancelReservation(tnum);
                break;
            case 4:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

