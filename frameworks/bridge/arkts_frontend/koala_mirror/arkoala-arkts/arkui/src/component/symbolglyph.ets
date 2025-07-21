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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor } from "./units"
import { Color, FontWeight } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class SymbolEffectInternal {
    public static fromPtr(ptr: KPointer): SymbolEffect {
        return new SymbolEffect(ptr)
    }
}
export class SymbolEffect implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SymbolEffect.getFinalizer())
    }
    constructor() {
        this(SymbolEffect.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SymbolEffect_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SymbolEffect_getFinalizer()
    }
}
export class ArkSymbolGlyphPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSymbolGlyphPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SymbolGlyph_construct(peerId, flags)
        const _peer  = new ArkSymbolGlyphPeer(_peerPtr, peerId, "SymbolGlyph", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSymbolGlyphOptionsAttribute(value?: Resource): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Resource_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphInterface_setSymbolGlyphOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: Array<ResourceColor> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ResourceColor = value_value[value_value_counter_i]
                let value_value_element_type : int32 = RuntimeType.UNDEFINED
                value_value_element_type = runtimeType(value_value_element)
                if (TypeChecker.isColor(value_value_element)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_element_0  = value_value_element as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_element_0))
                }
                else if (RuntimeType.NUMBER == value_value_element_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_element_1  = value_value_element as number
                    thisSerializer.writeNumber(value_value_element_1)
                }
                else if (RuntimeType.STRING == value_value_element_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_element_2  = value_value_element as string
                    thisSerializer.writeString(value_value_element_2)
                }
                else if (RuntimeType.OBJECT == value_value_element_type) {
                    thisSerializer.writeInt8((3).toChar())
                    const value_value_element_3  = value_value_element as Resource
                    Resource_serializer.write(thisSerializer, value_value_element_3)
                }
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEffectStrategyAttribute(value: SymbolEffectStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SymbolEffectStrategy)
            thisSerializer.writeInt32(TypeChecker.SymbolEffectStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setEffectStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRenderingStrategyAttribute(value: SymbolRenderingStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SymbolRenderingStrategy)
            thisSerializer.writeInt32(TypeChecker.SymbolRenderingStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setRenderingStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSymbolEffectAttribute(symbolEffect: SymbolEffect | undefined, triggerValue?: boolean | number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let symbolEffect_type : int32 = RuntimeType.UNDEFINED
        symbolEffect_type = runtimeType(symbolEffect)
        thisSerializer.writeInt8((symbolEffect_type).toChar())
        if ((symbolEffect_type) != (RuntimeType.UNDEFINED)) {
            const symbolEffect_value  = symbolEffect!
            SymbolEffect_serializer.write(thisSerializer, symbolEffect_value)
        }
        let triggerValue_type : int32 = RuntimeType.UNDEFINED
        triggerValue_type = runtimeType(triggerValue)
        thisSerializer.writeInt8((triggerValue_type).toChar())
        if ((triggerValue_type) != (RuntimeType.UNDEFINED)) {
            const triggerValue_value  = triggerValue!
            let triggerValue_value_type : int32 = RuntimeType.UNDEFINED
            triggerValue_value_type = runtimeType(triggerValue_value)
            if (RuntimeType.BOOLEAN == triggerValue_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const triggerValue_value_0  = triggerValue_value as boolean
                thisSerializer.writeBoolean(triggerValue_value_0)
            }
            else if (RuntimeType.NUMBER == triggerValue_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const triggerValue_value_1  = triggerValue_value as number
                thisSerializer.writeNumber(triggerValue_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setSymbolEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SymbolRenderingStrategy {
    SINGLE = 0,
    MULTIPLE_COLOR = 1,
    MULTIPLE_OPACITY = 2
}
export enum SymbolEffectStrategy {
    NONE = 0,
    SCALE = 1,
    HIERARCHICAL = 2
}
export enum EffectDirection {
    DOWN = 0,
    UP = 1
}
export enum EffectScope {
    LAYER = 0,
    WHOLE = 1
}
export enum EffectFillStyle {
    CUMULATIVE = 0,
    ITERATIVE = 1
}
export interface SymbolGlyphAttribute extends CommonMethod {
    fontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    fontColor(value: Array<ResourceColor> | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        throw new Error("Unimplemented method fontWeight")
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        throw new Error("Unimplemented method effectStrategy")
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        throw new Error("Unimplemented method renderingStrategy")
    }
    minFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method minFontScale")
    }
    maxFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontScale")
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue?: boolean | number): this {
        throw new Error("Unimplemented method symbolEffect")
    }
    attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSymbolGlyphStyle extends ArkCommonMethodStyle implements SymbolGlyphAttribute {
    fontSize_value?: number | string | Resource | undefined
    fontColor_value?: Array<ResourceColor> | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    effectStrategy_value?: SymbolEffectStrategy | undefined
    renderingStrategy_value?: SymbolRenderingStrategy | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    attributeModifier_value?: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined
    public fontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        return this
    }
    public symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue?: boolean | number): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SymbolGlyphAttribute): void {
        super.apply(target)
        if (this.fontSize_value !== undefined)
            target.fontSize(this.fontSize_value!)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.fontWeight_value !== undefined)
            target.fontWeight(this.fontWeight_value!)
        if (this.effectStrategy_value !== undefined)
            target.effectStrategy(this.effectStrategy_value!)
        if (this.renderingStrategy_value !== undefined)
            target.renderingStrategy(this.renderingStrategy_value!)
        if (this.minFontScale_value !== undefined)
            target.minFontScale(this.minFontScale_value!)
        if (this.maxFontScale_value !== undefined)
            target.maxFontScale(this.maxFontScale_value!)
    }
}

export class ArkSymbolGlyphComponent extends ArkCommonMethodComponent implements SymbolGlyphAttribute {
    getPeer(): ArkSymbolGlyphPeer {
        return (this.peer as ArkSymbolGlyphPeer)
    }
    public setSymbolGlyphOptions(value?: Resource): this {
        if (this.checkPriority("setSymbolGlyphOptions")) {
            const value_casted = value as (Resource | undefined)
            this.getPeer()?.setSymbolGlyphOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (Array<ResourceColor> | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (this.checkPriority("effectStrategy")) {
            const value_casted = value as (SymbolEffectStrategy | undefined)
            this.getPeer()?.setEffectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (this.checkPriority("renderingStrategy")) {
            const value_casted = value as (SymbolRenderingStrategy | undefined)
            this.getPeer()?.setRenderingStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue?: boolean | number): this {
        if (this.checkPriority("symbolEffect")) {
            const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
            const triggerValue_casted = triggerValue as (boolean | number | undefined)
            this.getPeer()?.setSymbolEffectAttribute(symbolEffect_casted, triggerValue_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSymbolGlyphStyle(receiver: SymbolGlyphAttribute, modifier: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSymbolGlyphStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("SymbolGlyph")
// export function SymbolGlyph(
//     value?: Resource,
//     @memo
//     content_?: () => void,
// ): SymbolGlyphAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function SymbolGlyph(
    @memo
    style: ((attributes: SymbolGlyphAttribute) => void) | undefined,
    value?: Resource,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSymbolGlyphComponent>((): ArkSymbolGlyphComponent => {
        return new ArkSymbolGlyphComponent()
    })
    NodeAttach<ArkSymbolGlyphPeer>((): ArkSymbolGlyphPeer => ArkSymbolGlyphPeer.create(receiver), (_: ArkSymbolGlyphPeer): void => {
        receiver.setSymbolGlyphOptions(value)
        style?.(receiver)
        withSymbolGlyphStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkSymbolGlyphSet extends ArkCommonMethodSet implements SymbolGlyphAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _fontSize_flag?: boolean
    _fontSize0_value?: number | string | Resource | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: Array<ResourceColor> | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: number | FontWeight | string | undefined
    _effectStrategy_flag?: boolean
    _effectStrategy0_value?: SymbolEffectStrategy | undefined
    _renderingStrategy_flag?: boolean
    _renderingStrategy0_value?: SymbolRenderingStrategy | undefined
    _minFontScale_flag?: boolean
    _minFontScale0_value?: number | Resource | undefined
    _maxFontScale_flag?: boolean
    _maxFontScale0_value?: number | Resource | undefined
    _symbolEffect_flag?: boolean
    _symbolEffect0_value?: SymbolEffect | undefined
    _symbolEffect1_value?: boolean | number | undefined
    applyModifierPatch(component: SymbolGlyphAttribute): void {
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as number | string | Resource | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as Array<ResourceColor> | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as number | FontWeight | string | undefined))
        if (this._effectStrategy_flag)
            component.effectStrategy((this._effectStrategy0_value as SymbolEffectStrategy | undefined))
        if (this._renderingStrategy_flag)
            component.renderingStrategy((this._renderingStrategy0_value as SymbolRenderingStrategy | undefined))
        if (this._minFontScale_flag)
            component.minFontScale((this._minFontScale0_value as number | Resource | undefined))
        if (this._maxFontScale_flag)
            component.maxFontScale((this._maxFontScale0_value as number | Resource | undefined))
        if (this._symbolEffect_flag)
            component.symbolEffect((this._symbolEffect0_value as SymbolEffect | undefined), (this._symbolEffect1_value as boolean | number | undefined))
    }
    public fontSize(value: number | string | Resource | undefined): this {
        this._fontSize_flag = true
        this._fontSize0_value = value
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = value
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        this._effectStrategy_flag = true
        this._effectStrategy0_value = value
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        this._renderingStrategy_flag = true
        this._renderingStrategy0_value = value
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        this._minFontScale_flag = true
        this._minFontScale0_value = value
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        this._maxFontScale_flag = true
        this._maxFontScale0_value = value
        return this
    }
    public symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue?: boolean | number): this {
        this._symbolEffect_flag = true
        this._symbolEffect0_value = symbolEffect
        this._symbolEffect1_value = triggerValue
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SymbolEffect_serializer {
    public static write(buffer: SerializerBase, value: SymbolEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SymbolEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SymbolEffectInternal.fromPtr(ptr)
    }
}
export class AppearSymbolEffect_serializer {
    public static write(buffer: SerializerBase, value: AppearSymbolEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): AppearSymbolEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return AppearSymbolEffectInternal.fromPtr(ptr)
    }
}
export class BounceSymbolEffect_serializer {
    public static write(buffer: SerializerBase, value: BounceSymbolEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BounceSymbolEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return BounceSymbolEffectInternal.fromPtr(ptr)
    }
}
export class DisappearSymbolEffect_serializer {
    public static write(buffer: SerializerBase, value: DisappearSymbolEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DisappearSymbolEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return DisappearSymbolEffectInternal.fromPtr(ptr)
    }
}
export class HierarchicalSymbolEffect_serializer {
    public static write(buffer: SerializerBase, value: HierarchicalSymbolEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): HierarchicalSymbolEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return HierarchicalSymbolEffectInternal.fromPtr(ptr)
    }
}
export class ReplaceSymbolEffect_serializer {
    public static write(buffer: SerializerBase, value: ReplaceSymbolEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ReplaceSymbolEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ReplaceSymbolEffectInternal.fromPtr(ptr)
    }
}
export class ScaleSymbolEffect_serializer {
    public static write(buffer: SerializerBase, value: ScaleSymbolEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ScaleSymbolEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ScaleSymbolEffectInternal.fromPtr(ptr)
    }
}
export class AppearSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): AppearSymbolEffect {
        return new AppearSymbolEffect(false, ptr)
    }
}
export class AppearSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope | undefined)
        this.setScope(scope_NonNull)
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor(scope?: EffectScope) {
        this(false, AppearSymbolEffect.construct(scope))
    }
    static construct(scope?: EffectScope): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        const retval  = ArkUIGeneratedNativeModule._AppearSymbolEffect_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._AppearSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope | undefined {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope | undefined): void {
        const scope_casted = scope as (EffectScope | undefined)
        this.setScope_serialize(scope_casted)
        return
    }
    private getScope_serialize(): EffectScope | undefined {
        const retval  = ArkUIGeneratedNativeModule._AppearSymbolEffect_getScope(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : EffectScope | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.EffectScope_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        ArkUIGeneratedNativeModule._AppearSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class BounceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): BounceSymbolEffect {
        return new BounceSymbolEffect(false, false, ptr)
    }
}
export class BounceSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope | undefined)
        this.setScope(scope_NonNull)
    }
    get direction(): EffectDirection | undefined {
        return this.getDirection()
    }
    set direction(direction: EffectDirection | undefined) {
        const direction_NonNull  = (direction as EffectDirection | undefined)
        this.setDirection(direction_NonNull)
    }
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor(scope?: EffectScope, direction?: EffectDirection) {
        this(false, false, BounceSymbolEffect.construct(scope, direction))
    }
    static construct(scope?: EffectScope, direction?: EffectDirection): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8((direction_type).toChar())
        if ((direction_type) != (RuntimeType.UNDEFINED)) {
            const direction_value  = (direction as EffectDirection)
            thisSerializer.writeInt32(TypeChecker.EffectDirection_ToNumeric(direction_value))
        }
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BounceSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope | undefined {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope | undefined): void {
        const scope_casted = scope as (EffectScope | undefined)
        this.setScope_serialize(scope_casted)
        return
    }
    private getDirection(): EffectDirection | undefined {
        return this.getDirection_serialize()
    }
    private setDirection(direction: EffectDirection | undefined): void {
        const direction_casted = direction as (EffectDirection | undefined)
        this.setDirection_serialize(direction_casted)
        return
    }
    private getScope_serialize(): EffectScope | undefined {
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_getScope(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : EffectScope | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.EffectScope_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getDirection_serialize(): EffectDirection | undefined {
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_getDirection(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : EffectDirection | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.EffectDirection_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : EffectDirection | undefined = buffer
        return returnResult
    }
    private setDirection_serialize(direction: EffectDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8((direction_type).toChar())
        if ((direction_type) != (RuntimeType.UNDEFINED)) {
            const direction_value  = (direction as EffectDirection)
            thisSerializer.writeInt32(TypeChecker.EffectDirection_ToNumeric(direction_value))
        }
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setDirection(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class DisappearSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): DisappearSymbolEffect {
        return new DisappearSymbolEffect(false, ptr)
    }
}
export class DisappearSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope | undefined)
        this.setScope(scope_NonNull)
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor(scope?: EffectScope) {
        this(false, DisappearSymbolEffect.construct(scope))
    }
    static construct(scope?: EffectScope): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        const retval  = ArkUIGeneratedNativeModule._DisappearSymbolEffect_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DisappearSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope | undefined {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope | undefined): void {
        const scope_casted = scope as (EffectScope | undefined)
        this.setScope_serialize(scope_casted)
        return
    }
    private getScope_serialize(): EffectScope | undefined {
        const retval  = ArkUIGeneratedNativeModule._DisappearSymbolEffect_getScope(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : EffectScope | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.EffectScope_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        ArkUIGeneratedNativeModule._DisappearSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class HierarchicalSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): HierarchicalSymbolEffect {
        return new HierarchicalSymbolEffect(false, ptr)
    }
}
export class HierarchicalSymbolEffect extends SymbolEffect implements MaterializedBase {
    get fillStyle(): EffectFillStyle | undefined {
        return this.getFillStyle()
    }
    set fillStyle(fillStyle: EffectFillStyle | undefined) {
        const fillStyle_NonNull  = (fillStyle as EffectFillStyle | undefined)
        this.setFillStyle(fillStyle_NonNull)
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor(fillStyle?: EffectFillStyle) {
        this(false, HierarchicalSymbolEffect.construct(fillStyle))
    }
    static construct(fillStyle?: EffectFillStyle): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let fillStyle_type : int32 = RuntimeType.UNDEFINED
        fillStyle_type = runtimeType(fillStyle)
        thisSerializer.writeInt8((fillStyle_type).toChar())
        if ((fillStyle_type) != (RuntimeType.UNDEFINED)) {
            const fillStyle_value  = (fillStyle as EffectFillStyle)
            thisSerializer.writeInt32(TypeChecker.EffectFillStyle_ToNumeric(fillStyle_value))
        }
        const retval  = ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_getFinalizer()
    }
    private getFillStyle(): EffectFillStyle | undefined {
        return this.getFillStyle_serialize()
    }
    private setFillStyle(fillStyle: EffectFillStyle | undefined): void {
        const fillStyle_casted = fillStyle as (EffectFillStyle | undefined)
        this.setFillStyle_serialize(fillStyle_casted)
        return
    }
    private getFillStyle_serialize(): EffectFillStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_getFillStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : EffectFillStyle | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.EffectFillStyle_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : EffectFillStyle | undefined = buffer
        return returnResult
    }
    private setFillStyle_serialize(fillStyle: EffectFillStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let fillStyle_type : int32 = RuntimeType.UNDEFINED
        fillStyle_type = runtimeType(fillStyle)
        thisSerializer.writeInt8((fillStyle_type).toChar())
        if ((fillStyle_type) != (RuntimeType.UNDEFINED)) {
            const fillStyle_value  = (fillStyle as EffectFillStyle)
            thisSerializer.writeInt32(TypeChecker.EffectFillStyle_ToNumeric(fillStyle_value))
        }
        ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_setFillStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ReplaceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): ReplaceSymbolEffect {
        return new ReplaceSymbolEffect(false, ptr)
    }
}
export class ReplaceSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope | undefined)
        this.setScope(scope_NonNull)
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor(scope?: EffectScope) {
        this(false, ReplaceSymbolEffect.construct(scope))
    }
    static construct(scope?: EffectScope): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        const retval  = ArkUIGeneratedNativeModule._ReplaceSymbolEffect_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ReplaceSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope | undefined {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope | undefined): void {
        const scope_casted = scope as (EffectScope | undefined)
        this.setScope_serialize(scope_casted)
        return
    }
    private getScope_serialize(): EffectScope | undefined {
        const retval  = ArkUIGeneratedNativeModule._ReplaceSymbolEffect_getScope(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : EffectScope | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.EffectScope_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        ArkUIGeneratedNativeModule._ReplaceSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ScaleSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): ScaleSymbolEffect {
        return new ScaleSymbolEffect(false, false, ptr)
    }
}
export class ScaleSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope | undefined)
        this.setScope(scope_NonNull)
    }
    get direction(): EffectDirection | undefined {
        return this.getDirection()
    }
    set direction(direction: EffectDirection | undefined) {
        const direction_NonNull  = (direction as EffectDirection | undefined)
        this.setDirection(direction_NonNull)
    }
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor(scope?: EffectScope, direction?: EffectDirection) {
        this(false, false, ScaleSymbolEffect.construct(scope, direction))
    }
    static construct(scope?: EffectScope, direction?: EffectDirection): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8((direction_type).toChar())
        if ((direction_type) != (RuntimeType.UNDEFINED)) {
            const direction_value  = (direction as EffectDirection)
            thisSerializer.writeInt32(TypeChecker.EffectDirection_ToNumeric(direction_value))
        }
        const retval  = ArkUIGeneratedNativeModule._ScaleSymbolEffect_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScaleSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope | undefined {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope | undefined): void {
        const scope_casted = scope as (EffectScope | undefined)
        this.setScope_serialize(scope_casted)
        return
    }
    private getDirection(): EffectDirection | undefined {
        return this.getDirection_serialize()
    }
    private setDirection(direction: EffectDirection | undefined): void {
        const direction_casted = direction as (EffectDirection | undefined)
        this.setDirection_serialize(direction_casted)
        return
    }
    private getScope_serialize(): EffectScope | undefined {
        const retval  = ArkUIGeneratedNativeModule._ScaleSymbolEffect_getScope(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : EffectScope | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.EffectScope_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8((scope_type).toChar())
        if ((scope_type) != (RuntimeType.UNDEFINED)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        ArkUIGeneratedNativeModule._ScaleSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getDirection_serialize(): EffectDirection | undefined {
        const retval  = ArkUIGeneratedNativeModule._ScaleSymbolEffect_getDirection(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : EffectDirection | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = TypeChecker.EffectDirection_FromNumeric(retvalDeserializer.readInt32())
        }
        const returnResult : EffectDirection | undefined = buffer
        return returnResult
    }
    private setDirection_serialize(direction: EffectDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8((direction_type).toChar())
        if ((direction_type) != (RuntimeType.UNDEFINED)) {
            const direction_value  = (direction as EffectDirection)
            thisSerializer.writeInt32(TypeChecker.EffectDirection_ToNumeric(direction_value))
        }
        ArkUIGeneratedNativeModule._ScaleSymbolEffect_setDirection(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
