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
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonShapeMethodModifier, CommonMethodModifier } from "./common"
import { Length } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkLinePeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLinePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Line_construct(peerId, flags)
        const _peer  = new ArkLinePeer(_peerPtr, peerId, 'Line', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLineOptionsAttribute(options?: LineOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            LineOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LineInterface_setLineOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStartPointAttribute(value: ShapePoint | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            const valueTmpValue_0  = valueTmpValue[0]
            if (valueTmpValue_0 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValue_0ForIdx0  = valueTmpValue_0 as string
                thisSerializer.writeString(valueTmpValue_0ForIdx0)
            } else if (valueTmpValue_0 instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValue_0ForIdx1  = valueTmpValue_0 as number
                thisSerializer.writeNumber(valueTmpValue_0ForIdx1)
            } else if (valueTmpValue_0 instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValue_0ForIdx2  = valueTmpValue_0 as Resource
                Resource_serializer.write(thisSerializer, valueTmpValue_0ForIdx2)
            }
            const valueTmpValue_1  = valueTmpValue[1]
            if (valueTmpValue_1 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValue_1ForIdx0  = valueTmpValue_1 as string
                thisSerializer.writeString(valueTmpValue_1ForIdx0)
            } else if (valueTmpValue_1 instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValue_1ForIdx1  = valueTmpValue_1 as number
                thisSerializer.writeNumber(valueTmpValue_1ForIdx1)
            } else if (valueTmpValue_1 instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValue_1ForIdx2  = valueTmpValue_1 as Resource
                Resource_serializer.write(thisSerializer, valueTmpValue_1ForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LineAttribute_setStartPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEndPointAttribute(value: ShapePoint | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            const valueTmpValue_0  = valueTmpValue[0]
            if (valueTmpValue_0 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValue_0ForIdx0  = valueTmpValue_0 as string
                thisSerializer.writeString(valueTmpValue_0ForIdx0)
            } else if (valueTmpValue_0 instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValue_0ForIdx1  = valueTmpValue_0 as number
                thisSerializer.writeNumber(valueTmpValue_0ForIdx1)
            } else if (valueTmpValue_0 instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValue_0ForIdx2  = valueTmpValue_0 as Resource
                Resource_serializer.write(thisSerializer, valueTmpValue_0ForIdx2)
            }
            const valueTmpValue_1  = valueTmpValue[1]
            if (valueTmpValue_1 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValue_1ForIdx0  = valueTmpValue_1 as string
                thisSerializer.writeString(valueTmpValue_1ForIdx0)
            } else if (valueTmpValue_1 instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValue_1ForIdx1  = valueTmpValue_1 as number
                thisSerializer.writeNumber(valueTmpValue_1ForIdx1)
            } else if (valueTmpValue_1 instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValue_1ForIdx2  = valueTmpValue_1 as Resource
                Resource_serializer.write(thisSerializer, valueTmpValue_1ForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LineAttribute_setEndPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type ShapePoint = [
    Length,
    Length
]
export interface LineOptions {
}
export interface LineAttribute extends CommonShapeMethod {
    startPoint(value: ShapePoint | undefined): this {
        throw new Error("Unimplemented method startPoint")
    }
    endPoint(value: ShapePoint | undefined): this {
        throw new Error("Unimplemented method endPoint")
    }
    attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkLineStyle extends ArkCommonShapeMethodStyle implements LineAttribute {
    startPoint_value?: ShapePoint | undefined
    endPoint_value?: ShapePoint | undefined
    attributeModifier_value?: AttributeModifier<LineAttribute> | AttributeModifier<CommonMethod> | undefined
    public startPoint(value: ShapePoint | undefined): this {
        return this
    }
    public endPoint(value: ShapePoint | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkLineComponent extends ArkCommonShapeMethodComponent implements LineAttribute {
    getPeer(): ArkLinePeer {
        return (this.peer as ArkLinePeer)
    }
    public setLineOptions(options?: LineOptions): this {
        if (this.checkPriority("setLineOptions")) {
            const options_casted = options as (LineOptions | undefined)
            this.getPeer()?.setLineOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public startPoint(value: ShapePoint | undefined): this {
        if (this.checkPriority("startPoint")) {
            const value_casted = value as (ShapePoint | undefined)
            this.getPeer()?.setStartPointAttribute(value_casted)
            return this
        }
        return this
    }
    public endPoint(value: ShapePoint | undefined): this {
        if (this.checkPriority("endPoint")) {
            const value_casted = value as (ShapePoint | undefined)
            this.getPeer()?.setEndPointAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Line(
    @memo
    style: ((attributes: LineAttribute) => void) | undefined,
    options?: LineOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLineComponent>((): ArkLineComponent => {
        return new ArkLineComponent()
    })
    NodeAttach<ArkLinePeer>((): ArkLinePeer => ArkLinePeer.create(receiver), (_: ArkLinePeer): void => {
        receiver.setLineOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class LineModifier extends CommonShapeMethodModifier implements LineAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _startPoint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _startPoint_0_0value?: ShapePoint | undefined
    _endPoint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _endPoint_0_0value?: ShapePoint | undefined
    applyModifierPatch(peer: ArkLinePeer): void {
        super.applyModifierPatch(peer)
        if (this._startPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._startPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStartPointAttribute((this._startPoint_0_0value as ShapePoint | undefined));
                    this._startPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._startPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._startPoint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStartPointAttribute((undefined as ShapePoint | undefined));
                }
            }
        }
        if (this._endPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._endPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEndPointAttribute((this._endPoint_0_0value as ShapePoint | undefined));
                    this._endPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._endPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._endPoint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEndPointAttribute((undefined as ShapePoint | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: LineModifier): void {
        super.mergeModifier(modifier)
        if (modifier._startPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._startPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.startPoint(modifier._startPoint_0_0value);
                    break;
                }
                default: {
                    this.startPoint((undefined as ShapePoint | undefined));
                }
            }
        }
        if (modifier._endPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._endPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.endPoint(modifier._endPoint_0_0value);
                    break;
                }
                default: {
                    this.endPoint((undefined as ShapePoint | undefined));
                }
            }
        }
    }
    startPoint(value: ShapePoint | undefined): this {
        if (((this._startPoint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._startPoint_0_flag = AttributeUpdaterFlag.UPDATE
            this._startPoint_0_0value = value
        } else
        {
            this._startPoint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    endPoint(value: ShapePoint | undefined): this {
        if (((this._endPoint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._endPoint_0_flag = AttributeUpdaterFlag.UPDATE
            this._endPoint_0_0value = value
        } else
        {
            this._endPoint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class LineOptions_serializer {
    public static write(buffer: SerializerBase, value: LineOptions): void {
    }
    public static read(buffer: DeserializerBase): LineOptions {
        let value : LineOptions = ({} as LineOptions)
        return value
    }
}
