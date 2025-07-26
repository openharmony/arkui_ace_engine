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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AnimationStatus, FillMode } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource, Resource_serializer } from "./../generated/resource"
import { image, image_PixelMap_serializer } from "./../generated/ohos.multimedia.image"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkImageAnimatorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImageAnimatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ImageAnimator_construct(peerId, flags)
        const _peer  = new ArkImageAnimatorPeer(_peerPtr, peerId, "ImageAnimator", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageAnimatorOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ImageAnimatorInterface_setImageAnimatorOptions(this.peer.ptr)
    }
    setImagesAttribute(value: Array<ImageFrameInfo> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ImageFrameInfo = value_value[value_value_counter_i]
                ImageFrameInfo_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setImages(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setReverseAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setReverse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFixedSizeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setFixedSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setFillMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setIterations(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMonitorInvisibleAreaAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setMonitorInvisibleArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setOnCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    public apply(target: ImageAnimatorAttribute): void {
        super.apply(target)
        if (this.images_value !== undefined)
            target.images(this.images_value!)
        if (this.state_value !== undefined)
            target.state(this.state_value!)
        if (this.duration_value !== undefined)
            target.duration(this.duration_value!)
        if (this.reverse_value !== undefined)
            target.reverse(this.reverse_value!)
        if (this.fixedSize_value !== undefined)
            target.fixedSize(this.fixedSize_value!)
        if (this.fillMode_value !== undefined)
            target.fillMode(this.fillMode_value!)
        if (this.iterations_value !== undefined)
            target.iterations(this.iterations_value!)
        if (this.monitorInvisibleArea_value !== undefined)
            target.monitorInvisibleArea(this.monitorInvisibleArea_value!)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withImageAnimatorStyle(receiver: ImageAnimatorAttribute, modifier: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkImageAnimatorStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("ImageAnimator")
// export function ImageAnimator(
//     
//     @memo
//     content_?: () => void,
// ): ImageAnimatorAttribute {
//     throw new Error("Not implemented")
// }

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
        withImageAnimatorStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkImageAnimatorSet extends ArkCommonMethodSet implements ImageAnimatorAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _images_flag?: boolean
    _images0_value?: Array<ImageFrameInfo> | undefined
    _state_flag?: boolean
    _state0_value?: AnimationStatus | undefined
    _duration_flag?: boolean
    _duration0_value?: number | undefined
    _reverse_flag?: boolean
    _reverse0_value?: boolean | undefined
    _fixedSize_flag?: boolean
    _fixedSize0_value?: boolean | undefined
    _fillMode_flag?: boolean
    _fillMode0_value?: FillMode | undefined
    _iterations_flag?: boolean
    _iterations0_value?: number | undefined
    _monitorInvisibleArea_flag?: boolean
    _monitorInvisibleArea0_value?: boolean | undefined
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
    applyModifierPatch(component: ImageAnimatorAttribute): void {
        if (this._images_flag)
            component.images((this._images0_value as Array<ImageFrameInfo> | undefined))
        if (this._state_flag)
            component.state((this._state0_value as AnimationStatus | undefined))
        if (this._duration_flag)
            component.duration((this._duration0_value as number | undefined))
        if (this._reverse_flag)
            component.reverse((this._reverse0_value as boolean | undefined))
        if (this._fixedSize_flag)
            component.fixedSize((this._fixedSize0_value as boolean | undefined))
        if (this._fillMode_flag)
            component.fillMode((this._fillMode0_value as FillMode | undefined))
        if (this._iterations_flag)
            component.iterations((this._iterations0_value as number | undefined))
        if (this._monitorInvisibleArea_flag)
            component.monitorInvisibleArea((this._monitorInvisibleArea0_value as boolean | undefined))
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
    }
    public images(value: Array<ImageFrameInfo> | undefined): this {
        this._images_flag = true
        this._images0_value = value
        return this
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
    public reverse(value: boolean | undefined): this {
        this._reverse_flag = true
        this._reverse0_value = value
        return this
    }
    public fixedSize(value: boolean | undefined): this {
        this._fixedSize_flag = true
        this._fixedSize0_value = value
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
    public monitorInvisibleArea(value: boolean | undefined): this {
        this._monitorInvisibleArea_flag = true
        this._monitorInvisibleArea0_value = value
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
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ImageFrameInfo_serializer {
    public static write(buffer: SerializerBase, value: ImageFrameInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_src  = value.src
        let value_src_type : int32 = RuntimeType.UNDEFINED
        value_src_type = runtimeType(value_src)
        if (RuntimeType.STRING == value_src_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_src_0  = value_src as string
            valueSerializer.writeString(value_src_0)
        }
        else if (TypeChecker.isResource(value_src, false, false, false, false, false)) {
            valueSerializer.writeInt8((1).toChar())
            const value_src_1  = value_src as Resource
            Resource_serializer.write(valueSerializer, value_src_1)
        }
        else if (TypeChecker.isimage_PixelMap(value_src, false, false)) {
            valueSerializer.writeInt8((2).toChar())
            const value_src_2  = value_src as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, value_src_2)
        }
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_0)
            }
            else if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as string
                valueSerializer.writeString(value_width_value_1)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_0)
            }
            else if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as string
                valueSerializer.writeString(value_height_value_1)
            }
        }
        const value_top  = value.top
        let value_top_type : int32 = RuntimeType.UNDEFINED
        value_top_type = runtimeType(value_top)
        valueSerializer.writeInt8((value_top_type).toChar())
        if ((value_top_type) != (RuntimeType.UNDEFINED)) {
            const value_top_value  = value_top!
            let value_top_value_type : int32 = RuntimeType.UNDEFINED
            value_top_value_type = runtimeType(value_top_value)
            if (RuntimeType.NUMBER == value_top_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_top_value_0  = value_top_value as number
                valueSerializer.writeNumber(value_top_value_0)
            }
            else if (RuntimeType.STRING == value_top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_top_value_1  = value_top_value as string
                valueSerializer.writeString(value_top_value_1)
            }
        }
        const value_left  = value.left
        let value_left_type : int32 = RuntimeType.UNDEFINED
        value_left_type = runtimeType(value_left)
        valueSerializer.writeInt8((value_left_type).toChar())
        if ((value_left_type) != (RuntimeType.UNDEFINED)) {
            const value_left_value  = value_left!
            let value_left_value_type : int32 = RuntimeType.UNDEFINED
            value_left_value_type = runtimeType(value_left_value)
            if (RuntimeType.NUMBER == value_left_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_left_value_0  = value_left_value as number
                valueSerializer.writeNumber(value_left_value_0)
            }
            else if (RuntimeType.STRING == value_left_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_left_value_1  = value_left_value as string
                valueSerializer.writeString(value_left_value_1)
            }
        }
        const value_duration  = value.duration
        let value_duration_type : int32 = RuntimeType.UNDEFINED
        value_duration_type = runtimeType(value_duration)
        valueSerializer.writeInt8((value_duration_type).toChar())
        if ((value_duration_type) != (RuntimeType.UNDEFINED)) {
            const value_duration_value  = value_duration!
            valueSerializer.writeNumber(value_duration_value)
        }
    }
    public static read(buffer: DeserializerBase): ImageFrameInfo {
        let valueDeserializer : DeserializerBase = buffer
        const src_buf_selector : int32 = valueDeserializer.readInt8()
        let src_buf : string | Resource | image.PixelMap | undefined
        if (src_buf_selector == (0).toChar()) {
            src_buf = (valueDeserializer.readString() as string)
        }
        else if (src_buf_selector == (1).toChar()) {
            src_buf = Resource_serializer.read(valueDeserializer)
        }
        else if (src_buf_selector == (2).toChar()) {
            src_buf = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        }
        else {
            throw new Error("One of the branches for src_buf has to be chosen through deserialisation.")
        }
        const src_result : string | Resource | image.PixelMap = (src_buf as string | Resource | image.PixelMap)
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : number | string | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : number | string | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as number | string)
        }
        const width_result : number | string | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : number | string | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : number | string | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as number | string)
        }
        const height_result : number | string | undefined = height_buf
        const top_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let top_buf : number | string | undefined
        if ((top_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const top_buf__selector : int32 = valueDeserializer.readInt8()
            let top_buf_ : number | string | undefined
            if (top_buf__selector == (0).toChar()) {
                top_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (top_buf__selector == (1).toChar()) {
                top_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for top_buf_ has to be chosen through deserialisation.")
            }
            top_buf = (top_buf_ as number | string)
        }
        const top_result : number | string | undefined = top_buf
        const left_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let left_buf : number | string | undefined
        if ((left_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const left_buf__selector : int32 = valueDeserializer.readInt8()
            let left_buf_ : number | string | undefined
            if (left_buf__selector == (0).toChar()) {
                left_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (left_buf__selector == (1).toChar()) {
                left_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for left_buf_ has to be chosen through deserialisation.")
            }
            left_buf = (left_buf_ as number | string)
        }
        const left_result : number | string | undefined = left_buf
        const duration_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let duration_buf : number | undefined
        if ((duration_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            duration_buf = (valueDeserializer.readNumber() as number)
        }
        const duration_result : number | undefined = duration_buf
        let value : ImageFrameInfo = ({src: src_result, width: width_result, height: height_result, top: top_result, left: left_result, duration: duration_result} as ImageFrameInfo)
        return value
    }
}
