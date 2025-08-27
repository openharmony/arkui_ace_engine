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
import { Dimension, ResourceColor, PX, VP, FP, LPX, Percentage } from "./units"
import { Callback_Number_Void } from "./alphabetIndexer"
import { Resource } from "global.resource"
import { Color } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkPanelPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkPanelPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Panel_construct(peerId, flags)
        const _peer  = new ArkPanelPeer(_peerPtr, peerId, "Panel", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPanelOptionsAttribute(show: boolean): void {
        ArkUIGeneratedNativeModule._PanelInterface_setPanelOptions(this.peer.ptr, show ? 1 : 0)
    }
    modeAttribute(value: PanelMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as PanelMode)
            thisSerializer.writeInt32(TypeChecker.PanelMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._PanelAttribute_mode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    typeAttribute(value: PanelType | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as PanelType)
            thisSerializer.writeInt32(TypeChecker.PanelType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._PanelAttribute_type(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dragBarAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._PanelAttribute_dragBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customHeightAttribute(value: Dimension | PanelHeight | undefined): void {
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
            else if (TypeChecker.isPanelHeight(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as PanelHeight
                thisSerializer.writeInt32(TypeChecker.PanelHeight_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._PanelAttribute_customHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fullHeightAttribute(value: number | string | undefined): void {
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
        }
        ArkUIGeneratedNativeModule._PanelAttribute_fullHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    halfHeightAttribute(value: number | string | undefined): void {
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
        }
        ArkUIGeneratedNativeModule._PanelAttribute_halfHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    miniHeightAttribute(value: number | string | undefined): void {
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
        }
        ArkUIGeneratedNativeModule._PanelAttribute_miniHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._PanelAttribute_show(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundMaskAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._PanelAttribute_backgroundMask(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showCloseIconAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._PanelAttribute_showCloseIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((width: number,height: number,mode: PanelMode) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PanelAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHeightChangeAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PanelAttribute_onHeightChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_modeAttribute(callback: ((mode: PanelMode | undefined) => void)): void {
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
export type PanelInterface = (show: boolean) => PanelAttribute;
export type Callback_Number_Number_PanelMode_Void = (width: number, height: number, mode: PanelMode) => void;
export type Callback_Opt_PanelMode_Void = (mode: PanelMode | undefined) => void;
export interface PanelAttribute extends CommonMethod {
    mode(value: PanelMode | undefined): this
    type(value: PanelType | undefined): this
    dragBar(value: boolean | undefined): this
    customHeight(value: Dimension | PanelHeight | undefined): this
    fullHeight(value: number | string | undefined): this
    halfHeight(value: number | string | undefined): this
    miniHeight(value: number | string | undefined): this
    show(value: boolean | undefined): this
    backgroundMask(value: ResourceColor | undefined): this
    showCloseIcon(value: boolean | undefined): this
    onChange(value: ((width: number,height: number,mode: PanelMode) => void) | undefined): this
    onHeightChange(value: ((index: number) => void) | undefined): this
    _onChangeEvent_mode(callback: ((mode: PanelMode | undefined) => void)): void
}
export class ArkPanelStyle extends ArkCommonMethodStyle implements PanelAttribute {
    mode_value?: PanelMode | undefined
    type_value?: PanelType | undefined
    dragBar_value?: boolean | undefined
    customHeight_value?: Dimension | PanelHeight | undefined
    fullHeight_value?: number | string | undefined
    halfHeight_value?: number | string | undefined
    miniHeight_value?: number | string | undefined
    show_value?: boolean | undefined
    backgroundMask_value?: ResourceColor | undefined
    showCloseIcon_value?: boolean | undefined
    onChange_value?: ((width: number,height: number,mode: PanelMode) => void) | undefined
    onHeightChange_value?: ((index: number) => void) | undefined
    public mode(value: PanelMode | undefined): this {
        return this
    }
    public type(value: PanelType | undefined): this {
        return this
    }
    public dragBar(value: boolean | undefined): this {
        return this
    }
    public customHeight(value: Dimension | PanelHeight | undefined): this {
        return this
    }
    public fullHeight(value: number | string | undefined): this {
        return this
    }
    public halfHeight(value: number | string | undefined): this {
        return this
    }
    public miniHeight(value: number | string | undefined): this {
        return this
    }
    public show(value: boolean | undefined): this {
        return this
    }
    public backgroundMask(value: ResourceColor | undefined): this {
        return this
    }
    public showCloseIcon(value: boolean | undefined): this {
        return this
    }
    public onChange(value: ((width: number,height: number,mode: PanelMode) => void) | undefined): this {
        return this
    }
    public onHeightChange(value: ((index: number) => void) | undefined): this {
        return this
    }
    public _onChangeEvent_mode(callback: ((mode: PanelMode | undefined) => void)): void {
        throw new Error("Unimplmented")
        }
}
export class ArkPanelComponent extends ArkCommonMethodComponent implements PanelAttribute {
    getPeer(): ArkPanelPeer {
        return (this.peer as ArkPanelPeer)
    }
    public setPanelOptions(show: boolean): this {
        if (this.checkPriority("setPanelOptions")) {
            const show_casted = show as (boolean)
            this.getPeer()?.setPanelOptionsAttribute(show_casted)
            return this
        }
        return this
    }
    public mode(value: PanelMode | undefined): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (PanelMode | undefined)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    public type(value: PanelType | undefined): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (PanelType | undefined)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    public dragBar(value: boolean | undefined): this {
        if (this.checkPriority("dragBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.dragBarAttribute(value_casted)
            return this
        }
        return this
    }
    public customHeight(value: Dimension | PanelHeight | undefined): this {
        if (this.checkPriority("customHeight")) {
            const value_casted = value as (Dimension | PanelHeight | undefined)
            this.getPeer()?.customHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fullHeight(value: number | string | undefined): this {
        if (this.checkPriority("fullHeight")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.fullHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public halfHeight(value: number | string | undefined): this {
        if (this.checkPriority("halfHeight")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.halfHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public miniHeight(value: number | string | undefined): this {
        if (this.checkPriority("miniHeight")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.miniHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public show(value: boolean | undefined): this {
        if (this.checkPriority("show")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.showAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundMask(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundMask")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.backgroundMaskAttribute(value_casted)
            return this
        }
        return this
    }
    public showCloseIcon(value: boolean | undefined): this {
        if (this.checkPriority("showCloseIcon")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.showCloseIconAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((width: number,height: number,mode: PanelMode) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((width: number,height: number,mode: PanelMode) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onHeightChange(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onHeightChange")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onHeightChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_mode(callback: ((mode: PanelMode | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_mode")) {
            const callback_casted = callback as (((mode: PanelMode | undefined) => void))
            this.getPeer()?._onChangeEvent_modeAttribute(callback_casted)
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
export function Panel(
    /** @memo */
    style: ((attributes: PanelAttribute) => void) | undefined,
    show: boolean,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkPanelComponent()
    })
    NodeAttach<ArkPanelPeer>((): ArkPanelPeer => ArkPanelPeer.create(receiver), (_: ArkPanelPeer) => {
        receiver.setPanelOptions(show)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
