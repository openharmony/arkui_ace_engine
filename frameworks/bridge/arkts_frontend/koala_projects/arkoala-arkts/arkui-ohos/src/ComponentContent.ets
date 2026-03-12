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
import { CustomBuilder } from './component/builder';
import { ReactiveBuilderNode } from './BuilderNode';
import { UIContext } from '@ohos/arkui/UIContext'
import { UIContextImpl } from './base/UIContextImpl'
import { FrameNode } from './FrameNode'
import { Content } from './Content'
import { KPointer, pointer, nullptr } from '@koalaui/interop'
import { BuilderNode, BuildOptions, voidBuilderFunc, TBuilderFunc } from './BuilderNode'
import { WrappedBuilder } from '#generated'
import { RecordData } from '@ohos.base'
import { int32 } from '@koalaui/common'
import { ArkUIAniModule } from 'arkui.ani'

export interface ComponentContentBase extends Content {
    getNodePtr(): KPointer | undefined;
}

export class ComponentContent<T = undefined> implements ComponentContentBase {
    // the name of "builderNode_" is used in ace_engine/interfaces/native/node/native_node_ani.cpp.
    private builderNode_: BuilderNode<T>;
    private parentWeak_?: WeakRef<FrameNode>;
    private attachedNodeRef_?: pointer;
    private instanceId_: int32;
    private isDisposed_: boolean;

    constructor(uiContext: UIContext, nodePtr: KPointer, frameNodePtr: KPointer) {
        this.builderNode_ = new BuilderNode<T>(uiContext, nodePtr, frameNodePtr);
        this.instanceId_ = (uiContext as UIContextImpl).instanceId_;
    }

    //@ts-ignore
    constructor(uiContext: UIContext, builder: WrappedBuilder<TBuilderFunc<T>>, params: T) {
        let builderNode = new BuilderNode<T>(uiContext);
        this.builderNode_ = builderNode;
        this.builderNode_.build(builder, params);
        this.instanceId_ = (uiContext as UIContextImpl).instanceId_;
    }

    constructor(uiContext: UIContext, builder: WrappedBuilder<TBuilderFunc<T>>, params: T, options: BuildOptions) {
        let builderNode = new BuilderNode<T>(uiContext);
        this.builderNode_ = builderNode;
        this.builderNode_.build(builder, params, options);
        this.instanceId_ = (uiContext as UIContextImpl).instanceId_;
    }

    constructor(uiContext: UIContext, builder: WrappedBuilder<voidBuilderFunc>) {
        let builderNode = new BuilderNode<T>(uiContext);
        this.builderNode_ = builderNode;
        this.builderNode_.build(builder);
        this.instanceId_ = (uiContext as UIContextImpl).instanceId_;
    }

    update(params: T): void {
        this.builderNode_.update(params);
    }

    getFrameNode(): FrameNode | null | undefined {
        return this.builderNode_.getFrameNodeWithoutCheck();
    }

    getNodePtr(): KPointer | undefined {
        // point to struct FrameNodePeer or undefined
        return this.builderNode_.getNodePtr();
    }

    getBuilderRootNode(): KPointer | undefined {
        return this.builderNode_.getBuilderRootNode();
    }

    isTransferred(): boolean {
        return false;
    }

    isDisposed(): boolean {
        ArkUIAniModule._CheckThreadValid(true, 0);
        return this.isDisposed_ && (this.builderNode_?.isDisposed() ?? true);
    }

    getInstanceId(): int32 {
        return this.instanceId_;
    }

    reuse(param?: RecordData): void {
        this.builderNode_.reuse(param);
    }

    recycle(): void {
        this.builderNode_.recycle();
    }

    dispose(): void {
        this.isDisposed_ = true;
        this.detachFromParent();
        this.builderNode_?.dispose();
    }

    updateConfiguration(): void {
        this.builderNode_.updateConfiguration();
    }

    setAttachedParent(frameNode?: WeakRef<FrameNode>): void {
        this.parentWeak_ = frameNode;
    }

    detachFromParent(): void {
        if (this.parentWeak_ === undefined) {
            return;
        }
        let parent = this.parentWeak_?.deref();
        if (parent !== undefined) {
            parent.removeComponentContent(this);
        }
    }

    public getNodeWithoutProxy(): pointer | undefined {
        // point to UINode or undefined
        return this.builderNode_?.getNodeWithoutProxy()
    }
}

function removeReactiveComponentContent(frameNode: FrameNode,
    content: ReactiveComponentContent): void {
    if (content === undefined || content === null || content.getFrameNode() === undefined ||
        content.getFrameNode() === null || content.getNodeWithoutProxy() === undefined ||
        content.getNodeWithoutProxy() === nullptr) {
        return;
    }
    const instanceId = frameNode.instanceId_!.toInt();
    ArkUIAniModule._Common_Sync_InstanceId(instanceId);
    let node = content.getNodeWithoutProxy();
    const peer = frameNode.getPeer();
    if (peer?.ptr && node) {
        ArkUIAniModule._RemoveComponent_FromFrameNode(peer!.ptr, node!);
        content.setAttachedParent(undefined);
    }
    ArkUIAniModule._Common_Restore_InstanceId();
}

export class ReactiveComponentContent implements ComponentContentBase {
    // the name of "builderNode_" is used in ace_engine/interfaces/native/node/native_node_ani.cpp.
    private builderNode_: ReactiveBuilderNode;
    private parentWeak_?: WeakRef<FrameNode>;
    private attachedNodeRef_?:pointer;
    private isDisposed_: boolean = false;
    //@ts-ignore
    constructor(uiContext: UIContext, builder: CustomBuilder, options?: BuildOptions) {
        let builderNode = new ReactiveBuilderNode(uiContext);
        this.builderNode_ = builderNode;
        this.builderNode_.build(builder, options);
    }

    getNodePtr(): KPointer | undefined {
        // point to struct FrameNodePeer or undefined
        return this.builderNode_.getNodePtr();
    }
    getFrameNode(): FrameNode | null | undefined {
        return this.builderNode_.getFrameNodeWithoutCheck();
    }
    reuse(param?: RecordData): void {
        this.builderNode_.reuse(param);
    }
    recycle(): void {
        this.builderNode_.recycle();
    }
    dispose(): void {
        this.detachFromParent();
        this.builderNode_?.dispose();
        this.isDisposed_ = true;
    }
    public isDisposed(): boolean {
        return this.isDisposed_ && (this.builderNode_?.isDisposed() ?? true)
    }
    updateConfiguration(): void {
        this.builderNode_.updateConfiguration();
    }
    setAttachedParent(frameNode?: WeakRef<FrameNode>): void {
        this.parentWeak_ = frameNode;
    }
    detachFromParent(): void {
        if (this.parentWeak_ === undefined) {
            return;
        }
        let parent = this.parentWeak_?.deref();
        if (parent !== undefined) {
            removeReactiveComponentContent(parent, this);
        }
    }

    public getNodeWithoutProxy(): pointer | undefined {
        // point to UINode or undefined
        return this.builderNode_?.getNodeWithoutProxy()
    }
    public flushState(): void {
        this.builderNode_.flushState();
    }
}
