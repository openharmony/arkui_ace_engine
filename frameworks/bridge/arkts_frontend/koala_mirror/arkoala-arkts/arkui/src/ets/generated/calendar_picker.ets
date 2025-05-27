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
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, PickerTextStyle, BlurStyle, PickerDialogButtonStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Offset, Length, VoidCallback, ResourceColor } from "./units"
import { Resource } from "./resource"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
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
        thisSerializer.writeInt8(options_type)
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
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCalendarPickerPeer {
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
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeCalendarOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerInterface_setCalendarPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_textStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((parameter: Date) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeAlignAttribute(alignType: CalendarAlign, offset?: Offset): void {
        const thisSerializer : Serializer = Serializer.hold()
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            const offset_value_dx  = offset_value.dx
            let offset_value_dx_type : int32 = RuntimeType.UNDEFINED
            offset_value_dx_type = runtimeType(offset_value_dx)
            if (RuntimeType.STRING == offset_value_dx_type) {
                thisSerializer.writeInt8(0)
                const offset_value_dx_0  = offset_value_dx as string
                thisSerializer.writeString(offset_value_dx_0)
            }
            else if (RuntimeType.NUMBER == offset_value_dx_type) {
                thisSerializer.writeInt8(1)
                const offset_value_dx_1  = offset_value_dx as number
                thisSerializer.writeNumber(offset_value_dx_1)
            }
            else if (RuntimeType.OBJECT == offset_value_dx_type) {
                thisSerializer.writeInt8(2)
                const offset_value_dx_2  = offset_value_dx as Resource
                thisSerializer.writeResource(offset_value_dx_2)
            }
            const offset_value_dy  = offset_value.dy
            let offset_value_dy_type : int32 = RuntimeType.UNDEFINED
            offset_value_dy_type = runtimeType(offset_value_dy)
            if (RuntimeType.STRING == offset_value_dy_type) {
                thisSerializer.writeInt8(0)
                const offset_value_dy_0  = offset_value_dy as string
                thisSerializer.writeString(offset_value_dy_0)
            }
            else if (RuntimeType.NUMBER == offset_value_dy_type) {
                thisSerializer.writeInt8(1)
                const offset_value_dy_1  = offset_value_dy as number
                thisSerializer.writeNumber(offset_value_dy_1)
            }
            else if (RuntimeType.OBJECT == offset_value_dy_type) {
                thisSerializer.writeInt8(2)
                const offset_value_dy_2  = offset_value_dy as Resource
                thisSerializer.writeResource(offset_value_dy_2)
            }
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_edgeAlign(this.peer.ptr, TypeChecker.CalendarAlign_ToNumeric(alignType), thisSerializer.asBuffer(), thisSerializer.length())
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
}

export type Callback_Date_Void = (parameter: Date) => void;
export interface CalendarPickerAttribute extends CommonMethod {
    textStyle(value: PickerTextStyle): this
    onChange(value: ((parameter: Date) => void)): this
    edgeAlign(alignType: CalendarAlign, offset?: Offset): this
    attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UICalendarPickerAttribute extends UICommonMethod {
    @memo
    textStyle(value: PickerTextStyle): this
    @memo
    onChange(value: ((parameter: Date) => void)): this
    @memo
    edgeAlign(alignType: CalendarAlign, offset?: Offset): this
    @memo
    attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkCalendarPickerStyle extends ArkCommonMethodStyle implements CalendarPickerAttribute {
    textStyle_value?: PickerTextStyle
    onChange_value?: ((parameter: Date) => void)
    public textStyle(value: PickerTextStyle): this {
        return this
    }
    public onChange(value: ((parameter: Date) => void)): this {
        return this
    }
    public edgeAlign(alignType: CalendarAlign, offset?: Offset): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface CalendarDialogOptions extends CalendarOptions {
    onAccept?: ((parameter: Date) => void);
    onCancel?: VoidCallback;
    onChange?: ((parameter: Date) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
@memo_stable
export class ArkCalendarPickerComponent extends ArkCommonMethodComponent implements UICalendarPickerAttribute {
    getPeer(): ArkCalendarPickerPeer {
        return (this.peer as ArkCalendarPickerPeer)
    }
    @memo
    public setCalendarPickerOptions(options?: CalendarOptions): this {
        if (this.checkPriority("setCalendarPickerOptions")) {
            const options_casted = options as (CalendarOptions | undefined)
            this.getPeer()?.setCalendarPickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    @memo
    public textStyle(value: PickerTextStyle): this {
        if (this.checkPriority("textStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.textStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onChange(value: ((parameter: Date) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((parameter: Date) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public edgeAlign(alignType: CalendarAlign, offset?: Offset): this {
        if (this.checkPriority("edgeAlign")) {
            const alignType_casted = alignType as (CalendarAlign)
            const offset_casted = offset as (Offset | undefined)
            this.getPeer()?.edgeAlignAttribute(alignType_casted, offset_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("CalendarPicker")
export function CalendarPicker(
    options?: CalendarOptions,
    @memo
    content_?: () => void,
): CalendarPickerAttribute {
    throw new Error("Not implemented")
}

@memo
export function CalendarPicker(
    @memo
    style: ((attributes: UICalendarPickerAttribute) => void) | undefined,
    options?: CalendarOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCalendarPickerComponent>((): ArkCalendarPickerComponent => {
        return new ArkCalendarPickerComponent()
    })
    NodeAttach<ArkCalendarPickerPeer>((): ArkCalendarPickerPeer => ArkCalendarPickerPeer.create(receiver), (_: ArkCalendarPickerPeer): void => {
        receiver.setCalendarPickerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
