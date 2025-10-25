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
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookBadgeAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ResourceColor, ResourceStr, Length, Position, Position_serializer } from "./units"
import { Color, FontWeight } from "./enums"
import { Resource } from "global.resource"
import { BadgeModifier } from "./../BadgeModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
export class ArkBadgePeer extends ArkCommonMethodPeer {
    attributeSet?: BadgeModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkBadgePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Badge_construct(peerId, flags)
        const _peer  = new ArkBadgePeer(_peerPtr, peerId, 'Badge', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setBadgeOptionsAttribute(value: BadgeParamWithNumber | BadgeParamWithString): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof BadgeParamWithNumber) {
            thisSerializer.writeInt8((0).toChar())
            const valueForIdx0  = value as BadgeParamWithNumber
            BadgeParamWithNumber_serializer.write(thisSerializer, valueForIdx0)
        } else if (value instanceof BadgeParamWithString) {
            thisSerializer.writeInt8((1).toChar())
            const valueForIdx1  = value as BadgeParamWithString
            BadgeParamWithString_serializer.write(thisSerializer, valueForIdx1)
        }
        ArkUIGeneratedNativeModule._BadgeInterface_setBadgeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    setBadgeOptions(value: BadgeParamWithNumber | BadgeParamWithString): this {
        throw new Error("Unimplemented method setBadgeOptions")
    }
    attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkBadgeStyle extends ArkCommonMethodStyle implements BadgeAttribute {
    attributeModifier_value?: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined
    setBadgeOptions(value: BadgeParamWithNumber | BadgeParamWithString): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkBadgeComponent extends ArkCommonMethodComponent implements BadgeAttribute {
    getPeer(): ArkBadgePeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkBadgePeer)
    }
    public setBadgeOptions(value: BadgeParamWithNumber | BadgeParamWithString): this {
        if (this.checkPriority("setBadgeOptions")) {
            const value_casted = value as (BadgeParamWithNumber | BadgeParamWithString)
            this.getPeer()?.setBadgeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookBadgeAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

export class BadgeStyle_serializer {
    public static write(buffer: SerializerBase, value: BadgeStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            if (valueHolderForFontSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForFontSizeTmpValueForIdx0  = valueHolderForFontSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontSizeTmpValueForIdx0)
            } else if (valueHolderForFontSizeTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForFontSizeTmpValueForIdx1  = valueHolderForFontSizeTmpValue as ResourceStr
                if (valueHolderForFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForFontSizeTmpValueForIdx1ForIdx0  = valueHolderForFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForFontSizeTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForFontSizeTmpValueForIdx1ForIdx1  = valueHolderForFontSizeTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForFontSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBadgeSize  = value.badgeSize
        if (valueHolderForBadgeSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBadgeSizeTmpValue  = valueHolderForBadgeSize!
            if (valueHolderForBadgeSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBadgeSizeTmpValueForIdx0  = valueHolderForBadgeSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForBadgeSizeTmpValueForIdx0)
            } else if (valueHolderForBadgeSizeTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBadgeSizeTmpValueForIdx1  = valueHolderForBadgeSizeTmpValue as ResourceStr
                if (valueHolderForBadgeSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForBadgeSizeTmpValueForIdx1ForIdx0  = valueHolderForBadgeSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForBadgeSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForBadgeSizeTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForBadgeSizeTmpValueForIdx1ForIdx1  = valueHolderForBadgeSizeTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBadgeSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBadgeColor  = value.badgeColor
        if (valueHolderForBadgeColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBadgeColorTmpValue  = valueHolderForBadgeColor!
            if (valueHolderForBadgeColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBadgeColorTmpValueForIdx0  = valueHolderForBadgeColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBadgeColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBadgeColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBadgeColorTmpValueForIdx1  = valueHolderForBadgeColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBadgeColorTmpValueForIdx1)
            } else if (valueHolderForBadgeColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForBadgeColorTmpValueForIdx2  = valueHolderForBadgeColorTmpValue as string
                valueSerializer.writeString(valueHolderForBadgeColorTmpValueForIdx2)
            } else if (valueHolderForBadgeColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForBadgeColorTmpValueForIdx3  = valueHolderForBadgeColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBadgeColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBorderColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBorderColorTmpValueForIdx1)
            } else if (valueHolderForBorderColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForBorderColorTmpValueForIdx2  = valueHolderForBorderColorTmpValue as string
                valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx2)
            } else if (valueHolderForBorderColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForBorderColorTmpValueForIdx3  = valueHolderForBorderColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as string
                valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0)
            } else if (valueHolderForBorderWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForBorderWidthTmpValueForIdx1)
            } else if (valueHolderForBorderWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForBorderWidthTmpValueForIdx2  = valueHolderForBorderWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = valueHolderForFontWeight!
            if (valueHolderForFontWeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForFontWeightTmpValueForIdx0  = valueHolderForFontWeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontWeightTmpValueForIdx0)
            } else if (valueHolderForFontWeightTmpValue instanceof FontWeight) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForFontWeightTmpValueForIdx1  = valueHolderForFontWeightTmpValue as FontWeight
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx1.valueOf())
            } else if (valueHolderForFontWeightTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForFontWeightTmpValueForIdx2  = valueHolderForFontWeightTmpValue as ResourceStr
                if (valueHolderForFontWeightTmpValueForIdx2 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForFontWeightTmpValueForIdx2ForIdx0  = valueHolderForFontWeightTmpValueForIdx2 as string
                    valueSerializer.writeString(valueHolderForFontWeightTmpValueForIdx2ForIdx0)
                } else if (valueHolderForFontWeightTmpValueForIdx2 instanceof Resource) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForFontWeightTmpValueForIdx2ForIdx1  = valueHolderForFontWeightTmpValueForIdx2 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForFontWeightTmpValueForIdx2ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BadgeStyle {
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
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSizeTmpBuf : number | ResourceStr | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBuf_ : number | ResourceStr | undefined
            if (fontSizeTmpBuf_UnionSelector == (0).toChar()) {
                fontSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontSizeTmpBuf_UnionSelector == (1).toChar()) {
                const fontSizeTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let fontSizeTmpBuf_BufU : string | Resource | undefined
                if (fontSizeTmpBuf_BufUUnionSelector == (0).toChar()) {
                    fontSizeTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (fontSizeTmpBuf_BufUUnionSelector == (1).toChar()) {
                    fontSizeTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for fontSizeTmpBuf_BufU has to be chosen through deserialisation.")
                }
                fontSizeTmpBuf_ = (fontSizeTmpBuf_BufU as string | Resource)
            } else {
                throw new Error("One of the branches for fontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            fontSizeTmpBuf = (fontSizeTmpBuf_ as number | ResourceStr)
        }
        const fontSizeTmpResult : number | ResourceStr | undefined = fontSizeTmpBuf
        const badgeSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let badgeSizeTmpBuf : number | ResourceStr | undefined = undefined
        if ((badgeSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const badgeSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let badgeSizeTmpBuf_ : number | ResourceStr | undefined
            if (badgeSizeTmpBuf_UnionSelector == (0).toChar()) {
                badgeSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (badgeSizeTmpBuf_UnionSelector == (1).toChar()) {
                const badgeSizeTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let badgeSizeTmpBuf_BufU : string | Resource | undefined
                if (badgeSizeTmpBuf_BufUUnionSelector == (0).toChar()) {
                    badgeSizeTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (badgeSizeTmpBuf_BufUUnionSelector == (1).toChar()) {
                    badgeSizeTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for badgeSizeTmpBuf_BufU has to be chosen through deserialisation.")
                }
                badgeSizeTmpBuf_ = (badgeSizeTmpBuf_BufU as string | Resource)
            } else {
                throw new Error("One of the branches for badgeSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            badgeSizeTmpBuf = (badgeSizeTmpBuf_ as number | ResourceStr)
        }
        const badgeSizeTmpResult : number | ResourceStr | undefined = badgeSizeTmpBuf
        const badgeColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let badgeColorTmpBuf : ResourceColor | undefined = undefined
        if ((badgeColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const badgeColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let badgeColorTmpBuf_ : Color | number | string | Resource | undefined
            if (badgeColorTmpBuf_UnionSelector == (0).toChar()) {
                badgeColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (badgeColorTmpBuf_UnionSelector == (1).toChar()) {
                badgeColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (badgeColorTmpBuf_UnionSelector == (2).toChar()) {
                badgeColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (badgeColorTmpBuf_UnionSelector == (3).toChar()) {
                badgeColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for badgeColorTmpBuf_ has to be chosen through deserialisation.")
            }
            badgeColorTmpBuf = (badgeColorTmpBuf_ as Color | number | string | Resource)
        }
        const badgeColorTmpResult : ResourceColor | undefined = badgeColorTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderColorTmpBuf : ResourceColor | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBuf_ : Color | number | string | Resource | undefined
            if (borderColorTmpBuf_UnionSelector == (0).toChar()) {
                borderColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (borderColorTmpBuf_UnionSelector == (1).toChar()) {
                borderColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (borderColorTmpBuf_UnionSelector == (2).toChar()) {
                borderColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (borderColorTmpBuf_UnionSelector == (3).toChar()) {
                borderColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderColorTmpBuf_ has to be chosen through deserialisation.")
            }
            borderColorTmpBuf = (borderColorTmpBuf_ as Color | number | string | Resource)
        }
        const borderColorTmpResult : ResourceColor | undefined = borderColorTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderWidthTmpBuf : Length | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBuf_ : string | number | Resource | undefined
            if (borderWidthTmpBuf_UnionSelector == (0).toChar()) {
                borderWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (borderWidthTmpBuf_UnionSelector == (1).toChar()) {
                borderWidthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (borderWidthTmpBuf_UnionSelector == (2).toChar()) {
                borderWidthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            borderWidthTmpBuf = (borderWidthTmpBuf_ as string | number | Resource)
        }
        const borderWidthTmpResult : Length | undefined = borderWidthTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeightTmpBuf : number | FontWeight | ResourceStr | undefined = undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontWeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontWeightTmpBuf_ : number | FontWeight | ResourceStr | undefined
            if (fontWeightTmpBuf_UnionSelector == (0).toChar()) {
                fontWeightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontWeightTmpBuf_UnionSelector == (1).toChar()) {
                fontWeightTmpBuf_ = FontWeight.fromValue(valueDeserializer.readInt32())
            } else if (fontWeightTmpBuf_UnionSelector == (2).toChar()) {
                const fontWeightTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let fontWeightTmpBuf_BufU : string | Resource | undefined
                if (fontWeightTmpBuf_BufUUnionSelector == (0).toChar()) {
                    fontWeightTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (fontWeightTmpBuf_BufUUnionSelector == (1).toChar()) {
                    fontWeightTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for fontWeightTmpBuf_BufU has to be chosen through deserialisation.")
                }
                fontWeightTmpBuf_ = (fontWeightTmpBuf_BufU as string | Resource)
            } else {
                throw new Error("One of the branches for fontWeightTmpBuf_ has to be chosen through deserialisation.")
            }
            fontWeightTmpBuf = (fontWeightTmpBuf_ as number | FontWeight | ResourceStr)
        }
        const fontWeightTmpResult : number | FontWeight | ResourceStr | undefined = fontWeightTmpBuf
        let value : BadgeStyle = ({color: colorTmpResult, fontSize: fontSizeTmpResult, badgeSize: badgeSizeTmpResult, badgeColor: badgeColorTmpResult, borderColor: borderColorTmpResult, borderWidth: borderWidthTmpResult, fontWeight: fontWeightTmpResult} as BadgeStyle)
        return value
    }
}
export class BadgeParamWithNumber_serializer {
    public static write(buffer: SerializerBase, value: BadgeParamWithNumber): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPosition  = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue  = valueHolderForPosition!
            if (valueHolderForPositionTmpValue instanceof BadgePosition) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForPositionTmpValueForIdx0  = valueHolderForPositionTmpValue as BadgePosition
                valueSerializer.writeInt32(valueHolderForPositionTmpValueForIdx0.valueOf())
            } else if (valueHolderForPositionTmpValue instanceof Position) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForPositionTmpValueForIdx1  = valueHolderForPositionTmpValue as Position
                Position_serializer.write(valueSerializer, valueHolderForPositionTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        BadgeStyle_serializer.write(valueSerializer, valueHolderForStyle)
        const valueHolderForCount  = value.count
        valueSerializer.writeNumber(valueHolderForCount)
        const valueHolderForMaxCount  = value.maxCount
        if (valueHolderForMaxCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxCountTmpValue  = valueHolderForMaxCount!
            valueSerializer.writeNumber(valueHolderForMaxCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BadgeParamWithNumber {
        let valueDeserializer : DeserializerBase = buffer
        const positionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let positionTmpBuf : BadgePosition | Position | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const positionTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let positionTmpBuf_ : BadgePosition | Position | undefined
            if (positionTmpBuf_UnionSelector == (0).toChar()) {
                positionTmpBuf_ = BadgePosition.fromValue(valueDeserializer.readInt32())
            } else if (positionTmpBuf_UnionSelector == (1).toChar()) {
                positionTmpBuf_ = Position_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for positionTmpBuf_ has to be chosen through deserialisation.")
            }
            positionTmpBuf = (positionTmpBuf_ as BadgePosition | Position)
        }
        const positionTmpResult : BadgePosition | Position | undefined = positionTmpBuf
        const styleTmpResult : BadgeStyle = BadgeStyle_serializer.read(valueDeserializer)
        const countTmpResult : number = (valueDeserializer.readNumber() as number)
        const maxCountTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxCountTmpBuf : number | undefined = undefined
        if ((maxCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxCountTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const maxCountTmpResult : number | undefined = maxCountTmpBuf
        let value : BadgeParamWithNumber = ({position: positionTmpResult, style: styleTmpResult, count: countTmpResult, maxCount: maxCountTmpResult} as BadgeParamWithNumber)
        return value
    }
}
export class BadgeParamWithString_serializer {
    public static write(buffer: SerializerBase, value: BadgeParamWithString): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPosition  = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue  = valueHolderForPosition!
            if (valueHolderForPositionTmpValue instanceof BadgePosition) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForPositionTmpValueForIdx0  = valueHolderForPositionTmpValue as BadgePosition
                valueSerializer.writeInt32(valueHolderForPositionTmpValueForIdx0.valueOf())
            } else if (valueHolderForPositionTmpValue instanceof Position) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForPositionTmpValueForIdx1  = valueHolderForPositionTmpValue as Position
                Position_serializer.write(valueSerializer, valueHolderForPositionTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        BadgeStyle_serializer.write(valueSerializer, valueHolderForStyle)
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForValueForIdx1  = valueHolderForValue as Resource
            Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): BadgeParamWithString {
        let valueDeserializer : DeserializerBase = buffer
        const positionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let positionTmpBuf : BadgePosition | Position | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const positionTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let positionTmpBuf_ : BadgePosition | Position | undefined
            if (positionTmpBuf_UnionSelector == (0).toChar()) {
                positionTmpBuf_ = BadgePosition.fromValue(valueDeserializer.readInt32())
            } else if (positionTmpBuf_UnionSelector == (1).toChar()) {
                positionTmpBuf_ = Position_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for positionTmpBuf_ has to be chosen through deserialisation.")
            }
            positionTmpBuf = (positionTmpBuf_ as BadgePosition | Position)
        }
        const positionTmpResult : BadgePosition | Position | undefined = positionTmpBuf
        const styleTmpResult : BadgeStyle = BadgeStyle_serializer.read(valueDeserializer)
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | Resource | undefined
        if (valueTmpBufUnionSelector == (0).toChar()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toChar()) {
            valueTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
        }
        const valueTmpResult : ResourceStr = (valueTmpBuf as string | Resource)
        let value : BadgeParamWithString = ({position: positionTmpResult, style: styleTmpResult, value: valueTmpResult} as BadgeParamWithString)
        return value
    }
}
