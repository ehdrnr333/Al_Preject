# C++ Work Note

> Author  : Park Dong-Ha (luncliff@gmail.com)  
> Updated : 16/06/04 


## Done

### Add
#### Created **Model** directory  
#### `CourseInterpreter` class
  Actually, the class is parsor for CSV file and create an `Course` object from the text stream.
  It doesn't contain the abstract model for the file's content and the only delimeter for CSV is '\t'.


### Change
#### `ILecTime` to `LecTime`  
  The lecture time interface is now light class.
  
#### `ICourse` to `Course`  
  The minimal concrete class for course concept.
  The new class is containing `LecTime`


### Remove
#### `TestLecture` class


## Tasks / To Do 
### `Day` files
  Current files doesn't support comparison with UTF-8 expression.
  Maybe regular expression can work better.

