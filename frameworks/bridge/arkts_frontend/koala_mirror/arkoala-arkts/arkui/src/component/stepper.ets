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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier, Bindable_Number_serializer } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkStepperPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkStepperPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Stepper_construct(peerId, flags)
        const _peer  = new ArkStepperPeer(_peerPtr, peerId, 'Stepper', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setStepperOptionsAttribute(value?: StepperOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            StepperOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StepperInterface_setStepperOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSkipAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnSkip(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((prevIndex: number,index: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNextAttribute(value: ((prevIndex: number,index: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnNext(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPreviousAttribute(value: ((prevIndex: number,index: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StepperAttribute_setOnPrevious(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface StepperOptions {
    index?: number | Bindable<number>;
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
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class StepperModifier extends CommonMethodModifier implements StepperAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onFinish_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFinish_0_0value?: (() => void) | undefined
    _onSkip_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSkip_0_0value?: (() => void) | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((prevIndex: number,index: number) => void) | undefined
    _onNext_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNext_0_0value?: ((prevIndex: number,index: number) => void) | undefined
    _onPrevious_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPrevious_0_0value?: ((prevIndex: number,index: number) => void) | undefined
    applyModifierPatch(peer: ArkStepperPeer): void {
        super.applyModifierPatch(peer)
        if (this._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onSkip_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSkip_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSkipAttribute((this._onSkip_0_0value as (() => void) | undefined));
                    this._onSkip_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSkip_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSkip_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSkipAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((prevIndex: number,index: number) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((prevIndex: number,index: number) => void) | undefined));
                }
            }
        }
        if (this._onNext_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNext_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNextAttribute((this._onNext_0_0value as ((prevIndex: number,index: number) => void) | undefined));
                    this._onNext_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNext_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNext_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNextAttribute((undefined as ((prevIndex: number,index: number) => void) | undefined));
                }
            }
        }
        if (this._onPrevious_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPrevious_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPreviousAttribute((this._onPrevious_0_0value as ((prevIndex: number,index: number) => void) | undefined));
                    this._onPrevious_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPrevious_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPrevious_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPreviousAttribute((undefined as ((prevIndex: number,index: number) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: StepperModifier): void {
        super.mergeModifier(modifier)
        if (modifier._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onSkip_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSkip_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSkip(modifier._onSkip_0_0value);
                    break;
                }
                default: {
                    this.onSkip((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((prevIndex: number,index: number) => void) | undefined));
                }
            }
        }
        if (modifier._onNext_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNext_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNext(modifier._onNext_0_0value);
                    break;
                }
                default: {
                    this.onNext((undefined as ((prevIndex: number,index: number) => void) | undefined));
                }
            }
        }
        if (modifier._onPrevious_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPrevious_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPrevious(modifier._onPrevious_0_0value);
                    break;
                }
                default: {
                    this.onPrevious((undefined as ((prevIndex: number,index: number) => void) | undefined));
                }
            }
        }
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
        } else
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSkip(value: (() => void) | undefined): this {
        if (((this._onSkip_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSkip_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSkip_0_0value = value
        } else
        {
            this._onSkip_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((prevIndex: number,index: number) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNext(value: ((prevIndex: number,index: number) => void) | undefined): this {
        if (((this._onNext_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNext_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNext_0_0value = value
        } else
        {
            this._onNext_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPrevious(value: ((prevIndex: number,index: number) => void) | undefined): this {
        if (((this._onPrevious_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPrevious_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPrevious_0_0value = value
        } else
        {
            this._onPrevious_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class StepperOptions_serializer {
    public static write(buffer: SerializerBase, value: StepperOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIndex  = value.index
        if (valueHolderForIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndexTmpValue  = valueHolderForIndex!
            if (valueHolderForIndexTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForIndexTmpValueForIdx0  = valueHolderForIndexTmpValue as number
                valueSerializer.writeNumber(valueHolderForIndexTmpValueForIdx0)
            } else if (valueHolderForIndexTmpValue instanceof Bindable<number>) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForIndexTmpValueForIdx1  = valueHolderForIndexTmpValue as Bindable<number>
                Bindable_Number_serializer.write(valueSerializer, valueHolderForIndexTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StepperOptions {
        let valueDeserializer : DeserializerBase = buffer
        const indexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indexTmpBuf : number | Bindable<number> | undefined
        if ((indexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indexTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let indexTmpBuf_ : number | Bindable<number> | undefined
            if (indexTmpBuf_UnionSelector == (0).toChar()) {
                indexTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (indexTmpBuf_UnionSelector == (1).toChar()) {
                indexTmpBuf_ = Bindable_Number_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for indexTmpBuf_ has to be chosen through deserialisation.")
            }
            indexTmpBuf = (indexTmpBuf_ as number | Bindable<number>)
        }
        const indexTmpResult : number | Bindable<number> | undefined = indexTmpBuf
        let value : StepperOptions = ({index: indexTmpResult} as StepperOptions)
        return value
    }
}
