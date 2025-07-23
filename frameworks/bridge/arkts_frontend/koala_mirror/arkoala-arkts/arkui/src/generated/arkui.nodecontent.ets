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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { Content } from "./ohos.arkui.node"
import { FrameNode, FrameNodeInternal } from "./arkui.FrameNode"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
export class NodeContentInternal {
    public static fromPtr(ptr: KPointer): NodeContent {
        return new NodeContent(ptr)
    }
}
export class NodeContent implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, NodeContent.getFinalizer())
    }
    constructor() {
        this(NodeContent.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NodeContent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NodeContent_getFinalizer()
    }
    public addFrameNode(node: FrameNode): void {
        const node_casted = node as (FrameNode)
        this.addFrameNode_serialize(node_casted)
        return
    }
    public removeFrameNode(node: FrameNode): void {
        const node_casted = node as (FrameNode)
        this.removeFrameNode_serialize(node_casted)
        return
    }
    private addFrameNode_serialize(node: FrameNode): void {
        ArkUIGeneratedNativeModule._NodeContent_addFrameNode(this.peer!.ptr, toPeerPtr(node))
    }
    private removeFrameNode_serialize(node: FrameNode): void {
        ArkUIGeneratedNativeModule._NodeContent_removeFrameNode(this.peer!.ptr, toPeerPtr(node))
    }
}
export class NodeContent_serializer {
    public static write(buffer: SerializerBase, value: NodeContent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): NodeContent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return NodeContentInternal.fromPtr(ptr)
    }
}
