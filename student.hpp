#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "img_member.hpp"

#include "status_assignment.hpp"
#include "feedback_assignment.hpp"

class Reviewer;
class Assignment;
namespace img_assgn{
    class MongoDbHandler;
}

class Student final: public Img_member {
    private:

        StatusAssignment statusAssignment;
        FeedbackAssignment feedbackAssignment;
        
        friend class Reviewer;

    public:

        Student(std::string& name, std::string& password, int enrollno);
        Student(const Img_member& img_member);
 
        void display_details() const;

        void view_feedback(Assignment* assignment); 

        void send_iteration(Reviewer& reviewer,Assignment* assignment);

        std::map<std::string, bool> get_all_status() const;
        std::map<std::string, std::vector<std::string>> get_all_feedback() const;

};    
#endif  