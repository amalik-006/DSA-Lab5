// Task: 01 
// Browser Tabs Management System 

#include <iostream>
#include <string>

using namespace std;

// Node representing one browser tab
struct Tab
{
    int id;
    string title;
    string url;

    Tab* next;
    Tab* prev;

    Tab(int tabId, const string& tabTitle, const string& tabUrl)
    {
        id = tabId;
        title = tabTitle;
        url = tabUrl;

        next = this;
        prev = this;
    }
};

// Circular Doubly Linked List for browser tabs
class BrowserTabManager
{
private:
    Tab* current;

public:
    BrowserTabManager()
    {
        current = nullptr;
    }

    // Destructor releases all dynamically allocated nodes
    ~BrowserTabManager()
    {
        clearAll();
    }

    // 1. Open a new tab after the current tab
    void openNewTab(int id, const string& title, const string& url)
    {
        Tab* newTab = new Tab(id, title, url);

        // Empty list
        if (current == nullptr)
        {
            current = newTab;
            return;
        }

        // Insert after current
        Tab* nextTab = current->next;

        newTab->next = nextTab;
        newTab->prev = current;

        current->next = newTab;
        nextTab->prev = newTab;
    }

    // 2. Close the current tab
    void closeCurrentTab()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        // Only one node exists
        if (current->next == current)
        {
            delete current;
            current = nullptr;
            return;
        }

        Tab* oldCurrent = current;
        Tab* nextTab = current->next;

        oldCurrent->prev->next = oldCurrent->next;
        oldCurrent->next->prev = oldCurrent->prev;

        current = nextTab;

        delete oldCurrent;
    }

    // 3. Move to next tab
    void moveNext()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        current = current->next;
    }

    // 4. Move to previous tab
    void movePrevious()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        current = current->prev;
    }

    // 5. Display current tab
    void displayCurrentTab() const
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\nCurrent Tab\n";
        cout << "ID: " << current->id << '\n';
        cout << "Title: " << current->title << '\n';
        cout << "URL: " << current->url << '\n';
    }

    // 6. Display all tabs forward
    void displayAllForward() const
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\nTabs Forward\n";

        Tab* temp = current;

        do
        {
            cout << "ID: " << temp->id
                 << " | Title: " << temp->title
                 << " | URL: " << temp->url << '\n';

            temp = temp->next;

        } while (temp != current);
    }

    // 7. Display all tabs backward
    void displayAllBackward() const
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\nTabs Backward\n";

        Tab* temp = current;

        do
        {
            cout << "ID: " << temp->id
                 << " | Title: " << temp->title
                 << " | URL: " << temp->url << '\n';

            temp = temp->prev;

        } while (temp != current);
    }

    // 8. Search tab by ID
    void searchTab(int id) const
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        Tab* temp = current;

        do
        {
            if (temp->id == id)
            {
                cout << "\nTab Found\n";
                cout << "ID: " << temp->id << '\n';
                cout << "Title: " << temp->title << '\n';
                cout << "URL: " << temp->url << '\n';
                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Tab with ID " << id << " not found.\n";
    }

private:

    // Delete every node safely
    void clearAll()
    {
        if (current == nullptr)
        {
            return;
        }

        Tab* start = current;
        Tab* temp = current->next;

        while (temp != start)
        {
            Tab* nextTab = temp->next;
            delete temp;
            temp = nextTab;
        }

        delete start;
        current = nullptr;
    }
};

int main()
{
    BrowserTabManager browser;

    // Opening tabs
    browser.openNewTab(1, "Google", "https://www.google.com");
    browser.openNewTab(2, "YouTube", "https://www.youtube.com");
    browser.openNewTab(3, "GitHub", "https://github.com");

    cout << "Initial tabs:";
    browser.displayAllForward();

    // Current tab movement
    cout << "\nMoving to next tab:";
    browser.moveNext();
    browser.displayCurrentTab();

    cout << "\nMoving to previous tab:";
    browser.movePrevious();
    browser.displayCurrentTab();

    // Search
    cout << "\nSearching for Tab ID 2:";
    browser.searchTab(2);

    // Backward traversal
    browser.displayAllBackward();

    // Close current tab
    cout << "\nClosing current tab...";
    browser.closeCurrentTab();

    browser.displayAllForward();

    return 0;
}