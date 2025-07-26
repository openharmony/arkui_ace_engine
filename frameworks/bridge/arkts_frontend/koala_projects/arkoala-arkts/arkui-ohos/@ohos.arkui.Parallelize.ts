
import { int32, KoalaCallsiteKey, observableProxy, Utils } from "@koalaui/common"
import { MutableState, rememberDisposable, mutableState, __context, StateContext, memoEntry, __id, StateManager, ComputableState, NodeAttach } from "@koalaui/runtime"
import { PeerNode } from "arkui/PeerNode";
import { ArkComponentRootPeer } from "arkui/component";
import { ArkUIGeneratedNativeModule } from "#components"
import { Serializer } from "arkui/component/peers/Serializer";
import { UIContext } from "@ohos/arkui/UIContext"
import { UIContextImpl, ContextRecord } from "arkui/handwritten/UIContextImpl"
import { ArkUIAniModule } from "arkui.ani"


/** @memo:stable */
export class ParallelNode {
    private __needAttach?: MutableState<boolean> = mutableState<boolean>(false);
    private status: int32 = 0; // 0: initial 1: building 2:builded 3:attached
    private manager: StateManager | undefined = undefined;
    private rootState: ComputableState<PeerNode> | undefined = undefined
    private peerNode: ArkComponentRootPeer | undefined = undefined
    private get needAttach(): boolean {
        return this.__needAttach!.value;
    }
    private set needAttach(value: boolean) {
        this.__needAttach!.value = value;
    }

    /** @memo */
    build(
        /** @memo */
        builder: () => void) {
        Utils.traceBegin(`ParallelNode build ${this.status}`)
        if (this.needAttach && this.status == 2) {
            this.manager!.merge(__context(), this.rootState!, () => {
                this.manager!.syncChanges()
                this.manager!.updateSnapshot()
                this.rootState!.value
            });
            this.status = 3; // is attached
            Utils.traceEnd();
            return;
        }
        if (this.status == 0) {
            this.manager = __context().fork(
                (manager: StateContext) => {
                    const stateManager = manager as StateManager
                    const data: ContextRecord | undefined = stateManager.contextData ? stateManager.contextData as ContextRecord : undefined
                    let uiContext = data?.uiContext as UIContextImpl
                    ArkUIAniModule._Common_Sync_InstanceId(uiContext!.getInstanceId());
                    ArkUIAniModule._SetParallelScoped(true)
                    this.peerNode = ArkComponentRootPeer.create(undefined)

                    this.rootState = stateManager.updatableNode<PeerNode>(this.peerNode!, (context: StateContext) => {
                        const frozen = stateManager.frozen
                        stateManager.frozen = true
                        memoEntry<void>(context, 0, builder)
                        stateManager.frozen = frozen
                    })
                    this.rootState!.value
                    ArkUIAniModule._SetParallelScoped(false)
                    ArkUIAniModule._Common_Restore_InstanceId();
                },
                () => {
                    (__context() as StateManager)?.scheduleCallback(() => {
                        Utils.traceBegin(`sub manager build complete`)
                        this.status = 2;
                        this.needAttach = true
                        Utils.traceEnd();
                    })
                }) as StateManager;
            this.status = 1;
            Utils.traceEnd();
            return;
        }
        this.manager!.merge(__context(), this.rootState!, () => {
            this.manager!.syncChanges()
            this.manager!.updateSnapshot()
            this.rootState!.value
        });
        Utils.traceEnd();
    }

    dispose(): void {
        this.manager?.terminate<PeerNode>(this.rootState!)

    }
}

export interface ParallelOption {
    enable?: boolean,
    initlize?: () => void,
    completed?: () => void,
}

/** @memo:stable */
export interface ParallelAttribute {
}

/** @memo */
export function ParallelizeUI(
    /** @memo */
    style: ((attributes: ParallelAttribute) => void) | undefined,
    options?: ParallelOption | undefined,
    /** @memo */
    content_?: () => void,
) {
    const enable = rememberDisposable<boolean>(() => {
        if (options?.enable == false) {
            return false
        }
        return true;

    }, () => { })
    if (enable == false) {
        content_?.()
        return;
    }
    Serializer.setMultithreadMode()
    const receiver = rememberDisposable<ParallelNode>(() => {
        return new ParallelNode();
    }, (parallelNode: ParallelNode | undefined) => {
        parallelNode?.dispose()
    })
    if (content_ !== undefined) {
        receiver.build(content_!)
    }
}