/**
 * @file setup.h
 * @brief Sets up the components of the project. Most functions accept "int argc, char **argv" and return "int"
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_SETUP_H
#define LCOM_PROJ_SETUP_H

/**
 * @brief Cleans up the program by freeing memory, disabling subscriptions and returning to text mode
 * @return int : 0 on success
 */
int (prog_cleanup)();

/**
 * @brief Retrieves the home directory provided by main.c, then prints its content and loads interrupts
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (proj_setup)(int argc, char **argv);

/**
 * @brief This function sets up a penguin
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (penguin_setup)(int argc, char **argv);

/**
 * @brief Debug setup function for the keyboard
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (keyboard_debug_setup)(int argc, char **argv);

/**
 * @brief Test function for the Real Time Clock
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (rtc_test)(int argc, char **argv);

/**
 * @brief Sets up windows (not the OS)
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (windows_setup)(int argc, char **argv);

/**
 * @brief Can either create a chat or transfer a file. Used for standalone purposes (i.e., without the desktop environment)
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (serial_port)(int argc, char **argv);

/**
 * @brief Sets up Inter Process Communication
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int ipc_setup(int argc, char **argv);

#endif /* LCOM_PROJ_SETUP_H */
