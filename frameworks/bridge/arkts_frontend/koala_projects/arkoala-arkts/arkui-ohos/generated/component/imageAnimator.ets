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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AnimationStatus, FillMode } from "./enums"
import { AttributeModifier, extractors, hookImageAnimatorAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Resource } from "global.resource"
import { default as image } from "@ohos.multimedia.image"
import { ImageAnimatorModifier } from "./../ImageAnimatorModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
import { ModifierStateManager } from '../CommonModifier';
export class ArkImageAnimatorPeer extends ArkCommonMethodPeer {
    attributeSet?: ImageAnimatorModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDurationAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_setFillMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIterationsAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
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
    width?: double | string;
    height?: double | string;
    top?: double | string;
    left?: double | string;
    duration?: int32;
}
export interface ImageAnimatorAttribute extends CommonMethod {
    setImageAnimatorOptions(): this {
        throw new Error("Unimplemented method setImageAnimatorOptions")
    }
    images(value: Array<ImageFrameInfo> | undefined): this {
        throw new Error("Unimplemented method images")
    }
    state(value: AnimationStatus | undefined): this {
        throw new Error("Unimplemented method state")
    }
    duration(value: int32 | undefined): this {
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
    iterations(value: int32 | undefined): this {
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
    duration_value?: int32 | undefined
    reverse_value?: boolean | undefined
    fixedSize_value?: boolean | undefined
    fillMode_value?: FillMode | undefined
    iterations_value?: int32 | undefined
    monitorInvisibleArea_value?: boolean | undefined
    onStart_value?: (() => void) | undefined
    onPause_value?: (() => void) | undefined
    onRepeat_value?: (() => void) | undefined
    onCancel_value?: (() => void) | undefined
    onFinish_value?: (() => void) | undefined
    attributeModifier_value?: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined
    setImageAnimatorOptions(): this {
        return this
    }
    images(value: Array<ImageFrameInfo> | undefined): this {
        return this
    }
    state(value: AnimationStatus | undefined): this {
        return this
    }
    duration(value: int32 | undefined): this {
        return this
    }
    reverse(value: boolean | undefined): this {
        return this
    }
    fixedSize(value: boolean | undefined): this {
        return this
    }
    fillMode(value: FillMode | undefined): this {
        return this
    }
    iterations(value: int32 | undefined): this {
        return this
    }
    monitorInvisibleArea(value: boolean | undefined): this {
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
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkImageAnimatorComponent extends ArkCommonMethodComponent implements ImageAnimatorAttribute {
    getPeer(): ArkImageAnimatorPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkImageAnimatorPeer)
    }
    public setImageAnimatorOptions(): this {
        if (this.checkPriority("setImageAnimatorOptions")) {
            this.getPeer()?.setImageAnimatorOptionsAttribute()
            this.applyOptionsFinish('ImageAnimatorAttribute');
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
    public duration(value: int32 | undefined): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (int32 | undefined)
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
    public iterations(value: int32 | undefined): this {
        if (this.checkPriority("iterations")) {
            const value_casted = value as (int32 | undefined)
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
         ModifierStateManager.INSTANCE.scope(() => {
            hookImageAnimatorAttributeModifier(this, value); 
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
export function ImageAnimatorImpl(
    @memo
    style: ((attributes: ImageAnimatorAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkImageAnimatorComponent>((): ArkImageAnimatorComponent => {
        return new ArkImageAnimatorComponent()
    })
    NodeAttach<ArkImageAnimatorPeer>((): ArkImageAnimatorPeer => ArkImageAnimatorPeer.create(receiver), (peer: ArkImageAnimatorPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class ImageFrameInfo_serializer {
    public static write(buffer: SerializerBase, value: ImageFrameInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSrcForIdx0  = valueHolderForSrc as string
            valueSerializer.writeString(valueHolderForSrcForIdx0)
        } else if (valueHolderForSrc instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForSrcForIdx1  = valueHolderForSrc as Resource
            Resource_serializer.write(valueSerializer, valueHolderForSrcForIdx1)
        } else if (valueHolderForSrc instanceof image.PixelMap) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForSrcForIdx2  = valueHolderForSrc as image.PixelMap
            image_PixelMap_serializer.write(valueSerializer, valueHolderForSrcForIdx2)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
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
            if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
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
            if (valueHolderForTopTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTopTmpValueForIdx0  = valueHolderForTopTmpValue as double
                valueSerializer.writeFloat64(valueHolderForTopTmpValueForIdx0)
            } else if (valueHolderForTopTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
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
            if (valueHolderForLeftTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeftTmpValueForIdx0  = valueHolderForLeftTmpValue as double
                valueSerializer.writeFloat64(valueHolderForLeftTmpValueForIdx0)
            } else if (valueHolderForLeftTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
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
            valueSerializer.writeInt32(valueHolderForDurationTmpValue)
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
        let widthTmpBuf : double | string | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : double | string | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as double | string)
        }
        const widthTmpResult : double | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : double | string | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : double | string | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as double | string)
        }
        const heightTmpResult : double | string | undefined = heightTmpBuf
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : double | string | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const topTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let topTmpBuf_ : double | string | undefined
            if (topTmpBuf_UnionSelector == (0).toChar()) {
                topTmpBuf_ = valueDeserializer.readFloat64()
            } else if (topTmpBuf_UnionSelector == (1).toChar()) {
                topTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for topTmpBuf_ has to be chosen through deserialisation.")
            }
            topTmpBuf = (topTmpBuf_ as double | string)
        }
        const topTmpResult : double | string | undefined = topTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : double | string | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leftTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let leftTmpBuf_ : double | string | undefined
            if (leftTmpBuf_UnionSelector == (0).toChar()) {
                leftTmpBuf_ = valueDeserializer.readFloat64()
            } else if (leftTmpBuf_UnionSelector == (1).toChar()) {
                leftTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for leftTmpBuf_ has to be chosen through deserialisation.")
            }
            leftTmpBuf = (leftTmpBuf_ as double | string)
        }
        const leftTmpResult : double | string | undefined = leftTmpBuf
        const durationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let durationTmpBuf : int32 | undefined = undefined
        if ((durationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            durationTmpBuf = valueDeserializer.readInt32()
        }
        const durationTmpResult : int32 | undefined = durationTmpBuf
        let value : ImageFrameInfo = ({src: srcTmpResult, width: widthTmpResult, height: heightTmpResult, top: topTmpResult, left: leftTmpResult, duration: durationTmpResult} as ImageFrameInfo)
        return value
    }
}
