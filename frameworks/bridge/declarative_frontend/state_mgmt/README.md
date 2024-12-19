# ArkUI Declarative State Management

State management TypeScript library for ArkUI declarative front-end.
Supports both older 'full update' for Component to Element classes
and newer 'partial update' for minimal scope NG UINode updates.

Developed at UI Frameworks Team at the Huawei R&D Center Helsinki, Finland.

## Building just state mgmt

The implementation is in Typescript.

Before first build:
`npm install`

For every debug build
`npm run build`

The output is one JS file:
`./dist/stateMgmt.js`

For every release build (default by build system)
`npm run build_release`

The output is one JS file:
`./distRelease/stateMgmt.js`

For profiler build. See StateMgmt Profiler.
`npm run build_profile`

The output is one JS file:
`./distProfile/stateMgmt.js`

The difference between debug build and release build is the removal
of all `stateMgmtConsole.log`/`.debug`/`.info` statements from the
release version JS output code.
NOTE: Output folder is one of following (dist, distRelease or distProfile). In ace_engine build distRelease output is copied to
```bash
./out/rk3568/obj/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/stateMgmt.js
```
## To get all logs
Change selected aceConsole.debug to aceConsole.error. At least from public statig debug. In file state_mgmt_console_trace.ts 
Enable debug: hdc shell param set persist.ace.debug.enabled 1
Build debug version npm run build
Generate .abc from dist/stateMgmt.js and copy to device and reboot.

## File Organising into Directories

- `./src/lib/*.ts` - implementation
    * `./src/lib/sdk/*.ts` - all files that include SDK definitons
    * `./src/lib/common/*.ts` - common files that do not include any SDK functionality
    * `./src/lib/full_update/*.ts` - files specific to the older version of state mgmt for full Component to Element update
    * `./src/lib/partial_update/*.ts` - files specfic to the newer version of state mgmt for NG UINode minimal scope updates
    * `./src/lib/v2/*.ts` - files specfic to V2 implementation
-`./src/index.ts` - implementation 'main' creates singletons.

## How to Develop - StateMgmt
* Change files .ts in src/lib folder
* Do npm install once after repo sync in state_mgmt folder... Then after that 'npm run build_release'
* Output file is in distRelease/stateMgmt.js
* Do script to convers stateMgmt.js to .abc and copy that to device.

```bash
# Make target RK3568 writable
hdc target mount
# Remove old file
hdc shell rm -rf /etc/abc/framework/stateMgmt.abc
# Use es2abc.exe with output parameter --output stateMgmt.abc
# Then copy stateMgmt.abc from build server to local disk and send to /etc/abc/framework
hdc file send stateMgmt.abc /etc/abc/framework
# Reboot device and it will load stateMgmt.abc at start up
hdc shell reboot
```

## StateMgmt Profiling

### Building

Execute follwing commands in framework/bridge/declarative_frontend/state_mgmt.

```bash
npm install
npm run build_profile
Adjust your script to copy stateMgmt.js from distProfile folder.
```

Then compile SW and flash / update .so

#### Initialization for App (DevEco)

By default you can see timing infor from framework. If you want to add something to your App then...
First, initialize an instance of the profiler in your ETS, at the top.
NOTE: The class declarations provided below are needed for DevEco apps

```typescript
// Native class
declare class StateMgmtProfiler {
  constructor(suite: string);
  begin(block: string): void;
  end(): void;
  report(): void;
  clear(): void;
}

// JS global object
declare class stateMgmtProfiler {
  static begin(blockName: string) : void;
  static end() : void;
  static report() : void;
  static clear(): void;
  static init(instance: StateMgmtProfiler) : void;
}

stateMgmtProfiler.init(new StateMgmtProfiler("MyProfiler"));
```

#### Placing blocks in code

In your JS code, wrap the code to be measured between `stateMgmtProfiler.begin("blockNameHere")` and `stateMgmtProfiler.end()`:

```typescript
stateMgmtProfiler.begin("HeavyMethodCall");
myObject.myVeryHeavyMethodCall();
// Nested blocks also work:
{
    stateMgmtProfiler.begin("EvenHeavierMethodCall");
    myObject.evenHeavierMethodCall();
    stateMgmtProfiler.end();
}
stateMgmtProfiler.end();
```

#### Print results

To print the results, you can use this script. You need to replace the package ID with your own and also see the WindowID of your package.
The last command invokes DFX log. The argument `-jsdump` is to invoke JS DFX logging and `-profiler` is the arg to dump profiler results.

```bash
#! /bin/bash
hdc shell param set persist.ace.debug.enabled 0 (needs to be done once)
Start the Test application NOW
hdc shell "hidumper -s WindowManagerService -a '-a'"
Check WinId of your app. Lets say its 11. Put it to -w arg.
hdc shell "hidumper -s WindowManagerService -a '-w 11 -jsdump -profiler'"
```

The output will be like this:
Total include childrens.

```bash
============================================================================================================
Block name                                                                #Calls          Self         Total
============================================================================================================
MyProfiler
 HeavyMethodCall                                                              1        1.465ms       1.465ms
  EvenHeavierMethodCall                                                       1        1.417ms       1.417ms
============================================================================================================
```

- Calling `stateMgmtProfiler.clear()` will clear the results.
- Calling `stateMgmtProfiler.report()` will print the results and then clear them.

## DFX Debug Log

DFX Debug Log is built to work on top of `hidumper`, which is OHOS info dump tool. The DFX Debug Log is used to request information from the process in a shell.

### Commands

- `-jsdump`
    * Requests JS debug logging from the `hidumper` service. It is followed by additional commands and arguments to format the output. See below.

Two output modifiers are defined in order to facilitate the usage of the commands:

- `-viewId`
    * Specifies the view for which information is obtaineed. It acts as an aditional argument to the command providing the view ID in the following format `viewId=##`. where `##` is the numerical ID of the target view.
- `-r`
    * Specifies whether the output of the command should be recursive or not. Non-recursive prints the information for the target view ommiting the same information about it's decendants.

For the purpose of logging the following commands are accepted as input:

- `-dumpAll`
    * Prints all information about the view. This combines the output of all other commands for the specified view. Default print is for root view if no view is specified.
- `-viewHierarchy`
    * Prints the view hierarchy of a particular view, namely the custom component children. Accepts `-viewId` argument and `-r` flag. Depending on the flags provided it can be either recursive, from a specific view downwards, or just the immediate children of the view. Default print is for root view non-recursive if no flags are provided. It also indicates the freeze state of the component if it is configured to be frozen while inactive.
- `-stateVariables`
    * Prints the variables dependencies of the view, and their respective owners and sync peers. Accepts `-viewId` argument. Default print is for root view if no view is specified.
- `-registeredElementIds`
    * Prints a list of components, namely JS classes such as `Column`, `TapGesture` etc. and their ID-s owned by the view. Accepts `-viewId` argument. Default print is for root view if not specified otherwise.
- `-dirtyElementIds`
    * Prints a list of dependent elmtIds that need partial update in next re-render. Accepts `-viewId` argument. Default print is for root view if not specified otherwise.
- `-inactiveComponents`
    * Prints the list of the components that are presently in an inactive or frozen state. These components are not actively processing updates and will stay inactive while in the background.

The application must be running and visible in order to receive commands. The `hidumper` service delivers the commands through the `WindowManagerService`. and the window ID is used to target a specific application.

```bash
#! /bin/bash
hdc shell "param set persist.ace.debug.enabled 0" (needs to be done once)
Start the Test application NOW
hdc shell "hidumper -s WindowManagerService -a '-a'"
Check WinId of your app. Lets say its 11. Put it to -w arg.
hdc shell "hidumper -s WindowManagerService -a '-w 11 -jsdump -dumpAll'"
hdc shell "hidumper -s WindowManagerService -a '-w 11 -jsdump -viewHierarchy'"
hdc shell "hidumper -s WindowManagerService -a '-w 11 -jsdump -viewHierarchy -inactiveComponents'"
```

### Important for Profiler and JSDump
PartialUpdateMode MUST be configured for your application. This can be made for example by changing following.
For API10...\OpenHarmony\Sdk\10\ets\build-tools\ets-loader\main.js and change const partialUpdateConfig = {
  partialUpdateMode: true, // from false

RK3568 /etc/acenewpipe.config must have application name under EANBLED to use newpipeline.
Example content of acenewpipe.config

```bash
ENABLED
com.example.myapplication
```
### Usefull examples

All the following commands concern a hypothetical window with ID 11 and view with ID 42. Note that -viewId is optional.

| Info | Shell command |
|-------|----------|
|Dump all info | `hidumper -s WindowManagerService -a '-w 11 -jsdump -dumpAll -viewId=42'`|
|Dump view hierarchy recursively | `hidumper -s WindowManagerService -a '-w 11 -jsdump -viewHierarchy -viewId=42 -r'`|
|Dump view hierarchy only for the target view | `hidumper -s WindowManagerService -a '-w 11 -jsdump -viewHierarchy -viewId=42'`|
|Dump the list of all registered element ids | `hidumper -s WindowManagerService -a '-w 11 -jsdump -registeredElementIds -viewId=42'`|
|Dump the list of all dirty element ids | `hidumper -s WindowManagerService -a '-w 11 -jsdump -dirtyElementIds -viewId=42'`|

### Example with dependent elements

`hidumper -s WindowManagerService -a '-w 11 -jsdump -dumpAll'`

Showing dependent elements for Link "stringValue".
```
@State/@Provide 'stringValue'[..]
 |--Dependent elements: 'Text[..]'; @Component 'Child1'[..], 'Text[..]'; @Component 'Child2'[..], Text[..]';
```
