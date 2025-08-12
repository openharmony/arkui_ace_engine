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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, PickerTextStyle, DateRange, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, PickerDialogButtonStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Offset, VoidCallback, ResourceColor } from "./units"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource } from "global.resource"
export class CalendarPickerDialog {
    public static show(options?: CalendarDialogOptions): void {
        const options_casted = options as (CalendarDialogOptions | undefined)
        CalendarPickerDialog.show_serialize(options_casted)
        return
    }
    private static show_serialize(options?: CalendarDialogOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeCalendarDialogOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkCalendarPickerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCalendarPickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CalendarPicker_construct(peerId, flags)
        const _peer  = new ArkCalendarPickerPeer(_peerPtr, peerId, "CalendarPicker", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCalendarPickerOptionsAttribute(options?: CalendarOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeCalendarOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerInterface_setCalendarPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyle0Attribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_textStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyle1Attribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_textStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChange0Attribute(value: ((parameter: Date) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_onChange0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChange1Attribute(value: ((parameter: Date) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_onChange1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    markTodayAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_markToday(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeAlign0Attribute(alignType: CalendarAlign | undefined, offset?: Offset): void {
        const thisSerializer : Serializer = Serializer.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8(alignType_type as int32)
        if ((RuntimeType.UNDEFINED) != (alignType_type)) {
            const alignType_value  = (alignType as CalendarAlign)
            thisSerializer.writeInt32(TypeChecker.CalendarAlign_ToNumeric(alignType_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type as int32)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            thisSerializer.writeOffset(offset_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_edgeAlign0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeAlign1Attribute(alignType: CalendarAlign | undefined, offset?: Offset): void {
        const thisSerializer : Serializer = Serializer.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8(alignType_type as int32)
        if ((RuntimeType.UNDEFINED) != (alignType_type)) {
            const alignType_value  = (alignType as CalendarAlign)
            thisSerializer.writeInt32(TypeChecker.CalendarAlign_ToNumeric(alignType_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type as int32)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            thisSerializer.writeOffset(offset_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_edgeAlign1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum CalendarAlign {
    START = 0,
    CENTER = 1,
    END = 2
}
export interface CalendarOptions {
    hintRadius?: number | Resource;
    selected?: Date;
    start?: Date;
    end?: Date;
    disabledDateRange?: Array<DateRange>;
}
export type CalendarPickerInterface = (options?: CalendarOptions) => CalendarPickerAttribute;
export type Callback_Date_Void = (parameter: Date) => void;
export interface CalendarPickerAttribute extends CommonMethod {
    textStyle(value: PickerTextStyle | undefined): this
    onChange(value: ((parameter: Date) => void) | undefined): this
    markToday(value: boolean | undefined): this
    edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this
}
export class ArkCalendarPickerStyle extends ArkCommonMethodStyle implements CalendarPickerAttribute {
    textStyle_value?: PickerTextStyle | undefined
    onChange_value?: ((parameter: Date) => void) | undefined
    markToday_value?: boolean | undefined
    public textStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    public onChange(value: ((parameter: Date) => void) | undefined): this {
        return this
    }
    public markToday(value: boolean | undefined): this {
        return this
    }
    public edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        return this
    }
}
export interface CalendarDialogOptions extends CalendarOptions {
    onAccept?: ((parameter: Date) => void);
    onCancel?: VoidCallback;
    onChange?: ((parameter: Date) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    markToday?: boolean;
}
export class ArkCalendarPickerComponent extends ArkCommonMethodComponent implements CalendarPickerAttribute {
    getPeer(): ArkCalendarPickerPeer {
        return (this.peer as ArkCalendarPickerPeer)
    }
    public setCalendarPickerOptions(options?: CalendarOptions): this {
        if (this.checkPriority("setCalendarPickerOptions")) {
            const options_casted = options as (CalendarOptions | undefined)
            this.getPeer()?.setCalendarPickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("textStyle")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PickerTextStyle | undefined)
                this.getPeer()?.textStyle0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PickerTextStyle | undefined)
                this.getPeer()?.textStyle1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onChange(value: ((parameter: Date) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((parameter: Date) => void) | undefined)
                this.getPeer()?.onChange0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((parameter: Date) => void) | undefined)
                this.getPeer()?.onChange1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public markToday(value: boolean | undefined): this {
        if (this.checkPriority("markToday")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.markTodayAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        if (this.checkPriority("edgeAlign")) {
            const alignType_type = runtimeType(alignType)
            const offset_type = runtimeType(offset)
            if ((RuntimeType.OBJECT == alignType_type) || (RuntimeType.OBJECT == alignType_type)) {
                const alignType_casted = alignType as (CalendarAlign | undefined)
                const offset_casted = offset as (Offset)
                this.getPeer()?.edgeAlign0Attribute(alignType_casted, offset_casted)
                return this
            }
            if ((RuntimeType.OBJECT == alignType_type) || (RuntimeType.OBJECT == alignType_type)) {
                const alignType_casted = alignType as (CalendarAlign | undefined)
                const offset_casted = offset as (Offset)
                this.getPeer()?.edgeAlign1Attribute(alignType_casted, offset_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function CalendarPicker(
    /** @memo */
    style: ((attributes: CalendarPickerAttribute) => void) | undefined,
    options?: CalendarOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkCalendarPickerComponent()
    })
    NodeAttach<ArkCalendarPickerPeer>((): ArkCalendarPickerPeer => ArkCalendarPickerPeer.create(receiver), (_: ArkCalendarPickerPeer) => {
        receiver.setCalendarPickerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
