#ifndef  MONGO_HANDLER
#define  MONGO_HANDLER

#include <iostream>

#include "img_member.hpp"
#include "assignment.hpp"

#include "mongo_config.hpp"
#include "student.hpp"

namespace img_assgn{
    const std::string mongoDburi = "mongodb://localhost:27017";
    const std::string databaseName = "img_assignment";

    class MongoDbHandler{
        private:
            mongocxx::client _client;
            mongocxx::uri _uri;
            mongocxx::database _database;

            bsoncxx::v_noabi::array::value make_array_tasks(Assignment& assignment){
                std::map<int, std::string> tasks = assignment.get_all_tasks();

                auto task_array_builder = bsoncxx::builder::basic::array{};

                for (auto it = tasks.begin(); it != tasks.end(); it++) {
                    int taskno = it->first;
                    std::string task = it->second;
                    task_array_builder.append(make_document(
                        kvp("taskno", taskno),
                        kvp("task", task)
                    ));
                }

                auto task_array = task_array_builder.extract();
                return task_array;

            }
            bsoncxx::v_noabi::array::value make_array_statusAssignments(Student& student) {
                std::map<std::string, bool> statusAssignments = student.get_all_status();
                auto statusAssignment_array_builder = bsoncxx::builder::basic::array{};

                for (auto it = statusAssignments.begin(); it!= statusAssignments.end(); it++){
                    std::string assignmentTitle = it->first;
                    bool status = it->second;
                    statusAssignment_array_builder.append(make_document(
                        kvp("assignmentTitle", assignmentTitle),
                        kvp("status", status)
                    )); 
                }
                return statusAssignment_array_builder.extract();
            }

            bsoncxx::v_noabi::array::value make_feedback_assignments(Student& student) {

                std::map<std::string, std::vector<std::string>> feedbackAssignments = student.get_all_feedback();

                auto feedbackAssignment_array_builder = bsoncxx::builder::basic::array{};

                for (auto it = feedbackAssignments.begin(); it!= feedbackAssignments.end(); it++){
                    std::string assignmentTitle = it->first;
                    auto feedbacks = it->second;
                    auto feedback_array_builder = bsoncxx::builder::basic::array{};
                    
                    for (const auto& feedback : feedbacks) {
                            feedback_array_builder.append(feedback);
                    }

                    feedbackAssignment_array_builder.append(make_document(
                        kvp("assignmentTitle", assignmentTitle),
                        kvp("feedback", feedback_array_builder)
                    ));
                }
                return feedbackAssignment_array_builder.extract();
            }
        public:
            MongoDbHandler(){
                this->_uri = mongocxx::uri(mongoDburi);
                this->_client =  mongocxx::client(_uri);
                this->_database = _client[databaseName];
            }

            //load from Db for img_member class
            Img_member db_load_img_member(int enrollno) {

                auto collection = _database["img_member"];

                auto result = collection.find_one(make_document(kvp("enrollno", enrollno)));

                auto view = result->view();

                bsoncxx::document::element nameElem = view["name"];
                bsoncxx::document::element passwordElem = view["password"];
                bsoncxx::document::element roleElem = view["role"];

                std::string name(nameElem.get_string().value.begin(), nameElem.get_string().value.end());
                std::string password(passwordElem.get_string().value.begin(), passwordElem.get_string().value.end());
                std::string role(roleElem.get_string().value.begin(), roleElem.get_string().value.end());
    
                return Img_member(name, enrollno, role, password);
            }            

            //save img member to Db
            void db_save_img_member(Img_member img_member){
                auto collection = _database["img_member"];
                collection.insert_one(
                    make_document(
                        kvp("name", img_member.get_name()),
                        kvp("enrollno",img_member.get_enrollno()),
                        kvp("password",img_member.get_password()),
                        kvp("role",img_member.get_role())
                        ));
                std::cout<<" document inserted "<<std::endl;
            }
            //update img member
            void db_update_img_member(Img_member &img_member) {
                auto collection = _database["img_member"];
                auto find_img_member = collection.find_one(make_document(
                    kvp("enrollno", img_member.get_enrollno())
                ));   
                if (find_img_member) {
                    img_member.update_details();
                    auto update_result = collection.update_many(
                        make_document(
                            kvp("enrollno", img_member.get_enrollno())
                        ), 
                        make_document(
                            kvp("$set", make_document(
                                kvp("name", img_member.get_name()),
                                kvp("password", img_member.get_password()),
                                kvp("role", img_member.get_role())
                            ))
                        )
                    );
                    if (update_result && update_result->modified_count() > 0) {
                        std::cout << "Document updated" << std::endl;
                    } else {
                        std::cout << "No document matched or updated" << std::endl;
                    }
                } else {
                    std::cout << "Error updating document: Document not found" << std::endl;
                }
            }

            //save assignment
            void db_save_assignment(Assignment& assignment) {

                auto task_array = make_array_tasks(assignment);

                auto assignment_doc = bsoncxx::builder::basic::document{};
                assignment_doc.append(
                    kvp("title", assignment.get_title()),
                    kvp("deadline", assignment.get_deadline()),
                    kvp("tasks", task_array)
                );                 

                auto collection = _database["assignment"];
                collection.insert_one(assignment_doc.view());

                std::cout<<" assignment inserted "<<std::endl;
            }

            //load assignment
            //should load element by their id or primary key
            Assignment db_load_assignment(const std::string& title) {
                auto collection = _database["assignment"];
                //std::cout<<"above";
                auto found = collection.find_one(make_document(kvp("title", title)));
                //std::cout<<"below";

                if (found) {
                    
                    auto view = found->view();

                    bsoncxx::document::element titleElem = view["title"];
                    bsoncxx::document::element deadlineElem = view["deadline"];
                    bsoncxx::document::element tasksElem = view["tasks"];

                    std::string assgn_title(titleElem.get_string().value.begin(), titleElem.get_string().value.end());
                    std::string assgn_deadline(deadlineElem.get_string().value.begin(), deadlineElem.get_string().value.end());    

                    std::map<int, std::string> tasks;

                    if (tasksElem.type() == bsoncxx::type::k_array) {

                        bsoncxx::array::view tasksArray = tasksElem.get_array().value;

                        for (const bsoncxx::array::element& ele : tasksArray){

                            bsoncxx::document::view oneTask = ele.get_document().value;

                            bsoncxx::document::element tasknoElem = oneTask["taskno"];
                            bsoncxx::document::element taskElem = oneTask["task"];

                            int taskno;
                            if (tasknoElem.type() == bsoncxx::type::k_int32) {
                                taskno = tasknoElem.get_int32().value;
                            } else if (tasknoElem.type() == bsoncxx::type::k_int64) {
                                taskno = static_cast<int>(tasknoElem.get_int64().value);
                            }

                            std::string task(taskElem.get_string().value.begin(), taskElem.get_string().value.end());

                            tasks[taskno] = task;
                        }
                    }

                    return Assignment(assgn_title, assgn_deadline, tasks);
                } else {
                    throw std::runtime_error("single assignment not found"); 
                }
            }
            //update assignment
            void db_update_assignment(Assignment &assignment) {
                auto collection = _database["assignment"];

                std::cout<<" Choose an option :\n 1. add task\n 2. change deadline\n";
                int i;
                std::cin>>i;
                std::cout<<std::endl;
                if (i == 1){
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clearing input buffer?
                    std::string new_task;
                    getline(std::cin,new_task);
                    assignment.add_task(new_task);                 
                } else if (i == 2 ) {
                    assignment.change_deadline();
                } else {
                    std::cout<<" Choose valid option! "<<std::endl;
                }

                auto result = collection.update_many(
                    make_document(kvp("title", assignment.get_title())),
                    make_document(
                        kvp("$push", make_document(
                            kvp("tasks", make_document(kvp("$each", make_array_tasks(assignment))))
                        )),
                        kvp("$set", make_document(
                            kvp("deadline", assignment.get_deadline())
                        ))
                    )
                );

                if (result && result->modified_count() > 0) {
                    std::cout << "Document updated" << std::endl;
                } else {
                    std::cout << "No document matched or updated" << std::endl;
                }
            } 
            //delete task
            void db_delete_task( Assignment& assignment){
                assignment.delete_task();
                
                auto collection = _database["assignment"];

                auto result = collection.update_many(
                make_document(kvp("title", assignment.get_title())),
                make_document(
                    kvp("$pull", make_document(
                    kvp("tasks", make_document(kvp("$exists", true)))
                    ))
                )
                );
            }
            //
            //fine till here
            std::string db_find_password(int &enrollno, std::string _collection){                     
                auto collection = _database[_collection];

                auto foundStudent = collection.find_one(make_document(kvp("enroll_no", enrollno)));

                auto view = foundStudent->view();

                bsoncxx::document::element passwordElem = view["password"];

                std::string password(passwordElem.get_string().value.begin(), passwordElem.get_string().value.end());

                return password;
            }
            
            void db_delete_student(int& enrollno) {
                auto collection = _database["student"];

                auto delete_one_result = collection.delete_one(make_document(kvp("enrollno", enrollno)));

                if (delete_one_result && delete_one_result->deleted_count() > 0) {
                    std::cout << "Student with enrollment number " << enrollno << " has been deleted successfully." << std::endl;
                } else {
                    std::cout << "No student found with enrollment number " << enrollno << "." << std::endl;
                }
            }

             void db_save_student(Student& student) {
                auto collection = _database["student"];

                auto statusAssignmentsDoc = make_array_statusAssignments(student);
                auto feedbackAssignmentsDoc = make_feedback_assignments(student);

                auto student_doc = bsoncxx::builder::basic::document{};
                student_doc.append(
                    kvp("name", student.get_name()),
                    kvp("password", student.get_password()),
                    kvp("enrollno", student.get_enrollno()),
                    kvp("role", student.get_role()),
                    kvp("statusAssignments", statusAssignmentsDoc),
                    kvp("feedbackAssignments", feedbackAssignmentsDoc)
                );

                collection.insert_one(student_doc.view());

                std::cout << "Student inserted" << std::endl;
            }

            

            Student db_load_student(const int& enrollno) {
                auto collection = _database["student"];
                auto found = collection.find_one(make_document(kvp("enrollno", enrollno)));

                if (found) {
                    auto view = found->view();

                    bsoncxx::document::element nameElem = view["name"];
                    bsoncxx::document::element passwordElem = view["password"];
                    bsoncxx::document::element roleElem = view["role"];

                    std::string name(nameElem.get_string().value.begin(), nameElem.get_string().value.end());
                    std::string password(passwordElem.get_string().value.begin(), passwordElem.get_string().value.end());
                    std::string role(roleElem.get_string().value.begin(), roleElem.get_string().value.end());

                    bsoncxx::document::element statusAssignmentElem = view["statusAssignments"];
                    
                    std::map<std::string, bool> statusAssignment;

                    if (statusAssignmentElem.type() == bsoncxx::type::k_array) {

                        bsoncxx::array::view statusAssignmentArray = statusAssignmentElem.get_array().value;

                        for (const bsoncxx::array::element& ele : statusAssignmentArray){

                            bsoncxx::document::view oneElem = ele.get_document().value;

                            bsoncxx::document::element assignmentTitleElem = oneElem["assignmentTitle"];
                            bsoncxx::document::element boolElem = oneElem["status"];

                            
                            bool status = boolElem.get_bool().value;
                            std::string assignmentTitle(assignmentTitleElem.get_string().value.begin(), assignmentTitleElem.get_string().value.end());

                            statusAssignment[assignmentTitle] = status;
                        }
                    }
                    bsoncxx::document::element feedbackAssignmentElem = view["feedbackAssignments"];
                    
                    std::map<std::string, std::vector<std::string>> feedbackAssignment;
                    //get_feedback_assignment
                    if (feedbackAssignmentElem.type() == bsoncxx::type::k_array) {

                        bsoncxx::array::view feedbackAssignmentArray = feedbackAssignmentElem.get_array().value;

                        for (const bsoncxx::array::element& ele : feedbackAssignmentArray){

                            bsoncxx::document::view oneElem = ele.get_document().value;

                            bsoncxx::document::element assignmentTitleElem = oneElem["assignmentTitle"];
                            bsoncxx::document::element feedbackElem = oneElem["feedback"];

                            std::string assignmentTitle(assignmentTitleElem.get_string().value.begin(), assignmentTitleElem.get_string().value.end());

                            std::vector<std::string> feedbacks;
                            bsoncxx::array::view feedbackAssignmentArray = feedbackElem.get_array().value;

                            for (const bsoncxx::array::element& feedback : feedbackAssignmentArray){

                                std::string stringFeedback(feedback.get_string().value.begin(), feedback.get_string().value.end());

                                feedbacks.push_back(stringFeedback);

                            }


                            feedbackAssignment[assignmentTitle] = feedbacks;
                        }
                    }

                    Student student = Student(name, password, enrollno);

                    student.set_status_assignment(statusAssignment);
                    student.set_feedback_assignment(feedbackAssignment);

                    return student;
                    std::cout << "Student loaded" << std::endl;
                } else {
                    throw std::runtime_error("Student not found");
                }
            }
                                             
    };
}
#endif

