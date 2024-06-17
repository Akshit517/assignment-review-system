#ifndef REVIEWER_H
#define REVIEWER_H

#include <iostream>
#include <vector>
#include <map>

#include "img_member.hpp"
#include "iteration.hpp"

class Student;
class Assignment;
namespace img_assgn{
    class MongoDbHandler;
}

class Reviewer final: public Img_member {
    private:
        std::vector<std::string> _assignmentAlloted;
        Iteration _iterationRequest;
        
    public:
        // create a reviewer
        Reviewer(std::string& name, std::string& password, int enrollno);
        Reviewer(Img_member& img_member);

        void display_details() const;
        // View assignments allotted to review
        void view_assignments_allotted() const;

        void add_assignment(Student& , Assignment*);

        //iteration requests
        void view_iteration_requests() const;
        Iteration get_iterationRequest() const;

        void update_assignmentStatus(Student& , Assignment* , bool& status);

        void update_assignment(Assignment*);

        void give_feedback(Student& , Assignment* , std::string& );
};
#endif
