/*
 * Header file for functions
 * This file is read before the main code by the compiler, and so,
 * it allow us to make use of this functions before declaring them
 * in the main code.
 * 
 * The use of this kind of files is absolutely optional for small
 * codes/projects like this one, but I find it a good practice to
 * use them anyway.
 */ 

void setup_wifi(void);

void on_message(char *topic, byte *payload, unsigned int length);
void reconnect(void);