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
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { AttributeModifier, hookGridItemAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { GridItemModifier } from "./../GridItemModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkGridItemPeer extends ArkCommonMethodPeer {
    attributeSet?: GridItemModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    setGridItemOptions(value?: GridItemOptions): this {
        throw new Error("Unimplemented method setGridItemOptions")
    }
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
    setGridItemOptions(value?: GridItemOptions): this {
        return this
    }
    rowStart(value: number | undefined): this {
        return this
    }
    rowEnd(value: number | undefined): this {
        return this
    }
    columnStart(value: number | undefined): this {
        return this
    }
    columnEnd(value: number | undefined): this {
        return this
    }
    selectable(value: boolean | undefined): this {
        return this
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        return this
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkGridItemComponent extends ArkCommonMethodComponent implements GridItemAttribute {
    getPeer(): ArkGridItemPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkGridItemPeer)
    }
    public setGridItemOptions(value?: GridItemOptions): this {
        if (this.checkPriority("setGridItemOptions")) {
            const value_casted = value as (GridItemOptions | undefined)
            this.getPeer()?.setGridItemOptionsAttribute(value_casted)
            this.applyOptionsFinish('GridItemAttribute');
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
        hookGridItemAttributeModifier(this, value);
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
export function GridItemImpl(
    @memo
    style: ((attributes: GridItemAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkGridItemComponent>((): ArkGridItemComponent => {
        return new ArkGridItemComponent()
    })
    NodeAttach<ArkGridItemPeer>((): ArkGridItemPeer => ArkGridItemPeer.create(receiver), (peer: ArkGridItemPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class GridItemOptions_serializer {
    public static write(buffer: SerializerBase, value: GridItemOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as GridItemStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridItemOptions {
        let valueDeserializer : DeserializerBase = buffer
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : GridItemStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = GridItemStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : GridItemStyle | undefined = styleTmpBuf
        let value : GridItemOptions = ({style: styleTmpResult} as GridItemOptions)
        return value
    }
}
