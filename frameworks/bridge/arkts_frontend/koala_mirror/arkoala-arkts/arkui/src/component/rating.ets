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
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ContentModifier, AttributeModifier, hookRatingContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ResourceStr } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRatingPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRatingPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Rating_construct(peerId, flags)
        const _peer  = new ArkRatingPeer(_peerPtr, peerId, "Rating", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRatingOptionsAttribute(options?: RatingOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            RatingOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._RatingInterface_setRatingOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStarsAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setStars(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStepSizeAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setStepSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStarStyleAttribute(value: StarStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            StarStyleOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setStarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnRatingChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<RatingConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_ratingAttribute(callback_: ((rating: number | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._RatingAttribute_set_onChangeEvent_rating(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RatingOptions {
    rating: number | undefined;
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
    _onChangeEvent_rating(callback_: ((rating: number | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_rating")
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
    public _onChangeEvent_rating(callback_: ((rating: number | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RatingAttribute): void {
        super.apply(target)
        if (this.stars_value !== undefined)
            target.stars(this.stars_value!)
        if (this.stepSize_value !== undefined)
            target.stepSize(this.stepSize_value!)
        if (this.starStyle_value !== undefined)
            target.starStyle(this.starStyle_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
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
            const value_casted = value as (ContentModifier<RatingConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_rating(callback_: ((rating: number | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_rating")) {
            const callback__casted = callback_ as (((rating: number | undefined) => void))
            this.getPeer()?.set_onChangeEvent_ratingAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRatingStyle(receiver: RatingAttribute, modifier: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRatingStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Rating")
// export function Rating(
//     options?: RatingOptions,
//     @memo
//     content_?: () => void,
// ): RatingAttribute {
//     throw new Error("Not implemented")
// }

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
        withRatingStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkRatingSet extends ArkCommonMethodSet implements RatingAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _stars_flag?: boolean
    _stars0_value?: number | undefined
    _stepSize_flag?: boolean
    _stepSize0_value?: number | undefined
    _starStyle_flag?: boolean
    _starStyle0_value?: StarStyleOptions | undefined
    _onChange_flag?: boolean
    _onChange0_value?: OnRatingChangeCallback | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<RatingConfiguration> | undefined
    __onChangeEvent_rating_flag?: boolean
    __onChangeEvent_rating0_value?: ((rating: number | undefined) => void)
    applyModifierPatch(component: RatingAttribute): void {
        if (this._stars_flag)
            component.stars((this._stars0_value as number | undefined))
        if (this._stepSize_flag)
            component.stepSize((this._stepSize0_value as number | undefined))
        if (this._starStyle_flag)
            component.starStyle((this._starStyle0_value as StarStyleOptions | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as OnRatingChangeCallback | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<RatingConfiguration> | undefined))
    }
    public stars(value: number | undefined): this {
        this._stars_flag = true
        this._stars0_value = value
        return this
    }
    public stepSize(value: number | undefined): this {
        this._stepSize_flag = true
        this._stepSize0_value = value
        return this
    }
    public starStyle(value: StarStyleOptions | undefined): this {
        this._starStyle_flag = true
        this._starStyle0_value = value
        return this
    }
    public onChange(value: OnRatingChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public _onChangeEvent_rating(callback_: ((rating: number | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RatingConfiguration_serializer {
    public static write(buffer: SerializerBase, value: RatingConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_rating  = value.rating
        valueSerializer.writeNumber(value_rating)
        const value_indicator  = value.indicator
        valueSerializer.writeBoolean(value_indicator)
        const value_stars  = value.stars
        valueSerializer.writeNumber(value_stars)
        const value_stepSize  = value.stepSize
        valueSerializer.writeNumber(value_stepSize)
        const value_triggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(value_triggerChange)
    }
    public static read(buffer: DeserializerBase): RatingConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<RatingConfiguration> = (valueDeserializer.readObject() as ContentModifier<RatingConfiguration>)
        const rating_result : number = (valueDeserializer.readNumber() as number)
        const indicator_result : boolean = valueDeserializer.readBoolean()
        const stars_result : number = (valueDeserializer.readNumber() as number)
        const stepSize_result : number = (valueDeserializer.readNumber() as number)
        const triggerChange_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChange_buf_call : KPointer = valueDeserializer.readPointer()
        const triggerChange_buf_callSync : KPointer = valueDeserializer.readPointer()
        const triggerChange_result : ((value0: number) => void) = (value0: number):void => { 
    const triggerChange_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    triggerChange_buf_argsSerializer.writeInt32(triggerChange_buf_resource.resourceId);
    triggerChange_buf_argsSerializer.writePointer(triggerChange_buf_call);
    triggerChange_buf_argsSerializer.writePointer(triggerChange_buf_callSync);
    triggerChange_buf_argsSerializer.writeNumber(value0);
    InteropNativeModule._CallCallback(36519084, triggerChange_buf_argsSerializer.asBuffer(), triggerChange_buf_argsSerializer.length());
    triggerChange_buf_argsSerializer.release();
    return; }
        let value : RatingConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, rating: rating_result, indicator: indicator_result, stars: stars_result, stepSize: stepSize_result, triggerChange: triggerChange_result} as RatingConfiguration)
        return value
    }
}
export class RatingOptions_serializer {
    public static write(buffer: SerializerBase, value: RatingOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_rating  = value.rating
        let value_rating_type : int32 = RuntimeType.UNDEFINED
        value_rating_type = runtimeType(value_rating)
        valueSerializer.writeInt8((value_rating_type).toChar())
        if ((value_rating_type) != (RuntimeType.UNDEFINED)) {
            const value_rating_value  = value_rating!
            valueSerializer.writeNumber(value_rating_value)
        }
        const value_indicator  = value.indicator
        let value_indicator_type : int32 = RuntimeType.UNDEFINED
        value_indicator_type = runtimeType(value_indicator)
        valueSerializer.writeInt8((value_indicator_type).toChar())
        if ((value_indicator_type) != (RuntimeType.UNDEFINED)) {
            const value_indicator_value  = value_indicator!
            valueSerializer.writeBoolean(value_indicator_value)
        }
    }
    public static read(buffer: DeserializerBase): RatingOptions {
        let valueDeserializer : DeserializerBase = buffer
        const rating_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rating_buf : number | undefined
        if ((rating_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            rating_buf = (valueDeserializer.readNumber() as number)
        }
        const rating_result : number | undefined = rating_buf
        const indicator_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicator_buf : boolean | undefined
        if ((indicator_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            indicator_buf = valueDeserializer.readBoolean()
        }
        const indicator_result : boolean | undefined = indicator_buf
        let value : RatingOptions = ({rating: rating_result, indicator: indicator_result} as RatingOptions)
        return value
    }
}
export class StarStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: StarStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_backgroundUri  = value.backgroundUri
        let value_backgroundUri_type : int32 = RuntimeType.UNDEFINED
        value_backgroundUri_type = runtimeType(value_backgroundUri)
        if (RuntimeType.STRING == value_backgroundUri_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_backgroundUri_0  = value_backgroundUri as string
            valueSerializer.writeString(value_backgroundUri_0)
        }
        else if (RuntimeType.OBJECT == value_backgroundUri_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_backgroundUri_1  = value_backgroundUri as Resource
            Resource_serializer.write(valueSerializer, value_backgroundUri_1)
        }
        const value_foregroundUri  = value.foregroundUri
        let value_foregroundUri_type : int32 = RuntimeType.UNDEFINED
        value_foregroundUri_type = runtimeType(value_foregroundUri)
        if (RuntimeType.STRING == value_foregroundUri_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_foregroundUri_0  = value_foregroundUri as string
            valueSerializer.writeString(value_foregroundUri_0)
        }
        else if (RuntimeType.OBJECT == value_foregroundUri_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_foregroundUri_1  = value_foregroundUri as Resource
            Resource_serializer.write(valueSerializer, value_foregroundUri_1)
        }
        const value_secondaryUri  = value.secondaryUri
        let value_secondaryUri_type : int32 = RuntimeType.UNDEFINED
        value_secondaryUri_type = runtimeType(value_secondaryUri)
        valueSerializer.writeInt8((value_secondaryUri_type).toChar())
        if ((value_secondaryUri_type) != (RuntimeType.UNDEFINED)) {
            const value_secondaryUri_value  = value_secondaryUri!
            let value_secondaryUri_value_type : int32 = RuntimeType.UNDEFINED
            value_secondaryUri_value_type = runtimeType(value_secondaryUri_value)
            if (RuntimeType.STRING == value_secondaryUri_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_secondaryUri_value_0  = value_secondaryUri_value as string
                valueSerializer.writeString(value_secondaryUri_value_0)
            }
            else if (RuntimeType.OBJECT == value_secondaryUri_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_secondaryUri_value_1  = value_secondaryUri_value as Resource
                Resource_serializer.write(valueSerializer, value_secondaryUri_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): StarStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundUri_buf_selector : int32 = valueDeserializer.readInt8()
        let backgroundUri_buf : string | Resource | undefined
        if (backgroundUri_buf_selector == (0).toChar()) {
            backgroundUri_buf = (valueDeserializer.readString() as string)
        }
        else if (backgroundUri_buf_selector == (1).toChar()) {
            backgroundUri_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for backgroundUri_buf has to be chosen through deserialisation.")
        }
        const backgroundUri_result : ResourceStr = (backgroundUri_buf as string | Resource)
        const foregroundUri_buf_selector : int32 = valueDeserializer.readInt8()
        let foregroundUri_buf : string | Resource | undefined
        if (foregroundUri_buf_selector == (0).toChar()) {
            foregroundUri_buf = (valueDeserializer.readString() as string)
        }
        else if (foregroundUri_buf_selector == (1).toChar()) {
            foregroundUri_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for foregroundUri_buf has to be chosen through deserialisation.")
        }
        const foregroundUri_result : ResourceStr = (foregroundUri_buf as string | Resource)
        const secondaryUri_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let secondaryUri_buf : ResourceStr | undefined
        if ((secondaryUri_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const secondaryUri_buf__selector : int32 = valueDeserializer.readInt8()
            let secondaryUri_buf_ : string | Resource | undefined
            if (secondaryUri_buf__selector == (0).toChar()) {
                secondaryUri_buf_ = (valueDeserializer.readString() as string)
            }
            else if (secondaryUri_buf__selector == (1).toChar()) {
                secondaryUri_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for secondaryUri_buf_ has to be chosen through deserialisation.")
            }
            secondaryUri_buf = (secondaryUri_buf_ as string | Resource)
        }
        const secondaryUri_result : ResourceStr | undefined = secondaryUri_buf
        let value : StarStyleOptions = ({backgroundUri: backgroundUri_result, foregroundUri: foregroundUri_result, secondaryUri: secondaryUri_result} as StarStyleOptions)
        return value
    }
}
