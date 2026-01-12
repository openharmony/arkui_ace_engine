/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookUIPickerComponentAttributeModifier, AttributeUpdater } from "#handwritten"
import { CustomBuilder } from "./builder"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { LengthMetrics } from "arkui.Graphics"
import { ResourceColor, BorderRadiuses, LocalizedBorderRadiuses, BorderRadiuses_serializer, LocalizedBorderRadiuses_serializer } from "./units"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { ModifierStateManager } from "./../CommonModifier"
import { UIPickerComponentModifier } from "./../UIPickerComponentModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics_serializer } from "./../Graphics"
import { Resource_serializer } from "./../framework/resource"
export class ArkUIPickerComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: UIPickerComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkUIPickerComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._UIPickerComponent_construct(peerId, flags)
        const _peer  = new ArkUIPickerComponentPeer(_peerPtr, peerId, 'UIPickerComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setUIPickerComponentOptionsAttribute(options?: UIPickerComponentOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            UIPickerComponentOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentInterface_setUIPickerComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnUIPickerComponentCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollStopAttribute(value: OnUIPickerComponentCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setOnScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setCanLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectionIndicatorAttribute(value: PickerIndicatorStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PickerIndicatorStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setSelectionIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface UIPickerComponentOptions {
    selectedIndex?: int32;
}
export type OnUIPickerComponentCallback = (selectedIndex: int32) => void;
export enum PickerIndicatorType {
    BACKGROUND = 0,
    DIVIDER = 1
}
export interface PickerIndicatorStyle {
    type: PickerIndicatorType;
    strokeWidth?: LengthMetrics;
    dividerColor?: ResourceColor;
    startMargin?: LengthMetrics;
    endMargin?: LengthMetrics;
    backgroundColor?: ResourceColor;
    borderRadius?: LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses;
}
export interface UIPickerComponentAttribute extends CommonMethod {
    setUIPickerComponentOptions(options?: UIPickerComponentOptions): this {
        throw new Error("Unimplemented method setUIPickerComponentOptions")
    }
    onChange(value: OnUIPickerComponentCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onScrollStop(value: OnUIPickerComponentCallback | undefined): this {
        throw new Error("Unimplemented method onScrollStop")
    }
    canLoop(value: boolean | undefined): this {
        throw new Error("Unimplemented method canLoop")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    selectionIndicator(value: PickerIndicatorStyle | undefined): this {
        throw new Error("Unimplemented method selectionIndicator")
    }
    attributeModifier(value: AttributeModifier<UIPickerComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkUIPickerComponentStyle extends ArkCommonMethodStyle implements UIPickerComponentAttribute {
    onChange_value?: OnUIPickerComponentCallback | undefined
    onScrollStop_value?: OnUIPickerComponentCallback | undefined
    canLoop_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    selectionIndicator_value?: PickerIndicatorStyle | undefined
    attributeModifier_value?: AttributeModifier<UIPickerComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    setUIPickerComponentOptions(options?: UIPickerComponentOptions): this {
        return this
    }
    onChange(value: OnUIPickerComponentCallback | undefined): this {
        return this
    }
    onScrollStop(value: OnUIPickerComponentCallback | undefined): this {
        return this
    }
    canLoop(value: boolean | undefined): this {
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    selectionIndicator(value: PickerIndicatorStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<UIPickerComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkUIPickerComponentComponent extends ArkCommonMethodComponent implements UIPickerComponentAttribute {
    getPeer(): ArkUIPickerComponentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkUIPickerComponentPeer)
    }
    public setUIPickerComponentOptions(options?: UIPickerComponentOptions): this {
        if (this.checkPriority("setUIPickerComponentOptions")) {
            const options_casted = options as (UIPickerComponentOptions | undefined)
            this.getPeer()?.setUIPickerComponentOptionsAttribute(options_casted)
            this.applyOptionsFinish('UIPickerComponentAttribute');
            return this
        }
        return this
    }
    public onChange(value: OnUIPickerComponentCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnUIPickerComponentCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: OnUIPickerComponentCallback | undefined): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as (OnUIPickerComponentCallback | undefined)
            this.getPeer()?.setOnScrollStopAttribute(value_casted)
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
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public selectionIndicator(value: PickerIndicatorStyle | undefined): this {
        if (this.checkPriority("selectionIndicator")) {
            const value_casted = value as (PickerIndicatorStyle | undefined)
            this.getPeer()?.setSelectionIndicatorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<UIPickerComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookUIPickerComponentAttributeModifier(this, value);
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
export function UIPickerComponentImpl(
    @memo
    style: ((attributes: UIPickerComponentAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkUIPickerComponentComponent>((): ArkUIPickerComponentComponent => {
        return new ArkUIPickerComponentComponent()
    })
    NodeAttach<ArkUIPickerComponentPeer>((): ArkUIPickerComponentPeer => ArkUIPickerComponentPeer.create(receiver), (peer: ArkUIPickerComponentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class UIPickerComponentOptions_serializer {
    public static write(buffer: SerializerBase, value: UIPickerComponentOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSelectedIndex  = value.selectedIndex
        if (valueHolderForSelectedIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedIndexTmpValue  = valueHolderForSelectedIndex!
            valueSerializer.writeInt32(valueHolderForSelectedIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): UIPickerComponentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const selectedIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedIndexTmpBuf : int32 | undefined = undefined
        if ((selectedIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedIndexTmpBuf = valueDeserializer.readInt32()
        }
        const selectedIndexTmpResult : int32 | undefined = selectedIndexTmpBuf
        let value : UIPickerComponentOptions = ({selectedIndex: selectedIndexTmpResult} as UIPickerComponentOptions)
        return value
    }
}
export class PickerIndicatorStyle_serializer {
    public static write(buffer: SerializerBase, value: PickerIndicatorStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDividerColor  = value.dividerColor
        if (valueHolderForDividerColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDividerColorTmpValue  = valueHolderForDividerColor!
            if (valueHolderForDividerColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForDividerColorTmpValueForIdx0  = valueHolderForDividerColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForDividerColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForDividerColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForDividerColorTmpValueForIdx1  = valueHolderForDividerColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForDividerColorTmpValueForIdx1)
            } else if (valueHolderForDividerColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForDividerColorTmpValueForIdx2  = valueHolderForDividerColorTmpValue as string
                valueSerializer.writeString(valueHolderForDividerColorTmpValueForIdx2)
            } else if (valueHolderForDividerColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForDividerColorTmpValueForIdx3  = valueHolderForDividerColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForDividerColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStartMargin  = value.startMargin
        if (valueHolderForStartMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartMarginTmpValue  = valueHolderForStartMargin!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStartMarginTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndMargin  = value.endMargin
        if (valueHolderForEndMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndMarginTmpValue  = valueHolderForEndMargin!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForEndMarginTmpValue)
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
            } else if (valueHolderForBackgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx1)
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
        const valueHolderForBorderRadius  = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue  = valueHolderForBorderRadius!
            if (valueHolderForBorderRadiusTmpValue instanceof LengthMetrics) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx0  = valueHolderForBorderRadiusTmpValue as LengthMetrics
                LengthMetrics_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx0)
            } else if (valueHolderForBorderRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx1  = valueHolderForBorderRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx1)
            } else if (valueHolderForBorderRadiusTmpValue instanceof LocalizedBorderRadiuses) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx2  = valueHolderForBorderRadiusTmpValue as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PickerIndicatorStyle {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : PickerIndicatorType = PickerIndicatorType.fromValue(valueDeserializer.readInt32())
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidthTmpBuf : LengthMetrics | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strokeWidthTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const strokeWidthTmpResult : LengthMetrics | undefined = strokeWidthTmpBuf
        const dividerColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dividerColorTmpBuf : ResourceColor | undefined = undefined
        if ((dividerColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const dividerColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let dividerColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (dividerColorTmpBuf_UnionSelector == (0).toByte()) {
                dividerColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (dividerColorTmpBuf_UnionSelector == (1).toByte()) {
                dividerColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (dividerColorTmpBuf_UnionSelector == (2).toByte()) {
                dividerColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (dividerColorTmpBuf_UnionSelector == (3).toByte()) {
                dividerColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for dividerColorTmpBuf_ has to be chosen through deserialisation.")
            }
            dividerColorTmpBuf = (dividerColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const dividerColorTmpResult : ResourceColor | undefined = dividerColorTmpBuf
        const startMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMarginTmpBuf : LengthMetrics | undefined = undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startMarginTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const startMarginTmpResult : LengthMetrics | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMarginTmpBuf : LengthMetrics | undefined = undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endMarginTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const endMarginTmpResult : LengthMetrics | undefined = endMarginTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toByte()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toByte()) {
                backgroundColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toByte()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toByte()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const borderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderRadiusTmpBuf : LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderRadiusTmpBuf_ : LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses | undefined
            if (borderRadiusTmpBuf_UnionSelector == (0).toByte()) {
                borderRadiusTmpBuf_ = LengthMetrics_serializer.read(valueDeserializer)
            } else if (borderRadiusTmpBuf_UnionSelector == (1).toByte()) {
                borderRadiusTmpBuf_ = BorderRadiuses_serializer.read(valueDeserializer)
            } else if (borderRadiusTmpBuf_UnionSelector == (2).toByte()) {
                borderRadiusTmpBuf_ = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            borderRadiusTmpBuf = (borderRadiusTmpBuf_ as LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses)
        }
        const borderRadiusTmpResult : LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses | undefined = borderRadiusTmpBuf
        let value : PickerIndicatorStyle = ({type: typeTmpResult, strokeWidth: strokeWidthTmpResult, dividerColor: dividerColorTmpResult, startMargin: startMarginTmpResult, endMargin: endMarginTmpResult, backgroundColor: backgroundColorTmpResult, borderRadius: borderRadiusTmpResult} as PickerIndicatorStyle)
        return value
    }
}
