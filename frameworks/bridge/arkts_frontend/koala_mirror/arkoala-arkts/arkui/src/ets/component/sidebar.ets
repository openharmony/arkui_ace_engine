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
import { DividerStyle_serializer, ArkCommonMethodPeer, CommonMethod, DividerStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Length, Dimension } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { image, image_PixelMap_serializer } from "./../generated/ohos.multimedia.image"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8((type_type).toChar())
        if ((type_type) != (RuntimeType.UNDEFINED)) {
            const type_value  = (type as SideBarContainerType)
            thisSerializer.writeInt32(TypeChecker.SideBarContainerType_ToNumeric(type_value))
        }
        ArkUIGeneratedNativeModule._SideBarContainerInterface_setSideBarContainerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowSideBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setShowSideBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlButtonAttribute(value: ButtonStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ButtonStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setControlButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowControlButtonAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setShowControlButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSideBarWidth0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setSideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinSideBarWidth0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMinSideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxSideBarWidth0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMaxSideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSideBarWidth1Attribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinSideBarWidth1Attribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMinSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxSideBarWidth1Attribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMaxSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoHideAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setAutoHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSideBarPositionAttribute(value: SideBarPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SideBarPosition)
            thisSerializer.writeInt32(TypeChecker.SideBarPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setSideBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DividerStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinContentWidthAttribute(value: Dimension | undefined): void {
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
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMinContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_showSideBarAttribute(callback_: ((showSideBar: boolean | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_set_onChangeEvent_showSideBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    shown: string | image.PixelMap | Resource;
    hidden: string | image.PixelMap | Resource;
    switching?: string | image.PixelMap | Resource;
}
export interface ButtonStyle {
    left?: number;
    top?: number;
    width?: number;
    height?: number;
    icons?: ButtonIconOptions;
}
export interface SideBarContainerAttribute extends CommonMethod {
    showSideBar(value: boolean | undefined): this {
        throw new Error("Unimplemented method showSideBar")
    }
    controlButton(value: ButtonStyle | undefined): this {
        throw new Error("Unimplemented method controlButton")
    }
    showControlButton(value: boolean | undefined): this {
        throw new Error("Unimplemented method showControlButton")
    }
    onChange(value: ((value: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    sideBarWidth(value: number | undefined): this {
        throw new Error("Unimplemented method sideBarWidth")
    }
    minSideBarWidth(value: number | undefined): this {
        throw new Error("Unimplemented method minSideBarWidth")
    }
    maxSideBarWidth(value: number | undefined): this {
        throw new Error("Unimplemented method maxSideBarWidth")
    }
    sideBarWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method sideBarWidth")
    }
    minSideBarWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method minSideBarWidth")
    }
    maxSideBarWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method maxSideBarWidth")
    }
    autoHide(value: boolean | undefined): this {
        throw new Error("Unimplemented method autoHide")
    }
    sideBarPosition(value: SideBarPosition | undefined): this {
        throw new Error("Unimplemented method sideBarPosition")
    }
    divider(value: DividerStyle | undefined): this {
        throw new Error("Unimplemented method divider")
    }
    minContentWidth(value: Dimension | undefined): this {
        throw new Error("Unimplemented method minContentWidth")
    }
    _onChangeEvent_showSideBar(callback_: ((showSideBar: boolean | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_showSideBar")
    }
    attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSideBarContainerStyle extends ArkCommonMethodStyle implements SideBarContainerAttribute {
    showSideBar_value?: boolean | undefined
    controlButton_value?: ButtonStyle | undefined
    showControlButton_value?: boolean | undefined
    onChange_value?: ((value: boolean) => void) | undefined
    sideBarWidth_value?: number | undefined
    minSideBarWidth_value?: number | undefined
    maxSideBarWidth_value?: number | undefined
    autoHide_value?: boolean | undefined
    sideBarPosition_value?: SideBarPosition | undefined
    divider_value?: DividerStyle | undefined
    minContentWidth_value?: Dimension | undefined
    attributeModifier_value?: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined
    public showSideBar(value: boolean | undefined): this {
        return this
    }
    public controlButton(value: ButtonStyle | undefined): this {
        return this
    }
    public showControlButton(value: boolean | undefined): this {
        return this
    }
    public onChange(value: ((value: boolean) => void) | undefined): this {
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
    public sideBarWidth(value: Length | undefined): this {
        return this
    }
    public minSideBarWidth(value: Length | undefined): this {
        return this
    }
    public maxSideBarWidth(value: Length | undefined): this {
        return this
    }
    public autoHide(value: boolean | undefined): this {
        return this
    }
    public sideBarPosition(value: SideBarPosition | undefined): this {
        return this
    }
    public divider(value: DividerStyle | undefined): this {
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        return this
    }
    public _onChangeEvent_showSideBar(callback_: ((showSideBar: boolean | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SideBarContainerAttribute): void {
        super.apply(target)
        if (this.showSideBar_value !== undefined)
            target.showSideBar(this.showSideBar_value!)
        if (this.controlButton_value !== undefined)
            target.controlButton(this.controlButton_value!)
        if (this.showControlButton_value !== undefined)
            target.showControlButton(this.showControlButton_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.sideBarWidth_value !== undefined)
            target.sideBarWidth(this.sideBarWidth_value!)
        if (this.minSideBarWidth_value !== undefined)
            target.minSideBarWidth(this.minSideBarWidth_value!)
        if (this.maxSideBarWidth_value !== undefined)
            target.maxSideBarWidth(this.maxSideBarWidth_value!)
        if (this.autoHide_value !== undefined)
            target.autoHide(this.autoHide_value!)
        if (this.sideBarPosition_value !== undefined)
            target.sideBarPosition(this.sideBarPosition_value!)
        if (this.divider_value !== undefined)
            target.divider(this.divider_value!)
        if (this.minContentWidth_value !== undefined)
            target.minContentWidth(this.minContentWidth_value!)
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
            this.getPeer()?.setShowSideBarAttribute(value_casted)
            return this
        }
        return this
    }
    public controlButton(value: ButtonStyle | undefined): this {
        if (this.checkPriority("controlButton")) {
            const value_casted = value as (ButtonStyle | undefined)
            this.getPeer()?.setControlButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public showControlButton(value: boolean | undefined): this {
        if (this.checkPriority("showControlButton")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setShowControlButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value: boolean) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: boolean) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public sideBarWidth(value: number | undefined): this {
        if (this.checkPriority("sideBarWidth")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setSideBarWidth0Attribute(value_casted)
            return this
        }
        return this
    }
    public minSideBarWidth(value: number | undefined): this {
        if (this.checkPriority("minSideBarWidth")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMinSideBarWidth0Attribute(value_casted)
            return this
        }
        return this
    }
    public maxSideBarWidth(value: number | undefined): this {
        if (this.checkPriority("maxSideBarWidth")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMaxSideBarWidth0Attribute(value_casted)
            return this
        }
        return this
    }
    public sideBarWidth(value: Length | undefined): this {
        if (this.checkPriority("sideBarWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setSideBarWidth1Attribute(value_casted)
            return this
        }
        return this
    }
    public minSideBarWidth(value: Length | undefined): this {
        if (this.checkPriority("minSideBarWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setMinSideBarWidth1Attribute(value_casted)
            return this
        }
        return this
    }
    public maxSideBarWidth(value: Length | undefined): this {
        if (this.checkPriority("maxSideBarWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setMaxSideBarWidth1Attribute(value_casted)
            return this
        }
        return this
    }
    public autoHide(value: boolean | undefined): this {
        if (this.checkPriority("autoHide")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoHideAttribute(value_casted)
            return this
        }
        return this
    }
    public sideBarPosition(value: SideBarPosition | undefined): this {
        if (this.checkPriority("sideBarPosition")) {
            const value_casted = value as (SideBarPosition | undefined)
            this.getPeer()?.setSideBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: DividerStyle | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerStyle | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setMinContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_showSideBar(callback_: ((showSideBar: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_showSideBar")) {
            const callback__casted = callback_ as (((showSideBar: boolean | undefined) => void))
            this.getPeer()?.set_onChangeEvent_showSideBarAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSideBarContainerStyle(receiver: SideBarContainerAttribute, modifier: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSideBarContainerStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("SideBarContainer")
// export function SideBarContainer(
//     type?: SideBarContainerType,
//     @memo
//     content_?: () => void,
// ): SideBarContainerAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function SideBarContainer(
    @memo
    style: ((attributes: SideBarContainerAttribute) => void) | undefined,
    type?: SideBarContainerType,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSideBarContainerComponent>((): ArkSideBarContainerComponent => {
        return new ArkSideBarContainerComponent()
    })
    NodeAttach<ArkSideBarContainerPeer>((): ArkSideBarContainerPeer => ArkSideBarContainerPeer.create(receiver), (_: ArkSideBarContainerPeer): void => {
        receiver.setSideBarContainerOptions(type)
        style?.(receiver)
        withSideBarContainerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkSideBarContainerSet extends ArkCommonMethodSet implements SideBarContainerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _showSideBar_flag?: boolean
    _showSideBar0_value?: boolean | undefined
    _controlButton_flag?: boolean
    _controlButton0_value?: ButtonStyle | undefined
    _showControlButton_flag?: boolean
    _showControlButton0_value?: boolean | undefined
    _onChange_flag?: boolean
    _onChange0_value?: ((value: boolean) => void) | undefined
    _sideBarWidth_flag?: boolean
    _sideBarWidth0_value?: Length | undefined
    _minSideBarWidth_flag?: boolean
    _minSideBarWidth0_value?: Length | undefined
    _maxSideBarWidth_flag?: boolean
    _maxSideBarWidth0_value?: Length | undefined
    _autoHide_flag?: boolean
    _autoHide0_value?: boolean | undefined
    _sideBarPosition_flag?: boolean
    _sideBarPosition0_value?: SideBarPosition | undefined
    _divider_flag?: boolean
    _divider0_value?: DividerStyle | undefined
    _minContentWidth_flag?: boolean
    _minContentWidth0_value?: Dimension | undefined
    __onChangeEvent_showSideBar_flag?: boolean
    __onChangeEvent_showSideBar0_value?: ((showSideBar: boolean | undefined) => void)
    applyModifierPatch(component: SideBarContainerAttribute): void {
        if (this._showSideBar_flag)
            component.showSideBar((this._showSideBar0_value as boolean | undefined))
        if (this._controlButton_flag)
            component.controlButton((this._controlButton0_value as ButtonStyle | undefined))
        if (this._showControlButton_flag)
            component.showControlButton((this._showControlButton0_value as boolean | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as ((value: boolean) => void) | undefined))
        if (this._sideBarWidth_flag)
            component.sideBarWidth((this._sideBarWidth0_value as Length | undefined))
        if (this._minSideBarWidth_flag)
            component.minSideBarWidth((this._minSideBarWidth0_value as Length | undefined))
        if (this._maxSideBarWidth_flag)
            component.maxSideBarWidth((this._maxSideBarWidth0_value as Length | undefined))
        if (this._autoHide_flag)
            component.autoHide((this._autoHide0_value as boolean | undefined))
        if (this._sideBarPosition_flag)
            component.sideBarPosition((this._sideBarPosition0_value as SideBarPosition | undefined))
        if (this._divider_flag)
            component.divider((this._divider0_value as DividerStyle | undefined))
        if (this._minContentWidth_flag)
            component.minContentWidth((this._minContentWidth0_value as Dimension | undefined))
    }
    public showSideBar(value: boolean | undefined): this {
        this._showSideBar_flag = true
        this._showSideBar0_value = value
        return this
    }
    public controlButton(value: ButtonStyle | undefined): this {
        this._controlButton_flag = true
        this._controlButton0_value = value
        return this
    }
    public showControlButton(value: boolean | undefined): this {
        this._showControlButton_flag = true
        this._showControlButton0_value = value
        return this
    }
    public onChange(value: ((value: boolean) => void) | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public sideBarWidth(value: Length | undefined): this {
        this._sideBarWidth_flag = true
        this._sideBarWidth0_value = value
        return this
    }
    public minSideBarWidth(value: Length | undefined): this {
        this._minSideBarWidth_flag = true
        this._minSideBarWidth0_value = value
        return this
    }
    public maxSideBarWidth(value: Length | undefined): this {
        this._maxSideBarWidth_flag = true
        this._maxSideBarWidth0_value = value
        return this
    }
    public autoHide(value: boolean | undefined): this {
        this._autoHide_flag = true
        this._autoHide0_value = value
        return this
    }
    public sideBarPosition(value: SideBarPosition | undefined): this {
        this._sideBarPosition_flag = true
        this._sideBarPosition0_value = value
        return this
    }
    public divider(value: DividerStyle | undefined): this {
        this._divider_flag = true
        this._divider0_value = value
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        this._minContentWidth_flag = true
        this._minContentWidth0_value = value
        return this
    }
    public _onChangeEvent_showSideBar(callback_: ((showSideBar: boolean | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ButtonIconOptions_serializer {
    public static write(buffer: SerializerBase, value: ButtonIconOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_shown  = value.shown
        let value_shown_type : int32 = RuntimeType.UNDEFINED
        value_shown_type = runtimeType(value_shown)
        if (RuntimeType.STRING == value_shown_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_shown_0  = value_shown as string
            valueSerializer.writeString(value_shown_0)
        }
        else if (TypeChecker.isimage_PixelMap(value_shown, false, false)) {
            valueSerializer.writeInt8((1).toChar())
            const value_shown_1  = value_shown as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, value_shown_1)
        }
        else if (TypeChecker.isResource(value_shown, false, false, false, false, false)) {
            valueSerializer.writeInt8((2).toChar())
            const value_shown_2  = value_shown as Resource
            Resource_serializer.write(valueSerializer, value_shown_2)
        }
        const value_hidden  = value.hidden
        let value_hidden_type : int32 = RuntimeType.UNDEFINED
        value_hidden_type = runtimeType(value_hidden)
        if (RuntimeType.STRING == value_hidden_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_hidden_0  = value_hidden as string
            valueSerializer.writeString(value_hidden_0)
        }
        else if (TypeChecker.isimage_PixelMap(value_hidden, false, false)) {
            valueSerializer.writeInt8((1).toChar())
            const value_hidden_1  = value_hidden as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, value_hidden_1)
        }
        else if (TypeChecker.isResource(value_hidden, false, false, false, false, false)) {
            valueSerializer.writeInt8((2).toChar())
            const value_hidden_2  = value_hidden as Resource
            Resource_serializer.write(valueSerializer, value_hidden_2)
        }
        const value_switching  = value.switching
        let value_switching_type : int32 = RuntimeType.UNDEFINED
        value_switching_type = runtimeType(value_switching)
        valueSerializer.writeInt8((value_switching_type).toChar())
        if ((value_switching_type) != (RuntimeType.UNDEFINED)) {
            const value_switching_value  = value_switching!
            let value_switching_value_type : int32 = RuntimeType.UNDEFINED
            value_switching_value_type = runtimeType(value_switching_value)
            if (RuntimeType.STRING == value_switching_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_switching_value_0  = value_switching_value as string
                valueSerializer.writeString(value_switching_value_0)
            }
            else if (TypeChecker.isimage_PixelMap(value_switching_value, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_switching_value_1  = value_switching_value as image.PixelMap
                image_PixelMap_serializer.write(valueSerializer, value_switching_value_1)
            }
            else if (TypeChecker.isResource(value_switching_value, false, false, false, false, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value_switching_value_2  = value_switching_value as Resource
                Resource_serializer.write(valueSerializer, value_switching_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): ButtonIconOptions {
        let valueDeserializer : DeserializerBase = buffer
        const shown_buf_selector : int32 = valueDeserializer.readInt8()
        let shown_buf : string | image.PixelMap | Resource | undefined
        if (shown_buf_selector == (0).toChar()) {
            shown_buf = (valueDeserializer.readString() as string)
        }
        else if (shown_buf_selector == (1).toChar()) {
            shown_buf = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        }
        else if (shown_buf_selector == (2).toChar()) {
            shown_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for shown_buf has to be chosen through deserialisation.")
        }
        const shown_result : string | image.PixelMap | Resource = (shown_buf as string | image.PixelMap | Resource)
        const hidden_buf_selector : int32 = valueDeserializer.readInt8()
        let hidden_buf : string | image.PixelMap | Resource | undefined
        if (hidden_buf_selector == (0).toChar()) {
            hidden_buf = (valueDeserializer.readString() as string)
        }
        else if (hidden_buf_selector == (1).toChar()) {
            hidden_buf = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        }
        else if (hidden_buf_selector == (2).toChar()) {
            hidden_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for hidden_buf has to be chosen through deserialisation.")
        }
        const hidden_result : string | image.PixelMap | Resource = (hidden_buf as string | image.PixelMap | Resource)
        const switching_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let switching_buf : string | image.PixelMap | Resource | undefined
        if ((switching_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const switching_buf__selector : int32 = valueDeserializer.readInt8()
            let switching_buf_ : string | image.PixelMap | Resource | undefined
            if (switching_buf__selector == (0).toChar()) {
                switching_buf_ = (valueDeserializer.readString() as string)
            }
            else if (switching_buf__selector == (1).toChar()) {
                switching_buf_ = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
            }
            else if (switching_buf__selector == (2).toChar()) {
                switching_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for switching_buf_ has to be chosen through deserialisation.")
            }
            switching_buf = (switching_buf_ as string | image.PixelMap | Resource)
        }
        const switching_result : string | image.PixelMap | Resource | undefined = switching_buf
        let value : ButtonIconOptions = ({shown: shown_result, hidden: hidden_result, switching: switching_result} as ButtonIconOptions)
        return value
    }
}
export class ButtonStyle_serializer {
    public static write(buffer: SerializerBase, value: ButtonStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = value_left!
            valueSerializer.writeNumber(value_left_value)
        }
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            valueSerializer.writeNumber(value_top_value)
        }
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            valueSerializer.writeNumber(value_width_value)
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            valueSerializer.writeNumber(value_height_value)
        }
        const value_icons  = value.icons
        let value_icons_type : int32 = RuntimeType.UNDEFINED
        value_icons_type = runtimeType(value_icons)
        valueSerializer.writeInt8((value_icons_type).toChar())
        if ((value_icons_type) != (RuntimeType.UNDEFINED)) {
            const value_icons_value  = value_icons!
            ButtonIconOptions_serializer.write(valueSerializer, value_icons_value)
        }
    }
    public static read(buffer: DeserializerBase): ButtonStyle {
        let valueDeserializer : DeserializerBase = buffer
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : number | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            left_buf = (valueDeserializer.readNumber() as number)
        }
        const left_result : number | undefined = left_buf
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : number | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            top_buf = (valueDeserializer.readNumber() as number)
        }
        const top_result : number | undefined = top_buf
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : number | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            width_buf = (valueDeserializer.readNumber() as number)
        }
        const width_result : number | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : number | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            height_buf = (valueDeserializer.readNumber() as number)
        }
        const height_result : number | undefined = height_buf
        const icons_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icons_buf : ButtonIconOptions | undefined
        if ((icons_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            icons_buf = ButtonIconOptions_serializer.read(valueDeserializer)
        }
        const icons_result : ButtonIconOptions | undefined = icons_buf
        let value : ButtonStyle = ({left: left_result, top: top_result, width: width_result, height: height_result, icons: icons_result} as ButtonStyle)
        return value
    }
}
