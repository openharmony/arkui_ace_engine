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
import { MouseButton, MouseAction } from "./ArkEnumsInterfaces"
import { Area, Length, Position } from "./ArkUnitsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface MouseEvent {
    button: MouseButton
    action: MouseAction
    displayX: number
    displayY: number
    windowX: number
    windowY: number
    screenX: number
    screenY: number
    x: number
    y: number
    stopPropagation: (() => void)
}
export class MouseEventInternal extends BaseEventInternal implements MaterializedBase,MouseEvent {
    get button(): MouseButton {
        return this.getButton()
    }
    set button(button: MouseButton) {
        this.setButton(button)
    }
    get action(): MouseAction {
        return this.getAction()
    }
    set action(action: MouseAction) {
        this.setAction(action)
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
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    static ctor_mouseevent(): KPointer {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = MouseEventInternal.ctor_mouseevent()
        this.peer = new Finalizable(ctorPtr, MouseEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._MouseEvent_getFinalizer()
    }
    private getButton(): MouseButton {
        return this.getButton_serialize()
    }
    private setButton(button: MouseButton): void {
        const button_casted = button as (MouseButton)
        this?.setButton_serialize(button_casted)
        return
    }
    private getAction(): MouseAction {
        return this.getAction_serialize()
    }
    private setAction(action: MouseAction): void {
        const action_casted = action as (MouseAction)
        this?.setAction_serialize(action_casted)
        return
    }
    private getDisplayX(): number {
        return this.getDisplayX_serialize()
    }
    private setDisplayX(displayX: number): void {
        const displayX_casted = displayX as (number)
        this?.setDisplayX_serialize(displayX_casted)
        return
    }
    private getDisplayY(): number {
        return this.getDisplayY_serialize()
    }
    private setDisplayY(displayY: number): void {
        const displayY_casted = displayY as (number)
        this?.setDisplayY_serialize(displayY_casted)
        return
    }
    private getWindowX(): number {
        return this.getWindowX_serialize()
    }
    private setWindowX(windowX: number): void {
        const windowX_casted = windowX as (number)
        this?.setWindowX_serialize(windowX_casted)
        return
    }
    private getWindowY(): number {
        return this.getWindowY_serialize()
    }
    private setWindowY(windowY: number): void {
        const windowY_casted = windowY as (number)
        this?.setWindowY_serialize(windowY_casted)
        return
    }
    private getScreenX(): number {
        return this.getScreenX_serialize()
    }
    private setScreenX(screenX: number): void {
        const screenX_casted = screenX as (number)
        this?.setScreenX_serialize(screenX_casted)
        return
    }
    private getScreenY(): number {
        return this.getScreenY_serialize()
    }
    private setScreenY(screenY: number): void {
        const screenY_casted = screenY as (number)
        this?.setScreenY_serialize(screenY_casted)
        return
    }
    private getX(): number {
        return this.getX_serialize()
    }
    private setX(x: number): void {
        const x_casted = x as (number)
        this?.setX_serialize(x_casted)
        return
    }
    private getY(): number {
        return this.getY_serialize()
    }
    private setY(y: number): void {
        const y_casted = y as (number)
        this?.setY_serialize(y_casted)
        return
    }
    private getStopPropagation(): (() => void) {
        return this.getStopPropagation_serialize()
    }
    private setStopPropagation(stopPropagation: (() => void)): void {
        const stopPropagation_casted = stopPropagation as ((() => void))
        this?.setStopPropagation_serialize(stopPropagation_casted)
        return
    }
    private getButton_serialize(): MouseButton {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getButton(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setButton_serialize(button: MouseButton): void {
        ArkUIGeneratedNativeModule._MouseEvent_setButton(this.peer!.ptr, button)
    }
    private getAction_serialize(): MouseAction {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getAction(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setAction_serialize(action: MouseAction): void {
        ArkUIGeneratedNativeModule._MouseEvent_setAction(this.peer!.ptr, action)
    }
    private getDisplayX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private setDisplayX_serialize(displayX: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setDisplayX(this.peer!.ptr, displayX)
    }
    private getDisplayY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private setDisplayY_serialize(displayY: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setDisplayY(this.peer!.ptr, displayY)
    }
    private getWindowX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private setWindowX_serialize(windowX: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setWindowX(this.peer!.ptr, windowX)
    }
    private getWindowY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private setWindowY_serialize(windowY: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setWindowY(this.peer!.ptr, windowY)
    }
    private getScreenX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getScreenX(this.peer!.ptr)
        return retval
    }
    private setScreenX_serialize(screenX: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setScreenX(this.peer!.ptr, screenX)
    }
    private getScreenY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getScreenY(this.peer!.ptr)
        return retval
    }
    private setScreenY_serialize(screenY: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setScreenY(this.peer!.ptr, screenY)
    }
    private getX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getX(this.peer!.ptr)
        return retval
    }
    private setX_serialize(x: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setX(this.peer!.ptr, x)
    }
    private getY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getY(this.peer!.ptr)
        return retval
    }
    private setY_serialize(y: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setY(this.peer!.ptr, y)
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval = ArkUIGeneratedNativeModule._MouseEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._MouseEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): MouseEventInternal {
        const obj: MouseEventInternal = new MouseEventInternal()
        obj.peer = new Finalizable(ptr, MouseEventInternal.getFinalizer())
        return obj
    }
}
