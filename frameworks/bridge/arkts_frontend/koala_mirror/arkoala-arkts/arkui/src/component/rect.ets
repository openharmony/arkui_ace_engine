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
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonShapeMethodModifier, CommonMethodModifier } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Length } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkRectPeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRectPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Rect_construct(peerId, flags)
        const _peer  = new ArkRectPeer(_peerPtr, peerId, 'Rect', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRectOptionsAttribute(options?: RectOptions | RoundedRectOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            if (optionsTmpValue instanceof RectOptions) {
                thisSerializer.writeInt8((0).toChar())
                const optionsTmpValueForIdx0  = optionsTmpValue as RectOptions
                RectOptions_serializer.write(thisSerializer, optionsTmpValueForIdx0)
            } else if (optionsTmpValue instanceof RoundedRectOptions) {
                thisSerializer.writeInt8((1).toChar())
                const optionsTmpValueForIdx1  = optionsTmpValue as RoundedRectOptions
                RoundedRectOptions_serializer.write(thisSerializer, optionsTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RectInterface_setRectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadiusAttribute(value: number | string | Array<number | string> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (TypeChecker.isArray_Union_Number_String(valueTmpValue)) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Array<number | string>
                thisSerializer.writeInt32((valueTmpValueForIdx2.length).toInt())
                for (let valueTmpValueForIdx2CounterI = 0; valueTmpValueForIdx2CounterI < valueTmpValueForIdx2.length; valueTmpValueForIdx2CounterI++) {
                    const valueTmpValueForIdx2TmpElement : number | string = valueTmpValueForIdx2[valueTmpValueForIdx2CounterI]
                    if (valueTmpValueForIdx2TmpElement instanceof number) {
                        thisSerializer.writeInt8((0).toChar())
                        const valueTmpValueForIdx2TmpElementForIdx0  = valueTmpValueForIdx2TmpElement as number
                        thisSerializer.writeNumber(valueTmpValueForIdx2TmpElementForIdx0)
                    } else if (valueTmpValueForIdx2TmpElement instanceof string) {
                        thisSerializer.writeInt8((1).toChar())
                        const valueTmpValueForIdx2TmpElementForIdx1  = valueTmpValueForIdx2TmpElement as string
                        thisSerializer.writeString(valueTmpValueForIdx2TmpElementForIdx1)
                    }
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RectAttribute_setRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type RadiusItem = [
    Length,
    Length
]
export interface RectOptions {
    width?: Length;
    height?: Length;
    radius?: Length | Array<RadiusItem>;
}
export interface RoundedRectOptions {
}
export interface RectAttribute extends CommonShapeMethod {
    radius(value: number | string | Array<number | string> | undefined): this {
        throw new Error("Unimplemented method radius")
    }
    attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRectStyle extends ArkCommonShapeMethodStyle implements RectAttribute {
    radius_value?: number | string | Array<number | string> | undefined
    attributeModifier_value?: AttributeModifier<RectAttribute> | AttributeModifier<CommonMethod> | undefined
    public radius(value: number | string | Array<number | string> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkRectComponent extends ArkCommonShapeMethodComponent implements RectAttribute {
    getPeer(): ArkRectPeer {
        return (this.peer as ArkRectPeer)
    }
    public setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        if (this.checkPriority("setRectOptions")) {
            const options_casted = options as (RectOptions | RoundedRectOptions | undefined)
            this.getPeer()?.setRectOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public radius(value: number | string | Array<number | string> | undefined): this {
        if (this.checkPriority("radius")) {
            const value_casted = value as (number | string | Array<number | string> | undefined)
            this.getPeer()?.setRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Rect(
    @memo
    style: ((attributes: RectAttribute) => void) | undefined,
    options?: RectOptions | RoundedRectOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRectComponent>((): ArkRectComponent => {
        return new ArkRectComponent()
    })
    NodeAttach<ArkRectPeer>((): ArkRectPeer => ArkRectPeer.create(receiver), (_: ArkRectPeer): void => {
        receiver.setRectOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class RectModifier extends CommonShapeMethodModifier implements RectAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _radius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radius_0_0value?: number | string | Array<number | string> | undefined
    applyModifierPatch(peer: ArkRectPeer): void {
        super.applyModifierPatch(peer)
        if (this._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadiusAttribute((this._radius_0_0value as number | string | Array<number | string> | undefined));
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadiusAttribute((undefined as number | string | Array<number | string> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RectModifier): void {
        super.mergeModifier(modifier)
        if (modifier._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radius(modifier._radius_0_0value);
                    break;
                }
                default: {
                    this.radius((undefined as number | string | Array<number | string> | undefined));
                }
            }
        }
    }
    radius(value: number | string | Array<number | string> | undefined): this {
        if (((this._radius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._radius_0_0value) !== (value)))
        {
            this._radius_0_flag = AttributeUpdaterFlag.UPDATE
            this._radius_0_0value = value
        } else
        {
            this._radius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RoundedRectOptions_serializer {
    public static write(buffer: SerializerBase, value: RoundedRectOptions): void {
    }
    public static read(buffer: DeserializerBase): RoundedRectOptions {
        let value : RoundedRectOptions = ({} as RoundedRectOptions)
        return value
    }
}
export class RectOptions_serializer {
    public static write(buffer: SerializerBase, value: RectOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof Length) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as Length
                if (valueHolderForRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx0  = valueHolderForRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx1  = valueHolderForRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toChar())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx2  = valueHolderForRadiusTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (TypeChecker.isArray_RadiusItem(valueHolderForRadiusTmpValue)) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as Array<RadiusItem>
                valueSerializer.writeInt32((valueHolderForRadiusTmpValueForIdx1.length).toInt())
                for (let valueHolderForRadiusTmpValueForIdx1CounterI = 0; valueHolderForRadiusTmpValueForIdx1CounterI < valueHolderForRadiusTmpValueForIdx1.length; valueHolderForRadiusTmpValueForIdx1CounterI++) {
                    const valueHolderForRadiusTmpValueForIdx1TmpElement : RadiusItem = valueHolderForRadiusTmpValueForIdx1[valueHolderForRadiusTmpValueForIdx1CounterI]
                    const valueHolderForRadiusTmpValueForIdx1TmpElement_0  = valueHolderForRadiusTmpValueForIdx1TmpElement[0]
                    if (valueHolderForRadiusTmpValueForIdx1TmpElement_0 instanceof string) {
                        valueSerializer.writeInt8((0).toChar())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx0  = valueHolderForRadiusTmpValueForIdx1TmpElement_0 as string
                        valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx0)
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_0 instanceof number) {
                        valueSerializer.writeInt8((1).toChar())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx1  = valueHolderForRadiusTmpValueForIdx1TmpElement_0 as number
                        valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx1)
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_0 instanceof Resource) {
                        valueSerializer.writeInt8((2).toChar())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx2  = valueHolderForRadiusTmpValueForIdx1TmpElement_0 as Resource
                        Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx2)
                    }
                    const valueHolderForRadiusTmpValueForIdx1TmpElement_1  = valueHolderForRadiusTmpValueForIdx1TmpElement[1]
                    if (valueHolderForRadiusTmpValueForIdx1TmpElement_1 instanceof string) {
                        valueSerializer.writeInt8((0).toChar())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx0  = valueHolderForRadiusTmpValueForIdx1TmpElement_1 as string
                        valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx0)
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_1 instanceof number) {
                        valueSerializer.writeInt8((1).toChar())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx1  = valueHolderForRadiusTmpValueForIdx1TmpElement_1 as number
                        valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx1)
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_1 instanceof Resource) {
                        valueSerializer.writeInt8((2).toChar())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx2  = valueHolderForRadiusTmpValueForIdx1TmpElement_1 as Resource
                        Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx2)
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RectOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Length | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | number | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | number | Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Length | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | number | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | number | Resource)
        }
        const heightTmpResult : Length | undefined = heightTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : Length | Array<RadiusItem> | undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBuf_ : Length | Array<RadiusItem> | undefined
            if (radiusTmpBuf_UnionSelector == (0).toChar()) {
                const radiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBuf_BufU : string | number | Resource | undefined
                if (radiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    radiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    radiusTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (radiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    radiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for radiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                radiusTmpBuf_ = (radiusTmpBuf_BufU as string | number | Resource)
            } else if (radiusTmpBuf_UnionSelector == (1).toChar()) {
                const radiusTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let radiusTmpBuf_BufU : Array<RadiusItem> = new Array<RadiusItem>(radiusTmpBuf_BufULength)
                for (let radiusTmpBuf_BufUBufCounterI = 0; radiusTmpBuf_BufUBufCounterI < radiusTmpBuf_BufULength; radiusTmpBuf_BufUBufCounterI++) {
                    const radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBuf_BufUTempBufValue0TempBuf : string | number | Resource | undefined
                    if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (0).toChar()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = (valueDeserializer.readString() as string)
                    } else if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (1).toChar()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = (valueDeserializer.readNumber() as number)
                    } else if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (2).toChar()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for radiusTmpBuf_BufUTempBufValue0TempBuf has to be chosen through deserialisation.")
                    }
                    const radiusTmpBuf_BufUTempBufValue0 : Length = (radiusTmpBuf_BufUTempBufValue0TempBuf as string | number | Resource)
                    const radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBuf_BufUTempBufValue1TempBuf : string | number | Resource | undefined
                    if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (0).toChar()) {
                        radiusTmpBuf_BufUTempBufValue1TempBuf = (valueDeserializer.readString() as string)
                    } else if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (1).toChar()) {
                        radiusTmpBuf_BufUTempBufValue1TempBuf = (valueDeserializer.readNumber() as number)
                    } else if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (2).toChar()) {
                        radiusTmpBuf_BufUTempBufValue1TempBuf = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for radiusTmpBuf_BufUTempBufValue1TempBuf has to be chosen through deserialisation.")
                    }
                    const radiusTmpBuf_BufUTempBufValue1 : Length = (radiusTmpBuf_BufUTempBufValue1TempBuf as string | number | Resource)
                    radiusTmpBuf_BufU[radiusTmpBuf_BufUBufCounterI] = ([radiusTmpBuf_BufUTempBufValue0, radiusTmpBuf_BufUTempBufValue1] as RadiusItem)
                }
                radiusTmpBuf_ = radiusTmpBuf_BufU
            } else {
                throw new Error("One of the branches for radiusTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusTmpBuf = (radiusTmpBuf_ as Length | Array<RadiusItem>)
        }
        const radiusTmpResult : Length | Array<RadiusItem> | undefined = radiusTmpBuf
        let value : RectOptions = ({width: widthTmpResult, height: heightTmpResult, radius: radiusTmpResult} as RectOptions)
        return value
    }
}
