# Implementation steps for es2panda plugins

## IDL based bindings generation

* Negotiate and obtain structured IDL within @panda/sdk
   * track IDL shape evolution

* Have a (may be partial) generator of:
    * bridge.cc,
    * Es2PandaNativeModule.ts
    * types.ts
    * enums.ts
    * C API debug printer stubs
    ...

* Have an infrastructure of regeneration into $SIG/arkoala-arkts/libarkts on @panda/sdk updates


## Plugin invocations

* Provide infrastructure to be able to invoke plugins at AFTER PARSER and AFTER CHECKER points
    * Ensure we can go from PARSER to CHECKED
    * Ensure we can go from CHECKED to BIN_GENERATED
    * Ensure the annotations are preserved at the CHECKED phase
    * Ensure we can go to BIN_GENERATED
    * Ensure the abc produced are linkable and working within applications (trivial, shopping etc)

## Compilation pipeline intergration

* Integrate es2panda.ts into compilation pipeline instead of es2panda
    * Teach arktsc script to be able to call es2panda call es2panda.ts interchangengly
    * Ensure the jsdoc to annotations propagate correctly ( /** @memo */ becomes @memo where needed )

* Integrate es2panda.ts as the preprocessor before ets-tsc
   * Ensure it can print out @annotations.
   * Handle ETSGLOBAL transformation, so that it doesn't apply multiple times

* Encapsulate all the preprocessors behind a single facade on the basis of arktsc script
    * The assumed path of transition can be something like
        * ets+memo+es2panda
        * ets+memo+es2panda.ts
        * es2panda.ts+ets+memo+es2panda.ts
        * es2panda.ts

    * Provide controls to switch between configurations

## C API completeness

* Ensure binder interface is complete
    * *there is API for "find declaration" for all the needed kinds of nodes (functions, methods, properties, types, variables etc)
    * "find declaration" consistently works throught imports and exports
* The missing AstNodes are handled by requests
* The missing node methods are handled by requests


## Plugin migration

### tsc partial switch off

* Provide options for partial switch off of parts of memo and ets plugins
* Provide

### Step by step MEMO plugin migration

The memo plugin transition is easier because it is working in es2panda which is already the last in the pipeline

* Provide @memo *call* rewrite in es2panda plugin
    * Enchance the managed API where needed
    * Adapt the relevant pieces of koala-transformer for es2panda
    * Ensure the transformed abc is linkable against the @koalaui/runtime and @memo declarations
    * demo-playground/ works against tsc-compiled runtime/
    * Reconcile jsdoc /** @memo */ vs @memo annotation
    * Ensure the plugin is working in the general compilation pipeline

* Provide the rest of the memo plugin with ad-hoc sequence of steps
   * incremental runtime source code is transformable
   * demo-playground/ works with es2panda transformed runtime
   * test suite test cases work

### Step by step ETS plugin migration

The ets plugin transition is trickier because it is working in the beginnig of the pipeline

* Have a prototype of the small plugin working at the PARSED stage
   * struct to "class extends ArkStructBase"
   * creation of Options interfaces
   * "import { StructBase } from the support library
   * Provide the StructBase version good for pure ArkTS

* Have a prototype of plugin working on CHECKED stage
   * Have ets hello world struct compiled
   * Have it running on host and on devices
   * Provide ets-tsc subsitute in the pipeline

* Advance the plugin to the level of shopping/ application
   * Advance runtime library where needed
   * Move to complete language features use as originally designed

* Advance the plugin to the level of photos/ application

