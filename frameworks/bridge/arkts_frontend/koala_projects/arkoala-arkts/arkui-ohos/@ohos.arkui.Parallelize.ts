import { int32 } from "@koalaui/common"
import { GlobalStateManager, MutableState, rememberDisposable, mutableState, __context,  memoEntry1, __id, StateManager, ComputableState, memoize } from "@koalaui/runtime"
import { StateContext } from 'arkui.incremental.runtime.state';
import { PeerNode } from "arkui/PeerNode";
import { ArkContentSlotPeer } from "arkui/component/contentSlot";
import { SerializerBase } from "@koalaui/interop";
import { UIContextImpl, ContextRecord } from "arkui/base/UIContextImpl"
import { ArkUIAniModule } from "arkui.ani"
import { setNeedCreate } from "arkui/ArkComponentRoot"
import { TaskScheduler } from "arkui/TaskScheduler"
import { AceTrace } from "arkui/base/AceTrace";

TaskScheduler.instance
class ContextScope {
    private oldManager: StateManager|undefined
    private manager: StateManager
    constructor(manager: StateManager) {
        this.manager = manager
    }
    enter() {
        this.oldManager = GlobalStateManager.GetLocalManager()
        GlobalStateManager.SetLocalManager(this.manager)
        const data: ContextRecord | undefined = this.manager.contextData ? this.manager.contextData as ContextRecord : undefined
        let uiContext = data?.uiContext as UIContextImpl
        ArkUIAniModule._Common_Sync_InstanceId(uiContext!.getInstanceId())
        ArkUIAniModule._SetParallelScoped(true)
    }

    leave() {
        ArkUIAniModule._SetParallelScoped(false)
        ArkUIAniModule._Common_Restore_InstanceId()
        GlobalStateManager.SetLocalManager(this.oldManager)
    }
}

/** @memo:stable */
export class ParallelNode<T> {
    private __needAttach?: MutableState<boolean> = mutableState<boolean>(false);
    private status: int32 = 0; // 0: initial 1: building 2:builded 3:attached
    private manager: StateManager | undefined = undefined;
    private rootState: ComputableState<PeerNode> | undefined = undefined
    private peerNode: PeerNode | undefined = undefined
    private options?: ParallelOption
    _args :T | undefined = undefined;
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
        paramCompute: () => T,
        /** @memo */
        builder: (args: T) => void,  updateUseParallel?: boolean) {
        this._args = memoize<T>(paramCompute);
        if (this.needAttach && this.status == 2) {
            this.manager!.merge(__context(), this.rootState!);
            this.update(updateUseParallel)
            this.options?.completed?.()
            this.status = 3; // is attached
            return;
        }
        if (this.status == 0) {
            const manager = (__context() as StateManager)
            this.manager = manager!.fork() as StateManager
            this.run(manager, this.manager!, builder)
            this.status = 1
            return;
        }
        this.manager!.merge(__context(), this.rootState!);
        this.update(updateUseParallel)
    }

    /** @memo */
    buildNoArgs(
        /** @memo */
        builder: () => void,  updateUseParallel?: boolean) {
        if (this.needAttach && this.status === 2) {
            this.manager!.merge(__context(), this.rootState!);
            this.update(updateUseParallel)
            this.options?.completed?.()
            this.status = 3; // is attached
            return;
        }
        if (this.status === 0) {
            const manager = (__context() as StateManager)
            this.manager = manager.fork() as StateManager
            this.run(manager, this.manager!, builder)
            this.status = 1
            return;
        }
        this.manager!.merge(__context(), this.rootState!);
        this.update(updateUseParallel)
    }

    run(mainManager: StateManager, manager: StateManager,
        /** @memo */
        builder: (args: T) => void) {
        const task = () => {
            let scope = new ContextScope(manager)
            scope.enter()
            this.peerNode = ArkContentSlotPeer.create(undefined) // temp node
            const result = setNeedCreate(true)
            this.rootState = manager!.updatableNode<PeerNode>(this.peerNode!, (context: StateContext) => {
                try {
                    memoEntry1<T,void>(context, 0, builder, this._args!)
                } catch(err: Error) {
                    console.error('parallel run in taskpool error :', err);
                    console.error(err.stack);
                }
                
            })
            this.rootState!.value
            setNeedCreate(result)
            scope.leave()

            mainManager.scheduleCallback(() => {
                this.status = 2
                this.needAttach = true
            })
            return undefined
        }
        AceTrace.begin(`submit`)
        TaskScheduler.instance.submit(task)
        AceTrace.end()
    }

    update(updateUseParallel?: boolean) {
        if (updateUseParallel) {
            const task = () => {
                this.rootState!.forceCompleteRerender()
                this.rootState!.value
            }
            TaskScheduler.instance.submit(task)
            return;
        }
        let scope = new ContextScope(this.manager!)
        scope.enter()
        const result = setNeedCreate(true)
        this.rootState!.forceCompleteRerender()
        this.rootState!.value
        setNeedCreate(result)
        scope.leave()
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

/** @memo */
export function ParallelizeUI<T>(
    options: ParallelOption | undefined,
    paramCompute: () => T,
    /** @memo */
    content_: (param: T) => void,
) {
    const option = rememberDisposable<ParallelOption | undefined>(() => {
        return options;
    }, () => { });

    if (option?.enable === false) {
        content_(paramCompute());
        return;
    }
    const receiver = rememberDisposable<ParallelNode<T>>(() => {
        return new ParallelNode<T>(options);
    }, (parallelNode: ParallelNode<T> | undefined) => {
        parallelNode?.dispose()
    })
    if (content_ !== undefined) {
        receiver.build(paramCompute, content_);
    }
}

/** @memo */
export function ParallelizeUI(
    options: ParallelOption | undefined,
    /** @memo */
    content_: () => void,
) {
    const option = rememberDisposable<ParallelOption | undefined>(() => {
        return options;
    }, () => { });
    if (option?.enable === false) {
        content_();
        return;
    }

    const receiver = rememberDisposable<ParallelNode<undefined>>(() => {
        return new ParallelNode<undefined>(options);
    }, (parallelNode: ParallelNode<undefined> | undefined) => {
        parallelNode?.dispose()
    })
    if (content_ !== undefined) {
        receiver.buildNoArgs(content_!, options?.updateUseParallel);
    }
}