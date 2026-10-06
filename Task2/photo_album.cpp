// Task: 02
// Circular Photo Album

#include <iostream>
#include <string>

using namespace std;

// Node representing one photo
struct Photo
{
    int id;
    string name;
    string dateTaken;
    string location;

    Photo* next;
    Photo* prev;

    Photo(int photoId,
          const string& photoName,
          const string& photoDate,
          const string& photoLocation)
    {
        id = photoId;
        name = photoName;
        dateTaken = photoDate;
        location = photoLocation;

        // A new node initially points to itself
        next = this;
        prev = this;
    }
};

// Circular Doubly Linked List for the photo album
class PhotoAlbum
{
private:
    Photo* head;
    Photo* current;

public:

    PhotoAlbum()
    {
        head = nullptr;
        current = nullptr;
    }

    // Destructor prevents memory leaks
    ~PhotoAlbum()
    {
        clearAll();
    }

    // Copying would cause a double delete
    PhotoAlbum(const PhotoAlbum&) = delete;
    PhotoAlbum& operator=(const PhotoAlbum&) = delete;

    // Check if a photo ID is already used
    bool idExists(int id) const
    {
        return findPhoto(id) != nullptr;
    }

    // 1. Add Photo
    // Insert at the end of the circular doubly linked list
    void addPhoto(int id,
                  const string& name,
                  const string& dateTaken,
                  const string& location)
    {
        Photo* newPhoto = new Photo(id, name, dateTaken, location);

        // Empty album
        if (head == nullptr)
        {
            head = newPhoto;
            current = newPhoto;
            return;
        }

        // Last node is head->prev
        Photo* tail = head->prev;

        newPhoto->next = head;
        newPhoto->prev = tail;

        tail->next = newPhoto;
        head->prev = newPhoto;
    }

    // 2. Insert Photo After Current
    void insertAfterCurrent(int id,
                            const string& name,
                            const string& dateTaken,
                            const string& location)
    {
        // Empty album
        if (current == nullptr)
        {
            addPhoto(id, name, dateTaken, location);
            return;
        }

        Photo* newPhoto = new Photo(id, name, dateTaken, location);
        Photo* nextPhoto = current->next;

        newPhoto->prev = current;
        newPhoto->next = nextPhoto;

        current->next = newPhoto;
        nextPhoto->prev = newPhoto;
    }

    // 3. Remove Photo by ID
    void removePhoto(int id)
    {
        if (head == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        Photo* photo = findPhoto(id);

        if (photo == nullptr)
        {
            cout << "Photo with ID " << id
                 << " not found.\n";
            return;
        }

        removeNode(photo);
        cout << "Photo removed successfully.\n";
    }

    // 4. Remove Current Photo
    void removeCurrentPhoto()
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        removeNode(current);
        cout << "Current photo removed successfully.\n";
    }

    // 5. Move Next
    void moveNext()
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        current = current->next;
    }

    // 6. Move Previous
    void movePrevious()
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        current = current->prev;
    }

    // 7. Display Album Forward
    void displayForward() const
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        cout << "\n===== Album Forward =====\n";

        Photo* temp = current;

        do
        {
            displayPhoto(temp);

            temp = temp->next;

        } while (temp != current);
    }

    // 8. Display Album Backward
    void displayBackward() const
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        cout << "\n===== Album Backward =====\n";

        Photo* temp = current;

        do
        {
            displayPhoto(temp);

            temp = temp->prev;

        } while (temp != current);
    }

    // 9. Search Photo by ID
    void searchPhoto(int id) const
    {
        if (head == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        Photo* photo = findPhoto(id);

        if (photo == nullptr)
        {
            cout << "Photo with ID " << id
                 << " not found.\n";
            return;
        }

        cout << "\n===== Photo Found =====\n";
        displayPhoto(photo);
    }

    // 10. Count Photos
    void countPhotos() const
    {
        if (head == nullptr)
        {
            cout << "Total photos: 0\n";
            return;
        }

        int count = 0;

        Photo* temp = head;

        do
        {
            count++;
            temp = temp->next;

        } while (temp != head);

        cout << "Total photos: " << count << '\n';
    }

    // Display currently selected photo
    void displayCurrentPhoto() const
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        cout << "\n===== Current Photo =====\n";
        displayPhoto(current);
    }

private:

    // Display one photo
    static void displayPhoto(const Photo* photo)
    {
        cout << "Photo ID: " << photo->id << '\n';
        cout << "Photo Name: " << photo->name << '\n';
        cout << "Date Taken: " << photo->dateTaken << '\n';
        cout << "Location: " << photo->location << '\n';
        cout << "-------------------------\n";
    }

    // Find a photo by ID
    Photo* findPhoto(int id) const
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        Photo* temp = head;

        do
        {
            if (temp->id == id)
            {
                return temp;
            }

            temp = temp->next;

        } while (temp != head);

        return nullptr;
    }

    // Remove a specific node
    void removeNode(Photo* node)
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

        Photo* start = head;
        Photo* temp = head->next;

        while (temp != start)
        {
            Photo* nextPhoto = temp->next;

            delete temp;

            temp = nextPhoto;
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

// Read the details of one photo
// Returns false if the ID already exists
bool readPhoto(const PhotoAlbum& album,
               int& id,
               string& name,
               string& dateTaken,
               string& location)
{
    id = readInt("Enter Photo ID: ");

    if (album.idExists(id))
    {
        cout << "A photo with ID " << id
             << " already exists.\n";
        return false;
    }

    cout << "Enter Photo Name: ";
    getline(cin, name);

    cout << "Enter Date Taken: ";
    getline(cin, dateTaken);

    cout << "Enter Location: ";
    getline(cin, location);

    return true;
}

void displayMenu()
{
    cout << "\n===== Circular Photo Album =====\n";
    cout << "1. Add Photo\n";
    cout << "2. Insert Photo After Current\n";
    cout << "3. Remove Photo by ID\n";
    cout << "4. Remove Current Photo\n";
    cout << "5. Move Next\n";
    cout << "6. Move Previous\n";
    cout << "7. Display Album Forward\n";
    cout << "8. Display Album Backward\n";
    cout << "9. Search Photo\n";
    cout << "10. Count Photos\n";
    cout << "11. Display Current Photo\n";
    cout << "0. Exit\n";
}

int main()
{
    PhotoAlbum album;

    int numberOfPhotos = readInt("Enter number of photos: ");

    // Prevent negative input
    while (numberOfPhotos < 0)
    {
        cout << "Number of photos cannot be negative.\n";
        numberOfPhotos = readInt("Enter number of photos: ");
    }

    // Input details of each photo
    for (int i = 0; i < numberOfPhotos; i++)
    {
        int id;
        string name;
        string dateTaken;
        string location;

        cout << "\nPhoto " << i + 1 << '\n';

        if (!readPhoto(album, id, name, dateTaken, location))
        {
            i--;
            continue;
        }

        album.addPhoto(id, name, dateTaken, location);
    }

    int choice;

    do
    {
        displayMenu();
        choice = readInt("Enter choice: ");

        int id;
        string name;
        string dateTaken;
        string location;

        switch (choice)
        {
            case 1:
                if (readPhoto(album, id, name, dateTaken, location))
                {
                    album.addPhoto(id, name, dateTaken, location);
                }
                break;

            case 2:
                if (readPhoto(album, id, name, dateTaken, location))
                {
                    album.insertAfterCurrent(id, name, dateTaken, location);
                }
                break;

            case 3:
                album.removePhoto(readInt("Enter Photo ID to remove: "));
                break;

            case 4:
                album.removeCurrentPhoto();
                break;

            case 5:
                album.moveNext();
                album.displayCurrentPhoto();
                break;

            case 6:
                album.movePrevious();
                album.displayCurrentPhoto();
                break;

            case 7:
                album.displayForward();
                break;

            case 8:
                album.displayBackward();
                break;

            case 9:
                album.searchPhoto(readInt("Enter Photo ID to search: "));
                break;

            case 10:
                album.countPhotos();
                break;

            case 11:
                album.displayCurrentPhoto();
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