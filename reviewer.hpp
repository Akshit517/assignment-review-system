#ifndef REVIEWER_H
#define REVIEWER_H

#include <iostream>
#include <vector>
#include <map>

#include "img_member.hpp"
#include "assignment.hpp"
#include "mongodb_handler.hpp"

class Reviewer: public Img_member {
    private:
        std::vector<std::string> _assignmentAlloted;
        std::map<std::string, std::vector<int>> _iterationRequest;
    public:
        // create a reviewer
        Reviewer(std::string& name, std::string& password, int enrollno);
        Reviewer(Img_member& img_member);

        void display_details() const;
        // View assignments allotted to review
        void view_assignments_allotted() const;

        // View iteration requests by students
        void view_iteration_requests() const;

        // Change deadline as a reviewer
        void change_assignment_deadline(const std::string& assignmentTitle, const std::string& newDeadline);

        void add_to_iterationRequest(const std::string& assignmentName, int studentEnrollNo);
        void update_assignment(const std::string&, img_assgn::MongoDbHandler&);

};
#endif
