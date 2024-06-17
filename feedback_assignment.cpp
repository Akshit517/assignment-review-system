#include "feedback_assignment.hpp"
#include "assignment.hpp"

void FeedbackAssignment::display_feedback (Assignment* assignment) const {
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

void FeedbackAssignment::assign_feedback(Assignment* assignment, const std::string& feedback) {
    feedbackAssignments[assignment->get_title()].push_back(feedback);
    std::cout << "Feedback of assignment -" << assignment->get_title() << std::endl;
}

void FeedbackAssignment::set_feedback_assignment(std::map<std::string, std::vector<std::string>> feedbackAssignment) {
    this->feedbackAssignments = feedbackAssignment;
}

std::map<std::string, std::vector<std::string>> FeedbackAssignment::get_feedback() const {
    return this->feedbackAssignments;
}