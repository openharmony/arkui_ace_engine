/*
* Copyright (c) 2024 Huawei Device Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

class CallbackRecord {
    constructor(callback, autoDisposable) {
        this.callback = callback
        this.autoDisposable = autoDisposable
    }
}

class CallbackRegistry {
    static INSTANCE = new CallbackRegistry()
    callbacks = new Map()
    id = 1
    constructor() {
        this.callbacks.set(0, new CallbackRecord(
            (args, length) => {
                // console.log(`Callback 0 called with args = ${args} and length = ${length}`)
                throw new Error(`Null callback called`)
            }, false)
        )
    }

    wrap(callback, autoDisposable) {
        const id = this.id++
        this.callbacks.set(id, new CallbackRecord(callback, autoDisposable))
        return id
    }

    call(id, args, length) {
        if (!this.callbacks.has(id)) {
            // console.log(`Callback ${id} is not known`)
            throw new Error(`Disposed or unwrapped callback called (id = ${id})`)
        }
        const record = this.callbacks.get(id)
        if (record.autoDisposable) {
            this.dispose(id)
        }
        return record.callback(args, length)
    }

    dispose(id) {
        this.callbacks.delete(id)
    }
}

function wrapCallback(callback, autoDisposable) {
    if (autoDisposable === void 0) { autoDisposable = true; }
    return CallbackRegistry.INSTANCE.wrap(callback, autoDisposable);
}

function disposeCallback(id) {
    CallbackRegistry.INSTANCE.dispose(id);
}

function callCallback(id, args, length) {
    return CallbackRegistry.INSTANCE.call(id, args, length);
}

let theModule = undefined;
export function nativeModule() {
    if (theModule)
        return theModule;
    let modules = LOAD_NATIVE
    if (!modules)
        throw new Error("Cannot load native module");
    theModule = {}
    for (let module of Object.keys(modules)) {
        Object.assign(theModule, modules[module])
    }
    theModule._SetCallbackDispatcher(callCallback);
    return theModule;
}
var rootPointer;
function getNativePipelineContext() {
    var root = rootPointer;
    return nativeModule()._GetPipelineContext(root);
}
export async function runEventLoop() {
    var pipelineContext = getNativePipelineContext()
    nativeModule()._SetVsyncCallback(pipelineContext)

    while (!nativeModule()._RunApplication(0, 0)) {
        await nativeModule()._VSyncAwait(pipelineContext)
    }
    console.log("EXIT_APP");
    process?.exit(0)
}
export function checkLoader(variant, appName) {
    let vm = -1;
    let classPath = `/data/storage/el1/bundle/libs/__ARCH__`;
    let nativePath = classPath;
    switch (variant) {
        case 'panda': {
            vm = 4;
            break;
        }
    }
    let result = nativeModule()._LoadVirtualMachine(vm, classPath, nativePath);
    if (result == 0) {
        rootPointer = nativeModule()._StartApplication(appName, "ArkTSLoaderParam");
        if (rootPointer != 0) {
            setTimeout(async () => runEventLoop(), 0);
        }
        else {
            console.log("checkLoader: rootPointer is nullptr")
        }
    }
    else {
        throw new Error("Cannot start VM: " + result);
    }
    return result;
}
