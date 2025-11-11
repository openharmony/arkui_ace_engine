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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, Bindable, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_Arkui_Component_Units_ResourceStr_serializer, Bindable_Array_Arkui_Component_Units_ResourceStr_serializer, Bindable_Number_serializer, Bindable_Array_Number_serializer, PickerDialogButtonStyle_serializer, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ShadowOptions_serializer } from "./common"
import { Resource_serializer } from "./../framework/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Dimension, ResourceStr, ResourceColor, Offset, Font_serializer, Font, Offset_serializer } from "./units"
import { Resource } from "global.resource"
import { CrownSensitivity, Color, TextOverflow } from "./enums"
import { AttributeModifier, extractors, hookTextPickerAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { LengthMetrics } from "arkui.Graphics"
import { DialogAlignment } from "./alertDialog"
import { TextPickerModifier } from "./../TextPickerModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics_serializer } from "./../Graphics"
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
    attributeSet?: TextPickerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextPickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextPicker_construct(peerId, flags)
        const _peer  = new ArkTextPickerPeer(_peerPtr, peerId, 'TextPicker', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextPickerOptionsAttribute(options?: TextPickerOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            TextPickerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerInterface_setTextPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultPickerItemHeightAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDefaultPickerItemHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCanLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setCanLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisappearTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PickerTextStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDisappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PickerTextStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PickerTextStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setSelectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisableTextStyleAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDisableTextStyleAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultTextStyleAttribute(value: TextPickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextPickerTextStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDefaultTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnTextPickerChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollStopAttribute(value: TextPickerScrollStopCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setOnScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEnterSelectedAreaAttribute(value: TextPickerEnterSelectedAreaCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setOnEnterSelectedArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedIndexAttribute(value: number | Array<number> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (TypeChecker.isArray_Number(valueTmpValue)) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Array<number>
                thisSerializer.writeInt32((valueTmpValueForIdx1.length).toInt())
                for (let valueTmpValueForIdx1CounterI = 0; valueTmpValueForIdx1CounterI < valueTmpValueForIdx1.length; valueTmpValueForIdx1CounterI++) {
                    const valueTmpValueForIdx1TmpElement : number = valueTmpValueForIdx1[valueTmpValueForIdx1CounterI]
                    thisSerializer.writeNumber(valueTmpValueForIdx1TmpElement)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setSelectedIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerOptions | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DividerOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setGradientHeightAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setGradientHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDigitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CrownSensitivity)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_setDigitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    value?: ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>>;
    selected?: number | Array<number> | Bindable<number> | Bindable<Array<number>>;
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
    setTextPickerOptions(options?: TextPickerOptions): this {
        throw new Error("Unimplemented method setTextPickerOptions")
    }
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
    divider(value: DividerOptions | null | undefined): this {
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
    divider_value?: DividerOptions | null | undefined
    gradientHeight_value?: Dimension | undefined
    enableHapticFeedback_value?: boolean | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    attributeModifier_value?: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined
    setTextPickerOptions(options?: TextPickerOptions): this {
        return this
    }
    defaultPickerItemHeight(value: number | string | undefined): this {
        return this
    }
    canLoop(value: boolean | undefined): this {
        return this
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    textStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    disableTextStyleAnimation(value: boolean | undefined): this {
        return this
    }
    defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        return this
    }
    onChange(value: OnTextPickerChangeCallback | undefined): this {
        return this
    }
    onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        return this
    }
    onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        return this
    }
    selectedIndex(value: number | Array<number> | undefined): this {
        return this
    }
    divider(value: DividerOptions | null | undefined): this {
        return this
    }
    gradientHeight(value: Dimension | undefined): this {
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
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
    public divider(value: DividerOptions | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerOptions | null | undefined)
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
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookTextPickerAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function TextPickerImpl(
    @memo
    style: ((attributes: TextPickerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTextPickerComponent>((): ArkTextPickerComponent => {
        return new ArkTextPickerComponent()
    })
    NodeAttach<ArkTextPickerPeer>((): ArkTextPickerPeer => ArkTextPickerPeer.create(receiver), (peer: ArkTextPickerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
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
        const valueHolderForText  = value.text
        if (valueHolderForText instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForTextForIdx0  = valueHolderForText as string
            valueSerializer.writeString(valueHolderForTextForIdx0)
        } else if (valueHolderForText instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForTextForIdx1  = valueHolderForText as Resource
            Resource_serializer.write(valueSerializer, valueHolderForTextForIdx1)
        }
        const valueHolderForChildren  = value.children
        if (valueHolderForChildren !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForChildrenTmpValue  = valueHolderForChildren!
            valueSerializer.writeInt32((valueHolderForChildrenTmpValue.length).toInt())
            for (let valueHolderForChildrenTmpValueCounterI = 0; valueHolderForChildrenTmpValueCounterI < valueHolderForChildrenTmpValue.length; valueHolderForChildrenTmpValueCounterI++) {
                const valueHolderForChildrenTmpValueTmpElement : TextCascadePickerRangeContent = valueHolderForChildrenTmpValue[valueHolderForChildrenTmpValueCounterI]
                TextCascadePickerRangeContent_serializer.write(valueSerializer, valueHolderForChildrenTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextCascadePickerRangeContent {
        let valueDeserializer : DeserializerBase = buffer
        const textTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let textTmpBuf : string | Resource | undefined
        if (textTmpBufUnionSelector == (0).toChar()) {
            textTmpBuf = (valueDeserializer.readString() as string)
        } else if (textTmpBufUnionSelector == (1).toChar()) {
            textTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for textTmpBuf has to be chosen through deserialisation.")
        }
        const textTmpResult : string | Resource = (textTmpBuf as string | Resource)
        const childrenTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let childrenTmpBuf : Array<TextCascadePickerRangeContent> | undefined = undefined
        if ((childrenTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const childrenTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let childrenTmpBuf_ : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(childrenTmpBuf_Length)
            for (let childrenTmpBuf_BufCounterI = 0; childrenTmpBuf_BufCounterI < childrenTmpBuf_Length; childrenTmpBuf_BufCounterI++) {
                childrenTmpBuf_[childrenTmpBuf_BufCounterI] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            childrenTmpBuf = childrenTmpBuf_
        }
        const childrenTmpResult : Array<TextCascadePickerRangeContent> | undefined = childrenTmpBuf
        let value : TextCascadePickerRangeContent = ({text: textTmpResult, children: childrenTmpResult} as TextCascadePickerRangeContent)
        return value
    }
}
export class TextPickerRangeContent_serializer {
    public static write(buffer: SerializerBase, value: TextPickerRangeContent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForIconForIdx0  = valueHolderForIcon as string
            valueSerializer.writeString(valueHolderForIconForIdx0)
        } else if (valueHolderForIcon instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForIconForIdx1  = valueHolderForIcon as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconForIdx1)
        }
        const valueHolderForText  = value.text
        if (valueHolderForText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextTmpValue  = valueHolderForText!
            if (valueHolderForTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextTmpValueForIdx0  = valueHolderForTextTmpValue as string
                valueSerializer.writeString(valueHolderForTextTmpValueForIdx0)
            } else if (valueHolderForTextTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTextTmpValueForIdx1  = valueHolderForTextTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextPickerRangeContent {
        let valueDeserializer : DeserializerBase = buffer
        const iconTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconTmpBuf : string | Resource | undefined
        if (iconTmpBufUnionSelector == (0).toChar()) {
            iconTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconTmpBufUnionSelector == (1).toChar()) {
            iconTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconTmpBuf has to be chosen through deserialisation.")
        }
        const iconTmpResult : string | Resource = (iconTmpBuf as string | Resource)
        const textTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textTmpBuf : string | Resource | undefined = undefined
        if ((textTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let textTmpBuf_ : string | Resource | undefined
            if (textTmpBuf_UnionSelector == (0).toChar()) {
                textTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (textTmpBuf_UnionSelector == (1).toChar()) {
                textTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for textTmpBuf_ has to be chosen through deserialisation.")
            }
            textTmpBuf = (textTmpBuf_ as string | Resource)
        }
        const textTmpResult : string | Resource | undefined = textTmpBuf
        let value : TextPickerRangeContent = ({icon: iconTmpResult, text: textTmpResult} as TextPickerRangeContent)
        return value
    }
}
export class TextPickerResult_serializer {
    public static write(buffer: SerializerBase, value: TextPickerResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (TypeChecker.isArray_String(valueHolderForValue)) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as Array<string>
            valueSerializer.writeInt32((valueHolderForValueForIdx1.length).toInt())
            for (let valueHolderForValueForIdx1CounterI = 0; valueHolderForValueForIdx1CounterI < valueHolderForValueForIdx1.length; valueHolderForValueForIdx1CounterI++) {
                const valueHolderForValueForIdx1TmpElement : string = valueHolderForValueForIdx1[valueHolderForValueForIdx1CounterI]
                valueSerializer.writeString(valueHolderForValueForIdx1TmpElement)
            }
        }
        const valueHolderForIndex  = value.index
        if (valueHolderForIndex instanceof number) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForIndexForIdx0  = valueHolderForIndex as number
            valueSerializer.writeNumber(valueHolderForIndexForIdx0)
        } else if (TypeChecker.isArray_Number(valueHolderForIndex)) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForIndexForIdx1  = valueHolderForIndex as Array<number>
            valueSerializer.writeInt32((valueHolderForIndexForIdx1.length).toInt())
            for (let valueHolderForIndexForIdx1CounterI = 0; valueHolderForIndexForIdx1CounterI < valueHolderForIndexForIdx1.length; valueHolderForIndexForIdx1CounterI++) {
                const valueHolderForIndexForIdx1TmpElement : number = valueHolderForIndexForIdx1[valueHolderForIndexForIdx1CounterI]
                valueSerializer.writeNumber(valueHolderForIndexForIdx1TmpElement)
            }
        }
    }
    public static read(buffer: DeserializerBase): TextPickerResult {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | Array<string> | undefined
        if (valueTmpBufUnionSelector == (0).toChar()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toChar()) {
            const valueTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let valueTmpBufBufU : Array<string> = new Array<string>(valueTmpBufBufULength)
            for (let valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
                valueTmpBufBufU[valueTmpBufBufUBufCounterI] = (valueDeserializer.readString() as string)
            }
            valueTmpBuf = valueTmpBufBufU
        } else {
            throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
        }
        const valueTmpResult : string | Array<string> = (valueTmpBuf as string | Array<string>)
        const indexTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let indexTmpBuf : number | Array<number> | undefined
        if (indexTmpBufUnionSelector == (0).toChar()) {
            indexTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (indexTmpBufUnionSelector == (1).toChar()) {
            const indexTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let indexTmpBufBufU : Array<number> = new Array<number>(indexTmpBufBufULength)
            for (let indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
                indexTmpBufBufU[indexTmpBufBufUBufCounterI] = (valueDeserializer.readNumber() as number)
            }
            indexTmpBuf = indexTmpBufBufU
        } else {
            throw new Error("One of the branches for indexTmpBuf has to be chosen through deserialisation.")
        }
        const indexTmpResult : number | Array<number> = (indexTmpBuf as number | Array<number>)
        let value : TextPickerResult = ({value: valueTmpResult, index: indexTmpResult} as TextPickerResult)
        return value
    }
}
export class DividerOptions_serializer {
    public static write(buffer: SerializerBase, value: DividerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            if (valueHolderForStrokeWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx0  = valueHolderForStrokeWidthTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeWidthTmpValueForIdx0)
            } else if (valueHolderForStrokeWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx1  = valueHolderForStrokeWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForStrokeWidthTmpValueForIdx1)
            } else if (valueHolderForStrokeWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx2  = valueHolderForStrokeWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStartMargin  = value.startMargin
        if (valueHolderForStartMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartMarginTmpValue  = valueHolderForStartMargin!
            if (valueHolderForStartMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStartMarginTmpValueForIdx0  = valueHolderForStartMarginTmpValue as string
                valueSerializer.writeString(valueHolderForStartMarginTmpValueForIdx0)
            } else if (valueHolderForStartMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStartMarginTmpValueForIdx1  = valueHolderForStartMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForStartMarginTmpValueForIdx1)
            } else if (valueHolderForStartMarginTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStartMarginTmpValueForIdx2  = valueHolderForStartMarginTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStartMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndMargin  = value.endMargin
        if (valueHolderForEndMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndMarginTmpValue  = valueHolderForEndMargin!
            if (valueHolderForEndMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForEndMarginTmpValueForIdx0  = valueHolderForEndMarginTmpValue as string
                valueSerializer.writeString(valueHolderForEndMarginTmpValueForIdx0)
            } else if (valueHolderForEndMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForEndMarginTmpValueForIdx1  = valueHolderForEndMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForEndMarginTmpValueForIdx1)
            } else if (valueHolderForEndMarginTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForEndMarginTmpValueForIdx2  = valueHolderForEndMarginTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForEndMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DividerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidthTmpBuf : Dimension | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let strokeWidthTmpBuf_ : string | number | Resource | undefined
            if (strokeWidthTmpBuf_UnionSelector == (0).toChar()) {
                strokeWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (strokeWidthTmpBuf_UnionSelector == (1).toChar()) {
                strokeWidthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (strokeWidthTmpBuf_UnionSelector == (2).toChar()) {
                strokeWidthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for strokeWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            strokeWidthTmpBuf = (strokeWidthTmpBuf_ as string | number | Resource)
        }
        const strokeWidthTmpResult : Dimension | undefined = strokeWidthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | number | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | number | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const startMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMarginTmpBuf : Dimension | undefined = undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startMarginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let startMarginTmpBuf_ : string | number | Resource | undefined
            if (startMarginTmpBuf_UnionSelector == (0).toChar()) {
                startMarginTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (startMarginTmpBuf_UnionSelector == (1).toChar()) {
                startMarginTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (startMarginTmpBuf_UnionSelector == (2).toChar()) {
                startMarginTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for startMarginTmpBuf_ has to be chosen through deserialisation.")
            }
            startMarginTmpBuf = (startMarginTmpBuf_ as string | number | Resource)
        }
        const startMarginTmpResult : Dimension | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMarginTmpBuf : Dimension | undefined = undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endMarginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let endMarginTmpBuf_ : string | number | Resource | undefined
            if (endMarginTmpBuf_UnionSelector == (0).toChar()) {
                endMarginTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (endMarginTmpBuf_UnionSelector == (1).toChar()) {
                endMarginTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (endMarginTmpBuf_UnionSelector == (2).toChar()) {
                endMarginTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for endMarginTmpBuf_ has to be chosen through deserialisation.")
            }
            endMarginTmpBuf = (endMarginTmpBuf_ as string | number | Resource)
        }
        const endMarginTmpResult : Dimension | undefined = endMarginTmpBuf
        let value : DividerOptions = ({strokeWidth: strokeWidthTmpResult, color: colorTmpResult, startMargin: startMarginTmpResult, endMargin: endMarginTmpResult} as DividerOptions)
        return value
    }
}
export class TextPickerOptions_serializer {
    public static write(buffer: SerializerBase, value: TextPickerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRange  = value.range
        if (TypeChecker.isArray_String(valueHolderForRange)) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForRangeForIdx0  = valueHolderForRange as Array<string>
            valueSerializer.writeInt32((valueHolderForRangeForIdx0.length).toInt())
            for (let valueHolderForRangeForIdx0CounterI = 0; valueHolderForRangeForIdx0CounterI < valueHolderForRangeForIdx0.length; valueHolderForRangeForIdx0CounterI++) {
                const valueHolderForRangeForIdx0TmpElement : string = valueHolderForRangeForIdx0[valueHolderForRangeForIdx0CounterI]
                valueSerializer.writeString(valueHolderForRangeForIdx0TmpElement)
            }
        } else if (TypeChecker.isArray_Array_String(valueHolderForRange)) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRangeForIdx1  = valueHolderForRange as Array<Array<string>>
            valueSerializer.writeInt32((valueHolderForRangeForIdx1.length).toInt())
            for (let valueHolderForRangeForIdx1CounterI = 0; valueHolderForRangeForIdx1CounterI < valueHolderForRangeForIdx1.length; valueHolderForRangeForIdx1CounterI++) {
                const valueHolderForRangeForIdx1TmpElement : Array<string> = valueHolderForRangeForIdx1[valueHolderForRangeForIdx1CounterI]
                valueSerializer.writeInt32((valueHolderForRangeForIdx1TmpElement.length).toInt())
                for (let valueHolderForRangeForIdx1TmpElementCounterI = 0; valueHolderForRangeForIdx1TmpElementCounterI < valueHolderForRangeForIdx1TmpElement.length; valueHolderForRangeForIdx1TmpElementCounterI++) {
                    const valueHolderForRangeForIdx1TmpElementTmpElement : string = valueHolderForRangeForIdx1TmpElement[valueHolderForRangeForIdx1TmpElementCounterI]
                    valueSerializer.writeString(valueHolderForRangeForIdx1TmpElementTmpElement)
                }
            }
        } else if (valueHolderForRange instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForRangeForIdx2  = valueHolderForRange as Resource
            Resource_serializer.write(valueSerializer, valueHolderForRangeForIdx2)
        } else if (TypeChecker.isArray_TextPickerRangeContent(valueHolderForRange)) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForRangeForIdx3  = valueHolderForRange as Array<TextPickerRangeContent>
            valueSerializer.writeInt32((valueHolderForRangeForIdx3.length).toInt())
            for (let valueHolderForRangeForIdx3CounterI = 0; valueHolderForRangeForIdx3CounterI < valueHolderForRangeForIdx3.length; valueHolderForRangeForIdx3CounterI++) {
                const valueHolderForRangeForIdx3TmpElement : TextPickerRangeContent = valueHolderForRangeForIdx3[valueHolderForRangeForIdx3CounterI]
                TextPickerRangeContent_serializer.write(valueSerializer, valueHolderForRangeForIdx3TmpElement)
            }
        } else if (TypeChecker.isArray_TextCascadePickerRangeContent(valueHolderForRange)) {
            valueSerializer.writeInt8((4).toByte())
            const valueHolderForRangeForIdx4  = valueHolderForRange as Array<TextCascadePickerRangeContent>
            valueSerializer.writeInt32((valueHolderForRangeForIdx4.length).toInt())
            for (let valueHolderForRangeForIdx4CounterI = 0; valueHolderForRangeForIdx4CounterI < valueHolderForRangeForIdx4.length; valueHolderForRangeForIdx4CounterI++) {
                const valueHolderForRangeForIdx4TmpElement : TextCascadePickerRangeContent = valueHolderForRangeForIdx4[valueHolderForRangeForIdx4CounterI]
                TextCascadePickerRangeContent_serializer.write(valueSerializer, valueHolderForRangeForIdx4TmpElement)
            }
        }
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            if (valueHolderForValueTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as ResourceStr
                if (valueHolderForValueTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx0  = valueHolderForValueTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForValueTmpValueForIdx0ForIdx0)
                } else if (valueHolderForValueTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx1  = valueHolderForValueTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx1)
                }
            } else if (TypeChecker.isArray_ResourceStr(valueHolderForValueTmpValue)) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForValueTmpValueForIdx1  = valueHolderForValueTmpValue as Array<ResourceStr>
                valueSerializer.writeInt32((valueHolderForValueTmpValueForIdx1.length).toInt())
                for (let valueHolderForValueTmpValueForIdx1CounterI = 0; valueHolderForValueTmpValueForIdx1CounterI < valueHolderForValueTmpValueForIdx1.length; valueHolderForValueTmpValueForIdx1CounterI++) {
                    const valueHolderForValueTmpValueForIdx1TmpElement : ResourceStr = valueHolderForValueTmpValueForIdx1[valueHolderForValueTmpValueForIdx1CounterI]
                    if (valueHolderForValueTmpValueForIdx1TmpElement instanceof string) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderForValueTmpValueForIdx1TmpElementForIdx0  = valueHolderForValueTmpValueForIdx1TmpElement as string
                        valueSerializer.writeString(valueHolderForValueTmpValueForIdx1TmpElementForIdx0)
                    } else if (valueHolderForValueTmpValueForIdx1TmpElement instanceof Resource) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForValueTmpValueForIdx1TmpElementForIdx1  = valueHolderForValueTmpValueForIdx1TmpElement as Resource
                        Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1TmpElementForIdx1)
                    }
                }
            } else if (valueHolderForValueTmpValue instanceof Bindable && valueHolderForValueTmpValue.value instanceof ResourceStr) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForValueTmpValueForIdx2  = valueHolderForValueTmpValue as Bindable<ResourceStr>
                Bindable_Arkui_Component_Units_ResourceStr_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx2)
            } else if (valueHolderForValueTmpValue instanceof Bindable<Array<ResourceStr>>) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForValueTmpValueForIdx3  = valueHolderForValueTmpValue as Bindable<Array<ResourceStr>>
                Bindable_Array_Arkui_Component_Units_ResourceStr_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            if (valueHolderForSelectedTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedTmpValueForIdx0  = valueHolderForSelectedTmpValue as number
                valueSerializer.writeNumber(valueHolderForSelectedTmpValueForIdx0)
            } else if (TypeChecker.isArray_Number(valueHolderForSelectedTmpValue)) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedTmpValueForIdx1  = valueHolderForSelectedTmpValue as Array<number>
                valueSerializer.writeInt32((valueHolderForSelectedTmpValueForIdx1.length).toInt())
                for (let valueHolderForSelectedTmpValueForIdx1CounterI = 0; valueHolderForSelectedTmpValueForIdx1CounterI < valueHolderForSelectedTmpValueForIdx1.length; valueHolderForSelectedTmpValueForIdx1CounterI++) {
                    const valueHolderForSelectedTmpValueForIdx1TmpElement : number = valueHolderForSelectedTmpValueForIdx1[valueHolderForSelectedTmpValueForIdx1CounterI]
                    valueSerializer.writeNumber(valueHolderForSelectedTmpValueForIdx1TmpElement)
                }
            } else if (valueHolderForSelectedTmpValue instanceof Bindable && valueHolderForSelectedTmpValue.value instanceof number) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedTmpValueForIdx2  = valueHolderForSelectedTmpValue as Bindable<number>
                Bindable_Number_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx2)
            } else if (valueHolderForSelectedTmpValue instanceof Bindable<Array<number>>) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedTmpValueForIdx3  = valueHolderForSelectedTmpValue as Bindable<Array<number>>
                Bindable_Array_Number_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColumnWidths  = value.columnWidths
        if (valueHolderForColumnWidths !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColumnWidthsTmpValue  = valueHolderForColumnWidths!
            valueSerializer.writeInt32((valueHolderForColumnWidthsTmpValue.length).toInt())
            for (let valueHolderForColumnWidthsTmpValueCounterI = 0; valueHolderForColumnWidthsTmpValueCounterI < valueHolderForColumnWidthsTmpValue.length; valueHolderForColumnWidthsTmpValueCounterI++) {
                const valueHolderForColumnWidthsTmpValueTmpElement : LengthMetrics = valueHolderForColumnWidthsTmpValue[valueHolderForColumnWidthsTmpValueCounterI]
                LengthMetrics_serializer.write(valueSerializer, valueHolderForColumnWidthsTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextPickerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const rangeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let rangeTmpBuf : Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> | undefined
        if (rangeTmpBufUnionSelector == (0).toChar()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<string> = new Array<string>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = (valueDeserializer.readString() as string)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (1).toChar()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<Array<string>> = new Array<Array<string>>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                const rangeTmpBufBufUTempBufLength : int32 = valueDeserializer.readInt32()
                let rangeTmpBufBufUTempBuf : Array<string> = new Array<string>(rangeTmpBufBufUTempBufLength)
                for (let rangeTmpBufBufUTempBufBufCounterI = 0; rangeTmpBufBufUTempBufBufCounterI < rangeTmpBufBufUTempBufLength; rangeTmpBufBufUTempBufBufCounterI++) {
                    rangeTmpBufBufUTempBuf[rangeTmpBufBufUTempBufBufCounterI] = (valueDeserializer.readString() as string)
                }
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = rangeTmpBufBufUTempBuf
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (2).toChar()) {
            rangeTmpBuf = Resource_serializer.read(valueDeserializer)
        } else if (rangeTmpBufUnionSelector == (3).toChar()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<TextPickerRangeContent> = new Array<TextPickerRangeContent>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = TextPickerRangeContent_serializer.read(valueDeserializer)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (4).toChar()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else {
            throw new Error("One of the branches for rangeTmpBuf has to be chosen through deserialisation.")
        }
        const rangeTmpResult : Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> = (rangeTmpBuf as Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>)
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let valueTmpBuf : ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>> | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBuf_ : ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>> | undefined
            if (valueTmpBuf_UnionSelector == (0).toChar()) {
                const valueTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let valueTmpBuf_BufU : string | Resource | undefined
                if (valueTmpBuf_BufUUnionSelector == (0).toChar()) {
                    valueTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (valueTmpBuf_BufUUnionSelector == (1).toChar()) {
                    valueTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for valueTmpBuf_BufU has to be chosen through deserialisation.")
                }
                valueTmpBuf_ = (valueTmpBuf_BufU as string | Resource)
            } else if (valueTmpBuf_UnionSelector == (1).toChar()) {
                const valueTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let valueTmpBuf_BufU : Array<ResourceStr> = new Array<ResourceStr>(valueTmpBuf_BufULength)
                for (let valueTmpBuf_BufUBufCounterI = 0; valueTmpBuf_BufUBufCounterI < valueTmpBuf_BufULength; valueTmpBuf_BufUBufCounterI++) {
                    const valueTmpBuf_BufUTempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let valueTmpBuf_BufUTempBuf : string | Resource | undefined
                    if (valueTmpBuf_BufUTempBufUnionSelector == (0).toChar()) {
                        valueTmpBuf_BufUTempBuf = (valueDeserializer.readString() as string)
                    } else if (valueTmpBuf_BufUTempBufUnionSelector == (1).toChar()) {
                        valueTmpBuf_BufUTempBuf = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for valueTmpBuf_BufUTempBuf has to be chosen through deserialisation.")
                    }
                    valueTmpBuf_BufU[valueTmpBuf_BufUBufCounterI] = (valueTmpBuf_BufUTempBuf as string | Resource)
                }
                valueTmpBuf_ = valueTmpBuf_BufU
            } else if (valueTmpBuf_UnionSelector == (2).toChar()) {
                valueTmpBuf_ = Bindable_Arkui_Component_Units_ResourceStr_serializer.read(valueDeserializer)
            } else if (valueTmpBuf_UnionSelector == (3).toChar()) {
                valueTmpBuf_ = Bindable_Array_Arkui_Component_Units_ResourceStr_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for valueTmpBuf_ has to be chosen through deserialisation.")
            }
            valueTmpBuf = (valueTmpBuf_ as ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>>)
        }
        const valueTmpResult : ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>> | undefined = valueTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTmpBuf : number | Array<number> | Bindable<number> | Bindable<Array<number>> | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let selectedTmpBuf_ : number | Array<number> | Bindable<number> | Bindable<Array<number>> | undefined
            if (selectedTmpBuf_UnionSelector == (0).toChar()) {
                selectedTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (selectedTmpBuf_UnionSelector == (1).toChar()) {
                const selectedTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let selectedTmpBuf_BufU : Array<number> = new Array<number>(selectedTmpBuf_BufULength)
                for (let selectedTmpBuf_BufUBufCounterI = 0; selectedTmpBuf_BufUBufCounterI < selectedTmpBuf_BufULength; selectedTmpBuf_BufUBufCounterI++) {
                    selectedTmpBuf_BufU[selectedTmpBuf_BufUBufCounterI] = (valueDeserializer.readNumber() as number)
                }
                selectedTmpBuf_ = selectedTmpBuf_BufU
            } else if (selectedTmpBuf_UnionSelector == (2).toChar()) {
                selectedTmpBuf_ = Bindable_Number_serializer.read(valueDeserializer)
            } else if (selectedTmpBuf_UnionSelector == (3).toChar()) {
                selectedTmpBuf_ = Bindable_Array_Number_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for selectedTmpBuf_ has to be chosen through deserialisation.")
            }
            selectedTmpBuf = (selectedTmpBuf_ as number | Array<number> | Bindable<number> | Bindable<Array<number>>)
        }
        const selectedTmpResult : number | Array<number> | Bindable<number> | Bindable<Array<number>> | undefined = selectedTmpBuf
        const columnWidthsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let columnWidthsTmpBuf : Array<LengthMetrics> | undefined = undefined
        if ((columnWidthsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const columnWidthsTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let columnWidthsTmpBuf_ : Array<LengthMetrics> = new Array<LengthMetrics>(columnWidthsTmpBuf_Length)
            for (let columnWidthsTmpBuf_BufCounterI = 0; columnWidthsTmpBuf_BufCounterI < columnWidthsTmpBuf_Length; columnWidthsTmpBuf_BufCounterI++) {
                columnWidthsTmpBuf_[columnWidthsTmpBuf_BufCounterI] = LengthMetrics_serializer.read(valueDeserializer)
            }
            columnWidthsTmpBuf = columnWidthsTmpBuf_
        }
        const columnWidthsTmpResult : Array<LengthMetrics> | undefined = columnWidthsTmpBuf
        let value : TextPickerOptions = ({range: rangeTmpResult, value: valueTmpResult, selected: selectedTmpResult, columnWidths: columnWidthsTmpResult} as TextPickerOptions)
        return value
    }
}
export class TextPickerTextStyle_serializer {
    public static write(buffer: SerializerBase, value: TextPickerTextStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFont  = value.font
        if (valueHolderForFont !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontTmpValue  = valueHolderForFont!
            Font_serializer.write(valueSerializer, valueHolderForFontTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMinFontSize  = value.minFontSize
        if (valueHolderForMinFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinFontSizeTmpValue  = valueHolderForMinFontSize!
            if (valueHolderForMinFontSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx0  = valueHolderForMinFontSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForMinFontSizeTmpValueForIdx0)
            } else if (valueHolderForMinFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx1  = valueHolderForMinFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForMinFontSizeTmpValueForIdx1)
            } else if (valueHolderForMinFontSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx2  = valueHolderForMinFontSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMinFontSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxFontSize  = value.maxFontSize
        if (valueHolderForMaxFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxFontSizeTmpValue  = valueHolderForMaxFontSize!
            if (valueHolderForMaxFontSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx0  = valueHolderForMaxFontSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForMaxFontSizeTmpValueForIdx0)
            } else if (valueHolderForMaxFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx1  = valueHolderForMaxFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForMaxFontSizeTmpValueForIdx1)
            } else if (valueHolderForMaxFontSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx2  = valueHolderForMaxFontSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMaxFontSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOverflow  = value.overflow
        if (valueHolderForOverflow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowTmpValue  = (valueHolderForOverflow as TextOverflow)
            valueSerializer.writeInt32(valueHolderForOverflowTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextPickerTextStyle {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | number | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | number | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const fontTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontTmpBuf : Font | undefined = undefined
        if ((fontTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontTmpBuf = Font_serializer.read(valueDeserializer)
        }
        const fontTmpResult : Font | undefined = fontTmpBuf
        const minFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minFontSizeTmpBuf : number | string | Resource | undefined = undefined
        if ((minFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minFontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let minFontSizeTmpBuf_ : number | string | Resource | undefined
            if (minFontSizeTmpBuf_UnionSelector == (0).toChar()) {
                minFontSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (minFontSizeTmpBuf_UnionSelector == (1).toChar()) {
                minFontSizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (minFontSizeTmpBuf_UnionSelector == (2).toChar()) {
                minFontSizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for minFontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            minFontSizeTmpBuf = (minFontSizeTmpBuf_ as number | string | Resource)
        }
        const minFontSizeTmpResult : number | string | Resource | undefined = minFontSizeTmpBuf
        const maxFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxFontSizeTmpBuf : number | string | Resource | undefined = undefined
        if ((maxFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxFontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let maxFontSizeTmpBuf_ : number | string | Resource | undefined
            if (maxFontSizeTmpBuf_UnionSelector == (0).toChar()) {
                maxFontSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (maxFontSizeTmpBuf_UnionSelector == (1).toChar()) {
                maxFontSizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (maxFontSizeTmpBuf_UnionSelector == (2).toChar()) {
                maxFontSizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for maxFontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            maxFontSizeTmpBuf = (maxFontSizeTmpBuf_ as number | string | Resource)
        }
        const maxFontSizeTmpResult : number | string | Resource | undefined = maxFontSizeTmpBuf
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflowTmpBuf : TextOverflow | undefined = undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            overflowTmpBuf = TextOverflow.fromValue(valueDeserializer.readInt32())
        }
        const overflowTmpResult : TextOverflow | undefined = overflowTmpBuf
        let value : TextPickerTextStyle = ({color: colorTmpResult, font: fontTmpResult, minFontSize: minFontSizeTmpResult, maxFontSize: maxFontSizeTmpResult, overflow: overflowTmpResult} as TextPickerTextStyle)
        return value
    }
}
export class TextPickerDialogOptions_serializer {
    public static write(buffer: SerializerBase, value: TextPickerDialogOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRange  = value.range
        if (TypeChecker.isArray_String(valueHolderForRange)) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForRangeForIdx0  = valueHolderForRange as Array<string>
            valueSerializer.writeInt32((valueHolderForRangeForIdx0.length).toInt())
            for (let valueHolderForRangeForIdx0CounterI = 0; valueHolderForRangeForIdx0CounterI < valueHolderForRangeForIdx0.length; valueHolderForRangeForIdx0CounterI++) {
                const valueHolderForRangeForIdx0TmpElement : string = valueHolderForRangeForIdx0[valueHolderForRangeForIdx0CounterI]
                valueSerializer.writeString(valueHolderForRangeForIdx0TmpElement)
            }
        } else if (TypeChecker.isArray_Array_String(valueHolderForRange)) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRangeForIdx1  = valueHolderForRange as Array<Array<string>>
            valueSerializer.writeInt32((valueHolderForRangeForIdx1.length).toInt())
            for (let valueHolderForRangeForIdx1CounterI = 0; valueHolderForRangeForIdx1CounterI < valueHolderForRangeForIdx1.length; valueHolderForRangeForIdx1CounterI++) {
                const valueHolderForRangeForIdx1TmpElement : Array<string> = valueHolderForRangeForIdx1[valueHolderForRangeForIdx1CounterI]
                valueSerializer.writeInt32((valueHolderForRangeForIdx1TmpElement.length).toInt())
                for (let valueHolderForRangeForIdx1TmpElementCounterI = 0; valueHolderForRangeForIdx1TmpElementCounterI < valueHolderForRangeForIdx1TmpElement.length; valueHolderForRangeForIdx1TmpElementCounterI++) {
                    const valueHolderForRangeForIdx1TmpElementTmpElement : string = valueHolderForRangeForIdx1TmpElement[valueHolderForRangeForIdx1TmpElementCounterI]
                    valueSerializer.writeString(valueHolderForRangeForIdx1TmpElementTmpElement)
                }
            }
        } else if (valueHolderForRange instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForRangeForIdx2  = valueHolderForRange as Resource
            Resource_serializer.write(valueSerializer, valueHolderForRangeForIdx2)
        } else if (TypeChecker.isArray_TextPickerRangeContent(valueHolderForRange)) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForRangeForIdx3  = valueHolderForRange as Array<TextPickerRangeContent>
            valueSerializer.writeInt32((valueHolderForRangeForIdx3.length).toInt())
            for (let valueHolderForRangeForIdx3CounterI = 0; valueHolderForRangeForIdx3CounterI < valueHolderForRangeForIdx3.length; valueHolderForRangeForIdx3CounterI++) {
                const valueHolderForRangeForIdx3TmpElement : TextPickerRangeContent = valueHolderForRangeForIdx3[valueHolderForRangeForIdx3CounterI]
                TextPickerRangeContent_serializer.write(valueSerializer, valueHolderForRangeForIdx3TmpElement)
            }
        } else if (TypeChecker.isArray_TextCascadePickerRangeContent(valueHolderForRange)) {
            valueSerializer.writeInt8((4).toByte())
            const valueHolderForRangeForIdx4  = valueHolderForRange as Array<TextCascadePickerRangeContent>
            valueSerializer.writeInt32((valueHolderForRangeForIdx4.length).toInt())
            for (let valueHolderForRangeForIdx4CounterI = 0; valueHolderForRangeForIdx4CounterI < valueHolderForRangeForIdx4.length; valueHolderForRangeForIdx4CounterI++) {
                const valueHolderForRangeForIdx4TmpElement : TextCascadePickerRangeContent = valueHolderForRangeForIdx4[valueHolderForRangeForIdx4CounterI]
                TextCascadePickerRangeContent_serializer.write(valueSerializer, valueHolderForRangeForIdx4TmpElement)
            }
        }
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            if (valueHolderForValueTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as ResourceStr
                if (valueHolderForValueTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx0  = valueHolderForValueTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForValueTmpValueForIdx0ForIdx0)
                } else if (valueHolderForValueTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx1  = valueHolderForValueTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx1)
                }
            } else if (TypeChecker.isArray_ResourceStr(valueHolderForValueTmpValue)) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForValueTmpValueForIdx1  = valueHolderForValueTmpValue as Array<ResourceStr>
                valueSerializer.writeInt32((valueHolderForValueTmpValueForIdx1.length).toInt())
                for (let valueHolderForValueTmpValueForIdx1CounterI = 0; valueHolderForValueTmpValueForIdx1CounterI < valueHolderForValueTmpValueForIdx1.length; valueHolderForValueTmpValueForIdx1CounterI++) {
                    const valueHolderForValueTmpValueForIdx1TmpElement : ResourceStr = valueHolderForValueTmpValueForIdx1[valueHolderForValueTmpValueForIdx1CounterI]
                    if (valueHolderForValueTmpValueForIdx1TmpElement instanceof string) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderForValueTmpValueForIdx1TmpElementForIdx0  = valueHolderForValueTmpValueForIdx1TmpElement as string
                        valueSerializer.writeString(valueHolderForValueTmpValueForIdx1TmpElementForIdx0)
                    } else if (valueHolderForValueTmpValueForIdx1TmpElement instanceof Resource) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForValueTmpValueForIdx1TmpElementForIdx1  = valueHolderForValueTmpValueForIdx1TmpElement as Resource
                        Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1TmpElementForIdx1)
                    }
                }
            } else if (valueHolderForValueTmpValue instanceof Bindable && valueHolderForValueTmpValue.value instanceof ResourceStr) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForValueTmpValueForIdx2  = valueHolderForValueTmpValue as Bindable<ResourceStr>
                Bindable_Arkui_Component_Units_ResourceStr_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx2)
            } else if (valueHolderForValueTmpValue instanceof Bindable<Array<ResourceStr>>) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForValueTmpValueForIdx3  = valueHolderForValueTmpValue as Bindable<Array<ResourceStr>>
                Bindable_Array_Arkui_Component_Units_ResourceStr_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            if (valueHolderForSelectedTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedTmpValueForIdx0  = valueHolderForSelectedTmpValue as number
                valueSerializer.writeNumber(valueHolderForSelectedTmpValueForIdx0)
            } else if (TypeChecker.isArray_Number(valueHolderForSelectedTmpValue)) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedTmpValueForIdx1  = valueHolderForSelectedTmpValue as Array<number>
                valueSerializer.writeInt32((valueHolderForSelectedTmpValueForIdx1.length).toInt())
                for (let valueHolderForSelectedTmpValueForIdx1CounterI = 0; valueHolderForSelectedTmpValueForIdx1CounterI < valueHolderForSelectedTmpValueForIdx1.length; valueHolderForSelectedTmpValueForIdx1CounterI++) {
                    const valueHolderForSelectedTmpValueForIdx1TmpElement : number = valueHolderForSelectedTmpValueForIdx1[valueHolderForSelectedTmpValueForIdx1CounterI]
                    valueSerializer.writeNumber(valueHolderForSelectedTmpValueForIdx1TmpElement)
                }
            } else if (valueHolderForSelectedTmpValue instanceof Bindable && valueHolderForSelectedTmpValue.value instanceof number) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedTmpValueForIdx2  = valueHolderForSelectedTmpValue as Bindable<number>
                Bindable_Number_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx2)
            } else if (valueHolderForSelectedTmpValue instanceof Bindable<Array<number>>) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedTmpValueForIdx3  = valueHolderForSelectedTmpValue as Bindable<Array<number>>
                Bindable_Array_Number_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColumnWidths  = value.columnWidths
        if (valueHolderForColumnWidths !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColumnWidthsTmpValue  = valueHolderForColumnWidths!
            valueSerializer.writeInt32((valueHolderForColumnWidthsTmpValue.length).toInt())
            for (let valueHolderForColumnWidthsTmpValueCounterI = 0; valueHolderForColumnWidthsTmpValueCounterI < valueHolderForColumnWidthsTmpValue.length; valueHolderForColumnWidthsTmpValueCounterI++) {
                const valueHolderForColumnWidthsTmpValueTmpElement : LengthMetrics = valueHolderForColumnWidthsTmpValue[valueHolderForColumnWidthsTmpValueCounterI]
                LengthMetrics_serializer.write(valueSerializer, valueHolderForColumnWidthsTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDefaultPickerItemHeight  = value.defaultPickerItemHeight
        if (valueHolderForDefaultPickerItemHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDefaultPickerItemHeightTmpValue  = valueHolderForDefaultPickerItemHeight!
            if (valueHolderForDefaultPickerItemHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForDefaultPickerItemHeightTmpValueForIdx0  = valueHolderForDefaultPickerItemHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForDefaultPickerItemHeightTmpValueForIdx0)
            } else if (valueHolderForDefaultPickerItemHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForDefaultPickerItemHeightTmpValueForIdx1  = valueHolderForDefaultPickerItemHeightTmpValue as string
                valueSerializer.writeString(valueHolderForDefaultPickerItemHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCanLoop  = value.canLoop
        if (valueHolderForCanLoop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCanLoopTmpValue  = valueHolderForCanLoop!
            valueSerializer.writeBoolean(valueHolderForCanLoopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDisappearTextStyle  = value.disappearTextStyle
        if (valueHolderForDisappearTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDisappearTextStyleTmpValue  = valueHolderForDisappearTextStyle!
            PickerTextStyle_serializer.write(valueSerializer, valueHolderForDisappearTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextStyle  = value.textStyle
        if (valueHolderForTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextStyleTmpValue  = valueHolderForTextStyle!
            PickerTextStyle_serializer.write(valueSerializer, valueHolderForTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAcceptButtonStyle  = value.acceptButtonStyle
        if (valueHolderForAcceptButtonStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAcceptButtonStyleTmpValue  = valueHolderForAcceptButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, valueHolderForAcceptButtonStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCancelButtonStyle  = value.cancelButtonStyle
        if (valueHolderForCancelButtonStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelButtonStyleTmpValue  = valueHolderForCancelButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, valueHolderForCancelButtonStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelectedTextStyle  = value.selectedTextStyle
        if (valueHolderForSelectedTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTextStyleTmpValue  = valueHolderForSelectedTextStyle!
            PickerTextStyle_serializer.write(valueSerializer, valueHolderForSelectedTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDisableTextStyleAnimation  = value.disableTextStyleAnimation
        if (valueHolderForDisableTextStyleAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDisableTextStyleAnimationTmpValue  = valueHolderForDisableTextStyleAnimation!
            valueSerializer.writeBoolean(valueHolderForDisableTextStyleAnimationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDefaultTextStyle  = value.defaultTextStyle
        if (valueHolderForDefaultTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDefaultTextStyleTmpValue  = valueHolderForDefaultTextStyle!
            TextPickerTextStyle_serializer.write(valueSerializer, valueHolderForDefaultTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnAccept  = value.onAccept
        if (valueHolderForOnAccept !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnAcceptTmpValue  = valueHolderForOnAccept!
            valueSerializer.holdAndWriteCallback(valueHolderForOnAcceptTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnCancel  = value.onCancel
        if (valueHolderForOnCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnCancelTmpValue  = valueHolderForOnCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForOnCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnChange  = value.onChange
        if (valueHolderForOnChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnChangeTmpValue  = valueHolderForOnChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnScrollStop  = value.onScrollStop
        if (valueHolderForOnScrollStop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnScrollStopTmpValue  = valueHolderForOnScrollStop!
            valueSerializer.holdAndWriteCallback(valueHolderForOnScrollStopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnEnterSelectedArea  = value.onEnterSelectedArea
        if (valueHolderForOnEnterSelectedArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnEnterSelectedAreaTmpValue  = valueHolderForOnEnterSelectedArea!
            valueSerializer.holdAndWriteCallback(valueHolderForOnEnterSelectedAreaTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskRect  = value.maskRect
        if (valueHolderForMaskRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskRectTmpValue  = valueHolderForMaskRect!
            Rectangle_serializer.write(valueSerializer, valueHolderForMaskRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignment  = value.alignment
        if (valueHolderForAlignment !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignmentTmpValue  = (valueHolderForAlignment as DialogAlignment)
            valueSerializer.writeInt32(valueHolderForAlignmentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            Offset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidAppear  = value.onDidAppear
        if (valueHolderForOnDidAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidAppearTmpValue  = valueHolderForOnDidAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidDisappear  = value.onDidDisappear
        if (valueHolderForOnDidDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidDisappearTmpValue  = valueHolderForOnDidDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillAppear  = value.onWillAppear
        if (valueHolderForOnWillAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillAppearTmpValue  = valueHolderForOnWillAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDisappear  = value.onWillDisappear
        if (valueHolderForOnWillDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDisappearTmpValue  = valueHolderForOnWillDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow  = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue  = valueHolderForShadow!
            if (valueHolderForShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShadowTmpValueForIdx0  = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShadowTmpValueForIdx1  = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(valueHolderForShadowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode  = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue  = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHoverModeArea  = value.hoverModeArea
        if (valueHolderForHoverModeArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHoverModeAreaTmpValue  = (valueHolderForHoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(valueHolderForHoverModeAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHapticFeedback  = value.enableHapticFeedback
        if (valueHolderForEnableHapticFeedback !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHapticFeedbackTmpValue  = valueHolderForEnableHapticFeedback!
            valueSerializer.writeBoolean(valueHolderForEnableHapticFeedbackTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextPickerDialogOptions {
        let valueDeserializer : DeserializerBase = buffer
        const rangeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let rangeTmpBuf : Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> | undefined
        if (rangeTmpBufUnionSelector == (0).toChar()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<string> = new Array<string>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = (valueDeserializer.readString() as string)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (1).toChar()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<Array<string>> = new Array<Array<string>>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                const rangeTmpBufBufUTempBufLength : int32 = valueDeserializer.readInt32()
                let rangeTmpBufBufUTempBuf : Array<string> = new Array<string>(rangeTmpBufBufUTempBufLength)
                for (let rangeTmpBufBufUTempBufBufCounterI = 0; rangeTmpBufBufUTempBufBufCounterI < rangeTmpBufBufUTempBufLength; rangeTmpBufBufUTempBufBufCounterI++) {
                    rangeTmpBufBufUTempBuf[rangeTmpBufBufUTempBufBufCounterI] = (valueDeserializer.readString() as string)
                }
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = rangeTmpBufBufUTempBuf
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (2).toChar()) {
            rangeTmpBuf = Resource_serializer.read(valueDeserializer)
        } else if (rangeTmpBufUnionSelector == (3).toChar()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<TextPickerRangeContent> = new Array<TextPickerRangeContent>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = TextPickerRangeContent_serializer.read(valueDeserializer)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (4).toChar()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else {
            throw new Error("One of the branches for rangeTmpBuf has to be chosen through deserialisation.")
        }
        const rangeTmpResult : Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> = (rangeTmpBuf as Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>)
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let valueTmpBuf : ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>> | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBuf_ : ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>> | undefined
            if (valueTmpBuf_UnionSelector == (0).toChar()) {
                const valueTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let valueTmpBuf_BufU : string | Resource | undefined
                if (valueTmpBuf_BufUUnionSelector == (0).toChar()) {
                    valueTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (valueTmpBuf_BufUUnionSelector == (1).toChar()) {
                    valueTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for valueTmpBuf_BufU has to be chosen through deserialisation.")
                }
                valueTmpBuf_ = (valueTmpBuf_BufU as string | Resource)
            } else if (valueTmpBuf_UnionSelector == (1).toChar()) {
                const valueTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let valueTmpBuf_BufU : Array<ResourceStr> = new Array<ResourceStr>(valueTmpBuf_BufULength)
                for (let valueTmpBuf_BufUBufCounterI = 0; valueTmpBuf_BufUBufCounterI < valueTmpBuf_BufULength; valueTmpBuf_BufUBufCounterI++) {
                    const valueTmpBuf_BufUTempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let valueTmpBuf_BufUTempBuf : string | Resource | undefined
                    if (valueTmpBuf_BufUTempBufUnionSelector == (0).toChar()) {
                        valueTmpBuf_BufUTempBuf = (valueDeserializer.readString() as string)
                    } else if (valueTmpBuf_BufUTempBufUnionSelector == (1).toChar()) {
                        valueTmpBuf_BufUTempBuf = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for valueTmpBuf_BufUTempBuf has to be chosen through deserialisation.")
                    }
                    valueTmpBuf_BufU[valueTmpBuf_BufUBufCounterI] = (valueTmpBuf_BufUTempBuf as string | Resource)
                }
                valueTmpBuf_ = valueTmpBuf_BufU
            } else if (valueTmpBuf_UnionSelector == (2).toChar()) {
                valueTmpBuf_ = Bindable_Arkui_Component_Units_ResourceStr_serializer.read(valueDeserializer)
            } else if (valueTmpBuf_UnionSelector == (3).toChar()) {
                valueTmpBuf_ = Bindable_Array_Arkui_Component_Units_ResourceStr_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for valueTmpBuf_ has to be chosen through deserialisation.")
            }
            valueTmpBuf = (valueTmpBuf_ as ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>>)
        }
        const valueTmpResult : ResourceStr | Array<ResourceStr> | Bindable<ResourceStr> | Bindable<Array<ResourceStr>> | undefined = valueTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTmpBuf : number | Array<number> | Bindable<number> | Bindable<Array<number>> | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let selectedTmpBuf_ : number | Array<number> | Bindable<number> | Bindable<Array<number>> | undefined
            if (selectedTmpBuf_UnionSelector == (0).toChar()) {
                selectedTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (selectedTmpBuf_UnionSelector == (1).toChar()) {
                const selectedTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let selectedTmpBuf_BufU : Array<number> = new Array<number>(selectedTmpBuf_BufULength)
                for (let selectedTmpBuf_BufUBufCounterI = 0; selectedTmpBuf_BufUBufCounterI < selectedTmpBuf_BufULength; selectedTmpBuf_BufUBufCounterI++) {
                    selectedTmpBuf_BufU[selectedTmpBuf_BufUBufCounterI] = (valueDeserializer.readNumber() as number)
                }
                selectedTmpBuf_ = selectedTmpBuf_BufU
            } else if (selectedTmpBuf_UnionSelector == (2).toChar()) {
                selectedTmpBuf_ = Bindable_Number_serializer.read(valueDeserializer)
            } else if (selectedTmpBuf_UnionSelector == (3).toChar()) {
                selectedTmpBuf_ = Bindable_Array_Number_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for selectedTmpBuf_ has to be chosen through deserialisation.")
            }
            selectedTmpBuf = (selectedTmpBuf_ as number | Array<number> | Bindable<number> | Bindable<Array<number>>)
        }
        const selectedTmpResult : number | Array<number> | Bindable<number> | Bindable<Array<number>> | undefined = selectedTmpBuf
        const columnWidthsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let columnWidthsTmpBuf : Array<LengthMetrics> | undefined = undefined
        if ((columnWidthsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const columnWidthsTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let columnWidthsTmpBuf_ : Array<LengthMetrics> = new Array<LengthMetrics>(columnWidthsTmpBuf_Length)
            for (let columnWidthsTmpBuf_BufCounterI = 0; columnWidthsTmpBuf_BufCounterI < columnWidthsTmpBuf_Length; columnWidthsTmpBuf_BufCounterI++) {
                columnWidthsTmpBuf_[columnWidthsTmpBuf_BufCounterI] = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
            }
            columnWidthsTmpBuf = columnWidthsTmpBuf_
        }
        const columnWidthsTmpResult : Array<LengthMetrics> | undefined = columnWidthsTmpBuf
        const defaultPickerItemHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let defaultPickerItemHeightTmpBuf : number | string | undefined = undefined
        if ((defaultPickerItemHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const defaultPickerItemHeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let defaultPickerItemHeightTmpBuf_ : number | string | undefined
            if (defaultPickerItemHeightTmpBuf_UnionSelector == (0).toChar()) {
                defaultPickerItemHeightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (defaultPickerItemHeightTmpBuf_UnionSelector == (1).toChar()) {
                defaultPickerItemHeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for defaultPickerItemHeightTmpBuf_ has to be chosen through deserialisation.")
            }
            defaultPickerItemHeightTmpBuf = (defaultPickerItemHeightTmpBuf_ as number | string)
        }
        const defaultPickerItemHeightTmpResult : number | string | undefined = defaultPickerItemHeightTmpBuf
        const canLoopTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let canLoopTmpBuf : boolean | undefined = undefined
        if ((canLoopTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            canLoopTmpBuf = valueDeserializer.readBoolean()
        }
        const canLoopTmpResult : boolean | undefined = canLoopTmpBuf
        const disappearTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disappearTextStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((disappearTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            disappearTextStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const disappearTextStyleTmpResult : PickerTextStyle | undefined = disappearTextStyleTmpBuf
        const textStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((textStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const textStyleTmpResult : PickerTextStyle | undefined = textStyleTmpBuf
        const acceptButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let acceptButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((acceptButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            acceptButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const acceptButtonStyleTmpResult : PickerDialogButtonStyle | undefined = acceptButtonStyleTmpBuf
        const cancelButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((cancelButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            cancelButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const cancelButtonStyleTmpResult : PickerDialogButtonStyle | undefined = cancelButtonStyleTmpBuf
        const selectedTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTextStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((selectedTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedTextStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const selectedTextStyleTmpResult : PickerTextStyle | undefined = selectedTextStyleTmpBuf
        const disableTextStyleAnimationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disableTextStyleAnimationTmpBuf : boolean | undefined = undefined
        if ((disableTextStyleAnimationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            disableTextStyleAnimationTmpBuf = valueDeserializer.readBoolean()
        }
        const disableTextStyleAnimationTmpResult : boolean | undefined = disableTextStyleAnimationTmpBuf
        const defaultTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let defaultTextStyleTmpBuf : TextPickerTextStyle | undefined = undefined
        if ((defaultTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            defaultTextStyleTmpBuf = TextPickerTextStyle_serializer.read(valueDeserializer)
        }
        const defaultTextStyleTmpResult : TextPickerTextStyle | undefined = defaultTextStyleTmpBuf
        const onAcceptTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onAcceptTmpBuf : ((value: TextPickerResult) => void) | undefined = undefined
        if ((onAcceptTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAcceptTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAcceptTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onAcceptTmpBuf = (value: TextPickerResult):void => {
                const onAcceptTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onAcceptTmpBuf_BufArgsSerializer.writeInt32(onAcceptTmpBuf_BufResource.resourceId);
                onAcceptTmpBuf_BufArgsSerializer.writePointer(onAcceptTmpBuf_BufCall);
                onAcceptTmpBuf_BufArgsSerializer.writePointer(onAcceptTmpBuf_BufCallSync);
                TextPickerResult_serializer.write(onAcceptTmpBuf_BufArgsSerializer, value);
                InteropNativeModule._CallCallbackSync(10, 1290504509, onAcceptTmpBuf_BufArgsSerializer.asBuffer(), onAcceptTmpBuf_BufArgsSerializer.length());
                onAcceptTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onAcceptTmpResult : ((value: TextPickerResult) => void) | undefined = onAcceptTmpBuf
        const onCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onCancelTmpBuf : (() => void) | undefined = undefined
        if ((onCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onCancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onCancelTmpBuf = ():void => {
                const onCancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onCancelTmpBuf_BufArgsSerializer.writeInt32(onCancelTmpBuf_BufResource.resourceId);
                onCancelTmpBuf_BufArgsSerializer.writePointer(onCancelTmpBuf_BufCall);
                onCancelTmpBuf_BufArgsSerializer.writePointer(onCancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onCancelTmpBuf_BufArgsSerializer.asBuffer(), onCancelTmpBuf_BufArgsSerializer.length());
                onCancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onCancelTmpResult : (() => void) | undefined = onCancelTmpBuf
        const onChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onChangeTmpBuf : ((value: TextPickerResult) => void) | undefined = undefined
        if ((onChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onChangeTmpBuf = (value: TextPickerResult):void => {
                const onChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onChangeTmpBuf_BufArgsSerializer.writeInt32(onChangeTmpBuf_BufResource.resourceId);
                onChangeTmpBuf_BufArgsSerializer.writePointer(onChangeTmpBuf_BufCall);
                onChangeTmpBuf_BufArgsSerializer.writePointer(onChangeTmpBuf_BufCallSync);
                TextPickerResult_serializer.write(onChangeTmpBuf_BufArgsSerializer, value);
                InteropNativeModule._CallCallbackSync(10, 1290504509, onChangeTmpBuf_BufArgsSerializer.asBuffer(), onChangeTmpBuf_BufArgsSerializer.length());
                onChangeTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onChangeTmpResult : ((value: TextPickerResult) => void) | undefined = onChangeTmpBuf
        const onScrollStopTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onScrollStopTmpBuf : ((value: TextPickerResult) => void) | undefined = undefined
        if ((onScrollStopTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onScrollStopTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onScrollStopTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onScrollStopTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onScrollStopTmpBuf = (value: TextPickerResult):void => {
                const onScrollStopTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onScrollStopTmpBuf_BufArgsSerializer.writeInt32(onScrollStopTmpBuf_BufResource.resourceId);
                onScrollStopTmpBuf_BufArgsSerializer.writePointer(onScrollStopTmpBuf_BufCall);
                onScrollStopTmpBuf_BufArgsSerializer.writePointer(onScrollStopTmpBuf_BufCallSync);
                TextPickerResult_serializer.write(onScrollStopTmpBuf_BufArgsSerializer, value);
                InteropNativeModule._CallCallbackSync(10, 1290504509, onScrollStopTmpBuf_BufArgsSerializer.asBuffer(), onScrollStopTmpBuf_BufArgsSerializer.length());
                onScrollStopTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onScrollStopTmpResult : ((value: TextPickerResult) => void) | undefined = onScrollStopTmpBuf
        const onEnterSelectedAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onEnterSelectedAreaTmpBuf : ((value: TextPickerResult) => void) | undefined = undefined
        if ((onEnterSelectedAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onEnterSelectedAreaTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onEnterSelectedAreaTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onEnterSelectedAreaTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onEnterSelectedAreaTmpBuf = (value: TextPickerResult):void => {
                const onEnterSelectedAreaTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onEnterSelectedAreaTmpBuf_BufArgsSerializer.writeInt32(onEnterSelectedAreaTmpBuf_BufResource.resourceId);
                onEnterSelectedAreaTmpBuf_BufArgsSerializer.writePointer(onEnterSelectedAreaTmpBuf_BufCall);
                onEnterSelectedAreaTmpBuf_BufArgsSerializer.writePointer(onEnterSelectedAreaTmpBuf_BufCallSync);
                TextPickerResult_serializer.write(onEnterSelectedAreaTmpBuf_BufArgsSerializer, value);
                InteropNativeModule._CallCallbackSync(10, 1290504509, onEnterSelectedAreaTmpBuf_BufArgsSerializer.asBuffer(), onEnterSelectedAreaTmpBuf_BufArgsSerializer.length());
                onEnterSelectedAreaTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onEnterSelectedAreaTmpResult : ((value: TextPickerResult) => void) | undefined = onEnterSelectedAreaTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetTmpBuf : Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : (() => void) | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : (() => void) | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : (() => void) | undefined = onWillDisappearTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBuf_ : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBuf_UnionSelector == (0).toChar()) {
                shadowTmpBuf_ = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBuf_UnionSelector == (1).toChar()) {
                shadowTmpBuf_ = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for shadowTmpBuf_ has to be chosen through deserialisation.")
            }
            shadowTmpBuf = (shadowTmpBuf_ as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const enableHapticFeedbackTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHapticFeedbackTmpBuf : boolean | undefined = undefined
        if ((enableHapticFeedbackTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHapticFeedbackTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHapticFeedbackTmpResult : boolean | undefined = enableHapticFeedbackTmpBuf
        let value : TextPickerDialogOptions = ({range: rangeTmpResult, value: valueTmpResult, selected: selectedTmpResult, columnWidths: columnWidthsTmpResult, defaultPickerItemHeight: defaultPickerItemHeightTmpResult, canLoop: canLoopTmpResult, disappearTextStyle: disappearTextStyleTmpResult, textStyle: textStyleTmpResult, acceptButtonStyle: acceptButtonStyleTmpResult, cancelButtonStyle: cancelButtonStyleTmpResult, selectedTextStyle: selectedTextStyleTmpResult, disableTextStyleAnimation: disableTextStyleAnimationTmpResult, defaultTextStyle: defaultTextStyleTmpResult, onAccept: onAcceptTmpResult, onCancel: onCancelTmpResult, onChange: onChangeTmpResult, onScrollStop: onScrollStopTmpResult, onEnterSelectedArea: onEnterSelectedAreaTmpResult, maskRect: maskRectTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, shadow: shadowTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, enableHapticFeedback: enableHapticFeedbackTmpResult} as TextPickerDialogOptions)
        return value
    }
}
