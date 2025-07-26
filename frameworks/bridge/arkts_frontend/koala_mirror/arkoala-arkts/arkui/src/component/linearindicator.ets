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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { LengthMetrics, ColorMetrics, LengthMetrics_serializer, ColorMetrics_serializer } from "./../generated/arkui.Graphics"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    private setProgress_serialize(index: number, progress: number): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_setProgress(this.peer!.ptr, index, progress)
    }
    private start_serialize(options?: LinearIndicatorStartOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            LinearIndicatorStartOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorController_start(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private pause_serialize(): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_pause(this.peer!.ptr)
    }
    private stop_serialize(): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_stop(this.peer!.ptr)
    }
}
export class ArkLinearIndicatorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLinearIndicatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LinearIndicator_construct(peerId, flags)
        const _peer  = new ArkLinearIndicatorPeer(_peerPtr, peerId, "LinearIndicator", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLinearIndicatorOptionsAttribute(count?: number, controller?: LinearIndicatorController): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8((count_type).toChar())
        if ((count_type) != (RuntimeType.UNDEFINED)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8((controller_type).toChar())
        if ((controller_type) != (RuntimeType.UNDEFINED)) {
            const controller_value  = controller!
            LinearIndicatorController_serializer.write(thisSerializer, controller_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorInterface_setLinearIndicatorOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorStyleAttribute(value: LinearIndicatorStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            LinearIndicatorStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorAttribute_setIndicatorStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorAttribute_setIndicatorLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnLinearIndicatorChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
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
    public indicatorStyle(value: LinearIndicatorStyle | undefined): this {
        return this
    }
    public indicatorLoop(value: boolean | undefined): this {
        return this
    }
    public onChange(value: OnLinearIndicatorChangeCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<LinearIndicatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: LinearIndicatorAttribute): void {
        super.apply(target)
        if (this.indicatorStyle_value !== undefined)
            target.indicatorStyle(this.indicatorStyle_value!)
        if (this.indicatorLoop_value !== undefined)
            target.indicatorLoop(this.indicatorLoop_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
    }
}
export type OnLinearIndicatorChangeCallback = (index: number, progress: number) => void;

export class ArkLinearIndicatorComponent extends ArkCommonMethodComponent implements LinearIndicatorAttribute {
    getPeer(): ArkLinearIndicatorPeer {
        return (this.peer as ArkLinearIndicatorPeer)
    }
    public setLinearIndicatorOptions(count?: number, controller?: LinearIndicatorController): this {
        if (this.checkPriority("setLinearIndicatorOptions")) {
            const count_casted = count as (number | undefined)
            const controller_casted = controller as (LinearIndicatorController | undefined)
            this.getPeer()?.setLinearIndicatorOptionsAttribute(count_casted, controller_casted)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withLinearIndicatorStyle(receiver: LinearIndicatorAttribute, modifier: AttributeModifier<LinearIndicatorAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkLinearIndicatorStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("LinearIndicator")
// export function LinearIndicator(
//     count?: number, controller?: LinearIndicatorController,
//     @memo
//     content_?: () => void,
// ): LinearIndicatorAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function LinearIndicator(
    @memo
    style: ((attributes: LinearIndicatorAttribute) => void) | undefined,
    count?: number, controller?: LinearIndicatorController,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLinearIndicatorComponent>((): ArkLinearIndicatorComponent => {
        return new ArkLinearIndicatorComponent()
    })
    NodeAttach<ArkLinearIndicatorPeer>((): ArkLinearIndicatorPeer => ArkLinearIndicatorPeer.create(receiver), (_: ArkLinearIndicatorPeer): void => {
        receiver.setLinearIndicatorOptions(count,controller)
        style?.(receiver)
        withLinearIndicatorStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkLinearIndicatorSet extends ArkCommonMethodSet implements LinearIndicatorAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _indicatorStyle_flag?: boolean
    _indicatorStyle0_value?: LinearIndicatorStyle | undefined
    _indicatorLoop_flag?: boolean
    _indicatorLoop0_value?: boolean | undefined
    _onChange_flag?: boolean
    _onChange0_value?: OnLinearIndicatorChangeCallback | undefined
    applyModifierPatch(component: LinearIndicatorAttribute): void {
        if (this._indicatorStyle_flag)
            component.indicatorStyle((this._indicatorStyle0_value as LinearIndicatorStyle | undefined))
        if (this._indicatorLoop_flag)
            component.indicatorLoop((this._indicatorLoop0_value as boolean | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as OnLinearIndicatorChangeCallback | undefined))
    }
    public indicatorStyle(value: LinearIndicatorStyle | undefined): this {
        this._indicatorStyle_flag = true
        this._indicatorStyle0_value = value
        return this
    }
    public indicatorLoop(value: boolean | undefined): this {
        this._indicatorLoop_flag = true
        this._indicatorLoop0_value = value
        return this
    }
    public onChange(value: OnLinearIndicatorChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<LinearIndicatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        const value_interval  = value.interval
        let value_interval_type : int32 = RuntimeType.UNDEFINED
        value_interval_type = runtimeType(value_interval)
        valueSerializer.writeInt8((value_interval_type).toChar())
        if ((value_interval_type) != (RuntimeType.UNDEFINED)) {
            const value_interval_value  = value_interval!
            valueSerializer.writeNumber(value_interval_value)
        }
        const value_duration  = value.duration
        let value_duration_type : int32 = RuntimeType.UNDEFINED
        value_duration_type = runtimeType(value_duration)
        valueSerializer.writeInt8((value_duration_type).toChar())
        if ((value_duration_type) != (RuntimeType.UNDEFINED)) {
            const value_duration_value  = value_duration!
            valueSerializer.writeNumber(value_duration_value)
        }
    }
    public static read(buffer: DeserializerBase): LinearIndicatorStartOptions {
        let valueDeserializer : DeserializerBase = buffer
        const interval_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let interval_buf : number | undefined
        if ((interval_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            interval_buf = (valueDeserializer.readNumber() as number)
        }
        const interval_result : number | undefined = interval_buf
        const duration_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let duration_buf : number | undefined
        if ((duration_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            duration_buf = (valueDeserializer.readNumber() as number)
        }
        const duration_result : number | undefined = duration_buf
        let value : LinearIndicatorStartOptions = ({interval: interval_result, duration: duration_result} as LinearIndicatorStartOptions)
        return value
    }
}
export class LinearIndicatorStyle_serializer {
    public static write(buffer: SerializerBase, value: LinearIndicatorStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_space  = value.space
        let value_space_type : int32 = RuntimeType.UNDEFINED
        value_space_type = runtimeType(value_space)
        valueSerializer.writeInt8((value_space_type).toChar())
        if ((value_space_type) != (RuntimeType.UNDEFINED)) {
            const value_space_value  = value_space!
            LengthMetrics_serializer.write(valueSerializer, value_space_value)
        }
        const value_strokeWidth  = value.strokeWidth
        let value_strokeWidth_type : int32 = RuntimeType.UNDEFINED
        value_strokeWidth_type = runtimeType(value_strokeWidth)
        valueSerializer.writeInt8((value_strokeWidth_type).toChar())
        if ((value_strokeWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeWidth_value  = value_strokeWidth!
            LengthMetrics_serializer.write(valueSerializer, value_strokeWidth_value)
        }
        const value_strokeRadius  = value.strokeRadius
        let value_strokeRadius_type : int32 = RuntimeType.UNDEFINED
        value_strokeRadius_type = runtimeType(value_strokeRadius)
        valueSerializer.writeInt8((value_strokeRadius_type).toChar())
        if ((value_strokeRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeRadius_value  = value_strokeRadius!
            LengthMetrics_serializer.write(valueSerializer, value_strokeRadius_value)
        }
        const value_trackBackgroundColor  = value.trackBackgroundColor
        let value_trackBackgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_trackBackgroundColor_type = runtimeType(value_trackBackgroundColor)
        valueSerializer.writeInt8((value_trackBackgroundColor_type).toChar())
        if ((value_trackBackgroundColor_type) != (RuntimeType.UNDEFINED)) {
            const value_trackBackgroundColor_value  = value_trackBackgroundColor!
            ColorMetrics_serializer.write(valueSerializer, value_trackBackgroundColor_value)
        }
        const value_trackColor  = value.trackColor
        let value_trackColor_type : int32 = RuntimeType.UNDEFINED
        value_trackColor_type = runtimeType(value_trackColor)
        valueSerializer.writeInt8((value_trackColor_type).toChar())
        if ((value_trackColor_type) != (RuntimeType.UNDEFINED)) {
            const value_trackColor_value  = value_trackColor!
            ColorMetrics_serializer.write(valueSerializer, value_trackColor_value)
        }
    }
    public static read(buffer: DeserializerBase): LinearIndicatorStyle {
        let valueDeserializer : DeserializerBase = buffer
        const space_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let space_buf : LengthMetrics | undefined
        if ((space_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            space_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const space_result : LengthMetrics | undefined = space_buf
        const strokeWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidth_buf : LengthMetrics | undefined
        if ((strokeWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            strokeWidth_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const strokeWidth_result : LengthMetrics | undefined = strokeWidth_buf
        const strokeRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeRadius_buf : LengthMetrics | undefined
        if ((strokeRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            strokeRadius_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const strokeRadius_result : LengthMetrics | undefined = strokeRadius_buf
        const trackBackgroundColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let trackBackgroundColor_buf : ColorMetrics | undefined
        if ((trackBackgroundColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            trackBackgroundColor_buf = (ColorMetrics_serializer.read(valueDeserializer) as ColorMetrics)
        }
        const trackBackgroundColor_result : ColorMetrics | undefined = trackBackgroundColor_buf
        const trackColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let trackColor_buf : ColorMetrics | undefined
        if ((trackColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            trackColor_buf = (ColorMetrics_serializer.read(valueDeserializer) as ColorMetrics)
        }
        const trackColor_result : ColorMetrics | undefined = trackColor_buf
        let value : LinearIndicatorStyle = ({space: space_result, strokeWidth: strokeWidth_result, strokeRadius: strokeRadius_result, trackBackgroundColor: trackBackgroundColor_result, trackColor: trackColor_result} as LinearIndicatorStyle)
        return value
    }
}
