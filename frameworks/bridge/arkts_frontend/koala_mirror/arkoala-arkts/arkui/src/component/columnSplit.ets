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
import { Dimension } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkColumnSplitPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkColumnSplitPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ColumnSplit_construct(peerId, flags)
        const _peer  = new ArkColumnSplitPeer(_peerPtr, peerId, "ColumnSplit", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setColumnSplitOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ColumnSplitInterface_setColumnSplitOptions(this.peer.ptr)
    }
    setResizeableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ColumnSplitAttribute_setResizeable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: ColumnSplitDividerStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ColumnSplitDividerStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ColumnSplitAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ColumnSplitDividerStyle {
    startMargin?: Dimension;
    endMargin?: Dimension;
}
export interface ColumnSplitAttribute extends CommonMethod {
    resizeable(value: boolean | undefined): this {
        throw new Error("Unimplemented method resizeable")
    }
    divider(value: ColumnSplitDividerStyle | undefined): this {
        throw new Error("Unimplemented method divider")
    }
    attributeModifier(value: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkColumnSplitStyle extends ArkCommonMethodStyle implements ColumnSplitAttribute {
    resizeable_value?: boolean | undefined
    divider_value?: ColumnSplitDividerStyle | undefined
    attributeModifier_value?: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined
    public resizeable(value: boolean | undefined): this {
        return this
    }
    public divider(value: ColumnSplitDividerStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ColumnSplitAttribute): void {
        super.apply(target)
        if (this.resizeable_value !== undefined)
            target.resizeable(this.resizeable_value!)
        if (this.divider_value !== undefined)
            target.divider(this.divider_value!)
    }
}

export class ArkColumnSplitComponent extends ArkCommonMethodComponent implements ColumnSplitAttribute {
    getPeer(): ArkColumnSplitPeer {
        return (this.peer as ArkColumnSplitPeer)
    }
    public setColumnSplitOptions(): this {
        if (this.checkPriority("setColumnSplitOptions")) {
            this.getPeer()?.setColumnSplitOptionsAttribute()
            return this
        }
        return this
    }
    public resizeable(value: boolean | undefined): this {
        if (this.checkPriority("resizeable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setResizeableAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: ColumnSplitDividerStyle | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ColumnSplitDividerStyle | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withColumnSplitStyle(receiver: ColumnSplitAttribute, modifier: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkColumnSplitStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("ColumnSplit")
// export function ColumnSplit(
//     
//     @memo
//     content_?: () => void,
// ): ColumnSplitAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function ColumnSplit(
    @memo
    style: ((attributes: ColumnSplitAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkColumnSplitComponent>((): ArkColumnSplitComponent => {
        return new ArkColumnSplitComponent()
    })
    NodeAttach<ArkColumnSplitPeer>((): ArkColumnSplitPeer => ArkColumnSplitPeer.create(receiver), (_: ArkColumnSplitPeer): void => {
        receiver.setColumnSplitOptions()
        style?.(receiver)
        withColumnSplitStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkColumnSplitSet extends ArkCommonMethodSet implements ColumnSplitAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _resizeable_flag?: boolean
    _resizeable0_value?: boolean | undefined
    _divider_flag?: boolean
    _divider0_value?: ColumnSplitDividerStyle | undefined
    applyModifierPatch(component: ColumnSplitAttribute): void {
        if (this._resizeable_flag)
            component.resizeable((this._resizeable0_value as boolean | undefined))
        if (this._divider_flag)
            component.divider((this._divider0_value as ColumnSplitDividerStyle | undefined))
    }
    public resizeable(value: boolean | undefined): this {
        this._resizeable_flag = true
        this._resizeable0_value = value
        return this
    }
    public divider(value: ColumnSplitDividerStyle | undefined): this {
        this._divider_flag = true
        this._divider0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ColumnSplitDividerStyle_serializer {
    public static write(buffer: SerializerBase, value: ColumnSplitDividerStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_startMargin  = value.startMargin
        let value_startMargin_type : int32 = RuntimeType.UNDEFINED
        value_startMargin_type = runtimeType(value_startMargin)
        valueSerializer.writeInt8((value_startMargin_type).toChar())
        if ((value_startMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_startMargin_value  = value_startMargin!
            let value_startMargin_value_type : int32 = RuntimeType.UNDEFINED
            value_startMargin_value_type = runtimeType(value_startMargin_value)
            if (RuntimeType.STRING == value_startMargin_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_startMargin_value_0  = value_startMargin_value as string
                valueSerializer.writeString(value_startMargin_value_0)
            }
            else if (RuntimeType.NUMBER == value_startMargin_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_startMargin_value_1  = value_startMargin_value as number
                valueSerializer.writeNumber(value_startMargin_value_1)
            }
            else if (RuntimeType.OBJECT == value_startMargin_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_startMargin_value_2  = value_startMargin_value as Resource
                Resource_serializer.write(valueSerializer, value_startMargin_value_2)
            }
        }
        const value_endMargin  = value.endMargin
        let value_endMargin_type : int32 = RuntimeType.UNDEFINED
        value_endMargin_type = runtimeType(value_endMargin)
        valueSerializer.writeInt8((value_endMargin_type).toChar())
        if ((value_endMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_endMargin_value  = value_endMargin!
            let value_endMargin_value_type : int32 = RuntimeType.UNDEFINED
            value_endMargin_value_type = runtimeType(value_endMargin_value)
            if (RuntimeType.STRING == value_endMargin_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_endMargin_value_0  = value_endMargin_value as string
                valueSerializer.writeString(value_endMargin_value_0)
            }
            else if (RuntimeType.NUMBER == value_endMargin_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_endMargin_value_1  = value_endMargin_value as number
                valueSerializer.writeNumber(value_endMargin_value_1)
            }
            else if (RuntimeType.OBJECT == value_endMargin_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_endMargin_value_2  = value_endMargin_value as Resource
                Resource_serializer.write(valueSerializer, value_endMargin_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): ColumnSplitDividerStyle {
        let valueDeserializer : DeserializerBase = buffer
        const startMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMargin_buf : Dimension | undefined
        if ((startMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const startMargin_buf__selector : int32 = valueDeserializer.readInt8()
            let startMargin_buf_ : string | number | Resource | undefined
            if (startMargin_buf__selector == (0).toChar()) {
                startMargin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (startMargin_buf__selector == (1).toChar()) {
                startMargin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (startMargin_buf__selector == (2).toChar()) {
                startMargin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for startMargin_buf_ has to be chosen through deserialisation.")
            }
            startMargin_buf = (startMargin_buf_ as string | number | Resource)
        }
        const startMargin_result : Dimension | undefined = startMargin_buf
        const endMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMargin_buf : Dimension | undefined
        if ((endMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const endMargin_buf__selector : int32 = valueDeserializer.readInt8()
            let endMargin_buf_ : string | number | Resource | undefined
            if (endMargin_buf__selector == (0).toChar()) {
                endMargin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (endMargin_buf__selector == (1).toChar()) {
                endMargin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (endMargin_buf__selector == (2).toChar()) {
                endMargin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for endMargin_buf_ has to be chosen through deserialisation.")
            }
            endMargin_buf = (endMargin_buf_ as string | number | Resource)
        }
        const endMargin_result : Dimension | undefined = endMargin_buf
        let value : ColumnSplitDividerStyle = ({startMargin: startMargin_result, endMargin: endMargin_result} as ColumnSplitDividerStyle)
        return value
    }
}
