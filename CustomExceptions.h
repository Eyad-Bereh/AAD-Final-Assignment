#ifndef __CUSTOM_EXCEPTIONS_H__
#define __CUSTOM_EXCEPTIONS_H__

#include <exception>
#include "Patch.h"

namespace CustomExceptions {
    class AssigningWeightToUnWeightedGraphException : public std::exception {
        public:
        virtual const char* what() const throw() {
            return "Error: weighted graph must be assigned a weight for each of its edges.\nTo resolve this error call the Graph::AddEdge() method which takes 3 parameters instead of 2.";
        }
    };

    class NotAssigningWeightToWeightedGraphException : public std::exception {
        public:
        virtual const char* what() const throw() {
            return "Error: unweighted graph cannot be assigned a weight for any of its edges.\nTo resolve this error call the Graph::AddEdge() method which takes 2 parameters instead of 3.";
        }
    };

    class EdgeNotExistException : public std::exception {
        private:
            int start;
            int end;

        public:
        EdgeNotExistException(int start, int end) {
            this->start = start;
            this->end = end;
        }

        virtual const char* what() const throw() {
            std::string message = "Error: no such edge from node ";
            message += std::to_string(this->start);
            message += " to node ";
            message += std::to_string(this->end);
            message += " exist.";
            return message.c_str();
        }
    };

    class GraphOutOfBoundsException : public std::exception {
        private:
        int GraphSize;
        int GivenValue;

        public:
        GraphOutOfBoundsException(int GraphSize, int GivenValue) {
            this->GraphSize = GraphSize;
            this->GivenValue = GivenValue;
        }

        virtual const char* what() const throw() {
            std::string message = "Error: graph out of bounds.\nDouble check the supplied parameters and make sure that you haven't supplied a negative value or a value greater than or equal to graph size.\nNotice that the graph contains only ";
            message += std::to_string(this->GraphSize);
            message += " nodes while.\nGiven value: ";
            message += std::to_string(this->GivenValue);
            return message.c_str();
        }
    };
}

#endif