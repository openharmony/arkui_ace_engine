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
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Callback_Boolean_Void } from "./navigation"
import { Callback_Opt_Boolean_Void } from "./checkbox"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentContent } from "./arkui-custom"
import { Length } from "./units"
import { Callback_Number_Void } from "./alphabetIndexer"

export class ArkListItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkListItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ListItem_construct(peerId, flags)
        const _peer  = new ArkListItemPeer(_peerPtr, peerId, "ListItem", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListItemOptions0Attribute(value?: ListItemOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeListItemOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemInterface_setListItemOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setListItemOptions1Attribute(value?: string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemInterface_setListItemOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stickyAttribute(value: Sticky | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Sticky)
            thisSerializer.writeInt32(TypeChecker.Sticky_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_sticky(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editableAttribute(value: boolean | EditMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.BOOLEAN == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as boolean
                thisSerializer.writeBoolean(value_value_0)
            }
            else if (TypeChecker.isEditMode(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EditMode
                thisSerializer.writeInt32(TypeChecker.EditMode_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_editable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_selectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    swipeActionAttribute(value: SwipeActionOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSwipeActionOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_swipeAction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((select: boolean | undefined) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._ListItemAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum Sticky {
    NONE = 0,
    None = 0,
    NORMAL = 1,
    Normal = 1,
    OPACITY = 2,
    Opacity = 2
}
export enum EditMode {
    NONE = 0,
    None = 0,
    DELETABLE = 1,
    Deletable = 1,
    MOVABLE = 2,
    Movable = 2
}
export enum SwipeEdgeEffect {
    SPRING = 0,
    Spring = 0,
    NONE = 1,
    None = 1
}
export enum SwipeActionState {
    COLLAPSED = 0,
    EXPANDED = 1,
    ACTIONING = 2
}
export type Callback_SwipeActionState_Void = (state: SwipeActionState) => void;
export interface SwipeActionItem {
    builder?: CustomBuilder;
    builderComponent?: ComponentContent;
    actionAreaDistance?: Length;
    onAction?: (() => void);
    onEnterActionArea?: (() => void);
    onExitActionArea?: (() => void);
    onStateChange?: ((state: SwipeActionState) => void);
}
export interface SwipeActionOptions {
    start?: CustomBuilder | SwipeActionItem;
    end?: CustomBuilder | SwipeActionItem;
    edgeEffect?: SwipeEdgeEffect;
    onOffsetChange?: ((index: number) => void);
}
export enum ListItemStyle {
    NONE = 0,
    CARD = 1
}
export interface ListItemOptions {
    style?: ListItemStyle;
}
export interface ListItemAttribute extends CommonMethod {
    sticky(value: Sticky | undefined): this
    editable(value: boolean | EditMode | undefined): this
    selectable(value: boolean | undefined): this
    selected(value: boolean | undefined): this
    swipeAction(value: SwipeActionOptions | undefined): this
    onSelect(value: ((isVisible: boolean) => void) | undefined): this
    _onChangeEvent_selected(callback: ((select: boolean | undefined) => void)): void
}
export class ArkListItemStyle extends ArkCommonMethodStyle implements ListItemAttribute {
    sticky_value?: Sticky | undefined
    editable_value?: boolean | EditMode | undefined
    selectable_value?: boolean | undefined
    selected_value?: boolean | undefined
    swipeAction_value?: SwipeActionOptions | undefined
    onSelect_value?: ((isVisible: boolean) => void) | undefined
    public sticky(value: Sticky | undefined): this {
        return this
    }
    public editable(value: boolean | EditMode | undefined): this {
        return this
    }
    public selectable(value: boolean | undefined): this {
        return this
    }
    public selected(value: boolean | undefined): this {
        return this
    }
    public swipeAction(value: SwipeActionOptions | undefined): this {
        return this
    }
    public onSelect(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((select: boolean | undefined) => void)): void {
        throw new Error("Unimplmented")
        }
}
export class ArkListItemComponent extends ArkCommonMethodComponent implements ListItemAttribute {
    getPeer(): ArkListItemPeer {
        return (this.peer as ArkListItemPeer)
    }
    public setListItemOptions(value?: ListItemOptions | string): this {
        if (this.checkPriority("setListItemOptions")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ListItemOptions | undefined)
                this.getPeer()?.setListItemOptions0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (string | undefined)
                this.getPeer()?.setListItemOptions1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public sticky(value: Sticky | undefined): this {
        if (this.checkPriority("sticky")) {
            const value_casted = value as (Sticky | undefined)
            this.getPeer()?.stickyAttribute(value_casted)
            return this
        }
        return this
    }
    public editable(value: boolean | EditMode | undefined): this {
        if (this.checkPriority("editable")) {
            const value_casted = value as (boolean | EditMode | undefined)
            this.getPeer()?.editableAttribute(value_casted)
            return this
        }
        return this
    }
    public selectable(value: boolean | undefined): this {
        if (this.checkPriority("selectable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.selectableAttribute(value_casted)
            return this
        }
        return this
    }
    public selected(value: boolean | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    public swipeAction(value: SwipeActionOptions | undefined): this {
        if (this.checkPriority("swipeAction")) {
            const value_casted = value as (SwipeActionOptions | undefined)
            this.getPeer()?.swipeActionAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selected(callback: ((select: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((select: boolean | undefined) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
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
export function ListItem(
    /** @memo */
    style: ((attributes: ListItemAttribute) => void) | undefined,
    value?: ListItemOptions | undefined,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkListItemComponent()
    })
    NodeAttach<ArkListItemPeer>((): ArkListItemPeer => ArkListItemPeer.create(receiver), (_: ArkListItemPeer) => {
        receiver.setListItemOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
