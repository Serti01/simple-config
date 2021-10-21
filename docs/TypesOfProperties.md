# Types of Properties
Usable types and data type they represent<br/>
All types are case insensitive<br/>

`IEV` = Internal Enum Value (in regards to `sc::value_t`)<br/>
`IEV: enum value, enum name`, ie: `IEV: 3, boolean`<br/>

## Null
Represents nothing<br/>
ie: `property/null;`<br/>
IEV: 0, `null`<br/>

## Array
Represents an array of values of a certain types<br/>
ie: `property/array[type]: [...]`, `property/array[boolean]: [true,true,false];`<br/>
IEV: 1, `array`<br/>

## String
Represents a string of characters<br/>
ie: `property/string: "string";`, `name/string: "SimpleName";`<br/>
IEV: 2, `string`<br/>

## Boolean
Represents a true or false state (case insensitive)<br/>
ie: `property/boolean: true;`, `DebuggingEnabled/boolean: false;`<br/>
IEV: 3, `boolean`<br/>

## Integer
Represents a signed 8-bit integer<br/>
ie: `property/int: 25;`, `Directions/int: 3;`<br/>
IEV: 4, `nint`<br/>

## Unsigned Integer
Represents an unsigned 8-bit integer<br/>
ie: `property/uint: 100;`, `Balance/uint: 1230;`<br/>
IEV: 5, `nuint`<br/>

## Float
Represents an 8-bit floating point number<br/>
ie: `property/float: 3.14;`, `Price/float: 3.99;`<br/>
IEV: 6, `nfloat`<br/>

## Bytes
Represents an array of bytes<br/>
ie: `property/bytes: 0x1234;`, `MagicBytes/bytes: 0x01ff;`<br/>
IEV: 7, `bytes`<br/>
