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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AnimationStatus, FillMode, PlayMode } from "./enums"
import { default as curves } from "@ohos.curves"
import { AttributeModifier, hookAnimatorAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { AnimatorModifier } from "./../AnimatorModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class FrictionMotionInternal {
    public static fromPtr(ptr: KPointer): FrictionMotion {
        return new FrictionMotion(false, false, false, ptr)
    }
}
export class FrictionMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, _1: boolean, _2: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, FrictionMotion.getFinalizer())
    }
    constructor(friction: number, position: number, velocity: number) {
        this(false, false, false, FrictionMotion.construct(friction, position, velocity))
    }
    static construct(friction: number, position: number, velocity: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrictionMotion_construct(friction, position, velocity)
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FrictionMotion_getFinalizer()
    }
}
export class ScrollMotionInternal {
    public static fromPtr(ptr: KPointer): ScrollMotion {
        return new ScrollMotion(false, false, false, false, false, ptr)
    }
}
export class ScrollMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, _1: boolean, _2: boolean, _3: boolean, _4: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ScrollMotion.getFinalizer())
    }
    constructor(position: number, velocity: number, min: number, max: number, prop: SpringProp) {
        this(false, false, false, false, false, ScrollMotion.construct(position, velocity, min, max, prop))
    }
    static construct(position: number, velocity: number, min: number, max: number, prop: SpringProp): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ScrollMotion_construct(position, velocity, min, max, toPeerPtr(prop))
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScrollMotion_getFinalizer()
    }
}
export class SpringMotionInternal {
    public static fromPtr(ptr: KPointer): SpringMotion {
        return new SpringMotion(false, false, false, false, ptr)
    }
}
export class SpringMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, _1: boolean, _2: boolean, _3: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SpringMotion.getFinalizer())
    }
    constructor(start: number, end: number, velocity: number, prop: SpringProp) {
        this(false, false, false, false, SpringMotion.construct(start, end, velocity, prop))
    }
    static construct(start: number, end: number, velocity: number, prop: SpringProp): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SpringMotion_construct(start, end, velocity, toPeerPtr(prop))
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SpringMotion_getFinalizer()
    }
}
export class SpringPropInternal {
    public static fromPtr(ptr: KPointer): SpringProp {
        return new SpringProp(false, false, false, ptr)
    }
}
export class SpringProp implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, _1: boolean, _2: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SpringProp.getFinalizer())
    }
    constructor(mass: number, stiffness: number, damping: number) {
        this(false, false, false, SpringProp.construct(mass, stiffness, damping))
    }
    static construct(mass: number, stiffness: number, damping: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SpringProp_construct(mass, stiffness, damping)
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SpringProp_getFinalizer()
    }
}
export class ArkAnimatorPeer extends ArkCommonMethodPeer {
    attributeSet?: AnimatorModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkAnimatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Animator_construct(peerId, flags)
        const _peer  = new ArkAnimatorPeer(_peerPtr, peerId, 'Animator', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setAnimatorOptionsAttribute(value: string): void {
        ArkUIGeneratedNativeModule._AnimatorInterface_setAnimatorOptions(this.peer.ptr, value)
    }
    setStateAttribute(value: AnimationStatus | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as AnimationStatus)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDurationAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCurveAttribute(value: curves.Curve | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as curves.Curve)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setCurve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDelayAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setDelay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillModeAttribute(value: FillMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FillMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setFillMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIterationsAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setIterations(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPlayModeAttribute(value: PlayMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as PlayMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setPlayMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMotionAttribute(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof SpringMotion) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as SpringMotion
                SpringMotion_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FrictionMotion) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as FrictionMotion
                FrictionMotion_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof ScrollMotion) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as ScrollMotion
                ScrollMotion_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setMotion(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPauseAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRepeatAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCancelAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFrameAttribute(value: ((value: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnFrame(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface AnimatorAttribute extends CommonMethod {
    setAnimatorOptions(value: string): this {
        throw new Error("Unimplemented method setAnimatorOptions")
    }
    state(value: AnimationStatus | undefined): this {
        throw new Error("Unimplemented method state")
    }
    duration(value: number | undefined): this {
        throw new Error("Unimplemented method duration")
    }
    curve(value: curves.Curve | undefined): this {
        throw new Error("Unimplemented method curve")
    }
    delay(value: number | undefined): this {
        throw new Error("Unimplemented method delay")
    }
    fillMode(value: FillMode | undefined): this {
        throw new Error("Unimplemented method fillMode")
    }
    iterations(value: number | undefined): this {
        throw new Error("Unimplemented method iterations")
    }
    playMode(value: PlayMode | undefined): this {
        throw new Error("Unimplemented method playMode")
    }
    motion(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): this {
        throw new Error("Unimplemented method motion")
    }
    onStart(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onStart")
    }
    onPause(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onPause")
    }
    onRepeat(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onRepeat")
    }
    onCancel(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onCancel")
    }
    onFinish(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onFinish")
    }
    onFrame(value: ((value: number) => void) | undefined): this {
        throw new Error("Unimplemented method onFrame")
    }
    attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkAnimatorStyle extends ArkCommonMethodStyle implements AnimatorAttribute {
    state_value?: AnimationStatus | undefined
    duration_value?: number | undefined
    curve_value?: curves.Curve | undefined
    delay_value?: number | undefined
    fillMode_value?: FillMode | undefined
    iterations_value?: number | undefined
    playMode_value?: PlayMode | undefined
    motion_value?: SpringMotion | FrictionMotion | ScrollMotion | undefined
    onStart_value?: (() => void) | undefined
    onPause_value?: (() => void) | undefined
    onRepeat_value?: (() => void) | undefined
    onCancel_value?: (() => void) | undefined
    onFinish_value?: (() => void) | undefined
    onFrame_value?: ((value: number) => void) | undefined
    attributeModifier_value?: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined
    setAnimatorOptions(value: string): this {
        return this
    }
    state(value: AnimationStatus | undefined): this {
        return this
    }
    duration(value: number | undefined): this {
        return this
    }
    curve(value: curves.Curve | undefined): this {
        return this
    }
    delay(value: number | undefined): this {
        return this
    }
    fillMode(value: FillMode | undefined): this {
        return this
    }
    iterations(value: number | undefined): this {
        return this
    }
    playMode(value: PlayMode | undefined): this {
        return this
    }
    motion(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): this {
        return this
    }
    onStart(value: (() => void) | undefined): this {
        return this
    }
    onPause(value: (() => void) | undefined): this {
        return this
    }
    onRepeat(value: (() => void) | undefined): this {
        return this
    }
    onCancel(value: (() => void) | undefined): this {
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        return this
    }
    onFrame(value: ((value: number) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkAnimatorComponent extends ArkCommonMethodComponent implements AnimatorAttribute {
    getPeer(): ArkAnimatorPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkAnimatorPeer)
    }
    public setAnimatorOptions(value: string): this {
        if (this.checkPriority("setAnimatorOptions")) {
            const value_casted = value as (string)
            this.getPeer()?.setAnimatorOptionsAttribute(value_casted)
            this.applyOptionsFinish('AnimatorAttribute');
            return this
        }
        return this
    }
    public state(value: AnimationStatus | undefined): this {
        if (this.checkPriority("state")) {
            const value_casted = value as (AnimationStatus | undefined)
            this.getPeer()?.setStateAttribute(value_casted)
            return this
        }
        return this
    }
    public duration(value: number | undefined): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setDurationAttribute(value_casted)
            return this
        }
        return this
    }
    public curve(value: curves.Curve | undefined): this {
        if (this.checkPriority("curve")) {
            const value_casted = value as (curves.Curve | undefined)
            this.getPeer()?.setCurveAttribute(value_casted)
            return this
        }
        return this
    }
    public delay(value: number | undefined): this {
        if (this.checkPriority("delay")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setDelayAttribute(value_casted)
            return this
        }
        return this
    }
    public fillMode(value: FillMode | undefined): this {
        if (this.checkPriority("fillMode")) {
            const value_casted = value as (FillMode | undefined)
            this.getPeer()?.setFillModeAttribute(value_casted)
            return this
        }
        return this
    }
    public iterations(value: number | undefined): this {
        if (this.checkPriority("iterations")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setIterationsAttribute(value_casted)
            return this
        }
        return this
    }
    public playMode(value: PlayMode | undefined): this {
        if (this.checkPriority("playMode")) {
            const value_casted = value as (PlayMode | undefined)
            this.getPeer()?.setPlayModeAttribute(value_casted)
            return this
        }
        return this
    }
    public motion(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): this {
        if (this.checkPriority("motion")) {
            const value_casted = value as (SpringMotion | FrictionMotion | ScrollMotion | undefined)
            this.getPeer()?.setMotionAttribute(value_casted)
            return this
        }
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onPause(value: (() => void) | undefined): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnPauseAttribute(value_casted)
            return this
        }
        return this
    }
    public onRepeat(value: (() => void) | undefined): this {
        if (this.checkPriority("onRepeat")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    public onCancel(value: (() => void) | undefined): this {
        if (this.checkPriority("onCancel")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnCancelAttribute(value_casted)
            return this
        }
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public onFrame(value: ((value: number) => void) | undefined): this {
        if (this.checkPriority("onFrame")) {
            const value_casted = value as (((value: number) => void) | undefined)
            this.getPeer()?.setOnFrameAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookAnimatorAttributeModifier(this, value);
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
export function AnimatorImpl(
    @memo
    style: ((attributes: AnimatorAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkAnimatorComponent>((): ArkAnimatorComponent => {
        return new ArkAnimatorComponent()
    })
    NodeAttach<ArkAnimatorPeer>((): ArkAnimatorPeer => ArkAnimatorPeer.create(receiver), (peer: ArkAnimatorPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class FrictionMotion_serializer {
    public static write(buffer: SerializerBase, value: FrictionMotion): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): FrictionMotion {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return FrictionMotionInternal.fromPtr(ptr)
    }
}
export class ScrollMotion_serializer {
    public static write(buffer: SerializerBase, value: ScrollMotion): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ScrollMotion {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ScrollMotionInternal.fromPtr(ptr)
    }
}
export class SpringMotion_serializer {
    public static write(buffer: SerializerBase, value: SpringMotion): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SpringMotion {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SpringMotionInternal.fromPtr(ptr)
    }
}
export class SpringProp_serializer {
    public static write(buffer: SerializerBase, value: SpringProp): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SpringProp {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SpringPropInternal.fromPtr(ptr)
    }
}
