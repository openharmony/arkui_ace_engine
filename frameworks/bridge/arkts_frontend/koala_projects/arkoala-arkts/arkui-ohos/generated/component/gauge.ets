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
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { LinearGradient_serializer, LinearGradient } from './dataPanel'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, CommonConfiguration, ArkCommonMethodComponent } from './common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length, ResourceStr as arkui_component_units_ResourceStr, Dimension } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { CustomBuilder } from './builder'
import { ContentModifier, AttributeModifier, hookGaugeContentModifier, hookGaugeAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { GaugeModifier } from './../GaugeModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkGaugePeer extends ArkCommonMethodPeer {
    attributeSet?: GaugeModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGaugePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Gauge_construct(peerId, flags)
        const _peer  = new ArkGaugePeer(_peerPtr, peerId, 'Gauge', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGaugeOptionsAttribute(options: GaugeOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        GaugeOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._GaugeInterface_setGaugeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setValueAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setValue(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStartAngleAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setStartAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEndAngleAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setEndAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorsAttribute(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ResourceColor) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceColor
                if (valueTmpValueForIdx0 instanceof arkui_component_enums_Color) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as arkui_component_enums_Color
                    thisSerializer.writeInt32((valueTmpValueForIdx0ForIdx0.getOrdinal()) % (12))
                } else if (valueTmpValueForIdx0 instanceof int32) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as int32
                    thisSerializer.writeInt32(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof LinearGradient) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as LinearGradient
                LinearGradient_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Array) {
                if (valueTmpValue.length == 0) {
                    thisSerializer.writeInt8((2).toByte())
                    thisSerializer.writeInt32(0)
                } else {
                    const valueTmpValueElem  = valueTmpValue[0]
                    if (valueTmpValueElem instanceof Tuple) {
                        thisSerializer.writeInt8((2).toByte())
                        const valueTmpValueForIdx2  = valueTmpValue as Array<[ ResourceColor | LinearGradient, double ]>
                        thisSerializer.writeInt32((valueTmpValueForIdx2.length).toInt())
                        for (let valueTmpValueForIdx2CounterI = 0; valueTmpValueForIdx2CounterI < valueTmpValueForIdx2.length; valueTmpValueForIdx2CounterI++) {
                            const valueTmpValueForIdx2TmpElement : [ ResourceColor | LinearGradient, double ] = valueTmpValueForIdx2[valueTmpValueForIdx2CounterI]
                            const valueTmpValueForIdx2TmpElement_0  = valueTmpValueForIdx2TmpElement[0]
                            if (valueTmpValueForIdx2TmpElement_0 instanceof ResourceColor) {
                                thisSerializer.writeInt8((0).toByte())
                                const valueTmpValueForIdx2TmpElement_0ForIdx0  = valueTmpValueForIdx2TmpElement_0 as ResourceColor
                                if (valueTmpValueForIdx2TmpElement_0ForIdx0 instanceof arkui_component_enums_Color) {
                                    thisSerializer.writeInt8((0).toByte())
                                    const valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx0  = valueTmpValueForIdx2TmpElement_0ForIdx0 as arkui_component_enums_Color
                                    thisSerializer.writeInt32((valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx0.getOrdinal()) % (12))
                                } else if (valueTmpValueForIdx2TmpElement_0ForIdx0 instanceof int32) {
                                    thisSerializer.writeInt8((1).toByte())
                                    const valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx1  = valueTmpValueForIdx2TmpElement_0ForIdx0 as int32
                                    thisSerializer.writeInt32(valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx1)
                                } else if (valueTmpValueForIdx2TmpElement_0ForIdx0 instanceof string) {
                                    thisSerializer.writeInt8((2).toByte())
                                    const valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx2  = valueTmpValueForIdx2TmpElement_0ForIdx0 as string
                                    thisSerializer.writeString(valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx2)
                                } else if (valueTmpValueForIdx2TmpElement_0ForIdx0 instanceof arkui_component_units_Resource) {
                                    thisSerializer.writeInt8((3).toByte())
                                    const valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx3  = valueTmpValueForIdx2TmpElement_0ForIdx0 as arkui_component_units_Resource
                                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx3)
                                }
                            } else if (valueTmpValueForIdx2TmpElement_0 instanceof LinearGradient) {
                                thisSerializer.writeInt8((1).toByte())
                                const valueTmpValueForIdx2TmpElement_0ForIdx1  = valueTmpValueForIdx2TmpElement_0 as LinearGradient
                                LinearGradient_serializer.write(thisSerializer, valueTmpValueForIdx2TmpElement_0ForIdx1)
                            }
                            const valueTmpValueForIdx2TmpElement_1  = valueTmpValueForIdx2TmpElement[1]
                            thisSerializer.writeFloat64(valueTmpValueForIdx2TmpElement_1)
                        }
                    }
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setColors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDescriptionAttribute(value: CustomBuilder | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setDescription(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackShadowAttribute(value: GaugeShadowOptions | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            GaugeShadowOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setTrackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorAttribute(value: GaugeIndicatorOptions | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            GaugeIndicatorOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrivacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GaugeOptions {
    value: double | undefined;
    min?: double;
    max?: double;
}
export interface GaugeShadowOptions extends MultiShadowOptions {
}
export interface GaugeIndicatorOptions {
    icon?: arkui_component_units_ResourceStr;
    space?: Dimension;
}
export interface GaugeConfiguration extends CommonConfiguration<GaugeConfiguration> {
    value: double;
    min: double;
    max: double;
}
export interface GaugeAttribute extends CommonMethod {
    setGaugeOptions(options: GaugeOptions): this {
        throw new Error('Unimplemented method setGaugeOptions')
    }
    value(value: double | undefined): this {
        throw new Error('Unimplemented method value')
    }
    startAngle(value: double | undefined): this {
        throw new Error('Unimplemented method startAngle')
    }
    endAngle(value: double | undefined): this {
        throw new Error('Unimplemented method endAngle')
    }
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined): this {
        throw new Error('Unimplemented method colors')
    }
    strokeWidth(value: Length | undefined): this {
        throw new Error('Unimplemented method strokeWidth')
    }
    description(value: CustomBuilder | null | undefined): this {
        throw new Error('Unimplemented method description')
    }
    trackShadow(value: GaugeShadowOptions | null | undefined): this {
        throw new Error('Unimplemented method trackShadow')
    }
    indicator(value: GaugeIndicatorOptions | null | undefined): this {
        throw new Error('Unimplemented method indicator')
    }
    privacySensitive(value: boolean | undefined): this {
        throw new Error('Unimplemented method privacySensitive')
    }
    contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkGaugeComponent extends ArkCommonMethodComponent implements GaugeAttribute {
    getPeer(): ArkGaugePeer {
        return (this.peer as ArkGaugePeer)
    }
    public setGaugeOptions(options: GaugeOptions): this {
        if (this.checkPriority('setGaugeOptions')) {
            const options_casted = options as (GaugeOptions)
            this.getPeer()?.setGaugeOptionsAttribute(options_casted)
            this.applyOptionsFinish('GaugeAttribute');
            return this
        }
        return this
    }
    public value(value: double | undefined): this {
        if (this.checkPriority('value')) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setValueAttribute(value_casted)
            return this
        }
        return this
    }
    public startAngle(value: double | undefined): this {
        if (this.checkPriority('startAngle')) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setStartAngleAttribute(value_casted)
            return this
        }
        return this
    }
    public endAngle(value: double | undefined): this {
        if (this.checkPriority('endAngle')) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setEndAngleAttribute(value_casted)
            return this
        }
        return this
    }
    public colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined): this {
        if (this.checkPriority('colors')) {
            const value_casted = value as (ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined)
            this.getPeer()?.setColorsAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        if (this.checkPriority('strokeWidth')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public description(value: CustomBuilder | null | undefined): this {
        if (this.checkPriority('description')) {
            const value_casted = value as (CustomBuilder | null | undefined)
            this.getPeer()?.setDescriptionAttribute(value_casted)
            return this
        }
        return this
    }
    public trackShadow(value: GaugeShadowOptions | null | undefined): this {
        if (this.checkPriority('trackShadow')) {
            const value_casted = value as (GaugeShadowOptions | null | undefined)
            this.getPeer()?.setTrackShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public indicator(value: GaugeIndicatorOptions | null | undefined): this {
        if (this.checkPriority('indicator')) {
            const value_casted = value as (GaugeIndicatorOptions | null | undefined)
            this.getPeer()?.setIndicatorAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority('privacySensitive')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPrivacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookGaugeContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookGaugeAttributeModifier(this, value);
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
export function GaugeImpl(
    @memo @memo_skip
    style: ((attributes: GaugeAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkGaugeComponent>((): ArkGaugeComponent => {
        return new ArkGaugeComponent()
    })
    NodeAttach<ArkGaugePeer>((): ArkGaugePeer => ArkGaugePeer.create(receiver), (_: ArkGaugePeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class GaugeConfiguration_serializer {
    public static write(buffer: SerializerBase, value: GaugeConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForValue  = value.value
        valueSerializer.writeFloat64(valueHolderForValue)
        const valueHolderForMin  = value.min
        valueSerializer.writeFloat64(valueHolderForMin)
        const valueHolderForMax  = value.max
        valueSerializer.writeFloat64(valueHolderForMax)
    }
    public static read(buffer: DeserializerBase): GaugeConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<GaugeConfiguration> = (valueDeserializer.readObject() as ContentModifier<GaugeConfiguration>)
        const valueTmpResult : double = valueDeserializer.readFloat64()
        const minTmpResult : double = valueDeserializer.readFloat64()
        const maxTmpResult : double = valueDeserializer.readFloat64()
        let value : GaugeConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, value: valueTmpResult, min: minTmpResult, max: maxTmpResult} as GaugeConfiguration)
        return value
    }
}
export class GaugeOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            valueSerializer.writeFloat64(valueHolderForValueTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMin  = value.min
        if (valueHolderForMin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinTmpValue  = valueHolderForMin!
            valueSerializer.writeFloat64(valueHolderForMinTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMax  = value.max
        if (valueHolderForMax !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxTmpValue  = valueHolderForMax!
            valueSerializer.writeFloat64(valueHolderForMaxTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GaugeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let valueTmpBuf : double | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            valueTmpBuf = valueDeserializer.readFloat64()
        }
        const valueTmpResult : double | undefined = valueTmpBuf
        const minTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let minTmpBuf : double | undefined = undefined
        if ((minTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            minTmpBuf = valueDeserializer.readFloat64()
        }
        const minTmpResult : double | undefined = minTmpBuf
        const maxTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxTmpBuf : double | undefined = undefined
        if ((maxTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxTmpBuf = valueDeserializer.readFloat64()
        }
        const maxTmpResult : double | undefined = maxTmpBuf
        let value : GaugeOptions = ({value: valueTmpResult, min: minTmpResult, max: maxTmpResult} as GaugeOptions)
        return value
    }
}
export class GaugeShadowOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeShadowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRadiusTmpValueForIdx0)
            } else if (valueHolderForRadiusTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffsetX  = value.offsetX
        if (valueHolderForOffsetX !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetXTmpValue  = valueHolderForOffsetX!
            if (valueHolderForOffsetXTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForOffsetXTmpValueForIdx0  = valueHolderForOffsetXTmpValue as double
                valueSerializer.writeFloat64(valueHolderForOffsetXTmpValueForIdx0)
            } else if (valueHolderForOffsetXTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOffsetXTmpValueForIdx1  = valueHolderForOffsetXTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForOffsetXTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffsetY  = value.offsetY
        if (valueHolderForOffsetY !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetYTmpValue  = valueHolderForOffsetY!
            if (valueHolderForOffsetYTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForOffsetYTmpValueForIdx0  = valueHolderForOffsetYTmpValue as double
                valueSerializer.writeFloat64(valueHolderForOffsetYTmpValueForIdx0)
            } else if (valueHolderForOffsetYTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOffsetYTmpValueForIdx1  = valueHolderForOffsetYTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForOffsetYTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GaugeShadowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBufOpt : double | global_resource_Resource | undefined
            if (radiusTmpBufOptUnionSelector == (0).toByte()) {
                radiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (radiusTmpBufOptUnionSelector == (1).toByte()) {
                radiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for radiusTmpBufOpt has to be chosen through deserialisation.')
            }
            radiusTmpBuf = (radiusTmpBufOpt as double | global_resource_Resource)
        }
        const radiusTmpResult : double | global_resource_Resource | undefined = radiusTmpBuf
        const offsetXTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetXTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((offsetXTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetXTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let offsetXTmpBufOpt : double | global_resource_Resource | undefined
            if (offsetXTmpBufOptUnionSelector == (0).toByte()) {
                offsetXTmpBufOpt = valueDeserializer.readFloat64()
            } else if (offsetXTmpBufOptUnionSelector == (1).toByte()) {
                offsetXTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for offsetXTmpBufOpt has to be chosen through deserialisation.')
            }
            offsetXTmpBuf = (offsetXTmpBufOpt as double | global_resource_Resource)
        }
        const offsetXTmpResult : double | global_resource_Resource | undefined = offsetXTmpBuf
        const offsetYTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetYTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((offsetYTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetYTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let offsetYTmpBufOpt : double | global_resource_Resource | undefined
            if (offsetYTmpBufOptUnionSelector == (0).toByte()) {
                offsetYTmpBufOpt = valueDeserializer.readFloat64()
            } else if (offsetYTmpBufOptUnionSelector == (1).toByte()) {
                offsetYTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for offsetYTmpBufOpt has to be chosen through deserialisation.')
            }
            offsetYTmpBuf = (offsetYTmpBufOpt as double | global_resource_Resource)
        }
        const offsetYTmpResult : double | global_resource_Resource | undefined = offsetYTmpBuf
        let value : GaugeShadowOptions = ({radius: radiusTmpResult, offsetX: offsetXTmpResult, offsetY: offsetYTmpResult} as GaugeShadowOptions)
        return value
    }
}
export class GaugeIndicatorOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeIndicatorOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            if (valueHolderForSpaceTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSpaceTmpValueForIdx0  = valueHolderForSpaceTmpValue as string
                valueSerializer.writeString(valueHolderForSpaceTmpValueForIdx0)
            } else if (valueHolderForSpaceTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSpaceTmpValueForIdx1  = valueHolderForSpaceTmpValue as number
                valueSerializer.writeNumber(valueHolderForSpaceTmpValueForIdx1)
            } else if (valueHolderForSpaceTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSpaceTmpValueForIdx2  = valueHolderForSpaceTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSpaceTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GaugeIndicatorOptions {
        let valueDeserializer : DeserializerBase = buffer
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let iconTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (iconTmpBufOptUnionSelector == (0).toByte()) {
                iconTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (iconTmpBufOptUnionSelector == (1).toByte()) {
                iconTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for iconTmpBufOpt has to be chosen through deserialisation.')
            }
            iconTmpBuf = (iconTmpBufOpt as string | arkui_component_units_Resource)
        }
        const iconTmpResult : arkui_component_units_ResourceStr | undefined = iconTmpBuf
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let spaceTmpBuf : Dimension | undefined = undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spaceTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let spaceTmpBufOpt : string | number | global_resource_Resource | undefined
            if (spaceTmpBufOptUnionSelector == (0).toByte()) {
                spaceTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (spaceTmpBufOptUnionSelector == (1).toByte()) {
                spaceTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (spaceTmpBufOptUnionSelector == (2).toByte()) {
                spaceTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for spaceTmpBufOpt has to be chosen through deserialisation.')
            }
            spaceTmpBuf = (spaceTmpBufOpt as string | number | global_resource_Resource)
        }
        const spaceTmpResult : Dimension | undefined = spaceTmpBuf
        let value : GaugeIndicatorOptions = ({icon: iconTmpResult, space: spaceTmpResult} as GaugeIndicatorOptions)
        return value
    }
}
