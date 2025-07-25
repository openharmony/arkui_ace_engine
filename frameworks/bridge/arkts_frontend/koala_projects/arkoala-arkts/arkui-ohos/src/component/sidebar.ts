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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Callback_Boolean_Void } from "./navigation"
import { Length, Dimension, PX, VP, FP, LPX, Percentage, ResourceColor } from "./units"
import { Callback_Opt_Boolean_Void } from "./checkbox"
import { Resource } from "global/resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { PixelMap } from "./arkui-pixelmap"

export interface DividerStyle {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
export class ArkSideBarContainerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSideBarContainerPeer {
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
    showSideBarAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_showSideBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    controlButtonAttribute(value: ButtonStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeButtonStyle(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_controlButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showControlButtonAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_showControlButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sideBarWidth0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sideBarWidth1Attribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minSideBarWidth0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minSideBarWidth1Attribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxSideBarWidth0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxSideBarWidth1Attribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoHideAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_autoHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sideBarPositionAttribute(value: SideBarPosition | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SideBarPosition)
            thisSerializer.writeInt32(TypeChecker.SideBarPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: DividerStyle | null | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyleSidebar(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minContentWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_showSideBarAttribute(callback: ((select: boolean | undefined) => void)): void {
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
export type SideBarContainerInterface = (type?: SideBarContainerType) => SideBarContainerAttribute;
export interface SideBarContainerAttribute extends CommonMethod {
    showSideBar(value: boolean | undefined): this
    controlButton(value: ButtonStyle | undefined): this
    showControlButton(value: boolean | undefined): this
    onChange(value: ((isVisible: boolean) => void) | undefined): this
    sideBarWidth(value: number | undefined): this
    minSideBarWidth(value: number | undefined): this
    maxSideBarWidth(value: number | undefined): this
    autoHide(value: boolean | undefined): this
    sideBarPosition(value: SideBarPosition | undefined): this
    divider(value: DividerStyle | null | undefined): this
    minContentWidth(value: Dimension | undefined): this
    _onChangeEvent_showSideBar(callback: ((select: boolean | undefined) => void)): void
}
export class ArkSideBarContainerStyle extends ArkCommonMethodStyle implements SideBarContainerAttribute {
    showSideBar_value?: boolean | undefined
    controlButton_value?: ButtonStyle | undefined
    showControlButton_value?: boolean | undefined
    onChange_value?: ((isVisible: boolean) => void) | undefined
    sideBarWidth_value?: number | undefined
    minSideBarWidth_value?: number | undefined
    maxSideBarWidth_value?: number | undefined
    autoHide_value?: boolean | undefined
    sideBarPosition_value?: SideBarPosition | undefined
    divider_value?: DividerStyle | null | undefined
    minContentWidth_value?: Dimension | undefined
    public showSideBar(value: boolean | undefined): this {
        return this
    }
    public controlButton(value: ButtonStyle | undefined): this {
        return this
    }
    public showControlButton(value: boolean | undefined): this {
        return this
    }
    public onChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public sideBarWidth(value: number | undefined): this {
        return this
    }
    public minSideBarWidth(value: number | undefined): this {
        return this
    }
    public maxSideBarWidth(value: number | undefined): this {
        return this
    }
    public autoHide(value: boolean | undefined): this {
        return this
    }
    public sideBarPosition(value: SideBarPosition | undefined): this {
        return this
    }
    public divider(value: DividerStyle | null | undefined): this {
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        return this
    }
    public _onChangeEvent_showSideBar(callback: ((select: boolean | undefined) => void)): void {
        throw new Error("Unimplmented")
        }
}
export class ArkSideBarContainerComponent extends ArkCommonMethodComponent implements SideBarContainerAttribute {
    getPeer(): ArkSideBarContainerPeer {
        return (this.peer as ArkSideBarContainerPeer)
    }
    public setSideBarContainerOptions(type?: SideBarContainerType): this {
        if (this.checkPriority("setSideBarContainerOptions")) {
            const type_casted = type as (SideBarContainerType | undefined)
            this.getPeer()?.setSideBarContainerOptionsAttribute(type_casted)
            return this
        }
        return this
    }
    public showSideBar(value: boolean | undefined): this {
        if (this.checkPriority("showSideBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.showSideBarAttribute(value_casted)
            return this
        }
        return this
    }
    public controlButton(value: ButtonStyle | undefined): this {
        if (this.checkPriority("controlButton")) {
            const value_casted = value as (ButtonStyle | undefined)
            this.getPeer()?.controlButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public showControlButton(value: boolean | undefined): this {
        if (this.checkPriority("showControlButton")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.showControlButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public sideBarWidth(value: number | undefined): this {
        if (this.checkPriority("sideBarWidth")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.sideBarWidth0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | undefined)
                this.getPeer()?.sideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public minSideBarWidth(value: number | undefined): this {
        if (this.checkPriority("minSideBarWidth")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.minSideBarWidth0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | undefined)
                this.getPeer()?.minSideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public maxSideBarWidth(value: number | undefined): this {
        if (this.checkPriority("maxSideBarWidth")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.maxSideBarWidth0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | undefined)
                this.getPeer()?.maxSideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public autoHide(value: boolean | undefined): this {
        if (this.checkPriority("autoHide")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.autoHideAttribute(value_casted)
            return this
        }
        return this
    }
    public sideBarPosition(value: SideBarPosition | undefined): this {
        if (this.checkPriority("sideBarPosition")) {
            const value_casted = value as (SideBarPosition | undefined)
            this.getPeer()?.sideBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: DividerStyle | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerStyle | null | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.minContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_showSideBar(callback: ((select: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_showSideBar")) {
            const callback_casted = callback as (((select: boolean | undefined) => void))
            this.getPeer()?._onChangeEvent_showSideBarAttribute(callback_casted)
            return
        }
        return
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function SideBarContainer(
    /** @memo */
    style: ((attributes: SideBarContainerAttribute) => void) | undefined,
    type?: SideBarContainerType,
    /** @memo */
    content_?: (() => void) | undefined,
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
