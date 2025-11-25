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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookLinearIndicatorAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { LengthMetrics, ColorMetrics } from "arkui.Graphics"
import { LinearIndicatorModifier } from "./../LinearIndicatorModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics_serializer, ColorMetrics_serializer } from "./../Graphics"
export class LinearIndicatorControllerInternal {
    public static fromPtr(ptr: KPointer): LinearIndicatorController {
        return new LinearIndicatorController(ptr)
    }
}
export class LinearIndicatorController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LinearIndicatorController.getFinalizer())
    }
    constructor() {
        this(LinearIndicatorController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LinearIndicatorController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LinearIndicatorController_getFinalizer()
    }
    public setProgress(index: number, progress: number): void {
        const index_casted = index as (number)
        const progress_casted = progress as (number)
        this.setProgress_serialize(index_casted, progress_casted)
        return
    }
    public start(options?: LinearIndicatorStartOptions): void {
        const options_casted = options as (LinearIndicatorStartOptions | undefined)
        this.start_serialize(options_casted)
        return
    }
    public pause(): void {
        this.pause_serialize()
        return
    }
    public stop(): void {
        this.stop_serialize()
        return
    }
    setProgress_serialize(index: number, progress: number): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_setProgress(this.peer!.ptr, index, progress)
    }
    start_serialize(options?: LinearIndicatorStartOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            LinearIndicatorStartOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorController_start(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pause_serialize(): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_pause(this.peer!.ptr)
    }
    stop_serialize(): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_stop(this.peer!.ptr)
    }
}
export class ArkLinearIndicatorPeer extends ArkCommonMethodPeer {
    attributeSet?: LinearIndicatorModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLinearIndicatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LinearIndicator_construct(peerId, flags)
        const _peer  = new ArkLinearIndicatorPeer(_peerPtr, peerId, 'LinearIndicator', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLinearIndicatorOptionsAttribute(count?: number, controller?: LinearIndicatorController): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue  = count!
            thisSerializer.writeNumber(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (controller !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const controllerTmpValue  = controller!
            LinearIndicatorController_serializer.write(thisSerializer, controllerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorInterface_setLinearIndicatorOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorStyleAttribute(value: LinearIndicatorStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            LinearIndicatorStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorAttribute_setIndicatorStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorAttribute_setIndicatorLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnLinearIndicatorChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface LinearIndicatorStartOptions {
    interval?: number;
    duration?: number;
}
export interface LinearIndicatorStyle {
    space?: LengthMetrics;
    strokeWidth?: LengthMetrics;
    strokeRadius?: LengthMetrics;
    trackBackgroundColor?: ColorMetrics;
    trackColor?: ColorMetrics;
}
export interface LinearIndicatorAttribute extends CommonMethod {
    setLinearIndicatorOptions(count?: number, controller?: LinearIndicatorController): this {
        throw new Error("Unimplemented method setLinearIndicatorOptions")
    }
    indicatorStyle(value: LinearIndicatorStyle | undefined): this {
        throw new Error("Unimplemented method indicatorStyle")
    }
    indicatorLoop(value: boolean | undefined): this {
        throw new Error("Unimplemented method indicatorLoop")
    }
    onChange(value: OnLinearIndicatorChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    attributeModifier(value: AttributeModifier<LinearIndicatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkLinearIndicatorStyle extends ArkCommonMethodStyle implements LinearIndicatorAttribute {
    indicatorStyle_value?: LinearIndicatorStyle | undefined
    indicatorLoop_value?: boolean | undefined
    onChange_value?: OnLinearIndicatorChangeCallback | undefined
    attributeModifier_value?: AttributeModifier<LinearIndicatorAttribute> | AttributeModifier<CommonMethod> | undefined
    setLinearIndicatorOptions(count?: number, controller?: LinearIndicatorController): this {
        return this
    }
    indicatorStyle(value: LinearIndicatorStyle | undefined): this {
        return this
    }
    indicatorLoop(value: boolean | undefined): this {
        return this
    }
    onChange(value: OnLinearIndicatorChangeCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<LinearIndicatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export type OnLinearIndicatorChangeCallback = (index: number, progress: number) => void;

export class ArkLinearIndicatorComponent extends ArkCommonMethodComponent implements LinearIndicatorAttribute {
    getPeer(): ArkLinearIndicatorPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkLinearIndicatorPeer)
    }
    public setLinearIndicatorOptions(count?: number, controller?: LinearIndicatorController): this {
        if (this.checkPriority("setLinearIndicatorOptions")) {
            const count_casted = count as (number | undefined)
            const controller_casted = controller as (LinearIndicatorController | undefined)
            this.getPeer()?.setLinearIndicatorOptionsAttribute(count_casted, controller_casted)
            this.applyOptionsFinish('LinearIndicatorAttribute');
            return this
        }
        return this
    }
    public indicatorStyle(value: LinearIndicatorStyle | undefined): this {
        if (this.checkPriority("indicatorStyle")) {
            const value_casted = value as (LinearIndicatorStyle | undefined)
            this.getPeer()?.setIndicatorStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public indicatorLoop(value: boolean | undefined): this {
        if (this.checkPriority("indicatorLoop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setIndicatorLoopAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnLinearIndicatorChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnLinearIndicatorChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LinearIndicatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookLinearIndicatorAttributeModifier(this, value);
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
export function LinearIndicatorImpl(
    @memo
    style: ((attributes: LinearIndicatorAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLinearIndicatorComponent>((): ArkLinearIndicatorComponent => {
        return new ArkLinearIndicatorComponent()
    })
    NodeAttach<ArkLinearIndicatorPeer>((): ArkLinearIndicatorPeer => ArkLinearIndicatorPeer.create(receiver), (peer: ArkLinearIndicatorPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class LinearIndicatorController_serializer {
    public static write(buffer: SerializerBase, value: LinearIndicatorController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LinearIndicatorController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LinearIndicatorControllerInternal.fromPtr(ptr)
    }
}
export class LinearIndicatorStartOptions_serializer {
    public static write(buffer: SerializerBase, value: LinearIndicatorStartOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForInterval  = value.interval
        if (valueHolderForInterval !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIntervalTmpValue  = valueHolderForInterval!
            valueSerializer.writeNumber(valueHolderForIntervalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDuration  = value.duration
        if (valueHolderForDuration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDurationTmpValue  = valueHolderForDuration!
            valueSerializer.writeNumber(valueHolderForDurationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LinearIndicatorStartOptions {
        let valueDeserializer : DeserializerBase = buffer
        const intervalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let intervalTmpBuf : number | undefined = undefined
        if ((intervalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            intervalTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const intervalTmpResult : number | undefined = intervalTmpBuf
        const durationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let durationTmpBuf : number | undefined = undefined
        if ((durationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            durationTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const durationTmpResult : number | undefined = durationTmpBuf
        let value : LinearIndicatorStartOptions = ({interval: intervalTmpResult, duration: durationTmpResult} as LinearIndicatorStartOptions)
        return value
    }
}
export class LinearIndicatorStyle_serializer {
    public static write(buffer: SerializerBase, value: LinearIndicatorStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForSpaceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeRadius  = value.strokeRadius
        if (valueHolderForStrokeRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeRadiusTmpValue  = valueHolderForStrokeRadius!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStrokeRadiusTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTrackBackgroundColor  = value.trackBackgroundColor
        if (valueHolderForTrackBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTrackBackgroundColorTmpValue  = valueHolderForTrackBackgroundColor!
            ColorMetrics_serializer.write(valueSerializer, valueHolderForTrackBackgroundColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTrackColor  = value.trackColor
        if (valueHolderForTrackColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTrackColorTmpValue  = valueHolderForTrackColor!
            ColorMetrics_serializer.write(valueSerializer, valueHolderForTrackColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LinearIndicatorStyle {
        let valueDeserializer : DeserializerBase = buffer
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let spaceTmpBuf : LengthMetrics | undefined = undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            spaceTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const spaceTmpResult : LengthMetrics | undefined = spaceTmpBuf
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidthTmpBuf : LengthMetrics | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strokeWidthTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const strokeWidthTmpResult : LengthMetrics | undefined = strokeWidthTmpBuf
        const strokeRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeRadiusTmpBuf : LengthMetrics | undefined = undefined
        if ((strokeRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strokeRadiusTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const strokeRadiusTmpResult : LengthMetrics | undefined = strokeRadiusTmpBuf
        const trackBackgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let trackBackgroundColorTmpBuf : ColorMetrics | undefined = undefined
        if ((trackBackgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            trackBackgroundColorTmpBuf = ColorMetrics_serializer.read(valueDeserializer)
        }
        const trackBackgroundColorTmpResult : ColorMetrics | undefined = trackBackgroundColorTmpBuf
        const trackColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let trackColorTmpBuf : ColorMetrics | undefined = undefined
        if ((trackColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            trackColorTmpBuf = ColorMetrics_serializer.read(valueDeserializer)
        }
        const trackColorTmpResult : ColorMetrics | undefined = trackColorTmpBuf
        let value : LinearIndicatorStyle = ({space: spaceTmpResult, strokeWidth: strokeWidthTmpResult, strokeRadius: strokeRadiusTmpResult, trackBackgroundColor: trackBackgroundColorTmpResult, trackColor: trackColorTmpResult} as LinearIndicatorStyle)
        return value
    }
}
