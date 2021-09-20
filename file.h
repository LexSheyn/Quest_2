#pragma once
#include "func.h"
#include "time_show.h"

class File
{
public:

    std::string dialogue[200];
    std::string choice[200][5];

    std::string path_dialogue;
    std::string path_choice;
    std::string path_save_1;
    std::string path_save_2;
    std::string path_save_3;
    std::string path_save_4;

    // OLD:
    bool FindWord(const std::string filename, const std::string word);
    bool FindWord2(std::string word);
    int Rewrite(std::string file_path, std::string file_text);
    int Write(std::string file_path, std::string file_text);
    int Read(std::string file_path);
    int Read_write(std::string file_path);
    int FindDialogueOLD(std::string mark);
    int ShowDialogueOLD(std::string mark);
    int FindChoiceOLD(std::string mark);
    int CheckChoiceOLD(std::string mark, std::string& indicator);
    int ShowChoiceOLD(std::string mark);
    int FindGoOLD(std::string mark);
    int FindWayOLD(std::string& chapter);

    // TEST:
    int FindDialogue(std::string& dialogue_buffer, int chapter);
    int FindChoice(std::string& choice_buffer, int chapter, int number);
    int CheckChoice(int chapter, int number, std::string& indicator);
    int FindWay(int& chapter, int number);
    int SaveChapter(int chapter, int SAVE_SLOT);
    int SaveRoom(std::string room_name, int check_room, int SAVE_SLOT);
    int SaveInventory(std::string inventory_slot, int slot_number, int SAVE_SLOT);
    int LoadChapter(int& save_chapter, int SAVE_SLOT);
    std::string LoadSavedName(int SAVE_SLOT);
    int LoadRoom(std::string room_name, int& save_room, int SAVE_SLOT);
    int LoadInventory(std::string& save_inventory, int slot_number, int SAVE_SLOT);


    File();
    ~File();
};

File::File(void)
{
    //cerr << "Object is being created" << endl;
}

File::~File(void)
{
    //cerr << "Object is being deleted" << endl;
}

bool File::FindWord(const std::string filename, const std::string word) //
{
    std::string tmp;

    bool result = false;

    std::ifstream file(filename);

    while (file >> tmp)
    {
        if (word == tmp)
        {
            result = true;
        }
    }
    return result;
}

bool File::FindWord2(std::string word) //
{
    std::string tmp;

    bool result = false;

    std::ifstream file("Game\\dialogue\\scenario.txt");

    while (file >> tmp)
    {
        //if (word == tmp)
        if (tmp == word)
        {
            result = true;
        }
    }

    file.close();

    return result;
}

int File::Rewrite(std::string file_path, std::string file_text) //
{
    std::string path = file_path;
    std::string text = file_text;

    std::ofstream out;  // поток для записи

    out.open(path);     // окрываем файл для записи

    if (out.is_open())
    {
        out << text << std::endl;
    }

    out.close();

    return 0;
}

int File::Write(std::string file_path, std::string file_text) //
{
    std::string path = file_path;
    std::string text = file_text;

    std::ofstream out(path, std::ios::app);
    if (out.is_open())
    {
        out << text << std::endl;
    }
    out.close();

    return 0;
}

int File::Read(std::string file_path) //
{
    std::string path = file_path;

    std::string line;

    std::ifstream in(path); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            std::cout << "\n    ";
            std::cout << line;
        }
    }
    in.close();     // закрываем файл

    return 0;
}

int File::Read_write(std::string file_path) //
{
    std::string path = file_path;

    std::string line;

    std::ifstream in(path); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            std::cout << "\n    ";
            //write(line);
        }
    }
    in.close();     // закрываем файл

    return 0;
}

int File::FindDialogueOLD(std::string mark) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '@' + mark + '@';
    std::string f = '#' + mark + '#';

    std::string path = "Game\\dialogue\\scenario.txt";
    std::string path_choice = "Game\\dialogue\\dialogue.txt";

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp + "\n    ";
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    Rewrite(path_choice, "\n\n    " + input);

    return 0;
}

int File::ShowDialogueOLD(std::string mark) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '@' + mark + '@';
    std::string f = '#' + mark + '#';

    std::string path = "Game\\dialogue\\scenario.txt";

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp + "\n    ";
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    //write("\n\n    " + input);

    return 0;
}

int File::FindChoiceOLD(std::string mark) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '$' + mark + '$';
    std::string f = '%' + mark + '%';

    std::string path = "Game\\dialogue\\scenario.txt";
    std::string path_choice = "Game\\dialogue\\choice.txt";

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    Rewrite(path_choice, input);

    return 0;
}

int File::CheckChoiceOLD(std::string mark, std::string& indicator) //
{
    FindChoiceOLD(mark);

    std::string input = "";
    std::string temp = " ";

    std::string f = "&";

    std::string path = "Game\\dialogue\\choice.txt";

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(input.find(f), input.length() - 1);

    indicator = input;

    return 0;
}

int File::ShowChoiceOLD(std::string mark) //
{
    FindChoiceOLD(mark);

    std::string input = "";
    std::string temp = " ";

    std::string f = "&";

    std::string path = "Game\\dialogue\\choice.txt";

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(input.find(f), input.length() - 1);

    std::cout << "\n\n    " << "> " << input;

    return 0;
}

int File::FindGoOLD(std::string mark) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '{' + mark + '}';
    std::string f = '[' + mark + ']';

    std::string path = "Game\\dialogue\\scenario.txt";
    std::string path_choice = "Game\\dialogue\\choice.txt";

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    Rewrite(path_choice, input);

    return 0;
}

int File::FindWayOLD(std::string& chapter) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = "&";

    std::string path = "Game\\dialogue\\choice.txt";

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());

    chapter = input;

    return 0;
}

//==========================================================================(TEST)============
int File::FindDialogue(std::string& dialogue_buffer, int chapter) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '@' + std::to_string(chapter) + '@';
    std::string f = '#' + std::to_string(chapter) + '#';

    std::ifstream in(path_dialogue);

    if (in.fail())
    {
        // I need error message here, like "File not found" etc. -
        // the reason of the failure
        std::cerr << "ERROR: FAILED TO LOAD " << path_dialogue;
        return 1;
    }

    while (!in.eof())
    {
        getline(in, temp);
        input = input + temp + "\n    ";
    }

    in.close();

    input.erase(0, input.find(s) + s.length()); // HIDE NUMBER
    //input.erase(0, input.find(s)); // SHOW NUMBER
    input.erase(input.find(f), input.length() - 1);

    dialogue_buffer = "\n\n    " + input;

    return 0;
}

int File::FindChoice(std::string& choice_buffer, int chapter, int number) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '@' + std::to_string(chapter) + '@' + '(' + std::to_string(number) + ')';
    std::string f = '#' + std::to_string(chapter) + '#';

    std::string f2 = "&";

    std::ifstream in(path_choice);

    if (in.fail())
    {
        // I need error message here, like "File not found" etc. -
        // the reason of the failure
        std::cerr << "ERROR: FAILED TO LOAD " << path_choice;
        return 1;
    }

    while (!in.eof())
    {
        getline(in, temp);
        input = input + temp;
    }

    in.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    input.erase(input.find(f2), input.length() - 1); // HIDE WAY

    choice_buffer = "> " + input;

    return 0;
}

int File::CheckChoice(int chapter, int number, std::string& indicator) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '@' + std::to_string(chapter) + '@' + '(' + std::to_string(number) + ')';
    std::string f = '#' + std::to_string(chapter) + '#';

    std::string f2 = "&";

    std::ifstream in(path_choice);

    while (!in.eof())
    {
        getline(in, temp);
        input = input + temp;
    }

    in.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    input.erase(input.find(f2), input.length() - 1);

    indicator = input;

    return 0;
}

int File::FindWay(int& chapter, int number) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '@' + std::to_string(chapter) + '@' + '(' + std::to_string(number) + ')';
    std::string f = '#' + std::to_string(chapter) + '#';

    std::string f2 = "&";

    std::string path = path_choice;

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    input.erase(0, input.find(f2) + f2.length());

    chapter = std::stoi(input);

    return 0;
}

int File::SaveChapter(int chapter, int SAVE_SLOT) //
{
    std::string path;

    if (SAVE_SLOT == 1)
    {
        path = path_save_1;
    }
    else if (SAVE_SLOT == 2)
    {
        path = path_save_2;
    }
    else if (SAVE_SLOT == 3)
    {
        path = path_save_3;
    }
    else if (SAVE_SLOT == 4)
    {
        path = path_save_4;
    }
        
    std::string save_chapter = "@" + std::to_string(chapter) + "#";

    std::ofstream out;  // поток для записи

    out.open(path);     // окрываем файл для записи

    if (out.is_open())
    {
        //out << "D" << return_current_time_and_date << "T" << "\n" << save_chapter << "\n";
        out << "D" << show_current_time() << "T" << "\n" << save_chapter << "\n";
    }

    out.close();

    return 0;
}

int File::SaveRoom(std::string room_name, int check_room, int SAVE_SLOT) //
{
    std::string path;

    if (SAVE_SLOT == 1)
    {
        path = path_save_1;
    }
    else if (SAVE_SLOT == 2)
    {
        path = path_save_2;
    }
    else if (SAVE_SLOT == 3)
    {
        path = path_save_3;
    }
    else if (SAVE_SLOT == 4)
    {
        path = path_save_4;
    }

    std::string save_room = "$" + room_name + "$" + std::to_string(check_room) + "%" + room_name + "%";

    std::ofstream out(path, std::ios::app);
    if (out.is_open())
    {
        out << save_room << "\n";
    }
    out.close();

    return 0;
}

int File::SaveInventory(std::string inventory_slot, int slot_number, int SAVE_SLOT) //
{
    std::string path;

    if (SAVE_SLOT == 1)
    {
        path = path_save_1;
    }
    else if (SAVE_SLOT == 2)
    {
        path = path_save_2;
    }
    else if (SAVE_SLOT == 3)
    {
        path = path_save_3;
    }
    else if (SAVE_SLOT == 4)
    {
        path = path_save_4;
    }

    std::string save_inventory_slot;

    save_inventory_slot = "[" + std::to_string(slot_number) + "]" + inventory_slot;
    save_inventory_slot = save_inventory_slot + "{" + std::to_string(slot_number) + "}";

    std::ofstream out(path, std::ios::app);
    if (out.is_open())
    {
        out << save_inventory_slot << "\n";
    }
    out.close();

    return 0;
}

int File::LoadChapter(int& save_chapter, int SAVE_SLOT) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = "@";
    std::string f = "#";

    std::string path;

    if (SAVE_SLOT == 1)
    {
        path = path_save_1;
    }
    else if (SAVE_SLOT == 2)
    {
        path = path_save_2;
    }
    else if (SAVE_SLOT == 3)
    {
        path = path_save_3;
    }
    else if (SAVE_SLOT == 4)
    {
        path = path_save_4;
    }

    std::ifstream fin(path);

    if (fin.fail())
    {
        // I need error message here, like "File not found" etc. -
        // the reason of the failure
        //std::cerr << "\tNo saved data";
        return 1;
    }


    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    save_chapter = std::stoi(input);

    return 0;
}

std::string File::LoadSavedName(int SAVE_SLOT) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = "D";
    std::string f = "T";

    std::string path;

    if (SAVE_SLOT == 1)
    {
        path = path_save_1;
    }
    else if (SAVE_SLOT == 2)
    {
        path = path_save_2;
    }
    else if (SAVE_SLOT == 3)
    {
        path = path_save_3;
    }
    else if (SAVE_SLOT == 4)
    {
        path = path_save_4;
    }

    std::ifstream fin(path);

    if (fin.fail())
    {
        // I need error message here, like "File not found" etc. -
        // the reason of the failure
        return "Wrong DT";
    }

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);
        
    return input;
}

int File::LoadRoom(std::string room_name, int& save_room, int SAVE_SLOT) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = "$" + room_name + "$";
    std::string f = "%" + room_name + "%";

    std::string path;

    if (SAVE_SLOT == 1)
    {
        path = path_save_1;
    }
    else if (SAVE_SLOT == 2)
    {
        path = path_save_2;
    }
    else if (SAVE_SLOT == 3)
    {
        path = path_save_3;
    }
    else if (SAVE_SLOT == 4)
    {
        path = path_save_4;
    }

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    save_room = std::stoi(input);

    return 0;
}

int File::LoadInventory(std::string& save_inventory, int slot_number, int SAVE_SLOT) //
{
    std::string input = "";
    std::string temp = " ";

    std::string s = '[' + std::to_string(slot_number) + ']';
    std::string f = '{' + std::to_string(slot_number) + '}';

    std::string path;

    if (SAVE_SLOT == 1)
    {
        path = path_save_1;
    }
    else if (SAVE_SLOT == 2)
    {
        path = path_save_2;
    }
    else if (SAVE_SLOT == 3)
    {
        path = path_save_3;
    }
    else if (SAVE_SLOT == 4)
    {
        path = path_save_4;
    }

    std::ifstream fin(path);

    while (!fin.eof())
    {
        getline(fin, temp);
        input = input + temp;
    }

    fin.close();

    input.erase(0, input.find(s) + s.length());
    input.erase(input.find(f), input.length() - 1);

    save_inventory = input;

    return 0;
}