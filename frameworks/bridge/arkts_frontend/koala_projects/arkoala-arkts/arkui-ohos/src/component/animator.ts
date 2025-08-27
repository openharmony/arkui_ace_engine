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
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AnimationStatus, Curve, FillMode, PlayMode } from "./enums"
import { Callback_Number_Void } from "./alphabetIndexer"
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkAnimatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Animator_construct(peerId, flags)
        const _peer  = new ArkAnimatorPeer(_peerPtr, peerId, "Animator", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setAnimatorOptionsAttribute(value: string): void {
        ArkUIGeneratedNativeModule._AnimatorInterface_setAnimatorOptions(this.peer.ptr, value)
    }
    stateAttribute(value: AnimationStatus | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AnimationStatus)
            thisSerializer.writeInt32(TypeChecker.AnimationStatus_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_state(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    durationAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_duration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    curveAttribute(value: Curve | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Curve)
            thisSerializer.writeInt32(TypeChecker.Curve_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_curve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    delayAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_delay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillModeAttribute(value: FillMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FillMode)
            thisSerializer.writeInt32(TypeChecker.FillMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_fillMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    iterationsAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_iterations(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    playModeAttribute(value: PlayMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as PlayMode)
            thisSerializer.writeInt32(TypeChecker.PlayMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_playMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    motionAttribute(value: SpringMotion | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSpringMotion(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_motion(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPauseAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_onPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRepeatAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_onRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCancelAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_onCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFrameAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_onFrame(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type AnimatorInterface = (value: string) => AnimatorAttribute;
export interface AnimatorAttribute extends CommonMethod {
    state(value: AnimationStatus | undefined): this
    duration(value: number | undefined): this
    curve(value: Curve | undefined): this
    delay(value: number | undefined): this
    fillMode(value: FillMode | undefined): this
    iterations(value: number | undefined): this
    playMode(value: PlayMode | undefined): this
    motion(value: SpringMotion | undefined): this
    onStart(value: (() => void) | undefined): this
    onPause(value: (() => void) | undefined): this
    onRepeat(value: (() => void) | undefined): this
    onCancel(value: (() => void) | undefined): this
    onFinish(value: (() => void) | undefined): this
    onFrame(value: ((index: number) => void) | undefined): this
}
export class ArkAnimatorStyle extends ArkCommonMethodStyle implements AnimatorAttribute {
    state_value?: AnimationStatus | undefined
    duration_value?: number | undefined
    curve_value?: Curve | undefined
    delay_value?: number | undefined
    fillMode_value?: FillMode | undefined
    iterations_value?: number | undefined
    playMode_value?: PlayMode | undefined
    motion_value?: SpringMotion | undefined
    onStart_value?: (() => void) | undefined
    onPause_value?: (() => void) | undefined
    onRepeat_value?: (() => void) | undefined
    onCancel_value?: (() => void) | undefined
    onFinish_value?: (() => void) | undefined
    onFrame_value?: ((index: number) => void) | undefined
    public state(value: AnimationStatus | undefined): this {
        return this
    }
    public duration(value: number | undefined): this {
        return this
    }
    public curve(value: Curve | undefined): this {
        return this
    }
    public delay(value: number | undefined): this {
        return this
    }
    public fillMode(value: FillMode | undefined): this {
        return this
    }
    public iterations(value: number | undefined): this {
        return this
    }
    public playMode(value: PlayMode | undefined): this {
        return this
    }
    public motion(value: SpringMotion | undefined): this {
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        return this
    }
    public onPause(value: (() => void) | undefined): this {
        return this
    }
    public onRepeat(value: (() => void) | undefined): this {
        return this
    }
    public onCancel(value: (() => void) | undefined): this {
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        return this
    }
    public onFrame(value: ((index: number) => void) | undefined): this {
        return this
    }
}
export class ArkAnimatorComponent extends ArkCommonMethodComponent implements AnimatorAttribute {
    getPeer(): ArkAnimatorPeer {
        return (this.peer as ArkAnimatorPeer)
    }
    public setAnimatorOptions(value: string): this {
        if (this.checkPriority("setAnimatorOptions")) {
            const value_casted = value as (string)
            this.getPeer()?.setAnimatorOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public state(value: AnimationStatus | undefined): this {
        if (this.checkPriority("state")) {
            const value_casted = value as (AnimationStatus | undefined)
            this.getPeer()?.stateAttribute(value_casted)
            return this
        }
        return this
    }
    public duration(value: number | undefined): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.durationAttribute(value_casted)
            return this
        }
        return this
    }
    public curve(value: Curve | undefined): this {
        if (this.checkPriority("curve")) {
            const value_casted = value as (Curve | undefined)
            this.getPeer()?.curveAttribute(value_casted)
            return this
        }
        return this
    }
    public delay(value: number | undefined): this {
        if (this.checkPriority("delay")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.delayAttribute(value_casted)
            return this
        }
        return this
    }
    public fillMode(value: FillMode | undefined): this {
        if (this.checkPriority("fillMode")) {
            const value_casted = value as (FillMode | undefined)
            this.getPeer()?.fillModeAttribute(value_casted)
            return this
        }
        return this
    }
    public iterations(value: number | undefined): this {
        if (this.checkPriority("iterations")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.iterationsAttribute(value_casted)
            return this
        }
        return this
    }
    public playMode(value: PlayMode | undefined): this {
        if (this.checkPriority("playMode")) {
            const value_casted = value as (PlayMode | undefined)
            this.getPeer()?.playModeAttribute(value_casted)
            return this
        }
        return this
    }
    public motion(value: SpringMotion | undefined): this {
        if (this.checkPriority("motion")) {
            const value_casted = value as (SpringMotion | undefined)
            this.getPeer()?.motionAttribute(value_casted)
            return this
        }
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onPause(value: (() => void) | undefined): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onPauseAttribute(value_casted)
            return this
        }
        return this
    }
    public onRepeat(value: (() => void) | undefined): this {
        if (this.checkPriority("onRepeat")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    public onCancel(value: (() => void) | undefined): this {
        if (this.checkPriority("onCancel")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onCancelAttribute(value_casted)
            return this
        }
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public onFrame(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onFrame")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onFrameAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Animator(
    /** @memo */
    style: ((attributes: AnimatorAttribute) => void) | undefined,
    value: string,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkAnimatorComponent()
    })
    NodeAttach<ArkAnimatorPeer>((): ArkAnimatorPeer => ArkAnimatorPeer.create(receiver), (_: ArkAnimatorPeer) => {
        receiver.setAnimatorOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
