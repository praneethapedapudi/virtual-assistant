#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <ctime>

using namespace std;

// Function to speak a phrase
void speak(const string& phrase) {
    string command = "espeak \"" + phrase + "\"";
    const char *charComm = command.c_str();
    system(charComm);
}

// function to get name of user
string userName(const string& prompt) {
    string input;
    cout << prompt << endl;
    speak(prompt);
    cin >> input;
    return input;
}

// Function to wish the user based on the time of day
void wishUser(const string& name) {
    time_t currTime = time(0);
    tm *lclTime = localtime(&currTime);
    string greeting;

    if (lclTime->tm_hour < 12)
        greeting = "Good Morning " + name;
    else if (lclTime->tm_hour >= 12 && lclTime->tm_hour < 16)
        greeting = "Good Afternoon " + name;
    else
        greeting = "Good Evening " + name;

    cout << greeting << endl;
    speak(greeting);
}

// for web search
void performWebSearch(const string& query) {
    // Encode spaces as '+'
    string encodedQuery = query;
    for (char& c : encodedQuery) {
        if (c == ' ') {
            c = '+';
        }
    }
    string searchURL = "https://www.google.com/search?q=" + encodedQuery;

    // Open the default web browser with the search results
    string openCommand;

    // Platform-specific commands to open the default web browser
#ifdef _WIN32
    openCommand = "start " + searchURL;
#endif

    // Execute the command
    system(openCommand.c_str());
}

// Function to display current time and date
void displayTimeDate() {
    time_t curTime = time(0);
    char *dt = ctime(&curTime);
    cout << "Current time and date is: " << endl << dt << endl;
    speak("Current time and date is " + string(dt));
}
// void performWebSearch(const string &query)
// {
    
//     string encoded=replaceSpaces(query);
//     string searchURL = "https://www.google.com/search?q="+encoded;

//     // Open the default web browser with the search results
//     string openCommand;

// // Platform-specific commands to open the default web browser
// #ifdef _WIN32
//     openCommand = "start " + searchURL;
// #endif

//     // Execute the command
//     system(openCommand.c_str());
// }


int main()
{
    system("cls");

    // fancy ascii text for starting intro

    cout << "  |   | _)        _ _|                                |                      _)   " << endl;
    cout << "  |   |  |          |        _` |  __ `__ \\           |   _` |   __| \\ \\   /  |   __| " << endl;
    cout << "  ___ |  |          |       (   |  |   |   |      \\   |  (   |  |     \\ \\ /   | \\__ \\ " << endl;
    cout << " _|  _| _|  )     ___|     \\__,_| _|  _|  _|     \\___/  \\__,_| _|      \\_/   _| ____/" << endl;
    cout << "           /                                                                         " << endl;

    cout << "<====================  I AM YOUR PERSONAL VIRTUAL ASSISTANT  ===========================>" << endl;
    
    speak("Hi, I am Jarvis. I am your personal virtual assistant. Please enter your name");
    string name = userName("=========================\n| Please enter your name |\n=========================");

    char password[20]; // creating password
    char ch[100];      // to take command from user
    do
    {    
        string enteredPassword = userName("HI " + name + "! PLEASE ENTER YOUR PASSWORD");
        cout<<endl;
        fflush(stdin); //ot getchar();

        // to start apps
        STARTUPINFO startupInfo = {0};
        PROCESS_INFORMATION processInfo = {0};

        if (strcmp(enteredPassword.c_str(), "jarvis") == 0)
        {
            cout << "\n<=============================>\n"
                 << endl;
            wishUser(name);
            do
            {
                cout << endl << "How can I help you " << name << endl << endl;
                speak("How can I help you");
                string query = userName("Your query --->");
                //cin.getline(ch, sizeof(ch));
                //gets(ch);
                cout << "Fetching results for your query--->";
                speak("Fetching results for your query");

                if (query == "hello" || query == "hi")
                {
                   cout << "Hello " << name << endl;
                    speak("Hello " + name + ". Type 'm' or 'M' for the menu");
                }

                else if (query == "m" || query == "M")
                {
                    cout << endl << "Type '1' for guide" << endl;
                    cout << "Type '2' for introduction" << endl;
                    cout << "Type '3' to quit" << endl;
                    cout << "Type '4' for time and date" << endl;
                    cout << "Type '5' for guide to open apps or websites" << endl;
                    cout << "Type '6' for web search" << endl;
                    speak("Type 1 for guide. Type 2 for introduction. Type 3 to quit. Type 4 for time and date. Type 5 for guide to open apps or websites. Type '6' for web search");

                    // cout<<"Press '1' or type 'hi'"<<name<<endl;
                }

                else if (query == "2")
                {
                    cout << "My name is Jarvis. I am a virtual assistant created by Praneetha" << endl;
                    speak("My name is Jarvis. I am a virtual assistant created by Praneetha");
                }

                else if (query == "bye" || query == "3" || query == "stop")
                {
                    cout << "Good Bye, " << name << ". Have a nice day." << endl;
                    speak("Goodbye " + name + ". Have a nice day");
                    exit(0);
                }

                else if (query == "4" || query == "time" || query == "date")
                {
                    // function for time and date
                    displayTimeDate();
                }
                else if (query == "5")
                {
                    cout << "Type 'open <app_name>" << endl
                         << "For example: open google/open notepad" << endl;
                    speak("Type 'open app name'. For example: Open google or Open notepad");
                }
                else if (query == "6")
                {
                    cout << "Type your search query" << endl;
                    speak("Type your search query");
                    string searchQuery;
                    getchar();
                    getline(cin, searchQuery);
                    performWebSearch(searchQuery);
                }

                else if (query == "open notepad")
                {
                    cout << "opening notepad..." << endl;
                    speak("Opening notepad");
                    CreateProcess(TEXT("C:\\Windows\\notepad.exe"), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startupInfo, &processInfo);                    
                }

                else if (query == "open google")
                {
                    cout << "opening google..." << endl;
                    speak("Opening google");
                    system("start https://www.google.com");
                }
                else if(query == "open wikipedia"){
                    cout<<"opening wikipedia..."<<endl;
                    speak("Opening wikipedia");
                    system("start https://www.wikipedia.com");
                }

                else
                {
                    cout << "I am sorry, I couldn't understand your query. Please try again or type m/M for menu" << endl;
                    speak("I am sorry, I couldn't understand your query. Please try again or type m for the menu");
                }

            }while (true);
        }
        else
        {
            cout << "=====================" << endl;
            cout << "| Incorrect password |" << endl;
            cout << "| Please try again   |" << endl;
            speak("Incorrect password. Please try again");

        }
    } while (true);

    return 0;
}