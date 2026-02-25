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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { AttributeModifier, hookUIPickerComponentAttributeModifier, AttributeUpdater } from '#handwritten'
import { CustomBuilder } from './builder'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from 'arkui.Graphics'
import { ResourceColor, Resource as arkui_component_units_Resource, BorderRadiuses, LocalizedBorderRadiuses, BorderRadiuses_serializer, LocalizedBorderRadiuses_serializer } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { UIPickerComponentModifier } from './../UIPickerComponentModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkUIPickerComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: UIPickerComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkUIPickerComponentPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._UIPickerComponent_construct(peerId, flags)
        const _peer = new ArkUIPickerComponentPeer(_peerPtr, peerId, 'UIPickerComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setUIPickerComponentOptionsAttribute(options?: UIPickerComponentOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            UIPickerComponentOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentInterface_setUIPickerComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnUIPickerComponentCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollStopAttribute(value: OnUIPickerComponentCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setOnScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCanLoopAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setCanLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIPickerComponentAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectionIndicatorAttribute(value: PickerIndicatorStyle | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
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
    strokeWidth?: arkui_Graphics_LengthMetrics;
    dividerColor?: ResourceColor;
    startMargin?: arkui_Graphics_LengthMetrics;
    endMargin?: arkui_Graphics_LengthMetrics;
    backgroundColor?: ResourceColor;
    borderRadius?: arkui_Graphics_LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses;
}
export interface UIPickerComponentAttribute extends CommonMethod {
    setUIPickerComponentOptions(options?: UIPickerComponentOptions): this {
        throw new Error('Unimplemented method setUIPickerComponentOptions')
    }
    onChange(value: OnUIPickerComponentCallback | undefined): this {
        throw new Error('Unimplemented method onChange')
    }
    onScrollStop(value: OnUIPickerComponentCallback | undefined): this {
        throw new Error('Unimplemented method onScrollStop')
    }
    canLoop(value: boolean | undefined): this {
        throw new Error('Unimplemented method canLoop')
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableHapticFeedback')
    }
    selectionIndicator(value: PickerIndicatorStyle | undefined): this {
        throw new Error('Unimplemented method selectionIndicator')
    }
    attributeModifier(value: AttributeModifier<UIPickerComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkUIPickerComponentComponent extends ArkCommonMethodComponent implements UIPickerComponentAttribute {
    getPeer(): ArkUIPickerComponentPeer {
        return (this.peer as ArkUIPickerComponentPeer)
    }
    public setUIPickerComponentOptions(options?: UIPickerComponentOptions): this {
        const options_casted = options as (UIPickerComponentOptions | undefined)
        this.getPeer()?.setUIPickerComponentOptionsAttribute(options_casted)
        this.applyOptionsFinish('UIPickerComponentAttribute');
        return this
    }
    public onChange(value: OnUIPickerComponentCallback | undefined): this {
        const value_casted = value as (OnUIPickerComponentCallback | undefined)
        this.getPeer()?.setOnChangeAttribute(value_casted)
        return this
    }
    public onScrollStop(value: OnUIPickerComponentCallback | undefined): this {
        const value_casted = value as (OnUIPickerComponentCallback | undefined)
        this.getPeer()?.setOnScrollStopAttribute(value_casted)
        return this
    }
    public canLoop(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setCanLoopAttribute(value_casted)
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
        return this
    }
    public selectionIndicator(value: PickerIndicatorStyle | undefined): this {
        const value_casted = value as (PickerIndicatorStyle | undefined)
        this.getPeer()?.setSelectionIndicatorAttribute(value_casted)
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
    @memo @memo_skip
    style: ((attributes: UIPickerComponentAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkUIPickerComponentComponent>((): ArkUIPickerComponentComponent => {
        return new ArkUIPickerComponentComponent()
    })
    NodeAttach<ArkUIPickerComponentPeer>((): ArkUIPickerComponentPeer => ArkUIPickerComponentPeer.create(receiver), (_: ArkUIPickerComponentPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class UIPickerComponentOptions_serializer {
    public static write(buffer: SerializerBase, value: UIPickerComponentOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSelectedIndex = value.selectedIndex
        if (valueHolderForSelectedIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedIndexTmpValue = valueHolderForSelectedIndex!
            valueSerializer.writeInt32(valueHolderForSelectedIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): UIPickerComponentOptions {
        let valueDeserializer: DeserializerBase = buffer
        const selectedIndexTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let selectedIndexTmpBuf: int32 | undefined = undefined
        if ((selectedIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedIndexTmpBuf = valueDeserializer.readInt32()
        }
        const selectedIndexTmpResult: int32 | undefined = selectedIndexTmpBuf
        let value: UIPickerComponentOptions = ({selectedIndex: selectedIndexTmpResult} as UIPickerComponentOptions)
        return value
    }
}
export class PickerIndicatorStyle_serializer {
    public static write(buffer: SerializerBase, value: PickerIndicatorStyle): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForType = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
        const valueHolderForStrokeWidth = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue = valueHolderForStrokeWidth!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDividerColor = value.dividerColor
        if (valueHolderForDividerColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDividerColorTmpValue = valueHolderForDividerColor!
            if (valueHolderForDividerColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForDividerColorTmpValueForIdx0 = valueHolderForDividerColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForDividerColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForDividerColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForDividerColorTmpValueForIdx1 = valueHolderForDividerColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForDividerColorTmpValueForIdx1)
            } else if (valueHolderForDividerColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForDividerColorTmpValueForIdx2 = valueHolderForDividerColorTmpValue as string
                valueSerializer.writeString(valueHolderForDividerColorTmpValueForIdx2)
            } else if (valueHolderForDividerColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForDividerColorTmpValueForIdx3 = valueHolderForDividerColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForDividerColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStartMargin = value.startMargin
        if (valueHolderForStartMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartMarginTmpValue = valueHolderForStartMargin!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForStartMarginTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndMargin = value.endMargin
        if (valueHolderForEndMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndMarginTmpValue = valueHolderForEndMargin!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForEndMarginTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0 = valueHolderForBackgroundColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForBackgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1 = valueHolderForBackgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2 = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3 = valueHolderForBackgroundColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderRadius = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue = valueHolderForBorderRadius!
            if (valueHolderForBorderRadiusTmpValue instanceof arkui_Graphics_LengthMetrics) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx0 = valueHolderForBorderRadiusTmpValue as arkui_Graphics_LengthMetrics
                arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx0)
            } else if (valueHolderForBorderRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx1 = valueHolderForBorderRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx1)
            } else if (valueHolderForBorderRadiusTmpValue instanceof LocalizedBorderRadiuses) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx2 = valueHolderForBorderRadiusTmpValue as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PickerIndicatorStyle {
        let valueDeserializer: DeserializerBase = buffer
        const typeTmpResult: PickerIndicatorType = PickerIndicatorType.fromValue(valueDeserializer.readInt32())
        const strokeWidthTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let strokeWidthTmpBuf: arkui_Graphics_LengthMetrics | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strokeWidthTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const strokeWidthTmpResult: arkui_Graphics_LengthMetrics | undefined = strokeWidthTmpBuf
        const dividerColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let dividerColorTmpBuf: ResourceColor | undefined = undefined
        if ((dividerColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const dividerColorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let dividerColorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (dividerColorTmpBufOptUnionSelector == (0).toByte()) {
                dividerColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (dividerColorTmpBufOptUnionSelector == (1).toByte()) {
                dividerColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (dividerColorTmpBufOptUnionSelector == (2).toByte()) {
                dividerColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (dividerColorTmpBufOptUnionSelector == (3).toByte()) {
                dividerColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for dividerColorTmpBufOpt has to be chosen through deserialisation.')
            }
            dividerColorTmpBuf = (dividerColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const dividerColorTmpResult: ResourceColor | undefined = dividerColorTmpBuf
        const startMarginTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let startMarginTmpBuf: arkui_Graphics_LengthMetrics | undefined = undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startMarginTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const startMarginTmpResult: arkui_Graphics_LengthMetrics | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let endMarginTmpBuf: arkui_Graphics_LengthMetrics | undefined = undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endMarginTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const endMarginTmpResult: arkui_Graphics_LengthMetrics | undefined = endMarginTmpBuf
        const backgroundColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let backgroundColorTmpBuf: ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
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
        const backgroundColorTmpResult: ResourceColor | undefined = backgroundColorTmpBuf
        const borderRadiusTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let borderRadiusTmpBuf: arkui_Graphics_LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderRadiusTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let borderRadiusTmpBufOpt: arkui_Graphics_LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses | undefined
            if (borderRadiusTmpBufOptUnionSelector == (0).toByte()) {
                borderRadiusTmpBufOpt = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
            } else if (borderRadiusTmpBufOptUnionSelector == (1).toByte()) {
                borderRadiusTmpBufOpt = BorderRadiuses_serializer.read(valueDeserializer)
            } else if (borderRadiusTmpBufOptUnionSelector == (2).toByte()) {
                borderRadiusTmpBufOpt = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            borderRadiusTmpBuf = (borderRadiusTmpBufOpt as arkui_Graphics_LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses)
        }
        const borderRadiusTmpResult: arkui_Graphics_LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses | undefined = borderRadiusTmpBuf
        let value: PickerIndicatorStyle = ({type: typeTmpResult, strokeWidth: strokeWidthTmpResult, dividerColor: dividerColorTmpResult, startMargin: startMarginTmpResult, endMargin: endMarginTmpResult, backgroundColor: backgroundColorTmpResult, borderRadius: borderRadiusTmpResult} as PickerIndicatorStyle)
        return value
    }
}
