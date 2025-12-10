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
import { global_resource_Resource_serializer } from './../framework/resource'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonShapeMethodPeer, CommonShapeMethod as arkui_component_common_CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonMethodComponent } from './common'
import { Length, Resource as arkui_component_units_Resource } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { AttributeModifier, hookRectAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { RectModifier } from './../RectModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkRectPeer extends ArkCommonShapeMethodPeer {
    attributeSet?: RectModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
                } else if (valueTmpValueForIdx0 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof Array) {
                if (valueTmpValue.length == 0) {
                    thisSerializer.writeInt8((1).toByte())
                    thisSerializer.writeInt32(0)
                } else {
                    const valueTmpValueElem  = valueTmpValue[0]
                    if (valueTmpValueElem instanceof Tuple) {
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
                            } else if (valueTmpValueForIdx1TmpElement_0 instanceof arkui_component_units_Resource) {
                                thisSerializer.writeInt8((2).toByte())
                                const valueTmpValueForIdx1TmpElement_0ForIdx2  = valueTmpValueForIdx1TmpElement_0 as arkui_component_units_Resource
                                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement_0ForIdx2)
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
                            } else if (valueTmpValueForIdx1TmpElement_1 instanceof arkui_component_units_Resource) {
                                thisSerializer.writeInt8((2).toByte())
                                const valueTmpValueForIdx1TmpElement_1ForIdx2  = valueTmpValueForIdx1TmpElement_1 as arkui_component_units_Resource
                                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement_1ForIdx2)
                            }
                        }
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
export interface RectAttribute extends arkui_component_common_CommonShapeMethod {
    setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        throw new Error('Unimplemented method setRectOptions')
    }
    radiusWidth(value: double | string | undefined): this {
        throw new Error('Unimplemented method radiusWidth')
    }
    radiusHeight(value: double | string | undefined): this {
        throw new Error('Unimplemented method radiusHeight')
    }
    radius(value: Length | Array<RadiusItem> | undefined): this {
        throw new Error('Unimplemented method radius')
    }
    attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<arkui_component_common_CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkRectComponent extends ArkCommonShapeMethodComponent implements RectAttribute {
    getPeer(): ArkRectPeer {
        return (this.peer as ArkRectPeer)
    }
    public setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        if (this.checkPriority('setRectOptions')) {
            const options_casted = options as (RectOptions | RoundedRectOptions | undefined)
            this.getPeer()?.setRectOptionsAttribute(options_casted)
            this.applyOptionsFinish('RectAttribute');
            return this
        }
        return this
    }
    public radiusWidth(value: double | string | undefined): this {
        if (this.checkPriority('radiusWidth')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setRadiusWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public radiusHeight(value: double | string | undefined): this {
        if (this.checkPriority('radiusHeight')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setRadiusHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public radius(value: Length | Array<RadiusItem> | undefined): this {
        if (this.checkPriority('radius')) {
            const value_casted = value as (Length | Array<RadiusItem> | undefined)
            this.getPeer()?.setRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<arkui_component_common_CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
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
    @memo @memo_skip
    style: ((attributes: RectAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkRectComponent>((): ArkRectComponent => {
        return new ArkRectComponent()
    })
    NodeAttach<ArkRectPeer>((): ArkRectPeer => ArkRectPeer.create(receiver), (_: ArkRectPeer): void => {
        style?.(receiver)
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
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : double | string | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : double | string | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as double | string)
        }
        const widthTmpResult : double | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : double | string | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt : double | string | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as double | string)
        }
        const heightTmpResult : double | string | undefined = heightTmpBuf
        const radiusWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusWidthTmpBuf : double | string | undefined = undefined
        if ((radiusWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let radiusWidthTmpBufOpt : double | string | undefined
            if (radiusWidthTmpBufOptUnionSelector == (0).toByte()) {
                radiusWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (radiusWidthTmpBufOptUnionSelector == (1).toByte()) {
                radiusWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for radiusWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            radiusWidthTmpBuf = (radiusWidthTmpBufOpt as double | string)
        }
        const radiusWidthTmpResult : double | string | undefined = radiusWidthTmpBuf
        const radiusHeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusHeightTmpBuf : double | string | undefined = undefined
        if ((radiusHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusHeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let radiusHeightTmpBufOpt : double | string | undefined
            if (radiusHeightTmpBufOptUnionSelector == (0).toByte()) {
                radiusHeightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (radiusHeightTmpBufOptUnionSelector == (1).toByte()) {
                radiusHeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for radiusHeightTmpBufOpt has to be chosen through deserialisation.')
            }
            radiusHeightTmpBuf = (radiusHeightTmpBufOpt as double | string)
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
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof double) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx1  = valueHolderForRadiusTmpValueForIdx0 as double
                    valueSerializer.writeFloat64(valueHolderForRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx2  = valueHolderForRadiusTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForRadiusTmpValue instanceof Array) {
                if (valueHolderForRadiusTmpValue.length == 0) {
                    valueSerializer.writeInt8((1).toByte())
                    valueSerializer.writeInt32(0)
                } else {
                    const valueHolderForRadiusTmpValueElem  = valueHolderForRadiusTmpValue[0]
                    if (valueHolderForRadiusTmpValueElem instanceof Tuple) {
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
                            } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_0 instanceof arkui_component_units_Resource) {
                                valueSerializer.writeInt8((2).toByte())
                                const valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx2  = valueHolderForRadiusTmpValueForIdx1TmpElement_0 as arkui_component_units_Resource
                                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1TmpElement_0ForIdx2)
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
                            } else if (valueHolderForRadiusTmpValueForIdx1TmpElement_1 instanceof arkui_component_units_Resource) {
                                valueSerializer.writeInt8((2).toByte())
                                const valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx2  = valueHolderForRadiusTmpValueForIdx1TmpElement_1 as arkui_component_units_Resource
                                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1TmpElement_1ForIdx2)
                            }
                        }
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RectOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : double | string | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : double | string | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as double | string)
        }
        const widthTmpResult : double | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : double | string | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt : double | string | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as double | string)
        }
        const heightTmpResult : double | string | undefined = heightTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusTmpBuf : Length | Array<RadiusItem> | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBufOpt : Length | Array<RadiusItem> | undefined
            if (radiusTmpBufOptUnionSelector == (0).toByte()) {
                const radiusTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBufOptBufU : string | double | arkui_component_units_Resource | undefined
                if (radiusTmpBufOptBufUUnionSelector == (0).toByte()) {
                    radiusTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBufOptBufUUnionSelector == (1).toByte()) {
                    radiusTmpBufOptBufU = valueDeserializer.readFloat64()
                } else if (radiusTmpBufOptBufUUnionSelector == (2).toByte()) {
                    radiusTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for radiusTmpBufOptBufU has to be chosen through deserialisation.')
                }
                radiusTmpBufOpt = (radiusTmpBufOptBufU as string | double | arkui_component_units_Resource)
            } else if (radiusTmpBufOptUnionSelector == (1).toByte()) {
                const radiusTmpBufOptBufULength : int32 = valueDeserializer.readInt32()
                let radiusTmpBufOptBufU : Array<RadiusItem> = new Array<RadiusItem>(radiusTmpBufOptBufULength)
                for (let radiusTmpBufOptBufUBufCounterI = 0; radiusTmpBufOptBufUBufCounterI < radiusTmpBufOptBufULength; radiusTmpBufOptBufUBufCounterI++) {
                    const radiusTmpBufOptBufUTempBufValue0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBufOptBufUTempBufValue0TempBuf : string | double | arkui_component_units_Resource | undefined
                    if (radiusTmpBufOptBufUTempBufValue0TempBufUnionSelector == (0).toByte()) {
                        radiusTmpBufOptBufUTempBufValue0TempBuf = (valueDeserializer.readString() as string)
                    } else if (radiusTmpBufOptBufUTempBufValue0TempBufUnionSelector == (1).toByte()) {
                        radiusTmpBufOptBufUTempBufValue0TempBuf = valueDeserializer.readFloat64()
                    } else if (radiusTmpBufOptBufUTempBufValue0TempBufUnionSelector == (2).toByte()) {
                        radiusTmpBufOptBufUTempBufValue0TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error('One of the branches for radiusTmpBufOptBufUTempBufValue0TempBuf has to be chosen through deserialisation.')
                    }
                    const radiusTmpBufOptBufUTempBufValue0 : Length = (radiusTmpBufOptBufUTempBufValue0TempBuf as string | double | arkui_component_units_Resource)
                    const radiusTmpBufOptBufUTempBufValue1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBufOptBufUTempBufValue1TempBuf : string | double | arkui_component_units_Resource | undefined
                    if (radiusTmpBufOptBufUTempBufValue1TempBufUnionSelector == (0).toByte()) {
                        radiusTmpBufOptBufUTempBufValue1TempBuf = (valueDeserializer.readString() as string)
                    } else if (radiusTmpBufOptBufUTempBufValue1TempBufUnionSelector == (1).toByte()) {
                        radiusTmpBufOptBufUTempBufValue1TempBuf = valueDeserializer.readFloat64()
                    } else if (radiusTmpBufOptBufUTempBufValue1TempBufUnionSelector == (2).toByte()) {
                        radiusTmpBufOptBufUTempBufValue1TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error('One of the branches for radiusTmpBufOptBufUTempBufValue1TempBuf has to be chosen through deserialisation.')
                    }
                    const radiusTmpBufOptBufUTempBufValue1 : Length = (radiusTmpBufOptBufUTempBufValue1TempBuf as string | double | arkui_component_units_Resource)
                    radiusTmpBufOptBufU[radiusTmpBufOptBufUBufCounterI] = ([radiusTmpBufOptBufUTempBufValue0, radiusTmpBufOptBufUTempBufValue1] as RadiusItem)
                }
                radiusTmpBufOpt = radiusTmpBufOptBufU
            } else {
                throw new Error('One of the branches for radiusTmpBufOpt has to be chosen through deserialisation.')
            }
            radiusTmpBuf = (radiusTmpBufOpt as Length | Array<RadiusItem>)
        }
        const radiusTmpResult : Length | Array<RadiusItem> | undefined = radiusTmpBuf
        let value : RectOptions = ({width: widthTmpResult, height: heightTmpResult, radius: radiusTmpResult} as RectOptions)
        return value
    }
}
