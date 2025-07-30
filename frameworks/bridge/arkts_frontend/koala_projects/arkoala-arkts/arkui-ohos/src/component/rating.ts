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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Callback_Number_Void } from "./alphabetIndexer"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkRatingPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRatingPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Rating_construct(peerId, flags)
        const _peer  = new ArkRatingPeer(_peerPtr, peerId, "Rating", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRatingOptionsAttribute(options?: RatingOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRatingOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RatingInterface_setRatingOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stars0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_stars0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stars1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_stars1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stepSize0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_stepSize0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stepSize1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_stepSize1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    starStyle0Attribute(value: StarStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeStarStyleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_starStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    starStyle1Attribute(value: StarStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeStarStyleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_starStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChange0Attribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_onChange0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChange1Attribute(value: OnRatingChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_onChange1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifier0Attribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_contentModifier0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifier1Attribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._RatingAttribute_contentModifier1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_ratingAttribute(callback: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._RatingAttribute__onChangeEvent_rating(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RatingOptions {
    rating: number;
    indicator?: boolean;
}
export interface StarStyleOptions {
    backgroundUri: string;
    foregroundUri: string;
    secondaryUri?: string;
}
export type RatingInterface = (options?: RatingOptions) => RatingAttribute;
export interface RatingConfiguration extends CommonConfiguration {
    rating: number;
    indicator: boolean;
    stars: number;
    stepSize: number;
    triggerChange: ((index: number) => void);
}
export type OnRatingChangeCallback = (rating: number) => void;
export interface RatingAttribute extends CommonMethod {
    stars(value: number | undefined): this
    stepSize(value: number | undefined): this
    starStyle(value: StarStyleOptions | undefined): this
    onChange(value: ((index: number) => void) | undefined | OnRatingChangeCallback | undefined): this
    contentModifier(value: ContentModifier | undefined): this
    _onChangeEvent_rating(callback: ((index: number) => void)): void
}
export class ArkRatingStyle extends ArkCommonMethodStyle implements RatingAttribute {
    stars_value?: number | undefined
    stepSize_value?: number | undefined
    starStyle_value?: StarStyleOptions | undefined
    onChange_value?: ((index: number) => void) | undefined
    contentModifier_value?: ContentModifier | undefined
    public stars(value: number | undefined): this {
        return this
    }
    public stepSize(value: number | undefined): this {
        return this
    }
    public starStyle(value: StarStyleOptions | undefined): this {
        return this
    }
    public onChange(value: ((index: number) => void) | undefined | OnRatingChangeCallback | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        return this
    }
    public _onChangeEvent_rating(callback: ((index: number) => void)): void {
        throw new Error("Unimplmented")
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
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.stars0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.stars1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public stepSize(value: number | undefined): this {
        if (this.checkPriority("stepSize")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.stepSize0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.stepSize1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public starStyle(value: StarStyleOptions | undefined): this {
        if (this.checkPriority("starStyle")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (StarStyleOptions | undefined)
                this.getPeer()?.starStyle0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (StarStyleOptions | undefined)
                this.getPeer()?.starStyle1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onChange(value: ((index: number) => void) | undefined | OnRatingChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((index: number) => void) | undefined)
                this.getPeer()?.onChange0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (OnRatingChangeCallback | undefined)
                this.getPeer()?.onChange1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.BIGINT == value_type) || (RuntimeType.BOOLEAN == value_type) || (RuntimeType.FUNCTION == value_type) || (RuntimeType.MATERIALIZED == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.SYMBOL == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ContentModifier | undefined)
                this.getPeer()?.contentModifier0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BIGINT == value_type) || (RuntimeType.BOOLEAN == value_type) || (RuntimeType.FUNCTION == value_type) || (RuntimeType.MATERIALIZED == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.SYMBOL == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ContentModifier | undefined)
                this.getPeer()?.contentModifier1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public _onChangeEvent_rating(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_rating")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_ratingAttribute(callback_casted)
            return
        }
        return
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Rating(
    /** @memo */
    style: ((attributes: RatingAttribute) => void) | undefined,
    options?: RatingOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkRatingComponent()
    })
    NodeAttach<ArkRatingPeer>((): ArkRatingPeer => ArkRatingPeer.create(receiver), (_: ArkRatingPeer) => {
        receiver.setRatingOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
