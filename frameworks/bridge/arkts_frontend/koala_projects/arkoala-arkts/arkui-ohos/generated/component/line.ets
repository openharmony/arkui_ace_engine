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
import { AttributeModifier, hookLineAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { LineModifier } from './../LineModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkLinePeer extends ArkCommonShapeMethodPeer {
    attributeSet?: LineModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValue_0ForIdx0  = valueTmpValue_0 as string
                thisSerializer.writeString(valueTmpValue_0ForIdx0)
            } else if (valueTmpValue_0 instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValue_0ForIdx1  = valueTmpValue_0 as double
                thisSerializer.writeFloat64(valueTmpValue_0ForIdx1)
            } else if (valueTmpValue_0 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValue_0ForIdx2  = valueTmpValue_0 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValue_0ForIdx2)
            }
            const valueTmpValue_1  = valueTmpValue[1]
            if (valueTmpValue_1 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValue_1ForIdx0  = valueTmpValue_1 as string
                thisSerializer.writeString(valueTmpValue_1ForIdx0)
            } else if (valueTmpValue_1 instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValue_1ForIdx1  = valueTmpValue_1 as double
                thisSerializer.writeFloat64(valueTmpValue_1ForIdx1)
            } else if (valueTmpValue_1 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValue_1ForIdx2  = valueTmpValue_1 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValue_1ForIdx2)
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValue_0ForIdx0  = valueTmpValue_0 as string
                thisSerializer.writeString(valueTmpValue_0ForIdx0)
            } else if (valueTmpValue_0 instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValue_0ForIdx1  = valueTmpValue_0 as double
                thisSerializer.writeFloat64(valueTmpValue_0ForIdx1)
            } else if (valueTmpValue_0 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValue_0ForIdx2  = valueTmpValue_0 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValue_0ForIdx2)
            }
            const valueTmpValue_1  = valueTmpValue[1]
            if (valueTmpValue_1 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValue_1ForIdx0  = valueTmpValue_1 as string
                thisSerializer.writeString(valueTmpValue_1ForIdx0)
            } else if (valueTmpValue_1 instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValue_1ForIdx1  = valueTmpValue_1 as double
                thisSerializer.writeFloat64(valueTmpValue_1ForIdx1)
            } else if (valueTmpValue_1 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValue_1ForIdx2  = valueTmpValue_1 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValue_1ForIdx2)
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
    width?: string | double;
    height?: string | double;
}
export interface LineAttribute extends arkui_component_common_CommonShapeMethod {
    setLineOptions(options?: LineOptions): this {
        throw new Error('Unimplemented method setLineOptions')
    }
    startPoint(value: ShapePoint | undefined): this {
        throw new Error('Unimplemented method startPoint')
    }
    endPoint(value: ShapePoint | undefined): this {
        throw new Error('Unimplemented method endPoint')
    }
    attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<arkui_component_common_CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkLineComponent extends ArkCommonShapeMethodComponent implements LineAttribute {
    getPeer(): ArkLinePeer {
        return (this.peer as ArkLinePeer)
    }
    public setLineOptions(options?: LineOptions): this {
        if (this.checkPriority('setLineOptions')) {
            const options_casted = options as (LineOptions | undefined)
            this.getPeer()?.setLineOptionsAttribute(options_casted)
            this.applyOptionsFinish('LineAttribute');
            return this
        }
        return this
    }
    public startPoint(value: ShapePoint | undefined): this {
        if (this.checkPriority('startPoint')) {
            const value_casted = value as (ShapePoint | undefined)
            this.getPeer()?.setStartPointAttribute(value_casted)
            return this
        }
        return this
    }
    public endPoint(value: ShapePoint | undefined): this {
        if (this.checkPriority('endPoint')) {
            const value_casted = value as (ShapePoint | undefined)
            this.getPeer()?.setEndPointAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LineAttribute> | AttributeModifier<arkui_component_common_CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookLineAttributeModifier(this, value);
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
export function LineImpl(
    @memo @memo_skip
    style: ((attributes: LineAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkLineComponent>((): ArkLineComponent => {
        return new ArkLineComponent()
    })
    NodeAttach<ArkLinePeer>((): ArkLinePeer => ArkLinePeer.create(receiver), (_: ArkLinePeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class LineOptions_serializer {
    public static write(buffer: SerializerBase, value: LineOptions): void {
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
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : string | double | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : string | double | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = valueDeserializer.readFloat64()
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as string | double)
        }
        const widthTmpResult : string | double | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : string | double | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt : string | double | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = valueDeserializer.readFloat64()
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as string | double)
        }
        const heightTmpResult : string | double | undefined = heightTmpBuf
        let value : LineOptions = ({width: widthTmpResult, height: heightTmpResult} as LineOptions)
        return value
    }
}
