# C API design style

## Why?

C API to libace provides stable and high performance interface to ACE engine for wide
variety of programming languages and frameworks. This API must have the following properties:

   * Long term compatibility
   * High performance
   * Reliable wrt binary layout changes
   * Usable in other complex projects
   * Usable from pure C

## API shape

 We provide strictly versioned collection of C API in the following manner:
 ```c
struct ArkUIAnyAPI {
    ArkUI_Int32 version;
};

struct ArkUIAPI1 {
    int version;
    void (*op1)(int arg1);
};


struct ArkUIAPI2 {
    int version;
    int (*op2)(int arg1, int arg2);
}

// Entry point
extern "C" DLL_EXPORT const ArkUIAnyAPI *GetArkUIAPI(int kind, int version);

// Find API 1, version 5.
ArkUIAPI1* api1 = GetArkUIAPI(1, 5);
if (api1) api1->op1(16);

// Find API 1, version 3.
ArkUIAPI2* api2 = GetArkUIAPI(2, 3);
if (api2) api2->op2(1, 2);
```
This way, we can expose several API families via single entry point and keep
backward compatibility by providing multiple implementation versions to ensure
backward compatibility.

## API design guidelines

Following practices are advised to ensure maximum level of compatibility, performance
and usability. Here we discuss only public interface exposed by our library, and not
discuss implementation's source code policies, that controled by respective coding style
guidelines.

### Source code organization

   * All publicly visible definitions and interfaces must be listed in single file,
*arkoala_api.h*
   * This file must not include any other files and be fully self-contained
   * The file must be written in pure C, so that it's usable from both C and C++ code
   * No macro-definitions other that numeric constants or conditional compilation constructions allowed
   * Only enums, struct, typedef and union definitions are allowed
   * Nothing else, including function forward declaration or constants allowed

### Types

   * All types going via interfaces must be declared in *arkoala_api.h*
   * Using of compound structures is not recommended, and to be avoided
   * Following primitive types are defined:
        * `ArkUI_Bool` - boolean
        * `ArkUI_Int8` - signed integers
        * `ArkUI_Int16`
        * `ArkUI_Int32`
        * `ArkUI_Int64`
        * `ArkUI_Uint8` - unsigned integers
        * `ArkUI_Uint16`
        * `ArkUI_Uint32`
        * `ArkUI_Uint64`
        * `ArkUI_Float32` - IEEE floating point types
        * `ArkUI_Float64`
        * `ArkUI_CharPtr` - null-terminated UTF-8 string
   * Arrays of primitive types (implemented as primitive type pointer and its size) could be used
   * Bit-fields are disallowed
   * Constructions like `ArkUI_Int32[]` must be avoided, `ArkUI_Int32*` must be used instead
   * To define type of distinct opaque handle following pattern to be used
     ```c
     struct _ArkUIMyType; // forward declaration
     typedef _ArkUIMyType* ArkUIMyTypeHandle; // pointer to an opaque structure
     ```
     Functions returning and receiving such handles must do so consistently
   * Every function can accept primitive types
   * structs can be one of three types:
      * Data struct: used to pass/return values in API. Data struct can have fields of
        primitive types, arrays and structs of other allowed types.
        No other types (including function pointers) allowed.
      * API struct: must contain int version as the first field, and list of
       function pointer fields afterwards. No other field types allowed. `GetArkUIAPI()`
       returns pointer to such struct.
      * Interface struct: must have list of function fields, no other fields allowed.
        Usually used to group related APIs.
    * Functions can only accept primitive types and their arrays, data struct pointers, enums or unions.
    * Functions in API and interface structs can also return API and interface structs pointers
    * Avoid using function pointers, instead use integral values to refer callbacks in
    VM friendly manner (see `ArkUIAPICallbackMethod`)

### Naming

   * Structs, enums and unions must start their names with `ArkUI` prefix, to ensure no naming conflict with other software exists
   * Struct, union and enums names must be like `ArkUIMyStruct`, i.e. prefix and then Pascal-case name
   * Enum elements must be named like FOO_BAR, i.e. upper case snake-case
   * Functions pointers must be named in camel case, like `void (*myFunctionName)()`

### API style

   * Primitive type arguments with clear meaning must be preferred
   * `ArkUI_Float32` is strongly recommended FP type, `ArkUI_Int32` is recommended integral type
   * Minimal and stable surface control API is preferred, i.e. in case of complex component instead of
```c
   struct ArkUIMyComponentModifier {
    void (*setKnob1)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetKnob1)(ArkUINodeHandle node);
    void (*setKnob2)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetKnob2)(ArkUINodeHandle node);
```
    better use something like
```c
   struct ArkUIMyComponentModifier {
    void (*controlKnob)(ArkUINodeHandle node,
        ArkUIMyComponentOperations operation,
        ArkUI_Int32 knobNumber,
        ArkUI_Int32* intValues, ArkUI_Int32 intValuesSize,
        ArkUI_Float32* floatValues, ArkUI_Int32 floatValuesSize);
   };
```
   * Design API in VM friendly way, i.e allow mechanism where pinned buffers from VM, such as JS ArrayBuffer can be used directly as C API call argument

### Callbacks

   * Callbacks are expected to be executed only during C API call (via `ArkUIAPICallbackMethod` operations)
   * Asynchronous callbacks (callbacks that executed sometimes later)
    are strongly not recommended. For cases where it is not avoidable, one must to ensure
    that code is ready to function is suchcallback is called from another thread
   * For asynchronous operations events mechanism must be used (async request is put
    into the queue and latter requested by API user via `checkEvent()` call)

### Memory management

   * Try to design API to avoid unneeded memory management
   * Use const pointers to pass values and regular pointers for in-out and out parameters
   * TODO: strings return mechanism (arena-based)
   * Avoid APIs that requires explicit release call, instead assume construction that
   resources associated with tree node and released once tree node gone (with `disposeNode`)

### Concurrency

   * Most APIs must be callable from any thread, but we assume that no concurrent
   access to the same UI tree happens
   * For arguments we assume that all data being passed and returned is only valid
   during single call

### Performance techniques

   * Avoid unneeded copies and data shuffling, especially for the large data
   * Avoid code which requires API user to create unknown-sized buffers on caller side,
     prefer fixed/limited size arrays

### Backward compatibility

   * When making changes affecting binary layout (that is, changing structures, adding/removing/modifying functions) always increase API version for affected APIs
   * When backward compatibility must be kept - consider strategy of keeping old implementation and providing it on implementation side (i.e. loading old library and chaining to it)
   * Be reasonable about design of your APIs, think ahead and avoid overly specific operations, think the way that you have to support this API for several years