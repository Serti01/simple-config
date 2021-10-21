# Types of Properties
Usable types and data type they represent
All types are case insensitive

`IEV` = Internal Enum Value (in regards to `sc::value_t`)
`IEV: enum value, enum name`, ie: `IEV: 3, boolean`

## Null
Represents nothing
ie: `property/null;`, `
IEV: 0, `null`

## Array
Represents an array of values of a certain types
ie: `property/array[type]: [...]`, `property/array[boolean]: [true,true,false];`<br/>
IEV: 1, `array`<br/>

## String
Represents a string of characters
ie: `property/string: "string";`, `name/string: "SimpleName";`<br/>
IEV: 2, `string`<br/>

## Boolean
Represents a true or false state (case insensitive)
ie: `property/boolean: true;`, `DebuggingEnabled/boolean: false;`<br/>
IEV: 3, `boolean`<br/>

## Integer
Represents a signed 8-bit integer
ie: `property/int: 25;`, `Directions/int: 3;`<br/>
IEV: 4, `nint`<br/>

## Unsigned Integer
Represents an unsigned 8-bit integer
ie: `property/uint: 100;`, `Balance/uint: 1230;`<br/>
IEV: 5, `nuint`<br/>

## Float
Represents an 8-bit floating point number
ie: `property/float: 3.14;`, `Price/float: 3.99;`<br/>
IEV: 6, `nfloat`<br/>

## Bytes
Represents an array of bytes
ie: `property/bytes: 0x1234;`, `MagicBytes/bytes: 0x01ff;`<br/>
IEV: 7, `bytes`<br/>