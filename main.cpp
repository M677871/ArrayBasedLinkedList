/*-- main.cpp --------------------------------------------------------------

  This program provides an interactive, menu-driven interface to test and
  demonstrate the functionality of the ArrayLinkedList<T,N> class backed
  by a fixed-size NodePool<T,N>. Users can insert, remove, search, sort,
  and display elements without dynamic memory allocation.

  Usage:
    • The list capacity is determined by the template parameter N (here N=5).
    • Two lists (`list` and `list2`) share the same NodePool.
    • Menu options 1–8:  various insert operations (front, back, after/before a specific value, etc.).
    • Menu options 9–14: various remove operations (front, back, value, etc.).
    • Menu options 15–16: sorting in ascending or descending order.
    • Menu options 17–24: other operations (display, find, reverse, size, etc.).
    • Menu option   25: exit the program.

  Precondition:  None (NodePool and lists initialize to empty state).
  Postcondition: All allocations and deallocations occur within the fixed
                 pool; program exits cleanly when user selects “25. Exit”.

-------------------------------------------------------------------------*/

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
        cout << "\n=== Linked List Menu ==="
             << "\n\n=== Insert Operations ==="
             << "\n1. Insert At Front"
             << "\n2. Insert At Back"
             << "\n3. Insert After A Specific Value"
             << "\n4. Insert Before A Specific Value"
             << "\n5. Insert In Ascending Order"
             << "\n6. Insert In Descending Order"
             << "\n7. Insert At A Specific Position" // option to insert the value between 0 and the size
             << "\n8. Insert Back At A Position" // the value is always inserted at the back by choosing one of the free slots

             << "\n\n=== Remove Operations ==="
             << "\n9. Remove Value"
             << "\n10. Remove At Position"
             << "\n11. Remove Duplicates"
             << "\n12. Remove All Ocurrences Of A Value"
             << "\n13. Remove After A Specific Value"
             << "\n14. Remove Before A Specific Value"

             << "\n\n=== Sorting Operations ==="
             << "\n15. Sort In Ascending Order"
             << "\n16. Sort In Descending Order"

             << "\n\n=== Other Operations ==="
             << "\n17. Display List"
             << "\n18. Find Value"
             << "\n19. Reverse List"
             << "\n20. Size"
             << "\n21. Clear List"
             << "\n22. Create/Append To Second List"
             << "\n23. Concatenate With Second List (+=)"
             << "\n24. Display Free/Used Slots"

             << "\n\n=== Exit ==="
             << "\n25. Exit"
             << "\n\nSelect an option: ";

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
            cout << "Value to insert after: ";
            getline(cin, key);
            cout << "New Value: ";
            getline(cin, value);
            result = list.insertAfter(key, value);
            cout << (result ? "Inserted" : "Key not found") << endl;
            break;
        case 4:
            cout << "Key: ";
            if (list.isEmpty())
            {
                cout << "List is empty" << endl;
                break;
            }
            cout << "the keys are :" << list << endl;
            cout << "Value to insert before: ";
            getline(cin, key);
            cout << "New Value: ";
            getline(cin, value);
            result = list.insertBefore(key, value);
            cout << (result ? "Inserted" : "Key not found") << endl;
            break;
        case 5:
            cout << "value to insert in ascending order: ";
            getline(cin, value);
            list.insertSorted(value);
            cout << "List after insertion: " << list;
            break;
        case 6:
            cout << "value to insert in descending order: ";
            getline(cin, value);
            list.insertSorted(value);
            cout << "List after insertion: " << list;
            break;
        case 7:
            if (pool.freeCount() == 0)
            {
                cout << "No free slots available. \n"
                     << endl;
            }
            else
            {
                cout << "choose a position  between 0 and " << pool.usedCount()  << endl;
               
            };

            cout << "Position: ";
            cin >> pos;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Value: ";
            getline(cin, value);
            result = list.insertAtPosition(pos, value);
            cout << (result ? "Inserted" : "Invalid position") << endl;
            break;
        case 8:
            if (pool.freeCount() == 0)
            {
                cout << "No free slots available. \n"
                     << endl;
            }
            else
            {
                cout << "Free slots: ";
                pool.displayFree(cout);
                cout << endl;
            };
            cout << "Position: ";
            cin >> pos;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Value: ";
            getline(cin, value);
            result = list.insertAt(pos, value);
            cout << (result ? "Inserted" : "Invalid position") << endl;
            break;
        case 9:
            if (list.isEmpty())
            {
                cout << "List is empty" << endl;
                break;
            }
            cout << "values: " << list << endl;
            cout << "Value to delete: ";
            getline(cin, value);
            result = list.removeValue(value);
            cout << (result ? "Removed" : "Value not found") << endl;
            break;
        case 10:
            if (pool.usedCount() == 0)
            {
                cout << "No used slots available. \n"
                     << endl;
                break;
            }
            cout << "Used slots: \n";
            pool.displayUsed(cout);
            cout << endl
                 << "Position: ";
            cin >> pos;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            result = list.removeSlot(pos);
            cout << (result ? "Removed" : "Invalid position") << endl;
            break;
        case 11:
            list.removeDuplicates();
            cout << "Duplicates removed: " << list;
            break;
        case 12:
            cout << "values: " << list << endl;
            cout << "Value to remove all occurrences: ";
            getline(cin, value);
            result = list.removeAllOccurrences(value);
            cout << (result ? "Removed all occurrences" : "Value not found") << endl;
            break;
        case 13:
            cout << "values: " << list << endl;
            cout << "Value to remove after: ";
            getline(cin, key);
            result = list.removeAfter(key);
            cout << (result ? "Removed" : "Deletion failed.") << endl;
            break;
        case 14:
            cout << "values: " << list << endl;
            cout << "Value to remove before: ";
            getline(cin, key);
            result = list.removeBefore(key);
            cout << (result ? "Removed" : "Deletion failed.") << endl;
            break;
        case 15:
            list.sortAscending();
            cout << "List in ascending order: " << list << endl;
            break;
        case 16:
            list.sortDescending();
            cout << "List in descending order: " << list << endl;
            break;
        case 17:
            cout << list;
            break;
        case 18:
            cout << "Value: ";
            getline(cin, value);
            pos = list.find(value);
            if (pos >= 0)
                cout << "Found at position " << pos << endl;
            else
                cout << "Not found" << endl;
            break;
        case 19:
            list.reverse();
            cout << "List reversed" << endl;
            break;
        case 20:
            cout << "Size: " << list.size() << endl;
            break;
        case 21:
            list.clear();
            cout << "List cleared" << endl;
            break;
        case 22:
            cout << "Enter value to append to second list: ";
            getline(cin, value);
            list2.insertBack(value);
            cout << "Second list now: " << list2;
            break;
        case 23:
            list += list2;
            cout << "After concatenation: " << list;
            break;
        case 24:
            if (pool.freeCount() == 0)
            {
                cout << "No free slots available. \n"
                     << endl
                     << "Used slots: ";
                pool.displayUsed(cout);
                break;
            }
            if (pool.usedCount() == 0)
            {
                cout << "No used slots available. \n"
                     << endl
                     << "Free slots: ";
                pool.displayFree(cout);
                break;
            }
            cout << "Free slots: \n";
            pool.displayFree(cout);
            cout << endl
                 << "Used slots: ";
            pool.displayUsed(cout);
            break;
        case 25:
            return 0;
        default:
            cout << "Invalid option" << endl;
        }
    }

    return 0;
}
