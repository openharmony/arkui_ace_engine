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
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { FlexDirection, FlexWrap, FlexAlign, ItemAlign } from "./enums"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkFlexPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFlexPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Flex_construct(peerId, flags)
        const _peer  = new ArkFlexPeer(_peerPtr, peerId, 'Flex', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFlexOptionsAttribute(value?: FlexOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            FlexOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FlexInterface_setFlexOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._FlexAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface FlexOptions {
    direction?: FlexDirection;
    wrap?: FlexWrap;
    justifyContent?: FlexAlign;
    alignItems?: ItemAlign;
    alignContent?: FlexAlign;
    space?: FlexSpaceOptions;
}
export interface FlexSpaceOptions {
    main?: LengthMetrics;
    cross?: LengthMetrics;
}
export interface FlexAttribute extends CommonMethod {
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error("Unimplemented method pointLight")
    }
    attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkFlexStyle extends ArkCommonMethodStyle implements FlexAttribute {
    pointLight_value?: PointLightStyle | undefined
    attributeModifier_value?: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined
    public pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkFlexComponent extends ArkCommonMethodComponent implements FlexAttribute {
    getPeer(): ArkFlexPeer {
        return (this.peer as ArkFlexPeer)
    }
    public setFlexOptions(value?: FlexOptions): this {
        if (this.checkPriority("setFlexOptions")) {
            const value_casted = value as (FlexOptions | undefined)
            this.getPeer()?.setFlexOptionsAttribute(value_casted)
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
    public attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Flex(
    @memo
    style: ((attributes: FlexAttribute) => void) | undefined,
    value?: FlexOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkFlexComponent>((): ArkFlexComponent => {
        return new ArkFlexComponent()
    })
    NodeAttach<ArkFlexPeer>((): ArkFlexPeer => ArkFlexPeer.create(receiver), (_: ArkFlexPeer): void => {
        receiver.setFlexOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class FlexModifier extends CommonMethodModifier implements FlexAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _pointLight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pointLight_0_0value?: PointLightStyle | undefined
    applyModifierPatch(peer: ArkFlexPeer): void {
        super.applyModifierPatch(peer)
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
    }
    mergeModifier(modifier: FlexModifier): void {
        super.mergeModifier(modifier)
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
    public attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class FlexSpaceOptions_serializer {
    public static write(buffer: SerializerBase, value: FlexSpaceOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMain  = value.main
        if (valueHolderForMain !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMainTmpValue  = valueHolderForMain!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForMainTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCross  = value.cross
        if (valueHolderForCross !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCrossTmpValue  = valueHolderForCross!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForCrossTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FlexSpaceOptions {
        let valueDeserializer : DeserializerBase = buffer
        const mainTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mainTmpBuf : LengthMetrics | undefined
        if ((mainTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mainTmpBuf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const mainTmpResult : LengthMetrics | undefined = mainTmpBuf
        const crossTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let crossTmpBuf : LengthMetrics | undefined
        if ((crossTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            crossTmpBuf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const crossTmpResult : LengthMetrics | undefined = crossTmpBuf
        let value : FlexSpaceOptions = ({main: mainTmpResult, cross: crossTmpResult} as FlexSpaceOptions)
        return value
    }
}
export class FlexOptions_serializer {
    public static write(buffer: SerializerBase, value: FlexOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForDirection  = value.direction
        if (valueHolderForDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDirectionTmpValue  = (valueHolderForDirection as FlexDirection)
            valueSerializer.writeInt32(TypeChecker.FlexDirection_ToNumeric(valueHolderForDirectionTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWrap  = value.wrap
        if (valueHolderForWrap !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWrapTmpValue  = (valueHolderForWrap as FlexWrap)
            valueSerializer.writeInt32(TypeChecker.FlexWrap_ToNumeric(valueHolderForWrapTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForJustifyContent  = value.justifyContent
        if (valueHolderForJustifyContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForJustifyContentTmpValue  = (valueHolderForJustifyContent as FlexAlign)
            valueSerializer.writeInt32(TypeChecker.FlexAlign_ToNumeric(valueHolderForJustifyContentTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignItems  = value.alignItems
        if (valueHolderForAlignItems !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignItemsTmpValue  = (valueHolderForAlignItems as ItemAlign)
            valueSerializer.writeInt32(TypeChecker.ItemAlign_ToNumeric(valueHolderForAlignItemsTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignContent  = value.alignContent
        if (valueHolderForAlignContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignContentTmpValue  = (valueHolderForAlignContent as FlexAlign)
            valueSerializer.writeInt32(TypeChecker.FlexAlign_ToNumeric(valueHolderForAlignContentTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            FlexSpaceOptions_serializer.write(valueSerializer, valueHolderForSpaceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FlexOptions {
        let valueDeserializer : DeserializerBase = buffer
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let directionTmpBuf : FlexDirection | undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = TypeChecker.FlexDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const directionTmpResult : FlexDirection | undefined = directionTmpBuf
        const wrapTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wrapTmpBuf : FlexWrap | undefined
        if ((wrapTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wrapTmpBuf = TypeChecker.FlexWrap_FromNumeric(valueDeserializer.readInt32())
        }
        const wrapTmpResult : FlexWrap | undefined = wrapTmpBuf
        const justifyContentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let justifyContentTmpBuf : FlexAlign | undefined
        if ((justifyContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            justifyContentTmpBuf = TypeChecker.FlexAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const justifyContentTmpResult : FlexAlign | undefined = justifyContentTmpBuf
        const alignItemsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignItemsTmpBuf : ItemAlign | undefined
        if ((alignItemsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignItemsTmpBuf = TypeChecker.ItemAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const alignItemsTmpResult : ItemAlign | undefined = alignItemsTmpBuf
        const alignContentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignContentTmpBuf : FlexAlign | undefined
        if ((alignContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignContentTmpBuf = TypeChecker.FlexAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const alignContentTmpResult : FlexAlign | undefined = alignContentTmpBuf
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let spaceTmpBuf : FlexSpaceOptions | undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            spaceTmpBuf = FlexSpaceOptions_serializer.read(valueDeserializer)
        }
        const spaceTmpResult : FlexSpaceOptions | undefined = spaceTmpBuf
        let value : FlexOptions = ({direction: directionTmpResult, wrap: wrapTmpResult, justifyContent: justifyContentTmpResult, alignItems: alignItemsTmpResult, alignContent: alignContentTmpResult, space: spaceTmpResult} as FlexOptions)
        return value
    }
}
