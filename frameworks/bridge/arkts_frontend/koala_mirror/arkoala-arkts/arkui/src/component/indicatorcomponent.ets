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
import { DotIndicator_serializer, DigitIndicator_serializer, DotIndicator, DigitIndicator } from "./swiper"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
        if (useAnimation !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const useAnimationTmpValue  = useAnimation!
            thisSerializer.writeBoolean(useAnimationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
    setInitialIndexAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_setInitialIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCountAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as DotIndicator
                DotIndicator_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof DigitIndicator) {
                thisSerializer.writeInt8((1).toChar())
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
    setOnChangeAttribute(value: ((value0: number) => void) | undefined): void {
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
    initialIndex(value: number | undefined): this {
        throw new Error("Unimplemented method initialIndex")
    }
    count(value: number | undefined): this {
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
    onChange(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
            this.getPeer()?.setInitialIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public count(value: number | undefined): this {
        if (this.checkPriority("count")) {
            const value_casted = value as (number | undefined)
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
    public onChange(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function IndicatorComponent(
    @memo
    style: ((attributes: IndicatorComponentAttribute) => void) | undefined,
    controller?: IndicatorComponentController,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkIndicatorComponentComponent>((): ArkIndicatorComponentComponent => {
        return new ArkIndicatorComponentComponent()
    })
    NodeAttach<ArkIndicatorComponentPeer>((): ArkIndicatorComponentPeer => ArkIndicatorComponentPeer.create(receiver), (_: ArkIndicatorComponentPeer): void => {
        receiver.setIndicatorComponentOptions(controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class IndicatorComponentModifier extends CommonMethodModifier implements IndicatorComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _initialIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _initialIndex_0_0value?: number | undefined
    _count_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _count_0_0value?: number | undefined
    _style_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _style_0_0value?: DotIndicator | DigitIndicator | undefined
    _loop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _loop_0_0value?: boolean | undefined
    _vertical_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _vertical_0_0value?: boolean | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value0: number) => void) | undefined
    applyModifierPatch(peer: ArkIndicatorComponentPeer): void {
        super.applyModifierPatch(peer)
        if (this._initialIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._initialIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInitialIndexAttribute((this._initialIndex_0_0value as number | undefined));
                    this._initialIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._initialIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._initialIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInitialIndexAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._count_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._count_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCountAttribute((this._count_0_0value as number | undefined));
                    this._count_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._count_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._count_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCountAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._style_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._style_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStyleAttribute((this._style_0_0value as DotIndicator | DigitIndicator | undefined));
                    this._style_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._style_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._style_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStyleAttribute((undefined as DotIndicator | DigitIndicator | undefined));
                }
            }
        }
        if (this._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._loop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._vertical_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVerticalAttribute((this._vertical_0_0value as boolean | undefined));
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._vertical_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVerticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value0: number) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: IndicatorComponentModifier): void {
        super.mergeModifier(modifier)
        if (modifier._initialIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._initialIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.initialIndex(modifier._initialIndex_0_0value);
                    break;
                }
                default: {
                    this.initialIndex((undefined as number | undefined));
                }
            }
        }
        if (modifier._count_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._count_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.count(modifier._count_0_0value);
                    break;
                }
                default: {
                    this.count((undefined as number | undefined));
                }
            }
        }
        if (modifier._style_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._style_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.style(modifier._style_0_0value);
                    break;
                }
                default: {
                    this.style((undefined as DotIndicator | DigitIndicator | undefined));
                }
            }
        }
        if (modifier._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._vertical_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.vertical(modifier._vertical_0_0value);
                    break;
                }
                default: {
                    this.vertical((undefined as boolean | undefined));
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
                    this.onChange((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
    }
    initialIndex(value: number | undefined): this {
        if (((this._initialIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._initialIndex_0_0value) !== (value)))
        {
            this._initialIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._initialIndex_0_0value = value
        } else
        {
            this._initialIndex_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    count(value: number | undefined): this {
        if (((this._count_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._count_0_0value) !== (value)))
        {
            this._count_0_flag = AttributeUpdaterFlag.UPDATE
            this._count_0_0value = value
        } else
        {
            this._count_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    style(value: DotIndicator | DigitIndicator | undefined): this {
        if (((this._style_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._style_0_flag = AttributeUpdaterFlag.UPDATE
            this._style_0_0value = value
        } else
        {
            this._style_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._loop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._loop_0_0value) !== (value)))
        {
            this._loop_0_flag = AttributeUpdaterFlag.UPDATE
            this._loop_0_0value = value
        } else
        {
            this._loop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    vertical(value: boolean | undefined): this {
        if (((this._vertical_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._vertical_0_0value) !== (value)))
        {
            this._vertical_0_flag = AttributeUpdaterFlag.UPDATE
            this._vertical_0_0value = value
        } else
        {
            this._vertical_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value0: number) => void) | undefined): this {
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
    public attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
