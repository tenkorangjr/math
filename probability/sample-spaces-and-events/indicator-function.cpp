#include <iostream>
#include <cstdlib>

class SampleSpace {
    public: 
        SampleSpace(int sz) 
        :   omega_(sz) {
            for (int i = 0; i < sz; i++) {
                omega_[i] = rand() % 101; // generate a random number b/n 1 and 100
            }
        }

        /**
         * Generate an Event of a random size
         */
        std::vector<int> GenerateEvent() {


        }

        /**
         * Generate Event of a specified size
         */
        std::vector<int> GenerateEvent(int sz) {

        }

    private: 
        std::vector<int> omega_;

};