#include <cstdlib>
#include <iostream>
#include <string>
#include "NodePool.h"
#include "List.h"

using namespace std;

int main()
{
    NodePool<string, 5> pool;
    ArrayLinkedList<string, 5> list(pool);
    ArrayLinkedList<string, 5> list2(pool);

    while (true)
    {
        cout << "\n=== Linked List Menu ===\n"
             << "1. Insert Front\n"
             << "2. Insert Back\n"
             << "3. Insert After\n"
             << "4. Insert \n"
             << "5. Remove Value\n"
             << "6. Remove At Position\n"
             << "7. Display List\n"
             << "8. Find Value\n"
             << "9. Reverse List\n"
             << "10. Size\n"
             << "11. Clear List\n"
             << "12. Concatenate with second list (+=)\n"
             << "13. Create/Append to second list\n"
             << "14. Remove Duplicates\n"
             << "15. Insert in Sorted Order\n"
             << "16. Insert in Descending Order\n"
             << "17.sort in descending order\n"
             << "18. Sort in ascending order\n"
             <<"19. insert At a specific  position\n"
             << "20. Exit\n"
             << "Select an option: ";
        int choice;
        if (!(cin >> choice))
            break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string value, key;
        int pos;
        bool result;

        switch (choice)
        {
        case 1:
            cout << "Value: ";
            getline(cin, value);
            list.insertFront(value);
            break;
        case 2:
            cout << "Value: ";
            getline(cin, value);
            list.insertBack(value);
            break;
        case 3:
            cout << "Key: ";
            if (list.isEmpty())
            {
                cout << "List is empty" << endl;
                break;
            }
            cout << "the keys are :" << list << endl;
            getline(cin, key);
            cout << "New Value: ";
            getline(cin, value);
            result = list.insertAfter(key, value);
            cout << (result ? "Inserted" : "Key not found") << endl;
            break;
        case 4:
            cout << "Free slots: ";
            pool.displayFree(cout);
            cout << endl
                 << "Position: ";
            cin >> pos;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Value: ";
            getline(cin, value);
            result = list.insertAt(pos, value);
            cout << (result ? "Inserted" : "Invalid position") << endl;
            break;
        case 5:
            cout << "List : ";
            if (list.isEmpty())
            {
                cout << "List is empty" << endl;
                break;
            }
            cout << "the keys are :" << list << endl;
            getline(cin, value);
            result = list.removeValue(value);
            cout << (result ? "Removed" : "Value not found") << endl;
            break;
        case 6:
            if (list.isEmpty())
            {

                cout << "List is empty" << endl;
                break;
            }
            cout << "the Used positions are :" << endl;
            pool.displayUsed(cout);
            cout << endl
                 << "Position: ";
            cin >> pos;
            result = list.removeSlot(pos);
            cout << (result ? "Removed" : "Invalid position") << endl;
            break;
        case 7:
            cout << list;
            break;
        case 8:
            cout << "Value: ";
            getline(cin, value);
            pos = list.find(value);
            if (pos >= 0)
                cout << "Found at position " << pos << endl;
            else
                cout << "Not found" << endl;
            break;
        case 9:
            list.reverse();
            cout << "List reversed" << endl;
            break;
        case 10:
            cout << "Size: " << list.size() << endl;
            break;
        case 11:
            list.clear();
            cout << "List cleared" << endl;
            break;
        case 12:
            list += list2;
            cout << "After concatenation: " << list;
            break;
        case 13:
            cout << "Enter value to append to second list: ";
            getline(cin, value);
            list2.insertBack(value);
            cout << "Second list now: " << list2;
            break;
        case 14:
            list.removeDuplicates();
            cout << "Duplicates removed: " << list;
            break;
        case 15:
            cout << "value to insert in sorted order: ";
            getline(cin, value);
            list.insertSorted(value);
            cout << "List after insertion: " << list;
            break;
        case 16:
            cout << "value to insert in descending order: ";
            getline(cin, value);
            list.insertSorted(value);
            cout << "List after insertion: " << list;
            break;
        case 17:
            list.sortDescending();
            cout << "List in descending order: " << list << endl;
            break;
        case 18:
            list.sortAscending();
            cout << "List in ascending order: " << list << endl;
            break;
case 19:
            cout << "Position: ";
            cin >> pos;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Value: ";
            getline(cin, value);
            result = list.insertAtPosition(pos, value);
            cout << (result ? "Inserted" : "Invalid position") << endl;
            break;
        case 20:
            return 0;
        default:
            cout << "Invalid option" << endl;
        }
    }

    return 0;

 }

 
 
