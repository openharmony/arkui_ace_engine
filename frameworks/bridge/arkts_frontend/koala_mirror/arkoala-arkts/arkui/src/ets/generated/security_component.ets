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
import { Dimension, Position, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions } from "./units"
import { Edges } from "./arkui-graphics"
import { FontStyle } from "./arkui-graphics-text"
import { FontWeight, BorderStyle, Color } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
    iconSizeAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_iconSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutDirectionAttribute(value: SecurityComponentLayoutDirection): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_layoutDirection(this.peer.ptr, TypeChecker.SecurityComponentLayoutDirection_ToNumeric(value))
    }
    positionAttribute(value: Position): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(value)
        ArkUIGeneratedNativeModule._SecurityComponentMethod_position(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    markAnchorAttribute(value: Position): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(value)
        ArkUIGeneratedNativeModule._SecurityComponentMethod_markAnchor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offsetAttribute(value: Position | Edges | LocalizedEdges): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPosition(value, false, false)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Position
            thisSerializer.writePosition(value_0)
        }
        else if (TypeChecker.isEdges(value, true, false, true, false)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Edges
            thisSerializer.writeEdges(value_1)
        }
        else if (TypeChecker.isLocalizedEdges(value, true, false, true, false)) {
            thisSerializer.writeInt8(2)
            const value_2  = value as LocalizedEdges
            thisSerializer.writeLocalizedEdges(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_offset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontStyle(this.peer.ptr, TypeChecker.FontStyle_ToNumeric(value))
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_1))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    iconColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_iconColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_backgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderStyleAttribute(value: BorderStyle): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderStyle(this.peer.ptr, TypeChecker.BorderStyle_ToNumeric(value))
    }
    borderWidthAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderRadiusAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    paddingAttribute(value: Padding | Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPadding(value, false, false, false, false)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Padding
            const value_0_top  = value_0.top
            let value_0_top_type : int32 = RuntimeType.UNDEFINED
            value_0_top_type = runtimeType(value_0_top)
            thisSerializer.writeInt8(value_0_top_type)
            if ((RuntimeType.UNDEFINED) != (value_0_top_type)) {
                const value_0_top_value  = value_0_top!
                let value_0_top_value_type : int32 = RuntimeType.UNDEFINED
                value_0_top_value_type = runtimeType(value_0_top_value)
                if (RuntimeType.STRING == value_0_top_value_type) {
                    thisSerializer.writeInt8(0)
                    const value_0_top_value_0  = value_0_top_value as string
                    thisSerializer.writeString(value_0_top_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_top_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_0_top_value_1  = value_0_top_value as number
                    thisSerializer.writeNumber(value_0_top_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_top_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_0_top_value_2  = value_0_top_value as Resource
                    thisSerializer.writeResource(value_0_top_value_2)
                }
            }
            const value_0_right  = value_0.right
            let value_0_right_type : int32 = RuntimeType.UNDEFINED
            value_0_right_type = runtimeType(value_0_right)
            thisSerializer.writeInt8(value_0_right_type)
            if ((RuntimeType.UNDEFINED) != (value_0_right_type)) {
                const value_0_right_value  = value_0_right!
                let value_0_right_value_type : int32 = RuntimeType.UNDEFINED
                value_0_right_value_type = runtimeType(value_0_right_value)
                if (RuntimeType.STRING == value_0_right_value_type) {
                    thisSerializer.writeInt8(0)
                    const value_0_right_value_0  = value_0_right_value as string
                    thisSerializer.writeString(value_0_right_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_right_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_0_right_value_1  = value_0_right_value as number
                    thisSerializer.writeNumber(value_0_right_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_right_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_0_right_value_2  = value_0_right_value as Resource
                    thisSerializer.writeResource(value_0_right_value_2)
                }
            }
            const value_0_bottom  = value_0.bottom
            let value_0_bottom_type : int32 = RuntimeType.UNDEFINED
            value_0_bottom_type = runtimeType(value_0_bottom)
            thisSerializer.writeInt8(value_0_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_0_bottom_type)) {
                const value_0_bottom_value  = value_0_bottom!
                let value_0_bottom_value_type : int32 = RuntimeType.UNDEFINED
                value_0_bottom_value_type = runtimeType(value_0_bottom_value)
                if (RuntimeType.STRING == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(0)
                    const value_0_bottom_value_0  = value_0_bottom_value as string
                    thisSerializer.writeString(value_0_bottom_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_0_bottom_value_1  = value_0_bottom_value as number
                    thisSerializer.writeNumber(value_0_bottom_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_0_bottom_value_2  = value_0_bottom_value as Resource
                    thisSerializer.writeResource(value_0_bottom_value_2)
                }
            }
            const value_0_left  = value_0.left
            let value_0_left_type : int32 = RuntimeType.UNDEFINED
            value_0_left_type = runtimeType(value_0_left)
            thisSerializer.writeInt8(value_0_left_type)
            if ((RuntimeType.UNDEFINED) != (value_0_left_type)) {
                const value_0_left_value  = value_0_left!
                let value_0_left_value_type : int32 = RuntimeType.UNDEFINED
                value_0_left_value_type = runtimeType(value_0_left_value)
                if (RuntimeType.STRING == value_0_left_value_type) {
                    thisSerializer.writeInt8(0)
                    const value_0_left_value_0  = value_0_left_value as string
                    thisSerializer.writeString(value_0_left_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_left_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_0_left_value_1  = value_0_left_value as number
                    thisSerializer.writeNumber(value_0_left_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_left_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_0_left_value_2  = value_0_left_value as Resource
                    thisSerializer.writeResource(value_0_left_value_2)
                }
            }
        }
        else if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Dimension
            let value_1_type : int32 = RuntimeType.UNDEFINED
            value_1_type = runtimeType(value_1)
            if (RuntimeType.STRING == value_1_type) {
                thisSerializer.writeInt8(0)
                const value_1_0  = value_1 as string
                thisSerializer.writeString(value_1_0)
            }
            else if (RuntimeType.NUMBER == value_1_type) {
                thisSerializer.writeInt8(1)
                const value_1_1  = value_1 as number
                thisSerializer.writeNumber(value_1_1)
            }
            else if (RuntimeType.OBJECT == value_1_type) {
                thisSerializer.writeInt8(2)
                const value_1_2  = value_1 as Resource
                thisSerializer.writeResource(value_1_2)
            }
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_padding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textIconSpaceAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_textIconSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyAttribute(value: string): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_key(this.peer.ptr, value)
    }
    widthAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_width(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_height(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sizeAttribute(value: SizeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(value)
        ArkUIGeneratedNativeModule._SecurityComponentMethod_size(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    constraintSizeAttribute(value: ConstraintSizeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeConstraintSizeOptions(value)
        ArkUIGeneratedNativeModule._SecurityComponentMethod_constraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SecurityComponentLayoutDirection {
    HORIZONTAL = 0,
    VERTICAL = 1
}
export interface SecurityComponentMethod {
    iconSize(value: Dimension): this
    layoutDirection(value: SecurityComponentLayoutDirection): this
    position(value: Position): this
    markAnchor(value: Position): this
    offset(value: Position | Edges | LocalizedEdges): this
    fontSize(value: Dimension): this
    fontStyle(value: FontStyle): this
    fontWeight(value: number | FontWeight | string): this
    fontFamily(value: string | Resource): this
    fontColor(value: ResourceColor): this
    iconColor(value: ResourceColor): this
    backgroundColor(value: ResourceColor): this
    borderStyle(value: BorderStyle): this
    borderWidth(value: Dimension): this
    borderColor(value: ResourceColor): this
    borderRadius(value: Dimension): this
    padding(value: Padding | Dimension): this
    textIconSpace(value: Dimension): this
    key(value: string): this
    width(value: Length): this
    height(value: Length): this
    size(value: SizeOptions): this
    constraintSize(value: ConstraintSizeOptions): this
    attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this
}
export interface UISecurityComponentMethod {
    @memo
    iconSize(value: Dimension): this
    @memo
    layoutDirection(value: SecurityComponentLayoutDirection): this
    @memo
    position(value: Position): this
    @memo
    markAnchor(value: Position): this
    @memo
    offset(value: Position | Edges | LocalizedEdges): this
    @memo
    fontSize(value: Dimension): this
    @memo
    fontStyle(value: FontStyle): this
    @memo
    fontWeight(value: number | FontWeight | string): this
    @memo
    fontFamily(value: string | Resource): this
    @memo
    fontColor(value: ResourceColor): this
    @memo
    iconColor(value: ResourceColor): this
    @memo
    backgroundColor(value: ResourceColor): this
    @memo
    borderStyle(value: BorderStyle): this
    @memo
    borderWidth(value: Dimension): this
    @memo
    borderColor(value: ResourceColor): this
    @memo
    borderRadius(value: Dimension): this
    @memo
    padding(value: Padding | Dimension): this
    @memo
    textIconSpace(value: Dimension): this
    @memo
    key(value: string): this
    @memo
    width(value: Length): this
    @memo
    height(value: Length): this
    @memo
    size(value: SizeOptions): this
    @memo
    constraintSize(value: ConstraintSizeOptions): this
    @memo
    attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this
}
export class ArkSecurityComponentMethodStyle implements SecurityComponentMethod {
    iconSize_value?: Dimension
    layoutDirection_value?: SecurityComponentLayoutDirection
    position_value?: Position
    markAnchor_value?: Position
    offset_value?: Position | Edges | LocalizedEdges
    fontSize_value?: Dimension
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: string | Resource
    fontColor_value?: ResourceColor
    iconColor_value?: ResourceColor
    backgroundColor_value?: ResourceColor
    borderStyle_value?: BorderStyle
    borderWidth_value?: Dimension
    borderColor_value?: ResourceColor
    borderRadius_value?: Dimension
    padding_value?: Padding | Dimension
    textIconSpace_value?: Dimension
    key_value?: string
    width_value?: Length
    height_value?: Length
    size_value?: SizeOptions
    constraintSize_value?: ConstraintSizeOptions
    public iconSize(value: Dimension): this {
        return this
    }
    public layoutDirection(value: SecurityComponentLayoutDirection): this {
        return this
    }
    public position(value: Position): this {
        return this
    }
    public markAnchor(value: Position): this {
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges): this {
        return this
    }
    public fontSize(value: Dimension): this {
        return this
    }
    public fontStyle(value: FontStyle): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string): this {
        return this
    }
    public fontFamily(value: string | Resource): this {
        return this
    }
    public fontColor(value: ResourceColor): this {
        return this
    }
    public iconColor(value: ResourceColor): this {
        return this
    }
    public backgroundColor(value: ResourceColor): this {
        return this
    }
    public borderStyle(value: BorderStyle): this {
        return this
    }
    public borderWidth(value: Dimension): this {
        return this
    }
    public borderColor(value: ResourceColor): this {
        return this
    }
    public borderRadius(value: Dimension): this {
        return this
    }
    public padding(value: Padding | Dimension): this {
        return this
    }
    public textIconSpace(value: Dimension): this {
        return this
    }
    public key(value: string): this {
        return this
    }
    public width(value: Length): this {
        return this
    }
    public height(value: Length): this {
        return this
    }
    public size(value: SizeOptions): this {
        return this
    }
    public constraintSize(value: ConstraintSizeOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkSecurityComponentMethodComponent extends ComponentBase implements UISecurityComponentMethod {
    getPeer(): ArkSecurityComponentMethodPeer {
        return (this.peer as ArkSecurityComponentMethodPeer)
    }
    @memo
    public iconSize(value: Dimension): this {
        if (this.checkPriority("iconSize")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.iconSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public layoutDirection(value: SecurityComponentLayoutDirection): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (SecurityComponentLayoutDirection)
            this.getPeer()?.layoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public position(value: Position): this {
        if (this.checkPriority("position")) {
            const value_casted = value as (Position)
            this.getPeer()?.positionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public markAnchor(value: Position): this {
        if (this.checkPriority("markAnchor")) {
            const value_casted = value as (Position)
            this.getPeer()?.markAnchorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public offset(value: Position | Edges | LocalizedEdges): this {
        if (this.checkPriority("offset")) {
            const value_casted = value as (Position | Edges | LocalizedEdges)
            this.getPeer()?.offsetAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontSize(value: Dimension): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontStyle(value: FontStyle): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontFamily(value: string | Resource): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public iconColor(value: ResourceColor): this {
        if (this.checkPriority("iconColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.iconColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public backgroundColor(value: ResourceColor): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public borderStyle(value: BorderStyle): this {
        if (this.checkPriority("borderStyle")) {
            const value_casted = value as (BorderStyle)
            this.getPeer()?.borderStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public borderWidth(value: Dimension): this {
        if (this.checkPriority("borderWidth")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.borderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public borderColor(value: ResourceColor): this {
        if (this.checkPriority("borderColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.borderColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public borderRadius(value: Dimension): this {
        if (this.checkPriority("borderRadius")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.borderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public padding(value: Padding | Dimension): this {
        if (this.checkPriority("padding")) {
            const value_casted = value as (Padding | Dimension)
            this.getPeer()?.paddingAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textIconSpace(value: Dimension): this {
        if (this.checkPriority("textIconSpace")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.textIconSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public key(value: string): this {
        if (this.checkPriority("key")) {
            const value_casted = value as (string)
            this.getPeer()?.keyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public width(value: Length): this {
        if (this.checkPriority("width")) {
            const value_casted = value as (Length)
            this.getPeer()?.widthAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public height(value: Length): this {
        if (this.checkPriority("height")) {
            const value_casted = value as (Length)
            this.getPeer()?.heightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public size(value: SizeOptions): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public constraintSize(value: ConstraintSizeOptions): this {
        if (this.checkPriority("constraintSize")) {
            const value_casted = value as (ConstraintSizeOptions)
            this.getPeer()?.constraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
