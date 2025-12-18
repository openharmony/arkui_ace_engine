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
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent } from './common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length, PX, VP, LPX, Font as arkui_component_units_Font, arkui_component_units_Font_serializer } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { ContentModifier, AttributeModifier, hookProgressContentModifier, hookProgressAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from '@arkui.Graphics'
import { ProgressModifier } from './../ProgressModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
export class ArkProgressPeer extends ArkCommonMethodPeer {
    attributeSet?: ProgressModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkProgressPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Progress_construct(peerId, flags)
        const _peer  = new ArkProgressPeer(_peerPtr, peerId, 'Progress', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setProgressOptionsAttribute(options: ProgressOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ProgressOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ProgressInterface_setProgressOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ProgressAttribute_setValue(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
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
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStyleAttribute(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof LinearStyleOptions) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as LinearStyleOptions
                LinearStyleOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof RingStyleOptions) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as RingStyleOptions
                RingStyleOptions_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof CapsuleStyleOptions) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as CapsuleStyleOptions
                CapsuleStyleOptions_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof ProgressStyleOptions) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as ProgressStyleOptions
                ProgressStyleOptions_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_setStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ProgressAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ProgressOptions {
    value: double;
    total?: double;
    type?: ProgressType;
}
export enum ProgressType {
    Linear = 0,
    Ring = 1,
    Eclipse = 2,
    ScaleRing = 3,
    Capsule = 4,
    LINEAR = 0,
    RING = 1,
    ECLIPSE = 2,
    SCALE_RING = 3,
    CAPSULE = 4
}
export enum ProgressStatus {
    LOADING = 0,
    PROGRESSING = 1
}
export interface ProgressStyleOptions extends CommonProgressStyleOptions {
    strokeWidth?: Length;
    scaleCount?: int32;
    scaleWidth?: Length;
}
export interface CommonProgressStyleOptions {
    enableSmoothEffect?: boolean;
}
export interface ScanEffectOptions {
    enableScanEffect?: boolean;
}
export interface EclipseStyleOptions extends CommonProgressStyleOptions {
}
export interface ScaleRingStyleOptions extends CommonProgressStyleOptions {
    strokeWidth?: Length;
    scaleWidth?: Length;
    scaleCount?: int32;
}
export interface RingStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    strokeWidth?: Length;
    shadow?: boolean;
    status?: ProgressStatus;
}
export interface LinearStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    strokeWidth?: Length;
    strokeRadius?: PX | VP | LPX | global_resource_Resource;
}
export interface CapsuleStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    borderColor?: ResourceColor;
    borderWidth?: Length;
    content?: string;
    font?: arkui_component_units_Font;
    fontColor?: ResourceColor;
    showDefaultPercentage?: boolean;
    borderRadius?: arkui_Graphics_LengthMetrics;
}
export enum ProgressStyle {
    Linear = 0,
    Ring = 1,
    Eclipse = 2,
    ScaleRing = 3,
    Capsule = 4,
    LINEAR = 0,
    RING = 1,
    ECLIPSE = 2,
    SCALE_RING = 3,
    CAPSULE = 4
}
export interface ProgressStyleMap {
}
export interface ProgressAttribute extends CommonMethod {
    setProgressOptions(options: ProgressOptions): this {
        throw new Error('Unimplemented method setProgressOptions')
    }
    value(value: double | undefined): this {
        throw new Error('Unimplemented method value')
    }
    color(value: ResourceColor | LinearGradient | undefined): this {
        throw new Error('Unimplemented method color')
    }
    style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        throw new Error('Unimplemented method style')
    }
    privacySensitive(value: boolean | undefined): this {
        throw new Error('Unimplemented method privacySensitive')
    }
    contentModifier(value: ContentModifier<ProgressConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    attributeModifier(value: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface ProgressConfiguration extends CommonConfiguration<ProgressConfiguration> {
    value: double;
    total: double;
}

export class ArkProgressComponent extends ArkCommonMethodComponent implements ProgressAttribute {
    getPeer(): ArkProgressPeer {
        return (this.peer as ArkProgressPeer)
    }
    public setProgressOptions(options: ProgressOptions): this {
        if (this.checkPriority('setProgressOptions')) {
            const options_casted = options as (ProgressOptions)
            this.getPeer()?.setProgressOptionsAttribute(options_casted)
            this.applyOptionsFinish('ProgressAttribute');
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
    public color(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority('color')) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.setColorAttribute(value_casted)
            return this
        }
        return this
    }
    public style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        if (this.checkPriority('style')) {
            const value_casted = value as (LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined)
            this.getPeer()?.setStyleAttribute(value_casted)
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
    public contentModifier(value: ContentModifier<ProgressConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookProgressContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookProgressAttributeModifier(this, value);
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
export function ProgressImpl(
    @memo @memo_skip
    style: ((attributes: ProgressAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkProgressComponent>((): ArkProgressComponent => {
        return new ArkProgressComponent()
    })
    NodeAttach<ArkProgressPeer>((): ArkProgressPeer => ArkProgressPeer.create(receiver), (_: ArkProgressPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class ProgressConfiguration_serializer {
    public static write(buffer: SerializerBase, value: ProgressConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForValue  = value.value
        valueSerializer.writeFloat64(valueHolderForValue)
        const valueHolderForTotal  = value.total
        valueSerializer.writeFloat64(valueHolderForTotal)
    }
    public static read(buffer: DeserializerBase): ProgressConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<ProgressConfiguration> = (valueDeserializer.readObject() as ContentModifier<ProgressConfiguration>)
        const valueTmpResult : double = valueDeserializer.readFloat64()
        const totalTmpResult : double = valueDeserializer.readFloat64()
        let value : ProgressConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, value: valueTmpResult, total: totalTmpResult} as ProgressConfiguration)
        return value
    }
}
export class ProgressOptions_serializer {
    public static write(buffer: SerializerBase, value: ProgressOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        valueSerializer.writeFloat64(valueHolderForValue)
        const valueHolderForTotal  = value.total
        if (valueHolderForTotal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTotalTmpValue  = valueHolderForTotal!
            valueSerializer.writeFloat64(valueHolderForTotalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = (valueHolderForType as ProgressType)
            valueSerializer.writeInt32(valueHolderForTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ProgressOptions {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpResult : double = valueDeserializer.readFloat64()
        const totalTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let totalTmpBuf : double | undefined = undefined
        if ((totalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            totalTmpBuf = valueDeserializer.readFloat64()
        }
        const totalTmpResult : double | undefined = totalTmpBuf
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let typeTmpBuf : ProgressType | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = ProgressType.fromValue(valueDeserializer.readInt32())
        }
        const typeTmpResult : ProgressType | undefined = typeTmpBuf
        let value : ProgressOptions = ({value: valueTmpResult, total: totalTmpResult, type: typeTmpResult} as ProgressOptions)
        return value
    }
}
export class LinearStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: LinearStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnableScanEffect  = value.enableScanEffect
        if (valueHolderForEnableScanEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableScanEffectTmpValue  = valueHolderForEnableScanEffect!
            valueSerializer.writeBoolean(valueHolderForEnableScanEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableSmoothEffect  = value.enableSmoothEffect
        if (valueHolderForEnableSmoothEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableSmoothEffectTmpValue  = valueHolderForEnableSmoothEffect!
            valueSerializer.writeBoolean(valueHolderForEnableSmoothEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            if (valueHolderForStrokeWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx0  = valueHolderForStrokeWidthTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeWidthTmpValueForIdx0)
            } else if (valueHolderForStrokeWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx1  = valueHolderForStrokeWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForStrokeWidthTmpValueForIdx1)
            } else if (valueHolderForStrokeWidthTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx2  = valueHolderForStrokeWidthTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeRadius  = value.strokeRadius
        if (valueHolderForStrokeRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeRadiusTmpValue  = valueHolderForStrokeRadius!
            if (valueHolderForStrokeRadiusTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeRadiusTmpValueForIdx0  = valueHolderForStrokeRadiusTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeRadiusTmpValueForIdx0)
            } else if (valueHolderForStrokeRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeRadiusTmpValueForIdx1  = valueHolderForStrokeRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForStrokeRadiusTmpValueForIdx1)
            } else if (valueHolderForStrokeRadiusTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeRadiusTmpValueForIdx2  = valueHolderForStrokeRadiusTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStrokeRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LinearStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableScanEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableScanEffectTmpBuf : boolean | undefined = undefined
        if ((enableScanEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableScanEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableScanEffectTmpResult : boolean | undefined = enableScanEffectTmpBuf
        const enableSmoothEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableSmoothEffectTmpBuf : boolean | undefined = undefined
        if ((enableSmoothEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableSmoothEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableSmoothEffectTmpResult : boolean | undefined = enableSmoothEffectTmpBuf
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeWidthTmpBuf : Length | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let strokeWidthTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (strokeWidthTmpBufOptUnionSelector == (0).toByte()) {
                strokeWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (strokeWidthTmpBufOptUnionSelector == (1).toByte()) {
                strokeWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (strokeWidthTmpBufOptUnionSelector == (2).toByte()) {
                strokeWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for strokeWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            strokeWidthTmpBuf = (strokeWidthTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const strokeWidthTmpResult : Length | undefined = strokeWidthTmpBuf
        const strokeRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeRadiusTmpBuf : string | double | global_resource_Resource | undefined = undefined
        if ((strokeRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let strokeRadiusTmpBufOpt : string | double | global_resource_Resource | undefined
            if (strokeRadiusTmpBufOptUnionSelector == (0).toByte()) {
                strokeRadiusTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (strokeRadiusTmpBufOptUnionSelector == (1).toByte()) {
                strokeRadiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (strokeRadiusTmpBufOptUnionSelector == (2).toByte()) {
                strokeRadiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for strokeRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            strokeRadiusTmpBuf = (strokeRadiusTmpBufOpt as string | double | global_resource_Resource)
        }
        const strokeRadiusTmpResult : PX | VP | LPX | global_resource_Resource | undefined = strokeRadiusTmpBuf
        let value : LinearStyleOptions = ({enableScanEffect: enableScanEffectTmpResult, enableSmoothEffect: enableSmoothEffectTmpResult, strokeWidth: strokeWidthTmpResult, strokeRadius: strokeRadiusTmpResult} as LinearStyleOptions)
        return value
    }
}
export class ProgressStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: ProgressStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnableSmoothEffect  = value.enableSmoothEffect
        if (valueHolderForEnableSmoothEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableSmoothEffectTmpValue  = valueHolderForEnableSmoothEffect!
            valueSerializer.writeBoolean(valueHolderForEnableSmoothEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            if (valueHolderForStrokeWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx0  = valueHolderForStrokeWidthTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeWidthTmpValueForIdx0)
            } else if (valueHolderForStrokeWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx1  = valueHolderForStrokeWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForStrokeWidthTmpValueForIdx1)
            } else if (valueHolderForStrokeWidthTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx2  = valueHolderForStrokeWidthTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScaleCount  = value.scaleCount
        if (valueHolderForScaleCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScaleCountTmpValue  = valueHolderForScaleCount!
            valueSerializer.writeInt32(valueHolderForScaleCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScaleWidth  = value.scaleWidth
        if (valueHolderForScaleWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScaleWidthTmpValue  = valueHolderForScaleWidth!
            if (valueHolderForScaleWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForScaleWidthTmpValueForIdx0  = valueHolderForScaleWidthTmpValue as string
                valueSerializer.writeString(valueHolderForScaleWidthTmpValueForIdx0)
            } else if (valueHolderForScaleWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForScaleWidthTmpValueForIdx1  = valueHolderForScaleWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForScaleWidthTmpValueForIdx1)
            } else if (valueHolderForScaleWidthTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForScaleWidthTmpValueForIdx2  = valueHolderForScaleWidthTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForScaleWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ProgressStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableSmoothEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableSmoothEffectTmpBuf : boolean | undefined = undefined
        if ((enableSmoothEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableSmoothEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableSmoothEffectTmpResult : boolean | undefined = enableSmoothEffectTmpBuf
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeWidthTmpBuf : Length | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let strokeWidthTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (strokeWidthTmpBufOptUnionSelector == (0).toByte()) {
                strokeWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (strokeWidthTmpBufOptUnionSelector == (1).toByte()) {
                strokeWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (strokeWidthTmpBufOptUnionSelector == (2).toByte()) {
                strokeWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for strokeWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            strokeWidthTmpBuf = (strokeWidthTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const strokeWidthTmpResult : Length | undefined = strokeWidthTmpBuf
        const scaleCountTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let scaleCountTmpBuf : int32 | undefined = undefined
        if ((scaleCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scaleCountTmpBuf = valueDeserializer.readInt32()
        }
        const scaleCountTmpResult : int32 | undefined = scaleCountTmpBuf
        const scaleWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let scaleWidthTmpBuf : Length | undefined = undefined
        if ((scaleWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const scaleWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let scaleWidthTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (scaleWidthTmpBufOptUnionSelector == (0).toByte()) {
                scaleWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (scaleWidthTmpBufOptUnionSelector == (1).toByte()) {
                scaleWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (scaleWidthTmpBufOptUnionSelector == (2).toByte()) {
                scaleWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for scaleWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            scaleWidthTmpBuf = (scaleWidthTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const scaleWidthTmpResult : Length | undefined = scaleWidthTmpBuf
        let value : ProgressStyleOptions = ({enableSmoothEffect: enableSmoothEffectTmpResult, strokeWidth: strokeWidthTmpResult, scaleCount: scaleCountTmpResult, scaleWidth: scaleWidthTmpResult} as ProgressStyleOptions)
        return value
    }
}
export class RingStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RingStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnableScanEffect  = value.enableScanEffect
        if (valueHolderForEnableScanEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableScanEffectTmpValue  = valueHolderForEnableScanEffect!
            valueSerializer.writeBoolean(valueHolderForEnableScanEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableSmoothEffect  = value.enableSmoothEffect
        if (valueHolderForEnableSmoothEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableSmoothEffectTmpValue  = valueHolderForEnableSmoothEffect!
            valueSerializer.writeBoolean(valueHolderForEnableSmoothEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            if (valueHolderForStrokeWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx0  = valueHolderForStrokeWidthTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeWidthTmpValueForIdx0)
            } else if (valueHolderForStrokeWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx1  = valueHolderForStrokeWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForStrokeWidthTmpValueForIdx1)
            } else if (valueHolderForStrokeWidthTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeWidthTmpValueForIdx2  = valueHolderForStrokeWidthTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow  = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue  = valueHolderForShadow!
            valueSerializer.writeBoolean(valueHolderForShadowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStatus  = value.status
        if (valueHolderForStatus !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStatusTmpValue  = (valueHolderForStatus as ProgressStatus)
            valueSerializer.writeInt32(valueHolderForStatusTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RingStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableScanEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableScanEffectTmpBuf : boolean | undefined = undefined
        if ((enableScanEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableScanEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableScanEffectTmpResult : boolean | undefined = enableScanEffectTmpBuf
        const enableSmoothEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableSmoothEffectTmpBuf : boolean | undefined = undefined
        if ((enableSmoothEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableSmoothEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableSmoothEffectTmpResult : boolean | undefined = enableSmoothEffectTmpBuf
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeWidthTmpBuf : Length | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let strokeWidthTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (strokeWidthTmpBufOptUnionSelector == (0).toByte()) {
                strokeWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (strokeWidthTmpBufOptUnionSelector == (1).toByte()) {
                strokeWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (strokeWidthTmpBufOptUnionSelector == (2).toByte()) {
                strokeWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for strokeWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            strokeWidthTmpBuf = (strokeWidthTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const strokeWidthTmpResult : Length | undefined = strokeWidthTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let shadowTmpBuf : boolean | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            shadowTmpBuf = valueDeserializer.readBoolean()
        }
        const shadowTmpResult : boolean | undefined = shadowTmpBuf
        const statusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let statusTmpBuf : ProgressStatus | undefined = undefined
        if ((statusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            statusTmpBuf = ProgressStatus.fromValue(valueDeserializer.readInt32())
        }
        const statusTmpResult : ProgressStatus | undefined = statusTmpBuf
        let value : RingStyleOptions = ({enableScanEffect: enableScanEffectTmpResult, enableSmoothEffect: enableSmoothEffectTmpResult, strokeWidth: strokeWidthTmpResult, shadow: shadowTmpResult, status: statusTmpResult} as RingStyleOptions)
        return value
    }
}
export class CapsuleStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: CapsuleStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnableScanEffect  = value.enableScanEffect
        if (valueHolderForEnableScanEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableScanEffectTmpValue  = valueHolderForEnableScanEffect!
            valueSerializer.writeBoolean(valueHolderForEnableScanEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableSmoothEffect  = value.enableSmoothEffect
        if (valueHolderForEnableSmoothEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableSmoothEffectTmpValue  = valueHolderForEnableSmoothEffect!
            valueSerializer.writeBoolean(valueHolderForEnableSmoothEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBorderColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForBorderColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx1)
            } else if (valueHolderForBorderColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderColorTmpValueForIdx2  = valueHolderForBorderColorTmpValue as string
                valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx2)
            } else if (valueHolderForBorderColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBorderColorTmpValueForIdx3  = valueHolderForBorderColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as string
                valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0)
            } else if (valueHolderForBorderWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBorderWidthTmpValueForIdx1)
            } else if (valueHolderForBorderWidthTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderWidthTmpValueForIdx2  = valueHolderForBorderWidthTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForContent  = value.content
        if (valueHolderForContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForContentTmpValue  = valueHolderForContent!
            valueSerializer.writeString(valueHolderForContentTmpValue)
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
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            if (valueHolderForFontColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontColorTmpValueForIdx0  = valueHolderForFontColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForFontColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForFontColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontColorTmpValueForIdx1  = valueHolderForFontColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontColorTmpValueForIdx1)
            } else if (valueHolderForFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontColorTmpValueForIdx2  = valueHolderForFontColorTmpValue as string
                valueSerializer.writeString(valueHolderForFontColorTmpValueForIdx2)
            } else if (valueHolderForFontColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForFontColorTmpValueForIdx3  = valueHolderForFontColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowDefaultPercentage  = value.showDefaultPercentage
        if (valueHolderForShowDefaultPercentage !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowDefaultPercentageTmpValue  = valueHolderForShowDefaultPercentage!
            valueSerializer.writeBoolean(valueHolderForShowDefaultPercentageTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderRadius  = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue  = valueHolderForBorderRadius!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CapsuleStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableScanEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableScanEffectTmpBuf : boolean | undefined = undefined
        if ((enableScanEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableScanEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableScanEffectTmpResult : boolean | undefined = enableScanEffectTmpBuf
        const enableSmoothEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableSmoothEffectTmpBuf : boolean | undefined = undefined
        if ((enableSmoothEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableSmoothEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableSmoothEffectTmpResult : boolean | undefined = enableSmoothEffectTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderColorTmpBuf : ResourceColor | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (borderColorTmpBufOptUnionSelector == (0).toByte()) {
                borderColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (borderColorTmpBufOptUnionSelector == (1).toByte()) {
                borderColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (borderColorTmpBufOptUnionSelector == (2).toByte()) {
                borderColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (borderColorTmpBufOptUnionSelector == (3).toByte()) {
                borderColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderColorTmpBufOpt has to be chosen through deserialisation.')
            }
            borderColorTmpBuf = (borderColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const borderColorTmpResult : ResourceColor | undefined = borderColorTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderWidthTmpBuf : Length | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (borderWidthTmpBufOptUnionSelector == (0).toByte()) {
                borderWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (borderWidthTmpBufOptUnionSelector == (1).toByte()) {
                borderWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (borderWidthTmpBufOptUnionSelector == (2).toByte()) {
                borderWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            borderWidthTmpBuf = (borderWidthTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const borderWidthTmpResult : Length | undefined = borderWidthTmpBuf
        const contentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let contentTmpBuf : string | undefined = undefined
        if ((contentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            contentTmpBuf = (valueDeserializer.readString() as string)
        }
        const contentTmpResult : string | undefined = contentTmpBuf
        const fontTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontTmpBuf : arkui_component_units_Font | undefined = undefined
        if ((fontTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontTmpBuf = arkui_component_units_Font_serializer.read(valueDeserializer)
        }
        const fontTmpResult : arkui_component_units_Font | undefined = fontTmpBuf
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontColorTmpBuf : ResourceColor | undefined = undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (fontColorTmpBufOptUnionSelector == (0).toByte()) {
                fontColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (fontColorTmpBufOptUnionSelector == (1).toByte()) {
                fontColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontColorTmpBufOptUnionSelector == (2).toByte()) {
                fontColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontColorTmpBufOptUnionSelector == (3).toByte()) {
                fontColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontColorTmpBufOpt has to be chosen through deserialisation.')
            }
            fontColorTmpBuf = (fontColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const fontColorTmpResult : ResourceColor | undefined = fontColorTmpBuf
        const showDefaultPercentageTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let showDefaultPercentageTmpBuf : boolean | undefined = undefined
        if ((showDefaultPercentageTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showDefaultPercentageTmpBuf = valueDeserializer.readBoolean()
        }
        const showDefaultPercentageTmpResult : boolean | undefined = showDefaultPercentageTmpBuf
        const borderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderRadiusTmpBuf : arkui_Graphics_LengthMetrics | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            borderRadiusTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const borderRadiusTmpResult : arkui_Graphics_LengthMetrics | undefined = borderRadiusTmpBuf
        let value : CapsuleStyleOptions = ({enableScanEffect: enableScanEffectTmpResult, enableSmoothEffect: enableSmoothEffectTmpResult, borderColor: borderColorTmpResult, borderWidth: borderWidthTmpResult, content: contentTmpResult, font: fontTmpResult, fontColor: fontColorTmpResult, showDefaultPercentage: showDefaultPercentageTmpResult, borderRadius: borderRadiusTmpResult} as CapsuleStyleOptions)
        return value
    }
}
