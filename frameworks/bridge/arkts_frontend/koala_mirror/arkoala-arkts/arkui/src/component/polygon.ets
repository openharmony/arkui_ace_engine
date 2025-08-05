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
import { ShapePoint } from "./line"
import { Length } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkPolygonPeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPolygonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Polygon_construct(peerId, flags)
        const _peer  = new ArkPolygonPeer(_peerPtr, peerId, 'Polygon', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPolygonOptionsAttribute(options?: PolygonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            PolygonOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PolygonInterface_setPolygonOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointsAttribute(value: Array<ShapePoint> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ShapePoint = valueTmpValue[valueTmpValueCounterI]
                const valueTmpValueTmpElement_0  = valueTmpValueTmpElement[0]
                if (valueTmpValueTmpElement_0 instanceof string) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueTmpElement_0ForIdx0  = valueTmpValueTmpElement_0 as string
                    thisSerializer.writeString(valueTmpValueTmpElement_0ForIdx0)
                } else if (valueTmpValueTmpElement_0 instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueTmpElement_0ForIdx1  = valueTmpValueTmpElement_0 as number
                    thisSerializer.writeNumber(valueTmpValueTmpElement_0ForIdx1)
                } else if (valueTmpValueTmpElement_0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueTmpElement_0ForIdx2  = valueTmpValueTmpElement_0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueTmpElement_0ForIdx2)
                }
                const valueTmpValueTmpElement_1  = valueTmpValueTmpElement[1]
                if (valueTmpValueTmpElement_1 instanceof string) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueTmpElement_1ForIdx0  = valueTmpValueTmpElement_1 as string
                    thisSerializer.writeString(valueTmpValueTmpElement_1ForIdx0)
                } else if (valueTmpValueTmpElement_1 instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueTmpElement_1ForIdx1  = valueTmpValueTmpElement_1 as number
                    thisSerializer.writeNumber(valueTmpValueTmpElement_1ForIdx1)
                } else if (valueTmpValueTmpElement_1 instanceof Resource) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueTmpElement_1ForIdx2  = valueTmpValueTmpElement_1 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueTmpElement_1ForIdx2)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PolygonAttribute_setPoints(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PolygonOptions {
}
export interface PolygonAttribute extends CommonShapeMethod {
    points(value: Array<ShapePoint> | undefined): this {
        throw new Error("Unimplemented method points")
    }
    attributeModifier(value: AttributeModifier<PolygonAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkPolygonStyle extends ArkCommonShapeMethodStyle implements PolygonAttribute {
    points_value?: Array<ShapePoint> | undefined
    attributeModifier_value?: AttributeModifier<PolygonAttribute> | AttributeModifier<CommonMethod> | undefined
    public points(value: Array<ShapePoint> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PolygonAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkPolygonComponent extends ArkCommonShapeMethodComponent implements PolygonAttribute {
    getPeer(): ArkPolygonPeer {
        return (this.peer as ArkPolygonPeer)
    }
    public setPolygonOptions(options?: PolygonOptions): this {
        if (this.checkPriority("setPolygonOptions")) {
            const options_casted = options as (PolygonOptions | undefined)
            this.getPeer()?.setPolygonOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public points(value: Array<ShapePoint> | undefined): this {
        if (this.checkPriority("points")) {
            const value_casted = value as (Array<ShapePoint> | undefined)
            this.getPeer()?.setPointsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PolygonAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Polygon(
    @memo
    style: ((attributes: PolygonAttribute) => void) | undefined,
    options?: PolygonOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPolygonComponent>((): ArkPolygonComponent => {
        return new ArkPolygonComponent()
    })
    NodeAttach<ArkPolygonPeer>((): ArkPolygonPeer => ArkPolygonPeer.create(receiver), (_: ArkPolygonPeer): void => {
        receiver.setPolygonOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class PolygonModifier extends CommonShapeMethodModifier implements PolygonAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _points_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _points_0_0value?: Array<ShapePoint> | undefined
    applyModifierPatch(peer: ArkPolygonPeer): void {
        super.applyModifierPatch(peer)
        if (this._points_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._points_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPointsAttribute((this._points_0_0value as Array<ShapePoint> | undefined));
                    this._points_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._points_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._points_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPointsAttribute((undefined as Array<ShapePoint> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PolygonModifier): void {
        super.mergeModifier(modifier)
        if (modifier._points_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._points_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.points(modifier._points_0_0value);
                    break;
                }
                default: {
                    this.points((undefined as Array<ShapePoint> | undefined));
                }
            }
        }
    }
    points(value: Array<ShapePoint> | undefined): this {
        if (((this._points_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._points_0_flag = AttributeUpdaterFlag.UPDATE
            this._points_0_0value = value
        } else
        {
            this._points_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PolygonAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class PolygonOptions_serializer {
    public static write(buffer: SerializerBase, value: PolygonOptions): void {
    }
    public static read(buffer: DeserializerBase): PolygonOptions {
        let value : PolygonOptions = ({} as PolygonOptions)
        return value
    }
}
