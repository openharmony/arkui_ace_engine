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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, KInt32ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { DotIndicator_serializer, DigitIndicator_serializer, DotIndicator, DigitIndicator } from "./swiper"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { hookIndicatorComponentAttributeModifier, AttributeModifier, AttributeUpdater } from "#handwritten"
import { IndicatorComponentModifier } from "./../IndicatorComponentModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class IndicatorComponentControllerInternal {
    public static fromPtr(ptr: KPointer): IndicatorComponentController {
        return new IndicatorComponentController(ptr)
    }
}
export class IndicatorComponentController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, IndicatorComponentController.getFinalizer())
    }
    constructor() {
        this(IndicatorComponentController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._IndicatorComponentController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._IndicatorComponentController_getFinalizer()
    }
    public showNext(): void {
        this.showNext_serialize()
        return
    }
    public showPrevious(): void {
        this.showPrevious_serialize()
        return
    }
    public changeIndex(index: int32 | undefined, useAnimation?: boolean): void {
        const index_casted = index as (int32 | undefined)
        const useAnimation_casted = useAnimation as (boolean | undefined)
        this.changeIndex_serialize(index_casted, useAnimation_casted)
        return
    }
    showNext_serialize(): void {
        ArkUIGeneratedNativeModule._IndicatorComponentController_showNext(this.peer!.ptr)
    }
    showPrevious_serialize(): void {
        ArkUIGeneratedNativeModule._IndicatorComponentController_showPrevious(this.peer!.ptr)
    }
    changeIndex_serialize(index: int32 | undefined, useAnimation?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (index !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const indexTmpValue  = index!
            thisSerializer.writeInt32(indexTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (useAnimation !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const useAnimationTmpValue  = useAnimation!
            thisSerializer.writeBoolean(useAnimationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentController_changeIndex(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkIndicatorComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: IndicatorComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkIndicatorComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._IndicatorComponent_construct(peerId, flags)
        const _peer  = new ArkIndicatorComponentPeer(_peerPtr, peerId, 'IndicatorComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setIndicatorComponentOptionsAttribute(controller?: IndicatorComponentController): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (controller !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const controllerTmpValue  = controller!
            IndicatorComponentController_serializer.write(thisSerializer, controllerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentInterface_setIndicatorComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInitialIndexAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_setInitialIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCountAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_setCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStyleAttribute(value: DotIndicator | DigitIndicator | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof DotIndicator) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as DotIndicator
                DotIndicator_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof DigitIndicator) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as DigitIndicator
                DigitIndicator_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_setStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_setLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_setVertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value0: int32) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface IndicatorComponentAttribute extends CommonMethod {
    setIndicatorComponentOptions(controller?: IndicatorComponentController): this {
        throw new Error("Unimplemented method setIndicatorComponentOptions")
    }
    initialIndex(value: int32 | undefined): this {
        throw new Error("Unimplemented method initialIndex")
    }
    count(value: int32 | undefined): this {
        throw new Error("Unimplemented method count")
    }
    style(value: DotIndicator | DigitIndicator | undefined): this {
        throw new Error("Unimplemented method style")
    }
    loop(value: boolean | undefined): this {
        throw new Error("Unimplemented method loop")
    }
    vertical(value: boolean | undefined): this {
        throw new Error("Unimplemented method vertical")
    }
    onChange(value: ((value0: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkIndicatorComponentStyle extends ArkCommonMethodStyle implements IndicatorComponentAttribute {
    initialIndex_value?: int32 | undefined
    count_value?: int32 | undefined
    style_value?: DotIndicator | DigitIndicator | undefined
    loop_value?: boolean | undefined
    vertical_value?: boolean | undefined
    onChange_value?: ((value0: int32) => void) | undefined
    setIndicatorComponentOptions(controller?: IndicatorComponentController): this {
        return this
    }
    initialIndex(value: int32 | undefined): this {
        return this
    }
    count(value: int32 | undefined): this {
        return this
    }
    style(value: DotIndicator | DigitIndicator | undefined): this {
        return this
    }
    loop(value: boolean | undefined): this {
        return this
    }
    vertical(value: boolean | undefined): this {
        return this
    }
    onChange(value: ((value0: int32) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkIndicatorComponentComponent extends ArkCommonMethodComponent implements IndicatorComponentAttribute {
    getPeer(): ArkIndicatorComponentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkIndicatorComponentPeer)
    }
    public setIndicatorComponentOptions(controller?: IndicatorComponentController): this {
        if (this.checkPriority("setIndicatorComponentOptions")) {
            const controller_casted = controller as (IndicatorComponentController | undefined)
            this.getPeer()?.setIndicatorComponentOptionsAttribute(controller_casted)
            this.applyOptionsFinish('IndicatorComponentAttribute');
            return this
        }
        return this
    }
    public initialIndex(value: int32 | undefined): this {
        if (this.checkPriority("initialIndex")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setInitialIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public count(value: int32 | undefined): this {
        if (this.checkPriority("count")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setCountAttribute(value_casted)
            return this
        }
        return this
    }
    public style(value: DotIndicator | DigitIndicator | undefined): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (DotIndicator | DigitIndicator | undefined)
            this.getPeer()?.setStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public loop(value: boolean | undefined): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setLoopAttribute(value_casted)
            return this
        }
        return this
    }
    public vertical(value: boolean | undefined): this {
        if (this.checkPriority("vertical")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setVerticalAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value0: int32) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: int32) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
         ModifierStateManager.INSTANCE.scope(() => {
            hookIndicatorComponentAttributeModifier(this, value);
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
export function IndicatorComponentImpl(
    @memo
    style: ((attributes: IndicatorComponentAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkIndicatorComponentComponent>((): ArkIndicatorComponentComponent => {
        return new ArkIndicatorComponentComponent()
    })
    NodeAttach<ArkIndicatorComponentPeer>((): ArkIndicatorComponentPeer => ArkIndicatorComponentPeer.create(receiver), (peer: ArkIndicatorComponentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class IndicatorComponentController_serializer {
    public static write(buffer: SerializerBase, value: IndicatorComponentController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): IndicatorComponentController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return IndicatorComponentControllerInternal.fromPtr(ptr)
    }
}
