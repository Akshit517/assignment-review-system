#pragma once

#include <iostream>
#include <string>

class Iteration;

class ReviewerAccessor {
private:
    Iteration& _parent;

    friend class Iteration;
    friend class Reviewer;
    ReviewerAccessor(Iteration& parent);

    void view_iteration_requests() const;
};
