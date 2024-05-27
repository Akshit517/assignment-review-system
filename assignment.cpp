#include "assignment.hpp" 
#include <map>

//Assignment constructor/add a new assignment
Assignment::Assignment(std::string title, std::string deadline){
    this->title = title;
    this->deadline = deadline;
}
Assignment::Assignment(std::string title, std::string deadline, std::map<int,std::string> tasks){
    this->title = title;
    this->deadline = deadline;
    this->tasks = tasks;
}

//display assigment details 
void Assignment::display_assignment_details(){
    std::cout<<"Title: "<<this->title<<std::endl;
    std::cout<<"Tasks:"<<std::endl;
    
    for (auto it = this->tasks.begin(); it != this->tasks.end(); ++it) {
        std::cout<<it->first <<". "<<it->second<<std::endl;
    }
}
//add a new task to assignment
void Assignment::add_task(std::string descTask){
    int taskNumber = this->tasks.size() + 1;

    this->tasks[taskNumber] = descTask;

    std::cout<<"added new task"<<std::endl;
}

//delete a task
void Assignment::delete_task(){
    int taskno;

    std::cout<<"Enter taskno to remove: ";
    std::cin>>taskno;

    auto it = this->tasks.find(taskno);
    if (it != this->tasks.end()) {
        this->tasks.erase(it);
        std::cout << "Task removed" << std::endl;
    } else {
        std::cout << "Task not found" << std::endl;
    }
}

//change deadline
void Assignment::change_deadline(){
    std::cout<<"ENTER NEW DEADLINE : ";
    std::string new_deadline;
    std::cin>>new_deadline;
    this->deadline=new_deadline;
    std::cout<<"\nchanged deadline successfully!"<<std::endl;
}
std::string Assignment::get_title() const {
    return title;
}
std::string Assignment::get_deadline() const {
    return deadline;
}
std::string Assignment::get_task(int taskNumber) const {
    auto it = tasks.find(taskNumber);
    if (it != tasks.end()) {
        return it->second;
    } else {
        return "task number not found\n";
    }
}

std::map<int, std::string> Assignment::get_all_tasks() const {
    return tasks;
}
