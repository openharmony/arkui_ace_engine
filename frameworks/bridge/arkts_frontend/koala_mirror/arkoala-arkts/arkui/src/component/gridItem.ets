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
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            GridItemOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._GridItemInterface_setGridItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowStartAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setRowStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowEndAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setRowEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnStartAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setColumnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnEndAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setColumnEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: ((isSelected: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectedAttribute(callback_: ((selected: boolean | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._GridItemAttribute_set_onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    rowStart(value: number | undefined): this {
        throw new Error("Unimplemented method rowStart")
    }
    rowEnd(value: number | undefined): this {
        throw new Error("Unimplemented method rowEnd")
    }
    columnStart(value: number | undefined): this {
        throw new Error("Unimplemented method columnStart")
    }
    columnEnd(value: number | undefined): this {
        throw new Error("Unimplemented method columnEnd")
    }
    selectable(value: boolean | undefined): this {
        throw new Error("Unimplemented method selectable")
    }
    selected(value: boolean | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onSelect")
    }
    _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selected")
    }
    attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkGridItemStyle extends ArkCommonMethodStyle implements GridItemAttribute {
    rowStart_value?: number | undefined
    rowEnd_value?: number | undefined
    columnStart_value?: number | undefined
    columnEnd_value?: number | undefined
    selectable_value?: boolean | undefined
    selected_value?: boolean | undefined
    onSelect_value?: ((isSelected: boolean) => void) | undefined
    attributeModifier_value?: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined
    public rowStart(value: number | undefined): this {
        return this
    }
    public rowEnd(value: number | undefined): this {
        return this
    }
    public columnStart(value: number | undefined): this {
        return this
    }
    public columnEnd(value: number | undefined): this {
        return this
    }
    public selectable(value: boolean | undefined): this {
        return this
    }
    public selected(value: boolean | undefined): this {
        return this
    }
    public onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: GridItemAttribute): void {
        super.apply(target)
        if (this.rowStart_value !== undefined)
            target.rowStart(this.rowStart_value!)
        if (this.rowEnd_value !== undefined)
            target.rowEnd(this.rowEnd_value!)
        if (this.columnStart_value !== undefined)
            target.columnStart(this.columnStart_value!)
        if (this.columnEnd_value !== undefined)
            target.columnEnd(this.columnEnd_value!)
        if (this.selectable_value !== undefined)
            target.selectable(this.selectable_value!)
        if (this.selected_value !== undefined)
            target.selected(this.selected_value!)
        if (this.onSelect_value !== undefined)
            target.onSelect(this.onSelect_value!)
    }
}

export class ArkGridItemComponent extends ArkCommonMethodComponent implements GridItemAttribute {
    getPeer(): ArkGridItemPeer {
        return (this.peer as ArkGridItemPeer)
    }
    public setGridItemOptions(value?: GridItemOptions): this {
        if (this.checkPriority("setGridItemOptions")) {
            const value_casted = value as (GridItemOptions | undefined)
            this.getPeer()?.setGridItemOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public rowStart(value: number | undefined): this {
        if (this.checkPriority("rowStart")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setRowStartAttribute(value_casted)
            return this
        }
        return this
    }
    public rowEnd(value: number | undefined): this {
        if (this.checkPriority("rowEnd")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setRowEndAttribute(value_casted)
            return this
        }
        return this
    }
    public columnStart(value: number | undefined): this {
        if (this.checkPriority("columnStart")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setColumnStartAttribute(value_casted)
            return this
        }
        return this
    }
    public columnEnd(value: number | undefined): this {
        if (this.checkPriority("columnEnd")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setColumnEndAttribute(value_casted)
            return this
        }
        return this
    }
    public selectable(value: boolean | undefined): this {
        if (this.checkPriority("selectable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    public selected(value: boolean | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((isSelected: boolean) => void) | undefined)
            this.getPeer()?.setOnSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback__casted = callback_ as (((selected: boolean | undefined) => void))
            this.getPeer()?.set_onChangeEvent_selectedAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withGridItemStyle(receiver: GridItemAttribute, modifier: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkGridItemStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("GridItem")
// export function GridItem(
//     value?: GridItemOptions,
//     @memo
//     content_?: () => void,
// ): GridItemAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function GridItem(
    @memo
    style: ((attributes: GridItemAttribute) => void) | undefined,
    value?: GridItemOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkGridItemComponent>((): ArkGridItemComponent => {
        return new ArkGridItemComponent()
    })
    NodeAttach<ArkGridItemPeer>((): ArkGridItemPeer => ArkGridItemPeer.create(receiver), (_: ArkGridItemPeer): void => {
        receiver.setGridItemOptions(value)
        style?.(receiver)
        withGridItemStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkGridItemSet extends ArkCommonMethodSet implements GridItemAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _rowStart_flag?: boolean
    _rowStart0_value?: number | undefined
    _rowEnd_flag?: boolean
    _rowEnd0_value?: number | undefined
    _columnStart_flag?: boolean
    _columnStart0_value?: number | undefined
    _columnEnd_flag?: boolean
    _columnEnd0_value?: number | undefined
    _selectable_flag?: boolean
    _selectable0_value?: boolean | undefined
    _selected_flag?: boolean
    _selected0_value?: boolean | undefined
    _onSelect_flag?: boolean
    _onSelect0_value?: ((isSelected: boolean) => void) | undefined
    __onChangeEvent_selected_flag?: boolean
    __onChangeEvent_selected0_value?: ((selected: boolean | undefined) => void)
    applyModifierPatch(component: GridItemAttribute): void {
        if (this._rowStart_flag)
            component.rowStart((this._rowStart0_value as number | undefined))
        if (this._rowEnd_flag)
            component.rowEnd((this._rowEnd0_value as number | undefined))
        if (this._columnStart_flag)
            component.columnStart((this._columnStart0_value as number | undefined))
        if (this._columnEnd_flag)
            component.columnEnd((this._columnEnd0_value as number | undefined))
        if (this._selectable_flag)
            component.selectable((this._selectable0_value as boolean | undefined))
        if (this._selected_flag)
            component.selected((this._selected0_value as boolean | undefined))
        if (this._onSelect_flag)
            component.onSelect((this._onSelect0_value as ((isSelected: boolean) => void) | undefined))
    }
    public rowStart(value: number | undefined): this {
        this._rowStart_flag = true
        this._rowStart0_value = value
        return this
    }
    public rowEnd(value: number | undefined): this {
        this._rowEnd_flag = true
        this._rowEnd0_value = value
        return this
    }
    public columnStart(value: number | undefined): this {
        this._columnStart_flag = true
        this._columnStart0_value = value
        return this
    }
    public columnEnd(value: number | undefined): this {
        this._columnEnd_flag = true
        this._columnEnd0_value = value
        return this
    }
    public selectable(value: boolean | undefined): this {
        this._selectable_flag = true
        this._selectable0_value = value
        return this
    }
    public selected(value: boolean | undefined): this {
        this._selected_flag = true
        this._selected0_value = value
        return this
    }
    public onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        this._onSelect_flag = true
        this._onSelect0_value = value
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class GridItemOptions_serializer {
    public static write(buffer: SerializerBase, value: GridItemOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as GridItemStyle)
            valueSerializer.writeInt32(TypeChecker.GridItemStyle_ToNumeric(value_style_value))
        }
    }
    public static read(buffer: DeserializerBase): GridItemOptions {
        let valueDeserializer : DeserializerBase = buffer
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : GridItemStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.GridItemStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : GridItemStyle | undefined = style_buf
        let value : GridItemOptions = ({style: style_result} as GridItemOptions)
        return value
    }
}
