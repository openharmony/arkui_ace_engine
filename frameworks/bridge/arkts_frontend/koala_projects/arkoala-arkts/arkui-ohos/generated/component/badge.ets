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
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { AttributeModifier, hookBadgeAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { ResourceColor, Resource as arkui_component_units_Resource, ResourceStr as arkui_component_units_ResourceStr, Length, Position, Position_serializer } from './units'
import { Color as arkui_component_enums_Color, FontWeight } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { BadgeModifier } from './../BadgeModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkBadgePeer extends ArkCommonMethodPeer {
    attributeSet?: BadgeModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkBadgePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Badge_construct(peerId, flags)
        const _peer  = new ArkBadgePeer(_peerPtr, peerId, 'Badge', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setBadgeOptionsAttribute(value: BadgeParamWithNumber | BadgeParamWithString): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof BadgeParamWithNumber) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as BadgeParamWithNumber
            BadgeParamWithNumber_serializer.write(thisSerializer, valueForIdx0)
        } else if (value instanceof BadgeParamWithString) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as BadgeParamWithString
            BadgeParamWithString_serializer.write(thisSerializer, valueForIdx1)
        }
        ArkUIGeneratedNativeModule._BadgeInterface_setBadgeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum BadgePosition {
    RightTop = 0,
    Right = 1,
    Left = 2,
    RIGHT_TOP = 0,
    RIGHT = 1,
    LEFT = 2
}
export interface BadgeStyle {
    color?: ResourceColor;
    fontSize?: double | arkui_component_units_ResourceStr;
    badgeSize?: double | arkui_component_units_ResourceStr;
    badgeColor?: ResourceColor;
    borderColor?: ResourceColor;
    borderWidth?: Length;
    fontWeight?: int32 | FontWeight | arkui_component_units_ResourceStr;
}
export interface BadgeParam {
    position?: BadgePosition | Position;
    style: BadgeStyle;
}
export interface BadgeParamWithNumber extends BadgeParam {
    count: int32;
    maxCount?: int32;
}
export interface BadgeParamWithString extends BadgeParam {
    value: arkui_component_units_ResourceStr;
}
export interface BadgeAttribute extends CommonMethod {
    setBadgeOptions(value: BadgeParamWithNumber | BadgeParamWithString): this {
        throw new Error('Unimplemented method setBadgeOptions')
    }
    attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkBadgeComponent extends ArkCommonMethodComponent implements BadgeAttribute {
    getPeer(): ArkBadgePeer {
        return (this.peer as ArkBadgePeer)
    }
    public setBadgeOptions(value: BadgeParamWithNumber | BadgeParamWithString): this {
        if (this.checkPriority('setBadgeOptions')) {
            const value_casted = value as (BadgeParamWithNumber | BadgeParamWithString)
            this.getPeer()?.setBadgeOptionsAttribute(value_casted)
            this.applyOptionsFinish('BadgeAttribute');
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<BadgeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookBadgeAttributeModifier(this, value);
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
export class BadgeStyle_serializer {
    public static write(buffer: SerializerBase, value: BadgeStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            if (valueHolderForFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontSizeTmpValueForIdx0  = valueHolderForFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForFontSizeTmpValueForIdx0)
            } else if (valueHolderForFontSizeTmpValue instanceof arkui_component_units_ResourceStr) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontSizeTmpValueForIdx1  = valueHolderForFontSizeTmpValue as arkui_component_units_ResourceStr
                if (valueHolderForFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForFontSizeTmpValueForIdx1ForIdx0  = valueHolderForFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForFontSizeTmpValueForIdx1 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForFontSizeTmpValueForIdx1ForIdx1  = valueHolderForFontSizeTmpValueForIdx1 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBadgeSize  = value.badgeSize
        if (valueHolderForBadgeSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBadgeSizeTmpValue  = valueHolderForBadgeSize!
            if (valueHolderForBadgeSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBadgeSizeTmpValueForIdx0  = valueHolderForBadgeSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBadgeSizeTmpValueForIdx0)
            } else if (valueHolderForBadgeSizeTmpValue instanceof arkui_component_units_ResourceStr) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBadgeSizeTmpValueForIdx1  = valueHolderForBadgeSizeTmpValue as arkui_component_units_ResourceStr
                if (valueHolderForBadgeSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBadgeSizeTmpValueForIdx1ForIdx0  = valueHolderForBadgeSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForBadgeSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForBadgeSizeTmpValueForIdx1 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBadgeSizeTmpValueForIdx1ForIdx1  = valueHolderForBadgeSizeTmpValueForIdx1 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForBadgeSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBadgeColor  = value.badgeColor
        if (valueHolderForBadgeColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBadgeColorTmpValue  = valueHolderForBadgeColor!
            if (valueHolderForBadgeColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBadgeColorTmpValueForIdx0  = valueHolderForBadgeColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBadgeColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForBadgeColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBadgeColorTmpValueForIdx1  = valueHolderForBadgeColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBadgeColorTmpValueForIdx1)
            } else if (valueHolderForBadgeColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBadgeColorTmpValueForIdx2  = valueHolderForBadgeColorTmpValue as string
                valueSerializer.writeString(valueHolderForBadgeColorTmpValueForIdx2)
            } else if (valueHolderForBadgeColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBadgeColorTmpValueForIdx3  = valueHolderForBadgeColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBadgeColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBorderColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForBorderColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx1)
            } else if (valueHolderForBorderColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderColorTmpValueForIdx2  = valueHolderForBorderColorTmpValue as string
                valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx2)
            } else if (valueHolderForBorderColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBorderColorTmpValueForIdx3  = valueHolderForBorderColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as string
                valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0)
            } else if (valueHolderForBorderWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBorderWidthTmpValueForIdx1)
            } else if (valueHolderForBorderWidthTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderWidthTmpValueForIdx2  = valueHolderForBorderWidthTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = valueHolderForFontWeight!
            if (valueHolderForFontWeightTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontWeightTmpValueForIdx0  = valueHolderForFontWeightTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx0)
            } else if (valueHolderForFontWeightTmpValue instanceof FontWeight) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontWeightTmpValueForIdx1  = valueHolderForFontWeightTmpValue as FontWeight
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx1.valueOf())
            } else if (valueHolderForFontWeightTmpValue instanceof arkui_component_units_ResourceStr) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontWeightTmpValueForIdx2  = valueHolderForFontWeightTmpValue as arkui_component_units_ResourceStr
                if (valueHolderForFontWeightTmpValueForIdx2 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForFontWeightTmpValueForIdx2ForIdx0  = valueHolderForFontWeightTmpValueForIdx2 as string
                    valueSerializer.writeString(valueHolderForFontWeightTmpValueForIdx2ForIdx0)
                } else if (valueHolderForFontWeightTmpValueForIdx2 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForFontWeightTmpValueForIdx2ForIdx1  = valueHolderForFontWeightTmpValueForIdx2 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontWeightTmpValueForIdx2ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BadgeStyle {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = valueDeserializer.readInt32()
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (colorTmpBufOptUnionSelector == (3).toByte()) {
                colorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontSizeTmpBuf : double | arkui_component_units_ResourceStr | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBufOpt : double | arkui_component_units_ResourceStr | undefined
            if (fontSizeTmpBufOptUnionSelector == (0).toByte()) {
                fontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (fontSizeTmpBufOptUnionSelector == (1).toByte()) {
                const fontSizeTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let fontSizeTmpBufOptBufU : string | arkui_component_units_Resource | undefined
                if (fontSizeTmpBufOptBufUUnionSelector == (0).toByte()) {
                    fontSizeTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (fontSizeTmpBufOptBufUUnionSelector == (1).toByte()) {
                    fontSizeTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for fontSizeTmpBufOptBufU has to be chosen through deserialisation.')
                }
                fontSizeTmpBufOpt = (fontSizeTmpBufOptBufU as string | arkui_component_units_Resource)
            } else {
                throw new Error('One of the branches for fontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            fontSizeTmpBuf = (fontSizeTmpBufOpt as double | arkui_component_units_ResourceStr)
        }
        const fontSizeTmpResult : double | arkui_component_units_ResourceStr | undefined = fontSizeTmpBuf
        const badgeSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let badgeSizeTmpBuf : double | arkui_component_units_ResourceStr | undefined = undefined
        if ((badgeSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const badgeSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let badgeSizeTmpBufOpt : double | arkui_component_units_ResourceStr | undefined
            if (badgeSizeTmpBufOptUnionSelector == (0).toByte()) {
                badgeSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (badgeSizeTmpBufOptUnionSelector == (1).toByte()) {
                const badgeSizeTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let badgeSizeTmpBufOptBufU : string | arkui_component_units_Resource | undefined
                if (badgeSizeTmpBufOptBufUUnionSelector == (0).toByte()) {
                    badgeSizeTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (badgeSizeTmpBufOptBufUUnionSelector == (1).toByte()) {
                    badgeSizeTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for badgeSizeTmpBufOptBufU has to be chosen through deserialisation.')
                }
                badgeSizeTmpBufOpt = (badgeSizeTmpBufOptBufU as string | arkui_component_units_Resource)
            } else {
                throw new Error('One of the branches for badgeSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            badgeSizeTmpBuf = (badgeSizeTmpBufOpt as double | arkui_component_units_ResourceStr)
        }
        const badgeSizeTmpResult : double | arkui_component_units_ResourceStr | undefined = badgeSizeTmpBuf
        const badgeColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let badgeColorTmpBuf : ResourceColor | undefined = undefined
        if ((badgeColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const badgeColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let badgeColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (badgeColorTmpBufOptUnionSelector == (0).toByte()) {
                badgeColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (badgeColorTmpBufOptUnionSelector == (1).toByte()) {
                badgeColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (badgeColorTmpBufOptUnionSelector == (2).toByte()) {
                badgeColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (badgeColorTmpBufOptUnionSelector == (3).toByte()) {
                badgeColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for badgeColorTmpBufOpt has to be chosen through deserialisation.')
            }
            badgeColorTmpBuf = (badgeColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const badgeColorTmpResult : ResourceColor | undefined = badgeColorTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderColorTmpBuf : ResourceColor | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (borderColorTmpBufOptUnionSelector == (0).toByte()) {
                borderColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (borderColorTmpBufOptUnionSelector == (1).toByte()) {
                borderColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (borderColorTmpBufOptUnionSelector == (2).toByte()) {
                borderColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (borderColorTmpBufOptUnionSelector == (3).toByte()) {
                borderColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderColorTmpBufOpt has to be chosen through deserialisation.')
            }
            borderColorTmpBuf = (borderColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const borderColorTmpResult : ResourceColor | undefined = borderColorTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderWidthTmpBuf : Length | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (borderWidthTmpBufOptUnionSelector == (0).toByte()) {
                borderWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (borderWidthTmpBufOptUnionSelector == (1).toByte()) {
                borderWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (borderWidthTmpBufOptUnionSelector == (2).toByte()) {
                borderWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            borderWidthTmpBuf = (borderWidthTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const borderWidthTmpResult : Length | undefined = borderWidthTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontWeightTmpBuf : int32 | FontWeight | arkui_component_units_ResourceStr | undefined = undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontWeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontWeightTmpBufOpt : int32 | FontWeight | arkui_component_units_ResourceStr | undefined
            if (fontWeightTmpBufOptUnionSelector == (0).toByte()) {
                fontWeightTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontWeightTmpBufOptUnionSelector == (1).toByte()) {
                fontWeightTmpBufOpt = FontWeight.fromValue(valueDeserializer.readInt32())
            } else if (fontWeightTmpBufOptUnionSelector == (2).toByte()) {
                const fontWeightTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let fontWeightTmpBufOptBufU : string | arkui_component_units_Resource | undefined
                if (fontWeightTmpBufOptBufUUnionSelector == (0).toByte()) {
                    fontWeightTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (fontWeightTmpBufOptBufUUnionSelector == (1).toByte()) {
                    fontWeightTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for fontWeightTmpBufOptBufU has to be chosen through deserialisation.')
                }
                fontWeightTmpBufOpt = (fontWeightTmpBufOptBufU as string | arkui_component_units_Resource)
            } else {
                throw new Error('One of the branches for fontWeightTmpBufOpt has to be chosen through deserialisation.')
            }
            fontWeightTmpBuf = (fontWeightTmpBufOpt as int32 | FontWeight | arkui_component_units_ResourceStr)
        }
        const fontWeightTmpResult : int32 | FontWeight | arkui_component_units_ResourceStr | undefined = fontWeightTmpBuf
        let value : BadgeStyle = ({color: colorTmpResult, fontSize: fontSizeTmpResult, badgeSize: badgeSizeTmpResult, badgeColor: badgeColorTmpResult, borderColor: borderColorTmpResult, borderWidth: borderWidthTmpResult, fontWeight: fontWeightTmpResult} as BadgeStyle)
        return value
    }
}
export class BadgeParamWithNumber_serializer {
    public static write(buffer: SerializerBase, value: BadgeParamWithNumber): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPosition  = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue  = valueHolderForPosition!
            if (valueHolderForPositionTmpValue instanceof BadgePosition) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPositionTmpValueForIdx0  = valueHolderForPositionTmpValue as BadgePosition
                valueSerializer.writeInt32(valueHolderForPositionTmpValueForIdx0.valueOf())
            } else if (valueHolderForPositionTmpValue instanceof Position) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPositionTmpValueForIdx1  = valueHolderForPositionTmpValue as Position
                Position_serializer.write(valueSerializer, valueHolderForPositionTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        BadgeStyle_serializer.write(valueSerializer, valueHolderForStyle)
        const valueHolderForCount  = value.count
        valueSerializer.writeInt32(valueHolderForCount)
        const valueHolderForMaxCount  = value.maxCount
        if (valueHolderForMaxCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxCountTmpValue  = valueHolderForMaxCount!
            valueSerializer.writeInt32(valueHolderForMaxCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BadgeParamWithNumber {
        let valueDeserializer : DeserializerBase = buffer
        const positionTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let positionTmpBuf : BadgePosition | Position | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const positionTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let positionTmpBufOpt : BadgePosition | Position | undefined
            if (positionTmpBufOptUnionSelector == (0).toByte()) {
                positionTmpBufOpt = BadgePosition.fromValue(valueDeserializer.readInt32())
            } else if (positionTmpBufOptUnionSelector == (1).toByte()) {
                positionTmpBufOpt = Position_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for positionTmpBufOpt has to be chosen through deserialisation.')
            }
            positionTmpBuf = (positionTmpBufOpt as BadgePosition | Position)
        }
        const positionTmpResult : BadgePosition | Position | undefined = positionTmpBuf
        const styleTmpResult : BadgeStyle = BadgeStyle_serializer.read(valueDeserializer)
        const countTmpResult : int32 = valueDeserializer.readInt32()
        const maxCountTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxCountTmpBuf : int32 | undefined = undefined
        if ((maxCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxCountTmpBuf = valueDeserializer.readInt32()
        }
        const maxCountTmpResult : int32 | undefined = maxCountTmpBuf
        let value : BadgeParamWithNumber = ({position: positionTmpResult, style: styleTmpResult, count: countTmpResult, maxCount: maxCountTmpResult} as BadgeParamWithNumber)
        return value
    }
}
export class BadgeParamWithString_serializer {
    public static write(buffer: SerializerBase, value: BadgeParamWithString): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPosition  = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue  = valueHolderForPosition!
            if (valueHolderForPositionTmpValue instanceof BadgePosition) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPositionTmpValueForIdx0  = valueHolderForPositionTmpValue as BadgePosition
                valueSerializer.writeInt32(valueHolderForPositionTmpValueForIdx0.valueOf())
            } else if (valueHolderForPositionTmpValue instanceof Position) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPositionTmpValueForIdx1  = valueHolderForPositionTmpValue as Position
                Position_serializer.write(valueSerializer, valueHolderForPositionTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        BadgeStyle_serializer.write(valueSerializer, valueHolderForStyle)
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): BadgeParamWithString {
        let valueDeserializer : DeserializerBase = buffer
        const positionTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let positionTmpBuf : BadgePosition | Position | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const positionTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let positionTmpBufOpt : BadgePosition | Position | undefined
            if (positionTmpBufOptUnionSelector == (0).toByte()) {
                positionTmpBufOpt = BadgePosition.fromValue(valueDeserializer.readInt32())
            } else if (positionTmpBufOptUnionSelector == (1).toByte()) {
                positionTmpBufOpt = Position_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for positionTmpBufOpt has to be chosen through deserialisation.')
            }
            positionTmpBuf = (positionTmpBufOpt as BadgePosition | Position)
        }
        const positionTmpResult : BadgePosition | Position | undefined = positionTmpBuf
        const styleTmpResult : BadgeStyle = BadgeStyle_serializer.read(valueDeserializer)
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | arkui_component_units_Resource | undefined
        if (valueTmpBufUnionSelector == (0).toByte()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toByte()) {
            valueTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for valueTmpBuf has to be chosen through deserialisation.')
        }
        const valueTmpResult : arkui_component_units_ResourceStr = (valueTmpBuf as string | arkui_component_units_Resource)
        let value : BadgeParamWithString = ({position: positionTmpResult, style: styleTmpResult, value: valueTmpResult} as BadgeParamWithString)
        return value
    }
}
