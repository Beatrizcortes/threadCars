# threadCars

(4). It is used to generate a random integer (which will probably be really big). Since we’re using this number as the argument for sleep() and we don’t want to risk it of sleeping for too long, we pick the random number, divide it by 4 to make it significantly smaller and add 1 just in case the generated number was 0.

(5). Threads are different than processes and have no parental relationships with each other. Whenever the thread that created the others is finished, the process ends, thus bringing down with it the other threads. The only dependency relationship existing between threads is the “main” thread that was created when the process began.

(6). Of course, this calculation can imply a problem. Given that it’s a global variable, all threads can access it, and since every thread will access and change the variable at a random time, there is the possibility that two threads try to access it at the same time. If this happens, the outcome is hard to predict, but it’s better to avoid this problem altogether by placing a semaphore to lock the thread trying to access the variable if another one is doing it already. This is done by locking it before accessing the variable and, after changing it, unlocking the semaphore. This has been implemented in the code.
