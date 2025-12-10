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

import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { global_resource_Resource_serializer } from './../framework/resource'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkCommonMethodPeer, CommonMethod, Callback as arkui_component_common_Callback, ArkCommonMethodComponent } from './common'
import { Length, Resource as arkui_component_units_Resource, ResourceColor } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { Color as arkui_component_enums_Color } from './enums'
import { AttributeModifier, hookPatternLockAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from '@arkui.Graphics'
import { PatternLockModifier } from './../PatternLockModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
export class PatternLockControllerInternal {
    public static fromPtr(ptr: KPointer): PatternLockController {
        return new PatternLockController(MaterializedBaseTag.NOP, ptr)
    }
}
export class PatternLockController implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PatternLockController.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, PatternLockController.construct())
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
        ArkUIGeneratedNativeModule._PatternLockController_setChallengeResult(this.peer!.ptr, result.valueOf())
    }
}
export class ArkPatternLockPeer extends ArkCommonMethodPeer {
    attributeSet?: PatternLockModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setPathColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPathStrokeWidthAttribute(value: double | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PatternLockAttribute_setPathStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPatternCompleteAttribute(value: arkui_component_common_Callback<Array<int32>, void> | undefined): void {
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
    setOnDotConnectAttribute(value: arkui_component_common_Callback<int32, void> | undefined): void {
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
    radius?: arkui_Graphics_LengthMetrics;
    enableWaveEffect?: boolean;
    enableForeground?: boolean;
}
export interface PatternLockAttribute extends CommonMethod {
    setPatternLockOptions(controller?: PatternLockController): this {
        throw new Error('Unimplemented method setPatternLockOptions')
    }
    sideLength(value: Length | undefined): this {
        throw new Error('Unimplemented method sideLength')
    }
    circleRadius(value: Length | undefined): this {
        throw new Error('Unimplemented method circleRadius')
    }
    backgroundColor(value: ResourceColor | undefined): this
    regularColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method regularColor')
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method selectedColor')
    }
    activeColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method activeColor')
    }
    pathColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method pathColor')
    }
    pathStrokeWidth(value: double | string | undefined): this {
        throw new Error('Unimplemented method pathStrokeWidth')
    }
    onPatternComplete(value: arkui_component_common_Callback<Array<int32>, void> | undefined): this {
        throw new Error('Unimplemented method onPatternComplete')
    }
    autoReset(value: boolean | undefined): this {
        throw new Error('Unimplemented method autoReset')
    }
    onDotConnect(value: arkui_component_common_Callback<int32, void> | undefined): this {
        throw new Error('Unimplemented method onDotConnect')
    }
    activateCircleStyle(value: CircleStyleOptions | undefined): this {
        throw new Error('Unimplemented method activateCircleStyle')
    }
    skipUnselectedPoint(value: boolean | undefined): this {
        throw new Error('Unimplemented method skipUnselectedPoint')
    }
    attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkPatternLockComponent extends ArkCommonMethodComponent implements PatternLockAttribute {
    getPeer(): ArkPatternLockPeer {
        return (this.peer as ArkPatternLockPeer)
    }
    public setPatternLockOptions(controller?: PatternLockController): this {
        if (this.checkPriority('setPatternLockOptions')) {
            const controller_casted = controller as (PatternLockController | undefined)
            this.getPeer()?.setPatternLockOptionsAttribute(controller_casted)
            this.applyOptionsFinish('PatternLockAttribute');
            return this
        }
        return this
    }
    public sideLength(value: Length | undefined): this {
        if (this.checkPriority('sideLength')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setSideLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public circleRadius(value: Length | undefined): this {
        if (this.checkPriority('circleRadius')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setCircleRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('backgroundColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public regularColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('regularColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setRegularColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('selectedColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public activeColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('activeColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setActiveColorAttribute(value_casted)
            return this
        }
        return this
    }
    public pathColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('pathColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPathColorAttribute(value_casted)
            return this
        }
        return this
    }
    public pathStrokeWidth(value: double | string | undefined): this {
        if (this.checkPriority('pathStrokeWidth')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setPathStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public onPatternComplete(value: arkui_component_common_Callback<Array<int32>, void> | undefined): this {
        if (this.checkPriority('onPatternComplete')) {
            const value_casted = value as (arkui_component_common_Callback<Array<int32>, void> | undefined)
            this.getPeer()?.setOnPatternCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public autoReset(value: boolean | undefined): this {
        if (this.checkPriority('autoReset')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoResetAttribute(value_casted)
            return this
        }
        return this
    }
    public onDotConnect(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (this.checkPriority('onDotConnect')) {
            const value_casted = value as (arkui_component_common_Callback<int32, void> | undefined)
            this.getPeer()?.setOnDotConnectAttribute(value_casted)
            return this
        }
        return this
    }
    public activateCircleStyle(value: CircleStyleOptions | undefined): this {
        if (this.checkPriority('activateCircleStyle')) {
            const value_casted = value as (CircleStyleOptions | undefined)
            this.getPeer()?.setActivateCircleStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public skipUnselectedPoint(value: boolean | undefined): this {
        if (this.checkPriority('skipUnselectedPoint')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSkipUnselectedPointAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookPatternLockAttributeModifier(this, value);
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
export function PatternLockImpl(
    @memo @memo_skip
    style: ((attributes: PatternLockAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkPatternLockComponent>((): ArkPatternLockComponent => {
        return new ArkPatternLockComponent()
    })
    NodeAttach<ArkPatternLockPeer>((): ArkPatternLockPeer => ArkPatternLockPeer.create(receiver), (_: ArkPatternLockPeer): void => {
        style?.(receiver)
        content_?.()
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
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForRadiusTmpValue)
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
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = valueDeserializer.readInt32()
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (colorTmpBufOptUnionSelector == (3).toByte()) {
                colorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusTmpBuf : arkui_Graphics_LengthMetrics | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            radiusTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const radiusTmpResult : arkui_Graphics_LengthMetrics | undefined = radiusTmpBuf
        const enableWaveEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableWaveEffectTmpBuf : boolean | undefined = undefined
        if ((enableWaveEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableWaveEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const enableWaveEffectTmpResult : boolean | undefined = enableWaveEffectTmpBuf
        const enableForegroundTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableForegroundTmpBuf : boolean | undefined = undefined
        if ((enableForegroundTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableForegroundTmpBuf = valueDeserializer.readBoolean()
        }
        const enableForegroundTmpResult : boolean | undefined = enableForegroundTmpBuf
        let value : CircleStyleOptions = ({color: colorTmpResult, radius: radiusTmpResult, enableWaveEffect: enableWaveEffectTmpResult, enableForeground: enableForegroundTmpResult} as CircleStyleOptions)
        return value
    }
}
