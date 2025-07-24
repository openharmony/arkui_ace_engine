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

import { UIContext } from "./ArkCommonInterfaces"
import { Position } from "./ArkUnitsInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class FrameNodeInternal {
    public static fromPtr(ptr: KPointer): FrameNode {
        const obj : FrameNode = new FrameNode(undefined)
        obj.peer = new Finalizable(ptr, FrameNode.getFinalizer())
        return obj
    }
}
export class FrameNode implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_framenode(uiContext: UIContext): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeUIContext(uiContext)
        const retval  = ArkUIGeneratedNativeModule._FrameNode_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(uiContext?: UIContext) {
        if ((uiContext) !== (undefined))
        {
            const ctorPtr : KPointer = FrameNode.ctor_framenode((uiContext)!)
            this.peer = new Finalizable(ctorPtr, FrameNode.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FrameNode_getFinalizer()
    }
    public isModifiable(): boolean {
        return this.isModifiable_serialize()
    }
    public appendChild(node: FrameNode): void {
        const node_casted = node as (FrameNode)
        this.appendChild_serialize(node_casted)
        return
    }
    public insertChildAfter(child: FrameNode, sibling: FrameNode): void {
        const child_casted = child as (FrameNode)
        const sibling_casted = sibling as (FrameNode)
        this.insertChildAfter_serialize(child_casted, sibling_casted)
        return
    }
    public removeChild(node: FrameNode): void {
        const node_casted = node as (FrameNode)
        this.removeChild_serialize(node_casted)
        return
    }
    public clearChildren(): void {
        this.clearChildren_serialize()
        return
    }
    public getChild(index: number): FrameNode {
        const index_casted = index as (number)
        return this.getChild_serialize(index_casted)
    }
    public getFirstChild(): FrameNode {
        return this.getFirstChild_serialize()
    }
    public getNextSibling(): FrameNode {
        return this.getNextSibling_serialize()
    }
    public getPreviousSibling(): FrameNode {
        return this.getPreviousSibling_serialize()
    }
    public getParent(): FrameNode {
        return this.getParent_serialize()
    }
    public getChildrenCount(): int32 {
        return this.getChildrenCount_serialize()
    }
    public dispose(): void {
        this.dispose_serialize()
        return
    }
    public getOpacity(): number {
        return this.getOpacity_serialize()
    }
    public getPositionToWindowWithTransform(): Position {
        return this.getPositionToWindowWithTransform_serialize()
    }
    public static getFrameNodeByKey(name: string): FrameNode {
        const name_casted = name as (string)
        return FrameNode.getFrameNodeByKey_serialize(name_casted)
    }
    private isModifiable_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_isModifiable(this.peer!.ptr)
        return retval
    }
    private appendChild_serialize(node: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNode_appendChild(this.peer!.ptr, toPeerPtr(node))
    }
    private insertChildAfter_serialize(child: FrameNode, sibling: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNode_insertChildAfter(this.peer!.ptr, toPeerPtr(child), toPeerPtr(sibling))
    }
    private removeChild_serialize(node: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNode_removeChild(this.peer!.ptr, toPeerPtr(node))
    }
    private clearChildren_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_clearChildren(this.peer!.ptr)
    }
    private getChild_serialize(index: number): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getChild(this.peer!.ptr, index)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getFirstChild_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFirstChild(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getNextSibling_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getNextSibling(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getPreviousSibling_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getPreviousSibling(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getParent_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getParent(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getChildrenCount_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getChildrenCount(this.peer!.ptr)
        return retval
    }
    private dispose_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_dispose(this.peer!.ptr)
    }
    private getOpacity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getOpacity(this.peer!.ptr)
        return retval
    }
    private getPositionToWindowWithTransform_serialize(): Position {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getPositionToWindowWithTransform(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Position = retvalDeserializer.readPosition()
        return returnResult
    }
    private static getFrameNodeByKey_serialize(name: string): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByKey(name)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
}
