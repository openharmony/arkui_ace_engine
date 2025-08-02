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
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics } from "../Graphics"
import { ColorMetrics } from "../Graphics"

export class LinearIndicatorControllerInternal {
    public static fromPtr(ptr: KPointer): LinearIndicatorController {
        const obj : LinearIndicatorController = new LinearIndicatorController()
        obj.peer = new Finalizable(ptr, LinearIndicatorController.getFinalizer())
        return obj
    }
}
export class LinearIndicatorController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_linearindicatorcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LinearIndicatorController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = LinearIndicatorController.ctor_linearindicatorcontroller()
        this.peer = new Finalizable(ctorPtr, LinearIndicatorController.getFinalizer())
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
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeLinearIndicatorStartOptions(options_value)
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkLinearIndicatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LinearIndicator_construct(peerId, flags)
        const _peer  = new ArkLinearIndicatorPeer(_peerPtr, peerId, "LinearIndicator", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLinearIndicatorOptionsAttribute(count?: number, controller?: LinearIndicatorController): void {
        const thisSerializer : Serializer = Serializer.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8(count_type as int32)
        if ((RuntimeType.UNDEFINED) != (count_type)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8(controller_type as int32)
        if ((RuntimeType.UNDEFINED) != (controller_type)) {
            const controller_value  = controller!
            thisSerializer.writeLinearIndicatorController(controller_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorInterface_setLinearIndicatorOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorStyleAttribute(value: LinearIndicatorStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLinearIndicatorStyle(value_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorAttribute_indicatorStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorAttribute_indicatorLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: OnLinearIndicatorChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export type LinearIndicatorInterface = (count?: number, controller?: LinearIndicatorController) => LinearIndicatorAttribute;
export interface LinearIndicatorAttribute extends CommonMethod {
    indicatorStyle(value: LinearIndicatorStyle | undefined): this
    indicatorLoop(value: boolean | undefined): this
    onChange(value: OnLinearIndicatorChangeCallback | undefined): this
}
export class ArkLinearIndicatorStyle extends ArkCommonMethodStyle implements LinearIndicatorAttribute {
    indicatorStyle_value?: LinearIndicatorStyle | undefined
    indicatorLoop_value?: boolean | undefined
    onChange_value?: OnLinearIndicatorChangeCallback | undefined
    public indicatorStyle(value: LinearIndicatorStyle | undefined): this {
        return this
    }
    public indicatorLoop(value: boolean | undefined): this {
        return this
    }
    public onChange(value: OnLinearIndicatorChangeCallback | undefined): this {
        return this
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
            this.getPeer()?.indicatorStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public indicatorLoop(value: boolean | undefined): this {
        if (this.checkPriority("indicatorLoop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.indicatorLoopAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnLinearIndicatorChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnLinearIndicatorChangeCallback | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
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
export function LinearIndicator(
    /** @memo */
    style: ((attributes: LinearIndicatorAttribute) => void) | undefined,
    count?: number, controller?: LinearIndicatorController,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkLinearIndicatorComponent()
    })
    NodeAttach<ArkLinearIndicatorPeer>((): ArkLinearIndicatorPeer => ArkLinearIndicatorPeer.create(receiver), (_: ArkLinearIndicatorPeer) => {
        receiver.setLinearIndicatorOptions(count,controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
