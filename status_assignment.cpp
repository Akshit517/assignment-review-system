#include "assignment.hpp"
#include "status_assignment.hpp"

void StatusAssignment::update_status(Assignment* assignment, bool status) {
    statusAssignments[assignment->get_title()] = status;
    std::cout << "Status for assignment : " << assignment->get_title() << ": updated to " 
              << (status ? "completed" : "not completed") << std::endl;
}

void StatusAssignment::add_assignment (Assignment* assignment){
    statusAssignments[assignment->get_title()] = false; 
}

void StatusAssignment::display_status() const {

    for (auto it = statusAssignments.begin(); it != statusAssignments.end(); it++){

        std::string status = it->second ? " Completed " : " Pending ";

        std::cout << "Status for assignment :\n" 
            << it->first << " ---> " << status << std::endl;
    }
    
}

std::map<std::string, bool> StatusAssignment::get_all_status() const {
    return this->statusAssignments;
}

void StatusAssignment::set_status_assignment(std::map<std::string, bool> statusAssignment) {
    this->statusAssignments = statusAssignment;
}