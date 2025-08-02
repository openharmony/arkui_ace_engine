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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, InteropNativeModule } from "@koalaui/interop"
import { Content } from "./Content"
import { FrameNode } from "./FrameNode"
export class NodeContentInternal {
    public static fromPtr(ptr: KPointer): NodeContent {
        const obj: NodeContent = new NodeContent()
        obj.peer = new Finalizable(ptr, NodeContent.getFinalizer())
        return obj
    }
}
export class NodeContent implements MaterializedBase, Content {
    peer?: Finalizable | undefined = undefined
    nodeArray_: Array<FrameNode>;
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_nodecontent(): KPointer {
        const retval = ArkUIGeneratedNativeModule._NodeContent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr: KPointer = NodeContent.ctor_nodecontent()
        this.peer = new Finalizable(ctorPtr, NodeContent.getFinalizer())
        this.nodeArray_ = new Array<FrameNode>();
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NodeContent_getFinalizer()
    }
    public addFrameNode(node: FrameNode): void {
        const node_casted = node as (FrameNode)
        if (this.nodeArray_.includes(node)) {
            return;
        }
        if (this.addFrameNode_serialize(node_casted)) {
            this.nodeArray_.push(node);
        }
    }
    public removeFrameNode(node: FrameNode): void {
        const node_casted = node as (FrameNode)
        if (!this.nodeArray_.includes(node)) {
            return;
        }
        if (this.removeFrameNode_serialize(node_casted)) {
            let index = this.nodeArray_.indexOf(node);
            if (index > -1) {
                this.nodeArray_.splice(index, 1);
            }
        }
    }
    private addFrameNode_serialize(node: FrameNode): boolean {
        const retval = ArkUIGeneratedNativeModule._NodeContent_addFrameNode(this.peer!.ptr, toPeerPtr(node))
        return retval
    }
    private removeFrameNode_serialize(node: FrameNode): boolean {
        const retval = ArkUIGeneratedNativeModule._NodeContent_removeFrameNode(this.peer!.ptr, toPeerPtr(node))
        return retval
    }
}
