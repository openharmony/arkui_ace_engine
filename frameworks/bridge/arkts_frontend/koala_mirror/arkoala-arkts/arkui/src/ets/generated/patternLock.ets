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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Length, ResourceColor } from "./units"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { LengthMetrics, LengthMetrics_serializer } from "./arkui.Graphics"
import { NodeAttach, remember } from "@koalaui/runtime"
export class PatternLockControllerInternal {
    public static fromPtr(ptr: KPointer): PatternLockController {
        return new PatternLockController(ptr)
    }
}
export class PatternLockController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PatternLockController.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PatternLockController_ctor()
        return retval
    }
    constructor() {
        this(PatternLockController.ctor())
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8(controller_type)
        if ((RuntimeType.UNDEFINED) != (controller_type)) {
            const controller_value  = controller!
            PatternLockController_serializer.write(thisSerializer, controller_value)
        }
        ArkUIGeneratedNativeModule._PatternLockInterface_setPatternLockOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sideLengthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_sideLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    circleRadiusAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_circleRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_backgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    regularColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_regularColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    activeColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_activeColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pathColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_pathColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pathStrokeWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_pathStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPatternCompleteAttribute(value: ((input: Array<number>) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_onPatternComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoResetAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_autoReset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDotConnectAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_onDotConnect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    activateCircleStyleAttribute(value: CircleStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            CircleStyleOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_activateCircleStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    skipUnselectedPointAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_skipUnselectedPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    enableForeground?: boolean;
}
export interface PatternLockAttribute extends CommonMethod {
    sideLength(value: Length | undefined): this
    circleRadius(value: Length | undefined): this
    backgroundColor(value: ResourceColor | undefined): this
    regularColor(value: ResourceColor | undefined): this
    selectedColor(value: ResourceColor | undefined): this
    activeColor(value: ResourceColor | undefined): this
    pathColor(value: ResourceColor | undefined): this
    pathStrokeWidth(value: number | string | undefined): this
    onPatternComplete(value: ((input: Array<number>) => void) | undefined): this
    autoReset(value: boolean | undefined): this
    onDotConnect(value: ((value0: number) => void) | undefined): this
    activateCircleStyle(value: CircleStyleOptions | undefined): this
    skipUnselectedPoint(value: boolean | undefined): this
    attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkPatternLockStyle extends ArkCommonMethodStyle implements PatternLockAttribute {
    sideLength_value?: Length | undefined
    circleRadius_value?: Length | undefined
    backgroundColor_value?: ResourceColor | undefined
    regularColor_value?: ResourceColor | undefined
    selectedColor_value?: ResourceColor | undefined
    activeColor_value?: ResourceColor | undefined
    pathColor_value?: ResourceColor | undefined
    pathStrokeWidth_value?: number | string | undefined
    onPatternComplete_value?: ((input: Array<number>) => void) | undefined
    autoReset_value?: boolean | undefined
    onDotConnect_value?: ((value0: number) => void) | undefined
    activateCircleStyle_value?: CircleStyleOptions | undefined
    skipUnselectedPoint_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined
    public sideLength(value: Length | undefined): this {
        return this
    }
    public circleRadius(value: Length | undefined): this {
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public regularColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public activeColor(value: ResourceColor | undefined): this {
        return this
    }
    public pathColor(value: ResourceColor | undefined): this {
        return this
    }
    public pathStrokeWidth(value: number | string | undefined): this {
        return this
    }
    public onPatternComplete(value: ((input: Array<number>) => void) | undefined): this {
        return this
    }
    public autoReset(value: boolean | undefined): this {
        return this
    }
    public onDotConnect(value: ((value0: number) => void) | undefined): this {
        return this
    }
    public activateCircleStyle(value: CircleStyleOptions | undefined): this {
        return this
    }
    public skipUnselectedPoint(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: PatternLockAttribute): void {
        super.apply(target)
        if (this.sideLength_value !== undefined)
            target.sideLength(this.sideLength_value!)
        if (this.circleRadius_value !== undefined)
            target.circleRadius(this.circleRadius_value!)
        if (this.backgroundColor_value !== undefined)
            target.backgroundColor(this.backgroundColor_value!)
        if (this.regularColor_value !== undefined)
            target.regularColor(this.regularColor_value!)
        if (this.selectedColor_value !== undefined)
            target.selectedColor(this.selectedColor_value!)
        if (this.activeColor_value !== undefined)
            target.activeColor(this.activeColor_value!)
        if (this.pathColor_value !== undefined)
            target.pathColor(this.pathColor_value!)
        if (this.pathStrokeWidth_value !== undefined)
            target.pathStrokeWidth(this.pathStrokeWidth_value!)
        if (this.onPatternComplete_value !== undefined)
            target.onPatternComplete(this.onPatternComplete_value!)
        if (this.autoReset_value !== undefined)
            target.autoReset(this.autoReset_value!)
        if (this.onDotConnect_value !== undefined)
            target.onDotConnect(this.onDotConnect_value!)
        if (this.activateCircleStyle_value !== undefined)
            target.activateCircleStyle(this.activateCircleStyle_value!)
        if (this.skipUnselectedPoint_value !== undefined)
            target.skipUnselectedPoint(this.skipUnselectedPoint_value!)
    }
}

export class ArkPatternLockComponent extends ArkCommonMethodComponent implements PatternLockAttribute {
    getPeer(): ArkPatternLockPeer {
        return (this.peer as ArkPatternLockPeer)
    }
    public setPatternLockOptions(controller?: PatternLockController): this {
        if (this.checkPriority("setPatternLockOptions")) {
            const controller_casted = controller as (PatternLockController | undefined)
            this.getPeer()?.setPatternLockOptionsAttribute(controller_casted)
            return this
        }
        return this
    }
    public sideLength(value: Length | undefined): this {
        if (this.checkPriority("sideLength")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.sideLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public circleRadius(value: Length | undefined): this {
        if (this.checkPriority("circleRadius")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.circleRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public regularColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("regularColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.regularColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public activeColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("activeColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.activeColorAttribute(value_casted)
            return this
        }
        return this
    }
    public pathColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("pathColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.pathColorAttribute(value_casted)
            return this
        }
        return this
    }
    public pathStrokeWidth(value: number | string | undefined): this {
        if (this.checkPriority("pathStrokeWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.pathStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public onPatternComplete(value: ((input: Array<number>) => void) | undefined): this {
        if (this.checkPriority("onPatternComplete")) {
            const value_casted = value as (((input: Array<number>) => void) | undefined)
            this.getPeer()?.onPatternCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public autoReset(value: boolean | undefined): this {
        if (this.checkPriority("autoReset")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.autoResetAttribute(value_casted)
            return this
        }
        return this
    }
    public onDotConnect(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onDotConnect")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.onDotConnectAttribute(value_casted)
            return this
        }
        return this
    }
    public activateCircleStyle(value: CircleStyleOptions | undefined): this {
        if (this.checkPriority("activateCircleStyle")) {
            const value_casted = value as (CircleStyleOptions | undefined)
            this.getPeer()?.activateCircleStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public skipUnselectedPoint(value: boolean | undefined): this {
        if (this.checkPriority("skipUnselectedPoint")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.skipUnselectedPointAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withPatternLockStyle(receiver: PatternLockAttribute, modifier: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkPatternLockStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("PatternLockImpl")
export function PatternLock(
    controller?: PatternLockController | undefined,
    @memo
    content_?: () => void,
): PatternLockAttribute {
    throw new Error("Not implemented")
}

@memo
export function PatternLockImpl(
    @memo
    style: ((attributes: PatternLockAttribute) => void) | undefined,
    controller?: PatternLockController | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPatternLockComponent>((): ArkPatternLockComponent => {
        return new ArkPatternLockComponent()
    })
    NodeAttach<ArkPatternLockPeer>((): ArkPatternLockPeer => ArkPatternLockPeer.create(receiver), (_: ArkPatternLockPeer): void => {
        receiver.setPatternLockOptions(controller)
        style?.(receiver)
        withPatternLockStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class PatternLockController_serializer {
    public static write(buffer: SerializerBase, value: PatternLockController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PatternLockController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PatternLockControllerInternal.fromPtr(ptr)
    }
}
export class CircleStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: CircleStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8(value_color_type)
        if ((RuntimeType.UNDEFINED) != (value_color_type)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8(0)
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8(1)
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8(2)
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8(3)
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        valueSerializer.writeInt8(value_radius_type)
        if ((RuntimeType.UNDEFINED) != (value_radius_type)) {
            const value_radius_value  = value_radius!
            LengthMetrics_serializer.write(valueSerializer, value_radius_value)
        }
        const value_enableWaveEffect  = value.enableWaveEffect
        let value_enableWaveEffect_type : int32 = RuntimeType.UNDEFINED
        value_enableWaveEffect_type = runtimeType(value_enableWaveEffect)
        valueSerializer.writeInt8(value_enableWaveEffect_type)
        if ((RuntimeType.UNDEFINED) != (value_enableWaveEffect_type)) {
            const value_enableWaveEffect_value  = value_enableWaveEffect!
            valueSerializer.writeBoolean(value_enableWaveEffect_value)
        }
        const value_enableForeground  = value.enableForeground
        let value_enableForeground_type : int32 = RuntimeType.UNDEFINED
        value_enableForeground_type = runtimeType(value_enableForeground)
        valueSerializer.writeInt8(value_enableForeground_type)
        if ((RuntimeType.UNDEFINED) != (value_enableForeground_type)) {
            const value_enableForeground_value  = value_enableForeground!
            valueSerializer.writeBoolean(value_enableForeground_value)
        }
    }
    public static read(buffer: DeserializerBase): CircleStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const color_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let color_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (color_buf_runtimeType))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == 0) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == 1) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == 2) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == 3) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const radius_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let radius_buf : LengthMetrics | undefined
        if ((RuntimeType.UNDEFINED) != (radius_buf_runtimeType))
        {
            radius_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const radius_result : LengthMetrics | undefined = radius_buf
        const enableWaveEffect_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let enableWaveEffect_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (enableWaveEffect_buf_runtimeType))
        {
            enableWaveEffect_buf = valueDeserializer.readBoolean()
        }
        const enableWaveEffect_result : boolean | undefined = enableWaveEffect_buf
        const enableForeground_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let enableForeground_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (enableForeground_buf_runtimeType))
        {
            enableForeground_buf = valueDeserializer.readBoolean()
        }
        const enableForeground_result : boolean | undefined = enableForeground_buf
        let value : CircleStyleOptions = ({color: color_result, radius: radius_result, enableWaveEffect: enableWaveEffect_result, enableForeground: enableForeground_result} as CircleStyleOptions)
        return value
    }
}
