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
import { ResourceColor, Length, PX, VP, LPX, Font } from "./units"
import { LinearGradient } from "./dataPanel"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Color } from "./enums"
import { Resource } from "global/resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics } from "../Graphics"

export class ArkProgressPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkProgressPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Progress_construct(peerId, flags)
        const _peer  = new ArkProgressPeer(_peerPtr, peerId, "Progress", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setProgressOptionsAttribute(options: ProgressOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeProgressOptions(options)
        ArkUIGeneratedNativeModule._ProgressInterface_setProgressOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    valueAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorAttribute(value: ResourceColor | LinearGradient | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LinearGradient
                thisSerializer.writeLinearGradient(value_value_1)
            } else {
                let value_value_type : int32 = RuntimeType.UNDEFINED
                value_value_type = runtimeType(value_value)
                if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0  = value_value as ResourceColor
                    let value_value_0_type : int32 = RuntimeType.UNDEFINED
                    value_value_0_type = runtimeType(value_value_0)
                    if (TypeChecker.isColor(value_value_0)) {
                        thisSerializer.writeInt8(0 as int32)
                        const value_value_0_0  = value_value_0 as Color
                        thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                    }
                    else if (RuntimeType.NUMBER == value_value_0_type) {
                        thisSerializer.writeInt8(1 as int32)
                        const value_value_0_1  = value_value_0 as number
                        thisSerializer.writeNumber(value_value_0_1)
                    }
                    else if (RuntimeType.STRING == value_value_0_type) {
                        thisSerializer.writeInt8(2 as int32)
                        const value_value_0_2  = value_value_0 as string
                        thisSerializer.writeString(value_value_0_2)
                    }
                    else if (RuntimeType.OBJECT == value_value_0_type) {
                        thisSerializer.writeInt8(3 as int32)
                        const value_value_0_3  = value_value_0 as Resource
                        thisSerializer.writeResource(value_value_0_3)
                    }
                }
            }
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    styleAttribute(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isLinearStyleOptions(value_value, true, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as LinearStyleOptions
                thisSerializer.writeLinearStyleOptions(value_value_0)
            }
            else if (TypeChecker.isRingStyleOptions(value_value, true, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as RingStyleOptions
                thisSerializer.writeRingStyleOptions(value_value_1)
            }
            else if (TypeChecker.isCapsuleStyleOptions(value_value, false, false, false, false, false, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as CapsuleStyleOptions
                thisSerializer.writeCapsuleStyleOptions(value_value_2)
            }
            else if (TypeChecker.isProgressStyleOptions(value_value, true, false, false)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as ProgressStyleOptions
                thisSerializer.writeProgressStyleOptions(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_style(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_privacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._ProgressAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ProgressOptions {
    value: number;
    total?: number;
    type?: ProgressType;
}
export enum ProgressType {
    LINEAR = 0,
    Linear = 0,
    RING = 1,
    Ring = 1,
    ECLIPSE = 2,
    Eclipse = 2,
    SCALE_RING = 3,
    ScaleRing = 3,
    CAPSULE = 4,
    Capsule = 4
}
export enum ProgressStatus {
    LOADING = 0,
    PROGRESSING = 1
}
export interface ProgressStyleOptions extends CommonProgressStyleOptions {
    strokeWidth?: Length;
    scaleCount?: number;
    scaleWidth?: Length;
}
export interface CommonProgressStyleOptions {
    enableSmoothEffect?: boolean;
}
export interface ScanEffectOptions {
    enableScanEffect?: boolean;
}
export interface EclipseStyleOptions extends CommonProgressStyleOptions {
}
export interface ScaleRingStyleOptions extends CommonProgressStyleOptions {
    strokeWidth?: Length;
    scaleWidth?: Length;
    scaleCount?: number;
}
export interface RingStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    strokeWidth?: Length;
    shadow?: boolean;
    status?: ProgressStatus;
}
export interface LinearStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    strokeWidth?: Length;
    strokeRadius?: PX | VP | LPX | Resource;
}
export interface CapsuleStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    borderColor?: ResourceColor;
    borderWidth?: Length;
    content?: string;
    font?: Font;
    fontColor?: ResourceColor;
    showDefaultPercentage?: boolean;
    borderRadius?: LengthMetrics;
}
export enum ProgressStyle {
    LINEAR = 0,
    Linear = 0,
    RING = 1,
    Ring = 1,
    ECLIPSE = 2,
    Eclipse = 2,
    SCALE_RING = 3,
    ScaleRing = 3,
    CAPSULE = 4,
    Capsule = 4
}
export interface ProgressStyleMap {
}
export type ProgressInterface = (options: ProgressOptions) => ProgressAttribute;
export interface ProgressAttribute extends CommonMethod {
    value(value: number | undefined): this
    color(value: ResourceColor | LinearGradient | undefined): this
    style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this
    privacySensitive(value: boolean | undefined): this
    contentModifier(value: ContentModifier | undefined): this
}
export class ArkProgressStyle extends ArkCommonMethodStyle implements ProgressAttribute {
    value_value?: number | undefined
    color_value?: ResourceColor | LinearGradient | undefined
    style_value?: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined
    privacySensitive_value?: boolean | undefined
    contentModifier_value?: ContentModifier | undefined
    public value(value: number | undefined): this {
        return this
    }
    public color(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    public style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        return this
        }
}
export interface ProgressConfiguration extends CommonConfiguration {
    value: number;
    total: number;
}
export class ArkProgressComponent extends ArkCommonMethodComponent implements ProgressAttribute {
    getPeer(): ArkProgressPeer {
        return (this.peer as ArkProgressPeer)
    }
    public setProgressOptions(options: ProgressOptions): this {
        if (this.checkPriority("setProgressOptions")) {
            const options_casted = options as (ProgressOptions)
            this.getPeer()?.setProgressOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public value(value: number | undefined): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.valueAttribute(value_casted)
            return this
        }
        return this
    }
    public color(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.colorAttribute(value_casted)
            return this
        }
        return this
    }
    public style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined)
            this.getPeer()?.styleAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier | undefined)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Progress(
    /** @memo */
    style: ((attributes: ProgressAttribute) => void) | undefined,
    options: ProgressOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkProgressComponent()
    })
    NodeAttach<ArkProgressPeer>((): ArkProgressPeer => ArkProgressPeer.create(receiver), (_: ArkProgressPeer) => {
        receiver.setProgressOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
