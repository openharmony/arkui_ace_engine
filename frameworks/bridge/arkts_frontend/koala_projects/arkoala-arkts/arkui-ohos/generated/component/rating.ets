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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, Bindable, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_F64_serializer } from "./common"
import { ContentModifier, AttributeModifier, hookRatingContentModifier, hookRatingAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ResourceStr } from "./units"
import { Resource } from "global.resource"
import { RatingModifier } from "./../RatingModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
export class ArkRatingPeer extends ArkCommonMethodPeer {
    attributeSet?: RatingModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRatingPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Rating_construct(peerId, flags)
        const _peer  = new ArkRatingPeer(_peerPtr, peerId, 'Rating', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRatingOptionsAttribute(options?: RatingOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            RatingOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RatingInterface_setRatingOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStarsAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setStars(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStepSizeAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setStepSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStarStyleAttribute(value: StarStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            StarStyleOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setStarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnRatingChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RatingOptions {
    rating: double | Bindable<double> | undefined;
    indicator?: boolean;
}
export interface StarStyleOptions {
    backgroundUri: ResourceStr | undefined;
    foregroundUri: ResourceStr | undefined;
    secondaryUri?: ResourceStr;
}
export interface RatingConfiguration extends CommonConfiguration<RatingConfiguration> {
    rating: double;
    indicator: boolean;
    stars: int32;
    stepSize: double;
    triggerChange: ((value0: double) => void);
}
export type OnRatingChangeCallback = (rating: double) => void;
export interface RatingAttribute extends CommonMethod {
    setRatingOptions(options?: RatingOptions): this {
        throw new Error("Unimplemented method setRatingOptions")
    }
    stars(value: int32 | undefined): this {
        throw new Error("Unimplemented method stars")
    }
    stepSize(value: double | undefined): this {
        throw new Error("Unimplemented method stepSize")
    }
    starStyle(value: StarStyleOptions | undefined): this {
        throw new Error("Unimplemented method starStyle")
    }
    onChange(value: OnRatingChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRatingStyle extends ArkCommonMethodStyle implements RatingAttribute {
    stars_value?: int32 | undefined
    stepSize_value?: double | undefined
    starStyle_value?: StarStyleOptions | undefined
    onChange_value?: OnRatingChangeCallback | undefined
    contentModifier_value?: ContentModifier<RatingConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined
    setRatingOptions(options?: RatingOptions): this {
        return this
    }
    stars(value: int32 | undefined): this {
        return this
    }
    stepSize(value: double | undefined): this {
        return this
    }
    starStyle(value: StarStyleOptions | undefined): this {
        return this
    }
    onChange(value: OnRatingChangeCallback | undefined): this {
        return this
    }
    contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkRatingComponent extends ArkCommonMethodComponent implements RatingAttribute {
    getPeer(): ArkRatingPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkRatingPeer)
    }
    public setRatingOptions(options?: RatingOptions): this {
        if (this.checkPriority("setRatingOptions")) {
            const options_casted = options as (RatingOptions | undefined)
            this.getPeer()?.setRatingOptionsAttribute(options_casted)
            this.applyOptionsFinish('RatingAttribute');
            return this
        }
        return this
    }
    public stars(value: int32 | undefined): this {
        if (this.checkPriority("stars")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setStarsAttribute(value_casted)
            return this
        }
        return this
    }
    public stepSize(value: double | undefined): this {
        if (this.checkPriority("stepSize")) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setStepSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public starStyle(value: StarStyleOptions | undefined): this {
        if (this.checkPriority("starStyle")) {
            const value_casted = value as (StarStyleOptions | undefined)
            this.getPeer()?.setStarStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnRatingChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnRatingChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            hookRatingContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookRatingAttributeModifier(this, value);
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
export function RatingImpl(
    @memo
    style: ((attributes: RatingAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRatingComponent>((): ArkRatingComponent => {
        return new ArkRatingComponent()
    })
    NodeAttach<ArkRatingPeer>((): ArkRatingPeer => ArkRatingPeer.create(receiver), (peer: ArkRatingPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class RatingConfiguration_serializer {
    public static write(buffer: SerializerBase, value: RatingConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForRating  = value.rating
        valueSerializer.writeFloat64(valueHolderForRating)
        const valueHolderForIndicator  = value.indicator
        valueSerializer.writeBoolean(valueHolderForIndicator)
        const valueHolderForStars  = value.stars
        valueSerializer.writeInt32(valueHolderForStars)
        const valueHolderForStepSize  = value.stepSize
        valueSerializer.writeFloat64(valueHolderForStepSize)
        const valueHolderForTriggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerChange)
    }
    public static read(buffer: DeserializerBase): RatingConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<RatingConfiguration> = (valueDeserializer.readObject() as ContentModifier<RatingConfiguration>)
        const ratingTmpResult : double = valueDeserializer.readFloat64()
        const indicatorTmpResult : boolean = valueDeserializer.readBoolean()
        const starsTmpResult : int32 = valueDeserializer.readInt32()
        const stepSizeTmpResult : double = valueDeserializer.readFloat64()
        const triggerChangeTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChangeTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpResult : ((value0: double) => void) = (value0: double):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeFloat64(value0);
            InteropNativeModule._CallCallbackSync(10, -949162837, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
            triggerChangeTmpBufBufArgsSerializer.release();
            return;
        }
        let value : RatingConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, rating: ratingTmpResult, indicator: indicatorTmpResult, stars: starsTmpResult, stepSize: stepSizeTmpResult, triggerChange: triggerChangeTmpResult} as RatingConfiguration)
        return value
    }
}
export class RatingOptions_serializer {
    public static write(buffer: SerializerBase, value: RatingOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRating  = value.rating
        if (valueHolderForRating !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRatingTmpValue  = valueHolderForRating!
            if (valueHolderForRatingTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRatingTmpValueForIdx0  = valueHolderForRatingTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRatingTmpValueForIdx0)
            } else if (valueHolderForRatingTmpValue instanceof Bindable<double>) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRatingTmpValueForIdx1  = valueHolderForRatingTmpValue as Bindable<double>
                Bindable_F64_serializer.write(valueSerializer, valueHolderForRatingTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIndicator  = value.indicator
        if (valueHolderForIndicator !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndicatorTmpValue  = valueHolderForIndicator!
            valueSerializer.writeBoolean(valueHolderForIndicatorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RatingOptions {
        let valueDeserializer : DeserializerBase = buffer
        const ratingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let ratingTmpBuf : double | Bindable<double> | undefined = undefined
        if ((ratingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const ratingTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let ratingTmpBuf_ : double | Bindable<double> | undefined
            if (ratingTmpBuf_UnionSelector == (0).toChar()) {
                ratingTmpBuf_ = valueDeserializer.readFloat64()
            } else if (ratingTmpBuf_UnionSelector == (1).toChar()) {
                ratingTmpBuf_ = Bindable_F64_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for ratingTmpBuf_ has to be chosen through deserialisation.")
            }
            ratingTmpBuf = (ratingTmpBuf_ as double | Bindable<double>)
        }
        const ratingTmpResult : double | Bindable<double> | undefined = ratingTmpBuf
        const indicatorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorTmpBuf : boolean | undefined = undefined
        if ((indicatorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            indicatorTmpBuf = valueDeserializer.readBoolean()
        }
        const indicatorTmpResult : boolean | undefined = indicatorTmpBuf
        let value : RatingOptions = ({rating: ratingTmpResult, indicator: indicatorTmpResult} as RatingOptions)
        return value
    }
}
export class StarStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: StarStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBackgroundUri  = value.backgroundUri
        if (valueHolderForBackgroundUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundUriTmpValue  = valueHolderForBackgroundUri!
            if (valueHolderForBackgroundUriTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundUriTmpValueForIdx0  = valueHolderForBackgroundUriTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundUriTmpValueForIdx0)
            } else if (valueHolderForBackgroundUriTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundUriTmpValueForIdx1  = valueHolderForBackgroundUriTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundUriTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForForegroundUri  = value.foregroundUri
        if (valueHolderForForegroundUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForForegroundUriTmpValue  = valueHolderForForegroundUri!
            if (valueHolderForForegroundUriTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForForegroundUriTmpValueForIdx0  = valueHolderForForegroundUriTmpValue as string
                valueSerializer.writeString(valueHolderForForegroundUriTmpValueForIdx0)
            } else if (valueHolderForForegroundUriTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForForegroundUriTmpValueForIdx1  = valueHolderForForegroundUriTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForForegroundUriTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSecondaryUri  = value.secondaryUri
        if (valueHolderForSecondaryUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSecondaryUriTmpValue  = valueHolderForSecondaryUri!
            if (valueHolderForSecondaryUriTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSecondaryUriTmpValueForIdx0  = valueHolderForSecondaryUriTmpValue as string
                valueSerializer.writeString(valueHolderForSecondaryUriTmpValueForIdx0)
            } else if (valueHolderForSecondaryUriTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSecondaryUriTmpValueForIdx1  = valueHolderForSecondaryUriTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSecondaryUriTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StarStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundUriTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundUriTmpBuf : ResourceStr | undefined = undefined
        if ((backgroundUriTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundUriTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundUriTmpBuf_ : string | Resource | undefined
            if (backgroundUriTmpBuf_UnionSelector == (0).toChar()) {
                backgroundUriTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundUriTmpBuf_UnionSelector == (1).toChar()) {
                backgroundUriTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundUriTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundUriTmpBuf = (backgroundUriTmpBuf_ as string | Resource)
        }
        const backgroundUriTmpResult : ResourceStr | undefined = backgroundUriTmpBuf
        const foregroundUriTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let foregroundUriTmpBuf : ResourceStr | undefined = undefined
        if ((foregroundUriTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const foregroundUriTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let foregroundUriTmpBuf_ : string | Resource | undefined
            if (foregroundUriTmpBuf_UnionSelector == (0).toChar()) {
                foregroundUriTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (foregroundUriTmpBuf_UnionSelector == (1).toChar()) {
                foregroundUriTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for foregroundUriTmpBuf_ has to be chosen through deserialisation.")
            }
            foregroundUriTmpBuf = (foregroundUriTmpBuf_ as string | Resource)
        }
        const foregroundUriTmpResult : ResourceStr | undefined = foregroundUriTmpBuf
        const secondaryUriTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let secondaryUriTmpBuf : ResourceStr | undefined = undefined
        if ((secondaryUriTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const secondaryUriTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let secondaryUriTmpBuf_ : string | Resource | undefined
            if (secondaryUriTmpBuf_UnionSelector == (0).toChar()) {
                secondaryUriTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (secondaryUriTmpBuf_UnionSelector == (1).toChar()) {
                secondaryUriTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for secondaryUriTmpBuf_ has to be chosen through deserialisation.")
            }
            secondaryUriTmpBuf = (secondaryUriTmpBuf_ as string | Resource)
        }
        const secondaryUriTmpResult : ResourceStr | undefined = secondaryUriTmpBuf
        let value : StarStyleOptions = ({backgroundUri: backgroundUriTmpResult, foregroundUri: foregroundUriTmpResult, secondaryUri: secondaryUriTmpResult} as StarStyleOptions)
        return value
    }
}
