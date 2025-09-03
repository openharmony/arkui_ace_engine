
import { int32, KoalaCallsiteKey, observableProxy } from "@koalaui/common"
import { MutableState, rememberDisposable, mutableState, __context, StateContext, memoEntry, __id, StateManager, ComputableState, remember } from "@koalaui/runtime"
import { PeerNode } from "arkui/PeerNode";
import { ArkContentSlotPeer } from "arkui/component";
import { ArkUIGeneratedNativeModule } from "#components"
import { Serializer } from "arkui/component/peers/Serializer";
import { UIContext } from "@ohos/arkui/UIContext"
import { UIContextImpl, ContextRecord } from "arkui/handwritten/UIContextImpl"
import { ArkUIAniModule } from "arkui.ani"
import { setNeedCreate } from "arkui/ArkComponentRoot"
import { AceTrace } from "arkui/AceTrace";
import { ArkCommonMethodComponent, CommonMethod } from 'arkui/component/common'


/** @memo:stable */
export class ParallelNode {
    private __needAttach?: MutableState<boolean> = mutableState<boolean>(false);
    private status: int32 = 0; // 0: initial 1: building 2:builded 3:attached
    private manager: StateManager | undefined = undefined;
    private rootState: ComputableState<PeerNode> | undefined = undefined
    private peerNode: PeerNode | undefined = undefined
    private options?: ParallelOption
    private get needAttach(): boolean {
        return this.__needAttach!.value;
    }
    private set needAttach(value: boolean) {
        this.__needAttach!.value = value;
    }

    constructor(options?: ParallelOption) {
        this.options = options
    }

    /** @memo */
    build(
        /** @memo */
        builder: () => void, updateUseParallel: boolean = false) {
        if (this.needAttach && this.status == 2) {
            this.manager!.merge(__context(), this.rootState!, () => {
                if (updateUseParallel) {
                    const task = () => {
                        AceTrace.begin('update use Parallel')
                        this.manager!.syncChanges()
                        this.manager!.updateSnapshot()
                        this.rootState!.value
                        AceTrace.end()
                    }
                    //@ts-ignore
                    taskpool.execute(task).then(() => { }).catch((err: Error) => {
                        console.error('update use Parallel in taskpool error :', err);
                        console.error(err.stack);
                    })
                    return;
                }
                this.manager!.syncChanges()
                this.manager!.updateSnapshot()
                this.rootState!.value
            });
            this.options?.completed?.()
            this.status = 3; // is attached
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
                    this.peerNode = ArkContentSlotPeer.create(undefined)
                    const result = setNeedCreate(true);

                    this.rootState = stateManager.updatableNode<PeerNode>(this.peerNode!, (context: StateContext) => {
                        const frozen = stateManager.frozen
                        stateManager.frozen = true
                        memoEntry<void>(context, 0, builder)
                        stateManager.frozen = frozen
                    })
                    this.rootState!.value
                    setNeedCreate(result);
                    ArkUIAniModule._SetParallelScoped(false)
                    ArkUIAniModule._Common_Restore_InstanceId();
                },
                () => {
                    (__context() as StateManager)?.scheduleCallback(() => {
                        this.status = 2;
                        this.needAttach = true
                    })
                }) as StateManager;
            this.status = 1;
            return;
        }
        this.manager!.merge(__context(), this.rootState!, () => {
            if (updateUseParallel) {
                const task = () => {
                    AceTrace.begin('update use Parallel')
                    this.manager!.syncChanges()
                    this.manager!.updateSnapshot()
                    this.rootState!.value
                    AceTrace.end()
                }
                //@ts-ignore
                taskpool.execute(task).then(() => { }).catch((err: Error) => {
                    console.error('update use Parallel in taskpool error :', err);
                    console.error(err.stack);
                })
                return;
            }
            this.manager!.syncChanges()
            this.manager!.updateSnapshot()
            this.rootState!.value
        });
    }

    dispose(): void {
        this.manager?.terminate<PeerNode>(this.rootState!)

    }
}

export interface ParallelOption {
    enable?: boolean,
    initlize?: () => void,
    completed?: () => void,
    updateUseParallel?: boolean,
}

export interface UIParallelAttribute extends CommonMethod {
    enable?: boolean;
    updateUseParallel?: boolean;

    setParallelizeUIOptions(options?: ParallelOption): this;
}

export class ArkParallelComponent extends ArkCommonMethodComponent implements UIParallelAttribute {
    enable?: boolean = true;
    initlize?: () => void = undefined;
    completed?: () => void = undefined;
    updateUseParallel?: boolean = undefined;

    public setParallelizeUIOptions(options?: ParallelOption): this {
        this.enable = options?.enable;
        this.initlize = options?.initlize;
        this.completed = options?.completed;
        this.updateUseParallel = options?.updateUseParallel;
        return this;
    }
}

/** @memo */
export function ParallelizeUIImpl(
    /** @memo */
    style: ((attributes: UIParallelAttribute) => void) | undefined,
    /** @memo */
    content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkParallelComponent();
    });
    style?.(receiver);
    if (receiver.enable === false) {
        content_?.();
        return;
    }
    Serializer.setMultithreadMode();
    const parallelNode = rememberDisposable<ParallelNode>(() => {
        return new ParallelNode({
            enable: receiver.enable,
            initlize: receiver.initlize,
            completed: receiver.completed,
            updateUseParallel: receiver.updateUseParallel
        });
    }, (parallelNode: ParallelNode | undefined) => {
        parallelNode?.dispose();
    });

    if (content_ !== undefined) {
        parallelNode.build(content_!, receiver.updateUseParallel);
    }
}