# Incremental runtime demo playground

This is a demo playground that allows to play with Koala 
incremental runtime and memo functions

## Prerequisites

Make sure to follow GETTING_STARTED.md and DEVELOPMENT.md
to set up your environment.

Then go to the playground and run the example.

```
cd demo-playgorund
npm run run
```

It will compile the example, print the rewritten code to console and run example.

Have fun: tweak the example and see how the tree is rebuilt incrementally!


## Things to look at

The demo source file in

    demo-playground/src/index.ts

The koala-transformer compiler plugin managing @memo annotaions is applied in

    demo-playground/tsconfig.json

Note the "trace":true plugin argument -- it instructs the plugin to emit the result of AST transformation to console.


