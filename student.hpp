#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "img_member.hpp"

class Reviewer;
class Assignment;

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

        void display_details() const;

        //view your assgn feedback
        void view_feedback(Assignment* assignment); 

        void add_assignment(Assignment* assignment);
        
        void assign_feedback(Assignment* assignment, const std::string& feedback);

        void send_iteration(Reviewer& reviewer,Assignment* assignment);

        //getters
        std::map<std::string, bool> get_all_status() const;
        std::map<std::string, std::vector<std::string>> get_all_feedback() const;

        //setters
        void set_status_assignment(std::map<std::string, bool>);
        void set_feedback_assignment(std::map<std::string, std::vector<std::string>>);

};    
#endif  