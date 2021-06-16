#include <iostream>
#include <conio.h>
#include <fstream>
#include<sstream>
#include <string.h>
using namespace std;
class Helper                                    //helper class to use stringlength,Getstringfrombuffer and stringcopy function
{
public:
	static void StringConcatenate(char *str1, char *str2)       //append string after string without declaration of new array
	{
		while (*str1 != '\0')
		{
			str1++;                             //to reach end of array
		}
		while (*str2 != '\0')
		{
			*str1 = *str2;                            //place content of str2 in str1
			str1++, str2++;
		}
		*str1 = '\0';                              // null placed to prevent junk values
	}
	static int strlength(char *str)
	{
		int i = 0;
		while (str[i] != 0)
		{
			i++;
		}
		return i;
	}
	static char *Getstringfrombuffer(char *str)
	{
		int size = strlength(str);
		char *temp = new char[size + 1];
		for (int i = 0; i < size; i++)
		{
			temp[i] = str[i];
		}
		temp[size] = '\0';
		return temp;
	}
	static void StringCopy(char* dest, char* src)
	{
		int i = 0;
		for (; src[i] != '\0'; i++)
			dest[i] = src[i];
		dest[i] = '\0';
	}
	
};
class object                    //parent class 
{
private:
	char* ID;
public:
	object()
	{
		ID = 0;
	}
	~object()
	{
		if (ID != 0)
			delete[] ID;
	}
	virtual void setid(int a)
	{
		
	}
	void setID(char *i)
	{
		int size = Helper::strlength(i);
		ID = new char[size + 1];
		Helper::StringCopy(ID, i);
	}
	char *getID()
	{
		return ID;
	}
	virtual void printnameid()    //polymorphism
	{}
	virtual void printname()       //polymorphism
	{}
};
class Date
{
private:
	static Date CurrentDate;
	int day;
	int month;
	int year;
public:
	~Date()
	{}
	Date(int d = 1, int m = 1, int y = 1960)
	{
		day = d;
		month = m;
		year = y;
	}
	static void SetCurrentDate(int d, int m, int y)
	{
		CurrentDate.day = d;
		CurrentDate.month = m;
		CurrentDate.year = y;
	}
	static int GetCurrentDay()
	{
		return CurrentDate.day;
	}
	static int GetCurrentMonth()
	{
		return CurrentDate.month;
	}
	static int GetCurrentYear()
	{
		return CurrentDate.year; 
	}
	static void PrintCurrentDate()
	{ 
		cout << CurrentDate.day << "/" << CurrentDate.month << "/" << CurrentDate.year << endl;
	}
	void setday(int d)
	{
		day = d;
	}
	void setmonth(int m)
	{
		month = m;
	}
	void setyear(int y)
	{
		year = y;
	}
	int getday()
	{
		return day;
	}
	int getmonth()
	{
		return month;
	}
	int getyear()
	{
		return year;
	}
};
Date Date::CurrentDate(1, 1, 1960);
class post;
class page;
class users;
class Date;
class comments;
class comments :public object
{
private:
	char *description;
	object *commentby;
public:
	~comments()
	{
		if (description != 0)
			delete[] description;
	}
	void setid(int a)
	{
		char* temp = new char;
		temp[0] = 'c';
		temp[1] = 0;
		stringstream ss;
		ss << a;
		string newstr = ss.str();
		char* var = new char;
		int i;
		for (i = 0; newstr[i] != 0; i++)
		{
			var[i] = newstr[i];
		}
		var[i] = 0;
		Helper::StringConcatenate(temp, var);
		setID(temp);
	}
	void setdescription(char* c,object *u)
	{
		commentby = u;
		description = c;
	}
	void print()
	{
		commentby->printname();
		cout << description << endl;
	}
	void setcommentby(object *u)
	{
		commentby = u;
	}
	void loadcomments(ifstream& fin3)
	{
		char buffer[80];
		fin3 >> buffer;
		setID(buffer);
	}
	void loaddescription(ifstream& fin3)
	{
		char buffer[80];
		fin3.getline(buffer, 80);
		description = Helper::Getstringfrombuffer(buffer);
	}
};
class post :public object
{
private:
	char* Description;
	int likecount;
	int commentcount;
	object *postby;
	object** Likedby;
	Date Date1;
	comments** Comment;
public:
	~post()
	{
		if (Description != 0)
			delete Description;
	}
	post()
	{
		commentcount = 0;
		likecount = 0;
		Description = 0;
	}
	void setid(int a)
	{
		char* temp = new char;
		temp[0] = 'p';
		temp[1] = 'o';
		temp[2] = 's';
		temp[3] = 't';
		temp[4] = 0;
		stringstream ss;
		ss << a;
		string newstr = ss.str();
		char* var = new char;
		int i;
		for (i = 0; newstr[i] != 0; i++)
		{
			var[i] = newstr[i];
		}
		var[i] = 0;
		Helper::StringConcatenate(temp, var);
		setID(temp);
		/*if (a < 10)
		{
			temp[1] = a;
			temp[2] = 0;
		}
		else
		{
			temp[1] = a + 38;
			temp[2] = a + 38;
			temp[3] = 0;
		}*/
	}
	void setinfo(char *desc, int d, int m, int y)
	{
		Description = desc;
		Date1.setday(d);
		Date1.setmonth(m);
		Date1.setyear(y);
		likecount = 0;
		commentcount = 0;
	}
	char* getdescription()
	{
		return Description;
	}
	void setsharedby(object* u)
	{
		postby = u;
	}
	int searchin(char *u)
	{
		int i;
		for (i = 0; Description[i] != '\0'; i++)
		{
			int j = 0;
			if (Description[i] == u[j])
			{
				while (Description[i] == u[j])
				{
					i++;
					j++;
				}
				if (u[j] == '\0')
				{
					return 1;
				}
			}
		}
		return 0;
	}
	void ViewPostlikes()
	{
		for (int i = 0; i < likecount; i++)
			Likedby[i]->printnameid();
	}
	int getday()
	{
		return Date1.getday();
	}
	int getmonth()
	{
		return Date1.getmonth();
	}
	int getyear()
	{
		return Date1.getyear();
	}
	void print()
	{
		cout << getID();
		cout << "'" << Description << "'"<<endl;
	}
	void printposthome()
	{
		cout << "'" << Description << "'" << endl<<endl;
		//cout << Date1.getday() << "/" << Date1.getmonth() << "/" << Date1.getyear() << endl;
		for (int i = 0; i < commentcount; i++)
			Comment[i]->print();
	}
	void printpost()
	{
		cout << getID();
		cout << "'" << Description << "'";
		cout << Date1.getday() << "/" << Date1.getmonth() << "/" << Date1.getyear() << endl;
		for (int i = 0; i < commentcount; i++)
			Comment[i]->print();
	}
	void setcommentN(object* o, comments* c)
	{
		if (commentcount == 0)
			Comment = new comments*[10];
		else if (commentcount == 10)
			throw out_of_range("Maximum number of comments reached");
		Comment[commentcount] = c;
		Comment[commentcount]->setcommentby(o);
		commentcount++;

	}
	void setcomment(comments *c)
	{
		if (commentcount < 10)
		{
			if (commentcount == 0)
				Comment = new comments*[10];
			Comment[commentcount] = c;
			commentcount++;
		}
		else if  (commentcount >10)
			throw out_of_range("Maximum number of comments reached");
		
	}
	void setlikes(object *a)
	{
		if (likecount < 10)
		{
			if (likecount == 0)
				Likedby = new object*[10];
			Likedby[likecount] = a;
			likecount++;
		}
		else if (likecount>10)
			throw out_of_range("Maximum number of likes reached");
	}
	void setlikestonull()
	{
		Likedby = 0;
	}
	void loadposts(ifstream& fin2)
	{
		char buffer[80];
		fin2.getline(buffer, 80);
		fin2 >> buffer;
		setID(buffer);
		int temp;
		fin2 >> temp;
		Date1.setday(temp);
		fin2 >> temp;
		Date1.setmonth(temp);
		fin2 >> temp;
		Date1.setyear(temp);
		fin2.getline(buffer, 80);
		fin2.getline(buffer, 80);
		Description = Helper::Getstringfrombuffer(buffer);
	}
};
class page :public object
{
private:
	char* Title;
	post** Timeline;
	int posts;
	int Likecount;
public:
	~page()
	{
		if (Title != 0)
			delete[] Title;
		for (int i = 0; i < 10; i++)
			delete Timeline[i];
		delete[] Timeline;
	}
	page()
	{
		posts = 0;
		Title = 0;
		Timeline = 0;
		Likecount = 0;
	}
	int searchinP(char *u)
	{
		int i;
		for (i = 0; Title[i] != '\0'; i++)
		{
			int j = 0;
			if (Title[i] == u[j])
			{
				while (Title[i] == u[j])
				{
					i++;
					j++;
				}

				if (u[j] == '\0')
				{
					return 1;
				}
			}
		}
		return 0;
	}
	void printpost()
	{
		for (int i = 0; i < posts; i++)
		{
			Timeline[i]->printpost();
		}
	}
	void Printlatestposts()
	{
		int day = Date::GetCurrentDay();
		int month = Date::GetCurrentMonth();
		int year = Date::GetCurrentYear();

		for (int i = 0; i < posts; i++)
		{
			int DAY = Timeline[i]->getday();
			int MONTH = Timeline[i]->getmonth();
			int YEAR = Timeline[i]->getyear();
			if (day == DAY && month == MONTH && year == YEAR || day - 1 == DAY && month == MONTH && year == YEAR)
			{
				cout << Title << " shared ";
				Timeline[i]->printposthome();
			}
		}
	}
	void printnameid()
	{
		cout << getID() << "-" << Title << endl;
	}
	void printname()
	{
		cout << Title << " wrote ";
	}
	void name()
	{
		cout << Title << endl;
	}
	void Addposts(post* p)
	{
		if (posts == 0)
		{
			Timeline = new post*[10];
		}
		Timeline[posts] = p;
		posts++;
	}
	void Printlikedpages()
	{
		cout << getID() << "-" << Title << endl;
	}
	void loadpages(ifstream& fin1)
	{
		char buffer[80];
		fin1 >> buffer;
		setID(buffer);
		fin1.getline(buffer, 80);
		Title = Helper::Getstringfrombuffer(buffer);
	}
};

class users :public object
{
private:
	char* fname;
	char* lname;
	char** friendsids;   
	char **LikedpagesID;  
	users** Friendslist;
	page** Likedpages;
	post** Timeline;
	int posts;
	int friends;
	int pages;
	int friendcount;
	int likedpagescount;
public:
	~users()
	{
		if (fname != 0 && lname != 0)
		{
			delete fname;
			delete lname;
		}
		for (int i = 0; i < 10; i++)
			delete Timeline[i];
		delete[] Timeline;
		for (int k = 0; k < friendcount; k++)
			delete friendsids[k];
		delete[] friendsids;
		for (int j = 0; j < likedpagescount; j++)
			delete LikedpagesID[j];
		delete[] LikedpagesID;
	}
	void Printlatestposts()
	{
		int day = Date::GetCurrentDay();
		int month = Date::GetCurrentMonth();
		int year = Date::GetCurrentYear();
		for (int i = 0; i < posts; i++)
		{
			int DAY = Timeline[i]->getday();
			int MONTH = Timeline[i]->getmonth();
			int YEAR = Timeline[i]->getyear();
			if (day == DAY && month == MONTH && year == YEAR || day - 1 == DAY && month == MONTH && year == YEAR)
			{
				cout << fname<<" "<<lname << " shared ";
				Timeline[i]->printposthome();
			}
		}
	}
	void printname()
	{
		cout << fname << " " << lname << " wrote ";
	}
	void printnameid()
	{
		cout << getID() << "-" << fname << " " << lname << endl;
	}
	int searchinU(char *u)
	{
		int i = 0, found = -1;
		while (fname[i] != 0)
		{
			if (fname[i] == u[0])
			{
				int j = 0;
				found = 1;
				while (u[j] != '\0')
				{
					if (u[i + j] != fname[j])
					{
						found = 0;
						break;
					}
					j++;
				}
			}
			i++;
			if (found == 1)
			{
				return 1;
			}
		}
		i = 0, found = -1;
		while (lname[i] != 0)
		{
			if (lname[i] == u[0])
			{
				int j = 0;
				found = 1;
				while (u[j] != '\0')
				{
					if (u[i + j] != lname[j])
					{
						found = 0;
						break;
					}
					j++;
				}
			}
			i++;
			if (found == 1)
			{
				return 1;
			}
		}
		return 0;
	}
	void ViewHomepage()
	{
		for (int i = 0; i < friendcount; i++)
		{
			Friendslist[i]->Printlatestposts();
			cout << endl;
		}
		for (int k = 0; k < likedpagescount; k++)
		{
			Likedpages[k]->Printlatestposts();
			cout << endl;
		}
	}
	void ViewTimeline()
	{
		for (int i = 0; i < posts; i++)
		{
			Timeline[i]->printpost();
			cout << endl;
		}
	}
	
	char** getlikedpages()
	{
		return LikedpagesID;
	}
	void Addposts(post* p)
	{
		if (posts < 10)
		{
			if (posts == 0)
			{
				Timeline = new post*[10];
			}
			Timeline[posts] = p;
			posts++;
		}
		else
			throw out_of_range("Maximum number of posts reached");

	}
	users()
	{
		posts = 0;
		pages = 0;
		friends = 0;
		fname = 0;
		lname = 0;
		friendsids = 0;
		Timeline = 0;
		LikedpagesID = 0;
		friendcount = 0;
		likedpagescount = 0;
	}
	int getfriendcount()
	{
		return friendcount;
	}
	void printinfo()
	{
		cout  << fname << " " << lname << " successfully set as Current User"<<endl;
	}
	int getlikedpagescount()
	{
		return likedpagescount;
	}
	void Addlikedpages(page* p)
	{
		Likedpages[pages] = p;
		pages++;
	}
	void Addfriend(users* a)
	{
		Friendslist[friends] = a;
		friends++;
	}
	void loadusers(ifstream& fin)
	{
		char buffer[80];
		fin >> buffer;
		setID(buffer);
		fin >> buffer;
		fname = Helper::Getstringfrombuffer(buffer);
		fin >> buffer;
		lname = Helper::Getstringfrombuffer(buffer);
		fin >> buffer;
		if (strcmp(buffer, "-1") != 0)
		{
			friendsids = new char*[10];
			for (int i = 0; strcmp(buffer, "-1") != 0; i++)
			{
				Friendslist = new users*[10];
				int size = Helper::strlength(buffer);
				friendsids[i] = new char[size];
				Helper::StringCopy(friendsids[i], buffer);
				fin >> buffer;
				friendcount++;
			}
		}
		else
		{
			friendsids = 0;
		}
		fin >> buffer;
		if (strcmp(buffer, "-1") != 0)
		{
			LikedpagesID = new char*[10];
			for (int i = 0; strcmp(buffer, "-1") != 0; i++)
			{
				Likedpages = new page*[10];
				int size = Helper::strlength(buffer);
				LikedpagesID[i] = new char[size];
				Helper::StringCopy(LikedpagesID[i], buffer);
				fin >> buffer;
				likedpagescount++;
			}
		}
		else
		{
			LikedpagesID = 0;
		}
	}
	void Printfriendslist()
	{
		cout << getID() << "-" << fname << " " << lname << endl;
	}
	char **getfriendsids()
	{
		return friendsids;
	}
	void ViewFriendList()
	{
		for (int i = 0; i < friendcount; i++)
		{
			Friendslist[i]->Printfriendslist();
		}
		cout << endl;
	}
	void ViewLikedPages()
	{
		for (int i = 0; i < likedpagescount; i++)
		{
			Likedpages[i]->Printlikedpages();
		}
		cout << endl;
	}
};

class facebook :public users
{
private:
	users *Currentuser;
	users **TUser;
	page **Tpages;
	post **Tposts;
	comments **Tcomments;
public:
	static Date CurrentDate;
	static int totalusers;
	static int totalpages;
	static int totalposts;
	static int totalcomments;
	facebook()
	{
		Currentuser = 0;
		TUser = 0;
		Tcomments = 0;
		Tpages = 0;
		Tposts = 0;
	}
	~facebook()
	{
		if (Currentuser != 0)
			delete Currentuser;
		for (int i = 0; i < totalusers; i++)
			delete TUser[i];
		delete[]TUser;
		for (int i = 0; i < totalpages; i++)
			delete Tpages[i];
		delete[]Tpages;
		for (int i = 0; i < totalposts; i++)
			delete Tposts[i];
		delete[]Tposts;
		for (int i = 0; i < totalcomments; i++)
			delete Tcomments[i];
		delete[] Tcomments;
	}
	void ViewPage(char *u)
	{
		int index = Returnindex(u);
		Tpages[index - 1]->name();
		cout << endl << endl;
		Tpages[index-1]->printpost();
	}
	void ViewPostlikes(char *u)
	{
		int index = ReturnIndex(u);
		Tposts[index-1]->ViewPostlikes();
	}
	void search(char* s)                           
	{
		int found = 0;
		for (int i = 0; i < totalusers; i++)
		{
			int temp = TUser[i]->searchinU(s);
			if (temp == 1)
			{
				found = 1;
				TUser[i]->printnameid();
			}
		}
		for (int j = 0; j < totalpages; j++)
		{
			int temp = Tpages[j]->searchinP(s);
			if (temp == 1)
			{
				found = 1;
				Tpages[j]->printnameid();
			}
		}
		for (int k = 0; k < totalposts; k++)
		{
			int temp = Tposts[k]->searchin(s);
			if (temp == 1)
			{
				found = 1;
				Tposts[k]->print();
			}
		}
		if (found == 0)
		{
			cout << "No results found" << endl;
		}
	}
	void Loadusers(ifstream& fin)
	{
		fin >> totalusers;
		char buffer[80];
		fin.getline(buffer, 80);

		TUser = new users*[totalusers];
		for (int i = 0; i < totalusers; i++)
		{
			TUser[i] = new users;
		}
		for (int j = 0; j < totalusers; j++)
		{
			TUser[j]->loadusers(fin);
		}
	}
	void Loadpages(ifstream& fin1)
	{
		fin1 >> totalpages;
		char buffer[80];
		fin1.getline(buffer, 80);
		Tpages = new page*[totalpages];
		for (int i = 0; i < totalpages; i++)
		{
			Tpages[i] = new page;
		}
		for (int j = 0; j < totalpages; j++)
		{
			Tpages[j]->loadpages(fin1);
		}
	}
	void Loadposts(ifstream& fin2)
	{
		fin2 >> totalposts;
		char buffer[80];
		for (int i = 0; i < 7; i++)
			fin2.getline(buffer, 80);
		Tposts = new post*[totalposts];
		for (int i = 0; i < totalposts; i++)
		{
			Tposts[i] = new post;
		}
		for (int j = 0; j < totalposts; j++)
		{
			Tposts[j]->loadposts(fin2);
			fin2 >> buffer;
			int temp = Returnindex(buffer) - 1;
			char var1 = Returnchar(buffer);
			if (var1 == 'u')
			{
				TUser[temp]->Addposts(Tposts[j]);
			}
			else
			{
				Tpages[temp]->Addposts(Tposts[j]);
			}
			fin2 >> buffer;
			if (strcmp(buffer, "-1") != 0)
			{
				for (int i = 0; strcmp(buffer, "-1") != 0; i++)
				{
					int temp = Returnindex(buffer) - 1;
					char var = Returnchar(buffer);
					if (var == 'u')
					{
						Tposts[j]->setlikes(TUser[temp]);
					}
					if (var == 'p')
					{
						Tposts[j]->setlikes(Tpages[temp]);
					}
					fin2 >> buffer;
				}
			}
			else
			{
				Tposts[j]->setlikestonull();
			}
			fin2.getline(buffer, 80);
		}
	}
	void Loadcomments(ifstream& fin3)           //load comments
	{
		fin3 >> totalcomments;
		char buffer[150];
		fin3.getline(buffer, 150);
		fin3.getline(buffer, 150);
		Tcomments = new comments*[totalcomments];
		for (int i = 0; i < totalcomments; i++)
		{
			Tcomments[i] = new comments;
		}
		for (int j = 0; j < totalcomments; j++)
		{
			Tcomments[j]->loadcomments(fin3);
			fin3 >> buffer;
			int temp = Returnint(buffer) - 1;
			Tposts[temp]->setcomment(Tcomments[j]);
			fin3 >> buffer;
			int temp2;
			char var = Returnchar(buffer);
			if (var == 'u')
			{
				temp2 = Returnindex(buffer) - 1;
				Tcomments[j]->setcommentby(TUser[temp2]);
			}
			else if (var == 'p')
			{
				temp2 = Returnindex(buffer) - 1;
				Tcomments[j]->setcommentby(Tpages[temp2]);
			}
			Tcomments[j]->loaddescription(fin3);
		}
	}
	int Returnint(char *u)
	{
		return u[4] - 48;
	}
	char Returnchar(char *u)
	{
		return u[0];
	}
	int Returnindex(char *u)
	{
		int size = Helper::strlength(u) - 1;
		int index = 0;
		if (size == 1)
		{
			index = u[1] - 48;
		}
		if (size == 2)
		{
			index = (u[1] - 48) + ((u[2] - 48) + 9);
		}
		return index;
	}
	int ReturnIndex(char *u)
	{
		int size = Helper::strlength(u) - 1;
		int index = 0;
		if (size == 4)
		{
			index = u[4] - 48;
		}
		if (size == 5)
		{
			index = (u[4] - 48) + ((u[5] - 48) + 9);
		}
		return index;
	}
	void SetCurrentUser(char *u)
	{
		int index;
		index = (Returnindex(u));
		Currentuser = TUser[index - 1];
	}
	void linkingusers()
	{
		for (int i = 0; i < totalusers; i++)
		{
			char **temp = TUser[i]->getfriendsids();
			int temp1;
			for (int j = 0; j < TUser[i]->getfriendcount(); j++)
			{
				temp1 = Returnindex(temp[j]) - 1;
				TUser[i]->Addfriend(TUser[temp1]);
			}
		}
	}
	void Likepost(char* u)
	{
		int index = ReturnIndex(u);
		Tposts[index - 1]->setlikes(Currentuser);
	}
	void CommentPost(char *u,char* c)
	{
		int index = ReturnIndex(u);
		int commentid =totalcomments+1;
		comments* a = new comments;
		a->setdescription(c,Currentuser);
		a->setid(commentid);
		for (int i = commentid; i < commentid + 1; i++)
		{
			Tcomments[i] = new comments;
			Tcomments[i] = a;
		}
		totalcomments++;
		Tposts[index - 1]->setcomment(a);
	}
	void Sharepost(char *u)                                //share post from another user to Currentusers Timeline
	{
		int day = Date::GetCurrentDay();
		int month = Date::GetCurrentMonth();
		int year = Date::GetCurrentYear();
		int index = ReturnIndex(u);
		int postid = totalposts+1;
		char* desc = Tposts[index - 1]->getdescription();
		post* p = new post;
		p->setid(postid);
		p->setsharedby(Currentuser);
		p->setinfo(desc, day,month,year);
		for (int i = postid - 1; i < postid + 1; i++)
		{
			Tposts[i] = new post;
			Tposts[i] = p;
		}
		totalposts++;
		Currentuser->Addposts(p);
	}
	void linkingpages()                                     //linkpages
	{
		int temp1;
		for (int k = 0; k < totalusers; k++)
		{
			char**temp = TUser[k]->getlikedpages();
			for (int j = 0; j < TUser[k]->getlikedpagescount(); j++)
			{
				temp1 = Returnindex(temp[j]) - 1;
				TUser[k]->Addlikedpages(Tpages[temp1]);
			}
		}
	}
	void Viewpost(char* u)                          
	{
		int index = ReturnIndex(u);
		Tposts[index - 1]->printpost();
	}
	void Run()
	{
		this->SetCurrentUser("u7");
		Currentuser->printinfo();
		cout << "----------------------------------FriendsList--------------------------------" << endl;
		Currentuser->ViewFriendList();
		cout << "----------------------------------LikedPages--------------------------------" << endl;
		Currentuser->ViewLikedPages();
		cout << "----------------------------------Timeline--------------------------------" << endl;
		Currentuser->ViewTimeline();
		cout << "----------------------------------Homepage--------------------------------" << endl;
		Currentuser->ViewHomepage();
		cout << "----------------------------------ViewPage--------------------------------" << endl;
		this->ViewPage("p5");
		cout << "----------------------------------Search--------------------------------" <<endl;
		this->search("Ali");
		cout << "----------------------------------PostLikes--------------------------------" << endl;
		this->ViewPostlikes("post1");
		cout << "----------------------------------SetLikes--------------------------------" << endl;
		this->Likepost("post1");
		this->ViewPostlikes("post1");
		cout << "----------------------------------Posts--------------------------------" << endl;
		this->Viewpost("post1");
		cout << "----------------------------------SetComment--------------------------------" << endl;
		this->CommentPost("post2", "thanks");
		this->Viewpost("post2");
		cout << "----------------------------------SharePost--------------------------------" << endl;
		this->Sharepost("post4");
		this->Sharepost("post8");
		this->Sharepost("post1");
		cout << "----------------------------------Timeline--------------------------------" << endl;
		Currentuser->ViewTimeline();
	}
};
int facebook::totalusers = 0;
int facebook::totalposts = 0;
int facebook::totalcomments = 0;
int facebook::totalpages = 0;
int main()
{
	ifstream fin("Project-SocialNetworkUers.txt");
	ifstream fin1("Project-SocialNetworkPages.txt");
	ifstream fin2("Project-SocialNetworkPosts.txt");
	ifstream fin3("Project-SocialNetworkComments.txt");
	facebook f;
	Date::SetCurrentDate(15, 11, 2017);
	cout << "System Date:    ";
	Date::PrintCurrentDate();
	f.Loadusers(fin);
	f.Loadpages(fin1);
	f.Loadposts(fin2);
	f.Loadcomments(fin3);
	f.linkingusers();
	f.linkingpages();
	f.Run();
	_getch();
}
