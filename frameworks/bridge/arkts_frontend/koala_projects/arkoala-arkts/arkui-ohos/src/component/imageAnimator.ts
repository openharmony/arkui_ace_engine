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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { AnimationStatus, FillMode } from "./enums"
import { Callback_Void } from "./abilityComponent"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource } from "global/resource"
import { PixelMap } from "./arkui-pixelmap"
import { AttributeModifier, UICommonBase } from "./../handwritten"
export class ArkImageAnimatorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkImageAnimatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ImageAnimator_construct(peerId, flags)
        const _peer  = new ArkImageAnimatorPeer(_peerPtr, peerId, "ImageAnimator", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageAnimatorOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ImageAnimatorInterface_setImageAnimatorOptions(this.peer.ptr)
    }
    imagesAttribute(value: Array<ImageFrameInfo> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ImageFrameInfo = value_value[i]
                thisSerializer.writeImageFrameInfo(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_images(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_state(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_duration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    reverseAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_reverse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fixedSizeAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_fixedSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    preDecodeAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_preDecode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_fillMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_iterations(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    monitorInvisibleAreaAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_monitorInvisibleArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type ImageAnimatorInterface = () => ImageAnimatorAttribute;
export interface ImageFrameInfo {
    src: string | Resource | PixelMap;
    width?: number | string;
    height?: number | string;
    top?: number | string;
    left?: number | string;
    duration?: number;
}
export interface ImageAnimatorAttribute extends CommonMethod {
    images(value: Array<ImageFrameInfo> | undefined): this
    state(value: AnimationStatus | undefined): this
    duration(value: number | undefined): this
    reverse(value: boolean | undefined): this
    fixedSize(value: boolean | undefined): this
    preDecode(value: number | undefined): this
    fillMode(value: FillMode | undefined): this
    iterations(value: number | undefined): this
    monitorInvisibleArea(value: boolean | undefined): this
    onStart(value: (() => void) | undefined): this
    onPause(value: (() => void) | undefined): this
    onRepeat(value: (() => void) | undefined): this
    onCancel(value: (() => void) | undefined): this
    onFinish(value: (() => void) | undefined): this
    attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIImageAnimatorAttribute extends UICommonMethod {
    /** @memo */
    images(value: Array<ImageFrameInfo> | undefined): this
    /** @memo */
    state(value: AnimationStatus | undefined): this
    /** @memo */
    duration(value: number | undefined): this
    /** @memo */
    reverse(value: boolean | undefined): this
    /** @memo */
    fixedSize(value: boolean | undefined): this
    /** @memo */
    preDecode(value: number | undefined): this
    /** @memo */
    fillMode(value: FillMode | undefined): this
    /** @memo */
    iterations(value: number | undefined): this
    /** @memo */
    monitorInvisibleArea(value: boolean | undefined): this
    /** @memo */
    onStart(value: (() => void) | undefined): this
    /** @memo */
    onPause(value: (() => void) | undefined): this
    /** @memo */
    onRepeat(value: (() => void) | undefined): this
    /** @memo */
    onCancel(value: (() => void) | undefined): this
    /** @memo */
    onFinish(value: (() => void) | undefined): this
    /** @memo */
    attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkImageAnimatorStyle extends ArkCommonMethodStyle implements ImageAnimatorAttribute {
    images_value?: Array<ImageFrameInfo> | undefined
    state_value?: AnimationStatus | undefined
    duration_value?: number | undefined
    reverse_value?: boolean | undefined
    fixedSize_value?: boolean | undefined
    preDecode_value?: number | undefined
    fillMode_value?: FillMode | undefined
    iterations_value?: number | undefined
    monitorInvisibleArea_value?: boolean | undefined
    onStart_value?: (() => void) | undefined
    onPause_value?: (() => void) | undefined
    onRepeat_value?: (() => void) | undefined
    onCancel_value?: (() => void) | undefined
    onFinish_value?: (() => void) | undefined
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
    public preDecode(value: number | undefined): this {
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
/** @memo:stable */
export class ArkImageAnimatorComponent extends ArkCommonMethodComponent implements UIImageAnimatorAttribute {
    getPeer(): ArkImageAnimatorPeer {
        return (this.peer as ArkImageAnimatorPeer)
    }
    /** @memo */
    public setImageAnimatorOptions(): this {
        if (this.checkPriority("setImageAnimatorOptions")) {
            this.getPeer()?.setImageAnimatorOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public images(value: Array<ImageFrameInfo> | undefined): this {
        if (this.checkPriority("images")) {
            const value_casted = value as (Array<ImageFrameInfo> | undefined)
            this.getPeer()?.imagesAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public state(value: AnimationStatus | undefined): this {
        if (this.checkPriority("state")) {
            const value_casted = value as (AnimationStatus | undefined)
            this.getPeer()?.stateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public duration(value: number | undefined): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.durationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public reverse(value: boolean | undefined): this {
        if (this.checkPriority("reverse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.reverseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fixedSize(value: boolean | undefined): this {
        if (this.checkPriority("fixedSize")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.fixedSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public preDecode(value: number | undefined): this {
        if (this.checkPriority("preDecode")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.preDecodeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fillMode(value: FillMode | undefined): this {
        if (this.checkPriority("fillMode")) {
            const value_casted = value as (FillMode | undefined)
            this.getPeer()?.fillModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public iterations(value: number | undefined): this {
        if (this.checkPriority("iterations")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.iterationsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public monitorInvisibleArea(value: boolean | undefined): this {
        if (this.checkPriority("monitorInvisibleArea")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.monitorInvisibleAreaAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPause(value: (() => void) | undefined): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onPauseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRepeat(value: (() => void) | undefined): this {
        if (this.checkPriority("onRepeat")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCancel(value: (() => void) | undefined): this {
        if (this.checkPriority("onCancel")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onCancelAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFinish(value: (() => void) | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ImageAnimator(
    /** @memo */
    style: ((attributes: UIImageAnimatorAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkImageAnimatorComponent()
    })
    NodeAttach<ArkImageAnimatorPeer>((): ArkImageAnimatorPeer => ArkImageAnimatorPeer.create(receiver), (_: ArkImageAnimatorPeer) => {
        receiver.setImageAnimatorOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
