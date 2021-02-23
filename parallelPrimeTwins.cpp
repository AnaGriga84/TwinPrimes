/*! \mainpage Twin Prime Numbers Project
    \author Ana Griga , Student Number: C00231441
    \date 22.02.2021
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <chrono>
/*! 
  \file parallelPrimeTwins.cpp
  \brief The task is to implement a parallel program that counts the number of prime numbers less than a given number and 
  finds a list of all twin primes less than the given number and also the twin prime pairs. A twin prime pair being a prime number
  that has a prime gap of 2. For acheiving parallelism, OpenMP was used as follows:
     \param  #pragma omp parallel – this is the basic directive that defines the code that it will execute in parallel and is used to fork supplementary threads to carry out the work attached in the block of code after the #pragma construct. The block will be all  executed in parallel by all the threads.
      \param #pragma omp parallel for – used in the code above divides the iterations of the for loop between the produced threads.
      \param #pragma omp parallel for schedule(dynamic) – schedule controls how the loop iterations are distributed between the threads. Static means that it is determined at the beginning which thread will do which value and dynamic means that each thread will work on a portion of values and then take the next portion which has not been processed by any thread. Dynamic improves balancing even though it involves some communication overheads. 
      \param #pragma omp parallel for schedule(dynamic) num_threads(numberOfThreads) – sets limits on the amount of threads that
      \param #pragma omp critical – defines the section of the code that must be executed by only a single thread at the time. Only one thread can enter a critical section at a time; others are kept at the entrance to critical section. This directive prevents any race conditions from happening
  */


/*! \fn bool checkPrime(int number)
	\brief The first method is a boolean method which checks if the given number is prime. The corner cases are checked and the for loop passes over the middle five numbers.
*/

bool checkPrime(int number)
{
    int num = number;
    if(num <= 1) return false;
    if(num <= 3) return true;

    if(num % 2 == 0 || num %3 ==0) return false;
    //skiping the middle five numbers
    for(int i=5; i*i<=num; i=i+6)
    {
        if(num%i == 0 || num%(i+2) == 0) 
        return false;
    }
    return true;
}
/*! \fn void primeRange(int first, int last)
    \brief This method traverses each numbers in the interval and counts how many numbers of primes are up to the number introduced.
*/  
void primeRange(int first, int last)
{
    int i;
    int count = 0;
    #pragma omp parallel for schedule(dynamic) num_threads(4) 
    for(i = first; i<= last; i++)
    {
        if(checkPrime(i))
        {
             #pragma omp critical
            //printf("%d \n" , i);
            count ++;
        }
    }
    printf("The number of primes: %d \n", count);
}
/*! \fn void primePairs(int first, int last)
    \brief The primePairs method prints the twin numbers checking first if the numbers are prime using the checkPrime method. 
    It is printing the current prime number and the current prime number at which 2 is added, which are the twin prime numbers.
*/  
void primePairs(int first, int last)
{
    std::cout << "Twin Primes: " <<std::endl;
    int count = 0;
    #pragma omp parallel for schedule(dynamic) num_threads(4)
    for(int i= first; i<= last; i++)
    {
        if(checkPrime(i) && checkPrime(i+2))
        {
            #pragma omp critical 
            count++;
            printf("[ %d, %d ] \n", i, i+2);
        }
    }
    printf("There are %d prime pairs between %d and %d \n", count, first, last);
}
 
int main(int argc, char *argv[])
{
    int first=1;
    char *value = argv[1];
    int last = atoi(value);
    auto startTime = std::chrono::high_resolution_clock::now();
    primeRange(first, last);
    primePairs(first, last);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime).count();  
    std::cout << "Parallel, 4 threads,  5000000 : "  << duration << " milliseconds" <<std::endl;
    return 0;
}

