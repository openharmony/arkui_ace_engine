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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Bindable_Boolean_serializer, Bindable_Arkui_Component_Units_Length_serializer, DividerStyle_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, DividerStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Length, Dimension } from "./units"
import { Resource } from "global.resource"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { extractors, hookSideBarContainerAttributeModifier, AttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { default as image } from "@ohos.multimedia.image"
import { SideBarContainerModifier } from "./../SideBarContainerModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
export class ArkSideBarContainerPeer extends ArkCommonMethodPeer {
    attributeSet?: SideBarContainerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (type !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const typeTmpValue  = (type as SideBarContainerType)
            thisSerializer.writeInt32(typeTmpValue.valueOf())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<boolean>) {
                thisSerializer.writeInt8((1).toByte())
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
    setSideBarWidthAttribute(value: Length | Bindable<Length> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Length
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof Bindable<Length>) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<Length>
                Bindable_Arkui_Component_Units_Length_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setSideBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinSideBarWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMinSideBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxSideBarWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setMaxSideBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_setSideBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerStyle | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
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
    left?: double;
    top?: double;
    width?: double;
    height?: double;
    icons?: ButtonIconOptions;
}
export interface SideBarContainerAttribute extends CommonMethod {
    setSideBarContainerOptions(type?: SideBarContainerType): this {
        throw new Error("Unimplemented method setSideBarContainerOptions")
    }
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
    sideBarWidth(value: Length | Bindable<Length> | undefined): this {
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
    divider(value: DividerStyle | null | undefined): this {
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
    sideBarWidth_value?: Length | Bindable<Length> | undefined
    minSideBarWidth_value?: Length | undefined
    maxSideBarWidth_value?: Length | undefined
    autoHide_value?: boolean | undefined
    sideBarPosition_value?: SideBarPosition | undefined
    divider_value?: DividerStyle | null | undefined
    minContentWidth_value?: Dimension | undefined
    setSideBarContainerOptions(type?: SideBarContainerType): this {
        return this
    }
    showSideBar(value: boolean | Bindable<boolean> | undefined): this {
        return this
    }
    controlButton(value: ButtonStyle | undefined): this {
        return this
    }
    showControlButton(value: boolean | undefined): this {
        return this
    }
    onChange(value: ((value: boolean) => void) | undefined): this {
        return this
    }
    sideBarWidth(value: Length | Bindable<Length> | undefined): this {
        return this
    }
    minSideBarWidth(value: Length | undefined): this {
        return this
    }
    maxSideBarWidth(value: Length | undefined): this {
        return this
    }
    autoHide(value: boolean | undefined): this {
        return this
    }
    sideBarPosition(value: SideBarPosition | undefined): this {
        return this
    }
    divider(value: DividerStyle | null | undefined): this {
        return this
    }
    minContentWidth(value: Dimension | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkSideBarContainerComponent extends ArkCommonMethodComponent implements SideBarContainerAttribute {
    getPeer(): ArkSideBarContainerPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkSideBarContainerPeer)
    }
    public setSideBarContainerOptions(type?: SideBarContainerType): this {
        if (this.checkPriority("setSideBarContainerOptions")) {
            const type_casted = type as (SideBarContainerType | undefined)
            this.getPeer()?.setSideBarContainerOptionsAttribute(type_casted)
            this.applyOptionsFinish('SideBarContainerAttribute');
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
    public sideBarWidth(value: Length | Bindable<Length> | undefined): this {
        if (this.checkPriority("sideBarWidth")) {
            const value_casted = value as (Length | Bindable<Length> | undefined)
            this.getPeer()?.setSideBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public minSideBarWidth(value: Length | undefined): this {
        if (this.checkPriority("minSideBarWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setMinSideBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public maxSideBarWidth(value: Length | undefined): this {
        if (this.checkPriority("maxSideBarWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setMaxSideBarWidthAttribute(value_casted)
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
    public divider(value: DividerStyle | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerStyle | null | undefined)
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
        ModifierStateManager.INSTANCE.scope(() => {
          hookSideBarContainerAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function SideBarContainerImpl(
    @memo
    style: ((attributes: SideBarContainerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSideBarContainerComponent>((): ArkSideBarContainerComponent => {
        return new ArkSideBarContainerComponent()
    })
    NodeAttach<ArkSideBarContainerPeer>((): ArkSideBarContainerPeer => ArkSideBarContainerPeer.create(receiver), (peer: ArkSideBarContainerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class ButtonIconOptions_serializer {
    public static write(buffer: SerializerBase, value: ButtonIconOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForShown  = value.shown
        if (valueHolderForShown instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForShownForIdx0  = valueHolderForShown as string
            valueSerializer.writeString(valueHolderForShownForIdx0)
        } else if (valueHolderForShown instanceof image.PixelMap) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForShownForIdx1  = valueHolderForShown as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, valueHolderForShownForIdx1)
        } else if (valueHolderForShown instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForShownForIdx2  = valueHolderForShown as Resource
            Resource_serializer.write(valueSerializer, valueHolderForShownForIdx2)
        }
        const valueHolderForHidden  = value.hidden
        if (valueHolderForHidden instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForHiddenForIdx0  = valueHolderForHidden as string
            valueSerializer.writeString(valueHolderForHiddenForIdx0)
        } else if (valueHolderForHidden instanceof image.PixelMap) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForHiddenForIdx1  = valueHolderForHidden as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, valueHolderForHiddenForIdx1)
        } else if (valueHolderForHidden instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForHiddenForIdx2  = valueHolderForHidden as Resource
            Resource_serializer.write(valueSerializer, valueHolderForHiddenForIdx2)
        }
        const valueHolderForSwitching  = value.switching
        if (valueHolderForSwitching !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSwitchingTmpValue  = valueHolderForSwitching!
            if (valueHolderForSwitchingTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSwitchingTmpValueForIdx0  = valueHolderForSwitchingTmpValue as string
                valueSerializer.writeString(valueHolderForSwitchingTmpValueForIdx0)
            } else if (valueHolderForSwitchingTmpValue instanceof image.PixelMap) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSwitchingTmpValueForIdx1  = valueHolderForSwitchingTmpValue as image.PixelMap
                image_PixelMap_serializer.write(valueSerializer, valueHolderForSwitchingTmpValueForIdx1)
            } else if (valueHolderForSwitchingTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
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
        let switchingTmpBuf : string | image.PixelMap | Resource | undefined = undefined
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
            valueSerializer.writeFloat64(valueHolderForLeftTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            valueSerializer.writeFloat64(valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            valueSerializer.writeFloat64(valueHolderForWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            valueSerializer.writeFloat64(valueHolderForHeightTmpValue)
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
        let leftTmpBuf : double | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            leftTmpBuf = valueDeserializer.readFloat64()
        }
        const leftTmpResult : double | undefined = leftTmpBuf
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : double | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = valueDeserializer.readFloat64()
        }
        const topTmpResult : double | undefined = topTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : double | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            widthTmpBuf = valueDeserializer.readFloat64()
        }
        const widthTmpResult : double | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : double | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightTmpBuf = valueDeserializer.readFloat64()
        }
        const heightTmpResult : double | undefined = heightTmpBuf
        const iconsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconsTmpBuf : ButtonIconOptions | undefined = undefined
        if ((iconsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            iconsTmpBuf = ButtonIconOptions_serializer.read(valueDeserializer)
        }
        const iconsTmpResult : ButtonIconOptions | undefined = iconsTmpBuf
        let value : ButtonStyle = ({left: leftTmpResult, top: topTmpResult, width: widthTmpResult, height: heightTmpResult, icons: iconsTmpResult} as ButtonStyle)
        return value
    }
}
