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
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AnimationStatus, FillMode, PlayMode } from "./enums"
import { curves } from "./../generated/ohos.curves"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    setStateAttribute(value: AnimationStatus | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as AnimationStatus)
            thisSerializer.writeInt32(TypeChecker.AnimationStatus_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDurationAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCurveAttribute(value: curves.Curve | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as curves.Curve)
            thisSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setCurve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDelayAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setDelay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillModeAttribute(value: FillMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FillMode)
            thisSerializer.writeInt32(TypeChecker.FillMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setFillMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIterationsAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setIterations(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPlayModeAttribute(value: PlayMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as PlayMode)
            thisSerializer.writeInt32(TypeChecker.PlayMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setPlayMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMotionAttribute(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isSpringMotion(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as SpringMotion
                SpringMotion_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isFrictionMotion(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as FrictionMotion
                FrictionMotion_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isScrollMotion(value_value)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as ScrollMotion
                ScrollMotion_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setMotion(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPauseAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRepeatAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCancelAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFrameAttribute(value: ((value: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AnimatorAttribute_setOnFrame(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface AnimatorAttribute extends CommonMethod {
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
    public state(value: AnimationStatus | undefined): this {
        return this
    }
    public duration(value: number | undefined): this {
        return this
    }
    public curve(value: curves.Curve | undefined): this {
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
    public motion(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): this {
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
    public onFrame(value: ((value: number) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: AnimatorAttribute): void {
        super.apply(target)
        if (this.state_value !== undefined)
            target.state(this.state_value!)
        if (this.duration_value !== undefined)
            target.duration(this.duration_value!)
        if (this.curve_value !== undefined)
            target.curve(this.curve_value!)
        if (this.delay_value !== undefined)
            target.delay(this.delay_value!)
        if (this.fillMode_value !== undefined)
            target.fillMode(this.fillMode_value!)
        if (this.iterations_value !== undefined)
            target.iterations(this.iterations_value!)
        if (this.playMode_value !== undefined)
            target.playMode(this.playMode_value!)
        if (this.motion_value !== undefined)
            target.motion(this.motion_value!)
        if (this.onStart_value !== undefined)
            target.onStart(this.onStart_value!)
        if (this.onPause_value !== undefined)
            target.onPause(this.onPause_value!)
        if (this.onRepeat_value !== undefined)
            target.onRepeat(this.onRepeat_value!)
        if (this.onCancel_value !== undefined)
            target.onCancel(this.onCancel_value!)
        if (this.onFinish_value !== undefined)
            target.onFinish(this.onFinish_value!)
        if (this.onFrame_value !== undefined)
            target.onFrame(this.onFrame_value!)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withAnimatorStyle(receiver: AnimatorAttribute, modifier: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkAnimatorStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Animator")
// export function Animator(
//     value: string,
//     @memo
//     content_?: () => void,
// ): AnimatorAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Animator(
    @memo
    style: ((attributes: AnimatorAttribute) => void) | undefined,
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
        withAnimatorStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkAnimatorSet extends ArkCommonMethodSet implements AnimatorAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _state_flag?: boolean
    _state0_value?: AnimationStatus | undefined
    _duration_flag?: boolean
    _duration0_value?: number | undefined
    _curve_flag?: boolean
    _curve0_value?: curves.Curve | undefined
    _delay_flag?: boolean
    _delay0_value?: number | undefined
    _fillMode_flag?: boolean
    _fillMode0_value?: FillMode | undefined
    _iterations_flag?: boolean
    _iterations0_value?: number | undefined
    _playMode_flag?: boolean
    _playMode0_value?: PlayMode | undefined
    _motion_flag?: boolean
    _motion0_value?: SpringMotion | FrictionMotion | ScrollMotion | undefined
    _onStart_flag?: boolean
    _onStart0_value?: (() => void) | undefined
    _onPause_flag?: boolean
    _onPause0_value?: (() => void) | undefined
    _onRepeat_flag?: boolean
    _onRepeat0_value?: (() => void) | undefined
    _onCancel_flag?: boolean
    _onCancel0_value?: (() => void) | undefined
    _onFinish_flag?: boolean
    _onFinish0_value?: (() => void) | undefined
    _onFrame_flag?: boolean
    _onFrame0_value?: ((value: number) => void) | undefined
    applyModifierPatch(component: AnimatorAttribute): void {
        if (this._state_flag)
            component.state((this._state0_value as AnimationStatus | undefined))
        if (this._duration_flag)
            component.duration((this._duration0_value as number | undefined))
        if (this._curve_flag)
            component.curve((this._curve0_value as curves.Curve | undefined))
        if (this._delay_flag)
            component.delay((this._delay0_value as number | undefined))
        if (this._fillMode_flag)
            component.fillMode((this._fillMode0_value as FillMode | undefined))
        if (this._iterations_flag)
            component.iterations((this._iterations0_value as number | undefined))
        if (this._playMode_flag)
            component.playMode((this._playMode0_value as PlayMode | undefined))
        if (this._motion_flag)
            component.motion((this._motion0_value as SpringMotion | FrictionMotion | ScrollMotion | undefined))
        if (this._onStart_flag)
            component.onStart((this._onStart0_value as (() => void) | undefined))
        if (this._onPause_flag)
            component.onPause((this._onPause0_value as (() => void) | undefined))
        if (this._onRepeat_flag)
            component.onRepeat((this._onRepeat0_value as (() => void) | undefined))
        if (this._onCancel_flag)
            component.onCancel((this._onCancel0_value as (() => void) | undefined))
        if (this._onFinish_flag)
            component.onFinish((this._onFinish0_value as (() => void) | undefined))
        if (this._onFrame_flag)
            component.onFrame((this._onFrame0_value as ((value: number) => void) | undefined))
    }
    public state(value: AnimationStatus | undefined): this {
        this._state_flag = true
        this._state0_value = value
        return this
    }
    public duration(value: number | undefined): this {
        this._duration_flag = true
        this._duration0_value = value
        return this
    }
    public curve(value: curves.Curve | undefined): this {
        this._curve_flag = true
        this._curve0_value = value
        return this
    }
    public delay(value: number | undefined): this {
        this._delay_flag = true
        this._delay0_value = value
        return this
    }
    public fillMode(value: FillMode | undefined): this {
        this._fillMode_flag = true
        this._fillMode0_value = value
        return this
    }
    public iterations(value: number | undefined): this {
        this._iterations_flag = true
        this._iterations0_value = value
        return this
    }
    public playMode(value: PlayMode | undefined): this {
        this._playMode_flag = true
        this._playMode0_value = value
        return this
    }
    public motion(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): this {
        this._motion_flag = true
        this._motion0_value = value
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        this._onStart_flag = true
        this._onStart0_value = value
        return this
    }
    public onPause(value: (() => void) | undefined): this {
        this._onPause_flag = true
        this._onPause0_value = value
        return this
    }
    public onRepeat(value: (() => void) | undefined): this {
        this._onRepeat_flag = true
        this._onRepeat0_value = value
        return this
    }
    public onCancel(value: (() => void) | undefined): this {
        this._onCancel_flag = true
        this._onCancel0_value = value
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        this._onFinish_flag = true
        this._onFinish0_value = value
        return this
    }
    public onFrame(value: ((value: number) => void) | undefined): this {
        this._onFrame_flag = true
        this._onFrame0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
