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

import { int32, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "./../../ComponentBase"
import { PeerNode } from "./../../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions, PX, VP, FP, LPX, Percentage } from "./../ArkUnitsInterfaces"
import { SecurityComponentLayoutDirection } from "./../ArkSecurityComponentInterfaces"
import { FontStyle, FontWeight, BorderStyle, Color } from "./../ArkEnumsInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
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
        ArkUIGeneratedNativeModule._SecurityComponentMethod_iconSize(this.peer.ptr, value)
    }
    layoutDirectionAttribute(value: SecurityComponentLayoutDirection): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_layoutDirection(this.peer.ptr, value.valueOf())
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Position
            thisSerializer.writePosition(value_0)
        }
        else if (TypeChecker.isEdges(value, true, false, true, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Edges
            thisSerializer.writeEdges(value_1)
        }
        else if (TypeChecker.isLocalizedEdges(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedEdges
            thisSerializer.writeLocalizedEdges(value_2)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_offset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Dimension): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontSize(this.peer.ptr, value)
    }
    fontStyleAttribute(value: FontStyle): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_fontStyle(this.peer.ptr, value.valueOf())
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(value_1.valueOf())
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_backgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderStyleAttribute(value: BorderStyle): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderStyle(this.peer.ptr, value.valueOf())
    }
    borderWidthAttribute(value: Dimension): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderWidth(this.peer.ptr, value)
    }
    borderColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderRadiusAttribute(value: Dimension): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_borderRadius(this.peer.ptr, value)
    }
    paddingAttribute(value: Padding | Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPadding(value, false, false, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Padding
            const value_0_top  = value_0.top
            let value_0_top_type : int32 = RuntimeType.UNDEFINED
            value_0_top_type = runtimeType(value_0_top)
            thisSerializer.writeInt8(value_0_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_top_type)) {
                const value_0_top_value  = value_0_top!
                thisSerializer.writeLength(value_0_top_value)
            }
            const value_0_right  = value_0.right
            let value_0_right_type : int32 = RuntimeType.UNDEFINED
            value_0_right_type = runtimeType(value_0_right)
            thisSerializer.writeInt8(value_0_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_right_type)) {
                const value_0_right_value  = value_0_right!
                thisSerializer.writeLength(value_0_right_value)
            }
            const value_0_bottom  = value_0.bottom
            let value_0_bottom_type : int32 = RuntimeType.UNDEFINED
            value_0_bottom_type = runtimeType(value_0_bottom)
            thisSerializer.writeInt8(value_0_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_bottom_type)) {
                const value_0_bottom_value  = value_0_bottom!
                thisSerializer.writeLength(value_0_bottom_value)
            }
            const value_0_left  = value_0.left
            let value_0_left_type : int32 = RuntimeType.UNDEFINED
            value_0_left_type = runtimeType(value_0_left)
            thisSerializer.writeInt8(value_0_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_left_type)) {
                const value_0_left_value  = value_0_left!
                thisSerializer.writeLength(value_0_left_value)
            }
        }
        else if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isResource(value, false, false, false, false, false)))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Dimension
            thisSerializer.writeLength(value_1)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_padding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textIconSpaceAttribute(value: Dimension): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_textIconSpace(this.peer.ptr, value)
    }
    keyAttribute(value: string): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_key(this.peer.ptr, value)
    }
    widthAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_width(this.peer.ptr, value)
    }
    heightAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._SecurityComponentMethod_height(this.peer.ptr, value)
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
export interface ArkSecurityComponentMethodAttributes {
    iconSize?: Dimension
    layoutDirection?: SecurityComponentLayoutDirection
    position?: Position
    markAnchor?: Position
    offset?: Position | Edges | LocalizedEdges
    fontSize?: Dimension
    fontStyle?: FontStyle
    fontWeight?: number | FontWeight | string
    fontFamily?: string | Resource
    fontColor?: ResourceColor
    iconColor?: ResourceColor
    backgroundColor?: ResourceColor
    borderStyle?: BorderStyle
    borderWidth?: Dimension
    borderColor?: ResourceColor
    borderRadius?: Dimension
    padding?: Padding | Dimension
    textIconSpace?: Dimension
    key?: string
    width?: Length
    height?: Length
    size?: SizeOptions
    constraintSize?: ConstraintSizeOptions
}
