#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string answer = "Answer";
    vector<int> foundCharIndexes;
    int foundCount = 0;
    int lives = 5;

    cout << "Enter the word to guess:"<< "\n";
    cin >> answer;

    while (foundCount < answer.size() && lives > 0)
    {
        char userChoice = ' ';
        bool found = false;
        cout << "Choose a letter..." << "\n";
        cin >> userChoice;

        for (int i = 0; i < answer.length(); i++)
        {
            if (userChoice == answer[i])
            {
                found = true;
                foundCharIndexes.push_back(i);
            }
        }

        if (found == false)
            lives--;

        cout << " \n   Lives Remaining : " << lives << "\n";

        foundCount = 0;
        for (int i = 0; i < answer.length(); ++i)
        {
            if (find(foundCharIndexes.begin(), foundCharIndexes.end(), i) != foundCharIndexes.end())
            {
                cout << answer[i] << " ";
                foundCount++; 
            }
            else
            {
                cout << "_ ";
            }
        }
        cout << "\n";
    }

    if (lives != 0)
        cout << "\nYou found the word!" << "\n";
    else
        cout << "\nYou failed :(" << "\n";

    return 0;
}