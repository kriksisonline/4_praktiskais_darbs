#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <vector>

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

int sellProduct(string fileName, string productName);
int searchProduct(string fileName, string productName);

int main() {
    Item item;
    string input;
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
            cout << "Kuru produktu pardod?" << endl;
            cin >> input;
            sellProduct(FILE_NAME, input);
            break;
        case 4:
            cout << "Meklet prouktu: ";
            cin >> input;
            searchProduct(FILE_NAME, input);
            break;
        default:
            cout << "\nKluda! Nepareiza izvelne!" << endl;
            return 0;
        }
    }
    return 0;
}

int sellProduct(string fileName, string productName){
    Item product;
    Item soldProduct;
    bool go = true;
    vector<Item> fileData(10);
    double quantity;
    double sold;
    int productInteger = 0;
    int soldProductInteger = 0;
    int productQuantityInteger = 0;

    ifstream fileObj_in(fileName, ios::in | ios::binary); //ieseivo vektora all data info 
    if (!fileObj_in.is_open()){
    cout << "Kluda atverot failu" << endl;
    return -1;
    }
    while (go){    
        fileObj_in.read((char *)&product, sizeof(product));
        fileData[productInteger] = product;
        productInteger++;
        if (fileObj_in.eof()){
            go = false;
        }
    }
    productQuantityInteger = productInteger;
    fileObj_in.close();

    productInteger = 0;
    go = true;

    fileObj_in.open(fileName, ios::in | ios::binary); //atrod pardoto produktu
    if (!fileObj_in){
        cout << "Kluda atverot failu" << endl;
        return -1;
    }
    while (go){
        fileObj_in.read((char*)&product, sizeof(product)); //izlabo pardota produkta informaciju
        if (!strcmp(productName.c_str(), product.itemName)){
            strcpy(soldProduct.itemName, product.itemName);
            soldProduct.itemPrice = product.itemPrice;
            soldProduct.itemQuantity = product.itemQuantity - (double)1;
            soldProduct.itemsSold = product.itemsSold + (double)1;   
            fileData[productInteger] = soldProduct;
            go = false;
        } else if (fileObj_in.eof()){
            cout << "Kluda: produkta ievade!" << endl;
            productInteger = 0;
            return 0;
        }
        productInteger ++;
    }
    soldProductInteger = productInteger;
    productInteger = 0;
    fileObj_in.close();

    ofstream fileObj_out;
    fileObj_out.open(fileName, ios::trunc | ios::binary); //ieraksta izlaboto informaciju binary file
    while (productQuantityInteger > productInteger){
        product = fileData[productInteger];
        fileObj_out.write((char*)&product, sizeof(product));
        productInteger ++;
    }
    fileObj_out.close();
    
    return 0;
}

int searchProduct(string fileName, string productName){
    Item product;
    ifstream file;

    file.open(fileName, ios::in);
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
