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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, BindableResourceStr, Bindable, BindableResourceStrArray, PickerDialogButtonStyle, Callback as arkui_component_common_Callback, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, Bindable_ResourceStr_serializer, Bindable_Resource_serializer, Bindable_String_serializer, Bindable_Array_ResourceStr_serializer, Bindable_Array_Resource_serializer, Bindable_Array_String_serializer, Bindable_I32_serializer, Bindable_Array_I32_serializer, PickerDialogButtonStyle_serializer, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ShadowOptions_serializer } from './common'
import { global_resource_Resource_serializer } from './../framework/resource'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { Dimension, Resource as arkui_component_units_Resource, ResourceStr as arkui_component_units_ResourceStr, ResourceColor, Offset, arkui_component_units_Font_serializer, Font as arkui_component_units_Font, Offset_serializer } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { CrownSensitivity, Color as arkui_component_enums_Color, TextOverflow } from './enums'
import { AttributeModifier, hookTextPickerDivider, hookTextPickerAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from '@arkui.Graphics'
import { DialogAlignment } from './alertDialog'
import { TextPickerModifier } from './../TextPickerModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
export class ArkTextPickerPeer extends ArkCommonMethodPeer {
    attributeSet?: TextPickerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
    setDefaultPickerItemHeightAttribute(value: double | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
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
    setSelectedIndexAttribute(value: int32 | Array<int32> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Array) {
                if (valueTmpValue.length == 0) {
                    thisSerializer.writeInt8((1).toByte())
                    thisSerializer.writeInt32(0)
                } else {
                    const valueTmpValueElem  = valueTmpValue[0]
                    if (valueTmpValueElem instanceof int32) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueForIdx1  = valueTmpValue as Array<int32>
                        thisSerializer.writeInt32((valueTmpValueForIdx1.length).toInt())
                        for (let valueTmpValueForIdx1CounterI = 0; valueTmpValueForIdx1CounterI < valueTmpValueForIdx1.length; valueTmpValueForIdx1CounterI++) {
                            const valueTmpValueForIdx1TmpElement : int32 = valueTmpValueForIdx1[valueTmpValueForIdx1CounterI]
                            thisSerializer.writeInt32(valueTmpValueForIdx1TmpElement)
                        }
                    }
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
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
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
    icon: string | arkui_component_units_Resource;
    text?: string | arkui_component_units_Resource;
}
export interface TextCascadePickerRangeContent {
    text: string | arkui_component_units_Resource;
    children?: Array<TextCascadePickerRangeContent>;
}
export interface TextPickerOptions {
    range: Array<string> | Array<Array<string>> | arkui_component_units_Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>;
    value?: BindableResourceStr | BindableResourceStrArray;
    selected?: int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>>;
    columnWidths?: Array<arkui_Graphics_LengthMetrics>;
}
export interface DividerOptions {
    strokeWidth?: Dimension;
    color?: ResourceColor;
    startMargin?: Dimension;
    endMargin?: Dimension;
}
export interface TextPickerTextStyle extends PickerTextStyle {
    minFontSize?: double | string | arkui_component_units_Resource;
    maxFontSize?: double | string | arkui_component_units_Resource;
    overflow?: TextOverflow;
}
export type TextPickerScrollStopCallback = (value: string | Array<string>, index: int32 | Array<int32>) => void;
export type OnTextPickerChangeCallback = (selectItem: string | Array<string>, index: int32 | Array<int32>) => void;
export type TextPickerEnterSelectedAreaCallback = (value: string | Array<string>, index: int32 | Array<int32>) => void;
export interface TextPickerAttribute extends CommonMethod {
    setTextPickerOptions(options?: TextPickerOptions): this {
        throw new Error('Unimplemented method setTextPickerOptions')
    }
    defaultPickerItemHeight(value: double | string | undefined): this {
        throw new Error('Unimplemented method defaultPickerItemHeight')
    }
    canLoop(value: boolean | undefined): this {
        throw new Error('Unimplemented method canLoop')
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        throw new Error('Unimplemented method disappearTextStyle')
    }
    textStyle(value: PickerTextStyle | undefined): this {
        throw new Error('Unimplemented method textStyle')
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        throw new Error('Unimplemented method selectedTextStyle')
    }
    disableTextStyleAnimation(value: boolean | undefined): this {
        throw new Error('Unimplemented method disableTextStyleAnimation')
    }
    defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        throw new Error('Unimplemented method defaultTextStyle')
    }
    onChange(value: OnTextPickerChangeCallback | undefined): this {
        throw new Error('Unimplemented method onChange')
    }
    onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        throw new Error('Unimplemented method onScrollStop')
    }
    onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        throw new Error('Unimplemented method onEnterSelectedArea')
    }
    selectedIndex(value: int32 | Array<int32> | undefined): this {
        throw new Error('Unimplemented method selectedIndex')
    }
    divider(value: DividerOptions | null | undefined): this {
        throw new Error('Unimplemented method divider')
    }
    gradientHeight(value: Dimension | undefined): this {
        throw new Error('Unimplemented method gradientHeight')
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableHapticFeedback')
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error('Unimplemented method digitalCrownSensitivity')
    }
    attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface TextPickerResult {
    value: string | Array<string>;
    index: int32 | Array<int32>;
}
export interface TextPickerDialogOptions extends TextPickerOptions {
    defaultPickerItemHeight?: double | string;
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
    onScrollStop?: arkui_component_common_Callback<TextPickerResult, void>;
    onEnterSelectedArea?: arkui_component_common_Callback<TextPickerResult, void>;
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
        if (this.checkPriority('setTextPickerOptions')) {
            const options_casted = options as (TextPickerOptions | undefined)
            this.getPeer()?.setTextPickerOptionsAttribute(options_casted)
            this.applyOptionsFinish('TextPickerAttribute');
            return this
        }
        return this
    }
    public defaultPickerItemHeight(value: double | string | undefined): this {
        if (this.checkPriority('defaultPickerItemHeight')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setDefaultPickerItemHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public canLoop(value: boolean | undefined): this {
        if (this.checkPriority('canLoop')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setCanLoopAttribute(value_casted)
            return this
        }
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority('disappearTextStyle')) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setDisappearTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority('textStyle')) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority('selectedTextStyle')) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setSelectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public disableTextStyleAnimation(value: boolean | undefined): this {
        if (this.checkPriority('disableTextStyleAnimation')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDisableTextStyleAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        if (this.checkPriority('defaultTextStyle')) {
            const value_casted = value as (TextPickerTextStyle | undefined)
            this.getPeer()?.setDefaultTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnTextPickerChangeCallback | undefined): this {
        if (this.checkPriority('onChange')) {
            const value_casted = value as (OnTextPickerChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        if (this.checkPriority('onScrollStop')) {
            const value_casted = value as (TextPickerScrollStopCallback | undefined)
            this.getPeer()?.setOnScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    public onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        if (this.checkPriority('onEnterSelectedArea')) {
            const value_casted = value as (TextPickerEnterSelectedAreaCallback | undefined)
            this.getPeer()?.setOnEnterSelectedAreaAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedIndex(value: int32 | Array<int32> | undefined): this {
        if (this.checkPriority('selectedIndex')) {
            const value_casted = value as (int32 | Array<int32> | undefined)
            this.getPeer()?.setSelectedIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: DividerOptions | null | undefined): this {
        if (this.checkPriority('divider')) {
            hookTextPickerDivider(this, value)
            const value_casted = value as (DividerOptions | null | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public gradientHeight(value: Dimension | undefined): this {
        if (this.checkPriority('gradientHeight')) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setGradientHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority('enableHapticFeedback')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority('digitalCrownSensitivity')) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookTextPickerAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function TextPickerImpl(
    @memo @memo_skip
    style: ((attributes: TextPickerAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkTextPickerComponent>((): ArkTextPickerComponent => {
        return new ArkTextPickerComponent()
    })
    NodeAttach<ArkTextPickerPeer>((): ArkTextPickerPeer => ArkTextPickerPeer.create(receiver), (_: ArkTextPickerPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class TextCascadePickerRangeContent_serializer {
    public static write(buffer: SerializerBase, value: TextCascadePickerRangeContent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForText  = value.text
        if (valueHolderForText instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForTextForIdx0  = valueHolderForText as string
            valueSerializer.writeString(valueHolderForTextForIdx0)
        } else if (valueHolderForText instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForTextForIdx1  = valueHolderForText as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForTextForIdx1)
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
        let textTmpBuf : string | arkui_component_units_Resource | undefined
        if (textTmpBufUnionSelector == (0).toByte()) {
            textTmpBuf = (valueDeserializer.readString() as string)
        } else if (textTmpBufUnionSelector == (1).toByte()) {
            textTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for textTmpBuf has to be chosen through deserialisation.')
        }
        const textTmpResult : string | arkui_component_units_Resource = (textTmpBuf as string | arkui_component_units_Resource)
        const childrenTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let childrenTmpBuf : Array<TextCascadePickerRangeContent> | undefined = undefined
        if ((childrenTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const childrenTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let childrenTmpBufOpt : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(childrenTmpBufOptLength)
            for (let childrenTmpBufOptBufCounterI = 0; childrenTmpBufOptBufCounterI < childrenTmpBufOptLength; childrenTmpBufOptBufCounterI++) {
                childrenTmpBufOpt[childrenTmpBufOptBufCounterI] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            childrenTmpBuf = childrenTmpBufOpt
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
        } else if (valueHolderForIcon instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForIconForIdx1  = valueHolderForIcon as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForIconForIdx1)
        }
        const valueHolderForText  = value.text
        if (valueHolderForText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextTmpValue  = valueHolderForText!
            if (valueHolderForTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextTmpValueForIdx0  = valueHolderForTextTmpValue as string
                valueSerializer.writeString(valueHolderForTextTmpValueForIdx0)
            } else if (valueHolderForTextTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTextTmpValueForIdx1  = valueHolderForTextTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextPickerRangeContent {
        let valueDeserializer : DeserializerBase = buffer
        const iconTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconTmpBuf : string | arkui_component_units_Resource | undefined
        if (iconTmpBufUnionSelector == (0).toByte()) {
            iconTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconTmpBufUnionSelector == (1).toByte()) {
            iconTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for iconTmpBuf has to be chosen through deserialisation.')
        }
        const iconTmpResult : string | arkui_component_units_Resource = (iconTmpBuf as string | arkui_component_units_Resource)
        const textTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textTmpBuf : string | arkui_component_units_Resource | undefined = undefined
        if ((textTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let textTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (textTmpBufOptUnionSelector == (0).toByte()) {
                textTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (textTmpBufOptUnionSelector == (1).toByte()) {
                textTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for textTmpBufOpt has to be chosen through deserialisation.')
            }
            textTmpBuf = (textTmpBufOpt as string | arkui_component_units_Resource)
        }
        const textTmpResult : string | arkui_component_units_Resource | undefined = textTmpBuf
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
        } else if (valueHolderForValue instanceof Array) {
            if (valueHolderForValue.length == 0) {
                valueSerializer.writeInt8((1).toByte())
                valueSerializer.writeInt32(0)
            } else {
                const valueHolderForValueElem  = valueHolderForValue[0]
                if (valueHolderForValueElem instanceof string) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForValueForIdx1  = valueHolderForValue as Array<string>
                    valueSerializer.writeInt32((valueHolderForValueForIdx1.length).toInt())
                    for (let valueHolderForValueForIdx1CounterI = 0; valueHolderForValueForIdx1CounterI < valueHolderForValueForIdx1.length; valueHolderForValueForIdx1CounterI++) {
                        const valueHolderForValueForIdx1TmpElement : string = valueHolderForValueForIdx1[valueHolderForValueForIdx1CounterI]
                        valueSerializer.writeString(valueHolderForValueForIdx1TmpElement)
                    }
                }
            }
        }
        const valueHolderForIndex  = value.index
        if (valueHolderForIndex instanceof int32) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForIndexForIdx0  = valueHolderForIndex as int32
            valueSerializer.writeInt32(valueHolderForIndexForIdx0)
        } else if (valueHolderForIndex instanceof Array) {
            if (valueHolderForIndex.length == 0) {
                valueSerializer.writeInt8((1).toByte())
                valueSerializer.writeInt32(0)
            } else {
                const valueHolderForIndexElem  = valueHolderForIndex[0]
                if (valueHolderForIndexElem instanceof int32) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForIndexForIdx1  = valueHolderForIndex as Array<int32>
                    valueSerializer.writeInt32((valueHolderForIndexForIdx1.length).toInt())
                    for (let valueHolderForIndexForIdx1CounterI = 0; valueHolderForIndexForIdx1CounterI < valueHolderForIndexForIdx1.length; valueHolderForIndexForIdx1CounterI++) {
                        const valueHolderForIndexForIdx1TmpElement : int32 = valueHolderForIndexForIdx1[valueHolderForIndexForIdx1CounterI]
                        valueSerializer.writeInt32(valueHolderForIndexForIdx1TmpElement)
                    }
                }
            }
        }
    }
    public static read(buffer: DeserializerBase): TextPickerResult {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | Array<string> | undefined
        if (valueTmpBufUnionSelector == (0).toByte()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toByte()) {
            const valueTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let valueTmpBufBufU : Array<string> = new Array<string>(valueTmpBufBufULength)
            for (let valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
                valueTmpBufBufU[valueTmpBufBufUBufCounterI] = (valueDeserializer.readString() as string)
            }
            valueTmpBuf = valueTmpBufBufU
        } else {
            throw new Error('One of the branches for valueTmpBuf has to be chosen through deserialisation.')
        }
        const valueTmpResult : string | Array<string> = (valueTmpBuf as string | Array<string>)
        const indexTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let indexTmpBuf : int32 | Array<int32> | undefined
        if (indexTmpBufUnionSelector == (0).toByte()) {
            indexTmpBuf = valueDeserializer.readInt32()
        } else if (indexTmpBufUnionSelector == (1).toByte()) {
            const indexTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let indexTmpBufBufU : Array<int32> = new Array<int32>(indexTmpBufBufULength)
            for (let indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
                indexTmpBufBufU[indexTmpBufBufUBufCounterI] = valueDeserializer.readInt32()
            }
            indexTmpBuf = indexTmpBufBufU
        } else {
            throw new Error('One of the branches for indexTmpBuf has to be chosen through deserialisation.')
        }
        const indexTmpResult : int32 | Array<int32> = (indexTmpBuf as int32 | Array<int32>)
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
            } else if (valueHolderForStrokeWidthTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx2  = valueHolderForStrokeWidthTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
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
            } else if (valueHolderForStartMarginTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStartMarginTmpValueForIdx2  = valueHolderForStartMarginTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStartMarginTmpValueForIdx2)
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
            } else if (valueHolderForEndMarginTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForEndMarginTmpValueForIdx2  = valueHolderForEndMarginTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForEndMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DividerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeWidthTmpBuf : Dimension | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let strokeWidthTmpBufOpt : string | number | global_resource_Resource | undefined
            if (strokeWidthTmpBufOptUnionSelector == (0).toByte()) {
                strokeWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (strokeWidthTmpBufOptUnionSelector == (1).toByte()) {
                strokeWidthTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (strokeWidthTmpBufOptUnionSelector == (2).toByte()) {
                strokeWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for strokeWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            strokeWidthTmpBuf = (strokeWidthTmpBufOpt as string | number | global_resource_Resource)
        }
        const strokeWidthTmpResult : Dimension | undefined = strokeWidthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = valueDeserializer.readInt32()
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (colorTmpBufOptUnionSelector == (3).toByte()) {
                colorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const startMarginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startMarginTmpBuf : Dimension | undefined = undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startMarginTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let startMarginTmpBufOpt : string | number | global_resource_Resource | undefined
            if (startMarginTmpBufOptUnionSelector == (0).toByte()) {
                startMarginTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (startMarginTmpBufOptUnionSelector == (1).toByte()) {
                startMarginTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (startMarginTmpBufOptUnionSelector == (2).toByte()) {
                startMarginTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for startMarginTmpBufOpt has to be chosen through deserialisation.')
            }
            startMarginTmpBuf = (startMarginTmpBufOpt as string | number | global_resource_Resource)
        }
        const startMarginTmpResult : Dimension | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endMarginTmpBuf : Dimension | undefined = undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endMarginTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let endMarginTmpBufOpt : string | number | global_resource_Resource | undefined
            if (endMarginTmpBufOptUnionSelector == (0).toByte()) {
                endMarginTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (endMarginTmpBufOptUnionSelector == (1).toByte()) {
                endMarginTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (endMarginTmpBufOptUnionSelector == (2).toByte()) {
                endMarginTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for endMarginTmpBufOpt has to be chosen through deserialisation.')
            }
            endMarginTmpBuf = (endMarginTmpBufOpt as string | number | global_resource_Resource)
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
        if (valueHolderForRange instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForRangeForIdx2  = valueHolderForRange as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForRangeForIdx2)
        } else if (valueHolderForRange instanceof Array) {
            if (valueHolderForRange.length == 0) {
                valueSerializer.writeInt8((0).toByte())
                valueSerializer.writeInt32(0)
            } else {
                const valueHolderForRangeElem  = valueHolderForRange[0]
                if (valueHolderForRangeElem instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForRangeForIdx0  = valueHolderForRange as Array<string>
                    valueSerializer.writeInt32((valueHolderForRangeForIdx0.length).toInt())
                    for (let valueHolderForRangeForIdx0CounterI = 0; valueHolderForRangeForIdx0CounterI < valueHolderForRangeForIdx0.length; valueHolderForRangeForIdx0CounterI++) {
                        const valueHolderForRangeForIdx0TmpElement : string = valueHolderForRangeForIdx0[valueHolderForRangeForIdx0CounterI]
                        valueSerializer.writeString(valueHolderForRangeForIdx0TmpElement)
                    }
                } else if (valueHolderForRangeElem instanceof TextPickerRangeContent) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForRangeForIdx3  = valueHolderForRange as Array<TextPickerRangeContent>
                    valueSerializer.writeInt32((valueHolderForRangeForIdx3.length).toInt())
                    for (let valueHolderForRangeForIdx3CounterI = 0; valueHolderForRangeForIdx3CounterI < valueHolderForRangeForIdx3.length; valueHolderForRangeForIdx3CounterI++) {
                        const valueHolderForRangeForIdx3TmpElement : TextPickerRangeContent = valueHolderForRangeForIdx3[valueHolderForRangeForIdx3CounterI]
                        TextPickerRangeContent_serializer.write(valueSerializer, valueHolderForRangeForIdx3TmpElement)
                    }
                } else if (valueHolderForRangeElem instanceof TextCascadePickerRangeContent) {
                    valueSerializer.writeInt8((4).toByte())
                    const valueHolderForRangeForIdx4  = valueHolderForRange as Array<TextCascadePickerRangeContent>
                    valueSerializer.writeInt32((valueHolderForRangeForIdx4.length).toInt())
                    for (let valueHolderForRangeForIdx4CounterI = 0; valueHolderForRangeForIdx4CounterI < valueHolderForRangeForIdx4.length; valueHolderForRangeForIdx4CounterI++) {
                        const valueHolderForRangeForIdx4TmpElement : TextCascadePickerRangeContent = valueHolderForRangeForIdx4[valueHolderForRangeForIdx4CounterI]
                        TextCascadePickerRangeContent_serializer.write(valueSerializer, valueHolderForRangeForIdx4TmpElement)
                    }
                } else if (valueHolderForRangeElem instanceof Array) {
                    if (valueHolderForRangeElem.length == 0) {
                        valueSerializer.writeInt8((1).toByte())
                        valueSerializer.writeInt32(0)
                    } else {
                        const valueHolderForRangeElemElem  = valueHolderForRangeElem[0]
                        if (valueHolderForRangeElemElem instanceof string) {
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
                        }
                    }
                }
            }
        }
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            if (valueHolderForValueTmpValue instanceof BindableResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as BindableResourceStr
                if (valueHolderForValueTmpValueForIdx0 instanceof arkui_component_units_ResourceStr) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx0  = valueHolderForValueTmpValueForIdx0 as arkui_component_units_ResourceStr
                    if (valueHolderForValueTmpValueForIdx0ForIdx0 instanceof string) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderForValueTmpValueForIdx0ForIdx0ForIdx0  = valueHolderForValueTmpValueForIdx0ForIdx0 as string
                        valueSerializer.writeString(valueHolderForValueTmpValueForIdx0ForIdx0ForIdx0)
                    } else if (valueHolderForValueTmpValueForIdx0ForIdx0 instanceof arkui_component_units_Resource) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForValueTmpValueForIdx0ForIdx0ForIdx1  = valueHolderForValueTmpValueForIdx0ForIdx0 as arkui_component_units_Resource
                        global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx0ForIdx1)
                    }
                } else if (valueHolderForValueTmpValueForIdx0 instanceof Bindable) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx1  = valueHolderForValueTmpValueForIdx0 as Bindable<arkui_component_units_ResourceStr>
                    Bindable_ResourceStr_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx1)
                } else if (valueHolderForValueTmpValueForIdx0 instanceof Bindable) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx2  = valueHolderForValueTmpValueForIdx0 as Bindable<global_resource_Resource>
                    Bindable_Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx2)
                } else if (valueHolderForValueTmpValueForIdx0 instanceof Bindable) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx3  = valueHolderForValueTmpValueForIdx0 as Bindable<string>
                    Bindable_String_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForValueTmpValue instanceof BindableResourceStrArray) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForValueTmpValueForIdx1  = valueHolderForValueTmpValue as BindableResourceStrArray
                if (valueHolderForValueTmpValueForIdx1 instanceof Bindable) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForValueTmpValueForIdx1ForIdx1  = valueHolderForValueTmpValueForIdx1 as Bindable<Array<arkui_component_units_ResourceStr>>
                    Bindable_Array_ResourceStr_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1ForIdx1)
                } else if (valueHolderForValueTmpValueForIdx1 instanceof Bindable) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForValueTmpValueForIdx1ForIdx2  = valueHolderForValueTmpValueForIdx1 as Bindable<Array<global_resource_Resource>>
                    Bindable_Array_Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1ForIdx2)
                } else if (valueHolderForValueTmpValueForIdx1 instanceof Bindable) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForValueTmpValueForIdx1ForIdx3  = valueHolderForValueTmpValueForIdx1 as Bindable<Array<string>>
                    Bindable_Array_String_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1ForIdx3)
                } else if (valueHolderForValueTmpValueForIdx1 instanceof Array) {
                    if (valueHolderForValueTmpValueForIdx1.length == 0) {
                        valueSerializer.writeInt8((0).toByte())
                        valueSerializer.writeInt32(0)
                    } else {
                        const valueHolderForValueTmpValueForIdx1Elem  = valueHolderForValueTmpValueForIdx1[0]
                        if (valueHolderForValueTmpValueForIdx1Elem instanceof arkui_component_units_ResourceStr) {
                            valueSerializer.writeInt8((0).toByte())
                            const valueHolderForValueTmpValueForIdx1ForIdx0  = valueHolderForValueTmpValueForIdx1 as Array<arkui_component_units_ResourceStr>
                            valueSerializer.writeInt32((valueHolderForValueTmpValueForIdx1ForIdx0.length).toInt())
                            for (let valueHolderForValueTmpValueForIdx1ForIdx0CounterI = 0; valueHolderForValueTmpValueForIdx1ForIdx0CounterI < valueHolderForValueTmpValueForIdx1ForIdx0.length; valueHolderForValueTmpValueForIdx1ForIdx0CounterI++) {
                                const valueHolderForValueTmpValueForIdx1ForIdx0TmpElement : arkui_component_units_ResourceStr = valueHolderForValueTmpValueForIdx1ForIdx0[valueHolderForValueTmpValueForIdx1ForIdx0CounterI]
                                if (valueHolderForValueTmpValueForIdx1ForIdx0TmpElement instanceof string) {
                                    valueSerializer.writeInt8((0).toByte())
                                    const valueHolderForValueTmpValueForIdx1ForIdx0TmpElementForIdx0  = valueHolderForValueTmpValueForIdx1ForIdx0TmpElement as string
                                    valueSerializer.writeString(valueHolderForValueTmpValueForIdx1ForIdx0TmpElementForIdx0)
                                } else if (valueHolderForValueTmpValueForIdx1ForIdx0TmpElement instanceof arkui_component_units_Resource) {
                                    valueSerializer.writeInt8((1).toByte())
                                    const valueHolderForValueTmpValueForIdx1ForIdx0TmpElementForIdx1  = valueHolderForValueTmpValueForIdx1ForIdx0TmpElement as arkui_component_units_Resource
                                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1ForIdx0TmpElementForIdx1)
                                }
                            }
                        }
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            if (valueHolderForSelectedTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedTmpValueForIdx0  = valueHolderForSelectedTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSelectedTmpValueForIdx0)
            } else if (valueHolderForSelectedTmpValue instanceof Bindable) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedTmpValueForIdx2  = valueHolderForSelectedTmpValue as Bindable<int32>
                Bindable_I32_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx2)
            } else if (valueHolderForSelectedTmpValue instanceof Bindable) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedTmpValueForIdx3  = valueHolderForSelectedTmpValue as Bindable<Array<int32>>
                Bindable_Array_I32_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx3)
            } else if (valueHolderForSelectedTmpValue instanceof Array) {
                if (valueHolderForSelectedTmpValue.length == 0) {
                    valueSerializer.writeInt8((1).toByte())
                    valueSerializer.writeInt32(0)
                } else {
                    const valueHolderForSelectedTmpValueElem  = valueHolderForSelectedTmpValue[0]
                    if (valueHolderForSelectedTmpValueElem instanceof int32) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForSelectedTmpValueForIdx1  = valueHolderForSelectedTmpValue as Array<int32>
                        valueSerializer.writeInt32((valueHolderForSelectedTmpValueForIdx1.length).toInt())
                        for (let valueHolderForSelectedTmpValueForIdx1CounterI = 0; valueHolderForSelectedTmpValueForIdx1CounterI < valueHolderForSelectedTmpValueForIdx1.length; valueHolderForSelectedTmpValueForIdx1CounterI++) {
                            const valueHolderForSelectedTmpValueForIdx1TmpElement : int32 = valueHolderForSelectedTmpValueForIdx1[valueHolderForSelectedTmpValueForIdx1CounterI]
                            valueSerializer.writeInt32(valueHolderForSelectedTmpValueForIdx1TmpElement)
                        }
                    }
                }
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
                const valueHolderForColumnWidthsTmpValueTmpElement : arkui_Graphics_LengthMetrics = valueHolderForColumnWidthsTmpValue[valueHolderForColumnWidthsTmpValueCounterI]
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForColumnWidthsTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextPickerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const rangeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let rangeTmpBuf : Array<string> | Array<Array<string>> | arkui_component_units_Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> | undefined
        if (rangeTmpBufUnionSelector == (0).toByte()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<string> = new Array<string>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = (valueDeserializer.readString() as string)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (1).toByte()) {
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
        } else if (rangeTmpBufUnionSelector == (2).toByte()) {
            rangeTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else if (rangeTmpBufUnionSelector == (3).toByte()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<TextPickerRangeContent> = new Array<TextPickerRangeContent>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = TextPickerRangeContent_serializer.read(valueDeserializer)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (4).toByte()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else {
            throw new Error('One of the branches for rangeTmpBuf has to be chosen through deserialisation.')
        }
        const rangeTmpResult : Array<string> | Array<Array<string>> | arkui_component_units_Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> = (rangeTmpBuf as Array<string> | Array<Array<string>> | arkui_component_units_Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>)
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let valueTmpBuf : BindableResourceStr | BindableResourceStrArray | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBufOpt : BindableResourceStr | BindableResourceStrArray | undefined
            if (valueTmpBufOptUnionSelector == (0).toByte()) {
                const valueTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let valueTmpBufOptBufU : arkui_component_units_ResourceStr | Bindable<arkui_component_units_ResourceStr> | Bindable<global_resource_Resource> | Bindable<string> | undefined
                if (valueTmpBufOptBufUUnionSelector == (0).toByte()) {
                    const valueTmpBufOptBufUBufUUnionSelector : int32 = valueDeserializer.readInt8()
                    let valueTmpBufOptBufUBufU : string | arkui_component_units_Resource | undefined
                    if (valueTmpBufOptBufUBufUUnionSelector == (0).toByte()) {
                        valueTmpBufOptBufUBufU = (valueDeserializer.readString() as string)
                    } else if (valueTmpBufOptBufUBufUUnionSelector == (1).toByte()) {
                        valueTmpBufOptBufUBufU = global_resource_Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error('One of the branches for valueTmpBufOptBufUBufU has to be chosen through deserialisation.')
                    }
                    valueTmpBufOptBufU = (valueTmpBufOptBufUBufU as string | arkui_component_units_Resource)
                } else if (valueTmpBufOptBufUUnionSelector == (1).toByte()) {
                    valueTmpBufOptBufU = Bindable_ResourceStr_serializer.read(valueDeserializer)
                } else if (valueTmpBufOptBufUUnionSelector == (2).toByte()) {
                    valueTmpBufOptBufU = Bindable_Resource_serializer.read(valueDeserializer)
                } else if (valueTmpBufOptBufUUnionSelector == (3).toByte()) {
                    valueTmpBufOptBufU = Bindable_String_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for valueTmpBufOptBufU has to be chosen through deserialisation.')
                }
                valueTmpBufOpt = (valueTmpBufOptBufU as arkui_component_units_ResourceStr | Bindable<arkui_component_units_ResourceStr> | Bindable<global_resource_Resource> | Bindable<string>)
            } else if (valueTmpBufOptUnionSelector == (1).toByte()) {
                const valueTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let valueTmpBufOptBufU : Array<arkui_component_units_ResourceStr> | Bindable<Array<arkui_component_units_ResourceStr>> | Bindable<Array<global_resource_Resource>> | Bindable<Array<string>> | undefined
                if (valueTmpBufOptBufUUnionSelector == (0).toByte()) {
                    const valueTmpBufOptBufUBufULength : int32 = valueDeserializer.readInt32()
                    let valueTmpBufOptBufUBufU : Array<arkui_component_units_ResourceStr> = new Array<arkui_component_units_ResourceStr>(valueTmpBufOptBufUBufULength)
                    for (let valueTmpBufOptBufUBufUBufCounterI = 0; valueTmpBufOptBufUBufUBufCounterI < valueTmpBufOptBufUBufULength; valueTmpBufOptBufUBufUBufCounterI++) {
                        const valueTmpBufOptBufUBufUTempBufUnionSelector : int32 = valueDeserializer.readInt8()
                        let valueTmpBufOptBufUBufUTempBuf : string | arkui_component_units_Resource | undefined
                        if (valueTmpBufOptBufUBufUTempBufUnionSelector == (0).toByte()) {
                            valueTmpBufOptBufUBufUTempBuf = (valueDeserializer.readString() as string)
                        } else if (valueTmpBufOptBufUBufUTempBufUnionSelector == (1).toByte()) {
                            valueTmpBufOptBufUBufUTempBuf = global_resource_Resource_serializer.read(valueDeserializer)
                        } else {
                            throw new Error('One of the branches for valueTmpBufOptBufUBufUTempBuf has to be chosen through deserialisation.')
                        }
                        valueTmpBufOptBufUBufU[valueTmpBufOptBufUBufUBufCounterI] = (valueTmpBufOptBufUBufUTempBuf as string | arkui_component_units_Resource)
                    }
                    valueTmpBufOptBufU = valueTmpBufOptBufUBufU
                } else if (valueTmpBufOptBufUUnionSelector == (1).toByte()) {
                    valueTmpBufOptBufU = Bindable_Array_ResourceStr_serializer.read(valueDeserializer)
                } else if (valueTmpBufOptBufUUnionSelector == (2).toByte()) {
                    valueTmpBufOptBufU = Bindable_Array_Resource_serializer.read(valueDeserializer)
                } else if (valueTmpBufOptBufUUnionSelector == (3).toByte()) {
                    valueTmpBufOptBufU = Bindable_Array_String_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for valueTmpBufOptBufU has to be chosen through deserialisation.')
                }
                valueTmpBufOpt = (valueTmpBufOptBufU as Array<arkui_component_units_ResourceStr> | Bindable<Array<arkui_component_units_ResourceStr>> | Bindable<Array<global_resource_Resource>> | Bindable<Array<string>>)
            } else {
                throw new Error('One of the branches for valueTmpBufOpt has to be chosen through deserialisation.')
            }
            valueTmpBuf = (valueTmpBufOpt as BindableResourceStr | BindableResourceStrArray)
        }
        const valueTmpResult : BindableResourceStr | BindableResourceStrArray | undefined = valueTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedTmpBuf : int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>> | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let selectedTmpBufOpt : int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>> | undefined
            if (selectedTmpBufOptUnionSelector == (0).toByte()) {
                selectedTmpBufOpt = valueDeserializer.readInt32()
            } else if (selectedTmpBufOptUnionSelector == (1).toByte()) {
                const selectedTmpBufOptBufULength : int32 = valueDeserializer.readInt32()
                let selectedTmpBufOptBufU : Array<int32> = new Array<int32>(selectedTmpBufOptBufULength)
                for (let selectedTmpBufOptBufUBufCounterI = 0; selectedTmpBufOptBufUBufCounterI < selectedTmpBufOptBufULength; selectedTmpBufOptBufUBufCounterI++) {
                    selectedTmpBufOptBufU[selectedTmpBufOptBufUBufCounterI] = valueDeserializer.readInt32()
                }
                selectedTmpBufOpt = selectedTmpBufOptBufU
            } else if (selectedTmpBufOptUnionSelector == (2).toByte()) {
                selectedTmpBufOpt = Bindable_I32_serializer.read(valueDeserializer)
            } else if (selectedTmpBufOptUnionSelector == (3).toByte()) {
                selectedTmpBufOpt = Bindable_Array_I32_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for selectedTmpBufOpt has to be chosen through deserialisation.')
            }
            selectedTmpBuf = (selectedTmpBufOpt as int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>>)
        }
        const selectedTmpResult : int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>> | undefined = selectedTmpBuf
        const columnWidthsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let columnWidthsTmpBuf : Array<arkui_Graphics_LengthMetrics> | undefined = undefined
        if ((columnWidthsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const columnWidthsTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let columnWidthsTmpBufOpt : Array<arkui_Graphics_LengthMetrics> = new Array<arkui_Graphics_LengthMetrics>(columnWidthsTmpBufOptLength)
            for (let columnWidthsTmpBufOptBufCounterI = 0; columnWidthsTmpBufOptBufCounterI < columnWidthsTmpBufOptLength; columnWidthsTmpBufOptBufCounterI++) {
                columnWidthsTmpBufOpt[columnWidthsTmpBufOptBufCounterI] = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            }
            columnWidthsTmpBuf = columnWidthsTmpBufOpt
        }
        const columnWidthsTmpResult : Array<arkui_Graphics_LengthMetrics> | undefined = columnWidthsTmpBuf
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
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFont  = value.font
        if (valueHolderForFont !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontTmpValue  = valueHolderForFont!
            arkui_component_units_Font_serializer.write(valueSerializer, valueHolderForFontTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMinFontSize  = value.minFontSize
        if (valueHolderForMinFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinFontSizeTmpValue  = valueHolderForMinFontSize!
            if (valueHolderForMinFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx0  = valueHolderForMinFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMinFontSizeTmpValueForIdx0)
            } else if (valueHolderForMinFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx1  = valueHolderForMinFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForMinFontSizeTmpValueForIdx1)
            } else if (valueHolderForMinFontSizeTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx2  = valueHolderForMinFontSizeTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMinFontSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxFontSize  = value.maxFontSize
        if (valueHolderForMaxFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxFontSizeTmpValue  = valueHolderForMaxFontSize!
            if (valueHolderForMaxFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx0  = valueHolderForMaxFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMaxFontSizeTmpValueForIdx0)
            } else if (valueHolderForMaxFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx1  = valueHolderForMaxFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForMaxFontSizeTmpValueForIdx1)
            } else if (valueHolderForMaxFontSizeTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx2  = valueHolderForMaxFontSizeTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMaxFontSizeTmpValueForIdx2)
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
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = valueDeserializer.readInt32()
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (colorTmpBufOptUnionSelector == (3).toByte()) {
                colorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const fontTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontTmpBuf : arkui_component_units_Font | undefined = undefined
        if ((fontTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontTmpBuf = arkui_component_units_Font_serializer.read(valueDeserializer)
        }
        const fontTmpResult : arkui_component_units_Font | undefined = fontTmpBuf
        const minFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let minFontSizeTmpBuf : double | string | arkui_component_units_Resource | undefined = undefined
        if ((minFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minFontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let minFontSizeTmpBufOpt : double | string | arkui_component_units_Resource | undefined
            if (minFontSizeTmpBufOptUnionSelector == (0).toByte()) {
                minFontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (minFontSizeTmpBufOptUnionSelector == (1).toByte()) {
                minFontSizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (minFontSizeTmpBufOptUnionSelector == (2).toByte()) {
                minFontSizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for minFontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            minFontSizeTmpBuf = (minFontSizeTmpBufOpt as double | string | arkui_component_units_Resource)
        }
        const minFontSizeTmpResult : double | string | arkui_component_units_Resource | undefined = minFontSizeTmpBuf
        const maxFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxFontSizeTmpBuf : double | string | arkui_component_units_Resource | undefined = undefined
        if ((maxFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxFontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let maxFontSizeTmpBufOpt : double | string | arkui_component_units_Resource | undefined
            if (maxFontSizeTmpBufOptUnionSelector == (0).toByte()) {
                maxFontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (maxFontSizeTmpBufOptUnionSelector == (1).toByte()) {
                maxFontSizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (maxFontSizeTmpBufOptUnionSelector == (2).toByte()) {
                maxFontSizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for maxFontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            maxFontSizeTmpBuf = (maxFontSizeTmpBufOpt as double | string | arkui_component_units_Resource)
        }
        const maxFontSizeTmpResult : double | string | arkui_component_units_Resource | undefined = maxFontSizeTmpBuf
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
        if (valueHolderForRange instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForRangeForIdx2  = valueHolderForRange as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForRangeForIdx2)
        } else if (valueHolderForRange instanceof Array) {
            if (valueHolderForRange.length == 0) {
                valueSerializer.writeInt8((0).toByte())
                valueSerializer.writeInt32(0)
            } else {
                const valueHolderForRangeElem  = valueHolderForRange[0]
                if (valueHolderForRangeElem instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForRangeForIdx0  = valueHolderForRange as Array<string>
                    valueSerializer.writeInt32((valueHolderForRangeForIdx0.length).toInt())
                    for (let valueHolderForRangeForIdx0CounterI = 0; valueHolderForRangeForIdx0CounterI < valueHolderForRangeForIdx0.length; valueHolderForRangeForIdx0CounterI++) {
                        const valueHolderForRangeForIdx0TmpElement : string = valueHolderForRangeForIdx0[valueHolderForRangeForIdx0CounterI]
                        valueSerializer.writeString(valueHolderForRangeForIdx0TmpElement)
                    }
                } else if (valueHolderForRangeElem instanceof TextPickerRangeContent) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForRangeForIdx3  = valueHolderForRange as Array<TextPickerRangeContent>
                    valueSerializer.writeInt32((valueHolderForRangeForIdx3.length).toInt())
                    for (let valueHolderForRangeForIdx3CounterI = 0; valueHolderForRangeForIdx3CounterI < valueHolderForRangeForIdx3.length; valueHolderForRangeForIdx3CounterI++) {
                        const valueHolderForRangeForIdx3TmpElement : TextPickerRangeContent = valueHolderForRangeForIdx3[valueHolderForRangeForIdx3CounterI]
                        TextPickerRangeContent_serializer.write(valueSerializer, valueHolderForRangeForIdx3TmpElement)
                    }
                } else if (valueHolderForRangeElem instanceof TextCascadePickerRangeContent) {
                    valueSerializer.writeInt8((4).toByte())
                    const valueHolderForRangeForIdx4  = valueHolderForRange as Array<TextCascadePickerRangeContent>
                    valueSerializer.writeInt32((valueHolderForRangeForIdx4.length).toInt())
                    for (let valueHolderForRangeForIdx4CounterI = 0; valueHolderForRangeForIdx4CounterI < valueHolderForRangeForIdx4.length; valueHolderForRangeForIdx4CounterI++) {
                        const valueHolderForRangeForIdx4TmpElement : TextCascadePickerRangeContent = valueHolderForRangeForIdx4[valueHolderForRangeForIdx4CounterI]
                        TextCascadePickerRangeContent_serializer.write(valueSerializer, valueHolderForRangeForIdx4TmpElement)
                    }
                } else if (valueHolderForRangeElem instanceof Array) {
                    if (valueHolderForRangeElem.length == 0) {
                        valueSerializer.writeInt8((1).toByte())
                        valueSerializer.writeInt32(0)
                    } else {
                        const valueHolderForRangeElemElem  = valueHolderForRangeElem[0]
                        if (valueHolderForRangeElemElem instanceof string) {
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
                        }
                    }
                }
            }
        }
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            if (valueHolderForValueTmpValue instanceof BindableResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as BindableResourceStr
                if (valueHolderForValueTmpValueForIdx0 instanceof arkui_component_units_ResourceStr) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx0  = valueHolderForValueTmpValueForIdx0 as arkui_component_units_ResourceStr
                    if (valueHolderForValueTmpValueForIdx0ForIdx0 instanceof string) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderForValueTmpValueForIdx0ForIdx0ForIdx0  = valueHolderForValueTmpValueForIdx0ForIdx0 as string
                        valueSerializer.writeString(valueHolderForValueTmpValueForIdx0ForIdx0ForIdx0)
                    } else if (valueHolderForValueTmpValueForIdx0ForIdx0 instanceof arkui_component_units_Resource) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForValueTmpValueForIdx0ForIdx0ForIdx1  = valueHolderForValueTmpValueForIdx0ForIdx0 as arkui_component_units_Resource
                        global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx0ForIdx1)
                    }
                } else if (valueHolderForValueTmpValueForIdx0 instanceof Bindable) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx1  = valueHolderForValueTmpValueForIdx0 as Bindable<arkui_component_units_ResourceStr>
                    Bindable_ResourceStr_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx1)
                } else if (valueHolderForValueTmpValueForIdx0 instanceof Bindable) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx2  = valueHolderForValueTmpValueForIdx0 as Bindable<global_resource_Resource>
                    Bindable_Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx2)
                } else if (valueHolderForValueTmpValueForIdx0 instanceof Bindable) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForValueTmpValueForIdx0ForIdx3  = valueHolderForValueTmpValueForIdx0 as Bindable<string>
                    Bindable_String_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForValueTmpValue instanceof BindableResourceStrArray) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForValueTmpValueForIdx1  = valueHolderForValueTmpValue as BindableResourceStrArray
                if (valueHolderForValueTmpValueForIdx1 instanceof Bindable) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForValueTmpValueForIdx1ForIdx1  = valueHolderForValueTmpValueForIdx1 as Bindable<Array<arkui_component_units_ResourceStr>>
                    Bindable_Array_ResourceStr_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1ForIdx1)
                } else if (valueHolderForValueTmpValueForIdx1 instanceof Bindable) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForValueTmpValueForIdx1ForIdx2  = valueHolderForValueTmpValueForIdx1 as Bindable<Array<global_resource_Resource>>
                    Bindable_Array_Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1ForIdx2)
                } else if (valueHolderForValueTmpValueForIdx1 instanceof Bindable) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForValueTmpValueForIdx1ForIdx3  = valueHolderForValueTmpValueForIdx1 as Bindable<Array<string>>
                    Bindable_Array_String_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1ForIdx3)
                } else if (valueHolderForValueTmpValueForIdx1 instanceof Array) {
                    if (valueHolderForValueTmpValueForIdx1.length == 0) {
                        valueSerializer.writeInt8((0).toByte())
                        valueSerializer.writeInt32(0)
                    } else {
                        const valueHolderForValueTmpValueForIdx1Elem  = valueHolderForValueTmpValueForIdx1[0]
                        if (valueHolderForValueTmpValueForIdx1Elem instanceof arkui_component_units_ResourceStr) {
                            valueSerializer.writeInt8((0).toByte())
                            const valueHolderForValueTmpValueForIdx1ForIdx0  = valueHolderForValueTmpValueForIdx1 as Array<arkui_component_units_ResourceStr>
                            valueSerializer.writeInt32((valueHolderForValueTmpValueForIdx1ForIdx0.length).toInt())
                            for (let valueHolderForValueTmpValueForIdx1ForIdx0CounterI = 0; valueHolderForValueTmpValueForIdx1ForIdx0CounterI < valueHolderForValueTmpValueForIdx1ForIdx0.length; valueHolderForValueTmpValueForIdx1ForIdx0CounterI++) {
                                const valueHolderForValueTmpValueForIdx1ForIdx0TmpElement : arkui_component_units_ResourceStr = valueHolderForValueTmpValueForIdx1ForIdx0[valueHolderForValueTmpValueForIdx1ForIdx0CounterI]
                                if (valueHolderForValueTmpValueForIdx1ForIdx0TmpElement instanceof string) {
                                    valueSerializer.writeInt8((0).toByte())
                                    const valueHolderForValueTmpValueForIdx1ForIdx0TmpElementForIdx0  = valueHolderForValueTmpValueForIdx1ForIdx0TmpElement as string
                                    valueSerializer.writeString(valueHolderForValueTmpValueForIdx1ForIdx0TmpElementForIdx0)
                                } else if (valueHolderForValueTmpValueForIdx1ForIdx0TmpElement instanceof arkui_component_units_Resource) {
                                    valueSerializer.writeInt8((1).toByte())
                                    const valueHolderForValueTmpValueForIdx1ForIdx0TmpElementForIdx1  = valueHolderForValueTmpValueForIdx1ForIdx0TmpElement as arkui_component_units_Resource
                                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1ForIdx0TmpElementForIdx1)
                                }
                            }
                        }
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            if (valueHolderForSelectedTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedTmpValueForIdx0  = valueHolderForSelectedTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSelectedTmpValueForIdx0)
            } else if (valueHolderForSelectedTmpValue instanceof Bindable) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedTmpValueForIdx2  = valueHolderForSelectedTmpValue as Bindable<int32>
                Bindable_I32_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx2)
            } else if (valueHolderForSelectedTmpValue instanceof Bindable) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedTmpValueForIdx3  = valueHolderForSelectedTmpValue as Bindable<Array<int32>>
                Bindable_Array_I32_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx3)
            } else if (valueHolderForSelectedTmpValue instanceof Array) {
                if (valueHolderForSelectedTmpValue.length == 0) {
                    valueSerializer.writeInt8((1).toByte())
                    valueSerializer.writeInt32(0)
                } else {
                    const valueHolderForSelectedTmpValueElem  = valueHolderForSelectedTmpValue[0]
                    if (valueHolderForSelectedTmpValueElem instanceof int32) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForSelectedTmpValueForIdx1  = valueHolderForSelectedTmpValue as Array<int32>
                        valueSerializer.writeInt32((valueHolderForSelectedTmpValueForIdx1.length).toInt())
                        for (let valueHolderForSelectedTmpValueForIdx1CounterI = 0; valueHolderForSelectedTmpValueForIdx1CounterI < valueHolderForSelectedTmpValueForIdx1.length; valueHolderForSelectedTmpValueForIdx1CounterI++) {
                            const valueHolderForSelectedTmpValueForIdx1TmpElement : int32 = valueHolderForSelectedTmpValueForIdx1[valueHolderForSelectedTmpValueForIdx1CounterI]
                            valueSerializer.writeInt32(valueHolderForSelectedTmpValueForIdx1TmpElement)
                        }
                    }
                }
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
                const valueHolderForColumnWidthsTmpValueTmpElement : arkui_Graphics_LengthMetrics = valueHolderForColumnWidthsTmpValue[valueHolderForColumnWidthsTmpValueCounterI]
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForColumnWidthsTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDefaultPickerItemHeight  = value.defaultPickerItemHeight
        if (valueHolderForDefaultPickerItemHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDefaultPickerItemHeightTmpValue  = valueHolderForDefaultPickerItemHeight!
            if (valueHolderForDefaultPickerItemHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForDefaultPickerItemHeightTmpValueForIdx0  = valueHolderForDefaultPickerItemHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForDefaultPickerItemHeightTmpValueForIdx0)
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
            if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForBackgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
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
        let rangeTmpBuf : Array<string> | Array<Array<string>> | arkui_component_units_Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> | undefined
        if (rangeTmpBufUnionSelector == (0).toByte()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<string> = new Array<string>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = (valueDeserializer.readString() as string)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (1).toByte()) {
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
        } else if (rangeTmpBufUnionSelector == (2).toByte()) {
            rangeTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else if (rangeTmpBufUnionSelector == (3).toByte()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<TextPickerRangeContent> = new Array<TextPickerRangeContent>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = TextPickerRangeContent_serializer.read(valueDeserializer)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else if (rangeTmpBufUnionSelector == (4).toByte()) {
            const rangeTmpBufBufULength : int32 = valueDeserializer.readInt32()
            let rangeTmpBufBufU : Array<TextCascadePickerRangeContent> = new Array<TextCascadePickerRangeContent>(rangeTmpBufBufULength)
            for (let rangeTmpBufBufUBufCounterI = 0; rangeTmpBufBufUBufCounterI < rangeTmpBufBufULength; rangeTmpBufBufUBufCounterI++) {
                rangeTmpBufBufU[rangeTmpBufBufUBufCounterI] = TextCascadePickerRangeContent_serializer.read(valueDeserializer)
            }
            rangeTmpBuf = rangeTmpBufBufU
        } else {
            throw new Error('One of the branches for rangeTmpBuf has to be chosen through deserialisation.')
        }
        const rangeTmpResult : Array<string> | Array<Array<string>> | arkui_component_units_Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent> = (rangeTmpBuf as Array<string> | Array<Array<string>> | arkui_component_units_Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>)
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let valueTmpBuf : BindableResourceStr | BindableResourceStrArray | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBufOpt : BindableResourceStr | BindableResourceStrArray | undefined
            if (valueTmpBufOptUnionSelector == (0).toByte()) {
                const valueTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let valueTmpBufOptBufU : arkui_component_units_ResourceStr | Bindable<arkui_component_units_ResourceStr> | Bindable<global_resource_Resource> | Bindable<string> | undefined
                if (valueTmpBufOptBufUUnionSelector == (0).toByte()) {
                    const valueTmpBufOptBufUBufUUnionSelector : int32 = valueDeserializer.readInt8()
                    let valueTmpBufOptBufUBufU : string | arkui_component_units_Resource | undefined
                    if (valueTmpBufOptBufUBufUUnionSelector == (0).toByte()) {
                        valueTmpBufOptBufUBufU = (valueDeserializer.readString() as string)
                    } else if (valueTmpBufOptBufUBufUUnionSelector == (1).toByte()) {
                        valueTmpBufOptBufUBufU = global_resource_Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error('One of the branches for valueTmpBufOptBufUBufU has to be chosen through deserialisation.')
                    }
                    valueTmpBufOptBufU = (valueTmpBufOptBufUBufU as string | arkui_component_units_Resource)
                } else if (valueTmpBufOptBufUUnionSelector == (1).toByte()) {
                    valueTmpBufOptBufU = Bindable_ResourceStr_serializer.read(valueDeserializer)
                } else if (valueTmpBufOptBufUUnionSelector == (2).toByte()) {
                    valueTmpBufOptBufU = Bindable_Resource_serializer.read(valueDeserializer)
                } else if (valueTmpBufOptBufUUnionSelector == (3).toByte()) {
                    valueTmpBufOptBufU = Bindable_String_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for valueTmpBufOptBufU has to be chosen through deserialisation.')
                }
                valueTmpBufOpt = (valueTmpBufOptBufU as arkui_component_units_ResourceStr | Bindable<arkui_component_units_ResourceStr> | Bindable<global_resource_Resource> | Bindable<string>)
            } else if (valueTmpBufOptUnionSelector == (1).toByte()) {
                const valueTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let valueTmpBufOptBufU : Array<arkui_component_units_ResourceStr> | Bindable<Array<arkui_component_units_ResourceStr>> | Bindable<Array<global_resource_Resource>> | Bindable<Array<string>> | undefined
                if (valueTmpBufOptBufUUnionSelector == (0).toByte()) {
                    const valueTmpBufOptBufUBufULength : int32 = valueDeserializer.readInt32()
                    let valueTmpBufOptBufUBufU : Array<arkui_component_units_ResourceStr> = new Array<arkui_component_units_ResourceStr>(valueTmpBufOptBufUBufULength)
                    for (let valueTmpBufOptBufUBufUBufCounterI = 0; valueTmpBufOptBufUBufUBufCounterI < valueTmpBufOptBufUBufULength; valueTmpBufOptBufUBufUBufCounterI++) {
                        const valueTmpBufOptBufUBufUTempBufUnionSelector : int32 = valueDeserializer.readInt8()
                        let valueTmpBufOptBufUBufUTempBuf : string | arkui_component_units_Resource | undefined
                        if (valueTmpBufOptBufUBufUTempBufUnionSelector == (0).toByte()) {
                            valueTmpBufOptBufUBufUTempBuf = (valueDeserializer.readString() as string)
                        } else if (valueTmpBufOptBufUBufUTempBufUnionSelector == (1).toByte()) {
                            valueTmpBufOptBufUBufUTempBuf = global_resource_Resource_serializer.read(valueDeserializer)
                        } else {
                            throw new Error('One of the branches for valueTmpBufOptBufUBufUTempBuf has to be chosen through deserialisation.')
                        }
                        valueTmpBufOptBufUBufU[valueTmpBufOptBufUBufUBufCounterI] = (valueTmpBufOptBufUBufUTempBuf as string | arkui_component_units_Resource)
                    }
                    valueTmpBufOptBufU = valueTmpBufOptBufUBufU
                } else if (valueTmpBufOptBufUUnionSelector == (1).toByte()) {
                    valueTmpBufOptBufU = Bindable_Array_ResourceStr_serializer.read(valueDeserializer)
                } else if (valueTmpBufOptBufUUnionSelector == (2).toByte()) {
                    valueTmpBufOptBufU = Bindable_Array_Resource_serializer.read(valueDeserializer)
                } else if (valueTmpBufOptBufUUnionSelector == (3).toByte()) {
                    valueTmpBufOptBufU = Bindable_Array_String_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for valueTmpBufOptBufU has to be chosen through deserialisation.')
                }
                valueTmpBufOpt = (valueTmpBufOptBufU as Array<arkui_component_units_ResourceStr> | Bindable<Array<arkui_component_units_ResourceStr>> | Bindable<Array<global_resource_Resource>> | Bindable<Array<string>>)
            } else {
                throw new Error('One of the branches for valueTmpBufOpt has to be chosen through deserialisation.')
            }
            valueTmpBuf = (valueTmpBufOpt as BindableResourceStr | BindableResourceStrArray)
        }
        const valueTmpResult : BindableResourceStr | BindableResourceStrArray | undefined = valueTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedTmpBuf : int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>> | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let selectedTmpBufOpt : int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>> | undefined
            if (selectedTmpBufOptUnionSelector == (0).toByte()) {
                selectedTmpBufOpt = valueDeserializer.readInt32()
            } else if (selectedTmpBufOptUnionSelector == (1).toByte()) {
                const selectedTmpBufOptBufULength : int32 = valueDeserializer.readInt32()
                let selectedTmpBufOptBufU : Array<int32> = new Array<int32>(selectedTmpBufOptBufULength)
                for (let selectedTmpBufOptBufUBufCounterI = 0; selectedTmpBufOptBufUBufCounterI < selectedTmpBufOptBufULength; selectedTmpBufOptBufUBufCounterI++) {
                    selectedTmpBufOptBufU[selectedTmpBufOptBufUBufCounterI] = valueDeserializer.readInt32()
                }
                selectedTmpBufOpt = selectedTmpBufOptBufU
            } else if (selectedTmpBufOptUnionSelector == (2).toByte()) {
                selectedTmpBufOpt = Bindable_I32_serializer.read(valueDeserializer)
            } else if (selectedTmpBufOptUnionSelector == (3).toByte()) {
                selectedTmpBufOpt = Bindable_Array_I32_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for selectedTmpBufOpt has to be chosen through deserialisation.')
            }
            selectedTmpBuf = (selectedTmpBufOpt as int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>>)
        }
        const selectedTmpResult : int32 | Array<int32> | Bindable<int32> | Bindable<Array<int32>> | undefined = selectedTmpBuf
        const columnWidthsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let columnWidthsTmpBuf : Array<arkui_Graphics_LengthMetrics> | undefined = undefined
        if ((columnWidthsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const columnWidthsTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let columnWidthsTmpBufOpt : Array<arkui_Graphics_LengthMetrics> = new Array<arkui_Graphics_LengthMetrics>(columnWidthsTmpBufOptLength)
            for (let columnWidthsTmpBufOptBufCounterI = 0; columnWidthsTmpBufOptBufCounterI < columnWidthsTmpBufOptLength; columnWidthsTmpBufOptBufCounterI++) {
                columnWidthsTmpBufOpt[columnWidthsTmpBufOptBufCounterI] = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            }
            columnWidthsTmpBuf = columnWidthsTmpBufOpt
        }
        const columnWidthsTmpResult : Array<arkui_Graphics_LengthMetrics> | undefined = columnWidthsTmpBuf
        const defaultPickerItemHeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let defaultPickerItemHeightTmpBuf : double | string | undefined = undefined
        if ((defaultPickerItemHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const defaultPickerItemHeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let defaultPickerItemHeightTmpBufOpt : double | string | undefined
            if (defaultPickerItemHeightTmpBufOptUnionSelector == (0).toByte()) {
                defaultPickerItemHeightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (defaultPickerItemHeightTmpBufOptUnionSelector == (1).toByte()) {
                defaultPickerItemHeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for defaultPickerItemHeightTmpBufOpt has to be chosen through deserialisation.')
            }
            defaultPickerItemHeightTmpBuf = (defaultPickerItemHeightTmpBufOpt as double | string)
        }
        const defaultPickerItemHeightTmpResult : double | string | undefined = defaultPickerItemHeightTmpBuf
        const canLoopTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let canLoopTmpBuf : boolean | undefined = undefined
        if ((canLoopTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            canLoopTmpBuf = valueDeserializer.readBoolean()
        }
        const canLoopTmpResult : boolean | undefined = canLoopTmpBuf
        const disappearTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let disappearTextStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((disappearTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            disappearTextStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const disappearTextStyleTmpResult : PickerTextStyle | undefined = disappearTextStyleTmpBuf
        const textStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((textStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const textStyleTmpResult : PickerTextStyle | undefined = textStyleTmpBuf
        const acceptButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let acceptButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((acceptButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            acceptButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const acceptButtonStyleTmpResult : PickerDialogButtonStyle | undefined = acceptButtonStyleTmpBuf
        const cancelButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let cancelButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((cancelButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            cancelButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const cancelButtonStyleTmpResult : PickerDialogButtonStyle | undefined = cancelButtonStyleTmpBuf
        const selectedTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedTextStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((selectedTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedTextStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const selectedTextStyleTmpResult : PickerTextStyle | undefined = selectedTextStyleTmpBuf
        const disableTextStyleAnimationTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let disableTextStyleAnimationTmpBuf : boolean | undefined = undefined
        if ((disableTextStyleAnimationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            disableTextStyleAnimationTmpBuf = valueDeserializer.readBoolean()
        }
        const disableTextStyleAnimationTmpResult : boolean | undefined = disableTextStyleAnimationTmpBuf
        const defaultTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let defaultTextStyleTmpBuf : TextPickerTextStyle | undefined = undefined
        if ((defaultTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            defaultTextStyleTmpBuf = TextPickerTextStyle_serializer.read(valueDeserializer)
        }
        const defaultTextStyleTmpResult : TextPickerTextStyle | undefined = defaultTextStyleTmpBuf
        const onAcceptTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onAcceptTmpBuf : ((value: TextPickerResult) => void) | undefined = undefined
        if ((onAcceptTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAcceptTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAcceptTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBufOptClosure  = (value: TextPickerResult):void => {
                const onAcceptTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onAcceptTmpBufOptBufArgsSerializer.writeInt32(onAcceptTmpBufOptBufResource.resourceId);
                onAcceptTmpBufOptBufArgsSerializer.writePointer(onAcceptTmpBufOptBufCall);
                onAcceptTmpBufOptBufArgsSerializer.writePointer(onAcceptTmpBufOptBufCallSync);
                TextPickerResult_serializer.write(onAcceptTmpBufOptBufArgsSerializer, value);
                InteropNativeModule._CallCallbackSync(10, -44384479, onAcceptTmpBufOptBufArgsSerializer.asBuffer(), onAcceptTmpBufOptBufArgsSerializer.length());
                onAcceptTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onAcceptTmpBufOptClosure, onAcceptTmpBufOptBufResource)
            onAcceptTmpBuf = onAcceptTmpBufOptClosure
        }
        const onAcceptTmpResult : ((value: TextPickerResult) => void) | undefined = onAcceptTmpBuf
        const onCancelTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onCancelTmpBuf : (() => void) | undefined = undefined
        if ((onCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onCancelTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancelTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBufOptClosure  = ():void => {
                const onCancelTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onCancelTmpBufOptBufArgsSerializer.writeInt32(onCancelTmpBufOptBufResource.resourceId);
                onCancelTmpBufOptBufArgsSerializer.writePointer(onCancelTmpBufOptBufCall);
                onCancelTmpBufOptBufArgsSerializer.writePointer(onCancelTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onCancelTmpBufOptBufArgsSerializer.asBuffer(), onCancelTmpBufOptBufArgsSerializer.length());
                onCancelTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onCancelTmpBufOptClosure, onCancelTmpBufOptBufResource)
            onCancelTmpBuf = onCancelTmpBufOptClosure
        }
        const onCancelTmpResult : (() => void) | undefined = onCancelTmpBuf
        const onChangeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onChangeTmpBuf : ((value: TextPickerResult) => void) | undefined = undefined
        if ((onChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onChangeTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onChangeTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBufOptClosure  = (value: TextPickerResult):void => {
                const onChangeTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onChangeTmpBufOptBufArgsSerializer.writeInt32(onChangeTmpBufOptBufResource.resourceId);
                onChangeTmpBufOptBufArgsSerializer.writePointer(onChangeTmpBufOptBufCall);
                onChangeTmpBufOptBufArgsSerializer.writePointer(onChangeTmpBufOptBufCallSync);
                TextPickerResult_serializer.write(onChangeTmpBufOptBufArgsSerializer, value);
                InteropNativeModule._CallCallbackSync(10, -44384479, onChangeTmpBufOptBufArgsSerializer.asBuffer(), onChangeTmpBufOptBufArgsSerializer.length());
                onChangeTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onChangeTmpBufOptClosure, onChangeTmpBufOptBufResource)
            onChangeTmpBuf = onChangeTmpBufOptClosure
        }
        const onChangeTmpResult : ((value: TextPickerResult) => void) | undefined = onChangeTmpBuf
        const onScrollStopTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onScrollStopTmpBuf : arkui_component_common_Callback<TextPickerResult, void> | undefined = undefined
        if ((onScrollStopTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onScrollStopTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onScrollStopTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onScrollStopTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onScrollStopTmpBufOptClosure  = (data: TextPickerResult):void => {
                const onScrollStopTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onScrollStopTmpBufOptBufArgsSerializer.writeInt32(onScrollStopTmpBufOptBufResource.resourceId);
                onScrollStopTmpBufOptBufArgsSerializer.writePointer(onScrollStopTmpBufOptBufCall);
                onScrollStopTmpBufOptBufArgsSerializer.writePointer(onScrollStopTmpBufOptBufCallSync);
                TextPickerResult_serializer.write(onScrollStopTmpBufOptBufArgsSerializer, data);
                InteropNativeModule._CallCallbackSync(10, 1943280125, onScrollStopTmpBufOptBufArgsSerializer.asBuffer(), onScrollStopTmpBufOptBufArgsSerializer.length());
                onScrollStopTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onScrollStopTmpBufOptClosure, onScrollStopTmpBufOptBufResource)
            onScrollStopTmpBuf = onScrollStopTmpBufOptClosure
        }
        const onScrollStopTmpResult : arkui_component_common_Callback<TextPickerResult, void> | undefined = onScrollStopTmpBuf
        const onEnterSelectedAreaTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onEnterSelectedAreaTmpBuf : arkui_component_common_Callback<TextPickerResult, void> | undefined = undefined
        if ((onEnterSelectedAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onEnterSelectedAreaTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onEnterSelectedAreaTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onEnterSelectedAreaTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onEnterSelectedAreaTmpBufOptClosure  = (data: TextPickerResult):void => {
                const onEnterSelectedAreaTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onEnterSelectedAreaTmpBufOptBufArgsSerializer.writeInt32(onEnterSelectedAreaTmpBufOptBufResource.resourceId);
                onEnterSelectedAreaTmpBufOptBufArgsSerializer.writePointer(onEnterSelectedAreaTmpBufOptBufCall);
                onEnterSelectedAreaTmpBufOptBufArgsSerializer.writePointer(onEnterSelectedAreaTmpBufOptBufCallSync);
                TextPickerResult_serializer.write(onEnterSelectedAreaTmpBufOptBufArgsSerializer, data);
                InteropNativeModule._CallCallbackSync(10, 1943280125, onEnterSelectedAreaTmpBufOptBufArgsSerializer.asBuffer(), onEnterSelectedAreaTmpBufOptBufArgsSerializer.length());
                onEnterSelectedAreaTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onEnterSelectedAreaTmpBufOptClosure, onEnterSelectedAreaTmpBufOptBufResource)
            onEnterSelectedAreaTmpBuf = onEnterSelectedAreaTmpBufOptClosure
        }
        const onEnterSelectedAreaTmpResult : arkui_component_common_Callback<TextPickerResult, void> | undefined = onEnterSelectedAreaTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (backgroundColorTmpBufOptUnionSelector == (0).toByte()) {
                backgroundColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBufOptUnionSelector == (1).toByte()) {
                backgroundColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (backgroundColorTmpBufOptUnionSelector == (2).toByte()) {
                backgroundColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBufOptUnionSelector == (3).toByte()) {
                backgroundColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for backgroundColorTmpBufOpt has to be chosen through deserialisation.')
            }
            backgroundColorTmpBuf = (backgroundColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDidAppearTmpBuf : (() => void) | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBufOptClosure  = ():void => {
                const onDidAppearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBufOptBufArgsSerializer.writeInt32(onDidAppearTmpBufOptBufResource.resourceId);
                onDidAppearTmpBufOptBufArgsSerializer.writePointer(onDidAppearTmpBufOptBufCall);
                onDidAppearTmpBufOptBufArgsSerializer.writePointer(onDidAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onDidAppearTmpBufOptBufArgsSerializer.asBuffer(), onDidAppearTmpBufOptBufArgsSerializer.length());
                onDidAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidAppearTmpBufOptClosure, onDidAppearTmpBufOptBufResource)
            onDidAppearTmpBuf = onDidAppearTmpBufOptClosure
        }
        const onDidAppearTmpResult : (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDidDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBufOptClosure  = ():void => {
                const onDidDisappearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBufOptBufArgsSerializer.writeInt32(onDidDisappearTmpBufOptBufResource.resourceId);
                onDidDisappearTmpBufOptBufArgsSerializer.writePointer(onDidDisappearTmpBufOptBufCall);
                onDidDisappearTmpBufOptBufArgsSerializer.writePointer(onDidDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onDidDisappearTmpBufOptBufArgsSerializer.asBuffer(), onDidDisappearTmpBufOptBufArgsSerializer.length());
                onDidDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidDisappearTmpBufOptClosure, onDidDisappearTmpBufOptBufResource)
            onDidDisappearTmpBuf = onDidDisappearTmpBufOptClosure
        }
        const onDidDisappearTmpResult : (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onWillAppearTmpBuf : (() => void) | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBufOptClosure  = ():void => {
                const onWillAppearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBufOptBufArgsSerializer.writeInt32(onWillAppearTmpBufOptBufResource.resourceId);
                onWillAppearTmpBufOptBufArgsSerializer.writePointer(onWillAppearTmpBufOptBufCall);
                onWillAppearTmpBufOptBufArgsSerializer.writePointer(onWillAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onWillAppearTmpBufOptBufArgsSerializer.asBuffer(), onWillAppearTmpBufOptBufArgsSerializer.length());
                onWillAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillAppearTmpBufOptClosure, onWillAppearTmpBufOptBufResource)
            onWillAppearTmpBuf = onWillAppearTmpBufOptClosure
        }
        const onWillAppearTmpResult : (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onWillDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBufOptClosure  = ():void => {
                const onWillDisappearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBufOptBufArgsSerializer.writeInt32(onWillDisappearTmpBufOptBufResource.resourceId);
                onWillDisappearTmpBufOptBufArgsSerializer.writePointer(onWillDisappearTmpBufOptBufCall);
                onWillDisappearTmpBufOptBufArgsSerializer.writePointer(onWillDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onWillDisappearTmpBufOptBufArgsSerializer.asBuffer(), onWillDisappearTmpBufOptBufArgsSerializer.length());
                onWillDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillDisappearTmpBufOptClosure, onWillDisappearTmpBufOptBufResource)
            onWillDisappearTmpBuf = onWillDisappearTmpBufOptClosure
        }
        const onWillDisappearTmpResult : (() => void) | undefined = onWillDisappearTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBufOpt : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBufOptUnionSelector == (0).toByte()) {
                shadowTmpBufOpt = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBufOptUnionSelector == (1).toByte()) {
                shadowTmpBufOpt = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for shadowTmpBufOpt has to be chosen through deserialisation.')
            }
            shadowTmpBuf = (shadowTmpBufOpt as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const enableHapticFeedbackTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableHapticFeedbackTmpBuf : boolean | undefined = undefined
        if ((enableHapticFeedbackTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHapticFeedbackTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHapticFeedbackTmpResult : boolean | undefined = enableHapticFeedbackTmpBuf
        let value : TextPickerDialogOptions = ({range: rangeTmpResult, value: valueTmpResult, selected: selectedTmpResult, columnWidths: columnWidthsTmpResult, defaultPickerItemHeight: defaultPickerItemHeightTmpResult, canLoop: canLoopTmpResult, disappearTextStyle: disappearTextStyleTmpResult, textStyle: textStyleTmpResult, acceptButtonStyle: acceptButtonStyleTmpResult, cancelButtonStyle: cancelButtonStyleTmpResult, selectedTextStyle: selectedTextStyleTmpResult, disableTextStyleAnimation: disableTextStyleAnimationTmpResult, defaultTextStyle: defaultTextStyleTmpResult, onAccept: onAcceptTmpResult, onCancel: onCancelTmpResult, onChange: onChangeTmpResult, onScrollStop: onScrollStopTmpResult, onEnterSelectedArea: onEnterSelectedAreaTmpResult, maskRect: maskRectTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, shadow: shadowTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, enableHapticFeedback: enableHapticFeedbackTmpResult} as TextPickerDialogOptions)
        return value
    }
}
