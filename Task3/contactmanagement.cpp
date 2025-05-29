#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

// Function to load contacts from file
vector<Contact> loadContacts() {
    vector<Contact> contacts;
    ifstream inFile("contacts.txt");
    Contact c;
    while (getline(inFile, c.name) && getline(inFile, c.phone) && getline(inFile, c.email)) {
        contacts.push_back(c);
    }
    inFile.close();
    return contacts;
}

// Function to save contacts to file
void saveContacts(const vector<Contact>& contacts) {
    ofstream outFile("contacts.txt");
    for (const auto& c : contacts) {
        outFile << c.name << endl;
        outFile << c.phone << endl;
        outFile << c.email << endl;
    }
    outFile.close();
}

// Function to display contacts
void displayContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found.\n";
        return;
    }

    cout << left << setw(5) << "No." << setw(20) << "Name" << setw(15) << "Phone" << "Email" << endl;
    cout << "-------------------------------------------------------------\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << setw(5) << i + 1
             << setw(20) << contacts[i].name
             << setw(15) << contacts[i].phone
             << contacts[i].email << endl;
    }
}

// Function to add a new contact
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phone);
    cout << "Enter email: ";
    getline(cin, newContact.email);

    contacts.push_back(newContact);
    saveContacts(contacts);
    cout << "Contact added successfully!\n";
}

// Function to edit a contact
void editContact(vector<Contact>& contacts) {
    displayContacts(contacts);
    if (contacts.empty()) return;

    int index;
    cout << "Enter contact number to edit: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    Contact& c = contacts[index - 1];
    cin.ignore();
    cout << "Enter new name (" << c.name << "): ";
    getline(cin, c.name);
    cout << "Enter new phone (" << c.phone << "): ";
    getline(cin, c.phone);
    cout << "Enter new email (" << c.email << "): ";
    getline(cin, c.email);

    saveContacts(contacts);
    cout << "Contact updated successfully!\n";
}

// Function to delete a contact
void deleteContact(vector<Contact>& contacts) {
    displayContacts(contacts);
    if (contacts.empty()) return;

    int index;
    cout << "Enter contact number to delete: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    saveContacts(contacts);
    cout << "Contact deleted successfully!\n";
}

int main() {
    vector<Contact> contacts = loadContacts();
    int choice;

    do {
        cout << "\n===== Contact Management System =====\n";
        cout << "1. View Contacts\n";
        cout << "2. Add Contact\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayContacts(contacts); break;
            case 2: addContact(contacts); break;
            case 3: editContact(contacts); break;
            case 4: deleteContact(contacts); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
