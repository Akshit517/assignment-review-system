#ifndef REVIWERLOGIN_H
#define REVIEWERLOGIN_H

#include <iostream>
#include "reviewer.hpp"
#include "student.hpp"

#include "mongodb_handler.hpp"

using namespace std;

void reviewer_login_options(){
    cout << "-------------------------------------------------------------\n";
    cout << "what would you like to do?\n\n";
    cout << "1. View Your Details\n";
    cout << "2. Add assignment\n";
    cout << "3. View Students and their assignment status\n";
    cout << "4. View iteration requests\n";
    cout << "5. Change Assignment details\n";
    cout << "6. Exit\n";
    cout << "-------------------------------------------------------------\n";
}
void reviewer_login(img_assgn::MongoDbHandler& mongodbhandler){
    string  pswd;
    int enrollno;
    cout << "-------------------------------------------------------------\n";
    cout << "Enter your Enrollment Number: ";
    cin >> enrollno;
    cout << "Enter your password: ";
    cin >> pswd;

    string foundStudentpswd = mongodbhandler.db_find_password(enrollno,"Reviewer");

    if (pswd == foundStudentpswd)
    {
        while (true)
        {
        cout<<endl;
        reviewer_login_options();
        int key3;
        cout << "Enter: ";
        cin >> key3;
        if (key3 == 1)
        {
            cout << "-------------------------------------------------------------\n";
            //show details
            Img_member member = mongodbhandler.db_load_img_member(enrollno);
            Reviewer reviewer = Reviewer(member);
            reviewer.display_details();
            //will always display empty iteration,etc.
        }
        else if (key3 == 2)
        {
            //add a new assignment
            std::string title, deadline;
            std::cout<< " Enter assignment title : "<<std::endl;
            getline(cin,title);
            std::cout<< " Enter assignment deadline : "<<std::endl;
            getline(cin,deadline);
            Assignment assignment = Assignment(title,  deadline);
            std::string firstTask;
            getline(cin,firstTask); 
            assignment.add_task(firstTask);

            mongodbhandler.db_save_assignment(assignment);
        }
        else if (key3 == 3)
        {
            std::cout<<" Enter enrollno ";
            std::cin>>enrollno;

            Student student = mongodbhandler.db_load_student(enrollno);
            student.display_details();

        }
        else if (key3 == 4)
        {
            //view iteration details
        }
        else if(key3==5)
        {
            std::string title;
            std::cout<< " Enter assignment title : "<<std::endl;
            getline(cin,title);
            Assignment assignment = mongodbhandler.db_load_assignment(title);
            mongodbhandler.db_update_assignment(assignment);
        }
        else if (key3 == 6)
        {
            cout<<"-----GOODBYE-----"<<endl;
            break;
        }
        else
        {
            cout << "Enter the correct key" << endl;
        }
        }              
    }
    else
    {
        cout << "no reviewer found !!" << endl;
    }
    cout << "-------------------------------------------------------------\n";
}
#endif