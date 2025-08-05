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
import { ArkCommonMethodPeer, CommonMethod, Bindable, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier, Bindable_Number_serializer } from "./common"
import { ContentModifier, AttributeModifier, hookRatingContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ResourceStr } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkRatingPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    setStarsAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setStars(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStepSizeAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
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
    rating: number | Bindable<number> | undefined;
    indicator?: boolean;
}
export interface StarStyleOptions {
    backgroundUri: ResourceStr;
    foregroundUri: ResourceStr;
    secondaryUri?: ResourceStr;
}
export interface RatingConfiguration extends CommonConfiguration<RatingConfiguration> {
    rating: number;
    indicator: boolean;
    stars: number;
    stepSize: number;
    triggerChange: ((value0: number) => void);
}
export type OnRatingChangeCallback = (rating: number) => void;
export interface RatingAttribute extends CommonMethod {
    stars(value: number | undefined): this {
        throw new Error("Unimplemented method stars")
    }
    stepSize(value: number | undefined): this {
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
    stars_value?: number | undefined
    stepSize_value?: number | undefined
    starStyle_value?: StarStyleOptions | undefined
    onChange_value?: OnRatingChangeCallback | undefined
    contentModifier_value?: ContentModifier<RatingConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined
    public stars(value: number | undefined): this {
        return this
    }
    public stepSize(value: number | undefined): this {
        return this
    }
    public starStyle(value: StarStyleOptions | undefined): this {
        return this
    }
    public onChange(value: OnRatingChangeCallback | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkRatingComponent extends ArkCommonMethodComponent implements RatingAttribute {
    getPeer(): ArkRatingPeer {
        return (this.peer as ArkRatingPeer)
    }
    public setRatingOptions(options?: RatingOptions): this {
        if (this.checkPriority("setRatingOptions")) {
            const options_casted = options as (RatingOptions | undefined)
            this.getPeer()?.setRatingOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public stars(value: number | undefined): this {
        if (this.checkPriority("stars")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setStarsAttribute(value_casted)
            return this
        }
        return this
    }
    public stepSize(value: number | undefined): this {
        if (this.checkPriority("stepSize")) {
            const value_casted = value as (number | undefined)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Rating(
    @memo
    style: ((attributes: RatingAttribute) => void) | undefined,
    options?: RatingOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRatingComponent>((): ArkRatingComponent => {
        return new ArkRatingComponent()
    })
    NodeAttach<ArkRatingPeer>((): ArkRatingPeer => ArkRatingPeer.create(receiver), (_: ArkRatingPeer): void => {
        receiver.setRatingOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class RatingModifier extends CommonMethodModifier implements RatingAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _stars_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stars_0_0value?: number | undefined
    _stepSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stepSize_0_0value?: number | undefined
    _starStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _starStyle_0_0value?: StarStyleOptions | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnRatingChangeCallback | undefined
    applyModifierPatch(peer: ArkRatingPeer): void {
        super.applyModifierPatch(peer)
        if (this._stars_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stars_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStarsAttribute((this._stars_0_0value as number | undefined));
                    this._stars_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stars_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stars_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStarsAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStepSizeAttribute((this._stepSize_0_0value as number | undefined));
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStepSizeAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._starStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._starStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStarStyleAttribute((this._starStyle_0_0value as StarStyleOptions | undefined));
                    this._starStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._starStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._starStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStarStyleAttribute((undefined as StarStyleOptions | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnRatingChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnRatingChangeCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RatingModifier): void {
        super.mergeModifier(modifier)
        if (modifier._stars_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stars_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stars(modifier._stars_0_0value);
                    break;
                }
                default: {
                    this.stars((undefined as number | undefined));
                }
            }
        }
        if (modifier._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stepSize(modifier._stepSize_0_0value);
                    break;
                }
                default: {
                    this.stepSize((undefined as number | undefined));
                }
            }
        }
        if (modifier._starStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._starStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.starStyle(modifier._starStyle_0_0value);
                    break;
                }
                default: {
                    this.starStyle((undefined as StarStyleOptions | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnRatingChangeCallback | undefined));
                }
            }
        }
    }
    stars(value: number | undefined): this {
        if (((this._stars_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stars_0_0value) !== (value)))
        {
            this._stars_0_flag = AttributeUpdaterFlag.UPDATE
            this._stars_0_0value = value
        } else
        {
            this._stars_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stepSize(value: number | undefined): this {
        if (((this._stepSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stepSize_0_0value) !== (value)))
        {
            this._stepSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._stepSize_0_0value = value
        } else
        {
            this._stepSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    starStyle(value: StarStyleOptions | undefined): this {
        if (((this._starStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._starStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._starStyle_0_0value = value
        } else
        {
            this._starStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnRatingChangeCallback | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RatingConfiguration_serializer {
    public static write(buffer: SerializerBase, value: RatingConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForRating  = value.rating
        valueSerializer.writeNumber(valueHolderForRating)
        const valueHolderForIndicator  = value.indicator
        valueSerializer.writeBoolean(valueHolderForIndicator)
        const valueHolderForStars  = value.stars
        valueSerializer.writeNumber(valueHolderForStars)
        const valueHolderForStepSize  = value.stepSize
        valueSerializer.writeNumber(valueHolderForStepSize)
        const valueHolderForTriggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerChange)
    }
    public static read(buffer: DeserializerBase): RatingConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<RatingConfiguration> = (valueDeserializer.readObject() as ContentModifier<RatingConfiguration>)
        const ratingTmpResult : number = (valueDeserializer.readNumber() as number)
        const indicatorTmpResult : boolean = valueDeserializer.readBoolean()
        const starsTmpResult : number = (valueDeserializer.readNumber() as number)
        const stepSizeTmpResult : number = (valueDeserializer.readNumber() as number)
        const triggerChangeTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChangeTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpResult : ((value0: number) => void) = (value0: number):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeNumber(value0);
            InteropNativeModule._CallCallback(36519084, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
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
            if (valueHolderForRatingTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForRatingTmpValueForIdx0  = valueHolderForRatingTmpValue as number
                valueSerializer.writeNumber(valueHolderForRatingTmpValueForIdx0)
            } else if (valueHolderForRatingTmpValue instanceof Bindable<number>) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForRatingTmpValueForIdx1  = valueHolderForRatingTmpValue as Bindable<number>
                Bindable_Number_serializer.write(valueSerializer, valueHolderForRatingTmpValueForIdx1)
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
        let ratingTmpBuf : number | Bindable<number> | undefined
        if ((ratingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const ratingTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let ratingTmpBuf_ : number | Bindable<number> | undefined
            if (ratingTmpBuf_UnionSelector == (0).toChar()) {
                ratingTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (ratingTmpBuf_UnionSelector == (1).toChar()) {
                ratingTmpBuf_ = Bindable_Number_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for ratingTmpBuf_ has to be chosen through deserialisation.")
            }
            ratingTmpBuf = (ratingTmpBuf_ as number | Bindable<number>)
        }
        const ratingTmpResult : number | Bindable<number> | undefined = ratingTmpBuf
        const indicatorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorTmpBuf : boolean | undefined
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
        if (valueHolderForBackgroundUri instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForBackgroundUriForIdx0  = valueHolderForBackgroundUri as string
            valueSerializer.writeString(valueHolderForBackgroundUriForIdx0)
        } else if (valueHolderForBackgroundUri instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForBackgroundUriForIdx1  = valueHolderForBackgroundUri as Resource
            Resource_serializer.write(valueSerializer, valueHolderForBackgroundUriForIdx1)
        }
        const valueHolderForForegroundUri  = value.foregroundUri
        if (valueHolderForForegroundUri instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForForegroundUriForIdx0  = valueHolderForForegroundUri as string
            valueSerializer.writeString(valueHolderForForegroundUriForIdx0)
        } else if (valueHolderForForegroundUri instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForForegroundUriForIdx1  = valueHolderForForegroundUri as Resource
            Resource_serializer.write(valueSerializer, valueHolderForForegroundUriForIdx1)
        }
        const valueHolderForSecondaryUri  = value.secondaryUri
        if (valueHolderForSecondaryUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSecondaryUriTmpValue  = valueHolderForSecondaryUri!
            if (valueHolderForSecondaryUriTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSecondaryUriTmpValueForIdx0  = valueHolderForSecondaryUriTmpValue as string
                valueSerializer.writeString(valueHolderForSecondaryUriTmpValueForIdx0)
            } else if (valueHolderForSecondaryUriTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForSecondaryUriTmpValueForIdx1  = valueHolderForSecondaryUriTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSecondaryUriTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StarStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundUriTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let backgroundUriTmpBuf : string | Resource | undefined
        if (backgroundUriTmpBufUnionSelector == (0).toChar()) {
            backgroundUriTmpBuf = (valueDeserializer.readString() as string)
        } else if (backgroundUriTmpBufUnionSelector == (1).toChar()) {
            backgroundUriTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for backgroundUriTmpBuf has to be chosen through deserialisation.")
        }
        const backgroundUriTmpResult : ResourceStr = (backgroundUriTmpBuf as string | Resource)
        const foregroundUriTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let foregroundUriTmpBuf : string | Resource | undefined
        if (foregroundUriTmpBufUnionSelector == (0).toChar()) {
            foregroundUriTmpBuf = (valueDeserializer.readString() as string)
        } else if (foregroundUriTmpBufUnionSelector == (1).toChar()) {
            foregroundUriTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for foregroundUriTmpBuf has to be chosen through deserialisation.")
        }
        const foregroundUriTmpResult : ResourceStr = (foregroundUriTmpBuf as string | Resource)
        const secondaryUriTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let secondaryUriTmpBuf : ResourceStr | undefined
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
