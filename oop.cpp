#include <iostream>
#include <string>
using namespace std;

class Customer {
    int idNumber;
    string name;
    char sex;
    int phoneNumber;

   public:
    Customer() {}

    Customer(int i, string n, char s, int pn) {
        idNumber = i;
        name = n;
        sex = s;
        phoneNumber = pn;
    }

    void display() {
        cout << "|=======================|\n";
        cout << "|        Customer " << idNumber << "\t|\n";
        cout << "|-----------------------|\n";
        cout << "| Name: " << name << "\t|\n";
        cout << "| Sex: " << sex << "\t\t|\n";
        cout << "| Phone Number: " << phoneNumber << "\t|\n";
        cout << "|=======================|\n\n";
    }
};

class Reservation {
    int reservationDay[3];  // d, m, y
    int receptionistId;
    Customer customer;

   public:
    Reservation() {}
    Reservation(int date, int month, int year, int id, Customer c) {
        reservationDay[0] = date;
        reservationDay[1] = month;
        reservationDay[2] = year;

        receptionistId = id;
        customer = c;
    }

    Customer getCustomer() {
        return customer;
    }

    int getDuration(int date, int month, int year) {
        return ((year - reservationDay[2]) * 365) + ((month - reservationDay[1]) * 30) + date - reservationDay[0] - 1;
    }
};

class Room {
    int number;
    int floor;
    int tier;
    float price;
    int numberOfBeds;
    bool isReservered;
    Reservation reservation;

   public:
    Room() {}
    Room(int num, int f, int t, float p, int beds) {
        number = num;
        floor = f;
        tier = t;
        price = p;
        numberOfBeds = beds;
        isReservered = false;
    }

    void setReservation(Reservation res) {
        reservation = res;
        isReservered = true;
    }

    Reservation getReservation() {
        return reservation;
    }

    float getPrice() {
        return price;
    }

    bool isRoomReserved() {
        return isReservered;
    }

    void clearReservation() {
        isReservered = false;
    }

    void display() {
        cout << "|=======================|\n";
        cout << "|        Room " << number << "\t|\n";
        cout << "|-----------------------|\n";
        cout << "| Floor: " << floor << "\t\t|\n";
        cout << "| Tier: " << tier << "\t\t|\n";
        cout << "| Price: " << price << "\t\t|\n";
        cout << "| Beds: " << numberOfBeds << "\t\t|\n";
        cout << "| Reserved: " << (isReservered ? "true" : "false") << "\t|\n";
        cout << "|=======================|\n\n";
    }
};

class Receptionist {
    int id;
    string name;
    char sex;
    string password;

   public:
    Receptionist() {}
    Receptionist(int i, string n, char s, string p) {
        id = i;
        name = n;
        sex = s;
        password = p;
    }

    bool isLoginCorrect(int i, string p) {
        return i == id && p == password;
    }

    void display() {
        cout << "|=======================|\n";
        cout << "|        Receptionist " << id << "\t|\n";
        cout << "|-----------------------|\n";
        cout << "| Name: " << name << "\t\t|\n";
        cout << "| Sex: " << sex << "\t\t|\n";
        cout << "|=======================|\n\n";
    }

    void makeReservation(Room rooms[]) {
        int roomNum;
        cout << "Room Number: ";
        cin >> roomNum;

        if (rooms[roomNum - 1].isRoomReserved()) {
            cout << "Sorry this room is Occupied. Cancelling...\n";
            return;
        }

        int idNumber, phoneNumber;
        char sex;
        string name;

        cout << "Customer Id Number: ";
        cin >> idNumber;
        cin.ignore();
        cout << "Customer Name: ";
        getline(cin, name);

        cout << "Customer Phone Number: ";
        cin >> phoneNumber;

        cout << "Customer Male or Female[m/f]: ";
        cin >> sex;

        int date, month, year;
        cout << "Date: ";
        cin >> date;

        cout << "Month: ";
        cin >> month;

        cout << "Year: ";
        cin >> year;

        rooms[roomNum - 1].setReservation(Reservation(date, month, year, id, Customer(idNumber, name, sex, phoneNumber)));
    }

    void checkout(Room rooms[]) {
        int roomNum;
        cout << "Room Number: ";
        cin >> roomNum;

        if (!rooms[roomNum - 1].isRoomReserved()) {
            cout << "Sorry this room is not Occupied. Cancelling...\n";
            return;
        }
        int date, month, year;
        cout << "Date: ";
        cin >> date;

        cout << "Month: ";
        cin >> month;

        cout << "Year: ";
        cin >> year;

        Reservation reservation = rooms[roomNum - 1].getReservation();
        float duration = reservation.getDuration(date, month, year);

        float total = duration * rooms[roomNum - 1].getPrice();

        cout << "Your total is: " << total << endl;

        rooms[roomNum - 1].clearReservation();
    }
};

class Manager {
    string name;
    string password;

   public:
    Manager() {}
    Manager(string n, string p) {
        name = n, password = p;
    }

    bool login() {
        string inputPassword;
        cout << "\n| MANAGER LOGIN |\n";

        int tries = 0;
        while (tries < 3) {
            cout << "password: ";
            cin >> inputPassword;
            if (inputPassword == password) return true;
            cout << "Sorry, Incorrect password.\n";
            tries++;
        }
        return false;
    }
};

class Hotel {
   public:
    Manager manager;
    Room rooms[25];
    Receptionist receptions[3];

   public:
    Hotel() {
        for (int i = 0; i < 25; i++) {
            int beds;

            if (i < 10)
                beds = 2;
            else if (i < 20)
                beds = 3;
            else
                beds = 4;

            rooms[i] = Room(i + 1, i / 5, (i / 5) + 1, 299 + ((i / 5) + 1) * 100, beds);
        };

        receptions[0] = Receptionist(1, "Sofia", 'f', "1234");
        receptions[1] = Receptionist(2, "Mark", 'M', "1234");
        receptions[2] = Receptionist(3, "Zoe", 'f', "1234");
        manager = Manager("Alex", "4321");
    }

    int receptionLogin() {
        string inputPassword;
        int inputId;
        cout << "| RECEPTIONIST LOGIN |\n";

        int tries = 0;
        while (tries < 3) {
            cout << "id: ";
            cin >> inputId;
            cout << "password: ";
            cin >> inputPassword;
            for (int i = 0; i < 3; i++) {
                if (receptions[i].isLoginCorrect(inputId, inputPassword)) return i;
            }
            cout << "Sorry, Incorrect id or password\n";
            tries++;
        }
        return -1;
    }

    void displayRooms() {
        for (int i = 0; i < 25; i++) {
            rooms[i].display();
        }
    }
};

int main() {
    Hotel hotel = Hotel();

    int role;
    while (1) {
        cout << " WELCOME TO HOTEL MANAGEMENT SYSTEM \n";
        cout << "login as \n\t[1] Manager.\n\t[2] Receptionst.\n\t[3] Quit.\n\n\t==> ";
        cin >> role;

        if (role == 1) {
            bool isLogged = hotel.manager.login();
            if (!isLogged) break;
            int option;
            while (1) {
                cout << "Manager.\n";
                cout << "\t[1] Check Rooms.\n\t[2] Check Receptionst.\n\t[3] Check Customers.\n\t[4] Logout.\n\n\t==> ";
                cin >> option;
                if (option == 1) {
                    hotel.displayRooms();
                } else if (option == 2) {
                    for (int i = 0; i < 3; i++) {
                        hotel.receptions[i].display();
                    }
                } else if (option == 3) {
                    bool isEmpty = true;
                    for (int i = 0; i < 25; i++) {
                        if (hotel.rooms[i].isRoomReserved()) {
                            hotel.rooms[i].getReservation().getCustomer().display();
                            isEmpty = false;
                        }
                    }
                    if (isEmpty) cout << "There are no Customers.\n";
                } else {
                    cout << "Logging out...\n";
                    break;
                }
            }

        } else if (role == 2) {
            int index = hotel.receptionLogin();

            if (index < -1) break;

            Receptionist loggedReceptionist = hotel.receptions[index];

            int option;
            while (1) {
                cout << "\t[1] Check Rooms.\n\t[2] Make Reservation.\n\t[3] Checkout.\n\t[4] Logout.\n\n\t==> ";
                cin >> option;
                if (option == 1) {
                    hotel.displayRooms();
                } else if (option == 2) {
                    loggedReceptionist.makeReservation(hotel.rooms);
                } else if (option == 3) {
                    loggedReceptionist.checkout(hotel.rooms);
                } else {
                    cout << "Logging out...\n";
                    break;
                }
            }
        } else
            break;
    }
    return 0;
}