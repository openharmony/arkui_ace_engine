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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet, PickerDialogButtonStyle_serializer, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ShadowOptions_serializer } from "./common"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Dimension, ResourceStr, ResourceColor, Offset, Font_serializer, Font, Offset_serializer } from "./units"
import { CrownSensitivity, Color, TextOverflow } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { DialogAlignment } from "./alertDialog"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TextPickerDialogInternal {
    public static fromPtr(ptr: KPointer): TextPickerDialog {
        return new TextPickerDialog(ptr)
    }
}
export class TextPickerDialog implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextPickerDialog.getFinalizer())
    }
    constructor() {
        this(TextPickerDialog.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextPickerDialog_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextPickerDialog_getFinalizer()
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            TextPickerOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextPickerInterface_setTextPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultPickerItemHeightAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDefaultPickerItemHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCanLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setCanLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisappearTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PickerTextStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDisappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PickerTextStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PickerTextStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setSelectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisableTextStyleAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDisableTextStyleAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultTextStyleAttribute(value: TextPickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextPickerTextStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDefaultTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnTextPickerChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollStopAttribute(value: TextPickerScrollStopCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setOnScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEnterSelectedAreaAttribute(value: TextPickerEnterSelectedAreaCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setOnEnterSelectedArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedIndexAttribute(value: number | Array<number> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Array<number>
                thisSerializer.writeInt32((value_value_1.length).toInt())
                for (let value_value_1_counter_i = 0; value_value_1_counter_i < value_value_1.length; value_value_1_counter_i++) {
                    const value_value_1_element : number = value_value_1[value_value_1_counter_i]
                    thisSerializer.writeNumber(value_value_1_element)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setSelectedIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DividerOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setGradientHeightAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setGradientHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDigitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CrownSensitivity)
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDigitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectedAttribute(callback_: ((selected: number | Array<number>) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._TextPickerAttribute_set_onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_valueAttribute(callback_: ((value: ResourceStr | Array<ResourceStr>) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._TextPickerAttribute_set_onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    value?: ResourceStr | Array<ResourceStr>;
    selected?: number | Array<number>;
    columnWidths?: Array<LengthMetrics>;
}
export interface DividerOptions {
    strokeWidth?: Dimension;
    color?: ResourceColor;
    startMargin?: Dimension;
    endMargin?: Dimension;
}
export interface TextPickerTextStyle extends PickerTextStyle {
    minFontSize?: number | string | Resource;
    maxFontSize?: number | string | Resource;
    overflow?: TextOverflow;
}
export type TextPickerScrollStopCallback = (value: string | Array<string>, index: number | Array<number>) => void;
export type OnTextPickerChangeCallback = (selectItem: string | Array<string>, index: number | Array<number>) => void;
export type TextPickerEnterSelectedAreaCallback = (value: string | Array<string>, index: number | Array<number>) => void;
export interface TextPickerAttribute extends CommonMethod {
    defaultPickerItemHeight(value: number | string | undefined): this {
        throw new Error("Unimplemented method defaultPickerItemHeight")
    }
    canLoop(value: boolean | undefined): this {
        throw new Error("Unimplemented method canLoop")
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        throw new Error("Unimplemented method disappearTextStyle")
    }
    textStyle(value: PickerTextStyle | undefined): this {
        throw new Error("Unimplemented method textStyle")
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        throw new Error("Unimplemented method selectedTextStyle")
    }
    disableTextStyleAnimation(value: boolean | undefined): this {
        throw new Error("Unimplemented method disableTextStyleAnimation")
    }
    defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        throw new Error("Unimplemented method defaultTextStyle")
    }
    onChange(value: OnTextPickerChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        throw new Error("Unimplemented method onScrollStop")
    }
    onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        throw new Error("Unimplemented method onEnterSelectedArea")
    }
    selectedIndex(value: number | Array<number> | undefined): this {
        throw new Error("Unimplemented method selectedIndex")
    }
    divider(value: DividerOptions | undefined): this {
        throw new Error("Unimplemented method divider")
    }
    gradientHeight(value: Dimension | undefined): this {
        throw new Error("Unimplemented method gradientHeight")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error("Unimplemented method digitalCrownSensitivity")
    }
    _onChangeEvent_selected(callback_: ((selected: number | Array<number>) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selected")
    }
    _onChangeEvent_value(callback_: ((value: ResourceStr | Array<ResourceStr>) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_value")
    }
    attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkTextPickerStyle extends ArkCommonMethodStyle implements TextPickerAttribute {
    defaultPickerItemHeight_value?: number | string | undefined
    canLoop_value?: boolean | undefined
    disappearTextStyle_value?: PickerTextStyle | undefined
    textStyle_value?: PickerTextStyle | undefined
    selectedTextStyle_value?: PickerTextStyle | undefined
    disableTextStyleAnimation_value?: boolean | undefined
    defaultTextStyle_value?: TextPickerTextStyle | undefined
    onChange_value?: OnTextPickerChangeCallback | undefined
    onScrollStop_value?: TextPickerScrollStopCallback | undefined
    onEnterSelectedArea_value?: TextPickerEnterSelectedAreaCallback | undefined
    selectedIndex_value?: number | Array<number> | undefined
    divider_value?: DividerOptions | undefined
    gradientHeight_value?: Dimension | undefined
    enableHapticFeedback_value?: boolean | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    attributeModifier_value?: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined
    public defaultPickerItemHeight(value: number | string | undefined): this {
        return this
    }
    public canLoop(value: boolean | undefined): this {
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    public disableTextStyleAnimation(value: boolean | undefined): this {
        return this
    }
    public defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        return this
    }
    public onChange(value: OnTextPickerChangeCallback | undefined): this {
        return this
    }
    public onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        return this
    }
    public onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        return this
    }
    public selectedIndex(value: number | Array<number> | undefined): this {
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        return this
    }
    public gradientHeight(value: Dimension | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: number | Array<number>) => void)): void {
        throw new Error("Unimplemented")
    }
    public _onChangeEvent_value(callback_: ((value: ResourceStr | Array<ResourceStr>) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TextPickerAttribute): void {
        super.apply(target)
        if (this.defaultPickerItemHeight_value !== undefined)
            target.defaultPickerItemHeight(this.defaultPickerItemHeight_value!)
        if (this.canLoop_value !== undefined)
            target.canLoop(this.canLoop_value!)
        if (this.disappearTextStyle_value !== undefined)
            target.disappearTextStyle(this.disappearTextStyle_value!)
        if (this.textStyle_value !== undefined)
            target.textStyle(this.textStyle_value!)
        if (this.selectedTextStyle_value !== undefined)
            target.selectedTextStyle(this.selectedTextStyle_value!)
        if (this.disableTextStyleAnimation_value !== undefined)
            target.disableTextStyleAnimation(this.disableTextStyleAnimation_value!)
        if (this.defaultTextStyle_value !== undefined)
            target.defaultTextStyle(this.defaultTextStyle_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.onScrollStop_value !== undefined)
            target.onScrollStop(this.onScrollStop_value!)
        if (this.onEnterSelectedArea_value !== undefined)
            target.onEnterSelectedArea(this.onEnterSelectedArea_value!)
        if (this.selectedIndex_value !== undefined)
            target.selectedIndex(this.selectedIndex_value!)
        if (this.divider_value !== undefined)
            target.divider(this.divider_value!)
        if (this.gradientHeight_value !== undefined)
            target.gradientHeight(this.gradientHeight_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
        if (this.digitalCrownSensitivity_value !== undefined)
            target.digitalCrownSensitivity(this.digitalCrownSensitivity_value!)
    }
}
export interface TextPickerResult {
    value: string | Array<string>;
    index: number | Array<number>;
}
export interface TextPickerDialogOptions extends TextPickerOptions {
    defaultPickerItemHeight?: number | string;
    canLoop?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    disableTextStyleAnimation?: boolean;
    defaultTextStyle?: TextPickerTextStyle;
    onAccept?: ((value: TextPickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value: TextPickerResult) => void);
    onScrollStop?: ((value: TextPickerResult) => void);
    onEnterSelectedArea?: ((value: TextPickerResult) => void);
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
}

export class ArkTextPickerComponent extends ArkCommonMethodComponent implements TextPickerAttribute {
    getPeer(): ArkTextPickerPeer {
        return (this.peer as ArkTextPickerPeer)
    }
    public setTextPickerOptions(options?: TextPickerOptions): this {
        if (this.checkPriority("setTextPickerOptions")) {
            const options_casted = options as (TextPickerOptions | undefined)
            this.getPeer()?.setTextPickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public defaultPickerItemHeight(value: number | string | undefined): this {
        if (this.checkPriority("defaultPickerItemHeight")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.setDefaultPickerItemHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public canLoop(value: boolean | undefined): this {
        if (this.checkPriority("canLoop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setCanLoopAttribute(value_casted)
            return this
        }
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("disappearTextStyle")) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setDisappearTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("textStyle")) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("selectedTextStyle")) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setSelectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public disableTextStyleAnimation(value: boolean | undefined): this {
        if (this.checkPriority("disableTextStyleAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDisableTextStyleAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        if (this.checkPriority("defaultTextStyle")) {
            const value_casted = value as (TextPickerTextStyle | undefined)
            this.getPeer()?.setDefaultTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnTextPickerChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnTextPickerChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as (TextPickerScrollStopCallback | undefined)
            this.getPeer()?.setOnScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    public onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        if (this.checkPriority("onEnterSelectedArea")) {
            const value_casted = value as (TextPickerEnterSelectedAreaCallback | undefined)
            this.getPeer()?.setOnEnterSelectedAreaAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedIndex(value: number | Array<number> | undefined): this {
        if (this.checkPriority("selectedIndex")) {
            const value_casted = value as (number | Array<number> | undefined)
            this.getPeer()?.setSelectedIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerOptions | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public gradientHeight(value: Dimension | undefined): this {
        if (this.checkPriority("gradientHeight")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setGradientHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority("digitalCrownSensitivity")) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: number | Array<number>) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback__casted = callback_ as (((selected: number | Array<number>) => void))
            this.getPeer()?.set_onChangeEvent_selectedAttribute(callback__casted)
            return
        }
        return
    }
    public _onChangeEvent_value(callback_: ((value: ResourceStr | Array<ResourceStr>) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback__casted = callback_ as (((value: ResourceStr | Array<ResourceStr>) => void))
            this.getPeer()?.set_onChangeEvent_valueAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTextPickerStyle(receiver: TextPickerAttribute, modifier: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTextPickerStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("TextPicker")
// export function TextPicker(
//     options?: TextPickerOptions,
//     @memo
//     content_?: () => void,
// ): TextPickerAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function TextPicker(
    @memo
    style: ((attributes: TextPickerAttribute) => void) | undefined,
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
        withTextPickerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkTextPickerSet extends ArkCommonMethodSet implements TextPickerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _defaultPickerItemHeight_flag?: boolean
    _defaultPickerItemHeight0_value?: number | string | undefined
    _canLoop_flag?: boolean
    _canLoop0_value?: boolean | undefined
    _disappearTextStyle_flag?: boolean
    _disappearTextStyle0_value?: PickerTextStyle | undefined
    _textStyle_flag?: boolean
    _textStyle0_value?: PickerTextStyle | undefined
    _selectedTextStyle_flag?: boolean
    _selectedTextStyle0_value?: PickerTextStyle | undefined
    _disableTextStyleAnimation_flag?: boolean
    _disableTextStyleAnimation0_value?: boolean | undefined
    _defaultTextStyle_flag?: boolean
    _defaultTextStyle0_value?: TextPickerTextStyle | undefined
    _onChange_flag?: boolean
    _onChange0_value?: OnTextPickerChangeCallback | undefined
    _onScrollStop_flag?: boolean
    _onScrollStop0_value?: TextPickerScrollStopCallback | undefined
    _onEnterSelectedArea_flag?: boolean
    _onEnterSelectedArea0_value?: TextPickerEnterSelectedAreaCallback | undefined
    _selectedIndex_flag?: boolean
    _selectedIndex0_value?: number | Array<number> | undefined
    _divider_flag?: boolean
    _divider0_value?: DividerOptions | undefined
    _gradientHeight_flag?: boolean
    _gradientHeight0_value?: Dimension | undefined
    _enableHapticFeedback_flag?: boolean
    _enableHapticFeedback0_value?: boolean | undefined
    _digitalCrownSensitivity_flag?: boolean
    _digitalCrownSensitivity0_value?: CrownSensitivity | undefined
    __onChangeEvent_selected_flag?: boolean
    __onChangeEvent_selected0_value?: ((selected: number | Array<number>) => void)
    __onChangeEvent_value_flag?: boolean
    __onChangeEvent_value0_value?: ((value: ResourceStr | Array<ResourceStr>) => void)
    applyModifierPatch(component: TextPickerAttribute): void {
        if (this._defaultPickerItemHeight_flag)
            component.defaultPickerItemHeight((this._defaultPickerItemHeight0_value as number | string | undefined))
        if (this._canLoop_flag)
            component.canLoop((this._canLoop0_value as boolean | undefined))
        if (this._disappearTextStyle_flag)
            component.disappearTextStyle((this._disappearTextStyle0_value as PickerTextStyle | undefined))
        if (this._textStyle_flag)
            component.textStyle((this._textStyle0_value as PickerTextStyle | undefined))
        if (this._selectedTextStyle_flag)
            component.selectedTextStyle((this._selectedTextStyle0_value as PickerTextStyle | undefined))
        if (this._disableTextStyleAnimation_flag)
            component.disableTextStyleAnimation((this._disableTextStyleAnimation0_value as boolean | undefined))
        if (this._defaultTextStyle_flag)
            component.defaultTextStyle((this._defaultTextStyle0_value as TextPickerTextStyle | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as OnTextPickerChangeCallback | undefined))
        if (this._onScrollStop_flag)
            component.onScrollStop((this._onScrollStop0_value as TextPickerScrollStopCallback | undefined))
        if (this._onEnterSelectedArea_flag)
            component.onEnterSelectedArea((this._onEnterSelectedArea0_value as TextPickerEnterSelectedAreaCallback | undefined))
        if (this._selectedIndex_flag)
            component.selectedIndex((this._selectedIndex0_value as number | Array<number> | undefined))
        if (this._divider_flag)
            component.divider((this._divider0_value as DividerOptions | undefined))
        if (this._gradientHeight_flag)
            component.gradientHeight((this._gradientHeight0_value as Dimension | undefined))
        if (this._enableHapticFeedback_flag)
            component.enableHapticFeedback((this._enableHapticFeedback0_value as boolean | undefined))
        if (this._digitalCrownSensitivity_flag)
            component.digitalCrownSensitivity((this._digitalCrownSensitivity0_value as CrownSensitivity | undefined))
    }
    public defaultPickerItemHeight(value: number | string | undefined): this {
        this._defaultPickerItemHeight_flag = true
        this._defaultPickerItemHeight0_value = value
        return this
    }
    public canLoop(value: boolean | undefined): this {
        this._canLoop_flag = true
        this._canLoop0_value = value
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        this._disappearTextStyle_flag = true
        this._disappearTextStyle0_value = value
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        this._textStyle_flag = true
        this._textStyle0_value = value
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        this._selectedTextStyle_flag = true
        this._selectedTextStyle0_value = value
        return this
    }
    public disableTextStyleAnimation(value: boolean | undefined): this {
        this._disableTextStyleAnimation_flag = true
        this._disableTextStyleAnimation0_value = value
        return this
    }
    public defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        this._defaultTextStyle_flag = true
        this._defaultTextStyle0_value = value
        return this
    }
    public onChange(value: OnTextPickerChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        this._onScrollStop_flag = true
        this._onScrollStop0_value = value
        return this
    }
    public onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        this._onEnterSelectedArea_flag = true
        this._onEnterSelectedArea0_value = value
        return this
    }
    public selectedIndex(value: number | Array<number> | undefined): this {
        this._selectedIndex_flag = true
        this._selectedIndex0_value = value
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        this._divider_flag = true
        this._divider0_value = value
        return this
    }
    public gradientHeight(value: Dimension | undefined): this {
        this._gradientHeight_flag = true
        this._gradientHeight0_value = value
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        this._enableHapticFeedback_flag = true
        this._enableHapticFeedback0_value = value
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        this._digitalCrownSensitivity_flag = true
        this._digitalCrownSensitivity0_value = value
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: number | Array<number>) => void)): void {
    }
    public _onChangeEvent_value(callback_: ((value: ResourceStr | Array<ResourceStr>) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class TextPickerDialog_serializer {
    public static write(buffer: SerializerBase, value: TextPickerDialog): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextPickerDialog {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextPickerDialogInternal.fromPtr(ptr)
    }
}
export class TextCascadePickerRangeContent_serializer {
    public static write(buffer: SerializerBase, value: TextCascadePickerRangeContent): void {
        let valueSerializer : SerializerBase = buffer
        const value_text  = value.text
        let value_text_type : int32 = RuntimeType.UNDEFINED
        value_text_type = runtimeType(value_text)
        if (RuntimeType.STRING == value_text_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_text_0  = value_text as string
            valueSerializer.writeString(value_text_0)
        }
        else if (RuntimeType.OBJECT == value_text_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_text_1  = value_text as Resource
            Resource_serializer.write(valueSerializer, value_text_1)
        }
        const value_children  = value.children
        let value_children_type : int32 = RuntimeType.UNDEFINED
        value_children_type = runtimeType(value_children)
        valueSerializer.writeInt8((value_children_type).toChar())
        if ((value_children_type) != (RuntimeType.UNDEFINED)) {
            const value_children_value  = value_children!
            valueSerializer.writeInt32((value_children_value.length).toInt())
            for (let value_children_value_counter_i = 0; value_children_value_counter_i < value_children_value.length; value_children_value_counter_i++) {
                const value_children_value_element : TextCascadePickerRangeContent = value_children_value[value_children_value_counter_i]
                TextCascadePickerRangeContent_serializer.write(valueSerializer, value_children_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): TextCascadePickerRangeContent {
        let valueDeserializer : DeserializerBase = buffer
        const text_buf_selector : int32 = valueDeserializer.readInt8()
        let text_buf : string | Resource | undefined
        if (text_buf_selector == (0).toChar()) {
            text_buf = (valueDeserializer.readString() as string)
        }
        else if (text_buf_selector == (1).toChar()) {
            text_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for text_buf has to be chosen through deserialisation.")
        }
        const text_result : string | Resource = (text_buf as string | Resource)
        const children_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let children_buf : Array<TextCascadePickerRangeContent> | undefined
        if ((children_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const children_buf__length : int32 = valueDeserializer.readInt32()
            let children_buf_ : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(children_buf__length)
            for (let children_buf__i = 0; children_buf__i < children_buf__length; children_buf__i++) {
                children_buf_[children_buf__i] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            children_buf = children_buf_
        }
        const children_result : Array<TextCascadePickerRangeContent> | undefined = children_buf
        let value : TextCascadePickerRangeContent = ({text: text_result, children: children_result} as TextCascadePickerRangeContent)
        return value
    }
}
export class TextPickerOptions_serializer {
    public static write(buffer: SerializerBase, value: TextPickerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_range  = value.range
        let value_range_type : int32 = RuntimeType.UNDEFINED
        value_range_type = runtimeType(value_range)
        if (((RuntimeType.OBJECT) == (value_range_type)) && (TypeChecker.isArray_String(value_range))) {
            valueSerializer.writeInt8((0).toChar())
            const value_range_0  = value_range as Array<string>
            valueSerializer.writeInt32((value_range_0.length).toInt())
            for (let value_range_0_counter_i = 0; value_range_0_counter_i < value_range_0.length; value_range_0_counter_i++) {
                const value_range_0_element : string = value_range_0[value_range_0_counter_i]
                valueSerializer.writeString(value_range_0_element)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_range_type)) && (TypeChecker.isArray_Array_String(value_range))) {
            valueSerializer.writeInt8((1).toChar())
            const value_range_1  = value_range as Array<Array<string>>
            valueSerializer.writeInt32((value_range_1.length).toInt())
            for (let value_range_1_counter_i = 0; value_range_1_counter_i < value_range_1.length; value_range_1_counter_i++) {
                const value_range_1_element : Array<string> = value_range_1[value_range_1_counter_i]
                valueSerializer.writeInt32((value_range_1_element.length).toInt())
                for (let value_range_1_element_counter_i = 0; value_range_1_element_counter_i < value_range_1_element.length; value_range_1_element_counter_i++) {
                    const value_range_1_element_element : string = value_range_1_element[value_range_1_element_counter_i]
                    valueSerializer.writeString(value_range_1_element_element)
                }
            }
        }
        else if (TypeChecker.isResource(value_range, false, false, false, false, false)) {
            valueSerializer.writeInt8((2).toChar())
            const value_range_2  = value_range as Resource
            Resource_serializer.write(valueSerializer, value_range_2)
        }
        else if (((RuntimeType.OBJECT) == (value_range_type)) && (TypeChecker.isArray_TextPickerRangeContent(value_range))) {
            valueSerializer.writeInt8((3).toChar())
            const value_range_3  = value_range as Array<TextPickerRangeContent>
            valueSerializer.writeInt32((value_range_3.length).toInt())
            for (let value_range_3_counter_i = 0; value_range_3_counter_i < value_range_3.length; value_range_3_counter_i++) {
                const value_range_3_element : TextPickerRangeContent = value_range_3[value_range_3_counter_i]
                TextPickerRangeContent_serializer.write(valueSerializer, value_range_3_element)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_range_type)) && (TypeChecker.isArray_TextCascadePickerRangeContent(value_range))) {
            valueSerializer.writeInt8((4).toChar())
            const value_range_4  = value_range as Array<TextCascadePickerRangeContent>
            valueSerializer.writeInt32((value_range_4.length).toInt())
            for (let value_range_4_counter_i = 0; value_range_4_counter_i < value_range_4.length; value_range_4_counter_i++) {
                const value_range_4_element : TextCascadePickerRangeContent = value_range_4[value_range_4_counter_i]
                TextCascadePickerRangeContent_serializer.write(valueSerializer, value_range_4_element)
            }
        }
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        valueSerializer.writeInt8((value_value_type).toChar())
        if ((value_value_type) != (RuntimeType.UNDEFINED)) {
            const value_value_value  = value_value!
            let value_value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_value_type = runtimeType(value_value_value)
            if ((RuntimeType.STRING == value_value_value_type) || (RuntimeType.OBJECT == value_value_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_value_value_0  = value_value_value as ResourceStr
                let value_value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_value_0_type = runtimeType(value_value_value_0)
                if (RuntimeType.STRING == value_value_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_value_value_0_0  = value_value_value_0 as string
                    valueSerializer.writeString(value_value_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_value_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_value_value_0_1  = value_value_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_value_value_0_1)
                }
            }
            else if (((RuntimeType.OBJECT) == (value_value_value_type)) && (TypeChecker.isArray_ResourceStr(value_value_value))) {
                valueSerializer.writeInt8((1).toChar())
                const value_value_value_1  = value_value_value as Array<ResourceStr>
                valueSerializer.writeInt32((value_value_value_1.length).toInt())
                for (let value_value_value_1_counter_i = 0; value_value_value_1_counter_i < value_value_value_1.length; value_value_value_1_counter_i++) {
                    const value_value_value_1_element : ResourceStr = value_value_value_1[value_value_value_1_counter_i]
                    let value_value_value_1_element_type : int32 = RuntimeType.UNDEFINED
                    value_value_value_1_element_type = runtimeType(value_value_value_1_element)
                    if (RuntimeType.STRING == value_value_value_1_element_type) {
                        valueSerializer.writeInt8((0).toChar())
                        const value_value_value_1_element_0  = value_value_value_1_element as string
                        valueSerializer.writeString(value_value_value_1_element_0)
                    }
                    else if (RuntimeType.OBJECT == value_value_value_1_element_type) {
                        valueSerializer.writeInt8((1).toChar())
                        const value_value_value_1_element_1  = value_value_value_1_element as Resource
                        Resource_serializer.write(valueSerializer, value_value_value_1_element_1)
                    }
                }
            }
        }
        const value_selected  = value.selected
        let value_selected_type : int32 = RuntimeType.UNDEFINED
        value_selected_type = runtimeType(value_selected)
        valueSerializer.writeInt8((value_selected_type).toChar())
        if ((value_selected_type) != (RuntimeType.UNDEFINED)) {
            const value_selected_value  = value_selected!
            let value_selected_value_type : int32 = RuntimeType.UNDEFINED
            value_selected_value_type = runtimeType(value_selected_value)
            if (RuntimeType.NUMBER == value_selected_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_selected_value_0  = value_selected_value as number
                valueSerializer.writeNumber(value_selected_value_0)
            }
            else if (RuntimeType.OBJECT == value_selected_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_selected_value_1  = value_selected_value as Array<number>
                valueSerializer.writeInt32((value_selected_value_1.length).toInt())
                for (let value_selected_value_1_counter_i = 0; value_selected_value_1_counter_i < value_selected_value_1.length; value_selected_value_1_counter_i++) {
                    const value_selected_value_1_element : number = value_selected_value_1[value_selected_value_1_counter_i]
                    valueSerializer.writeNumber(value_selected_value_1_element)
                }
            }
        }
        const value_columnWidths  = value.columnWidths
        let value_columnWidths_type : int32 = RuntimeType.UNDEFINED
        value_columnWidths_type = runtimeType(value_columnWidths)
        valueSerializer.writeInt8((value_columnWidths_type).toChar())
        if ((value_columnWidths_type) != (RuntimeType.UNDEFINED)) {
            const value_columnWidths_value  = value_columnWidths!
            valueSerializer.writeInt32((value_columnWidths_value.length).toInt())
            for (let value_columnWidths_value_counter_i = 0; value_columnWidths_value_counter_i < value_columnWidths_value.length; value_columnWidths_value_counter_i++) {
                const value_columnWidths_value_element : LengthMetrics = value_columnWidths_value[value_columnWidths_value_counter_i]
                LengthMetrics_serializer.write(valueSerializer, value_columnWidths_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): TextPickerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const range_buf_selector : int32 = valueDeserializer.readInt8()
        let range_buf : Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> | undefined
        if (range_buf_selector == (0).toChar()) {
            const range_buf_u_length : int32 = valueDeserializer.readInt32()
            let range_buf_u : Array<string> = new Array<string>(range_buf_u_length)
            for (let range_buf_u_i = 0; range_buf_u_i < range_buf_u_length; range_buf_u_i++) {
                range_buf_u[range_buf_u_i] = (valueDeserializer.readString() as string)
            }
            range_buf = range_buf_u
        }
        else if (range_buf_selector == (1).toChar()) {
            const range_buf_u_length : int32 = valueDeserializer.readInt32()
            let range_buf_u : Array<Array<string>> = new Array<Array<string>>(range_buf_u_length)
            for (let range_buf_u_i = 0; range_buf_u_i < range_buf_u_length; range_buf_u_i++) {
                const range_buf_u_buf_length : int32 = valueDeserializer.readInt32()
                let range_buf_u_buf : Array<string> = new Array<string>(range_buf_u_buf_length)
                for (let range_buf_u_buf_i = 0; range_buf_u_buf_i < range_buf_u_buf_length; range_buf_u_buf_i++) {
                    range_buf_u_buf[range_buf_u_buf_i] = (valueDeserializer.readString() as string)
                }
                range_buf_u[range_buf_u_i] = range_buf_u_buf
            }
            range_buf = range_buf_u
        }
        else if (range_buf_selector == (2).toChar()) {
            range_buf = Resource_serializer.read(valueDeserializer)
        }
        else if (range_buf_selector == (3).toChar()) {
            const range_buf_u_length : int32 = valueDeserializer.readInt32()
            let range_buf_u : Array<TextPickerRangeContent> = new Array<TextPickerRangeContent>(range_buf_u_length)
            for (let range_buf_u_i = 0; range_buf_u_i < range_buf_u_length; range_buf_u_i++) {
                range_buf_u[range_buf_u_i] = TextPickerRangeContent_serializer.read(valueDeserializer)
            }
            range_buf = range_buf_u
        }
        else if (range_buf_selector == (4).toChar()) {
            const range_buf_u_length : int32 = valueDeserializer.readInt32()
            let range_buf_u : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(range_buf_u_length)
            for (let range_buf_u_i = 0; range_buf_u_i < range_buf_u_length; range_buf_u_i++) {
                range_buf_u[range_buf_u_i] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            range_buf = range_buf_u
        }
        else {
            throw new Error("One of the branches for range_buf has to be chosen through deserialisation.")
        }
        const range_result : Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> = (range_buf as Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>)
        const value_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let value_buf : ResourceStr | Array<ResourceStr> | undefined
        if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const value_buf__selector : int32 = valueDeserializer.readInt8()
            let value_buf_ : ResourceStr | Array<ResourceStr> | undefined
            if (value_buf__selector == (0).toChar()) {
                const value_buf__u_selector : int32 = valueDeserializer.readInt8()
                let value_buf__u : string | Resource | undefined
                if (value_buf__u_selector == (0).toChar()) {
                    value_buf__u = (valueDeserializer.readString() as string)
                }
                else if (value_buf__u_selector == (1).toChar()) {
                    value_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for value_buf__u has to be chosen through deserialisation.")
                }
                value_buf_ = (value_buf__u as string | Resource)
            }
            else if (value_buf__selector == (1).toChar()) {
                const value_buf__u_length : int32 = valueDeserializer.readInt32()
                let value_buf__u : Array<ResourceStr> = new Array<ResourceStr>(value_buf__u_length)
                for (let value_buf__u_i = 0; value_buf__u_i < value_buf__u_length; value_buf__u_i++) {
                    const value_buf__u_buf_selector : int32 = valueDeserializer.readInt8()
                    let value_buf__u_buf : string | Resource | undefined
                    if (value_buf__u_buf_selector == (0).toChar()) {
                        value_buf__u_buf = (valueDeserializer.readString() as string)
                    }
                    else if (value_buf__u_buf_selector == (1).toChar()) {
                        value_buf__u_buf = Resource_serializer.read(valueDeserializer)
                    }
                    else {
                        throw new Error("One of the branches for value_buf__u_buf has to be chosen through deserialisation.")
                    }
                    value_buf__u[value_buf__u_i] = (value_buf__u_buf as string | Resource)
                }
                value_buf_ = value_buf__u
            }
            else {
                throw new Error("One of the branches for value_buf_ has to be chosen through deserialisation.")
            }
            value_buf = (value_buf_ as ResourceStr | Array<ResourceStr>)
        }
        const value_result : ResourceStr | Array<ResourceStr> | undefined = value_buf
        const selected_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selected_buf : number | Array<number> | undefined
        if ((selected_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const selected_buf__selector : int32 = valueDeserializer.readInt8()
            let selected_buf_ : number | Array<number> | undefined
            if (selected_buf__selector == (0).toChar()) {
                selected_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (selected_buf__selector == (1).toChar()) {
                const selected_buf__u_length : int32 = valueDeserializer.readInt32()
                let selected_buf__u : Array<number> = new Array<number>(selected_buf__u_length)
                for (let selected_buf__u_i = 0; selected_buf__u_i < selected_buf__u_length; selected_buf__u_i++) {
                    selected_buf__u[selected_buf__u_i] = (valueDeserializer.readNumber() as number)
                }
                selected_buf_ = selected_buf__u
            }
            else {
                throw new Error("One of the branches for selected_buf_ has to be chosen through deserialisation.")
            }
            selected_buf = (selected_buf_ as number | Array<number>)
        }
        const selected_result : number | Array<number> | undefined = selected_buf
        const columnWidths_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let columnWidths_buf : Array<LengthMetrics> | undefined
        if ((columnWidths_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const columnWidths_buf__length : int32 = valueDeserializer.readInt32()
            let columnWidths_buf_ : Array<LengthMetrics> = new Array<LengthMetrics>(columnWidths_buf__length)
            for (let columnWidths_buf__i = 0; columnWidths_buf__i < columnWidths_buf__length; columnWidths_buf__i++) {
                columnWidths_buf_[columnWidths_buf__i] = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            columnWidths_buf = columnWidths_buf_
        }
        const columnWidths_result : Array<LengthMetrics> | undefined = columnWidths_buf
        let value : TextPickerOptions = ({range: range_result, value: value_result, selected: selected_result, columnWidths: columnWidths_result} as TextPickerOptions)
        return value
    }
}
export class TextPickerRangeContent_serializer {
    public static write(buffer: SerializerBase, value: TextPickerRangeContent): void {
        let valueSerializer : SerializerBase = buffer
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        if (RuntimeType.STRING == value_icon_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_icon_0  = value_icon as string
            valueSerializer.writeString(value_icon_0)
        }
        else if (RuntimeType.OBJECT == value_icon_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_icon_1  = value_icon as Resource
            Resource_serializer.write(valueSerializer, value_icon_1)
        }
        const value_text  = value.text
        let value_text_type : int32 = RuntimeType.UNDEFINED
        value_text_type = runtimeType(value_text)
        valueSerializer.writeInt8((value_text_type).toChar())
        if ((value_text_type) != (RuntimeType.UNDEFINED)) {
            const value_text_value  = value_text!
            let value_text_value_type : int32 = RuntimeType.UNDEFINED
            value_text_value_type = runtimeType(value_text_value)
            if (RuntimeType.STRING == value_text_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_text_value_0  = value_text_value as string
                valueSerializer.writeString(value_text_value_0)
            }
            else if (RuntimeType.OBJECT == value_text_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_text_value_1  = value_text_value as Resource
                Resource_serializer.write(valueSerializer, value_text_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): TextPickerRangeContent {
        let valueDeserializer : DeserializerBase = buffer
        const icon_buf_selector : int32 = valueDeserializer.readInt8()
        let icon_buf : string | Resource | undefined
        if (icon_buf_selector == (0).toChar()) {
            icon_buf = (valueDeserializer.readString() as string)
        }
        else if (icon_buf_selector == (1).toChar()) {
            icon_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for icon_buf has to be chosen through deserialisation.")
        }
        const icon_result : string | Resource = (icon_buf as string | Resource)
        const text_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let text_buf : string | Resource | undefined
        if ((text_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const text_buf__selector : int32 = valueDeserializer.readInt8()
            let text_buf_ : string | Resource | undefined
            if (text_buf__selector == (0).toChar()) {
                text_buf_ = (valueDeserializer.readString() as string)
            }
            else if (text_buf__selector == (1).toChar()) {
                text_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for text_buf_ has to be chosen through deserialisation.")
            }
            text_buf = (text_buf_ as string | Resource)
        }
        const text_result : string | Resource | undefined = text_buf
        let value : TextPickerRangeContent = ({icon: icon_result, text: text_result} as TextPickerRangeContent)
        return value
    }
}
export class TextPickerResult_serializer {
    public static write(buffer: SerializerBase, value: TextPickerResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        if (RuntimeType.STRING == value_value_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_value_1  = value_value as Array<string>
            valueSerializer.writeInt32((value_value_1.length).toInt())
            for (let value_value_1_counter_i = 0; value_value_1_counter_i < value_value_1.length; value_value_1_counter_i++) {
                const value_value_1_element : string = value_value_1[value_value_1_counter_i]
                valueSerializer.writeString(value_value_1_element)
            }
        }
        const value_index  = value.index
        let value_index_type : int32 = RuntimeType.UNDEFINED
        value_index_type = runtimeType(value_index)
        if (RuntimeType.NUMBER == value_index_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_index_0  = value_index as number
            valueSerializer.writeNumber(value_index_0)
        }
        else if (RuntimeType.OBJECT == value_index_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_index_1  = value_index as Array<number>
            valueSerializer.writeInt32((value_index_1.length).toInt())
            for (let value_index_1_counter_i = 0; value_index_1_counter_i < value_index_1.length; value_index_1_counter_i++) {
                const value_index_1_element : number = value_index_1[value_index_1_counter_i]
                valueSerializer.writeNumber(value_index_1_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): TextPickerResult {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Array<string> | undefined
        if (value_buf_selector == (0).toChar()) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == (1).toChar()) {
            const value_buf_u_length : int32 = valueDeserializer.readInt32()
            let value_buf_u : Array<string> = new Array<string>(value_buf_u_length)
            for (let value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
                value_buf_u[value_buf_u_i] = (valueDeserializer.readString() as string)
            }
            value_buf = value_buf_u
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : string | Array<string> = (value_buf as string | Array<string>)
        const index_buf_selector : int32 = valueDeserializer.readInt8()
        let index_buf : number | Array<number> | undefined
        if (index_buf_selector == (0).toChar()) {
            index_buf = (valueDeserializer.readNumber() as number)
        }
        else if (index_buf_selector == (1).toChar()) {
            const index_buf_u_length : int32 = valueDeserializer.readInt32()
            let index_buf_u : Array<number> = new Array<number>(index_buf_u_length)
            for (let index_buf_u_i = 0; index_buf_u_i < index_buf_u_length; index_buf_u_i++) {
                index_buf_u[index_buf_u_i] = (valueDeserializer.readNumber() as number)
            }
            index_buf = index_buf_u
        }
        else {
            throw new Error("One of the branches for index_buf has to be chosen through deserialisation.")
        }
        const index_result : number | Array<number> = (index_buf as number | Array<number>)
        let value : TextPickerResult = ({value: value_result, index: index_result} as TextPickerResult)
        return value
    }
}
export class DividerOptions_serializer {
    public static write(buffer: SerializerBase, value: DividerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_strokeWidth  = value.strokeWidth
        let value_strokeWidth_type : int32 = RuntimeType.UNDEFINED
        value_strokeWidth_type = runtimeType(value_strokeWidth)
        valueSerializer.writeInt8((value_strokeWidth_type).toChar())
        if ((value_strokeWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeWidth_value  = value_strokeWidth!
            let value_strokeWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_strokeWidth_value_type = runtimeType(value_strokeWidth_value)
            if (RuntimeType.STRING == value_strokeWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_strokeWidth_value_0  = value_strokeWidth_value as string
                valueSerializer.writeString(value_strokeWidth_value_0)
            }
            else if (RuntimeType.NUMBER == value_strokeWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_strokeWidth_value_1  = value_strokeWidth_value as number
                valueSerializer.writeNumber(value_strokeWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value_strokeWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_strokeWidth_value_2  = value_strokeWidth_value as Resource
                Resource_serializer.write(valueSerializer, value_strokeWidth_value_2)
            }
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_startMargin  = value.startMargin
        let value_startMargin_type : int32 = RuntimeType.UNDEFINED
        value_startMargin_type = runtimeType(value_startMargin)
        valueSerializer.writeInt8((value_startMargin_type).toChar())
        if ((value_startMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_startMargin_value  = value_startMargin!
            let value_startMargin_value_type : int32 = RuntimeType.UNDEFINED
            value_startMargin_value_type = runtimeType(value_startMargin_value)
            if (RuntimeType.STRING == value_startMargin_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_startMargin_value_0  = value_startMargin_value as string
                valueSerializer.writeString(value_startMargin_value_0)
            }
            else if (RuntimeType.NUMBER == value_startMargin_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_startMargin_value_1  = value_startMargin_value as number
                valueSerializer.writeNumber(value_startMargin_value_1)
            }
            else if (RuntimeType.OBJECT == value_startMargin_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_startMargin_value_2  = value_startMargin_value as Resource
                Resource_serializer.write(valueSerializer, value_startMargin_value_2)
            }
        }
        const value_endMargin  = value.endMargin
        let value_endMargin_type : int32 = RuntimeType.UNDEFINED
        value_endMargin_type = runtimeType(value_endMargin)
        valueSerializer.writeInt8((value_endMargin_type).toChar())
        if ((value_endMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_endMargin_value  = value_endMargin!
            let value_endMargin_value_type : int32 = RuntimeType.UNDEFINED
            value_endMargin_value_type = runtimeType(value_endMargin_value)
            if (RuntimeType.STRING == value_endMargin_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_endMargin_value_0  = value_endMargin_value as string
                valueSerializer.writeString(value_endMargin_value_0)
            }
            else if (RuntimeType.NUMBER == value_endMargin_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_endMargin_value_1  = value_endMargin_value as number
                valueSerializer.writeNumber(value_endMargin_value_1)
            }
            else if (RuntimeType.OBJECT == value_endMargin_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_endMargin_value_2  = value_endMargin_value as Resource
                Resource_serializer.write(valueSerializer, value_endMargin_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): DividerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const strokeWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidth_buf : Dimension | undefined
        if ((strokeWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const strokeWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let strokeWidth_buf_ : string | number | Resource | undefined
            if (strokeWidth_buf__selector == (0).toChar()) {
                strokeWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else if (strokeWidth_buf__selector == (1).toChar()) {
                strokeWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (strokeWidth_buf__selector == (2).toChar()) {
                strokeWidth_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for strokeWidth_buf_ has to be chosen through deserialisation.")
            }
            strokeWidth_buf = (strokeWidth_buf_ as string | number | Resource)
        }
        const strokeWidth_result : Dimension | undefined = strokeWidth_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const startMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMargin_buf : Dimension | undefined
        if ((startMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const startMargin_buf__selector : int32 = valueDeserializer.readInt8()
            let startMargin_buf_ : string | number | Resource | undefined
            if (startMargin_buf__selector == (0).toChar()) {
                startMargin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (startMargin_buf__selector == (1).toChar()) {
                startMargin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (startMargin_buf__selector == (2).toChar()) {
                startMargin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for startMargin_buf_ has to be chosen through deserialisation.")
            }
            startMargin_buf = (startMargin_buf_ as string | number | Resource)
        }
        const startMargin_result : Dimension | undefined = startMargin_buf
        const endMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMargin_buf : Dimension | undefined
        if ((endMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const endMargin_buf__selector : int32 = valueDeserializer.readInt8()
            let endMargin_buf_ : string | number | Resource | undefined
            if (endMargin_buf__selector == (0).toChar()) {
                endMargin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (endMargin_buf__selector == (1).toChar()) {
                endMargin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (endMargin_buf__selector == (2).toChar()) {
                endMargin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for endMargin_buf_ has to be chosen through deserialisation.")
            }
            endMargin_buf = (endMargin_buf_ as string | number | Resource)
        }
        const endMargin_result : Dimension | undefined = endMargin_buf
        let value : DividerOptions = ({strokeWidth: strokeWidth_result, color: color_result, startMargin: startMargin_result, endMargin: endMargin_result} as DividerOptions)
        return value
    }
}
export class TextPickerTextStyle_serializer {
    public static write(buffer: SerializerBase, value: TextPickerTextStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_font  = value.font
        let value_font_type : int32 = RuntimeType.UNDEFINED
        value_font_type = runtimeType(value_font)
        valueSerializer.writeInt8((value_font_type).toChar())
        if ((value_font_type) != (RuntimeType.UNDEFINED)) {
            const value_font_value  = value_font!
            Font_serializer.write(valueSerializer, value_font_value)
        }
        const value_minFontSize  = value.minFontSize
        let value_minFontSize_type : int32 = RuntimeType.UNDEFINED
        value_minFontSize_type = runtimeType(value_minFontSize)
        valueSerializer.writeInt8((value_minFontSize_type).toChar())
        if ((value_minFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_minFontSize_value  = value_minFontSize!
            let value_minFontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_minFontSize_value_type = runtimeType(value_minFontSize_value)
            if (RuntimeType.NUMBER == value_minFontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_minFontSize_value_0  = value_minFontSize_value as number
                valueSerializer.writeNumber(value_minFontSize_value_0)
            }
            else if (RuntimeType.STRING == value_minFontSize_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_minFontSize_value_1  = value_minFontSize_value as string
                valueSerializer.writeString(value_minFontSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_minFontSize_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_minFontSize_value_2  = value_minFontSize_value as Resource
                Resource_serializer.write(valueSerializer, value_minFontSize_value_2)
            }
        }
        const value_maxFontSize  = value.maxFontSize
        let value_maxFontSize_type : int32 = RuntimeType.UNDEFINED
        value_maxFontSize_type = runtimeType(value_maxFontSize)
        valueSerializer.writeInt8((value_maxFontSize_type).toChar())
        if ((value_maxFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_maxFontSize_value  = value_maxFontSize!
            let value_maxFontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_maxFontSize_value_type = runtimeType(value_maxFontSize_value)
            if (RuntimeType.NUMBER == value_maxFontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_maxFontSize_value_0  = value_maxFontSize_value as number
                valueSerializer.writeNumber(value_maxFontSize_value_0)
            }
            else if (RuntimeType.STRING == value_maxFontSize_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_maxFontSize_value_1  = value_maxFontSize_value as string
                valueSerializer.writeString(value_maxFontSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_maxFontSize_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_maxFontSize_value_2  = value_maxFontSize_value as Resource
                Resource_serializer.write(valueSerializer, value_maxFontSize_value_2)
            }
        }
        const value_overflow  = value.overflow
        let value_overflow_type : int32 = RuntimeType.UNDEFINED
        value_overflow_type = runtimeType(value_overflow)
        valueSerializer.writeInt8((value_overflow_type).toChar())
        if ((value_overflow_type) != (RuntimeType.UNDEFINED)) {
            const value_overflow_value  = (value_overflow as TextOverflow)
            valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_overflow_value))
        }
    }
    public static read(buffer: DeserializerBase): TextPickerTextStyle {
        let valueDeserializer : DeserializerBase = buffer
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const font_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let font_buf : Font | undefined
        if ((font_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            font_buf = Font_serializer.read(valueDeserializer)
        }
        const font_result : Font | undefined = font_buf
        const minFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minFontSize_buf : number | string | Resource | undefined
        if ((minFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const minFontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let minFontSize_buf_ : number | string | Resource | undefined
            if (minFontSize_buf__selector == (0).toChar()) {
                minFontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (minFontSize_buf__selector == (1).toChar()) {
                minFontSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (minFontSize_buf__selector == (2).toChar()) {
                minFontSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for minFontSize_buf_ has to be chosen through deserialisation.")
            }
            minFontSize_buf = (minFontSize_buf_ as number | string | Resource)
        }
        const minFontSize_result : number | string | Resource | undefined = minFontSize_buf
        const maxFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxFontSize_buf : number | string | Resource | undefined
        if ((maxFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const maxFontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let maxFontSize_buf_ : number | string | Resource | undefined
            if (maxFontSize_buf__selector == (0).toChar()) {
                maxFontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (maxFontSize_buf__selector == (1).toChar()) {
                maxFontSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (maxFontSize_buf__selector == (2).toChar()) {
                maxFontSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for maxFontSize_buf_ has to be chosen through deserialisation.")
            }
            maxFontSize_buf = (maxFontSize_buf_ as number | string | Resource)
        }
        const maxFontSize_result : number | string | Resource | undefined = maxFontSize_buf
        const overflow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflow_buf : TextOverflow | undefined
        if ((overflow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            overflow_buf = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
        }
        const overflow_result : TextOverflow | undefined = overflow_buf
        let value : TextPickerTextStyle = ({color: color_result, font: font_result, minFontSize: minFontSize_result, maxFontSize: maxFontSize_result, overflow: overflow_result} as TextPickerTextStyle)
        return value
    }
}
export class TextPickerDialogOptions_serializer {
    public static write(buffer: SerializerBase, value: TextPickerDialogOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_range  = value.range
        let value_range_type : int32 = RuntimeType.UNDEFINED
        value_range_type = runtimeType(value_range)
        if (((RuntimeType.OBJECT) == (value_range_type)) && (TypeChecker.isArray_String(value_range))) {
            valueSerializer.writeInt8((0).toChar())
            const value_range_0  = value_range as Array<string>
            valueSerializer.writeInt32((value_range_0.length).toInt())
            for (let value_range_0_counter_i = 0; value_range_0_counter_i < value_range_0.length; value_range_0_counter_i++) {
                const value_range_0_element : string = value_range_0[value_range_0_counter_i]
                valueSerializer.writeString(value_range_0_element)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_range_type)) && (TypeChecker.isArray_Array_String(value_range))) {
            valueSerializer.writeInt8((1).toChar())
            const value_range_1  = value_range as Array<Array<string>>
            valueSerializer.writeInt32((value_range_1.length).toInt())
            for (let value_range_1_counter_i = 0; value_range_1_counter_i < value_range_1.length; value_range_1_counter_i++) {
                const value_range_1_element : Array<string> = value_range_1[value_range_1_counter_i]
                valueSerializer.writeInt32((value_range_1_element.length).toInt())
                for (let value_range_1_element_counter_i = 0; value_range_1_element_counter_i < value_range_1_element.length; value_range_1_element_counter_i++) {
                    const value_range_1_element_element : string = value_range_1_element[value_range_1_element_counter_i]
                    valueSerializer.writeString(value_range_1_element_element)
                }
            }
        }
        else if (TypeChecker.isResource(value_range, false, false, false, false, false)) {
            valueSerializer.writeInt8((2).toChar())
            const value_range_2  = value_range as Resource
            Resource_serializer.write(valueSerializer, value_range_2)
        }
        else if (((RuntimeType.OBJECT) == (value_range_type)) && (TypeChecker.isArray_TextPickerRangeContent(value_range))) {
            valueSerializer.writeInt8((3).toChar())
            const value_range_3  = value_range as Array<TextPickerRangeContent>
            valueSerializer.writeInt32((value_range_3.length).toInt())
            for (let value_range_3_counter_i = 0; value_range_3_counter_i < value_range_3.length; value_range_3_counter_i++) {
                const value_range_3_element : TextPickerRangeContent = value_range_3[value_range_3_counter_i]
                TextPickerRangeContent_serializer.write(valueSerializer, value_range_3_element)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_range_type)) && (TypeChecker.isArray_TextCascadePickerRangeContent(value_range))) {
            valueSerializer.writeInt8((4).toChar())
            const value_range_4  = value_range as Array<TextCascadePickerRangeContent>
            valueSerializer.writeInt32((value_range_4.length).toInt())
            for (let value_range_4_counter_i = 0; value_range_4_counter_i < value_range_4.length; value_range_4_counter_i++) {
                const value_range_4_element : TextCascadePickerRangeContent = value_range_4[value_range_4_counter_i]
                TextCascadePickerRangeContent_serializer.write(valueSerializer, value_range_4_element)
            }
        }
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        valueSerializer.writeInt8((value_value_type).toChar())
        if ((value_value_type) != (RuntimeType.UNDEFINED)) {
            const value_value_value  = value_value!
            let value_value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_value_type = runtimeType(value_value_value)
            if ((RuntimeType.STRING == value_value_value_type) || (RuntimeType.OBJECT == value_value_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_value_value_0  = value_value_value as ResourceStr
                let value_value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_value_0_type = runtimeType(value_value_value_0)
                if (RuntimeType.STRING == value_value_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_value_value_0_0  = value_value_value_0 as string
                    valueSerializer.writeString(value_value_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_value_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_value_value_0_1  = value_value_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_value_value_0_1)
                }
            }
            else if (((RuntimeType.OBJECT) == (value_value_value_type)) && (TypeChecker.isArray_ResourceStr(value_value_value))) {
                valueSerializer.writeInt8((1).toChar())
                const value_value_value_1  = value_value_value as Array<ResourceStr>
                valueSerializer.writeInt32((value_value_value_1.length).toInt())
                for (let value_value_value_1_counter_i = 0; value_value_value_1_counter_i < value_value_value_1.length; value_value_value_1_counter_i++) {
                    const value_value_value_1_element : ResourceStr = value_value_value_1[value_value_value_1_counter_i]
                    let value_value_value_1_element_type : int32 = RuntimeType.UNDEFINED
                    value_value_value_1_element_type = runtimeType(value_value_value_1_element)
                    if (RuntimeType.STRING == value_value_value_1_element_type) {
                        valueSerializer.writeInt8((0).toChar())
                        const value_value_value_1_element_0  = value_value_value_1_element as string
                        valueSerializer.writeString(value_value_value_1_element_0)
                    }
                    else if (RuntimeType.OBJECT == value_value_value_1_element_type) {
                        valueSerializer.writeInt8((1).toChar())
                        const value_value_value_1_element_1  = value_value_value_1_element as Resource
                        Resource_serializer.write(valueSerializer, value_value_value_1_element_1)
                    }
                }
            }
        }
        const value_selected  = value.selected
        let value_selected_type : int32 = RuntimeType.UNDEFINED
        value_selected_type = runtimeType(value_selected)
        valueSerializer.writeInt8((value_selected_type).toChar())
        if ((value_selected_type) != (RuntimeType.UNDEFINED)) {
            const value_selected_value  = value_selected!
            let value_selected_value_type : int32 = RuntimeType.UNDEFINED
            value_selected_value_type = runtimeType(value_selected_value)
            if (RuntimeType.NUMBER == value_selected_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_selected_value_0  = value_selected_value as number
                valueSerializer.writeNumber(value_selected_value_0)
            }
            else if (RuntimeType.OBJECT == value_selected_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_selected_value_1  = value_selected_value as Array<number>
                valueSerializer.writeInt32((value_selected_value_1.length).toInt())
                for (let value_selected_value_1_counter_i = 0; value_selected_value_1_counter_i < value_selected_value_1.length; value_selected_value_1_counter_i++) {
                    const value_selected_value_1_element : number = value_selected_value_1[value_selected_value_1_counter_i]
                    valueSerializer.writeNumber(value_selected_value_1_element)
                }
            }
        }
        const value_columnWidths  = value.columnWidths
        let value_columnWidths_type : int32 = RuntimeType.UNDEFINED
        value_columnWidths_type = runtimeType(value_columnWidths)
        valueSerializer.writeInt8((value_columnWidths_type).toChar())
        if ((value_columnWidths_type) != (RuntimeType.UNDEFINED)) {
            const value_columnWidths_value  = value_columnWidths!
            valueSerializer.writeInt32((value_columnWidths_value.length).toInt())
            for (let value_columnWidths_value_counter_i = 0; value_columnWidths_value_counter_i < value_columnWidths_value.length; value_columnWidths_value_counter_i++) {
                const value_columnWidths_value_element : LengthMetrics = value_columnWidths_value[value_columnWidths_value_counter_i]
                LengthMetrics_serializer.write(valueSerializer, value_columnWidths_value_element)
            }
        }
        const value_defaultPickerItemHeight  = value.defaultPickerItemHeight
        let value_defaultPickerItemHeight_type : int32 = RuntimeType.UNDEFINED
        value_defaultPickerItemHeight_type = runtimeType(value_defaultPickerItemHeight)
        valueSerializer.writeInt8((value_defaultPickerItemHeight_type).toChar())
        if ((value_defaultPickerItemHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_defaultPickerItemHeight_value  = value_defaultPickerItemHeight!
            let value_defaultPickerItemHeight_value_type : int32 = RuntimeType.UNDEFINED
            value_defaultPickerItemHeight_value_type = runtimeType(value_defaultPickerItemHeight_value)
            if (RuntimeType.NUMBER == value_defaultPickerItemHeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_defaultPickerItemHeight_value_0  = value_defaultPickerItemHeight_value as number
                valueSerializer.writeNumber(value_defaultPickerItemHeight_value_0)
            }
            else if (RuntimeType.STRING == value_defaultPickerItemHeight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_defaultPickerItemHeight_value_1  = value_defaultPickerItemHeight_value as string
                valueSerializer.writeString(value_defaultPickerItemHeight_value_1)
            }
        }
        const value_canLoop  = value.canLoop
        let value_canLoop_type : int32 = RuntimeType.UNDEFINED
        value_canLoop_type = runtimeType(value_canLoop)
        valueSerializer.writeInt8((value_canLoop_type).toChar())
        if ((value_canLoop_type) != (RuntimeType.UNDEFINED)) {
            const value_canLoop_value  = value_canLoop!
            valueSerializer.writeBoolean(value_canLoop_value)
        }
        const value_disappearTextStyle  = value.disappearTextStyle
        let value_disappearTextStyle_type : int32 = RuntimeType.UNDEFINED
        value_disappearTextStyle_type = runtimeType(value_disappearTextStyle)
        valueSerializer.writeInt8((value_disappearTextStyle_type).toChar())
        if ((value_disappearTextStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_disappearTextStyle_value  = value_disappearTextStyle!
            PickerTextStyle_serializer.write(valueSerializer, value_disappearTextStyle_value)
        }
        const value_textStyle  = value.textStyle
        let value_textStyle_type : int32 = RuntimeType.UNDEFINED
        value_textStyle_type = runtimeType(value_textStyle)
        valueSerializer.writeInt8((value_textStyle_type).toChar())
        if ((value_textStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_textStyle_value  = value_textStyle!
            PickerTextStyle_serializer.write(valueSerializer, value_textStyle_value)
        }
        const value_acceptButtonStyle  = value.acceptButtonStyle
        let value_acceptButtonStyle_type : int32 = RuntimeType.UNDEFINED
        value_acceptButtonStyle_type = runtimeType(value_acceptButtonStyle)
        valueSerializer.writeInt8((value_acceptButtonStyle_type).toChar())
        if ((value_acceptButtonStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_acceptButtonStyle_value  = value_acceptButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, value_acceptButtonStyle_value)
        }
        const value_cancelButtonStyle  = value.cancelButtonStyle
        let value_cancelButtonStyle_type : int32 = RuntimeType.UNDEFINED
        value_cancelButtonStyle_type = runtimeType(value_cancelButtonStyle)
        valueSerializer.writeInt8((value_cancelButtonStyle_type).toChar())
        if ((value_cancelButtonStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_cancelButtonStyle_value  = value_cancelButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, value_cancelButtonStyle_value)
        }
        const value_selectedTextStyle  = value.selectedTextStyle
        let value_selectedTextStyle_type : int32 = RuntimeType.UNDEFINED
        value_selectedTextStyle_type = runtimeType(value_selectedTextStyle)
        valueSerializer.writeInt8((value_selectedTextStyle_type).toChar())
        if ((value_selectedTextStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_selectedTextStyle_value  = value_selectedTextStyle!
            PickerTextStyle_serializer.write(valueSerializer, value_selectedTextStyle_value)
        }
        const value_disableTextStyleAnimation  = value.disableTextStyleAnimation
        let value_disableTextStyleAnimation_type : int32 = RuntimeType.UNDEFINED
        value_disableTextStyleAnimation_type = runtimeType(value_disableTextStyleAnimation)
        valueSerializer.writeInt8((value_disableTextStyleAnimation_type).toChar())
        if ((value_disableTextStyleAnimation_type) != (RuntimeType.UNDEFINED)) {
            const value_disableTextStyleAnimation_value  = value_disableTextStyleAnimation!
            valueSerializer.writeBoolean(value_disableTextStyleAnimation_value)
        }
        const value_defaultTextStyle  = value.defaultTextStyle
        let value_defaultTextStyle_type : int32 = RuntimeType.UNDEFINED
        value_defaultTextStyle_type = runtimeType(value_defaultTextStyle)
        valueSerializer.writeInt8((value_defaultTextStyle_type).toChar())
        if ((value_defaultTextStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_defaultTextStyle_value  = value_defaultTextStyle!
            TextPickerTextStyle_serializer.write(valueSerializer, value_defaultTextStyle_value)
        }
        const value_onAccept  = value.onAccept
        let value_onAccept_type : int32 = RuntimeType.UNDEFINED
        value_onAccept_type = runtimeType(value_onAccept)
        valueSerializer.writeInt8((value_onAccept_type).toChar())
        if ((value_onAccept_type) != (RuntimeType.UNDEFINED)) {
            const value_onAccept_value  = value_onAccept!
            valueSerializer.holdAndWriteCallback(value_onAccept_value)
        }
        const value_onCancel  = value.onCancel
        let value_onCancel_type : int32 = RuntimeType.UNDEFINED
        value_onCancel_type = runtimeType(value_onCancel)
        valueSerializer.writeInt8((value_onCancel_type).toChar())
        if ((value_onCancel_type) != (RuntimeType.UNDEFINED)) {
            const value_onCancel_value  = value_onCancel!
            valueSerializer.holdAndWriteCallback(value_onCancel_value)
        }
        const value_onChange  = value.onChange
        let value_onChange_type : int32 = RuntimeType.UNDEFINED
        value_onChange_type = runtimeType(value_onChange)
        valueSerializer.writeInt8((value_onChange_type).toChar())
        if ((value_onChange_type) != (RuntimeType.UNDEFINED)) {
            const value_onChange_value  = value_onChange!
            valueSerializer.holdAndWriteCallback(value_onChange_value)
        }
        const value_onScrollStop  = value.onScrollStop
        let value_onScrollStop_type : int32 = RuntimeType.UNDEFINED
        value_onScrollStop_type = runtimeType(value_onScrollStop)
        valueSerializer.writeInt8((value_onScrollStop_type).toChar())
        if ((value_onScrollStop_type) != (RuntimeType.UNDEFINED)) {
            const value_onScrollStop_value  = value_onScrollStop!
            valueSerializer.holdAndWriteCallback(value_onScrollStop_value)
        }
        const value_onEnterSelectedArea  = value.onEnterSelectedArea
        let value_onEnterSelectedArea_type : int32 = RuntimeType.UNDEFINED
        value_onEnterSelectedArea_type = runtimeType(value_onEnterSelectedArea)
        valueSerializer.writeInt8((value_onEnterSelectedArea_type).toChar())
        if ((value_onEnterSelectedArea_type) != (RuntimeType.UNDEFINED)) {
            const value_onEnterSelectedArea_value  = value_onEnterSelectedArea!
            valueSerializer.holdAndWriteCallback(value_onEnterSelectedArea_value)
        }
        const value_maskRect  = value.maskRect
        let value_maskRect_type : int32 = RuntimeType.UNDEFINED
        value_maskRect_type = runtimeType(value_maskRect)
        valueSerializer.writeInt8((value_maskRect_type).toChar())
        if ((value_maskRect_type) != (RuntimeType.UNDEFINED)) {
            const value_maskRect_value  = value_maskRect!
            Rectangle_serializer.write(valueSerializer, value_maskRect_value)
        }
        const value_alignment  = value.alignment
        let value_alignment_type : int32 = RuntimeType.UNDEFINED
        value_alignment_type = runtimeType(value_alignment)
        valueSerializer.writeInt8((value_alignment_type).toChar())
        if ((value_alignment_type) != (RuntimeType.UNDEFINED)) {
            const value_alignment_value  = (value_alignment as DialogAlignment)
            valueSerializer.writeInt32(TypeChecker.DialogAlignment_ToNumeric(value_alignment_value))
        }
        const value_offset  = value.offset
        let value_offset_type : int32 = RuntimeType.UNDEFINED
        value_offset_type = runtimeType(value_offset)
        valueSerializer.writeInt8((value_offset_type).toChar())
        if ((value_offset_type) != (RuntimeType.UNDEFINED)) {
            const value_offset_value  = value_offset!
            Offset_serializer.write(valueSerializer, value_offset_value)
        }
        const value_backgroundColor  = value.backgroundColor
        let value_backgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_backgroundColor_type = runtimeType(value_backgroundColor)
        valueSerializer.writeInt8((value_backgroundColor_type).toChar())
        if ((value_backgroundColor_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundColor_value  = value_backgroundColor!
            let value_backgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_backgroundColor_value_type = runtimeType(value_backgroundColor_value)
            if (TypeChecker.isColor(value_backgroundColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_backgroundColor_value_0  = value_backgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_backgroundColor_value_1  = value_backgroundColor_value as number
                valueSerializer.writeNumber(value_backgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_backgroundColor_value_2  = value_backgroundColor_value as string
                valueSerializer.writeString(value_backgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_backgroundColor_value_3  = value_backgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_backgroundColor_value_3)
            }
        }
        const value_backgroundBlurStyle  = value.backgroundBlurStyle
        let value_backgroundBlurStyle_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyle_type = runtimeType(value_backgroundBlurStyle)
        valueSerializer.writeInt8((value_backgroundBlurStyle_type).toChar())
        if ((value_backgroundBlurStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
        }
        const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
        valueSerializer.writeInt8((value_backgroundBlurStyleOptions_type).toChar())
        if ((value_backgroundBlurStyleOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, value_backgroundBlurStyleOptions_value)
        }
        const value_backgroundEffect  = value.backgroundEffect
        let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEffect_type = runtimeType(value_backgroundEffect)
        valueSerializer.writeInt8((value_backgroundEffect_type).toChar())
        if ((value_backgroundEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundEffect_value  = value_backgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, value_backgroundEffect_value)
        }
        const value_onDidAppear  = value.onDidAppear
        let value_onDidAppear_type : int32 = RuntimeType.UNDEFINED
        value_onDidAppear_type = runtimeType(value_onDidAppear)
        valueSerializer.writeInt8((value_onDidAppear_type).toChar())
        if ((value_onDidAppear_type) != (RuntimeType.UNDEFINED)) {
            const value_onDidAppear_value  = value_onDidAppear!
            valueSerializer.holdAndWriteCallback(value_onDidAppear_value)
        }
        const value_onDidDisappear  = value.onDidDisappear
        let value_onDidDisappear_type : int32 = RuntimeType.UNDEFINED
        value_onDidDisappear_type = runtimeType(value_onDidDisappear)
        valueSerializer.writeInt8((value_onDidDisappear_type).toChar())
        if ((value_onDidDisappear_type) != (RuntimeType.UNDEFINED)) {
            const value_onDidDisappear_value  = value_onDidDisappear!
            valueSerializer.holdAndWriteCallback(value_onDidDisappear_value)
        }
        const value_onWillAppear  = value.onWillAppear
        let value_onWillAppear_type : int32 = RuntimeType.UNDEFINED
        value_onWillAppear_type = runtimeType(value_onWillAppear)
        valueSerializer.writeInt8((value_onWillAppear_type).toChar())
        if ((value_onWillAppear_type) != (RuntimeType.UNDEFINED)) {
            const value_onWillAppear_value  = value_onWillAppear!
            valueSerializer.holdAndWriteCallback(value_onWillAppear_value)
        }
        const value_onWillDisappear  = value.onWillDisappear
        let value_onWillDisappear_type : int32 = RuntimeType.UNDEFINED
        value_onWillDisappear_type = runtimeType(value_onWillDisappear)
        valueSerializer.writeInt8((value_onWillDisappear_type).toChar())
        if ((value_onWillDisappear_type) != (RuntimeType.UNDEFINED)) {
            const value_onWillDisappear_value  = value_onWillDisappear!
            valueSerializer.holdAndWriteCallback(value_onWillDisappear_value)
        }
        const value_shadow  = value.shadow
        let value_shadow_type : int32 = RuntimeType.UNDEFINED
        value_shadow_type = runtimeType(value_shadow)
        valueSerializer.writeInt8((value_shadow_type).toChar())
        if ((value_shadow_type) != (RuntimeType.UNDEFINED)) {
            const value_shadow_value  = value_shadow!
            let value_shadow_value_type : int32 = RuntimeType.UNDEFINED
            value_shadow_value_type = runtimeType(value_shadow_value)
            if (RuntimeType.OBJECT == value_shadow_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_shadow_value_0  = value_shadow_value as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, value_shadow_value_0)
            }
            else if (TypeChecker.isShadowStyle(value_shadow_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_shadow_value_1  = value_shadow_value as ShadowStyle
                valueSerializer.writeInt32(TypeChecker.ShadowStyle_ToNumeric(value_shadow_value_1))
            }
        }
        const value_enableHoverMode  = value.enableHoverMode
        let value_enableHoverMode_type : int32 = RuntimeType.UNDEFINED
        value_enableHoverMode_type = runtimeType(value_enableHoverMode)
        valueSerializer.writeInt8((value_enableHoverMode_type).toChar())
        if ((value_enableHoverMode_type) != (RuntimeType.UNDEFINED)) {
            const value_enableHoverMode_value  = value_enableHoverMode!
            valueSerializer.writeBoolean(value_enableHoverMode_value)
        }
        const value_hoverModeArea  = value.hoverModeArea
        let value_hoverModeArea_type : int32 = RuntimeType.UNDEFINED
        value_hoverModeArea_type = runtimeType(value_hoverModeArea)
        valueSerializer.writeInt8((value_hoverModeArea_type).toChar())
        if ((value_hoverModeArea_type) != (RuntimeType.UNDEFINED)) {
            const value_hoverModeArea_value  = (value_hoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(TypeChecker.HoverModeAreaType_ToNumeric(value_hoverModeArea_value))
        }
        const value_enableHapticFeedback  = value.enableHapticFeedback
        let value_enableHapticFeedback_type : int32 = RuntimeType.UNDEFINED
        value_enableHapticFeedback_type = runtimeType(value_enableHapticFeedback)
        valueSerializer.writeInt8((value_enableHapticFeedback_type).toChar())
        if ((value_enableHapticFeedback_type) != (RuntimeType.UNDEFINED)) {
            const value_enableHapticFeedback_value  = value_enableHapticFeedback!
            valueSerializer.writeBoolean(value_enableHapticFeedback_value)
        }
    }
    public static read(buffer: DeserializerBase): TextPickerDialogOptions {
        let valueDeserializer : DeserializerBase = buffer
        const range_buf_selector : int32 = valueDeserializer.readInt8()
        let range_buf : Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> | undefined
        if (range_buf_selector == (0).toChar()) {
            const range_buf_u_length : int32 = valueDeserializer.readInt32()
            let range_buf_u : Array<string> = new Array<string>(range_buf_u_length)
            for (let range_buf_u_i = 0; range_buf_u_i < range_buf_u_length; range_buf_u_i++) {
                range_buf_u[range_buf_u_i] = (valueDeserializer.readString() as string)
            }
            range_buf = range_buf_u
        }
        else if (range_buf_selector == (1).toChar()) {
            const range_buf_u_length : int32 = valueDeserializer.readInt32()
            let range_buf_u : Array<Array<string>> = new Array<Array<string>>(range_buf_u_length)
            for (let range_buf_u_i = 0; range_buf_u_i < range_buf_u_length; range_buf_u_i++) {
                const range_buf_u_buf_length : int32 = valueDeserializer.readInt32()
                let range_buf_u_buf : Array<string> = new Array<string>(range_buf_u_buf_length)
                for (let range_buf_u_buf_i = 0; range_buf_u_buf_i < range_buf_u_buf_length; range_buf_u_buf_i++) {
                    range_buf_u_buf[range_buf_u_buf_i] = (valueDeserializer.readString() as string)
                }
                range_buf_u[range_buf_u_i] = range_buf_u_buf
            }
            range_buf = range_buf_u
        }
        else if (range_buf_selector == (2).toChar()) {
            range_buf = Resource_serializer.read(valueDeserializer)
        }
        else if (range_buf_selector == (3).toChar()) {
            const range_buf_u_length : int32 = valueDeserializer.readInt32()
            let range_buf_u : Array<TextPickerRangeContent> = new Array<TextPickerRangeContent>(range_buf_u_length)
            for (let range_buf_u_i = 0; range_buf_u_i < range_buf_u_length; range_buf_u_i++) {
                range_buf_u[range_buf_u_i] = TextPickerRangeContent_serializer.read(valueDeserializer)
            }
            range_buf = range_buf_u
        }
        else if (range_buf_selector == (4).toChar()) {
            const range_buf_u_length : int32 = valueDeserializer.readInt32()
            let range_buf_u : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(range_buf_u_length)
            for (let range_buf_u_i = 0; range_buf_u_i < range_buf_u_length; range_buf_u_i++) {
                range_buf_u[range_buf_u_i] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            range_buf = range_buf_u
        }
        else {
            throw new Error("One of the branches for range_buf has to be chosen through deserialisation.")
        }
        const range_result : Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> = (range_buf as Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>)
        const value_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let value_buf : ResourceStr | Array<ResourceStr> | undefined
        if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const value_buf__selector : int32 = valueDeserializer.readInt8()
            let value_buf_ : ResourceStr | Array<ResourceStr> | undefined
            if (value_buf__selector == (0).toChar()) {
                const value_buf__u_selector : int32 = valueDeserializer.readInt8()
                let value_buf__u : string | Resource | undefined
                if (value_buf__u_selector == (0).toChar()) {
                    value_buf__u = (valueDeserializer.readString() as string)
                }
                else if (value_buf__u_selector == (1).toChar()) {
                    value_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for value_buf__u has to be chosen through deserialisation.")
                }
                value_buf_ = (value_buf__u as string | Resource)
            }
            else if (value_buf__selector == (1).toChar()) {
                const value_buf__u_length : int32 = valueDeserializer.readInt32()
                let value_buf__u : Array<ResourceStr> = new Array<ResourceStr>(value_buf__u_length)
                for (let value_buf__u_i = 0; value_buf__u_i < value_buf__u_length; value_buf__u_i++) {
                    const value_buf__u_buf_selector : int32 = valueDeserializer.readInt8()
                    let value_buf__u_buf : string | Resource | undefined
                    if (value_buf__u_buf_selector == (0).toChar()) {
                        value_buf__u_buf = (valueDeserializer.readString() as string)
                    }
                    else if (value_buf__u_buf_selector == (1).toChar()) {
                        value_buf__u_buf = Resource_serializer.read(valueDeserializer)
                    }
                    else {
                        throw new Error("One of the branches for value_buf__u_buf has to be chosen through deserialisation.")
                    }
                    value_buf__u[value_buf__u_i] = (value_buf__u_buf as string | Resource)
                }
                value_buf_ = value_buf__u
            }
            else {
                throw new Error("One of the branches for value_buf_ has to be chosen through deserialisation.")
            }
            value_buf = (value_buf_ as ResourceStr | Array<ResourceStr>)
        }
        const value_result : ResourceStr | Array<ResourceStr> | undefined = value_buf
        const selected_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selected_buf : number | Array<number> | undefined
        if ((selected_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const selected_buf__selector : int32 = valueDeserializer.readInt8()
            let selected_buf_ : number | Array<number> | undefined
            if (selected_buf__selector == (0).toChar()) {
                selected_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (selected_buf__selector == (1).toChar()) {
                const selected_buf__u_length : int32 = valueDeserializer.readInt32()
                let selected_buf__u : Array<number> = new Array<number>(selected_buf__u_length)
                for (let selected_buf__u_i = 0; selected_buf__u_i < selected_buf__u_length; selected_buf__u_i++) {
                    selected_buf__u[selected_buf__u_i] = (valueDeserializer.readNumber() as number)
                }
                selected_buf_ = selected_buf__u
            }
            else {
                throw new Error("One of the branches for selected_buf_ has to be chosen through deserialisation.")
            }
            selected_buf = (selected_buf_ as number | Array<number>)
        }
        const selected_result : number | Array<number> | undefined = selected_buf
        const columnWidths_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let columnWidths_buf : Array<LengthMetrics> | undefined
        if ((columnWidths_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const columnWidths_buf__length : int32 = valueDeserializer.readInt32()
            let columnWidths_buf_ : Array<LengthMetrics> = new Array<LengthMetrics>(columnWidths_buf__length)
            for (let columnWidths_buf__i = 0; columnWidths_buf__i < columnWidths_buf__length; columnWidths_buf__i++) {
                columnWidths_buf_[columnWidths_buf__i] = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            columnWidths_buf = columnWidths_buf_
        }
        const columnWidths_result : Array<LengthMetrics> | undefined = columnWidths_buf
        const defaultPickerItemHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let defaultPickerItemHeight_buf : number | string | undefined
        if ((defaultPickerItemHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const defaultPickerItemHeight_buf__selector : int32 = valueDeserializer.readInt8()
            let defaultPickerItemHeight_buf_ : number | string | undefined
            if (defaultPickerItemHeight_buf__selector == (0).toChar()) {
                defaultPickerItemHeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (defaultPickerItemHeight_buf__selector == (1).toChar()) {
                defaultPickerItemHeight_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for defaultPickerItemHeight_buf_ has to be chosen through deserialisation.")
            }
            defaultPickerItemHeight_buf = (defaultPickerItemHeight_buf_ as number | string)
        }
        const defaultPickerItemHeight_result : number | string | undefined = defaultPickerItemHeight_buf
        const canLoop_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let canLoop_buf : boolean | undefined
        if ((canLoop_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            canLoop_buf = valueDeserializer.readBoolean()
        }
        const canLoop_result : boolean | undefined = canLoop_buf
        const disappearTextStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disappearTextStyle_buf : PickerTextStyle | undefined
        if ((disappearTextStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            disappearTextStyle_buf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const disappearTextStyle_result : PickerTextStyle | undefined = disappearTextStyle_buf
        const textStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textStyle_buf : PickerTextStyle | undefined
        if ((textStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            textStyle_buf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const textStyle_result : PickerTextStyle | undefined = textStyle_buf
        const acceptButtonStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let acceptButtonStyle_buf : PickerDialogButtonStyle | undefined
        if ((acceptButtonStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            acceptButtonStyle_buf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const acceptButtonStyle_result : PickerDialogButtonStyle | undefined = acceptButtonStyle_buf
        const cancelButtonStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelButtonStyle_buf : PickerDialogButtonStyle | undefined
        if ((cancelButtonStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            cancelButtonStyle_buf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const cancelButtonStyle_result : PickerDialogButtonStyle | undefined = cancelButtonStyle_buf
        const selectedTextStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTextStyle_buf : PickerTextStyle | undefined
        if ((selectedTextStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            selectedTextStyle_buf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const selectedTextStyle_result : PickerTextStyle | undefined = selectedTextStyle_buf
        const disableTextStyleAnimation_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disableTextStyleAnimation_buf : boolean | undefined
        if ((disableTextStyleAnimation_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            disableTextStyleAnimation_buf = valueDeserializer.readBoolean()
        }
        const disableTextStyleAnimation_result : boolean | undefined = disableTextStyleAnimation_buf
        const defaultTextStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let defaultTextStyle_buf : TextPickerTextStyle | undefined
        if ((defaultTextStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            defaultTextStyle_buf = TextPickerTextStyle_serializer.read(valueDeserializer)
        }
        const defaultTextStyle_result : TextPickerTextStyle | undefined = defaultTextStyle_buf
        const onAccept_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onAccept_buf : ((value: TextPickerResult) => void) | undefined
        if ((onAccept_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onAccept_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAccept_buf__call : KPointer = valueDeserializer.readPointer()
            const onAccept_buf__callSync : KPointer = valueDeserializer.readPointer()
            onAccept_buf = (value: TextPickerResult):void => { 
    const onAccept_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onAccept_buf__argsSerializer.writeInt32(onAccept_buf__resource.resourceId);
    onAccept_buf__argsSerializer.writePointer(onAccept_buf__call);
    onAccept_buf__argsSerializer.writePointer(onAccept_buf__callSync);
    TextPickerResult_serializer.write(onAccept_buf__argsSerializer, value);
    InteropNativeModule._CallCallback(1290504509, onAccept_buf__argsSerializer.asBuffer(), onAccept_buf__argsSerializer.length());
    onAccept_buf__argsSerializer.release();
    return; }
        }
        const onAccept_result : ((value: TextPickerResult) => void) | undefined = onAccept_buf
        const onCancel_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onCancel_buf : (() => void) | undefined
        if ((onCancel_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onCancel_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancel_buf__call : KPointer = valueDeserializer.readPointer()
            const onCancel_buf__callSync : KPointer = valueDeserializer.readPointer()
            onCancel_buf = ():void => { 
    const onCancel_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onCancel_buf__argsSerializer.writeInt32(onCancel_buf__resource.resourceId);
    onCancel_buf__argsSerializer.writePointer(onCancel_buf__call);
    onCancel_buf__argsSerializer.writePointer(onCancel_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onCancel_buf__argsSerializer.asBuffer(), onCancel_buf__argsSerializer.length());
    onCancel_buf__argsSerializer.release();
    return; }
        }
        const onCancel_result : (() => void) | undefined = onCancel_buf
        const onChange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onChange_buf : ((value: TextPickerResult) => void) | undefined
        if ((onChange_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onChange_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onChange_buf__call : KPointer = valueDeserializer.readPointer()
            const onChange_buf__callSync : KPointer = valueDeserializer.readPointer()
            onChange_buf = (value: TextPickerResult):void => { 
    const onChange_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onChange_buf__argsSerializer.writeInt32(onChange_buf__resource.resourceId);
    onChange_buf__argsSerializer.writePointer(onChange_buf__call);
    onChange_buf__argsSerializer.writePointer(onChange_buf__callSync);
    TextPickerResult_serializer.write(onChange_buf__argsSerializer, value);
    InteropNativeModule._CallCallback(1290504509, onChange_buf__argsSerializer.asBuffer(), onChange_buf__argsSerializer.length());
    onChange_buf__argsSerializer.release();
    return; }
        }
        const onChange_result : ((value: TextPickerResult) => void) | undefined = onChange_buf
        const onScrollStop_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onScrollStop_buf : ((value: TextPickerResult) => void) | undefined
        if ((onScrollStop_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onScrollStop_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onScrollStop_buf__call : KPointer = valueDeserializer.readPointer()
            const onScrollStop_buf__callSync : KPointer = valueDeserializer.readPointer()
            onScrollStop_buf = (value: TextPickerResult):void => { 
    const onScrollStop_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onScrollStop_buf__argsSerializer.writeInt32(onScrollStop_buf__resource.resourceId);
    onScrollStop_buf__argsSerializer.writePointer(onScrollStop_buf__call);
    onScrollStop_buf__argsSerializer.writePointer(onScrollStop_buf__callSync);
    TextPickerResult_serializer.write(onScrollStop_buf__argsSerializer, value);
    InteropNativeModule._CallCallback(1290504509, onScrollStop_buf__argsSerializer.asBuffer(), onScrollStop_buf__argsSerializer.length());
    onScrollStop_buf__argsSerializer.release();
    return; }
        }
        const onScrollStop_result : ((value: TextPickerResult) => void) | undefined = onScrollStop_buf
        const onEnterSelectedArea_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onEnterSelectedArea_buf : ((value: TextPickerResult) => void) | undefined
        if ((onEnterSelectedArea_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onEnterSelectedArea_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onEnterSelectedArea_buf__call : KPointer = valueDeserializer.readPointer()
            const onEnterSelectedArea_buf__callSync : KPointer = valueDeserializer.readPointer()
            onEnterSelectedArea_buf = (value: TextPickerResult):void => { 
    const onEnterSelectedArea_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onEnterSelectedArea_buf__argsSerializer.writeInt32(onEnterSelectedArea_buf__resource.resourceId);
    onEnterSelectedArea_buf__argsSerializer.writePointer(onEnterSelectedArea_buf__call);
    onEnterSelectedArea_buf__argsSerializer.writePointer(onEnterSelectedArea_buf__callSync);
    TextPickerResult_serializer.write(onEnterSelectedArea_buf__argsSerializer, value);
    InteropNativeModule._CallCallback(1290504509, onEnterSelectedArea_buf__argsSerializer.asBuffer(), onEnterSelectedArea_buf__argsSerializer.length());
    onEnterSelectedArea_buf__argsSerializer.release();
    return; }
        }
        const onEnterSelectedArea_result : ((value: TextPickerResult) => void) | undefined = onEnterSelectedArea_buf
        const maskRect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRect_buf : Rectangle | undefined
        if ((maskRect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maskRect_buf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRect_result : Rectangle | undefined = maskRect_buf
        const alignment_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignment_buf : DialogAlignment | undefined
        if ((alignment_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            alignment_buf = TypeChecker.DialogAlignment_FromNumeric(valueDeserializer.readInt32())
        }
        const alignment_result : DialogAlignment | undefined = alignment_buf
        const offset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offset_buf : Offset | undefined
        if ((offset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            offset_buf = Offset_serializer.read(valueDeserializer)
        }
        const offset_result : Offset | undefined = offset_buf
        const backgroundColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColor_buf : ResourceColor | undefined
        if ((backgroundColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const backgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let backgroundColor_buf_ : Color | number | string | Resource | undefined
            if (backgroundColor_buf__selector == (0).toChar()) {
                backgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (backgroundColor_buf__selector == (1).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (backgroundColor_buf__selector == (2).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (backgroundColor_buf__selector == (3).toChar()) {
                backgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for backgroundColor_buf_ has to be chosen through deserialisation.")
            }
            backgroundColor_buf = (backgroundColor_buf_ as Color | number | string | Resource)
        }
        const backgroundColor_result : ResourceColor | undefined = backgroundColor_buf
        const backgroundBlurStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyle_buf : BlurStyle | undefined
        if ((backgroundBlurStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyle_buf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyle_result : BlurStyle | undefined = backgroundBlurStyle_buf
        const backgroundBlurStyleOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptions_buf : BackgroundBlurStyleOptions | undefined
        if ((backgroundBlurStyleOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyleOptions_buf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptions_result : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptions_buf
        const backgroundEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffect_buf : BackgroundEffectOptions | undefined
        if ((backgroundEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundEffect_buf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffect_result : BackgroundEffectOptions | undefined = backgroundEffect_buf
        const onDidAppear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppear_buf : (() => void) | undefined
        if ((onDidAppear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onDidAppear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppear_buf__call : KPointer = valueDeserializer.readPointer()
            const onDidAppear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDidAppear_buf = ():void => { 
    const onDidAppear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDidAppear_buf__argsSerializer.writeInt32(onDidAppear_buf__resource.resourceId);
    onDidAppear_buf__argsSerializer.writePointer(onDidAppear_buf__call);
    onDidAppear_buf__argsSerializer.writePointer(onDidAppear_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onDidAppear_buf__argsSerializer.asBuffer(), onDidAppear_buf__argsSerializer.length());
    onDidAppear_buf__argsSerializer.release();
    return; }
        }
        const onDidAppear_result : (() => void) | undefined = onDidAppear_buf
        const onDidDisappear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappear_buf : (() => void) | undefined
        if ((onDidDisappear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onDidDisappear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappear_buf__call : KPointer = valueDeserializer.readPointer()
            const onDidDisappear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDidDisappear_buf = ():void => { 
    const onDidDisappear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDidDisappear_buf__argsSerializer.writeInt32(onDidDisappear_buf__resource.resourceId);
    onDidDisappear_buf__argsSerializer.writePointer(onDidDisappear_buf__call);
    onDidDisappear_buf__argsSerializer.writePointer(onDidDisappear_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onDidDisappear_buf__argsSerializer.asBuffer(), onDidDisappear_buf__argsSerializer.length());
    onDidDisappear_buf__argsSerializer.release();
    return; }
        }
        const onDidDisappear_result : (() => void) | undefined = onDidDisappear_buf
        const onWillAppear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppear_buf : (() => void) | undefined
        if ((onWillAppear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onWillAppear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppear_buf__call : KPointer = valueDeserializer.readPointer()
            const onWillAppear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onWillAppear_buf = ():void => { 
    const onWillAppear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onWillAppear_buf__argsSerializer.writeInt32(onWillAppear_buf__resource.resourceId);
    onWillAppear_buf__argsSerializer.writePointer(onWillAppear_buf__call);
    onWillAppear_buf__argsSerializer.writePointer(onWillAppear_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onWillAppear_buf__argsSerializer.asBuffer(), onWillAppear_buf__argsSerializer.length());
    onWillAppear_buf__argsSerializer.release();
    return; }
        }
        const onWillAppear_result : (() => void) | undefined = onWillAppear_buf
        const onWillDisappear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappear_buf : (() => void) | undefined
        if ((onWillDisappear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onWillDisappear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappear_buf__call : KPointer = valueDeserializer.readPointer()
            const onWillDisappear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onWillDisappear_buf = ():void => { 
    const onWillDisappear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onWillDisappear_buf__argsSerializer.writeInt32(onWillDisappear_buf__resource.resourceId);
    onWillDisappear_buf__argsSerializer.writePointer(onWillDisappear_buf__call);
    onWillDisappear_buf__argsSerializer.writePointer(onWillDisappear_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onWillDisappear_buf__argsSerializer.asBuffer(), onWillDisappear_buf__argsSerializer.length());
    onWillDisappear_buf__argsSerializer.release();
    return; }
        }
        const onWillDisappear_result : (() => void) | undefined = onWillDisappear_buf
        const shadow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadow_buf : ShadowOptions | ShadowStyle | undefined
        if ((shadow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const shadow_buf__selector : int32 = valueDeserializer.readInt8()
            let shadow_buf_ : ShadowOptions | ShadowStyle | undefined
            if (shadow_buf__selector == (0).toChar()) {
                shadow_buf_ = ShadowOptions_serializer.read(valueDeserializer)
            }
            else if (shadow_buf__selector == (1).toChar()) {
                shadow_buf_ = TypeChecker.ShadowStyle_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for shadow_buf_ has to be chosen through deserialisation.")
            }
            shadow_buf = (shadow_buf_ as ShadowOptions | ShadowStyle)
        }
        const shadow_result : ShadowOptions | ShadowStyle | undefined = shadow_buf
        const enableHoverMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverMode_buf : boolean | undefined
        if ((enableHoverMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableHoverMode_buf = valueDeserializer.readBoolean()
        }
        const enableHoverMode_result : boolean | undefined = enableHoverMode_buf
        const hoverModeArea_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeArea_buf : HoverModeAreaType | undefined
        if ((hoverModeArea_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            hoverModeArea_buf = TypeChecker.HoverModeAreaType_FromNumeric(valueDeserializer.readInt32())
        }
        const hoverModeArea_result : HoverModeAreaType | undefined = hoverModeArea_buf
        const enableHapticFeedback_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHapticFeedback_buf : boolean | undefined
        if ((enableHapticFeedback_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableHapticFeedback_buf = valueDeserializer.readBoolean()
        }
        const enableHapticFeedback_result : boolean | undefined = enableHapticFeedback_buf
        let value : TextPickerDialogOptions = ({range: range_result, value: value_result, selected: selected_result, columnWidths: columnWidths_result, defaultPickerItemHeight: defaultPickerItemHeight_result, canLoop: canLoop_result, disappearTextStyle: disappearTextStyle_result, textStyle: textStyle_result, acceptButtonStyle: acceptButtonStyle_result, cancelButtonStyle: cancelButtonStyle_result, selectedTextStyle: selectedTextStyle_result, disableTextStyleAnimation: disableTextStyleAnimation_result, defaultTextStyle: defaultTextStyle_result, onAccept: onAccept_result, onCancel: onCancel_result, onChange: onChange_result, onScrollStop: onScrollStop_result, onEnterSelectedArea: onEnterSelectedArea_result, maskRect: maskRect_result, alignment: alignment_result, offset: offset_result, backgroundColor: backgroundColor_result, backgroundBlurStyle: backgroundBlurStyle_result, backgroundBlurStyleOptions: backgroundBlurStyleOptions_result, backgroundEffect: backgroundEffect_result, onDidAppear: onDidAppear_result, onDidDisappear: onDidDisappear_result, onWillAppear: onWillAppear_result, onWillDisappear: onWillDisappear_result, shadow: shadow_result, enableHoverMode: enableHoverMode_result, hoverModeArea: hoverModeArea_result, enableHapticFeedback: enableHapticFeedback_result} as TextPickerDialogOptions)
        return value
    }
}
