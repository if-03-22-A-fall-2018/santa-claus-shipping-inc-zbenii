# Assignment - Santa Claus Shipping Inc.
While this assignment does not require you to write a lot of code (it is Christmas after all) you will work with some concepts we haven't trained extensively yet:
- memory allocations
- freeing of allocated memory
- more "generic" approaches in C

But there is nothing new so don't worry, just think a bit, revisit the lecture slides and you should be good to go.
As usual you are allowed to create as many additional (=not contained in the header files) functions as you need to write a clean and structured program.

## General idea
You are going to help Santa manage his shipments of presents to (only the nice!) kids in several cities.
We have information about children (their name, in which city they live and how good they behaved in the last year). This data is input into a collection.
But to get a good working tour plan for Christmas Eve, we'll need to optimize and group kids living in the same city together, to avoid multiple trips to the same place.
I suggest you attempt to solve this assignment by following the tasks in the order outlined below.
**Important:** In some tasks you will need to allocate memory. 
Be careful to implement proper delete methods to clean up at the end.

### Task 1 - Implementing a List
You already learned about linked lists, the most primitive collection type.
Now you are going to implement one of these with the following characteristics:
- The list will normally insert elements prepending (vs. appending)
- You don't need to implement logic for removing elements this time
- The list is only single linked
- The list will (additionally!) provide an option to insert after a specific node (this allows us to do a simple kind of sorted insert)
- **Most importantly:** You will implement a "generic" list, which can take any kind of data. The same implementation will be used several times in this assignment with different data in the nodes, so it is paramount to get this right. Hint: `void*`

### Task 2 - Child Data Management
This is basically a wrapper around our generic list that takes care of the sorted insert (remember: we need to group kids by city).
If your list implementation is sound this should be quick and easy to implement.

### Task 3 - Tour Planner
This is where most of our business logic lives. 
When provided the child management you implemented in the previous task (which already supplies us with a sufficiently sorted list) you will create a TourPlan.
A TourPlan is a nested data structure.
The root node contains some aggregated information and most importantly a list of plans for individual cities.
These CityPlans in turn contain the name of the city and a list of plans for individual kids (in this city).
The ChildPlan finally contains the name of the kid and how many presents he or she will received.
Hint: all those lists are not particularly sorted, you can use the default (prepending) add method.

Additionally, we need to calculate how many presents a child gets based on how good or bad he or she behaved.
The rule is simple: you get nothing unless you've been at least more good than bad (factor >= 0.6).
The maximum number of presents is 10, which you'll get at a factor >=1.0.
Hint: look at the respective test to get an understanding of how (simple) the distribution is supposed to work.

### Task 4 - Sample Program Run
In the previous tasks you implemented the whole program.
So at this point all UnitTests should be green.
Now you'll have to implement the proper output for our created TourPlan (because Santa needs it printed to take with him on the sleigh!).
In the file `santa_claus_main_driver.cpp` is a sample run already prepared. 
Create the print logic so that the following output is (exactly!) produced:
```
Shipping 14 presents to 6 children!
***
Shipment to Traun:
Horst: 0 presents
***
Shipment to Leonding:
Herbert: 2 presents
Peter: 5 presents
Susi: 0 presents
***
Shipment to Linz:
Maria: 3 presents
Daniel: 4 presents
***
```

### Task 5 - Memory Cleanup
Throughout the assignment you allocated memory dynamically.
As you know we can't rely on a garbage collector to automatically take care of the mess we created.
So we have to be very careful to free all memory blocks we previously allocated.
To help you ensure this you will use the tool valgrind (which you may have to install first).
Running the command ` valgrind --tool=memcheck ./santa_claus` has to produce an output like that:
```
==10208== HEAP SUMMARY:
==10208==     in use at exit: 0 bytes in 0 blocks
==10208==   total heap usage: 32 allocs, 32 frees, 1,472 bytes allocated
==10208== 
==10208== All heap blocks were freed -- no leaks are possible
```
The important part is, of course, that all allocated blocks have been properly freed by you.
Also be careful not to perform a "double-free" (freeing memory you already freed) or to read freed memory. 
All of these mistakes will show up in the valgrind report.
**Proper memory management is an important part of this assignment, having all unit test go green will not be enough this time!**

### Task 6 - Bonus
As a special Christmas gift you are given the chance to compensate for a few minor mistakes you made while implementing the main program.
To get this bonus you'll have to implement a user interface for our program, so that it is no longer necessary to define the child infos statically in code.
Come up with a process that prompts the program user to enter required information (city, name, goodness factor).
Multiple children can be inserted (no fixed limit), so... maybe you can use your list again? ;)

Be careful to implement proper input validation with re-prompts if incorrect data is provided.
