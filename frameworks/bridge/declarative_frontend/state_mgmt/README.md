# ArkUI Declarative State Management

State management TypeScript library for ArkUI declarative front-end.
Supports both older 'full update' for Component to Element classes
and newer 'partial update' for minimal scope NG UINode updates.

Developed at UI Frameworks Team at the Huawei R&D Center Helsinki, Finland.

## Building just state mgmt

The implementation is in Typescript.
TS sources are built into a single JS file using `tsc`.
`tsc` must be in shell's PATH.

Before first build:
`npm install`

For every debug build
`npm run build`

The output is one JS file:
`./dist/stateMgmt.js`

For every release build
`npm run build_release`

The output is one JS file:
`./distRelease/stateMgmt.js`

The difference between debug build and release build is the removal 
of all `stateMgmtConsole.log`/`.debug`/`.info` statements from the 
release version JS output code.

## Unit tests for state mgmt using node.js / npm

Unit tests run with Node.js on Ubuntu shell independent of the native ArkUI framework.

Before first run:
`npm install`

To compile the entire project and unit tests, and to run all tests
`npm test`

The output is one JS file:
`./distTest/stateMgmt_test.js`

The results are written to console.
Successful run ends with the message `Passed all XX cases, YYY test asertions.`.

## File Organising into Directories

- `./src/lib/*.ts` - implementation
    * `./src/lib/sdk/*.ts` - all files that include SDK definitons
    * `./src/lib/common/*.ts` - common files that do not include any SDK functionality
    * `./src/lib/full_update/*.ts` - files specific to the older version of state mgmt for full Component to Element update
    * `./src/lin/partial_update/*.ts` - files specfic to the newer version of state mgmt for NG UINode minimal scope updates
-`./src/index.ts` - implementation 'main' creates singletons.
-`./test/utest/*` - unit tests
