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

import { Callback_ClickEvent_Void, Callback_TouchEvent_Void, Callback_Void, Callback_KeyEvent_Void, Callback_MouseEvent_Void } from "./SyntheticDeclarations"
import { ClickEvent, ClickEventInternal } from "./ArkClickEventMaterialized"
import { TouchEvent, TouchEventInternal } from "./ArkTouchEventMaterialized"
import { KeyEvent, KeyEventInternal } from "./ArkKeyEventMaterialized"
import { HoverCallback, SizeChangeCallback, VisibleAreaEventOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { MouseEvent, MouseEventInternal } from "./ArkMouseEventMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface UICommonEvent {
    setOnClick(callback_?: ((event: ClickEvent) => void)): void
    setOnTouch(callback_?: ((event: TouchEvent) => void)): void
    setOnAppear(callback_?: (() => void)): void
    setOnDisappear(callback_?: (() => void)): void
    setOnKeyEvent(callback_?: ((event: KeyEvent) => void)): void
    setOnFocus(callback_?: (() => void)): void
    setOnBlur(callback_?: (() => void)): void
    setOnHover(callback_?: HoverCallback): void
    setOnMouse(callback_?: ((event: MouseEvent) => void)): void
    setOnSizeChange(callback_?: SizeChangeCallback): void
    setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event?: VisibleAreaChangeCallback): void
}
export class UICommonEventInternal implements MaterializedBase,UICommonEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_uicommonevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UICommonEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = UICommonEventInternal.ctor_uicommonevent()
        this.peer = new Finalizable(ctorPtr, UICommonEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UICommonEvent_getFinalizer()
    }
    public setOnClick(callback_?: ((event: ClickEvent) => void)): void {
        const callback__casted = callback_ as (((event: ClickEvent) => void) | undefined)
        this.setOnClick_serialize(callback__casted)
        return
    }
    public setOnTouch(callback_?: ((event: TouchEvent) => void)): void {
        const callback__casted = callback_ as (((event: TouchEvent) => void) | undefined)
        this.setOnTouch_serialize(callback__casted)
        return
    }
    public setOnAppear(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnAppear_serialize(callback__casted)
        return
    }
    public setOnDisappear(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnDisappear_serialize(callback__casted)
        return
    }
    public setOnKeyEvent(callback_?: ((event: KeyEvent) => void)): void {
        const callback__casted = callback_ as (((event: KeyEvent) => void) | undefined)
        this.setOnKeyEvent_serialize(callback__casted)
        return
    }
    public setOnFocus(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnFocus_serialize(callback__casted)
        return
    }
    public setOnBlur(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnBlur_serialize(callback__casted)
        return
    }
    public setOnHover(callback_?: HoverCallback): void {
        const callback__casted = callback_ as (HoverCallback | undefined)
        this.setOnHover_serialize(callback__casted)
        return
    }
    public setOnMouse(callback_?: ((event: MouseEvent) => void)): void {
        const callback__casted = callback_ as (((event: MouseEvent) => void) | undefined)
        this.setOnMouse_serialize(callback__casted)
        return
    }
    public setOnSizeChange(callback_?: SizeChangeCallback): void {
        const callback__casted = callback_ as (SizeChangeCallback | undefined)
        this.setOnSizeChange_serialize(callback__casted)
        return
    }
    public setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event?: VisibleAreaChangeCallback): void {
        const options_casted = options as (VisibleAreaEventOptions)
        const event_casted = event as (VisibleAreaChangeCallback | undefined)
        this.setOnVisibleAreaApproximateChange_serialize(options_casted, event_casted)
        return
    }
    private setOnClick_serialize(callback_?: ((event: ClickEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnClick(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnTouch_serialize(callback_?: ((event: TouchEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnTouch(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnAppear_serialize(callback_?: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnAppear(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnDisappear_serialize(callback_?: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnDisappear(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnKeyEvent_serialize(callback_?: ((event: KeyEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnKeyEvent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnFocus_serialize(callback_?: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnFocus(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnBlur_serialize(callback_?: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnBlur(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnHover_serialize(callback_?: HoverCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnHover(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnMouse_serialize(callback_?: ((event: MouseEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnMouse(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnSizeChange_serialize(callback_?: SizeChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnSizeChange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnVisibleAreaApproximateChange_serialize(options: VisibleAreaEventOptions, event?: VisibleAreaChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeVisibleAreaEventOptions(options)
        let event_type : int32 = RuntimeType.UNDEFINED
        event_type = runtimeType(event)
        thisSerializer.writeInt8(event_type as int32)
        if ((RuntimeType.UNDEFINED) != (event_type)) {
            const event_value  = event!
            thisSerializer.holdAndWriteCallback(event_value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnVisibleAreaApproximateChange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): UICommonEventInternal {
        const obj : UICommonEventInternal = new UICommonEventInternal()
        obj.peer = new Finalizable(ptr, UICommonEventInternal.getFinalizer())
        return obj
    }
}
