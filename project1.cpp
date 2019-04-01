#include<iostream>
#include<fstream>
using namespace std;

class ItemsDetails{
    public:
    char name[100];
    float price;
    int pid;
    void input(int );
    void output();
    void load();
};

class ManageItems : public ItemsDetails {
    public:
    void addItem();
    void modifyItem();
    void deleteItem();
    void showItem();
    void loadData();
    void pushData();
    void fileClear();

}readData[105];
int index = 0;
string outt = "              ";
string outt1 = "     ";

void ItemsDetails :: input(int id){
    cout<<"\n------------------------------------------------------------\n";
    this->pid = id;
    cout<<"Enter name of the Item: ";
    cin>>name;
    cout<<"Enter the price of the Item: ";
    cin>>price;
}

void ItemsDetails :: output(){
    if(pid != -1){
        cout<<outt<<pid<<outt<<name<<outt<<outt1<<price<<"\n";
        cout<<"---------------------------------------------------------------------\n";
    }
    // cout<<"\n\n";
}

void ItemsDetails :: load(){
    readData[index].pid = this->pid;
    int ip = 0;
    while(name[ip] != '\0')  readData[index].name[ip] = this->name[ip], ip++;
    readData[index].price = this->price;
    index++;
}

void ManageItems :: fileClear(){
    ofstream fout;
    fout.open("data.txt", ios::trunc);
    fout.close();
}

void ManageItems :: addItem(){
    int lastID;
    if(index) lastID = readData[index-1].pid;
    else lastID = 0;
    readData[index++].input(lastID+1);
}

void ManageItems :: showItem(){
    for(int i=0;i<index;i++) readData[i].output();
}

void ManageItems :: modifyItem(){
    cout<<"Enter the Product ID of the product you want to modify: ";
    int id;
    cin>>id;
    int i;
    bool fg = 0;
    for(i=0;i<index;i++){
        if(id == readData[i].pid){
            redo:
                fg = 1;
                cout<<"Enter 1 to modify product name...\n";
                cout<<"Enter 2 to modify product price...\n";
                cout<<"Enter your choice: ";
                int ch;
                float newPrice;
                char newName[100];
                cin>>ch;
                if(ch == 2){
                    cout<<"Enter the new amount: ";
                    cin>>newPrice;
                    readData[i].price = newPrice;
                }
                else if(ch == 1){
                    cout<<"Enter the new name of the product: ";
                    cin>>newName;
                    int ip = 0;
                    while(newName[ip] != '\0')  readData[i].name[ip] = newName[ip], ip++;
                }
                else{
                    cout<<"Ooopssss.... you have entered wrong choice.... ENTER AGAIN !!\n";
                    goto redo;
                }
            break;
        }
    }
    cout<<"Item number "<<id<<" has been modified successfully...!!\n";
}

void ManageItems :: deleteItem(){
    cout<<"Enter the Product ID of the product you want to delete: ";
    int id;
    cin>>id;
    int i;
    for(i=0;i<index;i++){
        if(id == readData[i].pid){
            readData[i].pid = -1;
            break;
        }
    }
    cout<<"Item number "<<id<<" has been deleted successfully...!!\n";
}

void ManageItems :: loadData(){
    ItemsDetails fetchedItem;
    fstream fin;
    fin.open("data.txt", ios::in | ios::out);
    fin.read((char*) &fetchedItem, sizeof(fetchedItem));
    while(!fin.eof()){
        fetchedItem.load();
        fin.read((char*) &fetchedItem, sizeof(fetchedItem));
    }
    fin.close();
    // for(int i=0;i<index;i++) readData[i].output();
}

void ManageItems :: pushData(){
    int i=0, j = index;
    ofstream fout;
    fout.open("data.txt", ios::app | ios::in | ios::out);
    while(j--){
        if(readData[i].pid != -1)
        fout.write((char*) &readData[i], sizeof(readData[i]));
        i++;
    }
    fout.close();
}

int main(){
    ManageItems ob;
    ob.loadData();

    cout<<"\n\n#######-------------- SELECT ANY OPTION ---------------#############\n\n\n";
    while(1){
        cout<<"1. Add Item || 2. Midify Item || 3. Delete Item || 4. Show Item || 5. Exit\n\n";
        cout<<"Enter your choice: ";
        int ch;
        cin>>ch;
        cout<<"\n\n";
        ManageItems obj;
        switch(ch){
            case 1: fflush(stdin);
                    obj.addItem();
                    cout<<"\n\n";
                    break;
            case 2: fflush(stdin);
                    obj.modifyItem();
                    cout<<"\n\n";
                    break;
            case 3: fflush(stdin);
                    obj.deleteItem();
                    cout<<"\n\n";
                    break;
            case 4: cout<<"|"<<outt1<<"Product ID"<<outt1<<"|"<<outt1<<"Product Name"<<outt1<<"|"<<outt1<<"Product Price"<<outt1<<"|\n";
                    cout<<"---------------------------------------------------------------------\n";
                    obj.showItem();
                    cout<<"\n\n";
                    break;
            case 5: obj.fileClear();
                    obj.pushData();
                    exit(0);
            default: cout<<"You have entered invalid choice...\n";
        }
        
    }
}