/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
import { Finalizable, InteropNativeModule, KPointer, loadNativeModuleLibrary, nullptr } from "@koalaui/interop"
import { finalizerRegister, Thunk } from "@koalaui/common"
import { ComputableState, MutableState, rememberMutableState, StateManager, createStateManager, GlobalStateManager } from "@koalaui/runtime"
import { WrappedBuilder } from "./component/builder"
import { BuilderRootFrameNode, FrameNode, FrameNodeUtils } from "./FrameNode"
import { PeerNode } from "./PeerNode"
import { ArkComponentRootPeer, List } from "./component"
import { createUiDetachedBuilderRoot } from "./ArkUIEntry"
import { BuilderNodeOps, BuilderNodeOptions } from "./component/arkui-custom"
import { ArkBuilderProxyNodePeer } from "./handwritten/BuilderProxyNode"
import { setNeedCreate } from "./ArkComponentRoot"

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
}

class BuilderNodeFinalizationRegisterCleanerThunk implements Thunk {
    private cleaner?: (builderNode: JSBuilderNode<Object>) => void
    private __jsBuilderNode?: JSBuilderNode<Object>
    constructor(cleaner: (builderNode: JSBuilderNode<Object>) => void, jsBuilderNode: JSBuilderNode<Object>) {
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
    public static removeJSBuilderNode(builderNode: JSBuilderNode<Object>) {
        if (builderNode) {
            builderNode.dispose();
        }
    }
    public static register(target: object) {
        let builderNode = target as BuilderNode<Object>
        let trunk = new BuilderNodeFinalizationRegisterCleanerThunk(BuilderNodeFinalizationRegisterProxy.removeJSBuilderNode, builderNode._JSBuilderNode)
        finalizerRegister(builderNode, trunk)
    }
    public static instance_: BuilderNodeFinalizationRegisterProxy = new BuilderNodeFinalizationRegisterProxy();
}

export type voidBuilderFunc = /** @memo */ () => void;

export type TBuilderFunc<T> = /** @memo */ (t: T) => void;

export class BuilderNode<T = undefined>{
    public _JSBuilderNode: JSBuilderNode<T>;
    constructor(uiContext: UIContext, options?: RenderOptions) {
        this._JSBuilderNode = new JSBuilderNode<T>(uiContext, options);
        BuilderNodeFinalizationRegisterProxy.register(this);
    }
    //@ts-ignore
    public build(builder: WrappedBuilder<TBuilderFunc<T>>, params: T, options?: BuildOptions): void {
        this._JSBuilderNode.buildT(builder, params, options);
    }
    //@ts-ignore
    public build(builder: WrappedBuilder<TBuilderFunc<T>>, params: T): void {
        this._JSBuilderNode.buildT(builder, params);
    }
    //@ts-ignore
    public build(builder: WrappedBuilder<voidBuilderFunc>) {
        this._JSBuilderNode.build0(builder);
    }
    public update(params: T) {
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
    }
    public reuse(param?: Record<string, Object>): void {
        this._JSBuilderNode.reuse(param);
    }
    public recycle(): void {
        this._JSBuilderNode.recycle();
    }
    public updateConfiguration(): void {
        this._JSBuilderNode.updateConfiguration();
    }
}

export class JSBuilderNode<T> extends BuilderNodeOps {
    peer?: Finalizable | undefined = undefined
    private __root?: PeerNode;
    private __arg?: T;
    private __rootStage?: ComputableState<PeerNode>;
    private __manager: StateManager;
    private __params?: MutableState<T>;
    private __builder?: WrappedBuilder<TBuilderFunc<T>>;
    private __builder0?: WrappedBuilder<voidBuilderFunc>;
    private __frameNode: BuilderRootFrameNode<T> | null;
    private __uiContext?: UIContext;
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(uiContext: UIContext, options?: RenderOptions) {
        super();
        this.__uiContext = uiContext;
        if (options !== undefined) {
            let buildOptions: BuilderNodeOptions = {};
            if (options?.selfIdealSize !== undefined) {
                buildOptions.selfIdealSize = options.selfIdealSize;
            }
            if (options?.surfaceId !== undefined) {
                buildOptions.surfaceId = options.surfaceId;
            }
            if (options?.type !== undefined) {
                buildOptions.type = (options.type === NodeRenderType.RENDER_TYPE_TEXTURE) ? 1 : 0;
            }
            this.setOptions(buildOptions);
        }
        this.__manager = createStateManager()!;
        this.__frameNode = null;
    }
    public postTouchEvent(touchEvent: TouchEvent): boolean {
        const touchEvent_casted = touchEvent as (TouchEvent)
        return this.postTouchEvent(touchEvent_casted)
    }
    public buildFunc() {
        this.__rootStage = createUiDetachedBuilderRoot(() => {
            if (this.__root == null) {
                this.__root = ArkBuilderProxyNodePeer.create(undefined);
            }
            return this.__root!;
        }, () => {
            if (this.__builder0) {
                const result = setNeedCreate(true);
                this.__builder0?.builder();
                setNeedCreate(result);
                return;
            }
            if (this.__params === undefined && this.__arg !== undefined) {
                this.__params = rememberMutableState<T>(this.__arg!);
            }
            if (this.__params?.value) {
                const result = setNeedCreate(true);
                this.__builder?.builder(this.__params!.value);
                setNeedCreate(result);
            }
        }, this.__manager!)
        this.__rootStage?.value;
        this.__frameNode = null;
        if (this.__root?.getPeerPtr() !== undefined && this.__root?.getPeerPtr() !== nullptr) {
            if (this.__uiContext === undefined) {
                InteropNativeModule._NativeLog("UIContext in BuilderNode is undefined, please check it.");
                return;
            }
            const frameNodeOfBuilderNode: KPointer = this.setRootFrameNodeInBuilderNode(this.__root!.getPeerPtr()!)
            this.__frameNode = FrameNodeUtils.createBuilderRootFrameNode<T>(this.__uiContext!, frameNodeOfBuilderNode);
            this.__frameNode?.setJsBuilderNode(this);
            this.setUpdateConfigurationCallback(this.updateConfiguration);
        }
    }

    public build0(builder: WrappedBuilder<voidBuilderFunc>): void {
        this.__builder0 = builder;
        this.__arg = undefined;
        this.__builder = undefined;
        const old = GlobalStateManager.GetLocalManager();
        GlobalStateManager.SetLocalManager(this.__manager);
        this.create(this.buildFunc);
        GlobalStateManager.SetLocalManager(old);
    }

    public buildT(builder: WrappedBuilder<TBuilderFunc<T>>, arg?: T, options?: BuildOptions): void {
        this.__builder = builder;
        this.__builder0 = undefined;
        this.__arg = arg;
        const old = GlobalStateManager.GetLocalManager();
        GlobalStateManager.SetLocalManager(this.__manager);
        this.create(this.buildFunc);
        GlobalStateManager.SetLocalManager(old);
    }

    public update(arg: T): void {
        if (this.__params === undefined) {
            InteropNativeModule._NativeLog("the params is not Initialized!!!");
            return;
        }
        const old = GlobalStateManager.GetLocalManager();
        GlobalStateManager.SetLocalManager(this.__manager);
        this.__params!.value = arg!;
        this.__manager!.syncChanges();
        this.__manager!.updateSnapshot();
        this.__rootStage?.value;
        GlobalStateManager.SetLocalManager(old);
    }

    public getFrameNode(): FrameNode | null {
        if (this.__frameNode !== undefined &&
            this.__frameNode !== null && this.__frameNode!._nodeId !== - 1) {
            return this.__frameNode!;
        }
        return null;
    }

    public reuse(param?: Record<string, Object>): void {
    }

    public recycle(): void {
    }

    public getFrameNodeWithoutCheck(): FrameNode | null | undefined {
        return this.__frameNode;
    }

    public updateConfiguration(): void {
    }

    public getValidNodePtr(): KPointer | undefined {
        return this.__frameNode?.peer?.ptr;
    }

    public disposeNode(): void {
        this.disposeAll();
        this.__frameNode = null;
    }

    private disposeAll(): void {
        super.disposeNode();
        this.__rootStage?.dispose();
    }

    public dispose(): void {
        this.disposeAll();
        this.__frameNode?.disposeNode();
        this.__frameNode = null;
    }
}