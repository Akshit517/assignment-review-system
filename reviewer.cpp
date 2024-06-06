#include <iostream>
#include <string>
#include "reviewer.hpp"
#include "student.hpp"
#include "mongodb_handler.hpp"

//change deadline as a reviewer
Reviewer::Reviewer(std::string& name, std::string& password, int enrollno)
: Img_member(name, enrollno, "Reviewer", password) {
    this->_assignmentAlloted = std::vector<std::string>();
    this->_iterationRequest = {};
}
Reviewer::Reviewer(Img_member& img_member)
    : Img_member(img_member) {
    this->_assignmentAlloted = std::vector<std::string>();
    this->_iterationRequest = {};
}

void Reviewer::display_details() const{
    std::cout << "Reviewer Details:" << std::endl;
    std::cout << "Name: " << get_name() << std::endl;
    std::cout << "Enrollment Number: " << get_enrollno() << std::endl;
    std::cout << "Role: " << get_role() << std::endl;
    std::cout << "Assignments Allotted: " << std::endl;
    for (const auto& assignment : _assignmentAlloted) {
        std::cout << "- " << assignment << std::endl;
    }
}

// View assignments allotted to review
void Reviewer::view_assignments_allotted() const {
    std::cout << "Assignments allotted to review:" << std::endl;
    for (const auto& assignment : _assignmentAlloted) {
        std::cout << "- " << assignment << std::endl;
    }
}

// View iteration requests by students
void Reviewer::view_iteration_requests() const {
    std::cout << "Iteration requests by students:" << std::endl;
    for (const auto& it : _iterationRequest) {
        std::cout << "Assignment: "<< it.first;
        std::cout << "Requests: ";
        for (const auto& requestId : it.second) {
            std::cout << requestId << " ";
        }
        std::cout << std::endl;
    }
}

void Reviewer::give_feedback(Student& student, Assignment* assignment, std::string& feedback){
    student.assign_feedback(assignment, feedback);
}

void Reviewer::update_assignmentStatus(Student& student, Assignment* assignment, bool& status){
    student.update_status(assignment, status);
}

// Change deadline as a reviewer
void Reviewer::update_assignment(const std::string& assignmentTitle, img_assgn::MongoDbHandler& mongodb_handler) {
    Assignment assignment  = mongodb_handler.db_load_assignment(assignmentTitle);
    std::cout << "Updating assignment: " << assignmentTitle;

    mongodb_handler.db_update_assignment(assignment);

    std::cout<<" assignment updated "<<std::endl;
}

void Reviewer::add_to_iterationRequest(const std::string& assignmentName, int studentEnrollNo) {
    _assignmentAlloted.push_back(assignmentName);
    _iterationRequest[assignmentName].push_back(studentEnrollNo);
    std::cout << "Added required to iteration " <<std::endl;
}