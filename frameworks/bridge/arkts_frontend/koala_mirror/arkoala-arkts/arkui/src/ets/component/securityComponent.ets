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
import { Resource_serializer, Resource } from "./../generated/resource"
import { Position_serializer, Edges_serializer, LocalizedEdges_serializer, BorderRadiuses_serializer, Padding_serializer, SizeOptions_serializer, ConstraintSizeOptions_serializer, Dimension, Position, Edges, LocalizedEdges, ResourceColor, BorderRadiuses, Padding, Length, SizeOptions, ConstraintSizeOptions, Bias } from "./units"
import { AlignRuleOption_serializer, LocalizedAlignRuleOptions_serializer, AlignRuleOption, LocalizedAlignRuleOptions, ChainStyle, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam } from "./common"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { FontStyle, FontWeight, Color, BorderStyle, Alignment, Axis, TextHeightAdaptivePolicy } from "./enums"
import { LengthMetrics } from "./../generated/arkui.Graphics"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
    setIconSizeAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setIconSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutDirectionAttribute(value: SecurityComponentLayoutDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SecurityComponentLayoutDirection)
            thisSerializer.writeInt32(TypeChecker.SecurityComponentLayoutDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setLayoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPositionAttribute(value: Position | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Position_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarkAnchorAttribute(value: Position | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Position_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMarkAnchor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOffsetAttribute(value: Position | Edges | LocalizedEdges | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPosition(value_value, false, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Position
                Position_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Edges
                Edges_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isLocalizedEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as LocalizedEdges
                LocalizedEdges_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: int32 | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as int32
                thisSerializer.writeInt32(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIconColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setIconColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBorderStyleAttribute(value: BorderStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BorderStyle)
            thisSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBorderStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBorderWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBorderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBorderColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBorderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBorderRadiusAttribute(radius: Dimension | BorderRadiuses | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let radius_type : int32 = RuntimeType.UNDEFINED
        radius_type = runtimeType(radius)
        thisSerializer.writeInt8((radius_type).toChar())
        if ((radius_type) != (RuntimeType.UNDEFINED)) {
            const radius_value  = radius!
            let radius_value_type : int32 = RuntimeType.UNDEFINED
            radius_value_type = runtimeType(radius_value)
            if ((RuntimeType.STRING == radius_value_type) || (RuntimeType.NUMBER == radius_value_type) || (RuntimeType.OBJECT == radius_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const radius_value_0  = radius_value as Dimension
                let radius_value_0_type : int32 = RuntimeType.UNDEFINED
                radius_value_0_type = runtimeType(radius_value_0)
                if (RuntimeType.STRING == radius_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const radius_value_0_0  = radius_value_0 as string
                    thisSerializer.writeString(radius_value_0_0)
                }
                else if (RuntimeType.NUMBER == radius_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const radius_value_0_1  = radius_value_0 as number
                    thisSerializer.writeNumber(radius_value_0_1)
                }
                else if (RuntimeType.OBJECT == radius_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const radius_value_0_2  = radius_value_0 as Resource
                    Resource_serializer.write(thisSerializer, radius_value_0_2)
                }
            }
            else if (TypeChecker.isBorderRadiuses(radius_value, false, false, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const radius_value_1  = radius_value as BorderRadiuses
                BorderRadiuses_serializer.write(thisSerializer, radius_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPaddingAttribute(value: Padding | Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, false, false, false, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Padding
                Padding_serializer.write(thisSerializer, value_value_0)
            }
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Dimension
                let value_value_1_type : int32 = RuntimeType.UNDEFINED
                value_value_1_type = runtimeType(value_value_1)
                if (RuntimeType.STRING == value_value_1_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_1_0  = value_value_1 as string
                    thisSerializer.writeString(value_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_value_1_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_1_1  = value_value_1 as number
                    thisSerializer.writeNumber(value_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_value_1_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_1_2  = value_value_1 as Resource
                    Resource_serializer.write(thisSerializer, value_value_1_2)
                }
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setPadding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextIconSpaceAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setTextIconSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setKey(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHeightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SizeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setConstraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ConstraintSizeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setConstraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignAttribute(alignType: Alignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8((alignType_type).toChar())
        if ((alignType_type) != (RuntimeType.UNDEFINED)) {
            const alignType_value  = (alignType as Alignment)
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(alignType_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignRules0Attribute(alignRule: AlignRuleOption | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignRule_type : int32 = RuntimeType.UNDEFINED
        alignRule_type = runtimeType(alignRule)
        thisSerializer.writeInt8((alignRule_type).toChar())
        if ((alignRule_type) != (RuntimeType.UNDEFINED)) {
            const alignRule_value  = alignRule!
            AlignRuleOption_serializer.write(thisSerializer, alignRule_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setAlignRules0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignRules1Attribute(alignRule: LocalizedAlignRuleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignRule_type : int32 = RuntimeType.UNDEFINED
        alignRule_type = runtimeType(alignRule)
        thisSerializer.writeInt8((alignRule_type).toChar())
        if ((alignRule_type) != (RuntimeType.UNDEFINED)) {
            const alignRule_value  = alignRule!
            LocalizedAlignRuleOptions_serializer.write(thisSerializer, alignRule_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setAlignRules1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIdAttribute(description: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let description_type : int32 = RuntimeType.UNDEFINED
        description_type = runtimeType(description)
        thisSerializer.writeInt8((description_type).toChar())
        if ((description_type) != (RuntimeType.UNDEFINED)) {
            const description_value  = description!
            thisSerializer.writeString(description_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setId(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChainModeAttribute(direction: Axis | undefined, style: ChainStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8((direction_type).toChar())
        if ((direction_type) != (RuntimeType.UNDEFINED)) {
            const direction_value  = (direction as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(direction_value))
        }
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8((style_type).toChar())
        if ((style_type) != (RuntimeType.UNDEFINED)) {
            const style_value  = (style as ChainStyle)
            thisSerializer.writeInt32(TypeChecker.ChainStyle_ToNumeric(style_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setChainMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(scale: double | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scale_type : int32 = RuntimeType.UNDEFINED
        scale_type = runtimeType(scale)
        thisSerializer.writeInt8((scale_type).toChar())
        if ((scale_type) != (RuntimeType.UNDEFINED)) {
            const scale_value  = scale!
            let scale_value_type : int32 = RuntimeType.UNDEFINED
            scale_value_type = runtimeType(scale_value)
            if (RuntimeType.NUMBER == scale_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const scale_value_0  = scale_value as double
                thisSerializer.writeFloat64(scale_value_0)
            }
            else if (RuntimeType.OBJECT == scale_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const scale_value_1  = scale_value as Resource
                Resource_serializer.write(thisSerializer, scale_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(scale: double | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scale_type : int32 = RuntimeType.UNDEFINED
        scale_type = runtimeType(scale)
        thisSerializer.writeInt8((scale_type).toChar())
        if ((scale_type) != (RuntimeType.UNDEFINED)) {
            const scale_value  = scale!
            let scale_value_type : int32 = RuntimeType.UNDEFINED
            scale_value_type = runtimeType(scale_value)
            if (RuntimeType.NUMBER == scale_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const scale_value_0  = scale_value as double
                thisSerializer.writeFloat64(scale_value_0)
            }
            else if (RuntimeType.OBJECT == scale_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const scale_value_1  = scale_value as Resource
                Resource_serializer.write(thisSerializer, scale_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLinesAttribute(line: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let line_type : int32 = RuntimeType.UNDEFINED
        line_type = runtimeType(line)
        thisSerializer.writeInt8((line_type).toChar())
        if ((line_type) != (RuntimeType.UNDEFINED)) {
            const line_value  = line!
            thisSerializer.writeInt32(line_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMaxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(minSize: double | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let minSize_type : int32 = RuntimeType.UNDEFINED
        minSize_type = runtimeType(minSize)
        thisSerializer.writeInt8((minSize_type).toChar())
        if ((minSize_type) != (RuntimeType.UNDEFINED)) {
            const minSize_value  = minSize!
            let minSize_value_type : int32 = RuntimeType.UNDEFINED
            minSize_value_type = runtimeType(minSize_value)
            if (RuntimeType.NUMBER == minSize_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const minSize_value_0  = minSize_value as double
                thisSerializer.writeFloat64(minSize_value_0)
            }
            else if (RuntimeType.STRING == minSize_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const minSize_value_1  = minSize_value as string
                thisSerializer.writeString(minSize_value_1)
            }
            else if (RuntimeType.OBJECT == minSize_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const minSize_value_2  = minSize_value as Resource
                Resource_serializer.write(thisSerializer, minSize_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontSizeAttribute(maxSize: double | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let maxSize_type : int32 = RuntimeType.UNDEFINED
        maxSize_type = runtimeType(maxSize)
        thisSerializer.writeInt8((maxSize_type).toChar())
        if ((maxSize_type) != (RuntimeType.UNDEFINED)) {
            const maxSize_value  = maxSize!
            let maxSize_value_type : int32 = RuntimeType.UNDEFINED
            maxSize_value_type = runtimeType(maxSize_value)
            if (RuntimeType.NUMBER == maxSize_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const maxSize_value_0  = maxSize_value as double
                thisSerializer.writeFloat64(maxSize_value_0)
            }
            else if (RuntimeType.STRING == maxSize_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const maxSize_value_1  = maxSize_value as string
                thisSerializer.writeString(maxSize_value_1)
            }
            else if (RuntimeType.OBJECT == maxSize_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const maxSize_value_2  = maxSize_value as Resource
                Resource_serializer.write(thisSerializer, maxSize_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMaxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHeightAdaptivePolicyAttribute(policy: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let policy_type : int32 = RuntimeType.UNDEFINED
        policy_type = runtimeType(policy)
        thisSerializer.writeInt8((policy_type).toChar())
        if ((policy_type) != (RuntimeType.UNDEFINED)) {
            const policy_value  = (policy as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(policy_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setHeightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnabledAttribute(respond: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let respond_type : int32 = RuntimeType.UNDEFINED
        respond_type = runtimeType(respond)
        thisSerializer.writeInt8((respond_type).toChar())
        if ((respond_type) != (RuntimeType.UNDEFINED)) {
            const respond_value  = respond!
            thisSerializer.writeBoolean(respond_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setEnabled(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    borderRadius(radius: Dimension | BorderRadiuses | undefined): this
    padding(value: Padding | Dimension | undefined): this
    textIconSpace(value: Dimension | undefined): this
    key(value: string | undefined): this
    width(value: Length | undefined): this
    height(value: Length | undefined): this
    size(value: SizeOptions | undefined): this
    constraintSize(value: ConstraintSizeOptions | undefined): this
    align(alignType: Alignment | undefined): this
    alignRules(alignRule: AlignRuleOption | undefined): this
    alignRules(alignRule: LocalizedAlignRuleOptions | undefined): this
    id(description: string | undefined): this
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this
    minFontScale(scale: double | Resource | undefined): this
    maxFontScale(scale: double | Resource | undefined): this
    maxLines(line: int32 | undefined): this
    minFontSize(minSize: double | string | Resource | undefined): this
    maxFontSize(maxSize: double | string | Resource | undefined): this
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
    public borderRadius(radius: Dimension | BorderRadiuses | undefined): this {
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
    public alignRules(alignRule: AlignRuleOption | undefined): this {
        return this
    }
    public alignRules(alignRule: LocalizedAlignRuleOptions | undefined): this {
        return this
    }
    public id(description: string | undefined): this {
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        return this
    }
    public minFontScale(scale: double | Resource | undefined): this {
        return this
    }
    public maxFontScale(scale: double | Resource | undefined): this {
        return this
    }
    public maxLines(line: int32 | undefined): this {
        return this
    }
    public minFontSize(minSize: double | string | Resource | undefined): this {
        return this
    }
    public maxFontSize(maxSize: double | string | Resource | undefined): this {
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
            this.getPeer()?.setIconSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (SecurityComponentLayoutDirection | undefined)
            this.getPeer()?.setLayoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public position(value: Position | undefined): this {
        if (this.checkPriority("position")) {
            const value_casted = value as (Position | undefined)
            this.getPeer()?.setPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public markAnchor(value: Position | undefined): this {
        if (this.checkPriority("markAnchor")) {
            const value_casted = value as (Position | undefined)
            this.getPeer()?.setMarkAnchorAttribute(value_casted)
            return this
        }
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges | undefined): this {
        if (this.checkPriority("offset")) {
            const value_casted = value as (Position | Edges | LocalizedEdges | undefined)
            this.getPeer()?.setOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: Dimension | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (int32 | FontWeight | string | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public iconColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("iconColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setIconColorAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public borderStyle(value: BorderStyle | undefined): this {
        if (this.checkPriority("borderStyle")) {
            const value_casted = value as (BorderStyle | undefined)
            this.getPeer()?.setBorderStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public borderWidth(value: Dimension | undefined): this {
        if (this.checkPriority("borderWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setBorderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public borderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("borderColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBorderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public borderRadius(radius: Dimension | BorderRadiuses | undefined): this {
        if (this.checkPriority("borderRadius")) {
            const radius_casted = radius as (Dimension | BorderRadiuses | undefined)
            this.getPeer()?.setBorderRadiusAttribute(radius_casted)
            return this
        }
        return this
    }
    public padding(value: Padding | Dimension | undefined): this {
        if (this.checkPriority("padding")) {
            const value_casted = value as (Padding | Dimension | undefined)
            this.getPeer()?.setPaddingAttribute(value_casted)
            return this
        }
        return this
    }
    public textIconSpace(value: Dimension | undefined): this {
        if (this.checkPriority("textIconSpace")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setTextIconSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public key(value: string | undefined): this {
        if (this.checkPriority("key")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setKeyAttribute(value_casted)
            return this
        }
        return this
    }
    public width(value: Length | undefined): this {
        if (this.checkPriority("width")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public height(value: Length | undefined): this {
        if (this.checkPriority("height")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public size(value: SizeOptions | undefined): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions | undefined)
            this.getPeer()?.setSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public constraintSize(value: ConstraintSizeOptions | undefined): this {
        if (this.checkPriority("constraintSize")) {
            const value_casted = value as (ConstraintSizeOptions | undefined)
            this.getPeer()?.setConstraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public align(alignType: Alignment | undefined): this {
        if (this.checkPriority("align")) {
            const alignType_casted = alignType as (Alignment | undefined)
            this.getPeer()?.setAlignAttribute(alignType_casted)
            return this
        }
        return this
    }
    public alignRules(alignRule: AlignRuleOption | undefined): this {
        if (this.checkPriority("alignRules")) {
            const alignRule_casted = alignRule as (AlignRuleOption | undefined)
            this.getPeer()?.setAlignRules0Attribute(alignRule_casted)
            return this
        }
        return this
    }
    public alignRules(alignRule: LocalizedAlignRuleOptions | undefined): this {
        if (this.checkPriority("alignRules")) {
            const alignRule_casted = alignRule as (LocalizedAlignRuleOptions | undefined)
            this.getPeer()?.setAlignRules1Attribute(alignRule_casted)
            return this
        }
        return this
    }
    public id(description: string | undefined): this {
        if (this.checkPriority("id")) {
            const description_casted = description as (string | undefined)
            this.getPeer()?.setIdAttribute(description_casted)
            return this
        }
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        if (this.checkPriority("chainMode")) {
            const direction_casted = direction as (Axis | undefined)
            const style_casted = style as (ChainStyle | undefined)
            this.getPeer()?.setChainModeAttribute(direction_casted, style_casted)
            return this
        }
        return this
    }
    public minFontScale(scale: double | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const scale_casted = scale as (double | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(scale_casted)
            return this
        }
        return this
    }
    public maxFontScale(scale: double | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const scale_casted = scale as (double | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(scale_casted)
            return this
        }
        return this
    }
    public maxLines(line: int32 | undefined): this {
        if (this.checkPriority("maxLines")) {
            const line_casted = line as (int32 | undefined)
            this.getPeer()?.setMaxLinesAttribute(line_casted)
            return this
        }
        return this
    }
    public minFontSize(minSize: double | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const minSize_casted = minSize as (double | string | Resource | undefined)
            this.getPeer()?.setMinFontSizeAttribute(minSize_casted)
            return this
        }
        return this
    }
    public maxFontSize(maxSize: double | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const maxSize_casted = maxSize as (double | string | Resource | undefined)
            this.getPeer()?.setMaxFontSizeAttribute(maxSize_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const policy_casted = policy as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.setHeightAdaptivePolicyAttribute(policy_casted)
            return this
        }
        return this
    }
    public enabled(respond: boolean | undefined): this {
        if (this.checkPriority("enabled")) {
            const respond_casted = respond as (boolean | undefined)
            this.getPeer()?.setEnabledAttribute(respond_casted)
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<SecurityComponentMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<SecurityComponentMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
export class ArkSecurityComponentMethodSet implements SecurityComponentMethod {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _iconSize_flag?: boolean
    _iconSize0_value?: Dimension | undefined
    _layoutDirection_flag?: boolean
    _layoutDirection0_value?: SecurityComponentLayoutDirection | undefined
    _position_flag?: boolean
    _position0_value?: Position | undefined
    _markAnchor_flag?: boolean
    _markAnchor0_value?: Position | undefined
    _offset_flag?: boolean
    _offset0_value?: Position | Edges | LocalizedEdges | undefined
    _fontSize_flag?: boolean
    _fontSize0_value?: Dimension | undefined
    _fontStyle_flag?: boolean
    _fontStyle0_value?: FontStyle | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: int32 | FontWeight | string | undefined
    _fontFamily_flag?: boolean
    _fontFamily0_value?: string | Resource | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _iconColor_flag?: boolean
    _iconColor0_value?: ResourceColor | undefined
    _backgroundColor_flag?: boolean
    _backgroundColor0_value?: ResourceColor | undefined
    _borderStyle_flag?: boolean
    _borderStyle0_value?: BorderStyle | undefined
    _borderWidth_flag?: boolean
    _borderWidth0_value?: Dimension | undefined
    _borderColor_flag?: boolean
    _borderColor0_value?: ResourceColor | undefined
    _borderRadius_flag?: boolean
    _borderRadius0_value?: Dimension | BorderRadiuses | undefined
    _padding_flag?: boolean
    _padding0_value?: Padding | Dimension | undefined
    _textIconSpace_flag?: boolean
    _textIconSpace0_value?: Dimension | undefined
    _key_flag?: boolean
    _key0_value?: string | undefined
    _width_flag?: boolean
    _width0_value?: Length | undefined
    _height_flag?: boolean
    _height0_value?: Length | undefined
    _size_flag?: boolean
    _size0_value?: SizeOptions | undefined
    _constraintSize_flag?: boolean
    _constraintSize0_value?: ConstraintSizeOptions | undefined
    _align_flag?: boolean
    _align0_value?: Alignment | undefined
    _alignRules_flag?: boolean
    _alignRules0_value?: LocalizedAlignRuleOptions | undefined
    _id_flag?: boolean
    _id0_value?: string | undefined
    _chainMode_flag?: boolean
    _chainMode0_value?: Axis | undefined
    _chainMode1_value?: ChainStyle | undefined
    _minFontScale_flag?: boolean
    _minFontScale0_value?: double | Resource | undefined
    _maxFontScale_flag?: boolean
    _maxFontScale0_value?: double | Resource | undefined
    _maxLines_flag?: boolean
    _maxLines0_value?: int32 | undefined
    _minFontSize_flag?: boolean
    _minFontSize0_value?: double | string | Resource | undefined
    _maxFontSize_flag?: boolean
    _maxFontSize0_value?: double | string | Resource | undefined
    _heightAdaptivePolicy_flag?: boolean
    _heightAdaptivePolicy0_value?: TextHeightAdaptivePolicy | undefined
    _enabled_flag?: boolean
    _enabled0_value?: boolean | undefined
    applyModifierPatch(component: SecurityComponentMethod): void {
        if (this._iconSize_flag)
            component.iconSize((this._iconSize0_value as Dimension | undefined))
        if (this._layoutDirection_flag)
            component.layoutDirection((this._layoutDirection0_value as SecurityComponentLayoutDirection | undefined))
        if (this._position_flag)
            component.position((this._position0_value as Position | undefined))
        if (this._markAnchor_flag)
            component.markAnchor((this._markAnchor0_value as Position | undefined))
        if (this._offset_flag)
            component.offset((this._offset0_value as Position | Edges | LocalizedEdges | undefined))
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as Dimension | undefined))
        if (this._fontStyle_flag)
            component.fontStyle((this._fontStyle0_value as FontStyle | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as int32 | FontWeight | string | undefined))
        if (this._fontFamily_flag)
            component.fontFamily((this._fontFamily0_value as string | Resource | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._iconColor_flag)
            component.iconColor((this._iconColor0_value as ResourceColor | undefined))
        if (this._backgroundColor_flag)
            component.backgroundColor((this._backgroundColor0_value as ResourceColor | undefined))
        if (this._borderStyle_flag)
            component.borderStyle((this._borderStyle0_value as BorderStyle | undefined))
        if (this._borderWidth_flag)
            component.borderWidth((this._borderWidth0_value as Dimension | undefined))
        if (this._borderColor_flag)
            component.borderColor((this._borderColor0_value as ResourceColor | undefined))
        if (this._borderRadius_flag)
            component.borderRadius((this._borderRadius0_value as Dimension | BorderRadiuses | undefined))
        if (this._padding_flag)
            component.padding((this._padding0_value as Padding | Dimension | undefined))
        if (this._textIconSpace_flag)
            component.textIconSpace((this._textIconSpace0_value as Dimension | undefined))
        if (this._key_flag)
            component.key((this._key0_value as string | undefined))
        if (this._width_flag)
            component.width((this._width0_value as Length | undefined))
        if (this._height_flag)
            component.height((this._height0_value as Length | undefined))
        if (this._size_flag)
            component.size((this._size0_value as SizeOptions | undefined))
        if (this._constraintSize_flag)
            component.constraintSize((this._constraintSize0_value as ConstraintSizeOptions | undefined))
        if (this._align_flag)
            component.align((this._align0_value as Alignment | undefined))
        if (this._alignRules_flag)
            component.alignRules((this._alignRules0_value as LocalizedAlignRuleOptions | undefined))
        if (this._id_flag)
            component.id((this._id0_value as string | undefined))
        if (this._chainMode_flag)
            component.chainMode((this._chainMode0_value as Axis | undefined), (this._chainMode1_value as ChainStyle | undefined))
        if (this._minFontScale_flag)
            component.minFontScale((this._minFontScale0_value as double | Resource | undefined))
        if (this._maxFontScale_flag)
            component.maxFontScale((this._maxFontScale0_value as double | Resource | undefined))
        if (this._maxLines_flag)
            component.maxLines((this._maxLines0_value as int32 | undefined))
        if (this._minFontSize_flag)
            component.minFontSize((this._minFontSize0_value as double | string | Resource | undefined))
        if (this._maxFontSize_flag)
            component.maxFontSize((this._maxFontSize0_value as double | string | Resource | undefined))
        if (this._heightAdaptivePolicy_flag)
            component.heightAdaptivePolicy((this._heightAdaptivePolicy0_value as TextHeightAdaptivePolicy | undefined))
        if (this._enabled_flag)
            component.enabled((this._enabled0_value as boolean | undefined))
    }
    public iconSize(value: Dimension | undefined): this {
        this._iconSize_flag = true
        this._iconSize0_value = value
        return this
    }
    public layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        this._layoutDirection_flag = true
        this._layoutDirection0_value = value
        return this
    }
    public position(value: Position | undefined): this {
        this._position_flag = true
        this._position0_value = value
        return this
    }
    public markAnchor(value: Position | undefined): this {
        this._markAnchor_flag = true
        this._markAnchor0_value = value
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges | undefined): this {
        this._offset_flag = true
        this._offset0_value = value
        return this
    }
    public fontSize(value: Dimension | undefined): this {
        this._fontSize_flag = true
        this._fontSize0_value = value
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        this._fontStyle_flag = true
        this._fontStyle0_value = value
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = value
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        this._fontFamily_flag = true
        this._fontFamily0_value = value
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public iconColor(value: ResourceColor | undefined): this {
        this._iconColor_flag = true
        this._iconColor0_value = value
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        this._backgroundColor_flag = true
        this._backgroundColor0_value = value
        return this
    }
    public borderStyle(value: BorderStyle | undefined): this {
        this._borderStyle_flag = true
        this._borderStyle0_value = value
        return this
    }
    public borderWidth(value: Dimension | undefined): this {
        this._borderWidth_flag = true
        this._borderWidth0_value = value
        return this
    }
    public borderColor(value: ResourceColor | undefined): this {
        this._borderColor_flag = true
        this._borderColor0_value = value
        return this
    }
    public borderRadius(radius: Dimension | BorderRadiuses | undefined): this {
        this._borderRadius_flag = true
        this._borderRadius0_value = radius
        return this
    }
    public padding(value: Padding | Dimension | undefined): this {
        this._padding_flag = true
        this._padding0_value = value
        return this
    }
    public textIconSpace(value: Dimension | undefined): this {
        this._textIconSpace_flag = true
        this._textIconSpace0_value = value
        return this
    }
    public key(value: string | undefined): this {
        this._key_flag = true
        this._key0_value = value
        return this
    }
    public width(value: Length | undefined): this {
        this._width_flag = true
        this._width0_value = value
        return this
    }
    public height(value: Length | undefined): this {
        this._height_flag = true
        this._height0_value = value
        return this
    }
    public size(value: SizeOptions | undefined): this {
        this._size_flag = true
        this._size0_value = value
        return this
    }
    public constraintSize(value: ConstraintSizeOptions | undefined): this {
        this._constraintSize_flag = true
        this._constraintSize0_value = value
        return this
    }
    public align(alignType: Alignment | undefined): this {
        this._align_flag = true
        this._align0_value = alignType
        return this
    }
    public alignRules(alignRule: LocalizedAlignRuleOptions | undefined): this {
        this._alignRules_flag = true
        this._alignRules0_value = alignRule
        return this
    }
    public id(description: string | undefined): this {
        this._id_flag = true
        this._id0_value = description
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        this._chainMode_flag = true
        this._chainMode0_value = direction
        this._chainMode1_value = style
        return this
    }
    public minFontScale(scale: double | Resource | undefined): this {
        this._minFontScale_flag = true
        this._minFontScale0_value = scale
        return this
    }
    public maxFontScale(scale: double | Resource | undefined): this {
        this._maxFontScale_flag = true
        this._maxFontScale0_value = scale
        return this
    }
    public maxLines(line: int32 | undefined): this {
        this._maxLines_flag = true
        this._maxLines0_value = line
        return this
    }
    public minFontSize(minSize: double | string | Resource | undefined): this {
        this._minFontSize_flag = true
        this._minFontSize0_value = minSize
        return this
    }
    public maxFontSize(maxSize: double | string | Resource | undefined): this {
        this._maxFontSize_flag = true
        this._maxFontSize0_value = maxSize
        return this
    }
    public heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        this._heightAdaptivePolicy_flag = true
        this._heightAdaptivePolicy0_value = policy
        return this
    }
    public enabled(respond: boolean | undefined): this {
        this._enabled_flag = true
        this._enabled0_value = respond
        return this
    }
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
