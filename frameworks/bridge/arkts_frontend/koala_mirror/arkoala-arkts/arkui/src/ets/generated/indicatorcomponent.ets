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
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { DotIndicator_serializer, DigitIndicator_serializer, DotIndicator, DigitIndicator } from "./swiper"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._IndicatorComponentController_ctor()
        return retval
    }
    constructor() {
        this(IndicatorComponentController.ctor())
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
    public changeIndex(index: number, useAnimation?: boolean): void {
        const index_casted = index as (number)
        const useAnimation_casted = useAnimation as (boolean | undefined)
        this.changeIndex_serialize(index_casted, useAnimation_casted)
        return
    }
    private showNext_serialize(): void {
        ArkUIGeneratedNativeModule._IndicatorComponentController_showNext(this.peer!.ptr)
    }
    private showPrevious_serialize(): void {
        ArkUIGeneratedNativeModule._IndicatorComponentController_showPrevious(this.peer!.ptr)
    }
    private changeIndex_serialize(index: number, useAnimation?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let useAnimation_type : int32 = RuntimeType.UNDEFINED
        useAnimation_type = runtimeType(useAnimation)
        thisSerializer.writeInt8(useAnimation_type)
        if ((RuntimeType.UNDEFINED) != (useAnimation_type)) {
            const useAnimation_value  = useAnimation!
            thisSerializer.writeBoolean(useAnimation_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentController_changeIndex(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkIndicatorComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkIndicatorComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._IndicatorComponent_construct(peerId, flags)
        const _peer  = new ArkIndicatorComponentPeer(_peerPtr, peerId, "IndicatorComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setIndicatorComponentOptionsAttribute(controller?: IndicatorComponentController): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8(controller_type)
        if ((RuntimeType.UNDEFINED) != (controller_type)) {
            const controller_value  = controller!
            IndicatorComponentController_serializer.write(thisSerializer, controller_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentInterface_setIndicatorComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    initialIndexAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_initialIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    countAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_count(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    styleAttribute(value: DotIndicator | DigitIndicator | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isDotIndicator(value_value))) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as DotIndicator
                DotIndicator_serializer.write(thisSerializer, value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isDigitIndicator(value_value))) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as DigitIndicator
                DigitIndicator_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_style(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    loopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_loop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    verticalAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_vertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface IndicatorComponentAttribute extends CommonMethod {
    initialIndex(value: number | undefined): this
    count(value: number | undefined): this
    style(value: DotIndicator | DigitIndicator | undefined): this
    loop(value: boolean | undefined): this
    vertical(value: boolean | undefined): this
    onChange(value: ((value0: number) => void) | undefined): this
    attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkIndicatorComponentStyle extends ArkCommonMethodStyle implements IndicatorComponentAttribute {
    initialIndex_value?: number | undefined
    count_value?: number | undefined
    style_value?: DotIndicator | DigitIndicator | undefined
    loop_value?: boolean | undefined
    vertical_value?: boolean | undefined
    onChange_value?: ((value0: number) => void) | undefined
    attributeModifier_value?: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    public initialIndex(value: number | undefined): this {
        return this
    }
    public count(value: number | undefined): this {
        return this
    }
    public style(value: DotIndicator | DigitIndicator | undefined): this {
        return this
    }
    public loop(value: boolean | undefined): this {
        return this
    }
    public vertical(value: boolean | undefined): this {
        return this
    }
    public onChange(value: ((value0: number) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: IndicatorComponentAttribute): void {
        super.apply(target)
        if (this.initialIndex_value !== undefined)
            target.initialIndex(this.initialIndex_value!)
        if (this.count_value !== undefined)
            target.count(this.count_value!)
        if (this.style_value !== undefined)
            target.style(this.style_value!)
        if (this.loop_value !== undefined)
            target.loop(this.loop_value!)
        if (this.vertical_value !== undefined)
            target.vertical(this.vertical_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
    }
}

export class ArkIndicatorComponentComponent extends ArkCommonMethodComponent implements IndicatorComponentAttribute {
    getPeer(): ArkIndicatorComponentPeer {
        return (this.peer as ArkIndicatorComponentPeer)
    }
    public setIndicatorComponentOptions(controller?: IndicatorComponentController): this {
        if (this.checkPriority("setIndicatorComponentOptions")) {
            const controller_casted = controller as (IndicatorComponentController | undefined)
            this.getPeer()?.setIndicatorComponentOptionsAttribute(controller_casted)
            return this
        }
        return this
    }
    public initialIndex(value: number | undefined): this {
        if (this.checkPriority("initialIndex")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.initialIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public count(value: number | undefined): this {
        if (this.checkPriority("count")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.countAttribute(value_casted)
            return this
        }
        return this
    }
    public style(value: DotIndicator | DigitIndicator | undefined): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (DotIndicator | DigitIndicator | undefined)
            this.getPeer()?.styleAttribute(value_casted)
            return this
        }
        return this
    }
    public loop(value: boolean | undefined): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.loopAttribute(value_casted)
            return this
        }
        return this
    }
    public vertical(value: boolean | undefined): this {
        if (this.checkPriority("vertical")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.verticalAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withIndicatorComponentStyle(receiver: IndicatorComponentAttribute, modifier: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkIndicatorComponentStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("IndicatorComponentImpl")
export function IndicatorComponent(
    controller?: IndicatorComponentController | undefined,
    @memo
    content_?: () => void,
): IndicatorComponentAttribute {
    throw new Error("Not implemented")
}

@memo
export function IndicatorComponentImpl(
    @memo
    style: ((attributes: IndicatorComponentAttribute) => void) | undefined,
    controller?: IndicatorComponentController | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkIndicatorComponentComponent>((): ArkIndicatorComponentComponent => {
        return new ArkIndicatorComponentComponent()
    })
    NodeAttach<ArkIndicatorComponentPeer>((): ArkIndicatorComponentPeer => ArkIndicatorComponentPeer.create(receiver), (_: ArkIndicatorComponentPeer): void => {
        receiver.setIndicatorComponentOptions(controller)
        style?.(receiver)
        withIndicatorComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
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
