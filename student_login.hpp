#ifndef STUDENTLOGIN_H
#define STUDENTLOGIN_H

#include <iostream>
#include "student.hpp"
#include "reviewer.hpp"

#include "mongo_config.hpp"
#include "mongodb_handler.hpp"

using namespace std;

void student_options_screen(){
    cout << "-------------------------------------------------------------\n";
    cout << "What would you like to do?\n\n";
    cout << "1. View Your Details\n";
    cout << "2. View assignment details\n";
    cout << "3. Request for iteration\n";
    cout << "4. Delete user\n";
    cout << "5. Exit\n";
    cout << "-------------------------------------------------------------"<<endl;
}
void student_login(img_assgn::MongoDbHandler& mongodbhandler){
    string pswd;
    int enrollno;
    cout << "-------------------------------------------------------------\n";
    cout << "Enter your Enrollment Number: ";
    cin >> enrollno;
    cout << endl;
    cout << "Enter your password: ";
    cin >> pswd;

    string foundStudentpswd = mongodbhandler.db_find_password(enrollno,"student");

    if (pswd == foundStudentpswd)
    {       
        while (true)
        {  
            student_options_screen();
            Student student = mongodbhandler.db_load_student(enrollno);
            int options;
            cout << "Enter: ";
            cin >> options;
            switch(options){
                case 1: {
                    //Img_member member =  mongodbhandler.db_load_img_member(enrollno);
                    student.display_details();     
                    break;
                    }
                case 2: {
                    std::string title;
                    std::cout << "Enter assignment title : " << std::endl;
                    getline(cin,title);
                    Assignment assignment = mongodbhandler.db_load_assignment(title);
                    assignment.display_assignment_details();  
                    break;
                    }
                case 3: {
                        std::cout<< " Enter a Reviwer enrollno :"<< std::endl;
                        int reviewerEnrollno;
                        std::cin>> reviewerEnrollno;
                        std::string assignmentTitle;
                        std::cout<<" \n Enter assignment title : ";
                        getline(cin,assignmentTitle);
                        //getline(cin, reviewerName);
                        //load from database
                        Img_member member = mongodbhandler.db_load_img_member(reviewerEnrollno);
                        Assignment assignment = mongodbhandler.db_load_assignment(assignmentTitle);
                        Reviewer reviewer = Reviewer(member);
                        reviewer.add_to_iterationRequest(assignment.get_title(), student.get_enrollno());
                        break;
                    }
                case 4: mongodbhandler.db_delete_student(enrollno);
                        break;
                case 5:
                        cout<<"-----GOODBYE-----"<<endl;
                        break;
                default: cout<<"-----Enter a valid option-----"<<endl;                                        
            }
        }
    }else {
        cout<<"no student found!!!"<<endl;
    }
    cout<<"______________________________________________\n";           
}


#endif