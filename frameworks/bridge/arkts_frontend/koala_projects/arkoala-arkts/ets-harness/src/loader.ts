import { int8Array } from "@koalaui/compat"
import { entry } from "./test_entry"

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

export interface LoaderOps {
    _LoadVirtualMachine(vmKind: int32, appClassPath: string, appLibPath: string): int32
    _StartApplication(appUrl: string, appParams: string): KPointer
    _RunApplication(arg0: int32, arg1: int32): boolean
}

export interface NativeControl extends LoaderOps {
    _EmitEvent(type: int32, target: int32, arg0: int32, arg1: int32): string
    _RestartWith(page: string): void
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
    return theModule
}

export enum TaskType {
    OnChange = 1,
    StartLog = 2,
    StopLog = 3,
    GetLog = 4,
}

export class AppControl {
    getLog(): string {
        return nativeModule()._EmitEvent(TaskType.GetLog, -1, 0, 0)
    }
    emitTask(type: int32, target: int32, arg1: int32 = 0, arg2: int32 = 0): AppControl {
        nativeModule()._EmitEvent(type, target, arg1, arg2)
        return this
    }
    start(): AppControl {
        nativeModule()._EmitEvent(TaskType.StartLog, -1, 0, 0)
        return this
    }
    stop(): AppControl {
        nativeModule()._EmitEvent(TaskType.StopLog, -1, 0, 0)
        return this
    }
    nextFrame(): AppControl {
        nativeModule()._RunApplication(0, 0)
        return this
    }
    loadPage(page: string): AppControl {
        nativeModule()._RestartWith(page)
        this.nextFrame()
        this.nextFrame()
        return this
    }
}

let vm = "panda"
let app = "EtsHarness"
let params = "Case1"

export function loadVM(variant: string, app: string, params: string, loopIterations?: number): void {
    let classPath = __dirname
    let nativePath = __dirname

    let vmKind = 2 // panda
    const control = new AppControl()

    const result = nativeModule()._LoadVirtualMachine(vmKind, classPath, nativePath)
    if (result == 0) {
        nativeModule()._StartApplication(app, params);
        control.nextFrame()
    } else {
        throw new Error(`Cannot start VM: ${result}`)
    }
    entry(control)
}

loadVM(vm, app, params, (process && process.argv.length > 4) ? parseInt(process.argv[4]) : undefined)
