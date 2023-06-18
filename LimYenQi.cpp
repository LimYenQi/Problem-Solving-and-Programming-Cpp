#include <iostream>
#include <iomanip>
using namespace std;

void clrscr();
void CinemaLogo();
int Movie();
void MovieDetails(int&);
void Class(int, int&, int&, int&);
void Seats(int&, int&, int&, int&);
void displaySeats(int, int);
void chooseSeats(int, int, int, int[], int[]);
void checkSeats(int, int[], int[]);
void food(int&, double&);
void confirmation(int, int, int, int, int, int, int, int[]);
void Calc(int, int, int, int, int, int, double);
void tickets(int, int, int, int, int, int, int, int[]);
void seatsLeft();
void salesReport();

const int THIRTY = 30;
int M1seats[3][30] = { 0 };
int M2seats[3][30] = { 0 };
int M3seats[3][30] = { 0 };
int m1c1 = 30, m1c2 = 30, m1c3 = 30, m2c1 = 30, m2c2 = 30, m2c3 = 30, m3c1 = 30, m3c2 = 30, m3c3 = 30;
int tscSeats[3] = { 0 }, taSeats[3] = { 0 }, tcSeats[3] = { 0 }, tsSeats[3] = { 0 }, tscSales[3] = { 0 }, taSales[3] = { 0 }, tcSales[3] = { 0 }, tsSales[3] = { 0 };
char confirm;
char cont;
char retry;

int main()
{
    int movieChoice, numSeats, scSeats, aSeats, cSeats, sSeats, seats, foodCode;
    double foodPrice;
    int seatsNo[30] = { 0 }, chkSeats[30] = { 0 };
    int classChoice = 0;

    do {
        do {
            //Display the logo of the cinema
            CinemaLogo();

            //Ask the user to choose which movie to watch
            do {
                movieChoice = Movie();
                MovieDetails(movieChoice);
            } while (movieChoice != 1 && movieChoice != 2 && movieChoice != 3);

            //Display the number of seats available and ask the user to choose the class he wants
            Class(movieChoice, classChoice, seats, numSeats);

            //Ask the user to enter the number of seats for every category
            do {
                Seats(scSeats, aSeats, cSeats, sSeats);
                if (scSeats < 0 || aSeats < 0 || cSeats < 0 || sSeats < 0) {
                    cout << "Invalid Input!! Please try again!" << endl;
                }
                if ((scSeats + aSeats + cSeats + sSeats) != numSeats) {
                    cout << "Total number of seats does not match!! Please try again!" << endl;
                }
            } while (scSeats < 0 || aSeats < 0 || cSeats < 0 || sSeats < 0 || (scSeats + aSeats + cSeats + sSeats) != numSeats);


            do {
                retry = '0';

                //Display the seat numbers available for the movie and the class chosen by the user
                displaySeats(movieChoice, classChoice);

                //Ask the user to choose the seat numbers that he wants
                chooseSeats(movieChoice, classChoice, numSeats, seatsNo, chkSeats);

                //Check if the seat number chosen is repeated
                checkSeats(numSeats, seatsNo, chkSeats);
            } while (retry == '1');

            //Ask the user if he wants any food or beverages
            food(foodCode, foodPrice);

            //Clear screen
            clrscr();
            //Print the logo of the cinema
            CinemaLogo();

            //Ask whether the user is confirm to proceed to payment
            confirmation(movieChoice, classChoice, scSeats, aSeats, cSeats, sSeats, numSeats, seatsNo);
            if (confirm != 'Y') {
                clrscr();
            }
            //Loop back to the start if the user do not want to proceed to payment
        } while (confirm != 'Y');

        //Clear screen
        clrscr();
        //Print the logo of the cinema
        CinemaLogo();

        //Calculate the total that the user needs to pay
        Calc(classChoice, movieChoice, scSeats, aSeats, cSeats, sSeats, foodPrice);

        //Print out the tickets that the user buys
        tickets(movieChoice, classChoice, scSeats, aSeats, cSeats, sSeats, numSeats, seatsNo);

        //Shows the number of seats left for every class of every movie
        seatsLeft();

        //Ask if there is any customerIf no, it will clear screen and go out from the loop
        if (cont == 'Y') {
            clrscr();
        }
        //If no more ticket is available
        if (m1c1 == 0 && m1c2 == 0 && m1c3 == 0 && m2c1 == 0 && m2c2 == 0 && m2c3 == 0 && m3c1 == 0 && m3c2 == 0 && m3c3 == 0) {
            CinemaLogo();
            cout << "No more ticket is available!!" << endl;
            cout << "Press any key to proceed to the sales report... ";
            cin >> retry;
        }
        //If there are still tickets available and there are customers it will loop from the start
    } while (cont == 'Y' && (m1c1 != 0 || m1c2 != 0 || m1c3 != 0 || m2c1 != 0 || m2c2 != 0 || m2c3 != 0 || m3c1 != 0 || m3c2 != 0 || m3c3 != 0));

    //If no more customer or no more ticket is available, it will clear screen and go out from the loop
    clrscr();
    //Print the logo of the cinema
    CinemaLogo();

    //Show the sales report for every movie
    salesReport();

    return 0;
}

void clrscr() {
    system("cls");
}
void CinemaLogo()
{
    cout << "\n********************************************************************************************************************************************* " << endl;
    cout << " _____________        ____         ________           _________  " << endl;
    cout << "|             |      /    \\       |   ___  \\         /         |  ________   ___    __   _________   ___    ___        ____       ___    ___ " << endl;
    cout << "|____     ____|     /  /\\  \\      |  |   |  |       /     _____| |__    __| |   \\  |  | |   ______| |   \\  /   |      /    \\      \\  \\  /  / " << endl;
    cout << "     |   |         /  /  \\  \\     |  |___|  |      |     |          |  |    |    \\ |  | |  |____    |    \\/    |     /  /\\  \\      \\  \\/  / " << endl;
    cout << "     |   |        /  /____\\  \\    |        /       |     |          |  |    |     \\|  | |   ____|   |          |    /  /__\\  \\      \\    / " << endl;
    cout << "     |   |       /   ______   \\   |   |\\   \\       |     |_____     |  |    |  |\\     | |  |        |  |\\  /|  |   /   ____   \\     /    \\ " << endl;
    cout << "     |   |      /   /      \\   \\  |   | \\   \\       \\          |  __|  |__  |  | \\    | |  |______  |  | \\/ |  |  /   /    \\   \\   /  /\\  \\ " << endl;
    cout << "     |___|     /___/        \\___\\ |___|  \\___\\       \\_________| |________| |__|  \\___| |_________| |__|    |__| /___/      \\___\\ /__/  \\__\\ " << endl;
    cout << "\n********************************************************************************************************************************************* " << endl;
    cout << "" << endl;
}
int Movie()
{
    int choice;

    cout << "Movies available :" << endl;
    cout << "   1. Sonic The Hedgehog" << endl;
    cout << "   2. Avengers: Endgame" << endl;
    cout << "   3. Her Blue Sky" << endl;
    cout << "Which movie would you like to watch ? (1/2/3) ";
    cin >> choice;

    return choice;
}
void MovieDetails(int& mChoice1)
{
    switch (mChoice1)
    {
    case 1:
        cout << "\nMovie name: Sonic The Hedgehog " << endl;
        cout << "Date/Time : Wednesday, 23/9/2020, 6:45p.m." << endl;
        if (m1c1 == 0 && m1c2 == 0 && m1c3 == 0) {
            cout << "\nNo seats are available for this movie!! Please choose another movie!" << endl;
            cout << endl;
            mChoice1 = 4;
        }
        break;
    case 2:
        cout << "\nMovie name: Avengers: Endgame " << endl;
        cout << "Date/Time : Wednesday, 23/9/2020, 5:15p.m." << endl;
        if (m2c1 == 0 && m2c2 == 0 && m2c3 == 0) {
            cout << "\nNo seats are available for this movie!! Please choose another movie!" << endl;
            cout << endl;
            mChoice1 = 4;
        }
        break;
    case 3:
        cout << "\nMovie name: Her Blue Sky " << endl;
        cout << "Date/Time : Wednesday, 23/9/2020, 8:15p.m." << endl;
        if (m3c1 == 0 && m3c2 == 0 && m3c3 == 0) {
            cout << "\nNo seats are available for this movie!! Please choose another movie!" << endl;
            cout << endl;
            mChoice1 = 4;
        }
        break;
    default:
        cout << "\nInvalid input!! Please try again!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "" << endl;
    }
}
void Class(int mChoice2, int& cChoice1, int& cseats, int& nSeats)
{
    if (mChoice2 == 1)
    {
        do {
            cout << "\nSeats available: " << endl;
            cout << "   Class 1 -- " << m1c1 << endl;
            cout << "   Class 2 -- " << m1c2 << endl;
            cout << "   Class 3 -- " << m1c3 << endl;
            do {
                cout << "Class required ? (1/2/3) ";
                cin >> cChoice1;
                if (cChoice1 != 1 && cChoice1 != 2 && cChoice1 != 3) {
                    cout << "Invalid input!! Please try again!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (cChoice1 != 1 && cChoice1 != 2 && cChoice1 != 3);
            if (cChoice1 == 1) {
                cseats = m1c1;
            }
            else if (cChoice1 == 2) {
                cseats = m1c2;
            }
            else if (cChoice1 == 3) {
                cseats = m1c3;
            }
            if (cseats == 0) {
                cout << "No more seats are available!! Please choose another class!" << endl;
            }
        } while (cseats == 0);
        do {
            cout << "Total number of seats required : ";
            cin >> nSeats;
            if (nSeats > cseats || nSeats == 0) {
                cout << "Invalid input!! Please try again!" << endl;
            }
        } while (nSeats > cseats || nSeats == 0);
    }
    else if (mChoice2 == 2)
    {
        do {
            cout << "\nSeats available: " << endl;
            cout << "   Class 1 -- " << m2c1 << endl;
            cout << "   Class 2 -- " << m2c2 << endl;
            cout << "   Class 3 -- " << m2c3 << endl;
            do {
                cout << "Class required ? (1/2/3) ";
                cin >> cChoice1;
                if (cChoice1 != 1 && cChoice1 != 2 && cChoice1 != 3) {
                    cout << "Invalid input!! Please try again!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (cChoice1 != 1 && cChoice1 != 2 && cChoice1 != 3);
            if (cChoice1 == 1) {
                cseats = m2c1;
            }
            else if (cChoice1 == 2) {
                cseats = m2c2;
            }
            else if (cChoice1 == 3) {
                cseats = m2c3;
            }
            if (cseats == 0) {
                cout << "No more seats is available!! Please choose another class!" << endl;
            }
        } while (cseats == 0);
        do {
            cout << "Total number of seats required : ";
            cin >> nSeats;
            if (nSeats > cseats || nSeats == 0) {
                cout << "Invalid input!! Please try again!" << endl;
            }
        } while (nSeats > cseats || nSeats == 0);
    }
    else if (mChoice2 == 3)
    {
        do {
            cout << "\nSeats available: " << endl;
            cout << "   Class 1 -- " << m3c1 << endl;
            cout << "   Class 2 -- " << m3c2 << endl;
            cout << "   Class 3 -- " << m3c3 << endl;
            do {
                cout << "Class required ? (1/2/3) ";
                cin >> cChoice1;
                if (cChoice1 != 1 && cChoice1 != 2 && cChoice1 != 3) {
                    cout << "\nInvalid input!! Please try again!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (cChoice1 != 1 && cChoice1 != 2 && cChoice1 != 3);
            if (cChoice1 == 1) {
                cseats = m3c1;
            }
            else if (cChoice1 == 2) {
                cseats = m3c2;
            }
            else if (cChoice1 == 3) {
                cseats = m3c3;
            }
            if (cseats == 0) {
                cout << "No more seats is available!! Please choose another class!" << endl;
            }
        } while (cseats == 0);
        do {
            cout << "Total number of seats required : ";
            while (!(cin >> nSeats)) {
                cout << "\nInvalid input!! Please try again!" << endl;
                cout << "Total number of seats required : ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (nSeats > cseats || nSeats == 0) {
                cout << "\nInvalid input!! Please try again!" << endl;
            }
        } while (nSeats > cseats || nSeats == 0);
    }
    else {
        cout << "\nInvalid input!! Please try again!" << endl;
    }
}
void Seats(int& sc1, int& adult1, int& child1, int& student1)
{
    cout << "\nNumber of seats required for " << endl;
    cout << "Senior Citizen (above 60 years old)    : ";
    while (!(cin >> sc1)) {
        cout << "\nInvalid input!! Please try again!" << endl;
        cout << "Senior Citizen (above 60 years old)    : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Adult                                  : ";
    while (!(cin >> adult1)) {
        cout << "\nInvalid input!! Please try again!" << endl;
        cout << "Adult                                  : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Child (below 12 years old)             : ";
    while (!(cin >> child1)) {
        cout << "\nInvalid input!! Please try again!" << endl;
        cout << "Child (below 12 years old)             : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Student (must show registration cards) : ";
    while (!(cin >> student1)) {
        cout << "\nInvalid input!! Please try again!" << endl;
        cout << "Student (must show registration cards) : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void displaySeats(int mChoice3, int cChoice3) {
    cout << "\nSeats available : " << endl;
    switch (mChoice3)
    {
    case 1:
        for (int i = 0; i < 30; i++) {
            if (M1seats[cChoice3 - 1][i] == 0) {
                cout << cChoice3 << setw(2) << setfill('0') << i + 1 << "  ";
            }
            else if (M1seats[cChoice3 - 1][i] == 1) {
                cout << "     ";
            }
            if (i == 9) {
                cout << endl;
            }
            if (i == 19) {
                cout << endl;
            }
        }
        break;
    case 2:
        for (int i = 0; i < 30; i++) {
            if (M2seats[cChoice3 - 1][i] == 0) {
                cout << cChoice3 << setw(2) << setfill('0') << i + 1 << "  ";
            }
            else if (M2seats[cChoice3 - 1][i] == 1) {
                cout << "     ";
            }
            if (i == 9) {
                cout << endl;
            }
            if (i == 19) {
                cout << endl;
            }
        }
        break;
    case 3:
        for (int i = 0; i < 30; i++) {
            if (M3seats[cChoice3 - 1][i] == 0) {
                cout << cChoice3 << setw(2) << setfill('0') << i + 1 << "  ";
            }
            else if (M3seats[cChoice3 - 1][i] == 1) {
                cout << "     ";
            }
            if (i == 9) {
                cout << endl;
            }
            if (i == 19) {
                cout << endl;
            }
        }
        break;
    }
}
void chooseSeats(int mChoice4, int cChoice4, int tSeats, int seatsno[], int chkSeats[]) {
    cout << "\n\nPlease enter the LAST TWO digits for your prefered seats : " << endl;
    if (mChoice4 == 1) {
        for (int i = 0; i < tSeats; i++) {
            do {
                cout << "Seat " << i + 1 << " : ";
                while (!(cin >> seatsno[i])) {
                    cout << "Invalid input!! Please try again!" << endl;
                    cout << "Seat " << i + 1 << " : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                chkSeats[i] = seatsno[i];
                if (seatsno[i] > 30 || seatsno[i] <= 0) {
                    cout << "Invalid input!! Please try again!" << endl;
                }
                if (cChoice4 - 1 < 3 && cChoice4 - 1 >= 0) {
                    if (M1seats[cChoice4 - 1][seatsno[i] - 1] == 1) {
                        cout << "This seat is not available!! Please choose another seat!" << endl;
                    }
                }
            } while (M1seats[cChoice4 - 1][seatsno[i] - 1] == 1 || seatsno[i] > 30 || seatsno[i] <= 0);
        }
    }
    else if (mChoice4 == 2) {
        for (int i = 0; i < tSeats; i++) {
            do {
                cout << "Seat " << i + 1 << " : ";
                while (!(cin >> seatsno[i])) {
                    cout << "Invalid input!! Please try again!" << endl;
                    cout << "Seat " << i + 1 << " : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                chkSeats[i] = seatsno[i];
                if (seatsno[i] > 30 || seatsno[i] <= 0) {
                    cout << "Invalid input!! Please try again!" << endl;
                }
                if (M2seats[cChoice4 - 1][seatsno[i] - 1] == 1) {
                    cout << "This seat is not available!! Please choose another seat!" << endl;
                }
            } while (M2seats[cChoice4 - 1][seatsno[i] - 1] == 1 || seatsno[i] > 30 || seatsno[i] <= 0);
        }
    }
    else if (mChoice4 == 3) {
        for (int i = 0; i < tSeats; i++) {
            do {
                cout << "Seat " << i + 1 << " : ";
                while (!(cin >> seatsno[i])) {
                    cout << "Invalid Input!! Please try again!" << endl;
                    cout << "Seat " << i + 1 << " : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                chkSeats[i] = seatsno[i];
                if (seatsno[i] > 30 || seatsno[i] <= 0) {
                    cout << "Invalid Input!! Please try again!" << endl;
                }
                if (M3seats[cChoice4 - 1][seatsno[i] - 1] == 1) {
                    cout << "This seat is not available!! Please choose another seat!" << endl;
                }
            } while (M3seats[cChoice4 - 1][seatsno[i] - 1] == 1 || seatsno[i] > 30 || seatsno[i] <= 0);
        }
    }
}
void checkSeats(int tSeats0, int seatsno0[], int chkSeats0[]) {
    for (int i = 0; i < tSeats0; i++) {
        chkSeats0[i] = 0;
        for (int j = 0; j < tSeats0; j++) {
            if (seatsno0[i] == chkSeats0[j]) {
                cout << "Seat number repeated!! Please try again!" << endl;
                do {
                    cout << "Press 1 to re-enter the seats : ";
                    cin >> retry;
                    if (retry != '1') {
                        cout << "Invalid Input!!" << endl;
                    }
                } while (retry != '1');
                break;
            }
        }
        for (int x = 0; x < tSeats0; x++) {
            chkSeats0[x] = seatsno0[x];
        }
        if (retry == '1') {
            break;
        }
    }
}
void food(int& fCode, double& fPrice) {
    fPrice = 0;
    int num = 0;
    char foodDrinks, conf;

    cout << "\nAny food or beverages? (Y/y for yes, any key for no) ";
    cin >> foodDrinks;
    foodDrinks = toupper(foodDrinks);
    if (foodDrinks == 'Y') {
        cout << "\nFood and Beverages Menu : " << endl;
        cout << "\t1. Popcorn                         -- RM 5.50" << endl;
        cout << "\t2. Coca-Cola                       -- RM 3.50" << endl;
        cout << "\t3. Popcorn Chicken                 -- RM 9.50" << endl;
        cout << "\t4. Chicken nuggets                 -- RM 7.50" << endl;
        cout << "\t5. Combo (Popcorn & Mineral water) -- RM 6.80" << endl;
        do {
            do {
                cout << "Which food or beverages would you like to choose? (1/2/3/4/5) ";
                cin >> fCode;
                if (fCode == 1) {
                    fPrice += 5.50;
                }
                else if (fCode == 2) {
                    fPrice += 3.50;
                }
                else if (fCode == 3) {
                    fPrice += 9.50;
                }
                else if (fCode == 4) {
                    fPrice += 7.50;
                }
                else if (fCode == 5) {
                    fPrice += 6.80;
                }
                else {
                    cout << "Invalid input!! Please try again!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (fCode == 1 || fCode == 2 || fCode == 3 || fCode == 4 || fCode == 5) {
                    do {
                        cout << "How much would your like to have? ";
                        while (!(cin >> num)) {
                            cout << "Invalid input!! Please try again!" << endl;
                            cout << "How much would your like to have? ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (num <= 0) {
                            cout << "Invalid input!! Please try again!" << endl;
                        }
                    } while (num <= 0);
                }
                fPrice *= num;
            } while (fCode != 1 && fCode != 2 && fCode != 3 && fCode != 4 && fCode != 5);
            cout << "\nAnymore? (Y/y for yes, any key for no) ";
            cin >> conf;
            conf = toupper(conf);
            cout << endl;
        } while (conf == 'Y');
    }
}
void confirmation(int mChoice5, int cChoice5, int sc2, int adult2, int child2, int student2, int tSeats1, int seatsno1[]) {
    if (mChoice5 == 1) {
        cout << "\nMovie name: Sonic The Hedgehog " << endl;
        cout << "Date/Time : Wednesday, 23/9/2020, 6:45p.m." << endl;
    }
    else if (mChoice5 == 2) {
        cout << "\nMovie name: Avengers: Endgame " << endl;
        cout << "Date/Time : Wednesday, 23/9/2020, 5:15p.m." << endl;
    }
    else if (mChoice5 == 3) {
        cout << "\nMovie name: Her Blue Sky " << endl;
        cout << "Date/Time : Wednesday, 23/9/2020, 8:15p.m." << endl;
    }
    cout << "\nClass chosen : Class " << cChoice5 << endl;
    cout << "\nNumber of seats chosen for " << endl;
    cout << "Senior Citizen (above 60 years old)    : " << sc2 << endl;
    cout << "Adult                                  : " << adult2 << endl;
    cout << "Child (below 12 years old)             : " << child2 << endl;
    cout << "Student (must show registration cards) : " << student2 << endl;
    cout << "Seats chosen : ";
    for (int i = 0; i < tSeats1; i++) {
        cout << setw(2) << setfill('0') << seatsno1[i] << ", ";
    }
    cout << endl;
    cout << "\nConfirm to proceed to payment? (Y/y for yes, any key for no) ";
    cin >> confirm;
    confirm = toupper(confirm);

    if (confirm == 'Y') {
        if (mChoice5 == 1) {
            tscSeats[0] += sc2;
            taSeats[0] += adult2;
            tcSeats[0] += child2;
            tsSeats[0] += student2;
            for (int i = 0; i < tSeats1; i++) {
                M1seats[cChoice5 - 1][seatsno1[i] - 1] = 1;
            }
        }
        else if (mChoice5 == 2) {
            tscSeats[1] += sc2;
            taSeats[1] += adult2;
            tcSeats[1] += child2;
            tsSeats[1] += student2;
            for (int i = 0; i < tSeats1; i++) {
                M2seats[cChoice5 - 1][seatsno1[i] - 1] = 1;
            }
        }
        else if (mChoice5 == 3) {
            tscSeats[2] += sc2;
            taSeats[2] += adult2;
            tcSeats[2] += child2;
            tsSeats[2] += student2;
            for (int i = 0; i < tSeats1; i++) {
                M3seats[cChoice5 - 1][seatsno1[i] - 1] = 1;
            }
        }
    }
}
void Calc(int cChoice6, int mChoice6, int sc2, int adult2, int child2, int student2, double fPrice1)
{
    int scPrice = 0, aPrice = 0, cPrice = 0, sPrice = 0, scTotal, aTotal, cTotal, sTotal;
    double dtotal, paid, total;

    if (cChoice6 == 1)
    {
        scPrice = 14;
        aPrice = 18;
        cPrice = 9;
        sPrice = 14;
    }
    else if (cChoice6 == 2)
    {
        scPrice = 16;
        aPrice = 20;
        cPrice = 10;
        sPrice = 16;
    }
    else if (cChoice6 == 3)
    {
        scPrice = 20;
        aPrice = 26;
        cPrice = 13;
        sPrice = 20;
    }
    scTotal = scPrice * sc2;
    aTotal = aPrice * adult2;
    cTotal = cPrice * child2;
    sTotal = sPrice * student2;
    total = scTotal + aTotal + cTotal + sTotal;

    cout << "\t\t\tBILLING" << endl;
    cout << "\n============================================================" << endl;
    cout << "\nTickets :" << endl;
    cout << "Price for Senior Citizen : " << sc2 << " x RM " << scPrice << " \t= RM " << scTotal << endl;
    cout << "Price for Adult          : " << adult2 << " x RM " << aPrice << " \t= RM " << aTotal << endl;
    cout << "Price for Child          : " << child2 << " x RM " << cPrice << " \t= RM " << cTotal << endl;
    cout << "Price for Student        : " << student2 << " x RM " << sPrice << " \t= RM " << sTotal << endl;
    cout << "\nFood and Beverages :" << endl;
    cout << "Price for Food and Bevarages \t\t= RM " << fixed << setprecision(2) << fPrice1 << endl;
    cout.unsetf(ios::fixed);
    total += fPrice1;
    cout << "\n\t\tTotal price to pay \t= RM " << fixed << setprecision(2) << total << endl;
    if (total >= 100) {
        dtotal = total * 0.95;
        cout << "\t\t5% Discount is offered for every transaction over RM 100" << endl;
        cout << "\t\tTotal after discount\t= RM " << fixed << setprecision(2) << dtotal << endl;
        cout.unsetf(ios::fixed);
    }
    tscSales[mChoice6 - 1] += scTotal;
    taSales[mChoice6 - 1] += aTotal;
    tcSales[mChoice6 - 1] += cTotal;
    tsSales[mChoice6 - 1] += sTotal;
    if (total >= 100) {
        do {
            cout << "\t\tCash paid          \t= RM ";
            while (!(cin >> paid)) {
                cout << "\nInvalid Input!! Please try again!" << endl;
                cout << "\t\tCash paid          \t= RM ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (paid < 0 || paid < dtotal) {
                cout << "\n\t\tInvalid Input!! Please try again!" << endl;
            }
        } while (paid < 0 || paid < dtotal);
        cout << "\t\tChange due         \t= RM " << fixed << setprecision(2) << paid - dtotal << endl;
        cout.unsetf(ios::fixed);
    }
    else {
        do {
            cout << "\t\tCash paid          \t= RM ";
            while (!(cin >> paid)) {
                cout << "\nInvalid Input!! Please try again!" << endl;
                cout << "\t\tCash paid          \t= RM ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (paid < 0 || paid < total) {
                cout << "\n\t\tInvalid Input!! Please try again!" << endl;
            }
        } while (paid < 0 || paid < total);
        cout << "\t\tChange due         \t= RM " << fixed << setprecision(2) << paid - total << endl;
        cout.unsetf(ios::fixed);
    }
}
void tickets(int mChoice7, int cChoice7, int sc3, int adult3, int child3, int student3, int tSeats2, int seatsno2[]) {
    cout << "\nHere are your ticket(s) : " << endl;
    for (int i = 0; i < tSeats2; i++) {
        cout << " ================================================================" << endl;
        cout << "|\tTAR Cinemax                                ";
        if (cChoice7 == 1) {
            cout << "Seat No. " << 100 + seatsno2[i] << "  |" << endl;
        }
        else if (cChoice7 == 2) {
            cout << "Seat No. " << 200 + seatsno2[i] << "  |" << endl;
        }
        else if (cChoice7 == 3) {
            cout << "Seat No. " << 300 + seatsno2[i] << "  |" << endl;
        }
        cout << "|                                                                |" << endl;
        if (mChoice7 == 1) {
            cout << "|\tMovie name: Sonic The Hedgehog                           |" << endl;
            cout << "|\tDate/Time : Wednesday, 23/9/2020, 6:45p.m.               |" << endl;
            cout << "|                                                                |" << endl;
        }
        else if (mChoice7 == 2) {
            cout << "|\tMovie name: Avengers: Endgame                            |" << endl;
            cout << "|\tDate/Time : Wednesday, 23/9/2020, 5:15p.m.               |" << endl;
            cout << "|                                                                |" << endl;
        }
        else if (mChoice7 == 3) {
            cout << "|\tMovie name: Her Blue Sky                                 |" << endl;
            cout << "|\tDate/Time : Wednesday, 23/9/2020, 8:15p.m.               |" << endl;
            cout << "|                                                                |" << endl;
        }
        if (sc3 > 0) {
            if (cChoice7 == 1) {
                cout << "|\t(Senior Citizen -- Class 1)                              |" << endl;
                cout << "|\tTicket Price : RM 14                                     |" << endl;
            }
            else if (cChoice7 == 2) {
                cout << "|\t(Senior Citizen -- Class 2)                              |" << endl;
                cout << "|\tTicket Price : RM 16                                     |" << endl;
            }
            else if (cChoice7 == 3) {
                cout << "|\t(Senior Citizen -- Class 3)                              |" << endl;
                cout << "|\tTicket Price : RM 20                                     |" << endl;
            }
            sc3 -= 1;
        }
        else if (adult3 > 0) {
            if (cChoice7 == 1) {
                cout << "|\t(Adult -- Class 1)                                       |" << endl;
                cout << "|\tTicket Price : RM 18                                     |" << endl;
            }
            else if (cChoice7 == 2) {
                cout << "|\t(Adult -- Class 2)                                       |" << endl;
                cout << "|\tTicket Price : RM 20                                     |" << endl;
            }
            else if (cChoice7 == 3) {
                cout << "|\t(Adult -- Class 3)                                       |" << endl;
                cout << "|\tTicket Price : RM 26                                     |" << endl;
            }
            adult3 -= 1;
        }
        else if (child3 > 0) {
            if (cChoice7 == 1) {
                cout << "|\t(Child -- Class 1)                                       |" << endl;
                cout << "|\tTicket Price : RM 9                                      |" << endl;
            }
            else if (cChoice7 == 2) {
                cout << "|\t(Child -- Class 2)                                       |" << endl;
                cout << "|\tTicket Price : RM 10                                     |" << endl;
            }
            else if (cChoice7 == 3) {
                cout << "|\t(Child -- Class 3)                                       |" << endl;
                cout << "|\tTicket Price : RM 13                                     |" << endl;
            }
            child3 -= 1;
        }
        else if (student3 > 0) {
            if (cChoice7 == 1) {
                cout << "|\t(Student -- Class 1)                                     |" << endl;
                cout << "|\tTicket Price : RM 14                                     |" << endl;
            }
            else if (cChoice7 == 2) {
                cout << "|\t(Student -- Class 2)                                     |" << endl;
                cout << "|\tTicket Price : RM 16                                     |" << endl;
            }
            else if (cChoice7 == 3) {
                cout << "|\t(Student -- Class 3)                                     |" << endl;
                cout << "|\tTicket Price : RM 20                                     |" << endl;
            }
            student3 -= 1;
        }
        cout << " ================================================================" << endl;
        cout << endl;
    }
}
void seatsLeft() {
    int x;
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M1seats[i][j] == 1) {
                    x -= 1;
                    m1c1 = x;
                }
            }
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M2seats[i][j] == 1) {
                    x -= 1;
                    m2c1 = x;
                }
            }
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M3seats[i][j] == 1) {
                    x -= 1;
                    m3c1 = x;
                }
            }
        }
        if (i == 1) {
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M1seats[i][j] == 1) {
                    x -= 1;
                    m1c2 = x;
                }
            }
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M2seats[i][j] == 1) {
                    x -= 1;
                    m2c2 = x;
                }
            }
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M3seats[i][j] == 1) {
                    x -= 1;
                    m3c2 = x;
                }
            }
        }
        if (i == 2) {
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M1seats[i][j] == 1) {
                    x -= 1;
                    m1c3 = x;
                }
            }
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M2seats[i][j] == 1) {
                    x -= 1;
                    m2c3 = x;
                }
            }
            x = 30;
            for (int j = 0; j < 30; j++) {
                if (M3seats[i][j] == 1) {
                    x -= 1;
                    m3c3 = x;
                }
            }
        }
    }
    cout << endl;
    cout << "Seats left for Sonic The Hedgehog :" << endl;
    cout << "Class 1 -- " << m1c1 << endl;
    cout << "Class 2 -- " << m1c2 << endl;
    cout << "Class 3 -- " << m1c3 << endl;
    cout << endl;
    cout << "Seats left for Avengers: Endgame :" << endl;
    cout << "Class 1 -- " << m2c1 << endl;
    cout << "Class 2 -- " << m2c2 << endl;
    cout << "Class 3 -- " << m2c3 << endl;
    cout << endl;
    cout << "Seats left for Her Blue Sky :" << endl;
    cout << "Class 1 -- " << m3c1 << endl;
    cout << "Class 2 -- " << m3c2 << endl;
    cout << "Class 3 -- " << m3c3 << endl;
    cout << endl;
    cout << "Anymore customer? (Y/y for yes, any key for no) ";
    cin >> cont;
    cont = toupper(cont);
}
void salesReport() {
    cout << "               TICKET SALES REPORT" << endl;
    cout << "\n==================================================" << endl;
    cout << "\nMovie name: Sonic The Hedgehog " << endl;
    cout << "Date/Time : Wednesday, 23/9/2020, 6:45p.m." << endl;
    cout << "\nSeat occupancy for" << endl;
    cout << "\tTotal Seats\tQuantity Sold\tSold(%)" << endl;
    cout << "Class 1\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m1c1 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m1c1)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "Class 2\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m1c2 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m1c2)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "Class 3\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m1c3 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m1c3)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "\t       ---\t         ---   -------" << endl;
    cout << "Overall\t\t90\t\t" << setw(4) << setfill(' ') << (THIRTY - m1c1) + (THIRTY - m1c2) + (THIRTY - m1c3) << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << (((THIRTY - double(m1c1)) + (THIRTY - double(m1c2)) + (THIRTY - double(m1c3))) / 90) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "\nSales for category" << endl;
    cout << "\t\tSeats\tSales(RM)" << endl;
    cout << "Senior Citizen\t" << setw(4) << setfill(' ') << tscSeats[0] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tscSales[0]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Adult\t\t" << setw(4) << setfill(' ') << taSeats[0] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(taSales[0]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Child\t\t" << setw(4) << setfill(' ') << tcSeats[0] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tcSales[0]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Student\t\t" << setw(4) << setfill(' ') << tsSeats[0] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tsSales[0]) << endl;
    cout.unsetf(ios::fixed);
    cout << "\t\t----\t-------" << endl;
    cout << "Total\t\t" << setw(4) << setfill(' ') << tscSeats[0] + taSeats[0] + tcSeats[0] + tsSeats[0] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tscSales[0]) + double(taSales[0]) + double(tcSales[0]) + double(tsSales[0]) << endl;
    cout.unsetf(ios::fixed);

    cout << "\n==================================================" << endl;
    cout << "\nMovie name: Avengers: Endgame " << endl;
    cout << "Date/Time : Wednesday, 23/9/2020, 5:15p.m." << endl;
    cout << "\nSeat occupancy for" << endl;
    cout << "\tTotal Seats\tQuantity Sold\tSold(%)" << endl;
    cout << "Class 1\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m2c1 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m2c1)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "Class 2\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m2c2 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m2c2)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "Class 3\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m2c3 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m2c3)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "\t       ---\t         ---   -------" << endl;
    cout << "Overall\t\t90\t\t" << setw(4) << setfill(' ') << (THIRTY - m2c1) + (THIRTY - m2c2) + (THIRTY - m2c3) << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << (((THIRTY - double(m2c1)) + (THIRTY - double(m2c2)) + (THIRTY - double(m2c3))) / 90) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "\nSales for category" << endl;
    cout << "\t\tSeats\tSales(RM)" << endl;
    cout << "Senior Citizen\t" << setw(4) << setfill(' ') << tscSeats[1] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tscSales[1]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Adult\t\t" << setw(4) << setfill(' ') << taSeats[1] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(taSales[1]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Child\t\t" << setw(4) << setfill(' ') << tcSeats[1] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tcSales[1]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Student\t\t" << setw(4) << setfill(' ') << tsSeats[1] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tsSales[1]) << endl;
    cout.unsetf(ios::fixed);
    cout << "\t\t----\t-------" << endl;
    cout << "Total\t\t" << setw(4) << setfill(' ') << tscSeats[1] + taSeats[1] + tcSeats[1] + tsSeats[1] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tscSales[1]) + double(taSales[1]) + double(tcSales[1]) + double(tsSales[1]) << endl;
    cout.unsetf(ios::fixed);

    cout << "\n==================================================" << endl;
    cout << "\nMovie name: Her Blue Sky " << endl;
    cout << "Date/Time : Wednesday, 23/9/2020, 8:15p.m." << endl;
    cout << "\nSeat occupancy for" << endl;
    cout << "\tTotal Seats\tQuantity Sold\tSold(%)" << endl;
    cout << "Class 1\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m3c1 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m3c1)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "Class 2\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m3c2 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m3c2)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "Class 3\t\t30\t\t" << setw(4) << setfill(' ') << THIRTY - m3c3 << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << ((THIRTY - double(m3c3)) / THIRTY) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "\t       ---\t         ---   -------" << endl;
    cout << "Overall\t\t90\t\t" << setw(4) << setfill(' ') << (THIRTY - m3c1) + (THIRTY - m3c2) + (THIRTY - m3c3) << "\t" << setw(6) << setfill(' ') << fixed << setprecision(2) << (((THIRTY - double(m3c1)) + (THIRTY - double(m3c2)) + (THIRTY - double(m3c3))) / 90) * 100 << endl;
    cout.unsetf(ios::fixed);
    cout << "\nSales for category" << endl;
    cout << "\t\tSeats\tSales(RM)" << endl;
    cout << "Senior Citizen\t" << setw(4) << setfill(' ') << tscSeats[2] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tscSales[2]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Adult\t\t" << setw(4) << setfill(' ') << taSeats[2] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(taSales[2]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Child\t\t" << setw(4) << setfill(' ') << tcSeats[2] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tcSales[2]) << endl;
    cout.unsetf(ios::fixed);
    cout << "Student\t\t" << setw(4) << setfill(' ') << tsSeats[2] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tsSales[2]) << endl;
    cout.unsetf(ios::fixed);
    cout << "\t\t----\t-------" << endl;
    cout << "Total\t\t" << setw(4) << setfill(' ') << tscSeats[2] + taSeats[2] + tcSeats[2] + tsSeats[2] << "\t" << setw(7) << setfill(' ') << fixed << setprecision(2) << double(tscSales[2]) + double(taSales[2]) + double(tcSales[2]) + double(tsSales[2]) << endl;
    cout.unsetf(ios::fixed);
}