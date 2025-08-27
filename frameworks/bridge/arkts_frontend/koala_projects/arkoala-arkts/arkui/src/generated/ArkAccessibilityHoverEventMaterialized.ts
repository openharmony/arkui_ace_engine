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

import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
import { AccessibilityHoverType } from "./ArkEnumsInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface AccessibilityHoverEvent {
    type: AccessibilityHoverType
    x: number
    y: number
    displayX: number
    displayY: number
    windowX: number
    windowY: number
}
export class AccessibilityHoverEventInternal extends BaseEventInternal implements MaterializedBase,AccessibilityHoverEvent {
    get type(): AccessibilityHoverType {
        return this.getType()
    }
    set type(type: AccessibilityHoverType) {
        this.setType(type)
    }
    get x(): number {
        return this.getX()
    }
    set x(x: number) {
        this.setX(x)
    }
    get y(): number {
        return this.getY()
    }
    set y(y: number) {
        this.setY(y)
    }
    get displayX(): number {
        return this.getDisplayX()
    }
    set displayX(displayX: number) {
        this.setDisplayX(displayX)
    }
    get displayY(): number {
        return this.getDisplayY()
    }
    set displayY(displayY: number) {
        this.setDisplayY(displayY)
    }
    get windowX(): number {
        return this.getWindowX()
    }
    set windowX(windowX: number) {
        this.setWindowX(windowX)
    }
    get windowY(): number {
        return this.getWindowY()
    }
    set windowY(windowY: number) {
        this.setWindowY(windowY)
    }
    static ctor_accessibilityhoverevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = AccessibilityHoverEventInternal.ctor_accessibilityhoverevent()
        this.peer = new Finalizable(ctorPtr, AccessibilityHoverEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getFinalizer()
    }
    private getType(): AccessibilityHoverType {
        return this.getType_serialize()
    }
    private setType(type: AccessibilityHoverType): void {
        const type_casted = type as (AccessibilityHoverType)
        this.setType_serialize(type_casted)
        return
    }
    private getX(): number {
        return this.getX_serialize()
    }
    private setX(x: number): void {
        const x_casted = x as (number)
        this.setX_serialize(x_casted)
        return
    }
    private getY(): number {
        return this.getY_serialize()
    }
    private setY(y: number): void {
        const y_casted = y as (number)
        this.setY_serialize(y_casted)
        return
    }
    private getDisplayX(): number {
        return this.getDisplayX_serialize()
    }
    private setDisplayX(displayX: number): void {
        const displayX_casted = displayX as (number)
        this.setDisplayX_serialize(displayX_casted)
        return
    }
    private getDisplayY(): number {
        return this.getDisplayY_serialize()
    }
    private setDisplayY(displayY: number): void {
        const displayY_casted = displayY as (number)
        this.setDisplayY_serialize(displayY_casted)
        return
    }
    private getWindowX(): number {
        return this.getWindowX_serialize()
    }
    private setWindowX(windowX: number): void {
        const windowX_casted = windowX as (number)
        this.setWindowX_serialize(windowX_casted)
        return
    }
    private getWindowY(): number {
        return this.getWindowY_serialize()
    }
    private setWindowY(windowY: number): void {
        const windowY_casted = windowY as (number)
        this.setWindowY_serialize(windowY_casted)
        return
    }
    private getType_serialize(): AccessibilityHoverType {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setType_serialize(type: AccessibilityHoverType): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setType(this.peer!.ptr, type.valueOf())
    }
    private getX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getX(this.peer!.ptr)
        return retval
    }
    private setX_serialize(x: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setX(this.peer!.ptr, x)
    }
    private getY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getY(this.peer!.ptr)
        return retval
    }
    private setY_serialize(y: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setY(this.peer!.ptr, y)
    }
    private getDisplayX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private setDisplayX_serialize(displayX: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setDisplayX(this.peer!.ptr, displayX)
    }
    private getDisplayY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private setDisplayY_serialize(displayY: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setDisplayY(this.peer!.ptr, displayY)
    }
    private getWindowX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private setWindowX_serialize(windowX: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setWindowX(this.peer!.ptr, windowX)
    }
    private getWindowY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private setWindowY_serialize(windowY: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setWindowY(this.peer!.ptr, windowY)
    }
    public static fromPtr(ptr: KPointer): AccessibilityHoverEventInternal {
        const obj : AccessibilityHoverEventInternal = new AccessibilityHoverEventInternal()
        obj.peer = new Finalizable(ptr, AccessibilityHoverEventInternal.getFinalizer())
        return obj
    }
}
