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
import { Bindable_Boolean_serializer, Bindable_Number_serializer, DividerStyle_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, DividerStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { Resource_serializer, Resource } from "./../generated/resource"
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
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkSideBarContainerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSideBarContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SideBarContainer_construct(peerId, flags)
        const _peer  = new ArkSideBarContainerPeer(_peerPtr, peerId, 'SideBarContainer', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSideBarContainerOptionsAttribute(type?: SideBarContainerType): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (type !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const typeTmpValue  = (type as SideBarContainerType)
            thisSerializer.writeInt32(TypeChecker.SideBarContainerType_ToNumeric(typeTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerInterface_setSideBarContainerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowSideBarAttribute(value: boolean | Bindable<boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<boolean>) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<boolean>
                Bindable_Boolean_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setShowSideBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlButtonAttribute(value: ButtonStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ButtonStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setControlButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowControlButtonAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setShowControlButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSideBarWidth0Attribute(value: number | Bindable<number> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<number>) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<number>
                Bindable_Number_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setSideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinSideBarWidth0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMinSideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxSideBarWidth0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMaxSideBarWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSideBarWidth1Attribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinSideBarWidth1Attribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMinSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxSideBarWidth1Attribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMaxSideBarWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoHideAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setAutoHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSideBarPositionAttribute(value: SideBarPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SideBarPosition)
            thisSerializer.writeInt32(TypeChecker.SideBarPosition_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setSideBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DividerStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinContentWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMinContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    showSideBar(value: boolean | Bindable<boolean> | undefined): this {
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
    sideBarWidth(value: number | Bindable<number> | undefined): this {
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
    attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSideBarContainerStyle extends ArkCommonMethodStyle implements SideBarContainerAttribute {
    showSideBar_value?: boolean | Bindable<boolean> | undefined
    controlButton_value?: ButtonStyle | undefined
    showControlButton_value?: boolean | undefined
    onChange_value?: ((value: boolean) => void) | undefined
    sideBarWidth_value?: number | Bindable<number> | undefined
    minSideBarWidth_value?: number | undefined
    maxSideBarWidth_value?: number | undefined
    autoHide_value?: boolean | undefined
    sideBarPosition_value?: SideBarPosition | undefined
    divider_value?: DividerStyle | undefined
    minContentWidth_value?: Dimension | undefined
    attributeModifier_value?: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined
    public showSideBar(value: boolean | Bindable<boolean> | undefined): this {
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
    public sideBarWidth(value: number | Bindable<number> | undefined): this {
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
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public showSideBar(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority("showSideBar")) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
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
    public sideBarWidth(value: number | Bindable<number> | undefined): this {
        if (this.checkPriority("sideBarWidth")) {
            const value_casted = value as (number | Bindable<number> | undefined)
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
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class SideBarContainerModifier extends CommonMethodModifier implements SideBarContainerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _showSideBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showSideBar_0_0value?: boolean | Bindable<boolean> | undefined
    _controlButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _controlButton_0_0value?: ButtonStyle | undefined
    _showControlButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showControlButton_0_0value?: boolean | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value: boolean) => void) | undefined
    _sideBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideBarWidth_0_0value?: number | Bindable<number> | undefined
    _minSideBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minSideBarWidth_0_0value?: number | undefined
    _maxSideBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxSideBarWidth_0_0value?: number | undefined
    _sideBarWidth_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideBarWidth_1_0value?: Length | undefined
    _minSideBarWidth_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minSideBarWidth_1_0value?: Length | undefined
    _maxSideBarWidth_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxSideBarWidth_1_0value?: Length | undefined
    _autoHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoHide_0_0value?: boolean | undefined
    _sideBarPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideBarPosition_0_0value?: SideBarPosition | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: DividerStyle | undefined
    _minContentWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minContentWidth_0_0value?: Dimension | undefined
    applyModifierPatch(peer: ArkSideBarContainerPeer): void {
        super.applyModifierPatch(peer)
        if (this._showSideBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showSideBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowSideBarAttribute((this._showSideBar_0_0value as boolean | Bindable<boolean> | undefined));
                    this._showSideBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showSideBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showSideBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowSideBarAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (this._controlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setControlButtonAttribute((this._controlButton_0_0value as ButtonStyle | undefined));
                    this._controlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controlButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setControlButtonAttribute((undefined as ButtonStyle | undefined));
                }
            }
        }
        if (this._showControlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showControlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowControlButtonAttribute((this._showControlButton_0_0value as boolean | undefined));
                    this._showControlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showControlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showControlButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowControlButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value: boolean) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value: boolean) => void) | undefined));
                }
            }
        }
        if (this._sideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSideBarWidth0Attribute((this._sideBarWidth_0_0value as number | Bindable<number> | undefined));
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSideBarWidth0Attribute((undefined as number | Bindable<number> | undefined));
                }
            }
        }
        if (this._minSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinSideBarWidth0Attribute((this._minSideBarWidth_0_0value as number | undefined));
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinSideBarWidth0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._maxSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxSideBarWidth0Attribute((this._maxSideBarWidth_0_0value as number | undefined));
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxSideBarWidth0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._sideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSideBarWidth1Attribute((this._sideBarWidth_1_0value as Length | undefined));
                    this._sideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideBarWidth_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSideBarWidth1Attribute((undefined as Length | undefined));
                }
            }
        }
        if (this._minSideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minSideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinSideBarWidth1Attribute((this._minSideBarWidth_1_0value as Length | undefined));
                    this._minSideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minSideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minSideBarWidth_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinSideBarWidth1Attribute((undefined as Length | undefined));
                }
            }
        }
        if (this._maxSideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxSideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxSideBarWidth1Attribute((this._maxSideBarWidth_1_0value as Length | undefined));
                    this._maxSideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxSideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxSideBarWidth_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxSideBarWidth1Attribute((undefined as Length | undefined));
                }
            }
        }
        if (this._autoHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoHideAttribute((this._autoHide_0_0value as boolean | undefined));
                    this._autoHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoHideAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._sideBarPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideBarPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSideBarPositionAttribute((this._sideBarPosition_0_0value as SideBarPosition | undefined));
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSideBarPositionAttribute((undefined as SideBarPosition | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDividerAttribute((this._divider_0_0value as DividerStyle | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDividerAttribute((undefined as DividerStyle | undefined));
                }
            }
        }
        if (this._minContentWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minContentWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinContentWidthAttribute((this._minContentWidth_0_0value as Dimension | undefined));
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinContentWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SideBarContainerModifier): void {
        super.mergeModifier(modifier)
        if (modifier._showSideBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showSideBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showSideBar(modifier._showSideBar_0_0value);
                    break;
                }
                default: {
                    this.showSideBar((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (modifier._controlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._controlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.controlButton(modifier._controlButton_0_0value);
                    break;
                }
                default: {
                    this.controlButton((undefined as ButtonStyle | undefined));
                }
            }
        }
        if (modifier._showControlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showControlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showControlButton(modifier._showControlButton_0_0value);
                    break;
                }
                default: {
                    this.showControlButton((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._sideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sideBarWidth(modifier._sideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.sideBarWidth((undefined as number | Bindable<number> | undefined));
                }
            }
        }
        if (modifier._minSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minSideBarWidth(modifier._minSideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.minSideBarWidth((undefined as number | undefined));
                }
            }
        }
        if (modifier._maxSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxSideBarWidth(modifier._maxSideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.maxSideBarWidth((undefined as number | undefined));
                }
            }
        }
        if (modifier._sideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sideBarWidth(modifier._sideBarWidth_1_0value);
                    break;
                }
                default: {
                    this.sideBarWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._minSideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minSideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minSideBarWidth(modifier._minSideBarWidth_1_0value);
                    break;
                }
                default: {
                    this.minSideBarWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._maxSideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxSideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxSideBarWidth(modifier._maxSideBarWidth_1_0value);
                    break;
                }
                default: {
                    this.maxSideBarWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._autoHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoHide(modifier._autoHide_0_0value);
                    break;
                }
                default: {
                    this.autoHide((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._sideBarPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sideBarPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sideBarPosition(modifier._sideBarPosition_0_0value);
                    break;
                }
                default: {
                    this.sideBarPosition((undefined as SideBarPosition | undefined));
                }
            }
        }
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerStyle | undefined));
                }
            }
        }
        if (modifier._minContentWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minContentWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minContentWidth(modifier._minContentWidth_0_0value);
                    break;
                }
                default: {
                    this.minContentWidth((undefined as Dimension | undefined));
                }
            }
        }
    }
    showSideBar(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._showSideBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._showSideBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._showSideBar_0_0value = value
        } else
        {
            this._showSideBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    controlButton(value: ButtonStyle | undefined): this {
        if (((this._controlButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._controlButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._controlButton_0_0value = value
        } else
        {
            this._controlButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    showControlButton(value: boolean | undefined): this {
        if (((this._showControlButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._showControlButton_0_0value) !== (value)))
        {
            this._showControlButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._showControlButton_0_0value = value
        } else
        {
            this._showControlButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value: boolean) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sideBarWidth(value: number | Bindable<number> | undefined): this {
        if (((this._sideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._sideBarWidth_0_0value = value
        } else
        {
            this._sideBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minSideBarWidth(value: number | undefined): this {
        if (((this._minSideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minSideBarWidth_0_0value) !== (value)))
        {
            this._minSideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._minSideBarWidth_0_0value = value
        } else
        {
            this._minSideBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxSideBarWidth(value: number | undefined): this {
        if (((this._maxSideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxSideBarWidth_0_0value) !== (value)))
        {
            this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxSideBarWidth_0_0value = value
        } else
        {
            this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sideBarWidth(value: Length | undefined): this {
        if (((this._sideBarWidth_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sideBarWidth_1_flag = AttributeUpdaterFlag.UPDATE
            this._sideBarWidth_1_0value = value
        } else
        {
            this._sideBarWidth_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minSideBarWidth(value: Length | undefined): this {
        if (((this._minSideBarWidth_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minSideBarWidth_1_flag = AttributeUpdaterFlag.UPDATE
            this._minSideBarWidth_1_0value = value
        } else
        {
            this._minSideBarWidth_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxSideBarWidth(value: Length | undefined): this {
        if (((this._maxSideBarWidth_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxSideBarWidth_1_flag = AttributeUpdaterFlag.UPDATE
            this._maxSideBarWidth_1_0value = value
        } else
        {
            this._maxSideBarWidth_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoHide(value: boolean | undefined): this {
        if (((this._autoHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoHide_0_0value) !== (value)))
        {
            this._autoHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoHide_0_0value = value
        } else
        {
            this._autoHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sideBarPosition(value: SideBarPosition | undefined): this {
        if (((this._sideBarPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sideBarPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._sideBarPosition_0_0value = value
        } else
        {
            this._sideBarPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: DividerStyle | undefined): this {
        if (((this._divider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE
            this._divider_0_0value = value
        } else
        {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minContentWidth(value: Dimension | undefined): this {
        if (((this._minContentWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minContentWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._minContentWidth_0_0value = value
        } else
        {
            this._minContentWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ButtonIconOptions_serializer {
    public static write(buffer: SerializerBase, value: ButtonIconOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForShown  = value.shown
        if (valueHolderForShown instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForShownForIdx0  = valueHolderForShown as string
            valueSerializer.writeString(valueHolderForShownForIdx0)
        } else if (valueHolderForShown instanceof image.PixelMap) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForShownForIdx1  = valueHolderForShown as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, valueHolderForShownForIdx1)
        } else if (valueHolderForShown instanceof Resource) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForShownForIdx2  = valueHolderForShown as Resource
            Resource_serializer.write(valueSerializer, valueHolderForShownForIdx2)
        }
        const valueHolderForHidden  = value.hidden
        if (valueHolderForHidden instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForHiddenForIdx0  = valueHolderForHidden as string
            valueSerializer.writeString(valueHolderForHiddenForIdx0)
        } else if (valueHolderForHidden instanceof image.PixelMap) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForHiddenForIdx1  = valueHolderForHidden as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, valueHolderForHiddenForIdx1)
        } else if (valueHolderForHidden instanceof Resource) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForHiddenForIdx2  = valueHolderForHidden as Resource
            Resource_serializer.write(valueSerializer, valueHolderForHiddenForIdx2)
        }
        const valueHolderForSwitching  = value.switching
        if (valueHolderForSwitching !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSwitchingTmpValue  = valueHolderForSwitching!
            if (valueHolderForSwitchingTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSwitchingTmpValueForIdx0  = valueHolderForSwitchingTmpValue as string
                valueSerializer.writeString(valueHolderForSwitchingTmpValueForIdx0)
            } else if (valueHolderForSwitchingTmpValue instanceof image.PixelMap) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForSwitchingTmpValueForIdx1  = valueHolderForSwitchingTmpValue as image.PixelMap
                image_PixelMap_serializer.write(valueSerializer, valueHolderForSwitchingTmpValueForIdx1)
            } else if (valueHolderForSwitchingTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForSwitchingTmpValueForIdx2  = valueHolderForSwitchingTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSwitchingTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ButtonIconOptions {
        let valueDeserializer : DeserializerBase = buffer
        const shownTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let shownTmpBuf : string | image.PixelMap | Resource | undefined
        if (shownTmpBufUnionSelector == (0).toChar()) {
            shownTmpBuf = (valueDeserializer.readString() as string)
        } else if (shownTmpBufUnionSelector == (1).toChar()) {
            shownTmpBuf = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        } else if (shownTmpBufUnionSelector == (2).toChar()) {
            shownTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for shownTmpBuf has to be chosen through deserialisation.")
        }
        const shownTmpResult : string | image.PixelMap | Resource = (shownTmpBuf as string | image.PixelMap | Resource)
        const hiddenTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let hiddenTmpBuf : string | image.PixelMap | Resource | undefined
        if (hiddenTmpBufUnionSelector == (0).toChar()) {
            hiddenTmpBuf = (valueDeserializer.readString() as string)
        } else if (hiddenTmpBufUnionSelector == (1).toChar()) {
            hiddenTmpBuf = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        } else if (hiddenTmpBufUnionSelector == (2).toChar()) {
            hiddenTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for hiddenTmpBuf has to be chosen through deserialisation.")
        }
        const hiddenTmpResult : string | image.PixelMap | Resource = (hiddenTmpBuf as string | image.PixelMap | Resource)
        const switchingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let switchingTmpBuf : string | image.PixelMap | Resource | undefined
        if ((switchingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const switchingTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let switchingTmpBuf_ : string | image.PixelMap | Resource | undefined
            if (switchingTmpBuf_UnionSelector == (0).toChar()) {
                switchingTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (switchingTmpBuf_UnionSelector == (1).toChar()) {
                switchingTmpBuf_ = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
            } else if (switchingTmpBuf_UnionSelector == (2).toChar()) {
                switchingTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for switchingTmpBuf_ has to be chosen through deserialisation.")
            }
            switchingTmpBuf = (switchingTmpBuf_ as string | image.PixelMap | Resource)
        }
        const switchingTmpResult : string | image.PixelMap | Resource | undefined = switchingTmpBuf
        let value : ButtonIconOptions = ({shown: shownTmpResult, hidden: hiddenTmpResult, switching: switchingTmpResult} as ButtonIconOptions)
        return value
    }
}
export class ButtonStyle_serializer {
    public static write(buffer: SerializerBase, value: ButtonStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            valueSerializer.writeNumber(valueHolderForLeftTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            valueSerializer.writeNumber(valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            valueSerializer.writeNumber(valueHolderForWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            valueSerializer.writeNumber(valueHolderForHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIcons  = value.icons
        if (valueHolderForIcons !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconsTmpValue  = valueHolderForIcons!
            ButtonIconOptions_serializer.write(valueSerializer, valueHolderForIconsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ButtonStyle {
        let valueDeserializer : DeserializerBase = buffer
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : number | undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            leftTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const leftTmpResult : number | undefined = leftTmpBuf
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : number | undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const topTmpResult : number | undefined = topTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : number | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            widthTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const widthTmpResult : number | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : number | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const heightTmpResult : number | undefined = heightTmpBuf
        const iconsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconsTmpBuf : ButtonIconOptions | undefined
        if ((iconsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            iconsTmpBuf = ButtonIconOptions_serializer.read(valueDeserializer)
        }
        const iconsTmpResult : ButtonIconOptions | undefined = iconsTmpBuf
        let value : ButtonStyle = ({left: leftTmpResult, top: topTmpResult, width: widthTmpResult, height: heightTmpResult, icons: iconsTmpResult} as ButtonStyle)
        return value
    }
}
