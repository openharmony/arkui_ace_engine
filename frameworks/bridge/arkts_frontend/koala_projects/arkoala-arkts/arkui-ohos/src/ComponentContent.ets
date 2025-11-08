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

import { UIContext } from "@ohos/arkui/UIContext"
import { FrameNode } from "./FrameNode"
import { Content } from "./Content"
import { KPointer, pointer } from "@koalaui/interop"
import { BuilderNode, BuildOptions, voidBuilderFunc, TBuilderFunc } from "./BuilderNode"
import { WrappedBuilder } from "#generated"
import { RecordData } from "@ohos.base"

export interface ComponentContentBase extends Content {
    getNodePtr(): KPointer | undefined;
}

export class ComponentContent<T = undefined> implements ComponentContentBase {
    // the name of "builderNode_" is used in ace_engine/interfaces/native/node/native_node_ani.cpp.
    private builderNode_: BuilderNode<T>;
    private parentWeak_?: WeakRef<FrameNode>;
    private attachedNodeRef_?:pointer;
    //@ts-ignore
    constructor(uiContext: UIContext, builder: WrappedBuilder<TBuilderFunc<T>>, params: T, options?: BuildOptions) {
        let builderNode = new BuilderNode<T>(uiContext, {});
        this.builderNode_ = builderNode;
        this.builderNode_.build(builder, params, options);
    }

    constructor(uiContext: UIContext, builder: WrappedBuilder<voidBuilderFunc>) {
        let builderNode = new BuilderNode<T>(uiContext, {});
        this.builderNode_ = builderNode;
        this.builderNode_.build(builder);
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
    reuse(param?: RecordData): void {
        this.builderNode_.reuse(param);
    }
    recycle(): void {
        this.builderNode_.recycle();
    }
    dispose(): void {
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

