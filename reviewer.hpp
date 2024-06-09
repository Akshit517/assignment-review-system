#ifndef REVIEWER_H
#define REVIEWER_H

#include <iostream>
#include <vector>
#include <map>

#include "img_member.hpp"

class Student;
class Assignment;
namespace img_assgn{
    class MongoDbHandler;
}

class Reviewer: public Img_member {
    private:
        std::vector<std::string> _assignmentAlloted;
        std::map<std::string, std::vector<int>> _iterationRequest;

        friend class Student;

        void add_to_iterationRequest(const std::string& assignmentName, int studentEnrollNo);
    public:
        // create a reviewer
        Reviewer(std::string& name, std::string& password, int enrollno);
        Reviewer(Img_member& img_member);

        void display_details() const;
        // View assignments allotted to review
        void view_assignments_allotted() const;

        // View iteration requests by students
        void view_iteration_requests() const;

        void update_assignmentStatus(Student& , Assignment* , bool& status);

        void update_assignment(const std::string&, img_assgn::MongoDbHandler&);

        void give_feedback(Student& , Assignment* , std::string& );
};
#endif
