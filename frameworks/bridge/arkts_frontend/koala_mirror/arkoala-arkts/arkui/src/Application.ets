/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { memo } from "@koalaui/runtime/annotations"
import { ComputableState, IncrementalNode, GlobalStateManager, StateManager, StateContext, memoEntry, MutableState, createAnimationTimer, callScheduledCallbacks } from "@koalaui/runtime"
import { int32, int64, scheduleCoroutine } from "@koalaui/common"
import { DeserializerBase, pointer, nullptr, KPointer, InteropNativeModule, registerNativeModuleLibraryName, KSerializerBuffer, wrapSystemCallback } from "@koalaui/interop"
import { PeerNode } from "./PeerNode"
import { ArkUINativeModule } from "#components"
import { EventEmulator } from "./generated"
import { UserView, UserApplicationControl } from "./UserView"
import { ClickEvent, ClickEventInternal } from "./generated"
import { checkEvents, setCustomEventsChecker } from "./Events"
import { checkArkoalaCallbacks } from "./CallbacksChecker"
import { setUIDetachedRootCreator } from "./CallbackTransformer"
import { enterForeignContext, leaveForeignContext } from "./handwritten"
import { Routed, TestComponentPeer } from "./handwritten"
import { AppStorage } from "./Storage"
import { deserializeAndCallCallback } from "./generated/peers/CallbackDeserializeCall"
import { NativeLog } from "./NativeLog"
import { taskpool } from "escompat"

setCustomEventsChecker(checkArkoalaCallbacks)

enum EventType {
    Click = 0,
    Text = 1,
    ExitApp = 2,
    StartLog = 3,
    StopLog = 4,
    GetLog = 5,
    SyncNeeded = 6,
}

class PartialUpdateRecord {
    public update: () => void
    public context: Object
    public callback: (before: boolean) => void

    constructor(update: () => void, context: Object, callback: (before: boolean) => void) {
        this.callback = callback
        this.context = context
        this.update = update
    }
}

let partialUpdates = new Array<PartialUpdateRecord>()
let _currentPartialUpdateContext: Object | undefined = undefined

/**
 * Provide partial update lambda and context.
 *
 * @param update - function that performs state update
 * @param context - context available to UI code when state update effect happens
 */
export function addPartialUpdate<T>(update: () => void, context: T, callback: (before: boolean) => void): void {
    partialUpdates.push(new PartialUpdateRecord(update, context as Object, callback))
}

/**
 * Current partial update context or undefined.
 *
 * @returns current partial update context
 */
export function currentPartialUpdateContext<T>(): T | undefined {
    return _currentPartialUpdateContext as (T | undefined)
}

// Improve: move to Application class.
let detachedRoots: Map<KPointer, ComputableState<PeerNode>> = new Map<KPointer, ComputableState<PeerNode>>()


export function createUiDetachedRoot(
    peerFactory: () => PeerNode,
    @memo
    builder: () => void // Improve: UserViewBuilder
): PeerNode {
    const manager = GlobalStateManager.instance
    const node = manager.updatableNode<PeerNode>(peerFactory(), (context: StateContext) => {
        const frozen = manager.frozen
        manager.frozen = true
        memoEntry<void>(context, 0, builder)
        manager.frozen = frozen
    })
    detachedRoots.set(node.value.peer.ptr, node)
    return node.value
}
setUIDetachedRootCreator(createUiDetachedRoot)

export function destroyUiDetachedRoot(node: PeerNode): void {
    if (!detachedRoots.has(node.peer.ptr))
        throw new Error(`Root with id ${node.peer.ptr} is not registered`)
    const root = detachedRoots.get(node.peer.ptr)!
    detachedRoots.delete(node.peer.ptr)
    root.dispose()
}

function dumpTree(node: IncrementalNode, indent: int32 = 0) {
    const indentToString = (indent: number) => {
        let str = ""
        for (let i = 0; i <= indent; i++) str += " "
        return str
    }

    if (indent == 0) InteropNativeModule._NativeLog("> Dump tree:")

    let child = node.firstChild
    InteropNativeModule._NativeLog("> " + indentToString(indent++) + "| " + node)

    while (child) {
        dumpTree(child!, indent + 1)
        child = child!.nextSibling
    }
}

function errorInfo(crash: Object): string {
    let msg = crash.toString() + "\n"
    if (Object.hasOwn(crash, "stack")) msg += (crash as Error).stack
    return msg
}

function registerSyncCallbackProcessor() {
    wrapSystemCallback(1, (buffer: KSerializerBuffer, length: int32) => {
        deserializeAndCallCallback(new DeserializerBase(buffer, length))
        return 0
    })
}

class UserEmulatedEvent {
    type: int32
    target: int32
    arg1?: int32
    arg2?: int32
    constructor(type: int32, target: int32, arg1?: int32, arg2?: int32) {
        this.type = type
        this.target = target
        this.arg1 = arg1
        this.arg2 = arg2
    }
}

class ReloadEmulatedEvent {
}

type EmulatedEvent = UserEmulatedEvent | ReloadEmulatedEvent

export const TEST_LOG_NUMBER = 4

class UserLinker {
    private readonly linker: AbcRuntimeLinker = new AbcRuntimeLinker(undefined, [])
    private readonly pathSet: Set<string> = new Set<string>
    constructor() { }
    public addAbcFile(file: string): void {
        if (this.pathSet.has(file))
            return

        console.log('UserLinker: adding abc file:' + file);
        this.pathSet.add(file)
        this.linker.addAbcFiles([file])
    }

    public addAbcFiles(fileList: string): void {
        fileList.split(':').forEach((file: string) => {
            this.addAbcFile(file);
        });
    }

    public createUserObject(className: string): Object {
        if (className.startsWith("class=")) {
            className = className.substring(6);
        }

        console.log('UserLinker: trying load class:' + className);

        const cls = this.linker.loadClass(className, true)
        return cls.createInstance()
    }
}

function eventHandlerTask(app: Application) {
    app.eventHandlerTask()
}

export class Application implements UserApplicationControl {
    private manager: StateManager | undefined = undefined
    private rootState: ComputableState<PeerNode> | undefined = undefined
    private timer: MutableState<int64> | undefined = undefined
    private currentCrash: Object | undefined = undefined
    private enableDumpTree = false
    private exitApp: boolean = false
    private userView: UserView | undefined = undefined

    private withLog = false
    private useNativeLog = true
    private emulatedEvents = new Array<EmulatedEvent>()
    private rootPointer: KPointer = nullptr
    public static linker: UserLinker = new UserLinker()
    private _params: string = ""
    get params(): string {
        return this._params
    }

    constructor(userView: UserView, params: string, useNativeLog: boolean) {
        this.userView = userView
        this.useNativeLog = useNativeLog
        this._params = params
    }

    private unblockVsync() {
        if (this.rootPointer != nullptr) {
            ArkUINativeModule._UnblockVsyncWait(this.rootPointer)
        }
    }

    private unblockCallbackWait() {
        if (this.rootPointer != nullptr) {
            InteropNativeModule._UnblockCallbackWait(this.rootPointer)
        }
    }

    eventHandlerTask() {
        console.log(`Using || UI`)
        while (!this.exitApp) {
            callScheduledCallbacks()
            this.checkAppEvents()
            this.unblockVsync()
            await (InteropNativeModule._CallbackAwait(this.rootPointer) as Promise<void>)
        }
    }

    ///////////////
    /**
     * These 6 APIs can be called by user from any coroutine.
     */
    startLog(): UserApplicationControl {
        NativeLog.Default.startNativeLog(TEST_LOG_NUMBER)
        return this
    }
    getLog(): string {
        return NativeLog.Default.getNativeLog(TEST_LOG_NUMBER)
    }
    stopLog(): UserApplicationControl {
        NativeLog.Default.stopNativeLog(TEST_LOG_NUMBER)
        return this
    }
    requestStopApp(): void {
        this.exitApp = true
        this.unblockVsync()
        this.unblockCallbackWait()
    }
    emitTask(type: int32, target: int32, arg1?: int32, arg2?: int32): UserApplicationControl {
        // Improve: protect emulatedEvents by lock
        this.emulatedEvents.push(new UserEmulatedEvent(type, target, arg1, arg2))
        this.unblockCallbackWait()
        return this
    }
    private vsyncWaiters = new Array<(value: UserApplicationControl) => void>()
    nextFrame(): Promise<UserApplicationControl> {
        this.unblockVsync()
        return new Promise<UserApplicationControl>((resolve, reject) => {
            // Improve: protect vsyncWaiters by lock
            this.vsyncWaiters.push(resolve)
        })
    }
    reloadView(): UserApplicationControl {
        // Improve: protect emulatedEvents by lock
        this.emulatedEvents.push(new ReloadEmulatedEvent())
        this.unblockCallbackWait()
        return this
    }
    /////////////

    static createMemoRootState(manager: StateManager,
        @memo
        builder: () => void, // Improve: UserViewBuilder
        withRouter: boolean = true
    ): ComputableState<PeerNode> {
        const peer = PeerNode.generateRootPeer()
        return manager.updatableNode<PeerNode>(peer, (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            memoEntry<void>(context, 0, () => { Routed(builder) })
            manager.frozen = frozen
        })
    }

    private computeRoot(): PeerNode {
        // let handle = ArkUINativeModule._SystemAPI_StartFrame()
        let result: PeerNode
        try {
            result = this.rootState!.value
            this.rootPointer = result.peer.ptr
        } finally {
            // ArkUINativeModule._SystemAPI_EndFrame(handle)
        }
        return result
    }

    start(foreignContext: pointer, loopIterations: int32): pointer {
        enterForeignContext(foreignContext)
        if (this.withLog) NativeLog.Default.startNativeLog(1)
        let root: PeerNode | undefined = undefined
        try {
            this.manager = GlobalStateManager.instance
            this.timer = createAnimationTimer(this.manager!)
            @memo
            let builder = this.userView!.getBuilder()
            this.rootState = Application.createMemoRootState(this.manager!, builder)
            root = this.computeRoot()
        } catch (e) {
            InteropNativeModule._NativeLog(`Application.start() error: ${e?.toString()}`)
            if (e instanceof Error) {
                const stack = e.stack
                if (stack) {
                    InteropNativeModule._NativeLog("Application.start() stack trace: " + stack)
                }
                leaveForeignContext()
                return nullptr
            }
        }
        if (this.withLog) {
            NativeLog.Default.stopNativeLog(1)
            if (this.useNativeLog) {
                InteropNativeModule._PrintGroupedLog(1)
            } else {
                let log = NativeLog.Default.getNativeLog(1)
                if (log.length > 0) {
                    InteropNativeModule._NativeLog(log)
                }
            }
        }

        leaveForeignContext()

        if (this.useOwnLoop) {
            this.runEventLoop(loopIterations)
        }
        return root!.peer.ptr
    }

    private processEmulatedEvent() {
        let event = this.emulatedEvents.shift()!

        if (event instanceof ReloadEmulatedEvent) {
            if (this.manager === undefined) {
                console.log("Manager is not inited")
            }
            AppStorage.clear()
            this.manager!.reset()
            this.rootState = Application.createMemoRootState(this.manager!, this.userView!.getBuilder(), false)
            return
        }

        if (event instanceof UserEmulatedEvent) {
            const node = PeerNode.findPeerByNativeId(event.target)
            if (node == undefined) {
                console.log(`Cannot find event target ${event.target}`)
            } else {
                switch (event.type) {
                    case 1: {
                        // console.log(`call onChange() for ${event.target}`)
                        const peer = node as TestComponentPeer
                        peer.onChangeCallback?.()
                        break
                    }
                }
            }
        }
    }

    private checkAppEvents() {
        while (this.emulatedEvents.length > 0) {
            this.processEmulatedEvent()
        }
        checkEvents()
        // Logically, coroutine resolvers are like events.
        scheduleCoroutine()
    }

    updateStates(manager: StateManager, root: ComputableState<PeerNode>): PeerNode {
        // Ensure all current state updates took effect.
        manager.syncChanges()
        manager.updateSnapshot()
        let rootPeer = this.computeRoot()
        for (const detachedRoot of detachedRoots.values()) {
            detachedRoot.value
        }
        if (partialUpdates.length > 0) {
            // If there are pending partial updates - we apply them one by one and provide update context.
            for (let update of partialUpdates) {
                // Set the context available via currentPartialUpdateContext() to @memo code.
                _currentPartialUpdateContext = update.context
                // Update states.
                update.update()
                // Propagate changes.
                manager.syncChanges()
                manager.updateSnapshot()
                // Notify subscriber.
                update.callback(true)
                // Compute new tree state
                try {
                    root.value
                    for (const detachedRoot of detachedRoots.values()) {
                        detachedRoot.value
                    }
                } catch (error: Error) {
                    console.log(`has error in partialUpdates: ${error.message} ${error.stack}`)
                }
                // Notify subscriber.
                update.callback(false)
                // Clear context.
                _currentPartialUpdateContext = undefined
            }
            // Clear partial updates list.
            partialUpdates.splice(0, partialUpdates.length)
        }
        return rootPeer
    }


    private render() {
        if (this.withLog) InteropNativeModule._NativeLog("ARKTS: render")
        ArkUINativeModule._MeasureLayoutAndDraw(this.rootPointer)
    }
    enter(arg0: int32, arg1: int32, foreignContext: pointer): boolean {
        enterForeignContext(foreignContext)
        let result = this.enterWrapped()
        leaveForeignContext()
        return result
    }

    crashDumped = false
    drawCurrentCrash() {
        const crash = this.currentCrash!
        let msg = errorInfo(crash)
        if (!this.crashDumped) {
            InteropNativeModule._NativeLog(msg)
            this.crashDumped = true
        }
        ArkUINativeModule._ShowCrash(msg ?? "unknown error message")
    }

    useOwnLoop = true
    parallelUI = false

    runEventLoop(loopIterations: int32) {
        console.log(`runEventLoop ${loopIterations}`)
        ArkUINativeModule._SetVsyncCallback(this.rootPointer)

        if (this.parallelUI)
            taskpool.execute(eventHandlerTask, this)

        while (!this.exitApp) {
            try {
                this.loopIteration()
                await (ArkUINativeModule._VSyncAwait(this.rootPointer) as Promise<void>)
                if (loopIterations > 0) {
                    if (--loopIterations == 0) break
                }
            } catch (error) {
                console.log(`Application.runEventLoop() error: ${error}`)
                if (error instanceof Error) {
                    const stack = error.stack
                    if (stack) {
                        console.log("Application.runEventLoop(): " + stack)
                    }
                }
                this.currentCrash = error as Object
                this.drawCurrentCrash()
                this.exitApp = true
            }
        }
    }

    private enterWrapped(): boolean {
        try {
            if (this.withLog) NativeLog.Default.startNativeLog(1)
            if (this.currentCrash) {
                this.drawCurrentCrash()
            } else {
                try {
                    this.loopIteration()
                } catch (error) {
                    InteropNativeModule._NativeLog(`Application.enter() error: ${error}`)
                    if (error instanceof Error) {
                        const stack = error.stack
                        if (stack) {
                            InteropNativeModule._NativeLog("Application.enter: " + stack)
                            return true
                        }
                    }
                    this.currentCrash = error as Object
                }
            }
            if (this.withLog) {
                NativeLog.Default.stopNativeLog(1)
                if (this.useNativeLog) {
                    InteropNativeModule._PrintGroupedLog(1)
                } else {
                    let log = NativeLog.Default.getNativeLog(1)
                    if (log.length > 0) {
                        InteropNativeModule._NativeLog(log)
                    }
                }
            }
        } catch (e) {
            if (e instanceof Error) {
                const stack = e.stack
                if (stack) {
                    console.log("Application.enter stack trace: " + stack)
                }
                this.exitApp = true
            }
        }
        return this.exitApp
    }

    loopIteration() {
        this.timer!.value = Double.toLong(Date.now())
        if (this.withLog) InteropNativeModule._NativeLog("ARKTS: loopIteration")
        if (!this.parallelUI) this.checkAppEvents()
        this.updateStates(this.manager!, this.rootState!)
        // Here we request to draw a frame and call custom components callbacks.
        this.render()
        // Call callbacks and sync.
        if (!this.parallelUI) callScheduledCallbacks()
        if (this.enableDumpTree) dumpTree(this.rootState!.value)
        while (this.vsyncWaiters.length > 0) {
            let resolve = this.vsyncWaiters.shift()!
            resolve(this)
        }
        scheduleCoroutine()
    }


    loadView(className: string, params: string): string {
        if (this.manager === undefined) {
            return "Manager is not inited"
        }

        const userView = Application.linker.createUserObject(className)
        this.manager!.reset()
        this.userView = userView as UserView
        this.userView!.provideControl(this)
        this.rootState = Application.createMemoRootState(this.manager!, this.userView!.getBuilder(), false)
        return "OK"
    }

    // Improve: make [emitEvent] suitable to get string argument
    emitEvent(type: int32, target: int32, arg0: int32, arg1: int32): string {
        console.log(`emitEvent ${type}, ${target}`)
        const node = PeerNode.findPeerByNativeId(target)
        try {
            switch (EventType.fromValue(type).valueOf()) {
                case EventType.Click.valueOf(): {
                    console.log("Emit click event for target:", target, node != undefined)
                    if (node != undefined) {
                        EventEmulator.emitClickEvent(node.peer.ptr, makeClickEvent(arg0, arg1))
                    }
                    break
                }
                case EventType.Text.valueOf(): {
                    InteropNativeModule._NativeLog("ARKTS: [emitEvent] EventType.Text is not implemented." + type)
                    break
                }
                case EventType.StartLog.valueOf(): {
                    NativeLog.Default.startNativeLog(0)
                    break
                }
                case EventType.StopLog.valueOf(): {
                    NativeLog.Default.stopNativeLog(0)
                    break
                }
                case EventType.GetLog.valueOf(): {
                    return NativeLog.Default.getNativeLog(0)
                }
                case EventType.ExitApp.valueOf(): {
                    this.exitApp = true
                    break
                }
                case EventType.SyncNeeded.valueOf(): {
                    return GlobalStateManager.instance.isUpdateNeeded() ? "true" : "false"
                }
                default: {
                    InteropNativeModule._NativeLog("ARKTS: [emitEvent] type = " + type + " is unknown.")
                    break
                }
            }
        } catch (error) {
            InteropNativeModule._NativeLog("emitEvent error: " + errorInfo(error as Object))
        }
        return "0"
    }

    static createApplication(appUrl: string, userPandaFilesPath: string, params: string, useNativeLog: boolean, vmKind: int32): Application {
        let suffix = vmKind == 2 ? "ets" : "ani"
        console.log(`Use ${suffix} flavour`)
        registerNativeModuleLibraryName("InteropNativeModule", `ArkoalaNative_${suffix}`)
        registerNativeModuleLibraryName("ArkUINativeModule", `ArkoalaNative_${suffix}`)
        registerNativeModuleLibraryName("ArkUIGeneratedNativeModule", `ArkoalaNative_${suffix}`)
        registerNativeModuleLibraryName("TestNativeModule", `ArkoalaNative_${suffix}`)
        registerSyncCallbackProcessor()

        // Improve: remove this line once we fix static blocks
        loadLibrary(`ArkoalaNative_${suffix}`)
        //

        Application.linker.addAbcFiles(userPandaFilesPath)
        const userView = Application.linker.createUserObject(appUrl) as UserView
        const app = new Application(userView, params, useNativeLog)
        userView.provideControl(app)
        return app
    }
}

function makeClickEvent(x: number, y: number): ClickEvent {
    let result = new ClickEventInternal()
    result.x = x
    result.y = y
    return result
}

