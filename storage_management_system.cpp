#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

#define FILE_NAME "the-file.txt"

using namespace std;

class Item {
// private:
//     char itemName[20];
//     double itemPrice, itemQuantity, itemsSold;
public:
    char itemName[20];
    double itemPrice, itemQuantity, itemsSold;

    void readItem() {
        cout << endl << "Informacija par produktu:" << endl;
        cout << "Nosaukums: ";
        cin.getline(itemName, 20);
        cout << "Cena: ";
        cin >> itemPrice;
        cout << "Pieejamais skaits: ";
        cin >> itemQuantity;
        cout << "Pardotais skaits: ";
        cin >> itemsSold;
    }
    void displayItem() {
        cout << left << setw(15) << itemName
             << left << setw(15) << itemPrice
             << left << setw(15) << itemQuantity
             << left << setw(15) << itemsSold << endl;
    }
    char *getItemName() { return itemName; }
};

int writeToFile(Item item, string filename) {
    item.readItem();
    fstream file;
    file.open(filename, ios::out|ios::binary|ios::app);
    if (!file){
        cout << "Kluda rakstot faila" << endl;
        return -1;
    }
    file.write((char*)&item,sizeof(item));
    file.close();
    cout << "Saglabats faila" << endl;
    return 0;
}

int readFromFile(string filename) {
    Item item;
    fstream file;
    file.open(filename,ios::in|ios::binary);
    if (!file){
        cout << "Kluda atverot failu" << endl;
        return -1;
    }
    if (file.read((char*)&item,sizeof(item))) {
        cout << endl
             << left << setw(15) << "Nosaukums"
             << left << setw(15) << "Cena"
             << left << setw(15) << "Pieejams"
             << left << setw(15) << "Pardots" << endl;
        while(!file.eof()) {
            item.displayItem();
            file.read((char*)&item,sizeof(item));
        }
    }
    else {
        cout << "Kluda nolasot no faila" << endl;
        return -1;
    }
    file.close();
    return 0;
}

int sellProduct(string file_name);
int searchProduct(string file_name);

int main() {
    Item item;
    int menuItem;
    cout << "----------NOLIKTAVA----------" << endl;
    cout << "0: Beigt darbibu" << endl;
    cout << "1: Pievienot produktu" << endl;
    cout << "2: Paradit visus produktus" << endl;
    cout << "3: Pardot produktu" << endl;
    cout << "4: Meklet produktu" << endl;
    while (true){
        cout << endl << "Izvele: ";
        cin >> menuItem;
        cin.clear();
        cin.ignore(1000, '\n');
        switch(menuItem) {
        case 0:
            return 0;
        case 1:
            cin.ignore();
            writeToFile(item, FILE_NAME);
            break;
        case 2:
            readFromFile(FILE_NAME);
            break;
        case 3:
            sellProduct(FILE_NAME);
            break;
        case 4:
            searchProduct(FILE_NAME);
            break;
        default:
            cout << "\nKluda! Nepareiza izvelne!" << endl;
            return 0;
        }
    }
    return 0;
}

int sellProduct(string fileName){
    Item product;
    Item soldProduct;
    char soldName[20];
    double quantity;
    double sold;
    fstream fileObj(fileName, ios::in | ios::out | ios::binary);
    
    cout << "Kuru produktu pardod?" << endl;
    cin >> soldName;
    cin.clear();
    cin.ignore(1000, '\n');

    fileObj.open(fileName);
    while (true){
        fileObj.read((char*)&product, sizeof(product));
        if (!strcmp(soldName, product.itemName)){
            
            return 0;
        }
        else if (fileObj.eof()){
            cout << "Kluda: produkta ievade!" << endl;
            return 0;
        }
    }

    strcpy(soldProduct.itemName, product.itemName);
    soldProduct.itemQuantity = product.itemQuantity - (double)1;
    soldProduct.itemsSold = product.itemsSold + (double)1;

    fileObj.write((char*)&soldProduct, sizeof(soldProduct));
    
    return 0;
}

int searchProduct(string fileName){
    Item product;
    ifstream file;
    string productName;

    cout << "Meklet prouktu: ";
    getline(cin, productName);

    file.open(fileName,ios::in);
    if (!file){
        cout << "Kluda atverot failu" << endl;
        return -1;
    }
    if (file.read((char*)&product, sizeof(product))){
        while (!file.eof()){
            if (product.getItemName() == productName){
                cout << endl
                     << left << setw(15) << "Nosaukums"
                     << left << setw(15) << "Cena"
                     << left << setw(15) << "Pieejams"
                     << left << setw(15) << "Pardots" << endl;
                product.displayItem();
                break;
            }
            file.read((char*)&product, sizeof(product));
        }
    }
    else {
        cout << "Kluda nolasot no faila" << endl;
        return -1;
    }
    file.close();
    cout << endl;
    return 0;
}
