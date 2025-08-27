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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, InteropNativeModule } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable } from "./common"
import { Callback_Number_Number_Void } from "./grid"
import { Callback_Number_Void } from "./alphabetIndexer"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { StepperOpsHandWritten } from "./../handwritten"

export class ArkStepperPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkStepperPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Stepper_construct(peerId, flags)
        const _peer  = new ArkStepperPeer(_peerPtr, peerId, "Stepper", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setStepperOptionsAttribute(value?: StepperOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            const value_value_index  = value_value.index
            let value_value_index_type : int32 = RuntimeType.UNDEFINED
            value_value_index_type = runtimeType(value_value_index)
            thisSerializer.writeInt8(value_value_index_type as int32)
            if ((RuntimeType.OBJECT) == (value_value_index_type)) {
                StepperOpsHandWritten.hookStepperAttributeStepperIndexImpl(this.peer.ptr,
                    (value_value_index as Bindable<number>));
                thisSerializer.release()
                return
            } else if ((RuntimeType.NUMBER) == (value_value_index_type)) {
                const value_value_index_value  = value_value_index! as number
                thisSerializer.writeNumber(value_value_index_value)
            }
        }
        ArkUIGeneratedNativeModule._StepperInterface_setStepperOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSkipAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_onSkip(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNextAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_onNext(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPreviousAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_onPrevious(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_indexAttribute(callback: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._StepperAttribute__onChangeEvent_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface StepperOptions {
    index?: number | Bindable<number>;
}
export type StepperInterface = (value?: StepperOptions) => StepperAttribute;
export interface StepperAttribute extends CommonMethod {
    onFinish(value: (() => void) | undefined): this
    onSkip(value: (() => void) | undefined): this
    onChange(value: ((first: number,last: number) => void) | undefined): this
    onNext(value: ((first: number,last: number) => void) | undefined): this
    onPrevious(value: ((first: number,last: number) => void) | undefined): this
    _onChangeEvent_index(callback: ((index: number | Bindable<number>) => void)): void
}
export class ArkStepperStyle extends ArkCommonMethodStyle implements StepperAttribute {
    onFinish_value?: (() => void) | undefined
    onSkip_value?: (() => void) | undefined
    onChange_value?: ((first: number,last: number) => void) | undefined
    onNext_value?: ((first: number,last: number) => void) | undefined
    onPrevious_value?: ((first: number,last: number) => void) | undefined
    public onFinish(value: (() => void) | undefined): this {
        return this
    }
    public onSkip(value: (() => void) | undefined): this {
        return this
    }
    public onChange(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public onNext(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public onPrevious(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public _onChangeEvent_index(callback: ((index: number | Bindable<number>) => void)): void {
        throw new Error("Unimplmented")
        }
}
export class ArkStepperComponent extends ArkCommonMethodComponent implements StepperAttribute {
    getPeer(): ArkStepperPeer {
        return (this.peer as ArkStepperPeer)
    }
    public setStepperOptions(value?: StepperOptions): this {
        if (this.checkPriority("setStepperOptions")) {
            const value_casted = value as (StepperOptions | undefined)
            this.getPeer()?.setStepperOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public onSkip(value: (() => void) | undefined): this {
        if (this.checkPriority("onSkip")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onSkipAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNext(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onNext")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onNextAttribute(value_casted)
            return this
        }
        return this
    }
    public onPrevious(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onPrevious")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onPreviousAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_index(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_index")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_indexAttribute(callback_casted)
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
export function Stepper(
    /** @memo */
    style: ((attributes: StepperAttribute) => void) | undefined,
    value?: StepperOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkStepperComponent()
    })
    NodeAttach<ArkStepperPeer>((): ArkStepperPeer => ArkStepperPeer.create(receiver), (_: ArkStepperPeer) => {
        receiver.setStepperOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
