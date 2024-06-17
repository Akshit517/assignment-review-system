#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Assignment{
    private:
        std::string title;
        std::map<int,std::string> tasks;
        std::string deadline;

        friend class Reviewer;

        void add_task(std::string);

        void delete_task();
    public : 
    
        Assignment(std::string title, std::string deadline);
        Assignment(std::string , std::string , std::map<int,std::string> );
        
        void display_assignment_details();
        
        void change_deadline();

        std::string get_title() const;
        
        std::string get_deadline() const;

        std::string get_task(int index) const;

        std::map<int,std::string> get_all_tasks() const;
};
#endif
