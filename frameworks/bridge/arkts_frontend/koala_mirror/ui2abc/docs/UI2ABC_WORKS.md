At least the following implementation steps are needed

## General plugin API infrastructure

### Large bodies of code

We need to ensure we can pass through at least:
   * incremental/runtime (v)
   * arkoala-arkts/arkui/src/* -- the handwritten part of arkoala (v)
   * arkoala-arkts/arkui-common/src/* -- the handwritten part of arkoala ( )
   * arkoala-arkts/arkui/src/generated/* -- the generated component classes  (v)
   * arkoala-arkts/arkui/src/sts/*  -- the generated facades ( )

### Perfomance and memory approaches

   * keep node overproduction under control
      * declaration cache (PR)
      * update logics
   * have fast-arktsc working with all three plugins (v)
   * Compile against the d.ts surface of arkoala

### The three plugin stack is capable of running in multi-file, multi-import scenario

   * In parallel work with the compiler people to ensure the proper scheme with "recheck" is moving (in progress: "rebind" + "recheck" works in small amount of cases, inserting imports in bound/checked stage plugin is non trivial)
   * work on ui2abc and fast-arktsc tools to hide implementation details from users (v)
   * The plugin configuration is per-module (v)

## Memo plugin works

   * Ensure we can compile incremental runtime (as a large body of memo code) with and after memo rewrite (v)
   * Ensure we can compile arkoala  (in progress)
   * Ensure the incremental runtime harness can run tests for ui2abc (v)
   * Ensure we can run test on incremental runtime compiled by ui2abc ( )
   * Have the diagnostics issued where needed. ( )
        * First to console ( )
        * Then, after compiler issue is implemented thtrough the C API ( )
   * Functional completeness ( )

## UI plugin works

   * Ensure the ets-harness is capable of running tests for ui2abc ( )
   * Transfer ets-plugin functionality to ui-plugin, covering by executable tests in parallel in ets-harness ( )
      * directed by user

## IDLize works

### arkgen

   * Gnereare proper ETS facades with proper interfaces in proper packages ( )
   * Have the generator emit d.ts surfaces of arkoala layers
   * Adapt enums, non-component interfaces, etc to be properly named and not expose users unneeded implementation details ( )
      * This is an iterative work in small steps ensuring runnability on every step.

### arktsgen

   * keep maintaining the plugin author needs (v)
   * keep following the @panda/sdk release cycle  (v)
   * work with DevOps to ensure the regular builds are really going (v)

## User code and intergration work

   * Transition from the small demo working on prototype arkui.ts to correctly work through arkoala implementations ( )
   * Bring the user app to the desired shape
        * This is an iterative work in small steps ensuring runnability on every step. (x)
   * trivial can startup on the host
   * trivial can run on a device/previewer
   * trvial is running fine
   * shopping can startup
   * shopping is running fine

