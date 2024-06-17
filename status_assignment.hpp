#pragma once

#include <iostream>
#include <map>
#include <string>

class Reviewer;
class Assignment;

class StatusAssignment{
    private:
        std::map<std::string, bool> statusAssignments;

        friend class Reviewer;

        void update_status(Assignment* assignment, bool status);

        void add_assignment( Assignment* ) ;

        void set_status_assignment(std::map<std::string, bool>);

    public:
        void display_status() const;

        std::map<std::string, bool> get_all_status() const;
};