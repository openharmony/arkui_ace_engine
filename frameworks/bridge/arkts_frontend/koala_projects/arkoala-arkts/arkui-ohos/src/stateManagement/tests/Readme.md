# Unit test framework and test cases for State Management 1.2

## Purpose
The main purpose is to enable fast verification of newly added functionality to state management during active development phase.

Other goals are:
* Make Unit test framework a part of the CI integration to verify that functionality is not broken for new builds.
* Make an installable OpenHarmony application (hap) to run on the device.
* Include to TDD/XTS test suits

## Running in development environment

The biggest advantage is the possibility of running unit test locally from bash linux shell and getting results almost instantly.

There is not need to go through time consuming execution of ./build.sh script to run test cases. Execution of the test cases happens by running make command. Makefile compiles files only from stateManagement folder and below. Classes from incremental engine and Ark runtime have their simplified mocked versions stored in stateManagement/mock folder. That makes unit test pretty independent from the rest of the OpenHarmony code.

Selection of which file to include - real or mocked done to compiling with different configuration files:


for the following import line in the mutableStateMeta.ts
```
import { ArkUIAniModule } from 'arkui.ani';
```
we configured as entry in arktsconfig.json that points to the mocked copy:
```
{
    "compilerOptions": {
        "baseUrl": "./",
        "paths": {
            "arkui.ani": ["./mock/env_mock"],
        }
    }
}
```

## Running tests 
To run the tests developer has to have Panda SDK that includes compiler and runtime libraries installed locally.

Steps to execute the test suite:
```
# Install Panda SDk, to be executed once
npm install

# Compile State Management and test cases and run them
make
```


## File structure
Location in the tree: `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/`

Test files will be sitting in tests folder: `stateManagement/tests`

```
stateManagement/
├── base
├── decoratorImpl
├── interop
├── memorize
├── mock
├── output
├── runtime
├── storage
├── tests
│   ├── lib
│   ├── v1Tov2
│   └── v2Tov1
└── tools
    ├── arkts
    └── ts

```

## Test case example
API developer has to create multiple test cases for different aspects of the API by calling function tcase. Test cases are bundled in the the test suite (call to tsuite function).

The structure of a test case is very straightforward:
- Execute some API functions
- Check results for correctness with test method

Framework will count number of test cases where assertion has failed and report that at the end of test run.


```
    const ttest = tsuite("AppStorageV2 API - simple") {
        tcase("connect, delete different ttypes") {

            // Create new entry in AppStorageV2 with key "ca"
            let valA1 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca", () => { return new ClassA; })
            // Get exiting entry from AppStorageV2 (no create function)
            // for key "ca"
            let valA2 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca")
            // Create new entry in AppStorageV2 with key "ca3"
            let valA3 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca3", () => { return new ClassA; })

            // Check for correctness and report errors
            test("ClassA type: has check", eq(valA1, valA2));
            test("ClassA propA: has check", eq(valA1?.propA, valA2?.propA));
            test("ClassA type: not eq", not_eq(valA1, valA3));

            // Cleanup code
            AppStorageV2.remove("ca");
            AppStorageV2.remove("ca3");

        }
    }

```


