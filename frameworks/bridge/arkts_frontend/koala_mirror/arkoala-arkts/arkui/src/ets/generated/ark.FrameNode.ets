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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Position_serializer, Position } from "./units"
import { UIContext, UIContextInternal } from "./ohos.arkui.UIContext"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
export class FrameNodeInternal {
    public static fromPtr(ptr: KPointer): FrameNode {
        return new FrameNode(ptr)
    }
}
export class FrameNode implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, FrameNode.getFinalizer())
    }
    static ctor(uiContext: UIContext): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_ctor(toPeerPtr(uiContext))
        return retval
    }
    constructor(uiContext: UIContext) {
        this(FrameNode.ctor((uiContext)!))
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
    public getChild(index: number, expandMode: number): FrameNode {
        const index_casted = index as (number)
        const expandMode_casted = expandMode as (number)
        return this.getChild_serialize(index_casted, expandMode_casted)
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
    public getId(): string {
        return this.getId_serialize()
    }
    public getUniqueId(): number {
        return this.getUniqueId_serialize()
    }
    public getOpacity(): number {
        return this.getOpacity_serialize()
    }
    public isVisible(): boolean {
        return this.isVisible_serialize()
    }
    public isClipToFrame(): boolean {
        return this.isClipToFrame_serialize()
    }
    public isAttached(): boolean {
        return this.isAttached_serialize()
    }
    public getInspectorInfo(): Object {
        return this.getInspectorInfo_serialize()
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    public disposeTree(): void {
        this.disposeTree_serialize()
        return
    }
    public setCrossLanguageOptions(options: CrossLanguageOptions): void {
        const options_casted = options as (CrossLanguageOptions)
        this.setCrossLanguageOptions_serialize(options_casted)
        return
    }
    public getCrossLanguageOptions(): CrossLanguageOptions {
        return this.getCrossLanguageOptions_serialize()
    }
    public getPositionToWindowWithTransform(): Position {
        return this.getPositionToWindowWithTransform_serialize()
    }
    public static getFrameNodeByKey(name: string): FrameNode {
        const name_casted = name as (string)
        return FrameNode.getFrameNodeByKey_serialize(name_casted)
    }
    public getIdByFrameNode(node: FrameNode): number {
        const node_casted = node as (FrameNode)
        return this.getIdByFrameNode_serialize(node_casted)
    }
    public moveTo(targetParent: FrameNode, index: number): void {
        const targetParent_casted = targetParent as (FrameNode)
        const index_casted = index as (number)
        this.moveTo_serialize(targetParent_casted, index_casted)
        return
    }
    public getFirstChildIndexWithoutExpand(): number {
        return this.getFirstChildIndexWithoutExpand_serialize()
    }
    public getLastChildIndexWithoutExpand(): number {
        return this.getLastChildIndexWithoutExpand_serialize()
    }
    public static getAttachedFrameNodeById(id: string): FrameNode {
        const id_casted = id as (string)
        return FrameNode.getAttachedFrameNodeById_serialize(id_casted)
    }
    public static getFrameNodeById(id: number): FrameNode {
        const id_casted = id as (number)
        return FrameNode.getFrameNodeById_serialize(id_casted)
    }
    public static getFrameNodeByUniqueId(id: number): FrameNode {
        const id_casted = id as (number)
        return FrameNode.getFrameNodeByUniqueId_serialize(id_casted)
    }
    public reuse(): void {
        this.reuse_serialize()
        return
    }
    public recycle(): void {
        this.recycle_serialize()
        return
    }
    public static getFrameNodePtr(node: FrameNode): KPointer {
        const node_casted = node as (FrameNode)
        return FrameNode.getFrameNodePtr_serialize(node_casted)
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
    private getChild_serialize(index: number, expandMode: number): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getChild(this.peer!.ptr, index, expandMode)
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
    private getId_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getId(this.peer!.ptr)
        return retval
    }
    private getUniqueId_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getUniqueId(this.peer!.ptr)
        return retval
    }
    private getOpacity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getOpacity(this.peer!.ptr)
        return retval
    }
    private isVisible_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_isVisible(this.peer!.ptr)
        return retval
    }
    private isClipToFrame_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_isClipToFrame(this.peer!.ptr)
        return retval
    }
    private isAttached_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_isAttached(this.peer!.ptr)
        return retval
    }
    private getInspectorInfo_serialize(): Object {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getInspectorInfo(this.peer!.ptr)
        return retval
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_invalidate(this.peer!.ptr)
    }
    private disposeTree_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_disposeTree(this.peer!.ptr)
    }
    private setCrossLanguageOptions_serialize(options: CrossLanguageOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CrossLanguageOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._FrameNode_setCrossLanguageOptions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getCrossLanguageOptions_serialize(): CrossLanguageOptions {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getCrossLanguageOptions(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : CrossLanguageOptions = CrossLanguageOptions_serializer.read(retvalDeserializer)
        return returnResult
    }
    private getPositionToWindowWithTransform_serialize(): Position {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getPositionToWindowWithTransform(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Position = Position_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getFrameNodeByKey_serialize(name: string): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByKey(name)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getIdByFrameNode_serialize(node: FrameNode): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getIdByFrameNode(this.peer!.ptr, toPeerPtr(node))
        return retval
    }
    private moveTo_serialize(targetParent: FrameNode, index: number): void {
        ArkUIGeneratedNativeModule._FrameNode_moveTo(this.peer!.ptr, toPeerPtr(targetParent), index)
    }
    private getFirstChildIndexWithoutExpand_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFirstChildIndexWithoutExpand(this.peer!.ptr)
        return retval
    }
    private getLastChildIndexWithoutExpand_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getLastChildIndexWithoutExpand(this.peer!.ptr)
        return retval
    }
    private static getAttachedFrameNodeById_serialize(id: string): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getAttachedFrameNodeById(id)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private static getFrameNodeById_serialize(id: number): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeById(id)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private static getFrameNodeByUniqueId_serialize(id: number): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByUniqueId(id)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private reuse_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_reuse(this.peer!.ptr)
    }
    private recycle_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_recycle(this.peer!.ptr)
    }
    private static getFrameNodePtr_serialize(node: FrameNode): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node))
        return retval
    }
}
export interface CrossLanguageOptions {
    attributeSetting?: boolean;
}
export class FrameNode_serializer {
    public static write(buffer: SerializerBase, value: FrameNode): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): FrameNode {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return FrameNodeInternal.fromPtr(ptr)
    }
}
export class CrossLanguageOptions_serializer {
    public static write(buffer: SerializerBase, value: CrossLanguageOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_attributeSetting  = value.attributeSetting
        let value_attributeSetting_type : int32 = RuntimeType.UNDEFINED
        value_attributeSetting_type = runtimeType(value_attributeSetting)
        valueSerializer.writeInt8(value_attributeSetting_type)
        if ((RuntimeType.UNDEFINED) != (value_attributeSetting_type)) {
            const value_attributeSetting_value  = value_attributeSetting!
            valueSerializer.writeBoolean(value_attributeSetting_value)
        }
    }
    public static read(buffer: DeserializerBase): CrossLanguageOptions {
        let valueDeserializer : DeserializerBase = buffer
        const attributeSetting_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let attributeSetting_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (attributeSetting_buf_runtimeType))
        {
            attributeSetting_buf = valueDeserializer.readBoolean()
        }
        const attributeSetting_result : boolean | undefined = attributeSetting_buf
        let value : CrossLanguageOptions = ({attributeSetting: attributeSetting_result} as CrossLanguageOptions)
        return value
    }
}
