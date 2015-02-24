so.json
=======

[JSON] *is a lightweight, text-based, language-independent data interchange format.*

This library brings a natural interface into C++ for playing with JSON data.


But, why another wheel?
-----------------------

Yes, there are many libraries can be used in C++ to decode/encode JSON.
But for those libraries I known -*I only know a few :sweat_smile:*,
I don't like them, because:

1. I want a natural data wrapper, not a rigid codec.
   I.e. I don't want to copy data between the interface provided by a library
   and the representation in my application.

   Instead of, I want the library:
   - has implicit type casting, e.g. numeric string to number, as other languages do;
   - has useful overloaded operators, to fit into an application directly & smoothly.

2. They are written in C (or C in mind), which are still hardly playing with their memories.

3. They are not written against the JSON standard.
   The JSON standard is [RFC 7159]. Neither [RFC 4627] nor the one specified in [JSON.org].
   See the [history] for fun!

4. They are not benefited from the new C++ standards.
   C++11 and C++14 make coding much easier.


So, how to use this library?
----------------------------

_TODO_ :running:


My personal opinions
--------------------

JSON is extremely useful in untrusted communications.

_CONTINUE_ :running:


License
-------
![LGPLv3]

Copyright (C) 2015  Iceberg YOUNG

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


---

[JSON]: http://rfc7159.net/rfc7159
"JavaScript Object Notation"

[RFC 7159]: http://www.rfc-editor.org/rfc/rfc7159.txt
"The JavaScript Object Notation (JSON) Data Interchange Format"

[RFC 4627]: http://www.rfc-editor.org/rfc/rfc4627.txt
"The application/json Media Type for JavaScript Object Notation (JSON)"

[JSON.org]: http://json.org/
"Introducing JSON"

[history]: https://www.tbray.org/ongoing/When/201x/2014/03/05/RFC7159-JSON
"JSON Redux AKA RFC7159"

[LGPLv3]: http://www.gnu.org/graphics/lgplv3-88x31.png
"GNU Lesser General Public License version 3"
