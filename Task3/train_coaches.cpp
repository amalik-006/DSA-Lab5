// Task: 03
// Train Coach Navigation System

#include <iostream>
#include <string>

using namespace std;

// Node representing one train coach
struct Coach
{
    int number;
    string type;
    int capacity;
    int passengers;

    Coach* next;
    Coach* prev;

    Coach(int coachNumber,
          const string& coachType,
          int coachCapacity,
          int coachPassengers)
    {
        number = coachNumber;
        type = coachType;
        capacity = coachCapacity;
        passengers = coachPassengers;

        // A new node initially points to itself
        next = this;
        prev = this;
    }
};

// Circular Doubly Linked List for the train
class Train
{
private:
    Coach* head;
    Coach* current;

public:

    Train()
    {
        head = nullptr;
        current = nullptr;
    }

    // Destructor prevents memory leaks
    ~Train()
    {
        clearAll();
    }

    // Copying would cause a double delete
    Train(const Train&) = delete;
    Train& operator=(const Train&) = delete;

    // Check if a coach number is already used
    bool coachExists(int number) const
    {
        return findCoach(number) != nullptr;
    }

    // 1. Add Coach
    // Add a coach at the end of the train
    void addCoach(int number,
                  const string& type,
                  int capacity,
                  int passengers)
    {
        Coach* newCoach = new Coach(number, type, capacity, passengers);

        // Empty train
        if (head == nullptr)
        {
            head = newCoach;
            current = newCoach;
            return;
        }

        // Last node is head->prev
        Coach* tail = head->prev;

        newCoach->next = head;
        newCoach->prev = tail;

        tail->next = newCoach;
        head->prev = newCoach;
    }

    // 2. Insert Coach After a Specified Coach
    void insertCoach(int afterNumber,
                     int number,
                     const string& type,
                     int capacity,
                     int passengers)
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Coach* target = findCoach(afterNumber);

        if (target == nullptr)
        {
            cout << "Coach " << afterNumber
                 << " not found.\n";
            return;
        }

        Coach* newCoach = new Coach(number, type, capacity, passengers);
        Coach* nextCoach = target->next;

        newCoach->prev = target;
        newCoach->next = nextCoach;

        target->next = newCoach;
        nextCoach->prev = newCoach;

        cout << "Coach inserted successfully.\n";
    }

    // 3. Remove Coach by Number
    void removeCoach(int number)
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Coach* coach = findCoach(number);

        if (coach == nullptr)
        {
            cout << "Coach " << number
                 << " not found.\n";
            return;
        }

        removeNode(coach);
        cout << "Coach removed successfully.\n";
    }

    // 4. Move Forward
    void moveForward()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        current = current->next;
    }

    // 5. Move Backward
    void moveBackward()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        current = current->prev;
    }

    // 6. Display Train Clockwise
    void displayClockwise() const
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        cout << "\n===== Train Clockwise =====\n";

        Coach* temp = head;

        do
        {
            displayCoach(temp);

            temp = temp->next;

        } while (temp != head);
    }

    // 7. Display Train Anti-clockwise
    void displayAntiClockwise() const
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        cout << "\n===== Train Anti-clockwise =====\n";

        // Start from the last coach
        Coach* start = head->prev;
        Coach* temp = start;

        do
        {
            displayCoach(temp);

            temp = temp->prev;

        } while (temp != start);
    }

    // 8. Search Coach by Number
    void searchCoach(int number) const
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Coach* coach = findCoach(number);

        if (coach == nullptr)
        {
            cout << "Coach " << number
                 << " not found.\n";
            return;
        }

        cout << "\n===== Coach Found =====\n";
        displayCoach(coach);
    }

    // 9. Find Maximum Available Capacity
    void findMaxAvailableCapacity() const
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Coach* best = head;
        Coach* temp = head->next;

        while (temp != head)
        {
            if (availableSeats(temp) > availableSeats(best))
            {
                best = temp;
            }

            temp = temp->next;
        }

        cout << "\n===== Maximum Available Capacity =====\n";
        displayCoach(best);
    }

    // 10. Display Current Coach
    void displayCurrentCoach() const
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        cout << "\n===== Current Coach =====\n";
        displayCoach(current);
    }

    // 11. Reverse Train Direction
    // Swaps next and prev of every node, no data is copied
    void reverseTrain()
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Coach* temp = head;

        do
        {
            // After the swap, the old next is reached through prev
            Coach* oldNext = temp->next;

            temp->next = temp->prev;
            temp->prev = oldNext;

            temp = oldNext;

        } while (temp != head);

        // Old last coach is now the first coach
        head = head->next;

        cout << "Train direction reversed.\n";
    }

private:

    // Number of empty seats in a coach
    static int availableSeats(const Coach* coach)
    {
        return coach->capacity - coach->passengers;
    }

    // Display one coach
    static void displayCoach(const Coach* coach)
    {
        cout << "Coach Number: " << coach->number << '\n';
        cout << "Coach Type: " << coach->type << '\n';
        cout << "Passenger Capacity: " << coach->capacity << '\n';
        cout << "Current Passengers: " << coach->passengers << '\n';
        cout << "Available Seats: " << availableSeats(coach) << '\n';
        cout << "-------------------------\n";
    }

    // Find a coach by number
    Coach* findCoach(int number) const
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        Coach* temp = head;

        do
        {
            if (temp->number == number)
            {
                return temp;
            }

            temp = temp->next;

        } while (temp != head);

        return nullptr;
    }

    // Remove a specific node
    void removeNode(Coach* node)
    {
        // Only one node exists
        if (node->next == node)
        {
            delete node;
            head = nullptr;
            current = nullptr;
            return;
        }

        // If removing head, next becomes head
        if (node == head)
        {
            head = node->next;
        }

        // If removing current, next becomes current
        if (node == current)
        {
            current = node->next;
        }

        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node;
    }

    // Delete all nodes
    void clearAll()
    {
        if (head == nullptr)
        {
            return;
        }

        Coach* start = head;
        Coach* temp = head->next;

        while (temp != start)
        {
            Coach* nextCoach = temp->next;

            delete temp;

            temp = nextCoach;
        }

        delete start;
        head = nullptr;
        current = nullptr;
    }
};

// Read an integer and ask again on invalid input
int readInt(const string& message)
{
    int value;

    cout << message;

    while (!(cin >> value))
    {
        if (cin.eof())
        {
            return 0;
        }

        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Invalid input. Try again: ";
    }

    cin.ignore(10000, '\n');

    return value;
}

// Read the details of one coach
// Returns false if the coach number already exists
bool readCoach(const Train& train,
               int& number,
               string& type,
               int& capacity,
               int& passengers)
{
    number = readInt("Enter Coach Number: ");

    if (train.coachExists(number))
    {
        cout << "Coach " << number
             << " already exists.\n";
        return false;
    }

    cout << "Enter Coach Type: ";
    getline(cin, type);

    capacity = readInt("Enter Passenger Capacity: ");

    while (capacity <= 0 && !cin.eof())
    {
        cout << "Capacity must be greater than 0.\n";
        capacity = readInt("Enter Passenger Capacity: ");
    }

    passengers = readInt("Enter Current Passengers: ");

    while ((passengers < 0 || passengers > capacity) && !cin.eof())
    {
        cout << "Passengers must be between 0 and " << capacity << ".\n";
        passengers = readInt("Enter Current Passengers: ");
    }

    return true;
}

void displayMenu()
{
    cout << "\n===== Train Coach Navigation System =====\n";
    cout << "1. Add Coach\n";
    cout << "2. Insert Coach\n";
    cout << "3. Remove Coach\n";
    cout << "4. Move Forward\n";
    cout << "5. Move Backward\n";
    cout << "6. Display Train Clockwise\n";
    cout << "7. Display Train Anti-clockwise\n";
    cout << "8. Search Coach\n";
    cout << "9. Find Maximum Available Capacity\n";
    cout << "10. Display Current Coach\n";
    cout << "11. Reverse Train Direction\n";
    cout << "0. Exit\n";
}

int main()
{
    Train train;

    int numberOfCoaches = readInt("Enter number of coaches: ");

    // Prevent negative input
    while (numberOfCoaches < 0)
    {
        cout << "Number of coaches cannot be negative.\n";
        numberOfCoaches = readInt("Enter number of coaches: ");
    }

    // Input details of each coach
    for (int i = 0; i < numberOfCoaches; i++)
    {
        int number;
        string type;
        int capacity;
        int passengers;

        cout << "\nCoach " << i + 1 << '\n';

        if (!readCoach(train, number, type, capacity, passengers))
        {
            i--;
            continue;
        }

        train.addCoach(number, type, capacity, passengers);
    }

    int choice;

    do
    {
        displayMenu();
        choice = readInt("Enter choice: ");

        int number;
        string type;
        int capacity;
        int passengers;

        switch (choice)
        {
            case 1:
                if (readCoach(train, number, type, capacity, passengers))
                {
                    train.addCoach(number, type, capacity, passengers);
                }
                break;

            case 2:
            {
                int afterNumber = readInt("Insert after Coach Number: ");

                if (readCoach(train, number, type, capacity, passengers))
                {
                    train.insertCoach(afterNumber, number, type,
                                      capacity, passengers);
                }
                break;
            }

            case 3:
                train.removeCoach(readInt("Enter Coach Number to remove: "));
                break;

            case 4:
                train.moveForward();
                train.displayCurrentCoach();
                break;

            case 5:
                train.moveBackward();
                train.displayCurrentCoach();
                break;

            case 6:
                train.displayClockwise();
                break;

            case 7:
                train.displayAntiClockwise();
                break;

            case 8:
                train.searchCoach(readInt("Enter Coach Number to search: "));
                break;

            case 9:
                train.findMaxAvailableCapacity();
                break;

            case 10:
                train.displayCurrentCoach();
                break;

            case 11:
                train.reverseTrain();
                break;

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0 && !cin.eof());

    return 0;
}