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
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ResourceColor, ResourceStr, Length, Position, Position_serializer } from "./units"
import { Color, FontWeight } from "./enums"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkBadgePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkBadgePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Badge_construct(peerId, flags)
        const _peer  = new ArkBadgePeer(_peerPtr, peerId, "Badge", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setBadgeOptions0Attribute(value: BadgeParamWithNumber): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        BadgeParamWithNumber_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._BadgeInterface_setBadgeOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBadgeOptions1Attribute(value: BadgeParamWithString): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        BadgeParamWithString_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._BadgeInterface_setBadgeOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum BadgePosition {
    RIGHT_TOP = 0,
    RightTop = 0,
    RIGHT = 1,
    Right = 1,
    LEFT = 2,
    Left = 2
}
export interface BadgeStyle {
    color?: ResourceColor;
    fontSize?: number | ResourceStr;
    badgeSize?: number | ResourceStr;
    badgeColor?: ResourceColor;
    borderColor?: ResourceColor;
    borderWidth?: Length;
    fontWeight?: number | FontWeight | ResourceStr;
}
export interface BadgeParam {
    position?: BadgePosition | Position;
    style: BadgeStyle;
}
export interface BadgeParamWithNumber extends BadgeParam {
    count: number;
    maxCount?: number;
}
export interface BadgeParamWithString extends BadgeParam {
    value: ResourceStr;
}
export interface BadgeAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkBadgeStyle extends ArkCommonMethodStyle implements BadgeAttribute {
    attributeModifier_value?: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: BadgeAttribute): void {
        super.apply(target)
    }
}

export class ArkBadgeComponent extends ArkCommonMethodComponent implements BadgeAttribute {
    getPeer(): ArkBadgePeer {
        return (this.peer as ArkBadgePeer)
    }
    public setBadgeOptions(value: BadgeParamWithNumber): this {
        if (this.checkPriority("setBadgeOptions")) {
            const value_casted = value as (BadgeParamWithNumber)
            this.getPeer()?.setBadgeOptions0Attribute(value_casted)
            return this
        }
        return this
    }
    public setBadgeOptions(value: BadgeParamWithString): this {
        if (this.checkPriority("setBadgeOptions")) {
            const value_casted = value as (BadgeParamWithString)
            this.getPeer()?.setBadgeOptions1Attribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withBadgeStyle(receiver: BadgeAttribute, modifier: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkBadgeStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Badge")
// export function Badge(
//     value: BadgeParamWithNumber,
//     @memo
//     content_?: () => void,
// ): BadgeAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Badge(
    @memo
    style: ((attributes: BadgeAttribute) => void) | undefined,
    value: BadgeParamWithNumber,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkBadgeComponent>((): ArkBadgeComponent => {
        return new ArkBadgeComponent()
    })
    NodeAttach<ArkBadgePeer>((): ArkBadgePeer => ArkBadgePeer.create(receiver), (_: ArkBadgePeer): void => {
        receiver.setBadgeOptions(value)
        style?.(receiver)
        withBadgeStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

// @memo
// @BuilderLambda("Badge")
// export function Badge(
//     value: BadgeParamWithString,
//     @memo
//     content_?: () => void,
// ): BadgeAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Badge(
    @memo
    style: ((attributes: BadgeAttribute) => void) | undefined,
    value: BadgeParamWithString,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkBadgeComponent>((): ArkBadgeComponent => {
        return new ArkBadgeComponent()
    })
    NodeAttach<ArkBadgePeer>((): ArkBadgePeer => ArkBadgePeer.create(receiver), (_: ArkBadgePeer): void => {
        receiver.setBadgeOptions(value)
        style?.(receiver)
        withBadgeStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkBadgeSet extends ArkCommonMethodSet implements BadgeAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: BadgeAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class BadgeStyle_serializer {
    public static write(buffer: SerializerBase, value: BadgeStyle): void {
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
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8((value_fontSize_type).toChar())
        if ((value_fontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_fontSize_value  = value_fontSize!
            let value_fontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_fontSize_value_type = runtimeType(value_fontSize_value)
            if (RuntimeType.NUMBER == value_fontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontSize_value_0  = value_fontSize_value as number
                valueSerializer.writeNumber(value_fontSize_value_0)
            }
            else if ((RuntimeType.STRING == value_fontSize_value_type) || (RuntimeType.OBJECT == value_fontSize_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontSize_value_1  = value_fontSize_value as ResourceStr
                let value_fontSize_value_1_type : int32 = RuntimeType.UNDEFINED
                value_fontSize_value_1_type = runtimeType(value_fontSize_value_1)
                if (RuntimeType.STRING == value_fontSize_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_fontSize_value_1_0  = value_fontSize_value_1 as string
                    valueSerializer.writeString(value_fontSize_value_1_0)
                }
                else if (RuntimeType.OBJECT == value_fontSize_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_fontSize_value_1_1  = value_fontSize_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_fontSize_value_1_1)
                }
            }
        }
        const value_badgeSize  = value.badgeSize
        let value_badgeSize_type : int32 = RuntimeType.UNDEFINED
        value_badgeSize_type = runtimeType(value_badgeSize)
        valueSerializer.writeInt8((value_badgeSize_type).toChar())
        if ((value_badgeSize_type) != (RuntimeType.UNDEFINED)) {
            const value_badgeSize_value  = value_badgeSize!
            let value_badgeSize_value_type : int32 = RuntimeType.UNDEFINED
            value_badgeSize_value_type = runtimeType(value_badgeSize_value)
            if (RuntimeType.NUMBER == value_badgeSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_badgeSize_value_0  = value_badgeSize_value as number
                valueSerializer.writeNumber(value_badgeSize_value_0)
            }
            else if ((RuntimeType.STRING == value_badgeSize_value_type) || (RuntimeType.OBJECT == value_badgeSize_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_badgeSize_value_1  = value_badgeSize_value as ResourceStr
                let value_badgeSize_value_1_type : int32 = RuntimeType.UNDEFINED
                value_badgeSize_value_1_type = runtimeType(value_badgeSize_value_1)
                if (RuntimeType.STRING == value_badgeSize_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_badgeSize_value_1_0  = value_badgeSize_value_1 as string
                    valueSerializer.writeString(value_badgeSize_value_1_0)
                }
                else if (RuntimeType.OBJECT == value_badgeSize_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_badgeSize_value_1_1  = value_badgeSize_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_badgeSize_value_1_1)
                }
            }
        }
        const value_badgeColor  = value.badgeColor
        let value_badgeColor_type : int32 = RuntimeType.UNDEFINED
        value_badgeColor_type = runtimeType(value_badgeColor)
        valueSerializer.writeInt8((value_badgeColor_type).toChar())
        if ((value_badgeColor_type) != (RuntimeType.UNDEFINED)) {
            const value_badgeColor_value  = value_badgeColor!
            let value_badgeColor_value_type : int32 = RuntimeType.UNDEFINED
            value_badgeColor_value_type = runtimeType(value_badgeColor_value)
            if (TypeChecker.isColor(value_badgeColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_badgeColor_value_0  = value_badgeColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_badgeColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_badgeColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_badgeColor_value_1  = value_badgeColor_value as number
                valueSerializer.writeNumber(value_badgeColor_value_1)
            }
            else if (RuntimeType.STRING == value_badgeColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_badgeColor_value_2  = value_badgeColor_value as string
                valueSerializer.writeString(value_badgeColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_badgeColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_badgeColor_value_3  = value_badgeColor_value as Resource
                Resource_serializer.write(valueSerializer, value_badgeColor_value_3)
            }
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
        const value_fontWeight  = value.fontWeight
        let value_fontWeight_type : int32 = RuntimeType.UNDEFINED
        value_fontWeight_type = runtimeType(value_fontWeight)
        valueSerializer.writeInt8((value_fontWeight_type).toChar())
        if ((value_fontWeight_type) != (RuntimeType.UNDEFINED)) {
            const value_fontWeight_value  = value_fontWeight!
            let value_fontWeight_value_type : int32 = RuntimeType.UNDEFINED
            value_fontWeight_value_type = runtimeType(value_fontWeight_value)
            if (RuntimeType.NUMBER == value_fontWeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontWeight_value_0  = value_fontWeight_value as number
                valueSerializer.writeNumber(value_fontWeight_value_0)
            }
            else if (TypeChecker.isFontWeight(value_fontWeight_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontWeight_value_1  = value_fontWeight_value as FontWeight
                valueSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_fontWeight_value_1))
            }
            else if ((RuntimeType.STRING == value_fontWeight_value_type) || (RuntimeType.OBJECT == value_fontWeight_value_type)) {
                valueSerializer.writeInt8((2).toChar())
                const value_fontWeight_value_2  = value_fontWeight_value as ResourceStr
                let value_fontWeight_value_2_type : int32 = RuntimeType.UNDEFINED
                value_fontWeight_value_2_type = runtimeType(value_fontWeight_value_2)
                if (RuntimeType.STRING == value_fontWeight_value_2_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_fontWeight_value_2_0  = value_fontWeight_value_2 as string
                    valueSerializer.writeString(value_fontWeight_value_2_0)
                }
                else if (RuntimeType.OBJECT == value_fontWeight_value_2_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_fontWeight_value_2_1  = value_fontWeight_value_2 as Resource
                    Resource_serializer.write(valueSerializer, value_fontWeight_value_2_1)
                }
            }
        }
    }
    public static read(buffer: DeserializerBase): BadgeStyle {
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
        const fontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSize_buf : number | ResourceStr | undefined
        if ((fontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let fontSize_buf_ : number | ResourceStr | undefined
            if (fontSize_buf__selector == (0).toChar()) {
                fontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontSize_buf__selector == (1).toChar()) {
                const fontSize_buf__u_selector : int32 = valueDeserializer.readInt8()
                let fontSize_buf__u : string | Resource | undefined
                if (fontSize_buf__u_selector == (0).toChar()) {
                    fontSize_buf__u = (valueDeserializer.readString() as string)
                }
                else if (fontSize_buf__u_selector == (1).toChar()) {
                    fontSize_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for fontSize_buf__u has to be chosen through deserialisation.")
                }
                fontSize_buf_ = (fontSize_buf__u as string | Resource)
            }
            else {
                throw new Error("One of the branches for fontSize_buf_ has to be chosen through deserialisation.")
            }
            fontSize_buf = (fontSize_buf_ as number | ResourceStr)
        }
        const fontSize_result : number | ResourceStr | undefined = fontSize_buf
        const badgeSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let badgeSize_buf : number | ResourceStr | undefined
        if ((badgeSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const badgeSize_buf__selector : int32 = valueDeserializer.readInt8()
            let badgeSize_buf_ : number | ResourceStr | undefined
            if (badgeSize_buf__selector == (0).toChar()) {
                badgeSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (badgeSize_buf__selector == (1).toChar()) {
                const badgeSize_buf__u_selector : int32 = valueDeserializer.readInt8()
                let badgeSize_buf__u : string | Resource | undefined
                if (badgeSize_buf__u_selector == (0).toChar()) {
                    badgeSize_buf__u = (valueDeserializer.readString() as string)
                }
                else if (badgeSize_buf__u_selector == (1).toChar()) {
                    badgeSize_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for badgeSize_buf__u has to be chosen through deserialisation.")
                }
                badgeSize_buf_ = (badgeSize_buf__u as string | Resource)
            }
            else {
                throw new Error("One of the branches for badgeSize_buf_ has to be chosen through deserialisation.")
            }
            badgeSize_buf = (badgeSize_buf_ as number | ResourceStr)
        }
        const badgeSize_result : number | ResourceStr | undefined = badgeSize_buf
        const badgeColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let badgeColor_buf : ResourceColor | undefined
        if ((badgeColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const badgeColor_buf__selector : int32 = valueDeserializer.readInt8()
            let badgeColor_buf_ : Color | number | string | Resource | undefined
            if (badgeColor_buf__selector == (0).toChar()) {
                badgeColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (badgeColor_buf__selector == (1).toChar()) {
                badgeColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (badgeColor_buf__selector == (2).toChar()) {
                badgeColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (badgeColor_buf__selector == (3).toChar()) {
                badgeColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for badgeColor_buf_ has to be chosen through deserialisation.")
            }
            badgeColor_buf = (badgeColor_buf_ as Color | number | string | Resource)
        }
        const badgeColor_result : ResourceColor | undefined = badgeColor_buf
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
        const fontWeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeight_buf : number | FontWeight | ResourceStr | undefined
        if ((fontWeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontWeight_buf__selector : int32 = valueDeserializer.readInt8()
            let fontWeight_buf_ : number | FontWeight | ResourceStr | undefined
            if (fontWeight_buf__selector == (0).toChar()) {
                fontWeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontWeight_buf__selector == (1).toChar()) {
                fontWeight_buf_ = TypeChecker.FontWeight_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontWeight_buf__selector == (2).toChar()) {
                const fontWeight_buf__u_selector : int32 = valueDeserializer.readInt8()
                let fontWeight_buf__u : string | Resource | undefined
                if (fontWeight_buf__u_selector == (0).toChar()) {
                    fontWeight_buf__u = (valueDeserializer.readString() as string)
                }
                else if (fontWeight_buf__u_selector == (1).toChar()) {
                    fontWeight_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for fontWeight_buf__u has to be chosen through deserialisation.")
                }
                fontWeight_buf_ = (fontWeight_buf__u as string | Resource)
            }
            else {
                throw new Error("One of the branches for fontWeight_buf_ has to be chosen through deserialisation.")
            }
            fontWeight_buf = (fontWeight_buf_ as number | FontWeight | ResourceStr)
        }
        const fontWeight_result : number | FontWeight | ResourceStr | undefined = fontWeight_buf
        let value : BadgeStyle = ({color: color_result, fontSize: fontSize_result, badgeSize: badgeSize_result, badgeColor: badgeColor_result, borderColor: borderColor_result, borderWidth: borderWidth_result, fontWeight: fontWeight_result} as BadgeStyle)
        return value
    }
}
export class BadgeParamWithNumber_serializer {
    public static write(buffer: SerializerBase, value: BadgeParamWithNumber): void {
        let valueSerializer : SerializerBase = buffer
        const value_position  = value.position
        let value_position_type : int32 = RuntimeType.UNDEFINED
        value_position_type = runtimeType(value_position)
        valueSerializer.writeInt8((value_position_type).toChar())
        if ((value_position_type) != (RuntimeType.UNDEFINED)) {
            const value_position_value  = value_position!
            let value_position_value_type : int32 = RuntimeType.UNDEFINED
            value_position_value_type = runtimeType(value_position_value)
            if (TypeChecker.isBadgePosition(value_position_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_position_value_0  = value_position_value as BadgePosition
                valueSerializer.writeInt32(TypeChecker.BadgePosition_ToNumeric(value_position_value_0))
            }
            else if (RuntimeType.OBJECT == value_position_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_position_value_1  = value_position_value as Position
                Position_serializer.write(valueSerializer, value_position_value_1)
            }
        }
        const value_style  = value.style
        BadgeStyle_serializer.write(valueSerializer, value_style)
        const value_count  = value.count
        valueSerializer.writeNumber(value_count)
        const value_maxCount  = value.maxCount
        let value_maxCount_type : int32 = RuntimeType.UNDEFINED
        value_maxCount_type = runtimeType(value_maxCount)
        valueSerializer.writeInt8((value_maxCount_type).toChar())
        if ((value_maxCount_type) != (RuntimeType.UNDEFINED)) {
            const value_maxCount_value  = value_maxCount!
            valueSerializer.writeNumber(value_maxCount_value)
        }
    }
    public static read(buffer: DeserializerBase): BadgeParamWithNumber {
        let valueDeserializer : DeserializerBase = buffer
        const position_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let position_buf : BadgePosition | Position | undefined
        if ((position_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const position_buf__selector : int32 = valueDeserializer.readInt8()
            let position_buf_ : BadgePosition | Position | undefined
            if (position_buf__selector == (0).toChar()) {
                position_buf_ = TypeChecker.BadgePosition_FromNumeric(valueDeserializer.readInt32())
            }
            else if (position_buf__selector == (1).toChar()) {
                position_buf_ = Position_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for position_buf_ has to be chosen through deserialisation.")
            }
            position_buf = (position_buf_ as BadgePosition | Position)
        }
        const position_result : BadgePosition | Position | undefined = position_buf
        const style_result : BadgeStyle = BadgeStyle_serializer.read(valueDeserializer)
        const count_result : number = (valueDeserializer.readNumber() as number)
        const maxCount_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxCount_buf : number | undefined
        if ((maxCount_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maxCount_buf = (valueDeserializer.readNumber() as number)
        }
        const maxCount_result : number | undefined = maxCount_buf
        let value : BadgeParamWithNumber = ({position: position_result, style: style_result, count: count_result, maxCount: maxCount_result} as BadgeParamWithNumber)
        return value
    }
}
export class BadgeParamWithString_serializer {
    public static write(buffer: SerializerBase, value: BadgeParamWithString): void {
        let valueSerializer : SerializerBase = buffer
        const value_position  = value.position
        let value_position_type : int32 = RuntimeType.UNDEFINED
        value_position_type = runtimeType(value_position)
        valueSerializer.writeInt8((value_position_type).toChar())
        if ((value_position_type) != (RuntimeType.UNDEFINED)) {
            const value_position_value  = value_position!
            let value_position_value_type : int32 = RuntimeType.UNDEFINED
            value_position_value_type = runtimeType(value_position_value)
            if (TypeChecker.isBadgePosition(value_position_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_position_value_0  = value_position_value as BadgePosition
                valueSerializer.writeInt32(TypeChecker.BadgePosition_ToNumeric(value_position_value_0))
            }
            else if (RuntimeType.OBJECT == value_position_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_position_value_1  = value_position_value as Position
                Position_serializer.write(valueSerializer, value_position_value_1)
            }
        }
        const value_style  = value.style
        BadgeStyle_serializer.write(valueSerializer, value_style)
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
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
    }
    public static read(buffer: DeserializerBase): BadgeParamWithString {
        let valueDeserializer : DeserializerBase = buffer
        const position_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let position_buf : BadgePosition | Position | undefined
        if ((position_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const position_buf__selector : int32 = valueDeserializer.readInt8()
            let position_buf_ : BadgePosition | Position | undefined
            if (position_buf__selector == (0).toChar()) {
                position_buf_ = TypeChecker.BadgePosition_FromNumeric(valueDeserializer.readInt32())
            }
            else if (position_buf__selector == (1).toChar()) {
                position_buf_ = Position_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for position_buf_ has to be chosen through deserialisation.")
            }
            position_buf = (position_buf_ as BadgePosition | Position)
        }
        const position_result : BadgePosition | Position | undefined = position_buf
        const style_result : BadgeStyle = BadgeStyle_serializer.read(valueDeserializer)
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Resource | undefined
        if (value_buf_selector == (0).toChar()) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == (1).toChar()) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : ResourceStr = (value_buf as string | Resource)
        let value : BadgeParamWithString = ({position: position_result, style: style_result, value: value_result} as BadgeParamWithString)
        return value
    }
}
