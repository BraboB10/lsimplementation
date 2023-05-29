#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <iomanip>
using namespace std;
int main(int argc, char* argv[]) {
    DIR* directory;		//pointer to directroy
	if (argc == 1) {	//if there is not an argument
    	directory = opendir(".");	//open current directory
		cout << endl << "Current Working Dir: " << get_current_dir_name() << endl << endl;	//print current directory
	} 
	else {
    	directory = opendir(argv[1]);	//if there is an argument
		cout << endl << "Current Working Dir: " << get_current_dir_name() << "/" << argv[1] << endl << endl;	//print current directory with the argument directory
	}
    if (directory != NULL) {	//runs if directory exists
        struct dirent* directinfo;	//struct to hold the directory info
        struct stat filestats; // struct to hold file stats
        while ((directinfo = readdir(directory)) != NULL) {		//reads through directory until there is nothing left
            struct stat filestats;	//struct that holds file stats
            string filepath = (argc == 1) ? string("./") + directinfo->d_name : string(argv[1]) + "/" + directinfo->d_name; //gets the file path this helps tell the accurate file sizes when changing to another directory
            stat(filepath.c_str(), &filestats);		//gets file stats
			stat(directinfo->d_name, &filestats);	//gets file stats
            cout << left << setw(10) << (S_ISDIR(filestats.st_mode) ? "DIR " : ""); //Is file a directory?
            cout << ((filestats.st_mode & S_IRUSR) ? "r" : "-"); // Can the owner read this file? Print r if yes and - if no
            cout << ((filestats.st_mode & S_IWUSR) ? "w" : "-"); // Can the owner write in this file? Print w if yes and - if no
            cout << ((filestats.st_mode & S_IXUSR) ? "x" : "-"); // Can the owner execute this file? Print x if yes and - if no
            cout << ((filestats.st_mode & S_IRGRP) ? "r" : "-"); // Can the group read this file? Print r if yes and - if no
            cout << ((filestats.st_mode & S_IWGRP) ? "w" : "-"); // Can the group write in this file? Print w if yes and - if no
            cout << ((filestats.st_mode & S_IXGRP) ? "x" : "-"); // Can the group execute this file? Print x if yes and - if no
            cout << ((filestats.st_mode & S_IROTH) ? "r" : "-"); // Can others read this file? Print r if yes and - if no
            cout << ((filestats.st_mode & S_IWOTH) ? "w" : "-"); // Can others write in this file? Print w if yes and - if no
            cout << ((filestats.st_mode & S_IXOTH) ? "x" : "-"); // Can others execute this file? Print x if yes and - if no
			cout << "   " << setw(40) << directinfo->d_name;	//prints the name of the file
            cout << setw(10) << filestats.st_size; // prints the file size
            cout << setw(20) << ctime(&filestats.st_mtime) << endl;	//prints the last modified date of the file
        }
        closedir(directory);	//closes the directory
    } 
    else {	//if the directory doesn't exist
        cout << "Directory does not exist." << endl;    //prints error message
        return 1;   //exits
    }
    return 0;   //exits
}
