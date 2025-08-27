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
import { DotIndicator, DigitIndicator } from "./swiper"
import { Callback_Number_Void } from "./alphabetIndexer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class IndicatorComponentControllerInternal {
    public static fromPtr(ptr: KPointer): IndicatorComponentController {
        const obj : IndicatorComponentController = new IndicatorComponentController()
        obj.peer = new Finalizable(ptr, IndicatorComponentController.getFinalizer())
        return obj
    }
}
export class IndicatorComponentController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_indicatorcomponentcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._IndicatorComponentController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = IndicatorComponentController.ctor_indicatorcomponentcontroller()
        this.peer = new Finalizable(ctorPtr, IndicatorComponentController.getFinalizer())
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
        const thisSerializer : Serializer = Serializer.hold()
        let useAnimation_type : int32 = RuntimeType.UNDEFINED
        useAnimation_type = runtimeType(useAnimation)
        thisSerializer.writeInt8(useAnimation_type as int32)
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkIndicatorComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._IndicatorComponent_construct(peerId, flags)
        const _peer  = new ArkIndicatorComponentPeer(_peerPtr, peerId, "IndicatorComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setIndicatorComponentOptionsAttribute(controller?: IndicatorComponentController): void {
        const thisSerializer : Serializer = Serializer.hold()
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8(controller_type as int32)
        if ((RuntimeType.UNDEFINED) != (controller_type)) {
            const controller_value  = controller!
            thisSerializer.writeIndicatorComponentController(controller_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentInterface_setIndicatorComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    initialIndexAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_initialIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    countAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_count(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    styleAttribute(value: DotIndicator | DigitIndicator | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isDotIndicator(value_value))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as DotIndicator
                thisSerializer.writeDotIndicator(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isDigitIndicator(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as DigitIndicator
                thisSerializer.writeDigitIndicator(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_style(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    loopAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_loop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    verticalAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_vertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type IndicatorComponentInterface = (controller?: IndicatorComponentController) => IndicatorComponentAttribute;
export interface IndicatorComponentAttribute extends CommonMethod {
    initialIndex(value: number | undefined): this
    count(value: number | undefined): this
    style(value: DotIndicator | DigitIndicator | undefined): this
    loop(value: boolean | undefined): this
    vertical(value: boolean | undefined): this
    onChange(value: ((index: number) => void) | undefined): this
}
export class ArkIndicatorComponentStyle extends ArkCommonMethodStyle implements IndicatorComponentAttribute {
    initialIndex_value?: number | undefined
    count_value?: number | undefined
    style_value?: DotIndicator | DigitIndicator | undefined
    loop_value?: boolean | undefined
    vertical_value?: boolean | undefined
    onChange_value?: ((index: number) => void) | undefined
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
    public onChange(value: ((index: number) => void) | undefined): this {
        return this
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
    public onChange(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((index: number) => void) | undefined)
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
export function IndicatorComponent(
    /** @memo */
    style: ((attributes: IndicatorComponentAttribute) => void) | undefined,
    controller?: IndicatorComponentController,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkIndicatorComponentComponent()
    })
    NodeAttach<ArkIndicatorComponentPeer>((): ArkIndicatorComponentPeer => ArkIndicatorComponentPeer.create(receiver), (_: ArkIndicatorComponentPeer) => {
        receiver.setIndicatorComponentOptions(controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
