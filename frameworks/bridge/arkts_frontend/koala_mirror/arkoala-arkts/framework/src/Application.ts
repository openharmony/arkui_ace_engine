/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { ComputableState, GlobalStateManager, IncrementalNode, MutableState, State, StateManager, contextLocal, contextLocalScope, createAnimationTimer, memoRoot } from "@koalaui/runtime"
import { ArkUINativeModule } from "./generated/ArkUINativeModule"
import { checkEvents } from "./Events"
import { ArkoalaHost, ArkoalaControl, WaitFramesEvent, UIElement } from "./Declarations"
import { ArkoalaControlImpl } from "./ArkoalaControl"
import { withString, KPointer } from "@koalaui/interop"
import { PeerNode } from "./PeerNode"
import { int32 } from "@koalaui/common"
import { loadNative } from "./load_native"
// import { initInteropModule } from "./generated/NativeModule"

const CURRENT_CONTROL = "ohos.arkoala.control"

let rootConstruct : () => PeerNode
export function setRootConstruct(rootConstructFun: () => PeerNode) {
    rootConstruct = rootConstructFun
}

export interface UIStructureCapture {
    rootElement: UIElement
}

export interface ApplicationEmulatedEvent {
    nodeId: number
    x: number
    y: number
    status: number
    text: string
}

/** @memo */
function withControl(
    /** @memo */
    ui: () => void,
    control: ArkoalaControl
) {
    contextLocalScope(CURRENT_CONTROL, control, () => {
        ui()
    })
}

/** @memo */
export function CurrentControl(): ArkoalaControl | undefined {
    return contextLocal<ArkoalaControl>(CURRENT_CONTROL)?.value
}

/**
 * Theory of operations.
 *
 * Here we introduce the notion of partial UI update resulting from the certain
 * state change transition and associated update context. Essentially idea is that
 * we perform state update, recompute new UI state and then let backend to perform
 * associated operation, i.e. implicit animation.
 * Improve: consider moving these functions to StateManager.
 */
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

let detachedRoots: Map<KPointer, ComputableState<PeerNode>> = new Map()

export function createUiDetachedRoot(
    nodeFactory: () => PeerNode,
    /** Improve: make this memo when CustomBuilder become memo function in TS */
    builder: () => void
): PeerNode {
    const root: ComputableState<PeerNode> = memoRoot(nodeFactory(), builder)
    detachedRoots.set(root.value.peer.ptr, root)
    return root.value
}

export function destroyUiDetachedRoot(node: PeerNode): void {
    if (!detachedRoots.has(node.peer.ptr))
        throw new Error(`Root with id ${node.peer.id} is not registered`)
    const root = detachedRoots.get(node.peer.ptr)!
    detachedRoots.delete(node.peer.ptr)
    root.dispose()
}

/**
 * Current partial update context or undefined.
 *
 * @returns current partial update context
 */
export function currentPartialUpdateContext<T>(): T | undefined {
    return _currentPartialUpdateContext as (T | undefined)
}

function uiRoot(
    /** @memo */
    ui: () => void,
    control: ArkoalaControl
): State<IncrementalNode> {
    const node = rootConstruct()
    const root: ComputableState<IncrementalNode> =
        memoRoot(node!,
        () => withControl(ui, control)
    )
    root.value
    return root
}

function updateStates(manager: StateManager, root: State<IncrementalNode>): void {
    // Ensure all current state updates took effect.
    manager.syncChanges()
    manager.updateSnapshot()
    root.value
    for (const detachedRoot of detachedRoots.values())
        detachedRoot.value
    if (partialUpdates.length > 0) {
        // If there are pending partial updates - we apply them one by one and provide update context.
        for (let update of partialUpdates) {
            // Set the context available via currentPartialUpdateContext() to @memo code.
            _currentPartialUpdateContext = update.context
            // Update states.
            update.update()
            // Propagate changes.
            manager.updateSnapshot()
            // Notify subscriber.
            update.callback(true)
            // Compute new tree state
            try {
                root.value
                for (const detachedRoot of detachedRoots.values())
                    detachedRoot.value
            } catch (error) {
                console.error('has error in partialUpdates')
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

function measureLayoutAndDraw(peerNode: PeerNode) {
    ArkUINativeModule._MeasureLayoutAndDraw(peerNode.peer.ptr)
}

function getNativePipelineContext(peerNode: PeerNode) {
    return ArkUINativeModule._GetPipelineContext(peerNode.peer.ptr)
}

/*
function getNativePipelineContext(peerNode: PeerNode) {
    return nativeModule()._GetPipelineContext(peerNode.peer.ptr)
}
*/

async function eventLoopRun(
    host: Partial<ArkoalaHost>|undefined,
    onStart: ((control: ArkoalaControl) => void) | undefined,
    onError: ((error: Error) => void) | undefined,
    currentDevice: int32,
    /** @memo */
    ui: () => void
) {
    let manager: StateManager = GlobalStateManager.instance
    let root: State<IncrementalNode> | undefined = undefined
    let timer: MutableState<number> = createAnimationTimer(manager)

    let control = new ArkoalaControlImpl()
    try {
        root = uiRoot(ui, control)
    } catch (e) {
        onError?.(new Error("Cannot start: " + (e as Object).toString()))
        return
    }

    const pipelineContext = getNativePipelineContext(root!.value as PeerNode)
    ArkUINativeModule._SetVsyncCallback(pipelineContext)
    const waitVsyncFunc = (() => ArkUINativeModule._VSyncAwait(pipelineContext))
    let unlocker = setInterval(() => {
        // Improve: uncomment this code to enable Koala animations.
        // timer.value = Date.now()
        if (GlobalStateManager.instance.isUpdateNeeded())
            ArkUINativeModule._UnblockVsyncWait(pipelineContext)
    }, 32)

    let exitApp = false
    let waitFramesCallback: (() => void) | undefined
    let skipFrames = 0
    control.addListener("arkoala.press", (args: Object) => {
        let event = args as Partial<ApplicationEmulatedEvent>
        // Improve: Call emulate click
    })
    control.addListener("arkoala.text.input", (args: Object) => {
        let event = args as Partial<ApplicationEmulatedEvent>
        // Improve: Call emulate text input
    })
    control.addListener("arkoala.app.exit", (args: Object) => {
        console.log("Got app exit request")
        exitApp = true
    })
    control.addListener("arkoala.wait.frames", (args: Object) => {
        let event = args as Partial<WaitFramesEvent>
        skipFrames = event?.skipFrames ?? 0
        waitFramesCallback = event.callback
    })
    onStart?.(control)
    let currentCrash: Object | undefined = undefined
    const enableDumpTree = false

    while (!exitApp) {
        // Timer state used for animations.
        timer.value = Date.now()
        if (currentCrash) {
            drawCurrentCrash(currentCrash)
        } else {
            try {
                // Check user events.
                checkEvents()
                // Here state update is applied to recompute and memo functions called.
                updateStates(manager, root)
                // Call callbacks.
                manager.callCallbacks()
                // Here we request to draw a frame and call custom components JS callbacks.
                measureLayoutAndDraw(root!.value as PeerNode)

                if (enableDumpTree) dumpTree(root.value)
            } catch (e) {
                currentCrash = e as Object
            }
        }
        // ... and wait till it is done.
        await waitVsyncFunc()

        if (waitFramesCallback != undefined) {
            if (skipFrames > 0) {
                skipFrames--
            } else {
                waitFramesCallback()
                waitFramesCallback = undefined
            }
        }
    }

    clearInterval(unlocker)
}

function eventLoopStart(
    host: Partial<ArkoalaHost>|undefined,
    onStart: (control: ArkoalaControl) => void,
    onError: (error: Error) => void,
    currentDevice: int32,
    /** @memo */
    ui: () => void
): void {
    // Start periodic job to check if there's dirty state and unblock vsync wait.
    // Improve: think of better solution!
    setTimeout(async () => {
        await eventLoopRun(host, onStart, onError, currentDevice, ui)
    }, 1)
}

export function startApplication(
    /** @memo */
    ui: () => void,
    host?: Partial<ArkoalaHost>
): Promise<ArkoalaControl> {
    loadNative()
    return new Promise<ArkoalaControl>((resolve, reject) => {
        try {
            Object.assign(ArkUINativeModule, host?.arkUINativeModule)
        } catch (e) {
            const err = e as Error
            console.error(err.toString(), err.stack)
            reject(e as Error)
            return
        }
        eventLoopStart(host, resolve, reject, 0, ui)
    })
}

export async function runApplication(
    /** @memo */
    ui: () => void,
    onStart?: (control: ArkoalaControl) => void,
    onError?: (error: Error) => void,
    host?: Partial<ArkoalaHost>
): Promise<void> {
    try {
        // initInteropModule(host?.nativeModule)
    } catch (e) {
        onError?.(e as Error)
        return
    }
    await eventLoopRun(host, onStart, onError, 0, ui)
}

let crashDumped = false
function drawCurrentCrash(crash: Object) {
    let msg = crash.toString() + "\n"
    if (Object.hasOwn(crash, "stack")) msg += (crash as Error).stack
    if (!crashDumped) {
        console.error(msg)
        crashDumped = true
    }
    withString(msg, (msgPtr: string | null) => ArkUINativeModule._ShowCrash(msgPtr ?? "unknown error message"))
}

function waitForVSync(pipelineContext: KPointer): Promise<void> {
    return ArkUINativeModule._VSyncAwait(pipelineContext) as Promise<void>
}

function dumpTree(node: IncrementalNode, indent: number = 0) {
    const indentToString = (indent: number) => {
        let str = ""
        for (let i = 0; i <= indent; i++) str += " "
        return str
    }

    if (indent == 0) console.log("[arkoala] Dump tree:")

    let child = node.firstChild
    console.log("[arkoala] " + indentToString(indent++) + "| " + node)

    while (child) {
        dumpTree(child, indent + 1)
        child = child.nextSibling
    }
}