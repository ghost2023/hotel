#include <iostream>
#include <string>
using namespace std;

struct Customer {
    int idNumber;
    string name;
    char sex;
    int phoneNumber;

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

struct Reservation {
    int reservationDay[3];  // d, m, y
    int receptionistId;
    struct Customer customer;
};

struct Room {
    int number;
    int floor;
    int tier;
    float price;
    int numberOfBeds;
    bool isReservered;
    struct Reservation reservation;

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

struct Receptionist {
    int id;
    string name;
    char sex;
    string password;

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

        if (rooms[roomNum - 1].isReservered) {
            cout << "Sorry this room is Occupied. Cancelling...\n";
            return;
        }

        Customer customer;

        cout << "Customer Id Number: ";
        cin >> customer.idNumber;
        cin.ignore();
        cout << "Customer Name: ";
        getline(cin, customer.name);

        cout << "Customer Phone Number: ";
        cin >> customer.phoneNumber;

        cout << "Customer Male or Female[m/f]: ";
        cin >> customer.sex;

        int reservationDay[3];
        cout << "Date: ";
        cin >> reservationDay[0];

        cout << "Month: ";
        cin >> reservationDay[1];

        cout << "Year: ";
        cin >> reservationDay[2];

        rooms[roomNum - 1].isReservered = true;
        rooms[roomNum - 1].reservation.reservationDay[0] = reservationDay[0];
        rooms[roomNum - 1].reservation.reservationDay[1] = reservationDay[1];
        rooms[roomNum - 1].reservation.reservationDay[2] = reservationDay[2];
        rooms[roomNum - 1].reservation.receptionistId = id;
        rooms[roomNum - 1].reservation.customer = customer;
    }

    void checkout(Room rooms[]) {
        int roomNum;
        cout << "Room Number: ";
        cin >> roomNum;

        if (!rooms[roomNum - 1].isReservered) {
            cout << "Sorry this room is not Occupied. Cancelling...\n";
            return;
        }
        int dateToday[3];
        cout << "Date: ";
        cin >> dateToday[0];

        cout << "Month: ";
        cin >> dateToday[1];

        cout << "Year: ";
        cin >> dateToday[2];

        Reservation reservation = rooms[roomNum - 1].reservation;
        float duration = (dateToday[2] - reservation.reservationDay[2]) * 365 +
                         (dateToday[1] - reservation.reservationDay[1]) * 30 +
                         (dateToday[0] - reservation.reservationDay[0]);

        float total = duration * rooms[roomNum - 1].price;

        cout << "Your total is: " << total << endl;

        Reservation emptyReservation;
        rooms[roomNum - 1].isReservered = false;
        rooms[roomNum - 1].reservation = emptyReservation;
    }
};

struct Manager {
    string name;
    string password;

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

struct Hotel {
    struct Manager manager;
    Room rooms[25];
    Receptionist receptions[3];

    void init() {
        for (int i = 0; i < 25; i++) {
            Reservation reservation;
            rooms[i].number = i + 1;
            rooms[i].floor = i / 5;
            rooms[i].tier = (i / 5) + 1;

            if (i < 10)
                rooms[i].numberOfBeds = 2;
            else if (i < 20)
                rooms[i].numberOfBeds = 3;
            else
                rooms[i].numberOfBeds = 4;

            rooms[i].price = 299 + ((i / 5) + 1) * 100;
            rooms[i].isReservered = false;
            rooms[i].reservation = reservation;
        };

        receptions[0] = {1, "Sofia", 'f', "1234"};
        receptions[1] = {2, "Mark", 'M', "1234"};
        receptions[2] = {3, "Zoe", 'f', "1234"};
        manager = {"Alex", "4321"};
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
                if (inputId == receptions[i].id && inputPassword == receptions[i].password) return i;
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
    Hotel hotel;
    hotel.init();

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
                        if (hotel.rooms[i].isReservered) {
                            hotel.rooms[i].reservation.customer.display();
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
                cout << "\nReception Id: " << loggedReceptionist.id << " .\n";
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