so.json
=======

[JSON] *is a lightweight, text-based, language-independent data interchange format.*


What This Library Provides
--------------------------

- Against the JSON standard.

  The JSON standard is [RFC 7159]. Neither the *obsoleted* [RFC 4627]
  nor the *non-standard* one specified in [JSON.org].
  See the [history] for fun!

- A natural data wrapper, not a rigid codec.

  Converting smoothly from/to native types.

- Benefits from modern C++.

  - No explicit memory management (`new` and `delete`).

  - `auto`, `for` (each) and many others make the code easy to read.


API
---

See [json.hpp](include/json.hpp).

- Construct from JSON text.

  ```cpp
  static
  so::json  so::json::parse(std::string);
  ```

  E.g.
  ```cpp
  auto j = so::json::parse(R"json({"hello":"world"})json");
  ```

- Convert to JSON text.

  ```cpp
  std::string  so::json::stringify();
  ```

  E.g.
  ```cpp
  std::cout << j.stringify();
  ```
  > ```
  > {"hello":"world"}
  > ```
  ```cpp
  std::cout << j.stringify(true);
  ```
  > ```
  > {
  > 	"hello": "world"
  > }
  > ```

- Construct from native types.

  ```cpp
  // null
  so::json::json(std::nullptr_t);
  // boolean
  so::json::json(bool);
  // number
  so::json::json(double);
  // string
  so::json::json(std::string);
  // array
  so::json::json(std::vector<so::json>);
  // object
  so::json::json(std::map<std::string, so::json>);
  ```

  E.g.
  ```cpp
  so::json object{
    {
      {"hello", "world"},
      {"array", {{"J", "S", "O", "N"}}}
    }
  };
  ```

- Assign from native types.

  ```cpp
  // null
  so::json&  so::json::operator=(std::nullptr_t);
  // boolean
  so::json&  so::json::operator=(bool);
  // number
  so::json&  so::json::operator=(double);
  // string
  so::json&  so::json::operator=(std::string);
  // array
  so::json&  so::json::operator=(std::vector<so::json>);
  // object
  so::json&  so::json::operator=(std::map<std::string, so::json>);
  ```

  > **Tip!**
  > All of them return `*this`.

- Convert to native types.

  ```cpp
  // boolean
  so::json::operator bool();
  // number
  so::json::operator double();
  // string
  so::json::operator std::string();
  // array
  so::json::operator std::vector<so::json>();
  // object
  so::json::operator std::map<std::string, so::json>();
  ```

  > **Under The Hood!**
  > See [casting rules](CASTING.md) for more details.

  Plus reference edition for in place manipulating array and object.

  ```cpp
  // array
  so::json::operator std::vector<so::json>&();
  // object
  so::json::operator std::map<std::string, so::json>&();
  ```

- Access child element of array and object.

  ```cpp
  so::json&  so::json::operator[](size_t);
  so::json&  so::json::operator[](std::string);
  ```

  Which will throw `std::out_of_range` if child not exists.

  ```cpp
  so::json&  so::json::operator()(size_t);
  so::json&  so::json::operator()(std::string);
  ```

  Which will create default value if child not exists.

  > **Tip!**
  > Mix use of `size_t` and `std::string` is acceptable.
  > E.g.
  > ```cpp
  > auto a = so::json::parse(R"json(["hello", "world"])json");
  > auto o = so::json::parse(R"json({"2":"hello", "3":"world"})json");
  > std::cout << a["0"].stringify() << o[3].stringify();
  > ```
  >> ```
  >> "hello""world"
  >> ```

- Compare equalization.

  ```cpp
  bool  so::json::operator==(so::json);
  ```

  > **Note!**
  > `<` and `<=` etc. are not provided, as it is ambiguity to do so
  > between different internal types.
  > Explicit type casting is preferred before those comparison.

- Check type.

  ```cpp
  std::string  so::json::type_name();
  ```
  ```cpp
  bool  so::is::null(so::json);
  bool  so::is::boolean(so::json);
  bool  so::is::number(so::json);
  bool  so::is::string(so::json);
  bool  so::is::array(so::json);
  bool  so::is::object(so::json);
  ```


Acknowledgement
---------------

The [json11] library has some ideas and purposes similar with this library.
I learnt from it.


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

[json11]: https://github.com/dropbox/json11
"A tiny JSON library for C++11."

[LGPLv3]: http://www.gnu.org/graphics/lgplv3-88x31.png
"GNU Lesser General Public License version 3"
