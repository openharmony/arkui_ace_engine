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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ShadowOptions_serializer, ShadowOptions, ClickEvent, HoverCallback, HoverEvent, BaseEvent, ArkCommonMethodComponent } from './common'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from '@arkui.Graphics'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { global_resource_Resource_serializer } from './../framework/resource'
import { arkui_component_units_Font_serializer, Font as arkui_component_units_Font, ResourceColor, Resource as arkui_component_units_Resource, Length, Dimension, BorderRadiuses, BorderRadiuses_serializer } from './units'
import { DecorationStyleInterface_serializer, DecorationStyleInterface } from './styledString'
import { Color as arkui_component_enums_Color, FontStyle, FontWeight, TextCase, InteractionHand } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { AttributeModifier, hookBaseSpanAttributeModifier, AttributeUpdater, hookSpanAttributeModifier } from '#handwritten'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { BaseSpanModifier } from './../BaseSpanModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { SpanModifier } from './../SpanModifier'
export class ArkBaseSpanPeer extends ArkCommonMethodPeer {
    attributeSet?: BaseSpanModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkBaseSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._BaseSpan_construct(peerId, flags)
        const _peer  = new ArkBaseSpanPeer(_peerPtr, peerId, 'BaseSpan', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextBackgroundStyleAttribute(value: TextBackgroundStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextBackgroundStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._BaseSpan_setTextBackgroundStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBaselineOffsetAttribute(value: arkui_Graphics_LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._BaseSpan_setBaselineOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkSpanPeer extends PeerNode {
    attributeSet?: SpanModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Span_construct(peerId, flags)
        const _peer  = new ArkSpanPeer(_peerPtr, peerId, 'Span', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSpanOptionsAttribute(value: string | global_resource_Resource): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as string
            thisSerializer.writeString(valueForIdx0)
        } else if (value instanceof global_resource_Resource) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as global_resource_Resource
            global_resource_Resource_serializer.write(thisSerializer, valueForIdx1)
        }
        ArkUIGeneratedNativeModule._SpanInterface_setSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(value: arkui_component_units_Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            arkui_component_units_Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: double | string | global_resource_Resource | undefined): void {
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
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FontStyle)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: int32 | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FontWeight) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as FontWeight
                thisSerializer.writeInt32(valueTmpValueForIdx1.valueOf())
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDecorationAttribute(value: DecorationStyleInterface | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DecorationStyleInterface_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setDecoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLetterSpacingAttribute(value: double | string | undefined): void {
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
        ArkUIGeneratedNativeModule._SpanAttribute_setLetterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextCaseAttribute(value: TextCase | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as TextCase)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setTextCase(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineHeightAttribute(value: Length | undefined): void {
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
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setLineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ShadowOptions) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ShadowOptions
                ShadowOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Array) {
                if (valueTmpValue.length == 0) {
                    thisSerializer.writeInt8((1).toByte())
                    thisSerializer.writeInt32(0)
                } else {
                    const valueTmpValueElem  = valueTmpValue[0]
                    if (valueTmpValueElem instanceof ShadowOptions) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueForIdx1  = valueTmpValue as Array<ShadowOptions>
                        thisSerializer.writeInt32((valueTmpValueForIdx1.length).toInt())
                        for (let valueTmpValueForIdx1CounterI = 0; valueTmpValueForIdx1CounterI < valueTmpValueForIdx1.length; valueTmpValueForIdx1CounterI++) {
                            const valueTmpValueForIdx1TmpElement : ShadowOptions = valueTmpValueForIdx1[valueTmpValueForIdx1CounterI]
                            ShadowOptions_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement)
                        }
                    }
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setTextShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextBackgroundStyleAttribute(value: TextBackgroundStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextBackgroundStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setTextBackgroundStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBaselineOffsetAttribute(value: arkui_Graphics_LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setBaselineOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setKey(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIdAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setId(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnClick0Attribute(value: ((event: ClickEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setOnClick0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHoverAttribute(value: HoverCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setOnHover(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnClick1Attribute(event: ((event: ClickEvent) => void) | undefined, distanceThreshold: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (event !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const eventTmpValue  = event!
            thisSerializer.holdAndWriteCallback(eventTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (distanceThreshold !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const distanceThresholdTmpValue  = distanceThreshold!
            thisSerializer.writeFloat64(distanceThresholdTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SpanAttribute_setOnClick1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextBackgroundStyle {
    color?: ResourceColor;
    radius?: Dimension | BorderRadiuses;
}
export interface BaseSpan extends CommonMethod {
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        throw new Error('Unimplemented method textBackgroundStyle')
    }
    baselineOffset(value: arkui_Graphics_LengthMetrics | undefined): this {
        throw new Error('Unimplemented method baselineOffset')
    }
    attributeModifier(value: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface SpanAttribute {
    setSpanOptions(value: string | global_resource_Resource): this {
        throw new Error('Unimplemented method setSpanOptions')
    }
    font(value: arkui_component_units_Font | undefined): this {
        throw new Error('Unimplemented method font')
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method fontColor')
    }
    fontSize(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method fontSize')
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error('Unimplemented method fontStyle')
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        throw new Error('Unimplemented method fontWeight')
    }
    fontFamily(value: string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method fontFamily')
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        throw new Error('Unimplemented method decoration')
    }
    letterSpacing(value: double | string | undefined): this {
        throw new Error('Unimplemented method letterSpacing')
    }
    textCase(value: TextCase | undefined): this {
        throw new Error('Unimplemented method textCase')
    }
    lineHeight(value: Length | undefined): this {
        throw new Error('Unimplemented method lineHeight')
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        throw new Error('Unimplemented method textShadow')
    }
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        throw new Error('Unimplemented method textBackgroundStyle')
    }
    baselineOffset(value: arkui_Graphics_LengthMetrics | undefined): this {
        throw new Error('Unimplemented method baselineOffset')
    }
    key(value: string | undefined): this {
        throw new Error('Unimplemented method key')
    }
    id(value: string | undefined): this {
        throw new Error('Unimplemented method id')
    }
    onClick(value: ((event: ClickEvent) => void) | undefined): this {
        throw new Error('Unimplemented method onClick')
    }
    onHover(value: HoverCallback | undefined): this {
        throw new Error('Unimplemented method onHover')
    }
    onClick(event: ((event: ClickEvent) => void) | undefined, distanceThreshold: double | undefined): this {
        throw new Error('Unimplemented method onClick')
    }
    attributeModifier(value: AttributeModifier<SpanAttribute> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkBaseSpanComponent extends ArkCommonMethodComponent implements BaseSpan {
    getPeer(): ArkBaseSpanPeer {
        return (this.peer as ArkBaseSpanPeer)
    }
    public textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        if (this.checkPriority('textBackgroundStyle')) {
            const value_casted = value as (TextBackgroundStyle | undefined)
            this.getPeer()?.setTextBackgroundStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public baselineOffset(value: arkui_Graphics_LengthMetrics | undefined): this {
        if (this.checkPriority('baselineOffset')) {
            const value_casted = value as (arkui_Graphics_LengthMetrics | undefined)
            this.getPeer()?.setBaselineOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookBaseSpanAttributeModifier(this, value);
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
export class ArkSpanComponent extends ComponentBase implements SpanAttribute {
    getPeer(): ArkSpanPeer {
        return (this.peer as ArkSpanPeer)
    }
    public setSpanOptions(value: string | global_resource_Resource): this {
        if (this.checkPriority('setSpanOptions')) {
            const value_casted = value as (string | global_resource_Resource)
            this.getPeer()?.setSpanOptionsAttribute(value_casted)
            this.applyOptionsFinish('SpanAttribute');
            return this
        }
        return this
    }
    public font(value: arkui_component_units_Font | undefined): this {
        if (this.checkPriority('font')) {
            const value_casted = value as (arkui_component_units_Font | undefined)
            this.getPeer()?.setFontAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('fontColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: double | string | global_resource_Resource | undefined): this {
        if (this.checkPriority('fontSize')) {
            const value_casted = value as (double | string | global_resource_Resource | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority('fontStyle')) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (this.checkPriority('fontWeight')) {
            const value_casted = value as (int32 | FontWeight | string | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | global_resource_Resource | undefined): this {
        if (this.checkPriority('fontFamily')) {
            const value_casted = value as (string | global_resource_Resource | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        if (this.checkPriority('decoration')) {
            const value_casted = value as (DecorationStyleInterface | undefined)
            this.getPeer()?.setDecorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: double | string | undefined): this {
        if (this.checkPriority('letterSpacing')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setLetterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public textCase(value: TextCase | undefined): this {
        if (this.checkPriority('textCase')) {
            const value_casted = value as (TextCase | undefined)
            this.getPeer()?.setTextCaseAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: Length | undefined): this {
        if (this.checkPriority('lineHeight')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setLineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (this.checkPriority('textShadow')) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
            this.getPeer()?.setTextShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        if (this.checkPriority('textBackgroundStyle')) {
            const value_casted = value as (TextBackgroundStyle | undefined)
            this.getPeer()?.setTextBackgroundStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public baselineOffset(value: arkui_Graphics_LengthMetrics | undefined): this {
        if (this.checkPriority('baselineOffset')) {
            const value_casted = value as (arkui_Graphics_LengthMetrics | undefined)
            this.getPeer()?.setBaselineOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public key(value: string | undefined): this {
        if (this.checkPriority('key')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setKeyAttribute(value_casted)
            return this
        }
        return this
    }
    public id(value: string | undefined): this {
        if (this.checkPriority('id')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setIdAttribute(value_casted)
            return this
        }
        return this
    }
    public onClick(value: ((event: ClickEvent) => void) | undefined): this {
        if (this.checkPriority('onClick')) {
            const value_casted = value as (((event: ClickEvent) => void) | undefined)
            this.getPeer()?.setOnClick0Attribute(value_casted)
            return this
        }
        return this
    }
    public onHover(value: HoverCallback | undefined): this {
        if (this.checkPriority('onHover')) {
            const value_casted = value as (HoverCallback | undefined)
            this.getPeer()?.setOnHoverAttribute(value_casted)
            return this
        }
        return this
    }
    public onClick(event: ((event: ClickEvent) => void) | undefined, distanceThreshold: double | undefined): this {
        if (this.checkPriority('onClick')) {
            const event_casted = event as (((event: ClickEvent) => void) | undefined)
            const distanceThreshold_casted = distanceThreshold as (double | undefined)
            this.getPeer()?.setOnClick1Attribute(event_casted, distanceThreshold_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SpanAttribute> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookSpanAttributeModifier(this, value);
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
export function SpanImpl(
    @memo @memo_skip
    style: ((attributes: SpanAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkSpanComponent>((): ArkSpanComponent => {
        return new ArkSpanComponent()
    })
    NodeAttach<ArkSpanPeer>((): ArkSpanPeer => ArkSpanPeer.create(receiver), (_: ArkSpanPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class TextBackgroundStyle_serializer {
    public static write(buffer: SerializerBase, value: TextBackgroundStyle): void {
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
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as Dimension
                if (valueHolderForRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx0  = valueHolderForRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx1  = valueHolderForRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForRadiusTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForRadiusTmpValueForIdx0ForIdx2  = valueHolderForRadiusTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextBackgroundStyle {
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
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusTmpBuf : Dimension | BorderRadiuses | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBufOpt : Dimension | BorderRadiuses | undefined
            if (radiusTmpBufOptUnionSelector == (0).toByte()) {
                const radiusTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let radiusTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (radiusTmpBufOptBufUUnionSelector == (0).toByte()) {
                    radiusTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (radiusTmpBufOptBufUUnionSelector == (1).toByte()) {
                    radiusTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (radiusTmpBufOptBufUUnionSelector == (2).toByte()) {
                    radiusTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for radiusTmpBufOptBufU has to be chosen through deserialisation.')
                }
                radiusTmpBufOpt = (radiusTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (radiusTmpBufOptUnionSelector == (1).toByte()) {
                radiusTmpBufOpt = BorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for radiusTmpBufOpt has to be chosen through deserialisation.')
            }
            radiusTmpBuf = (radiusTmpBufOpt as Dimension | BorderRadiuses)
        }
        const radiusTmpResult : Dimension | BorderRadiuses | undefined = radiusTmpBuf
        let value : TextBackgroundStyle = ({color: colorTmpResult, radius: radiusTmpResult} as TextBackgroundStyle)
        return value
    }
}
