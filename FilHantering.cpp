#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <windows.h>

using namespace std;

int main() {

    /* Läs och skriv namn till Namn.txt, sortera namnen i alfabetisk ordning för att sedan skriva ut i konsolen*/

    // Öppna filen för skrivning
    ofstream out_file;
    out_file.open("namn.txt", ios::out);

    // Skriv en lista på personer till filen
    out_file << "Viktor" << endl;
    out_file << "Li" << endl;
    out_file << "Göran" << endl;

    // Stäng filen
    out_file.close();

    // Öppna filen för läsning
    ifstream in_file;
    in_file.open("Namn.txt", ios::in);

    // Läs in en lista på personer från filen och sortera dem
    vector<string> namn;
    string name;
    while (in_file >> name) {
        namn.push_back(name);
    }

    in_file.close(); //stäng infile

    sort(namn.begin(), namn.end()); //ittererar från början till slutet

    // Skriv ut den sorterade listan
    for (const auto& namn : namn) {
        cout << namn << ", ";
    }
    cout << endl;

    /* Ta reda på om det går att skriva och läsa från fil*/
    cout << '\n' << endl;

    // Kontrollera om det går att läsa från filen
    ifstream in_fileTest;
    in_fileTest.open("Namn.txt", ios::in);
    if (in_fileTest.good()) {   //returnar true om det har gått till felfritt
        cout << "Det går att läsa från filen" << endl;
    }
    in_fileTest.close();

    // Kontrollera om det går att skriva till filen
    ofstream out_fileTest;
    out_fileTest.open("Namn.txt", ios::out);  //returnerar true om det gått till felfritt
    if (out_fileTest.good()) {
        cout << "Det går att skriva till filen" << endl;
    }
    out_fileTest.close();

    /*Lista filer från en mapp, samt lista alla filer av en viss typ!*/
    cout << '\n' << endl;

    WIN32_FIND_DATA data;
    wchar_t wfilename[MAX_PATH];
    MultiByteToWideChar(CP_UTF8, 0, "C:\\Users\\lilje\\Desktop\\Programing\\Practice\\FilHantering\\FilHantering\\*.txt", -1, wfilename, MAX_PATH);

    HANDLE hFind = FindFirstFile(wfilename, &data);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to find files" << std::endl;
        return 1;
    }

    do {
        std::wcout << data.cFileName << std::endl; //wcout används för att skriva ut wide character strings
    } while (FindNextFile(hFind, &data));

    FindClose(hFind);

    /* hitta längsta ordet i filen svenska-ord.txt samt hitta denn vanligaste bokstaven */
    cout << '\n' << endl;

    // Öppna för att läsa
    std::ifstream file("words.txt");

    // läs in varje ord och håll koll på den längsta hitils
    std::string longest_word;
    std::string word;
    while (file >> word) {
        if (word.length() > longest_word.length()) {
            longest_word = word;
        }
    }

    // skriv ut det längsta ordet
    std::cout << "Längsta ordet är : " << longest_word << std::endl;

    file.close();

    //skriv ut det mest uppkommande bokstaven

    // Öppna filen för läsning
    std::ifstream file1("words.txt");

    // Skapa en map där vi kan hålla koll på hur många gånger varje bokstav förekommer
    std::map<char, int> letter_counts;

    // Läs in varje bokstav i filen och öka räknaren för den bokstaven i mappen
    char letter;
    while (file1 >> letter) {
        ++letter_counts[letter];
    }

    // Sortera mappen efter hur många gånger varje bokstav förekommer
    std::pair<char, int> most_common_letter = *std::max_element(letter_counts.begin(), letter_counts.end(),
        [](const std::pair<char, int>& p1, const std::pair<char, int>& p2) {
            return p1.second < p2.second;
        });

    // Skriv ut den vanligaste bokstaven och hur många gånger den förekom
    std::cout << "Vanligaste bokstaven är: " << most_common_letter.first << std::endl;
    std::cout << "Den uppkom: " << most_common_letter.second << " gånger." << std::endl;
    file1.close();
}
