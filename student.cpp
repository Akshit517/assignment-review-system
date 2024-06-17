#include "student.hpp"
#include "assignment.hpp"
#include "reviewer.hpp"

Student::Student(std::string& name, std::string& password, int enrollno)
    : Img_member(name, enrollno, "Student", password) {
        this->statusAssignment = StatusAssignment();
        this->feedbackAssignment = FeedbackAssignment();
    }

Student::Student(const Img_member& img_member)
    : Img_member(img_member.get_name(), img_member.get_enrollno(), img_member.get_role(), img_member.get_password()) {
        this->statusAssignment = StatusAssignment();
        this->feedbackAssignment = FeedbackAssignment();
    }
    
void Student::view_feedback(Assignment* assignment) {
    this->feedbackAssignment.display_feedback(assignment);
}

void Student::display_details() const {
    std::cout << "Student Name: " << get_name() << std::endl;
    std::cout << "Enrollment Number: " << get_enrollno() << std::endl;
    std::cout << "Role: " << get_role() << std::endl;
    std::cout << "Assignments Status: " << std::endl;

    statusAssignment.display_status();
}


void Student::send_iteration(Reviewer& reviewer, Assignment* assignment){
    reviewer.get_iterationRequest()._studentAccessor.add_to_iterationRequest(assignment->get_title(), this->_enrollno);
}

std::map<std::string, bool> Student::get_all_status() const {
    return this->statusAssignment.get_all_status();
}

std::map<std::string, std::vector<std::string>> Student::get_all_feedback() const {
    return feedbackAssignment.get_feedback();
}

