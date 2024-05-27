#include "student.hpp"

//make student
Student::Student(std::string& name, std::string& password, int enrollno)
    : Img_member(name, enrollno, "Student", password) {}

Student::Student(const Img_member& img_member)
    : Img_member(img_member.get_name(), img_member.get_enrollno(), img_member.get_role(), img_member.get_password()) {}


// update assignment status
void Student::update_status(Assignment* assignment, bool status) {
    statusAssignments[assignment->get_title()] = status;
    std::cout << "Status for assignment : " << assignment->get_title() << ": updated to " 
              << (status ? "completed" : "not completed") << std::endl;
}

//view feedback
void Student::view_feedback(Assignment* assignment) {
    auto it = feedbackAssignments.find(assignment->get_title());
    if (it != feedbackAssignments.end()) {
        std::cout << "Feedback for assignment =" << assignment->get_title() << " :" << std::endl;
        for (const std::string& feedback : it->second) {
            std::cout << "- " << feedback << std::endl;
        }
    } else {
        std::cout << "No feedback available for assignment " << assignment->get_title() << std::endl;
    }
}

void Student::add_assignment(Assignment* assignment) {
    statusAssignments[assignment->get_title()] = false;
    feedbackAssignments[assignment->get_title()] = std::vector<std::string>(); 
    std::cout << "Assignment: " << assignment->get_title() << std::endl;
}

//display details
void Student::display_details() {
    std::cout << "Student Name: " << get_name() << std::endl;
    std::cout << "Enrollment Number: " << get_enrollno() << std::endl;
    std::cout << "Role: " << get_role() << std::endl;
    std::cout << "Assignments Status: " << std::endl;

    for (auto it = statusAssignments.begin(); it != statusAssignments.end(); it++) {
        std::cout << "- " << it->first << ": " << (it->second ? "completed" : "not completed") << std::endl;
    }

    std::cout << "Feedback on Assignments: " << std::endl;
    for (auto it = feedbackAssignments.begin(); it != feedbackAssignments.end(); it++) {
        std::cout << "- " << it->first << ":" << std::endl;
        for (const std::string& feedback : it->second) {
            std::cout << "  - " << feedback << std::endl;
        }
    }
}
void Student::assign_feedback(Assignment* assignment, const std::string& feedback) {
    feedbackAssignments[assignment->get_title()].push_back(feedback);
    std::cout << "Feedback of assignment -" << assignment->get_title() << std::endl;
}

std::map<std::string, bool> Student::get_all_status() const {
    return statusAssignments;
}

std::map<std::string, std::vector<std::string>> Student::get_all_feedback() const {
    return feedbackAssignments;
}
void Student::set_status_assignment(std::map<std::string, bool> statusAssignment) {
    this->statusAssignments = statusAssignment;
}

void Student::set_feedback_assignment(std::map<std::string, std::vector<std::string>> feedbackAssignment) {
    this->feedbackAssignments = feedbackAssignment;
}
