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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Length } from "./units"
import { Resource } from "global.resource"
import { AttributeModifier, hookRectAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { RectModifier } from "./../RectModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRectPeer extends ArkCommonShapeMethodPeer {
    attributeSet?: RectModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            if (optionsTmpValue instanceof RectOptions) {
                thisSerializer.writeInt8((0).toByte())
                const optionsTmpValueForIdx0  = optionsTmpValue as RectOptions
                RectOptions_serializer.write(thisSerializer, optionsTmpValueForIdx0)
            } else if (optionsTmpValue instanceof RoundedRectOptions) {
                thisSerializer.writeInt8((1).toByte())
                const optionsTmpValueForIdx1  = optionsTmpValue as RoundedRectOptions
                RoundedRectOptions_serializer.write(thisSerializer, optionsTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RectInterface_setRectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadiusWidthAttribute(value: double | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RectAttribute_setRadiusWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadiusHeightAttribute(value: double | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RectAttribute_setRadiusHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadiusAttribute(value: Length | Array<RadiusItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Length
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (TypeChecker.isArray_RadiusItem(valueTmpValue)) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Array<RadiusItem>
                thisSerializer.writeInt32((valueTmpValueForIdx1.length).toInt())
                for (let valueTmpValueForIdx1CounterI = 0; valueTmpValueForIdx1CounterI < valueTmpValueForIdx1.length; valueTmpValueForIdx1CounterI++) {
                    const valueTmpValueForIdx1TmpElement : RadiusItem = valueTmpValueForIdx1[valueTmpValueForIdx1CounterI]
                    const valueTmpValueForIdx1TmpElement_0  = valueTmpValueForIdx1TmpElement[0]
                    if (valueTmpValueForIdx1TmpElement_0 instanceof string) {
                        thisSerializer.writeInt8((0).toByte())
                        const valueTmpValueForIdx1TmpElement_0ForIdx0  = valueTmpValueForIdx1TmpElement_0 as string
                        thisSerializer.writeString(valueTmpValueForIdx1TmpElement_0ForIdx0)
                    } else if (valueTmpValueForIdx1TmpElement_0 instanceof number) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueForIdx1TmpElement_0ForIdx1  = valueTmpValueForIdx1TmpElement_0 as number
                        thisSerializer.writeNumber(valueTmpValueForIdx1TmpElement_0ForIdx1)
                    } else if (valueTmpValueForIdx1TmpElement_0 instanceof Resource) {
                        thisSerializer.writeInt8((2).toByte())
                        const valueTmpValueForIdx1TmpElement_0ForIdx2  = valueTmpValueForIdx1TmpElement_0 as Resource
                        Resource_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement_0ForIdx2)
                    }
                    const valueTmpValueForIdx1TmpElement_1  = valueTmpValueForIdx1TmpElement[1]
                    if (valueTmpValueForIdx1TmpElement_1 instanceof string) {
                        thisSerializer.writeInt8((0).toByte())
                        const valueTmpValueForIdx1TmpElement_1ForIdx0  = valueTmpValueForIdx1TmpElement_1 as string
                        thisSerializer.writeString(valueTmpValueForIdx1TmpElement_1ForIdx0)
                    } else if (valueTmpValueForIdx1TmpElement_1 instanceof number) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueForIdx1TmpElement_1ForIdx1  = valueTmpValueForIdx1TmpElement_1 as number
                        thisSerializer.writeNumber(valueTmpValueForIdx1TmpElement_1ForIdx1)
                    } else if (valueTmpValueForIdx1TmpElement_1 instanceof Resource) {
                        thisSerializer.writeInt8((2).toByte())
                        const valueTmpValueForIdx1TmpElement_1ForIdx2  = valueTmpValueForIdx1TmpElement_1 as Resource
                        Resource_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement_1ForIdx2)
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
    width?: double | string;
    height?: double | string;
    radius?: Length | Array<RadiusItem>;
}
export interface RoundedRectOptions {
    width?: double | string;
    height?: double | string;
    radiusWidth?: double | string;
    radiusHeight?: double | string;
}
export interface RectAttribute extends CommonShapeMethod {
    setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        throw new Error("Unimplemented method setRectOptions")
    }
    radiusWidth(value: double | string | undefined): this {
        throw new Error("Unimplemented method radiusWidth")
    }
    radiusHeight(value: double | string | undefined): this {
        throw new Error("Unimplemented method radiusHeight")
    }
    radius(value: Length | Array<RadiusItem> | undefined): this {
        throw new Error("Unimplemented method radius")
    }
    attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRectStyle extends ArkCommonShapeMethodStyle implements RectAttribute {
    radiusWidth_value?: double | string | undefined
    radiusHeight_value?: double | string | undefined
    radius_value?: Length | Array<RadiusItem> | undefined
    attributeModifier_value?: AttributeModifier<RectAttribute> | AttributeModifier<CommonMethod> | undefined
    setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        return this
    }
    radiusWidth(value: double | string | undefined): this {
        return this
    }
    radiusHeight(value: double | string | undefined): this {
        return this
    }
    radius(value: Length | Array<RadiusItem> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkRectComponent extends ArkCommonShapeMethodComponent implements RectAttribute {
    getPeer(): ArkRectPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkRectPeer)
    }
    public setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        if (this.checkPriority("setRectOptions")) {
            const options_casted = options as (RectOptions | RoundedRectOptions | undefined)
            this.getPeer()?.setRectOptionsAttribute(options_casted)
            this.applyOptionsFinish('RectAttribute');
            return this
        }
        return this
    }
    public radiusWidth(value: double | string | undefined): this {
        if (this.checkPriority("radiusWidth")) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setRadiusWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public radiusHeight(value: double | string | undefined): this {
        if (this.checkPriority("radiusHeight")) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setRadiusHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public radius(value: Length | Array<RadiusItem> | undefined): this {
        if (this.checkPriority("radius")) {
            const value_casted = value as (Length | Array<RadiusItem> | undefined)
            this.getPeer()?.setRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookRectAttributeModifier(this, value);
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
export function RectImpl(
    @memo
    style: ((attributes: RectAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRectComponent>((): ArkRectComponent => {
        return new ArkRectComponent()
    })
    NodeAttach<ArkRectPeer>((): ArkRectPeer => ArkRectPeer.create(receiver), (peer: ArkRectPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class RoundedRectOptions_serializer {
    public static write(buffer: SerializerBase, value: RoundedRectOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadiusWidth  = value.radiusWidth
        if (valueHolderForRadiusWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusWidthTmpValue  = valueHolderForRadiusWidth!
            if (valueHolderForRadiusWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusWidthTmpValueForIdx0  = valueHolderForRadiusWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRadiusWidthTmpValueForIdx0)
            } else if (valueHolderForRadiusWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusWidthTmpValueForIdx1  = valueHolderForRadiusWidthTmpValue as string
                valueSerializer.writeString(valueHolderForRadiusWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadiusHeight  = value.radiusHeight
        if (valueHolderForRadiusHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusHeightTmpValue  = valueHolderForRadiusHeight!
            if (valueHolderForRadiusHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusHeightTmpValueForIdx0  = valueHolderForRadiusHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRadiusHeightTmpValueForIdx0)
            } else if (valueHolderForRadiusHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusHeightTmpValueForIdx1  = valueHolderForRadiusHeightTmpValue as string
                valueSerializer.writeString(valueHolderForRadiusHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RoundedRectOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : double | string | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : double | string | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as double | string)
        }
        const widthTmpResult : double | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : double | string | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : double | string | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as double | string)
        }
        const heightTmpResult : double | string | undefined = heightTmpBuf
        const radiusWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusWidthTmpBuf : double | string | undefined = undefined
        if ((radiusWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusWidthTmpBuf_ : double | string | undefined
            if (radiusWidthTmpBuf_UnionSelector == (0).toChar()) {
                radiusWidthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (radiusWidthTmpBuf_UnionSelector == (1).toChar()) {
                radiusWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for radiusWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusWidthTmpBuf = (radiusWidthTmpBuf_ as double | string)
        }
        const radiusWidthTmpResult : double | string | undefined = radiusWidthTmpBuf
        const radiusHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusHeightTmpBuf : double | string | undefined = undefined
        if ((radiusHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusHeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusHeightTmpBuf_ : double | string | undefined
            if (radiusHeightTmpBuf_UnionSelector == (0).toChar()) {
                radiusHeightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (radiusHeightTmpBuf_UnionSelector == (1).toChar()) {
                radiusHeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for radiusHeightTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusHeightTmpBuf = (radiusHeightTmpBuf_ as double | string)
        }
        const radiusHeightTmpResult : double | string | undefined = radiusHeightTmpBuf
        let value : RoundedRectOptions = ({width: widthTmpResult, height: heightTmpResult, radiusWidth: radiusWidthTmpResult, radiusHeight: radiusHeightTmpResult} as RoundedRectOptions)
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
            if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof Length) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as Length
                if (valueHolderForRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx0  = valueHolderForRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx1  = valueHolderForRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx2  = valueHolderForRadiusTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (TypeChecker.isArray_RadiusItem(valueHolderForRadiusTmpValue)) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as Array<RadiusItem>
                valueSerializer.writeInt32((valueHolderForRadiusTmpValueForIdx1.length).toInt())
                for (let valueHolderForRadiusTmpValueForIdx1CounterI = 0; valueHolderForRadiusTmpValueForIdx1CounterI < valueHolderForRadiusTmpValueForIdx1.length; valueHolderForRadiusTmpValueForIdx1CounterI++) {
                    const valueHolderForRadiusTmpValueForIdx1TmpElement : RadiusItem = valueHolderForRadiusTmpValueForIdx1[valueHolderForRadiusTmpValueForIdx1CounterI]
                    const valueHolderForRadiusTmpValueForIdx1TmpElement_0  = valueHolderForRadiusTmpValueForIdx1TmpElement[0]
                    if (valueHolderForRadiusTmpValueForIdx1TmpElement_0 instanceof string) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx0  = valueHolderForRadiusTmpValueForIdx1TmpElement_0 as string
                        valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx0)
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_0 instanceof number) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx1  = valueHolderForRadiusTmpValueForIdx1TmpElement_0 as number
                        valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx1)
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_0 instanceof Resource) {
                        valueSerializer.writeInt8((2).toByte())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx2  = valueHolderForRadiusTmpValueForIdx1TmpElement_0 as Resource
                        Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx2)
                    }
                    const valueHolderForRadiusTmpValueForIdx1TmpElement_1  = valueHolderForRadiusTmpValueForIdx1TmpElement[1]
                    if (valueHolderForRadiusTmpValueForIdx1TmpElement_1 instanceof string) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx0  = valueHolderForRadiusTmpValueForIdx1TmpElement_1 as string
                        valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx0)
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_1 instanceof number) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx1  = valueHolderForRadiusTmpValueForIdx1TmpElement_1 as number
                        valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx1)
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_1 instanceof Resource) {
                        valueSerializer.writeInt8((2).toByte())
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
        let widthTmpBuf : double | string | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : double | string | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as double | string)
        }
        const widthTmpResult : double | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : double | string | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : double | string | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as double | string)
        }
        const heightTmpResult : double | string | undefined = heightTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : Length | Array<RadiusItem> | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBuf_ : Length | Array<RadiusItem> | undefined
            if (radiusTmpBuf_UnionSelector == (0).toChar()) {
                const radiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBuf_BufU : string | double | Resource | undefined
                if (radiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    radiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    radiusTmpBuf_BufU = valueDeserializer.readFloat64()
                } else if (radiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    radiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for radiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                radiusTmpBuf_ = (radiusTmpBuf_BufU as string | double | Resource)
            } else if (radiusTmpBuf_UnionSelector == (1).toChar()) {
                const radiusTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let radiusTmpBuf_BufU : Array<RadiusItem> = new Array<RadiusItem>(radiusTmpBuf_BufULength)
                for (let radiusTmpBuf_BufUBufCounterI = 0; radiusTmpBuf_BufUBufCounterI < radiusTmpBuf_BufULength; radiusTmpBuf_BufUBufCounterI++) {
                    const radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBuf_BufUTempBufValue0TempBuf : string | double | Resource | undefined
                    if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (0).toChar()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = (valueDeserializer.readString() as string)
                    } else if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (1).toChar()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = valueDeserializer.readFloat64()
                    } else if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (2).toChar()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for radiusTmpBuf_BufUTempBufValue0TempBuf has to be chosen through deserialisation.")
                    }
                    const radiusTmpBuf_BufUTempBufValue0 : Length = (radiusTmpBuf_BufUTempBufValue0TempBuf as string | double | Resource)
                    const radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBuf_BufUTempBufValue1TempBuf : string | double | Resource | undefined
                    if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (0).toChar()) {
                        radiusTmpBuf_BufUTempBufValue1TempBuf = (valueDeserializer.readString() as string)
                    } else if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (1).toChar()) {
                        radiusTmpBuf_BufUTempBufValue1TempBuf = valueDeserializer.readFloat64()
                    } else if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (2).toChar()) {
                        radiusTmpBuf_BufUTempBufValue1TempBuf = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for radiusTmpBuf_BufUTempBufValue1TempBuf has to be chosen through deserialisation.")
                    }
                    const radiusTmpBuf_BufUTempBufValue1 : Length = (radiusTmpBuf_BufUTempBufValue1TempBuf as string | double | Resource)
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
