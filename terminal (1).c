#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>

int main() {
  
  char personUsing[32];
  char input[256];
  char drive[20];
  char* scanResult;
  char existingDirectories;
  
  int extraDebugging = 0, commandFound = 1, usingDrive;
  
  usingDrive = 1;
  
  strcpy(drive, "hi");
  
  // Initialize personUsing
  printf("What is your name? ");
  scanResult = fgets(personUsing, sizeof(personUsing), stdin);
  if (scanResult == NULL) {
    printf("Error reading input.\n");
    return 1;
  }
  personUsing[strcspn(personUsing, "\n")] = '\0'; // Remove newline character

  printf("Your name is: %s\n", personUsing);

  time_t timeStamp; // Proper type for time

  printf("\n");
  while (usingDrive == 1) {
    timeStamp = time(NULL); // Update timestamp in each iteration
    printf("~/%s$ ", personUsing);
    scanResult = fgets(input, sizeof(input), stdin);

    if (extraDebugging == 1) {
      printf("\nCommand typed: %s", input);
      printf("Command's scan result: %s\n", scanResult);
      printf("Is command found?: %d\n", commandFound);
    }

    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    // sudo ls
    //      ^-command

    // sudominos
    int sudoCommand = 0;
    
    char* command = input;
    if(strncmp(command, "sudo", 4) == 0) {

      if(strlen(command) == 4) {
        // print help for sudo
        printf("Sudo help\n");
        continue;
      }

      if(command[4] == ' ') {
        // command is "sudo ____"
        command = command+5;
        sudoCommand = 1;
      }    
        
    }

    // Handle "name" command
    if (strncmp(command, "name ", 5) == 0) {
      strncpy(personUsing, command + 5, sizeof(personUsing) - 1);
      personUsing[sizeof(personUsing) - 1] = '\0'; // Ensure null termination
      printf("Name updated to: %s\n", personUsing);
      continue;
    }
///
    if (strncmp(command, "extraDebugging = true", 21) == 0) {
      printf("Extra debugging tools enabled!\n");
      extraDebugging = 1;
      continue;
    }

    if (scanResult == NULL) {
      printf("Error reading input.\n");
      return 1;
    }

    // Handle "time" command
    if (strncmp(command, "time", 4) == 0) {
      printf("Last updated time is: %s", ctime(&timeStamp));
      continue;
    }

    // Handle "exit" command
    if (strncmp(command, "exit", 4) == 0) {
      printf("Exited terminal. Choose user to boot into: ");
      scanResult = fgets(command, sizeof(command), stdin);
      if (scanResult == NULL) {
        printf("Error reading input.\n");
        return 1;
      }
      printf("Exiting user %s\n", personUsing);
      return 0;
    }

    if (strncmp(command, "ls", 2) == 0) {
      //printf("Existing files: \n", )
      if(sudoCommand == 1) {
        printf("Viewing hidden files\n");
      }
      
      DIR* dir;

      dir = opendir(".");
      if(dir == NULL) {
        printf("Error reading directory\n");
        continue;
      }


      printf("Found files:\n");
      struct dirent* entry;
      while( (entry=readdir(dir)) != NULL) {
        if (sudoCommand == 0 && entry->d_name[0] == '.') {
          continue; // non-sudo shouldn't see hidden files
        }

        printf("%s\n", entry->d_name);
      }
      closedir(dir);
      printf("\nTip: Use sudo ls to view hidden files\n");
      continue;
    }

    // if first 4 letters are "curl", then,
    // if the string length is 4, then show curl help file
    // if command[5] is ' ', move the command pointer forward, 
    // and process the rest of the command
    if (strncmp(command, "curl ", 4) == 0) {
      if (strlen(command) == 4) {
        printf("Curl is a command that downloads a file using https. Sudo is required.\n");
        continue;
      }
      
      if(command[4] == ' ') {
        if(sudoCommand == 0) {
          printf("Not allowed to curl\n");
          continue;
        }

        command = command + 5;
        printf("Running curl on %s\n", command);

        
        continue;
      }

    }

    if (strncmp(command, "help", 4) == 0) {
      printf("\nls - view files.\ncd - change directory.\nname - name user.\ntime - view time and timestamp.\nexit - exit shell and boot into new user.\nformat - format something. Use help -aurguments to view aurguments.\n");
      continue;
    }
  
    //printf("Command: %s\n", command);
  
    if (strncmp(command, "aurguments help", 15) == 0) {
      printf("\nformat - driver \n");
      continue;
    }
  
    if (strncmp(command, "format driver", 14) == 0) {
      printf("Writting all data to 0...\n");
      usingDrive = 0;
      continue;
    }

    if (strncmp(command, "launch ", 7) == 0) {
      system(command + 7);
      continue;
    }

    if (strncmp(command, "cat ", 4) == 0) {
      printf("\nCat");
      command = command + 4;
      printf(" %s\n", command);

      if (strncmp(command, "help", 4) == 0) {
        printf("Cat is a package manager. Install stuff using cat -S.")
      }

      if (strncmp(command, "-S", 2) == 0) {
        
      }
      
      continue;
    }
    
    // Unknown command
    commandFound = system(command);
  } // end of while
  if (usingDrive == 0) {
    printf("No driver found.\n");
  }
  return 0;  
} 