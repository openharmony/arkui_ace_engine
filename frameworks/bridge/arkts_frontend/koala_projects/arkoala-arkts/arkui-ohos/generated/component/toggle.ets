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
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, resourceFinalizerRegister, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, Callback as arkui_component_common_Callback, Bindable, ArkCommonMethodComponent, Bindable_Boolean_serializer } from './common'
import { ContentModifier, AttributeModifier, hookToggleContentModifier, hookToggleAttributeModifier, AttributeUpdater } from '#handwritten'
import { ResourceColor, Resource as arkui_component_units_Resource } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { ToggleModifier } from './../ToggleModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkTogglePeer extends ArkCommonMethodPeer {
    attributeSet?: ToggleModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTogglePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Toggle_construct(peerId, flags)
        const _peer  = new ArkTogglePeer(_peerPtr, peerId, 'Toggle', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setToggleOptionsAttribute(options: ToggleOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ToggleOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ToggleInterface_setToggleOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((isSelected: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSwitchPointColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setSwitchPointColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSwitchStyleAttribute(value: SwitchStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SwitchStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setSwitchStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ToggleType {
    Checkbox = 0,
    Switch = 1,
    Button = 2,
    CHECKBOX = 0,
    SWITCH = 1,
    BUTTON = 2
}
export interface SwitchStyle {
    pointRadius?: double | global_resource_Resource;
    unselectedColor?: ResourceColor;
    pointColor?: ResourceColor;
    trackBorderRadius?: double | global_resource_Resource;
}
export interface ToggleConfiguration extends CommonConfiguration<ToggleConfiguration> {
    isOn: boolean;
    triggerChange: arkui_component_common_Callback<boolean, void>;
}
export interface ToggleOptions {
    type: ToggleType;
    isOn?: boolean | Bindable<boolean> | undefined;
}
export interface ToggleAttribute extends CommonMethod {
    setToggleOptions(options: ToggleOptions): this {
        throw new Error('Unimplemented method setToggleOptions')
    }
    onChange(value: ((isSelected: boolean) => void) | undefined): this {
        throw new Error('Unimplemented method onChange')
    }
    contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method selectedColor')
    }
    switchPointColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method switchPointColor')
    }
    switchStyle(value: SwitchStyle | undefined): this {
        throw new Error('Unimplemented method switchStyle')
    }
    attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkToggleComponent extends ArkCommonMethodComponent implements ToggleAttribute {
    getPeer(): ArkTogglePeer {
        return (this.peer as ArkTogglePeer)
    }
    public setToggleOptions(options: ToggleOptions): this {
        if (this.checkPriority('setToggleOptions')) {
            const options_casted = options as (ToggleOptions)
            this.getPeer()?.setToggleOptionsAttribute(options_casted)
            this.applyOptionsFinish('ToggleAttribute');
            return this
        }
        return this
    }
    public onChange(value: ((isSelected: boolean) => void) | undefined): this {
        if (this.checkPriority('onChange')) {
            const value_casted = value as (((isSelected: boolean) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookToggleContentModifier(this, value)
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('selectedColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public switchPointColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('switchPointColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSwitchPointColorAttribute(value_casted)
            return this
        }
        return this
    }
    public switchStyle(value: SwitchStyle | undefined): this {
        if (this.checkPriority('switchStyle')) {
            const value_casted = value as (SwitchStyle | undefined)
            this.getPeer()?.setSwitchStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookToggleAttributeModifier(this, value);
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
export function ToggleImpl(
    @memo @memo_skip
    style: ((attributes: ToggleAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkToggleComponent>((): ArkToggleComponent => {
        return new ArkToggleComponent()
    })
    NodeAttach<ArkTogglePeer>((): ArkTogglePeer => ArkTogglePeer.create(receiver), (_: ArkTogglePeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class ToggleConfiguration_serializer {
    public static write(buffer: SerializerBase, value: ToggleConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForIsOn  = value.isOn
        valueSerializer.writeBoolean(valueHolderForIsOn)
        const valueHolderForTriggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerChange)
    }
    public static read(buffer: DeserializerBase): ToggleConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<ToggleConfiguration> = (valueDeserializer.readObject() as ContentModifier<ToggleConfiguration>)
        const isOnTmpResult : boolean = valueDeserializer.readBoolean()
        const triggerChangeTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChangeTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufClosure  = (data: boolean):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeBoolean(data);
            InteropNativeModule._CallCallbackSync(10, -1691789173, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
            triggerChangeTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(triggerChangeTmpBufClosure, triggerChangeTmpBufBufResource)
        const triggerChangeTmpResult : arkui_component_common_Callback<boolean, void> = triggerChangeTmpBufClosure
        let value : ToggleConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, isOn: isOnTmpResult, triggerChange: triggerChangeTmpResult} as ToggleConfiguration)
        return value
    }
}
export class SwitchStyle_serializer {
    public static write(buffer: SerializerBase, value: SwitchStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPointRadius  = value.pointRadius
        if (valueHolderForPointRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPointRadiusTmpValue  = valueHolderForPointRadius!
            if (valueHolderForPointRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPointRadiusTmpValueForIdx0  = valueHolderForPointRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForPointRadiusTmpValueForIdx0)
            } else if (valueHolderForPointRadiusTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPointRadiusTmpValueForIdx1  = valueHolderForPointRadiusTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForPointRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnselectedColor  = value.unselectedColor
        if (valueHolderForUnselectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnselectedColorTmpValue  = valueHolderForUnselectedColor!
            if (valueHolderForUnselectedColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx0  = valueHolderForUnselectedColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForUnselectedColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForUnselectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx1  = valueHolderForUnselectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx1)
            } else if (valueHolderForUnselectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx2  = valueHolderForUnselectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForUnselectedColorTmpValueForIdx2)
            } else if (valueHolderForUnselectedColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx3  = valueHolderForUnselectedColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForUnselectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPointColor  = value.pointColor
        if (valueHolderForPointColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPointColorTmpValue  = valueHolderForPointColor!
            if (valueHolderForPointColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPointColorTmpValueForIdx0  = valueHolderForPointColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForPointColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForPointColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPointColorTmpValueForIdx1  = valueHolderForPointColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForPointColorTmpValueForIdx1)
            } else if (valueHolderForPointColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForPointColorTmpValueForIdx2  = valueHolderForPointColorTmpValue as string
                valueSerializer.writeString(valueHolderForPointColorTmpValueForIdx2)
            } else if (valueHolderForPointColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForPointColorTmpValueForIdx3  = valueHolderForPointColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForPointColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTrackBorderRadius  = value.trackBorderRadius
        if (valueHolderForTrackBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTrackBorderRadiusTmpValue  = valueHolderForTrackBorderRadius!
            if (valueHolderForTrackBorderRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTrackBorderRadiusTmpValueForIdx0  = valueHolderForTrackBorderRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForTrackBorderRadiusTmpValueForIdx0)
            } else if (valueHolderForTrackBorderRadiusTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTrackBorderRadiusTmpValueForIdx1  = valueHolderForTrackBorderRadiusTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTrackBorderRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SwitchStyle {
        let valueDeserializer : DeserializerBase = buffer
        const pointRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let pointRadiusTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((pointRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const pointRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let pointRadiusTmpBufOpt : double | global_resource_Resource | undefined
            if (pointRadiusTmpBufOptUnionSelector == (0).toByte()) {
                pointRadiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (pointRadiusTmpBufOptUnionSelector == (1).toByte()) {
                pointRadiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for pointRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            pointRadiusTmpBuf = (pointRadiusTmpBufOpt as double | global_resource_Resource)
        }
        const pointRadiusTmpResult : double | global_resource_Resource | undefined = pointRadiusTmpBuf
        const unselectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let unselectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((unselectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const unselectedColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let unselectedColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (unselectedColorTmpBufOptUnionSelector == (0).toByte()) {
                unselectedColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (unselectedColorTmpBufOptUnionSelector == (1).toByte()) {
                unselectedColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (unselectedColorTmpBufOptUnionSelector == (2).toByte()) {
                unselectedColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (unselectedColorTmpBufOptUnionSelector == (3).toByte()) {
                unselectedColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for unselectedColorTmpBufOpt has to be chosen through deserialisation.')
            }
            unselectedColorTmpBuf = (unselectedColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const unselectedColorTmpResult : ResourceColor | undefined = unselectedColorTmpBuf
        const pointColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let pointColorTmpBuf : ResourceColor | undefined = undefined
        if ((pointColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const pointColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let pointColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (pointColorTmpBufOptUnionSelector == (0).toByte()) {
                pointColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (pointColorTmpBufOptUnionSelector == (1).toByte()) {
                pointColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (pointColorTmpBufOptUnionSelector == (2).toByte()) {
                pointColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (pointColorTmpBufOptUnionSelector == (3).toByte()) {
                pointColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for pointColorTmpBufOpt has to be chosen through deserialisation.')
            }
            pointColorTmpBuf = (pointColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const pointColorTmpResult : ResourceColor | undefined = pointColorTmpBuf
        const trackBorderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let trackBorderRadiusTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((trackBorderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const trackBorderRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let trackBorderRadiusTmpBufOpt : double | global_resource_Resource | undefined
            if (trackBorderRadiusTmpBufOptUnionSelector == (0).toByte()) {
                trackBorderRadiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (trackBorderRadiusTmpBufOptUnionSelector == (1).toByte()) {
                trackBorderRadiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for trackBorderRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            trackBorderRadiusTmpBuf = (trackBorderRadiusTmpBufOpt as double | global_resource_Resource)
        }
        const trackBorderRadiusTmpResult : double | global_resource_Resource | undefined = trackBorderRadiusTmpBuf
        let value : SwitchStyle = ({pointRadius: pointRadiusTmpResult, unselectedColor: unselectedColorTmpResult, pointColor: pointColorTmpResult, trackBorderRadius: trackBorderRadiusTmpResult} as SwitchStyle)
        return value
    }
}
export class ToggleOptions_serializer {
    public static write(buffer: SerializerBase, value: ToggleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
        const valueHolderForIsOn  = value.isOn
        if (valueHolderForIsOn !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsOnTmpValue  = valueHolderForIsOn!
            if (valueHolderForIsOnTmpValue instanceof boolean) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIsOnTmpValueForIdx0  = valueHolderForIsOnTmpValue as boolean
                valueSerializer.writeBoolean(valueHolderForIsOnTmpValueForIdx0)
            } else if (valueHolderForIsOnTmpValue instanceof Bindable) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIsOnTmpValueForIdx1  = valueHolderForIsOnTmpValue as Bindable<boolean>
                Bindable_Boolean_serializer.write(valueSerializer, valueHolderForIsOnTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ToggleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : ToggleType = ToggleType.fromValue(valueDeserializer.readInt32())
        const isOnTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let isOnTmpBuf : boolean | Bindable<boolean> | undefined = undefined
        if ((isOnTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const isOnTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let isOnTmpBufOpt : boolean | Bindable<boolean> | undefined
            if (isOnTmpBufOptUnionSelector == (0).toByte()) {
                isOnTmpBufOpt = valueDeserializer.readBoolean()
            } else if (isOnTmpBufOptUnionSelector == (1).toByte()) {
                isOnTmpBufOpt = Bindable_Boolean_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for isOnTmpBufOpt has to be chosen through deserialisation.')
            }
            isOnTmpBuf = (isOnTmpBufOpt as boolean | Bindable<boolean>)
        }
        const isOnTmpResult : boolean | Bindable<boolean> | undefined = isOnTmpBuf
        let value : ToggleOptions = ({type: typeTmpResult, isOn: isOnTmpResult} as ToggleOptions)
        return value
    }
}
