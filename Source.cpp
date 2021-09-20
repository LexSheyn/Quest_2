#include <fmod.hpp>
#include <thread>

#include "file.h"
#include "fullscreen.h"
#include "func.h"
#include "music.h"
#include "time_show.h"
#include "video.h"

int main()
{
    SetConsoleTitle(L"Saga of the Noble Barbarian: Dancing God");

    /*
    HWND consoleWindow = GetConsoleWindow();

    float widthX = 0;
    int width = 0;
    float heightX = 0;
    int height = 0;

    GetDesktopResolution(width, height);

    widthX = width;
    widthX = widthX - (widthX * (986 / widthX));
    heightX = height;
    heightX = heightX - (heightX * (512 / heightX));

    width = int(widthX);
    height = int(heightX);
    
    //std::cout << widthX << "  " << heightX;

    SetWindowPos(consoleWindow, 0, width / 2, height / 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    */
    //=SET=WINDOW=POSITION============================================Begin
    int dWidth;
    int dHeight;
    int cWidth;
    int cHeight;

    RECT desktop;
    RECT console;

    HWND hDesktop = GetDesktopWindow();
    HWND hConWindow = GetConsoleWindow();

    GetWindowRect(hDesktop, &desktop);
    GetWindowRect(hConWindow, &console);

    dWidth = desktop.right;
    dHeight = desktop.bottom;

    cWidth = 980; //console.right;
    cHeight = 510; //console.bottom;

    SetWindowPos(hConWindow, 0, (dWidth/2) - (cWidth/2), (dHeight/2) - (cHeight/1.5), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    //=SET=WINDOW=POSITION==============================================End

    setlocale(LC_ALL, ".1251"); // Печать кириллицы

    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251, шрифт консоли Lucida Console или Consolas
        
    int s = 1;                          // Speed
    int d = 10;                         // Delay
    int t = 1000;                       // Time
    const int game_start = 40;          // First chapter 40
    const int chapters_amount = 155;    // Last chapter number 153
    const int slots = 9;                // Inventory slots amount
    int chapter = game_start;           // Chapter number
    int percent = 0;                    // Percent i from chapters_amount
    int menu_mark = 1;                  // Menu counter
    bool continue_mark = 0;             // If 0: cout, if 1: write()
    bool start_mark = 0;                // If 0: Start, if 1: Restart
    bool sound_menu = 1;                // If 1 - start play sound, if 0 - do nothing
    bool menu_pause = 0;                // Menu pause indicator
    bool next = 0;
    int met_ghost = 0;                  // Meeting with ghost check
    int been_110 = 0;
    int been_108 = 0;
    int been_104 = 0;
    int save_met_ghost = 0;
    int save_been_110 = 0;
    int save_been_108 = 0;
    int save_been_104 = 0;
    std::string str_met_ghost = "(ghost)";  // Ghost
    std::string str_been_110 = "(110)";
    std::string str_been_108 = "(108)";
    std::string str_been_104 = "(104)";    
    int n = 0;                          // Counter for Loading()
    float volume = 0.8;                 // Sound volume    
    float volume_05 = 0.5;              // Sound volume 0.5f
    float vol = 0.8;
    bool vol_up = 0;
    bool vol_down = 0; 
    char a = '0';                       // Answer
    std::string check = " ";            // Checker for choices
    std::string inventory[slots];       // Inventory with 6 slots
    int no_choices_found = 0;
    int resource_loading_failed = 0;
    int counter = 0;    
    bool ESC_HELD = 0;
    //int ESC_PRESSED = 0;
    //int ESC_RELEASED = 0;

    //=ITEMS==========================================================Begin
    std::string item_Millipede_Claw = "Коготь многоножки";
    bool check_item_Millipede_Claw = 0;
    std::string item_Guard_Clothes = "Одеяние стражника";
    bool check_item_Guard_Clothes = 0;
    std::string item_Lucky_Solid = "Счастливый солид";
    bool check_item_Lucky_Solid = 0;
    std::string item_Priest_Talisman = "Талисман жреца";
    bool check_item_Priest_Talisman = 0;
    std::string item_Priest_Chlamys = "Хламида жреца";
    bool check_item_Priest_Chlamys = 0;
    std::string item_Wand = "Жезл";
    bool check_item_Wand = 0;
    std::string item_Silver_Rope = "Серебряная веревка";
    bool check_item_Silver_Rope = 0;
    std::string item_Scroll = "Свиток";
    bool check_item_Scroll = 0;
    //=ITEMS============================================================End

    //=SAVE=GAME======================================================Begin
    int save_chapter = 0;                  // Save chapter number
    std::string save_inventory[slots];     // Save inventory slots
    std::string SAVE[5];
    bool save_mark = 0;
    bool load_mark = 0;
    int SAVE_FILE = 0;
    int SAVE_OK[5] = {0, 0, 0, 0, 0};
    std::string no_data = "< NO DATA >";
    //=SAVE=GAME========================================================End
    
    //=INTRO==========================================================Begin
    bool show_intro = 1;                // If 1: Show intro, if 0: don't show intro
    int intro_number = 0;
    std::string intro[6];
    std::string intro_choice_1 = "> 1: — А можно поподробнее?";
    std::string intro_choice_2 = "> 2: — Конечно не согласен! И не подумаю даже — еще, чего доброго, убьют!";
    //=INTRO============================================================End

    File* file = new File;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    file->path_dialogue = "Resources\\dialogue\\scenario.txt";
    file->path_choice = "Resources\\dialogue\\choice.txt";
    file->path_save_1 = "Resources\\save\\save_1.txt";
    file->path_save_2 = "Resources\\save\\save_2.txt";
    file->path_save_3 = "Resources\\save\\save_3.txt";
    file->path_save_4 = "Resources\\save\\save_4.txt";

    //=LOADING========================================================Begin
    for (int i = 600; i <= 605; i++)
    {        
        if (file->FindDialogue(intro[i - 600], i) == 1)
        {
            resource_loading_failed = 1;
            ClearScreen();
            //std::cerr << "\n\n    ERROR: INTRO IS MISSING";
            break;
        }
    }
  
    std::cout << "\n\n    ";
    std::cout << "Loading dialogues:\t";
    for (int i = 1; i <= chapters_amount; i++)
    {
        if (file->FindDialogue(file->dialogue[i], i) == 1)
        {
            resource_loading_failed = 1;
            break;
        }
        Loading(i, chapters_amount, n);
    }
    n = 0;  // Reset for next Loading() calls

    std::cout << "\n\n    ";
    std::cout << "Loading choices:\t";
    for (int i = 1; i <= chapters_amount; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            if (file->FindChoice(file->choice[i][j], i, j) == 1)
            {
                resource_loading_failed = 1;
                no_choices_found = 1;
                break;
            }
        }

        if (no_choices_found == 1)
        {
            break;
        }

        Loading(i, chapters_amount, n);
    }
    n = 0;  // Reset for next Loading() calls

    for (int SAVE_SLOT = 1; SAVE_SLOT <= 4; SAVE_SLOT++)
    {
        if (file->LoadChapter(save_chapter, SAVE_SLOT) == 1)
        {
            SAVE[SAVE_SLOT] = no_data;
            SAVE_OK[SAVE_SLOT] = 0;
        }
        else if (save_chapter != 0)
        {
            if (file->LoadSavedName(SAVE_SLOT) != "Wrond DT")
            {
                SAVE[SAVE_SLOT] = file->LoadSavedName(SAVE_SLOT);

                SAVE_OK[SAVE_SLOT] = 1;
            }
            else
            {
                SAVE[SAVE_SLOT] = no_data;
                SAVE_OK[SAVE_SLOT] = 0;
            }
        }
        else
        {
            SAVE[SAVE_SLOT] = no_data;
            SAVE_OK[SAVE_SLOT] = 0;
        }        
    }

    if (resource_loading_failed == 1)
    {
        std::cerr << "\n\n    FATAL ERROR: Game resources are not found, press any key to exit";
        a = getch();
        a = '0';
        exit(1);
    }

    //=LOADING==========================================================End    

    //=MUSIC==========================================================Begin
    std::cout << "\n\n    ";
    std::cout << "Music: ";
    SetConsoleTextAttribute(hConsole, 128);
    std::cout << "                 "; // 17 spaces

    FMOD::System* sound_system;
    FMOD::System_Create(&sound_system);

    sound_system->init(100, FMOD_LOOP_NORMAL, 0); // 100 - number of channels available to use simultaneously

    // MENU
    FMOD::Sound* Menu; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\menu.mp3", FMOD_LOOP_NORMAL, 0, &Menu); // Load audio file into memory

    FMOD::Channel* MenuChannel; // Associating channel with audio file
    sound_system->playSound(Menu, 0, true, &MenuChannel); // Play audio file
    //MenuChannel->setLoopCount(-1); // Lopping sound, -1 means repeat endlessly

    MenuChannel->setVolume(volume);

    SetConsoleTextAttribute(hConsole, 240);
    std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
    std::cout << " ";

    // CLICK MENU
    FMOD::Sound* ClickMenu; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\menu_click.mp3", FMOD_DEFAULT, 0, &ClickMenu); // Load audio file into memory

    FMOD::Channel* ClickMenuChannel; // Associating channel with audio file
    sound_system->playSound(ClickMenu, 0, true, &ClickMenuChannel); // Play audio file
    ClickMenuChannel->stop();

    std::cout << "  ";

    // CHOICE
    FMOD::Sound* Choice; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\choice.mp3", FMOD_DEFAULT, 0, &Choice); // Load audio file into memory

    FMOD::Channel* ChoiceChannel; // Associating channel with audio file
    sound_system->playSound(Choice, 0, true, &ChoiceChannel); // Play audio file
    ChoiceChannel->stop();

    std::cout << "  ";

    // NEXT
    FMOD::Sound* NextSound; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\next.mp3", FMOD_DEFAULT, 0, &NextSound); // Load audio file into memory

    FMOD::Channel* NextChannel; // Associating channel with audio file
    sound_system->playSound(NextSound, 0, true, &NextChannel); // Play audio file
    NextChannel->stop();

    std::cout << "  ";

    // INVENORY
    FMOD::Sound* Inventory; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\inventory.mp3", FMOD_DEFAULT, 0, &Inventory); // Load audio file into memory

    FMOD::Channel* InventoryChannel; // Associating channel with audio file
    sound_system->playSound(Inventory, 0, true, &InventoryChannel); // Play audio file
    InventoryChannel->stop();

    std::cout << "  ";

    // INTRO
    FMOD::Sound* IntroSound; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\intro.mp3", FMOD_LOOP_NORMAL, 0, &IntroSound); // Load audio file into memory

    FMOD::Channel* IntroChannel; // Associating channel with audio file
    sound_system->playSound(IntroSound, 0, true, &IntroChannel); // Play audio file
    //IntroChannel->stop();

    std::cout << "  ";

    // MAIN THEME
    FMOD::Sound* MAINSound; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\main_theme.mp3", FMOD_LOOP_NORMAL, 0, &MAINSound); // Load audio file into memory

    FMOD::Channel* MAINChannel; // Associating channel with audio file
    sound_system->playSound(MAINSound, 0, true, &MAINChannel); // Play audio file
    //MAINChannel->stop();

    std::cout << "  ";

    // BATTLE
    FMOD::Sound* BattleSound; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\battle.mp3", FMOD_LOOP_NORMAL, 0, &BattleSound); // Load audio file into memory

    FMOD::Channel* BattleChannel; // Associating channel with audio file
    sound_system->playSound(BattleSound, 0, true, &BattleChannel); // Play audio file
    //BattleChannel->stop();

    std::cout << "  ";

    // BOSS
    FMOD::Sound* BOSSSound; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\BOSS.mp3", FMOD_LOOP_NORMAL, 0, &BOSSSound); // Load audio file into memory

    FMOD::Channel* BOSSChannel; // Associating channel with audio file
    sound_system->playSound(BOSSSound, 0, true, &BOSSChannel); // Play audio file
    //BOSSChannel->stop();

    std::cout << "  ";

    // FINAL
    FMOD::Sound* FinalSound; // Allocating memory for audio file
    sound_system->createSound("Resources\\sounds\\final.mp3", FMOD_LOOP_NORMAL, 0, &FinalSound); // Load audio file into memory

    FMOD::Channel* FinalChannel; // Associating channel with audio file
    sound_system->playSound(FinalSound, 0, true, &FinalChannel); // Play audio file
    //FinalChannel->stop();

    std::cout << "  ";
    SetConsoleTextAttribute(hConsole, 7);
    
    //MenuChannel->setVolume(volume);
    ClickMenuChannel->setVolume(volume);
    ChoiceChannel->setVolume(volume);
    NextChannel->setVolume(volume);
    InventoryChannel->setVolume(volume);
    IntroChannel->setVolume(volume);
    MAINChannel->setVolume(volume);
    BattleChannel->setVolume(volume);
    BOSSChannel->setVolume(volume);
    FinalChannel->setVolume(volume);

    MenuChannel->setPaused(false);
    //=MUSIC============================================================End
        
    ClearScreen();

    for (;;)
    {        
        //=MAIN=MENU======================================================Begin
        while (menu_mark == 1)
        {
            ClearScreen();
                        
            //std::cout << return_current_time_and_date();
            //std::cout << width << " " << height;

            if (menu_mark == 1 and menu_pause == 1)
            {
                MenuChannel->setPaused(false); // Set sound paused if (true), unpaused if (false)
            }
            menu_pause = 1;

            std::cout << "\n\n    ";
            std::cout << "Saga of the Noble Barbarian: Dancing God";
            std::cout << "\n\n    ";
            if (chapter != game_start and chapter != 0)
            {
                std::cout << "\n\n    ";
                std::cout << "[ 1 ] Restart";
                std::cout << "\n\n    ";
                std::cout << "[ 2 ] Continue";
                std::cout << "\n\n    ";
                std::cout << "[ 3 ] Save";
            }
            else
            {
                if (start_mark == 1 and chapter != 0)
                {                    
                    std::cout << "\n\n    ";
                    std::cout << "[ 1 ] Restart";
                    std::cout << "\n\n    ";
                    std::cout << "[ 2 ] Continue";
                    SetConsoleTextAttribute(hConsole, 8); // 8 - Dark
                    std::cout << "\n\n    ";
                    std::cout << "[ 3 ] Save";
                    SetConsoleTextAttribute(hConsole, 7); // 7 - Default

                }
                else
                {
                    std::cout << "\n\n    ";
                    std::cout << "[ 1 ] Start";
                    SetConsoleTextAttribute(hConsole, 8);
                    std::cout << "\n\n    ";
                    std::cout << "[ 2 ] Continue";
                    std::cout << "\n\n    ";
                    std::cout << "[ 3 ] Save";
                    SetConsoleTextAttribute(hConsole, 7);
                }
            }
            if (SAVE_OK[1] == 1 or SAVE_OK[2] == 1 or SAVE_OK[3] == 1 or SAVE_OK[4] == 1)
            {
                std::cout << "\n\n    ";
                std::cout << "[ 4 ] Load";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 8);
                std::cout << "\n\n    ";
                std::cout << "[ 4 ] Load";
                SetConsoleTextAttribute(hConsole, 7);
            }
            std::cout << "\n\n    ";
            std::cout << "[ESC] Exit";
            SetConsoleTextAttribute(hConsole, 8);
            std::cout << "\n\n    ";
            std::cout << "\n\n    ";
            std::cout << "Press [ + ] or [ - ] key to change sound volume";
            std::cout << "\n\n    ";
            std::cout << "Press [ENTER] key to skip animation";
            std::cout << "\n\n    ";
            std::cout << "Press [SPACE] key to access Menu when in game";
            std::cout << "\n\n    ";
            std::cout << "Press [ I ] key to access Inventory when in game";
            std::cout << "\n\n    ";
            std::cout << "Hold  [ESC] key to EXIT";
            SetConsoleTextAttribute(hConsole, 7);

            while (a != '1' and a != '2' and a != '3' and a != '4' and a != 27 and a != ' ')
            {
                a = _getch();

                if (a == '1') // Start or Restart
                {
                    chapter = game_start;

                    for (int i = 0; i < slots; i++)
                    {
                        inventory[i] = "< Empty >";
                    }

                    check_item_Priest_Chlamys = 0;

                    check_item_Millipede_Claw = 0;
 
                    check_item_Guard_Clothes = 0;

                    check_item_Lucky_Solid = 0;
  
                    check_item_Priest_Talisman = 0;

                    check_item_Priest_Chlamys = 0;

                    check_item_Wand = 0;

                    check_item_Silver_Rope = 0;

                    check_item_Scroll = 0;

                    met_ghost = 0;
                    been_110 = 0;
                    been_108 = 0;
                    been_104 = 0;


                    ClearScreen();
                    sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                    ClickMenuChannel->setVolume(vol);
                    std::cout << "\n\n    ";
                    //FlashText("Game started");
                    FlashTextOLD("GAME STARTED");

                    intro_number = 0;
                    start_mark = 1;
                    menu_mark = 2;
                    continue_mark = 0;
                }
                else if (a == '2') // Continue
                {
                    if (start_mark == 1 and chapter != 0)
                    {
                        sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                        ClickMenuChannel->setVolume(vol);
                        continue_mark = 1;
                        menu_mark = 2;
                    }
                    else
                    {
                        a = '0';
                    }
                }
                else if (a == '3') // Save
                {
                    if (chapter != game_start and chapter != 0)
                    {
                        save_mark = 1;
                        load_mark = 0;
                        menu_mark = 4;                    
                    }
                    else
                    {
                        a = '0';
                    }
                }
                else if (a == '4') // Load
                {
                    if (SAVE_OK[1] == 1 or SAVE_OK[2] == 1 or SAVE_OK[3] == 1 or SAVE_OK[4] == 1)
                    {
                        save_mark = 0;
                        load_mark = 1;                        
                        menu_mark = 4;                        
                    }
                    else
                    {
                        a = '0';
                    }
                }
                else if (a == 27) // Exit
                {
                    for (;;)
                    {
                        if (_kbhit())
                        {
                            if (GetAsyncKeyState(VK_ESCAPE) & 1)
                            {
                                counter++;
                                ESC_HELD = 1;
                                
                                if (counter > 2)
                                {
                                    std::cout << " ";
                                }
                            }
                            else
                            {
                                ESC_HELD = 0;
                                counter = 0;

                                SetConsoleTextAttribute(hConsole, 7);
                                
                                break;
                            }
                        }

                        if (counter == 2)
                        {
                            //system("cls");
                            ClearScreen();
                            std::cout << "\n\n    ";

                            SetConsoleTextAttribute(hConsole, 128);

                            for (int i = 0; i < 20; i++)
                            {
                                std::cout << " ";
                            }

                            SetConsoleTextAttribute(hConsole, 7);

                            std::cout << " EXIT";
                            std::cout << "\b\b\b\b\b";

                            SetConsoleTextAttribute(hConsole, 240);

                            for (int i = 0; i < 20; i++)
                            {
                                std::cout << "\b";
                            }
                        }

                        if (counter == 22)
                        {
                            SetConsoleTextAttribute(hConsole, 7);
                            sound_system->release(); // Clear allocated memory
                            exit(0);
                        }

                        Sleep(50);
                    }
                }
                else if (a == ' ')
                {
                    if (start_mark == 1 and chapter != 0)
                    {
                        sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                        ClickMenuChannel->setVolume(vol);
                        continue_mark = 1;
                        menu_mark = 2;
                    }
                    else
                    {
                        a = '0';
                    }
                }
                else if (a == '+')
                {
                    if (vol < 0.8f)
                    {
                        vol = vol + 0.1f;

                        MenuChannel->setVolume(vol);
                        ClickMenuChannel->setVolume(vol);
                        ChoiceChannel->setVolume(vol);
                        NextChannel->setVolume(vol);
                        InventoryChannel->setVolume(vol);
                        IntroChannel->setVolume(vol);
                        MAINChannel->setVolume(vol);
                        BattleChannel->setVolume(vol);
                        BOSSChannel->setVolume(vol);
                        FinalChannel->setVolume(vol);
                    }
                    sound_system->update();
                }
                else if (a == '-')
                {
                    if (vol > 0.2f)
                    {
                        vol = vol - 0.1f;

                        MenuChannel->setVolume(vol);
                        ClickMenuChannel->setVolume(vol);
                        ChoiceChannel->setVolume(vol);
                        NextChannel->setVolume(vol);
                        InventoryChannel->setVolume(vol);
                        IntroChannel->setVolume(vol);
                        MAINChannel->setVolume(vol);
                        BattleChannel->setVolume(vol);
                        BOSSChannel->setVolume(vol);
                        FinalChannel->setVolume(vol);
                    }
                    sound_system->update();
                }
            }
            a = '0';
            
            if (menu_mark != 1 and menu_mark != 4)
            {
                MenuChannel->setPaused(true); // Set sound paused if (true), unpaused if (false)
            }
        }
        a = '0';
        //=MAIN=MENU========================================================End

        //=SAVE=/=LOAD====================================================Begin
        while (menu_mark == 4)
        {
            ClearScreen();
            //system("cls");
            a = '0';

            std::cout << "\n\n    ";

            if (save_mark == 1)
            {
                std::cout << "Saving game:";                
            }

            if (load_mark == 1)
            {
                std::cout << "Loading game:";
            }

            std::cout << "\n\n    ";
            std::cout << "\n\n    ";
            std::cout << "[ 1 ] ";
            if (SAVE[1] == no_data)
            {
                SetConsoleTextAttribute(hConsole, 8);
                std::cout << SAVE[1];
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                std::cout << SAVE[1];
            }

            std::cout << "\n\n    ";
            std::cout << "[ 2 ] ";

            if (SAVE[2] == no_data)
            {
                SetConsoleTextAttribute(hConsole, 8);
                std::cout << SAVE[2];
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                std::cout << SAVE[2];
            }

            std::cout << "\n\n    ";
            std::cout << "[ 3 ] ";

            if (SAVE[3] == no_data)
            {
                SetConsoleTextAttribute(hConsole, 8);
                std::cout << SAVE[3];
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                std::cout << SAVE[3];
            }

            std::cout << "\n\n    ";
            std::cout << "[ 4 ] ";

            if (SAVE[4] == no_data)
            {
                SetConsoleTextAttribute(hConsole, 8);
                std::cout << SAVE[4];
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                std::cout << SAVE[4];
            }

            SetConsoleTextAttribute(hConsole, 8);
            std::cout << "\n\n    ";
            std::cout << "\n\n    ";
            std::cout << "\n\n    ";
            std::cout << "Press [SPACE] key to return to menu";
            SetConsoleTextAttribute(hConsole, 7);

            while (a != ' ' and a != '1' and a != '2' and a != '3' and a != '4')
            {
                a = _getch();
                
                switch (a)
                {
                case '1':
                    SAVE_FILE = 1;
                    break;

                case '2':
                    SAVE_FILE = 2;
                    break;

                case '3':
                    SAVE_FILE = 3;
                    break;

                case '4':
                    SAVE_FILE = 4;
                    break;

                case ' ':
                    SAVE_FILE = 0;
                    menu_mark = 1;
                    break;
                }
            }
                
            if (save_mark == 1)
            {
                if (SAVE_FILE != 0)
                {
                    ClearScreen();
                    sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                    ClickMenuChannel->setVolume(vol);
                    std::cout << "\n\n    ";
                    std::cout << "Saving game: ";

                    file->SaveChapter(chapter, SAVE_FILE);

                    for (int i = 0; i < slots; i++)
                    {
                        file->SaveInventory(inventory[i], i, SAVE_FILE);
                        Loading(i, slots - 1, n);
                    }
                    n = 0;

                    file->SaveRoom(str_met_ghost, met_ghost, SAVE_FILE);
                    file->SaveRoom(str_been_110, been_110, SAVE_FILE);
                    file->SaveRoom(str_been_108, been_108, SAVE_FILE);
                    file->SaveRoom(str_been_104, been_104, SAVE_FILE);

                    SAVE[SAVE_FILE] = file->LoadSavedName(SAVE_FILE);

                    ClearScreen();
                    std::cout << "\n\n    ";
                    std::cout << "Saved";

                    SAVE_OK[SAVE_FILE] = 1;

                    SAVE_FILE = 0;
                }
            }

            if (load_mark == 1)
            {
                if (SAVE_FILE != 0)
                {                    
                    if (SAVE_OK[SAVE_FILE] == 1)
                    {
                        ClearScreen();
                        sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                        ClickMenuChannel->setVolume(vol);
                        std::cout << "\n\n    ";
                        std::cout << "Loading game: ";

                        file->LoadChapter(save_chapter, SAVE_FILE);

                        for (int i = 0; i < slots; i++)
                        {
                            file->LoadInventory(save_inventory[i], i, SAVE_FILE);
                            Loading(i, slots - 1, n);
                        }
                        n = 0;  // Reset for next Loading() calls

                        file->LoadRoom(str_met_ghost, save_met_ghost, SAVE_FILE);
                        file->LoadRoom(str_been_110, save_been_110, SAVE_FILE);
                        file->LoadRoom(str_been_108, save_been_108, SAVE_FILE);
                        file->LoadRoom(str_been_104, save_been_104, SAVE_FILE);

                        chapter = save_chapter;

                        for (int i = 0; i < slots; i++)
                        {
                            inventory[i] = save_inventory[i];

                            if (inventory[i] == "< " + item_Priest_Chlamys + " >")
                            {
                                check_item_Priest_Chlamys = 1;
                            }

                            if (inventory[i] == "< " + item_Millipede_Claw + " >")
                            {
                                check_item_Millipede_Claw = 1;
                            }

                            if (inventory[i] == "< " + item_Guard_Clothes + " >")
                            {
                                check_item_Guard_Clothes = 1;
                            }

                            if (inventory[i] == "< " + item_Lucky_Solid + " >")
                            {
                                check_item_Lucky_Solid = 1;
                            }

                            if (inventory[i] == "< " + item_Priest_Talisman + " >")
                            {
                                check_item_Priest_Talisman = 1;
                            }

                            if (inventory[i] == "< " + item_Priest_Chlamys + " >")
                            {
                                check_item_Priest_Chlamys = 1;
                            }

                            if (inventory[i] == "< " + item_Wand + " >")
                            {
                                check_item_Wand = 1;
                            }

                            if (inventory[i] == "< " + item_Silver_Rope + " >")
                            {
                                check_item_Silver_Rope = 1;
                            }

                            if (inventory[i] == "< " + item_Scroll + " >")
                            {
                                check_item_Scroll = 1;
                            }
                        }

                        met_ghost = save_met_ghost;
                        been_110 = save_been_110;
                        been_108 = save_been_108;
                        been_104 = save_been_104;

                        ClearScreen();
                        std::cout << "\n\n    ";
                        std::cout << "Loaded";

                        Sleep(500);

                        MenuChannel->setPaused(true); // Set sound paused if (true), unpaused if (false)

                        start_mark = 1;
                        menu_mark = 2;

                        break;
                    }
                    SAVE_FILE = 0;
                }
            }
        }
        save_mark = 0;
        load_mark = 0;
        a = '0';
        //=SAVE=/=LOAD======================================================End

        while (menu_mark == 2)
        {
            ClearScreen();
            //=INTRO==========================================================Begin
            if (chapter != game_start)
            {
                show_intro = 0;
            }

            if (show_intro == 1)
            {
                IntroChannel->setPaused(false);
                if (intro_number < 5)
                {
                    if (continue_mark == 1)
                    {
                        std::cout << intro[intro_number];
                    }
                    else
                    {
                        WriteTEST(intro[intro_number], a);
                    }

                    NextIntroTEST(a, menu_mark, intro_number);
                    
                    if (a == ' ')
                    {
                        sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                        ClickMenuChannel->setVolume(vol);
                        IntroChannel->setPaused(true);
                    }
                    else if (a == 'i' or a == 'I' or a == 'ш' or a == 'Ш')
                    {
                        sound_system->playSound(Inventory, 0, false, &InventoryChannel); // Play audio file
                        InventoryChannel->setVolume(vol);
                    }
                    else
                    {
                        sound_system->playSound(NextSound, 0, false, &NextChannel); // Play audio file
                        NextChannel->setVolume(vol);
                    }
                    a = '0';

                    continue_mark = 0;

                }
                else if (intro_number == 5)
                {
                    if (continue_mark == 1)
                    {                        
                        std::cout << intro[intro_number];
                    }
                    else
                    {
                        WriteTEST(intro[intro_number], a);
                    }
                    std::cout << "\n\n    ";
                    std::cout << intro_choice_1;
                    std::cout << "\n\n    ";
                    std::cout << intro_choice_2;

                    continue_mark = 0;

                    while (a != '1' and a != '2' and a != ' ' and a != 'i' and a != 'I' and a != 'ш' and a != 'Ш')
                    {
                        a = _getch();

                        switch (a)
                        {
                        case '1':
                            ClearScreen();
                            sound_system->playSound(Choice, 0, false, &ChoiceChannel); // Play audio file
                            ChoiceChannel->setVolume(vol);
                            std::cout << "\n\n    ";
                            FlashText(intro_choice_1);
                            show_intro = 0;
                            chapter = 40;
                            break;
                        case '2':
                            ClearScreen();
                            sound_system->playSound(Choice, 0, false, &ChoiceChannel); // Play audio file
                            ChoiceChannel->setVolume(vol);
                            std::cout << "\n\n    ";
                            FlashText(intro_choice_2);
                            show_intro = 0;
                            chapter = 10;
                            break;
                        case ' ':
                            sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                            ClickMenuChannel->setVolume(vol);
                            menu_mark = 1;
                            IntroChannel->setPaused(true);
                            break;
                        }

                        if (a == 'i' or a == 'I' or a == 'ш' or a == 'Ш')
                        {
                            sound_system->playSound(Inventory, 0, false, &InventoryChannel); // Play audio file
                            InventoryChannel->setVolume(vol);
                            menu_mark = 3;
                        }
                    }
                    a = '0';
                }
            }//=INTRO============================================================End
            else
            {
                IntroChannel->setPaused(true);
                IntroChannel->setPosition(0, FMOD_TIMEUNIT_MS);

                if (chapter == 35 or chapter == 105 or chapter == 147 or chapter == 153 or chapter == 154)
                {
                    MAINChannel->setPaused(true);
                    BattleChannel->setPaused(true);
                    BOSSChannel->setPaused(false); // BOSS
                    FinalChannel->setPaused(true);
                }
                else if (chapter == 6 or chapter == 17 or chapter == 23 or chapter == 47 or chapter == 52 or chapter == 67
                    or chapter == 75 or chapter == 78 or chapter == 81 or chapter == 85 or chapter == 87 or chapter == 99
                    or chapter == 106 or chapter == 116 or chapter == 124 or chapter == 132 or chapter == 136 or chapter == 138
                    or chapter == 140 or chapter == 141 or chapter == 144 or chapter == 145 or chapter == 148 or chapter == 150)
                {
                    MAINChannel->setPaused(true);
                    BattleChannel->setPaused(false); // BATTLE
                    BOSSChannel->setPaused(true);
                    FinalChannel->setPaused(true);
                }
                else if (chapter == 155)
                {
                    MAINChannel->setPaused(true);
                    BattleChannel->setPaused(true);
                    BOSSChannel->setPaused(true);
                    FinalChannel->setPaused(false); // FINAL
                }
                else
                {
                    MAINChannel->setPaused(false); // MAIN THEME
                    BattleChannel->setPaused(true);
                    BOSSChannel->setPaused(true);
                    FinalChannel->setPaused(true);
                }
                
                if (chapter == 0)
                {
                    MAINChannel->setPaused(true);
                    BattleChannel->setPaused(true);
                    BOSSChannel->setPaused(true);
                    FinalChannel->setPaused(true);
                    MAINChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    BattleChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    BOSSChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    FinalChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    MenuChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    PlayVideo();
                    Dead(a, menu_mark);
                }
                else if (chapter == 156)
                {
                    MAINChannel->setPaused(true);
                    BattleChannel->setPaused(true);
                    BOSSChannel->setPaused(true);
                    FinalChannel->setPaused(true);
                    MAINChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    BattleChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    BOSSChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    FinalChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    MenuChannel->setPosition(0, FMOD_TIMEUNIT_MS);
                    chapter = game_start;
                    menu_mark = 1;
                    continue_mark = 0;
                    start_mark = 0;
                    show_intro = 1;
                }
                else
                {
                    //=CHECK=INVENTORY===================================Begin
                    if (chapter == 2)
                    {
                        if (check_item_Priest_Chlamys == 0)
                        {
                            for (int i = 0; i < slots; i++)
                            {
                                if (inventory[i] == "< Empty >")
                                {
                                    inventory[i] = "< " + item_Priest_Chlamys + " >";
                                    check_item_Priest_Chlamys = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (chapter == 5)
                    {
                        if (check_item_Lucky_Solid == 0)
                        {
                            for (int i = 0; i < slots; i++)
                            {
                                if (inventory[i] == "< Empty >")
                                {
                                    inventory[i] = "< " + item_Lucky_Solid + " >";
                                    check_item_Lucky_Solid = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (chapter == 75 or chapter == 99)
                    {
                        if (check_item_Millipede_Claw == 0)
                        {
                            for (int i = 0; i < slots; i++)
                            {
                                if (inventory[i] == "< Empty >")
                                {
                                    inventory[i] = "< " + item_Millipede_Claw + " >";
                                    check_item_Millipede_Claw = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (chapter == 76)
                    {
                        if (check_item_Wand == 0)
                        {
                            for (int i = 0; i < slots; i++)
                            {
                                if (inventory[i] == "< Empty >")
                                {
                                    inventory[i] = "< " + item_Wand + " >";
                                    check_item_Wand = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (chapter == 116)
                    {
                        if (check_item_Priest_Talisman == 0)
                        {
                            for (int i = 0; i < slots; i++)
                            {
                                if (inventory[i] == "< Empty >")
                                {
                                    inventory[i] = "< " + item_Priest_Talisman + " >";
                                    check_item_Priest_Talisman = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (chapter == 131)
                    {
                        if (check_item_Silver_Rope == 0)
                        {
                            for (int i = 0; i < slots; i++)
                            {
                                if (inventory[i] == "< Empty >")
                                {
                                    inventory[i] = "< " + item_Silver_Rope + " >";
                                    check_item_Silver_Rope = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (chapter == 135)
                    {
                        if (check_item_Guard_Clothes == 0)
                        {
                            for (int i = 0; i < slots; i++)
                            {
                                if (inventory[i] == "< Empty >")
                                {
                                    inventory[i] = "< " + item_Guard_Clothes + " >";
                                    check_item_Guard_Clothes = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (chapter == 146)
                    {
                        if (check_item_Scroll == 0)
                        {
                            for (int i = 0; i < slots; i++)
                            {
                                if (inventory[i] == "< Empty >")
                                {
                                    inventory[i] = "< " + item_Scroll + " >";
                                    check_item_Scroll = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (chapter == 97 and met_ghost == 0)
                    {
                        met_ghost = 1;
                    }

                    if (chapter == 110 and been_110 == 0)
                    {
                        been_110 = 1;
                    }

                    if (chapter == 108 and been_108 == 0)
                    {
                        been_108 = 1;
                    }

                    if (chapter == 104 and been_104 == 0)
                    {
                        been_104 = 1;
                    }
                    //=CHECK=INVENTORY=====================================End

                    if (continue_mark == 1)
                    {
                        std::cout << file->dialogue[chapter];
                    }
                    else
                    {
                        WriteTEST(file->dialogue[chapter], a);
                    }
                    continue_mark = 0;
                    
                    a = '0';

                    file->CheckChoice(chapter, 1, check);

                    if (check == "0")
                    {

                        NextTEST(a, menu_mark);
                            
                        if (chapter == 10)
                        {
                            sound_system->release(); // Clear allocated memory
                            exit(0);
                        }
                            
                        if (a == ' ')                        
                        {
                            sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                            ClickMenuChannel->setVolume(vol);
                            MAINChannel->setPaused(true);
                            BattleChannel->setPaused(true);
                            BOSSChannel->setPaused(true);
                            FinalChannel->setPaused(true);
                        }
                        else if (a == 'i' or a == 'I' or a == 'ш' or a == 'Ш')
                        {
                            sound_system->playSound(Inventory, 0, false, &InventoryChannel); // Play audio file
                            InventoryChannel->setVolume(vol);
                        }
                        else
                        {
                            sound_system->playSound(NextSound, 0, false, &NextChannel); // Play audio file
                            NextChannel->setVolume(vol);

                            if (chapter == 31)
                            {
                                if (check_item_Guard_Clothes == 1)
                                {
                                    chapter = 51;
                                }
                                else
                                {
                                    chapter = 67;
                                }
                            }
                            else if (chapter == 33)
                            {
                                if (check_item_Guard_Clothes == 1)
                                {
                                    chapter = 53;
                                }
                                else
                                {
                                    chapter = 67;
                                }
                            }
                            else if (chapter == 47)
                            {
                                if (check_item_Wand == 1)
                                {
                                    chapter = 87;
                                }
                                else
                                {
                                    chapter = 23;
                                }
                            }
                            else if (chapter == 154)
                            {
                                if (check_item_Priest_Talisman == 1)
                                {
                                    chapter = 147;
                                }
                                else
                                {
                                    chapter = 105;
                                }
                            }
                            else if (chapter == 145)
                            {
                                if (check_item_Wand == 1)
                                {
                                    chapter = 87;
                                }
                                else
                                {
                                    chapter = 23;
                                }
                            }
                            else
                            {
                                file->FindWay(chapter, 1);
                            }
                        }
                    }
                    else
                    {
                        if (chapter == 39 or chapter == 97)
                        {
                            if (check_item_Millipede_Claw == 1)
                            {
                                SetConsoleTextAttribute(hConsole, 8);
                                std::cout << "\n\n    ";
                                std::cout << file->choice[chapter][1];
                                SetConsoleTextAttribute(hConsole, 7);
                            }
                            else
                            {
                                std::cout << "\n\n    ";
                                std::cout << file->choice[chapter][1];
                            }
                        }
                        else
                        {
                            std::cout << "\n\n    ";
                            std::cout << file->choice[chapter][1];
                        }

                        if (chapter == 5 and check_item_Millipede_Claw == 1)
                        {
                            SetConsoleTextAttribute(hConsole, 8);
                            std::cout << "\n\n    ";
                            std::cout << file->choice[chapter][2];
                            SetConsoleTextAttribute(hConsole, 7);
                        }
                        else
                        {
                            std::cout << "\n\n    ";
                            std::cout << file->choice[chapter][2];
                        }

                        file->CheckChoice(chapter, 3, check);

                        if (check != "0")
                        {
                            std::cout << "\n\n    ";
                            std::cout << file->choice[chapter][3];
                        }
                        else
                        {
                            //cout << "\n\n    NOT FOUND";
                        }

                        file->CheckChoice(chapter, 4, check);

                        if (check != "0")
                        {
                            std::cout << "\n\n    ";
                            std::cout << file->choice[chapter][4];
                        }
                        else
                        {
                            //cout << "\n\n    NOT FOUND";
                        }

                        while (a != '1' and a != '2' and a != '3' and a != '4'
                            and a != ' ' and a != 'i' and a != 'I' and a != 'ш' and a != 'Ш')
                        {
                            a = _getch();

                            switch (a)
                            {
                            case '1':
                                if (chapter == 39 or chapter == 97)
                                {
                                    if (check_item_Millipede_Claw == 1)
                                    {
                                        a = '0';
                                        break;
                                    }
                                }

                                ClearScreen();
                                sound_system->playSound(Choice, 0, false, &ChoiceChannel); // Play audio file
                                ChoiceChannel->setVolume(vol);
                                std::cout << "\n\n    ";
                                FlashText(file->choice[chapter][1]);
                                
                                if (chapter == 108)
                                {
                                    if (been_108 == 1)
                                    {
                                        chapter = 144;
                                        break;
                                    }
                                }

                                file->FindWay(chapter, 1);
                                break;
                            case '2':
                                if (chapter == 5 and check_item_Millipede_Claw == 1)
                                {
                                    a = '0';
                                    break;
                                }
                                ClearScreen();
                                sound_system->playSound(Choice, 0, false, &ChoiceChannel); // Play audio file
                                ChoiceChannel->setVolume(vol);
                                std::cout << "\n\n    ";
                                FlashText(file->choice[chapter][2]);
                                
                                if (chapter == 75 or chapter == 99)
                                {
                                    if (met_ghost == 1)
                                    {
                                        chapter = 79;
                                        break;
                                    }
                                }

                                if (chapter == 117)
                                {
                                    if (met_ghost == 1)
                                    {
                                        chapter = 127;
                                        break;
                                    }
                                }

                                if (chapter == 110)
                                {
                                    if (been_110 == 1)
                                    {
                                        chapter = 144;
                                        break;
                                    }
                                }

                                file->FindWay(chapter, 2);
                                break;
                            case '3':
                                file->CheckChoice(chapter, 3, check);
                                if (check != "0")
                                {
                                    ClearScreen();
                                    sound_system->playSound(Choice, 0, false, &ChoiceChannel); // Play audio file
                                    ChoiceChannel->setVolume(vol);
                                    std::cout << "\n\n    ";
                                    FlashText(file->choice[chapter][3]);
                                    
                                    if (chapter == 5)
                                    {
                                        if (met_ghost == 1)
                                        {
                                            chapter = 59;
                                            break;
                                        }
                                    }

                                    if (chapter == 39)
                                    {
                                        if (met_ghost == 1)
                                        {
                                            chapter = 79;
                                            break;
                                        }
                                    }

                                    if (chapter == 104)
                                    {
                                        if (been_104 == 1)
                                        {
                                            chapter = 144;
                                            break;
                                        }
                                    }

                                    file->FindWay(chapter, 3);
                                    break;
                                }
                                else
                                {
                                    a = '0';
                                    break;
                                }
                            case '4':
                                file->CheckChoice(chapter, 4, check);
                                if (check != "0")
                                {
                                    ClearScreen();
                                    sound_system->playSound(Choice, 0, false, &ChoiceChannel); // Play audio file
                                    ChoiceChannel->setVolume(vol);
                                    std::cout << "\n\n    ";
                                    FlashText(file->choice[chapter][4]);
                                    file->FindWay(chapter, 4);
                                    break;
                                }
                                else
                                {
                                    a = '0';
                                    break;
                                }
                            case ' ':
                                sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                                ClickMenuChannel->setVolume(vol);
                                menu_mark = 1;
                                MAINChannel->setPaused(true);
                                BOSSChannel->setPaused(true); // Set sound paused if (true), unpaused if (false)
                                break;
                            }

                            if (a == 'i' or a == 'I' or a == 'ш' or a == 'Ш')
                            {
                                sound_system->playSound(Inventory, 0, false, &InventoryChannel); // Play audio file
                                InventoryChannel->setVolume(vol);
                                menu_mark = 3;
                            }
                        }
                    }
                }
            }
        }
        a = '0';
        //=INVENTORY======================================================Begin
        while (menu_mark == 3)
        {
            ClearScreen();

            for (int i = 0; i < slots; i++)
            {
                std::cout << "\n\n    ";
                if (inventory[i] == "< Empty >")
                {
                    SetConsoleTextAttribute(hConsole, 8);
                    std::cout << inventory[i];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else
                {
                    std::cout << inventory[i];
                }
            }

            std::cout << "\n\n    ";
            std::cout << "\n\n    ";
            SetConsoleTextAttribute(hConsole, 8);
            std::cout << "Press [ I ] key to close Inventory";
            SetConsoleTextAttribute(hConsole, 7);

            continue_mark = 1;

            while (a != ' ' and a != 'i' and a != 'I' and a != 'ш' and a != 'Ш')
            {
                a = _getch();

                if (a == 'i' or a == 'I' or a == 'ш' or a == 'Ш')
                {
                    sound_system->playSound(Inventory, 0, false, &InventoryChannel); // Play audio file
                    InventoryChannel->setVolume(vol);
                    menu_mark = 2;
                }
                
                if (a == ' ')
                {
                    sound_system->playSound(ClickMenu, 0, false, &ClickMenuChannel); // Play audio file
                    ClickMenuChannel->setVolume(vol);
                    IntroChannel->setPaused(true);
                    menu_mark = 1;
                    MAINChannel->setPaused(true);
                    BattleChannel->setPaused(true);
                    BOSSChannel->setPaused(true);
                    FinalChannel->setPaused(true);
                }
            }
        }
        //=INVENTORY========================================================End
        sound_system->update(); // Save sound information for new cycle or somethng like that...
        a = '0';
    }

    delete file;

    return 0;
}