#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
#include <map>


using namespace std;

struct Donor {
    string name;
    string bloodGroup;
    int units;
    string contactDetails;
    string email;
    string date;

    Donor(string n, string bg, int u, string cd, string e, string d)
        : name(n), bloodGroup(bg), units(u), contactDetails(cd), email(e), date(d) {}
};

class BloodBank {
private:
    string databaseFileName;
    map<string, int> bloodGroupUnits;  // Track total units per blood group

public:
    BloodBank() : databaseFileName("C:/Users/Dell/OneDrive/Desktop/dataset/donor_database.csv") {
        createDatabase();
    }

    void createDatabase() {
        ifstream file(databaseFileName.c_str());
        if (!file.good()) {
            ofstream newFile(databaseFileName.c_str());
            newFile.close();
            cout << "New database created." << endl;
        }
        file.close();
    }

    void loadDatabase(vector<Donor>& donors) {
        ifstream file(databaseFileName);
        string line;

        while (getline(file, line)) {
            istringstream ss(line);
            vector<string> tokens;

            while (getline(ss, line, ',')) {
                tokens.push_back(line);
            }

            if (tokens.size() == 6) {
                Donor newDonor(tokens[0], tokens[1], stoi(tokens[2]), tokens[3], tokens[4], tokens[5]);
                donors.push_back(newDonor);
                updateBloodGroupUnits(newDonor.bloodGroup, newDonor.units);
            }
        }

        file.close();
    }

    void saveDatabase(const Donor& donor) {
        ofstream file(databaseFileName, ios::app);
        file << donor.name << "," << donor.bloodGroup << "," << donor.units
             << "," << donor.contactDetails << "," << donor.email << "," << donor.date << endl;
        file.close();
    }

    void updateBloodGroupUnits(const string& bloodGroup, int units) {
        bloodGroupUnits[bloodGroup] += units;
    }

    void addDonor(const Donor& donor) {
        saveDatabase(donor);
        updateBloodGroupUnits(donor.bloodGroup, donor.units);
        cout << "Donor added successfully." << endl;
    }

    void addDonor() {
        string name, bloodGroup, contactDetails, email, date;
        int units;

        cin.ignore(); // Ensure newline from previous input is consumed

        cout << "Enter donor name: ";
        getline(cin, name);

        cout << "Enter blood group: ";
        getline(cin, bloodGroup);

        cout << "Enter units of blood donated: ";
        cin >> units;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        cout << "Enter contact details:\n Mobile number : ";
        getline(cin, contactDetails);

        cout << "Enter email: ";
        getline(cin, email);

        cout << "Enter donation date (YYYY-MM-DD): ";
        getline(cin, date);

        Donor newDonor(name, bloodGroup, units, contactDetails, email, date);
        addDonor(newDonor);
    }

    void displayDonorDetails(const Donor& donor) {
        cout << "Donor Name: " << donor.name << endl;
        cout << "Blood Group: " << donor.bloodGroup << endl;
        cout << "Units Donated: " << donor.units << endl;
        cout << "Contact Details: " << donor.contactDetails << endl;
        cout << "Email: " << donor.email << endl;
        cout << "Date: " << donor.date << endl;
        cout << "---------------------------" << endl;
    }

    void displayBloodGroupUnits() {
        cout << "Total Units per Blood Group:" << endl;
        for (const auto& entry : bloodGroupUnits) {
            cout << entry.first << ": " << entry.second << " units" << endl;
        }
    }

    void displayDonors(const vector<Donor>& donors, const string& filterDate = "") {
        cout << "Donors in the Blood Bank:" << endl;
        for (const auto& donor : donors) {
            if (filterDate.empty() || donor.date == filterDate) {
                displayDonorDetails(donor);
            }
        }
    }

    void searchByNameAndDisplay(const string& name) {
        vector<Donor> donors;
        loadDatabase(donors);

        bool found = false;
        for (const auto& donor : donors) {
            if (donor.name == name) {
                displayDonorDetails(donor);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Donor not available." << endl;
        }
    }

    void searchByBloodGroupAndDisplay(const string& bloodGroup) {
        vector<Donor> donors;
        loadDatabase(donors);

        bool found = false;
        for (const auto& donor : donors) {
            if (donor.bloodGroup == bloodGroup) {
                displayDonorDetails(donor);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Donor not available." << endl;
        }
    }

    void displayMainMenu() {
        cout << "\nBlood Bank Management System\n";
        cout << "1. Add Donor\n";
        cout << "2. View Donors\n";
        cout << "3. Search by Name\n";
        cout << "4. Search by Blood Group\n";
        cout << "5. Display Blood Group Units\n";
        cout << "6. Exit\n";
    }

    void handleUserInput() {
        int choice;
        string searchName, searchBloodGroup, filterDate;

        do {
            displayMainMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addDonor();
                    break;
                case 2:
                    {
                        cout << "Enter date to filter (Leave empty to show all): ";
                        cin.ignore();
                        getline(cin, filterDate);
                        vector<Donor> donors;
                        loadDatabase(donors);
                        displayDonors(donors, filterDate);
                    }
                    break;
                case 3:
                    cout << "Enter donor name to search: ";
                    cin.ignore();
                    getline(cin, searchName);
                    searchByNameAndDisplay(searchName);
                    break;
                case 4:
                    cout << "Enter blood group to search: ";
                    cin.ignore();
                    getline(cin, searchBloodGroup);
                    searchByBloodGroupAndDisplay(searchBloodGroup);
                    break;
                case 5:
                    displayBloodGroupUnits();
                    break;
                case 6:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            }
        } while (choice != 6);
    }
};

int main() {
    BloodBank bloodBank;
    bloodBank.handleUserInput();

    return 0;
}