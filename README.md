# DbaseFirm
## _c++ database engine_

A c++ project that I created in 2004-ish.  It was a sort of apprentice piece to employ structures that I was learning about at the time, with an early take on MVC, and datastructures where the database records were made of linked lists joining fields where each field in the column was part of a binary tree.  The aim was to create an object oriented database abstraction language which I seem to recall I did.
## caveat...
I created the c++ database engine using visual C++ 6.0 and had to fiddle one of the pointer mechanisms (from memory), a hack that was removed in the next version of C++.  So, its legacy code and fairly unpolished as I was still very much a student of coding early on in my dubious 'career'...

I tend to license all my stuff using an MIT license, although it probably isn't required in this case...

## My readme.txt written at the time...

## My First Database
-----------------

This is my first attempt at a program in c++ and as such I have 
used it as an opportunity to explore alternative programming
constructs.
It is a database where the fields are templated AVL trees.
Each item stored in an avl tree has a pointer to a record
which in turn has pointers to its fields.

The positive points about using this design are that each 
AVL tree can be searched independently using multithreading,
and in future, records could be displayed sorted by fieldtype.

The search function creates a searchobject from the given string
and passes this to the searchfunction in datafile which iterates
through the entries in the searchobject and searches the 
appropriate avltree in its own thread, adding the found 
recordnumbers to a vector of ints (in class termRecords) of
which there are as many as there are entries in the searchobject. 

As this is my first c++ program it is poorly designed.  
I can't help feel that a lot of the dynamic casting that 
goes on in datafile is due to poor design but it could be due 
to the templates. I created
the program on the fly without much planning. In review there are
lots of things that I could have done differently and would have
done if I had continued developing the program.  This approach to
creating a program is, I believe, called the iterative design
process and should be avoided by good forward planning and design.

In future, I will attempt to design programs using UML but at
least this program has helped me learn the STL, multithreading
issues, templated design, advanced data structures and windows
programming techniques amongst others.

If I were to develop this program then the first thing that I
would do would be to re write the search function to use a
parse tree.
