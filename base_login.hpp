#ifndef BASELOGIN_H
#define BASELOGIN_H

#include <iostream>
#include "reviewer.hpp"
#include "student.hpp"
#include "student_login.hpp"
#include "reviewer_login.hpp"
#include "mongodb_handler.hpp"

using namespace std;

void base_login_options(){
    cout << "-------------------------------------------------------------\n";
    cout << "1. Already a member of IMG"<<endl;
    cout << "2. Add a new IMG member"<<endl;
    cout << "3. Exit"<<endl;
    cout << "\n(Press 1/2/3)"<<endl;
    cout << "-------------------------------------------------------------\n";
}
void add_imgmember_screen(){
    cout << "-------------------------------------------------------------\n";
    cout << "1. Add Student\n";
    cout << "2. Add Reviewer\n";
    cout << "3. Go back \n";
    cout << "4. Exit \n";
    cout << "-------------------------------------------------------------\n";
}
void already_imgian_screen(){
    cout << "-------------------------------------------------------------"<<endl;
    cout << "1. Login as student"<<endl;
    cout << "2. Login as reviewer"<<endl;
    cout << "3. Exit"<<endl;
    cout << "-------------------------------------------------------------"<<endl;
}
void exit_message(){
    cout<<"-----GOODBYE-----"<<endl;
}
void base_login( img_assgn::MongoDbHandler& mongodb_handler )
{
    while (true)
    {
        base_login_options();
        int baseloginKey;
        cout << "Enter: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> baseloginKey;

        if (baseloginKey == 1)
        {   
            already_imgian_screen(); 
            int imgianKey;
            cout << "Enter: ";
            cin >> imgianKey;
            if (imgianKey == 3)
            {
                exit_message();
                break;
            }
            else if (imgianKey == 1)
            {
                student_login(mongodb_handler);
                break;
            }
            else if (imgianKey == 2)
            {
                reviewer_login(mongodb_handler);
                break;
            }
        }    
        else if (baseloginKey == 2)
        {
            add_imgmember_screen();
            int addmemberKey;
            cout << "Enter: ";
            cin >> addmemberKey;
            if (addmemberKey == 4)
            {
                exit_message();
                break;
            }   
            else if (addmemberKey == 3)
            {
                continue;
            }
            else if (addmemberKey == 2)
            {
                std::string name, password, role;
                int enrollno;
                std::cout<<"\nEnter name : ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(std::cin,name);
                std::cout<<"\nEnter password : ";
                getline(std::cin,password);
                std::cout<<"\nEnter enrollno : ";
                std::cin >> enrollno;

                role = "Reviewer";

                Img_member img_member = Img_member(name, enrollno, role, password);
                mongodb_handler.db_save_img_member(img_member);
                Reviewer reviewer = Reviewer(img_member);
                
                //no function for save to reviewer :(
            }
            else if (addmemberKey == 1)
            {
                std::string name, password, role;
                int enrollno;
                std::cout<<"\nEnter name : ";
                getline(std::cin,name);
                std::cout<<"\nEnter password : ";
                getline(std::cin,password);
                std::cout<<"\nEnter enrollno : ";
                std::cin >> enrollno;

                role = "Student";

                Img_member img_member = Img_member(name, enrollno, role, password);
                mongodb_handler.db_save_img_member(img_member);
                Student student = Student(img_member);
                mongodb_handler.db_save_student(student);
                std::cout<< " saved student ";
                
            }
            else{
                cout<<"choose a valid option!!\n";
            }
        }
        else if (baseloginKey == 3)
        {
            exit_message();
            break;
        }
        else
        {
            cout<<"ENTER A VALID INPUT!"<<endl;
            break;
        }
    }
}
#endif