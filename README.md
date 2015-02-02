JSON Is Easy To Use In C++
==========================


[JSON](http://rfc7159.net/rfc7159 "JavaScript Object Notation")
*is a lightweight, text-based, language-independent data interchange format.*

JSON is commonly used in many other programming languages.
It is extremely useful in untrusted communications.


But, why another wheel?
-----------------------


Yes, there are many libraries can be used in C++ to decode/encode JSON.
But for those libraries I known - *I only know a few* :), I don't like them, because:

1. I want a flexible data wrapper, not a rigid codec.
   I.E. I don't want to copy data between the codec interface and the representation in my application.

   To achieve this, the interface a JSON library provided should:
   - has implicit type casting, e.g. numeric string to number, as other languages do;
   - has useful overloaded operators, to fit into an application smoothly.

2. Many of them are written in C (or C in mind), which are still hardly playing with their memories.
