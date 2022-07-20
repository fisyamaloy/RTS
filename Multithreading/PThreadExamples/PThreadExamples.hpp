#include <Windows.h>
#include <pthread.h>
#include <iostream>

namespace pthread_examples
{
    namespace SimpleExample
    {
        void* sleepAndShow(const char* message)
        {
            for (int i = 0; i < 10; ++i)
            {
                Sleep(100);
                std::cout << message;
            }

            pthread_exit(NULL);
            return nullptr;
        }
        void* foo(void*)
        {
            return sleepAndShow("foo\n");
        }
        void* bar(void*)
        {
            return sleepAndShow("bar\n");
        }

        void run()
        {
            std::cout << "Start of SimpleExample running:\n";

            pthread_t threadInfo_1;
            if (pthread_create(&threadInfo_1, NULL, &foo, NULL) != 0) throw 1;
            pthread_t threadInfo_2;
            if (pthread_create(&threadInfo_2, NULL, &bar, NULL) != 0) throw 2;

            if (pthread_join(threadInfo_1, NULL) != 0) throw 3;
            if (pthread_join(threadInfo_2, NULL) != 0) throw 4;

            std::cout << "End of SimpleExample running\n";
            std::cout << "----------------------------\n";
        }
    }  // namespace example_1

    /////////////////////////////////////////
    namespace MutexExample
    {
        pthread_mutex_t mutex;

        void* sleepAndShow(const char* message)
        {
            for (int i = 0; i < 10; ++i)
            {
                Sleep(100);

                pthread_mutex_lock(&mutex);
                std::cout << message << std::endl;
                pthread_mutex_unlock(&mutex);
            }

            pthread_exit(NULL);
            return nullptr;
        }
        void* foo(void*)
        {
            return sleepAndShow("foo");
        }
        void* bar(void*)
        {
            return sleepAndShow("bar");
        }

        void run()
        {
            std::cout << "Start of MutexExample running:\n";

            pthread_mutex_init(&mutex, NULL);
            {
                pthread_t threadInfo_1;
                if (pthread_create(&threadInfo_1, NULL, &foo, NULL) != 0) throw 1;
                pthread_t threadInfo_2;
                if (pthread_create(&threadInfo_2, NULL, &bar, NULL) != 0) throw 2;

                if (pthread_join(threadInfo_1, NULL) != 0) throw 3;
                if (pthread_join(threadInfo_2, NULL) != 0) throw 4;
            }
            pthread_mutex_destroy(&mutex);

            std::cout << "End of MutexExample running\n";
            std::cout << "----------------------------\n";
        }
    }  // namespace example_2

    /////////////////////////////////////////
    namespace LoopThreadsExample
    {
        pthread_mutex_t mutex;

        void* foo(void* index) 
        {
            for (int i = 0; i < 10; ++i) 
            {
                Sleep(100);
                
                pthread_mutex_lock(&mutex);
                std::cout << *reinterpret_cast<int*>(index) << std::endl;
                pthread_mutex_unlock(&mutex);
                
            }

            delete index;
            return static_cast<void*>(new int(10));
        }

        void run() 
        {
            std::cout << "Start of LoopThreadsExample running:\n";
            
            pthread_mutex_init(&mutex, NULL);

            const int THREADS_AMOUNT = 4;
            pthread_t threadsInfo[THREADS_AMOUNT];

            for (int i = 0; i < 2; ++i) 
            {
                pthread_create(threadsInfo + i, NULL, &foo, new int(1));
            }

            for (int i = 2; i < 4; ++i) 
            { 
                pthread_create(threadsInfo + i, NULL, &foo, new int(2)); 
            }

            for (int i = 0; i < THREADS_AMOUNT; ++i) 
            {
                int* result;
                pthread_join(threadsInfo[i], reinterpret_cast<void**>(&result));
                
                pthread_mutex_lock(&mutex);
                std::cout << *result << std::endl;
                pthread_mutex_unlock(&mutex);
                
                delete result;
            }

            pthread_mutex_destroy(&mutex);

            std::cout << "End of LoopThreadsExample running\n";
            std::cout << "----------------------------\n";
        }
    }

}  // namespace pthread_examples
