#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <map>
#include <string>

#include "img_member.hpp"
#include "assignment.hpp"

class Student: public Img_member{
    private:
        std::map<std::string, bool> statusAssignments;
        std::map<std::string, std::vector<std::string>> feedbackAssignments;
    public:

        //display assignments information
        Student(std::string& name, std::string& password, int enrollno);
        Student(const Img_member& img_member);

        //update status
        void update_status(Assignment* assignment, bool status);

        void display_details();

        //view your assgn feedback
        void view_feedback(Assignment* assignment); 

        void add_assignment(Assignment* assignment);
        
        void assign_feedback(Assignment* assignment, const std::string& feedback);

        //no implementation
        void send_iteration(Assignment* assignment, const std::string& feedback);

        //getters
        std::map<std::string, bool> get_all_status() const;
        std::map<std::string, std::vector<std::string>> get_all_feedback() const;

        //setters
        void set_status_assignment(std::map<std::string, bool>);
        void set_feedback_assignment(std::map<std::string, std::vector<std::string>>);

};    
#endif  