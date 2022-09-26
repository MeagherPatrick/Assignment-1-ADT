#include <utility>

#include "Schedule.h"

using namespace std::rel_ops;

Schedule::Node::Node(Course c)
    :data(c),
    next(nullptr)
{
}

//------------------------------------------------------------------------------
Schedule::Schedule()
    :head(nullptr),
    tail(nullptr),
    totalCredits(0)
{
}

/**
 * @todo implement this function (it is simliar to Review 01)
 */
Schedule::Schedule(const Schedule& src)
    :head(nullptr),
    tail(nullptr),
    totalCredits(0)
{
    // Copy the src Linked List **data**
    this->head = nullptr;
    this->tail = nullptr;
    this->totalCredits = 0;

    // Start the Copy Operations
    Node* srcIt = src.head;

    while (srcIt != nullptr) {
        this->appendNoCheck(srcIt->data);

        srcIt = srcIt->next;
    }
}

/**
 * @todo implement this function (it is similar to Review 01)
 */
Schedule::~Schedule()
{
    Node* this_iterator = nullptr;  // Loop control pointer
    Node* to_delete = nullptr;  // Node to delete

    // start at the beginning of the this
    this_iterator = this->head;

    // iterate through the this and delete each node
    while (this_iterator != nullptr) {
        to_delete = this_iterator;

        // move to next node
        this_iterator = this_iterator->next;

        // delete the current node
        delete to_delete;

        to_delete = nullptr;  // dangling pointers are bad

        
        //std::cerr << "Deleting Node" << "\n";
    }

    
    //std::cerr << "Deleted List" << "\n";

    // no dangle ptr
    head = nullptr;
    tail = nullptr;

}



/**
 * @todo implement this function (it is similar to Review 01)
 */
void Schedule::appendNoCheck(Course course)
{
    // Create a new Node
    Node* courseNode = nullptr;

    // Store the "course" data within the node
    courseNode = new Node(course);

    // Handle the case where the first "course" is added 
    if (this->totalCredits == 0) {
        this->head = courseNode;
        this->tail = courseNode;
    }
    else {
        // Add the new course to the this
        //the current tail is set to courseNode maintaining the end of the list
        (this->tail)->next = courseNode;
        this->tail = courseNode;
    }
    //add credit hours 
    this->totalCredits += course.getCredits();

    // std::cerr << "totalCredits = " << this->totalCredits << std::endl;

     // Do not allow access to the node except
     // through the linked list
     // Is this line necessary?
    courseNode = nullptr;
}

/**
 * @todo implement this function
 */
bool Schedule::wouldViolateCreditLimit(Course course) const
{
    if (this->totalCredits >= 12)
    {
        return true;
    }
    return false;

}
/**
 * @todo implement this function
 */
bool Schedule::alreadyInSchedule(Course course) const
{
    // Loop control pointer
    Node* this_iterator = nullptr;


    // start at the beginning of the this
    this_iterator = this->head;

    // iterate through the this and **check if course is in schedule**
    while (this_iterator != nullptr) {
        if (this_iterator->data == course)
        {

            //std::cerr << "Course already in schedule";
            this_iterator = nullptr;
            return true;
        }
        // move to next node
        this_iterator = this_iterator->next;
    }
    return false;
}

//------------------------------------------------------------------------------
void Schedule::display(std::ostream& outs) const
{
    Node* it = head;

    outs << "  (" << totalCredits << " Total Credits)" << "\n";

    while (it != nullptr) {
        outs << "  - " << (it->data) << "\n";

        it = it->next;
    }
}

//------------------------------------------------------------------------------
Schedule& Schedule::operator=(Schedule rhs)
{
    swap(*this, rhs);

    return *this;
}
