# Basic File Structure of a SimepleConfig file
File extention: `.sc`, ie: `main.sc`

## Defining a property and value
`<Property>` is the name of the property<br/>
`<Type>` is any of the types defined in `TypesOfProperties.md`<br/>
`<Value>` is the value, respecting the `<Type>`<br/>
Whitespace and newlines after `:` are optional<br/>
`<Property>/<Type>: <Value>;`, ie: `EnableDebugging/bool: true;`, `ProgramName/string: "SimpleTest";`

## Writing a comment
Use `//` to begin a comment, the rest of the line is treated as a comment and won't be parsed.<br/>
ie: `property/type: value; // Comment`, in this context, `// Comment` wont be parsed

## Important Notes
Property names do not allow whitespace anywhere in it,<br/>
`Hello World/string: "Hello world";` Is NOT allowed<br/>
`HelloWorld/string: "Hello, world";` Is allowed<br/>

Comments are terminated at a new line<br/>

Property names and types are seperated by `/`<br/>

Types and values are seperated by `:`<br/>

Whole properties are seperated by `;`, not by newlines
