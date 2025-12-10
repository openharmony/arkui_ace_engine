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
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent } from './common'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { AttributeModifier, hookFlexAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { FlexDirection, FlexWrap, FlexAlign, ItemAlign } from './enums'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from '@arkui.Graphics'
import { FlexModifier } from './../FlexModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
export class ArkFlexPeer extends ArkCommonMethodPeer {
    attributeSet?: FlexModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
    main?: arkui_Graphics_LengthMetrics;
    cross?: arkui_Graphics_LengthMetrics;
}
export interface FlexAttribute extends CommonMethod {
    setFlexOptions(value?: FlexOptions): this {
        throw new Error('Unimplemented method setFlexOptions')
    }
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error('Unimplemented method pointLight')
    }
    attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkFlexComponent extends ArkCommonMethodComponent implements FlexAttribute {
    getPeer(): ArkFlexPeer {
        return (this.peer as ArkFlexPeer)
    }
    public setFlexOptions(value?: FlexOptions): this {
        if (this.checkPriority('setFlexOptions')) {
            const value_casted = value as (FlexOptions | undefined)
            this.getPeer()?.setFlexOptionsAttribute(value_casted)
            this.applyOptionsFinish('FlexAttribute');
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority('pointLight')) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.setPointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookFlexAttributeModifier(this, value);
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
export function FlexImpl(
    @memo @memo_skip
    style: ((attributes: FlexAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkFlexComponent>((): ArkFlexComponent => {
        return new ArkFlexComponent()
    })
    NodeAttach<ArkFlexPeer>((): ArkFlexPeer => ArkFlexPeer.create(receiver), (_: ArkFlexPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class FlexSpaceOptions_serializer {
    public static write(buffer: SerializerBase, value: FlexSpaceOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMain  = value.main
        if (valueHolderForMain !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMainTmpValue  = valueHolderForMain!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForMainTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCross  = value.cross
        if (valueHolderForCross !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCrossTmpValue  = valueHolderForCross!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForCrossTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FlexSpaceOptions {
        let valueDeserializer : DeserializerBase = buffer
        const mainTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let mainTmpBuf : arkui_Graphics_LengthMetrics | undefined = undefined
        if ((mainTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mainTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const mainTmpResult : arkui_Graphics_LengthMetrics | undefined = mainTmpBuf
        const crossTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let crossTmpBuf : arkui_Graphics_LengthMetrics | undefined = undefined
        if ((crossTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            crossTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const crossTmpResult : arkui_Graphics_LengthMetrics | undefined = crossTmpBuf
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
            valueSerializer.writeInt32(valueHolderForDirectionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWrap  = value.wrap
        if (valueHolderForWrap !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWrapTmpValue  = (valueHolderForWrap as FlexWrap)
            valueSerializer.writeInt32(valueHolderForWrapTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForJustifyContent  = value.justifyContent
        if (valueHolderForJustifyContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForJustifyContentTmpValue  = (valueHolderForJustifyContent as FlexAlign)
            valueSerializer.writeInt32(valueHolderForJustifyContentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignItems  = value.alignItems
        if (valueHolderForAlignItems !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignItemsTmpValue  = (valueHolderForAlignItems as ItemAlign)
            valueSerializer.writeInt32(valueHolderForAlignItemsTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignContent  = value.alignContent
        if (valueHolderForAlignContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignContentTmpValue  = (valueHolderForAlignContent as FlexAlign)
            valueSerializer.writeInt32(valueHolderForAlignContentTmpValue.valueOf())
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
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let directionTmpBuf : FlexDirection | undefined = undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = FlexDirection.fromValue(valueDeserializer.readInt32())
        }
        const directionTmpResult : FlexDirection | undefined = directionTmpBuf
        const wrapTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let wrapTmpBuf : FlexWrap | undefined = undefined
        if ((wrapTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wrapTmpBuf = FlexWrap.fromValue(valueDeserializer.readInt32())
        }
        const wrapTmpResult : FlexWrap | undefined = wrapTmpBuf
        const justifyContentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let justifyContentTmpBuf : FlexAlign | undefined = undefined
        if ((justifyContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            justifyContentTmpBuf = FlexAlign.fromValue(valueDeserializer.readInt32())
        }
        const justifyContentTmpResult : FlexAlign | undefined = justifyContentTmpBuf
        const alignItemsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let alignItemsTmpBuf : ItemAlign | undefined = undefined
        if ((alignItemsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignItemsTmpBuf = ItemAlign.fromValue(valueDeserializer.readInt32())
        }
        const alignItemsTmpResult : ItemAlign | undefined = alignItemsTmpBuf
        const alignContentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let alignContentTmpBuf : FlexAlign | undefined = undefined
        if ((alignContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignContentTmpBuf = FlexAlign.fromValue(valueDeserializer.readInt32())
        }
        const alignContentTmpResult : FlexAlign | undefined = alignContentTmpBuf
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let spaceTmpBuf : FlexSpaceOptions | undefined = undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            spaceTmpBuf = FlexSpaceOptions_serializer.read(valueDeserializer)
        }
        const spaceTmpResult : FlexSpaceOptions | undefined = spaceTmpBuf
        let value : FlexOptions = ({direction: directionTmpResult, wrap: wrapTmpResult, justifyContent: justifyContentTmpResult, alignItems: alignItemsTmpResult, alignContent: alignContentTmpResult, space: spaceTmpResult} as FlexOptions)
        return value
    }
}
