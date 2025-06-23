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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Dimension, Position, LocalizedEdges, ResourceColor, BorderRadiuses, Padding, Length, SizeOptions, ConstraintSizeOptions, PX, VP, FP, LPX, Percentage, Edges } from "./units"
import { FontStyle, FontWeight, BorderStyle, Alignment, TextHeightAdaptivePolicy, Axis, Color } from "./enums"
import { Resource } from "global.resource"
import { AlignRuleOption, LocalizedAlignRuleOptions, ChainStyle } from "./common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkSecurityComponentMethodPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSecurityComponentMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SecurityComponentMethod_construct(peerId, flags)
        const _peer  = new ArkSecurityComponentMethodPeer(_peerPtr, peerId, "SecurityComponentMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    iconSizeAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_iconSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutDirectionAttribute(value: SecurityComponentLayoutDirection | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SecurityComponentLayoutDirection)
            thisSerializer.writeInt32(TypeChecker.SecurityComponentLayoutDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_layoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    positionAttribute(value: Position | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePosition(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_position(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    markAnchorAttribute(value: Position | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePosition(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_markAnchor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offsetAttribute(value: Position | Edges | LocalizedEdges | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPosition(value_value, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Position
                thisSerializer.writePosition(value_value_0)
            }
            else if (TypeChecker.isEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Edges
                thisSerializer.writeEdges(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdges
                thisSerializer.writeLocalizedEdges(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_offset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    iconColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_iconColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_backgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderStyleAttribute(value: BorderStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BorderStyle)
            thisSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderRadius0Attribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderRadius0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderRadius1Attribute(value: Dimension | BorderRadiuses | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Dimension
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as BorderRadiuses
                thisSerializer.writeBorderRadiuses(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderRadius1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    paddingAttribute(value: Padding | Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Padding
                const value_value_0_top  = value_value_0.top
                let value_value_0_top_type : int32 = RuntimeType.UNDEFINED
                value_value_0_top_type = runtimeType(value_value_0_top)
                thisSerializer.writeInt8(value_value_0_top_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_top_type)) {
                    const value_value_0_top_value  = value_value_0_top!
                    thisSerializer.writeLength(value_value_0_top_value)
                }
                const value_value_0_right  = value_value_0.right
                let value_value_0_right_type : int32 = RuntimeType.UNDEFINED
                value_value_0_right_type = runtimeType(value_value_0_right)
                thisSerializer.writeInt8(value_value_0_right_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_right_type)) {
                    const value_value_0_right_value  = value_value_0_right!
                    thisSerializer.writeLength(value_value_0_right_value)
                }
                const value_value_0_bottom  = value_value_0.bottom
                let value_value_0_bottom_type : int32 = RuntimeType.UNDEFINED
                value_value_0_bottom_type = runtimeType(value_value_0_bottom)
                thisSerializer.writeInt8(value_value_0_bottom_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_bottom_type)) {
                    const value_value_0_bottom_value  = value_value_0_bottom!
                    thisSerializer.writeLength(value_value_0_bottom_value)
                }
                const value_value_0_left  = value_value_0.left
                let value_value_0_left_type : int32 = RuntimeType.UNDEFINED
                value_value_0_left_type = runtimeType(value_value_0_left)
                thisSerializer.writeInt8(value_value_0_left_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_left_type)) {
                    const value_value_0_left_value  = value_value_0_left!
                    thisSerializer.writeLength(value_value_0_left_value)
                }
            }
            else if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Dimension
                thisSerializer.writeLength(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_padding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textIconSpaceAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_textIconSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_key(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    widthAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_width(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_height(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSizeOptions(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_size(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    constraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeConstraintSizeOptions(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_constraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignAttribute(value: Alignment | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Alignment)
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_align(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules0Attribute(value: AlignRuleOption | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeAlignRuleOption(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_alignRules0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules1Attribute(value: LocalizedAlignRuleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLocalizedAlignRuleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_alignRules1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    idAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_id(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_minFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_maxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLinesAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_maxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_maxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_heightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enabledAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_enabled(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    chainModeAttribute(direction: Axis | undefined, style: ChainStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8(direction_type as int32)
        if ((RuntimeType.UNDEFINED) != (direction_type)) {
            const direction_value  = (direction as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(direction_value))
        }
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type as int32)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as ChainStyle)
            thisSerializer.writeInt32(TypeChecker.ChainStyle_ToNumeric(style_value))
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_chainMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    fontWeight(value: number | FontWeight | string | undefined): this
    fontFamily(value: string | Resource | undefined): this
    fontColor(value: ResourceColor | undefined): this
    iconColor(value: ResourceColor | undefined): this
    backgroundColor(value: ResourceColor | undefined): this
    borderStyle(value: BorderStyle | undefined): this
    borderWidth(value: Dimension | undefined): this
    borderColor(value: ResourceColor | undefined): this
    borderRadius(value: Dimension | undefined | Dimension | BorderRadiuses | undefined): this
    padding(value: Padding | Dimension | undefined): this
    textIconSpace(value: Dimension | undefined): this
    key(value: string | undefined): this
    width(value: Length | undefined): this
    height(value: Length | undefined): this
    size(value: SizeOptions | undefined): this
    constraintSize(value: ConstraintSizeOptions | undefined): this
    align(value: Alignment | undefined): this
    alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this
    id(value: string | undefined): this
    minFontScale(value: number | Resource | undefined): this
    maxFontScale(value: number | Resource | undefined): this
    maxLines(value: number | undefined): this
    minFontSize(value: number | string | Resource | undefined): this
    maxFontSize(value: number | string | Resource | undefined): this
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this
    enabled(value: boolean | undefined): this
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this
}
export class ArkSecurityComponentMethodStyle implements SecurityComponentMethod {
    iconSize_value?: Dimension | undefined
    layoutDirection_value?: SecurityComponentLayoutDirection | undefined
    position_value?: Position | undefined
    markAnchor_value?: Position | undefined
    offset_value?: Position | Edges | LocalizedEdges | undefined
    fontSize_value?: Dimension | undefined
    fontStyle_value?: FontStyle | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    fontFamily_value?: string | Resource | undefined
    fontColor_value?: ResourceColor | undefined
    iconColor_value?: ResourceColor | undefined
    backgroundColor_value?: ResourceColor | undefined
    borderStyle_value?: BorderStyle | undefined
    borderWidth_value?: Dimension | undefined
    borderColor_value?: ResourceColor | undefined
    borderRadius_value?: Dimension | undefined
    padding_value?: Padding | Dimension | undefined
    textIconSpace_value?: Dimension | undefined
    key_value?: string | undefined
    width_value?: Length | undefined
    height_value?: Length | undefined
    size_value?: SizeOptions | undefined
    constraintSize_value?: ConstraintSizeOptions | undefined
    align_value?: Alignment | undefined
    alignRules_value?: AlignRuleOption | undefined
    id_value?: string | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    maxLines_value?: number | undefined
    minFontSize_value?: number | string | Resource | undefined
    maxFontSize_value?: number | string | Resource | undefined
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy | undefined
    enabled_value?: boolean | undefined
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
    public fontWeight(value: number | FontWeight | string | undefined): this {
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
    public borderRadius(value: Dimension | undefined | Dimension | BorderRadiuses | undefined): this {
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
    public align(value: Alignment | undefined): this {
        return this
    }
    public alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this {
        return this
    }
    public id(value: string | undefined): this {
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        return this
    }
    public maxLines(value: number | undefined): this {
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        return this
    }
    public enabled(value: boolean | undefined): this {
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        return this
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
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
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
    public borderRadius(value: Dimension | undefined | Dimension | BorderRadiuses | undefined): this {
        if (this.checkPriority("borderRadius")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | undefined)
                this.getPeer()?.borderRadius0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | BorderRadiuses | undefined)
                this.getPeer()?.borderRadius1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
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
    public align(value: Alignment | undefined): this {
        if (this.checkPriority("align")) {
            const value_casted = value as (Alignment | undefined)
            this.getPeer()?.alignAttribute(value_casted)
            return this
        }
        return this
    }
    public alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this {
        if (this.checkPriority("alignRules")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (AlignRuleOption | undefined)
                this.getPeer()?.alignRules0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (LocalizedAlignRuleOptions | undefined)
                this.getPeer()?.alignRules1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public id(value: string | undefined): this {
        if (this.checkPriority("id")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.idAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.minFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.maxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLines(value: number | undefined): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.maxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.maxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.heightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    public enabled(value: boolean | undefined): this {
        if (this.checkPriority("enabled")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enabledAttribute(value_casted)
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
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
