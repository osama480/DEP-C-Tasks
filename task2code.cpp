#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Define the Contact class
class Contact {
public:
    string name;
    string phoneNumber;

    Contact(string n, string p) : name(n), phoneNumber(p) {}
};

// Function to add a contact
void addContact(vector<Contact>& contacts) {
    string name, phoneNumber;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    contacts.push_back(Contact(name, phoneNumber));
    cout << "Contact added successfully.\n";
}

// Function to view all contacts
void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to display.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". " << contacts[i].name << " - " << contacts[i].phoneNumber << "\n";
    }
}

// Function to delete a contact
void deleteContact(vector<Contact>& contacts) {
    int index;
    cout << "Enter the number of the contact to delete: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully.\n";
}

// Display the menu
void displayMenu() {
    cout << "\nContact Management System\n";
    cout << "1. Add Contact\n";
    cout << "2. View Contacts\n";
    cout << "3. Delete Contact\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Contact> contacts;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                deleteContact(contacts);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
