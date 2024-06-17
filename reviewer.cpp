#include <iostream>
#include <string>
#include "reviewer.hpp"
#include "student.hpp"
#include "assignment.hpp"
#include <limits>
//#include "mongodb_handler.hpp"

//change deadline as a reviewer
Reviewer::Reviewer(std::string& name, std::string& password, int enrollno)
: Img_member(name, enrollno, "Reviewer", password) {
    this->_assignmentAlloted = std::vector<std::string>();

}
Reviewer::Reviewer(Img_member& img_member)
    : Img_member(img_member) {
    this->_assignmentAlloted = std::vector<std::string>();
}

void Reviewer::display_details() const{

    std::cout << "Name: " << get_name() << std::endl;
    std::cout << "Enrollment Number: " << get_enrollno() << std::endl;
    std::cout << "Role: " << get_role() << std::endl;
    //std::cout << "Assignments Allotted: " << std::endl;
    //for (const auto& assignment : _assignmentAlloted) {
    //    std::cout << "-> " << assignment << std::endl;
    //}
}

void Reviewer::view_assignments_allotted() const {
    std::cout << "Assignments allotted to review:" << std::endl;
    for (const auto& assignment : _assignmentAlloted) {
        std::cout << "-> " << assignment << std::endl;
    }
}

void Reviewer::view_iteration_requests() const {
    _iterationRequest._reviewerAccessor.view_iteration_requests();
}

void Reviewer::give_feedback(Student& student, Assignment* assignment, std::string& feedback){
    student.feedbackAssignment.assign_feedback(assignment, feedback);
}

void Reviewer::update_assignmentStatus(Student& student, Assignment* assignment, bool& status){
    student.statusAssignment.update_status(assignment, status);
}

void Reviewer::update_assignment(Assignment* assignment) {
    std::cout << "Updating assignment: " << assignment->get_title() << std::endl;

    std::cout<<" Choose an option :\n 1. add task\n 2. change deadline\n";
    int i;
    std::cin>>i;
    std::cout<<std::endl;
    if (i == 1){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string new_task;
        getline(std::cin,new_task);
        assignment->add_task(new_task);                 
    } else if (i == 2 ) {
        assignment->change_deadline();
    } else {
        std::cout<<" Choose valid option! "<<std::endl;
    }

    std::cout<<" assignment updated "<<std::endl;
}

Iteration Reviewer::get_iterationRequest() const {
    return _iterationRequest;
}

void Reviewer::add_assignment(Student& student, Assignment* assignment){
    student.statusAssignment.add_assignment(assignment);
    student.feedbackAssignment.feedbackAssignments[assignment->get_title()] = std::vector<std::string>(); 
    std::cout << "Assignment: " << assignment->get_title() << std::endl;
};