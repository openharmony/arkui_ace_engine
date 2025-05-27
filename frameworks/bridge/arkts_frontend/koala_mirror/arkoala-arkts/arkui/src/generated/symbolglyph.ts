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

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, Finalizable, SerializerBase, registerCallback } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Resource } from "./resource"
import { ResourceColor } from "./units"
import { FontWeight, Color } from "./enums"
import { SymbolEffect, SymbolEffectInternal, EffectScope, EffectDirection } from "./arkui-external"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Deserializer } from "./peers/Deserializer"
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
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeResource(value_value)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphInterface_setSymbolGlyphOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: Array<ResourceColor>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ResourceColor = value[i]
            let value_element_type : int32 = RuntimeType.UNDEFINED
            value_element_type = runtimeType(value_element)
            if (TypeChecker.isColor(value_element)) {
                thisSerializer.writeInt8(0 as int32)
                const value_element_0  = value_element as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_element_0))
            }
            else if (RuntimeType.NUMBER == value_element_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_element_1  = value_element as number
                thisSerializer.writeNumber(value_element_1)
            }
            else if (RuntimeType.STRING == value_element_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_element_2  = value_element as string
                thisSerializer.writeString(value_element_2)
            }
            else if (RuntimeType.OBJECT == value_element_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_element_3  = value_element as Resource
                thisSerializer.writeResource(value_element_3)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_1))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    effectStrategyAttribute(value: SymbolEffectStrategy): void {
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_effectStrategy(this.peer.ptr, TypeChecker.SymbolEffectStrategy_ToNumeric(value))
    }
    renderingStrategyAttribute(value: SymbolRenderingStrategy): void {
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_renderingStrategy(this.peer.ptr, TypeChecker.SymbolRenderingStrategy_ToNumeric(value))
    }
    symbolEffect0Attribute(symbolEffect: SymbolEffect, isActive?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isActive_type : int32 = RuntimeType.UNDEFINED
        isActive_type = runtimeType(isActive)
        thisSerializer.writeInt8(isActive_type as int32)
        if ((RuntimeType.UNDEFINED) != (isActive_type)) {
            const isActive_value  = isActive!
            thisSerializer.writeBoolean(isActive_value)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_symbolEffect0(this.peer.ptr, toPeerPtr(symbolEffect), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    symbolEffect1Attribute(symbolEffect: SymbolEffect, triggerValue?: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let triggerValue_type : int32 = RuntimeType.UNDEFINED
        triggerValue_type = runtimeType(triggerValue)
        thisSerializer.writeInt8(triggerValue_type as int32)
        if ((RuntimeType.UNDEFINED) != (triggerValue_type)) {
            const triggerValue_value  = triggerValue!
            thisSerializer.writeNumber(triggerValue_value)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_symbolEffect1(this.peer.ptr, toPeerPtr(symbolEffect), thisSerializer.asBuffer(), thisSerializer.length())
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
export enum EffectFillStyle {
    CUMULATIVE = 0,
    ITERATIVE = 1
}
export interface SymbolGlyphAttribute extends CommonMethod {
    fontSize(value: number | string | Resource): this
    fontColor(value: Array<ResourceColor>): this
    fontWeight(value: number | FontWeight | string): this
    effectStrategy(value: SymbolEffectStrategy): this
    renderingStrategy(value: SymbolRenderingStrategy): this
    symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean | number): this
    attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UISymbolGlyphAttribute extends UICommonMethod {
    /** @memo */
    fontSize(value: number | string | Resource): this
    /** @memo */
    fontColor(value: Array<ResourceColor>): this
    /** @memo */
    fontWeight(value: number | FontWeight | string): this
    /** @memo */
    effectStrategy(value: SymbolEffectStrategy): this
    /** @memo */
    renderingStrategy(value: SymbolRenderingStrategy): this
    /** @memo */
    symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean | number): this
    /** @memo */
    attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSymbolGlyphStyle extends ArkCommonMethodStyle implements SymbolGlyphAttribute {
    fontSize_value?: number | string | Resource
    fontColor_value?: Array<ResourceColor>
    fontWeight_value?: number | FontWeight | string
    effectStrategy_value?: SymbolEffectStrategy
    renderingStrategy_value?: SymbolRenderingStrategy
    public fontSize(value: number | string | Resource): this {
        return this
    }
    public fontColor(value: Array<ResourceColor>): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string): this {
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy): this {
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy): this {
        return this
    }
    public symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean | number): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkSymbolGlyphComponent extends ArkCommonMethodComponent implements UISymbolGlyphAttribute {
    getPeer(): ArkSymbolGlyphPeer {
        return (this.peer as ArkSymbolGlyphPeer)
    }
    /** @memo */
    public setSymbolGlyphOptions(value?: Resource): this {
        if (this.checkPriority("setSymbolGlyphOptions")) {
            const value_casted = value as (Resource | undefined)
            this.getPeer()?.setSymbolGlyphOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontSize(value: number | string | Resource): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontColor(value: Array<ResourceColor>): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (Array<ResourceColor>)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public effectStrategy(value: SymbolEffectStrategy): this {
        if (this.checkPriority("effectStrategy")) {
            const value_casted = value as (SymbolEffectStrategy)
            this.getPeer()?.effectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderingStrategy(value: SymbolRenderingStrategy): this {
        if (this.checkPriority("renderingStrategy")) {
            const value_casted = value as (SymbolRenderingStrategy)
            this.getPeer()?.renderingStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean | number): this {
        if (this.checkPriority("symbolEffect")) {
            const symbolEffect_type = runtimeType(symbolEffect)
            const isActive_type = runtimeType(isActive)
            if ((RuntimeType.BOOLEAN == isActive_type) || (RuntimeType.UNDEFINED == isActive_type)) {
                const symbolEffect_casted = symbolEffect as (SymbolEffect)
                const isActive_casted = isActive as (boolean | undefined)
                this.getPeer()?.symbolEffect0Attribute(symbolEffect_casted, isActive_casted)
                return this
            }
            if ((RuntimeType.NUMBER == isActive_type) || (RuntimeType.UNDEFINED == isActive_type)) {
                const symbolEffect_casted = symbolEffect as (SymbolEffect)
                const triggerValue_casted = isActive as (number | undefined)
                this.getPeer()?.symbolEffect1Attribute(symbolEffect_casted, triggerValue_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkSymbolGlyph(
    /** @memo */
    style: ((attributes: UISymbolGlyphAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    value?: Resource,
): void {
    const receiver = remember(() => {
        return new ArkSymbolGlyphComponent()
    })
    NodeAttach<ArkSymbolGlyphPeer>((): ArkSymbolGlyphPeer => ArkSymbolGlyphPeer.create(receiver), (_: ArkSymbolGlyphPeer) => {
        receiver.setSymbolGlyphOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
export class HierarchicalSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): HierarchicalSymbolEffect {
        const obj : HierarchicalSymbolEffect = new HierarchicalSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, HierarchicalSymbolEffect.getFinalizer())
        return obj
    }
}
export class HierarchicalSymbolEffect extends SymbolEffect implements MaterializedBase {
    get fillStyle(): EffectFillStyle | undefined {
        return this.getFillStyle()
    }
    set fillStyle(fillStyle: EffectFillStyle | undefined) {
        const fillStyle_NonNull  = (fillStyle as EffectFillStyle)
        this.setFillStyle(fillStyle_NonNull)
    }
    static ctor_hierarchicalsymboleffect(fillStyle?: EffectFillStyle): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let fillStyle_type : int32 = RuntimeType.UNDEFINED
        fillStyle_type = runtimeType(fillStyle)
        thisSerializer.writeInt8(fillStyle_type as int32)
        if ((RuntimeType.UNDEFINED) != (fillStyle_type)) {
            const fillStyle_value  = (fillStyle as EffectFillStyle)
            thisSerializer.writeInt32(TypeChecker.EffectFillStyle_ToNumeric(fillStyle_value))
        }
        const retval  = ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(fillStyle?: EffectFillStyle) {
        super()
        const ctorPtr : KPointer = HierarchicalSymbolEffect.ctor_hierarchicalsymboleffect(fillStyle)
        this.peer = new Finalizable(ctorPtr, HierarchicalSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_getFinalizer()
    }
    private getFillStyle(): EffectFillStyle | undefined {
        return this.getFillStyle_serialize()
    }
    private setFillStyle(fillStyle: EffectFillStyle): void {
        const fillStyle_casted = fillStyle as (EffectFillStyle)
        this.setFillStyle_serialize(fillStyle_casted)
        return
    }
    private getFillStyle_serialize(): EffectFillStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_getFillStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setFillStyle_serialize(fillStyle: EffectFillStyle): void {
        ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_setFillStyle(this.peer!.ptr, TypeChecker.EffectFillStyle_ToNumeric(fillStyle))
    }
}
export class AppearSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): AppearSymbolEffect {
        const obj : AppearSymbolEffect = new AppearSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, AppearSymbolEffect.getFinalizer())
        return obj
    }
}
export class AppearSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    static ctor_appearsymboleffect(scope?: EffectScope): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type as int32)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        const retval  = ArkUIGeneratedNativeModule._AppearSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope) {
        super()
        const ctorPtr : KPointer = AppearSymbolEffect.ctor_appearsymboleffect(scope)
        this.peer = new Finalizable(ctorPtr, AppearSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._AppearSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope | undefined {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope): void {
        const scope_casted = scope as (EffectScope)
        this.setScope_serialize(scope_casted)
        return
    }
    private getScope_serialize(): EffectScope | undefined {
        const retval  = ArkUIGeneratedNativeModule._AppearSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._AppearSymbolEffect_setScope(this.peer!.ptr, TypeChecker.EffectScope_ToNumeric(scope))
    }
}
export class DisappearSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): DisappearSymbolEffect {
        const obj : DisappearSymbolEffect = new DisappearSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, DisappearSymbolEffect.getFinalizer())
        return obj
    }
}
export class DisappearSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    static ctor_disappearsymboleffect(scope?: EffectScope): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type as int32)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        const retval  = ArkUIGeneratedNativeModule._DisappearSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope) {
        super()
        const ctorPtr : KPointer = DisappearSymbolEffect.ctor_disappearsymboleffect(scope)
        this.peer = new Finalizable(ctorPtr, DisappearSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DisappearSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope | undefined {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope): void {
        const scope_casted = scope as (EffectScope)
        this.setScope_serialize(scope_casted)
        return
    }
    private getScope_serialize(): EffectScope | undefined {
        const retval  = ArkUIGeneratedNativeModule._DisappearSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._DisappearSymbolEffect_setScope(this.peer!.ptr, TypeChecker.EffectScope_ToNumeric(scope))
    }
}
export class BounceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): BounceSymbolEffect {
        const obj : BounceSymbolEffect = new BounceSymbolEffect(undefined, undefined)
        obj.peer = new Finalizable(ptr, BounceSymbolEffect.getFinalizer())
        return obj
    }
}
export class BounceSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    get direction(): EffectDirection | undefined {
        return this.getDirection()
    }
    set direction(direction: EffectDirection | undefined) {
        const direction_NonNull  = (direction as EffectDirection)
        this.setDirection(direction_NonNull)
    }
    static ctor_bouncesymboleffect(scope?: EffectScope, direction?: EffectDirection): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type as int32)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8(direction_type as int32)
        if ((RuntimeType.UNDEFINED) != (direction_type)) {
            const direction_value  = (direction as EffectDirection)
            thisSerializer.writeInt32(TypeChecker.EffectDirection_ToNumeric(direction_value))
        }
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope, direction?: EffectDirection) {
        super()
        const ctorPtr : KPointer = BounceSymbolEffect.ctor_bouncesymboleffect(scope, direction)
        this.peer = new Finalizable(ctorPtr, BounceSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BounceSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope | undefined {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope): void {
        const scope_casted = scope as (EffectScope)
        this.setScope_serialize(scope_casted)
        return
    }
    private getDirection(): EffectDirection | undefined {
        return this.getDirection_serialize()
    }
    private setDirection(direction: EffectDirection): void {
        const direction_casted = direction as (EffectDirection)
        this.setDirection_serialize(direction_casted)
        return
    }
    private getScope_serialize(): EffectScope | undefined {
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setScope(this.peer!.ptr, TypeChecker.EffectScope_ToNumeric(scope))
    }
    private getDirection_serialize(): EffectDirection | undefined {
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_getDirection(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDirection_serialize(direction: EffectDirection): void {
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setDirection(this.peer!.ptr, TypeChecker.EffectDirection_ToNumeric(direction))
    }
}
export class PulseSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): PulseSymbolEffect {
        const obj : PulseSymbolEffect = new PulseSymbolEffect()
        obj.peer = new Finalizable(ptr, PulseSymbolEffect.getFinalizer())
        return obj
    }
}
export class PulseSymbolEffect extends SymbolEffect implements MaterializedBase {
    static ctor_pulsesymboleffect(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PulseSymbolEffect_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = PulseSymbolEffect.ctor_pulsesymboleffect()
        this.peer = new Finalizable(ctorPtr, PulseSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PulseSymbolEffect_getFinalizer()
    }
}
