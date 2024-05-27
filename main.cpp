#include <cstdint>
#include <iostream>
#include <vector>

#include "img_member.hpp"
#include "assignment.hpp"

#include "mongo_config.hpp"
#include "mongodb_handler.hpp"
#include "base_login.hpp"
    
int main(){
    img_assgn::MongoDbHandler mongodbhandler = img_assgn::MongoDbHandler();
    base_login(mongodbhandler);
    return 0;
}