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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { Length, ResourceColor } from "./units"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
        const _peer  = new ArkPatternLockPeer(_peerPtr, peerId, 'PatternLock', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPatternLockOptionsAttribute(controller?: PatternLockController): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (controller !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const controllerTmpValue  = controller!
            PatternLockController_serializer.write(thisSerializer, controllerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockInterface_setPatternLockOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSideLengthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setSideLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCircleRadiusAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setCircleRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRegularColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setRegularColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setActiveColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setActiveColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPathColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setPathColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPathStrokeWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setPathStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPatternCompleteAttribute(value: ((input: Array<number>) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setOnPatternComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoResetAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setAutoReset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDotConnectAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setOnDotConnect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setActivateCircleStyleAttribute(value: CircleStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            CircleStyleOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setActivateCircleStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSkipUnselectedPointAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class PatternLockModifier extends CommonMethodModifier implements PatternLockAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _sideLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideLength_0_0value?: Length | undefined
    _circleRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _circleRadius_0_0value?: Length | undefined
    _backgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundColor_0_0value?: ResourceColor | undefined
    _regularColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _regularColor_0_0value?: ResourceColor | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _activeColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _activeColor_0_0value?: ResourceColor | undefined
    _pathColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pathColor_0_0value?: ResourceColor | undefined
    _pathStrokeWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pathStrokeWidth_0_0value?: number | string | undefined
    _onPatternComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPatternComplete_0_0value?: ((input: Array<number>) => void) | undefined
    _autoReset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoReset_0_0value?: boolean | undefined
    _onDotConnect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDotConnect_0_0value?: ((value0: number) => void) | undefined
    _activateCircleStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _activateCircleStyle_0_0value?: CircleStyleOptions | undefined
    _skipUnselectedPoint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _skipUnselectedPoint_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkPatternLockPeer): void {
        super.applyModifierPatch(peer)
        if (this._sideLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSideLengthAttribute((this._sideLength_0_0value as Length | undefined));
                    this._sideLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSideLengthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._circleRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._circleRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCircleRadiusAttribute((this._circleRadius_0_0value as Length | undefined));
                    this._circleRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._circleRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._circleRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCircleRadiusAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._backgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundColorAttribute((this._backgroundColor_0_0value as ResourceColor | undefined));
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._regularColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._regularColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRegularColorAttribute((this._regularColor_0_0value as ResourceColor | undefined));
                    this._regularColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._regularColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._regularColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRegularColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._activeColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._activeColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setActiveColorAttribute((this._activeColor_0_0value as ResourceColor | undefined));
                    this._activeColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._activeColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._activeColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setActiveColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._pathColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pathColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPathColorAttribute((this._pathColor_0_0value as ResourceColor | undefined));
                    this._pathColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pathColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pathColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPathColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._pathStrokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pathStrokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPathStrokeWidthAttribute((this._pathStrokeWidth_0_0value as number | string | undefined));
                    this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPathStrokeWidthAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._onPatternComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPatternComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPatternCompleteAttribute((this._onPatternComplete_0_0value as ((input: Array<number>) => void) | undefined));
                    this._onPatternComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPatternComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPatternComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPatternCompleteAttribute((undefined as ((input: Array<number>) => void) | undefined));
                }
            }
        }
        if (this._autoReset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoReset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoResetAttribute((this._autoReset_0_0value as boolean | undefined));
                    this._autoReset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoReset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoReset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoResetAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onDotConnect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDotConnect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDotConnectAttribute((this._onDotConnect_0_0value as ((value0: number) => void) | undefined));
                    this._onDotConnect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDotConnect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDotConnect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDotConnectAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._activateCircleStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._activateCircleStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setActivateCircleStyleAttribute((this._activateCircleStyle_0_0value as CircleStyleOptions | undefined));
                    this._activateCircleStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._activateCircleStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._activateCircleStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setActivateCircleStyleAttribute((undefined as CircleStyleOptions | undefined));
                }
            }
        }
        if (this._skipUnselectedPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._skipUnselectedPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSkipUnselectedPointAttribute((this._skipUnselectedPoint_0_0value as boolean | undefined));
                    this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSkipUnselectedPointAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PatternLockModifier): void {
        super.mergeModifier(modifier)
        if (modifier._sideLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sideLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sideLength(modifier._sideLength_0_0value);
                    break;
                }
                default: {
                    this.sideLength((undefined as Length | undefined));
                }
            }
        }
        if (modifier._circleRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._circleRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.circleRadius(modifier._circleRadius_0_0value);
                    break;
                }
                default: {
                    this.circleRadius((undefined as Length | undefined));
                }
            }
        }
        if (modifier._backgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundColor(modifier._backgroundColor_0_0value);
                    break;
                }
                default: {
                    this.backgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._regularColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._regularColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.regularColor(modifier._regularColor_0_0value);
                    break;
                }
                default: {
                    this.regularColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._activeColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._activeColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.activeColor(modifier._activeColor_0_0value);
                    break;
                }
                default: {
                    this.activeColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._pathColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pathColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pathColor(modifier._pathColor_0_0value);
                    break;
                }
                default: {
                    this.pathColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._pathStrokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pathStrokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pathStrokeWidth(modifier._pathStrokeWidth_0_0value);
                    break;
                }
                default: {
                    this.pathStrokeWidth((undefined as number | string | undefined));
                }
            }
        }
        if (modifier._onPatternComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPatternComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPatternComplete(modifier._onPatternComplete_0_0value);
                    break;
                }
                default: {
                    this.onPatternComplete((undefined as ((input: Array<number>) => void) | undefined));
                }
            }
        }
        if (modifier._autoReset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoReset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoReset(modifier._autoReset_0_0value);
                    break;
                }
                default: {
                    this.autoReset((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onDotConnect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDotConnect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDotConnect(modifier._onDotConnect_0_0value);
                    break;
                }
                default: {
                    this.onDotConnect((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._activateCircleStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._activateCircleStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.activateCircleStyle(modifier._activateCircleStyle_0_0value);
                    break;
                }
                default: {
                    this.activateCircleStyle((undefined as CircleStyleOptions | undefined));
                }
            }
        }
        if (modifier._skipUnselectedPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._skipUnselectedPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.skipUnselectedPoint(modifier._skipUnselectedPoint_0_0value);
                    break;
                }
                default: {
                    this.skipUnselectedPoint((undefined as boolean | undefined));
                }
            }
        }
    }
    sideLength(value: Length | undefined): this {
        if (((this._sideLength_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sideLength_0_flag = AttributeUpdaterFlag.UPDATE
            this._sideLength_0_0value = value
        } else
        {
            this._sideLength_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    circleRadius(value: Length | undefined): this {
        if (((this._circleRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._circleRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._circleRadius_0_0value = value
        } else
        {
            this._circleRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        if (((this._backgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundColor_0_0value = value
        } else
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    regularColor(value: ResourceColor | undefined): this {
        if (((this._regularColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._regularColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._regularColor_0_0value = value
        } else
        {
            this._regularColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._selectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedColor_0_0value = value
        } else
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    activeColor(value: ResourceColor | undefined): this {
        if (((this._activeColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._activeColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._activeColor_0_0value = value
        } else
        {
            this._activeColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pathColor(value: ResourceColor | undefined): this {
        if (((this._pathColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pathColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._pathColor_0_0value = value
        } else
        {
            this._pathColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pathStrokeWidth(value: number | string | undefined): this {
        if (((this._pathStrokeWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._pathStrokeWidth_0_0value) !== (value)))
        {
            this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._pathStrokeWidth_0_0value = value
        } else
        {
            this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPatternComplete(value: ((input: Array<number>) => void) | undefined): this {
        if (((this._onPatternComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPatternComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPatternComplete_0_0value = value
        } else
        {
            this._onPatternComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoReset(value: boolean | undefined): this {
        if (((this._autoReset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoReset_0_0value) !== (value)))
        {
            this._autoReset_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoReset_0_0value = value
        } else
        {
            this._autoReset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDotConnect(value: ((value0: number) => void) | undefined): this {
        if (((this._onDotConnect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDotConnect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDotConnect_0_0value = value
        } else
        {
            this._onDotConnect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    activateCircleStyle(value: CircleStyleOptions | undefined): this {
        if (((this._activateCircleStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._activateCircleStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._activateCircleStyle_0_0value = value
        } else
        {
            this._activateCircleStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    skipUnselectedPoint(value: boolean | undefined): this {
        if (((this._skipUnselectedPoint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._skipUnselectedPoint_0_0value) !== (value)))
        {
            this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.UPDATE
            this._skipUnselectedPoint_0_0value = value
        } else
        {
            this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.SKIP
        }
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
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForColorTmpValueForIdx0))
            } else if (valueHolderForColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForRadiusTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableWaveEffect  = value.enableWaveEffect
        if (valueHolderForEnableWaveEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableWaveEffectTmpValue  = valueHolderForEnableWaveEffect!
            valueSerializer.writeBoolean(valueHolderForEnableWaveEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableForeground  = value.enableForeground
        if (valueHolderForEnableForeground !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableForegroundTmpValue  = valueHolderForEnableForeground!
            valueSerializer.writeBoolean(valueHolderForEnableForegroundTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CircleStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | number | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | number | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : LengthMetrics | undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            radiusTmpBuf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const radiusTmpResult : LengthMetrics | undefined = radiusTmpBuf
        const enableWaveEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableWaveEffectTmpBuf : boolean | undefined
        if ((enableWaveEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableWaveEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableWaveEffectTmpResult : boolean | undefined = enableWaveEffectTmpBuf
        const enableForegroundTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableForegroundTmpBuf : boolean | undefined
        if ((enableForegroundTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableForegroundTmpBuf = valueDeserializer.readBoolean()
        }
        const enableForegroundTmpResult : boolean | undefined = enableForegroundTmpBuf
        let value : CircleStyleOptions = ({color: colorTmpResult, radius: radiusTmpResult, enableWaveEffect: enableWaveEffectTmpResult, enableForeground: enableForegroundTmpResult} as CircleStyleOptions)
        return value
    }
}
