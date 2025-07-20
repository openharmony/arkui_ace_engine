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

enum EventType {
    Click = 0,
    Text = 1,
    ExitApp = 2,
    StartLog = 3,
    StopLog = 4,
    GetLog = 5,
}

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
    _LoadVirtualMachine(vmKind: int32, bootFiles: string, userFiles: string, appLibPath: string): int32
    _StartApplication(appUrl: string, appParams: string, loopIterations: int32): KPointer
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
    _LoadView(className: string, params: string): string
}

function callCallback(id: int32, args: KUint8ArrayPtr, length: int32): int32 {
    console.log(`callCallback: ${id} data is ${length} bytes`)
    if (id == 3) {
        // Improve: implement setTimeout here.
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
        Object.assign(theModule, modules[moduleName]) // Improve: freeze?
    }
    theModule._SetCallbackDispatcher(callCallback)
    return theModule
}

interface TestControl {
    testName: string | undefined
    getLog(): string
    emitTask(type: int32, target: int32, arg1?: int32, arg2?: int32): TestControl
    start(): TestControl
    stop(): TestControl
    nextFrame(): TestControl
    skipFrames(count: int32): TestControl
    loadView(className: string, params: string): TestControl
}

enum TaskType {
    OnChange = 1,
    StartLog = 2,
    StopLog = 3,
    GetLog = 4,
}

class TestControlImpl implements TestControl {
    testName: string | undefined = undefined
    constructor(testName?: string) {
        this.testName = testName
    }
    getLog(): string {
        return nativeModule()._EmitEvent(TaskType.GetLog, -1, 0, 0)
    }
    emitTask(type: int32, target: int32, arg1: int32 = 0, arg2: int32 = 0): TestControl {
        nativeModule()._EmitEvent(type, target, arg1, arg2)
        return this
    }
    start(): TestControl {
        nativeModule()._EmitEvent(TaskType.StartLog, -1, 0, 0)
        return this
    }
    stop(): TestControl {
        nativeModule()._EmitEvent(TaskType.StopLog, -1, 0, 0)
        return this
    }
    nextFrame(): TestControl {
        nativeModule()._RunApplication(0, 0)
        return this
    }
    skipFrames(count: int32): TestControl {
        for (let i = 0; i < count; i++) {
            this.nextFrame()
        }
        return this
    }
    loadView(className: string, params: string): TestControl {
        const result = nativeModule()._LoadView(className, params)
        console.log(`LoadView gave ${result}`)
        return this
    }
}

class AppControl {
    constructor(private app: Application) {
        this.wait()
    }
    private timeStep: number = 500
    private tasks: Array<() => void> = new Array<() => void>()
    private tester = new TestControlImpl()

    testControl(): TestControl {
        return this.tester
    }

    wait(count: int32 = 1): AppControl {
        for (let i = 0; i < count; i++) {
            this.tasks.push(() => {/**empty*/})
        }
        return this
    }

    emitEvent(type: int32, target: int32, x: int32 = 100, y: int32 = 100): AppControl {
        this.tasks.push(() => {
            nativeModule()._EmitEvent(type, target, x, y)
        })
        return this
    }

    start(): AppControl {
        this.tasks.push(() => {
            nativeModule()._EmitEvent(EventType.StartLog, -1, 0, 0)
        })
        return this
    }

    stop(): AppControl {
        this.tasks.push(() => {
            nativeModule()._EmitEvent(EventType.StopLog, -1, 0, 0)
        })
        return this
    }

    async runTasks(): Promise<string> {
        return new Promise<string>((resolve) => {
            let index = 0
            const interval = setInterval(() => {
                if (index == this.tasks.length) {
                    clearInterval(interval)
                    resolve(nativeModule()._EmitEvent(EventType.GetLog, -1, 0, 0))
                    return
                }
                const task = this.tasks[index]
                task()
                index++
            }, this.timeStep)
        })
    }

    click(target: int32, x: int32 = 100, y: int32 = 100): AppControl {
        this.tasks.push(() => {
            nativeModule()._EmitEvent(EventType.Click, target, x, y)
        })
        return this
    }

    exit(): AppControl {
        nativeModule()._EmitEvent(EventType.ExitApp, -1, 0, 0)
        return this
    }
}

class Application {
    rootPointer: KPointer = nullptr
    needVsyncUnblock = false

    constructor(vmKind: int32, bootFiles: string, userFiles: string, nativePath: string, app: string, params: string, loopIterations?: int32) {
        const result = nativeModule()._LoadVirtualMachine(vmKind, bootFiles, userFiles, nativePath)
        if (result == 0) {
            this.rootPointer = nativeModule()._StartApplication(app, params, loopIterations ?? -1)
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
        if (this.needVsyncUnblock) {
            // Ensure that we periodically unlock vsync wait to check for pending promises!
            setInterval(() => {
                nativeModule()._UnblockVsyncWait(pipelineContext)
            }, 64)
        }
        while (!nativeModule()._RunApplication(0, 0)) {
            await nativeModule()._VSyncAwait(pipelineContext)
            if (loopIterations != undefined) {
                loopIterations--
                if (loopIterations === 0) {
                    break
                }
            }
        }
        console.log("EXIT_APP");
        process?.exit(0)
    }
}


let vm = "panda"
let app = "INVALID"
let params = ""

export function loadVM(variant: string, app: string, appParams: string, loopIterations?: number): Promise<AppControl> {
    let bootFiles = __dirname
    let userFiles = ""
    let nativePath = __dirname

    let vmKind = -1

    if (app.startsWith("tests")) {
        app = "class=@arkui.tests.ets.TestHarnessApp.TestHarness"
    }

    switch (variant) {
        case 'java': {
            vmKind = 1
            bootFiles = __dirname + "/../out/java-subset/bin"
            nativePath = __dirname + "/../native"
            break
        }
        case 'panda-ani':
        case 'panda': {
            vmKind = 4
            bootFiles = __dirname + "/bootPandaFiles"
            userFiles = __dirname + "/userPandaFiles"
            break
        }
        case 'panda-ets': {
            vmKind = 2
            break
        }
        case 'kotlin': {
            vmKind = 5
            break
        }
        default:
            throw new Error(`${variant} is not known`)
    }
    return new Application(vmKind, bootFiles, userFiles, nativePath, app, params, loopIterations).start(loopIterations)
}

if (process && process.argv.length > 2) {
    let vmApp = process.argv[2].split(":")
    vm = vmApp[0]
    if (vmApp.length > 1) {
        app = vmApp[1]
    }
    if (process.argv.length > 2) {
        const testName = process.argv[3]
        const isString = isNaN(parseInt(testName))
        if (isString) {
            params = testName ?? ""
        }
    }
}

loadVM(
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
            case "Tests": {
                testChecker(control)
                break;
            }
            default: {
                if (!app.startsWith('tests')) {
                    console.log("Checker is unassigned! app: " + app)
                    setTimeout(() => {
                        // Request app to exit in 10 secs.
                        control.emitEvent(2, 1001, 100, 100)
                    }, 10000)
                }
                break;
            }
        }
    })

async function trivialChecker(control: AppControl) {
    enum Targets {
        Increment = 1007,
        SwapColor1 = 1004,
        SwapColor2 = 1005,
    }
    control
        .start().wait()
        .click(Targets.SwapColor1).wait()
        .click(Targets.SwapColor2).wait()
        .click(Targets.SwapColor1).wait()
        .click(Targets.Increment).wait()
        .click(Targets.Increment).wait()
        .click(Targets.Increment).wait()
        .click(Targets.Increment).wait()
        .stop().wait()

    const expected: string =
        "In Page1 build()\n" +
        "Hi button\n" +
        "#### Swap\n" +
        "In Page1 build()\n" +
        "With blinker\n" +
        "Child1 aboutToAppear()\n" +
        "Bye button\n" +
        "#### Swap\n" +
        "In Page1 build()\n" +
        "Child1 aboutToDisappear()\n" +
        "Hi button\n" +
        "#### Swap\n" +
        "In Page1 build()\n" +
        "With blinker\n" +
        "Child1 aboutToAppear()\n" +
        "Click button\n" +
        "#### Set Button onClick! #2\n" +
        "In Page1 build()\n" +
        "With blinker\n" +
        "Child1 build()\n" +
        "Click button\n" +
        "#### Set Button onClick! #3\n" +
        "In Page1 build()\n" +
        "With blinker\n" +
        "Click button\n" +
        "#### Set Button onClick! #4\n" +
        "In Page1 build()\n" +
        "With blinker\n" +
        "Click button\n" +
        "#### Set Button onClick! #5\n" +
        "In Page1 build()\n" +
        "With blinker\n"

    const actual = await control.runTasks()
    compareResult(actual, expected)
    control.exit()
}

async function routerChecker(control: AppControl) {
    enum Targets {
        IncrementPage3 = 1003,
        IncrementPage2 = 1007,
        GoPage2 = 1004,
        GoBack = 1008,
    }
    control
        .start().wait()
        .click(Targets.IncrementPage3).wait()
        .click(Targets.GoPage2).wait(2)
        .click(Targets.IncrementPage2).wait()
        .click(Targets.GoBack).wait(2)
        .click(Targets.IncrementPage3).wait()
        .stop().wait()

    const expected: string =
        "Page3: clicked 12\n" +
        "Page3: Go clicked\n" +
        "Page3 onPageHide()\n" +
        "Page2 onPageShow()\n" +
        "Page2 aboutToAppear()\n" +
        "In Page2 build()\n" +
        "Page2: back clicked\n" +
        "Page3 onPageShow()\n" +
        "Page2 onPageHide()\n" +
        "Page3: clicked 13\n"

    const actual = await control.runTasks()
    compareResult(actual, expected)
    control.exit()
}

async function navigationChecker(control: AppControl) {
    enum Targets {
        GoBack = 1012,
        GoPage1 = 1005,
        GoPage2 = 1006,
    }
    control
        .start().wait()
        .click(Targets.GoPage1).wait()
        .click(Targets.GoBack).wait()
        .click(Targets.GoPage2).wait()
        .click(Targets.GoBack).wait()
        .stop().wait()

    // Improve: Navigation does not work
    const expected: string =
        "### Button 1005: <DETAIL PAGE> push.\n" +
        "### Button 1006: <SEARCH PAGE> push.\n"

    const actual = await control.runTasks()
    compareResult(actual, expected)
    control.exit()
}

async function testChecker(control: AppControl) {
    console.log(`TESTS with ${control.testControl()}`)
}

function compareResult(actual: string, expected: string) {
    if (actual !== expected) {
        console.log("\nFAIL!\n")
        const linesE = expected.split("\n")
        const linesA = actual.split("\n")
        for (let i = 0; i < Math.max(linesA.length, linesE.length); i++) {
            const a = linesA[i]
            const e = linesE[i]
            const result = a === e ? "OK" : "FAIL"
            console.log(a ?? "?", "|", e ?? "?", "=", result)
        }
        console.log("ACTUAL:\n" + actual)
        throw new Error("actual != expected")
    }
    console.log("\nSUCCESS!")
}