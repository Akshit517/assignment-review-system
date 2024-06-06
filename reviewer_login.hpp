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
    cout << "2. View Students and their assignment status\n";
    cout << "3. View iteration requests\n";
    cout << "4. Change Assignment details\n";
    cout << "4. Change Status of Student's assignment\n";
    cout << "5. Give feedback\n";
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
        Reviewer reviewer = mongodbhandler.db_load_reviewer(enrollno);
        cout<<endl;
        reviewer_login_options();
        int key3;
        cout << "Enter: ";
        cin >> key3;
        if (key3 == 1)
        {
            cout << "-------------------------------------------------------------\n";

            reviewer.display_details();
            
        }
        else if (key3 == 2)
        {
            std::cout<<" Enter enrollno ";
            std::cin>>enrollno;

            Student student = mongodbhandler.db_load_student(enrollno);
            student.display_details();

        }
        else if (key3 == 3)
        {
            reviewer.view_iteration_requests();
        }
        else if(key3==4)
        {
            std::string title;
            std::cout<< " Enter assignment title : "<<std::endl;
            getline(cin,title);

            reviewer.update_assignment(title, mongodbhandler);
        }
        else if (key3 == 5)
        {
            int enrollno;    
            cout << "Enter Student Enrollment Number: ";
            cin >> enrollno;
            Student student = mongodbhandler.db_load_student(enrollno);

            std::string assignmentTitle;
            std::cout<<" \n Enter assignment title : ";
            getline(cin,assignmentTitle);          
            Assignment assignment = mongodbhandler.db_load_assignment(assignmentTitle);
            Assignment* ptrAssignment  = &assignment;

            std::string feedback;
            std::cout<<" \n Enter the feedback : \n";
            getline(cin,feedback);  

            reviewer.give_feedback(student, ptrAssignment, feedback);
            break;
        }
        else if (key3 == 6)
        {
            int enrollno;    
            cout << "Enter Student Enrollment Number: ";
            cin >> enrollno;
            Student student = mongodbhandler.db_load_student(enrollno);

            std::string assignmentTitle;
            std::cout<<" \n Enter assignment title : ";
            getline(cin,assignmentTitle);          
            Assignment assignment = mongodbhandler.db_load_assignment(assignmentTitle);
            Assignment* ptrAssignment  = &assignment;

            bool status;
            std::cout<<" \n Enter status (true/false) : \n";
            std::cin>>status;

            reviewer.update_assignmentStatus(student, ptrAssignment, status);
            break;
        }
        else if (key3 == 7)
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