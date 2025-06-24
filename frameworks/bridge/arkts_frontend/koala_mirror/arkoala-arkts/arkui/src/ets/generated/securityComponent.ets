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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./resource"
import { Position_serializer, Edges_serializer, LocalizedEdges_serializer, Padding_serializer, SizeOptions_serializer, ConstraintSizeOptions_serializer, Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions, Bias } from "./units"
import { AlignRuleOption_serializer, LocalizedAlignRuleOptions_serializer, AlignRuleOption, LocalizedAlignRuleOptions, ChainStyle, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam } from "./common"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { FontStyle, FontWeight, Color, BorderStyle, Alignment, Axis, TextHeightAdaptivePolicy } from "./enums"
import { LengthMetrics } from "./arkui.Graphics"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier, AttributeUpdater } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSecurityComponentMethodPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSecurityComponentMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SecurityComponentMethod_construct(peerId, flags)
        const _peer  = new ArkSecurityComponentMethodPeer(_peerPtr, peerId, "SecurityComponentMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    iconSizeAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_iconSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutDirectionAttribute(value: SecurityComponentLayoutDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SecurityComponentLayoutDirection)
            thisSerializer.writeInt32(TypeChecker.SecurityComponentLayoutDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_layoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    positionAttribute(value: Position | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            Position_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_position(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    markAnchorAttribute(value: Position | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            Position_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_markAnchor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offsetAttribute(value: Position | Edges | LocalizedEdges | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPosition(value_value, false, false)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Position
                Position_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Edges
                Edges_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isLocalizedEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as LocalizedEdges
                LocalizedEdges_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_offset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: int32 | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as int32
                thisSerializer.writeInt32(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    iconColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_iconColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_backgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderStyleAttribute(value: BorderStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BorderStyle)
            thisSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderRadiusAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    paddingAttribute(value: Padding | Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Padding
                Padding_serializer.write(thisSerializer, value_value_0)
            }
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Dimension
                let value_value_1_type : int32 = RuntimeType.UNDEFINED
                value_value_1_type = runtimeType(value_value_1)
                if (RuntimeType.STRING == value_value_1_type) {
                    thisSerializer.writeInt8(0)
                    const value_value_1_0  = value_value_1 as string
                    thisSerializer.writeString(value_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_value_1_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_1_1  = value_value_1 as number
                    thisSerializer.writeNumber(value_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_value_1_type) {
                    thisSerializer.writeInt8(2)
                    const value_value_1_2  = value_value_1 as Resource
                    Resource_serializer.write(thisSerializer, value_value_1_2)
                }
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_padding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textIconSpaceAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_textIconSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_key(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    widthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_width(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_height(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            SizeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_size(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    constraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            ConstraintSizeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_constraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignAttribute(alignType: Alignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8(alignType_type)
        if ((RuntimeType.UNDEFINED) != (alignType_type)) {
            const alignType_value  = (alignType as Alignment)
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(alignType_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_align(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules0Attribute(alignRule: AlignRuleOption | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignRule_type : int32 = RuntimeType.UNDEFINED
        alignRule_type = runtimeType(alignRule)
        thisSerializer.writeInt8(alignRule_type)
        if ((RuntimeType.UNDEFINED) != (alignRule_type)) {
            const alignRule_value  = alignRule!
            AlignRuleOption_serializer.write(thisSerializer, alignRule_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_alignRules0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules1Attribute(alignRule: LocalizedAlignRuleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignRule_type : int32 = RuntimeType.UNDEFINED
        alignRule_type = runtimeType(alignRule)
        thisSerializer.writeInt8(alignRule_type)
        if ((RuntimeType.UNDEFINED) != (alignRule_type)) {
            const alignRule_value  = alignRule!
            LocalizedAlignRuleOptions_serializer.write(thisSerializer, alignRule_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_alignRules1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    idAttribute(description: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let description_type : int32 = RuntimeType.UNDEFINED
        description_type = runtimeType(description)
        thisSerializer.writeInt8(description_type)
        if ((RuntimeType.UNDEFINED) != (description_type)) {
            const description_value  = description!
            thisSerializer.writeString(description_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_id(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    chainModeAttribute(direction: Axis | undefined, style: ChainStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8(direction_type)
        if ((RuntimeType.UNDEFINED) != (direction_type)) {
            const direction_value  = (direction as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(direction_value))
        }
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as ChainStyle)
            thisSerializer.writeInt32(TypeChecker.ChainStyle_ToNumeric(style_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_chainMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontScaleAttribute(scale: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scale_type : int32 = RuntimeType.UNDEFINED
        scale_type = runtimeType(scale)
        thisSerializer.writeInt8(scale_type)
        if ((RuntimeType.UNDEFINED) != (scale_type)) {
            const scale_value  = scale!
            let scale_value_type : int32 = RuntimeType.UNDEFINED
            scale_value_type = runtimeType(scale_value)
            if (RuntimeType.NUMBER == scale_value_type) {
                thisSerializer.writeInt8(0)
                const scale_value_0  = scale_value as number
                thisSerializer.writeNumber(scale_value_0)
            }
            else if (RuntimeType.OBJECT == scale_value_type) {
                thisSerializer.writeInt8(1)
                const scale_value_1  = scale_value as Resource
                Resource_serializer.write(thisSerializer, scale_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_minFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontScaleAttribute(scale: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scale_type : int32 = RuntimeType.UNDEFINED
        scale_type = runtimeType(scale)
        thisSerializer.writeInt8(scale_type)
        if ((RuntimeType.UNDEFINED) != (scale_type)) {
            const scale_value  = scale!
            let scale_value_type : int32 = RuntimeType.UNDEFINED
            scale_value_type = runtimeType(scale_value)
            if (RuntimeType.NUMBER == scale_value_type) {
                thisSerializer.writeInt8(0)
                const scale_value_0  = scale_value as number
                thisSerializer.writeNumber(scale_value_0)
            }
            else if (RuntimeType.OBJECT == scale_value_type) {
                thisSerializer.writeInt8(1)
                const scale_value_1  = scale_value as Resource
                Resource_serializer.write(thisSerializer, scale_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_maxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLinesAttribute(line: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let line_type : int32 = RuntimeType.UNDEFINED
        line_type = runtimeType(line)
        thisSerializer.writeInt8(line_type)
        if ((RuntimeType.UNDEFINED) != (line_type)) {
            const line_value  = line!
            thisSerializer.writeNumber(line_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_maxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontSizeAttribute(minSize: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let minSize_type : int32 = RuntimeType.UNDEFINED
        minSize_type = runtimeType(minSize)
        thisSerializer.writeInt8(minSize_type)
        if ((RuntimeType.UNDEFINED) != (minSize_type)) {
            const minSize_value  = minSize!
            let minSize_value_type : int32 = RuntimeType.UNDEFINED
            minSize_value_type = runtimeType(minSize_value)
            if (RuntimeType.NUMBER == minSize_value_type) {
                thisSerializer.writeInt8(0)
                const minSize_value_0  = minSize_value as number
                thisSerializer.writeNumber(minSize_value_0)
            }
            else if (RuntimeType.STRING == minSize_value_type) {
                thisSerializer.writeInt8(1)
                const minSize_value_1  = minSize_value as string
                thisSerializer.writeString(minSize_value_1)
            }
            else if (RuntimeType.OBJECT == minSize_value_type) {
                thisSerializer.writeInt8(2)
                const minSize_value_2  = minSize_value as Resource
                Resource_serializer.write(thisSerializer, minSize_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(maxSize: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let maxSize_type : int32 = RuntimeType.UNDEFINED
        maxSize_type = runtimeType(maxSize)
        thisSerializer.writeInt8(maxSize_type)
        if ((RuntimeType.UNDEFINED) != (maxSize_type)) {
            const maxSize_value  = maxSize!
            let maxSize_value_type : int32 = RuntimeType.UNDEFINED
            maxSize_value_type = runtimeType(maxSize_value)
            if (RuntimeType.NUMBER == maxSize_value_type) {
                thisSerializer.writeInt8(0)
                const maxSize_value_0  = maxSize_value as number
                thisSerializer.writeNumber(maxSize_value_0)
            }
            else if (RuntimeType.STRING == maxSize_value_type) {
                thisSerializer.writeInt8(1)
                const maxSize_value_1  = maxSize_value as string
                thisSerializer.writeString(maxSize_value_1)
            }
            else if (RuntimeType.OBJECT == maxSize_value_type) {
                thisSerializer.writeInt8(2)
                const maxSize_value_2  = maxSize_value as Resource
                Resource_serializer.write(thisSerializer, maxSize_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_maxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(policy: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let policy_type : int32 = RuntimeType.UNDEFINED
        policy_type = runtimeType(policy)
        thisSerializer.writeInt8(policy_type)
        if ((RuntimeType.UNDEFINED) != (policy_type)) {
            const policy_value  = (policy as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(policy_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_heightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enabledAttribute(respond: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let respond_type : int32 = RuntimeType.UNDEFINED
        respond_type = runtimeType(respond)
        thisSerializer.writeInt8(respond_type)
        if ((RuntimeType.UNDEFINED) != (respond_type)) {
            const respond_value  = respond!
            thisSerializer.writeBoolean(respond_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_enabled(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SecurityComponentLayoutDirection {
    HORIZONTAL = 0,
    VERTICAL = 1
}
export interface SecurityComponentMethod {
    iconSize(value: Dimension | undefined): this
    layoutDirection(value: SecurityComponentLayoutDirection | undefined): this
    position(value: Position | undefined): this
    markAnchor(value: Position | undefined): this
    offset(value: Position | Edges | LocalizedEdges | undefined): this
    fontSize(value: Dimension | undefined): this
    fontStyle(value: FontStyle | undefined): this
    fontWeight(value: int32 | FontWeight | string | undefined): this
    fontFamily(value: string | Resource | undefined): this
    fontColor(value: ResourceColor | undefined): this
    iconColor(value: ResourceColor | undefined): this
    backgroundColor(value: ResourceColor | undefined): this
    borderStyle(value: BorderStyle | undefined): this
    borderWidth(value: Dimension | undefined): this
    borderColor(value: ResourceColor | undefined): this
    borderRadius(value: Dimension | undefined): this
    padding(value: Padding | Dimension | undefined): this
    textIconSpace(value: Dimension | undefined): this
    key(value: string | undefined): this
    width(value: Length | undefined): this
    height(value: Length | undefined): this
    size(value: SizeOptions | undefined): this
    constraintSize(value: ConstraintSizeOptions | undefined): this
    align(alignType: Alignment | undefined): this
    alignRules(alignRule: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this
    id(description: string | undefined): this
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this
    minFontScale(scale: number | Resource | undefined): this
    maxFontScale(scale: number | Resource | undefined): this
    maxLines(line: number | undefined): this
    minFontSize(minSize: number | string | Resource | undefined): this
    maxFontSize(maxSize: number | string | Resource | undefined): this
    heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this
    enabled(respond: boolean | undefined): this
    attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this
}
export class ArkSecurityComponentMethodStyle implements SecurityComponentMethod {
    public iconSize(value: Dimension | undefined): this {
        return this
    }
    public layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        return this
    }
    public position(value: Position | undefined): this {
        return this
    }
    public markAnchor(value: Position | undefined): this {
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges | undefined): this {
        return this
    }
    public fontSize(value: Dimension | undefined): this {
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public iconColor(value: ResourceColor | undefined): this {
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public borderStyle(value: BorderStyle | undefined): this {
        return this
    }
    public borderWidth(value: Dimension | undefined): this {
        return this
    }
    public borderColor(value: ResourceColor | undefined): this {
        return this
    }
    public borderRadius(value: Dimension | undefined): this {
        return this
    }
    public padding(value: Padding | Dimension | undefined): this {
        return this
    }
    public textIconSpace(value: Dimension | undefined): this {
        return this
    }
    public key(value: string | undefined): this {
        return this
    }
    public width(value: Length | undefined): this {
        return this
    }
    public height(value: Length | undefined): this {
        return this
    }
    public size(value: SizeOptions | undefined): this {
        return this
    }
    public constraintSize(value: ConstraintSizeOptions | undefined): this {
        return this
    }
    public align(alignType: Alignment | undefined): this {
        return this
    }
    public alignRules(alignRule: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this {
        return this
    }
    public id(description: string | undefined): this {
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        return this
    }
    public minFontScale(scale: number | Resource | undefined): this {
        return this
    }
    public maxFontScale(scale: number | Resource | undefined): this {
        return this
    }
    public maxLines(line: number | undefined): this {
        return this
    }
    public minFontSize(minSize: number | string | Resource | undefined): this {
        return this
    }
    public maxFontSize(maxSize: number | string | Resource | undefined): this {
        return this
    }
    public heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        return this
    }
    public enabled(respond: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SecurityComponentMethod): void {
    }
}
export class ArkSecurityComponentMethodComponent extends ComponentBase implements SecurityComponentMethod {
    getPeer(): ArkSecurityComponentMethodPeer {
        return (this.peer as ArkSecurityComponentMethodPeer)
    }
    public iconSize(value: Dimension | undefined): this {
        if (this.checkPriority("iconSize")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.iconSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (SecurityComponentLayoutDirection | undefined)
            this.getPeer()?.layoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public position(value: Position | undefined): this {
        if (this.checkPriority("position")) {
            const value_casted = value as (Position | undefined)
            this.getPeer()?.positionAttribute(value_casted)
            return this
        }
        return this
    }
    public markAnchor(value: Position | undefined): this {
        if (this.checkPriority("markAnchor")) {
            const value_casted = value as (Position | undefined)
            this.getPeer()?.markAnchorAttribute(value_casted)
            return this
        }
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges | undefined): this {
        if (this.checkPriority("offset")) {
            const value_casted = value as (Position | Edges | LocalizedEdges | undefined)
            this.getPeer()?.offsetAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: Dimension | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (int32 | FontWeight | string | undefined)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public iconColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("iconColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.iconColorAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public borderStyle(value: BorderStyle | undefined): this {
        if (this.checkPriority("borderStyle")) {
            const value_casted = value as (BorderStyle | undefined)
            this.getPeer()?.borderStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public borderWidth(value: Dimension | undefined): this {
        if (this.checkPriority("borderWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.borderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public borderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("borderColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.borderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public borderRadius(value: Dimension | undefined): this {
        if (this.checkPriority("borderRadius")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.borderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public padding(value: Padding | Dimension | undefined): this {
        if (this.checkPriority("padding")) {
            const value_casted = value as (Padding | Dimension | undefined)
            this.getPeer()?.paddingAttribute(value_casted)
            return this
        }
        return this
    }
    public textIconSpace(value: Dimension | undefined): this {
        if (this.checkPriority("textIconSpace")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.textIconSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public key(value: string | undefined): this {
        if (this.checkPriority("key")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.keyAttribute(value_casted)
            return this
        }
        return this
    }
    public width(value: Length | undefined): this {
        if (this.checkPriority("width")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.widthAttribute(value_casted)
            return this
        }
        return this
    }
    public height(value: Length | undefined): this {
        if (this.checkPriority("height")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.heightAttribute(value_casted)
            return this
        }
        return this
    }
    public size(value: SizeOptions | undefined): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions | undefined)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    public constraintSize(value: ConstraintSizeOptions | undefined): this {
        if (this.checkPriority("constraintSize")) {
            const value_casted = value as (ConstraintSizeOptions | undefined)
            this.getPeer()?.constraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public align(alignType: Alignment | undefined): this {
        if (this.checkPriority("align")) {
            const alignType_casted = alignType as (Alignment | undefined)
            this.getPeer()?.alignAttribute(alignType_casted)
            return this
        }
        return this
    }
    public alignRules(alignRule: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this {
        if (this.checkPriority("alignRules")) {
            const alignRule_type = runtimeType(alignRule)
            if ((RuntimeType.OBJECT == alignRule_type) || (RuntimeType.UNDEFINED == alignRule_type)) {
                const alignRule_casted = alignRule as (AlignRuleOption | undefined)
                this.getPeer()?.alignRules0Attribute(alignRule_casted)
                return this
            }
            if ((RuntimeType.OBJECT == alignRule_type) || (RuntimeType.UNDEFINED == alignRule_type)) {
                const alignRule_casted = alignRule as (LocalizedAlignRuleOptions | undefined)
                this.getPeer()?.alignRules1Attribute(alignRule_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public id(description: string | undefined): this {
        if (this.checkPriority("id")) {
            const description_casted = description as (string | undefined)
            this.getPeer()?.idAttribute(description_casted)
            return this
        }
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        if (this.checkPriority("chainMode")) {
            const direction_casted = direction as (Axis | undefined)
            const style_casted = style as (ChainStyle | undefined)
            this.getPeer()?.chainModeAttribute(direction_casted, style_casted)
            return this
        }
        return this
    }
    public minFontScale(scale: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const scale_casted = scale as (number | Resource | undefined)
            this.getPeer()?.minFontScaleAttribute(scale_casted)
            return this
        }
        return this
    }
    public maxFontScale(scale: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const scale_casted = scale as (number | Resource | undefined)
            this.getPeer()?.maxFontScaleAttribute(scale_casted)
            return this
        }
        return this
    }
    public maxLines(line: number | undefined): this {
        if (this.checkPriority("maxLines")) {
            const line_casted = line as (number | undefined)
            this.getPeer()?.maxLinesAttribute(line_casted)
            return this
        }
        return this
    }
    public minFontSize(minSize: number | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const minSize_casted = minSize as (number | string | Resource | undefined)
            this.getPeer()?.minFontSizeAttribute(minSize_casted)
            return this
        }
        return this
    }
    public maxFontSize(maxSize: number | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const maxSize_casted = maxSize as (number | string | Resource | undefined)
            this.getPeer()?.maxFontSizeAttribute(maxSize_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const policy_casted = policy as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.heightAdaptivePolicyAttribute(policy_casted)
            return this
        }
        return this
    }
    public enabled(respond: boolean | undefined): this {
        if (this.checkPriority("enabled")) {
            const respond_casted = respond as (boolean | undefined)
            this.getPeer()?.enabledAttribute(respond_casted)
            return this
        }
        return this
    }
    _modifier?: AttributeModifier<SecurityComponentMethod> | undefined
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSecurityComponentMethodStyle(receiver: SecurityComponentMethod, modifier: AttributeModifier<SecurityComponentMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSecurityComponentMethodStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<SecurityComponentMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<SecurityComponentMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
