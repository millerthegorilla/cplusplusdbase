My First Database
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

