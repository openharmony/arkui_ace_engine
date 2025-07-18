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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkStepperPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkStepperPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Stepper_construct(peerId, flags)
        const _peer  = new ArkStepperPeer(_peerPtr, peerId, "Stepper", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setStepperOptionsAttribute(value?: StepperOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            StepperOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._StepperInterface_setStepperOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSkipAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnSkip(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((prevIndex: number,index: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNextAttribute(value: ((prevIndex: number,index: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnNext(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPreviousAttribute(value: ((prevIndex: number,index: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnPrevious(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_indexAttribute(callback_: ((index: number) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._StepperAttribute_set_onChangeEvent_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface StepperOptions {
    index?: number;
}
export interface StepperAttribute extends CommonMethod {
    onFinish(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onFinish")
    }
    onSkip(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onSkip")
    }
    onChange(value: ((prevIndex: number,index: number) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onNext(value: ((prevIndex: number,index: number) => void) | undefined): this {
        throw new Error("Unimplemented method onNext")
    }
    onPrevious(value: ((prevIndex: number,index: number) => void) | undefined): this {
        throw new Error("Unimplemented method onPrevious")
    }
    _onChangeEvent_index(callback_: ((index: number) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_index")
    }
    attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkStepperStyle extends ArkCommonMethodStyle implements StepperAttribute {
    onFinish_value?: (() => void) | undefined
    onSkip_value?: (() => void) | undefined
    onChange_value?: ((prevIndex: number,index: number) => void) | undefined
    onNext_value?: ((prevIndex: number,index: number) => void) | undefined
    onPrevious_value?: ((prevIndex: number,index: number) => void) | undefined
    attributeModifier_value?: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined
    public onFinish(value: (() => void) | undefined): this {
        return this
    }
    public onSkip(value: (() => void) | undefined): this {
        return this
    }
    public onChange(value: ((prevIndex: number,index: number) => void) | undefined): this {
        return this
    }
    public onNext(value: ((prevIndex: number,index: number) => void) | undefined): this {
        return this
    }
    public onPrevious(value: ((prevIndex: number,index: number) => void) | undefined): this {
        return this
    }
    public _onChangeEvent_index(callback_: ((index: number) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: StepperAttribute): void {
        super.apply(target)
        if (this.onFinish_value !== undefined)
            target.onFinish(this.onFinish_value!)
        if (this.onSkip_value !== undefined)
            target.onSkip(this.onSkip_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.onNext_value !== undefined)
            target.onNext(this.onNext_value!)
        if (this.onPrevious_value !== undefined)
            target.onPrevious(this.onPrevious_value!)
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
            this.getPeer()?.setOnFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public onSkip(value: (() => void) | undefined): this {
        if (this.checkPriority("onSkip")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnSkipAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((prevIndex: number,index: number) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((prevIndex: number,index: number) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNext(value: ((prevIndex: number,index: number) => void) | undefined): this {
        if (this.checkPriority("onNext")) {
            const value_casted = value as (((prevIndex: number,index: number) => void) | undefined)
            this.getPeer()?.setOnNextAttribute(value_casted)
            return this
        }
        return this
    }
    public onPrevious(value: ((prevIndex: number,index: number) => void) | undefined): this {
        if (this.checkPriority("onPrevious")) {
            const value_casted = value as (((prevIndex: number,index: number) => void) | undefined)
            this.getPeer()?.setOnPreviousAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_index(callback_: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_index")) {
            const callback__casted = callback_ as (((index: number) => void))
            this.getPeer()?.set_onChangeEvent_indexAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withStepperStyle(receiver: StepperAttribute, modifier: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkStepperStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Stepper")
// export function Stepper(
//     value?: StepperOptions,
//     @memo
//     content_?: () => void,
// ): StepperAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Stepper(
    @memo
    style: ((attributes: StepperAttribute) => void) | undefined,
    value?: StepperOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkStepperComponent>((): ArkStepperComponent => {
        return new ArkStepperComponent()
    })
    NodeAttach<ArkStepperPeer>((): ArkStepperPeer => ArkStepperPeer.create(receiver), (_: ArkStepperPeer): void => {
        receiver.setStepperOptions(value)
        style?.(receiver)
        withStepperStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkStepperSet extends ArkCommonMethodSet implements StepperAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onFinish_flag?: boolean
    _onFinish0_value?: (() => void) | undefined
    _onSkip_flag?: boolean
    _onSkip0_value?: (() => void) | undefined
    _onChange_flag?: boolean
    _onChange0_value?: ((prevIndex: number,index: number) => void) | undefined
    _onNext_flag?: boolean
    _onNext0_value?: ((prevIndex: number,index: number) => void) | undefined
    _onPrevious_flag?: boolean
    _onPrevious0_value?: ((prevIndex: number,index: number) => void) | undefined
    __onChangeEvent_index_flag?: boolean
    __onChangeEvent_index0_value?: ((index: number) => void)
    applyModifierPatch(component: StepperAttribute): void {
        if (this._onFinish_flag)
            component.onFinish((this._onFinish0_value as (() => void) | undefined))
        if (this._onSkip_flag)
            component.onSkip((this._onSkip0_value as (() => void) | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as ((prevIndex: number,index: number) => void) | undefined))
        if (this._onNext_flag)
            component.onNext((this._onNext0_value as ((prevIndex: number,index: number) => void) | undefined))
        if (this._onPrevious_flag)
            component.onPrevious((this._onPrevious0_value as ((prevIndex: number,index: number) => void) | undefined))
    }
    public onFinish(value: (() => void) | undefined): this {
        this._onFinish_flag = true
        this._onFinish0_value = value
        return this
    }
    public onSkip(value: (() => void) | undefined): this {
        this._onSkip_flag = true
        this._onSkip0_value = value
        return this
    }
    public onChange(value: ((prevIndex: number,index: number) => void) | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public onNext(value: ((prevIndex: number,index: number) => void) | undefined): this {
        this._onNext_flag = true
        this._onNext0_value = value
        return this
    }
    public onPrevious(value: ((prevIndex: number,index: number) => void) | undefined): this {
        this._onPrevious_flag = true
        this._onPrevious0_value = value
        return this
    }
    public _onChangeEvent_index(callback_: ((index: number) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class StepperOptions_serializer {
    public static write(buffer: SerializerBase, value: StepperOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_index  = value.index
        let value_index_type : int32 = RuntimeType.UNDEFINED
        value_index_type = runtimeType(value_index)
        valueSerializer.writeInt8((value_index_type).toChar())
        if ((value_index_type) != (RuntimeType.UNDEFINED)) {
            const value_index_value  = value_index!
            valueSerializer.writeNumber(value_index_value)
        }
    }
    public static read(buffer: DeserializerBase): StepperOptions {
        let valueDeserializer : DeserializerBase = buffer
        const index_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let index_buf : number | undefined
        if ((index_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            index_buf = (valueDeserializer.readNumber() as number)
        }
        const index_result : number | undefined = index_buf
        let value : StepperOptions = ({index: index_result} as StepperOptions)
        return value
    }
}
