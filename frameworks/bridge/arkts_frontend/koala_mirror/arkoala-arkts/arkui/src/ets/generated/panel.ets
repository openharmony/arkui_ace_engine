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
import { Dimension, ResourceColor } from "./units"
import { Callback_Number_Void } from "./alphabet_indexer"
import { Resource } from "./resource"
import { Color } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkPanelPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPanelPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Panel_construct(peerId, flags)
        const _peer  = new ArkPanelPeer(_peerPtr, peerId, "Panel", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPanelOptionsAttribute(show: boolean): void {
        ArkUIGeneratedNativeModule._PanelInterface_setPanelOptions(this.peer.ptr, show ? 1 : 0)
    }
    modeAttribute(value: PanelMode): void {
        ArkUIGeneratedNativeModule._PanelAttribute_mode(this.peer.ptr, TypeChecker.PanelMode_ToNumeric(value))
    }
    typeAttribute(value: PanelType): void {
        ArkUIGeneratedNativeModule._PanelAttribute_type(this.peer.ptr, TypeChecker.PanelType_ToNumeric(value))
    }
    dragBarAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._PanelAttribute_dragBar(this.peer.ptr, value ? 1 : 0)
    }
    customHeightAttribute(value: Dimension | PanelHeight): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Dimension
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(2)
                const value_0_2  = value_0 as Resource
                thisSerializer.writeResource(value_0_2)
            }
        }
        else if (TypeChecker.isPanelHeight(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as PanelHeight
            thisSerializer.writeInt32(TypeChecker.PanelHeight_ToNumeric(value_1))
        }
        ArkUIGeneratedNativeModule._PanelAttribute_customHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fullHeightAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._PanelAttribute_fullHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    halfHeightAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._PanelAttribute_halfHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    miniHeightAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._PanelAttribute_miniHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._PanelAttribute_show(this.peer.ptr, value ? 1 : 0)
    }
    backgroundMaskAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._PanelAttribute_backgroundMask(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showCloseIconAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._PanelAttribute_showCloseIcon(this.peer.ptr, value ? 1 : 0)
    }
    onChangeAttribute(value: ((width: number,height: number,mode: PanelMode) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._PanelAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHeightChangeAttribute(value: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._PanelAttribute_onHeightChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_modeAttribute(callback: ((mode: PanelMode) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._PanelAttribute__onChangeEvent_mode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum PanelMode {
    MINI = 0,
    Mini = 0,
    HALF = 1,
    Half = 1,
    FULL = 2,
    Full = 2
}
export enum PanelType {
    MINIBAR = 0,
    Minibar = 0,
    FOLDABLE = 1,
    Foldable = 1,
    TEMPORARY = 2,
    Temporary = 2,
    CUSTOM = 3
}
export enum PanelHeight {
    WRAP_CONTENT = "wrapContent"
}

export type Callback_Number_Number_PanelMode_Void = (width: number, height: number, mode: PanelMode) => void;
export type Callback_PanelMode_Void = (mode: PanelMode) => void;
export interface PanelAttribute extends CommonMethod {
    mode(value: PanelMode): this
    type(value: PanelType): this
    dragBar(value: boolean): this
    customHeight(value: Dimension | PanelHeight): this
    fullHeight(value: number | string): this
    halfHeight(value: number | string): this
    miniHeight(value: number | string): this
    show(value: boolean): this
    backgroundMask(value: ResourceColor): this
    showCloseIcon(value: boolean): this
    onChange(value: ((width: number,height: number,mode: PanelMode) => void)): this
    onHeightChange(value: ((index: number) => void)): this
    _onChangeEvent_mode(callback: ((mode: PanelMode) => void)): void
    attributeModifier(value: AttributeModifier<PanelAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIPanelAttribute extends UICommonMethod {
    @memo
    mode(value: PanelMode): this
    @memo
    type(value: PanelType): this
    @memo
    dragBar(value: boolean): this
    @memo
    customHeight(value: Dimension | PanelHeight): this
    @memo
    fullHeight(value: number | string): this
    @memo
    halfHeight(value: number | string): this
    @memo
    miniHeight(value: number | string): this
    @memo
    show(value: boolean): this
    @memo
    backgroundMask(value: ResourceColor): this
    @memo
    showCloseIcon(value: boolean): this
    @memo
    onChange(value: ((width: number,height: number,mode: PanelMode) => void)): this
    @memo
    onHeightChange(value: ((index: number) => void)): this
    @memo
    _onChangeEvent_mode(callback: ((mode: PanelMode) => void)): void
    @memo
    attributeModifier(value: AttributeModifier<PanelAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkPanelStyle extends ArkCommonMethodStyle implements PanelAttribute {
    mode_value?: PanelMode
    type_value?: PanelType
    dragBar_value?: boolean
    customHeight_value?: Dimension | PanelHeight
    fullHeight_value?: number | string
    halfHeight_value?: number | string
    miniHeight_value?: number | string
    show_value?: boolean
    backgroundMask_value?: ResourceColor
    showCloseIcon_value?: boolean
    onChange_value?: ((width: number,height: number,mode: PanelMode) => void)
    onHeightChange_value?: ((index: number) => void)
    public mode(value: PanelMode): this {
        return this
    }
    public type(value: PanelType): this {
        return this
    }
    public dragBar(value: boolean): this {
        return this
    }
    public customHeight(value: Dimension | PanelHeight): this {
        return this
    }
    public fullHeight(value: number | string): this {
        return this
    }
    public halfHeight(value: number | string): this {
        return this
    }
    public miniHeight(value: number | string): this {
        return this
    }
    public show(value: boolean): this {
        return this
    }
    public backgroundMask(value: ResourceColor): this {
        return this
    }
    public showCloseIcon(value: boolean): this {
        return this
    }
    public onChange(value: ((width: number,height: number,mode: PanelMode) => void)): this {
        return this
    }
    public onHeightChange(value: ((index: number) => void)): this {
        return this
    }
    public _onChangeEvent_mode(callback: ((mode: PanelMode) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<PanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkPanelComponent extends ArkCommonMethodComponent implements UIPanelAttribute {
    getPeer(): ArkPanelPeer {
        return (this.peer as ArkPanelPeer)
    }
    @memo
    public setPanelOptions(show: boolean): this {
        if (this.checkPriority("setPanelOptions")) {
            const show_casted = show as (boolean)
            this.getPeer()?.setPanelOptionsAttribute(show_casted)
            return this
        }
        return this
    }
    @memo
    public mode(value: PanelMode): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (PanelMode)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public type(value: PanelType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (PanelType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public dragBar(value: boolean): this {
        if (this.checkPriority("dragBar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.dragBarAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public customHeight(value: Dimension | PanelHeight): this {
        if (this.checkPriority("customHeight")) {
            const value_casted = value as (Dimension | PanelHeight)
            this.getPeer()?.customHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fullHeight(value: number | string): this {
        if (this.checkPriority("fullHeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.fullHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public halfHeight(value: number | string): this {
        if (this.checkPriority("halfHeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.halfHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public miniHeight(value: number | string): this {
        if (this.checkPriority("miniHeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.miniHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public show(value: boolean): this {
        if (this.checkPriority("show")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public backgroundMask(value: ResourceColor): this {
        if (this.checkPriority("backgroundMask")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.backgroundMaskAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public showCloseIcon(value: boolean): this {
        if (this.checkPriority("showCloseIcon")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showCloseIconAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onChange(value: ((width: number,height: number,mode: PanelMode) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((width: number,height: number,mode: PanelMode) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onHeightChange(value: ((index: number) => void)): this {
        if (this.checkPriority("onHeightChange")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onHeightChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public _onChangeEvent_mode(callback: ((mode: PanelMode) => void)): void {
        if (this.checkPriority("_onChangeEvent_mode")) {
            const callback_casted = callback as (((mode: PanelMode) => void))
            this.getPeer()?._onChangeEvent_modeAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public attributeModifier(value: AttributeModifier<PanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Panel")
export function Panel(
    show: boolean,
    @memo
    content_?: () => void,
): PanelAttribute {
    throw new Error("Not implemented")
}

@memo
export function Panel(
    @memo
    style: ((attributes: UIPanelAttribute) => void) | undefined,
    show: boolean,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPanelComponent>((): ArkPanelComponent => {
        return new ArkPanelComponent()
    })
    NodeAttach<ArkPanelPeer>((): ArkPanelPeer => ArkPanelPeer.create(receiver), (_: ArkPanelPeer): void => {
        receiver.setPanelOptions(show)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
