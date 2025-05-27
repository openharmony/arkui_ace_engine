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
import { ArkCommonMethodPeer, CommonMethod, PickerTextStyle, PickerDialogButtonStyle, Rectangle, BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Callback_Void } from "./ability_component"
import { Dimension, ResourceColor, Offset } from "./units"
import { Resource } from "./resource"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { DialogAlignment } from "./alert_dialog"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TextPickerDialog {
    public static show(options?: TextPickerDialogOptions): void {
        const options_casted = options as (TextPickerDialogOptions | undefined)
        TextPickerDialog.show_serialize(options_casted)
        return
    }
    private static show_serialize(options?: TextPickerDialogOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTextPickerDialogOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextPickerDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkTextPickerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextPickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextPicker_construct(peerId, flags)
        const _peer  = new ArkTextPickerPeer(_peerPtr, peerId, "TextPicker", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextPickerOptionsAttribute(options?: TextPickerOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTextPickerOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextPickerInterface_setTextPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultPickerItemHeightAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_defaultPickerItemHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    canLoopAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextPickerAttribute_canLoop(this.peer.ptr, value ? 1 : 0)
    }
    disappearTextStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_disappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_textStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedTextStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_selectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAcceptAttribute(value: ((value: string,index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_onAccept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCancelAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_onCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value: string | Array<string>,index: number | Array<number>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedIndexAttribute(value: number | Array<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Array<number>
            thisSerializer.writeInt32(value_1.length as int32)
            for (let i = 0; i < value_1.length; i++) {
                const value_1_element : number = value_1[i]
                thisSerializer.writeNumber(value_1_element)
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_selectedIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: DividerOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gradientHeightAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_gradientHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((selected: number | Array<number>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextPickerAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_valueAttribute(callback: ((value: string | Array<string>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextPickerAttribute__onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextPickerRangeContent {
    icon: string | Resource;
    text?: string | Resource;
}
export interface TextCascadePickerRangeContent {
    text: string | Resource;
    children?: Array<TextCascadePickerRangeContent>;
}
export interface TextPickerOptions {
    range: Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>;
    value?: string | Array<string>;
    selected?: number | Array<number>;
}

export interface DividerOptions {
    strokeWidth?: Dimension;
    color?: ResourceColor;
    startMargin?: Dimension;
    endMargin?: Dimension;
}
export type Callback_String_Number_Void = (value: string, index: number) => void;
export type Type_TextPickerAttribute_onChange_callback = (value: string | Array<string>, index: number | Array<number>) => void;
export type Callback_Union_Number_Array_Number_Void = (selected: number | Array<number>) => void;
export type Callback_Union_String_Array_String_Void = (value: string | Array<string>) => void;
export interface TextPickerAttribute extends CommonMethod {
    defaultPickerItemHeight(value: number | string): this
    canLoop(value: boolean): this
    disappearTextStyle(value: PickerTextStyle): this
    textStyle(value: PickerTextStyle): this
    selectedTextStyle(value: PickerTextStyle): this
    onAccept(value: ((value: string,index: number) => void)): this
    onCancel(value: (() => void)): this
    onChange(value: ((value: string | Array<string>,index: number | Array<number>) => void)): this
    selectedIndex(value: number | Array<number>): this
    divider(value: DividerOptions | undefined): this
    gradientHeight(value: Dimension): this
    _onChangeEvent_selected(callback: ((selected: number | Array<number>) => void)): void
    _onChangeEvent_value(callback: ((value: string | Array<string>) => void)): void
    attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UITextPickerAttribute extends UICommonMethod {
    @memo
    defaultPickerItemHeight(value: number | string): this
    @memo
    canLoop(value: boolean): this
    @memo
    disappearTextStyle(value: PickerTextStyle): this
    @memo
    textStyle(value: PickerTextStyle): this
    @memo
    selectedTextStyle(value: PickerTextStyle): this
    @memo
    onAccept(value: ((value: string,index: number) => void)): this
    @memo
    onCancel(value: (() => void)): this
    @memo
    onChange(value: ((value: string | Array<string>,index: number | Array<number>) => void)): this
    @memo
    selectedIndex(value: number | Array<number>): this
    @memo
    divider(value: DividerOptions | undefined): this
    @memo
    gradientHeight(value: Dimension): this
    @memo
    _onChangeEvent_selected(callback: ((selected: number | Array<number>) => void)): void
    @memo
    _onChangeEvent_value(callback: ((value: string | Array<string>) => void)): void
    @memo
    attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkTextPickerStyle extends ArkCommonMethodStyle implements TextPickerAttribute {
    defaultPickerItemHeight_value?: number | string
    canLoop_value?: boolean
    disappearTextStyle_value?: PickerTextStyle
    textStyle_value?: PickerTextStyle
    selectedTextStyle_value?: PickerTextStyle
    onAccept_value?: ((value: string,index: number) => void)
    onCancel_value?: (() => void)
    onChange_value?: ((value: string | Array<string>,index: number | Array<number>) => void)
    selectedIndex_value?: number | Array<number>
    divider_value?: DividerOptions | undefined
    gradientHeight_value?: Dimension
    public defaultPickerItemHeight(value: number | string): this {
        return this
    }
    public canLoop(value: boolean): this {
        return this
    }
    public disappearTextStyle(value: PickerTextStyle): this {
        return this
    }
    public textStyle(value: PickerTextStyle): this {
        return this
    }
    public selectedTextStyle(value: PickerTextStyle): this {
        return this
    }
    public onAccept(value: ((value: string,index: number) => void)): this {
        return this
    }
    public onCancel(value: (() => void)): this {
        return this
    }
    public onChange(value: ((value: string | Array<string>,index: number | Array<number>) => void)): this {
        return this
    }
    public selectedIndex(value: number | Array<number>): this {
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        return this
    }
    public gradientHeight(value: Dimension): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((selected: number | Array<number>) => void)): void {
        throw new Error("Unimplmented")
    }
    public _onChangeEvent_value(callback: ((value: string | Array<string>) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface TextPickerResult {
    value: string | Array<string>;
    index: number | Array<number>;
}
export type Callback_TextPickerResult_Void = (value: TextPickerResult) => void;
export interface TextPickerDialogOptions extends TextPickerOptions {
    defaultPickerItemHeight?: number | string;
    canLoop?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    onAccept?: ((value: TextPickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value: TextPickerResult) => void);
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
@memo_stable
export class ArkTextPickerComponent extends ArkCommonMethodComponent implements UITextPickerAttribute {
    getPeer(): ArkTextPickerPeer {
        return (this.peer as ArkTextPickerPeer)
    }
    @memo
    public setTextPickerOptions(options?: TextPickerOptions): this {
        if (this.checkPriority("setTextPickerOptions")) {
            const options_casted = options as (TextPickerOptions | undefined)
            this.getPeer()?.setTextPickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    @memo
    public defaultPickerItemHeight(value: number | string): this {
        if (this.checkPriority("defaultPickerItemHeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.defaultPickerItemHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public canLoop(value: boolean): this {
        if (this.checkPriority("canLoop")) {
            const value_casted = value as (boolean)
            this.getPeer()?.canLoopAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public disappearTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("disappearTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.disappearTextStyleAttribute(value_casted)
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
    public selectedTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("selectedTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.selectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onAccept(value: ((value: string,index: number) => void)): this {
        if (this.checkPriority("onAccept")) {
            const value_casted = value as (((value: string,index: number) => void))
            this.getPeer()?.onAcceptAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onCancel(value: (() => void)): this {
        if (this.checkPriority("onCancel")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onCancelAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onChange(value: ((value: string | Array<string>,index: number | Array<number>) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: string | Array<string>,index: number | Array<number>) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedIndex(value: number | Array<number>): this {
        if (this.checkPriority("selectedIndex")) {
            const value_casted = value as (number | Array<number>)
            this.getPeer()?.selectedIndexAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public divider(value: DividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerOptions | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public gradientHeight(value: Dimension): this {
        if (this.checkPriority("gradientHeight")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.gradientHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public _onChangeEvent_selected(callback: ((selected: number | Array<number>) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((selected: number | Array<number>) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public _onChangeEvent_value(callback: ((value: string | Array<string>) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((value: string | Array<string>) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("TextPicker")
export function TextPicker(
    options?: TextPickerOptions,
    @memo
    content_?: () => void,
): TextPickerAttribute {
    throw new Error("Not implemented")
}

@memo
export function TextPicker(
    @memo
    style: ((attributes: UITextPickerAttribute) => void) | undefined,
    options?: TextPickerOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTextPickerComponent>((): ArkTextPickerComponent => {
        return new ArkTextPickerComponent()
    })
    NodeAttach<ArkTextPickerPeer>((): ArkTextPickerPeer => ArkTextPickerPeer.create(receiver), (_: ArkTextPickerPeer): void => {
        receiver.setTextPickerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
