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
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ItemAlign } from "./enums"
import { AttributeModifier, hookGridRowAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Length } from "./units"
import { Resource } from "global.resource"
import { GridRowModifier } from "./../GridRowModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
import { ModifierStateManager } from '../CommonModifier';

export class ArkGridRowPeer extends ArkCommonMethodPeer {
    attributeSet?: GridRowModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridRowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridRow_construct(peerId, flags)
        const _peer  = new ArkGridRowPeer(_peerPtr, peerId, 'GridRow', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridRowOptionsAttribute(option?: GridRowOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (option !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionTmpValue  = option!
            GridRowOptions_serializer.write(thisSerializer, optionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridRowInterface_setGridRowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBreakpointChangeAttribute(value: ((breakpoints: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridRowAttribute_setOnBreakpointChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: ItemAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ItemAlign)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridRowAttribute_setAlignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    xs?: int32;
    sm?: int32;
    md?: int32;
    lg?: int32;
    xl?: int32;
    xxl?: int32;
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
    columns?: int32 | GridRowColumnOption;
    breakpoints?: BreakPoints;
    direction?: GridRowDirection;
}
export interface GridRowAttribute extends CommonMethod {
    setGridRowOptions(option?: GridRowOptions): this {
        throw new Error("Unimplemented method setGridRowOptions")
    }
    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        throw new Error("Unimplemented method onBreakpointChange")
    }
    alignItems(value: ItemAlign | undefined): this {
        throw new Error("Unimplemented method alignItems")
    }
    attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkGridRowStyle extends ArkCommonMethodStyle implements GridRowAttribute {
    onBreakpointChange_value?: ((breakpoints: string) => void) | undefined
    alignItems_value?: ItemAlign | undefined
    attributeModifier_value?: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined
    setGridRowOptions(option?: GridRowOptions): this {
        return this
    }
    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        return this
    }
    alignItems(value: ItemAlign | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkGridRowComponent extends ArkCommonMethodComponent implements GridRowAttribute {
    getPeer(): ArkGridRowPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkGridRowPeer)
    }
    public setGridRowOptions(option?: GridRowOptions): this {
        if (this.checkPriority("setGridRowOptions")) {
            const option_casted = option as (GridRowOptions | undefined)
            this.getPeer()?.setGridRowOptionsAttribute(option_casted)
            this.applyOptionsFinish('GridRowAttribute');
            return this
        }
        return this
    }
    public onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        if (this.checkPriority("onBreakpointChange")) {
            const value_casted = value as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.setOnBreakpointChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public alignItems(value: ItemAlign | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (ItemAlign | undefined)
            this.getPeer()?.setAlignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookGridRowAttributeModifier(this, value);
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
export function GridRowImpl(
    @memo
    style: ((attributes: GridRowAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkGridRowComponent>((): ArkGridRowComponent => {
        return new ArkGridRowComponent()
    })
    NodeAttach<ArkGridRowPeer>((): ArkGridRowPeer => ArkGridRowPeer.create(receiver), (peer: ArkGridRowPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class BreakPoints_serializer {
    public static write(buffer: SerializerBase, value: BreakPoints): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            valueSerializer.writeInt32((valueHolderForValueTmpValue.length).toInt())
            for (let valueHolderForValueTmpValueCounterI = 0; valueHolderForValueTmpValueCounterI < valueHolderForValueTmpValue.length; valueHolderForValueTmpValueCounterI++) {
                const valueHolderForValueTmpValueTmpElement : string = valueHolderForValueTmpValue[valueHolderForValueTmpValueCounterI]
                valueSerializer.writeString(valueHolderForValueTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForReference  = value.reference
        if (valueHolderForReference !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForReferenceTmpValue  = (valueHolderForReference as BreakpointsReference)
            valueSerializer.writeInt32(valueHolderForReferenceTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BreakPoints {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let valueTmpBuf : Array<string> | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let valueTmpBuf_ : Array<string> = new Array<string>(valueTmpBuf_Length)
            for (let valueTmpBuf_BufCounterI = 0; valueTmpBuf_BufCounterI < valueTmpBuf_Length; valueTmpBuf_BufCounterI++) {
                valueTmpBuf_[valueTmpBuf_BufCounterI] = (valueDeserializer.readString() as string)
            }
            valueTmpBuf = valueTmpBuf_
        }
        const valueTmpResult : Array<string> | undefined = valueTmpBuf
        const referenceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let referenceTmpBuf : BreakpointsReference | undefined = undefined
        if ((referenceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            referenceTmpBuf = BreakpointsReference.fromValue(valueDeserializer.readInt32())
        }
        const referenceTmpResult : BreakpointsReference | undefined = referenceTmpBuf
        let value : BreakPoints = ({value: valueTmpResult, reference: referenceTmpResult} as BreakPoints)
        return value
    }
}
export class GridRowColumnOption_serializer {
    public static write(buffer: SerializerBase, value: GridRowColumnOption): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForXs  = value.xs
        if (valueHolderForXs !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXsTmpValue  = valueHolderForXs!
            valueSerializer.writeInt32(valueHolderForXsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSm  = value.sm
        if (valueHolderForSm !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSmTmpValue  = valueHolderForSm!
            valueSerializer.writeInt32(valueHolderForSmTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMd  = value.md
        if (valueHolderForMd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMdTmpValue  = valueHolderForMd!
            valueSerializer.writeInt32(valueHolderForMdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLg  = value.lg
        if (valueHolderForLg !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLgTmpValue  = valueHolderForLg!
            valueSerializer.writeInt32(valueHolderForLgTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXl  = value.xl
        if (valueHolderForXl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXlTmpValue  = valueHolderForXl!
            valueSerializer.writeInt32(valueHolderForXlTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXxl  = value.xxl
        if (valueHolderForXxl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXxlTmpValue  = valueHolderForXxl!
            valueSerializer.writeInt32(valueHolderForXxlTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridRowColumnOption {
        let valueDeserializer : DeserializerBase = buffer
        const xsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xsTmpBuf : int32 | undefined = undefined
        if ((xsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xsTmpBuf = valueDeserializer.readInt32()
        }
        const xsTmpResult : int32 | undefined = xsTmpBuf
        const smTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let smTmpBuf : int32 | undefined = undefined
        if ((smTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            smTmpBuf = valueDeserializer.readInt32()
        }
        const smTmpResult : int32 | undefined = smTmpBuf
        const mdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mdTmpBuf : int32 | undefined = undefined
        if ((mdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mdTmpBuf = valueDeserializer.readInt32()
        }
        const mdTmpResult : int32 | undefined = mdTmpBuf
        const lgTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lgTmpBuf : int32 | undefined = undefined
        if ((lgTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lgTmpBuf = valueDeserializer.readInt32()
        }
        const lgTmpResult : int32 | undefined = lgTmpBuf
        const xlTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xlTmpBuf : int32 | undefined = undefined
        if ((xlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xlTmpBuf = valueDeserializer.readInt32()
        }
        const xlTmpResult : int32 | undefined = xlTmpBuf
        const xxlTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xxlTmpBuf : int32 | undefined = undefined
        if ((xxlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xxlTmpBuf = valueDeserializer.readInt32()
        }
        const xxlTmpResult : int32 | undefined = xxlTmpBuf
        let value : GridRowColumnOption = ({xs: xsTmpResult, sm: smTmpResult, md: mdTmpResult, lg: lgTmpResult, xl: xlTmpResult, xxl: xxlTmpResult} as GridRowColumnOption)
        return value
    }
}
export class GridRowSizeOption_serializer {
    public static write(buffer: SerializerBase, value: GridRowSizeOption): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForXs  = value.xs
        if (valueHolderForXs !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXsTmpValue  = valueHolderForXs!
            if (valueHolderForXsTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForXsTmpValueForIdx0  = valueHolderForXsTmpValue as string
                valueSerializer.writeString(valueHolderForXsTmpValueForIdx0)
            } else if (valueHolderForXsTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForXsTmpValueForIdx1  = valueHolderForXsTmpValue as double
                valueSerializer.writeFloat64(valueHolderForXsTmpValueForIdx1)
            } else if (valueHolderForXsTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForXsTmpValueForIdx2  = valueHolderForXsTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForXsTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSm  = value.sm
        if (valueHolderForSm !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSmTmpValue  = valueHolderForSm!
            if (valueHolderForSmTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSmTmpValueForIdx0  = valueHolderForSmTmpValue as string
                valueSerializer.writeString(valueHolderForSmTmpValueForIdx0)
            } else if (valueHolderForSmTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSmTmpValueForIdx1  = valueHolderForSmTmpValue as double
                valueSerializer.writeFloat64(valueHolderForSmTmpValueForIdx1)
            } else if (valueHolderForSmTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSmTmpValueForIdx2  = valueHolderForSmTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSmTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMd  = value.md
        if (valueHolderForMd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMdTmpValue  = valueHolderForMd!
            if (valueHolderForMdTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMdTmpValueForIdx0  = valueHolderForMdTmpValue as string
                valueSerializer.writeString(valueHolderForMdTmpValueForIdx0)
            } else if (valueHolderForMdTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMdTmpValueForIdx1  = valueHolderForMdTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMdTmpValueForIdx1)
            } else if (valueHolderForMdTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMdTmpValueForIdx2  = valueHolderForMdTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMdTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLg  = value.lg
        if (valueHolderForLg !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLgTmpValue  = valueHolderForLg!
            if (valueHolderForLgTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLgTmpValueForIdx0  = valueHolderForLgTmpValue as string
                valueSerializer.writeString(valueHolderForLgTmpValueForIdx0)
            } else if (valueHolderForLgTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLgTmpValueForIdx1  = valueHolderForLgTmpValue as double
                valueSerializer.writeFloat64(valueHolderForLgTmpValueForIdx1)
            } else if (valueHolderForLgTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLgTmpValueForIdx2  = valueHolderForLgTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForLgTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXl  = value.xl
        if (valueHolderForXl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXlTmpValue  = valueHolderForXl!
            if (valueHolderForXlTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForXlTmpValueForIdx0  = valueHolderForXlTmpValue as string
                valueSerializer.writeString(valueHolderForXlTmpValueForIdx0)
            } else if (valueHolderForXlTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForXlTmpValueForIdx1  = valueHolderForXlTmpValue as double
                valueSerializer.writeFloat64(valueHolderForXlTmpValueForIdx1)
            } else if (valueHolderForXlTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForXlTmpValueForIdx2  = valueHolderForXlTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForXlTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXxl  = value.xxl
        if (valueHolderForXxl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXxlTmpValue  = valueHolderForXxl!
            if (valueHolderForXxlTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForXxlTmpValueForIdx0  = valueHolderForXxlTmpValue as string
                valueSerializer.writeString(valueHolderForXxlTmpValueForIdx0)
            } else if (valueHolderForXxlTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForXxlTmpValueForIdx1  = valueHolderForXxlTmpValue as double
                valueSerializer.writeFloat64(valueHolderForXxlTmpValueForIdx1)
            } else if (valueHolderForXxlTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForXxlTmpValueForIdx2  = valueHolderForXxlTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForXxlTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridRowSizeOption {
        let valueDeserializer : DeserializerBase = buffer
        const xsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xsTmpBuf : Length | undefined = undefined
        if ((xsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xsTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let xsTmpBuf_ : string | double | Resource | undefined
            if (xsTmpBuf_UnionSelector == (0).toChar()) {
                xsTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (xsTmpBuf_UnionSelector == (1).toChar()) {
                xsTmpBuf_ = valueDeserializer.readFloat64()
            } else if (xsTmpBuf_UnionSelector == (2).toChar()) {
                xsTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for xsTmpBuf_ has to be chosen through deserialisation.")
            }
            xsTmpBuf = (xsTmpBuf_ as string | double | Resource)
        }
        const xsTmpResult : Length | undefined = xsTmpBuf
        const smTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let smTmpBuf : Length | undefined = undefined
        if ((smTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const smTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let smTmpBuf_ : string | double | Resource | undefined
            if (smTmpBuf_UnionSelector == (0).toChar()) {
                smTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (smTmpBuf_UnionSelector == (1).toChar()) {
                smTmpBuf_ = valueDeserializer.readFloat64()
            } else if (smTmpBuf_UnionSelector == (2).toChar()) {
                smTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for smTmpBuf_ has to be chosen through deserialisation.")
            }
            smTmpBuf = (smTmpBuf_ as string | double | Resource)
        }
        const smTmpResult : Length | undefined = smTmpBuf
        const mdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mdTmpBuf : Length | undefined = undefined
        if ((mdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const mdTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let mdTmpBuf_ : string | double | Resource | undefined
            if (mdTmpBuf_UnionSelector == (0).toChar()) {
                mdTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (mdTmpBuf_UnionSelector == (1).toChar()) {
                mdTmpBuf_ = valueDeserializer.readFloat64()
            } else if (mdTmpBuf_UnionSelector == (2).toChar()) {
                mdTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for mdTmpBuf_ has to be chosen through deserialisation.")
            }
            mdTmpBuf = (mdTmpBuf_ as string | double | Resource)
        }
        const mdTmpResult : Length | undefined = mdTmpBuf
        const lgTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lgTmpBuf : Length | undefined = undefined
        if ((lgTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const lgTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let lgTmpBuf_ : string | double | Resource | undefined
            if (lgTmpBuf_UnionSelector == (0).toChar()) {
                lgTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (lgTmpBuf_UnionSelector == (1).toChar()) {
                lgTmpBuf_ = valueDeserializer.readFloat64()
            } else if (lgTmpBuf_UnionSelector == (2).toChar()) {
                lgTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for lgTmpBuf_ has to be chosen through deserialisation.")
            }
            lgTmpBuf = (lgTmpBuf_ as string | double | Resource)
        }
        const lgTmpResult : Length | undefined = lgTmpBuf
        const xlTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xlTmpBuf : Length | undefined = undefined
        if ((xlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xlTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let xlTmpBuf_ : string | double | Resource | undefined
            if (xlTmpBuf_UnionSelector == (0).toChar()) {
                xlTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (xlTmpBuf_UnionSelector == (1).toChar()) {
                xlTmpBuf_ = valueDeserializer.readFloat64()
            } else if (xlTmpBuf_UnionSelector == (2).toChar()) {
                xlTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for xlTmpBuf_ has to be chosen through deserialisation.")
            }
            xlTmpBuf = (xlTmpBuf_ as string | double | Resource)
        }
        const xlTmpResult : Length | undefined = xlTmpBuf
        const xxlTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xxlTmpBuf : Length | undefined = undefined
        if ((xxlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xxlTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let xxlTmpBuf_ : string | double | Resource | undefined
            if (xxlTmpBuf_UnionSelector == (0).toChar()) {
                xxlTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (xxlTmpBuf_UnionSelector == (1).toChar()) {
                xxlTmpBuf_ = valueDeserializer.readFloat64()
            } else if (xxlTmpBuf_UnionSelector == (2).toChar()) {
                xxlTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for xxlTmpBuf_ has to be chosen through deserialisation.")
            }
            xxlTmpBuf = (xxlTmpBuf_ as string | double | Resource)
        }
        const xxlTmpResult : Length | undefined = xxlTmpBuf
        let value : GridRowSizeOption = ({xs: xsTmpResult, sm: smTmpResult, md: mdTmpResult, lg: lgTmpResult, xl: xlTmpResult, xxl: xxlTmpResult} as GridRowSizeOption)
        return value
    }
}
export class GutterOption_serializer {
    public static write(buffer: SerializerBase, value: GutterOption): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        if (valueHolderForX !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXTmpValue  = valueHolderForX!
            if (valueHolderForXTmpValue instanceof Length) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForXTmpValueForIdx0  = valueHolderForXTmpValue as Length
                if (valueHolderForXTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForXTmpValueForIdx0ForIdx0  = valueHolderForXTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForXTmpValueForIdx0ForIdx0)
                } else if (valueHolderForXTmpValueForIdx0 instanceof double) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForXTmpValueForIdx0ForIdx1  = valueHolderForXTmpValueForIdx0 as double
                    valueSerializer.writeFloat64(valueHolderForXTmpValueForIdx0ForIdx1)
                } else if (valueHolderForXTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForXTmpValueForIdx0ForIdx2  = valueHolderForXTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForXTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForXTmpValue instanceof GridRowSizeOption) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForXTmpValueForIdx1  = valueHolderForXTmpValue as GridRowSizeOption
                GridRowSizeOption_serializer.write(valueSerializer, valueHolderForXTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForY  = value.y
        if (valueHolderForY !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForYTmpValue  = valueHolderForY!
            if (valueHolderForYTmpValue instanceof Length) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForYTmpValueForIdx0  = valueHolderForYTmpValue as Length
                if (valueHolderForYTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForYTmpValueForIdx0ForIdx0  = valueHolderForYTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForYTmpValueForIdx0ForIdx0)
                } else if (valueHolderForYTmpValueForIdx0 instanceof double) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForYTmpValueForIdx0ForIdx1  = valueHolderForYTmpValueForIdx0 as double
                    valueSerializer.writeFloat64(valueHolderForYTmpValueForIdx0ForIdx1)
                } else if (valueHolderForYTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForYTmpValueForIdx0ForIdx2  = valueHolderForYTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForYTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForYTmpValue instanceof GridRowSizeOption) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForYTmpValueForIdx1  = valueHolderForYTmpValue as GridRowSizeOption
                GridRowSizeOption_serializer.write(valueSerializer, valueHolderForYTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GutterOption {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xTmpBuf : Length | GridRowSizeOption | undefined = undefined
        if ((xTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let xTmpBuf_ : Length | GridRowSizeOption | undefined
            if (xTmpBuf_UnionSelector == (0).toChar()) {
                const xTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let xTmpBuf_BufU : string | double | Resource | undefined
                if (xTmpBuf_BufUUnionSelector == (0).toChar()) {
                    xTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (xTmpBuf_BufUUnionSelector == (1).toChar()) {
                    xTmpBuf_BufU = valueDeserializer.readFloat64()
                } else if (xTmpBuf_BufUUnionSelector == (2).toChar()) {
                    xTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for xTmpBuf_BufU has to be chosen through deserialisation.")
                }
                xTmpBuf_ = (xTmpBuf_BufU as string | double | Resource)
            } else if (xTmpBuf_UnionSelector == (1).toChar()) {
                xTmpBuf_ = GridRowSizeOption_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for xTmpBuf_ has to be chosen through deserialisation.")
            }
            xTmpBuf = (xTmpBuf_ as Length | GridRowSizeOption)
        }
        const xTmpResult : Length | GridRowSizeOption | undefined = xTmpBuf
        const yTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let yTmpBuf : Length | GridRowSizeOption | undefined = undefined
        if ((yTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const yTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let yTmpBuf_ : Length | GridRowSizeOption | undefined
            if (yTmpBuf_UnionSelector == (0).toChar()) {
                const yTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let yTmpBuf_BufU : string | double | Resource | undefined
                if (yTmpBuf_BufUUnionSelector == (0).toChar()) {
                    yTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (yTmpBuf_BufUUnionSelector == (1).toChar()) {
                    yTmpBuf_BufU = valueDeserializer.readFloat64()
                } else if (yTmpBuf_BufUUnionSelector == (2).toChar()) {
                    yTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for yTmpBuf_BufU has to be chosen through deserialisation.")
                }
                yTmpBuf_ = (yTmpBuf_BufU as string | double | Resource)
            } else if (yTmpBuf_UnionSelector == (1).toChar()) {
                yTmpBuf_ = GridRowSizeOption_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for yTmpBuf_ has to be chosen through deserialisation.")
            }
            yTmpBuf = (yTmpBuf_ as Length | GridRowSizeOption)
        }
        const yTmpResult : Length | GridRowSizeOption | undefined = yTmpBuf
        let value : GutterOption = ({x: xTmpResult, y: yTmpResult} as GutterOption)
        return value
    }
}
export class GridRowOptions_serializer {
    public static write(buffer: SerializerBase, value: GridRowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForGutter  = value.gutter
        if (valueHolderForGutter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGutterTmpValue  = valueHolderForGutter!
            if (valueHolderForGutterTmpValue instanceof Length) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForGutterTmpValueForIdx0  = valueHolderForGutterTmpValue as Length
                if (valueHolderForGutterTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForGutterTmpValueForIdx0ForIdx0  = valueHolderForGutterTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForGutterTmpValueForIdx0ForIdx0)
                } else if (valueHolderForGutterTmpValueForIdx0 instanceof double) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForGutterTmpValueForIdx0ForIdx1  = valueHolderForGutterTmpValueForIdx0 as double
                    valueSerializer.writeFloat64(valueHolderForGutterTmpValueForIdx0ForIdx1)
                } else if (valueHolderForGutterTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForGutterTmpValueForIdx0ForIdx2  = valueHolderForGutterTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForGutterTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForGutterTmpValue instanceof GutterOption) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForGutterTmpValueForIdx1  = valueHolderForGutterTmpValue as GutterOption
                GutterOption_serializer.write(valueSerializer, valueHolderForGutterTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColumns  = value.columns
        if (valueHolderForColumns !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColumnsTmpValue  = valueHolderForColumns!
            if (valueHolderForColumnsTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColumnsTmpValueForIdx0  = valueHolderForColumnsTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColumnsTmpValueForIdx0)
            } else if (valueHolderForColumnsTmpValue instanceof GridRowColumnOption) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColumnsTmpValueForIdx1  = valueHolderForColumnsTmpValue as GridRowColumnOption
                GridRowColumnOption_serializer.write(valueSerializer, valueHolderForColumnsTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBreakpoints  = value.breakpoints
        if (valueHolderForBreakpoints !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBreakpointsTmpValue  = valueHolderForBreakpoints!
            BreakPoints_serializer.write(valueSerializer, valueHolderForBreakpointsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDirection  = value.direction
        if (valueHolderForDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDirectionTmpValue  = (valueHolderForDirection as GridRowDirection)
            valueSerializer.writeInt32(valueHolderForDirectionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridRowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const gutterTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gutterTmpBuf : Length | GutterOption | undefined = undefined
        if ((gutterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const gutterTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let gutterTmpBuf_ : Length | GutterOption | undefined
            if (gutterTmpBuf_UnionSelector == (0).toChar()) {
                const gutterTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let gutterTmpBuf_BufU : string | double | Resource | undefined
                if (gutterTmpBuf_BufUUnionSelector == (0).toChar()) {
                    gutterTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (gutterTmpBuf_BufUUnionSelector == (1).toChar()) {
                    gutterTmpBuf_BufU = valueDeserializer.readFloat64()
                } else if (gutterTmpBuf_BufUUnionSelector == (2).toChar()) {
                    gutterTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for gutterTmpBuf_BufU has to be chosen through deserialisation.")
                }
                gutterTmpBuf_ = (gutterTmpBuf_BufU as string | double | Resource)
            } else if (gutterTmpBuf_UnionSelector == (1).toChar()) {
                gutterTmpBuf_ = GutterOption_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for gutterTmpBuf_ has to be chosen through deserialisation.")
            }
            gutterTmpBuf = (gutterTmpBuf_ as Length | GutterOption)
        }
        const gutterTmpResult : Length | GutterOption | undefined = gutterTmpBuf
        const columnsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let columnsTmpBuf : int32 | GridRowColumnOption | undefined = undefined
        if ((columnsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const columnsTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let columnsTmpBuf_ : int32 | GridRowColumnOption | undefined
            if (columnsTmpBuf_UnionSelector == (0).toChar()) {
                columnsTmpBuf_ = valueDeserializer.readInt32()
            } else if (columnsTmpBuf_UnionSelector == (1).toChar()) {
                columnsTmpBuf_ = GridRowColumnOption_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for columnsTmpBuf_ has to be chosen through deserialisation.")
            }
            columnsTmpBuf = (columnsTmpBuf_ as int32 | GridRowColumnOption)
        }
        const columnsTmpResult : int32 | GridRowColumnOption | undefined = columnsTmpBuf
        const breakpointsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let breakpointsTmpBuf : BreakPoints | undefined = undefined
        if ((breakpointsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            breakpointsTmpBuf = BreakPoints_serializer.read(valueDeserializer)
        }
        const breakpointsTmpResult : BreakPoints | undefined = breakpointsTmpBuf
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let directionTmpBuf : GridRowDirection | undefined = undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = GridRowDirection.fromValue(valueDeserializer.readInt32())
        }
        const directionTmpResult : GridRowDirection | undefined = directionTmpBuf
        let value : GridRowOptions = ({gutter: gutterTmpResult, columns: columnsTmpResult, breakpoints: breakpointsTmpResult, direction: directionTmpResult} as GridRowOptions)
        return value
    }
}
