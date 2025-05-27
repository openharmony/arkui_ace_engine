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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Length, ResourceColor } from "./units"
import { Callback_Number_Void } from "./alphabet_indexer"
import { Resource } from "./resource"
import { Color } from "./enums"
import { LengthMetrics } from "./arkui-graphics"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class PatternLockControllerInternal {
    public static fromPtr(ptr: KPointer): PatternLockController {
        const obj : PatternLockController = new PatternLockController()
        obj.peer = new Finalizable(ptr, PatternLockController.getFinalizer())
        return obj
    }
}
export class PatternLockController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_patternlockcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PatternLockController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = PatternLockController.ctor_patternlockcontroller()
        this.peer = new Finalizable(ctorPtr, PatternLockController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PatternLockController_getFinalizer()
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    public setChallengeResult(result: PatternLockChallengeResult): void {
        const result_casted = result as (PatternLockChallengeResult)
        this.setChallengeResult_serialize(result_casted)
        return
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._PatternLockController_reset(this.peer!.ptr)
    }
    private setChallengeResult_serialize(result: PatternLockChallengeResult): void {
        ArkUIGeneratedNativeModule._PatternLockController_setChallengeResult(this.peer!.ptr, TypeChecker.PatternLockChallengeResult_ToNumeric(result))
    }
}
export class ArkPatternLockPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPatternLockPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._PatternLock_construct(peerId, flags)
        const _peer  = new ArkPatternLockPeer(_peerPtr, peerId, "PatternLock", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPatternLockOptionsAttribute(controller?: PatternLockController): void {
        const thisSerializer : Serializer = Serializer.hold()
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8(controller_type as int32)
        if ((RuntimeType.UNDEFINED) != (controller_type)) {
            const controller_value  = controller!
            thisSerializer.writePatternLockController(controller_value)
        }
        ArkUIGeneratedNativeModule._PatternLockInterface_setPatternLockOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sideLengthAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_sideLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    circleRadiusAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_circleRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_backgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    regularColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_regularColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    activeColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_activeColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pathColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_pathColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pathStrokeWidthAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_pathStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPatternCompleteAttribute(value: ((input: Array<number>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._PatternLockAttribute_onPatternComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoResetAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._PatternLockAttribute_autoReset(this.peer.ptr, value ? 1 : 0)
    }
    onDotConnectAttribute(value: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._PatternLockAttribute_onDotConnect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    activateCircleStyleAttribute(value: CircleStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeCircleStyleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_activateCircleStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum PatternLockChallengeResult {
    CORRECT = 1,
    WRONG = 2
}
export interface CircleStyleOptions {
    color?: ResourceColor;
    radius?: LengthMetrics;
    enableWaveEffect?: boolean;
}

export type Callback_Array_Number_Void = (input: Array<number>) => void;
export interface PatternLockAttribute extends CommonMethod {
    sideLength(value: Length): this
    circleRadius(value: Length): this
    backgroundColor(value: ResourceColor): this
    regularColor(value: ResourceColor): this
    selectedColor(value: ResourceColor): this
    activeColor(value: ResourceColor): this
    pathColor(value: ResourceColor): this
    pathStrokeWidth(value: number | string): this
    onPatternComplete(value: ((input: Array<number>) => void)): this
    autoReset(value: boolean): this
    onDotConnect(value: ((index: number) => void)): this
    activateCircleStyle(value: CircleStyleOptions | undefined): this
    attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIPatternLockAttribute extends UICommonMethod {
    /** @memo */
    sideLength(value: Length): this
    /** @memo */
    circleRadius(value: Length): this
    /** @memo */
    backgroundColor(value: ResourceColor): this
    /** @memo */
    regularColor(value: ResourceColor): this
    /** @memo */
    selectedColor(value: ResourceColor): this
    /** @memo */
    activeColor(value: ResourceColor): this
    /** @memo */
    pathColor(value: ResourceColor): this
    /** @memo */
    pathStrokeWidth(value: number | string): this
    /** @memo */
    onPatternComplete(value: ((input: Array<number>) => void)): this
    /** @memo */
    autoReset(value: boolean): this
    /** @memo */
    onDotConnect(value: ((index: number) => void)): this
    /** @memo */
    activateCircleStyle(value: CircleStyleOptions | undefined): this
    /** @memo */
    attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkPatternLockStyle extends ArkCommonMethodStyle implements PatternLockAttribute {
    sideLength_value?: Length
    circleRadius_value?: Length
    backgroundColor_value?: ResourceColor
    regularColor_value?: ResourceColor
    selectedColor_value?: ResourceColor
    activeColor_value?: ResourceColor
    pathColor_value?: ResourceColor
    pathStrokeWidth_value?: number | string
    onPatternComplete_value?: ((input: Array<number>) => void)
    autoReset_value?: boolean
    onDotConnect_value?: ((index: number) => void)
    activateCircleStyle_value?: CircleStyleOptions | undefined
    public sideLength(value: Length): this {
        return this
    }
    public circleRadius(value: Length): this {
        return this
    }
    public backgroundColor(value: ResourceColor): this {
        return this
    }
    public regularColor(value: ResourceColor): this {
        return this
    }
    public selectedColor(value: ResourceColor): this {
        return this
    }
    public activeColor(value: ResourceColor): this {
        return this
    }
    public pathColor(value: ResourceColor): this {
        return this
    }
    public pathStrokeWidth(value: number | string): this {
        return this
    }
    public onPatternComplete(value: ((input: Array<number>) => void)): this {
        return this
    }
    public autoReset(value: boolean): this {
        return this
    }
    public onDotConnect(value: ((index: number) => void)): this {
        return this
    }
    public activateCircleStyle(value: CircleStyleOptions | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkPatternLockComponent extends ArkCommonMethodComponent implements UIPatternLockAttribute {
    getPeer(): ArkPatternLockPeer {
        return (this.peer as ArkPatternLockPeer)
    }
    /** @memo */
    public setPatternLockOptions(controller?: PatternLockController): this {
        if (this.checkPriority("setPatternLockOptions")) {
            const controller_casted = controller as (PatternLockController | undefined)
            this.getPeer()?.setPatternLockOptionsAttribute(controller_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sideLength(value: Length): this {
        if (this.checkPriority("sideLength")) {
            const value_casted = value as (Length)
            this.getPeer()?.sideLengthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public circleRadius(value: Length): this {
        if (this.checkPriority("circleRadius")) {
            const value_casted = value as (Length)
            this.getPeer()?.circleRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundColor(value: ResourceColor): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public regularColor(value: ResourceColor): this {
        if (this.checkPriority("regularColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.regularColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedColor(value: ResourceColor): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public activeColor(value: ResourceColor): this {
        if (this.checkPriority("activeColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.activeColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pathColor(value: ResourceColor): this {
        if (this.checkPriority("pathColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.pathColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pathStrokeWidth(value: number | string): this {
        if (this.checkPriority("pathStrokeWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.pathStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPatternComplete(value: ((input: Array<number>) => void)): this {
        if (this.checkPriority("onPatternComplete")) {
            const value_casted = value as (((input: Array<number>) => void))
            this.getPeer()?.onPatternCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoReset(value: boolean): this {
        if (this.checkPriority("autoReset")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoResetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDotConnect(value: ((index: number) => void)): this {
        if (this.checkPriority("onDotConnect")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onDotConnectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public activateCircleStyle(value: CircleStyleOptions | undefined): this {
        if (this.checkPriority("activateCircleStyle")) {
            const value_casted = value as (CircleStyleOptions | undefined)
            this.getPeer()?.activateCircleStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkPatternLock(
    /** @memo */
    style: ((attributes: UIPatternLockAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    controller?: PatternLockController,
): void {
    const receiver = remember(() => {
        return new ArkPatternLockComponent()
    })
    NodeAttach<ArkPatternLockPeer>((): ArkPatternLockPeer => ArkPatternLockPeer.create(receiver), (_: ArkPatternLockPeer) => {
        receiver.setPatternLockOptions(controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
