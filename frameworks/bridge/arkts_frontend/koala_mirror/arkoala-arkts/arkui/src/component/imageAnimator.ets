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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { AnimationStatus, FillMode } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource, Resource_serializer } from "./../generated/resource"
import { image, image_PixelMap_serializer } from "./../generated/ohos.multimedia.image"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkImageAnimatorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImageAnimatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ImageAnimator_construct(peerId, flags)
        const _peer  = new ArkImageAnimatorPeer(_peerPtr, peerId, 'ImageAnimator', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageAnimatorOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ImageAnimatorInterface_setImageAnimatorOptions(this.peer.ptr)
    }
    setImagesAttribute(value: Array<ImageFrameInfo> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ImageFrameInfo = valueTmpValue[valueTmpValueCounterI]
                ImageFrameInfo_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setImages(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setReverseAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setReverse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFixedSizeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setFixedSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setFillMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setIterations(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMonitorInvisibleAreaAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setMonitorInvisibleArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ImageFrameInfo {
    src: string | Resource | image.PixelMap;
    width?: number | string;
    height?: number | string;
    top?: number | string;
    left?: number | string;
    duration?: number;
}
export interface ImageAnimatorAttribute extends CommonMethod {
    images(value: Array<ImageFrameInfo> | undefined): this {
        throw new Error("Unimplemented method images")
    }
    state(value: AnimationStatus | undefined): this {
        throw new Error("Unimplemented method state")
    }
    duration(value: number | undefined): this {
        throw new Error("Unimplemented method duration")
    }
    reverse(value: boolean | undefined): this {
        throw new Error("Unimplemented method reverse")
    }
    fixedSize(value: boolean | undefined): this {
        throw new Error("Unimplemented method fixedSize")
    }
    fillMode(value: FillMode | undefined): this {
        throw new Error("Unimplemented method fillMode")
    }
    iterations(value: number | undefined): this {
        throw new Error("Unimplemented method iterations")
    }
    monitorInvisibleArea(value: boolean | undefined): this {
        throw new Error("Unimplemented method monitorInvisibleArea")
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
    attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkImageAnimatorStyle extends ArkCommonMethodStyle implements ImageAnimatorAttribute {
    images_value?: Array<ImageFrameInfo> | undefined
    state_value?: AnimationStatus | undefined
    duration_value?: number | undefined
    reverse_value?: boolean | undefined
    fixedSize_value?: boolean | undefined
    fillMode_value?: FillMode | undefined
    iterations_value?: number | undefined
    monitorInvisibleArea_value?: boolean | undefined
    onStart_value?: (() => void) | undefined
    onPause_value?: (() => void) | undefined
    onRepeat_value?: (() => void) | undefined
    onCancel_value?: (() => void) | undefined
    onFinish_value?: (() => void) | undefined
    attributeModifier_value?: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined
    public images(value: Array<ImageFrameInfo> | undefined): this {
        return this
    }
    public state(value: AnimationStatus | undefined): this {
        return this
    }
    public duration(value: number | undefined): this {
        return this
    }
    public reverse(value: boolean | undefined): this {
        return this
    }
    public fixedSize(value: boolean | undefined): this {
        return this
    }
    public fillMode(value: FillMode | undefined): this {
        return this
    }
    public iterations(value: number | undefined): this {
        return this
    }
    public monitorInvisibleArea(value: boolean | undefined): this {
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
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkImageAnimatorComponent extends ArkCommonMethodComponent implements ImageAnimatorAttribute {
    getPeer(): ArkImageAnimatorPeer {
        return (this.peer as ArkImageAnimatorPeer)
    }
    public setImageAnimatorOptions(): this {
        if (this.checkPriority("setImageAnimatorOptions")) {
            this.getPeer()?.setImageAnimatorOptionsAttribute()
            return this
        }
        return this
    }
    public images(value: Array<ImageFrameInfo> | undefined): this {
        if (this.checkPriority("images")) {
            const value_casted = value as (Array<ImageFrameInfo> | undefined)
            this.getPeer()?.setImagesAttribute(value_casted)
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
    public reverse(value: boolean | undefined): this {
        if (this.checkPriority("reverse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setReverseAttribute(value_casted)
            return this
        }
        return this
    }
    public fixedSize(value: boolean | undefined): this {
        if (this.checkPriority("fixedSize")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setFixedSizeAttribute(value_casted)
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
    public monitorInvisibleArea(value: boolean | undefined): this {
        if (this.checkPriority("monitorInvisibleArea")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMonitorInvisibleAreaAttribute(value_casted)
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
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function ImageAnimator(
    @memo
    style: ((attributes: ImageAnimatorAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkImageAnimatorComponent>((): ArkImageAnimatorComponent => {
        return new ArkImageAnimatorComponent()
    })
    NodeAttach<ArkImageAnimatorPeer>((): ArkImageAnimatorPeer => ArkImageAnimatorPeer.create(receiver), (_: ArkImageAnimatorPeer): void => {
        receiver.setImageAnimatorOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ImageAnimatorModifier extends CommonMethodModifier implements ImageAnimatorAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _images_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _images_0_0value?: Array<ImageFrameInfo> | undefined
    _state_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _state_0_0value?: AnimationStatus | undefined
    _duration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _duration_0_0value?: number | undefined
    _reverse_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _reverse_0_0value?: boolean | undefined
    _fixedSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fixedSize_0_0value?: boolean | undefined
    _fillMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillMode_0_0value?: FillMode | undefined
    _iterations_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _iterations_0_0value?: number | undefined
    _monitorInvisibleArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _monitorInvisibleArea_0_0value?: boolean | undefined
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
    applyModifierPatch(peer: ArkImageAnimatorPeer): void {
        super.applyModifierPatch(peer)
        if (this._images_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._images_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setImagesAttribute((this._images_0_0value as Array<ImageFrameInfo> | undefined));
                    this._images_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._images_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._images_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setImagesAttribute((undefined as Array<ImageFrameInfo> | undefined));
                }
            }
        }
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
        if (this._reverse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._reverse_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setReverseAttribute((this._reverse_0_0value as boolean | undefined));
                    this._reverse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._reverse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._reverse_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setReverseAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fixedSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fixedSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFixedSizeAttribute((this._fixedSize_0_0value as boolean | undefined));
                    this._fixedSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fixedSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fixedSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFixedSizeAttribute((undefined as boolean | undefined));
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
        if (this._monitorInvisibleArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._monitorInvisibleArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMonitorInvisibleAreaAttribute((this._monitorInvisibleArea_0_0value as boolean | undefined));
                    this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMonitorInvisibleAreaAttribute((undefined as boolean | undefined));
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
    }
    mergeModifier(modifier: ImageAnimatorModifier): void {
        super.mergeModifier(modifier)
        if (modifier._images_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._images_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.images(modifier._images_0_0value);
                    break;
                }
                default: {
                    this.images((undefined as Array<ImageFrameInfo> | undefined));
                }
            }
        }
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
        if (modifier._reverse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._reverse_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.reverse(modifier._reverse_0_0value);
                    break;
                }
                default: {
                    this.reverse((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fixedSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fixedSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fixedSize(modifier._fixedSize_0_0value);
                    break;
                }
                default: {
                    this.fixedSize((undefined as boolean | undefined));
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
        if (modifier._monitorInvisibleArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._monitorInvisibleArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.monitorInvisibleArea(modifier._monitorInvisibleArea_0_0value);
                    break;
                }
                default: {
                    this.monitorInvisibleArea((undefined as boolean | undefined));
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
    }
    images(value: Array<ImageFrameInfo> | undefined): this {
        if (((this._images_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._images_0_flag = AttributeUpdaterFlag.UPDATE
            this._images_0_0value = value
        } else
        {
            this._images_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
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
    reverse(value: boolean | undefined): this {
        if (((this._reverse_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._reverse_0_0value) !== (value)))
        {
            this._reverse_0_flag = AttributeUpdaterFlag.UPDATE
            this._reverse_0_0value = value
        } else
        {
            this._reverse_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fixedSize(value: boolean | undefined): this {
        if (((this._fixedSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fixedSize_0_0value) !== (value)))
        {
            this._fixedSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fixedSize_0_0value = value
        } else
        {
            this._fixedSize_0_flag = AttributeUpdaterFlag.SKIP
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
    monitorInvisibleArea(value: boolean | undefined): this {
        if (((this._monitorInvisibleArea_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._monitorInvisibleArea_0_0value) !== (value)))
        {
            this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.UPDATE
            this._monitorInvisibleArea_0_0value = value
        } else
        {
            this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.SKIP
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
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ImageFrameInfo_serializer {
    public static write(buffer: SerializerBase, value: ImageFrameInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForSrcForIdx0  = valueHolderForSrc as string
            valueSerializer.writeString(valueHolderForSrcForIdx0)
        } else if (valueHolderForSrc instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForSrcForIdx1  = valueHolderForSrc as Resource
            Resource_serializer.write(valueSerializer, valueHolderForSrcForIdx1)
        } else if (valueHolderForSrc instanceof image.PixelMap) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForSrcForIdx2  = valueHolderForSrc as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, valueHolderForSrcForIdx2)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            if (valueHolderForTopTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as number
                valueSerializer.writeNumber(valueHolderForTopTmpValueForIdx0)
            } else if (valueHolderForTopTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForTopTmpValueForIdx1  = valueHolderForTopTmpValue as string
                valueSerializer.writeString(valueHolderForTopTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            if (valueHolderForLeftTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForLeftTmpValueForIdx0  = valueHolderForLeftTmpValue as number
                valueSerializer.writeNumber(valueHolderForLeftTmpValueForIdx0)
            } else if (valueHolderForLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForLeftTmpValueForIdx1  = valueHolderForLeftTmpValue as string
                valueSerializer.writeString(valueHolderForLeftTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDuration  = value.duration
        if (valueHolderForDuration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDurationTmpValue  = valueHolderForDuration!
            valueSerializer.writeNumber(valueHolderForDurationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageFrameInfo {
        let valueDeserializer : DeserializerBase = buffer
        const srcTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let srcTmpBuf : string | Resource | image.PixelMap | undefined
        if (srcTmpBufUnionSelector == (0).toChar()) {
            srcTmpBuf = (valueDeserializer.readString() as string)
        } else if (srcTmpBufUnionSelector == (1).toChar()) {
            srcTmpBuf = Resource_serializer.read(valueDeserializer)
        } else if (srcTmpBufUnionSelector == (2).toChar()) {
            srcTmpBuf = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        } else {
            throw new Error("One of the branches for srcTmpBuf has to be chosen through deserialisation.")
        }
        const srcTmpResult : string | Resource | image.PixelMap = (srcTmpBuf as string | Resource | image.PixelMap)
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : number | string | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : number | string | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as number | string)
        }
        const widthTmpResult : number | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : number | string | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : number | string | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as number | string)
        }
        const heightTmpResult : number | string | undefined = heightTmpBuf
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : number | string | undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBuf_ : number | string | undefined
            if (topTmpBuf_UnionSelector == (0).toChar()) {
                topTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (topTmpBuf_UnionSelector == (1).toChar()) {
                topTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for topTmpBuf_ has to be chosen through deserialisation.")
            }
            topTmpBuf = (topTmpBuf_ as number | string)
        }
        const topTmpResult : number | string | undefined = topTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : number | string | undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBuf_ : number | string | undefined
            if (leftTmpBuf_UnionSelector == (0).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (leftTmpBuf_UnionSelector == (1).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for leftTmpBuf_ has to be chosen through deserialisation.")
            }
            leftTmpBuf = (leftTmpBuf_ as number | string)
        }
        const leftTmpResult : number | string | undefined = leftTmpBuf
        const durationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let durationTmpBuf : number | undefined
        if ((durationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            durationTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const durationTmpResult : number | undefined = durationTmpBuf
        let value : ImageFrameInfo = ({src: srcTmpResult, width: widthTmpResult, height: heightTmpResult, top: topTmpResult, left: leftTmpResult, duration: durationTmpResult} as ImageFrameInfo)
        return value
    }
}
