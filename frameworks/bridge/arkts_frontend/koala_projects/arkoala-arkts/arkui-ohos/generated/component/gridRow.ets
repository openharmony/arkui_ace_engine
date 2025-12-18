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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { ItemAlign } from './enums'
import { AttributeModifier, hookGridRowAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Length, Resource as arkui_component_units_Resource } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { GridRowModifier } from './../GridRowModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkGridRowPeer extends ArkCommonMethodPeer {
    attributeSet?: GridRowModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
    WindowSize = 0,
    ComponentSize = 1,
    WINDOW_SIZE = 0,
    COMPONENT_SIZE = 1
}
export enum GridRowDirection {
    Row = 0,
    RowReverse = 1,
    ROW = 0,
    ROW_REVERSE = 1
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
        throw new Error('Unimplemented method setGridRowOptions')
    }
    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        throw new Error('Unimplemented method onBreakpointChange')
    }
    alignItems(value: ItemAlign | undefined): this {
        throw new Error('Unimplemented method alignItems')
    }
    attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkGridRowComponent extends ArkCommonMethodComponent implements GridRowAttribute {
    getPeer(): ArkGridRowPeer {
        return (this.peer as ArkGridRowPeer)
    }
    public setGridRowOptions(option?: GridRowOptions): this {
        if (this.checkPriority('setGridRowOptions')) {
            const option_casted = option as (GridRowOptions | undefined)
            this.getPeer()?.setGridRowOptionsAttribute(option_casted)
            this.applyOptionsFinish('GridRowAttribute');
            return this
        }
        return this
    }
    public onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        if (this.checkPriority('onBreakpointChange')) {
            const value_casted = value as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.setOnBreakpointChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public alignItems(value: ItemAlign | undefined): this {
        if (this.checkPriority('alignItems')) {
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
    @memo @memo_skip
    style: ((attributes: GridRowAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkGridRowComponent>((): ArkGridRowComponent => {
        return new ArkGridRowComponent()
    })
    NodeAttach<ArkGridRowPeer>((): ArkGridRowPeer => ArkGridRowPeer.create(receiver), (_: ArkGridRowPeer): void => {
        style?.(receiver)
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
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let valueTmpBuf : Array<string> | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let valueTmpBufOpt : Array<string> = new Array<string>(valueTmpBufOptLength)
            for (let valueTmpBufOptBufCounterI = 0; valueTmpBufOptBufCounterI < valueTmpBufOptLength; valueTmpBufOptBufCounterI++) {
                valueTmpBufOpt[valueTmpBufOptBufCounterI] = (valueDeserializer.readString() as string)
            }
            valueTmpBuf = valueTmpBufOpt
        }
        const valueTmpResult : Array<string> | undefined = valueTmpBuf
        const referenceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
        const xsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xsTmpBuf : int32 | undefined = undefined
        if ((xsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xsTmpBuf = valueDeserializer.readInt32()
        }
        const xsTmpResult : int32 | undefined = xsTmpBuf
        const smTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let smTmpBuf : int32 | undefined = undefined
        if ((smTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            smTmpBuf = valueDeserializer.readInt32()
        }
        const smTmpResult : int32 | undefined = smTmpBuf
        const mdTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let mdTmpBuf : int32 | undefined = undefined
        if ((mdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mdTmpBuf = valueDeserializer.readInt32()
        }
        const mdTmpResult : int32 | undefined = mdTmpBuf
        const lgTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lgTmpBuf : int32 | undefined = undefined
        if ((lgTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lgTmpBuf = valueDeserializer.readInt32()
        }
        const lgTmpResult : int32 | undefined = lgTmpBuf
        const xlTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xlTmpBuf : int32 | undefined = undefined
        if ((xlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xlTmpBuf = valueDeserializer.readInt32()
        }
        const xlTmpResult : int32 | undefined = xlTmpBuf
        const xxlTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
            } else if (valueHolderForXsTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForXsTmpValueForIdx2  = valueHolderForXsTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForXsTmpValueForIdx2)
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
            } else if (valueHolderForSmTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSmTmpValueForIdx2  = valueHolderForSmTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSmTmpValueForIdx2)
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
            } else if (valueHolderForMdTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMdTmpValueForIdx2  = valueHolderForMdTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMdTmpValueForIdx2)
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
            } else if (valueHolderForLgTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLgTmpValueForIdx2  = valueHolderForLgTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLgTmpValueForIdx2)
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
            } else if (valueHolderForXlTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForXlTmpValueForIdx2  = valueHolderForXlTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForXlTmpValueForIdx2)
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
            } else if (valueHolderForXxlTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForXxlTmpValueForIdx2  = valueHolderForXxlTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForXxlTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridRowSizeOption {
        let valueDeserializer : DeserializerBase = buffer
        const xsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xsTmpBuf : Length | undefined = undefined
        if ((xsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xsTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let xsTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (xsTmpBufOptUnionSelector == (0).toByte()) {
                xsTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (xsTmpBufOptUnionSelector == (1).toByte()) {
                xsTmpBufOpt = valueDeserializer.readFloat64()
            } else if (xsTmpBufOptUnionSelector == (2).toByte()) {
                xsTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for xsTmpBufOpt has to be chosen through deserialisation.')
            }
            xsTmpBuf = (xsTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const xsTmpResult : Length | undefined = xsTmpBuf
        const smTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let smTmpBuf : Length | undefined = undefined
        if ((smTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const smTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let smTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (smTmpBufOptUnionSelector == (0).toByte()) {
                smTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (smTmpBufOptUnionSelector == (1).toByte()) {
                smTmpBufOpt = valueDeserializer.readFloat64()
            } else if (smTmpBufOptUnionSelector == (2).toByte()) {
                smTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for smTmpBufOpt has to be chosen through deserialisation.')
            }
            smTmpBuf = (smTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const smTmpResult : Length | undefined = smTmpBuf
        const mdTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let mdTmpBuf : Length | undefined = undefined
        if ((mdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const mdTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let mdTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (mdTmpBufOptUnionSelector == (0).toByte()) {
                mdTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (mdTmpBufOptUnionSelector == (1).toByte()) {
                mdTmpBufOpt = valueDeserializer.readFloat64()
            } else if (mdTmpBufOptUnionSelector == (2).toByte()) {
                mdTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for mdTmpBufOpt has to be chosen through deserialisation.')
            }
            mdTmpBuf = (mdTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const mdTmpResult : Length | undefined = mdTmpBuf
        const lgTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lgTmpBuf : Length | undefined = undefined
        if ((lgTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const lgTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let lgTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (lgTmpBufOptUnionSelector == (0).toByte()) {
                lgTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (lgTmpBufOptUnionSelector == (1).toByte()) {
                lgTmpBufOpt = valueDeserializer.readFloat64()
            } else if (lgTmpBufOptUnionSelector == (2).toByte()) {
                lgTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for lgTmpBufOpt has to be chosen through deserialisation.')
            }
            lgTmpBuf = (lgTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const lgTmpResult : Length | undefined = lgTmpBuf
        const xlTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xlTmpBuf : Length | undefined = undefined
        if ((xlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xlTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let xlTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (xlTmpBufOptUnionSelector == (0).toByte()) {
                xlTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (xlTmpBufOptUnionSelector == (1).toByte()) {
                xlTmpBufOpt = valueDeserializer.readFloat64()
            } else if (xlTmpBufOptUnionSelector == (2).toByte()) {
                xlTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for xlTmpBufOpt has to be chosen through deserialisation.')
            }
            xlTmpBuf = (xlTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const xlTmpResult : Length | undefined = xlTmpBuf
        const xxlTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xxlTmpBuf : Length | undefined = undefined
        if ((xxlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xxlTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let xxlTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (xxlTmpBufOptUnionSelector == (0).toByte()) {
                xxlTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (xxlTmpBufOptUnionSelector == (1).toByte()) {
                xxlTmpBufOpt = valueDeserializer.readFloat64()
            } else if (xxlTmpBufOptUnionSelector == (2).toByte()) {
                xxlTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for xxlTmpBufOpt has to be chosen through deserialisation.')
            }
            xxlTmpBuf = (xxlTmpBufOpt as string | double | arkui_component_units_Resource)
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
                } else if (valueHolderForXTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForXTmpValueForIdx0ForIdx2  = valueHolderForXTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForXTmpValueForIdx0ForIdx2)
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
                } else if (valueHolderForYTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForYTmpValueForIdx0ForIdx2  = valueHolderForYTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForYTmpValueForIdx0ForIdx2)
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
        const xTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xTmpBuf : Length | GridRowSizeOption | undefined = undefined
        if ((xTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let xTmpBufOpt : Length | GridRowSizeOption | undefined
            if (xTmpBufOptUnionSelector == (0).toByte()) {
                const xTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let xTmpBufOptBufU : string | double | arkui_component_units_Resource | undefined
                if (xTmpBufOptBufUUnionSelector == (0).toByte()) {
                    xTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (xTmpBufOptBufUUnionSelector == (1).toByte()) {
                    xTmpBufOptBufU = valueDeserializer.readFloat64()
                } else if (xTmpBufOptBufUUnionSelector == (2).toByte()) {
                    xTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for xTmpBufOptBufU has to be chosen through deserialisation.')
                }
                xTmpBufOpt = (xTmpBufOptBufU as string | double | arkui_component_units_Resource)
            } else if (xTmpBufOptUnionSelector == (1).toByte()) {
                xTmpBufOpt = GridRowSizeOption_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for xTmpBufOpt has to be chosen through deserialisation.')
            }
            xTmpBuf = (xTmpBufOpt as Length | GridRowSizeOption)
        }
        const xTmpResult : Length | GridRowSizeOption | undefined = xTmpBuf
        const yTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let yTmpBuf : Length | GridRowSizeOption | undefined = undefined
        if ((yTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const yTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let yTmpBufOpt : Length | GridRowSizeOption | undefined
            if (yTmpBufOptUnionSelector == (0).toByte()) {
                const yTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let yTmpBufOptBufU : string | double | arkui_component_units_Resource | undefined
                if (yTmpBufOptBufUUnionSelector == (0).toByte()) {
                    yTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (yTmpBufOptBufUUnionSelector == (1).toByte()) {
                    yTmpBufOptBufU = valueDeserializer.readFloat64()
                } else if (yTmpBufOptBufUUnionSelector == (2).toByte()) {
                    yTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for yTmpBufOptBufU has to be chosen through deserialisation.')
                }
                yTmpBufOpt = (yTmpBufOptBufU as string | double | arkui_component_units_Resource)
            } else if (yTmpBufOptUnionSelector == (1).toByte()) {
                yTmpBufOpt = GridRowSizeOption_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for yTmpBufOpt has to be chosen through deserialisation.')
            }
            yTmpBuf = (yTmpBufOpt as Length | GridRowSizeOption)
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
                } else if (valueHolderForGutterTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForGutterTmpValueForIdx0ForIdx2  = valueHolderForGutterTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForGutterTmpValueForIdx0ForIdx2)
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
        const gutterTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let gutterTmpBuf : Length | GutterOption | undefined = undefined
        if ((gutterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const gutterTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let gutterTmpBufOpt : Length | GutterOption | undefined
            if (gutterTmpBufOptUnionSelector == (0).toByte()) {
                const gutterTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let gutterTmpBufOptBufU : string | double | arkui_component_units_Resource | undefined
                if (gutterTmpBufOptBufUUnionSelector == (0).toByte()) {
                    gutterTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (gutterTmpBufOptBufUUnionSelector == (1).toByte()) {
                    gutterTmpBufOptBufU = valueDeserializer.readFloat64()
                } else if (gutterTmpBufOptBufUUnionSelector == (2).toByte()) {
                    gutterTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for gutterTmpBufOptBufU has to be chosen through deserialisation.')
                }
                gutterTmpBufOpt = (gutterTmpBufOptBufU as string | double | arkui_component_units_Resource)
            } else if (gutterTmpBufOptUnionSelector == (1).toByte()) {
                gutterTmpBufOpt = GutterOption_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for gutterTmpBufOpt has to be chosen through deserialisation.')
            }
            gutterTmpBuf = (gutterTmpBufOpt as Length | GutterOption)
        }
        const gutterTmpResult : Length | GutterOption | undefined = gutterTmpBuf
        const columnsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let columnsTmpBuf : int32 | GridRowColumnOption | undefined = undefined
        if ((columnsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const columnsTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let columnsTmpBufOpt : int32 | GridRowColumnOption | undefined
            if (columnsTmpBufOptUnionSelector == (0).toByte()) {
                columnsTmpBufOpt = valueDeserializer.readInt32()
            } else if (columnsTmpBufOptUnionSelector == (1).toByte()) {
                columnsTmpBufOpt = GridRowColumnOption_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for columnsTmpBufOpt has to be chosen through deserialisation.')
            }
            columnsTmpBuf = (columnsTmpBufOpt as int32 | GridRowColumnOption)
        }
        const columnsTmpResult : int32 | GridRowColumnOption | undefined = columnsTmpBuf
        const breakpointsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let breakpointsTmpBuf : BreakPoints | undefined = undefined
        if ((breakpointsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            breakpointsTmpBuf = BreakPoints_serializer.read(valueDeserializer)
        }
        const breakpointsTmpResult : BreakPoints | undefined = breakpointsTmpBuf
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let directionTmpBuf : GridRowDirection | undefined = undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = GridRowDirection.fromValue(valueDeserializer.readInt32())
        }
        const directionTmpResult : GridRowDirection | undefined = directionTmpBuf
        let value : GridRowOptions = ({gutter: gutterTmpResult, columns: columnsTmpResult, breakpoints: breakpointsTmpResult, direction: directionTmpResult} as GridRowOptions)
        return value
    }
}
