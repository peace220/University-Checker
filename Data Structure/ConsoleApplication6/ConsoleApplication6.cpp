#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime> 
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace std::chrono;

void regcus(const string& username);
void displayCusMenu();
void displaycusunis();
void SearchCusUni(const string& username);
void displayFeedbacks(const string& username1);
void reguserLogin();
void displaySavedUnis(const string& username);
void registeruser();
void AdminLogin();
void normaluserprocess();
void adminfeedbackprocess();
void displayAdminFeedbacks();
void replyToFeedback();
void displayAdminReplies();
void moveBetweenFeedbacks();
void generateReport();
void SearchSortOption();
void SearchAlgoOption();
void financial_calc();
void modifier();
void deletereguser();
void sort_dec_unis();
void displayRegUsers();
void updateField(const string& username);
void updateLastField(const string& username);
void insertUser();
void insertFeedback();
void SaveRepliesToFile();
void SaveUnis();
string generateFeedbackId();


struct UniversityNode {
    string Rank;
    string Institution;
    string LocationCode;
    string Location;
    string ArScore;
    string ArRank;
    string ErScore;
    string ErRank;
    string FsrScore;
    string FsrRank;
    string CpfScore;
    string CpfRank;
    string IfrScore;
    string IfrRank;
    string IsrScore;
    string IsrRank;
    string IrnScore;
    string IrnRank;
    string GerScore;
    string GerRank;
    string ScoreScaled;

    UniversityNode* PreviousAddress;
    UniversityNode* NextAddress;

}*Unihead, * Unitail;
struct UserNode {
    string username, password, type, age, email, name;
    UserNode* Nextaddress;
}*Userhead;
struct FavUniNode {
    string reguserid, university, rank, location;
    FavUniNode* Nextaddress;
}*FavUnihead;
struct FeedbackNode {
    string id;
    string usrid;
    string universityName;
    string feedbackMessage;
    string date;
    string status;
    FeedbackNode* Nextaddress;
}; FeedbackNode* Feedbackhead = nullptr;

struct ReplyNode {
    string id;
    string universityName;
    string feedbackMessage;
    string date;
    string reply;
    ReplyNode* next;
}; ReplyNode* ReplyHead = nullptr;

string generateFeedbackId() {
    // Generate a random number between 1000 and 9999
    int randomId = rand() % 9000 + 1000;
    return to_string(randomId);
}
FeedbackNode* createFeedbackNode(const string& id, const string& usrid, const string& uniname, const string& msg, const string& date, const string& status) {
    FeedbackNode* newnode = new FeedbackNode;
    newnode->id = id;
    newnode->usrid = usrid;
    newnode->universityName = uniname;
    newnode->feedbackMessage = msg;
    newnode->date = date;
    newnode->status = status;
    newnode->Nextaddress = nullptr;
    return newnode;
}

void InsertFeedbackNode(const string& usrid, const string& uniname, const string& feedback) {
    string feedbackId = generateFeedbackId();

    time_t now = time(nullptr);
    string timestamp = ctime(&now);
    // Remove the newline character from the timestamp
    timestamp.erase(timestamp.length() - 1);
    string status = "Pending";

    FeedbackNode* newnode = createFeedbackNode(feedbackId, usrid, uniname, feedback, timestamp, status);
    if (Feedbackhead == nullptr) {
        Feedbackhead = newnode;
    }
    else {
        newnode->Nextaddress = Feedbackhead;
        Feedbackhead = newnode;
    }
}

void insertFeedback() {
    FeedbackNode* current = Feedbackhead;
    string filename = "feedback.txt";
    ofstream file("feedback.txt", ios::app);
    time_t now = time(nullptr);
    string timestamp = ctime(&now);
    // Remove the newline character from the timestamp
    timestamp.erase(timestamp.length() - 1);

    while (current != nullptr) {
        if (file.is_open()) {
            if (!current->id.empty() && !current->usrid.empty() && !current->universityName.empty() && !current->feedbackMessage.empty() && !current->date.empty() && !current->status.empty()) {

                file << current->id << "," << current->usrid << "," << current->universityName << "," << current->feedbackMessage << "," << current->date << "," << current->status << endl;
            }
            current = current->Nextaddress;
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }
    file.close();
    cout << "Feedback Inserted Successfully" << endl;
    cout << "------------------------" << endl;
}


ReplyNode* createReplyNode(const string& id, const string& uniName, const string& feedbackMsg, const string& dt, const string& reply) {
    ReplyNode* newNode = new ReplyNode;
    newNode->id = id;
    newNode->universityName = uniName;
    newNode->feedbackMessage = feedbackMsg;
    newNode->date = dt;
    newNode->reply = reply;
    newNode->next = nullptr;
    return newNode;
}

void addReplyNode(const string& Id, const string& uniName, const string& feedbackMsg, const string& dt, const string& reply) {

    ReplyNode* newNode = createReplyNode(Id, uniName, feedbackMsg, dt, reply);
    if (ReplyHead == nullptr) {
        ReplyHead = newNode;
    }
    else {
        newNode->next = ReplyHead;
        ReplyHead = newNode;
    }
}

void saveRepliesToFile() {
    ReplyNode* current = ReplyHead;
    string filename = "reply.txt";
    ofstream file("reply.txt", ios::app);
    time_t now = time(nullptr);
    string timestamp = ctime(&now);
    // Remove the newline character from the timestamp
    timestamp.erase(timestamp.length() - 1);

    while (current != nullptr) {
        if (file.is_open()) {

            file << current->id << "," << current->universityName << "," << current->feedbackMessage << "," << current->date << "," << current->reply << endl;
            current = current->next;
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }
    file.close();
    cout << "Feedback Replies Saved Successfully" << endl;
    cout << "-----------------------------------" << endl;
}

class NormalUsers {
    int size;
public:

    UniversityNode* createnewnode(string Rank, string Institution, string LocationCode, string Location, string ArScore, string ArRank,
        string ErScore, string ErRank, string FsrScore, string FsrRank, string CpfScore,
        string CpfRank, string IfrScore, string IfrRank, string IsrScore, string IsrRank, string IrnScore,
        string IrnRank, string GerScore, string GerRank, string ScoreScaled) {
        UniversityNode* newnode = new UniversityNode;
        newnode->Rank = Rank;
        newnode->Institution = Institution;
        newnode->LocationCode = LocationCode;
        newnode->Location = Location;
        newnode->ArScore = ArScore;
        newnode->ArRank = ArRank;
        newnode->ErScore = ErScore;
        newnode->ErRank = ErRank;
        newnode->FsrScore = FsrScore;
        newnode->FsrRank = FsrRank;
        newnode->CpfScore = CpfScore;
        newnode->CpfRank = CpfRank;
        newnode->IfrScore = IfrScore;
        newnode->IfrRank = IfrRank;
        newnode->IsrScore = IsrScore;
        newnode->IsrRank = IsrRank;
        newnode->IrnScore = IrnScore;
        newnode->IrnRank = IrnRank;
        newnode->GerScore = GerScore;
        newnode->GerRank = GerRank;
        newnode->ScoreScaled = ScoreScaled;
        newnode->PreviousAddress = NULL;
        newnode->NextAddress = NULL;
        size++;
        return newnode;
    };

    //left means the first node right means the end node
    // Function to merge two sorted doubly linked lists
    UniversityNode* Merge(UniversityNode* First, UniversityNode* Second) {
        if (!First) { //if first node is empty return the second node
            return Second;
        }
        if (!Second) {
            return First;
        }

        if (First->Institution < Second->Institution) {
            First->NextAddress = Merge(First->NextAddress, Second);
            First->NextAddress->PreviousAddress = First;
            First->PreviousAddress = NULL;
            return First;
        }
        else {
            Second->NextAddress = Merge(First, Second->NextAddress);
            Second->NextAddress->PreviousAddress = Second;
            Second->PreviousAddress = NULL;
            return Second;
        }
    }

    UniversityNode* MergeSort(UniversityNode* Unihead) {
        if (!Unihead || !Unihead->NextAddress) { // if list is empty or the next node is empty
            return Unihead;
        }
        UniversityNode* Second = MergeSplit(Unihead);

        Unihead = MergeSort(Unihead);
        Second = MergeSort(Second);

        //merge the sorted split list
        return Merge(Unihead, Second);
    }

    UniversityNode* MergeSplit(UniversityNode* head)
    {
        UniversityNode* fast = head, * slow = head;
        while (fast->NextAddress && fast->NextAddress->NextAddress)
        {
            fast = fast->NextAddress->NextAddress;
            slow = slow->NextAddress;
        }
        UniversityNode* temp = slow->NextAddress;
        slow->NextAddress = NULL;
        return temp;
    }


    //low means the first node high means the end node
    //get the last node of the linked list
    UniversityNode* QucikLastNode(UniversityNode* root)
    {
        while (root && root->NextAddress)
            root = root->NextAddress;
        return root;
    }

    void Swap(UniversityNode* a, UniversityNode* b) {
        string tempRank = a->Rank;
        string tempInstitution = a->Institution;
        string tempLocationCode = a->LocationCode;
        string tempLocation = a->Location;
        string tempArScore = a->ArScore;
        string tempArRank = a->ArRank;
        string tempErScore = a->ErScore;
        string tempErRank = a->ErRank;
        string tempFsrScore = a->FsrScore;
        string tempFsrRank = a->FsrRank;
        string tempCpfScore = a->CpfScore;
        string tempCpfRank = a->CpfRank;
        string tempIfrScore = a->IfrScore;
        string tempIfrRank = a->IfrRank;
        string tempIsrScore = a->IsrScore;
        string tempIsrRank = a->IsrRank;
        string tempIrnScore = a->IrnScore;
        string tempIrnRank = a->IrnRank;
        string tempGerScore = a->GerScore;
        string tempGerRank = a->GerRank;
        string tempScoreScaled = a->ScoreScaled;

        a->Rank = b->Rank;
        a->Institution = b->Institution;
        a->LocationCode = b->LocationCode;
        a->Location = b->Location;
        a->ArScore = b->ArScore;
        a->ArRank = b->ArRank;
        a->ErScore = b->ErScore;
        a->ErRank = b->ErRank;
        a->FsrScore = b->FsrScore;
        a->FsrRank = b->FsrRank;
        a->CpfScore = b->CpfScore;
        a->CpfRank = b->CpfRank;
        a->IfrScore = b->IfrScore;
        a->IfrRank = b->IfrRank;
        a->IsrScore = b->IsrScore;
        a->IsrRank = b->IsrRank;
        a->IrnScore = b->IrnScore;
        a->IrnRank = b->IrnRank;
        a->GerScore = b->GerScore;
        a->GerRank = b->GerRank;
        a->ScoreScaled = b->ScoreScaled;

        b->Rank = tempRank;
        b->Institution = tempInstitution;
        b->LocationCode = tempLocationCode;
        b->Location = tempLocation;
        b->ArScore = tempArScore;
        b->ArRank = tempArRank;
        b->ErScore = tempErScore;
        b->ErRank = tempErRank;
        b->FsrScore = tempFsrScore;
        b->FsrRank = tempFsrRank;
        b->CpfScore = tempCpfScore;
        b->CpfRank = tempCpfRank;
        b->IfrScore = tempIfrScore;
        b->IfrRank = tempIfrRank;
        b->IsrScore = tempIsrScore;
        b->IsrRank = tempIsrRank;
        b->IrnScore = tempIrnScore;
        b->IrnRank = tempIrnRank;
        b->GerScore = tempGerScore;
        b->GerRank = tempGerRank;
        b->ScoreScaled = tempScoreScaled;
    }

    UniversityNode* Quickpartition(UniversityNode* low, UniversityNode* high, int selected_sort) {
        if (selected_sort == 1) {
            string pivotValue = low->Institution;
            UniversityNode* p = low; // get the first node
            UniversityNode* q = low->NextAddress; // get second node
            while (q != high) { // if its not equal to the final node
                if (q->Institution < pivotValue) { // if first node is bigger than pivotvalue
                    p = p->NextAddress;
                    Swap(p, q);
                }
                q = q->NextAddress;
            }
            Swap(p, low);
            return p;
        }
        return nullptr;

    }

    void QuickSort(UniversityNode* low, UniversityNode* high, int selected_sort) {
        if (low != high) {
            UniversityNode* mid = Quickpartition(low, high, selected_sort);
            QuickSort(low, mid, selected_sort);
            QuickSort(mid->NextAddress, high, selected_sort);
        }
    }

    void LinearSearch(string Institution) {
        int size = 0;
        UniversityNode* current = Unihead;

        if (current == NULL) {
            cout << "The list is empty" << endl;
        }
        while (current != NULL) {
            if (Institution == current->Institution) {
                cout << "Rank: " << current->Rank << endl;
                cout << "Institution:" << current->Institution << endl;
                cout << "Location Code:" << current->LocationCode << endl;
                cout << "Location:" << current->Location << endl;
                cout << "Academic Reputation Score: " << current->ArScore << endl;
                cout << "Academic Reputation Rank: " << current->ArRank << endl;
                cout << "Employer Reputation Score: " << current->ErScore << endl;
                cout << "Employer Reputation Rank: " << current->ErRank << endl;
                cout << "Faculty/Student Ratio Score: " << current->FsrScore << endl;
                cout << "Faculty/Student Ratio Rank: " << current->FsrRank << endl;
                cout << "Citations Per Faculty Score: " << current->CpfScore << endl;
                cout << "Citations Per Faculty Rank: " << current->CpfRank << endl;
                cout << "International Faculty Ratio Score: " << current->IfrScore << endl;
                cout << "International Faculty Ratio Rank: " << current->IfrRank << endl;
                cout << "International Student Ratio Score: " << current->IsrScore << endl;
                cout << "International Student Ratio Rank: " << current->IsrRank << endl;
                cout << "International Research Network Score: " << current->IrnScore << endl;
                cout << "International Research Network Rank: " << current->IrnRank << endl;
                cout << "Employment Outcome Score: " << current->GerScore << endl;
                cout << "Employment Outcome Rank: " << current->GerRank << endl;
                cout << "Score Scaled: " << current->ScoreScaled << endl;
                break;
            }
            current = current->NextAddress;
        }

    }

    UniversityNode* middle(UniversityNode* start, UniversityNode* last)
    {
        if (start == NULL)
            return NULL;
        UniversityNode* slow = start;
        UniversityNode* fast = start->NextAddress;
        while (fast != last)
        {
            fast = fast->NextAddress;
            if (fast != last)
            {
                slow = slow->NextAddress;
                fast = fast->NextAddress;
            }
        }

        return slow;
    }

    // Function for implementing the Binary
    // Search on linked list
    UniversityNode* BinarySearch(UniversityNode* Unihead, int Selected_Option, string value)
    {
        UniversityNode* start = Unihead;
        UniversityNode* last = NULL;
        do
        {
            // Find middle
            UniversityNode* mid = middle(start, last);

            // If middle is empty
            if (mid == NULL)
                return NULL;

            if (mid->Institution == value) {// If value is present at middle
                cout << "Rank: " << mid->Rank << endl;
                cout << "Institution:" << mid->Institution << endl;
                cout << "Location Code:" << mid->LocationCode << endl;
                cout << "Location:" << mid->Location << endl;
                cout << "Academic Reputation Score: " << mid->ArScore << endl;
                cout << "Academic Reputation Rank: " << mid->ArRank << endl;
                cout << "Employer Reputation Score: " << mid->ErScore << endl;
                cout << "Employer Reputation Rank: " << mid->ErRank << endl;
                cout << "Faculty/Student Ratio Score: " << mid->FsrScore << endl;
                cout << "Faculty/Student Ratio Rank: " << mid->FsrRank << endl;
                cout << "Citations Per Faculty Score: " << mid->CpfScore << endl;
                cout << "Citations Per Faculty Rank: " << mid->CpfRank << endl;
                cout << "International Faculty Ratio Score: " << mid->IfrScore << endl;
                cout << "International Faculty Ratio Rank: " << mid->IfrRank << endl;
                cout << "International Student Ratio Score: " << mid->IsrScore << endl;
                cout << "International Student Ratio Rank: " << mid->IsrRank << endl;
                cout << "International Research Network Score: " << mid->IrnScore << endl;
                cout << "International Research Network Rank: " << mid->IrnRank << endl;
                cout << "Employment Outcome Score: " << mid->GerScore << endl;
                cout << "Employment Outcome Rank: " << mid->GerRank << endl;
                cout << "Score Scaled: " << mid->ScoreScaled << endl;
                break;
                return mid;

            }
            else if (mid->Institution < value) {// If value is more than mid
                start = mid->NextAddress;
            }
            else {// If the value is less than mid.
                last = mid;
            }
        } while (last == NULL || last != start);
        // value not present
        return NULL;
    }

    void doublyInsertNodeFront(string Rank, string Institution, string LocationCode, string Location, string ArScore, string ArRank,
        string ErScore, string ErRank, string FsrScore, string FsrRank, string CpfScore,
        string CpfRank, string IfrScore, string IfrRank, string IsrScore, string IsrRank, string IrnScore,
        string IrnRank, string GerScore, string GerRank, string ScoreScaled)
    {
        UniversityNode* newnode = createnewnode(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank,
            IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled);
        if (Unihead == NULL) {
            Unihead = Unitail = newnode;
        }
        else {
            Unitail->NextAddress = newnode;
            Unitail = newnode;
        }
    }
    void singleInsertNode(string Rank, string Institution, string LocationCode, string Location, string ArScore, string ArRank,
        string ErScore, string ErRank, string FsrScore, string FsrRank, string CpfScore,
        string CpfRank, string IfrScore, string IfrRank, string IsrScore, string IsrRank, string IrnScore,
        string IrnRank, string GerScore, string GerRank, string ScoreScaled)
    {
        UniversityNode* newnode = createnewnode(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank,
            IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled);
        if (Unihead == NULL) {
            Unihead = newnode;
        }
        else {
            newnode->NextAddress = Unihead;
            Unihead = newnode;
        }
    }

    void displaysearchedUniversities(string searchvalue) {
        UniversityNode* searching = Unihead;

    }
    void displayUniversities() {
        UniversityNode* current = Unihead;
        while (current != NULL) { // if current is not end of list, still get any address
            cout << "Rank: " << current->Rank << endl;
            cout << "Institution:" << current->Institution << endl;
            cout << endl;
            current = current->NextAddress;
        }
    }
};

void ReadUniversityData() {
    NormalUsers List1;
    string Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore,
        IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled, tempInstitution;
    ifstream file;
    file.open("rankings.csv");
    getline(file, Rank);
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return;
    }
    while (file.good()) {
        getline(file, Rank, ',');
        getline(file, Institution, ',');
        getline(file, LocationCode, ',');
        if (LocationCode.length() != 2) {
            Institution += ", ";
            Institution += LocationCode;
            getline(file, LocationCode, ',');
        }
        getline(file, Location, ',');
        getline(file, ArScore, ',');
        getline(file, ArRank, ',');
        getline(file, ErScore, ',');
        getline(file, ErRank, ',');
        getline(file, FsrScore, ',');
        getline(file, FsrRank, ',');
        getline(file, CpfScore, ',');
        getline(file, CpfRank, ',');
        getline(file, IfrScore, ',');
        getline(file, IfrRank, ',');
        getline(file, IsrScore, ',');
        getline(file, IsrRank, ',');
        getline(file, IrnScore, ',');
        getline(file, IrnRank, ',');
        getline(file, GerScore, ',');
        getline(file, GerRank, ',');
        getline(file, ScoreScaled);
        if (Rank == "") {
            break;
        }
        else if (Rank == "Rank") {
            continue;
        }
        List1.doublyInsertNodeFront(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore,
            IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled);
    }
    file.close();
}


////////////////////// MENUS /////////////////////

void displayMainMenu1() {
    std::cout << "********************************************************" << std::endl;
    std::cout << "|                       Main Menu                    |" << std::endl;
    std::cout << "********************************************************" << std::endl;
    std::cout << "***          1. Explore Universities as a Guest     ***" << std::endl;
    std::cout << "***          2. Login as Customer                   ***" << std::endl;
    std::cout << "***          3. Login as Admin                      ***" << std::endl;
    std::cout << "***          4. Exit                                ***" << std::endl;
    std::cout << "*********************************************************" << std::endl;
    cout << "" << endl;
    cout << "Enter your choice: ";
}

void displayCusMenu() {
    cout << "" << endl;
    cout << "Customer Menu:" << endl;
    cout << "1. View All Universities" << endl;
    cout << "2. Sort Universities" << endl;
    cout << "3. Search Univerisity" << endl;
    cout << "4. View Your Feedbacks" << endl;
    cout << "5. View Your Saved Favourite Universities" << endl;
    cout << "6. LogOut" << endl;
    cout << "" << endl;
    cout << "Enter your choice: ";
}

void displayAdminMenu() {
    cout << "" << endl;
    cout << "Hello Admin" << endl;
    cout << "Admin Menu:" << endl;
    cout << "1. View All Registered Users" << endl;
    cout << "2. Modify Registered User Details Users" << endl;
    cout << "3. Delete Registered Users" << endl;
    cout << "4. View University Feedbacks" << endl;
    cout << "5. View Favourite Universities Report" << endl;
    cout << "6. LogOut" << endl;
    cout << "" << endl;
    cout << "Enter your choice: ";
}

void displayFeedbackMenu() {
    cout << "" << endl;
    cout << "Feedback Menu:" << endl;
    cout << "1. View All Pending Feedbacks " << endl;
    cout << "2. View All Replied Feedbacks " << endl;
    cout << "3. Move back and forth between Feedbacks" << endl;
    cout << "4. Exit" << endl;
    cout << "" << endl;
    cout << "Enter your choice: ";
}

void displayNormalUserMenu() {
    cout << "" << endl;
    cout << "Guest Users Menu:" << endl;
    cout << "1. View All Universities " << endl;
    cout << "2. Sort University Details" << endl;
    cout << "3. Search University Details" << endl;
    cout << "4. Register As a Customer" << endl;
    cout << "5. Check Eligibility for Scholarship" << endl;
    cout << "6. Exit" << endl;
    cout << "" << endl;
    cout << "Enter your choice: ";
}

////////////////// Process Options /////////

void processOption(int option) {
    switch (option) {
    case 1:
        cout << "" << endl;
        normaluserprocess();
        break;
    case 2:
        cout << "" << endl;
        reguserLogin();
        break;
    case 3:
        cout << "" << endl;
        AdminLogin();
        break;
    case 4:
        cout << "Exiting..." << endl;
        insertUser();
        SaveUnis();
        insertFeedback();
        saveRepliesToFile();
        exit(0);
        break;
    default:
        cout << "" << endl;
        cout << "Invalid option. Please try again." << endl;
        break;
    }
}

void processCustomerOption(int option, const string& username) {
    switch (option) {
    case 1:
        cout << "" << endl;
        displaycusunis();
        break;
    case 2:
        cout << "" << endl;
        sort_dec_unis();
        break;
    case 3:
        cout << "" << endl;
        SearchCusUni(username);
        break;
    case 4:
        cout << "" << endl;
        displayFeedbacks(username);
        break;
    case 5:
        cout << "" << endl;
        displaySavedUnis(username);
        break;
    case 6:
        cout << "" << endl;
        cout << "Logging Out..." << endl;
        // End the program
        break;
    default:
        cout << "" << endl;
        cout << "Invalid option. Please try again." << endl;
        break;
    }
}

void processAdminOption(int option) {
    switch (option) {
    case 1:
        cout << "" << endl;
        displayRegUsers();
        break;
    case 2:
        cout << "" << endl;
        modifier();
        break;
    case 3:
        cout << "" << endl;
        deletereguser();
        break;
    case 4:
        cout << "" << endl;
        adminfeedbackprocess();
        break;
    case 5:
        cout << "" << endl;
        generateReport();
        break;
    case 6:
        cout << "Logging Out" << endl;
        // End the program
        break;
    default:
        cout << "" << endl;
        cout << "Invalid option. Please try again." << endl;
        break;
    }
}

void processFeedbackOption(int option) {
    switch (option) {
    case 1:
        cout << "" << endl;
        displayAdminFeedbacks();
        break;
    case 2:
        cout << "" << endl;
        displayAdminReplies();
        break;
    case 3:
        cout << "" << endl;
        moveBetweenFeedbacks();
        break;
    case 4:
        cout << "Exiting..." << endl;
        // End the program
        break;
    default:
        cout << "" << endl;
        cout << "Invalid option. Please try again." << endl;
        break;
    }
}

void processNormalUserOption(int option) {
    switch (option) {
    case 1:
        cout << "" << endl;
        displaycusunis();
        break;
    case 2:
        cout << "" << endl;
        SearchSortOption();
        break;
    case 3:
        cout << "" << endl;
        SearchAlgoOption();
        break;
    case 4:
        cout << "" << endl;
        registeruser();
        break;
    case 5:
        cout << "" << endl;
        financial_calc();
        break;
    case 6:
        cout << "Exiting..." << endl;
        // End the program
        break;
    default:
        cout << "" << endl;
        cout << "Invalid option. Please try again." << endl;
        break;
    }
}

void normaluserprocess() {
    int choice;
    bool exitMenu = false;

    while (!exitMenu) {

        displayNormalUserMenu();
        fflush(stdin);
        cin >> choice;

        processNormalUserOption(choice);

        if (choice == 6) {
            exitMenu = true;
        }
        else {
            cout << endl;
        }
    }

}

void adminprocess() {
    int choice;
    bool exitMenu = false;

    while (!exitMenu) {

        displayAdminMenu();
        fflush(stdin);
        cin >> choice;

        processAdminOption(choice);

        if (choice == 6) {
            exitMenu = true;
        }
        else {
            cout << endl;

        }
    }

}

void adminfeedbackprocess() {
    int choice;
    bool exitMenu = false;

    while (!exitMenu) {

        displayFeedbackMenu();
        fflush(stdin);
        cin >> choice;

        processFeedbackOption(choice);

        if (choice == 4) {
            exitMenu = true;
        }
        else {
            cout << endl;
        }
    }

}

/////////////////////////////////////////////////////// NORMAL USERS ///////////////////////////////////////////////

////////////////////////////////////SORTING ALGO///////////////
void SearchSortOption() {
    NormalUsers SortAlgo;
    int SortOption;
    cout << "To compare different search please select a sort\n1.Quick Sort \n2.Merge Sort." << endl;
    cin >> SortOption;
    if (SortOption == 1) {
        auto start = high_resolution_clock::now();
        SortAlgo.QuickSort(Unihead, NULL, 1);
        auto stop = high_resolution_clock::now();
        SortAlgo.displayUniversities();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "*****************************" << endl;
        cout << "Time taken To Quick Sort" << endl;
        cout << duration.count() << " Microseconds, " << endl;
        cout << "*****************************" << endl;
    }
    else if (SortOption == 2) {
        auto start = high_resolution_clock::now();
        SortAlgo.MergeSort(Unihead);
        auto stop = high_resolution_clock::now();
        SortAlgo.displayUniversities();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "*****************************" << endl;
        cout << "Time taken To Merge Sort" << endl;
        cout << duration.count() << " Microseconds, " << endl;
        cout << "*****************************" << endl;

    }
    else {
        cout << "Invalid Input" << endl;

    }
}

////////////////////////////////////SEARCHING ALGO///////////////
void SearchAlgoOption() {
    NormalUsers SearchAlgo;
    string SearchOption;
    string UniName;
    cout << "To compare different search please select a sort\n1.Binary Search\n2.Linear Search\n3.Enter N to cancel." << endl;
    cin >> SearchOption;
    do {
        if (SearchOption == "1") {
            getline(cin, UniName);
            cout << "What University information you want to know, please enter a university name" << endl;
            getline(cin, UniName);
            auto start = high_resolution_clock::now();
            SearchAlgo.QuickSort(Unihead, NULL, 1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "" << endl;
            cout << "*****************************" << endl;
            cout << "Time taken Binary Search" << endl;
            cout << duration.count() << " Microseconds, " << endl;
            cout << "*****************************" << endl;
            if (SearchAlgo.BinarySearch(Unihead, 0, UniName) == NULL)
                printf("");
            else
                printf("Present");
            break;
        }
        else if (SearchOption == "2") {
            getline(cin, UniName);
            cout << "What University information you want to know, please enter a university name" << endl;
            getline(cin, UniName);
            auto start = high_resolution_clock::now();
            SearchAlgo.LinearSearch(UniName);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "" << endl;
            cout << "*****************************" << endl;
            cout << "Time taken Linear Search" << endl;
            cout << duration.count() << " Microseconds, " << endl;
            cout << "*****************************" << endl;
            break;
        }
        else if (SearchOption == "N" || SearchOption == "n") {
            cout << "" << endl;
            normaluserprocess();

        }
        else {
            cout << "Invalid option please select\n1.Binary Search\n2.Linear Search\n";
            cin >> SearchOption;
        }
    } while (true);
}

////// Register////


UserNode* createUserNode(string username, string password, string type, string age, string email, string name) {
    UserNode* newnode = new UserNode;
    newnode->username = username;
    newnode->password = password;
    newnode->type = type;
    newnode->age = age;
    newnode->email = email;
    newnode->name = name;
    newnode->Nextaddress = NULL;
    return newnode;
}

void InsertUserNode(string username, string password, string type, string age, string email, string name) {
    UserNode* newnode = createUserNode(username, password, type, age, email, name);
    if (Userhead == NULL) {
        Userhead = newnode;
    }
    else {
        newnode->Nextaddress = Userhead;
        Userhead = newnode;
    }
}

void insertUser() {
    UserNode* current = Userhead;
    string filename = "users.txt";
    ofstream file("users.txt", ios::app);
    time_t now = time(nullptr);
    string timestamp = ctime(&now);
    // Remove the newline character from the timestamp
    timestamp.erase(timestamp.length() - 1);

    while (current != NULL) {
        if (file.is_open()) {
            cout << current->username;
            file << current->username << "," << current->password << "," << current->type << "," << current->name << "," << current->age << "," << current->email << "," << timestamp << endl;
            current = current->Nextaddress;
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }
    file.close();
    cout << "" << endl;
    cout << "Registeration Successful" << endl;
    cout << "------------------------" << endl;
}

void insertUser(const string& filename, const string& username, const string& password, const string& type, const string& age, const string& email, const string& name) {
    ofstream file(filename, ios::app);
    time_t now = time(nullptr);
    string timestamp = ctime(&now);
    // Remove the newline character from the timestamp
    timestamp.erase(timestamp.length() - 1);

    if (file.is_open()) {
        file << username << "," << password << "," << type << "," << name << "," << age << "," << email << "," << timestamp << endl;
        file.close();
        cout << "" << endl;
        cout << "Registeration Successful" << endl;
        cout << "------------------------" << endl;
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

bool checkUsernameExists(const string& filename, const string& username) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string storedUsername;
        getline(ss, storedUsername, ',');

        if (storedUsername == username) {
            file.close();
            return true; // Username exists
        }
    }

    file.close();
    return false; // Username does not exist
}

void registeruser() {
    string filename = "users.txt";
    string username, password;
    string age;
    string email;
    string name;
    bool usernameExists = true;


    while (usernameExists) {
        cout << "" << endl;
        cout << "Enter Your Username: ";
        cin >> username;

        // Check if username already exists
        if (checkUsernameExists(filename, username)) {
            cout << "Username already exists. Please choose a different username." << endl;
        }
        else {
            usernameExists = false; // Username is valid, exit the loop
        }
    }

    cout << "Enter your Password: ";
    cin >> password;

    cout << "Enter Your Name: ";
    cin >> name;

    fflush(stdin);
    cout << "Enter your Email: ";
    cin >> email;

    cout << "Enter Your Age: ";
    cin >> age;

    string type = "customer";

    InsertUserNode(username, password, type, age, email, name);

    return;
}

///////////////////// Reg Customer/Admin Login ////////////////
struct AdminNode {
    string username;
    string password;
    string type;
    AdminNode* next;
};

void addNode(AdminNode** head_ref, string username, string password, string type) {
    AdminNode* new_node = new AdminNode;
    new_node->username = username;
    new_node->password = password;
    new_node->type = type;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void loadUsers(AdminNode** head_ref, string filename) {

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password, type;
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, type, ',');
            addNode(head_ref, username, password, type);
        }
        file.close();
    }
}

bool login(AdminNode* head, string username, string password, string type) {
    while (head != NULL) {
        if (head->username == username && head->password == password && head->type == type) {
            return true;
        }
        head = head->next;
    }
    return false;
}

void reguserLogin() {

    bool cancelLogin = false;
    string cancelInput;
    while (!cancelLogin) {
        AdminNode* head = NULL;
        loadUsers(&head, "users.txt");

        string username, password;
        cout << "Enter Username : ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;

        string type = "customer";

        if (login(head, username, password, type))
        {
            cout << "" << endl;
            cout << "Login Successful!" << endl;
            cout << "-------------------" << endl;
            updateField(username);
            cancelLogin = true;  // Exit the loop after successful login
            regcus(username);
        }
        else
        {
            cout << "Invalid username or Password" << endl;
            cout << "Try again? (Y/N): ";
            cin >> cancelInput;
            if (cancelInput == "N" || cancelInput == "n") {
                break;  // Exit the loop if user chooses not to try again
            }
        }
    }
}

void AdminLogin() {

    bool cancelLogin = false;
    string cancelInput;
    while (!cancelLogin) {
        AdminNode* head = NULL;
        loadUsers(&head, "users.txt");

        string username, password;
        cout << "" << endl;
        cout << "Enter Username : ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;

        string type = "admin";

        if (login(head, username, password, type))
        {
            cout << "" << endl;
            cout << "Login Successful!" << endl;
            cout << "-------------------" << endl;
            updateField(username);
            cancelLogin = true;  // Exit the loop after successful login
            adminprocess();
        }
        else
        {
            cout << "Invalid username or Password" << endl;
            cout << "" << endl;
            cout << "Try again? (Y/N): ";
            cout << "" << endl;
            cin >> cancelInput;
            if (cancelInput == "N" || cancelInput == "n") {
                break;  // Exit the loop if user chooses not to try again
            }
        }
    }
}

void updateField(const string& username) {
    string filename = "users.txt";
    ifstream file(filename);
    if (!file) {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    stringstream updatedContent;
    bool updated = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> columns;

        while (getline(ss, item, ',')) {
            columns.push_back(item);
        }

        if (columns.size() >= 2 && columns[0] == username) {
            // Modify the last field with the current date and time
            time_t now = time(nullptr);
            string timestamp = ctime(&now);
            // Remove the newline character from the timestamp
            timestamp.erase(timestamp.length() - 1);
            columns[columns.size() - 1] = timestamp;
            updated = true;
        }

        // Reconstruct the line with modified or original fields
        for (size_t i = 0; i < columns.size(); i++) {
            updatedContent << columns[i];
            if (i != columns.size() - 1) {
                updatedContent << ",";
            }
        }
        updatedContent << endl;
    }

    file.close();

    if (updated) {
        ofstream outputFile(filename);
        if (!outputFile) {
            cout << "Failed to open the file for writing." << endl;
            return;
        }
        outputFile << updatedContent.str();
        outputFile.close();

    }
    else {
        cout << "Username not found." << endl;
    }
}


//////////////////////// Display Customer Unis ///////////////
class DisplayUniNode {
public:
    string data;
    DisplayUniNode* next;

    DisplayUniNode(string data) {
        this->data = data;
        this->next = nullptr;
    }
};

class DisplayUniLinkedList {
public:
    DisplayUniNode* head;

    DisplayUniLinkedList() {
        this->head = nullptr;
    }

    void add_node(string data) {
        DisplayUniNode* new_node = new DisplayUniNode(data);
        if (this->head == nullptr) {
            this->head = new_node;
        }
        else {
            DisplayUniNode* current_node = this->head;
            while (current_node->next != nullptr) {
                current_node = current_node->next;
            }
            current_node->next = new_node;
        }
    }

    void print_table() {
        DisplayUniNode* current_node = this->head;
        int column_width1 = 5;  // Width of the first column
        int column_width2 = 15; // Width of the remaining columns

        // Print the top border
        cout << "+" << string(column_width1, '-') << "+"
            << string(column_width2 * 3, '-') << "+" << endl;

        // Print the column headers
        cout << "|" << left << setw(column_width1) << "ID"
            << "|" << left << setw(column_width2) << "University Name" << "|" << endl;

        // Print the header and data separator
        cout << "+" << string(column_width1, '=') << "+"
            << string(column_width2, '=') << "+" << endl;

        // Print each record
        while (current_node != nullptr) {
            cout << "|" << left << setw(column_width1) << current_node->data;
            current_node = current_node->next;
            for (int i = 0; i < 1; i++) {
                if (current_node != nullptr) {
                    cout << "|" << left << setw(column_width2) << current_node->data;
                    current_node = current_node->next;
                }
                else {
                    cout << "|" << left << setw(column_width2) << "";  // Empty cell if no data available
                }
            }
            cout << "|" << endl;
        }
    }

};

void displaycusunis() {
    DisplayUniLinkedList linked_list;
    string line;
    ifstream file("rankings.csv");
    while (getline(file, line))
    {
        stringstream ss(line);
        string item;
        int count = 0;
        while (getline(ss, item, ',') && count < 2) {
            linked_list.add_node(item);
            count++;
        }
    }
    linked_list.print_table();
}

void regcus(const string& username) {
    int choice;
    bool exitCustomerMenu = false;

    while (!exitCustomerMenu) {

        displayCusMenu();
        fflush(stdin);
        cin >> choice;

        processCustomerOption(choice, username);

        if (choice == 6) {
            exitCustomerMenu = true;
        }
        else {
            cout << endl;
        }
    }

}


/////////////////////// Search, Save Favourite and Feedback Customer Universities ////////
class UniversityNode1 {
public:
    string Rank;
    string Institution;
    string LocationCode;
    string Location;
    string ArScore;
    string ArRank;
    string ErScore;
    string ErRank;
    string FsrScore;
    string FsrRank;
    string CpfScore;
    string CpfRank;
    string IfrScore;
    string IfrRank;
    string IsrScore;
    string IsrRank;
    string IrnScore;
    string IrnRank;
    string GerScore;
    string GerRank;
    string ScoreScaled;
    string feedback;
    UniversityNode1* PreviousAddress;
    UniversityNode1* NextAddress; //pointer -> to store next item address

    UniversityNode1* next;

    UniversityNode1(string Rank, string Institution, string LocationCode, string Location, string ArScore, string ArRank, string ErScore, string ErRank, string FsrScore, string FsrRank, string CpfScore, string CpfRank, string IfrScore, string IfrRank, string IsrScore, string IsrRank, string IrnScore, string IrnRank, string GerScore, string GerRank, string ScoreScaled) {
        this->Rank = Rank;
        this->Institution = Institution;
        this->LocationCode = LocationCode;
        this->Location = Location;
        this->ArScore = ArScore;
        this->ArRank = ArRank;
        this->ErScore = ErScore;
        this->ErRank = ErRank;
        this->FsrScore = FsrScore;
        this->FsrRank = FsrRank;
        this->CpfScore = CpfScore;
        this->CpfRank = CpfRank;
        this->IfrScore = IfrScore;
        this->IfrRank = IfrRank;
        this->IsrScore = IsrScore;
        this->IsrRank = IsrRank;
        this->IrnScore = IrnScore;
        this->IrnRank = IrnRank;
        this->GerScore = GerScore;
        this->GerRank = GerRank;
        this->ScoreScaled = ScoreScaled;
        this->next = nullptr;
        this->NextAddress = NULL;
    }
}*head;

class UniversityLinkedList {
public:
    UniversityNode1* head;

    UniversityLinkedList() {
        this->head = nullptr;
    }

    void add_node(const string& Rank, const string& Institution, const string& LocationCode,
        const string& Location, const string& ArScore, const string& ArRank,
        const string& ErScore, const string& ErRank, const string& FsrScore,
        const string& FsrRank, const string& CpfScore, const string& CpfRank,
        const string& IfrScore, const string& IfrRank, const string& IsrScore,
        const string& IsrRank, const string& IrnScore, const string& IrnRank,
        const string& GerScore, const string& GerRank, const string& ScoreScaled) {
        UniversityNode1* new_node = new UniversityNode1(Rank, Institution, LocationCode, Location, ArScore, ArRank,
            ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank,
            IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank,
            GerScore, GerRank, ScoreScaled);
        if (this->head == nullptr) {
            this->head = new_node;
        }
        else {
            UniversityNode1* current_node = this->head;
            while (current_node->NextAddress != nullptr) {
                current_node = current_node->NextAddress;
            }
            current_node->NextAddress = new_node;
        }
    }

    UniversityNode1* find_node(const string& Rank) {
        UniversityNode1* current_node = this->head;
        while (current_node != nullptr) {
            if (current_node->Rank == Rank) {
                return current_node;
            }
            current_node = current_node->NextAddress;
        }
        return nullptr; // no match found
    }

    UniversityNode1* linear_search(const string& Rank) {
        UniversityNode1* current_node = this->head;
        while (current_node != nullptr) {
            if (current_node->Rank == Rank) {
                return current_node;
            }
            current_node = current_node->NextAddress;
        }
        return nullptr; // no match found
    }

    void addUniversity(const string& Rank, const string& Institution, const string& LocationCode,
        const string& Location, const string& ArScore, const string& ArRank,
        const string& ErScore, const string& ErRank, const string& FsrScore,
        const string& FsrRank, const string& CpfScore, const string& CpfRank,
        const string& IfrScore, const string& IfrRank, const string& IsrScore,
        const string& IsrRank, const string& IrnScore, const string& IrnRank,
        const string& GerScore, const string& GerRank, const string& ScoreScaled) {
        UniversityNode1* newUniversity = new UniversityNode1(Rank, Institution, LocationCode, Location, ArScore,
            ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore,
            CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore,
            IrnRank, GerScore, GerRank, ScoreScaled);
        if (head == nullptr) {
            head = newUniversity;
        }
        else {
            UniversityNode1* current = head;
            while (current->NextAddress != nullptr) {
                current = current->NextAddress;
            }
            current->NextAddress = newUniversity;
        }
    }

    UniversityNode1* mergeSort(UniversityNode1* start, const string& sortBasis) {
        if (start == nullptr || start->NextAddress == nullptr) {
            return start;
        }

        UniversityNode1* middle = getMiddle(start);
        UniversityNode1* nextToMiddle = middle->NextAddress;

        middle->NextAddress = nullptr;

        UniversityNode1* left = mergeSort(start, sortBasis);
        UniversityNode1* right = mergeSort(nextToMiddle, sortBasis);

        return merge(left, right, sortBasis);
    }

    UniversityNode1* merge(UniversityNode1* left, UniversityNode1* right, const string& sortBasis) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        UniversityNode1* merged = nullptr;
        if (compareUniversity(*left, *right, sortBasis)) {
            merged = left;
            merged->NextAddress = merge(left->NextAddress, right, sortBasis);
        }
        else {
            merged = right;
            merged->NextAddress = merge(left, right->NextAddress, sortBasis);
        }

        return merged;
    }

    UniversityNode1* getMiddle(UniversityNode1* start) {
        if (start == nullptr) {
            return start;
        }

        UniversityNode1* slow = start;
        UniversityNode1* fast = start->NextAddress;

        while (fast != nullptr) {
            fast = fast->NextAddress;
            if (fast != nullptr) {
                slow = slow->NextAddress;
                fast = fast->NextAddress;
            }
        }

        return slow;
    }

    bool compareUniversity(const UniversityNode1& u1, const UniversityNode1& u2, const string& sortBasis) {
        if (sortBasis == "1") {
            return u1.ArScore > u2.ArScore;
        }
        else if (sortBasis == "2") {
            return u1.ErScore > u2.ErScore;
        }
        else if (sortBasis == "3") {
            return u1.FsrScore > u2.FsrScore;
        }
        // Default sorting basis: Academic Reputation score
        return u1.ArScore > u2.ArScore;
    }

    void sortUniversities(const string& sortBasis) {
        head = mergeSort(head, sortBasis);
    }

    void printList2() {
        UniversityNode1* current = head;

        while (current != nullptr) {
            cout << "University Name: " << current->Institution << endl;
            cout << "Academic Reputation Score: " << current->ArScore << endl;
            cout << "Faculty/Student Ratio Score: " << current->FsrScore << endl;
            cout << "Employee Reputation Score: " << current->ErScore << endl;
            cout << "" << endl;
            current = current->NextAddress;
        }
    }
};

void addUni(const string& sortBasis) {
    UniversityLinkedList universities;
    ifstream file("rankings.csv");
    if (!file) {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> columns;

        while (getline(ss, item, ',')) {
            columns.push_back(item);
        }

        if (columns.size() >= 21) {
            string Rank = columns[0];
            string Institution = columns[1];
            string LocationCode = columns[2];
            string Location = columns[3];
            string ArScore = columns[4];
            string ArRank = columns[5];
            string ErScore = columns[6];
            string ErRank = columns[7];
            string FsrScore = columns[8];
            string FsrRank = columns[9];
            string CpfScore = columns[10];
            string CpfRank = columns[11];
            string IfrScore = columns[12];
            string IfrRank = columns[13];
            string IsrScore = columns[14];
            string IsrRank = columns[15];
            string IrnScore = columns[16];
            string IrnRank = columns[17];
            string GerScore = columns[18];
            string GerRank = columns[19];
            string ScoreScaled = columns[20];

            universities.addUniversity(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank,
                FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank,
                IrnScore, IrnRank, GerScore, GerRank, ScoreScaled);
        }
    }
    file.close();
    universities.sortUniversities(sortBasis);
    universities.printList2();
}

void sort_dec_unis()
{
    while (true) {
        UniversityLinkedList universities;
        string sortBasis;
        cout << "" << endl;
        cout << "Filter Options" << endl;
        cout << "1. Academic Reputation" << endl;
        cout << "2. Employability Reputation" << endl;
        cout << "3. Faculty Student Ratio" << endl;
        cout << "4. Main Customer Menu" << endl;
        cout << "" << endl;
        cout << "Choose the Filter you would like to apply (or enter 'q' to quit): ";
        cin >> sortBasis;


        if (sortBasis == "1" || sortBasis == "2" || sortBasis == "3") {
            addUni(sortBasis);
        }

        if (sortBasis == "4") {
            break;
        }
        else {
            cout << "Invalid Option Please Try Again" << endl;
            cout << "" << endl;
        }
    }
}


//////////// Save ////////////
int getLastSerialNumber() {
    // Open the file in read mode
    ifstream SaveUnisFile("saveunis.txt");

    int lastSerialNumber = 0;
    string line;

    // Read the file line by line
    while (getline(SaveUnisFile, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Split the line by comma
        stringstream ss(line);
        string token;
        getline(ss, token, ',');

        // Extract the serial number from the first column
        int serialNumber = stoi(token);

        // Update the lastSerialNumber if the current serial number is greater
        if (serialNumber > lastSerialNumber) {
            lastSerialNumber = serialNumber;
        }
    }

    // Close the file
    SaveUnisFile.close();

    return lastSerialNumber;
}

FavUniNode* CreateFavUniNode(string reguserid, string university, string rank, string location) {
    FavUniNode* newnode = new FavUniNode;
    newnode->reguserid = reguserid;
    newnode->university = university;
    newnode->rank = rank;
    newnode->location = location;
    newnode->Nextaddress = NULL;
    return newnode;
}

void InsertFavUniNode(string reguserid, string university, string rank, string location) {
    FavUniNode* newnode = CreateFavUniNode(reguserid, university, rank, location);
    if (FavUnihead == NULL) {
        FavUnihead = newnode;
    }
    else {
        newnode->Nextaddress = FavUnihead;
        FavUnihead = newnode;
    }
}


void SaveUnis() {
    FavUniNode* current = FavUnihead;
    int lastSerialNumber = getLastSerialNumber();
    int newSerialNumber = lastSerialNumber + 1;
    string Sno = to_string(newSerialNumber);

    // Open the SaveUnis file in append mode
    ofstream SaveUnisFile("saveunis.txt", ios::app);

    // Check if the file is opened successfully
    if (SaveUnisFile.is_open()) {
        // Write the feedback with ID and timestamp to the file
        while (current != NULL) {
            SaveUnisFile << Sno << ",";
            SaveUnisFile << current->reguserid << ",";
            SaveUnisFile << current->rank << ",";
            SaveUnisFile << current->university << ",";
            SaveUnisFile << current->location << endl;
            current = current->Nextaddress;
        }
        // Close the file
        SaveUnisFile.close();
        cout << "Favourite University Saved Successfully." << endl;
        cout << " -----------------------------------------" << endl;
    }
    else {
        cout << "Failed to Save University. Please try again later." << endl;
    }
}

void SearchCusUni(const string& username) {
    int choice;
    UniversityLinkedList linked_list;
    string line;
    ifstream file("rankings.csv");

    // Read data from CSV file and add nodes to linked list
    while (getline(file, line))
    {
        stringstream ss(line);
        string item;
        string Rank, Instituiton, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled;
        getline(ss, Rank, ',');
        getline(ss, Instituiton, ',');
        getline(ss, LocationCode, ',');
        getline(ss, Location, ',');
        getline(ss, ArScore, ',');
        getline(ss, ArRank, ',');
        getline(ss, ErScore, ',');
        getline(ss, ErRank, ',');
        getline(ss, FsrScore, ',');
        getline(ss, FsrRank, ',');
        getline(ss, CpfScore, ',');
        getline(ss, CpfRank, ',');
        getline(ss, IfrScore, ',');
        getline(ss, IfrRank, ',');
        getline(ss, IsrScore, ',');
        getline(ss, IsrRank, ',');
        getline(ss, IrnScore, ',');
        getline(ss, IrnRank, ',');
        getline(ss, GerScore, ',');
        getline(ss, GerRank, ',');
        getline(ss, ScoreScaled, ',');
        linked_list.add_node(Rank, Instituiton, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled);
    }

    // Prompt user for university name to search for
    string search_name;

    cout << "Enter the ID/Rank of a university to search for: ";
    fflush(stdin);
    getline(cin, search_name);

    // Find node in linked list matching search name using linear search and display details
    UniversityNode1* search_node = linked_list.linear_search(search_name);
    if (search_node == nullptr) {
        cout << "No match found for university named " << search_name << endl;
    }
    else {
        cout << "Details for " << search_node->Institution << endl;
        cout << "Rank: " << search_node->Rank << endl;
        cout << "Location: " << search_node->Location << endl;
        cout << " " << endl;
        cout << "Academic Reputation Score: " << search_node->ArScore << endl;
        cout << "Academic Reputation Rank: " << search_node->ArRank << endl;
        cout << " " << endl;
        cout << "Employability Repuation Score: " << search_node->ErScore << endl;
        cout << "Employability Repuation Rank: " << search_node->ErRank << endl;
        cout << " " << endl;
        cout << "Faculty/Student Ratio Score: " << search_node->FsrScore << endl;
        cout << "Faculty/Student Ratio Rank: " << search_node->FsrRank << endl;
        cout << " " << endl;
        cout << "Citations Per Faculty Score: " << search_node->CpfScore << endl;
        cout << "Citations Per Faculty Rank: " << search_node->CpfRank << endl;
        cout << " " << endl;
        cout << "International Faculty Ratio Score: " << search_node->IfrScore << endl;
        cout << "International Faculty Ratio Rank: " << search_node->IfrRank << endl;
        cout << " " << endl;
        cout << "International Student Ratio Score: " << search_node->IsrScore << endl;
        cout << "International Student Ratio Rank: " << search_node->IsrRank << endl;
        cout << " " << endl;
        cout << "International Research Network Score: " << search_node->IrnScore << endl;
        cout << "International Research Network Rank: " << search_node->IrnRank << endl;
        cout << " " << endl;
        cout << "Employment Outcome Score: " << search_node->GerScore << endl;
        cout << "Employment Outcome Rank: " << search_node->GerRank << endl;
        cout << " " << endl;
        cout << "Score Scaled: " << search_node->ScoreScaled << endl;
        cout << "-------------------------------------------------------------------------------- " << endl;


        bool exitMenu = false;

        while (!exitMenu) {
            int choice;
            cout << "" << endl;
            cout << "Select the Option you want to proceed with" << endl;
            cout << "1. Save University" << endl;
            cout << "2. Give Feedback To MOHE" << endl;
            cout << "3. Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            string userid = username;

            switch (choice) {
            case 1:
                InsertFavUniNode(userid, search_node->Institution, search_node->Rank, search_node->Location);
                cout << "University Favourited !" << endl;
                break;
            case 2: {
                srand(time(nullptr));
                string feedback;
                cout << "Name Of The University: " << search_node->Institution << endl;
                cout << "" << endl;
                cout << "Enter your Feedback for MoHE: ";
                fflush(stdin);  // Ignore the newline character in the input buffer
                getline(cin, feedback);

                InsertFeedbackNode(userid, search_node->Institution, feedback);
                cout << "Feedback Accepted" << endl;
                break;
            }
            case 3:
                exitMenu = true;  // Exit the loop and return to the main menu
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }
    }
}

/////////////////////// Sort University based on different ///////

////////////////////// View Your Feedbacks //////////////
void displayFeedbacks(const string& username) {

    cout << endl << string(25, '=') << "Feedbacks of MoHE" << string(25, '=') << endl;

    ifstream feedbackFile("feedback.txt");
    ifstream replyFile("reply.txt");

    if (!feedbackFile) {
        cout << "No feedbacks available." << endl;
        return;
    }

    string feedbackId, universityName, feedbackMessage, date, userid;
    while (getline(feedbackFile, feedbackId, ','))
    {
        getline(feedbackFile, userid, ',');
        getline(feedbackFile, universityName, ',');
        getline(feedbackFile, feedbackMessage, ',');
        getline(feedbackFile, date);

        if (username == userid)
        {
            cout << "Feedback ID: " << feedbackId << endl;
            cout << "University: " << universityName << endl;
            cout << "Feedback: " << feedbackMessage << endl;
            cout << "Date: " << date << endl << endl;

            // Search for a matching reply in the reply file
            string replyMessage;
            bool replyFound = false;

            string replyLine;
            while (getline(replyFile, replyLine)) {
                istringstream iss(replyLine);
                string id, replyUniversityName, replyFeedbackMessage, replyDate, reply;
                getline(iss, id, ',');
                getline(iss, replyUniversityName, ',');
                getline(iss, replyFeedbackMessage, ',');
                getline(iss, replyDate, ',');
                getline(iss, reply);

                // cout << endl << "++debug++" << endl;
                //cout << "reply line"<< replyLine << endl;

                if (id == feedbackId) {
                    replyFound = true;
                    cout << "Reply: " << reply << endl;
                    break;
                }
            }


            if (!replyFound) {
                cout << "Waiting For A Reply...... ." << endl;
            }
        }
        cout << endl;

        replyFile.clear();
        replyFile.seekg(0, ios::beg);

    }

    feedbackFile.close();
    replyFile.close();

}

void displayAdminFeedbacks() {

    cout << endl << string(25, '=') << "Pending Feedbacks of MoHE" << string(25, '=') << endl;

    ifstream feedbackFile("feedback.txt");

    if (!feedbackFile) {
        cout << "No feedbacks available." << endl;
        return;
    }

    string feedbackId, universityName, feedbackMessage, date, userid, stat;
    while (getline(feedbackFile, feedbackId, ','))
    {
        getline(feedbackFile, userid, ',');
        getline(feedbackFile, universityName, ',');
        getline(feedbackFile, feedbackMessage, ',');
        getline(feedbackFile, date, ',');
        getline(feedbackFile, stat);

        // Search for a matching reply in the reply file

        if (stat == "Pending")
        {
            cout << "Feedback ID: " << feedbackId << endl;
            cout << "University: " << universityName << endl;
            cout << "Feedback: " << feedbackMessage << endl;
            cout << "Date: " << date << endl << endl;
            cout << "Reply Status: Pending " << endl;
            cout << endl;
        }
    }
    feedbackFile.close();
    replyToFeedback();

}

struct Feedback {
    string feedbackID;
    string userid;
    string universityName;
    string feedbackMessage;
    string date;
    string reply; // new field for reply message

};

Feedback* feedbackList = nullptr; // Create a pointer to store feedbacks
int feedbackCount = 0; // Track the number of feedbacks
const int MAX_UNIVERSITIES = 5400;
const int MAX_CUSTOMERS = 5400;

void updateLastField(const string& username) {
    string filename = "feedback.txt";
    ifstream file(filename);
    if (!file) {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    stringstream updatedContent;
    bool updated = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> columns;

        while (getline(ss, item, ',')) {
            columns.push_back(item);
        }

        if (columns.size() >= 2 && columns[0] == username) {
            // Replace the last field with "Replied"
            columns[columns.size() - 1] = "Replied";
            updated = true;
        }

        // Reconstruct the line with modified or original fields
        for (size_t i = 0; i < columns.size(); i++) {
            updatedContent << columns[i];
            if (i != columns.size() - 1) {
                updatedContent << ",";
            }
        }
        updatedContent << endl;
    }

    file.close();

    if (updated) {
        ofstream outputFile(filename);
        if (!outputFile) {
            cout << "Failed to open the file for writing." << endl;
            return;
        }
        outputFile << updatedContent.str();
        outputFile.close();
        cout << "Field  successfully." << endl;
    }
    else {
        cout << "Username not found." << endl;
    }
}

bool compareTimestamps(const Feedback& feedback1, const Feedback& feedback2) {
    return feedback1.date > feedback2.date;
}

void replyToFeedback() {
    string feedbackId;
    cout << "Enter the Feedback ID you want to Reply To (Enter N to cancel the function): ";
    cin >> feedbackId;
    cin.ignore(); // Ignore the newline character

    ifstream feedbackFile("feedback.txt");
    ofstream replyFile("reply.txt", ios::app);

    if (!feedbackFile || !replyFile) {
        cout << "Failed to open files. Please try again later." << endl;
        return;
    }

    bool feedbackFound = false;
    if (feedbackId == "N" || feedbackId == "n") {
        feedbackFile.close();
        replyFile.close(); // Exit the loop if user chooses not to try again
    }
    string line;
    while (getline(feedbackFile, line)) {

        istringstream iss(line);
        string id, universityName, feedbackMessage, date, userid, stat;
        getline(iss, id, ',');
        getline(iss, userid, ',');
        getline(iss, universityName, ',');
        getline(iss, feedbackMessage, ',');
        getline(iss, date, ',');
        getline(iss, stat);

        if (id == feedbackId) {
            string replyMessage;
            cout << "Enter your reply message: ";
            getline(cin, replyMessage);
            addReplyNode(id, universityName, feedbackMessage, date, replyMessage);
            updateLastField(userid);
            feedbackFound = true;
            break;
        }
    }

    if (!feedbackFound) {
        cout << "No feedback found with the provided ID." << endl;
    }

    feedbackFile.close();
    replyFile.close();
}

void displayAdminReplies()
{

    cout << endl << string(25, '=') << "Replied Feedbacks of MoHE" << string(25, '=') << endl;

    ifstream replyFile("reply.txt");

    if (!replyFile) {
        cout << "No Universities Replied Yet." << endl;
        return;
    }

    string feedbackId, university, feedback, date, reply;
    while (getline(replyFile, feedbackId, ',')) {
        getline(replyFile, university, ',');
        getline(replyFile, feedback, ',');
        getline(replyFile, date, ',');
        getline(replyFile, reply);

        cout << "Feedback Id: " << feedbackId << endl;
        cout << "University: " << university << endl;
        cout << "Feedback: " << feedback << endl;
        cout << "Date and Time: " << date << endl;
        cout << "Reply: " << reply << endl << endl;
    }
    replyFile.close();
}

void retrieveFeedbacks() {
    ifstream feedbackFile("feedback.txt");
    if (!feedbackFile) {
        cerr << "Failed to open feedback file." << endl;
        return;
    }

    feedbackCount = 0; // Reset the feedback count
    feedbackList = new Feedback[100];

    string line;
    while (getline(feedbackFile, line)) {
        istringstream iss(line);
        string feedbackID, userid, universityName, feedbackMessage, date;
        getline(iss, feedbackID, ',');
        getline(iss, userid, ',');
        getline(iss, universityName, ',');
        getline(iss, feedbackMessage, ',');
        getline(iss, date, ',');

        // Create a new feedback and add it to the feedback list
        Feedback feedback;
        feedback.feedbackID = feedbackID;
        feedback.userid = userid;
        feedback.universityName = universityName;
        feedback.feedbackMessage = feedbackMessage;
        feedback.date = date;

        feedbackList[feedbackCount] = feedback;
        feedbackCount++;

        // Resize the feedbackList if it's full
        if (feedbackCount == 100) {
            Feedback* temp = new Feedback[feedbackCount * 2];
            memcpy(temp, feedbackList, feedbackCount * sizeof(Feedback));

            delete[] feedbackList;
            feedbackList = temp;
        }
    }

    sort(feedbackList, feedbackList + feedbackCount, compareTimestamps);
    feedbackFile.close();
}

void moveBetweenFeedbacks() {

    retrieveFeedbacks();
    if (feedbackCount == 0) {
        std::cout << "No feedbacks available." << endl;
        return;
    }

    int index = 0;
    char choice;

    do {
        std::cout << "Feedback ID: " << feedbackList[index].feedbackID << endl;
        std::cout << "University: " << feedbackList[index].universityName << endl;
        std::cout << "Feedback: " << feedbackList[index].feedbackMessage << endl;
        std::cout << "Date: " << feedbackList[index].date << endl << endl;


        std::cout << "Enter 'n' to move to the next feedback, 'p' to move to the previous feedback, "
            << "or 'q' to quit: ";
        cin >> choice;
        std::cout << "" << endl;

        if (choice == 'n') {
            index = (index + 1) % feedbackCount; // Move to the next feedback
        }
        else if (choice == 'p') {
            index = (index - 1 + feedbackCount) % feedbackCount; // Move to the previous feedback
        }
    } while (choice != 'q');


}

////////////////////// View Your Saved Unis //////////////
void displaySavedUnis(const string& username) {

    cout << endl << string(25, '=') << " Your Favourite Universities " << string(25, '=') << endl;
    cout << "" << endl;

    ifstream SavedFile("saveunis.txt");

    if (!SavedFile) {
        cout << "No Universities Saved." << endl;
        return;
    }

    string SavedId, universityName, location, userid, unirank;
    while (getline(SavedFile, SavedId, ','))
    {
        getline(SavedFile, userid, ',');
        getline(SavedFile, unirank, ',');
        getline(SavedFile, universityName, ',');
        getline(SavedFile, location);

        if (username == userid)
        {
            cout << "University: " << universityName << endl;
            cout << "World Rank: " << unirank << endl;
            cout << "Location: " << location << endl << endl;
        }
    }
    SavedFile.close();
}

void generateReport() {
    //Read the `saveunis.txt` file
    ifstream infile("saveunis.txt");
    if (!infile) {
        // Handle file opening error
        cout << "Error: Could not open the file." << endl;
    }

    // Declare and initialize variables
    const int MAX_SAVE_UNIS = 1000;
    int universityCount[MAX_SAVE_UNIS] = {};
    string universityNames[MAX_SAVE_UNIS];
    string countryNames[MAX_SAVE_UNIS];
    int numSaveUnis = 0;

    // Read the file and populate the arrays
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue; // Skip empty lines
        stringstream ss(line);
        string saveUniID, customerID, universityID, universityName, country;
        getline(ss, saveUniID, ',');
        getline(ss, customerID, ',');
        getline(ss, universityID, ',');
        getline(ss, universityName, ',');
        getline(ss, country);


        // Trim whitespace characters from the universityName and country strings
        universityName.erase(0, universityName.find_first_not_of(" \t\r\n"));
        universityName.erase(universityName.find_last_not_of(" \t\r\n") + 1);
        country.erase(0, country.find_first_not_of(" \t\r\n"));
        country.erase(country.find_last_not_of(" \t\r\n") + 1);

        // Check if the university already exists in the arrays
        bool found = false;
        for (int i = 0; i < numSaveUnis; i++) {
            if (universityNames[i] == universityName && countryNames[i] == country) {
                universityCount[i]++;
                found = true;
                break;
            }
        }

        // Add the university to the arrays if it doesn't already exist
        if (!found) {
            if (universityName.empty() || country.empty()) {
                continue; // Skip empty entries
            }
            universityCount[numSaveUnis] = 1;
            universityNames[numSaveUnis] = universityName;
            countryNames[numSaveUnis] = country;
            numSaveUnis++;
        }
    }

    infile.close();

    // Sort the universities in descending order by the number of times they appear in the saveuni.txt
    for (int i = 0; i < numSaveUnis - 1; i++) {
        for (int j = i + 1; j < numSaveUnis; j++) {
            if (universityCount[i] < universityCount[j]) {
                swap(universityCount[i], universityCount[j]);
                swap(universityNames[i], universityNames[j]);
                swap(countryNames[i], countryNames[j]);
            }
        }
    }

    // Print the report
    cout << "Report of all customers' favorite universities:" << endl;
    for (int i = 0; i < numSaveUnis; i++) {
        cout << i + 1 << ". " << universityNames[i] << ", " << countryNames[i] << " (" << universityCount[i] << " times)" << endl;
        if (i == 9) break; // Show only the top 10 universities
    }
}

////////////////// Modify and Delete User Info //////////////////////

struct User {
    string username;
    string password;
    string userType;
    string name;
    string age;
    string email;
    string lastActivity;
    User* next;
};

void modify(User* head, const string& username) {
    User* current = head;
    while (current != nullptr) {
        if (current->username == username) {
            cout << "Username: " << current->username << endl;
            cout << "Name: " << current->name << endl;
            cout << "Age: " << current->age << endl;
            cout << "Email: " << current->email << endl;
            cout << "Last Activity Date: " << current->lastActivity << endl;
            cout << endl;

            // Modify the user's information
            cout << "What do you want to modify? (name/age/email): ";
            string field;
            cin >> field;

            if (field == "name") {
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, current->name);
            }
            else if (field == "age") {
                cout << "Enter new age: ";
                cin >> current->age;
            }
            else if (field == "email") {
                cout << "Enter new email: ";
                cin.ignore();
                getline(cin, current->email);
            }
            else {
                cout << "Invalid field." << endl;
                return;
            }

            cout << "" << endl;
            cout << "User information Updated Successfully." << endl;
            cout << " --------------------------------------" << endl;
            return;
        }
        current = current->next;
    }

    cout << "User not found." << endl;
}

void displaymodifyUsers(User* head) {
    User* current = head;
    while (current != nullptr) {
        cout << "Username: " << current->username << endl;
        cout << "Name: " << current->name << endl;
        cout << "Age: " << current->age << endl;
        cout << "Email: " << current->email << endl;
        cout << "Last Activity Date: " << current->lastActivity << endl;
        cout << endl;
        current = current->next;
    }
}

void modifier() {
    ifstream usersFile("users.txt");
    if (!usersFile) {
        cout << "No Users available." << endl;
        return;
    }

    User* head = nullptr;
    User* tail = nullptr;

    string username, password, userType, name, age, email, lastActivity;
    while (getline(usersFile, username, ',')) {
        getline(usersFile, password, ',');
        getline(usersFile, userType, ',');
        getline(usersFile, name, ',');
        getline(usersFile, age, ',');
        getline(usersFile, email, ',');
        getline(usersFile, lastActivity);

        User* newUser = new User{ username, password, userType, name, age, email, lastActivity, nullptr };
        if (head == nullptr) {
            head = newUser;
            tail = newUser;
        }
        else {
            tail->next = newUser;
            tail = newUser;
        }
    }

    usersFile.close();

    string modifyUsername;
    cout << "Enter the username to modify: ";
    cin >> modifyUsername;

    modify(head, modifyUsername);

    // Update the users.txt file with the modified user data
    ofstream outFile("users.txt");
    if (outFile) {
        User* current = head;
        while (current != nullptr) {
            outFile << current->username << ","
                << current->password << ","
                << current->userType << ","
                << current->name << ","
                << current->age << ","
                << current->email << ","
                << current->lastActivity << endl;

            current = current->next;
        }

        outFile.close();
    }
    else {
        cerr << "Failed to open users.txt file for writing." << endl;
    }

    // Cleanup: Free memory allocated for the linked list
    User* temp = head;
    while (temp != nullptr) {
        User* nextUser = temp->next;
        delete temp;
        temp = nextUser;
    }

    return;
}

void deleteUser(User*& head, const string& username) {
    User* current = head;
    User* prev = nullptr;

    // Find the user to delete
    while (current != nullptr && current->username != username) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "User not found." << endl;
        return;
    }

    // Update the linked list
    if (prev != nullptr) {
        prev->next = current->next;
    }
    else {
        head = current->next;
    }

    delete current;
    cout << "User deleted successfully." << endl;
    cout << " --------------------------" << endl;
}

void displayUsers(const User* head) {
    const User* current = head;
    while (current != nullptr) {
        cout << "Username: " << current->username << endl;
        cout << "Last Activity: " << current->lastActivity << endl << endl;
        current = current->next;
    }
}

void deletereguser() {
    ifstream usersFile("users.txt");
    if (!usersFile) {
        cout << "No Users available." << endl;
        return;
    }

    User* head = nullptr;
    User* tail = nullptr;

    string username, password, userType, name, age, email, lastActivity;
    while (getline(usersFile, username, ',')) {
        getline(usersFile, password, ',');
        getline(usersFile, userType, ',');
        getline(usersFile, name, ',');
        getline(usersFile, age, ',');
        getline(usersFile, email, ',');
        getline(usersFile, lastActivity);

        User* newUser = new User{
            username, password, userType, name, age, email, lastActivity, nullptr
        };

        if (head == nullptr) {
            head = newUser;
            tail = newUser;
        }
        else {
            tail->next = newUser;
            tail = newUser;
        }
    }

    usersFile.close();

    cout << "Users loaded successfully." << endl << endl;

    // Display usernames and last activity
    displayUsers(head);

    // Example usage: Delete user
    string deleteUsername;
    cout << "Enter the username to delete: ";
    cin >> deleteUsername;
    deleteUser(head, deleteUsername);

    // Update the file with the modified user information
    ofstream outFile("users.txt");
    if (!outFile) {
        cerr << "Failed to open users.txt file for writing." << endl;
        return;
    }

    User* current = head;
    while (current != nullptr) {
        outFile << current->username << ","
            << current->password << ","
            << current->userType << ","
            << current->name << ","
            << current->age << ","
            << current->email << ","
            << current->lastActivity << endl;

        current = current->next;
    }

    outFile.close();

    // Cleanup: Free memory allocated for the linked list
    User* temp = head;
    while (temp != nullptr) {
        User* nextUser = temp->next;
        delete temp;
        temp = nextUser;
    }

    return;
}

void displayRegUsers() {

    cout << endl << string(25, '=') << " Registered Users " << string(25, '=') << endl;
    cout << "" << endl;

    ifstream SavedFile("users.txt");

    if (!SavedFile) {
        cout << "No Users Registered." << endl;
        return;
    }

    string SavedId, pass, type, name, email, date, age;
    while (getline(SavedFile, SavedId, ','))
    {
        getline(SavedFile, pass, ',');
        getline(SavedFile, type, ',');
        getline(SavedFile, name, ',');
        getline(SavedFile, age, ',');
        getline(SavedFile, email, ',');
        getline(SavedFile, date);


        cout << "Username: " << SavedId << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Email: " << email << endl;
        cout << "Last Activity: " << date << endl << endl;

    }
    SavedFile.close();
}
////////// Additional Features ////////////

void financial_calc() {
    double income;

    cout << "Welcome to the Financial Aid Calculator!" << endl;
    cout << "Please enter your annual income: RM ";
    cin >> income;
    cout << "" << endl;

    if (income < 20000) {
        cout << "Congratulations! You are Eligible for a Full Scholarship." << endl;
    }
    else if (income < 50000) {
        cout << "Congratulations! You are Eligible for a Partial Scholarship (50%)." << endl;
    }
    else if (income < 80000) {
        cout << "Congratulations! You are Eligible for a Grant." << endl;
    }
    else {
        cout << "Sorry, based on your income, you are not eligible for financial aid." << endl;
    }
    cout << "Contact MoHE for Further Details" << endl;

    return;
}

int main() {
    int choice;
    ReadUniversityData();
    NormalUsers asd;
    bool exitMenu = false;

    cout << "" << endl;
    cout << "" << endl;
    cout << "             UNIVERSITY RECOMMENDATION SYSTEM" << endl;
    cout << "             ********************************" << endl;
    cout << "" << endl;
    cout << "" << endl;

    while (!exitMenu) {

        displayMainMenu1();
        fflush(stdin);
        cin >> choice;
        processOption(choice);
        if (choice == 4) {
            insertUser();
            insertFeedback();
            saveRepliesToFile();
            SaveUnis();
            exitMenu = true;
        }
        else {
            cout << endl;

        }
    }

    return 0;
}
