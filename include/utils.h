// Login and registration functions for a train booking system
char login(void);
char login_page(User *user);
void register_page(User **user);
void add_user(User **user, char *username, char *password, char role);
char check_user(User *user, char *username, char *password);
void save_users(User *user);

// Train management functions
void add_train(Train **trains);
void view_trains(Train *trains);
void delete_train(Train **trains);
void update_train(Train **trains);
void save_trains(Train *trains);