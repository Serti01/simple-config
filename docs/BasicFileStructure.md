# Basic File Structure of a SimepleConfig file
File extention: `.sc`, ie: `main.sc`

## Defining a property and value
`<Property>` is the name of the property
`<Type>` is any of the types defined in `TypesOfProperties.md`
`<Value>` is the value, respecting the `<Type>`
Whitespace and newlines after `:` are optional
`<Property>/<Type>: <Value>;`, ie: `EnableDebugging/bool: true;`, `ProgramName/string: "SimpleTest";`

## Writing a comment
Use `//` to begin a comment, the rest of the line is treated as a comment and won't be parsed.
ie: `property/type: value; // Comment`, in this context, `// Comment` wont be parsed

## Important Notes
Property names do not allow whitespace anywhere in it,
`Hello World/string: "Hello world";` Is NOT allowed
`HelloWorld/string: "Hello, world";` Is allowed

Comments are terminated at a new line

Property names and types are seperated by `/`

Types and values are seperated by `:`

Whole properties are seperated by `;`, not by newlines
