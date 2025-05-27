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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { AnimationStatus, Curve, FillMode, PlayMode } from "./enums"
import { Callback_Void } from "./ability_component"
import { Callback_Number_Void } from "./alphabet_indexer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class SpringPropInternal {
    public static fromPtr(ptr: KPointer): SpringProp {
        const obj : SpringProp = new SpringProp(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, SpringProp.getFinalizer())
        return obj
    }
}
export class SpringProp implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_springprop(mass: number, stiffness: number, damping: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SpringProp_ctor(mass, stiffness, damping)
        return retval
    }
    constructor(mass?: number, stiffness?: number, damping?: number) {
        if (((mass) !== (undefined)) || ((stiffness) !== (undefined)) || ((damping) !== (undefined)))
        {
            const ctorPtr : KPointer = SpringProp.ctor_springprop((mass)!, (stiffness)!, (damping)!)
            this.peer = new Finalizable(ctorPtr, SpringProp.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SpringProp_getFinalizer()
    }
}
export class SpringMotionInternal {
    public static fromPtr(ptr: KPointer): SpringMotion {
        const obj : SpringMotion = new SpringMotion(undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, SpringMotion.getFinalizer())
        return obj
    }
}
export class SpringMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_springmotion(start: number, end: number, velocity: number, prop: SpringProp): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SpringMotion_ctor(start, end, velocity, toPeerPtr(prop))
        return retval
    }
    constructor(start?: number, end?: number, velocity?: number, prop?: SpringProp) {
        if (((start) !== (undefined)) || ((end) !== (undefined)) || ((velocity) !== (undefined)) || ((prop) !== (undefined)))
        {
            const ctorPtr : KPointer = SpringMotion.ctor_springmotion((start)!, (end)!, (velocity)!, (prop)!)
            this.peer = new Finalizable(ctorPtr, SpringMotion.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SpringMotion_getFinalizer()
    }
}
export class FrictionMotionInternal {
    public static fromPtr(ptr: KPointer): FrictionMotion {
        const obj : FrictionMotion = new FrictionMotion(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, FrictionMotion.getFinalizer())
        return obj
    }
}
export class FrictionMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_frictionmotion(friction: number, position: number, velocity: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrictionMotion_ctor(friction, position, velocity)
        return retval
    }
    constructor(friction?: number, position?: number, velocity?: number) {
        if (((friction) !== (undefined)) || ((position) !== (undefined)) || ((velocity) !== (undefined)))
        {
            const ctorPtr : KPointer = FrictionMotion.ctor_frictionmotion((friction)!, (position)!, (velocity)!)
            this.peer = new Finalizable(ctorPtr, FrictionMotion.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FrictionMotion_getFinalizer()
    }
}
export class ScrollMotionInternal {
    public static fromPtr(ptr: KPointer): ScrollMotion {
        const obj : ScrollMotion = new ScrollMotion(undefined, undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ScrollMotion.getFinalizer())
        return obj
    }
}
export class ScrollMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_scrollmotion(position: number, velocity: number, min: number, max: number, prop: SpringProp): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ScrollMotion_ctor(position, velocity, min, max, toPeerPtr(prop))
        return retval
    }
    constructor(position?: number, velocity?: number, min?: number, max?: number, prop?: SpringProp) {
        if (((position) !== (undefined)) || ((velocity) !== (undefined)) || ((min) !== (undefined)) || ((max) !== (undefined)) || ((prop) !== (undefined)))
        {
            const ctorPtr : KPointer = ScrollMotion.ctor_scrollmotion((position)!, (velocity)!, (min)!, (max)!, (prop)!)
            this.peer = new Finalizable(ctorPtr, ScrollMotion.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScrollMotion_getFinalizer()
    }
}
export class ArkAnimatorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkAnimatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Animator_construct(peerId, flags)
        const _peer  = new ArkAnimatorPeer(_peerPtr, peerId, "Animator", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setAnimatorOptionsAttribute(value: string): void {
        ArkUIGeneratedNativeModule._AnimatorInterface_setAnimatorOptions(this.peer.ptr, value)
    }
    stateAttribute(value: AnimationStatus): void {
        ArkUIGeneratedNativeModule._AnimatorAttribute_state(this.peer.ptr, TypeChecker.AnimationStatus_ToNumeric(value))
    }
    durationAttribute(value: number): void {
        ArkUIGeneratedNativeModule._AnimatorAttribute_duration(this.peer.ptr, value)
    }
    curveAttribute(value: Curve): void {
        ArkUIGeneratedNativeModule._AnimatorAttribute_curve(this.peer.ptr, TypeChecker.Curve_ToNumeric(value))
    }
    delayAttribute(value: number): void {
        ArkUIGeneratedNativeModule._AnimatorAttribute_delay(this.peer.ptr, value)
    }
    fillModeAttribute(value: FillMode): void {
        ArkUIGeneratedNativeModule._AnimatorAttribute_fillMode(this.peer.ptr, TypeChecker.FillMode_ToNumeric(value))
    }
    iterationsAttribute(value: number): void {
        ArkUIGeneratedNativeModule._AnimatorAttribute_iterations(this.peer.ptr, value)
    }
    playModeAttribute(value: PlayMode): void {
        ArkUIGeneratedNativeModule._AnimatorAttribute_playMode(this.peer.ptr, TypeChecker.PlayMode_ToNumeric(value))
    }
    motionAttribute(value: SpringMotion): void {
        ArkUIGeneratedNativeModule._AnimatorAttribute_motion(this.peer.ptr, toPeerPtr(value))
    }
    onStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AnimatorAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPauseAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AnimatorAttribute_onPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRepeatAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AnimatorAttribute_onRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCancelAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AnimatorAttribute_onCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AnimatorAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFrameAttribute(value: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AnimatorAttribute_onFrame(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

export interface AnimatorAttribute extends CommonMethod {
    state(value: AnimationStatus): this
    duration(value: number): this
    curve(value: Curve): this
    delay(value: number): this
    fillMode(value: FillMode): this
    iterations(value: number): this
    playMode(value: PlayMode): this
    motion(value: SpringMotion): this
    onStart(value: (() => void)): this
    onPause(value: (() => void)): this
    onRepeat(value: (() => void)): this
    onCancel(value: (() => void)): this
    onFinish(value: (() => void)): this
    onFrame(value: ((index: number) => void)): this
    attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIAnimatorAttribute extends UICommonMethod {
    @memo
    state(value: AnimationStatus): this
    @memo
    duration(value: number): this
    @memo
    curve(value: Curve): this
    @memo
    delay(value: number): this
    @memo
    fillMode(value: FillMode): this
    @memo
    iterations(value: number): this
    @memo
    playMode(value: PlayMode): this
    @memo
    motion(value: SpringMotion): this
    @memo
    onStart(value: (() => void)): this
    @memo
    onPause(value: (() => void)): this
    @memo
    onRepeat(value: (() => void)): this
    @memo
    onCancel(value: (() => void)): this
    @memo
    onFinish(value: (() => void)): this
    @memo
    onFrame(value: ((index: number) => void)): this
    @memo
    attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkAnimatorStyle extends ArkCommonMethodStyle implements AnimatorAttribute {
    state_value?: AnimationStatus
    duration_value?: number
    curve_value?: Curve
    delay_value?: number
    fillMode_value?: FillMode
    iterations_value?: number
    playMode_value?: PlayMode
    motion_value?: SpringMotion
    onStart_value?: (() => void)
    onPause_value?: (() => void)
    onRepeat_value?: (() => void)
    onCancel_value?: (() => void)
    onFinish_value?: (() => void)
    onFrame_value?: ((index: number) => void)
    public state(value: AnimationStatus): this {
        return this
    }
    public duration(value: number): this {
        return this
    }
    public curve(value: Curve): this {
        return this
    }
    public delay(value: number): this {
        return this
    }
    public fillMode(value: FillMode): this {
        return this
    }
    public iterations(value: number): this {
        return this
    }
    public playMode(value: PlayMode): this {
        return this
    }
    public motion(value: SpringMotion): this {
        return this
    }
    public onStart(value: (() => void)): this {
        return this
    }
    public onPause(value: (() => void)): this {
        return this
    }
    public onRepeat(value: (() => void)): this {
        return this
    }
    public onCancel(value: (() => void)): this {
        return this
    }
    public onFinish(value: (() => void)): this {
        return this
    }
    public onFrame(value: ((index: number) => void)): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkAnimatorComponent extends ArkCommonMethodComponent implements UIAnimatorAttribute {
    getPeer(): ArkAnimatorPeer {
        return (this.peer as ArkAnimatorPeer)
    }
    @memo
    public setAnimatorOptions(value: string): this {
        if (this.checkPriority("setAnimatorOptions")) {
            const value_casted = value as (string)
            this.getPeer()?.setAnimatorOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public state(value: AnimationStatus): this {
        if (this.checkPriority("state")) {
            const value_casted = value as (AnimationStatus)
            this.getPeer()?.stateAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public duration(value: number): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (number)
            this.getPeer()?.durationAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public curve(value: Curve): this {
        if (this.checkPriority("curve")) {
            const value_casted = value as (Curve)
            this.getPeer()?.curveAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public delay(value: number): this {
        if (this.checkPriority("delay")) {
            const value_casted = value as (number)
            this.getPeer()?.delayAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fillMode(value: FillMode): this {
        if (this.checkPriority("fillMode")) {
            const value_casted = value as (FillMode)
            this.getPeer()?.fillModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public iterations(value: number): this {
        if (this.checkPriority("iterations")) {
            const value_casted = value as (number)
            this.getPeer()?.iterationsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public playMode(value: PlayMode): this {
        if (this.checkPriority("playMode")) {
            const value_casted = value as (PlayMode)
            this.getPeer()?.playModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public motion(value: SpringMotion): this {
        if (this.checkPriority("motion")) {
            const value_casted = value as (SpringMotion)
            this.getPeer()?.motionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onStart(value: (() => void)): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onPause(value: (() => void)): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onPauseAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onRepeat(value: (() => void)): this {
        if (this.checkPriority("onRepeat")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onCancel(value: (() => void)): this {
        if (this.checkPriority("onCancel")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onCancelAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFinish(value: (() => void)): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFrame(value: ((index: number) => void)): this {
        if (this.checkPriority("onFrame")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onFrameAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Animator")
export function Animator(
    value: string,
    @memo
    content_?: () => void,
): AnimatorAttribute {
    throw new Error("Not implemented")
}

@memo
export function Animator(
    @memo
    style: ((attributes: UIAnimatorAttribute) => void) | undefined,
    value: string,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkAnimatorComponent>((): ArkAnimatorComponent => {
        return new ArkAnimatorComponent()
    })
    NodeAttach<ArkAnimatorPeer>((): ArkAnimatorPeer => ArkAnimatorPeer.create(receiver), (_: ArkAnimatorPeer): void => {
        receiver.setAnimatorOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
