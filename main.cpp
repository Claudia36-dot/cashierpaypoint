#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <windows.h>

using namespace std;

class Item
{
private:
    float price;
    string name;
    int quantity;
    float total;

public:
    Item(string n, float p, int q)
    {
        name = n;
        price = p;
        quantity = q;
        total = price * quantity;
    }

    string getName(){ return name; }
    float getPrice(){ return price; }
    int getQuantity(){ return quantity; }
    float getTotal(){ return total; }
};

class Teller
{
private:
    vector<Item> Items;

    float getSystemPrice(string name)
    {
        for (char &c : name)
        {
            c = tolower(c);
        }

        if (name == "rice")
            return 10.00;
        else if (name == "milk")
            return 15.00;
        else if (name == "water")
            return 5.00;
        else if (name == "sugar")
            return 5.00;
        else if (name == "bread")
            return 30.00;
        else if (name == "butter")
            return 20.00;
        else if (name == "egg")
            return 3.00;
        else if (name == "margarine")
            return 12.00;
        else
            return -1;
    }

public:

    void receiveItems()
    {
        string name;
        float price;
        int quantity;
        char choice;

        do
        {
            cout << "\nEnter item name: ";
            getline(cin >> ws, name);

            price = getSystemPrice(name);

            while (price == -1)
            {
                cout << "Item not found. Enter a valid item: ";
                getline(cin >> ws, name);

                price = getSystemPrice(name);
            }

            cout << "Enter quantity: ";
            cin >> quantity;

            Items.push_back(Item(name, price, quantity));

            cout << "\nDoes the customer have another item? (y/n): ";
            cin >> choice;

        } while (choice == 'y' || choice == 'Y');
    }


    void displayReceipt()
    {
        float grandTotal = 0;

        cout << fixed << setprecision(2);

        cout << "\n\n========== CUSTOMER RECEIPT ==========\n\n";

        cout << left
             << setw(6) << "No."
             << setw(20) << "Item"
             << setw(12) << "Price"
             << setw(10) << "Qty"
             << setw(12) << "Total"
             << endl;

        cout << "------------------------------------------------------------"
             << endl;

        for (size_t i = 0; i < Items.size(); i++)
        {
            cout << left
                 << setw(6) << i + 1
                 << setw(20) << Items[i].getName()
                 << setw(12) << Items[i].getPrice()
                 << setw(10) << Items[i].getQuantity()
                 << setw(12) << Items[i].getTotal()
                 << endl;

            grandTotal += Items[i].getTotal();

            cout << endl;
        }

        cout << "------------------------------------------------------------"
             << endl;

        cout << "Grand Total: GH " << grandTotal << endl;

        cout << "\n=======================================\n";
    }


    void printReceipt()
    {
        float grandTotal = 0;

        ofstream receipt("receipt.txt");

        if (!receipt)
        {
            cout << "Error: Could not create receipt." << endl;
            return;
        }

        receipt << fixed << setprecision(2);

        receipt << "========================================\n";
        receipt << "            CUSTOMER RECEIPT            \n";
        receipt << "========================================\n\n";

        receipt << left
                << setw(6) << "No."
                << setw(20) << "Item"
                << setw(12) << "Price"
                << setw(10) << "Qty"
                << setw(12) << "Total"
                << "\n";

        receipt << "------------------------------------------------------------\n";

        for (size_t i = 0; i < Items.size(); i++)
        {
            receipt << left
                    << setw(6) << i + 1
                    << setw(20) << Items[i].getName()
                    << setw(12) << Items[i].getPrice()
                    << setw(10) << Items[i].getQuantity()
                    << setw(12) << Items[i].getTotal()
                    << "\n\n";

            grandTotal += Items[i].getTotal();
        }

        receipt << "------------------------------------------------------------\n";
        receipt << "Grand Total: GH " << grandTotal << "\n\n";

        receipt << "========================================\n";
        receipt << "              Thank you!\n";
        receipt << "========================================\n";

        receipt.close();

        cout << "\nPrinting receipt...\n";

        system("notepad.exe /p receipt.txt");

        Sleep(5000);

        remove("receipt.txt");

        cout << "Receipt sent to printer successfully.\n";
    }
};


int main()
{
    Teller teller;

    teller.receiveItems();

    cout << "\n\nFINAL CUSTOMER LIST";
    teller.displayReceipt();
    // the customer's list
    cout << "\nPress Enter to print the receipt...";

    cin.ignore();
    cin.get();

    teller.printReceipt();

    return 0;
}
