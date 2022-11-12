#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <vector>
#include <cmath>

#define FILE_NAME "the-file.txt"

using namespace std;

class Item {
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

bool compare(double a, double b);
int topThreeExpensive(string fileName);
int topThreeCheapest(string fileName);
int topThreeBestSeller(string fileName);
int topThreeWorstSelling(string fileName);
int topThreeEarn(string fileName);
int topThreeLeast(string fileName);
int writeToFile(Item item, string filename);
int readFromFile(string filename);
int sellProduct(string fileName, string productName);
int searchProduct(string fileName, string productName);
void choiceInfo();

int main() {
    Item item;
    string input;
    int menuItem;
    cout << "Loading..." << '\n' << endl;
    cout << "*********************NOLIKTAVA*********************" << endl;

    while (true) {
        choiceInfo();
        cout << endl << "Kada ir Tava izvele?: ";
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
        case 5:
            cout << "# TOP 3 vismazak pardotie produki:" << endl;
            topThreeWorstSelling(FILE_NAME);
            break;
        case 6:
            cout << "# TOP 3 pelnoshakie produkti:" << endl;
            topThreeEarn(FILE_NAME);
            break;
        case 7:
            cout << "# TOP 3 letakie produkti:" << endl;
            topThreeCheapest(FILE_NAME);
            break;
        case 8:
            cout << "# TOP 3 dargakie produkti:" << endl;
            topThreeExpensive(FILE_NAME);
            break;
        case 9:
            cout << "# TOP 3 slikti pelnoshie produkti:" << endl;
            topThreeLeast(FILE_NAME);
            break;
        case 10:
            cout << "# TOP 3 pardotakie produkti:" << endl;
            topThreeBestSeller(FILE_NAME);
            break;
        default:
            cout << "\nKluda! Nepareiza izvelne!" << endl;
            return 0;
        }
    }
    return 0;
}

bool compare(double a, double b) {
    return (fabs(a - b) < 0.01);
}

int topThreeLeast(string fileName) {
    vector<Item> firstVect;
    vector<Item> secndVect;
    vector<Item> thirdVect;
    Item product;
    Item firstEarn;
    Item secndEarn;
    Item thirdEarn;
    double minEarnings;
    double earnings;
    
    ifstream fileObj_in(fileName, ios::in | ios::binary); //ieseivo vektora all data info 
    if (!fileObj_in.is_open()) {
    cout << "Kluda atverot failu" << endl;
    return -1;
    }
    while (!fileObj_in.eof()) {
        fileObj_in.read((char*)&product, sizeof(product));
        if (!fileObj_in.eof()){
            firstVect.push_back(product);
        }
    }
    fileObj_in.close();

    minEarnings = firstVect[0].itemPrice * firstVect[0].itemsSold;
    for (int i = 0; i < firstVect.size(); i++) {
        earnings = firstVect[i].itemPrice * firstVect[i].itemsSold;
        if (earnings <= minEarnings) {
            minEarnings = earnings;
            firstEarn = firstVect[i];
        }
    }
    for (int i = 0; i < firstVect.size(); i++) { //ieliek jauna vektora bez worstProduct
        if (strcmp (firstEarn.itemName, firstVect[i].itemName) == 0) {
        } else {
            secndVect.push_back(firstVect[i]);
        }
    }

    minEarnings = secndVect[0].itemPrice * secndVect[0].itemsSold;
    for (int i = 0; i < secndVect.size(); i++) {
        earnings = secndVect[i].itemPrice * secndVect[i].itemsSold;
        if (earnings <= minEarnings) {
            minEarnings = earnings;
            secndEarn = secndVect[i];
        }
    }
    for (int i = 0; i < secndVect.size(); i++) {
        if (strcmp (firstEarn.itemName, secndVect[i].itemName) == 0) {
        } else if (strcmp (secndEarn.itemName, secndVect[i].itemName) == 0) {
        } else {
            thirdVect.push_back (secndVect[i]);
        }
    }

    minEarnings = thirdVect[0].itemPrice * thirdVect[0].itemPrice;
    for (int i = 0; i < secndVect.size(); i++) {
        earnings = thirdVect[i].itemPrice * thirdVect[i].itemPrice;
        if (earnings <= minEarnings) {
            minEarnings = earnings;
            thirdEarn = thirdVect[i];
        }
    }

    firstEarn.displayItem();
    cout << "Pelnja: " << firstEarn.itemPrice * firstEarn.itemsSold << endl;
    secndEarn.displayItem();
    cout << "Pelnja: " << secndEarn.itemPrice * secndEarn.itemsSold << endl;
    thirdEarn.displayItem();
    cout << "Pelnja: " << thirdEarn.itemPrice * thirdEarn.itemsSold << endl;

    return 0;    
}

int topThreeBestSeller(string fileName) {
    vector<Item> fileData;
    vector<Item> fileDataExeptWorst;
    vector<Item> fileDataExeptTwoWorst;
    Item product;
    Item bestProduct;
    Item secondBestProduct;
    Item thirdBestProduct;
    int best = 0;
    
    ifstream fileObj_in(fileName, ios::in | ios::binary); //ieseivo vektora all data info 
    if (!fileObj_in.is_open()) {
    cout << "Kluda atverot failu" << endl;
    return -1;
    }
    while (!fileObj_in.eof()) {
        fileObj_in.read((char*)&product, sizeof(product));
        if (!fileObj_in.eof()){
            fileData.push_back(product);
        }
    }
    fileObj_in.close();
    
    // galvena logjika
    best = fileData[0].itemsSold;
    for (int i = 0; i < fileData.size(); i++) {
        if (fileData[i].itemsSold >= best) {
            bestProduct = fileData[i];
            best = fileData[i].itemsSold;
        }
    }
    for (int i = 0; i < fileData.size(); i++) {
        if (strcmp(fileData[i].itemName, bestProduct.itemName) == 0) {
        } else {
            fileDataExeptWorst.push_back(fileData[i]);
        }
    }
    best = fileDataExeptWorst[0].itemsSold;
    for (int i = 0; i < fileDataExeptWorst.size(); i++) {
        if (fileDataExeptWorst[i].itemsSold >= best) {
            secondBestProduct = fileDataExeptWorst[i];  
            best = fileDataExeptWorst[i].itemsSold;
        }
    }
    for (int i = 0; i < fileDataExeptWorst.size(); i++) {
        if (strcmp(fileDataExeptWorst[i].itemName, bestProduct.itemName) == 0){
        } else if (strcmp(fileDataExeptWorst[i].itemName, secondBestProduct.itemName) == 0) {
        } else {
            fileDataExeptTwoWorst.push_back(fileDataExeptWorst[i]);
        }        
    }
    best = fileDataExeptTwoWorst[0].itemsSold;
    for (int i = 0; i < fileDataExeptTwoWorst.size(); i++) {
        if (fileDataExeptTwoWorst[i].itemsSold >= best) {
            thirdBestProduct = fileDataExeptTwoWorst[i];
            best = fileDataExeptTwoWorst[i].itemsSold;
        }
    }
    
    bestProduct.displayItem();
    secondBestProduct.displayItem();
    thirdBestProduct.displayItem();
    return 0;
}

int topThreeExpensive(string fileName) {
    vector<Item> firstVect;
    vector<Item> secndVect;
    vector<Item> thirdVect;
    Item product;
    Item firstExp;
    Item secndExp;
    Item thirdExp;
    double mostExp;
    double expensive;
    
    ifstream fileObj_in(fileName, ios::in | ios::binary);
    if (!fileObj_in.is_open()) {
    cout << "Kluda atverot failu" << endl;
    return -1;
    }
    while (!fileObj_in.eof()) {
        fileObj_in.read((char*)&product, sizeof(product));
        if (!fileObj_in.eof()){
            firstVect.push_back(product);
        }
    }
    fileObj_in.close();

    mostExp = firstVect[0].itemPrice;
    for (int i = 0; i < firstVect.size(); i++) {
        expensive = firstVect[i].itemPrice;
        if (mostExp <= expensive) {
            mostExp = expensive;
            firstExp = firstVect[i];
        }
    }
    for (int i = 0; i < firstVect.size(); i++) {
        if (strcmp (firstExp.itemName, firstVect[i].itemName) == 0) {
        } else {
            secndVect.push_back(firstVect[i]);
        }
    }

    mostExp = secndVect[0].itemPrice;
    for (int i = 0; i < secndVect.size(); i++) {
        expensive = secndVect[i].itemPrice;
        if (mostExp <= expensive) {
            mostExp = expensive;
            secndExp = secndVect[i];
        }
    }
    for (int i = 0; i < secndVect.size(); i++) {
        if (strcmp (firstExp.itemName, secndVect[i].itemName) == 0) {
        } else if (strcmp (secndExp.itemName, secndVect[i].itemName) == 0) {
        } else {
            thirdVect.push_back (secndVect[i]);
        }
    }
    
    mostExp = secndVect[0].itemPrice;
    for (int i = 0; i < thirdVect.size(); i++) {
        expensive = thirdVect[i].itemPrice;
        if (mostExp <= expensive) {
            mostExp = expensive;
            thirdExp = thirdVect[i];
        }
    }

    firstExp.displayItem();
    secndExp.displayItem();
    thirdExp.displayItem();

    return 0;
}

int topThreeCheapest(string fileName) {
    vector<Item> firstVect;
    vector<Item> secndVect;
    vector<Item> thirdVect;
    Item product;
    Item firstCheap;
    Item secndCheap;
    Item thirdCheap;
    double cheapest;
    double cheap;
    
    ifstream fileObj_in(fileName, ios::in | ios::binary); //ieseivo vektora all data info 
    if (!fileObj_in.is_open()) {
    cout << "Kluda atverot failu" << endl;
    return -1;
    }
    while (!fileObj_in.eof()) {
        fileObj_in.read((char*)&product, sizeof(product));
        if (!fileObj_in.eof()){
            firstVect.push_back(product);
        }
    }
    fileObj_in.close();

    cheapest = firstVect[0].itemPrice;
    for (int i = 0; i < firstVect.size(); i++) {
        cheap = firstVect[i].itemPrice;
        if (cheapest >= cheap) {
            cheapest = cheap;
            firstCheap = firstVect[i];
        }
    }
    for (int i = 0; i < firstVect.size(); i++) {
        if (strcmp (firstCheap.itemName, firstVect[i].itemName) == 0) {
        } else {
            secndVect.push_back(firstVect[i]);
        }
    }

    cheapest = secndVect[0].itemPrice;
    for (int i = 0; i < secndVect.size(); i++) {
        cheap = secndVect[i].itemPrice;
        if (cheapest >= cheap) {
            cheapest = cheap;
            secndCheap = secndVect[i];
        }
    }
    for (int i = 0; i < secndVect.size(); i++) {
        if (strcmp (firstCheap.itemName, secndVect[i].itemName) == 0) {
        } else if (strcmp (secndCheap.itemName, secndVect[i].itemName) == 0) {
        } else {
            thirdVect.push_back (secndVect[i]);
        }
    }
    
    cheapest = secndVect[0].itemPrice;
    for (int i = 0; i < thirdVect.size(); i++) {
        cheap = thirdVect[i].itemPrice;
        if (cheapest >= cheap) {
            cheapest = cheap;
            thirdCheap = thirdVect[i];
        }
    }

    // cout << '\n' << '\n'; //tiek pie visiem vektora datiem
    // for (int i = 0; i < secndVect.size(); i++){
    //     cout << secndVect[i].itemName << '\t' << secndVect[i].itemPrice << endl;
    // }

    firstCheap.displayItem();
    secndCheap.displayItem();
    thirdCheap.displayItem();

    return 0;
}

int topThreeEarn(string fileName) {
    vector<Item> firstVect;
    vector<Item> secndVect;
    vector<Item> thirdVect;
    Item product;
    Item firstEarn;
    Item secndEarn;
    Item thirdEarn;
    int maxEarnings;
    int earnings;
    
    ifstream fileObj_in(fileName, ios::in | ios::binary); //ieseivo vektora all data info 
    if (!fileObj_in.is_open()) {
    cout << "Kluda atverot failu" << endl;
    return -1;
    }
    while (!fileObj_in.eof()) {
        fileObj_in.read((char*)&product, sizeof(product));
        if (!fileObj_in.eof()){
            firstVect.push_back(product);
        }
    }
    fileObj_in.close();

    maxEarnings = firstVect[0].itemPrice * firstVect[0].itemsSold;
    for (int i = 0; i < firstVect.size(); i++) {
        earnings = firstVect[i].itemPrice * firstVect[i].itemsSold;
        if (earnings >= maxEarnings) {
            maxEarnings = earnings;
            firstEarn = firstVect[i];
        }
    }
    for (int i = 0; i < firstVect.size(); i++) { //ieliek jauna vektora bez worstProduct
        if (strcmp (firstEarn.itemName, firstVect[i].itemName) == 0) {
        } else {
            secndVect.push_back(firstVect[i]);
        }
    }

    maxEarnings = secndVect[0].itemPrice * secndVect[0].itemsSold;
    for (int i = 0; i < firstVect.size(); i++) {
        earnings = secndVect[i].itemPrice * secndVect[i].itemsSold;
        if (earnings >= maxEarnings) {
            maxEarnings = earnings;
            secndEarn = secndVect[i];
        }
    }
    for (int i = 0; i < secndVect.size(); i++) {
        if (strcmp (firstEarn.itemName, secndVect[i].itemName) == 0) {
        } else if (strcmp (secndEarn.itemName, secndVect[i].itemName) == 0) {
        } else {
            thirdVect.push_back (secndVect[i]);
        }
    }

    maxEarnings = thirdVect[0].itemPrice * thirdVect[0].itemPrice;
    for (int i = 0; i < secndVect.size(); i++) {
        earnings = thirdVect[i].itemPrice * thirdVect[i].itemPrice;
        if (earnings >= maxEarnings) {
            maxEarnings = earnings;
            thirdEarn = thirdVect[i];
        }
    }

    firstEarn.displayItem();
    cout << "Pelnja: " << firstEarn.itemPrice * firstEarn.itemsSold << endl;
    secndEarn.displayItem();
    cout << "Pelnja: " << secndEarn.itemPrice * secndEarn.itemsSold << endl;
    thirdEarn.displayItem();
    cout << "Pelnja: " << thirdEarn.itemPrice * thirdEarn.itemsSold << endl;

    return 0;
}

int topThreeWorstSelling(string fileName) {
    vector<Item> fileData;
    vector<Item> fileDataExeptWorst;
    vector<Item> fileDataExeptTwoWorst;
    Item product;
    Item worstProduct;
    Item secondWorstProduct;
    Item thirdWorstProduct;
    int theWorst = 0;
    
    ifstream fileObj_in(fileName, ios::in | ios::binary); //ieseivo vektora all data info 
    if (!fileObj_in.is_open()) {
    cout << "Kluda atverot failu" << endl;
    return -1;
    }
    while (!fileObj_in.eof()) {
        fileObj_in.read((char*)&product, sizeof(product));
        if (!fileObj_in.eof()){
            fileData.push_back(product);
        }
    }
    fileObj_in.close();
    
    // galvena logjika
    theWorst = fileData[0].itemsSold; //atrod vismazako
    for (int i = 0; i < fileData.size(); i++) {
        if (fileData[i].itemsSold <= theWorst) {
            worstProduct = fileData[i];
            theWorst = fileData[i].itemsSold;
        }
    }
    for (int i = 0; i < fileData.size(); i++) { //ieliek jauna vektora bez worstProduct
        if (strcmp(fileData[i].itemName, worstProduct.itemName) == 0) {
        } else {
            fileDataExeptWorst.push_back(fileData[i]);
        }
    }
    theWorst = fileDataExeptWorst[0].itemsSold; //talak tapati logjika
    for (int i = 0; i < fileDataExeptWorst.size(); i++) {
        if (fileDataExeptWorst[i].itemsSold <= theWorst) {
            secondWorstProduct = fileDataExeptWorst[i];  
            theWorst = fileDataExeptWorst[i].itemsSold;
        }
    }
    for (int i = 0; i < fileDataExeptWorst.size(); i++) {
        if (strcmp(fileDataExeptWorst[i].itemName, worstProduct.itemName) == 0){
        } else if (strcmp(fileDataExeptWorst[i].itemName, secondWorstProduct.itemName) == 0) {
        } else {
            fileDataExeptTwoWorst.push_back(fileDataExeptWorst[i]);
        }        
    }
    theWorst = fileDataExeptTwoWorst[0].itemsSold;
    for (int i = 0; i < fileDataExeptTwoWorst.size(); i++) {
        if (fileDataExeptTwoWorst[i].itemsSold <= theWorst) {
            thirdWorstProduct = fileDataExeptTwoWorst[i];
            theWorst = fileDataExeptTwoWorst[i].itemsSold;
        }
    }

    // cout << '\n' << '\n'; //tiek pie visiem vektora datiem
    // for (int i = 0; i < productQuantityInteger; i++){
    //     cout << fileDataExeptTwoWorst[i].itemName << '\t' << fileDataExeptTwoWorst[i].itemsSold << endl;
    // }
    
    worstProduct.displayItem();
    secondWorstProduct.displayItem();
    thirdWorstProduct.displayItem();
    return 0;
}

int sellProduct(string fileName, string productName) {
    Item product;
    Item soldProduct;
    bool go = true;
    vector<Item> fileData;
    vector<Item> soldFileData;

    double quantity;
    double sold;
    int productInteger = 0;
    int soldProductInteger = 0;
    int productQuantityInteger = 0;

    ifstream fileObj_in(fileName, ios::in | ios::binary); //ieseivo vektora all data info
    if (!fileObj_in.is_open()) {
    cout << "Kluda atverot failu" << endl;
    return -1;
    }
    while (!fileObj_in.eof()) {
        fileObj_in.read((char*)&product, sizeof(product));
        fileData.push_back(product);
        productInteger++;
    }
    fileData.pop_back();
    productInteger--;
    productQuantityInteger = productInteger;
    fileObj_in.close();

    for (int i = 0; i < fileData.size(); i++) {
        if (strcmp(fileData[i].itemName, productName.c_str()) == 0) {
            soldProduct = fileData[i];
            soldProduct.itemQuantity = soldProduct.itemQuantity - (double)1;
            soldProduct.itemsSold = soldProduct.itemsSold + (double)1;
            soldFileData.push_back(soldProduct);
        } else {
            soldFileData.push_back(fileData[i]);
        }
    }
    
    remove(fileName.c_str());
    fstream file;
    file.open(fileName, ios::out|ios::binary|ios::app);
    if (!file){
        cout << "Kluda rakstot faila" << endl;
        return -1;
    }
    for (int i = 0; i < soldFileData.size(); i++) {
    file.write((char*)&soldFileData[i],sizeof(soldFileData[i]));
    }
    file.close();

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
    if (file.read((char*)&product, sizeof(product))){ //loops iet cauri produktiem lidz sakrit nosaukumi
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

void choiceInfo() {
    cout << '\n';
    cout << "---------------IZVELNE--------------" << '\n'; 
    cout << "0: Beigt darbibu" << '\n';
    cout << "1: Pievienot produktu" << '\n';
    cout << "2: Paradit visus produktus" << '\n';
    cout << "3: Pardot produktu" << '\n';
    cout << "4: Meklet produktu" << '\n';
    cout << "5: TOP 3 vismazak pardotie produkti" << '\n';
    cout << "6: TOP 3 pelnoshakie produkti" << '\n';
    cout << "7: TOP 3 letakie produkti" << '\n';
    cout << "8: TOP 3 dargakie produkti" << '\n';
    cout << "9: TOP 3 slikti pelnoshie produkti" << '\n';
    cout << "10: TOP 3 pardotakie produkti" << '\n';
    cout << "------------------------------------";
}