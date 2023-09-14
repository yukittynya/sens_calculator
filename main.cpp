#include <iostream>
#include <vector>

struct gameYaws{
    std::string gameName;
    double yaw;
};

struct userSettings{
    std::string gameName;
    double yaw, cm_sens, game_sens;
    int dpi;
};

userSettings USER_SETTINGS;
const double CM_PER_INCH = 2.54;

std::vector<gameYaws> GAME_YAWS = {
    {"Source", 0.022},
    {"CS", 0.022},
    {"Apex", 0.022},
    {"Quake", 0.022},
    {"Overwatch", 0.0066},
        {"ow2", 0.0066},
    {"COD", 0.0066},
    {"Valorant", 0.06996},
        {"val", 0.06996}
};

double calc_cm(int dpi, double sens, double yaw) {
    double cm = (360 / (yaw * sens)) / dpi * CM_PER_INCH;
    cm = static_cast<float>(static_cast<int>(cm * 10.)) / 10.;
    return cm;
}

void print_games() {
    system("cls");
    for (std::vector<gameYaws>::iterator game = GAME_YAWS.begin(); game != GAME_YAWS.end(); ++game) {
        std::cout << game->gameName << "\n";
    }
    system("pause");
}

void help_screen() {
    system("cls");
    std::cout << "This application allows you to calculate the cm/360 of your sensitivity and to convert it between games\n"
    << "Type 'cm' to calculate the cm/360\n"
    << "Type 'convert' to convert to a specific game\n"
    << "Type 'games' to view the list of games\n"
    << "Type 'sens' tp add your sens\n";
    system("pause");
}

void welcome_screen() {
    system("cls");
    std::cout << "Welcome to yukii's sensitivity calculator3\n"
    << "Type 'help' for info\n"
    << "Type 'exit' to exit\n";
}

double get_yaw(std::string game_name) {
    for (std::vector<gameYaws>::iterator game = GAME_YAWS.begin(); game != GAME_YAWS.end(); ++game) {
        if (game -> gameName == game_name) return game -> yaw;
    }

    return 0;
}  

void add_sens() {
    std::string game, user_input;
    int dpi;
    double game_sens, yaw = 0;

    system("cls");
    while (yaw == 0) {
        std::cout << "Enter your game\n";
        std::cin >> game;

        yaw = get_yaw(game);
    }

    std::cout << "Enter your DPI\n";
    std::cin >> dpi;

    std::cout << "Enter your sens\n";
    std::cin >> game_sens;

    USER_SETTINGS.dpi = dpi;
    USER_SETTINGS.game_sens = game_sens;
    USER_SETTINGS.yaw = yaw;
    USER_SETTINGS.gameName = game;
    USER_SETTINGS.cm_sens = calc_cm(dpi, game_sens, yaw);
}

double convert_sens(double yaw) {
    double sens;

    sens = (360 / (USER_SETTINGS.dpi * (USER_SETTINGS.cm_sens / CM_PER_INCH))) / yaw;
    return sens;
}

void convert_screen() {
    if (USER_SETTINGS.cm_sens == 0) add_sens();

    std::string game;
    double yaw = 0;

    while (yaw == 0) {
        system("cls");
        std::cout << "Enter desired game (Type 'games' to see supported games): \n";
        std::cin >> game;

        if (game == "games") print_games();

        yaw = get_yaw(game);
    }

    std::cout << "Your sens in '" << game << "' is: " << convert_sens(yaw) << "\n"; 
    system("pause");
}

void sens_screen() {
    add_sens();
    std::cout << "Sens added\n";
    system("pause");
}

void cm_screen() {
    system("cls");

    if (USER_SETTINGS.cm_sens == 0) add_sens();

    std::cout << "Your sens: " << USER_SETTINGS.cm_sens << "cm/360\n";
    system("pause"); 
}

void menu_select(std::string input) {
    if (input == "help") help_screen();
    if (input == "cm") cm_screen();
    if (input == "games") print_games();
    if (input == "sens") sens_screen();
    if (input == "convert") convert_screen();
}

int main() {
    std::string user_input;

    welcome_screen();
    while (std::cin >> user_input && user_input != "exit") {
        menu_select(user_input);
        welcome_screen();
    }

    return 0;
}
