import { ArkTestComponentPeer, checkArkoalaCallbacks, checkEvents, PeerNode, setCustomEventsChecker, UserView, UserViewBuilder } from "@koalaui/arkts-arkui"
import { int64 } from "@koalaui/common"
import { InteropNativeModule, KPointer, pointer, registerNativeModuleLibraryName } from "@koalaui/interop"
import { callScheduledCallbacks, ComputableState, createAnimationTimer, GlobalStateManager, memoEntry, MutableState, StateContext, StateManager } from "@koalaui/runtime"
import { ArkUINativeModule } from "#components"
import { int32 } from "@koalaui/common"

setCustomEventsChecker(checkArkoalaCallbacks)

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

let detachedRoots: Map<KPointer, ComputableState<PeerNode>> = new Map<KPointer, ComputableState<PeerNode>>()

function createMemoRoot(
    manager: StateManager,
    /** @memo */
    builder: UserViewBuilder
): ComputableState<PeerNode> {
    const peer = PeerNode.generateRootPeer()
    const node = manager.updatableNode<PeerNode>(peer, (context: StateContext) => {
        const frozen = manager.frozen
        manager.frozen = true
        memoEntry<void>(context, 0, builder)
        manager.frozen = frozen
    })
    node.value
    return node
}


export class EtsHarnessApplication {
    private manager: StateManager | undefined = undefined
    private root: ComputableState<PeerNode>  | undefined = undefined
    private timer: MutableState<int64> | undefined = undefined
    private userView: UserView | undefined = undefined
    private appId: string = "EtsHarness"

    constructor(app: string, userView: UserView, useNativeLog: boolean) {
        this.userView = userView
        this.appId = app
    }

    static createApplication(app: string, page: string, useNativeLog: boolean): EtsHarnessApplication {
        registerNativeModuleLibraryName("InteropNativeModule", "ArkoalaNative_ark")
        registerNativeModuleLibraryName("ArkUINativeModule", "ArkoalaNative_ark")
        registerNativeModuleLibraryName("ArkUIGeneratedNativeModule", "ArkoalaNative_ark")
        registerNativeModuleLibraryName("TestNativeModule", "ArkoalaNative_ark")
        const userView = ArkUINativeModule._LoadUserView(app, page)
        if (userView == undefined) throw new Error("Cannot load user view");
        return new EtsHarnessApplication(app, userView as UserView, useNativeLog)
    }

    restartWith(page: string) {
        if (this.manager === undefined) {
            return
        }
        this.manager!.reset()
        const userView = ArkUINativeModule._LoadUserView(this.appId, page)
        if (userView == undefined) throw new Error("Cannot load user view");
        this.userView = userView as UserView
        let
        /** @memo */
        content = this.userView!.getBuilder()
        this.root = createMemoRoot(this.manager!, content)
    }

    start(): pointer {
        this.manager = GlobalStateManager.instance
        this.timer = createAnimationTimer(this.manager!)
        let
        /** @memo */
        content = this.userView!.getBuilder()
        this.root = createMemoRoot(this.manager!, content)
        return this.root!.value.peer.ptr
    }

    enter(arg0: int32, arg1: int32): boolean {
        this.timer!.value = Date.now() as int64
        checkEvents()
        this.updateStates(this.manager!, this.root!)
        callScheduledCallbacks()
        return true
    }

    emitEvent(type: int32, target: int32, arg0: int32, arg1: int32): string {
        const node = PeerNode.findPeerByNativeId(target)
        let result = "0"
        switch (type) {
            case 1: {
                if (node != undefined) {
                    const peer = node as ArkTestComponentPeer
                    peer.onChangeCallback?.()
                }
                break
            }
            case 2: {
                UserView.startNativeLog(0)
                break;
            }
            case 3: {
                UserView.stopNativeLog(0)
                break;
            }
            case 4: {
                result = UserView.getNativeLog(0)
                break;
            }
            default: {
                InteropNativeModule._NativeLog(">>> Unsupported event type: " + type)
                break;
            }
        }
        return result
    }

    updateStates(manager: StateManager, root: ComputableState<PeerNode> ) {
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
                manager.syncChanges()
                manager.updateSnapshot()
                // Notify subscriber.
                update.callback(true)
                // Compute new tree state
                try {
                    root.value
                    for (const detachedRoot of detachedRoots.values())
                        detachedRoot.value
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
}
