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
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Length, ResourceColor } from "./units"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
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
    constructor() {
        this(PatternLockController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PatternLockController_construct()
        return retval
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
        thisSerializer.writeInt8((controller_type).toChar())
        if ((controller_type) != (RuntimeType.UNDEFINED)) {
            const controller_value  = controller!
            PatternLockController_serializer.write(thisSerializer, controller_value)
        }
        ArkUIGeneratedNativeModule._PatternLockInterface_setPatternLockOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSideLengthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setSideLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCircleRadiusAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setCircleRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRegularColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setRegularColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setActiveColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setActiveColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPathColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setPathColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPathStrokeWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setPathStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPatternCompleteAttribute(value: ((input: Array<number>) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setOnPatternComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoResetAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setAutoReset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDotConnectAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setOnDotConnect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setActivateCircleStyleAttribute(value: CircleStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            CircleStyleOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setActivateCircleStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSkipUnselectedPointAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setSkipUnselectedPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    sideLength(value: Length | undefined): this {
        throw new Error("Unimplemented method sideLength")
    }
    circleRadius(value: Length | undefined): this {
        throw new Error("Unimplemented method circleRadius")
    }
    backgroundColor(value: ResourceColor | undefined): this
    regularColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method regularColor")
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    activeColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method activeColor")
    }
    pathColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method pathColor")
    }
    pathStrokeWidth(value: number | string | undefined): this {
        throw new Error("Unimplemented method pathStrokeWidth")
    }
    onPatternComplete(value: ((input: Array<number>) => void) | undefined): this {
        throw new Error("Unimplemented method onPatternComplete")
    }
    autoReset(value: boolean | undefined): this {
        throw new Error("Unimplemented method autoReset")
    }
    onDotConnect(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onDotConnect")
    }
    activateCircleStyle(value: CircleStyleOptions | undefined): this {
        throw new Error("Unimplemented method activateCircleStyle")
    }
    skipUnselectedPoint(value: boolean | undefined): this {
        throw new Error("Unimplemented method skipUnselectedPoint")
    }
    attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
            this.getPeer()?.setSideLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public circleRadius(value: Length | undefined): this {
        if (this.checkPriority("circleRadius")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setCircleRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public regularColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("regularColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setRegularColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public activeColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("activeColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setActiveColorAttribute(value_casted)
            return this
        }
        return this
    }
    public pathColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("pathColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPathColorAttribute(value_casted)
            return this
        }
        return this
    }
    public pathStrokeWidth(value: number | string | undefined): this {
        if (this.checkPriority("pathStrokeWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.setPathStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public onPatternComplete(value: ((input: Array<number>) => void) | undefined): this {
        if (this.checkPriority("onPatternComplete")) {
            const value_casted = value as (((input: Array<number>) => void) | undefined)
            this.getPeer()?.setOnPatternCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public autoReset(value: boolean | undefined): this {
        if (this.checkPriority("autoReset")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoResetAttribute(value_casted)
            return this
        }
        return this
    }
    public onDotConnect(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onDotConnect")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnDotConnectAttribute(value_casted)
            return this
        }
        return this
    }
    public activateCircleStyle(value: CircleStyleOptions | undefined): this {
        if (this.checkPriority("activateCircleStyle")) {
            const value_casted = value as (CircleStyleOptions | undefined)
            this.getPeer()?.setActivateCircleStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public skipUnselectedPoint(value: boolean | undefined): this {
        if (this.checkPriority("skipUnselectedPoint")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSkipUnselectedPointAttribute(value_casted)
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("PatternLock")
// export function PatternLock(
//     controller?: PatternLockController,
//     @memo
//     content_?: () => void,
// ): PatternLockAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function PatternLock(
    @memo
    style: ((attributes: PatternLockAttribute) => void) | undefined,
    controller?: PatternLockController,
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

export class ArkPatternLockSet extends ArkCommonMethodSet implements PatternLockAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _sideLength_flag?: boolean
    _sideLength0_value?: Length | undefined
    _circleRadius_flag?: boolean
    _circleRadius0_value?: Length | undefined
    _backgroundColor_flag?: boolean
    _backgroundColor0_value?: ResourceColor | undefined
    _regularColor_flag?: boolean
    _regularColor0_value?: ResourceColor | undefined
    _selectedColor_flag?: boolean
    _selectedColor0_value?: ResourceColor | undefined
    _activeColor_flag?: boolean
    _activeColor0_value?: ResourceColor | undefined
    _pathColor_flag?: boolean
    _pathColor0_value?: ResourceColor | undefined
    _pathStrokeWidth_flag?: boolean
    _pathStrokeWidth0_value?: number | string | undefined
    _onPatternComplete_flag?: boolean
    _onPatternComplete0_value?: ((input: Array<number>) => void) | undefined
    _autoReset_flag?: boolean
    _autoReset0_value?: boolean | undefined
    _onDotConnect_flag?: boolean
    _onDotConnect0_value?: ((value0: number) => void) | undefined
    _activateCircleStyle_flag?: boolean
    _activateCircleStyle0_value?: CircleStyleOptions | undefined
    _skipUnselectedPoint_flag?: boolean
    _skipUnselectedPoint0_value?: boolean | undefined
    applyModifierPatch(component: PatternLockAttribute): void {
        if (this._sideLength_flag)
            component.sideLength((this._sideLength0_value as Length | undefined))
        if (this._circleRadius_flag)
            component.circleRadius((this._circleRadius0_value as Length | undefined))
        if (this._backgroundColor_flag)
            component.backgroundColor((this._backgroundColor0_value as ResourceColor | undefined))
        if (this._regularColor_flag)
            component.regularColor((this._regularColor0_value as ResourceColor | undefined))
        if (this._selectedColor_flag)
            component.selectedColor((this._selectedColor0_value as ResourceColor | undefined))
        if (this._activeColor_flag)
            component.activeColor((this._activeColor0_value as ResourceColor | undefined))
        if (this._pathColor_flag)
            component.pathColor((this._pathColor0_value as ResourceColor | undefined))
        if (this._pathStrokeWidth_flag)
            component.pathStrokeWidth((this._pathStrokeWidth0_value as number | string | undefined))
        if (this._onPatternComplete_flag)
            component.onPatternComplete((this._onPatternComplete0_value as ((input: Array<number>) => void) | undefined))
        if (this._autoReset_flag)
            component.autoReset((this._autoReset0_value as boolean | undefined))
        if (this._onDotConnect_flag)
            component.onDotConnect((this._onDotConnect0_value as ((value0: number) => void) | undefined))
        if (this._activateCircleStyle_flag)
            component.activateCircleStyle((this._activateCircleStyle0_value as CircleStyleOptions | undefined))
        if (this._skipUnselectedPoint_flag)
            component.skipUnselectedPoint((this._skipUnselectedPoint0_value as boolean | undefined))
    }
    public sideLength(value: Length | undefined): this {
        this._sideLength_flag = true
        this._sideLength0_value = value
        return this
    }
    public circleRadius(value: Length | undefined): this {
        this._circleRadius_flag = true
        this._circleRadius0_value = value
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        this._backgroundColor_flag = true
        this._backgroundColor0_value = value
        return this
    }
    public regularColor(value: ResourceColor | undefined): this {
        this._regularColor_flag = true
        this._regularColor0_value = value
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        this._selectedColor_flag = true
        this._selectedColor0_value = value
        return this
    }
    public activeColor(value: ResourceColor | undefined): this {
        this._activeColor_flag = true
        this._activeColor0_value = value
        return this
    }
    public pathColor(value: ResourceColor | undefined): this {
        this._pathColor_flag = true
        this._pathColor0_value = value
        return this
    }
    public pathStrokeWidth(value: number | string | undefined): this {
        this._pathStrokeWidth_flag = true
        this._pathStrokeWidth0_value = value
        return this
    }
    public onPatternComplete(value: ((input: Array<number>) => void) | undefined): this {
        this._onPatternComplete_flag = true
        this._onPatternComplete0_value = value
        return this
    }
    public autoReset(value: boolean | undefined): this {
        this._autoReset_flag = true
        this._autoReset0_value = value
        return this
    }
    public onDotConnect(value: ((value0: number) => void) | undefined): this {
        this._onDotConnect_flag = true
        this._onDotConnect0_value = value
        return this
    }
    public activateCircleStyle(value: CircleStyleOptions | undefined): this {
        this._activateCircleStyle_flag = true
        this._activateCircleStyle0_value = value
        return this
    }
    public skipUnselectedPoint(value: boolean | undefined): this {
        this._skipUnselectedPoint_flag = true
        this._skipUnselectedPoint0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        valueSerializer.writeInt8((value_radius_type).toChar())
        if ((value_radius_type) != (RuntimeType.UNDEFINED)) {
            const value_radius_value  = value_radius!
            LengthMetrics_serializer.write(valueSerializer, value_radius_value)
        }
        const value_enableWaveEffect  = value.enableWaveEffect
        let value_enableWaveEffect_type : int32 = RuntimeType.UNDEFINED
        value_enableWaveEffect_type = runtimeType(value_enableWaveEffect)
        valueSerializer.writeInt8((value_enableWaveEffect_type).toChar())
        if ((value_enableWaveEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_enableWaveEffect_value  = value_enableWaveEffect!
            valueSerializer.writeBoolean(value_enableWaveEffect_value)
        }
        const value_enableForeground  = value.enableForeground
        let value_enableForeground_type : int32 = RuntimeType.UNDEFINED
        value_enableForeground_type = runtimeType(value_enableForeground)
        valueSerializer.writeInt8((value_enableForeground_type).toChar())
        if ((value_enableForeground_type) != (RuntimeType.UNDEFINED)) {
            const value_enableForeground_value  = value_enableForeground!
            valueSerializer.writeBoolean(value_enableForeground_value)
        }
    }
    public static read(buffer: DeserializerBase): CircleStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const radius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radius_buf : LengthMetrics | undefined
        if ((radius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            radius_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const radius_result : LengthMetrics | undefined = radius_buf
        const enableWaveEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableWaveEffect_buf : boolean | undefined
        if ((enableWaveEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableWaveEffect_buf = valueDeserializer.readBoolean()
        }
        const enableWaveEffect_result : boolean | undefined = enableWaveEffect_buf
        const enableForeground_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableForeground_buf : boolean | undefined
        if ((enableForeground_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableForeground_buf = valueDeserializer.readBoolean()
        }
        const enableForeground_result : boolean | undefined = enableForeground_buf
        let value : CircleStyleOptions = ({color: color_result, radius: radius_result, enableWaveEffect: enableWaveEffect_result, enableForeground: enableForeground_result} as CircleStyleOptions)
        return value
    }
}
