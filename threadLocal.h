//
// Created by Dhiraj Borade on 10/05/16.
//

#ifndef THREADLOCAL_H_
#define THREADLOCAL_H_

#include <iostream>
#include <mutex>
#include <thread>
#include <pthread.h>
#include <map>
#include <algorithm>
using namespace std;

namespace cop5618
{
    template <typename T>
    class threadLocal
    {
    public:
        threadLocal(){
            thread_id = (long)pthread_self(); // variable used to store an unique id as per each thread
        }
        ~threadLocal(){}
        //disable copy, assign, move, and move assign constructors
        threadLocal(const threadLocal&) = delete;
        threadLocal& operator = (const threadLocal&) = delete;
        threadLocal(threadLocal&&) = delete;
        threadLocal& operator = (const threadLocal&&) = delete;
        /**
        * Returns a reference to the current thread's value.
        * If no value has been previously set by this
        * thread, an out_of_range exception is thrown.
        *
        */
        const T& get() const
        {
            std::lock_guard<std::mutex> guard(map_mutex);
            if (threadLocal::mymap.find(thread_id) != threadLocal::mymap.end())
                return threadLocal::mymap.find(thread_id) -> second;
            else throw std::runtime_error("Out of Range");
        }

        /**
        * Sets the value of the threadLocal for the current thread
        * to val.
        */

        void set(T setValue)
        {
            std::lock_guard<std::mutex> guard(map_mutex); // Value corresponding to the thread is stored and a key is assigned
            threadLocal::mymap[thread_id] = setValue;
        }

        /**
        * Removes the current thread's value for the threadLocal
        */

        void remove()
        {
            std::lock_guard<std::mutex> guard(map_mutex);
            if (threadLocal::mymap.find(thread_id) != threadLocal::mymap.end())
                threadLocal::mymap.erase(thread_id);
            else throw std::runtime_error("No such element is present in the map");
        }

        /**
        * Friend function. Useful for debugging only, shows values for all threads.
        */

        template <typename U>
        friend std::ostream& operator<< (std::ostream& outputStream, const threadLocal<U>& obj)
        {
            std::lock_guard<std::mutex> lock(obj.map_mutex);
            for( auto i = obj.mymap.begin(); i != obj.mymap.end(); ++i )
            {
                outputStream << i -> first << " - " << i -> second;
            }
            return outputStream;
        }

    private:
        typedef std::map<uint64_t,T> varMap; // Variable Map is declared
        varMap mymap;
        uint64_t thread_id; // key used to identify different threads
        mutable std::mutex map_mutex;
    };
} /* namespace cop5618 */
#endif /* THREADLOCAL_H_ */