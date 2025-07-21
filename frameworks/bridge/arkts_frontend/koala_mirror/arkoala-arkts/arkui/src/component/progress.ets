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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { LinearGradient_serializer, LinearGradient } from "./dataPanel"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor, Length, PX, VP, LPX, Font, Font_serializer } from "./units"
import { Color } from "./enums"
import { ContentModifier, AttributeModifier, hookProgressContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkProgressPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkProgressPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Progress_construct(peerId, flags)
        const _peer  = new ArkProgressPeer(_peerPtr, peerId, "Progress", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setProgressOptionsAttribute(options: ProgressOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ProgressOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ProgressInterface_setProgressOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setValueAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_setValue(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((3).toChar())
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as LinearGradient
                LinearGradient_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStyleAttribute(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isLinearStyleOptions(value_value, true, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as LinearStyleOptions
                LinearStyleOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isRingStyleOptions(value_value, true, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as RingStyleOptions
                RingStyleOptions_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isCapsuleStyleOptions(value_value, false, false, false, false, false, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as CapsuleStyleOptions
                CapsuleStyleOptions_serializer.write(thisSerializer, value_value_2)
            }
            else if (TypeChecker.isProgressStyleOptions(value_value, true, false, false)) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as ProgressStyleOptions
                ProgressStyleOptions_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_setStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrivacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<ProgressConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ProgressOptions {
    value: number;
    total?: number;
    type?: ProgressType;
}
export enum ProgressType {
    LINEAR = 0,
    Linear = 0,
    RING = 1,
    Ring = 1,
    ECLIPSE = 2,
    Eclipse = 2,
    SCALE_RING = 3,
    ScaleRing = 3,
    CAPSULE = 4,
    Capsule = 4
}
export enum ProgressStatus {
    LOADING = 0,
    PROGRESSING = 1
}
export interface ProgressStyleOptions extends CommonProgressStyleOptions {
    strokeWidth?: Length;
    scaleCount?: number;
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
    scaleCount?: number;
}
export interface RingStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    strokeWidth?: Length;
    shadow?: boolean;
    status?: ProgressStatus;
}
export interface LinearStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    strokeWidth?: Length;
    strokeRadius?: PX | VP | LPX | Resource;
}
export interface CapsuleStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    borderColor?: ResourceColor;
    borderWidth?: Length;
    font?: Font;
    fontColor?: ResourceColor;
    showDefaultPercentage?: boolean;
    borderRadius?: LengthMetrics;
}
export enum ProgressStyle {
    LINEAR = 0,
    Linear = 0,
    RING = 1,
    Ring = 1,
    ECLIPSE = 2,
    Eclipse = 2,
    SCALE_RING = 3,
    ScaleRing = 3,
    CAPSULE = 4,
    Capsule = 4
}
export interface ProgressStyleMap {
}
export interface ProgressAttribute extends CommonMethod {
    value(value: number | undefined): this {
        throw new Error("Unimplemented method value")
    }
    color(value: ResourceColor | LinearGradient | undefined): this {
        throw new Error("Unimplemented method color")
    }
    style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        throw new Error("Unimplemented method style")
    }
    privacySensitive(value: boolean | undefined): this {
        throw new Error("Unimplemented method privacySensitive")
    }
    contentModifier(value: ContentModifier<ProgressConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    attributeModifier(value: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkProgressStyle extends ArkCommonMethodStyle implements ProgressAttribute {
    value_value?: number | undefined
    color_value?: ResourceColor | LinearGradient | undefined
    style_value?: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined
    privacySensitive_value?: boolean | undefined
    contentModifier_value?: ContentModifier<ProgressConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined
    public value(value: number | undefined): this {
        return this
    }
    public color(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    public style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<ProgressConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ProgressAttribute): void {
        super.apply(target)
        if (this.value_value !== undefined)
            target.value(this.value_value!)
        if (this.color_value !== undefined)
            target.color(this.color_value!)
        if (this.style_value !== undefined)
            target.style(this.style_value!)
        if (this.privacySensitive_value !== undefined)
            target.privacySensitive(this.privacySensitive_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
    }
}
export interface ProgressConfiguration extends CommonConfiguration<ProgressConfiguration> {
    value: number;
    total: number;
}

export class ArkProgressComponent extends ArkCommonMethodComponent implements ProgressAttribute {
    getPeer(): ArkProgressPeer {
        return (this.peer as ArkProgressPeer)
    }
    public setProgressOptions(options: ProgressOptions): this {
        if (this.checkPriority("setProgressOptions")) {
            const options_casted = options as (ProgressOptions)
            this.getPeer()?.setProgressOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public value(value: number | undefined): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setValueAttribute(value_casted)
            return this
        }
        return this
    }
    public color(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.setColorAttribute(value_casted)
            return this
        }
        return this
    }
    public style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined)
            this.getPeer()?.setStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPrivacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<ProgressConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<ProgressConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withProgressStyle(receiver: ProgressAttribute, modifier: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkProgressStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Progress")
// export function Progress(
//     options: ProgressOptions,
//     @memo
//     content_?: () => void,
// ): ProgressAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Progress(
    @memo
    style: ((attributes: ProgressAttribute) => void) | undefined,
    options: ProgressOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkProgressComponent>((): ArkProgressComponent => {
        return new ArkProgressComponent()
    })
    NodeAttach<ArkProgressPeer>((): ArkProgressPeer => ArkProgressPeer.create(receiver), (_: ArkProgressPeer): void => {
        receiver.setProgressOptions(options)
        style?.(receiver)
        withProgressStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkProgressSet extends ArkCommonMethodSet implements ProgressAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _value_flag?: boolean
    _value0_value?: number | undefined
    _color_flag?: boolean
    _color0_value?: ResourceColor | LinearGradient | undefined
    _style_flag?: boolean
    _style0_value?: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined
    _privacySensitive_flag?: boolean
    _privacySensitive0_value?: boolean | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<ProgressConfiguration> | undefined
    applyModifierPatch(component: ProgressAttribute): void {
        if (this._value_flag)
            component.value((this._value0_value as number | undefined))
        if (this._color_flag)
            component.color((this._color0_value as ResourceColor | LinearGradient | undefined))
        if (this._style_flag)
            component.style((this._style0_value as LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined))
        if (this._privacySensitive_flag)
            component.privacySensitive((this._privacySensitive0_value as boolean | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<ProgressConfiguration> | undefined))
    }
    public value(value: number | undefined): this {
        this._value_flag = true
        this._value0_value = value
        return this
    }
    public color(value: ResourceColor | LinearGradient | undefined): this {
        this._color_flag = true
        this._color0_value = value
        return this
    }
    public style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        this._style_flag = true
        this._style0_value = value
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        this._privacySensitive_flag = true
        this._privacySensitive0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<ProgressConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ProgressConfiguration_serializer {
    public static write(buffer: SerializerBase, value: ProgressConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_value  = value.value
        valueSerializer.writeNumber(value_value)
        const value_total  = value.total
        valueSerializer.writeNumber(value_total)
    }
    public static read(buffer: DeserializerBase): ProgressConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<ProgressConfiguration> = (valueDeserializer.readObject() as ContentModifier<ProgressConfiguration>)
        const value_result : number = (valueDeserializer.readNumber() as number)
        const total_result : number = (valueDeserializer.readNumber() as number)
        let value : ProgressConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, value: value_result, total: total_result} as ProgressConfiguration)
        return value
    }
}
export class ProgressOptions_serializer {
    public static write(buffer: SerializerBase, value: ProgressOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        valueSerializer.writeNumber(value_value)
        const value_total  = value.total
        let value_total_type : int32 = RuntimeType.UNDEFINED
        value_total_type = runtimeType(value_total)
        valueSerializer.writeInt8((value_total_type).toChar())
        if ((value_total_type) != (RuntimeType.UNDEFINED)) {
            const value_total_value  = value_total!
            valueSerializer.writeNumber(value_total_value)
        }
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8((value_type_type).toChar())
        if ((value_type_type) != (RuntimeType.UNDEFINED)) {
            const value_type_value  = (value_type as ProgressType)
            valueSerializer.writeInt32(TypeChecker.ProgressType_ToNumeric(value_type_value))
        }
    }
    public static read(buffer: DeserializerBase): ProgressOptions {
        let valueDeserializer : DeserializerBase = buffer
        const value_result : number = (valueDeserializer.readNumber() as number)
        const total_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let total_buf : number | undefined
        if ((total_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            total_buf = (valueDeserializer.readNumber() as number)
        }
        const total_result : number | undefined = total_buf
        const type_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let type_buf : ProgressType | undefined
        if ((type_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            type_buf = TypeChecker.ProgressType_FromNumeric(valueDeserializer.readInt32())
        }
        const type_result : ProgressType | undefined = type_buf
        let value : ProgressOptions = ({value: value_result, total: total_result, type: type_result} as ProgressOptions)
        return value
    }
}
export class LinearStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: LinearStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_enableScanEffect  = value.enableScanEffect
        let value_enableScanEffect_type : int32 = RuntimeType.UNDEFINED
        value_enableScanEffect_type = runtimeType(value_enableScanEffect)
        valueSerializer.writeInt8((value_enableScanEffect_type).toChar())
        if ((value_enableScanEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_enableScanEffect_value  = value_enableScanEffect!
            valueSerializer.writeBoolean(value_enableScanEffect_value)
        }
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
        const value_strokeRadius  = value.strokeRadius
        let value_strokeRadius_type : int32 = RuntimeType.UNDEFINED
        value_strokeRadius_type = runtimeType(value_strokeRadius)
        valueSerializer.writeInt8((value_strokeRadius_type).toChar())
        if ((value_strokeRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeRadius_value  = value_strokeRadius!
            let value_strokeRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_strokeRadius_value_type = runtimeType(value_strokeRadius_value)
            if (RuntimeType.STRING == value_strokeRadius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_strokeRadius_value_0  = value_strokeRadius_value as string
                valueSerializer.writeString(value_strokeRadius_value_0)
            }
            else if (RuntimeType.NUMBER == value_strokeRadius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_strokeRadius_value_1  = value_strokeRadius_value as number
                valueSerializer.writeNumber(value_strokeRadius_value_1)
            }
            else if (RuntimeType.OBJECT == value_strokeRadius_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_strokeRadius_value_2  = value_strokeRadius_value as Resource
                Resource_serializer.write(valueSerializer, value_strokeRadius_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): LinearStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableScanEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableScanEffect_buf : boolean | undefined
        if ((enableScanEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableScanEffect_buf = valueDeserializer.readBoolean()
        }
        const enableScanEffect_result : boolean | undefined = enableScanEffect_buf
        const strokeWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidth_buf : Length | undefined
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
        const strokeWidth_result : Length | undefined = strokeWidth_buf
        const strokeRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeRadius_buf : string | number | Resource | undefined
        if ((strokeRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const strokeRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let strokeRadius_buf_ : string | number | Resource | undefined
            if (strokeRadius_buf__selector == (0).toChar()) {
                strokeRadius_buf_ = (valueDeserializer.readString() as string)
            }
            else if (strokeRadius_buf__selector == (1).toChar()) {
                strokeRadius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (strokeRadius_buf__selector == (2).toChar()) {
                strokeRadius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for strokeRadius_buf_ has to be chosen through deserialisation.")
            }
            strokeRadius_buf = (strokeRadius_buf_ as string | number | Resource)
        }
        const strokeRadius_result : PX | VP | LPX | Resource | undefined = strokeRadius_buf
        let value : LinearStyleOptions = ({enableScanEffect: enableScanEffect_result, strokeWidth: strokeWidth_result, strokeRadius: strokeRadius_result} as LinearStyleOptions)
        return value
    }
}
export class ProgressStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: ProgressStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_enableSmoothEffect  = value.enableSmoothEffect
        let value_enableSmoothEffect_type : int32 = RuntimeType.UNDEFINED
        value_enableSmoothEffect_type = runtimeType(value_enableSmoothEffect)
        valueSerializer.writeInt8((value_enableSmoothEffect_type).toChar())
        if ((value_enableSmoothEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_enableSmoothEffect_value  = value_enableSmoothEffect!
            valueSerializer.writeBoolean(value_enableSmoothEffect_value)
        }
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
        const value_scaleCount  = value.scaleCount
        let value_scaleCount_type : int32 = RuntimeType.UNDEFINED
        value_scaleCount_type = runtimeType(value_scaleCount)
        valueSerializer.writeInt8((value_scaleCount_type).toChar())
        if ((value_scaleCount_type) != (RuntimeType.UNDEFINED)) {
            const value_scaleCount_value  = value_scaleCount!
            valueSerializer.writeNumber(value_scaleCount_value)
        }
        const value_scaleWidth  = value.scaleWidth
        let value_scaleWidth_type : int32 = RuntimeType.UNDEFINED
        value_scaleWidth_type = runtimeType(value_scaleWidth)
        valueSerializer.writeInt8((value_scaleWidth_type).toChar())
        if ((value_scaleWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_scaleWidth_value  = value_scaleWidth!
            let value_scaleWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_scaleWidth_value_type = runtimeType(value_scaleWidth_value)
            if (RuntimeType.STRING == value_scaleWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_scaleWidth_value_0  = value_scaleWidth_value as string
                valueSerializer.writeString(value_scaleWidth_value_0)
            }
            else if (RuntimeType.NUMBER == value_scaleWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_scaleWidth_value_1  = value_scaleWidth_value as number
                valueSerializer.writeNumber(value_scaleWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value_scaleWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_scaleWidth_value_2  = value_scaleWidth_value as Resource
                Resource_serializer.write(valueSerializer, value_scaleWidth_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): ProgressStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableSmoothEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableSmoothEffect_buf : boolean | undefined
        if ((enableSmoothEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableSmoothEffect_buf = valueDeserializer.readBoolean()
        }
        const enableSmoothEffect_result : boolean | undefined = enableSmoothEffect_buf
        const strokeWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidth_buf : Length | undefined
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
        const strokeWidth_result : Length | undefined = strokeWidth_buf
        const scaleCount_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scaleCount_buf : number | undefined
        if ((scaleCount_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scaleCount_buf = (valueDeserializer.readNumber() as number)
        }
        const scaleCount_result : number | undefined = scaleCount_buf
        const scaleWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scaleWidth_buf : Length | undefined
        if ((scaleWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const scaleWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let scaleWidth_buf_ : string | number | Resource | undefined
            if (scaleWidth_buf__selector == (0).toChar()) {
                scaleWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else if (scaleWidth_buf__selector == (1).toChar()) {
                scaleWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (scaleWidth_buf__selector == (2).toChar()) {
                scaleWidth_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for scaleWidth_buf_ has to be chosen through deserialisation.")
            }
            scaleWidth_buf = (scaleWidth_buf_ as string | number | Resource)
        }
        const scaleWidth_result : Length | undefined = scaleWidth_buf
        let value : ProgressStyleOptions = ({enableSmoothEffect: enableSmoothEffect_result, strokeWidth: strokeWidth_result, scaleCount: scaleCount_result, scaleWidth: scaleWidth_result} as ProgressStyleOptions)
        return value
    }
}
export class RingStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RingStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_enableScanEffect  = value.enableScanEffect
        let value_enableScanEffect_type : int32 = RuntimeType.UNDEFINED
        value_enableScanEffect_type = runtimeType(value_enableScanEffect)
        valueSerializer.writeInt8((value_enableScanEffect_type).toChar())
        if ((value_enableScanEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_enableScanEffect_value  = value_enableScanEffect!
            valueSerializer.writeBoolean(value_enableScanEffect_value)
        }
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
        const value_shadow  = value.shadow
        let value_shadow_type : int32 = RuntimeType.UNDEFINED
        value_shadow_type = runtimeType(value_shadow)
        valueSerializer.writeInt8((value_shadow_type).toChar())
        if ((value_shadow_type) != (RuntimeType.UNDEFINED)) {
            const value_shadow_value  = value_shadow!
            valueSerializer.writeBoolean(value_shadow_value)
        }
        const value_status  = value.status
        let value_status_type : int32 = RuntimeType.UNDEFINED
        value_status_type = runtimeType(value_status)
        valueSerializer.writeInt8((value_status_type).toChar())
        if ((value_status_type) != (RuntimeType.UNDEFINED)) {
            const value_status_value  = (value_status as ProgressStatus)
            valueSerializer.writeInt32(TypeChecker.ProgressStatus_ToNumeric(value_status_value))
        }
    }
    public static read(buffer: DeserializerBase): RingStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableScanEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableScanEffect_buf : boolean | undefined
        if ((enableScanEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableScanEffect_buf = valueDeserializer.readBoolean()
        }
        const enableScanEffect_result : boolean | undefined = enableScanEffect_buf
        const strokeWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidth_buf : Length | undefined
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
        const strokeWidth_result : Length | undefined = strokeWidth_buf
        const shadow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadow_buf : boolean | undefined
        if ((shadow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            shadow_buf = valueDeserializer.readBoolean()
        }
        const shadow_result : boolean | undefined = shadow_buf
        const status_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let status_buf : ProgressStatus | undefined
        if ((status_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            status_buf = TypeChecker.ProgressStatus_FromNumeric(valueDeserializer.readInt32())
        }
        const status_result : ProgressStatus | undefined = status_buf
        let value : RingStyleOptions = ({enableScanEffect: enableScanEffect_result, strokeWidth: strokeWidth_result, shadow: shadow_result, status: status_result} as RingStyleOptions)
        return value
    }
}
export class CapsuleStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: CapsuleStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_enableScanEffect  = value.enableScanEffect
        let value_enableScanEffect_type : int32 = RuntimeType.UNDEFINED
        value_enableScanEffect_type = runtimeType(value_enableScanEffect)
        valueSerializer.writeInt8((value_enableScanEffect_type).toChar())
        if ((value_enableScanEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_enableScanEffect_value  = value_enableScanEffect!
            valueSerializer.writeBoolean(value_enableScanEffect_value)
        }
        const value_borderColor  = value.borderColor
        let value_borderColor_type : int32 = RuntimeType.UNDEFINED
        value_borderColor_type = runtimeType(value_borderColor)
        valueSerializer.writeInt8((value_borderColor_type).toChar())
        if ((value_borderColor_type) != (RuntimeType.UNDEFINED)) {
            const value_borderColor_value  = value_borderColor!
            let value_borderColor_value_type : int32 = RuntimeType.UNDEFINED
            value_borderColor_value_type = runtimeType(value_borderColor_value)
            if (TypeChecker.isColor(value_borderColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_borderColor_value_0  = value_borderColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_borderColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_borderColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_borderColor_value_1  = value_borderColor_value as number
                valueSerializer.writeNumber(value_borderColor_value_1)
            }
            else if (RuntimeType.STRING == value_borderColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_borderColor_value_2  = value_borderColor_value as string
                valueSerializer.writeString(value_borderColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_borderColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_borderColor_value_3  = value_borderColor_value as Resource
                Resource_serializer.write(valueSerializer, value_borderColor_value_3)
            }
        }
        const value_borderWidth  = value.borderWidth
        let value_borderWidth_type : int32 = RuntimeType.UNDEFINED
        value_borderWidth_type = runtimeType(value_borderWidth)
        valueSerializer.writeInt8((value_borderWidth_type).toChar())
        if ((value_borderWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_borderWidth_value  = value_borderWidth!
            let value_borderWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_borderWidth_value_type = runtimeType(value_borderWidth_value)
            if (RuntimeType.STRING == value_borderWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_borderWidth_value_0  = value_borderWidth_value as string
                valueSerializer.writeString(value_borderWidth_value_0)
            }
            else if (RuntimeType.NUMBER == value_borderWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_borderWidth_value_1  = value_borderWidth_value as number
                valueSerializer.writeNumber(value_borderWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value_borderWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_borderWidth_value_2  = value_borderWidth_value as Resource
                Resource_serializer.write(valueSerializer, value_borderWidth_value_2)
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
        const value_fontColor  = value.fontColor
        let value_fontColor_type : int32 = RuntimeType.UNDEFINED
        value_fontColor_type = runtimeType(value_fontColor)
        valueSerializer.writeInt8((value_fontColor_type).toChar())
        if ((value_fontColor_type) != (RuntimeType.UNDEFINED)) {
            const value_fontColor_value  = value_fontColor!
            let value_fontColor_value_type : int32 = RuntimeType.UNDEFINED
            value_fontColor_value_type = runtimeType(value_fontColor_value)
            if (TypeChecker.isColor(value_fontColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontColor_value_0  = value_fontColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_fontColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontColor_value_1  = value_fontColor_value as number
                valueSerializer.writeNumber(value_fontColor_value_1)
            }
            else if (RuntimeType.STRING == value_fontColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_fontColor_value_2  = value_fontColor_value as string
                valueSerializer.writeString(value_fontColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_fontColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_fontColor_value_3  = value_fontColor_value as Resource
                Resource_serializer.write(valueSerializer, value_fontColor_value_3)
            }
        }
        const value_showDefaultPercentage  = value.showDefaultPercentage
        let value_showDefaultPercentage_type : int32 = RuntimeType.UNDEFINED
        value_showDefaultPercentage_type = runtimeType(value_showDefaultPercentage)
        valueSerializer.writeInt8((value_showDefaultPercentage_type).toChar())
        if ((value_showDefaultPercentage_type) != (RuntimeType.UNDEFINED)) {
            const value_showDefaultPercentage_value  = value_showDefaultPercentage!
            valueSerializer.writeBoolean(value_showDefaultPercentage_value)
        }
        const value_borderRadius  = value.borderRadius
        let value_borderRadius_type : int32 = RuntimeType.UNDEFINED
        value_borderRadius_type = runtimeType(value_borderRadius)
        valueSerializer.writeInt8((value_borderRadius_type).toChar())
        if ((value_borderRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_borderRadius_value  = value_borderRadius!
            LengthMetrics_serializer.write(valueSerializer, value_borderRadius_value)
        }
    }
    public static read(buffer: DeserializerBase): CapsuleStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableScanEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableScanEffect_buf : boolean | undefined
        if ((enableScanEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableScanEffect_buf = valueDeserializer.readBoolean()
        }
        const enableScanEffect_result : boolean | undefined = enableScanEffect_buf
        const borderColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderColor_buf : ResourceColor | undefined
        if ((borderColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const borderColor_buf__selector : int32 = valueDeserializer.readInt8()
            let borderColor_buf_ : Color | number | string | Resource | undefined
            if (borderColor_buf__selector == (0).toChar()) {
                borderColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (borderColor_buf__selector == (1).toChar()) {
                borderColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (borderColor_buf__selector == (2).toChar()) {
                borderColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (borderColor_buf__selector == (3).toChar()) {
                borderColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderColor_buf_ has to be chosen through deserialisation.")
            }
            borderColor_buf = (borderColor_buf_ as Color | number | string | Resource)
        }
        const borderColor_result : ResourceColor | undefined = borderColor_buf
        const borderWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderWidth_buf : Length | undefined
        if ((borderWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const borderWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let borderWidth_buf_ : string | number | Resource | undefined
            if (borderWidth_buf__selector == (0).toChar()) {
                borderWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else if (borderWidth_buf__selector == (1).toChar()) {
                borderWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (borderWidth_buf__selector == (2).toChar()) {
                borderWidth_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderWidth_buf_ has to be chosen through deserialisation.")
            }
            borderWidth_buf = (borderWidth_buf_ as string | number | Resource)
        }
        const borderWidth_result : Length | undefined = borderWidth_buf
        const font_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let font_buf : Font | undefined
        if ((font_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            font_buf = Font_serializer.read(valueDeserializer)
        }
        const font_result : Font | undefined = font_buf
        const fontColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontColor_buf : ResourceColor | undefined
        if ((fontColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontColor_buf__selector : int32 = valueDeserializer.readInt8()
            let fontColor_buf_ : Color | number | string | Resource | undefined
            if (fontColor_buf__selector == (0).toChar()) {
                fontColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontColor_buf__selector == (1).toChar()) {
                fontColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontColor_buf__selector == (2).toChar()) {
                fontColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontColor_buf__selector == (3).toChar()) {
                fontColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontColor_buf_ has to be chosen through deserialisation.")
            }
            fontColor_buf = (fontColor_buf_ as Color | number | string | Resource)
        }
        const fontColor_result : ResourceColor | undefined = fontColor_buf
        const showDefaultPercentage_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showDefaultPercentage_buf : boolean | undefined
        if ((showDefaultPercentage_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            showDefaultPercentage_buf = valueDeserializer.readBoolean()
        }
        const showDefaultPercentage_result : boolean | undefined = showDefaultPercentage_buf
        const borderRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderRadius_buf : LengthMetrics | undefined
        if ((borderRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            borderRadius_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const borderRadius_result : LengthMetrics | undefined = borderRadius_buf
        let value : CapsuleStyleOptions = ({enableScanEffect: enableScanEffect_result, borderColor: borderColor_result, borderWidth: borderWidth_result, font: font_result, fontColor: fontColor_result, showDefaultPercentage: showDefaultPercentage_result, borderRadius: borderRadius_result} as CapsuleStyleOptions)
        return value
    }
}
