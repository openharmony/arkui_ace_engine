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
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { HorizontalAlign, FlexAlign } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkColumnPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkColumnPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Column_construct(peerId, flags)
        const _peer  = new ArkColumnPeer(_peerPtr, peerId, "Column", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setColumnOptionsAttribute(options?: ColumnOptions | ColumnOptionsV2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            let options_value_type : int32 = RuntimeType.UNDEFINED
            options_value_type = runtimeType(options_value)
            if (TypeChecker.isColumnOptions(options_value, false)) {
                thisSerializer.writeInt8((0).toChar())
                const options_value_0  = options_value as ColumnOptions
                ColumnOptions_serializer.write(thisSerializer, options_value_0)
            }
            else if (TypeChecker.isColumnOptionsV2(options_value, false)) {
                thisSerializer.writeInt8((1).toChar())
                const options_value_1  = options_value as ColumnOptionsV2
                ColumnOptionsV2_serializer.write(thisSerializer, options_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ColumnInterface_setColumnOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: HorizontalAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as HorizontalAlign)
            thisSerializer.writeInt32(TypeChecker.HorizontalAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setAlignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJustifyContentAttribute(value: FlexAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FlexAlign)
            thisSerializer.writeInt32(TypeChecker.FlexAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setJustifyContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PointLightStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setReverseAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setReverse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type SpaceType = string | number | Resource;
export interface ColumnOptions {
    space?: string | number;
}
export interface ColumnOptionsV2 {
    _stub: int32;
}
export interface ColumnAttribute extends CommonMethod {
    alignItems(value: HorizontalAlign | undefined): this {
        throw new Error("Unimplemented method alignItems")
    }
    justifyContent(value: FlexAlign | undefined): this {
        throw new Error("Unimplemented method justifyContent")
    }
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error("Unimplemented method pointLight")
    }
    reverse(value: boolean | undefined): this {
        throw new Error("Unimplemented method reverse")
    }
    attributeModifier(value: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkColumnStyle extends ArkCommonMethodStyle implements ColumnAttribute {
    alignItems_value?: HorizontalAlign | undefined
    justifyContent_value?: FlexAlign | undefined
    pointLight_value?: PointLightStyle | undefined
    reverse_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined
    public alignItems(value: HorizontalAlign | undefined): this {
        return this
    }
    public justifyContent(value: FlexAlign | undefined): this {
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    public reverse(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ColumnAttribute): void {
        super.apply(target)
        if (this.alignItems_value !== undefined)
            target.alignItems(this.alignItems_value!)
        if (this.justifyContent_value !== undefined)
            target.justifyContent(this.justifyContent_value!)
        if (this.pointLight_value !== undefined)
            target.pointLight(this.pointLight_value!)
        if (this.reverse_value !== undefined)
            target.reverse(this.reverse_value!)
    }
}

export class ArkColumnComponent extends ArkCommonMethodComponent implements ColumnAttribute {
    getPeer(): ArkColumnPeer {
        return (this.peer as ArkColumnPeer)
    }
    public setColumnOptions(options?: ColumnOptions | ColumnOptionsV2): this {
        if (this.checkPriority("setColumnOptions")) {
            const options_casted = options as (ColumnOptions | ColumnOptionsV2 | undefined)
            this.getPeer()?.setColumnOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public alignItems(value: HorizontalAlign | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (HorizontalAlign | undefined)
            this.getPeer()?.setAlignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    public justifyContent(value: FlexAlign | undefined): this {
        if (this.checkPriority("justifyContent")) {
            const value_casted = value as (FlexAlign | undefined)
            this.getPeer()?.setJustifyContentAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.setPointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public reverse(value: boolean | undefined): this {
        if (this.checkPriority("reverse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setReverseAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withColumnStyle(receiver: ColumnAttribute, modifier: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkColumnStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Column")
// export function Column(
//     options?: ColumnOptions | ColumnOptionsV2,
//     @memo
//     content_?: () => void,
// ): ColumnAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Column(
    @memo
    style: ((attributes: ColumnAttribute) => void) | undefined,
    options?: ColumnOptions | ColumnOptionsV2,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkColumnComponent>((): ArkColumnComponent => {
        return new ArkColumnComponent()
    })
    NodeAttach<ArkColumnPeer>((): ArkColumnPeer => ArkColumnPeer.create(receiver), (_: ArkColumnPeer): void => {
        receiver.setColumnOptions(options)
        style?.(receiver)
        withColumnStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkColumnSet extends ArkCommonMethodSet implements ColumnAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alignItems_flag?: boolean
    _alignItems0_value?: HorizontalAlign | undefined
    _justifyContent_flag?: boolean
    _justifyContent0_value?: FlexAlign | undefined
    _pointLight_flag?: boolean
    _pointLight0_value?: PointLightStyle | undefined
    _reverse_flag?: boolean
    _reverse0_value?: boolean | undefined
    applyModifierPatch(component: ColumnAttribute): void {
        if (this._alignItems_flag)
            component.alignItems((this._alignItems0_value as HorizontalAlign | undefined))
        if (this._justifyContent_flag)
            component.justifyContent((this._justifyContent0_value as FlexAlign | undefined))
        if (this._pointLight_flag)
            component.pointLight((this._pointLight0_value as PointLightStyle | undefined))
        if (this._reverse_flag)
            component.reverse((this._reverse0_value as boolean | undefined))
    }
    public alignItems(value: HorizontalAlign | undefined): this {
        this._alignItems_flag = true
        this._alignItems0_value = value
        return this
    }
    public justifyContent(value: FlexAlign | undefined): this {
        this._justifyContent_flag = true
        this._justifyContent0_value = value
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        this._pointLight_flag = true
        this._pointLight0_value = value
        return this
    }
    public reverse(value: boolean | undefined): this {
        this._reverse_flag = true
        this._reverse0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ColumnOptions_serializer {
    public static write(buffer: SerializerBase, value: ColumnOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_space  = value.space
        let value_space_type : int32 = RuntimeType.UNDEFINED
        value_space_type = runtimeType(value_space)
        valueSerializer.writeInt8((value_space_type).toChar())
        if ((value_space_type) != (RuntimeType.UNDEFINED)) {
            const value_space_value  = value_space!
            let value_space_value_type : int32 = RuntimeType.UNDEFINED
            value_space_value_type = runtimeType(value_space_value)
            if (RuntimeType.STRING == value_space_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_space_value_0  = value_space_value as string
                valueSerializer.writeString(value_space_value_0)
            }
            else if (RuntimeType.NUMBER == value_space_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_space_value_1  = value_space_value as number
                valueSerializer.writeNumber(value_space_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): ColumnOptions {
        let valueDeserializer : DeserializerBase = buffer
        const space_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let space_buf : string | number | undefined
        if ((space_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const space_buf__selector : int32 = valueDeserializer.readInt8()
            let space_buf_ : string | number | undefined
            if (space_buf__selector == (0).toChar()) {
                space_buf_ = (valueDeserializer.readString() as string)
            }
            else if (space_buf__selector == (1).toChar()) {
                space_buf_ = (valueDeserializer.readNumber() as number)
            }
            else {
                throw new Error("One of the branches for space_buf_ has to be chosen through deserialisation.")
            }
            space_buf = (space_buf_ as string | number)
        }
        const space_result : string | number | undefined = space_buf
        let value : ColumnOptions = ({space: space_result} as ColumnOptions)
        return value
    }
}
export class ColumnOptionsV2_serializer {
    public static write(buffer: SerializerBase, value: ColumnOptionsV2): void {
        let valueSerializer : SerializerBase = buffer
        const value__stub  = value._stub
        valueSerializer.writeInt32(value__stub)
    }
    public static read(buffer: DeserializerBase): ColumnOptionsV2 {
        let valueDeserializer : DeserializerBase = buffer
        const _stub_result : int32 = valueDeserializer.readInt32()
        let value : ColumnOptionsV2 = ({_stub: _stub_result} as ColumnOptionsV2)
        return value
    }
}
