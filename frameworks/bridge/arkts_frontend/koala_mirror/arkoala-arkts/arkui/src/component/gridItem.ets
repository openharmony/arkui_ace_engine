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
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkGridItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridItem_construct(peerId, flags)
        const _peer  = new ArkGridItemPeer(_peerPtr, peerId, 'GridItem', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridItemOptionsAttribute(value?: GridItemOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            GridItemOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridItemInterface_setGridItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowStartAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setRowStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowEndAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setRowEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnStartAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setColumnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnEndAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setColumnEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: boolean | Bindable<boolean> | undefined): void {
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
        ArkUIGeneratedNativeModule._GridItemAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: ((isSelected: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridItemAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    selected(value: boolean | Bindable<boolean> | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onSelect")
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
    selected_value?: boolean | Bindable<boolean> | undefined
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
    public selected(value: boolean | Bindable<boolean> | undefined): this {
        return this
    }
    public onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public selected(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
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
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class GridItemModifier extends CommonMethodModifier implements GridItemAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _rowStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowStart_0_0value?: number | undefined
    _rowEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowEnd_0_0value?: number | undefined
    _columnStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnStart_0_0value?: number | undefined
    _columnEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnEnd_0_0value?: number | undefined
    _selectable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectable_0_0value?: boolean | undefined
    _selected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selected_0_0value?: boolean | Bindable<boolean> | undefined
    _onSelect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelect_0_0value?: ((isSelected: boolean) => void) | undefined
    applyModifierPatch(peer: ArkGridItemPeer): void {
        super.applyModifierPatch(peer)
        if (this._rowStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowStartAttribute((this._rowStart_0_0value as number | undefined));
                    this._rowStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowStartAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._rowEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowEndAttribute((this._rowEnd_0_0value as number | undefined));
                    this._rowEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowEndAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._columnStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnStartAttribute((this._columnStart_0_0value as number | undefined));
                    this._columnStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnStartAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._columnEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnEndAttribute((this._columnEnd_0_0value as number | undefined));
                    this._columnEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnEndAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._selectable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectableAttribute((this._selectable_0_0value as boolean | undefined));
                    this._selectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedAttribute((this._selected_0_0value as boolean | Bindable<boolean> | undefined));
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (this._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSelectAttribute((this._onSelect_0_0value as ((isSelected: boolean) => void) | undefined));
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSelectAttribute((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: GridItemModifier): void {
        super.mergeModifier(modifier)
        if (modifier._rowStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowStart(modifier._rowStart_0_0value);
                    break;
                }
                default: {
                    this.rowStart((undefined as number | undefined));
                }
            }
        }
        if (modifier._rowEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowEnd(modifier._rowEnd_0_0value);
                    break;
                }
                default: {
                    this.rowEnd((undefined as number | undefined));
                }
            }
        }
        if (modifier._columnStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnStart(modifier._columnStart_0_0value);
                    break;
                }
                default: {
                    this.columnStart((undefined as number | undefined));
                }
            }
        }
        if (modifier._columnEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnEnd(modifier._columnEnd_0_0value);
                    break;
                }
                default: {
                    this.columnEnd((undefined as number | undefined));
                }
            }
        }
        if (modifier._selectable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectable(modifier._selectable_0_0value);
                    break;
                }
                default: {
                    this.selectable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (modifier._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
    }
    rowStart(value: number | undefined): this {
        if (((this._rowStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._rowStart_0_0value) !== (value)))
        {
            this._rowStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowStart_0_0value = value
        } else
        {
            this._rowStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rowEnd(value: number | undefined): this {
        if (((this._rowEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._rowEnd_0_0value) !== (value)))
        {
            this._rowEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowEnd_0_0value = value
        } else
        {
            this._rowEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    columnStart(value: number | undefined): this {
        if (((this._columnStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._columnStart_0_0value) !== (value)))
        {
            this._columnStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnStart_0_0value = value
        } else
        {
            this._columnStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    columnEnd(value: number | undefined): this {
        if (((this._columnEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._columnEnd_0_0value) !== (value)))
        {
            this._columnEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnEnd_0_0value = value
        } else
        {
            this._columnEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectable(value: boolean | undefined): this {
        if (((this._selectable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._selectable_0_0value) !== (value)))
        {
            this._selectable_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectable_0_0value = value
        } else
        {
            this._selectable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._selected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selected_0_flag = AttributeUpdaterFlag.UPDATE
            this._selected_0_0value = value
        } else
        {
            this._selected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        if (((this._onSelect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelect_0_0value = value
        } else
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class GridItemOptions_serializer {
    public static write(buffer: SerializerBase, value: GridItemOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as GridItemStyle)
            valueSerializer.writeInt32(TypeChecker.GridItemStyle_ToNumeric(valueHolderForStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridItemOptions {
        let valueDeserializer : DeserializerBase = buffer
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : GridItemStyle | undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = TypeChecker.GridItemStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const styleTmpResult : GridItemStyle | undefined = styleTmpBuf
        let value : GridItemOptions = ({style: styleTmpResult} as GridItemOptions)
        return value
    }
}
