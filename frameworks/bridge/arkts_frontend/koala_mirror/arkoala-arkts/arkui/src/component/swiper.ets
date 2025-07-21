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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { VoidCallback, Length, ResourceColor, VP, Font, Font_serializer } from "./units"
import { IndicatorComponentController_serializer, IndicatorComponentController } from "./indicatorcomponent"
import { curves_ICurve_serializer, curves } from "./../generated/ohos.curves"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { EdgeEffect, PageFlipMode, Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
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
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SwiperContentTransitionProxyInternal.getFinalizer())
    }
    constructor() {
        this(SwiperContentTransitionProxyInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): SwiperContentTransitionProxyInternal {
        return new SwiperContentTransitionProxyInternal(ptr)
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
}
export class SwiperControllerInternal {
    public static fromPtr(ptr: KPointer): SwiperController {
        return new SwiperController(ptr)
    }
}
export class SwiperController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SwiperController.getFinalizer())
    }
    constructor() {
        this(SwiperController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwiperController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwiperController_getFinalizer()
    }
    public showNext(): void {
        this.showNext_serialize()
        return
    }
    public showPrevious(): void {
        this.showPrevious_serialize()
        return
    }
    public changeIndex(index: number, animationMode?: SwiperAnimationMode | boolean): void {
        const index_casted = index as (number)
        const animationMode_casted = animationMode as (SwiperAnimationMode | boolean | undefined)
        this.changeIndex_serialize(index_casted, animationMode_casted)
        return
    }
    public finishAnimation(callback_?: VoidCallback): void {
        const callback__casted = callback_ as (VoidCallback | undefined)
        this.finishAnimation_serialize(callback__casted)
        return
    }
    public preloadItems(indices: Array<number> | undefined): Promise<void> {
        const indices_casted = indices as (Array<number> | undefined)
        return this.preloadItems_serialize(indices_casted)
    }
    private showNext_serialize(): void {
        ArkUIGeneratedNativeModule._SwiperController_showNext(this.peer!.ptr)
    }
    private showPrevious_serialize(): void {
        ArkUIGeneratedNativeModule._SwiperController_showPrevious(this.peer!.ptr)
    }
    private changeIndex_serialize(index: number, animationMode?: SwiperAnimationMode | boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animationMode_type : int32 = RuntimeType.UNDEFINED
        animationMode_type = runtimeType(animationMode)
        thisSerializer.writeInt8((animationMode_type).toChar())
        if ((animationMode_type) != (RuntimeType.UNDEFINED)) {
            const animationMode_value  = animationMode!
            let animationMode_value_type : int32 = RuntimeType.UNDEFINED
            animationMode_value_type = runtimeType(animationMode_value)
            if (TypeChecker.isSwiperAnimationMode(animationMode_value)) {
                thisSerializer.writeInt8((0).toChar())
                const animationMode_value_0  = animationMode_value as SwiperAnimationMode
                thisSerializer.writeInt32(TypeChecker.SwiperAnimationMode_ToNumeric(animationMode_value_0))
            }
            else if (RuntimeType.BOOLEAN == animationMode_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const animationMode_value_1  = animationMode_value as boolean
                thisSerializer.writeBoolean(animationMode_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SwiperController_changeIndex(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private finishAnimation_serialize(callback_?: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8((callback__type).toChar())
        if ((callback__type) != (RuntimeType.UNDEFINED)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._SwiperController_finishAnimation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private preloadItems_serialize(indices: Array<number> | undefined): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let indices_type : int32 = RuntimeType.UNDEFINED
        indices_type = runtimeType(indices)
        thisSerializer.writeInt8((indices_type).toChar())
        if ((indices_type) != (RuntimeType.UNDEFINED)) {
            const indices_value  = indices!
            thisSerializer.writeInt32((indices_value.length).toInt())
            for (let indices_value_counter_i = 0; indices_value_counter_i < indices_value.length; indices_value_counter_i++) {
                const indices_value_element : number = indices_value[indices_value_counter_i]
                thisSerializer.writeNumber(indices_value_element)
            }
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._SwiperController_preloadItems(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export class ArkSwiperPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSwiperPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Swiper_construct(peerId, flags)
        const _peer  = new ArkSwiperPeer(_peerPtr, peerId, "Swiper", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSwiperOptionsAttribute(controller?: SwiperController): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8((controller_type).toChar())
        if ((controller_type) != (RuntimeType.UNDEFINED)) {
            const controller_value  = controller!
            SwiperController_serializer.write(thisSerializer, controller_value)
        }
        ArkUIGeneratedNativeModule._SwiperInterface_setSwiperOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndexAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIntervalAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setInterval(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorAttribute(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isIndicatorComponentController(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as IndicatorComponentController
                IndicatorComponentController_serializer.write(thisSerializer, value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isDotIndicator(value_value))) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as DotIndicator
                DotIndicator_serializer.write(thisSerializer, value_value_1)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isDigitIndicator(value_value))) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as DigitIndicator
                DigitIndicator_serializer.write(thisSerializer, value_value_2)
            }
            else if (RuntimeType.BOOLEAN == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as boolean
                thisSerializer.writeBoolean(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDurationAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setVertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemSpaceAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setItemSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisplayModeAttribute(value: SwiperDisplayMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SwiperDisplayMode)
            thisSerializer.writeInt32(TypeChecker.SwiperDisplayMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDisplayMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEffectModeAttribute(value: EdgeEffect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setEffectMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisableSwipeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDisableSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCurveAttribute(value: curves.Curve | string | curves.ICurve | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.iscurves_Curve(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as curves.Curve
                thisSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(value_value_0))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as curves.ICurve
                curves_ICurve_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setCurve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUnselectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnUnselected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAnimationStartAttribute(value: OnSwiperAnimationStartCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAnimationEndAttribute(value: OnSwiperAnimationEndCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGestureSwipeAttribute(value: OnSwiperGestureSwipeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNestedScrollAttribute(value: SwiperNestedScrollMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SwiperNestedScrollMode)
            thisSerializer.writeInt32(TypeChecker.SwiperNestedScrollMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomContentTransitionAttribute(value: SwiperContentAnimatedTransition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SwiperContentAnimatedTransition_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setCustomContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentDidScrollAttribute(value: ContentDidScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnContentDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorInteractiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setIndicatorInteractive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPageFlipModeAttribute(value: PageFlipMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as PageFlipMode)
            thisSerializer.writeInt32(TypeChecker.PageFlipMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setPageFlipMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentWillScrollAttribute(value: ContentWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnContentWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoPlayAttribute(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let autoPlay_type : int32 = RuntimeType.UNDEFINED
        autoPlay_type = runtimeType(autoPlay)
        thisSerializer.writeInt8((autoPlay_type).toChar())
        if ((autoPlay_type) != (RuntimeType.UNDEFINED)) {
            const autoPlay_value  = autoPlay!
            thisSerializer.writeBoolean(autoPlay_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            AutoPlayOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setAutoPlay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisplayArrowAttribute(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ArrowStyle
                ArrowStyle_serializer.write(thisSerializer, value_value_0)
            }
            else if (RuntimeType.BOOLEAN == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as boolean
                thisSerializer.writeBoolean(value_value_1)
            }
        }
        let isHoverShow_type : int32 = RuntimeType.UNDEFINED
        isHoverShow_type = runtimeType(isHoverShow)
        thisSerializer.writeInt8((isHoverShow_type).toChar())
        if ((isHoverShow_type) != (RuntimeType.UNDEFINED)) {
            const isHoverShow_value  = isHoverShow!
            thisSerializer.writeBoolean(isHoverShow_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDisplayArrow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount1Attribute(count: number | undefined, isShown: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8((count_type).toChar())
        if ((count_type) != (RuntimeType.UNDEFINED)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let isShown_type : int32 = RuntimeType.UNDEFINED
        isShown_type = runtimeType(isShown)
        thisSerializer.writeInt8((isShown_type).toChar())
        if ((isShown_type) != (RuntimeType.UNDEFINED)) {
            const isShown_value  = isShown!
            thisSerializer.writeBoolean(isShown_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setCachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisplayCountAttribute(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as SwiperAutoFill
                SwiperAutoFill_serializer.write(thisSerializer, value_value_2)
            }
        }
        let swipeByGroup_type : int32 = RuntimeType.UNDEFINED
        swipeByGroup_type = runtimeType(swipeByGroup)
        thisSerializer.writeInt8((swipeByGroup_type).toChar())
        if ((swipeByGroup_type) != (RuntimeType.UNDEFINED)) {
            const swipeByGroup_value  = swipeByGroup!
            thisSerializer.writeBoolean(swipeByGroup_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDisplayCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrevMarginAttribute(value: Length | undefined, ignoreBlank?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        let ignoreBlank_type : int32 = RuntimeType.UNDEFINED
        ignoreBlank_type = runtimeType(ignoreBlank)
        thisSerializer.writeInt8((ignoreBlank_type).toChar())
        if ((ignoreBlank_type) != (RuntimeType.UNDEFINED)) {
            const ignoreBlank_value  = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlank_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setPrevMargin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNextMarginAttribute(value: Length | undefined, ignoreBlank?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        let ignoreBlank_type : int32 = RuntimeType.UNDEFINED
        ignoreBlank_type = runtimeType(ignoreBlank)
        thisSerializer.writeInt8((ignoreBlank_type).toChar())
        if ((ignoreBlank_type) != (RuntimeType.UNDEFINED)) {
            const ignoreBlank_value  = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlank_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setNextMargin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_indexAttribute(callback_: ((index: number | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._SwiperAttribute_set_onChangeEvent_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    STRETCH = 0
}
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
    index(value: number | undefined): this {
        throw new Error("Unimplemented method index")
    }
    interval(value: number | undefined): this {
        throw new Error("Unimplemented method interval")
    }
    indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        throw new Error("Unimplemented method indicator")
    }
    loop(value: boolean | undefined): this {
        throw new Error("Unimplemented method loop")
    }
    duration(value: number | undefined): this {
        throw new Error("Unimplemented method duration")
    }
    vertical(value: boolean | undefined): this {
        throw new Error("Unimplemented method vertical")
    }
    itemSpace(value: number | string | undefined): this {
        throw new Error("Unimplemented method itemSpace")
    }
    displayMode(value: SwiperDisplayMode | undefined): this {
        throw new Error("Unimplemented method displayMode")
    }
    cachedCount(value: number | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    effectMode(value: EdgeEffect | undefined): this {
        throw new Error("Unimplemented method effectMode")
    }
    disableSwipe(value: boolean | undefined): this {
        throw new Error("Unimplemented method disableSwipe")
    }
    curve(value: curves.Curve | string | curves.ICurve | undefined): this {
        throw new Error("Unimplemented method curve")
    }
    onChange(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onSelected(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onSelected")
    }
    onUnselected(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onUnselected")
    }
    onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        throw new Error("Unimplemented method onAnimationStart")
    }
    onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        throw new Error("Unimplemented method onAnimationEnd")
    }
    onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        throw new Error("Unimplemented method onGestureSwipe")
    }
    nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        throw new Error("Unimplemented method nestedScroll")
    }
    customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        throw new Error("Unimplemented method customContentTransition")
    }
    onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        throw new Error("Unimplemented method onContentDidScroll")
    }
    indicatorInteractive(value: boolean | undefined): this {
        throw new Error("Unimplemented method indicatorInteractive")
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        throw new Error("Unimplemented method pageFlipMode")
    }
    onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        throw new Error("Unimplemented method onContentWillScroll")
    }
    autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): this {
        throw new Error("Unimplemented method autoPlay")
    }
    displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        throw new Error("Unimplemented method displayArrow")
    }
    cachedCount(count: number | undefined, isShown: boolean | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    displayCount(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        throw new Error("Unimplemented method displayCount")
    }
    prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        throw new Error("Unimplemented method prevMargin")
    }
    nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        throw new Error("Unimplemented method nextMargin")
    }
    _onChangeEvent_index(callback_: ((index: number | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_index")
    }
    attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSwiperStyle extends ArkCommonMethodStyle implements SwiperAttribute {
    index_value?: number | undefined
    interval_value?: number | undefined
    indicator_value?: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined
    loop_value?: boolean | undefined
    duration_value?: number | undefined
    vertical_value?: boolean | undefined
    itemSpace_value?: number | string | undefined
    displayMode_value?: SwiperDisplayMode | undefined
    cachedCount_value?: number | undefined
    effectMode_value?: EdgeEffect | undefined
    disableSwipe_value?: boolean | undefined
    curve_value?: curves.Curve | string | curves.ICurve | undefined
    onChange_value?: ((value0: number) => void) | undefined
    onSelected_value?: ((value0: number) => void) | undefined
    onUnselected_value?: ((value0: number) => void) | undefined
    onAnimationStart_value?: OnSwiperAnimationStartCallback | undefined
    onAnimationEnd_value?: OnSwiperAnimationEndCallback | undefined
    onGestureSwipe_value?: OnSwiperGestureSwipeCallback | undefined
    nestedScroll_value?: SwiperNestedScrollMode | undefined
    customContentTransition_value?: SwiperContentAnimatedTransition | undefined
    onContentDidScroll_value?: ContentDidScrollCallback | undefined
    indicatorInteractive_value?: boolean | undefined
    pageFlipMode_value?: PageFlipMode | undefined
    onContentWillScroll_value?: ContentWillScrollCallback | undefined
    attributeModifier_value?: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined
    public index(value: number | undefined): this {
        return this
    }
    public interval(value: number | undefined): this {
        return this
    }
    public indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
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
    public cachedCount(value: number | undefined): this {
        return this
    }
    public effectMode(value: EdgeEffect | undefined): this {
        return this
    }
    public disableSwipe(value: boolean | undefined): this {
        return this
    }
    public curve(value: curves.Curve | string | curves.ICurve | undefined): this {
        return this
    }
    public onChange(value: ((value0: number) => void) | undefined): this {
        return this
    }
    public onSelected(value: ((value0: number) => void) | undefined): this {
        return this
    }
    public onUnselected(value: ((value0: number) => void) | undefined): this {
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
    public autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): this {
        return this
    }
    public displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        return this
    }
    public cachedCount(count: number | undefined, isShown: boolean | undefined): this {
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
    public _onChangeEvent_index(callback_: ((index: number | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SwiperAttribute): void {
        super.apply(target)
        if (this.index_value !== undefined)
            target.index(this.index_value!)
        if (this.interval_value !== undefined)
            target.interval(this.interval_value!)
        if (this.indicator_value !== undefined)
            target.indicator(this.indicator_value!)
        if (this.loop_value !== undefined)
            target.loop(this.loop_value!)
        if (this.duration_value !== undefined)
            target.duration(this.duration_value!)
        if (this.vertical_value !== undefined)
            target.vertical(this.vertical_value!)
        if (this.itemSpace_value !== undefined)
            target.itemSpace(this.itemSpace_value!)
        if (this.displayMode_value !== undefined)
            target.displayMode(this.displayMode_value!)
        if (this.cachedCount_value !== undefined)
            target.cachedCount(this.cachedCount_value!)
        if (this.effectMode_value !== undefined)
            target.effectMode(this.effectMode_value!)
        if (this.disableSwipe_value !== undefined)
            target.disableSwipe(this.disableSwipe_value!)
        if (this.curve_value !== undefined)
            target.curve(this.curve_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.onSelected_value !== undefined)
            target.onSelected(this.onSelected_value!)
        if (this.onUnselected_value !== undefined)
            target.onUnselected(this.onUnselected_value!)
        if (this.onAnimationStart_value !== undefined)
            target.onAnimationStart(this.onAnimationStart_value!)
        if (this.onAnimationEnd_value !== undefined)
            target.onAnimationEnd(this.onAnimationEnd_value!)
        if (this.onGestureSwipe_value !== undefined)
            target.onGestureSwipe(this.onGestureSwipe_value!)
        if (this.nestedScroll_value !== undefined)
            target.nestedScroll(this.nestedScroll_value!)
        if (this.customContentTransition_value !== undefined)
            target.customContentTransition(this.customContentTransition_value!)
        if (this.onContentDidScroll_value !== undefined)
            target.onContentDidScroll(this.onContentDidScroll_value!)
        if (this.indicatorInteractive_value !== undefined)
            target.indicatorInteractive(this.indicatorInteractive_value!)
        if (this.pageFlipMode_value !== undefined)
            target.pageFlipMode(this.pageFlipMode_value!)
        if (this.onContentWillScroll_value !== undefined)
            target.onContentWillScroll(this.onContentWillScroll_value!)
    }
}
export interface SwiperContentAnimatedTransition {
    timeout?: number;
    transition: ((value0: SwiperContentTransitionProxy) => void);
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
            this.getPeer()?.setIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public interval(value: number | undefined): this {
        if (this.checkPriority("interval")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setIntervalAttribute(value_casted)
            return this
        }
        return this
    }
    public indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        if (this.checkPriority("indicator")) {
            const value_casted = value as (IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined)
            this.getPeer()?.setIndicatorAttribute(value_casted)
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
    public duration(value: number | undefined): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setDurationAttribute(value_casted)
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
    public itemSpace(value: number | string | undefined): this {
        if (this.checkPriority("itemSpace")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.setItemSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public displayMode(value: SwiperDisplayMode | undefined): this {
        if (this.checkPriority("displayMode")) {
            const value_casted = value as (SwiperDisplayMode | undefined)
            this.getPeer()?.setDisplayModeAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(value: number | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
            return this
        }
        return this
    }
    public effectMode(value: EdgeEffect | undefined): this {
        if (this.checkPriority("effectMode")) {
            const value_casted = value as (EdgeEffect | undefined)
            this.getPeer()?.setEffectModeAttribute(value_casted)
            return this
        }
        return this
    }
    public disableSwipe(value: boolean | undefined): this {
        if (this.checkPriority("disableSwipe")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDisableSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    public curve(value: curves.Curve | string | curves.ICurve | undefined): this {
        if (this.checkPriority("curve")) {
            const value_casted = value as (curves.Curve | string | curves.ICurve | undefined)
            this.getPeer()?.setCurveAttribute(value_casted)
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
    public onSelected(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onSelected")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onUnselected(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onUnselected")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnUnselectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        if (this.checkPriority("onAnimationStart")) {
            const value_casted = value as (OnSwiperAnimationStartCallback | undefined)
            this.getPeer()?.setOnAnimationStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        if (this.checkPriority("onAnimationEnd")) {
            const value_casted = value as (OnSwiperAnimationEndCallback | undefined)
            this.getPeer()?.setOnAnimationEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        if (this.checkPriority("onGestureSwipe")) {
            const value_casted = value as (OnSwiperGestureSwipeCallback | undefined)
            this.getPeer()?.setOnGestureSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (SwiperNestedScrollMode | undefined)
            this.getPeer()?.setNestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        if (this.checkPriority("customContentTransition")) {
            const value_casted = value as (SwiperContentAnimatedTransition | undefined)
            this.getPeer()?.setCustomContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        if (this.checkPriority("onContentDidScroll")) {
            const value_casted = value as (ContentDidScrollCallback | undefined)
            this.getPeer()?.setOnContentDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public indicatorInteractive(value: boolean | undefined): this {
        if (this.checkPriority("indicatorInteractive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setIndicatorInteractiveAttribute(value_casted)
            return this
        }
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        if (this.checkPriority("pageFlipMode")) {
            const value_casted = value as (PageFlipMode | undefined)
            this.getPeer()?.setPageFlipModeAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        if (this.checkPriority("onContentWillScroll")) {
            const value_casted = value as (ContentWillScrollCallback | undefined)
            this.getPeer()?.setOnContentWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): this {
        if (this.checkPriority("autoPlay")) {
            const autoPlay_casted = autoPlay as (boolean | undefined)
            const options_casted = options as (AutoPlayOptions | undefined)
            this.getPeer()?.setAutoPlayAttribute(autoPlay_casted, options_casted)
            return this
        }
        return this
    }
    public displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        if (this.checkPriority("displayArrow")) {
            const value_casted = value as (ArrowStyle | boolean | undefined)
            const isHoverShow_casted = isHoverShow as (boolean | undefined)
            this.getPeer()?.setDisplayArrowAttribute(value_casted, isHoverShow_casted)
            return this
        }
        return this
    }
    public cachedCount(count: number | undefined, isShown: boolean | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const count_casted = count as (number | undefined)
            const isShown_casted = isShown as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, isShown_casted)
            return this
        }
        return this
    }
    public displayCount(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        if (this.checkPriority("displayCount")) {
            const value_casted = value as (number | string | SwiperAutoFill | undefined)
            const swipeByGroup_casted = swipeByGroup as (boolean | undefined)
            this.getPeer()?.setDisplayCountAttribute(value_casted, swipeByGroup_casted)
            return this
        }
        return this
    }
    public prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (this.checkPriority("prevMargin")) {
            const value_casted = value as (Length | undefined)
            const ignoreBlank_casted = ignoreBlank as (boolean | undefined)
            this.getPeer()?.setPrevMarginAttribute(value_casted, ignoreBlank_casted)
            return this
        }
        return this
    }
    public nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (this.checkPriority("nextMargin")) {
            const value_casted = value as (Length | undefined)
            const ignoreBlank_casted = ignoreBlank as (boolean | undefined)
            this.getPeer()?.setNextMarginAttribute(value_casted, ignoreBlank_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_index(callback_: ((index: number | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_index")) {
            const callback__casted = callback_ as (((index: number | undefined) => void))
            this.getPeer()?.set_onChangeEvent_indexAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSwiperStyle(receiver: SwiperAttribute, modifier: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSwiperStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Swiper")
// export function Swiper(
//     controller?: SwiperController,
//     @memo
//     content_?: () => void,
// ): SwiperAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Swiper(
    @memo
    style: ((attributes: SwiperAttribute) => void) | undefined,
    controller?: SwiperController,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSwiperComponent>((): ArkSwiperComponent => {
        return new ArkSwiperComponent()
    })
    NodeAttach<ArkSwiperPeer>((): ArkSwiperPeer => ArkSwiperPeer.create(receiver), (_: ArkSwiperPeer): void => {
        receiver.setSwiperOptions(controller)
        style?.(receiver)
        withSwiperStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkSwiperSet extends ArkCommonMethodSet implements SwiperAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _index_flag?: boolean
    _index0_value?: number | undefined
    _interval_flag?: boolean
    _interval0_value?: number | undefined
    _indicator_flag?: boolean
    _indicator0_value?: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined
    _loop_flag?: boolean
    _loop0_value?: boolean | undefined
    _duration_flag?: boolean
    _duration0_value?: number | undefined
    _vertical_flag?: boolean
    _vertical0_value?: boolean | undefined
    _itemSpace_flag?: boolean
    _itemSpace0_value?: number | string | undefined
    _displayMode_flag?: boolean
    _displayMode0_value?: SwiperDisplayMode | undefined
    _cachedCount_flag?: boolean
    _cachedCount0_value?: number | undefined
    _cachedCount1_value?: boolean | undefined
    _effectMode_flag?: boolean
    _effectMode0_value?: EdgeEffect | undefined
    _disableSwipe_flag?: boolean
    _disableSwipe0_value?: boolean | undefined
    _curve_flag?: boolean
    _curve0_value?: curves.Curve | string | curves.ICurve | undefined
    _onChange_flag?: boolean
    _onChange0_value?: ((value0: number) => void) | undefined
    _onSelected_flag?: boolean
    _onSelected0_value?: ((value0: number) => void) | undefined
    _onUnselected_flag?: boolean
    _onUnselected0_value?: ((value0: number) => void) | undefined
    _onAnimationStart_flag?: boolean
    _onAnimationStart0_value?: OnSwiperAnimationStartCallback | undefined
    _onAnimationEnd_flag?: boolean
    _onAnimationEnd0_value?: OnSwiperAnimationEndCallback | undefined
    _onGestureSwipe_flag?: boolean
    _onGestureSwipe0_value?: OnSwiperGestureSwipeCallback | undefined
    _nestedScroll_flag?: boolean
    _nestedScroll0_value?: SwiperNestedScrollMode | undefined
    _customContentTransition_flag?: boolean
    _customContentTransition0_value?: SwiperContentAnimatedTransition | undefined
    _onContentDidScroll_flag?: boolean
    _onContentDidScroll0_value?: ContentDidScrollCallback | undefined
    _indicatorInteractive_flag?: boolean
    _indicatorInteractive0_value?: boolean | undefined
    _pageFlipMode_flag?: boolean
    _pageFlipMode0_value?: PageFlipMode | undefined
    _onContentWillScroll_flag?: boolean
    _onContentWillScroll0_value?: ContentWillScrollCallback | undefined
    _autoPlay_flag?: boolean
    _autoPlay0_value?: boolean | undefined
    _autoPlay1_value?: AutoPlayOptions | undefined
    _displayArrow_flag?: boolean
    _displayArrow0_value?: ArrowStyle | boolean | undefined
    _displayArrow1_value?: boolean | undefined
    _displayCount_flag?: boolean
    _displayCount0_value?: number | string | SwiperAutoFill | undefined
    _displayCount1_value?: boolean | undefined
    _prevMargin_flag?: boolean
    _prevMargin0_value?: Length | undefined
    _prevMargin1_value?: boolean | undefined
    _nextMargin_flag?: boolean
    _nextMargin0_value?: Length | undefined
    _nextMargin1_value?: boolean | undefined
    __onChangeEvent_index_flag?: boolean
    __onChangeEvent_index0_value?: ((index: number | undefined) => void)
    applyModifierPatch(component: SwiperAttribute): void {
        if (this._index_flag)
            component.index((this._index0_value as number | undefined))
        if (this._interval_flag)
            component.interval((this._interval0_value as number | undefined))
        if (this._indicator_flag)
            component.indicator((this._indicator0_value as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined))
        if (this._loop_flag)
            component.loop((this._loop0_value as boolean | undefined))
        if (this._duration_flag)
            component.duration((this._duration0_value as number | undefined))
        if (this._vertical_flag)
            component.vertical((this._vertical0_value as boolean | undefined))
        if (this._itemSpace_flag)
            component.itemSpace((this._itemSpace0_value as number | string | undefined))
        if (this._displayMode_flag)
            component.displayMode((this._displayMode0_value as SwiperDisplayMode | undefined))
        if (this._cachedCount_flag)
            component.cachedCount((this._cachedCount0_value as number | undefined), (this._cachedCount1_value as boolean | undefined))
        if (this._effectMode_flag)
            component.effectMode((this._effectMode0_value as EdgeEffect | undefined))
        if (this._disableSwipe_flag)
            component.disableSwipe((this._disableSwipe0_value as boolean | undefined))
        if (this._curve_flag)
            component.curve((this._curve0_value as curves.Curve | string | curves.ICurve | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as ((value0: number) => void) | undefined))
        if (this._onSelected_flag)
            component.onSelected((this._onSelected0_value as ((value0: number) => void) | undefined))
        if (this._onUnselected_flag)
            component.onUnselected((this._onUnselected0_value as ((value0: number) => void) | undefined))
        if (this._onAnimationStart_flag)
            component.onAnimationStart((this._onAnimationStart0_value as OnSwiperAnimationStartCallback | undefined))
        if (this._onAnimationEnd_flag)
            component.onAnimationEnd((this._onAnimationEnd0_value as OnSwiperAnimationEndCallback | undefined))
        if (this._onGestureSwipe_flag)
            component.onGestureSwipe((this._onGestureSwipe0_value as OnSwiperGestureSwipeCallback | undefined))
        if (this._nestedScroll_flag)
            component.nestedScroll((this._nestedScroll0_value as SwiperNestedScrollMode | undefined))
        if (this._customContentTransition_flag)
            component.customContentTransition((this._customContentTransition0_value as SwiperContentAnimatedTransition | undefined))
        if (this._onContentDidScroll_flag)
            component.onContentDidScroll((this._onContentDidScroll0_value as ContentDidScrollCallback | undefined))
        if (this._indicatorInteractive_flag)
            component.indicatorInteractive((this._indicatorInteractive0_value as boolean | undefined))
        if (this._pageFlipMode_flag)
            component.pageFlipMode((this._pageFlipMode0_value as PageFlipMode | undefined))
        if (this._onContentWillScroll_flag)
            component.onContentWillScroll((this._onContentWillScroll0_value as ContentWillScrollCallback | undefined))
        if (this._autoPlay_flag)
            component.autoPlay((this._autoPlay0_value as boolean | undefined), (this._autoPlay1_value as AutoPlayOptions | undefined))
        if (this._displayArrow_flag)
            component.displayArrow((this._displayArrow0_value as ArrowStyle | boolean | undefined), (this._displayArrow1_value as boolean | undefined))
        if (this._displayCount_flag)
            component.displayCount((this._displayCount0_value as number | string | SwiperAutoFill | undefined), (this._displayCount1_value as boolean | undefined))
        if (this._prevMargin_flag)
            component.prevMargin((this._prevMargin0_value as Length | undefined), (this._prevMargin1_value as boolean | undefined))
        if (this._nextMargin_flag)
            component.nextMargin((this._nextMargin0_value as Length | undefined), (this._nextMargin1_value as boolean | undefined))
    }
    public index(value: number | undefined): this {
        this._index_flag = true
        this._index0_value = value
        return this
    }
    public interval(value: number | undefined): this {
        this._interval_flag = true
        this._interval0_value = value
        return this
    }
    public indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        this._indicator_flag = true
        this._indicator0_value = value
        return this
    }
    public loop(value: boolean | undefined): this {
        this._loop_flag = true
        this._loop0_value = value
        return this
    }
    public duration(value: number | undefined): this {
        this._duration_flag = true
        this._duration0_value = value
        return this
    }
    public vertical(value: boolean | undefined): this {
        this._vertical_flag = true
        this._vertical0_value = value
        return this
    }
    public itemSpace(value: number | string | undefined): this {
        this._itemSpace_flag = true
        this._itemSpace0_value = value
        return this
    }
    public displayMode(value: SwiperDisplayMode | undefined): this {
        this._displayMode_flag = true
        this._displayMode0_value = value
        return this
    }
    public cachedCount(count: number | undefined, isShown: boolean | undefined): this {
        this._cachedCount_flag = true
        this._cachedCount0_value = count
        this._cachedCount1_value = isShown
        return this
    }
    public effectMode(value: EdgeEffect | undefined): this {
        this._effectMode_flag = true
        this._effectMode0_value = value
        return this
    }
    public disableSwipe(value: boolean | undefined): this {
        this._disableSwipe_flag = true
        this._disableSwipe0_value = value
        return this
    }
    public curve(value: curves.Curve | string | curves.ICurve | undefined): this {
        this._curve_flag = true
        this._curve0_value = value
        return this
    }
    public onChange(value: ((value0: number) => void) | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public onSelected(value: ((value0: number) => void) | undefined): this {
        this._onSelected_flag = true
        this._onSelected0_value = value
        return this
    }
    public onUnselected(value: ((value0: number) => void) | undefined): this {
        this._onUnselected_flag = true
        this._onUnselected0_value = value
        return this
    }
    public onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        this._onAnimationStart_flag = true
        this._onAnimationStart0_value = value
        return this
    }
    public onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        this._onAnimationEnd_flag = true
        this._onAnimationEnd0_value = value
        return this
    }
    public onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        this._onGestureSwipe_flag = true
        this._onGestureSwipe0_value = value
        return this
    }
    public nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        this._nestedScroll_flag = true
        this._nestedScroll0_value = value
        return this
    }
    public customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        this._customContentTransition_flag = true
        this._customContentTransition0_value = value
        return this
    }
    public onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        this._onContentDidScroll_flag = true
        this._onContentDidScroll0_value = value
        return this
    }
    public indicatorInteractive(value: boolean | undefined): this {
        this._indicatorInteractive_flag = true
        this._indicatorInteractive0_value = value
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        this._pageFlipMode_flag = true
        this._pageFlipMode0_value = value
        return this
    }
    public onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        this._onContentWillScroll_flag = true
        this._onContentWillScroll0_value = value
        return this
    }
    public autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): this {
        this._autoPlay_flag = true
        this._autoPlay0_value = autoPlay
        this._autoPlay1_value = options
        return this
    }
    public displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        this._displayArrow_flag = true
        this._displayArrow0_value = value
        this._displayArrow1_value = isHoverShow
        return this
    }
    public displayCount(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        this._displayCount_flag = true
        this._displayCount0_value = value
        this._displayCount1_value = swipeByGroup
        return this
    }
    public prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        this._prevMargin_flag = true
        this._prevMargin0_value = value
        this._prevMargin1_value = ignoreBlank
        return this
    }
    public nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        this._nextMargin_flag = true
        this._nextMargin0_value = value
        this._nextMargin1_value = ignoreBlank
        return this
    }
    public _onChangeEvent_index(callback_: ((index: number | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
export class SwiperAnimationEvent_serializer {
    public static write(buffer: SerializerBase, value: SwiperAnimationEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_currentOffset  = value.currentOffset
        valueSerializer.writeNumber(value_currentOffset)
        const value_targetOffset  = value.targetOffset
        valueSerializer.writeNumber(value_targetOffset)
        const value_velocity  = value.velocity
        valueSerializer.writeNumber(value_velocity)
    }
    public static read(buffer: DeserializerBase): SwiperAnimationEvent {
        let valueDeserializer : DeserializerBase = buffer
        const currentOffset_result : number = (valueDeserializer.readNumber() as number)
        const targetOffset_result : number = (valueDeserializer.readNumber() as number)
        const velocity_result : number = (valueDeserializer.readNumber() as number)
        let value : SwiperAnimationEvent = ({currentOffset: currentOffset_result, targetOffset: targetOffset_result, velocity: velocity_result} as SwiperAnimationEvent)
        return value
    }
}
export class SwiperContentTransitionProxy_serializer {
    public static write(buffer: SerializerBase, value: SwiperContentTransitionProxy): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SwiperContentTransitionProxy {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SwiperContentTransitionProxyInternal.fromPtr(ptr)
    }
}
export class SwiperContentWillScrollResult_serializer {
    public static write(buffer: SerializerBase, value: SwiperContentWillScrollResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_currentIndex  = value.currentIndex
        valueSerializer.writeNumber(value_currentIndex)
        const value_comingIndex  = value.comingIndex
        valueSerializer.writeNumber(value_comingIndex)
        const value_offset  = value.offset
        valueSerializer.writeNumber(value_offset)
    }
    public static read(buffer: DeserializerBase): SwiperContentWillScrollResult {
        let valueDeserializer : DeserializerBase = buffer
        const currentIndex_result : number = (valueDeserializer.readNumber() as number)
        const comingIndex_result : number = (valueDeserializer.readNumber() as number)
        const offset_result : number = (valueDeserializer.readNumber() as number)
        let value : SwiperContentWillScrollResult = ({currentIndex: currentIndex_result, comingIndex: comingIndex_result, offset: offset_result} as SwiperContentWillScrollResult)
        return value
    }
}
export class SwiperController_serializer {
    public static write(buffer: SerializerBase, value: SwiperController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SwiperController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SwiperControllerInternal.fromPtr(ptr)
    }
}
export class AutoPlayOptions_serializer {
    public static write(buffer: SerializerBase, value: AutoPlayOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_stopWhenTouched  = value.stopWhenTouched
        valueSerializer.writeBoolean(value_stopWhenTouched)
    }
    public static read(buffer: DeserializerBase): AutoPlayOptions {
        let valueDeserializer : DeserializerBase = buffer
        const stopWhenTouched_result : boolean = valueDeserializer.readBoolean()
        let value : AutoPlayOptions = ({stopWhenTouched: stopWhenTouched_result} as AutoPlayOptions)
        return value
    }
}
export class SwiperAutoFill_serializer {
    public static write(buffer: SerializerBase, value: SwiperAutoFill): void {
        let valueSerializer : SerializerBase = buffer
        const value_minSize  = value.minSize
        let value_minSize_type : int32 = RuntimeType.UNDEFINED
        value_minSize_type = runtimeType(value_minSize)
        if (RuntimeType.STRING == value_minSize_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_minSize_0  = value_minSize as string
            valueSerializer.writeString(value_minSize_0)
        }
        else if (RuntimeType.NUMBER == value_minSize_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_minSize_1  = value_minSize as number
            valueSerializer.writeNumber(value_minSize_1)
        }
    }
    public static read(buffer: DeserializerBase): SwiperAutoFill {
        let valueDeserializer : DeserializerBase = buffer
        const minSize_buf_selector : int32 = valueDeserializer.readInt8()
        let minSize_buf : string | number | undefined
        if (minSize_buf_selector == (0).toChar()) {
            minSize_buf = (valueDeserializer.readString() as string)
        }
        else if (minSize_buf_selector == (1).toChar()) {
            minSize_buf = (valueDeserializer.readNumber() as number)
        }
        else {
            throw new Error("One of the branches for minSize_buf has to be chosen through deserialisation.")
        }
        const minSize_result : VP = (minSize_buf as string | number)
        let value : SwiperAutoFill = ({minSize: minSize_result} as SwiperAutoFill)
        return value
    }
}
export class SwiperContentAnimatedTransition_serializer {
    public static write(buffer: SerializerBase, value: SwiperContentAnimatedTransition): void {
        let valueSerializer : SerializerBase = buffer
        const value_timeout  = value.timeout
        let value_timeout_type : int32 = RuntimeType.UNDEFINED
        value_timeout_type = runtimeType(value_timeout)
        valueSerializer.writeInt8((value_timeout_type).toChar())
        if ((value_timeout_type) != (RuntimeType.UNDEFINED)) {
            const value_timeout_value  = value_timeout!
            valueSerializer.writeNumber(value_timeout_value)
        }
        const value_transition  = value.transition
        valueSerializer.holdAndWriteCallback(value_transition)
    }
    public static read(buffer: DeserializerBase): SwiperContentAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const timeout_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeout_buf : number | undefined
        if ((timeout_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            timeout_buf = (valueDeserializer.readNumber() as number)
        }
        const timeout_result : number | undefined = timeout_buf
        const transition_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const transition_buf_call : KPointer = valueDeserializer.readPointer()
        const transition_buf_callSync : KPointer = valueDeserializer.readPointer()
        const transition_result : ((value0: SwiperContentTransitionProxy) => void) = (value0: SwiperContentTransitionProxy):void => { 
    const transition_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    transition_buf_argsSerializer.writeInt32(transition_buf_resource.resourceId);
    transition_buf_argsSerializer.writePointer(transition_buf_call);
    transition_buf_argsSerializer.writePointer(transition_buf_callSync);
    SwiperContentTransitionProxy_serializer.write(transition_buf_argsSerializer, value0);
    InteropNativeModule._CallCallback(-416053361, transition_buf_argsSerializer.asBuffer(), transition_buf_argsSerializer.length());
    transition_buf_argsSerializer.release();
    return; }
        let value : SwiperContentAnimatedTransition = ({timeout: timeout_result, transition: transition_result} as SwiperContentAnimatedTransition)
        return value
    }
}
export class ArrowStyle_serializer {
    public static write(buffer: SerializerBase, value: ArrowStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_showBackground  = value.showBackground
        let value_showBackground_type : int32 = RuntimeType.UNDEFINED
        value_showBackground_type = runtimeType(value_showBackground)
        valueSerializer.writeInt8((value_showBackground_type).toChar())
        if ((value_showBackground_type) != (RuntimeType.UNDEFINED)) {
            const value_showBackground_value  = value_showBackground!
            valueSerializer.writeBoolean(value_showBackground_value)
        }
        const value_isSidebarMiddle  = value.isSidebarMiddle
        let value_isSidebarMiddle_type : int32 = RuntimeType.UNDEFINED
        value_isSidebarMiddle_type = runtimeType(value_isSidebarMiddle)
        valueSerializer.writeInt8((value_isSidebarMiddle_type).toChar())
        if ((value_isSidebarMiddle_type) != (RuntimeType.UNDEFINED)) {
            const value_isSidebarMiddle_value  = value_isSidebarMiddle!
            valueSerializer.writeBoolean(value_isSidebarMiddle_value)
        }
        const value_backgroundSize  = value.backgroundSize
        let value_backgroundSize_type : int32 = RuntimeType.UNDEFINED
        value_backgroundSize_type = runtimeType(value_backgroundSize)
        valueSerializer.writeInt8((value_backgroundSize_type).toChar())
        if ((value_backgroundSize_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundSize_value  = value_backgroundSize!
            let value_backgroundSize_value_type : int32 = RuntimeType.UNDEFINED
            value_backgroundSize_value_type = runtimeType(value_backgroundSize_value)
            if (RuntimeType.STRING == value_backgroundSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_backgroundSize_value_0  = value_backgroundSize_value as string
                valueSerializer.writeString(value_backgroundSize_value_0)
            }
            else if (RuntimeType.NUMBER == value_backgroundSize_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_backgroundSize_value_1  = value_backgroundSize_value as number
                valueSerializer.writeNumber(value_backgroundSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_backgroundSize_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_backgroundSize_value_2  = value_backgroundSize_value as Resource
                Resource_serializer.write(valueSerializer, value_backgroundSize_value_2)
            }
        }
        const value_backgroundColor  = value.backgroundColor
        let value_backgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_backgroundColor_type = runtimeType(value_backgroundColor)
        valueSerializer.writeInt8((value_backgroundColor_type).toChar())
        if ((value_backgroundColor_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundColor_value  = value_backgroundColor!
            let value_backgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_backgroundColor_value_type = runtimeType(value_backgroundColor_value)
            if (TypeChecker.isColor(value_backgroundColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_backgroundColor_value_0  = value_backgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_backgroundColor_value_1  = value_backgroundColor_value as number
                valueSerializer.writeNumber(value_backgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_backgroundColor_value_2  = value_backgroundColor_value as string
                valueSerializer.writeString(value_backgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_backgroundColor_value_3  = value_backgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_backgroundColor_value_3)
            }
        }
        const value_arrowSize  = value.arrowSize
        let value_arrowSize_type : int32 = RuntimeType.UNDEFINED
        value_arrowSize_type = runtimeType(value_arrowSize)
        valueSerializer.writeInt8((value_arrowSize_type).toChar())
        if ((value_arrowSize_type) != (RuntimeType.UNDEFINED)) {
            const value_arrowSize_value  = value_arrowSize!
            let value_arrowSize_value_type : int32 = RuntimeType.UNDEFINED
            value_arrowSize_value_type = runtimeType(value_arrowSize_value)
            if (RuntimeType.STRING == value_arrowSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_arrowSize_value_0  = value_arrowSize_value as string
                valueSerializer.writeString(value_arrowSize_value_0)
            }
            else if (RuntimeType.NUMBER == value_arrowSize_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_arrowSize_value_1  = value_arrowSize_value as number
                valueSerializer.writeNumber(value_arrowSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_arrowSize_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_arrowSize_value_2  = value_arrowSize_value as Resource
                Resource_serializer.write(valueSerializer, value_arrowSize_value_2)
            }
        }
        const value_arrowColor  = value.arrowColor
        let value_arrowColor_type : int32 = RuntimeType.UNDEFINED
        value_arrowColor_type = runtimeType(value_arrowColor)
        valueSerializer.writeInt8((value_arrowColor_type).toChar())
        if ((value_arrowColor_type) != (RuntimeType.UNDEFINED)) {
            const value_arrowColor_value  = value_arrowColor!
            let value_arrowColor_value_type : int32 = RuntimeType.UNDEFINED
            value_arrowColor_value_type = runtimeType(value_arrowColor_value)
            if (TypeChecker.isColor(value_arrowColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_arrowColor_value_0  = value_arrowColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_arrowColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_arrowColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_arrowColor_value_1  = value_arrowColor_value as number
                valueSerializer.writeNumber(value_arrowColor_value_1)
            }
            else if (RuntimeType.STRING == value_arrowColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_arrowColor_value_2  = value_arrowColor_value as string
                valueSerializer.writeString(value_arrowColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_arrowColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_arrowColor_value_3  = value_arrowColor_value as Resource
                Resource_serializer.write(valueSerializer, value_arrowColor_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): ArrowStyle {
        let valueDeserializer : DeserializerBase = buffer
        const showBackground_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showBackground_buf : boolean | undefined
        if ((showBackground_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            showBackground_buf = valueDeserializer.readBoolean()
        }
        const showBackground_result : boolean | undefined = showBackground_buf
        const isSidebarMiddle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isSidebarMiddle_buf : boolean | undefined
        if ((isSidebarMiddle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isSidebarMiddle_buf = valueDeserializer.readBoolean()
        }
        const isSidebarMiddle_result : boolean | undefined = isSidebarMiddle_buf
        const backgroundSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundSize_buf : Length | undefined
        if ((backgroundSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const backgroundSize_buf__selector : int32 = valueDeserializer.readInt8()
            let backgroundSize_buf_ : string | number | Resource | undefined
            if (backgroundSize_buf__selector == (0).toChar()) {
                backgroundSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (backgroundSize_buf__selector == (1).toChar()) {
                backgroundSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (backgroundSize_buf__selector == (2).toChar()) {
                backgroundSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for backgroundSize_buf_ has to be chosen through deserialisation.")
            }
            backgroundSize_buf = (backgroundSize_buf_ as string | number | Resource)
        }
        const backgroundSize_result : Length | undefined = backgroundSize_buf
        const backgroundColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColor_buf : ResourceColor | undefined
        if ((backgroundColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const backgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let backgroundColor_buf_ : Color | number | string | Resource | undefined
            if (backgroundColor_buf__selector == (0).toChar()) {
                backgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (backgroundColor_buf__selector == (1).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (backgroundColor_buf__selector == (2).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (backgroundColor_buf__selector == (3).toChar()) {
                backgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for backgroundColor_buf_ has to be chosen through deserialisation.")
            }
            backgroundColor_buf = (backgroundColor_buf_ as Color | number | string | Resource)
        }
        const backgroundColor_result : ResourceColor | undefined = backgroundColor_buf
        const arrowSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let arrowSize_buf : Length | undefined
        if ((arrowSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const arrowSize_buf__selector : int32 = valueDeserializer.readInt8()
            let arrowSize_buf_ : string | number | Resource | undefined
            if (arrowSize_buf__selector == (0).toChar()) {
                arrowSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (arrowSize_buf__selector == (1).toChar()) {
                arrowSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (arrowSize_buf__selector == (2).toChar()) {
                arrowSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for arrowSize_buf_ has to be chosen through deserialisation.")
            }
            arrowSize_buf = (arrowSize_buf_ as string | number | Resource)
        }
        const arrowSize_result : Length | undefined = arrowSize_buf
        const arrowColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let arrowColor_buf : ResourceColor | undefined
        if ((arrowColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const arrowColor_buf__selector : int32 = valueDeserializer.readInt8()
            let arrowColor_buf_ : Color | number | string | Resource | undefined
            if (arrowColor_buf__selector == (0).toChar()) {
                arrowColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (arrowColor_buf__selector == (1).toChar()) {
                arrowColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (arrowColor_buf__selector == (2).toChar()) {
                arrowColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (arrowColor_buf__selector == (3).toChar()) {
                arrowColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for arrowColor_buf_ has to be chosen through deserialisation.")
            }
            arrowColor_buf = (arrowColor_buf_ as Color | number | string | Resource)
        }
        const arrowColor_result : ResourceColor | undefined = arrowColor_buf
        let value : ArrowStyle = ({showBackground: showBackground_result, isSidebarMiddle: isSidebarMiddle_result, backgroundSize: backgroundSize_result, backgroundColor: backgroundColor_result, arrowSize: arrowSize_result, arrowColor: arrowColor_result} as ArrowStyle)
        return value
    }
}
export class DotIndicator_serializer {
    public static write(buffer: SerializerBase, value: DotIndicator): void {
        let valueSerializer : SerializerBase = buffer
        const value__left  = value._left
        let value__left_type : int32 = RuntimeType.UNDEFINED
        value__left_type = runtimeType(value__left)
        valueSerializer.writeInt8((value__left_type).toChar())
        if ((value__left_type) != (RuntimeType.UNDEFINED)) {
            const value__left_value  = value__left!
            let value__left_value_type : int32 = RuntimeType.UNDEFINED
            value__left_value_type = runtimeType(value__left_value)
            if (RuntimeType.STRING == value__left_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__left_value_0  = value__left_value as string
                valueSerializer.writeString(value__left_value_0)
            }
            else if (RuntimeType.NUMBER == value__left_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__left_value_1  = value__left_value as number
                valueSerializer.writeNumber(value__left_value_1)
            }
            else if (RuntimeType.OBJECT == value__left_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__left_value_2  = value__left_value as Resource
                Resource_serializer.write(valueSerializer, value__left_value_2)
            }
        }
        const value__top  = value._top
        let value__top_type : int32 = RuntimeType.UNDEFINED
        value__top_type = runtimeType(value__top)
        valueSerializer.writeInt8((value__top_type).toChar())
        if ((value__top_type) != (RuntimeType.UNDEFINED)) {
            const value__top_value  = value__top!
            let value__top_value_type : int32 = RuntimeType.UNDEFINED
            value__top_value_type = runtimeType(value__top_value)
            if (RuntimeType.STRING == value__top_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__top_value_0  = value__top_value as string
                valueSerializer.writeString(value__top_value_0)
            }
            else if (RuntimeType.NUMBER == value__top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__top_value_1  = value__top_value as number
                valueSerializer.writeNumber(value__top_value_1)
            }
            else if (RuntimeType.OBJECT == value__top_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__top_value_2  = value__top_value as Resource
                Resource_serializer.write(valueSerializer, value__top_value_2)
            }
        }
        const value__right  = value._right
        let value__right_type : int32 = RuntimeType.UNDEFINED
        value__right_type = runtimeType(value__right)
        valueSerializer.writeInt8((value__right_type).toChar())
        if ((value__right_type) != (RuntimeType.UNDEFINED)) {
            const value__right_value  = value__right!
            let value__right_value_type : int32 = RuntimeType.UNDEFINED
            value__right_value_type = runtimeType(value__right_value)
            if (RuntimeType.STRING == value__right_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__right_value_0  = value__right_value as string
                valueSerializer.writeString(value__right_value_0)
            }
            else if (RuntimeType.NUMBER == value__right_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__right_value_1  = value__right_value as number
                valueSerializer.writeNumber(value__right_value_1)
            }
            else if (RuntimeType.OBJECT == value__right_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__right_value_2  = value__right_value as Resource
                Resource_serializer.write(valueSerializer, value__right_value_2)
            }
        }
        const value__bottom  = value._bottom
        let value__bottom_type : int32 = RuntimeType.UNDEFINED
        value__bottom_type = runtimeType(value__bottom)
        valueSerializer.writeInt8((value__bottom_type).toChar())
        if ((value__bottom_type) != (RuntimeType.UNDEFINED)) {
            const value__bottom_value  = value__bottom!
            let value__bottom_value_type : int32 = RuntimeType.UNDEFINED
            value__bottom_value_type = runtimeType(value__bottom_value)
            if (RuntimeType.STRING == value__bottom_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__bottom_value_0  = value__bottom_value as string
                valueSerializer.writeString(value__bottom_value_0)
            }
            else if (RuntimeType.NUMBER == value__bottom_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__bottom_value_1  = value__bottom_value as number
                valueSerializer.writeNumber(value__bottom_value_1)
            }
            else if (RuntimeType.OBJECT == value__bottom_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__bottom_value_2  = value__bottom_value as Resource
                Resource_serializer.write(valueSerializer, value__bottom_value_2)
            }
        }
        const value__start  = value._start
        let value__start_type : int32 = RuntimeType.UNDEFINED
        value__start_type = runtimeType(value__start)
        valueSerializer.writeInt8((value__start_type).toChar())
        if ((value__start_type) != (RuntimeType.UNDEFINED)) {
            const value__start_value  = value__start!
            LengthMetrics_serializer.write(valueSerializer, value__start_value)
        }
        const value__end  = value._end
        let value__end_type : int32 = RuntimeType.UNDEFINED
        value__end_type = runtimeType(value__end)
        valueSerializer.writeInt8((value__end_type).toChar())
        if ((value__end_type) != (RuntimeType.UNDEFINED)) {
            const value__end_value  = value__end!
            LengthMetrics_serializer.write(valueSerializer, value__end_value)
        }
        const value__itemWidth  = value._itemWidth
        let value__itemWidth_type : int32 = RuntimeType.UNDEFINED
        value__itemWidth_type = runtimeType(value__itemWidth)
        valueSerializer.writeInt8((value__itemWidth_type).toChar())
        if ((value__itemWidth_type) != (RuntimeType.UNDEFINED)) {
            const value__itemWidth_value  = value__itemWidth!
            let value__itemWidth_value_type : int32 = RuntimeType.UNDEFINED
            value__itemWidth_value_type = runtimeType(value__itemWidth_value)
            if (RuntimeType.STRING == value__itemWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__itemWidth_value_0  = value__itemWidth_value as string
                valueSerializer.writeString(value__itemWidth_value_0)
            }
            else if (RuntimeType.NUMBER == value__itemWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__itemWidth_value_1  = value__itemWidth_value as number
                valueSerializer.writeNumber(value__itemWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value__itemWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__itemWidth_value_2  = value__itemWidth_value as Resource
                Resource_serializer.write(valueSerializer, value__itemWidth_value_2)
            }
        }
        const value__itemHeight  = value._itemHeight
        let value__itemHeight_type : int32 = RuntimeType.UNDEFINED
        value__itemHeight_type = runtimeType(value__itemHeight)
        valueSerializer.writeInt8((value__itemHeight_type).toChar())
        if ((value__itemHeight_type) != (RuntimeType.UNDEFINED)) {
            const value__itemHeight_value  = value__itemHeight!
            let value__itemHeight_value_type : int32 = RuntimeType.UNDEFINED
            value__itemHeight_value_type = runtimeType(value__itemHeight_value)
            if (RuntimeType.STRING == value__itemHeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__itemHeight_value_0  = value__itemHeight_value as string
                valueSerializer.writeString(value__itemHeight_value_0)
            }
            else if (RuntimeType.NUMBER == value__itemHeight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__itemHeight_value_1  = value__itemHeight_value as number
                valueSerializer.writeNumber(value__itemHeight_value_1)
            }
            else if (RuntimeType.OBJECT == value__itemHeight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__itemHeight_value_2  = value__itemHeight_value as Resource
                Resource_serializer.write(valueSerializer, value__itemHeight_value_2)
            }
        }
        const value__selectedItemWidth  = value._selectedItemWidth
        let value__selectedItemWidth_type : int32 = RuntimeType.UNDEFINED
        value__selectedItemWidth_type = runtimeType(value__selectedItemWidth)
        valueSerializer.writeInt8((value__selectedItemWidth_type).toChar())
        if ((value__selectedItemWidth_type) != (RuntimeType.UNDEFINED)) {
            const value__selectedItemWidth_value  = value__selectedItemWidth!
            let value__selectedItemWidth_value_type : int32 = RuntimeType.UNDEFINED
            value__selectedItemWidth_value_type = runtimeType(value__selectedItemWidth_value)
            if (RuntimeType.STRING == value__selectedItemWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__selectedItemWidth_value_0  = value__selectedItemWidth_value as string
                valueSerializer.writeString(value__selectedItemWidth_value_0)
            }
            else if (RuntimeType.NUMBER == value__selectedItemWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__selectedItemWidth_value_1  = value__selectedItemWidth_value as number
                valueSerializer.writeNumber(value__selectedItemWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value__selectedItemWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__selectedItemWidth_value_2  = value__selectedItemWidth_value as Resource
                Resource_serializer.write(valueSerializer, value__selectedItemWidth_value_2)
            }
        }
        const value__selectedItemHeight  = value._selectedItemHeight
        let value__selectedItemHeight_type : int32 = RuntimeType.UNDEFINED
        value__selectedItemHeight_type = runtimeType(value__selectedItemHeight)
        valueSerializer.writeInt8((value__selectedItemHeight_type).toChar())
        if ((value__selectedItemHeight_type) != (RuntimeType.UNDEFINED)) {
            const value__selectedItemHeight_value  = value__selectedItemHeight!
            let value__selectedItemHeight_value_type : int32 = RuntimeType.UNDEFINED
            value__selectedItemHeight_value_type = runtimeType(value__selectedItemHeight_value)
            if (RuntimeType.STRING == value__selectedItemHeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__selectedItemHeight_value_0  = value__selectedItemHeight_value as string
                valueSerializer.writeString(value__selectedItemHeight_value_0)
            }
            else if (RuntimeType.NUMBER == value__selectedItemHeight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__selectedItemHeight_value_1  = value__selectedItemHeight_value as number
                valueSerializer.writeNumber(value__selectedItemHeight_value_1)
            }
            else if (RuntimeType.OBJECT == value__selectedItemHeight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__selectedItemHeight_value_2  = value__selectedItemHeight_value as Resource
                Resource_serializer.write(valueSerializer, value__selectedItemHeight_value_2)
            }
        }
        const value__mask  = value._mask
        let value__mask_type : int32 = RuntimeType.UNDEFINED
        value__mask_type = runtimeType(value__mask)
        valueSerializer.writeInt8((value__mask_type).toChar())
        if ((value__mask_type) != (RuntimeType.UNDEFINED)) {
            const value__mask_value  = value__mask!
            valueSerializer.writeBoolean(value__mask_value)
        }
        const value__color  = value._color
        let value__color_type : int32 = RuntimeType.UNDEFINED
        value__color_type = runtimeType(value__color)
        valueSerializer.writeInt8((value__color_type).toChar())
        if ((value__color_type) != (RuntimeType.UNDEFINED)) {
            const value__color_value  = value__color!
            let value__color_value_type : int32 = RuntimeType.UNDEFINED
            value__color_value_type = runtimeType(value__color_value)
            if (TypeChecker.isColor(value__color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value__color_value_0  = value__color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value__color_value_0))
            }
            else if (RuntimeType.NUMBER == value__color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__color_value_1  = value__color_value as number
                valueSerializer.writeNumber(value__color_value_1)
            }
            else if (RuntimeType.STRING == value__color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__color_value_2  = value__color_value as string
                valueSerializer.writeString(value__color_value_2)
            }
            else if (RuntimeType.OBJECT == value__color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value__color_value_3  = value__color_value as Resource
                Resource_serializer.write(valueSerializer, value__color_value_3)
            }
        }
        const value__selectedColor  = value._selectedColor
        let value__selectedColor_type : int32 = RuntimeType.UNDEFINED
        value__selectedColor_type = runtimeType(value__selectedColor)
        valueSerializer.writeInt8((value__selectedColor_type).toChar())
        if ((value__selectedColor_type) != (RuntimeType.UNDEFINED)) {
            const value__selectedColor_value  = value__selectedColor!
            let value__selectedColor_value_type : int32 = RuntimeType.UNDEFINED
            value__selectedColor_value_type = runtimeType(value__selectedColor_value)
            if (TypeChecker.isColor(value__selectedColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value__selectedColor_value_0  = value__selectedColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value__selectedColor_value_0))
            }
            else if (RuntimeType.NUMBER == value__selectedColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__selectedColor_value_1  = value__selectedColor_value as number
                valueSerializer.writeNumber(value__selectedColor_value_1)
            }
            else if (RuntimeType.STRING == value__selectedColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__selectedColor_value_2  = value__selectedColor_value as string
                valueSerializer.writeString(value__selectedColor_value_2)
            }
            else if (RuntimeType.OBJECT == value__selectedColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value__selectedColor_value_3  = value__selectedColor_value as Resource
                Resource_serializer.write(valueSerializer, value__selectedColor_value_3)
            }
        }
        const value__maxDisplayCount  = value._maxDisplayCount
        let value__maxDisplayCount_type : int32 = RuntimeType.UNDEFINED
        value__maxDisplayCount_type = runtimeType(value__maxDisplayCount)
        valueSerializer.writeInt8((value__maxDisplayCount_type).toChar())
        if ((value__maxDisplayCount_type) != (RuntimeType.UNDEFINED)) {
            const value__maxDisplayCount_value  = value__maxDisplayCount!
            valueSerializer.writeNumber(value__maxDisplayCount_value)
        }
        const value__space  = value._space
        let value__space_type : int32 = RuntimeType.UNDEFINED
        value__space_type = runtimeType(value__space)
        valueSerializer.writeInt8((value__space_type).toChar())
        if ((value__space_type) != (RuntimeType.UNDEFINED)) {
            const value__space_value  = value__space!
            LengthMetrics_serializer.write(valueSerializer, value__space_value)
        }
    }
    public static read(buffer: DeserializerBase): DotIndicator {
        throw new Error("Can not deserialize builder class")
    }
}
export class DigitIndicator_serializer {
    public static write(buffer: SerializerBase, value: DigitIndicator): void {
        let valueSerializer : SerializerBase = buffer
        const value__left  = value._left
        let value__left_type : int32 = RuntimeType.UNDEFINED
        value__left_type = runtimeType(value__left)
        valueSerializer.writeInt8((value__left_type).toChar())
        if ((value__left_type) != (RuntimeType.UNDEFINED)) {
            const value__left_value  = value__left!
            let value__left_value_type : int32 = RuntimeType.UNDEFINED
            value__left_value_type = runtimeType(value__left_value)
            if (RuntimeType.STRING == value__left_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__left_value_0  = value__left_value as string
                valueSerializer.writeString(value__left_value_0)
            }
            else if (RuntimeType.NUMBER == value__left_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__left_value_1  = value__left_value as number
                valueSerializer.writeNumber(value__left_value_1)
            }
            else if (RuntimeType.OBJECT == value__left_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__left_value_2  = value__left_value as Resource
                Resource_serializer.write(valueSerializer, value__left_value_2)
            }
        }
        const value__top  = value._top
        let value__top_type : int32 = RuntimeType.UNDEFINED
        value__top_type = runtimeType(value__top)
        valueSerializer.writeInt8((value__top_type).toChar())
        if ((value__top_type) != (RuntimeType.UNDEFINED)) {
            const value__top_value  = value__top!
            let value__top_value_type : int32 = RuntimeType.UNDEFINED
            value__top_value_type = runtimeType(value__top_value)
            if (RuntimeType.STRING == value__top_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__top_value_0  = value__top_value as string
                valueSerializer.writeString(value__top_value_0)
            }
            else if (RuntimeType.NUMBER == value__top_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__top_value_1  = value__top_value as number
                valueSerializer.writeNumber(value__top_value_1)
            }
            else if (RuntimeType.OBJECT == value__top_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__top_value_2  = value__top_value as Resource
                Resource_serializer.write(valueSerializer, value__top_value_2)
            }
        }
        const value__right  = value._right
        let value__right_type : int32 = RuntimeType.UNDEFINED
        value__right_type = runtimeType(value__right)
        valueSerializer.writeInt8((value__right_type).toChar())
        if ((value__right_type) != (RuntimeType.UNDEFINED)) {
            const value__right_value  = value__right!
            let value__right_value_type : int32 = RuntimeType.UNDEFINED
            value__right_value_type = runtimeType(value__right_value)
            if (RuntimeType.STRING == value__right_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__right_value_0  = value__right_value as string
                valueSerializer.writeString(value__right_value_0)
            }
            else if (RuntimeType.NUMBER == value__right_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__right_value_1  = value__right_value as number
                valueSerializer.writeNumber(value__right_value_1)
            }
            else if (RuntimeType.OBJECT == value__right_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__right_value_2  = value__right_value as Resource
                Resource_serializer.write(valueSerializer, value__right_value_2)
            }
        }
        const value__bottom  = value._bottom
        let value__bottom_type : int32 = RuntimeType.UNDEFINED
        value__bottom_type = runtimeType(value__bottom)
        valueSerializer.writeInt8((value__bottom_type).toChar())
        if ((value__bottom_type) != (RuntimeType.UNDEFINED)) {
            const value__bottom_value  = value__bottom!
            let value__bottom_value_type : int32 = RuntimeType.UNDEFINED
            value__bottom_value_type = runtimeType(value__bottom_value)
            if (RuntimeType.STRING == value__bottom_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__bottom_value_0  = value__bottom_value as string
                valueSerializer.writeString(value__bottom_value_0)
            }
            else if (RuntimeType.NUMBER == value__bottom_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__bottom_value_1  = value__bottom_value as number
                valueSerializer.writeNumber(value__bottom_value_1)
            }
            else if (RuntimeType.OBJECT == value__bottom_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__bottom_value_2  = value__bottom_value as Resource
                Resource_serializer.write(valueSerializer, value__bottom_value_2)
            }
        }
        const value__start  = value._start
        let value__start_type : int32 = RuntimeType.UNDEFINED
        value__start_type = runtimeType(value__start)
        valueSerializer.writeInt8((value__start_type).toChar())
        if ((value__start_type) != (RuntimeType.UNDEFINED)) {
            const value__start_value  = value__start!
            LengthMetrics_serializer.write(valueSerializer, value__start_value)
        }
        const value__end  = value._end
        let value__end_type : int32 = RuntimeType.UNDEFINED
        value__end_type = runtimeType(value__end)
        valueSerializer.writeInt8((value__end_type).toChar())
        if ((value__end_type) != (RuntimeType.UNDEFINED)) {
            const value__end_value  = value__end!
            LengthMetrics_serializer.write(valueSerializer, value__end_value)
        }
        const value__fontColor  = value._fontColor
        let value__fontColor_type : int32 = RuntimeType.UNDEFINED
        value__fontColor_type = runtimeType(value__fontColor)
        valueSerializer.writeInt8((value__fontColor_type).toChar())
        if ((value__fontColor_type) != (RuntimeType.UNDEFINED)) {
            const value__fontColor_value  = value__fontColor!
            let value__fontColor_value_type : int32 = RuntimeType.UNDEFINED
            value__fontColor_value_type = runtimeType(value__fontColor_value)
            if (TypeChecker.isColor(value__fontColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value__fontColor_value_0  = value__fontColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value__fontColor_value_0))
            }
            else if (RuntimeType.NUMBER == value__fontColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__fontColor_value_1  = value__fontColor_value as number
                valueSerializer.writeNumber(value__fontColor_value_1)
            }
            else if (RuntimeType.STRING == value__fontColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__fontColor_value_2  = value__fontColor_value as string
                valueSerializer.writeString(value__fontColor_value_2)
            }
            else if (RuntimeType.OBJECT == value__fontColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value__fontColor_value_3  = value__fontColor_value as Resource
                Resource_serializer.write(valueSerializer, value__fontColor_value_3)
            }
        }
        const value__selectedFontColor  = value._selectedFontColor
        let value__selectedFontColor_type : int32 = RuntimeType.UNDEFINED
        value__selectedFontColor_type = runtimeType(value__selectedFontColor)
        valueSerializer.writeInt8((value__selectedFontColor_type).toChar())
        if ((value__selectedFontColor_type) != (RuntimeType.UNDEFINED)) {
            const value__selectedFontColor_value  = value__selectedFontColor!
            let value__selectedFontColor_value_type : int32 = RuntimeType.UNDEFINED
            value__selectedFontColor_value_type = runtimeType(value__selectedFontColor_value)
            if (TypeChecker.isColor(value__selectedFontColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value__selectedFontColor_value_0  = value__selectedFontColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value__selectedFontColor_value_0))
            }
            else if (RuntimeType.NUMBER == value__selectedFontColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__selectedFontColor_value_1  = value__selectedFontColor_value as number
                valueSerializer.writeNumber(value__selectedFontColor_value_1)
            }
            else if (RuntimeType.STRING == value__selectedFontColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value__selectedFontColor_value_2  = value__selectedFontColor_value as string
                valueSerializer.writeString(value__selectedFontColor_value_2)
            }
            else if (RuntimeType.OBJECT == value__selectedFontColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value__selectedFontColor_value_3  = value__selectedFontColor_value as Resource
                Resource_serializer.write(valueSerializer, value__selectedFontColor_value_3)
            }
        }
        const value__digitFont  = value._digitFont
        let value__digitFont_type : int32 = RuntimeType.UNDEFINED
        value__digitFont_type = runtimeType(value__digitFont)
        valueSerializer.writeInt8((value__digitFont_type).toChar())
        if ((value__digitFont_type) != (RuntimeType.UNDEFINED)) {
            const value__digitFont_value  = value__digitFont!
            Font_serializer.write(valueSerializer, value__digitFont_value)
        }
        const value__selectedDigitFont  = value._selectedDigitFont
        let value__selectedDigitFont_type : int32 = RuntimeType.UNDEFINED
        value__selectedDigitFont_type = runtimeType(value__selectedDigitFont)
        valueSerializer.writeInt8((value__selectedDigitFont_type).toChar())
        if ((value__selectedDigitFont_type) != (RuntimeType.UNDEFINED)) {
            const value__selectedDigitFont_value  = value__selectedDigitFont!
            Font_serializer.write(valueSerializer, value__selectedDigitFont_value)
        }
    }
    public static read(buffer: DeserializerBase): DigitIndicator {
        throw new Error("Can not deserialize builder class")
    }
}
