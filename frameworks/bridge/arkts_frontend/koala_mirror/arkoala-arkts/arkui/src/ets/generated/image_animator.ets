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
import { Callback_Void } from "./ability_component"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Resource } from "./resource"
import { PixelMap } from "./arkui-pixelmap"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
    imagesAttribute(value: Array<ImageFrameInfo>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ImageFrameInfo = value[i]
            thisSerializer.writeImageFrameInfo(value_element)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_images(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stateAttribute(value: AnimationStatus): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_state(this.peer.ptr, TypeChecker.AnimationStatus_ToNumeric(value))
    }
    durationAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_duration(this.peer.ptr, value)
    }
    reverseAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_reverse(this.peer.ptr, value ? 1 : 0)
    }
    fixedSizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_fixedSize(this.peer.ptr, value ? 1 : 0)
    }
    preDecodeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_preDecode(this.peer.ptr, value)
    }
    fillModeAttribute(value: FillMode): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_fillMode(this.peer.ptr, TypeChecker.FillMode_ToNumeric(value))
    }
    iterationsAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_iterations(this.peer.ptr, value)
    }
    onStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPauseAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRepeatAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCancelAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

export interface ImageFrameInfo {
    src: string | Resource | PixelMap;
    width?: number | string;
    height?: number | string;
    top?: number | string;
    left?: number | string;
    duration?: number;
}
export interface ImageAnimatorAttribute extends CommonMethod {
    images(value: Array<ImageFrameInfo>): this
    state(value: AnimationStatus): this
    duration(value: number): this
    reverse(value: boolean): this
    fixedSize(value: boolean): this
    preDecode(value: number): this
    fillMode(value: FillMode): this
    iterations(value: number): this
    onStart(value: (() => void)): this
    onPause(value: (() => void)): this
    onRepeat(value: (() => void)): this
    onCancel(value: (() => void)): this
    onFinish(value: (() => void)): this
    attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIImageAnimatorAttribute extends UICommonMethod {
    @memo
    images(value: Array<ImageFrameInfo>): this
    @memo
    state(value: AnimationStatus): this
    @memo
    duration(value: number): this
    @memo
    reverse(value: boolean): this
    @memo
    fixedSize(value: boolean): this
    @memo
    preDecode(value: number): this
    @memo
    fillMode(value: FillMode): this
    @memo
    iterations(value: number): this
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
    attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkImageAnimatorStyle extends ArkCommonMethodStyle implements ImageAnimatorAttribute {
    images_value?: Array<ImageFrameInfo>
    state_value?: AnimationStatus
    duration_value?: number
    reverse_value?: boolean
    fixedSize_value?: boolean
    preDecode_value?: number
    fillMode_value?: FillMode
    iterations_value?: number
    onStart_value?: (() => void)
    onPause_value?: (() => void)
    onRepeat_value?: (() => void)
    onCancel_value?: (() => void)
    onFinish_value?: (() => void)
    public images(value: Array<ImageFrameInfo>): this {
        return this
    }
    public state(value: AnimationStatus): this {
        return this
    }
    public duration(value: number): this {
        return this
    }
    public reverse(value: boolean): this {
        return this
    }
    public fixedSize(value: boolean): this {
        return this
    }
    public preDecode(value: number): this {
        return this
    }
    public fillMode(value: FillMode): this {
        return this
    }
    public iterations(value: number): this {
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
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkImageAnimatorComponent extends ArkCommonMethodComponent implements UIImageAnimatorAttribute {
    getPeer(): ArkImageAnimatorPeer {
        return (this.peer as ArkImageAnimatorPeer)
    }
    @memo
    public setImageAnimatorOptions(): this {
        if (this.checkPriority("setImageAnimatorOptions")) {
            this.getPeer()?.setImageAnimatorOptionsAttribute()
            return this
        }
        return this
    }
    @memo
    public images(value: Array<ImageFrameInfo>): this {
        if (this.checkPriority("images")) {
            const value_casted = value as (Array<ImageFrameInfo>)
            this.getPeer()?.imagesAttribute(value_casted)
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
    public reverse(value: boolean): this {
        if (this.checkPriority("reverse")) {
            const value_casted = value as (boolean)
            this.getPeer()?.reverseAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fixedSize(value: boolean): this {
        if (this.checkPriority("fixedSize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.fixedSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public preDecode(value: number): this {
        if (this.checkPriority("preDecode")) {
            const value_casted = value as (number)
            this.getPeer()?.preDecodeAttribute(value_casted)
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
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("ImageAnimator")
export function ImageAnimator(
    
    @memo
    content_?: () => void,
): ImageAnimatorAttribute {
    throw new Error("Not implemented")
}

@memo
export function ImageAnimator(
    @memo
    style: ((attributes: UIImageAnimatorAttribute) => void) | undefined,
    
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
