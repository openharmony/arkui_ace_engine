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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource } from "global.resource"
import { ResourceColor } from "./units"
import { FontWeight, Color } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

import { Deserializer } from "./peers/Deserializer"
export enum EffectDirection {
    DOWN = 0,
    UP = 1
}
export enum EffectScope {
    LAYER = 0,
    WHOLE = 1
}
export class SymbolEffectInternal {
    public static fromPtr(ptr: KPointer): SymbolEffect {
        const obj : SymbolEffect = new SymbolEffect()
        obj.peer = new Finalizable(ptr, SymbolEffect.getFinalizer())
        return obj
    }
}
export class SymbolEffect implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_symboleffect(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SymbolEffect_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SymbolEffect.ctor_symboleffect()
        this.peer = new Finalizable(ctorPtr, SymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SymbolEffect_getFinalizer()
    }
    public dummyForAccessorGenerate(): void {
        this.dummyForAccessorGenerate_serialize()
        return
    }
    private dummyForAccessorGenerate_serialize(): void {
        ArkUIGeneratedNativeModule._SymbolEffect_dummyForAccessorGenerate(this.peer!.ptr)
    }
}
export class ScaleSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): ScaleSymbolEffect {
        const obj : ScaleSymbolEffect = new ScaleSymbolEffect(undefined, undefined)
        obj.peer = new Finalizable(ptr, ScaleSymbolEffect.getFinalizer())
        return obj
    }
}
export class ScaleSymbolEffect extends SymbolEffect implements MaterializedBase {
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
    static ctor_scalesymboleffect(scope?: EffectScope, direction?: EffectDirection): KPointer {
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
        const retval  = ArkUIGeneratedNativeModule._ScaleSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope, direction?: EffectDirection) {
        super()
        const ctorPtr : KPointer = ScaleSymbolEffect.ctor_scalesymboleffect(scope, direction)
        this.peer = new Finalizable(ctorPtr, ScaleSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScaleSymbolEffect_getFinalizer()
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
        const retval  = ArkUIGeneratedNativeModule._ScaleSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._ScaleSymbolEffect_setScope(this.peer!.ptr, TypeChecker.EffectScope_ToNumeric(scope))
    }
    private getDirection_serialize(): EffectDirection | undefined {
        const retval  = ArkUIGeneratedNativeModule._ScaleSymbolEffect_getDirection(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDirection_serialize(direction: EffectDirection): void {
        ArkUIGeneratedNativeModule._ScaleSymbolEffect_setDirection(this.peer!.ptr, TypeChecker.EffectDirection_ToNumeric(direction))
    }
}
export class ReplaceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): ReplaceSymbolEffect {
        const obj : ReplaceSymbolEffect = new ReplaceSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, ReplaceSymbolEffect.getFinalizer())
        return obj
    }
}
export class ReplaceSymbolEffect extends SymbolEffect implements MaterializedBase {
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    static ctor_replacesymboleffect(scope?: EffectScope): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type as int32)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(TypeChecker.EffectScope_ToNumeric(scope_value))
        }
        const retval  = ArkUIGeneratedNativeModule._ReplaceSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope) {
        super()
        const ctorPtr : KPointer = ReplaceSymbolEffect.ctor_replacesymboleffect(scope)
        this.peer = new Finalizable(ctorPtr, ReplaceSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ReplaceSymbolEffect_getFinalizer()
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
        const retval  = ArkUIGeneratedNativeModule._ReplaceSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._ReplaceSymbolEffect_setScope(this.peer!.ptr, TypeChecker.EffectScope_ToNumeric(scope))
    }
}
export class ArkSymbolGlyphPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSymbolGlyphPeer {
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
    fontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: Array<ResourceColor> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ResourceColor = value_value[i]
                let value_value_element_type : int32 = RuntimeType.UNDEFINED
                value_value_element_type = runtimeType(value_value_element)
                if (TypeChecker.isColor(value_value_element)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_element_0  = value_value_element as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_element_0))
                }
                else if (RuntimeType.NUMBER == value_value_element_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_element_1  = value_value_element as number
                    thisSerializer.writeNumber(value_value_element_1)
                }
                else if (RuntimeType.STRING == value_value_element_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_element_2  = value_value_element as string
                    thisSerializer.writeString(value_value_element_2)
                }
                else if (RuntimeType.OBJECT == value_value_element_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_element_3  = value_value_element as Resource
                    thisSerializer.writeResource(value_value_element_3)
                }
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    effectStrategyAttribute(value: SymbolEffectStrategy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SymbolEffectStrategy)
            thisSerializer.writeInt32(TypeChecker.SymbolEffectStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_effectStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderingStrategyAttribute(value: SymbolRenderingStrategy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SymbolRenderingStrategy)
            thisSerializer.writeInt32(TypeChecker.SymbolRenderingStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_renderingStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_minFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_maxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    symbolEffect0Attribute(symbolEffect: SymbolEffect | undefined, isActive?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let symbolEffect_type : int32 = RuntimeType.UNDEFINED
        symbolEffect_type = runtimeType(symbolEffect)
        thisSerializer.writeInt8(symbolEffect_type as int32)
        if ((RuntimeType.UNDEFINED) != (symbolEffect_type)) {
            const symbolEffect_value  = symbolEffect!
            thisSerializer.writeSymbolEffect(symbolEffect_value)
        }
        let isActive_type : int32 = RuntimeType.UNDEFINED
        isActive_type = runtimeType(isActive)
        thisSerializer.writeInt8(isActive_type as int32)
        if ((RuntimeType.UNDEFINED) != (isActive_type)) {
            const isActive_value  = isActive!
            thisSerializer.writeBoolean(isActive_value)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_symbolEffect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    symbolEffect1Attribute(symbolEffect: SymbolEffect | undefined, triggerValue?: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let symbolEffect_type : int32 = RuntimeType.UNDEFINED
        symbolEffect_type = runtimeType(symbolEffect)
        thisSerializer.writeInt8(symbolEffect_type as int32)
        if ((RuntimeType.UNDEFINED) != (symbolEffect_type)) {
            const symbolEffect_value  = symbolEffect!
            thisSerializer.writeSymbolEffect(symbolEffect_value)
        }
        let triggerValue_type : int32 = RuntimeType.UNDEFINED
        triggerValue_type = runtimeType(triggerValue)
        thisSerializer.writeInt8(triggerValue_type as int32)
        if ((RuntimeType.UNDEFINED) != (triggerValue_type)) {
            const triggerValue_value  = triggerValue!
            thisSerializer.writeNumber(triggerValue_value)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_symbolEffect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type SymbolGlyphInterface = (value?: Resource) => SymbolGlyphAttribute;
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
    fontSize(value: number | string | Resource | undefined): this
    fontColor(value: Array<ResourceColor> | undefined): this
    fontWeight(value: number | FontWeight | string | undefined): this
    effectStrategy(value: SymbolEffectStrategy | undefined): this
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this
    minFontScale(value: number | Resource | undefined): this
    maxFontScale(value: number | Resource | undefined): this
    symbolEffect(symbolEffect: SymbolEffect | undefined, isActive?: boolean | number): this
}
export class ArkSymbolGlyphStyle extends ArkCommonMethodStyle implements SymbolGlyphAttribute {
    fontSize_value?: number | string | Resource | undefined
    fontColor_value?: Array<ResourceColor> | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    effectStrategy_value?: SymbolEffectStrategy | undefined
    renderingStrategy_value?: SymbolRenderingStrategy | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
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
    public symbolEffect(symbolEffect: SymbolEffect | undefined, isActive?: boolean | number): this {
        return this
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
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (Array<ResourceColor> | undefined)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (this.checkPriority("effectStrategy")) {
            const value_casted = value as (SymbolEffectStrategy | undefined)
            this.getPeer()?.effectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (this.checkPriority("renderingStrategy")) {
            const value_casted = value as (SymbolRenderingStrategy | undefined)
            this.getPeer()?.renderingStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.minFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.maxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public symbolEffect(symbolEffect: SymbolEffect | undefined, isActive?: boolean | number | undefined): this {
        if (this.checkPriority("symbolEffect")) {
            const symbolEffect_type = runtimeType(symbolEffect)
            const isActive_type = runtimeType(isActive)
            if (((RuntimeType.OBJECT == symbolEffect_type) || (RuntimeType.UNDEFINED == symbolEffect_type)) && ((RuntimeType.BOOLEAN == isActive_type) || (RuntimeType.UNDEFINED == isActive_type))) {
                const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
                const isActive_casted = isActive as (boolean | undefined)
                this.getPeer()?.symbolEffect0Attribute(symbolEffect_casted, isActive_casted)
                return this
            }
            if (((RuntimeType.OBJECT == symbolEffect_type) || (RuntimeType.UNDEFINED == symbolEffect_type)) && ((RuntimeType.NUMBER == isActive_type) || (RuntimeType.UNDEFINED == isActive_type))) {
                const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
                const triggerValue_casted = isActive as (number | undefined)
                this.getPeer()?.symbolEffect1Attribute(symbolEffect_casted, triggerValue_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function SymbolGlyph(
    /** @memo */
    style: ((attributes: SymbolGlyphAttribute) => void) | undefined,
    value?: Resource,
    /** @memo */
    content_?: (() => void) | undefined,
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
