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

import { TouchEvent, } from "./component/common"
import { Size } from "./Graphics"
import { UIContext } from "@ohos/arkui/UIContext"
import { Finalizable, InteropNativeModule, KPointer, loadNativeModuleLibrary, nullptr, pointer } from "@koalaui/interop"
import { finalizerRegister, Thunk, int32 } from "@koalaui/common"
import { ComputableState, MutableState, rememberMutableState, StateManager, memoEntry, createStateManager, GlobalStateManager, IncrementalNode } from "@koalaui/runtime"
import { StateContext } from 'arkui.incremental.runtime.state';
import { WrappedBuilder } from "./component/builder"
import { BuilderRootFrameNode, FrameNode, FrameNodeUtils } from "./FrameNode"
import { BuilderRootNodeType, findPeerNode, PeerNode, PeerNodeType } from "./PeerNode"
import { BuilderNodeOps, BuilderNodeOptions } from "#generated"
import { ArkBuilderProxyNodePeer } from "./base/BuilderProxyNode"
import { setNeedCreate } from "./ArkComponentRoot"
import { UIContextUtil } from "arkui/base/UIContextUtil"
import { ArkUIAniModule } from 'arkui.ani'
import { UIContextImpl, ContextRecord } from "./base/UIContextImpl"
import { RecordData } from "@ohos.base"
import { ParallelizeUI } from "../@ohos.arkui.Parallelize"

export enum NodeRenderType {
    RENDER_TYPE_DISPLAY = 0,
    RENDER_TYPE_TEXTURE = 1
}
export interface RenderOptions {
    selfIdealSize?: Size;
    type?: NodeRenderType;
    surfaceId?: string;
}
export interface BuildOptions {
    nestingBuilderSupported?: boolean;
    useParallel?: boolean;
}

const __uiNode_name_map__: Array<string> = ["ContentSlot", "CustomComponent", "ForEach", "LazyForEach", "Repeat", "IfElse", "Span", "ContainerSpan", "SymbolSpan"]

class BuilderRootNode extends PeerNode {
    public __parent?: ArkBuilderProxyNodePeer;

    protected constructor(peerPtr: pointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags, BuilderRootNodeType)
    }

    public static create(): BuilderRootNode {
        const peerId = PeerNode.nextId()
        const peerPtr = ArkUIAniModule._DetachedFreeRoot_Construct(peerId);
        if (!peerPtr) {
            throw new Error('create BuilderRootNode fail')
        }
        return new BuilderRootNode(peerPtr, peerId, 'BuilderRootNode')
    }
}
// mark the tree create by BuilderNode
let detachedStatMgt: Map<WeakRef<StateManager>, WeakRef<ComputableState<BuilderRootNode>>> = new Map<WeakRef<StateManager>, WeakRef<ComputableState<BuilderRootNode>>>()


function createUiDetachedBuilderRoot(
    peerFactory: () => BuilderRootNode,
    /** @memo */
    builder: () => void,
    manager: StateManager,
    instanceId: int32
): ComputableState<BuilderRootNode> {
    const node = manager.updatableNode<BuilderRootNode>(peerFactory(), (context: StateContext) => {
        ArkUIAniModule._Common_Sync_InstanceId(instanceId)
        memoEntry<void>(context, 0, builder)
        ArkUIAniModule._Common_Restore_InstanceId()
    })
    detachedStatMgt.set(new WeakRef<StateManager>(manager), new WeakRef<ComputableState<BuilderRootNode>>(node))
    return node
}

export function flushBuilderRootNode(): void {
    // updateState in BuilderNode
    let deletedMap: Array<WeakRef<StateManager>> = new Array<WeakRef<StateManager>>()
    for (const mgt of detachedStatMgt) {
        let stateMgt = mgt[0]?.deref()
        let peerNode = mgt[1]?.deref()
        if (stateMgt !== undefined && peerNode !== undefined) {
            const old = GlobalStateManager.instance;
            GlobalStateManager.SetLocalManager(stateMgt);
            stateMgt.callCallbacks()
            stateMgt.syncChanges()
            stateMgt.updateSnapshot()
            peerNode!.value;
            GlobalStateManager.SetLocalManager(old);
        } else {
            deletedMap.push(mgt[0]);
        }
    }
    // delete stateManager used by BuilderNode
    for (const mgt of deletedMap) {
        detachedStatMgt.delete(mgt);
    }
}

class BuilderNodeFinalizationRegisterCleanerThunk<T> implements Thunk {
    private cleaner?: (builderNode: JSBuilderNode<T>) => void
    private __jsBuilderNode?: JSBuilderNode<T>
    constructor(cleaner: (builderNode: JSBuilderNode<T>) => void, jsBuilderNode: JSBuilderNode<T>) {
        this.cleaner = cleaner
        this.__jsBuilderNode = jsBuilderNode;
    }
    clean() {
        if (this.__jsBuilderNode) {
            this.cleaner?.(this.__jsBuilderNode!)
        }
        this.cleaner = undefined;
        this.__jsBuilderNode = undefined;
    }
}

class BuilderNodeFinalizationRegisterProxy {
    public static removeJSBuilderNode<T>(builderNode: JSBuilderNode<T>): void {
        if (builderNode) {
            builderNode.dispose();
        }
    }
    public static register<T>(target: object): void {
        let builderNode = target as BuilderNode<T>
        let trunk = new BuilderNodeFinalizationRegisterCleanerThunk<T>(BuilderNodeFinalizationRegisterProxy.removeJSBuilderNode<T>, builderNode._JSBuilderNode<T>)
        finalizerRegister(builderNode, trunk)
    }
    public static instance_: BuilderNodeFinalizationRegisterProxy = new BuilderNodeFinalizationRegisterProxy();
}

export type voidBuilderFunc = /** @memo */ () => void;

export type TBuilderFunc<T> = /** @memo */ (t: T) => void;

export class BuilderNode<T = undefined> {
    public _JSBuilderNode: JSBuilderNode<T>;
    // the name of "nodePtr_" is used in ace_engine/interfaces/native/node/native_node_ani.cpp.
    private nodePtr_: KPointer | undefined;
    constructor(uiContext: UIContext, options?: RenderOptions) {
        this._JSBuilderNode = new JSBuilderNode<T>(uiContext, options);
        BuilderNodeFinalizationRegisterProxy.register<T>(this);
    }
    //@ts-ignore
    public build(builder: WrappedBuilder<TBuilderFunc<T>>, params: T, options?: BuildOptions): void {
        this._JSBuilderNode.buildT(builder, params, options);
        this.nodePtr_ = this._JSBuilderNode.getValidNodePtr();
    }
    //@ts-ignore
    public build(builder: WrappedBuilder<TBuilderFunc<T>>, params: T): void {
        this._JSBuilderNode.buildT(builder, params);
        this.nodePtr_ = this._JSBuilderNode.getValidNodePtr();
    }
    //@ts-ignore
    public build(builder: WrappedBuilder<voidBuilderFunc>): void {
        this._JSBuilderNode.build0(builder);
        this.nodePtr_ = this._JSBuilderNode.getValidNodePtr();
    }
    public update(params: T): void {
        this._JSBuilderNode.update(params);
    }
    public getNodePtr(): KPointer | undefined {
        return this._JSBuilderNode.getValidNodePtr();
    }
    public getFrameNode(): FrameNode | null {
        return this._JSBuilderNode.getFrameNode();
    }
    public getFrameNodeWithoutCheck(): FrameNode | null | undefined {
        return this._JSBuilderNode.getFrameNodeWithoutCheck();
    }
    public postTouchEvent(touchEvent: TouchEvent): boolean {
        let ret = this._JSBuilderNode.postTouchEvent(touchEvent);
        return ret;
    }
    public dispose(): void {
        this._JSBuilderNode.disposeNode();
        this.nodePtr_ = undefined;
    }
    public reuse(param?: RecordData): void {
        this._JSBuilderNode.reuse(param);
    }
    public recycle(): void {
        this._JSBuilderNode.recycle();
    }
    public updateConfiguration(): void {
        this._JSBuilderNode.updateConfiguration();
    }

    public getNodeWithoutProxy(): pointer | undefined {
        return this._JSBuilderNode.getNodeWithoutProxy();
    }
}

export class JSBuilderNode<T> extends BuilderNodeOps {
    peer?: Finalizable | undefined = undefined
    private __root?: BuilderRootNode;
    private __builderRootNode?: PeerNode;
    private __builderProxyNode?: ArkBuilderProxyNodePeer;
    private __arg?: T;
    private __rootStage?: ComputableState<BuilderRootNode>;
    private __manager: StateManager;
    private __params?: MutableState<T>;
    private __builder?: WrappedBuilder<TBuilderFunc<T>>;
    private __builder0?: WrappedBuilder<voidBuilderFunc>;
    private __frameNode: BuilderRootFrameNode<T> | null;
    private __uiContext?: UIContextImpl;
    private _instanceId: int32 = -1;
    private __buildOptions: BuildOptions | undefined = undefined
    private __updateUseParallel: boolean = false;

    private reset(): void {
        this.__root = undefined;
        this.__builderProxyNode = undefined;
        this.__builderRootNode = undefined;
        this.__rootStage = undefined;
        this.__params = undefined;
        this.__arg = undefined;
        this.__builder0 = undefined;
        this.__builder = undefined;
        this.__frameNode = null;
    }
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(uiContext: UIContext, options?: RenderOptions) {
        super();
        this.__uiContext = uiContext as UIContextImpl;
        this._instanceId = (uiContext as UIContextImpl).instanceId_;
        if (options !== undefined) {
            let buildOptions: BuilderNodeOptions = {};
            if (options?.selfIdealSize !== undefined) {
                buildOptions.selfIdealSize = options.selfIdealSize;
            }
            if (options?.surfaceId !== undefined) {
                buildOptions.surfaceId = options.surfaceId;
            }
            if (options?.type !== undefined) {
                buildOptions.type = options.type!;
            }
            this.setOptions(buildOptions);
        }
        this.__manager = createStateManager()!;
        let uiData = new ContextRecord();
        uiData.uiContext = uiContext;
        this.__manager.contextData = uiData;
        this.__frameNode = null;
    }

    public buildFunc(): void {
        let instanceId: int32 = 0;
        if (this.__uiContext === undefined) {
            instanceId = UIContextUtil.getCurrentInstanceId();
        } else {
            instanceId = this._instanceId;
        }
        this.__rootStage = createUiDetachedBuilderRoot(() => {
            if (this.__root == null) {
                this.__root = BuilderRootNode.create();
            }
            return this.__root!;
        }, () => {
            if (this.__builder0) {
                const result = setNeedCreate(true);
                if (this.__buildOptions?.useParallel) {
                    const builder = this.__builder0?.builder;
                    ParallelizeUI({
                        completed: () => {
                            this.__builderProxyNode?.peer?.addChild(this.__root!.getPeerPtr());
                        }
                    }, builder as () => void);
                } else {
                    this.__builder0?.builder();
                }
                setNeedCreate(result);
                return;
            }
            this.__params = rememberMutableState<T>(this.__arg as T);
            if (this.__params) {
                const result = setNeedCreate(true);
                if (this.__buildOptions?.useParallel) {
                    /** @memo */
                    const builder = (params: T) => {
                        this.__builder?.builder(params);
                    }
                    ParallelizeUI<T>({
                        completed: () => {
                            const ptr = this.__root!.getPeerPtr()
                            this.__builderProxyNode?.peer?.addChild(this.__root!.getPeerPtr());
                        },
                        updateUseParallel: this.__updateUseParallel
                    }, () => { return this.__params!.value }, builder);
                } else {
                    this.__builder?.builder(this.__params!.value);
                }
                setNeedCreate(result);
            }
        }, this.__manager!, instanceId)
        this.__rootStage?.value;
        if ((!this.__root?.firstChild || !findPeerNode(this.__root!)?.getPeerPtr()) && !this.__buildOptions?.useParallel) {
            this.reset();
            return;
        }
        if (this.__root !== null || this.__buildOptions?.useParallel) {
            this.__builderProxyNode = ArkBuilderProxyNodePeer.create(undefined);
            this.__root!.__parent = this.__builderProxyNode;
            this.__builderProxyNode!.hasChild = true;
            this.__builderProxyNode?.peer?.addChild(this.__root!.getPeerPtr());
            this.__builderRootNode = this.__builderProxyNode;
        } else {
            this.__builderRootNode = findPeerNode(this.__root!);
        }
        this.__frameNode = null;
        if (this.__builderRootNode?.getPeerPtr() !== undefined && this.__builderRootNode?.getPeerPtr() !== nullptr) {
            if (this.__uiContext === undefined) {
                InteropNativeModule._NativeLog("UIContext in BuilderNode is undefined, please check it.");
                return;
            }
            const frameNodeOfBuilderNode: KPointer = this.setRootFrameNodeInBuilderNode(this.__builderRootNode!.getPeerPtr()!)
            this.__frameNode = FrameNodeUtils.createBuilderRootFrameNode<T>(this.__uiContext!, frameNodeOfBuilderNode);
            this.__frameNode?.setJsBuilderNode(this);
            this.setUpdateConfigurationCallback(this.updateConfiguration);
        }
    }

    public getNodeWithoutProxy(): pointer | undefined {
        let pointer = this.__root?.getPeerPtr();
        return pointer ? pointer : undefined;
    }

    public build0(builder: WrappedBuilder<voidBuilderFunc>): void {
        this.__builder0 = builder;
        this.__arg = undefined;
        this.__builder = undefined;
        ArkUIAniModule._Common_Sync_InstanceId(this._instanceId);
        const old = GlobalStateManager.instance;
        GlobalStateManager.SetLocalManager(this.__manager);
        this.create(this.buildFunc);
        GlobalStateManager.SetLocalManager(old);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public buildT(builder: WrappedBuilder<TBuilderFunc<T>>, arg?: T, options?: BuildOptions): void {
        this.__builder = builder;
        this.__builder0 = undefined;
        this.__arg = arg;
        this.__buildOptions = options;
        ArkUIAniModule._Common_Sync_InstanceId(this._instanceId);
        const old = GlobalStateManager.instance;
        GlobalStateManager.SetLocalManager(this.__manager);
        this.create(this.buildFunc);
        GlobalStateManager.SetLocalManager(old);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public update(arg: T): void {
        if (this.__params === undefined) {
            InteropNativeModule._NativeLog("the params is not Initialized!!!");
            return;
        }
        ArkUIAniModule._Common_Sync_InstanceId(this._instanceId);
        const old = GlobalStateManager.instance;
        GlobalStateManager.SetLocalManager(this.__manager);
        this.__updateUseParallel = !(this.__frameNode?.isAttached() ?? true);
        this.__params!.value = arg!;
        this.__rootStage?.forceCompleteRerender();
        this.__manager!.syncChanges();
        this.__manager!.updateSnapshot();
        this.__rootStage?.value;
        this.__updateUseParallel = false;
        GlobalStateManager.SetLocalManager(old);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public getFrameNode(): FrameNode | null {
        if (this.__frameNode !== undefined &&
            this.__frameNode !== null && this.__frameNode!._nodeId !== - 1) {
            return this.__frameNode!;
        }
        return null;
    }

    public reuse(param?: RecordData): void {
        if (this.__root) {
            let node = findPeerNode(this.__root!);
            node?.onReuse(true, param);
        }
    }

    public recycle(): void {
        if (this.__root) {
            let node = findPeerNode(this.__root!);
            node?.onRecycle(true);
        }
    }

    public getFrameNodeWithoutCheck(): FrameNode | null | undefined {
        return this.__frameNode;
    }

    public updateConfiguration(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this._instanceId);
        const old = GlobalStateManager.instance;
        GlobalStateManager.SetLocalManager(this.__manager);
        this.__rootStage?.forceCompleteRerender();
        this.__manager?.syncChanges();
        this.__manager?.updateSnapshot();
        this.__rootStage?.value;
        GlobalStateManager.SetLocalManager(old);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public getValidNodePtr(): KPointer | undefined {
        return this.__frameNode?.peer?.ptr;
    }

    public disposeNode(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this._instanceId);
        this.disposeAll();
        this.__frameNode?.disposeNode();
        this.__frameNode = null;
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    private disposeAll(): void {
        super.disposeNode();
        this.__builderProxyNode?.dispose();
        this.__manager.reset();
    }

    public dispose(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this._instanceId);
        this.disposeAll();
        this.__frameNode?.disposeNode();
        this.__frameNode = null;
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}
