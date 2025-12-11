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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_I32_serializer } from "./common"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { hookStepperAttributeModifier, AttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { StepperModifier } from "./../StepperModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkStepperPeer extends ArkCommonMethodPeer {
    attributeSet?: StepperModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
    setOnChangeAttribute(value: ((prevIndex: int32,index: int32) => void) | undefined): void {
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
    setOnNextAttribute(value: ((prevIndex: int32,index: int32) => void) | undefined): void {
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
    setOnPreviousAttribute(value: ((prevIndex: int32,index: int32) => void) | undefined): void {
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
    index?: int32 | Bindable<int32>;
}
export interface StepperAttribute extends CommonMethod {
    setStepperOptions(value?: StepperOptions): this {
        throw new Error("Unimplemented method setStepperOptions")
    }
    onFinish(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onFinish")
    }
    onSkip(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onSkip")
    }
    onChange(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onNext(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onNext")
    }
    onPrevious(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onPrevious")
    }
    attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkStepperStyle extends ArkCommonMethodStyle implements StepperAttribute {
    onFinish_value?: (() => void) | undefined
    onSkip_value?: (() => void) | undefined
    onChange_value?: ((prevIndex: int32,index: int32) => void) | undefined
    onNext_value?: ((prevIndex: int32,index: int32) => void) | undefined
    onPrevious_value?: ((prevIndex: int32,index: int32) => void) | undefined
    setStepperOptions(value?: StepperOptions): this {
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        return this
    }
    onSkip(value: (() => void) | undefined): this {
        return this
    }
    onChange(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        return this
    }
    onNext(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        return this
    }
    onPrevious(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkStepperComponent extends ArkCommonMethodComponent implements StepperAttribute {
    getPeer(): ArkStepperPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkStepperPeer)
    }
    public setStepperOptions(value?: StepperOptions): this {
        if (this.checkPriority("setStepperOptions")) {
            const value_casted = value as (StepperOptions | undefined)
            this.getPeer()?.setStepperOptionsAttribute(value_casted)
            this.applyOptionsFinish('StepperAttribute');
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
    public onChange(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((prevIndex: int32,index: int32) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNext(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        if (this.checkPriority("onNext")) {
            const value_casted = value as (((prevIndex: int32,index: int32) => void) | undefined)
            this.getPeer()?.setOnNextAttribute(value_casted)
            return this
        }
        return this
    }
    public onPrevious(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        if (this.checkPriority("onPrevious")) {
            const value_casted = value as (((prevIndex: int32,index: int32) => void) | undefined)
            this.getPeer()?.setOnPreviousAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookStepperAttributeModifier(this, value);
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
export function StepperImpl(
    @memo
    style: ((attributes: StepperAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkStepperComponent>((): ArkStepperComponent => {
        return new ArkStepperComponent()
    })
    NodeAttach<ArkStepperPeer>((): ArkStepperPeer => ArkStepperPeer.create(receiver), (peer: ArkStepperPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class StepperOptions_serializer {
    public static write(buffer: SerializerBase, value: StepperOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIndex  = value.index
        if (valueHolderForIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndexTmpValue  = valueHolderForIndex!
            if (valueHolderForIndexTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIndexTmpValueForIdx0  = valueHolderForIndexTmpValue as int32
                valueSerializer.writeInt32(valueHolderForIndexTmpValueForIdx0)
            } else if (valueHolderForIndexTmpValue instanceof Bindable<int32>) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIndexTmpValueForIdx1  = valueHolderForIndexTmpValue as Bindable<int32>
                Bindable_I32_serializer.write(valueSerializer, valueHolderForIndexTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StepperOptions {
        let valueDeserializer : DeserializerBase = buffer
        const indexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indexTmpBuf : int32 | Bindable<int32> | undefined = undefined
        if ((indexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indexTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let indexTmpBuf_ : int32 | Bindable<int32> | undefined
            if (indexTmpBuf_UnionSelector == (0).toChar()) {
                indexTmpBuf_ = valueDeserializer.readInt32()
            } else if (indexTmpBuf_UnionSelector == (1).toChar()) {
                indexTmpBuf_ = Bindable_I32_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for indexTmpBuf_ has to be chosen through deserialisation.")
            }
            indexTmpBuf = (indexTmpBuf_ as int32 | Bindable<int32>)
        }
        const indexTmpResult : int32 | Bindable<int32> | undefined = indexTmpBuf
        let value : StepperOptions = ({index: indexTmpResult} as StepperOptions)
        return value
    }
}
