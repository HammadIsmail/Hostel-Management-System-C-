#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <cmath>
using namespace std;
const int MAX_CUSTOMER = 100;
string getField(string record, int field);
void availbleRooms();
void menu();
void info();
void header();
void updateInfo();
void admin(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[]);
void user(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[]);
void deleteInfo();
void addCustumer(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[]);
void deleteCustumer(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[]);
void updateCustumer(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[]);
void viewRecords(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[]);
bool login();
void signUp();
void loginInfo();
void recordInfo();
void signUpInfo();
void custumer(string ID[],string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[]);

int main() {
    system("cls");
           // Intializing the the here
   string names[MAX_CUSTOMER];
    string addresses[MAX_CUSTOMER];
    string roomTypes[MAX_CUSTOMER];
    string days[MAX_CUSTOMER];
    string CNICs[MAX_CUSTOMER];
    string rooms[MAX_CUSTOMER];
    string ID[MAX_CUSTOMER] ;
    string rent[MAX_CUSTOMER];
    int count = 0;
    // for color
    system("color 0A");
    // to display UMAS header
    header();
    cout << "Press Enter to Continue.........";
    getch();
    system("cls");
    while (true)
    {
          info();
    cout<<"Enter (1) for Admin "<<endl;
    cout<<"Enter (2) for Client "<<endl;
    cout<<"Enter (3) for Exit "<<endl;
    cout<<"Enter the option :";
    int opt;
    cin>>opt;
    switch (opt)
    {
    case 1:
    admin(ID,names,addresses,roomTypes,days, CNICs, rooms,count, rent);
    break;
    case 2:
    user(ID,names,addresses,roomTypes,days, CNICs, rooms,count, rent);
    break;
    case 3:
        exit(0);
    default:
    cout<<"Invalid Input";
        break;
    }
    }
    
  
   
        return 0;
}

/////// Area of Fuctions start from here////////////////////// 

// Logic for Sign up and login
bool login() {
    string username, password, user, pass;

    cout << "~~~> Username: ";
    cin >> username;
    cout << "~~~> Password: ";
    cin >> password;

    fstream fs;
    fs.open("Login.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening Login.txt file." << endl;
        return false;
    }

    getline(fs, user);
    getline(fs, pass);
    fs.close();

    if (username == user && password == pass) {
        return true;
    } else {
        return false;
    }
}

void signUp() {
    fstream fs;
    string username, password;
    cout << "~~~> Username: ";
    cin >> username;
    cout << "~~~> Password: ";
    cin >> password;

    fs.open("Login.txt", ios::out);
    if (!fs.is_open()) {
        cout << "Error opening Login.txt file." << endl;
        return;
    }

    fs << username << endl;
    fs << password << endl;
    fs.close();

    cout << "Login information written to Login.txt successfully." << endl;
    Sleep(1000);
    cout << "Press any Key to Continue........" << endl;
    getch();
}
//////Logic to add customer///////

void addCustumer(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[])
 {
    int TotalRent[MAX_CUSTOMER];
   availbleRooms();
    if (count < MAX_CUSTOMER) {
        cout << "Enter ID  = ";
        cin >> ID[count];
        cin.ignore();
        cout << "Enter Your Name = ";
        getline(cin, names[count]);
        cout << "Enter Your Address Name = ";
        getline(cin, addresses[count]);
        cout << "Enter Your RoomType  = ";
        cin >> roomTypes[count];
        cout << "Enter Your Days to stay  = ";
        cin >> days[count];
        cout << "Enter Your CNIC = ";
        cin >> CNICs[count];
        cout << "Enter Room No = ";
        cin >> rooms[count];
        cout<<"Enter Rent of Room = ";
        cin>>rent[count];
       TotalRent[count]=stoi(days[count])*stoi(rent[count]);
        cout << "Record Entered...... " << endl;

        // logic to add data to file
        fstream fs;
        fs.open("CustumerData.txt", ios::app);
        if (!fs.is_open()) {
            cout << "Error opening CustumerData.txt file." << endl;
            return;
        }

        fs << ID[count] << "," << names[count] << "," << addresses[count] << "," << roomTypes[count] << ","
           << days[count] << "," << CNICs[count] << "," << rooms[count]<<","<<TotalRent[count] << endl;

        fs.close();

        count+=1; // Increment count after writing to the file
        getch();
        system("CLS");
    } else {
        cout << "Maximum number of customers reached." << endl;
        getch();
        system("CLS");
    }
}

/// Function to view the record ////////////
void viewRecords(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[])
{
    string record;
    fstream data;
    data.open("CustumerData.txt", ios::in);
    int idx = 0;

    while (getline(data, record) && idx < MAX_CUSTOMER) {
        ID[idx] = getField(record, 1);
        names[idx] = getField(record, 2);
        addresses[idx] = getField(record, 3);
        roomTypes[idx] = getField(record, 4);
        days[idx] = getField(record, 5);
        CNICs[idx] = getField(record, 6);
        rooms[idx] = getField(record, 7);
        rent[idx] = getField(record, 8);

        idx = idx + 1;
    }
        count=idx;
        if(idx>0)
        {
        cout << "Following customers Exist in the System" << endl;
        cout << "Index\tID\tName\tAddress\t\tRoomType\tDays\tCNIC\tRoom No\t\tRent" << endl;
        for (int i = 0; i < idx; i++) {
            cout << i << "\t" << ID[i] << "\t" << names[i] << "\t" << addresses[i] << "\t" << roomTypes[i] << "\t\t"
                 << days[i] << "\t" << CNICs[i] << "\t" << rooms[i]<<"\t\t"<<rent[i]<<endl;

        }
        }
        else
        {
            cout<<"No data to display.....";
        }
    data.close();
    cout<<endl;
    cout <<"Press any key to continue  "<<endl;
    getch();
    system("CLS");
}

/// function to check fields;////////////
string getField(string record, int field)
{
    int commaCount = 1;
    string item;
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}

/////////////////////////////////////////// Functions for Headers //////////////////////////////////

void header() {
    fstream fs;
    string line;

    fs.open("header.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening header.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();
}

void menu()
{
    fstream fs;
    string line;

    fs.open("menu.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening header.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();

}

void info()
{
	fstream fs;
    string line;

    fs.open("Info.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening header.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();

}
void loginInfo()
{
 fstream fs;
    string line;

    fs.open("loginInfo.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening header.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();

}
void recordInfo()
{

 fstream fs;
    string line;

    fs.open("recordInfo.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening header.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();
}

void updateInfo()
{
        fstream fs;
   string line;

    fs.open("updateInfo.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening header.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();

}

void deleteInfo()
{
    fstream fs;
 string line;

    fs.open("deleteInfo.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening header.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();

}

void signUpInfo()
{
 fstream fs;
    string line;


    fs.open("SignUpInfo.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening header.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();
}


// Function for custumer
void custumer(string ID[],string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[])
{
  
      // no of  Custumer wants to enter 
    cout << "Enter the number of customers you want to enter: ";
    int numcustomers;
    cin >> numcustomers;
    
     while (count < numcustomers) {
        system("CLS");
        menu();

        int choice;
        cout << "Enter Your Choice = ";
        cin >> choice;
        
        switch (choice) {
        case 1:
            system("CLS");
            cin.ignore();
            info();
            addCustumer(ID,names, addresses, roomTypes, days, CNICs, rooms, count, rent);
            system("CLS");
            break;
        case 2:
                    system("CLS");
                    recordInfo();
                viewRecords(ID, names,  addresses,  roomTypes,  days,  CNICs,  rooms,count,rent);
                       system("CLS");
            break;
        case 3:
            updateCustumer(ID, names,  addresses,  roomTypes,  days,  CNICs,  rooms,  count,rent);
            system("CLS");
            break;
        case 4:
                   deleteCustumer(ID, names,  addresses,  roomTypes,  days,  CNICs,  rooms,count,rent);
                   system("cls");
            break;
        case 0:
                exit(0);
        default:
            cout << "Invalid Choice!!!" << endl;

        }
    }        
    }
    /// function for deleting customer

void deleteCustumer(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[])
{
    system("cls");
deleteInfo();
viewRecords(ID, names,  addresses,  roomTypes,  days,  CNICs,  rooms,  count,rent);
if (count>0)
{
 int c = 0;
 fstream customer;
 fstream temp;
fstream room;
string r;
int t;
    string line;
    int opt;
    cout << "ENTER THE CUSTOMER'S NUMBER WHOSE DATA YOU WANT DELETED (Starting from 0) = ";
    cin >> opt;

    customer.open("CustumerData.txt", ios::in);
    temp.open("Temp.txt", ios::out);
    room.open("Room.txt", ios::in);
    getline(room,r);
    t =stoi(r)+1;
    room.close();
    room.open("Room.txt", ios::out);
    room<<t;
    room.close();
    while (getline(customer, line))
    {
        if (c != opt)
        {
            temp << line << endl;
        }
        c++;
    }
    customer.close();
    temp.close();
    remove("CustumerData.txt");
    rename("Temp.txt", "CustumerData.txt");
    cout << "DATA DELETED ! ";
    getch();
    system("cls");
}
else
{
    cout<<"No data to delete...";
    getch();
}

}

void updateCustumer(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[])
{
      system("cls");
updateInfo();
viewRecords(ID, names,  addresses,  roomTypes,  days,  CNICs,  rooms,    count,rent);
if (count>0)
{
 int c = 0;
 fstream customer;
 fstream temp;
    string line;
    int opt;
    cout << "ENTER THE customer'S NUMBER WHOSE DATA YOU WANT DELETED (Starting from 0) = ";
    cin >> opt;

    customer.open("CustumerData.txt", ios::in);
    temp.open("Temp.txt", ios::out);
    while (getline(customer, line))
    {
        
        if (c == opt)
        {
            cin.ignore();
        cout << "Enter ID  = ";
        cin >> ID[opt];
        cin.ignore();
        cout << "Enter Your Name = ";
        getline(cin, names[opt]);
        cout << "Enter Your Address Name = ";
        getline(cin, addresses[opt]);
        cout << "Enter Your RoomType  = ";
        cin >> roomTypes[opt];
        cout << "Enter Your Days to stay  = ";
        cin >> days[opt];
        cout << "Enter Your CNIC = ";
        cin >> CNICs[opt];
        cout << "Enter Room No = ";
        cin >> rooms[opt];
        cout << "Enter Room Rent = ";
        cin >> rent[opt];

        temp << ID[opt] << "," << names[opt] << "," << addresses[opt] << "," << roomTypes[opt] << ","
           << days[opt] << "," << CNICs[opt] << "," << rooms[opt] <<","<<rent[opt]<<endl;
        }
       else
        {
            temp << line << endl;
        }
        c++;
    }
    customer.close();
    temp.close();
    remove("CustumerData.txt");
    rename("Temp.txt", "CustumerData.txt");
    cout << "DATA Updated ! ";
    getch();
    system("cls");
}
else
{
    cout<<"No data to Update...";
    getch();
}
}
void availbleRooms()
{
	fstream fs;
    string line;

    fs.open("Room.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening Room.txt file." << endl;
        return;
    }
int total;
    while (!fs.eof()) {
        getline(fs, line);
total = stoi(line)-1 ;
        cout <<"Available Rooms are "<<total<< endl;
    }
    fs.close();
 fs.open("Room.txt", ios::out);
 fs<<total;
fs.close();
}

void admin(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[])
{
 while (true)
    {
        system("cls");
        info();
        cout << "Press (1) to SignUp and (2) for SignIn : ";
    int select;
    cin >> select;
     bool loggedIn = false;
    switch (select) {
    case 1:
    // for signup
        system("cls");
        signUpInfo();
        signUp();
        break;
    case 2:
    // for login
            system("cls");
        while (!loggedIn) {
             loginInfo();
            loggedIn = login();

            if (!loggedIn) {
                cout << "Login failed. Please try again." << endl;
                getch();
                system("CLS");
            }
        }
        /// for Entering Custumer 
    system("cls");
    info();
    custumer( ID, names,  addresses,  roomTypes,  days,  CNICs,  rooms,  count, rent);
    default:
        cout << "Invalid Input";
    }
    }
}

void user(string ID[] ,string names[], string addresses[], string roomTypes[], string days[], string CNICs[], string rooms[],  int& count,string rent[])
{
    system("cls");
    info();
     string record;
    fstream data;
    string id;
    cout << "Enter the ID : ";
    cin>>id;
    data.open("CustumerData.txt", ios::in);
   int idx = 0;
    while (getline(data, record) && idx < MAX_CUSTOMER) {
         ID[idx] = getField(record, 1);
        names[idx] = getField(record, 2);
        addresses[idx] = getField(record, 3);
        roomTypes[idx] = getField(record, 4);
        days[idx] = getField(record, 5);
        CNICs[idx] = getField(record, 6);
        rooms[idx] = getField(record, 7);
        rent[idx] = getField(record, 8);
        if (ID[idx] == id)
        {
            break;
        }
        
        idx = idx + 1;
    }
    system("cls");
    recordInfo();
    
        cout << "Following customers Exist in the System" << endl;
        cout << "Index\tID\tName\tAddress\t\tRoomType\tDays\tCNIC\tRoom No\t\tRent" << endl;
            cout << idx << "\t" << ID[idx] << "\t" << names[idx] << "\t" << addresses[idx] << "\t" << roomTypes[idx] << "\t\t"
                 << days[idx] << "\t" << CNICs[idx] << "\t" << rooms[idx]<<"\t\t"<<rent[idx]<<endl;
 
    data.close();  
    cout <<"Press any key to continue  "<<endl;
    getch();
    system("CLS");
}