//
// Created by Dhiraj Borade on 10/05/16.
//

/** Main function for HW1
 *
 * Make sure your program runs with this.
 */

#include <iostream>
#include "threadLocal.h"

using namespace cop5618;
using namespace std;

int errorCounter = 0;

threadLocal<int> variableThreadLocal; // Global variable declared which is used as Thread Local Variable

int test_threadLocal();
void testCase01();
void testCase02();
void testCase03();
void testCase04();
void testCase05();
void testCase06();


int main()
{
    int err = test_threadLocal();
    cout << err << " of 6 test cases have failed" << endl;
    return err;
}

int test_threadLocal()
{
    testCase01(); // Set value where the thread does not have a preexisting value.
    testCase02(); // Set value where the thread has a preexisting value
    testCase03(); // Attempt to read a non-existing value
    testCase04(); // Read an existing value
    testCase05(); // Remove a value
    testCase06(); // Attempt to remove a non-existing value

    return errorCounter;

}

void function01 (const string& name, int value)
{
    variableThreadLocal.set(value);
    cout << "Value Set : " << value << " in Thread : " << name << endl;
}

void function02 (const string& name, int value1, int value2)
{
    variableThreadLocal.set(value1);
    cout << "Value Set : " << value1 << " in Thread : " << name << endl;
    variableThreadLocal.set(value2);
    cout << "Preexisting Value Replaced : " << value2 << " in Thread : " << name << endl;
}

void function03 (const string& name)
{
    try
    {
        variableThreadLocal.get();
    }
    catch (exception& e)
    {
        cout << "No value present in Thread: " << name << endl;
        errorCounter++;
    }
}

void function04 (const string& name, int value)
{
    variableThreadLocal.set(value);
    try
    {
        variableThreadLocal.get();
    }
    catch (exception& e)
    {
        cout << "Value in Thread " << name << " : " << variableThreadLocal.get() << endl;
        errorCounter++;
    }
}

void function05 (const string& name, int value)
{
    variableThreadLocal.set(value);
    try
    {
        variableThreadLocal.remove();
    }
    catch (exception& e)
    {
        cout << "Value removed from the Map corresponding to Thread: " << name << endl;
        errorCounter++;
    }
}

void function06 (const string& name)
{
    try
    {
        variableThreadLocal.remove();
    }
    catch (exception& e)
    {
        cout << "No such element found in the Thread:" << name << endl;
        errorCounter++;
    }
}

void testCase01()
{
    thread a(function01, "A", 100);

    a.join();
}

void testCase02()
{
    thread b(function02, "B", 200, 300);

    b.join();
}

void testCase03()
{
    thread c(function03, "C");

    c.join();
}

void testCase04()
{
    thread d(function04, "D", 400);

    d.join();
}

void testCase05()
{
    thread e(function05, "E", 500);

    e.join();
}

/* This test case fails, since it tries to remove an non existing value */
void testCase06()
{
    thread f(function06, "F");

    f.join();
}

