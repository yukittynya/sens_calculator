#include <iostream>
#include <vector>

struct game_yaw {
    std::string game_name;
    double yaw;
};  

struct user_settings {
    std::string game_name;
    double cm_sens = 0, game_sens = 0, yaw = 0;
    int dpi = 0;

};

user_settings * ptr_user_settings = new user_settings;

std::vector<game_yaw> game_yaws = {
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

const double CM_PER_INCH = 2.54;

//use functions
double calc_cm(int dpi, double sens, double yaw) {
    double cm = (360 / (yaw * sens)) / dpi * CM_PER_INCH;
    cm = static_cast<float>(static_cast<int>(cm * 10.)) / 10.;
    return cm;
}

double get_yaw(std::string game_name) {
    for (std::vector<game_yaw>::iterator itr = game_yaws.begin(); itr != game_yaws.end(); ++itr) {
        if (itr -> game_name == game_name) {
            return itr -> yaw;
        }
    }

    return 0;
}

void add_settings() {
    std::cout << "Enter game:\n";
    std::cin >> ptr_user_settings -> game_name;

    std::cout << "Enter DPI:\n";
    std::cin >> ptr_user_settings -> dpi;

    std::cout << "Enter sensitivity:\n";
    std::cin >> ptr_user_settings -> game_sens;

    ptr_user_settings -> yaw = get_yaw(ptr_user_settings -> game_name);
    ptr_user_settings -> cm_sens = calc_cm(ptr_user_settings -> dpi, ptr_user_settings -> game_sens, ptr_user_settings -> yaw);
}

double convert_sens(double new_yaw) {
    return (360 / (ptr_user_settings -> dpi * (ptr_user_settings -> cm_sens / CM_PER_INCH))) / new_yaw; 
}

//screens
void welcome_screen() {
    system("cls");

    std::cout << "Welcome to yukii's sensitivity calculator\n"
    << "Type 'help' for info\n"
    << "Type 'exit' to exit\n";
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

void cm_screen() {
    system("cls");

    if (ptr_user_settings -> yaw == 0) add_settings();

    std::cout << "CM/360: " << ptr_user_settings -> cm_sens << "\n";

    system("pause");
}

void print_games() {
    system("cls");

    for (std::vector<game_yaw>::iterator itr = game_yaws.begin(); itr != game_yaws.end(); ++itr) {
        std::cout << itr -> game_name << "\n";
    }

    system("pause");
}

void sens_screen() {
    system("cls");

    add_settings();

    system("pause");
}

void convert_screen() {
    std::string user_input;
    double new_yaw = 0, game_sens;

    system("cls");

    if (ptr_user_settings -> yaw == 0) add_settings();

    while (new_yaw == 0) {
        system("cls");

        std::cout << "Enter game to convert to (Current game: " << ptr_user_settings -> game_name << ", Current sensitivity: " << ptr_user_settings -> cm_sens << "cm/360):\n";
        std::cin >> user_input;

        new_yaw = get_yaw(user_input);
    }

    game_sens = convert_sens(new_yaw);
    std::cout << "Game sensitivity: " << game_sens << "\n";

    system("pause");
}

void menu_select(std::string user_input) {
    if (user_input == "help") help_screen();
    if (user_input == "cm") cm_screen();
    if (user_input == "games") print_games();
    if (user_input == "sens") sens_screen();
    if (user_input == "convert") convert_screen();
    if (user_input == "exit") exit(0);
}

int main() {
    std::string user_input; 

    welcome_screen();
    while (std::cin >> user_input) {
        menu_select(user_input);
        welcome_screen();
    }

    delete ptr_user_settings;
    return 0;
}
