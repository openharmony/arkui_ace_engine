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
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
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
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkColumnPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkColumnPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Column_construct(peerId, flags)
        const _peer  = new ArkColumnPeer(_peerPtr, peerId, 'Column', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setColumnOptionsAttribute(options?: ColumnOptions | ColumnOptionsV2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            if (optionsTmpValue instanceof ColumnOptions) {
                thisSerializer.writeInt8((0).toChar())
                const optionsTmpValueForIdx0  = optionsTmpValue as ColumnOptions
                ColumnOptions_serializer.write(thisSerializer, optionsTmpValueForIdx0)
            } else if (optionsTmpValue instanceof ColumnOptionsV2) {
                thisSerializer.writeInt8((1).toChar())
                const optionsTmpValueForIdx1  = optionsTmpValue as ColumnOptionsV2
                ColumnOptionsV2_serializer.write(thisSerializer, optionsTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnInterface_setColumnOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: HorizontalAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as HorizontalAlign)
            thisSerializer.writeInt32(TypeChecker.HorizontalAlign_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setAlignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJustifyContentAttribute(value: FlexAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FlexAlign)
            thisSerializer.writeInt32(TypeChecker.FlexAlign_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setJustifyContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PointLightStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setReverseAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ColumnAttribute_setReverse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type SpaceType = string | number | Resource;
export interface ColumnOptions {
    space?: SpaceType;
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ColumnModifier extends CommonMethodModifier implements ColumnAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alignItems_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignItems_0_0value?: HorizontalAlign | undefined
    _justifyContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _justifyContent_0_0value?: FlexAlign | undefined
    _pointLight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pointLight_0_0value?: PointLightStyle | undefined
    _reverse_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _reverse_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkColumnPeer): void {
        super.applyModifierPatch(peer)
        if (this._alignItems_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignItemsAttribute((this._alignItems_0_0value as HorizontalAlign | undefined));
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignItemsAttribute((undefined as HorizontalAlign | undefined));
                }
            }
        }
        if (this._justifyContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._justifyContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJustifyContentAttribute((this._justifyContent_0_0value as FlexAlign | undefined));
                    this._justifyContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._justifyContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._justifyContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJustifyContentAttribute((undefined as FlexAlign | undefined));
                }
            }
        }
        if (this._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPointLightAttribute((this._pointLight_0_0value as PointLightStyle | undefined));
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPointLightAttribute((undefined as PointLightStyle | undefined));
                }
            }
        }
        if (this._reverse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._reverse_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setReverseAttribute((this._reverse_0_0value as boolean | undefined));
                    this._reverse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._reverse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._reverse_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setReverseAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ColumnModifier): void {
        super.mergeModifier(modifier)
        if (modifier._alignItems_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignItems(modifier._alignItems_0_0value);
                    break;
                }
                default: {
                    this.alignItems((undefined as HorizontalAlign | undefined));
                }
            }
        }
        if (modifier._justifyContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._justifyContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.justifyContent(modifier._justifyContent_0_0value);
                    break;
                }
                default: {
                    this.justifyContent((undefined as FlexAlign | undefined));
                }
            }
        }
        if (modifier._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pointLight(modifier._pointLight_0_0value);
                    break;
                }
                default: {
                    this.pointLight((undefined as PointLightStyle | undefined));
                }
            }
        }
        if (modifier._reverse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._reverse_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.reverse(modifier._reverse_0_0value);
                    break;
                }
                default: {
                    this.reverse((undefined as boolean | undefined));
                }
            }
        }
    }
    alignItems(value: HorizontalAlign | undefined): this {
        if (((this._alignItems_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignItems_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignItems_0_0value = value
        } else
        {
            this._alignItems_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    justifyContent(value: FlexAlign | undefined): this {
        if (((this._justifyContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._justifyContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._justifyContent_0_0value = value
        } else
        {
            this._justifyContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pointLight(value: PointLightStyle | undefined): this {
        if (((this._pointLight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.UPDATE
            this._pointLight_0_0value = value
        } else
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    reverse(value: boolean | undefined): this {
        if (((this._reverse_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._reverse_0_0value) !== (value)))
        {
            this._reverse_0_flag = AttributeUpdaterFlag.UPDATE
            this._reverse_0_0value = value
        } else
        {
            this._reverse_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ColumnOptionsV2_serializer {
    public static write(buffer: SerializerBase, value: ColumnOptionsV2): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderFor_stub  = value._stub
        valueSerializer.writeInt32(valueHolderFor_stub)
    }
    public static read(buffer: DeserializerBase): ColumnOptionsV2 {
        let valueDeserializer : DeserializerBase = buffer
        const _stubTmpResult : int32 = valueDeserializer.readInt32()
        let value : ColumnOptionsV2 = ({_stub: _stubTmpResult} as ColumnOptionsV2)
        return value
    }
}
export class ColumnOptions_serializer {
    public static write(buffer: SerializerBase, value: ColumnOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            if (valueHolderForSpaceTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSpaceTmpValueForIdx0  = valueHolderForSpaceTmpValue as string
                valueSerializer.writeString(valueHolderForSpaceTmpValueForIdx0)
            } else if (valueHolderForSpaceTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForSpaceTmpValueForIdx1  = valueHolderForSpaceTmpValue as number
                valueSerializer.writeNumber(valueHolderForSpaceTmpValueForIdx1)
            } else if (valueHolderForSpaceTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForSpaceTmpValueForIdx2  = valueHolderForSpaceTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSpaceTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ColumnOptions {
        let valueDeserializer : DeserializerBase = buffer
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let spaceTmpBuf : SpaceType | undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spaceTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let spaceTmpBuf_ : string | number | Resource | undefined
            if (spaceTmpBuf_UnionSelector == (0).toChar()) {
                spaceTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (spaceTmpBuf_UnionSelector == (1).toChar()) {
                spaceTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (spaceTmpBuf_UnionSelector == (2).toChar()) {
                spaceTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for spaceTmpBuf_ has to be chosen through deserialisation.")
            }
            spaceTmpBuf = (spaceTmpBuf_ as string | number | Resource)
        }
        const spaceTmpResult : SpaceType | undefined = spaceTmpBuf
        let value : ColumnOptions = ({space: spaceTmpResult} as ColumnOptions)
        return value
    }
}
