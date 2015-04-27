#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<algorithm>
#include<time.h>
#include<sstream>

using std:: cout;
using std:: cin;
using std::ifstream;
using std::ofstream;
using std:: endl;
using std::string;
using std::random_shuffle;
using std::stringstream;

int tableTried,score;
string userLoggedIn;

void scoresList(string username)
{
	system("cls");
	int i = 0,writeToScreen = 0;
	ifstream readFile("scores.dat");
	string fileContents[1000];
	while(!readFile.eof())
	{
		readFile>>fileContents[i];
		i++;
	}
	readFile.close();
	if(username == "admin")
	{
		cout<<"This list is arranged in the pattern of:\nUsername\nscore out of 12 for 1 times tables\nscore out of 12 for 2 times tables\n ect\n";
		while(writeToScreen < i)
		{
			cout<< fileContents[writeToScreen]<<endl;
			writeToScreen++;
		}
	}
	else
	{
		while(writeToScreen < i )
		{
			if(fileContents[writeToScreen] == username)
			{
				cout<<"My best scores are:\n";
				cout<<" 1:"<<fileContents[writeToScreen + 1]<<endl;
				cout<<" 2:"<<fileContents[writeToScreen + 2]<<endl;
				cout<<" 3:"<<fileContents[writeToScreen + 3]<<endl;
				cout<<" 4:"<<fileContents[writeToScreen + 4]<<endl;
				cout<<" 5:"<<fileContents[writeToScreen + 5]<<endl;
				cout<<" 6:"<<fileContents[writeToScreen + 6]<<endl;
				cout<<" 7:"<<fileContents[writeToScreen + 7]<<endl;
				cout<<" 8:"<<fileContents[writeToScreen + 8]<<endl;
				cout<<" 9:"<<fileContents[writeToScreen + 9]<<endl;
				cout<<"10:"<<fileContents[writeToScreen + 10]<<endl;
				cout<<"11:"<<fileContents[writeToScreen + 11]<<endl;
				cout<<"12:"<<fileContents[writeToScreen + 12]<<endl;
			}
			writeToScreen++;
		}
	}
}

void userPassList(){
	ifstream readFile("login.dat");
	int i =0,writeI =0;
	string data[2000];
	while(!readFile.eof())
		{
		readFile>>data[i];
		i++;
		}
	system("cls");
	cout<<"The current usernames and passwords on file are:\n";

	while(writeI <= i){
		cout<<data[writeI]<<" "<<data[writeI +1]<<endl;
		writeI = writeI +2;
		}
	readFile.close();
	}

void game()
	{
	system("cls");
	int multiplicationTable[12]={1,2,3,4,5,6,7,8,9,10,11,12},i=0,userTableSelected = 0,userSelection,numberCorrect =0, iteration =0, answer,userAnswer;
	srand(time(NULL));
	random_shuffle(&multiplicationTable[0], &multiplicationTable[11]);
	cout<<endl;
	selection:
	cout<<"What multiplication table would you like to try today? (Between 1 and 12)"<<endl;
	cin>>userTableSelected;
	if(userTableSelected < 13)
	{
		system("cls");
		cout<<"You have chosen "<<userTableSelected<<" time tables\n";
		while(iteration < 12)
		{
			cout<<userTableSelected<<" x "<<multiplicationTable[iteration]<<" =";
			cin>>userAnswer;
			answer = userTableSelected * multiplicationTable[iteration];
			if(userAnswer == answer)
			{
				cout<<"Correct!\n";
				numberCorrect++;
			}
			else
			{
				cout<<"Wrong\n";
			}
			iteration++;
		}
		cout<<"You got "<<numberCorrect<<" correct out of 12\n";
		score = numberCorrect;
		tableTried = userTableSelected;
	}
	else
	{
		cout<<"Please enter a number between 1 and 12\n";
		goto selection;
	}
	}

int writeScorestoFile(string username)
{
	string fileContents[1000];
	ifstream readFile("scores.dat");
	ofstream writeFile;
	int readIteration = 0,writeIteration = 0, modIteration = 0;
	//Read inital file contents
	while(!readFile.eof())
	{
		readFile>>fileContents[readIteration];
		readIteration++;
	}
	readFile.close();
	//Modifies the original file
	while(modIteration < readIteration)
	{
		if(username == fileContents[modIteration])
		{
			// converts strings to ints
			int fileScore;
			stringstream converint(fileContents[modIteration + tableTried]);
			converint >> fileScore;
			if(score > fileScore)
			{
				// converts ints to strings
				stringstream converstr;
				converstr << score;
				cout<<"\nNew HIGHSCORE!\n";
				fileContents[modIteration + tableTried] = converstr.str();
				goto writetofile;
			}
			else
			{
				goto writetofile;
			}
		}
		modIteration++;
	}
	//Write information back to file
	writetofile:
	writeFile.open("scores.dat");
	while(writeIteration < readIteration)
	{
		writeFile<<fileContents[writeIteration]<<endl;		
		writeIteration++;
	}
	writeFile.close();
	return 0;
}

void addUser()
{
	system("cls");
	string username, password,passwordCheck;
	cout<<"Please enter the new username:";
	cin>>username;
	cout<<"Please enter the new password:";
	cin>>password;
	cout<<"Please enter your new password again:";
	cin>>passwordCheck;
	if (password == passwordCheck)
	{

		string fileContents[4000];
		ifstream readFile("login.dat");
		ofstream writeFile;
		int readIteration = 0,writeIteration = 0;
		//Read inital file contents
		while(!readFile.eof())
		{
			readFile>>fileContents[readIteration];
			readIteration++;
		}
		readFile.close();
		//Modifies the original file
		fileContents[readIteration] = username;
		fileContents[readIteration+1] = password;

		//Write information back to file
writetscoresofile:
		writeFile.open("login.dat");
		while(writeIteration <= readIteration +2)
		{
			writeFile<<fileContents[writeIteration]<<endl;		
			writeIteration++;
		}
		writeFile.close();


		// Score file introducted to new user, setting all highscores to 0
		//Read inital file contents
		ifstream readScoreFile("scores.dat");
		string fileScoreContents[4000];
		ofstream writeScoreFile;
		int readScoreIteration = 0,writeScoreIteration = 0, i = 1;
		while(!readScoreFile.eof())
		{
			readScoreFile>>fileScoreContents[readScoreIteration];
			readScoreIteration++;
		}
		readScoreFile.close();
		//Modifies the original file
		fileScoreContents[readScoreIteration] = username;
		string zero = "0";
		while(i <= 12)
		{
			fileScoreContents[readScoreIteration + i] = zero;
			i++;
		}

		//Write information back to file
		writeScoreFile.open("scores.dat");
		while(writeScoreIteration <= readScoreIteration + 12)
		{
			writeScoreFile<<fileScoreContents[writeScoreIteration]<<endl;		
			writeScoreIteration++;
		}
		writeScoreFile.close(); 
		cout<<"Thank you admin, the user "<<username<<" is now in the database\n";
	} 
	else
	{
		cout<<"Sorry the passwords didn't match";
	}
}

 string login()
 {
	int readIteration = 0, compareIteration = 0;
	ifstream logindata("login.dat");
	string username, password, array[4000];
	cout<<"Welcome to the Multiplication arena!\n";
	cout<<"Please enter your username:";
	cin>>username;
	cout<<"Please enter your password:";
	cin>>password;
	system("cls");
	while(!logindata.eof())
		{
			logindata >> array[readIteration];
			readIteration++;
		}
	logindata.close();
	while(compareIteration<readIteration)
		{
		if(username == array[compareIteration])	
			{
			if(password == array[compareIteration +1])
				{
				cout<<"Welcome "<<username<<endl;
				return(username);
				}
			}
		compareIteration++;
		}
	cout<<"Sorry your username and passwords don't match\n";
	return("no");
 }

void main() // Begin Program
{
	int input;
	string username;
	bool loggedIn;
	username = login();
	if(username == "no")
		{
		goto end;
		}
	loggedIn = true;
	if(loggedIn = true)
		{
			userLoggedIn = username;
		if(username == "admin")
			{
	adminSelection:
		cout<<"What would you like to do today?\n";
		cout<<"1. View Username and Password list\n"<<"2. View Statistics\n"<<"3. Add User\n"<<"4. Exit\n";
		cin>>input;
		switch(input)
			{
			case 1:
				userPassList();
				goto adminSelection;
				break;
			case 2:
				scoresList(username);
				goto adminSelection;
				break;
			case 3:
				addUser();
				goto adminSelection;
				break;
			case 4:
				goto end;
				break;
			default:
				cout<<"Please enter a valid option\n";
				system("cls");
				goto adminSelection;
				break;
			}
			}
		else
			{
stdSelection:
		cout<<"What would you like to do today?\n";
		cout<<"1. Times Tables Game\n"<<"2. View my statistics\n"<<"3. Exit\n";
		cin>>input;
		switch(input)
			{
			case 1:
				game();
				writeScorestoFile(username);
				goto stdSelection;
				break;
			case 2:
				scoresList(username);
				goto stdSelection;
				break;
			case 3:
				goto end;
				break;
			default:
				system("cls");
				cout<<"Please enter a valid option\n";
				goto stdSelection;
				break;
			}
			}
		}
	else
		{
		goto end;
		}

	end:
	cout<<"Goodbye"<<endl;
	system("pause");
}