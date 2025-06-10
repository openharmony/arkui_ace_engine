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
import { Callback_Void } from "./SyntheticDeclarations"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface ClickEvent {
    displayX: number
    displayY: number
    windowX: number
    windowY: number
    screenX: number
    screenY: number
    x: number
    y: number
    preventDefault: (() => void)
}
export class ClickEventInternal extends BaseEventInternal implements MaterializedBase,ClickEvent {
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
    get screenX(): number {
        return this.getScreenX()
    }
    set screenX(screenX: number) {
        this.setScreenX(screenX)
    }
    get screenY(): number {
        return this.getScreenY()
    }
    set screenY(screenY: number) {
        this.setScreenY(screenY)
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
    get preventDefault(): (() => void) {
        throw new Error("Not implemented")
    }
    set preventDefault(preventDefault: (() => void)) {
        this.setPreventDefault(preventDefault)
    }
    static ctor_clickevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = ClickEventInternal.ctor_clickevent()
        this.peer = new Finalizable(ctorPtr, ClickEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ClickEvent_getFinalizer()
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
    private getScreenX(): number {
        return this.getScreenX_serialize()
    }
    private setScreenX(screenX: number): void {
        const screenX_casted = screenX as (number)
        this.setScreenX_serialize(screenX_casted)
        return
    }
    private getScreenY(): number {
        return this.getScreenY_serialize()
    }
    private setScreenY(screenY: number): void {
        const screenY_casted = screenY as (number)
        this.setScreenY_serialize(screenY_casted)
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
    private getPreventDefault(): (() => void) {
        return this.getPreventDefault_serialize()
    }
    private setPreventDefault(preventDefault: (() => void)): void {
        const preventDefault_casted = preventDefault as ((() => void))
        this.setPreventDefault_serialize(preventDefault_casted)
        return
    }
    private getDisplayX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private setDisplayX_serialize(displayX: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setDisplayX(this.peer!.ptr, displayX)
    }
    private getDisplayY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private setDisplayY_serialize(displayY: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setDisplayY(this.peer!.ptr, displayY)
    }
    private getWindowX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private setWindowX_serialize(windowX: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setWindowX(this.peer!.ptr, windowX)
    }
    private getWindowY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private setWindowY_serialize(windowY: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setWindowY(this.peer!.ptr, windowY)
    }
    private getScreenX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getScreenX(this.peer!.ptr)
        return retval
    }
    private setScreenX_serialize(screenX: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setScreenX(this.peer!.ptr, screenX)
    }
    private getScreenY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getScreenY(this.peer!.ptr)
        return retval
    }
    private setScreenY_serialize(screenY: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setScreenY(this.peer!.ptr, screenY)
    }
    private getX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getX(this.peer!.ptr)
        return retval
    }
    private setX_serialize(x: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setX(this.peer!.ptr, x)
    }
    private getY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getY(this.peer!.ptr)
        return retval
    }
    private setY_serialize(y: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setY(this.peer!.ptr, y)
    }
    private getPreventDefault_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getPreventDefault(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setPreventDefault_serialize(preventDefault: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(preventDefault)
        ArkUIGeneratedNativeModule._ClickEvent_setPreventDefault(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): ClickEventInternal {
        const obj : ClickEventInternal = new ClickEventInternal()
        obj.peer = new Finalizable(ptr, ClickEventInternal.getFinalizer())
        return obj
    }
}
