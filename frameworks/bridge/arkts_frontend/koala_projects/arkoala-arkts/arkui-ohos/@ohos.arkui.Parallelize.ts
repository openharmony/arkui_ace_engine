import { KPointer, InteropNativeModule } from "@koalaui/interop"
import { int32} from "@koalaui/common"
import { GlobalStateManager, MutableState, rememberDisposable, mutableState, __context, memoEntry1, memoEntry, __id, StateManager, ComputableState, memoize, NodeAttach, remember } from '@koalaui/runtime'
import { StateContext } from 'arkui.incremental.runtime.state';
import { PeerNode } from "arkui/PeerNode"
import { ArkContentSlotPeer } from "arkui/component/contentSlot"
import { ArkListPeer } from "arkui/component/list";
import { ArkGridPeer } from "arkui/component/grid";
import { SerializerBase } from "@koalaui/interop"
import { UIContextImpl, ContextRecord } from "arkui/base/UIContextImpl"
import { ArkUIAniModule } from "arkui.ani"
import { setNeedCreate } from "arkui/ArkComponentRoot"
import { TaskScheduler } from "arkui/TaskScheduler"
import { AceTrace } from "arkui/base/AceTrace"
import { ObserveSingleton } from "arkui/stateManagement/base/observeSingleton";
import { OBSERVE } from "arkui/stateManagement";

TaskScheduler.instance
class ContextScope {
    private oldManager: StateManager | undefined
    private manager: StateManager
    private instanceId: int32 = 0
    constructor(manager: StateManager, instanceId: int32) {
        this.manager = manager
        this.instanceId = instanceId
    }
    enter() {
        this.oldManager = GlobalStateManager.GetLocalManager()
        GlobalStateManager.SetLocalManager(this.manager)
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId)
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
    private __needAttach?: MutableState<boolean> = mutableState<boolean>(false)
    private status: int32 = 0 // 0: initial 1: building 2:builded 3:attached
    private manager: StateManager | undefined = undefined
    private rootState: ComputableState<PeerNode> | undefined = undefined
    private peerNode: PeerNode | undefined = undefined
    private options?: ParallelOption
    private instanceId: int32 = 0
    private uiContext: UIContextImpl
    _args: T | undefined = undefined
    private get needAttach(): boolean {
        return this.__needAttach!.value
    }
    private set needAttach(value: boolean) {
        this.__needAttach!.value = value
    }

    constructor(uiContext: UIContextImpl, options?: ParallelOption) {
        this.uiContext = uiContext
        this.options = options
    }

    /** @memo */
    build(
        paramCompute: () => T,
        /** @memo */
        builder: (args: T) => void,  updateUseParallel?: boolean) {
        this._args = memoize<T>(paramCompute)
        if (this.needAttach && this.status === 2) {
            this.manager!.merge((__context() as StateManager), this.rootState!)
            this.update(updateUseParallel)
            this.options?.completed?.()
            this.status = 3 // is attached
            return
        }
        if (this.status === 0) {
            this.manager = (__context() as StateManager).fork() as StateManager
            let createFun = () => {
                this.rootState = this.manager!.updatableNode<PeerNode>(this.peerNode!, (context: StateContext) => {
                    try {
                        const frozen = this.manager!.frozen
                        this.manager!.frozen = true
                        memoEntry1<T, void>(context, 0, builder, this._args as T)
                        this.manager!.frozen = frozen
                    } catch (err: Error) {
                        console.error('parallel run in taskpool error :', err)
                        console.error(err.stack)
                    }
                })
            }
            this.run((__context() as StateManager), this.manager!, createFun)
            this.status = 1
            return
        }
        if (this.status === 0) {
            this.manager!.merge(__context() as StateManager, this.rootState!)
            this.update(updateUseParallel)
        }
    }

    /** @memo */
    buildNoArgs(
        /** @memo */
        builder: () => void,  updateUseParallel?: boolean) {
        if (this.needAttach && this.status === 2) {
            this.manager!.merge(__context() as StateManager, this.rootState!)
            this.update(updateUseParallel)
            this.options?.completed?.()
            this.status = 3 // is attached
            return
        }
        if (this.status === 0) {
            this.manager = (__context() as StateManager).fork() as StateManager
            let createFun = () => {
                this.rootState = this.manager!.updatableNode<PeerNode>(this.peerNode!, (context: StateContext) => {
                    try {
                        const frozen = this.manager!.frozen
                        this.manager!.frozen = true
                        memoEntry<void>(context, 0, builder)
                        this.manager!.frozen = frozen
                    } catch (err: Error) {
                        console.error('parallel run in taskpool error :', err)
                        console.error(err.stack)
                    }
                })
            }
            this.run((__context() as StateManager), this.manager!, createFun)
            this.status = 1
            return
        }
        if (this.status === 0) {
            this.manager!.merge(__context() as StateManager, this.rootState!)
            this.update(updateUseParallel)
        }
    }

    /** @memo */
    buildArrayItem<V>(
        value: V, index: int32,
        paramCreate: (item: V, index: int32) => T,
        /** @memo */
        content_: (param: T) => void) {
        this._args = memoize<T>(() => { return paramCreate(value, index) })
        if (this.needAttach && this.status === 2) {
            this.manager!.merge(__context() as StateManager, this.rootState!)
            this.update()
            this.options?.completed?.()
            this.status = 3 // is attached
            return
        }
        if (this.status === 0) {
            this.manager = (__context() as StateManager).fork() as StateManager
            let createFun = () => {
                this.rootState = this.manager!.updatableNode<PeerNode>(this.peerNode!, (context: StateContext) => {
                    try {
                        const frozen = this.manager!.frozen
                        this.manager!.frozen = true
                        memoEntry<void>(context, 0, () => { content_(this._args as T) })
                        this.manager!.frozen = frozen
                    } catch (err: Error) {
                        console.error('parallel run in taskpool error :', err)
                        console.error(err.stack)
                    }
                })
            }
            this.run((__context() as StateManager), this.manager!, createFun)
            this.status = 1
            return
        }
        if (this.status === 0) {
            this.manager!.merge(__context() as StateManager, this.rootState!)
            this.update()
        }
    }

    run(mainManager: StateManager, manager: StateManager,
        builder: () => void) {
        const task = () => {
            AceTrace.begin(`parallelize build`)
            let scope = new ContextScope(manager, this.uiContext.getInstanceId())
            scope.enter()
            this.peerNode = ArkContentSlotPeer.create(undefined) // temp node
            const result = setNeedCreate(true)
            builder()
            this.rootState!.value
            setNeedCreate(result)
            scope.leave()
            TaskScheduler.postToMain(() => {
                AceTrace.begin(`parallelize run complete`)
                this.uiContext.scheduleCallback(() => {
                    this.status = 2
                    this.needAttach = true
                })
                ArkUIAniModule._CustomNode_RequestFrame()
                AceTrace.end()
            })
            AceTrace.end()
            return undefined
        }
        TaskScheduler.instance.submit(task)
    }

    update(updateUseParallel?: boolean) {
        if (updateUseParallel) {
            const task = () => {
                this.rootState!.forceCompleteRerender()
                this.rootState!.value
            }
            TaskScheduler.instance.submit(task)
            return
        }
        let scope = new ContextScope(this.manager!, this.uiContext.getInstanceId())
        scope.enter()
        const result = setNeedCreate(true)
        this.rootState!.forceCompleteRerender()
        this.rootState!.value
        setNeedCreate(result)
        scope.leave()
    }

    dispose(): void {
        this.__needAttach?.dispose();
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
    const option = remember<ParallelOption | undefined>(() => {
        return options
    })

    if (option?.enable === false) {
        content_(paramCompute())
        return
    }
    SerializerBase.setMultithreadMode()
    const data: ContextRecord | undefined = (__context() as StateManager)?.contextData as ContextRecord
    let uiContext = data?.uiContext as UIContextImpl
    const receiver = rememberDisposable<ParallelNode<T>>(() => {
        return new ParallelNode<T>(uiContext!, options)
    }, (parallelNode: ParallelNode<T> | undefined) => {
        parallelNode?.dispose()
    })
    if (content_ !== undefined) {
        receiver.build(paramCompute, content_)
    }
}

/** @memo */
export function ParallelizeUI(
    options: ParallelOption | undefined,
    /** @memo */
    content_: (() => void)
) {
    const option = remember<ParallelOption>(() => {
        return options ??  {enable: true} as ParallelOption
    })
    if (option?.enable === false) {
        content_()
        return
    }
    const data: ContextRecord | undefined = (__context() as StateManager)?.contextData as ContextRecord
    let uiContext = data?.uiContext as UIContextImpl
    SerializerBase.setMultithreadMode()
    const receiver = rememberDisposable<ParallelNode<undefined>>(() => {
        return new ParallelNode<undefined>(uiContext!, options)
    }, (parallelNode: ParallelNode<undefined> | undefined) => {
        parallelNode?.dispose()
    })
    if (content_ !== undefined) {
        receiver.buildNoArgs(content_!, options?.updateUseParallel)
    }
}

let adapterUpdateSet = new Set<AdapterNode>

let adapterUpdateCallback = () => {
    console.log(`[ParallelizeUI Adapter ]adapterUpdateCallback `)
    adapterUpdateSet.forEach((node) => {
        node.updateItem()
    })
}

interface AdapterNode {
    updateItem():void
}

class ParallelizeUIAdapterNode<V, T> implements AdapterNode {
    peerId = PeerNode.nextId()
    node?: PeerNode
    arr?: Array<V>
    paramCreate?: (item: V, index: int32) => T
    /** @memo */
    content?: (param: T) => void
    items = new Map<int32, ComputableState<PeerNode>>()
    renderingComponent = OBSERVE.renderingComponent

    setSourceAndCallback(arr: Array<V>,
        paramCreate: (item: V, index: int32) => T,
        /** @memo */
        content: (param: T) => void) {
        this.arr = arr
        this.paramCreate = paramCreate
        this.content = content
        this.init()
    }

    dispose() {
        this.items.forEach((node, key, map) => {
            node?.dispose()
        })
        adapterUpdateSet.delete(this)
    }

    init() {
        if (this.node === undefined) {
            return
        }
        ArkUIAniModule._ParallelizeUIAdapterNode_RegisterCallback(
            this.node!.peer!.ptr, () => { return this.getCount() },
            (index: int32, needBuild: int32, isCache: int32) => { return this.getNodeByIndex(index, needBuild, isCache) }
        )
        // adapterUpdateMap.set(0 , () => { this.updateItem() })
        adapterUpdateSet.add(this)
    }

    getCount(): int32 {
        if (this.arr) {
            console.log(`[ParallelizeUI Adapter ]getCount ${this.arr!.length}`)
            return this.arr!.length
        }
        console.log(`[ParallelizeUI Adapter ]getCount 0`)
        return 0

    }

    getNodeByIndex(index: int32, needBuild:int32, isCache?: int32): KPointer {
        if (this.arr == undefined ||  this.arr!.length <= index) {
            return 0
        }

        if (this.items.has(index)) {
            const node = this.items.get(index)!
            return node.value.getPeerPtr()
        }
        if (needBuild == 0) {
            return 0
        }

        /** @memo */
        let nodeBuilder = () => {
            AceTrace.begin(`parallel build item[${index} ${OBSERVE.renderingComponent}]`)
            let old = OBSERVE.renderingComponent
            OBSERVE.renderingComponent = this.renderingComponent
            SerializerBase.setMultithreadMode()
            const data: ContextRecord | undefined = (__context() as StateManager)?.contextData as ContextRecord
            let uiContext = data?.uiContext as UIContextImpl
            const receiver = rememberDisposable<ParallelNode<T>>(() => {
                return new ParallelNode<T>(uiContext!,
                    { completed: () => { this.onCreateComplete() } } as ParallelOption)
            }, (parallelNode: ParallelNode<T> | undefined) => {
                parallelNode?.dispose()
            })
            receiver.build(() => { return this.paramCreate!(this.arr![index], index) }, this.content!)
            OBSERVE.renderingComponent = old
            AceTrace.end()
        }

        if (isCache === 0) {
            this.getNodeByIndex(index + 1, 1, 1)
            this.getNodeByIndex(index + 2, 1, 1)
        }
        return this.createNode(nodeBuilder, index)
    }

    onCreateComplete() {

        ArkUIAniModule._ParallelizeUIAdapterNode_Reset(this.node!.peer!.ptr)
    }

    createNode(
        /** @memo */
        nodeBuilder: () => void,
        index: int32) {
        const manager = GlobalStateManager.instance
        const node = manager.updatableNode<PeerNode>(ArkContentSlotPeer.create(undefined),
            (context: StateContext) => {
                // let param = memoize<T>(() => { return this.paramCreate!(this.arr![index], index) })
                memoEntry<void>(context, 0, nodeBuilder)
            }
        )
        this.items.set(index, node)
        return node!.value.getPeerPtr()
    }

    updateItem(): void {
        this.items.forEach((node, key, map) => {
            console.log(`[ParallelizeUI Adapter ]updateItem ${key}`)
            node?.value
        })
    }
}


/** @memo */
export function ParallelizeUI<V, T>(
    options: ParallelOption | undefined,
    arr: Array<V>,
    paramCreate: (item: V, index: int32) => T,
    /** @memo */
    content_: (param: T) => void) {
    const option = rememberDisposable<ParallelOption | undefined>(() => {
        return options
    }, () => { })

    if (option?.enable === false) {
        arr.forEach((value, index) => {
            content_(paramCreate(value, index as int32))
        })
        return
    }
    SerializerBase.setMultithreadMode()

    let isLazy = false
    const peerNode = (__context() as StateManager).node
    if (peerNode instanceof ArkListPeer || peerNode instanceof ArkGridPeer) {
        isLazy = true
    }
    const data: ContextRecord | undefined = (__context() as StateManager)?.contextData as ContextRecord
    let uiContext = data?.uiContext as UIContextImpl
    if (!isLazy) {
        arr.forEach((value, index) => {
            const receiver = rememberDisposable<ParallelNode<T>>(() => {
                return new ParallelNode<T>(uiContext!, options)
            }, (parallelNode: ParallelNode<T> | undefined) => {
                parallelNode?.dispose()
            })
            if (content_ !== undefined) {
                receiver.buildArrayItem(value, index as int32, paramCreate, content_)
            }
        })
    } else {
        const data: ContextRecord | undefined = (__context() as StateManager)?.contextData as ContextRecord
        let uiContext = data?.uiContext as UIContextImpl
        uiContext.updateParallelizeItemNodeCallback_ = adapterUpdateCallback
        let adapterNode = rememberDisposable(() => new ParallelizeUIAdapterNode<V, T>(), (adapter?: ParallelizeUIAdapterNode<V, T>) => {
            adapter?.dispose()
        })
        NodeAttach(
            () => {
                const _peerPtr = ArkUIAniModule._ParallelizeUIAdapterNode_Construct(adapterNode.peerId)
                if (!_peerPtr) {
                    throw new Error(`Failed to create ParallelizeUINode with id: ${adapterNode.peerId}`)
                }
                const _peer = new PeerNode(_peerPtr, adapterNode.peerId, 'ParallelizeUINode', 0)
                adapterNode.node = _peer
                adapterNode.setSourceAndCallback(arr, paramCreate, content_)
                return _peer
            },
            (node: PeerNode) => {

            }
        )
    }
}
