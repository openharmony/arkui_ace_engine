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
import { ItemAlign } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Length } from "./units"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkGridRowPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridRowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridRow_construct(peerId, flags)
        const _peer  = new ArkGridRowPeer(_peerPtr, peerId, "GridRow", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridRowOptionsAttribute(option?: GridRowOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let option_type : int32 = RuntimeType.UNDEFINED
        option_type = runtimeType(option)
        thisSerializer.writeInt8(option_type as int32)
        if ((RuntimeType.UNDEFINED) != (option_type)) {
            const option_value  = option!
            thisSerializer.writeGridRowOptions(option_value)
        }
        ArkUIGeneratedNativeModule._GridRowInterface_setGridRowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBreakpointChangeAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridRowAttribute_onBreakpointChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignItemsAttribute(value: ItemAlign): void {
        ArkUIGeneratedNativeModule._GridRowAttribute_alignItems(this.peer.ptr, TypeChecker.ItemAlign_ToNumeric(value))
    }
}
export interface GridRowSizeOption {
    xs?: Length;
    sm?: Length;
    md?: Length;
    lg?: Length;
    xl?: Length;
    xxl?: Length;
}
export interface GridRowColumnOption {
    xs?: number;
    sm?: number;
    md?: number;
    lg?: number;
    xl?: number;
    xxl?: number;
}
export interface GutterOption {
    x?: Length | GridRowSizeOption;
    y?: Length | GridRowSizeOption;
}
export enum BreakpointsReference {
    WINDOW_SIZE = 0,
    WindowSize = 0,
    COMPONENT_SIZE = 1,
    ComponentSize = 1
}
export enum GridRowDirection {
    ROW = 0,
    Row = 0,
    ROW_REVERSE = 1,
    RowReverse = 1
}
export interface BreakPoints {
    value?: Array<string>;
    reference?: BreakpointsReference;
}
export interface GridRowOptions {
    gutter?: Length | GutterOption;
    columns?: number | GridRowColumnOption;
    breakpoints?: BreakPoints;
    direction?: GridRowDirection;
}

export type Callback_String_Void = (breakpoints: string) => void;
export interface GridRowAttribute extends CommonMethod {
    onBreakpointChange(value: ((breakpoints: string) => void)): this
    alignItems(value: ItemAlign): this
    attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIGridRowAttribute extends UICommonMethod {
    /** @memo */
    onBreakpointChange(value: ((breakpoints: string) => void)): this
    /** @memo */
    alignItems(value: ItemAlign): this
    /** @memo */
    attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkGridRowStyle extends ArkCommonMethodStyle implements GridRowAttribute {
    onBreakpointChange_value?: ((breakpoints: string) => void)
    alignItems_value?: ItemAlign
    public onBreakpointChange(value: ((breakpoints: string) => void)): this {
        return this
    }
    public alignItems(value: ItemAlign): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkGridRowComponent extends ArkCommonMethodComponent implements UIGridRowAttribute {
    getPeer(): ArkGridRowPeer {
        return (this.peer as ArkGridRowPeer)
    }
    /** @memo */
    public setGridRowOptions(option?: GridRowOptions): this {
        if (this.checkPriority("setGridRowOptions")) {
            const option_casted = option as (GridRowOptions | undefined)
            this.getPeer()?.setGridRowOptionsAttribute(option_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onBreakpointChange(value: ((breakpoints: string) => void)): this {
        if (this.checkPriority("onBreakpointChange")) {
            const value_casted = value as (((breakpoints: string) => void))
            this.getPeer()?.onBreakpointChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignItems(value: ItemAlign): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (ItemAlign)
            this.getPeer()?.alignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkGridRow(
    /** @memo */
    style: ((attributes: UIGridRowAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    option?: GridRowOptions,
): void {
    const receiver = remember(() => {
        return new ArkGridRowComponent()
    })
    NodeAttach<ArkGridRowPeer>((): ArkGridRowPeer => ArkGridRowPeer.create(receiver), (_: ArkGridRowPeer) => {
        receiver.setGridRowOptions(option)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
