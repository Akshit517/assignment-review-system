#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Reviewer;
class Assignment;

class FeedbackAssignment{
    private:

    friend class Reviewer;
    
    std::map<std::string, std::vector<std::string>> feedbackAssignments;  

    void assign_feedback(Assignment* , const std::string&);

    void set_feedback_assignment(std::map<std::string, std::vector<std::string>>);
        
    public:

    void display_feedback(Assignment*) const;

    std::map<std::string, std::vector<std::string>> get_feedback() const;
};