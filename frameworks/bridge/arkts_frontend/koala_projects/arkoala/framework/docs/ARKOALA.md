## ARKOALA development guide

### Ideas

Arkoala as a project is about controlling native UI nodes
with an incremental runtime, and allow pluggable architecture
for the UI being controlled.

### FrameNode API

See file `api.h` for possible API shape between native
nodes implementation and higher level C++ API. Arkoala's NAPI
module looks up symbol `getArkUINodeAPI()` with
`dlsym()`/`GetProcAddress()` and uses that for all entry points
to the frame management API.
Basic implementation of tree manipulation APIS provided in
`dummy_impl.cc`.

### Managed side

For a simple example of general nodes control take a look
on `startArkoalaApplication()` and `startArkoalaApplication2()`
functions, showing manual state update propagation and possible
example of real event loop.

For example with actual implementation of ArkUI components
take a look at an example transforming .ets call like

```swift
struct Comp {
    @State
    realWidth: number = 100
    Column() {
        Button("Hi")
    }
    .width(realWidth)
```
to calls to
```typescript
class ArkComp() {
    realWidth = mutableState(100)
    build() {
        Column((instance) => instance.width(realWidth.value), () => {
            Button((instance) => {}, "Hi")
        })
    }
}
```
and provides implementation for basic `ArkCommon`, `ArkButton`.

### Hands on

Make sure Meson build system and C++ compiler for
your platform is installed.

Do once to configure
```bash
npm install
npm -C arkoala run configure:native-node-host
npm run
```

Then to do rebuild and run test just do
```bash
npm run arkoala:loader:test
```
