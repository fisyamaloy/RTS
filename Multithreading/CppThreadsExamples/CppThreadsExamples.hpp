#pragma once
#include <chrono>
#include <condition_variable>
#include <csignal>
#include <iostream>
#include <mutex>
#include <thread>

namespace CppThreadsExamples
{
    namespace SimpleExample
    {
        void foo()
        {
            for (int i = 0; i < 10; ++i)
            {
                std::cout << "thread_id: " << std::this_thread::get_id() << " foo()" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }

        void run()
        {
            std::thread thr(foo);
            thr.detach();

            for (int i = 0; i < 10; ++i)
            {
                std::cout << "thread_id: " << std::this_thread::get_id() << " run()" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
            }
        }
    }  // namespace SimpleExample

    namespace PassingArgumentsToThread
    {
        void displaySum(const int a, const int b)
        {
            std::cout << "displaySum() STARTED" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            std::cout << "a + b = " << a + b << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "displaySum() FINISHED" << std::endl;
        }

        void run()
        {
            std::thread thr(displaySum, 3, 2);

            for (int i = 0; i < 10; ++i)
            {
                std::cout << "thread_id: " << std::this_thread::get_id() << " foo()" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            thr.join();
        }
    }  // namespace PassingArgumentsToThread

    namespace GettingResultFromThread
    {
        int calculateSum(const int a, const int b)
        {
            std::cout << "displaySum() STARTED" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            std::cout << "displaySum() FINISHED" << std::endl;

            return a + b;
        }

        void run()
        {
            int         result;
            std::thread thr([&result]() { result = calculateSum(3, 4); });

            for (int i = 0; i < 10; ++i)
            {
                std::cout << "thread_id: " << std::this_thread::get_id() << " foo()" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            thr.join();
            std::cout << result << std::endl;
        }
    }  // namespace GettingResultFromThread

    namespace ThreadsAndClassMethods
    {
        class MyClass
        {
        public:
            void displaySum(const int a, const int b)
            {
                std::cout << "displaySum() STARTED" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                std::cout << "a + b = " << a + b << std::endl;

                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "displaySum() FINISHED" << std::endl;
            }

            int calculateSum(const int a, const int b)
            {
                std::cout << "displaySum() STARTED" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                std::cout << "displaySum() FINISHED" << std::endl;
                return a + b;
            }

            void calculateSum(const int a, const int b, int& result)
            {
                std::cout << "displaySum() STARTED" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                result = a + b;
                std::cout << "displaySum() FINISHED" << std::endl;
            }
        };

        void run()
        {
            MyClass m;

            int         result_1;
            std::thread t_1([&]() { result_1 = m.calculateSum(3, 4); });
            t_1.join();
            std::cout << "int calculateSum(const int a, const int b): " << result_1 << std::endl;

            std::thread t_2(&MyClass::displaySum, m, 3, 5);
            t_2.join();

            int         result_3;
            std::thread t_3([&result_3, &m]() { m.calculateSum(1, 2, result_3); });
            t_3.join();
            std::cout << "int calculateSum(const int a, const int b): " << result_3 << std::endl;
        }

    }  // namespace ThreadsAndClassMethods

    namespace SimpleMutex
    {
        std::mutex m;

        void unsafe_output(const char symb) 
        {
            std::cout << symb << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        void foo(const char symb)
        {
            while (true)
            {
                std::lock_guard<std::mutex> lg(m);
                unsafe_output(symb);
            }
        }

        void run()
        {
            std::thread t_1(foo, '#');
            std::thread t_2(foo, '@');
            t_1.join();
            t_2.join();
        }

    }  // namespace SimpleMutex

    namespace Deadlock
    {
        std::mutex m_1;
        std::mutex m_2;

        void foo(const char symb)
        {
            for (int i = 0; i < 10; ++i)
            {
                m_1.lock();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                m_2.lock();

                std::cout << symb << std::endl;
                m_1.unlock();
                m_2.unlock();
            }
        }

        void bar(const char symb)
        {
            for (int i = 0; i < 10; ++i)
            {
                m_2.lock();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                m_1.lock();

                std::cout << symb << std::endl;
                m_2.unlock();
                m_1.unlock();
            }
        }

        void run()
        {
            std::thread t_1(foo, '#');
            std::thread t_2(bar, '@');
            t_1.join();
            t_2.join();
        }
    }  // namespace Deadlock

    namespace RecursiveMutex
    {
        std::recursive_mutex rm;

        void show(const int quantity)
        {
            rm.lock();
            std::cout << quantity << " ";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            if (quantity < 0)
            {
                std::cout << '\n';
                rm.unlock();
                return;
            }

            show(quantity - 1);
            rm.unlock();
        }

        void run()
        {
            std::thread t_1(show, 10);
            std::thread t_2(show, 10);
            t_1.join();
            t_2.join();
        }
    }  // namespace RecursiveMutex

    namespace ConditionalVariable
    {
        std::condition_variable cv;
        std::mutex              m;
        bool                    showNumbers = false;

        void foo()
        {
            static int counter = 0;

            while (true)
            {
                std::unique_lock<std::mutex> ul(m);
                cv.wait(ul, []() {
                    return showNumbers;
                });  // The same as: while (!showNumbers) cv.wait(ul);

                std::cout << ++counter << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }

        void bar()
        {
            while (true)
            {
                char key;
                std::cin >> key;

                if (key == 'y')
                {
                    showNumbers = true;
                    cv.notify_one();
                }
                else if (key == 'n')
                    showNumbers = false;
            }
        }

        void run()
        {
            std::thread t_1(foo);
            std::thread t_2(bar);
            t_1.join();
            t_2.join();
        }

    }  // namespace ConditionalVariable

}  // namespace CppThreadsExamples

namespace IPCSignalExamples
{
    void sigintHandler(int signum)
    {
        std::cout << "Interrupt signal (" << signum << ") received.\n";

        // cleanup and close up stuff here
        // terminate program

        exit(signum);
    }

    void run()
    {
        signal(SIGINT, sigintHandler);

        int i = 0;
        while (1)
        {
            if (++i == 3) raise(SIGINT);

            std::cout << "Going to sleep...." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

}  // namespace IPCSignalExamples
