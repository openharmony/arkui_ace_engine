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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { AnimationStatus, FillMode, PlayMode } from "./enums"
import { curves } from "./../generated/ohos.curves"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
            thisSerializer.writeInt32(TypeChecker.AnimationStatus_ToNumeric(valueTmpValue))
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
            thisSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(valueTmpValue))
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
            thisSerializer.writeInt32(TypeChecker.FillMode_ToNumeric(valueTmpValue))
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
            thisSerializer.writeInt32(TypeChecker.PlayMode_ToNumeric(valueTmpValue))
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as SpringMotion
                SpringMotion_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FrictionMotion) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as FrictionMotion
                FrictionMotion_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof ScrollMotion) {
                thisSerializer.writeInt8((2).toChar())
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class AnimatorModifier extends CommonMethodModifier implements AnimatorAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _state_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _state_0_0value?: AnimationStatus | undefined
    _duration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _duration_0_0value?: number | undefined
    _curve_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _curve_0_0value?: curves.Curve | undefined
    _delay_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _delay_0_0value?: number | undefined
    _fillMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillMode_0_0value?: FillMode | undefined
    _iterations_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _iterations_0_0value?: number | undefined
    _playMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _playMode_0_0value?: PlayMode | undefined
    _motion_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _motion_0_0value?: SpringMotion | FrictionMotion | ScrollMotion | undefined
    _onStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onStart_0_0value?: (() => void) | undefined
    _onPause_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPause_0_0value?: (() => void) | undefined
    _onRepeat_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRepeat_0_0value?: (() => void) | undefined
    _onCancel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCancel_0_0value?: (() => void) | undefined
    _onFinish_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFinish_0_0value?: (() => void) | undefined
    _onFrame_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFrame_0_0value?: ((value: number) => void) | undefined
    applyModifierPatch(peer: ArkAnimatorPeer): void {
        super.applyModifierPatch(peer)
        if (this._state_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._state_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStateAttribute((this._state_0_0value as AnimationStatus | undefined));
                    this._state_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._state_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._state_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStateAttribute((undefined as AnimationStatus | undefined));
                }
            }
        }
        if (this._duration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._duration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDurationAttribute((this._duration_0_0value as number | undefined));
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._duration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDurationAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._curve_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._curve_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCurveAttribute((this._curve_0_0value as curves.Curve | undefined));
                    this._curve_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._curve_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._curve_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCurveAttribute((undefined as curves.Curve | undefined));
                }
            }
        }
        if (this._delay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._delay_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDelayAttribute((this._delay_0_0value as number | undefined));
                    this._delay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._delay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._delay_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDelayAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._fillMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fillMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFillModeAttribute((this._fillMode_0_0value as FillMode | undefined));
                    this._fillMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fillMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fillMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFillModeAttribute((undefined as FillMode | undefined));
                }
            }
        }
        if (this._iterations_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._iterations_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIterationsAttribute((this._iterations_0_0value as number | undefined));
                    this._iterations_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._iterations_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._iterations_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIterationsAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._playMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._playMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPlayModeAttribute((this._playMode_0_0value as PlayMode | undefined));
                    this._playMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._playMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._playMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPlayModeAttribute((undefined as PlayMode | undefined));
                }
            }
        }
        if (this._motion_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._motion_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMotionAttribute((this._motion_0_0value as SpringMotion | FrictionMotion | ScrollMotion | undefined));
                    this._motion_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._motion_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._motion_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMotionAttribute((undefined as SpringMotion | FrictionMotion | ScrollMotion | undefined));
                }
            }
        }
        if (this._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnStartAttribute((this._onStart_0_0value as (() => void) | undefined));
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onPause_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPause_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPauseAttribute((this._onPause_0_0value as (() => void) | undefined));
                    this._onPause_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPause_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPause_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPauseAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onRepeat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRepeat_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRepeatAttribute((this._onRepeat_0_0value as (() => void) | undefined));
                    this._onRepeat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRepeat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRepeat_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRepeatAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onCancel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCancel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCancelAttribute((this._onCancel_0_0value as (() => void) | undefined));
                    this._onCancel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCancel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCancel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCancelAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onFrame_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFrame_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFrameAttribute((this._onFrame_0_0value as ((value: number) => void) | undefined));
                    this._onFrame_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFrame_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFrame_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFrameAttribute((undefined as ((value: number) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: AnimatorModifier): void {
        super.mergeModifier(modifier)
        if (modifier._state_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._state_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.state(modifier._state_0_0value);
                    break;
                }
                default: {
                    this.state((undefined as AnimationStatus | undefined));
                }
            }
        }
        if (modifier._duration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._duration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.duration(modifier._duration_0_0value);
                    break;
                }
                default: {
                    this.duration((undefined as number | undefined));
                }
            }
        }
        if (modifier._curve_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._curve_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.curve(modifier._curve_0_0value);
                    break;
                }
                default: {
                    this.curve((undefined as curves.Curve | undefined));
                }
            }
        }
        if (modifier._delay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._delay_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.delay(modifier._delay_0_0value);
                    break;
                }
                default: {
                    this.delay((undefined as number | undefined));
                }
            }
        }
        if (modifier._fillMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fillMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fillMode(modifier._fillMode_0_0value);
                    break;
                }
                default: {
                    this.fillMode((undefined as FillMode | undefined));
                }
            }
        }
        if (modifier._iterations_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._iterations_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.iterations(modifier._iterations_0_0value);
                    break;
                }
                default: {
                    this.iterations((undefined as number | undefined));
                }
            }
        }
        if (modifier._playMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._playMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.playMode(modifier._playMode_0_0value);
                    break;
                }
                default: {
                    this.playMode((undefined as PlayMode | undefined));
                }
            }
        }
        if (modifier._motion_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._motion_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.motion(modifier._motion_0_0value);
                    break;
                }
                default: {
                    this.motion((undefined as SpringMotion | FrictionMotion | ScrollMotion | undefined));
                }
            }
        }
        if (modifier._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onPause_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPause_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPause(modifier._onPause_0_0value);
                    break;
                }
                default: {
                    this.onPause((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onRepeat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRepeat_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRepeat(modifier._onRepeat_0_0value);
                    break;
                }
                default: {
                    this.onRepeat((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onCancel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCancel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCancel(modifier._onCancel_0_0value);
                    break;
                }
                default: {
                    this.onCancel((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onFrame_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFrame_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFrame(modifier._onFrame_0_0value);
                    break;
                }
                default: {
                    this.onFrame((undefined as ((value: number) => void) | undefined));
                }
            }
        }
    }
    state(value: AnimationStatus | undefined): this {
        if (((this._state_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._state_0_flag = AttributeUpdaterFlag.UPDATE
            this._state_0_0value = value
        } else
        {
            this._state_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    duration(value: number | undefined): this {
        if (((this._duration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._duration_0_0value) !== (value)))
        {
            this._duration_0_flag = AttributeUpdaterFlag.UPDATE
            this._duration_0_0value = value
        } else
        {
            this._duration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    curve(value: curves.Curve | undefined): this {
        if (((this._curve_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._curve_0_flag = AttributeUpdaterFlag.UPDATE
            this._curve_0_0value = value
        } else
        {
            this._curve_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    delay(value: number | undefined): this {
        if (((this._delay_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._delay_0_0value) !== (value)))
        {
            this._delay_0_flag = AttributeUpdaterFlag.UPDATE
            this._delay_0_0value = value
        } else
        {
            this._delay_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fillMode(value: FillMode | undefined): this {
        if (((this._fillMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fillMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._fillMode_0_0value = value
        } else
        {
            this._fillMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    iterations(value: number | undefined): this {
        if (((this._iterations_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._iterations_0_0value) !== (value)))
        {
            this._iterations_0_flag = AttributeUpdaterFlag.UPDATE
            this._iterations_0_0value = value
        } else
        {
            this._iterations_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    playMode(value: PlayMode | undefined): this {
        if (((this._playMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._playMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._playMode_0_0value = value
        } else
        {
            this._playMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    motion(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): this {
        if (((this._motion_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._motion_0_flag = AttributeUpdaterFlag.UPDATE
            this._motion_0_0value = value
        } else
        {
            this._motion_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onStart(value: (() => void) | undefined): this {
        if (((this._onStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onStart_0_0value = value
        } else
        {
            this._onStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPause(value: (() => void) | undefined): this {
        if (((this._onPause_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPause_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPause_0_0value = value
        } else
        {
            this._onPause_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRepeat(value: (() => void) | undefined): this {
        if (((this._onRepeat_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRepeat_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRepeat_0_0value = value
        } else
        {
            this._onRepeat_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCancel(value: (() => void) | undefined): this {
        if (((this._onCancel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onCancel_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCancel_0_0value = value
        } else
        {
            this._onCancel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
        } else
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFrame(value: ((value: number) => void) | undefined): this {
        if (((this._onFrame_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFrame_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFrame_0_0value = value
        } else
        {
            this._onFrame_0_flag = AttributeUpdaterFlag.SKIP
        }
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
