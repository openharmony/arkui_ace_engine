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

import { DragBehavior, Summary, DragResult, Rectangle } from "./ArkCommonInterfaces"
import { UnifiedData, UnifiedDataInternal } from "./ArkUnifiedDataMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface DragEvent {
    dragBehavior: DragBehavior
    useCustomDropAnimation: boolean
    getDisplayX(): number
    getDisplayY(): number
    getWindowX(): number
    getWindowY(): number
    getX(): number
    getY(): number
    setData(unifiedData: UnifiedData): void
    getData(): UnifiedData
    getSummary(): Summary
    setResult(dragResult: DragResult): void
    getResult(): DragResult
    getPreviewRect(): Rectangle
    getVelocityX(): number
    getVelocityY(): number
    getVelocity(): number
    getModifierKeyState(keys: Array<string>): boolean
}
export class DragEventInternal implements MaterializedBase,DragEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get dragBehavior(): DragBehavior {
        return this.getDragBehavior()
    }
    set dragBehavior(dragBehavior: DragBehavior) {
        this.setDragBehavior(dragBehavior)
    }
    get useCustomDropAnimation(): boolean {
        return this.getUseCustomDropAnimation()
    }
    set useCustomDropAnimation(useCustomDropAnimation: boolean) {
        this.setUseCustomDropAnimation(useCustomDropAnimation)
    }
    static ctor_dragevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = DragEventInternal.ctor_dragevent()
        this.peer = new Finalizable(ctorPtr, DragEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DragEvent_getFinalizer()
    }
    public getDisplayX(): number {
        return this.getDisplayX_serialize()
    }
    public getDisplayY(): number {
        return this.getDisplayY_serialize()
    }
    public getWindowX(): number {
        return this.getWindowX_serialize()
    }
    public getWindowY(): number {
        return this.getWindowY_serialize()
    }
    public getX(): number {
        return this.getX_serialize()
    }
    public getY(): number {
        return this.getY_serialize()
    }
    public setData(unifiedData: UnifiedData): void {
        const unifiedData_casted = unifiedData as (UnifiedData)
        this.setData_serialize(unifiedData_casted)
        return
    }
    public getData(): UnifiedData {
        return this.getData_serialize()
    }
    public getSummary(): Summary {
        return this.getSummary_serialize()
    }
    public setResult(dragResult: DragResult): void {
        const dragResult_casted = dragResult as (DragResult)
        this.setResult_serialize(dragResult_casted)
        return
    }
    public getResult(): DragResult {
        return this.getResult_serialize()
    }
    public getPreviewRect(): Rectangle {
        return this.getPreviewRect_serialize()
    }
    public getVelocityX(): number {
        return this.getVelocityX_serialize()
    }
    public getVelocityY(): number {
        return this.getVelocityY_serialize()
    }
    public getVelocity(): number {
        return this.getVelocity_serialize()
    }
    public getModifierKeyState(keys: Array<string>): boolean {
        const keys_casted = keys as (Array<string>)
        return this.getModifierKeyState_serialize(keys_casted)
    }
    private getDragBehavior(): DragBehavior {
        return this.getDragBehavior_serialize()
    }
    private setDragBehavior(dragBehavior: DragBehavior): void {
        const dragBehavior_casted = dragBehavior as (DragBehavior)
        this.setDragBehavior_serialize(dragBehavior_casted)
        return
    }
    private getUseCustomDropAnimation(): boolean {
        return this.getUseCustomDropAnimation_serialize()
    }
    private setUseCustomDropAnimation(useCustomDropAnimation: boolean): void {
        const useCustomDropAnimation_casted = useCustomDropAnimation as (boolean)
        this.setUseCustomDropAnimation_serialize(useCustomDropAnimation_casted)
        return
    }
    private getDisplayX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private getDisplayY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private getWindowX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private getWindowY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private getX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getX(this.peer!.ptr)
        return retval
    }
    private getY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getY(this.peer!.ptr)
        return retval
    }
    private setData_serialize(unifiedData: UnifiedData): void {
        ArkUIGeneratedNativeModule._DragEvent_setData(this.peer!.ptr, toPeerPtr(unifiedData))
    }
    private getData_serialize(): UnifiedData {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getData(this.peer!.ptr)
        const obj : UnifiedData = UnifiedDataInternal.fromPtr(retval)
        return obj
    }
    private getSummary_serialize(): Summary {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getSummary(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : Summary = retvalDeserializer.readSummary()
        return returnResult
    }
    private setResult_serialize(dragResult: DragResult): void {
        ArkUIGeneratedNativeModule._DragEvent_setResult(this.peer!.ptr, dragResult.valueOf())
    }
    private getResult_serialize(): DragResult {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getResult(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getPreviewRect_serialize(): Rectangle {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getPreviewRect(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : Rectangle = retvalDeserializer.readRectangle()
        return returnResult
    }
    private getVelocityX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getVelocityX(this.peer!.ptr)
        return retval
    }
    private getVelocityY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getVelocityY(this.peer!.ptr)
        return retval
    }
    private getVelocity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getVelocity(this.peer!.ptr)
        return retval
    }
    private getModifierKeyState_serialize(keys: Array<string>): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(keys.length as int32)
        for (let i = 0; i < keys.length; i++) {
            const keys_element : string = keys[i]
            thisSerializer.writeString(keys_element)
        }
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getModifierKeyState(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getDragBehavior_serialize(): DragBehavior {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getDragBehavior(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDragBehavior_serialize(dragBehavior: DragBehavior): void {
        ArkUIGeneratedNativeModule._DragEvent_setDragBehavior(this.peer!.ptr, dragBehavior.valueOf())
    }
    private getUseCustomDropAnimation_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getUseCustomDropAnimation(this.peer!.ptr)
        return retval
    }
    private setUseCustomDropAnimation_serialize(useCustomDropAnimation: boolean): void {
        ArkUIGeneratedNativeModule._DragEvent_setUseCustomDropAnimation(this.peer!.ptr, useCustomDropAnimation ? 1 : 0)
    }
    public static fromPtr(ptr: KPointer): DragEventInternal {
        const obj : DragEventInternal = new DragEventInternal()
        obj.peer = new Finalizable(ptr, DragEventInternal.getFinalizer())
        return obj
    }
}
