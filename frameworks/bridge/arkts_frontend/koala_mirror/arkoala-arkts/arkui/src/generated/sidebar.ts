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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Callback_Boolean_Void } from "./navigation"
import { Length, Dimension } from "./units"
import { DividerStyle } from "./tabs"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { PixelMap } from "./arkui-pixelmap"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSideBarContainerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSideBarContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SideBarContainer_construct(peerId, flags)
        const _peer  = new ArkSideBarContainerPeer(_peerPtr, peerId, "SideBarContainer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSideBarContainerOptionsAttribute(type?: SideBarContainerType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as SideBarContainerType)
            thisSerializer.writeInt32(TypeChecker.SideBarContainerType_ToNumeric(type_value))
        }
        ArkUIGeneratedNativeModule._SideBarContainerInterface_setSideBarContainerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showSideBarAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_showSideBar(this.peer.ptr, value ? 1 : 0)
    }
    controlButtonAttribute(value: ButtonStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeButtonStyle(value)
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_controlButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showControlButtonAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_showControlButton(this.peer.ptr, value ? 1 : 0)
    }
    onChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sideBarWidth0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth0(this.peer.ptr, value)
    }
    sideBarWidth1Attribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minSideBarWidth0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth0(this.peer.ptr, value)
    }
    minSideBarWidth1Attribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxSideBarWidth0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth0(this.peer.ptr, value)
    }
    maxSideBarWidth1Attribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoHideAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_autoHide(this.peer.ptr, value ? 1 : 0)
    }
    sideBarPositionAttribute(value: SideBarPosition): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarPosition(this.peer.ptr, TypeChecker.SideBarPosition_ToNumeric(value))
    }
    dividerAttribute(value: DividerStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyle(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minContentWidthAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_showSideBarAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SideBarContainerAttribute__onChangeEvent_showSideBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SideBarContainerType {
    EMBED = 0,
    Embed = 0,
    OVERLAY = 1,
    Overlay = 1,
    AUTO = 2
}
export enum SideBarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1
}
export interface ButtonIconOptions {
    shown: string | PixelMap | Resource;
    hidden: string | PixelMap | Resource;
    switching?: string | PixelMap | Resource;
}
export interface ButtonStyle {
    left?: number;
    top?: number;
    width?: number;
    height?: number;
    icons?: ButtonIconOptions;
}

export interface SideBarContainerAttribute extends CommonMethod {
    showSideBar(value: boolean): this
    controlButton(value: ButtonStyle): this
    showControlButton(value: boolean): this
    onChange(value: ((isVisible: boolean) => void)): this
    sideBarWidth(value: number | Length): this
    minSideBarWidth(value: number | Length): this
    maxSideBarWidth(value: number | Length): this
    autoHide(value: boolean): this
    sideBarPosition(value: SideBarPosition): this
    divider(value: DividerStyle | undefined): this
    minContentWidth(value: Dimension): this
    _onChangeEvent_showSideBar(callback: ((isVisible: boolean) => void)): void
    attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UISideBarContainerAttribute extends UICommonMethod {
    /** @memo */
    showSideBar(value: boolean): this
    /** @memo */
    controlButton(value: ButtonStyle): this
    /** @memo */
    showControlButton(value: boolean): this
    /** @memo */
    onChange(value: ((isVisible: boolean) => void)): this
    /** @memo */
    sideBarWidth(value: number | Length): this
    /** @memo */
    minSideBarWidth(value: number | Length): this
    /** @memo */
    maxSideBarWidth(value: number | Length): this
    /** @memo */
    autoHide(value: boolean): this
    /** @memo */
    sideBarPosition(value: SideBarPosition): this
    /** @memo */
    divider(value: DividerStyle | undefined): this
    /** @memo */
    minContentWidth(value: Dimension): this
    /** @memo */
    _onChangeEvent_showSideBar(callback: ((isVisible: boolean) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSideBarContainerStyle extends ArkCommonMethodStyle implements SideBarContainerAttribute {
    showSideBar_value?: boolean
    controlButton_value?: ButtonStyle
    showControlButton_value?: boolean
    onChange_value?: ((isVisible: boolean) => void)
    sideBarWidth_value?: number
    minSideBarWidth_value?: number
    maxSideBarWidth_value?: number
    autoHide_value?: boolean
    sideBarPosition_value?: SideBarPosition
    divider_value?: DividerStyle | undefined
    minContentWidth_value?: Dimension
    public showSideBar(value: boolean): this {
        return this
    }
    public controlButton(value: ButtonStyle): this {
        return this
    }
    public showControlButton(value: boolean): this {
        return this
    }
    public onChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public sideBarWidth(value: number | Length): this {
        return this
    }
    public minSideBarWidth(value: number | Length): this {
        return this
    }
    public maxSideBarWidth(value: number | Length): this {
        return this
    }
    public autoHide(value: boolean): this {
        return this
    }
    public sideBarPosition(value: SideBarPosition): this {
        return this
    }
    public divider(value: DividerStyle | undefined): this {
        return this
    }
    public minContentWidth(value: Dimension): this {
        return this
    }
    public _onChangeEvent_showSideBar(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkSideBarContainerComponent extends ArkCommonMethodComponent implements UISideBarContainerAttribute {
    getPeer(): ArkSideBarContainerPeer {
        return (this.peer as ArkSideBarContainerPeer)
    }
    /** @memo */
    public setSideBarContainerOptions(type?: SideBarContainerType): this {
        if (this.checkPriority("setSideBarContainerOptions")) {
            const type_casted = type as (SideBarContainerType | undefined)
            this.getPeer()?.setSideBarContainerOptionsAttribute(type_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showSideBar(value: boolean): this {
        if (this.checkPriority("showSideBar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showSideBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public controlButton(value: ButtonStyle): this {
        if (this.checkPriority("controlButton")) {
            const value_casted = value as (ButtonStyle)
            this.getPeer()?.controlButtonAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showControlButton(value: boolean): this {
        if (this.checkPriority("showControlButton")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showControlButtonAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sideBarWidth(value: number | Length): this {
        if (this.checkPriority("sideBarWidth")) {
            const value_type = runtimeType(value)
            if (RuntimeType.NUMBER == value_type) {
                const value_casted = value as (number)
                this.getPeer()?.sideBarWidth0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
                const value_casted = value as (Length)
                this.getPeer()?.sideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public minSideBarWidth(value: number | Length): this {
        if (this.checkPriority("minSideBarWidth")) {
            const value_type = runtimeType(value)
            if (RuntimeType.NUMBER == value_type) {
                const value_casted = value as (number)
                this.getPeer()?.minSideBarWidth0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
                const value_casted = value as (Length)
                this.getPeer()?.minSideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public maxSideBarWidth(value: number | Length): this {
        if (this.checkPriority("maxSideBarWidth")) {
            const value_type = runtimeType(value)
            if (RuntimeType.NUMBER == value_type) {
                const value_casted = value as (number)
                this.getPeer()?.maxSideBarWidth0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
                const value_casted = value as (Length)
                this.getPeer()?.maxSideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public autoHide(value: boolean): this {
        if (this.checkPriority("autoHide")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoHideAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sideBarPosition(value: SideBarPosition): this {
        if (this.checkPriority("sideBarPosition")) {
            const value_casted = value as (SideBarPosition)
            this.getPeer()?.sideBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public divider(value: DividerStyle | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerStyle | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minContentWidth(value: Dimension): this {
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.minContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_showSideBar(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_showSideBar")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_showSideBarAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkSideBarContainer(
    /** @memo */
    style: ((attributes: UISideBarContainerAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    type?: SideBarContainerType,
): void {
    const receiver = remember(() => {
        return new ArkSideBarContainerComponent()
    })
    NodeAttach<ArkSideBarContainerPeer>((): ArkSideBarContainerPeer => ArkSideBarContainerPeer.create(receiver), (_: ArkSideBarContainerPeer) => {
        receiver.setSideBarContainerOptions(type)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
