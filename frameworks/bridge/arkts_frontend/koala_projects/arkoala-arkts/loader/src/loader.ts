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

type int32 = number
type int64 = number
type float32 = number

export type KStringPtr = string
export type KStringArrayPtr = Uint8Array
export type KInt32ArrayPtr =  Int32Array
export type KFloat32ArrayPtr = Float32Array
export type KUint8ArrayPtr = Uint8Array
export type KInt = int32
export type KUInt = int32
export type KLong = int64
export type KFloat = float32
export type KBoolean = int32
export type KPointer = bigint
export type pointer = KPointer
export type KNativePointer = KPointer

const nullptr = BigInt(0)

export interface LoaderOps {
    _LoadVirtualMachine(vmKind: int32, appClassPath: string, appLibPath: string): int32
    _StartApplication(appUrl: string, appParams: string): KPointer
    _RunApplication(arg0: int32, arg1: int32): boolean
    _SetCallbackDispatcher(dispather: Object): void
    _CallCallbackSync(kind: int32, data: Uint8Array, length: int32): void
}

export interface NativeControl extends LoaderOps {
    _GetPipelineContext(root: KPointer): KPointer
    _SetVsyncCallback(pipeline: KPointer): void
    _VSyncAwait(pipeline: KPointer): Promise<void>
    _UnblockVsyncWait(pipeline: KPointer): void
    _EmitEvent(type: int32, target: int32, arg0: int32, arg1: int32): string
}

function callCallback(id: int32, args: KUint8ArrayPtr, length: int32): int32 {
    console.log(`callCallback: ${id} data is ${length} bytes`)
    if (id == 3) {
        // TODO: implement setTimeout here.
    }
    return 0
}

let theModule: NativeControl | undefined = undefined

declare const LOAD_NATIVE: object

export function nativeModule(): NativeControl {
    if (theModule) return theModule
    theModule = new Object() as NativeControl
    const modules = LOAD_NATIVE as any
    if (!modules)
        throw new Error("Cannot load native module")
    for (const moduleName of Object.keys(modules)) {
        Object.assign(theModule, modules[moduleName]) // TODO freeze?
    }
    theModule._SetCallbackDispatcher(callCallback)
    return theModule
}

class AppControl {
    constructor(private app: Application) {}

    emitEvent(type: int32, target: int32, x: int32, y: int32): void {
        nativeModule()._EmitEvent(type, target, x, y)
    }
}

class Application {
    rootPointer: KPointer  = nullptr

    constructor(vmKind: int32, classPath: string, nativePath: string, app: string, params: string) {
        const result = nativeModule()._LoadVirtualMachine(vmKind, classPath, nativePath)
        if (result == 0) {
            this.rootPointer = nativeModule()._StartApplication(app, params);
        } else {
            throw new Error(`Cannot start VM: ${result}`)
        }
    }

    start(loopIterations?: int32): Promise<AppControl> {
        return new Promise((resolve, reject) =>
            setTimeout(async () => this.runEventLoop(resolve, loopIterations), 0)
        )
    }

    getNativePipelineContext(): KPointer {
        return nativeModule()._GetPipelineContext(this.rootPointer)
    }

    async runEventLoop(resolve: (control: AppControl) => void, loopIterations: number | undefined) {
        const pipelineContext = this.getNativePipelineContext()
        nativeModule()._SetVsyncCallback(pipelineContext)
        resolve(new AppControl(this))
        while (!nativeModule()._RunApplication(0, 0)) {
            await nativeModule()._VSyncAwait(pipelineContext)
            if (loopIterations != undefined) {
                loopIterations--
                if (loopIterations === 0) {
                    process?.exit(0)
                }
            }
        }
        console.log("EXIT_APP");
        process?.exit(0)
    }
}

export function checkLoader(variant: string, app: string, params: string, loopIterations?: number): Promise<AppControl> {
    let classPath = __dirname
    let nativePath = __dirname

    let vmKind = -1

    switch (variant) {
        case 'java': {
            vmKind = 1
            classPath = __dirname + "/../out/java-subset/bin"
            nativePath = __dirname + "/../native"
            break
        }
        case 'panda-ani':
        case 'panda': {
            vmKind = 4
            break
        }
        case 'panda-ets': {
            vmKind = 2
            break
        }
        default:
            throw new Error(`${variant} is not known`)
    }

    return new Application(vmKind, classPath, nativePath, app, params).start(loopIterations)
}

let vm = "panda"
let app = "UserApp"
let params = "ArkTSLoaderParam"

if (process && process.argv.length > 2) {
    let vmApp = process.argv[2].split(":")
    vm = vmApp[0]
    if (vmApp.length > 1)
        app = vmApp[1]
    if (vmApp.length > 2) {
        const isString = isNaN(parseInt(vmApp[2]))
        if (isString) {
            params = vmApp[2]
        }
    }
}

checkLoader(
    vm, app, params,
    (process && process.argv.length > 3) ? parseInt(process.argv[3]) : undefined)
    .then(control => {
        console.log(`Started ${app}...`)
        switch (app) {
            case "ComExampleTrivialApplication": {
                trivialChecker(control)
                break
            }
            case "ComExampleNavigationApplication": {
                navigationChecker(control)
                break
            }
            case "ComExampleRoutingApplication": {
                routerChecker(control)
                break;
            }
            default: {
                console.log("Checker is unassigned! app: " + app)
                setTimeout(() => {
                    // Request app to exit in 10 secs.
                    control.emitEvent(2, 1001, 100, 100)
                }, 10000)
                break;
            }
        }
    })

function navigationChecker(control: AppControl) {
    const stepStack = [
        "Wait",
        "GoBack",
        "Wait",
        "GoPage2",
        "Wait",
        "GoBack",
        "Wait",
        "GoPage1",
    ]
    let componentId = 1001
    const interval = setInterval(() => {
        const kind = stepStack.pop()
        switch (kind) {
            case "Exit": {
                componentId = 1001
                control.emitEvent(2, componentId, 100, 100)
                clearInterval(interval)
                break;
            }
            case "GoBack": {
                componentId = 1012
                control.emitEvent(0, componentId, 100, 100)
                break;
            }
            case "GoPage1": {
                componentId = 1005
                control.emitEvent(0, componentId, 100, 100)
                break;
            }
            case "GoPage2": {
                componentId = 1006
                control.emitEvent(0, componentId, 100, 100)
                break;
            }
            default:
                // wait
                break;
        }
    }, 1000)
}

function routerChecker(control: AppControl) {
    const steps = [
        "ClickPage3",
        "Wait",
        "GoPage2",
        "Wait",
        "Wait",
        "ClickPage2",
        "Wait",
        "GoBack",
        "Wait",
        "ClickPage3",
        "Wait",
        "Exit"
    ]
    let currentStep = 0
    let button1Page3Id = 1003
    let button2Page3Id = 1004
    let button1Page2Id = 1007
    let button2Page2Id = 1008

    const interval = setInterval(() => {
        const kind = steps[currentStep++]
        switch (kind) {
            case "Exit": {
                control.emitEvent(2, 1000, 100, 100)
                clearInterval(interval)
                break;
            }
            case "GoBack": {
                control.emitEvent(0, button2Page2Id, 100, 100)
                break;
            }
            case "ClickPage3": {
                control.emitEvent(0, button1Page3Id, 100, 100)
                break;
            }
            case "ClickPage2": {
                control.emitEvent(0, button1Page2Id, 100, 100)
                break;
            }
            case "GoPage2": {
                control.emitEvent(0, button2Page3Id, 100, 100)
                break;
            }
            case "Wait": break
            default:
                throw new Error(`Unknown command: ${kind}`)
        }
    }, 1000)
}

function trivialChecker(control: AppControl) {
    const stepStack = [
        "Exit",
        "Wait",
        "IncrementClicks",
        "IncrementClicks",
        "IncrementClicks",
        "IncrementClicks",
        "Wait",
        "SwapColor1",
        "Wait",
        "SwapColor2",
        "Wait",
        "SwapColor1",
    ]
    let componentId = 1001
    const interval = setInterval(() => {
        const kind = stepStack.pop()
        switch (kind) {
            case "Exit": {
                componentId = 1001
                control.emitEvent(2, componentId, 100, 100)
                clearInterval(interval)
                break;
            }
            case "IncrementClicks": {
                componentId = 1005
                control.emitEvent(0, componentId, 100, 100)
                break;
            }
            case "SwapColor1": {
                componentId = 1003
                control.emitEvent(0, componentId, 100, 100)
                break;
            }
            case "SwapColor2": {
                componentId = 1004
                control.emitEvent(0, componentId, 100, 100)
                break;
            }
            default:
                // wait
                break;
        }
    }, 1000)
}