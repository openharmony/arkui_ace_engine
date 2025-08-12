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

import { VoidCallback, Length, VP, ResourceColor, Font } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ICurve, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { IndicatorComponentController } from "./indicatorcomponent"
import { EdgeEffect, Curve, PageFlipMode } from "./enums"
import { Callback_Number_Void, Callback_Opt_Number_Void } from "./alphabetIndexer"
import { IndicatorStyle } from "./arkui-external"
import { Resource } from "global.resource"
import { NodeAttach, remember } from "@koalaui/runtime"

import { LengthMetrics } from "../Graphics"
export class SwiperControllerInternal {
    public static fromPtr(ptr: KPointer): SwiperController {
        const obj : SwiperController = new SwiperController()
        obj.peer = new Finalizable(ptr, SwiperController.getFinalizer())
        return obj
    }
}
export class SwiperController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_swipercontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwiperController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SwiperController.ctor_swipercontroller()
        this.peer = new Finalizable(ctorPtr, SwiperController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwiperController_getFinalizer()
    }
    public showNext(): undefined {
        return this.showNext_serialize()
    }
    public showPrevious(): undefined {
        return this.showPrevious_serialize()
    }
    public changeIndex(index: number, useAnimation?: boolean | undefined | SwiperAnimationMode | boolean | undefined): undefined {
        const index_type = runtimeType(index)
        const useAnimation_type = runtimeType(useAnimation)
        if ((RuntimeType.BOOLEAN == useAnimation_type) || (RuntimeType.UNDEFINED == useAnimation_type)) {
            const index_casted = index as (number)
            const useAnimation_casted = useAnimation as (boolean | undefined)
            return this.changeIndex0_serialize(index_casted, useAnimation_casted)
        }
        if ((RuntimeType.NUMBER == useAnimation_type) || (RuntimeType.BOOLEAN == useAnimation_type) || (RuntimeType.UNDEFINED == useAnimation_type)) {
            const index_casted = index as (number)
            const animationMode_casted = useAnimation as (SwiperAnimationMode | boolean | undefined)
            return this.changeIndex1_serialize(index_casted, animationMode_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public finishAnimation(callback_?: VoidCallback): undefined {
        const callback__casted = callback_ as (VoidCallback | undefined)
        return this.finishAnimation_serialize(callback__casted)
    }
    public preloadItems(indices: Array<number> | undefined): Promise<void> {
        const indices_casted = indices as (Array<number> | undefined)
        return this.preloadItems_serialize(indices_casted)
    }
    private showNext_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._SwiperController_showNext(this.peer!.ptr)
        return retval
    }
    private showPrevious_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._SwiperController_showPrevious(this.peer!.ptr)
        return retval
    }
    private changeIndex0_serialize(index: number, useAnimation?: boolean): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let useAnimation_type : int32 = RuntimeType.UNDEFINED
        useAnimation_type = runtimeType(useAnimation)
        thisSerializer.writeInt8(useAnimation_type as int32)
        if ((RuntimeType.UNDEFINED) != (useAnimation_type)) {
            const useAnimation_value  = useAnimation!
            thisSerializer.writeBoolean(useAnimation_value)
        }
        const retval  = ArkUIGeneratedNativeModule._SwiperController_changeIndex0(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private changeIndex1_serialize(index: number, animationMode?: SwiperAnimationMode | boolean): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let animationMode_type : int32 = RuntimeType.UNDEFINED
        animationMode_type = runtimeType(animationMode)
        thisSerializer.writeInt8(animationMode_type as int32)
        if ((RuntimeType.UNDEFINED) != (animationMode_type)) {
            const animationMode_value  = animationMode!
            let animationMode_value_type : int32 = RuntimeType.UNDEFINED
            animationMode_value_type = runtimeType(animationMode_value)
            if (TypeChecker.isSwiperAnimationMode(animationMode_value)) {
                thisSerializer.writeInt8(0 as int32)
                const animationMode_value_0  = animationMode_value as SwiperAnimationMode
                thisSerializer.writeInt32(TypeChecker.SwiperAnimationMode_ToNumeric(animationMode_value_0))
            }
            else if (RuntimeType.BOOLEAN == animationMode_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const animationMode_value_1  = animationMode_value as boolean
                thisSerializer.writeBoolean(animationMode_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._SwiperController_changeIndex1(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private finishAnimation_serialize(callback_?: VoidCallback): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        const retval  = ArkUIGeneratedNativeModule._SwiperController_finishAnimation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private preloadItems_serialize(indices: Array<number> | undefined): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        let indices_type : int32 = RuntimeType.UNDEFINED
        indices_type = runtimeType(indices)
        thisSerializer.writeInt8(indices_type as int32)
        if ((RuntimeType.UNDEFINED) != (indices_type)) {
            const indices_value  = indices!
            thisSerializer.writeInt32(indices_value.length as int32)
            for (let i = 0; i < indices_value.length; i++) {
                const indices_value_element : number = indices_value[i]
                thisSerializer.writeNumber(indices_value_element)
            }
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._SwiperController_preloadItems(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export interface SwiperContentTransitionProxy {
    selectedIndex: number
    index: number
    position: number
    mainAxisLength: number
    finishTransition(): void
}
export class SwiperContentTransitionProxyInternal implements MaterializedBase,SwiperContentTransitionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get selectedIndex(): number {
        return this.getSelectedIndex()
    }
    set selectedIndex(selectedIndex: number) {
        this.setSelectedIndex(selectedIndex)
    }
    get index(): number {
        return this.getIndex()
    }
    set index(index: number) {
        this.setIndex(index)
    }
    get position(): number {
        return this.getPosition()
    }
    set position(position: number) {
        this.setPosition(position)
    }
    get mainAxisLength(): number {
        return this.getMainAxisLength()
    }
    set mainAxisLength(mainAxisLength: number) {
        this.setMainAxisLength(mainAxisLength)
    }
    static ctor_swipercontenttransitionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SwiperContentTransitionProxyInternal.ctor_swipercontenttransitionproxy()
        this.peer = new Finalizable(ctorPtr, SwiperContentTransitionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getFinalizer()
    }
    public finishTransition(): void {
        this.finishTransition_serialize()
        return
    }
    private getSelectedIndex(): number {
        return this.getSelectedIndex_serialize()
    }
    private setSelectedIndex(selectedIndex: number): void {
        const selectedIndex_casted = selectedIndex as (number)
        this.setSelectedIndex_serialize(selectedIndex_casted)
        return
    }
    private getIndex(): number {
        return this.getIndex_serialize()
    }
    private setIndex(index: number): void {
        const index_casted = index as (number)
        this.setIndex_serialize(index_casted)
        return
    }
    private getPosition(): number {
        return this.getPosition_serialize()
    }
    private setPosition(position: number): void {
        const position_casted = position as (number)
        this.setPosition_serialize(position_casted)
        return
    }
    private getMainAxisLength(): number {
        return this.getMainAxisLength_serialize()
    }
    private setMainAxisLength(mainAxisLength: number): void {
        const mainAxisLength_casted = mainAxisLength as (number)
        this.setMainAxisLength_serialize(mainAxisLength_casted)
        return
    }
    private finishTransition_serialize(): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_finishTransition(this.peer!.ptr)
    }
    private getSelectedIndex_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getSelectedIndex(this.peer!.ptr)
        return retval
    }
    private setSelectedIndex_serialize(selectedIndex: number): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_setSelectedIndex(this.peer!.ptr, selectedIndex)
    }
    private getIndex_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getIndex(this.peer!.ptr)
        return retval
    }
    private setIndex_serialize(index: number): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_setIndex(this.peer!.ptr, index)
    }
    private getPosition_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getPosition(this.peer!.ptr)
        return retval
    }
    private setPosition_serialize(position: number): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_setPosition(this.peer!.ptr, position)
    }
    private getMainAxisLength_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getMainAxisLength(this.peer!.ptr)
        return retval
    }
    private setMainAxisLength_serialize(mainAxisLength: number): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_setMainAxisLength(this.peer!.ptr, mainAxisLength)
    }
    public static fromPtr(ptr: KPointer): SwiperContentTransitionProxyInternal {
        const obj : SwiperContentTransitionProxyInternal = new SwiperContentTransitionProxyInternal()
        obj.peer = new Finalizable(ptr, SwiperContentTransitionProxyInternal.getFinalizer())
        return obj
    }
}
export class ArkSwiperPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSwiperPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Swiper_construct(peerId, flags)
        const _peer  = new ArkSwiperPeer(_peerPtr, peerId, "Swiper", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSwiperOptionsAttribute(controller?: SwiperController): void {
        const thisSerializer : Serializer = Serializer.hold()
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8(controller_type as int32)
        if ((RuntimeType.UNDEFINED) != (controller_type)) {
            const controller_value  = controller!
            thisSerializer.writeSwiperController(controller_value)
        }
        ArkUIGeneratedNativeModule._SwiperInterface_setSwiperOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indexAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoPlay0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_autoPlay0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoPlay1Attribute(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let autoPlay_type : int32 = RuntimeType.UNDEFINED
        autoPlay_type = runtimeType(autoPlay)
        thisSerializer.writeInt8(autoPlay_type as int32)
        if ((RuntimeType.UNDEFINED) != (autoPlay_type)) {
            const autoPlay_value  = autoPlay!
            thisSerializer.writeBoolean(autoPlay_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeAutoPlayOptions(options_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_autoPlay1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    intervalAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_interval(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicator0Attribute(value: DotIndicator | DigitIndicator | boolean | undefined): void {
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
            else if (RuntimeType.BOOLEAN == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as boolean
                thisSerializer.writeBoolean(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicator0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicator1Attribute(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isIndicatorComponentController(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as IndicatorComponentController
                thisSerializer.writeIndicatorComponentController(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isDotIndicator(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as DotIndicator
                thisSerializer.writeDotIndicator(value_value_1)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isDigitIndicator(value_value))) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as DigitIndicator
                thisSerializer.writeDigitIndicator(value_value_2)
            }
            else if (RuntimeType.BOOLEAN == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as boolean
                thisSerializer.writeBoolean(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicator1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SwiperAttribute_loop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    durationAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_duration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SwiperAttribute_vertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    itemSpaceAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_itemSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    displayModeAttribute(value: SwiperDisplayMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SwiperDisplayMode)
            thisSerializer.writeInt32(TypeChecker.SwiperDisplayMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_displayMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_cachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount1Attribute(count: number | undefined, isShown: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8(count_type as int32)
        if ((RuntimeType.UNDEFINED) != (count_type)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let isShown_type : int32 = RuntimeType.UNDEFINED
        isShown_type = runtimeType(isShown)
        thisSerializer.writeInt8(isShown_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShown_type)) {
            const isShown_value  = isShown!
            thisSerializer.writeBoolean(isShown_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_cachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    effectModeAttribute(value: EdgeEffect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_effectMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    disableSwipeAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_disableSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    curveAttribute(value: Curve | string | ICurve | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isCurve(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Curve
                thisSerializer.writeInt32(TypeChecker.Curve_ToNumeric(value_value_0))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as ICurve
                thisSerializer.writeICurve(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_curve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SwiperAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectedAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_onSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorStyleAttribute(value: IndicatorStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeIndicatorStyle(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicatorStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUnselectedAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_onUnselected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationStartAttribute(value: OnSwiperAnimationStartCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_onAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationEndAttribute(value: OnSwiperAnimationEndCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_onAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureSwipeAttribute(value: OnSwiperGestureSwipeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_onGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: SwiperNestedScrollMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SwiperNestedScrollMode)
            thisSerializer.writeInt32(TypeChecker.SwiperNestedScrollMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customContentTransitionAttribute(value: SwiperContentAnimatedTransition | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSwiperContentAnimatedTransition(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_customContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentDidScrollAttribute(value: ContentDidScrollCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_onContentDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorInteractiveAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicatorInteractive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pageFlipModeAttribute(value: PageFlipMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as PageFlipMode)
            thisSerializer.writeInt32(TypeChecker.PageFlipMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_pageFlipMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentWillScrollAttribute(value: ContentWillScrollCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_onContentWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    displayArrowAttribute(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ArrowStyle
                thisSerializer.writeArrowStyle(value_value_0)
            }
            else if (RuntimeType.BOOLEAN == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as boolean
                thisSerializer.writeBoolean(value_value_1)
            }
        }
        let isHoverShow_type : int32 = RuntimeType.UNDEFINED
        isHoverShow_type = runtimeType(isHoverShow)
        thisSerializer.writeInt8(isHoverShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isHoverShow_type)) {
            const isHoverShow_value  = isHoverShow!
            thisSerializer.writeBoolean(isHoverShow_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_displayArrow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    displayCountAttribute(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as SwiperAutoFill
                thisSerializer.writeSwiperAutoFill(value_value_2)
            }
        }
        let swipeByGroup_type : int32 = RuntimeType.UNDEFINED
        swipeByGroup_type = runtimeType(swipeByGroup)
        thisSerializer.writeInt8(swipeByGroup_type as int32)
        if ((RuntimeType.UNDEFINED) != (swipeByGroup_type)) {
            const swipeByGroup_value  = swipeByGroup!
            thisSerializer.writeBoolean(swipeByGroup_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_displayCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    prevMarginAttribute(value: Length | undefined, ignoreBlank?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        let ignoreBlank_type : int32 = RuntimeType.UNDEFINED
        ignoreBlank_type = runtimeType(ignoreBlank)
        thisSerializer.writeInt8(ignoreBlank_type as int32)
        if ((RuntimeType.UNDEFINED) != (ignoreBlank_type)) {
            const ignoreBlank_value  = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlank_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_prevMargin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nextMarginAttribute(value: Length | undefined, ignoreBlank?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        let ignoreBlank_type : int32 = RuntimeType.UNDEFINED
        ignoreBlank_type = runtimeType(ignoreBlank)
        thisSerializer.writeInt8(ignoreBlank_type as int32)
        if ((RuntimeType.UNDEFINED) != (ignoreBlank_type)) {
            const ignoreBlank_value  = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlank_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_nextMargin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_indexAttribute(callback: ((selected: number | undefined) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SwiperAttribute__onChangeEvent_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface SwiperAutoFill {
    minSize: VP;
}
export interface ArrowStyle {
    showBackground?: boolean;
    isSidebarMiddle?: boolean;
    backgroundSize?: Length;
    backgroundColor?: ResourceColor;
    arrowSize?: Length;
    arrowColor?: ResourceColor;
}
export enum SwiperDisplayMode {
    LEGACY_STRETCH = 0,
    Stretch = 0,
    LEGACY_AUTO_LINEAR = 1,
    AutoLinear = 1,
    STRETCH = 2,
    AUTO_LINEAR = 3
}
export type SwiperInterface = (controller?: SwiperController) => SwiperAttribute;
export interface SwiperAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
export interface AutoPlayOptions {
    stopWhenTouched: boolean;
}
export enum SwiperNestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1
}
export enum SwiperAnimationMode {
    NO_ANIMATION = 0,
    DEFAULT_ANIMATION = 1,
    FAST_ANIMATION = 2
}
export type OnSwiperAnimationStartCallback = (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void;
export type OnSwiperAnimationEndCallback = (index: number, extraInfo: SwiperAnimationEvent) => void;
export type OnSwiperGestureSwipeCallback = (index: number, extraInfo: SwiperAnimationEvent) => void;
export interface SwiperAttribute extends CommonMethod {
    index(value: number | undefined): this
    autoPlay(autoPlay: boolean | undefined, options?: AutoPlayOptions): this
    interval(value: number | undefined): this
    indicator(value: DotIndicator | DigitIndicator | boolean | undefined | IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this
    loop(value: boolean | undefined): this
    duration(value: number | undefined): this
    vertical(value: boolean | undefined): this
    itemSpace(value: number | string | undefined): this
    displayMode(value: SwiperDisplayMode | undefined): this
    cachedCount(count: number | undefined, isShown?: boolean): this
    effectMode(value: EdgeEffect | undefined): this
    disableSwipe(value: boolean | undefined): this
    curve(value: Curve | string | ICurve | undefined): this
    onChange(value: ((index: number) => void) | undefined): this
    onSelected(value: ((index: number) => void) | undefined): this
    indicatorStyle(value: IndicatorStyle | undefined): this
    onUnselected(value: ((index: number) => void) | undefined): this
    onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this
    onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this
    onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this
    nestedScroll(value: SwiperNestedScrollMode | undefined): this
    customContentTransition(value: SwiperContentAnimatedTransition | undefined): this
    onContentDidScroll(value: ContentDidScrollCallback | undefined): this
    indicatorInteractive(value: boolean | undefined): this
    pageFlipMode(value: PageFlipMode | undefined): this
    onContentWillScroll(value: ContentWillScrollCallback | undefined): this
    displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this
    displayCount(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this
    prevMargin(value: Length | undefined, ignoreBlank?: boolean): this
    nextMargin(value: Length | undefined, ignoreBlank?: boolean): this
    _onChangeEvent_index(callback: ((selected: number | undefined) => void)): void
}
export class ArkSwiperStyle extends ArkCommonMethodStyle implements SwiperAttribute {
    index_value?: number | undefined
    autoPlay_value?: boolean | undefined
    interval_value?: number | undefined
    indicator_value?: DotIndicator | DigitIndicator | boolean | undefined
    loop_value?: boolean | undefined
    duration_value?: number | undefined
    vertical_value?: boolean | undefined
    itemSpace_value?: number | string | undefined
    displayMode_value?: SwiperDisplayMode | undefined
    cachedCount_value?: number | undefined
    effectMode_value?: EdgeEffect | undefined
    disableSwipe_value?: boolean | undefined
    curve_value?: Curve | string | ICurve | undefined
    onChange_value?: ((index: number) => void) | undefined
    onSelected_value?: ((index: number) => void) | undefined
    indicatorStyle_value?: IndicatorStyle
    onUnselected_value?: ((index: number) => void) | undefined
    onAnimationStart_value?: OnSwiperAnimationStartCallback | undefined
    onAnimationEnd_value?: OnSwiperAnimationEndCallback | undefined
    onGestureSwipe_value?: OnSwiperGestureSwipeCallback | undefined
    nestedScroll_value?: SwiperNestedScrollMode | undefined
    customContentTransition_value?: SwiperContentAnimatedTransition | undefined
    onContentDidScroll_value?: ContentDidScrollCallback | undefined
    indicatorInteractive_value?: boolean | undefined
    pageFlipMode_value?: PageFlipMode | undefined
    onContentWillScroll_value?: ContentWillScrollCallback | undefined
    public index(value: number | undefined): this {
        return this
    }
    public autoPlay(autoPlay: boolean | undefined, options?: AutoPlayOptions): this {
        return this
    }
    public interval(value: number | undefined): this {
        return this
    }
    public indicator(value: DotIndicator | DigitIndicator | boolean | undefined | IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        return this
    }
    public loop(value: boolean | undefined): this {
        return this
    }
    public duration(value: number | undefined): this {
        return this
    }
    public vertical(value: boolean | undefined): this {
        return this
    }
    public itemSpace(value: number | string | undefined): this {
        return this
    }
    public displayMode(value: SwiperDisplayMode | undefined): this {
        return this
    }
    public cachedCount(count: number | undefined, isShown?: boolean): this {
        return this
    }
    public effectMode(value: EdgeEffect | undefined): this {
        return this
    }
    public disableSwipe(value: boolean | undefined): this {
        return this
    }
    public curve(value: Curve | string | ICurve | undefined): this {
        return this
    }
    public onChange(value: ((index: number) => void) | undefined): this {
        return this
    }
    public onSelected(value: ((index: number) => void) | undefined): this {
        return this
    }
    public indicatorStyle(value: IndicatorStyle | undefined): this {
        return this
    }
    public onUnselected(value: ((index: number) => void) | undefined): this {
        return this
    }
    public onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        return this
    }
    public onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        return this
    }
    public onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        return this
    }
    public nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        return this
    }
    public customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        return this
    }
    public onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        return this
    }
    public indicatorInteractive(value: boolean | undefined): this {
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        return this
    }
    public onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        return this
    }
    public displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        return this
    }
    public displayCount(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        return this
    }
    public prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        return this
    }
    public nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        return this
    }
    public _onChangeEvent_index(callback: ((selected: number | undefined) => void)): void {
        throw new Error("Unimplmented")
        }
}
export type Callback_SwiperContentTransitionProxy_Void = (parameter: SwiperContentTransitionProxy) => void;
export interface SwiperContentAnimatedTransition {
    timeout?: number;
    transition: ((parameter: SwiperContentTransitionProxy) => void);
}
export interface SwiperContentWillScrollResult {
    currentIndex: number;
    comingIndex: number;
    offset: number;
}
export type ContentDidScrollCallback = (selectedIndex: number, index: number, position: number, mainAxisLength: number) => void;
export type ContentWillScrollCallback = (result: SwiperContentWillScrollResult) => boolean;
export class ArkSwiperComponent extends ArkCommonMethodComponent implements SwiperAttribute {
    getPeer(): ArkSwiperPeer {
        return (this.peer as ArkSwiperPeer)
    }
    public setSwiperOptions(controller?: SwiperController): this {
        if (this.checkPriority("setSwiperOptions")) {
            const controller_casted = controller as (SwiperController | undefined)
            this.getPeer()?.setSwiperOptionsAttribute(controller_casted)
            return this
        }
        return this
    }
    public index(value: number | undefined): this {
        if (this.checkPriority("index")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.indexAttribute(value_casted)
            return this
        }
        return this
    }
    public autoPlay(autoPlay: boolean | undefined, options?: AutoPlayOptions): this {
        if (this.checkPriority("autoPlay")) {
            const autoPlay_type = runtimeType(autoPlay)
            const options_type = runtimeType(options)
            if (((RuntimeType.BOOLEAN == autoPlay_type) || (RuntimeType.UNDEFINED == autoPlay_type)) && (RuntimeType.UNDEFINED == options_type)) {
                const value_casted = autoPlay as (boolean | undefined)
                this.getPeer()?.autoPlay0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == autoPlay_type) || (RuntimeType.UNDEFINED == autoPlay_type)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const autoPlay_casted = autoPlay as (boolean | undefined)
                const options_casted = options as (AutoPlayOptions | undefined)
                this.getPeer()?.autoPlay1Attribute(autoPlay_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public interval(value: number | undefined): this {
        if (this.checkPriority("interval")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.intervalAttribute(value_casted)
            return this
        }
        return this
    }
    public indicator(value: DotIndicator | DigitIndicator | boolean | undefined | IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        if (this.checkPriority("indicator")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (DotIndicator | DigitIndicator | boolean | undefined)
                this.getPeer()?.indicator0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined)
                this.getPeer()?.indicator1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
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
    public duration(value: number | undefined): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.durationAttribute(value_casted)
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
    public itemSpace(value: number | string | undefined): this {
        if (this.checkPriority("itemSpace")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.itemSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public displayMode(value: SwiperDisplayMode | undefined): this {
        if (this.checkPriority("displayMode")) {
            const value_casted = value as (SwiperDisplayMode | undefined)
            this.getPeer()?.displayModeAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(count: number | undefined, isShown?: boolean): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(count)
            const isShown_type = runtimeType(isShown)
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) && (RuntimeType.UNDEFINED == isShown_type)) {
                const value_casted = count as (number | undefined)
                this.getPeer()?.cachedCount0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) && ((RuntimeType.BOOLEAN == isShown_type) || (RuntimeType.UNDEFINED == isShown_type))) {
                const count_casted = count as (number | undefined)
                const isShown_casted = isShown as (boolean | undefined)
                this.getPeer()?.cachedCount1Attribute(count_casted, isShown_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public effectMode(value: EdgeEffect | undefined): this {
        if (this.checkPriority("effectMode")) {
            const value_casted = value as (EdgeEffect | undefined)
            this.getPeer()?.effectModeAttribute(value_casted)
            return this
        }
        return this
    }
    public disableSwipe(value: boolean | undefined): this {
        if (this.checkPriority("disableSwipe")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.disableSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    public curve(value: Curve | string | ICurve | undefined): this {
        if (this.checkPriority("curve")) {
            const value_casted = value as (Curve | string | ICurve | undefined)
            this.getPeer()?.curveAttribute(value_casted)
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
    public onSelected(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onSelected")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public indicatorStyle(value: IndicatorStyle | undefined): this {
        if (this.checkPriority("indicatorStyle")) {
            const value_casted = value as (IndicatorStyle | undefined)
            this.getPeer()?.indicatorStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onUnselected(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onUnselected")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onUnselectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        if (this.checkPriority("onAnimationStart")) {
            const value_casted = value as (OnSwiperAnimationStartCallback | undefined)
            this.getPeer()?.onAnimationStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        if (this.checkPriority("onAnimationEnd")) {
            const value_casted = value as (OnSwiperAnimationEndCallback | undefined)
            this.getPeer()?.onAnimationEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        if (this.checkPriority("onGestureSwipe")) {
            const value_casted = value as (OnSwiperGestureSwipeCallback | undefined)
            this.getPeer()?.onGestureSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (SwiperNestedScrollMode | undefined)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        if (this.checkPriority("customContentTransition")) {
            const value_casted = value as (SwiperContentAnimatedTransition | undefined)
            this.getPeer()?.customContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        if (this.checkPriority("onContentDidScroll")) {
            const value_casted = value as (ContentDidScrollCallback | undefined)
            this.getPeer()?.onContentDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public indicatorInteractive(value: boolean | undefined): this {
        if (this.checkPriority("indicatorInteractive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.indicatorInteractiveAttribute(value_casted)
            return this
        }
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        if (this.checkPriority("pageFlipMode")) {
            const value_casted = value as (PageFlipMode | undefined)
            this.getPeer()?.pageFlipModeAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        if (this.checkPriority("onContentWillScroll")) {
            const value_casted = value as (ContentWillScrollCallback | undefined)
            this.getPeer()?.onContentWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        if (this.checkPriority("displayArrow")) {
            const value_casted = value as (ArrowStyle | boolean | undefined)
            const isHoverShow_casted = isHoverShow as (boolean)
            this.getPeer()?.displayArrowAttribute(value_casted, isHoverShow_casted)
            return this
        }
        return this
    }
    public displayCount(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        if (this.checkPriority("displayCount")) {
            const value_casted = value as (number | string | SwiperAutoFill | undefined)
            const swipeByGroup_casted = swipeByGroup as (boolean)
            this.getPeer()?.displayCountAttribute(value_casted, swipeByGroup_casted)
            return this
        }
        return this
    }
    public prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (this.checkPriority("prevMargin")) {
            const value_casted = value as (Length | undefined)
            const ignoreBlank_casted = ignoreBlank as (boolean)
            this.getPeer()?.prevMarginAttribute(value_casted, ignoreBlank_casted)
            return this
        }
        return this
    }
    public nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (this.checkPriority("nextMargin")) {
            const value_casted = value as (Length | undefined)
            const ignoreBlank_casted = ignoreBlank as (boolean)
            this.getPeer()?.nextMarginAttribute(value_casted, ignoreBlank_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_index(callback: ((selected: number | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_index")) {
            const callback_casted = callback as (((selected: number | undefined) => void))
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
export function Swiper(
    /** @memo */
    style: ((attributes: SwiperAttribute) => void) | undefined,
    controller?: SwiperController,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkSwiperComponent()
    })
    NodeAttach<ArkSwiperPeer>((): ArkSwiperPeer => ArkSwiperPeer.create(receiver), (_: ArkSwiperPeer) => {
        receiver.setSwiperOptions(controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
export class Indicator {
    _left?: Length | undefined
    _top?: Length | undefined
    _right?: Length | undefined
    _bottom?: Length | undefined
    _start?: LengthMetrics | undefined
    _end?: LengthMetrics | undefined
    constructor() {
    }
    static dot(): DotIndicator {
        return new DotIndicator()
    }
    static digit(): DigitIndicator {
        return new DigitIndicator()
    }
    left(value: Length): this {
        this._left = value
        return this
    }
    top(value: Length): this {
        this._top = value
        return this
    }
    right(value: Length): this {
        this._right = value
        return this
    }
    bottom(value: Length): this {
        this._bottom = value
        return this
    }
    start(value: LengthMetrics): this {
        this._start = value
        return this
    }
    end(value: LengthMetrics): this {
        this._end = value
        return this
    }
}
export class DotIndicator {
    _left?: Length | undefined
    _top?: Length | undefined
    _right?: Length | undefined
    _bottom?: Length | undefined
    _start?: LengthMetrics | undefined
    _end?: LengthMetrics | undefined
    _itemWidth?: Length | undefined
    _itemHeight?: Length | undefined
    _selectedItemWidth?: Length | undefined
    _selectedItemHeight?: Length | undefined
    _mask?: boolean | undefined
    _color?: ResourceColor | undefined
    _selectedColor?: ResourceColor | undefined
    _maxDisplayCount?: number | undefined
    _space?: LengthMetrics | undefined
    constructor() {
    }
    static dot(): DotIndicator {
        return new DotIndicator()
    }
    static digit(): DigitIndicator {
        return new DigitIndicator()
    }
    left(value: Length): this {
        this._left = value
        return this
    }
    top(value: Length): this {
        this._top = value
        return this
    }
    right(value: Length): this {
        this._right = value
        return this
    }
    bottom(value: Length): this {
        this._bottom = value
        return this
    }
    start(value: LengthMetrics): this {
        this._start = value
        return this
    }
    end(value: LengthMetrics): this {
        this._end = value
        return this
    }
    itemWidth(value: Length): this {
        this._itemWidth = value
        return this
    }
    itemHeight(value: Length): this {
        this._itemHeight = value
        return this
    }
    selectedItemWidth(value: Length): this {
        this._selectedItemWidth = value
        return this
    }
    selectedItemHeight(value: Length): this {
        this._selectedItemHeight = value
        return this
    }
    mask(value: boolean): this {
        this._mask = value
        return this
    }
    color(value: ResourceColor): this {
        this._color = value
        return this
    }
    selectedColor(value: ResourceColor): this {
        this._selectedColor = value
        return this
    }
    maxDisplayCount(maxDisplayCount: number): this {
        this._maxDisplayCount = maxDisplayCount
        return this
    }
    space(space: LengthMetrics): this {
        this._space = space
        return this
    }
}
export class DigitIndicator {
    _left?: Length | undefined
    _top?: Length | undefined
    _right?: Length | undefined
    _bottom?: Length | undefined
    _start?: LengthMetrics | undefined
    _end?: LengthMetrics | undefined
    _fontColor?: ResourceColor | undefined
    _selectedFontColor?: ResourceColor | undefined
    _digitFont?: Font | undefined
    _selectedDigitFont?: Font | undefined
    constructor() {
    }
    static dot(): DotIndicator {
        return new DotIndicator()
    }
    static digit(): DigitIndicator {
        return new DigitIndicator()
    }
    left(value: Length): this {
        this._left = value
        return this
    }
    top(value: Length): this {
        this._top = value
        return this
    }
    right(value: Length): this {
        this._right = value
        return this
    }
    bottom(value: Length): this {
        this._bottom = value
        return this
    }
    start(value: LengthMetrics): this {
        this._start = value
        return this
    }
    end(value: LengthMetrics): this {
        this._end = value
        return this
    }
    fontColor(value: ResourceColor): this {
        this._fontColor = value
        return this
    }
    selectedFontColor(value: ResourceColor): this {
        this._selectedFontColor = value
        return this
    }
    digitFont(value: Font): this {
        this._digitFont = value
        return this
    }
    selectedDigitFont(value: Font): this {
        this._selectedDigitFont = value
        return this
    }
}
