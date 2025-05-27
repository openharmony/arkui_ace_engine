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
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkGridItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridItem_construct(peerId, flags)
        const _peer  = new ArkGridItemPeer(_peerPtr, peerId, "GridItem", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridItemOptionsAttribute(value?: GridItemOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeGridItemOptions(value_value)
        }
        ArkUIGeneratedNativeModule._GridItemInterface_setGridItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowStartAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridItemAttribute_rowStart(this.peer.ptr, value)
    }
    rowEndAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridItemAttribute_rowEnd(this.peer.ptr, value)
    }
    columnStartAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridItemAttribute_columnStart(this.peer.ptr, value)
    }
    columnEndAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridItemAttribute_columnEnd(this.peer.ptr, value)
    }
    forceRebuildAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridItemAttribute_forceRebuild(this.peer.ptr, value ? 1 : 0)
    }
    selectableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridItemAttribute_selectable(this.peer.ptr, value ? 1 : 0)
    }
    selectedAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridItemAttribute_selected(this.peer.ptr, value ? 1 : 0)
    }
    onSelectAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridItemAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._GridItemAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum GridItemStyle {
    NONE = 0,
    PLAIN = 1
}
export interface GridItemOptions {
    style?: GridItemStyle;
}

export interface GridItemAttribute extends CommonMethod {
    rowStart(value: number): this
    rowEnd(value: number): this
    columnStart(value: number): this
    columnEnd(value: number): this
    forceRebuild(value: boolean): this
    selectable(value: boolean): this
    selected(value: boolean): this
    onSelect(value: ((isVisible: boolean) => void)): this
    _onChangeEvent_selected(callback: ((isVisible: boolean) => void)): void
    attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIGridItemAttribute extends UICommonMethod {
    /** @memo */
    rowStart(value: number): this
    /** @memo */
    rowEnd(value: number): this
    /** @memo */
    columnStart(value: number): this
    /** @memo */
    columnEnd(value: number): this
    /** @memo */
    forceRebuild(value: boolean): this
    /** @memo */
    selectable(value: boolean): this
    /** @memo */
    selected(value: boolean): this
    /** @memo */
    onSelect(value: ((isVisible: boolean) => void)): this
    /** @memo */
    _onChangeEvent_selected(callback: ((isVisible: boolean) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkGridItemStyle extends ArkCommonMethodStyle implements GridItemAttribute {
    rowStart_value?: number
    rowEnd_value?: number
    columnStart_value?: number
    columnEnd_value?: number
    forceRebuild_value?: boolean
    selectable_value?: boolean
    selected_value?: boolean
    onSelect_value?: ((isVisible: boolean) => void)
    public rowStart(value: number): this {
        return this
    }
    public rowEnd(value: number): this {
        return this
    }
    public columnStart(value: number): this {
        return this
    }
    public columnEnd(value: number): this {
        return this
    }
    public forceRebuild(value: boolean): this {
        return this
    }
    public selectable(value: boolean): this {
        return this
    }
    public selected(value: boolean): this {
        return this
    }
    public onSelect(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkGridItemComponent extends ArkCommonMethodComponent implements UIGridItemAttribute {
    getPeer(): ArkGridItemPeer {
        return (this.peer as ArkGridItemPeer)
    }
    /** @memo */
    public setGridItemOptions(value?: GridItemOptions): this {
        if (this.checkPriority("setGridItemOptions")) {
            const value_casted = value as (GridItemOptions | undefined)
            this.getPeer()?.setGridItemOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowStart(value: number): this {
        if (this.checkPriority("rowStart")) {
            const value_casted = value as (number)
            this.getPeer()?.rowStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowEnd(value: number): this {
        if (this.checkPriority("rowEnd")) {
            const value_casted = value as (number)
            this.getPeer()?.rowEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnStart(value: number): this {
        if (this.checkPriority("columnStart")) {
            const value_casted = value as (number)
            this.getPeer()?.columnStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnEnd(value: number): this {
        if (this.checkPriority("columnEnd")) {
            const value_casted = value as (number)
            this.getPeer()?.columnEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public forceRebuild(value: boolean): this {
        if (this.checkPriority("forceRebuild")) {
            const value_casted = value as (boolean)
            this.getPeer()?.forceRebuildAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectable(value: boolean): this {
        if (this.checkPriority("selectable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selected(value: boolean): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelect(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkGridItem(
    /** @memo */
    style: ((attributes: UIGridItemAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    value?: GridItemOptions,
): void {
    const receiver = remember(() => {
        return new ArkGridItemComponent()
    })
    NodeAttach<ArkGridItemPeer>((): ArkGridItemPeer => ArkGridItemPeer.create(receiver), (_: ArkGridItemPeer) => {
        receiver.setGridItemOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
