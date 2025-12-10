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

import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { global_resource_Resource_serializer } from './../framework/resource'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { Resource as global_resource_Resource } from 'global.resource'
import { ResourceColor, Resource as arkui_component_units_Resource } from './units'
import { Color as arkui_component_enums_Color, FontWeight } from './enums'
import { AttributeModifier, hookSymbolGlyphAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { SymbolGlyphModifier } from './../SymbolGlyphModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class SymbolEffectInternal {
    public static fromPtr(ptr: KPointer): SymbolEffect {
        return new SymbolEffect(MaterializedBaseTag.NOP, ptr)
    }
}
export class SymbolEffect implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SymbolEffect.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, SymbolEffect.construct())
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
    attributeSet?: SymbolGlyphModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSymbolGlyphPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SymbolGlyph_construct(peerId, flags)
        const _peer  = new ArkSymbolGlyphPeer(_peerPtr, peerId, 'SymbolGlyph', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSymbolGlyphOptionsAttribute(value?: global_resource_Resource): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            global_resource_Resource_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphInterface_setSymbolGlyphOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: Array<ResourceColor> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ResourceColor = valueTmpValue[valueTmpValueCounterI]
                if (valueTmpValueTmpElement instanceof arkui_component_enums_Color) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueTmpElementForIdx0  = valueTmpValueTmpElement as arkui_component_enums_Color
                    thisSerializer.writeInt32((valueTmpValueTmpElementForIdx0.getOrdinal()) % (12))
                } else if (valueTmpValueTmpElement instanceof int32) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueTmpElementForIdx1  = valueTmpValueTmpElement as int32
                    thisSerializer.writeInt32(valueTmpValueTmpElementForIdx1)
                } else if (valueTmpValueTmpElement instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueTmpElementForIdx2  = valueTmpValueTmpElement as string
                    thisSerializer.writeString(valueTmpValueTmpElementForIdx2)
                } else if (valueTmpValueTmpElement instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueTmpElementForIdx3  = valueTmpValueTmpElement as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueTmpElementForIdx3)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEffectStrategyAttribute(value: SymbolEffectStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SymbolEffectStrategy)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setEffectStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRenderingStrategyAttribute(value: SymbolRenderingStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SymbolRenderingStrategy)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setRenderingStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSymbolEffect0Attribute(value: SymbolEffect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SymbolEffect_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setSymbolEffect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: double | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: double | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSymbolEffect1Attribute(symbolEffect: SymbolEffect | undefined, isActive: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (symbolEffect !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const symbolEffectTmpValue  = symbolEffect!
            SymbolEffect_serializer.write(thisSerializer, symbolEffectTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (isActive !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const isActiveTmpValue  = isActive!
            thisSerializer.writeBoolean(isActiveTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setSymbolEffect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSymbolEffect2Attribute(symbolEffect: SymbolEffect | undefined, triggerValue: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (symbolEffect !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const symbolEffectTmpValue  = symbolEffect!
            SymbolEffect_serializer.write(thisSerializer, symbolEffectTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (triggerValue !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const triggerValueTmpValue  = triggerValue!
            thisSerializer.writeInt32(triggerValueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolGlyphAttribute_setSymbolEffect2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    setSymbolGlyphOptions(value?: global_resource_Resource): this {
        throw new Error('Unimplemented method setSymbolGlyphOptions')
    }
    fontSize(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method fontSize')
    }
    fontColor(value: Array<ResourceColor> | undefined): this {
        throw new Error('Unimplemented method fontColor')
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        throw new Error('Unimplemented method fontWeight')
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        throw new Error('Unimplemented method effectStrategy')
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        throw new Error('Unimplemented method renderingStrategy')
    }
    symbolEffect(value: SymbolEffect | undefined): this {
        throw new Error('Unimplemented method symbolEffect')
    }
    minFontScale(value: double | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method minFontScale')
    }
    maxFontScale(value: double | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method maxFontScale')
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, isActive: boolean | undefined): this {
        throw new Error('Unimplemented method symbolEffect')
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue: int32 | undefined): this {
        throw new Error('Unimplemented method symbolEffect')
    }
    attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkSymbolGlyphComponent extends ArkCommonMethodComponent implements SymbolGlyphAttribute {
    getPeer(): ArkSymbolGlyphPeer {
        return (this.peer as ArkSymbolGlyphPeer)
    }
    public setSymbolGlyphOptions(value?: global_resource_Resource): this {
        if (this.checkPriority('setSymbolGlyphOptions')) {
            const value_casted = value as (global_resource_Resource | undefined)
            this.getPeer()?.setSymbolGlyphOptionsAttribute(value_casted)
            this.applyOptionsFinish('SymbolGlyphAttribute');
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
    public fontColor(value: Array<ResourceColor> | undefined): this {
        if (this.checkPriority('fontColor')) {
            const value_casted = value as (Array<ResourceColor> | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
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
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (this.checkPriority('effectStrategy')) {
            const value_casted = value as (SymbolEffectStrategy | undefined)
            this.getPeer()?.setEffectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (this.checkPriority('renderingStrategy')) {
            const value_casted = value as (SymbolRenderingStrategy | undefined)
            this.getPeer()?.setRenderingStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public symbolEffect(value: SymbolEffect | undefined): this {
        if (this.checkPriority('symbolEffect')) {
            const value_casted = value as (SymbolEffect | undefined)
            this.getPeer()?.setSymbolEffect0Attribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: double | global_resource_Resource | undefined): this {
        if (this.checkPriority('minFontScale')) {
            const value_casted = value as (double | global_resource_Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: double | global_resource_Resource | undefined): this {
        if (this.checkPriority('maxFontScale')) {
            const value_casted = value as (double | global_resource_Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public symbolEffect(symbolEffect: SymbolEffect | undefined, isActive: boolean | undefined): this {
        if (this.checkPriority('symbolEffect')) {
            const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
            const isActive_casted = isActive as (boolean | undefined)
            this.getPeer()?.setSymbolEffect1Attribute(symbolEffect_casted, isActive_casted)
            return this
        }
        return this
    }
    public symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue: int32 | undefined): this {
        if (this.checkPriority('symbolEffect')) {
            const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
            const triggerValue_casted = triggerValue as (int32 | undefined)
            this.getPeer()?.setSymbolEffect2Attribute(symbolEffect_casted, triggerValue_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookSymbolGlyphAttributeModifier(this, value);
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
export function SymbolGlyphImpl(
    @memo @memo_skip
    style: ((attributes: SymbolGlyphAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkSymbolGlyphComponent>((): ArkSymbolGlyphComponent => {
        return new ArkSymbolGlyphComponent()
    })
    NodeAttach<ArkSymbolGlyphPeer>((): ArkSymbolGlyphPeer => ArkSymbolGlyphPeer.create(receiver), (_: ArkSymbolGlyphPeer): void => {
        style?.(receiver)
        content_?.()
    })
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
export class PulseSymbolEffect_serializer {
    public static write(buffer: SerializerBase, value: PulseSymbolEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PulseSymbolEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PulseSymbolEffectInternal.fromPtr(ptr)
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
export class AppearSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): AppearSymbolEffect {
        return new AppearSymbolEffect(MaterializedBaseTag.NOP, ptr)
    }
}
export class AppearSymbolEffect extends SymbolEffect implements MaterializedBase {
    public scope?: EffectScope | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.scope = this.getScope()
    }
    constructor(scope?: EffectScope) {
        this(MaterializedBaseTag.NOP, AppearSymbolEffect.construct(scope))
        this.scope = this.getScope()
    }
    static construct(scope?: EffectScope): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EffectScope | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EffectScope.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AppearSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class BounceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): BounceSymbolEffect {
        return new BounceSymbolEffect(MaterializedBaseTag.NOP, ptr)
    }
}
export class BounceSymbolEffect extends SymbolEffect implements MaterializedBase {
    public scope?: EffectScope | undefined
    public direction?: EffectDirection | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.scope = this.getScope()
        this.direction = this.getDirection()
    }
    constructor(scope?: EffectScope, direction?: EffectDirection) {
        this(MaterializedBaseTag.NOP, BounceSymbolEffect.construct(scope, direction))
        this.scope = this.getScope()
        this.direction = this.getDirection()
    }
    static construct(scope?: EffectScope, direction?: EffectDirection): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (direction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const directionTmpValue  = (direction as EffectDirection)
            thisSerializer.writeInt32(directionTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EffectScope | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EffectScope.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getDirection_serialize(): EffectDirection | undefined {
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_getDirection(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EffectDirection | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EffectDirection.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : EffectDirection | undefined = buffer
        return returnResult
    }
    private setDirection_serialize(direction: EffectDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (direction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const directionTmpValue  = (direction as EffectDirection)
            thisSerializer.writeInt32(directionTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setDirection(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class DisappearSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): DisappearSymbolEffect {
        return new DisappearSymbolEffect(MaterializedBaseTag.NOP, ptr)
    }
}
export class DisappearSymbolEffect extends SymbolEffect implements MaterializedBase {
    public scope?: EffectScope | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.scope = this.getScope()
    }
    constructor(scope?: EffectScope) {
        this(MaterializedBaseTag.NOP, DisappearSymbolEffect.construct(scope))
        this.scope = this.getScope()
    }
    static construct(scope?: EffectScope): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EffectScope | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EffectScope.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DisappearSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class HierarchicalSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): HierarchicalSymbolEffect {
        return new HierarchicalSymbolEffect(MaterializedBaseTag.NOP, ptr)
    }
}
export class HierarchicalSymbolEffect extends SymbolEffect implements MaterializedBase {
    public fillStyle?: EffectFillStyle | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.fillStyle = this.getFillStyle()
    }
    constructor(fillStyle?: EffectFillStyle) {
        this(MaterializedBaseTag.NOP, HierarchicalSymbolEffect.construct(fillStyle))
        this.fillStyle = this.getFillStyle()
    }
    static construct(fillStyle?: EffectFillStyle): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fillStyle !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fillStyleTmpValue  = (fillStyle as EffectFillStyle)
            thisSerializer.writeInt32(fillStyleTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EffectFillStyle | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EffectFillStyle.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : EffectFillStyle | undefined = buffer
        return returnResult
    }
    private setFillStyle_serialize(fillStyle: EffectFillStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fillStyle !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fillStyleTmpValue  = (fillStyle as EffectFillStyle)
            thisSerializer.writeInt32(fillStyleTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_setFillStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class PulseSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): PulseSymbolEffect {
        return new PulseSymbolEffect(MaterializedBaseTag.NOP, ptr)
    }
}
export class PulseSymbolEffect extends SymbolEffect implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, PulseSymbolEffect.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PulseSymbolEffect_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PulseSymbolEffect_getFinalizer()
    }
}
export class ReplaceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): ReplaceSymbolEffect {
        return new ReplaceSymbolEffect(MaterializedBaseTag.NOP, ptr)
    }
}
export class ReplaceSymbolEffect extends SymbolEffect implements MaterializedBase {
    public scope?: EffectScope | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.scope = this.getScope()
    }
    constructor(scope?: EffectScope) {
        this(MaterializedBaseTag.NOP, ReplaceSymbolEffect.construct(scope))
        this.scope = this.getScope()
    }
    static construct(scope?: EffectScope): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EffectScope | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EffectScope.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ReplaceSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ScaleSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): ScaleSymbolEffect {
        return new ScaleSymbolEffect(MaterializedBaseTag.NOP, ptr)
    }
}
export class ScaleSymbolEffect extends SymbolEffect implements MaterializedBase {
    public scope?: EffectScope | undefined
    public direction?: EffectDirection | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.scope = this.getScope()
        this.direction = this.getDirection()
    }
    constructor(scope?: EffectScope, direction?: EffectDirection) {
        this(MaterializedBaseTag.NOP, ScaleSymbolEffect.construct(scope, direction))
        this.scope = this.getScope()
        this.direction = this.getDirection()
    }
    static construct(scope?: EffectScope, direction?: EffectDirection): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (direction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const directionTmpValue  = (direction as EffectDirection)
            thisSerializer.writeInt32(directionTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EffectScope | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EffectScope.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : EffectScope | undefined = buffer
        return returnResult
    }
    private setScope_serialize(scope: EffectScope | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scope !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scopeTmpValue  = (scope as EffectScope)
            thisSerializer.writeInt32(scopeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScaleSymbolEffect_setScope(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getDirection_serialize(): EffectDirection | undefined {
        const retval  = ArkUIGeneratedNativeModule._ScaleSymbolEffect_getDirection(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EffectDirection | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EffectDirection.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : EffectDirection | undefined = buffer
        return returnResult
    }
    private setDirection_serialize(direction: EffectDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (direction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const directionTmpValue  = (direction as EffectDirection)
            thisSerializer.writeInt32(directionTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScaleSymbolEffect_setDirection(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
