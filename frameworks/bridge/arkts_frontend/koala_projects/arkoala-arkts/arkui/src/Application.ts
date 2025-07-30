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

import { ComputableState, IncrementalNode, GlobalStateManager, StateManager, StateContext, memoEntry, MutableState, createAnimationTimer, callScheduledCallbacks, scheduleCallback } from "@koalaui/runtime"
import { int32, int64, scheduleCoroutine } from "@koalaui/common"
import { pointer, nullptr, KPointer, InteropNativeModule, registerNativeModuleLibraryName, KSerializerBuffer } from "@koalaui/interop"
import { PeerNode } from "./PeerNode"
import { ArkUINativeModule } from "#components"
import { EventEmulator } from "./generated/ArkEventEmulatorMaterialized"
import { UserView, UserViewBuilder } from "./UserView"
import { ClickEvent, ClickEventInternal } from "./generated/ArkClickEventMaterialized"
import { checkEvents, setCustomEventsChecker } from "./generated/Events"
import { checkArkoalaCallbacks } from "./generated/peers/CallbacksChecker"
import { setUIDetachedRootCreator } from "./generated/peers/CallbackTransformer"
import { enterForeignContext, leaveForeignContext } from "./handwritten"
import { Routed } from "./handwritten"
import { wrapSystemCallback, KUint8ArrayPtr } from "@koalaui/interop"
import { deserializeAndCallCallback } from "./generated/peers/CallbackDeserializeCall"
import { Deserializer } from "./generated/peers/Deserializer"

setCustomEventsChecker(checkArkoalaCallbacks)

enum EventType {
    Click = 0,
    Text = 1,
    ExitApp = 2
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

// TODO: move to Application class.
let detachedRoots: Map<KPointer, ComputableState<PeerNode>> = new Map<KPointer, ComputableState<PeerNode>>()


export function createUiDetachedRoot(
    peerFactory: () => PeerNode,
    /** @memo */
    builder: () => void
): PeerNode {
    const manager = GlobalStateManager.instance
    const node = manager.updatableNode<PeerNode>(peerFactory(), (context: StateContext) => {
        const frozen = manager.frozen
        manager.frozen = true
        memoEntry<void>(context, 0, () => { Routed(builder) } )
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

let crashDumped = false
function drawCurrentCrash(crash: Object) {
    let msg = errorInfo(crash)
    if (!crashDumped) {
        InteropNativeModule._NativeLog(msg)
        crashDumped = true
    }
    ArkUINativeModule._ShowCrash(msg ?? "unknown error message")
}

function registerSyncCallbackProcessor() {
    wrapSystemCallback(1, (buff:KSerializerBuffer, len:int32) => {
        deserializeAndCallCallback(new Deserializer(buff, len))
        return 0
    })
}

export class Application {
    private manager: StateManager | undefined = undefined
    private rootState: ComputableState<PeerNode> | undefined = undefined
    private timer: MutableState<int64> | undefined = undefined
    private currentCrash: Object | undefined = undefined
    private enableDumpTree = false
    private exitApp: boolean = false
    private userView: UserView | undefined = undefined

    private withLog = false
    private useNativeLog = true

    constructor(userView: UserView, useNativeLog: boolean) {
        this.userView = userView
        this.useNativeLog = useNativeLog
    }

    static createMemoRootState(manager: StateManager,
        /** @memo */
        builder: UserViewBuilder
    ): ComputableState<PeerNode> {
        const peer = PeerNode.generateRootPeer()
        return manager.updatableNode<PeerNode>(peer, (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            memoEntry<void>(context, 0, () => { Routed(builder) } )
            manager.frozen = frozen
        })
    }

    private computeRoot(): PeerNode {
        // let handle = ArkUINativeModule._SystemAPI_StartFrame()
        let result: PeerNode
        try {
            result = this.rootState!.value
        } finally {
            // ArkUINativeModule._SystemAPI_EndFrame(handle)
        }
        return result
    }

    start(foreignContext: pointer): pointer {
        enterForeignContext(foreignContext)
        if (this.withLog) UserView.startNativeLog(1)
        let root: PeerNode | undefined = undefined
        try {
            this.manager = GlobalStateManager.instance
            console.warn("Application start 111")
            this.timer = createAnimationTimer(this.manager!)
            console.warn("Application start 222")
            /** @memo */
            let builder = this.userView!.getBuilder()
            console.warn("Application start 333")
            this.rootState = Application.createMemoRootState(this.manager!, builder)
            console.warn("Application start 444")
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
            UserView.stopNativeLog(1)
            if (this.useNativeLog) {
                InteropNativeModule._PrintGroupedLog(1)
            } else {
                let log = UserView.getNativeLog(1)
                if (log.length > 0) {
                    InteropNativeModule._NativeLog(log)
                }
            }
        }
        leaveForeignContext()
        return root!.peer.ptr
    }

    private checkEvents(what: int32) {
        // NativeModule._NativeLog("ARKTS: checkEvents")
        checkEvents()
    }

    private updateState() {
        // NativeModule._NativeLog("ARKTS: updateState")
        this.updateStates(this.manager!, this.rootState!)
        // Here we request to draw a frame and call custom components callbacks.
        let root = this.rootState!.value
        ArkUINativeModule._MeasureLayoutAndDraw(root.peer.ptr)
        // Call callbacks and sync
        callScheduledCallbacks()
    }

    updateStates(manager: StateManager, root: ComputableState<PeerNode>) {
        // Ensure all current state updates took effect.
        manager.syncChanges()
        manager.updateSnapshot()
        this.computeRoot()
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
                } catch (error) {
                    InteropNativeModule._NativeLog('has error in partialUpdates')
                }
                // Notify subscriber.
                update.callback(false)
                // Clear context.
                _currentPartialUpdateContext = undefined
            }
            // Clear partial updates list.
            partialUpdates.splice(0, partialUpdates.length)
        }
    }


    private render() {
        if (this.withLog) InteropNativeModule._NativeLog("ARKTS: render")
    }
    enter(arg0: int32, arg1: int32, foreignContext: pointer): boolean {
        enterForeignContext(foreignContext)
        try {
        if (this.withLog) UserView.startNativeLog(1)

        if (this.currentCrash) {
            drawCurrentCrash(this.currentCrash!)
        } else {
            try {
                this.timer!.value = Date.now() as int64
                this.loopIteration(arg0, arg1)
                if (this.enableDumpTree) dumpTree(this.rootState!.value)
            } catch (error) {
                InteropNativeModule._NativeLog(`Application.enter() error: ${error}`)
                if (error instanceof Error) {
                    const stack = error.stack
                    if (stack) {
                        leaveForeignContext()
                        InteropNativeModule._NativeLog("Application.enter: " + stack)
                        return true
                    }
                }
                this.currentCrash = error as Object
            }
        }
        if (this.withLog) {
            UserView.stopNativeLog(1)
            if (this.useNativeLog) {
                InteropNativeModule._PrintGroupedLog(1)
            } else {
                let log = UserView.getNativeLog(1)
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
        scheduleCoroutine()
        leaveForeignContext()
        return this.exitApp
    }

    loopIteration(arg0: int32, arg1: int32) {
        if (this.withLog) InteropNativeModule._NativeLog("ARKTS: loopIteration")
        this.checkEvents(arg0)
        this.updateState()
        this.render()
    }

    // TODO: make [emitEvent] suitable to get string argument
    emitEvent(type: int32, target: int32, arg0: int32, arg1: int32): string {
        console.log("emitEvent for " + target)
        const node = PeerNode.findPeerByNativeId(target)
        if (node != undefined) {
            try {
                switch (type as EventType) {
                    case EventType.Click: {
                        EventEmulator.emitClickEvent(node.peer.ptr, makeClickEvent(10, 20))
                        break
                    }
                    case EventType.Text: {
                        InteropNativeModule._NativeLog("ARKTS: [emitEvent] EventType.Text is not implemented." + type)
                        break
                    }
                    case EventType.ExitApp: {
                        this.exitApp = true
                        break
                    }
                    default: {
                        InteropNativeModule._NativeLog("ARKTS: [emitEvent] type = " + type + " is unknown.")
                        break
                    }
                }
            } catch (error) {
                InteropNativeModule._NativeLog("emitEvent error: " + errorInfo(error as Object))
            }
        } else {
            console.log(`Cannot find target node ${target}`)
        }
        return "0"
    }

    static createApplication(appUrl: string, params: string, useNativeLog: boolean, vmKind: int32): Application {
        let suffix = vmKind == 4 ? "_ani" : "_ark"
        registerNativeModuleLibraryName("InteropNativeModule", `ArkoalaNative${suffix}`)
        registerNativeModuleLibraryName("ArkUINativeModule", `ArkoalaNative${suffix}`)
        registerNativeModuleLibraryName("ArkUIGeneratedNativeModule", `ArkoalaNative${suffix}`)
        registerNativeModuleLibraryName("TestNativeModule", `ArkoalaNative${suffix}`)
        registerSyncCallbackProcessor()
        const userView = ArkUINativeModule._LoadUserView(appUrl, params)
        if (userView == undefined) throw new Error("Cannot load user view");
        return new Application(userView as UserView, useNativeLog)
    }
}

function makeClickEvent(x: number, y: number): ClickEvent {
    let result = new ClickEventInternal()
    result.x = x
    result.y = y
    return result
}

