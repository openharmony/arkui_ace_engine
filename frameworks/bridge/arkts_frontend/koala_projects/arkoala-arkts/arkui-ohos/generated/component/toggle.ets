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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_Boolean_serializer } from "./common"
import { ContentModifier, AttributeModifier, hookToggleContentModifier, hookToggleAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { ResourceColor } from "./units"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ToggleModifier } from "./../ToggleModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkTogglePeer extends ArkCommonMethodPeer {
    attributeSet?: ToggleModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ToggleOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ToggleInterface_setToggleOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value0: boolean) => void) | undefined): void {
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
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
    CHECKBOX = 0,
    Checkbox = 0,
    SWITCH = 1,
    Switch = 1,
    BUTTON = 2,
    Button = 2
}
export interface SwitchStyle {
    pointRadius?: double | Resource;
    unselectedColor?: ResourceColor;
    pointColor?: ResourceColor;
    trackBorderRadius?: double | Resource;
}
export interface ToggleConfiguration extends CommonConfiguration<ToggleConfiguration> {
    isOn: boolean;
    toggleEnabled: boolean;
    triggerChange: ((value0: boolean) => void);
}
export interface ToggleOptions {
    type: ToggleType;
    isOn?: boolean | Bindable<boolean> | undefined;
}
export interface ToggleAttribute extends CommonMethod {
    setToggleOptions(options: ToggleOptions): this {
        throw new Error("Unimplemented method setToggleOptions")
    }
    onChange(value: ((value0: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    switchPointColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method switchPointColor")
    }
    switchStyle(value: SwitchStyle | undefined): this {
        throw new Error("Unimplemented method switchStyle")
    }
    attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkToggleStyle extends ArkCommonMethodStyle implements ToggleAttribute {
    onChange_value?: ((value0: boolean) => void) | undefined
    contentModifier_value?: ContentModifier<ToggleConfiguration> | undefined
    selectedColor_value?: ResourceColor | undefined
    switchPointColor_value?: ResourceColor | undefined
    switchStyle_value?: SwitchStyle | undefined
    attributeModifier_value?: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined
    setToggleOptions(options: ToggleOptions): this {
        return this
    }
    onChange(value: ((value0: boolean) => void) | undefined): this {
        return this
    }
    contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    switchPointColor(value: ResourceColor | undefined): this {
        return this
    }
    switchStyle(value: SwitchStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkToggleComponent extends ArkCommonMethodComponent implements ToggleAttribute {
    getPeer(): ArkTogglePeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkTogglePeer)
    }
    public setToggleOptions(options: ToggleOptions): this {
        if (this.checkPriority("setToggleOptions")) {
            const options_casted = options as (ToggleOptions)
            this.getPeer()?.setToggleOptionsAttribute(options_casted)
            this.applyOptionsFinish('ToggleAttribute');
            return this
        }
        return this
    }
    public onChange(value: ((value0: boolean) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: boolean) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            hookToggleContentModifier(this, value)
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public switchPointColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("switchPointColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSwitchPointColorAttribute(value_casted)
            return this
        }
        return this
    }
    public switchStyle(value: SwitchStyle | undefined): this {
        if (this.checkPriority("switchStyle")) {
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
    @memo
    style: ((attributes: ToggleAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkToggleComponent>((): ArkToggleComponent => {
        return new ArkToggleComponent()
    })
    NodeAttach<ArkTogglePeer>((): ArkTogglePeer => ArkTogglePeer.create(receiver), (peer: ArkTogglePeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
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
        const valueHolderForToggleEnabled  = value.toggleEnabled
        valueSerializer.writeBoolean(valueHolderForToggleEnabled)
        const valueHolderForTriggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerChange)
    }
    public static read(buffer: DeserializerBase): ToggleConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<ToggleConfiguration> = (valueDeserializer.readObject() as ContentModifier<ToggleConfiguration>)
        const isOnTmpResult : boolean = valueDeserializer.readBoolean()
        const toggleEnabledTmpResult : boolean = valueDeserializer.readBoolean()
        const triggerChangeTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChangeTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpResult : ((value0: boolean) => void) = (value0: boolean):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeBoolean(value0);
            InteropNativeModule._CallCallbackSync(10, 313269291, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
            triggerChangeTmpBufBufArgsSerializer.release();
            return;
        }
        let value : ToggleConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, isOn: isOnTmpResult, toggleEnabled: toggleEnabledTmpResult, triggerChange: triggerChangeTmpResult} as ToggleConfiguration)
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
            } else if (valueHolderForPointRadiusTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPointRadiusTmpValueForIdx1  = valueHolderForPointRadiusTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForPointRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnselectedColor  = value.unselectedColor
        if (valueHolderForUnselectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnselectedColorTmpValue  = valueHolderForUnselectedColor!
            if (valueHolderForUnselectedColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx0  = valueHolderForUnselectedColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForUnselectedColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx1  = valueHolderForUnselectedColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForUnselectedColorTmpValueForIdx1)
            } else if (valueHolderForUnselectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx2  = valueHolderForUnselectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForUnselectedColorTmpValueForIdx2)
            } else if (valueHolderForUnselectedColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx3  = valueHolderForUnselectedColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForUnselectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPointColor  = value.pointColor
        if (valueHolderForPointColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPointColorTmpValue  = valueHolderForPointColor!
            if (valueHolderForPointColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPointColorTmpValueForIdx0  = valueHolderForPointColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForPointColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForPointColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPointColorTmpValueForIdx1  = valueHolderForPointColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForPointColorTmpValueForIdx1)
            } else if (valueHolderForPointColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForPointColorTmpValueForIdx2  = valueHolderForPointColorTmpValue as string
                valueSerializer.writeString(valueHolderForPointColorTmpValueForIdx2)
            } else if (valueHolderForPointColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForPointColorTmpValueForIdx3  = valueHolderForPointColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForPointColorTmpValueForIdx3)
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
            } else if (valueHolderForTrackBorderRadiusTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTrackBorderRadiusTmpValueForIdx1  = valueHolderForTrackBorderRadiusTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTrackBorderRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SwitchStyle {
        let valueDeserializer : DeserializerBase = buffer
        const pointRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let pointRadiusTmpBuf : double | Resource | undefined = undefined
        if ((pointRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const pointRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let pointRadiusTmpBuf_ : double | Resource | undefined
            if (pointRadiusTmpBuf_UnionSelector == (0).toChar()) {
                pointRadiusTmpBuf_ = valueDeserializer.readFloat64()
            } else if (pointRadiusTmpBuf_UnionSelector == (1).toChar()) {
                pointRadiusTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for pointRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            pointRadiusTmpBuf = (pointRadiusTmpBuf_ as double | Resource)
        }
        const pointRadiusTmpResult : double | Resource | undefined = pointRadiusTmpBuf
        const unselectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let unselectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((unselectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const unselectedColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let unselectedColorTmpBuf_ : Color | number | string | Resource | undefined
            if (unselectedColorTmpBuf_UnionSelector == (0).toChar()) {
                unselectedColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (unselectedColorTmpBuf_UnionSelector == (1).toChar()) {
                unselectedColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (unselectedColorTmpBuf_UnionSelector == (2).toChar()) {
                unselectedColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (unselectedColorTmpBuf_UnionSelector == (3).toChar()) {
                unselectedColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for unselectedColorTmpBuf_ has to be chosen through deserialisation.")
            }
            unselectedColorTmpBuf = (unselectedColorTmpBuf_ as Color | number | string | Resource)
        }
        const unselectedColorTmpResult : ResourceColor | undefined = unselectedColorTmpBuf
        const pointColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let pointColorTmpBuf : ResourceColor | undefined = undefined
        if ((pointColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const pointColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let pointColorTmpBuf_ : Color | number | string | Resource | undefined
            if (pointColorTmpBuf_UnionSelector == (0).toChar()) {
                pointColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (pointColorTmpBuf_UnionSelector == (1).toChar()) {
                pointColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (pointColorTmpBuf_UnionSelector == (2).toChar()) {
                pointColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (pointColorTmpBuf_UnionSelector == (3).toChar()) {
                pointColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for pointColorTmpBuf_ has to be chosen through deserialisation.")
            }
            pointColorTmpBuf = (pointColorTmpBuf_ as Color | number | string | Resource)
        }
        const pointColorTmpResult : ResourceColor | undefined = pointColorTmpBuf
        const trackBorderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let trackBorderRadiusTmpBuf : double | Resource | undefined = undefined
        if ((trackBorderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const trackBorderRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let trackBorderRadiusTmpBuf_ : double | Resource | undefined
            if (trackBorderRadiusTmpBuf_UnionSelector == (0).toChar()) {
                trackBorderRadiusTmpBuf_ = valueDeserializer.readFloat64()
            } else if (trackBorderRadiusTmpBuf_UnionSelector == (1).toChar()) {
                trackBorderRadiusTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for trackBorderRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            trackBorderRadiusTmpBuf = (trackBorderRadiusTmpBuf_ as double | Resource)
        }
        const trackBorderRadiusTmpResult : double | Resource | undefined = trackBorderRadiusTmpBuf
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
            } else if (valueHolderForIsOnTmpValue instanceof Bindable<boolean>) {
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
        const isOnTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isOnTmpBuf : boolean | Bindable<boolean> | undefined = undefined
        if ((isOnTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const isOnTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let isOnTmpBuf_ : boolean | Bindable<boolean> | undefined
            if (isOnTmpBuf_UnionSelector == (0).toChar()) {
                isOnTmpBuf_ = valueDeserializer.readBoolean()
            } else if (isOnTmpBuf_UnionSelector == (1).toChar()) {
                isOnTmpBuf_ = Bindable_Boolean_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for isOnTmpBuf_ has to be chosen through deserialisation.")
            }
            isOnTmpBuf = (isOnTmpBuf_ as boolean | Bindable<boolean>)
        }
        const isOnTmpResult : boolean | Bindable<boolean> | undefined = isOnTmpBuf
        let value : ToggleOptions = ({type: typeTmpResult, isOn: isOnTmpResult} as ToggleOptions)
        return value
    }
}
