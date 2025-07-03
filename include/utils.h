//Login and registration functions for a train booking system
char login(void);
char login_page(User *user);
void register_page(User** user);
void add_user(User** user, char* username, char* password, char role);
char check_user(User* user, char* username, char* password);

// Train management functions
void add_train(Train** trains);
void view_trains(Train* trains);
