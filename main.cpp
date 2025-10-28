#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "hashtable.hpp"
#include "item.hpp"

using namespace std;

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, HashTable<string, AmazonItem>& id_table, HashTable<string, AmazonItem>& cat_table)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
        const AmazonItem* target = id_table.Find(line.substr(line.find("find") + 5));

        if (target == nullptr) {
            cout << "Inventory/Product not found" << endl;
        }
        else {
            target->print();
        }
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        string category = line.substr(line.find("ry") + 3);
        const AmazonItem* target = cat_table.Find(category);
        if (target == nullptr) {
            cout << "Invalid Category" << endl;
        }
        else {
            cout << "Items at category \"" << category << "\" :" << endl; 
            cat_table.PrintAtKey(category);
        }
    }
}

void fillIdTable(vector<AmazonItem>& items, HashTable<string, AmazonItem>& id_table)
{
    for (auto& item : items) {
        if (id_table.Insert(item.getId(), item)); // inserts each item to the table, using id as the key
    }
}

void fillCatTable(vector<AmazonItem>& items, HashTable<string, AmazonItem>& cat_table)
{
    for (int i = 0; i < (int)items.size(); i++) {
        for (auto category : items.at(i).getCategories()) {
            if (category == "NA") {
                break;
            }
            else {
                cat_table.Insert(category, items.at(i));
            }
        }
    }
}

void bootStrap(HashTable<string, AmazonItem>& id_table, HashTable<string, AmazonItem>& cat_table)
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";

    vector<AmazonItem> items;

    fstream in;
    in.open("data.csv");
    string temp;
    getline(in, temp); // read the header line of the csv file

    while (getline(in, temp)) {
        items.push_back(AmazonItem(temp)); // fills a vector with items, to be used to correctly fill the hash tables 
    }

    in.close();

    fillIdTable(items, id_table); // fills a hashtable with ids as keys
    fillCatTable(items, cat_table); // fills a hashtable categories as keys
}

int main(int argc, char const *argv[])
{
    string line;
    HashTable<string, AmazonItem> item_ids(2368); // based on the fact that each id is 32 chars, ranging from 0 to z, the max value is 3904, and min is 1536, so a table the size of max-min is all that is necessary
    HashTable<string, AmazonItem> item_categories(50); // I'm not going to count the number of categories so I'll just guess 50

    bootStrap(item_ids, item_categories);
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line, item_ids, item_categories);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
