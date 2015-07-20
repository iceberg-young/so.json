Casting Between Content Types
=============================

Sections below will explain rules of casting a content type `A` (section head)
to another content type `B` (&rArr; column).

> **Go & Back**
> column indicates whether `a == (A)(B)a`.
> :x:: false; :o:: conditional true; empty: true.

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
 default    | boolean | :x:       | `true`
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
 default    | boolean | :x:       | `true`
            | number  | :o:       | [`strtod(x)`]
            | array   |           | `[x]`
            | object  | :x:       | `{"0":x}`

[`strtod(x)`]: http://en.cppreference.com/w/cpp/string/byte/strtof


Array
-----

 From       | &rArr;  | Go & Back | To
-----------:|:-------:|:---------:|:-----------
 `[]`       | boolean |           | `false`
            | number  |           | `NaN`
 default    | boolean | :x:       | `true`
            | number  | :o:       | 1<sup>st</sup> child
            | string  | :o:       | comma separated children
            | object  |           | index as key


Object
------

 From       | &rArr;  | Go & Back | To
-----------:|:-------:|:---------:|:-----------
 `{}`       | boolean |           | `false`
            | number  |           | `NaN`
            | string  |           | `""`
            | array   |           | `[]`
 default    | boolean | :x:       | `true`
            | number  | :o:       | 1<sup>st</sup> child
            | string  | :x:       | `"[type key]\nvalue"`
            | array   | :x:       | values (sorted by keys)
