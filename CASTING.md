Casting Between Content Types
=============================

Sections below will explain rules of casting a content type `A` (section head)
to another content type `B` (&rArr; column).

> **Go & Back**
> column indicates whether `a == (A)(B)a`.
>
> |  :x:  |     :o:     | *not set* |
> |:-----:|:-----------:|:---------:|
> | false | conditional |   true    |


Null
----

 From       | &rArr;  | To
-----------:|:-------:|:-----------
 `null`     | bool    | `false`
            | number  | `0.0`
            | string  | `""`
            | array   | `[]`
            | object  | `{}`


Boolean
-------

 From       | &rArr;  | To
-----------:|:-------:|:-----------
 `false`    | number  | `0.0`
            | string  | `""`
            | array   | `[]`
            | object  | `{}`
 `true`     | number  | `1.0`
            | string  | `"1"`
            | array   | `[true]`
            | object  | `{"0":true}`


Number
------

 From       | &rArr;  | Go & Back | To
-----------:|:-------:|:---------:|:-----------
 `0`        | boolean |           | `false`
 `Infinity` | string  |           | `"Infinity"`
 `NaN`      | string  |           | `"NaN"`
            | array   |           | `[]`
            | object  |           | `{}`
 otherwise  | boolean | :x:       | `true`
            | string  |           | `printf("%.16g", x)`
            | array   |           | `[x]`
            | object  |           | `{"0":x}`


String
------

 From       | &rArr;  | Go & Back | To
-----------:|:-------:|:---------:|:-----------
 `""`       | boolean |           | `false`
            | array   |           | `[]`
            | object  |           | `{}`
 otherwise  | boolean | :x:       | `true`
            | number  | :o:       | `std::strtod(x)`
            | array   |           | `[x]`
            | object  | :x:       | `{"0":x}`

> :o: If the content is numeric, as described in [std::strtod].
[std::strtod]: http://en.cppreference.com/w/cpp/string/byte/strtof


Array
-----

 From       | &rArr;  | Go & Back | To
-----------:|:-------:|:---------:|:-----------
 `[]`       | boolean |           | `false`
            | number  |           | `NaN`
 size()==1  | number  | :o: :one: | 1<sup>st</sup> child
 otherwise  | boolean | :x:       | `true`
            | number  | :x:       | `Infinity`
            | string  | :o: :two: | comma separated children
            | object  |           | index as key

> :o: :one: If the only child is a `number`.

> :o: :two: If there is only one `string` child.

### Caution!

Stacked array cannot be distinguished from flat array when casting to string.
E.g.
```cpp
std::cout << so::json::parse("[1,2,[3,4,[5,6],7,8],9,0]").to_string();
```
> ```
> 1,2,3,4,5,6,7,8,9,0
> ```


Object
------

 From       | &rArr;  | Go & Back | To
-----------:|:-------:|:---------:|:-----------
 `{}`       | boolean |           | `false`
            | number  |           | `NaN`
            | string  |           | `""`
            | array   |           | `[]`
 size()==1  | number  | :o:       | 1<sup>st</sup> child
 otherwise  | boolean | :x:       | `true`
            | number  | :x:       | `-Infinity`
            | string  | :x:       | `(`type`:`count`)` *recursively, see below*
            | array   | :x:       | values (sorted by keys)

> :o: If the only child is a `number`.

### Example of casting `object` to `string`

```cpp
auto object = R"json(
{
    "0":[],
    "1":[1],
    "2":"two",
    "3":{
        "0":null,
        "1":false,
        "2":true
    },
    "4":{
        "3":true,
        "4":false,
        "5":null
    },
    "5":{
        "0":"hello",
        "1":"world"
    }
}
)json";
std::cout << so::json::parse(object).to_string();
```
> ```
> ((boolean:2 null:1):2 (string:2):1 array:2 string:1)
> ```