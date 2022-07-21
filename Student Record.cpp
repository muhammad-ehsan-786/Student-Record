#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;
class Student
{
	protected:
		 
		public:
			friend class filing;
};

class Personal_details:public Student
{
	private:
		char name[20], f_name[20], gender[6];
	    long int  cnic;
	    int roll_no;
	    long int  mobile_no;
	    char address[20], religion[10], nationality[10];
	public:
		Personal_details()
		{
			roll_no=0;
			cnic=0;
			mobile_no=0;
		}
		void input_personal()
{
    cout<<"Enter personal details of student"<<endl<<endl<<endl;
    cout<<"Enter the roll no. of student:"<<endl;
    cin>>roll_no;
	cout<<"Enter the Name of Student:";
	cin.ignore();
    cin.getline(name,20);
	cout<<"Enter the Name of Student's Father:"<<endl;
	cin.getline(f_name,20);
	cout<<"Enter the Gender of Student:"<<endl;
	cin.getline(gender,6);
	cin.ignore();
	cout<<"Enter the CNIC of Student:"<<endl;
	cin>>cnic;
	cin.ignore();
	cout<<"Enter the Mobile Number of Student:"<<endl;
	cin>>mobile_no;
	cin.ignore();
	cout<<"Enter the Address of Student:"<<endl;
	cin.getline(address,20);
	cin.ignore();
	cout<<"Enter the Nationality of Student:"<<endl;
	cin.getline(nationality,10);
	cin.ignore();
	cout<<"Enter the Religion of Student:"<<endl;
	cin.getline(religion,10);
	cin.ignore();
}
void show_personal()
{
	cout<<"Roll No. of Student="<<roll_no<<endl;
	cout<<"Name of Student="<<name<<endl;
	cout<<"Name of Student's Father="<<f_name<<endl;
	cout<<"Gender of Student="<<gender<<endl;
	cout<<"CNIC of student="<<cnic<<endl;
	cout<<"Mobile No.="<<mobile_no<<endl;
	cout<<"Address of Student="<<address<<endl;
	cout<<"Nationality of Student="<<nationality<<endl;
	cout<<"Religion of Student="<<religion<<endl;

}
friend class filing;
};
class  Academic_details:public Student
{
	private:
	int semester;
	float prcntg,cgpa;
	public:
		Academic_details()
		{
			semester=0;
			prcntg=0.0;
			cgpa=0.0;
		}
		void input_academic()
{
    cin.ignore();
    cout<<"Enter Semseter no. of Student:"<<endl;
	cin>>semester;
	cout<<"Enter the Percentage of Student:"<<endl;
	cin>>prcntg;
	cout<<"Enter the CGPA of Student:"<<endl;
	cin>>cgpa;
}
void show_acadmic()
{
	cout<<"\n\n\n\n Acadamic Details"<<endl;
	cout<<"Semseter ="<<semester<<endl;
	cout<<"Parcentage="<<prcntg<<endl;
	cout<<"CGPA="<<cgpa<<endl;
}
friend class filing;

};
fstream file;
class filing
{
	public:
	
	void write_student(Personal_details pd,	Academic_details ad)
{

	
	file.open("studentuiit.dat",ios::out|ios::app);
	pd.input_personal();
	ad.input_academic();
	file.write((char*)&pd,sizeof(pd));
	file.write((char*)&ad,sizeof(ad));
	file.close();
}
void display_all(Personal_details pd,	Academic_details ad)
{
	file.open("studentuiit.dat",ios::in);
	while(file.read((char*)&pd,sizeof(pd))&&file.read((char*)&ad,sizeof(ad)))
	{
		pd.show_personal();
		ad.show_acadmic();
		cout<<"\n=============================\n";
		getch();
	}
	file.close();
	getch();
}
void display_sp(Personal_details pd,	Academic_details ad, Student s)
{
	int n;
	cout<<"Enter the roll no. of student you want to search:"<<endl;
	cin>>n;
    int flag=0;
    file.open("studentuiit.dat",ios::in);
    while(file.read((char*)&pd,sizeof(pd))&&file.read((char*)&ad,sizeof(ad)))
    {
        if(pd.roll_no==n)
        {
            system("cls");
            pd.show_personal();
            ad.show_acadmic();
            flag=1;
        }
    }
    file.close();
    if(flag==0)
        cout<<"\n\nrecord not exist";
    getch();
}
void modify_student(Personal_details pd,	Academic_details ad, Student s)
{
    double no,found=0;
    system("cls");
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The roll number of student";
    cin>>no;
     file.open("studentuiit.dat",ios::in|ios::out);
    while(file.read((char*)&pd,sizeof(pd)) && found==0 && file.read((char*)&ad,sizeof(ad)))
    {
        if(pd.roll_no==no)
        {
            pd.show_personal();
            ad.show_acadmic();
            cout<<"\nPlease Enter The New Details of student"<<endl;
            pd.input_personal();
            ad.input_academic();
            double pos=-1*sizeof(ad);
            file.seekp(pos,ios::cur);
            file.write((char*)&pd,sizeof(pd));
            file.write((char*)&ad,sizeof(ad));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    file.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}
void delete_record(Personal_details pd,	Academic_details ad, Student s)
{
	  int no;
    system("cls");
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The roll number of student You Want To Delete";
    cin>>no;
    file.open("studentuiit.dat",ios::in|ios::out);
    fstream file2;
    file2.open("uiit.dat",ios::out);
    file.seekg(0,ios::beg);
    while(file.read((char*)&pd,sizeof(pd))&&file.read((char*)&pd,sizeof(pd)))
    {
        if(pd.roll_no!=no)
      {
            file2.write((char*)&pd,sizeof(pd));
            file2.write((char*)&ad,sizeof(ad));
        }
    }
      file2.close();
    file.close();
    remove("studentuiit.dat");
    rename("uiit.dat","studentuiit.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
}

void show_tabular(Personal_details pd,	Academic_details ad, Student s)
    {
        cout<<setw(4)<<pd.roll_no<<setw(14)<<pd.name<<setw(10)<<ad.prcntg<<"   "<<ad.cgpa<<endl;
    }


void class_result(Personal_details pd,	Academic_details ad,Student s)
{
    system("cls");
    file.open("studentuiit.dat",ios::in);
    if(!file)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout<<"\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
    cout<<"======================================\n";
    cout<<"Roll No.     Name         %age    CGPA\n";
    cout<<"======================================\n";

    while(file.read((char*)&pd,sizeof(pd))&& file.read((char*)&ad,sizeof(ad)))
    {
        show_tabular(pd,ad,s);
    }
    file.close();
    getch();
}

void entry_menu(Personal_details pd,	Academic_details ad,Student s)
{
    system("cls");
    char ch2;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.BACK TO MAIN MENU";
   
    cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    cin>>ch2;
    switch(ch2)
    {
    case '1':
        system("cls");
        write_student(pd,ad);
        break;
    case '2':
        display_all(pd,ad);
        break;
    case '3':
        system("cls");
        display_sp(pd,ad,s);
        break;
    case '4':
        modify_student(pd,ad,s);
        break;
    case '5':
        delete_record(pd,ad,s);
        break;
    case '6':
        break;
    default:
        cout<<"\a";
        entry_menu(pd,ad,s);
    }
}
void result(Personal_details pd,	Academic_details ad,Student s)
{
    int ans,rno;
    char ch;
    system("cls");
    cout<<"\n\n\nRESULT MENU";
    cout<<"\n\n\n1. Class Result\n\n2. Student Report Card\n\n3.Back to Main Menu";
    cout<<"\n\n\nEnter Choice (1/2)? ";
    cin>>ans;
    switch(ans)
    {
    case 1 :
        class_result(pd,ad,s);
        break;
    case 2 :
    {
        do
        {
            system("cls");
            char ans;
            cout<<"\n\nEnter Roll Number Of Student : ";
            cin>>rno;
            display_sp(pd,ad,s);
            cout<<"\n\nDo you want to See More Result (y/n)?";
            cin>>ans;
        }
        while(ans=='y'||ans=='Y');

        break;
    }
    case 3:
        break;
    default:
        cout<<"\a";
    }
}



};

void welcome()

{
	cout<<"\t\t\t\t********                   ********    ******   ******   ************************\n";
	cout<<"\t\t\t\t********                   ********    ******   ******   ************************\n";
	cout<<"\t\t\t\t********                   ********    ******   ******   ************************\n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t********                   ********    ******   ******            ******         \n";
	cout<<"\t\t\t\t***********************************    ******   ******            ******         \n";
	cout<<"\t\t\t\t***********************************    ******   ******            ******         \n";
	cout<<"\t\t\t\t***********************************    ******   ******            ******         \n";	
	
}


int main()
{
	welcome();
 char ch;
    do
    {
    
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. RESULT MENU";
        cout<<"\n\n\t02. ENTRY/EDIT MENU";
        cout<<"\n\n\t03. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        cin>>ch;
        Personal_details pd;
		Academic_details ad;
		Student s;
		filing f;
        switch(ch)
        {
        case '1':
            system("cls");
            f.result(pd,ad,s);
            break;
        case '2':
            f.entry_menu(pd,ad,s);
            break;
        case '3':
            exit(0);
        default :
            cout<<"\a";
        }
    }
    while(ch!='3');
}


