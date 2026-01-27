/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ModifierStateManager } from "./../CommonModifier"
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
    setRadiusWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RectAttribute_setRadiusWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadiusHeightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
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
                } else if (valueTmpValueForIdx0 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx0ForIdx1)
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
                    } else if (valueTmpValueForIdx1TmpElement_0 instanceof double) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueForIdx1TmpElement_0ForIdx1  = valueTmpValueForIdx1TmpElement_0 as double
                        thisSerializer.writeFloat64(valueTmpValueForIdx1TmpElement_0ForIdx1)
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
                    } else if (valueTmpValueForIdx1TmpElement_1 instanceof double) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueForIdx1TmpElement_1ForIdx1  = valueTmpValueForIdx1TmpElement_1 as double
                        thisSerializer.writeFloat64(valueTmpValueForIdx1TmpElement_1ForIdx1)
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
    width?: Length;
    height?: Length;
    radius?: Length | Array<RadiusItem>;
}
export interface RoundedRectOptions {
    width?: Length;
    height?: Length;
    radiusWidth?: Length;
    radiusHeight?: Length;
}
export interface RectAttribute extends CommonShapeMethod {
    setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        throw new Error("Unimplemented method setRectOptions")
    }
    radiusWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method radiusWidth")
    }
    radiusHeight(value: Length | undefined): this {
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
    radiusWidth_value?: Length | undefined
    radiusHeight_value?: Length | undefined
    radius_value?: Length | Array<RadiusItem> | undefined
    attributeModifier_value?: AttributeModifier<RectAttribute> | AttributeModifier<CommonMethod> | undefined
    setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        return this
    }
    radiusWidth(value: Length | undefined): this {
        return this
    }
    radiusHeight(value: Length | undefined): this {
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
    public radiusWidth(value: Length | undefined): this {
        if (this.checkPriority("radiusWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setRadiusWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public radiusHeight(value: Length | undefined): this {
        if (this.checkPriority("radiusHeight")) {
            const value_casted = value as (Length | undefined)
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
): void {
    const receiver = remember<ArkRectComponent>((): ArkRectComponent => {
        return new ArkRectComponent()
    })
    NodeAttach<ArkRectPeer>((): ArkRectPeer => ArkRectPeer.create(receiver), (peer: ArkRectPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
    })
}

export class RoundedRectOptions_serializer {
    public static write(buffer: SerializerBase, value: RoundedRectOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadiusWidth  = value.radiusWidth
        if (valueHolderForRadiusWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusWidthTmpValue  = valueHolderForRadiusWidth!
            if (valueHolderForRadiusWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusWidthTmpValueForIdx0  = valueHolderForRadiusWidthTmpValue as string
                valueSerializer.writeString(valueHolderForRadiusWidthTmpValueForIdx0)
            } else if (valueHolderForRadiusWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusWidthTmpValueForIdx1  = valueHolderForRadiusWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRadiusWidthTmpValueForIdx1)
            } else if (valueHolderForRadiusWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRadiusWidthTmpValueForIdx2  = valueHolderForRadiusWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRadiusWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadiusHeight  = value.radiusHeight
        if (valueHolderForRadiusHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusHeightTmpValue  = valueHolderForRadiusHeight!
            if (valueHolderForRadiusHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusHeightTmpValueForIdx0  = valueHolderForRadiusHeightTmpValue as string
                valueSerializer.writeString(valueHolderForRadiusHeightTmpValueForIdx0)
            } else if (valueHolderForRadiusHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusHeightTmpValueForIdx1  = valueHolderForRadiusHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRadiusHeightTmpValueForIdx1)
            } else if (valueHolderForRadiusHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRadiusHeightTmpValueForIdx2  = valueHolderForRadiusHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRadiusHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RoundedRectOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Length | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | double | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toByte()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toByte()) {
                widthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (widthTmpBuf_UnionSelector == (2).toByte()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | double | Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Length | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | double | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toByte()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toByte()) {
                heightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (heightTmpBuf_UnionSelector == (2).toByte()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | double | Resource)
        }
        const heightTmpResult : Length | undefined = heightTmpBuf
        const radiusWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusWidthTmpBuf : Length | undefined = undefined
        if ((radiusWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusWidthTmpBuf_ : string | double | Resource | undefined
            if (radiusWidthTmpBuf_UnionSelector == (0).toByte()) {
                radiusWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (radiusWidthTmpBuf_UnionSelector == (1).toByte()) {
                radiusWidthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (radiusWidthTmpBuf_UnionSelector == (2).toByte()) {
                radiusWidthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for radiusWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusWidthTmpBuf = (radiusWidthTmpBuf_ as string | double | Resource)
        }
        const radiusWidthTmpResult : Length | undefined = radiusWidthTmpBuf
        const radiusHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusHeightTmpBuf : Length | undefined = undefined
        if ((radiusHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusHeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusHeightTmpBuf_ : string | double | Resource | undefined
            if (radiusHeightTmpBuf_UnionSelector == (0).toByte()) {
                radiusHeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (radiusHeightTmpBuf_UnionSelector == (1).toByte()) {
                radiusHeightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (radiusHeightTmpBuf_UnionSelector == (2).toByte()) {
                radiusHeightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for radiusHeightTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusHeightTmpBuf = (radiusHeightTmpBuf_ as string | double | Resource)
        }
        const radiusHeightTmpResult : Length | undefined = radiusHeightTmpBuf
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
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as Length
                if (valueHolderForRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx0  = valueHolderForRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof double) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx1  = valueHolderForRadiusTmpValueForIdx0 as double
                    valueSerializer.writeFloat64(valueHolderForRadiusTmpValueForIdx0ForIdx1)
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
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_0 instanceof double) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx1  = valueHolderForRadiusTmpValueForIdx1TmpElement_0 as double
                        valueSerializer.writeFloat64(valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx1)
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
                    } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_1 instanceof double) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx1  = valueHolderForRadiusTmpValueForIdx1TmpElement_1 as double
                        valueSerializer.writeFloat64(valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx1)
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
        let widthTmpBuf : Length | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | double | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toByte()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toByte()) {
                widthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (widthTmpBuf_UnionSelector == (2).toByte()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | double | Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Length | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | double | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toByte()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toByte()) {
                heightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (heightTmpBuf_UnionSelector == (2).toByte()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | double | Resource)
        }
        const heightTmpResult : Length | undefined = heightTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : Length | Array<RadiusItem> | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBuf_ : Length | Array<RadiusItem> | undefined
            if (radiusTmpBuf_UnionSelector == (0).toByte()) {
                const radiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBuf_BufU : string | double | Resource | undefined
                if (radiusTmpBuf_BufUUnionSelector == (0).toByte()) {
                    radiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBuf_BufUUnionSelector == (1).toByte()) {
                    radiusTmpBuf_BufU = valueDeserializer.readFloat64()
                } else if (radiusTmpBuf_BufUUnionSelector == (2).toByte()) {
                    radiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for radiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                radiusTmpBuf_ = (radiusTmpBuf_BufU as string | double | Resource)
            } else if (radiusTmpBuf_UnionSelector == (1).toByte()) {
                const radiusTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let radiusTmpBuf_BufU : Array<RadiusItem> = new Array<RadiusItem>(radiusTmpBuf_BufULength)
                for (let radiusTmpBuf_BufUBufCounterI = 0; radiusTmpBuf_BufUBufCounterI < radiusTmpBuf_BufULength; radiusTmpBuf_BufUBufCounterI++) {
                    const radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBuf_BufUTempBufValue0TempBuf : string | double | Resource | undefined
                    if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (0).toByte()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = (valueDeserializer.readString() as string)
                    } else if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (1).toByte()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = valueDeserializer.readFloat64()
                    } else if (radiusTmpBuf_BufUTempBufValue0TempBufUnionSelector == (2).toByte()) {
                        radiusTmpBuf_BufUTempBufValue0TempBuf = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for radiusTmpBuf_BufUTempBufValue0TempBuf has to be chosen through deserialisation.")
                    }
                    const radiusTmpBuf_BufUTempBufValue0 : Length = (radiusTmpBuf_BufUTempBufValue0TempBuf as string | double | Resource)
                    const radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBuf_BufUTempBufValue1TempBuf : string | double | Resource | undefined
                    if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (0).toByte()) {
                        radiusTmpBuf_BufUTempBufValue1TempBuf = (valueDeserializer.readString() as string)
                    } else if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (1).toByte()) {
                        radiusTmpBuf_BufUTempBufValue1TempBuf = valueDeserializer.readFloat64()
                    } else if (radiusTmpBuf_BufUTempBufValue1TempBufUnionSelector == (2).toByte()) {
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
