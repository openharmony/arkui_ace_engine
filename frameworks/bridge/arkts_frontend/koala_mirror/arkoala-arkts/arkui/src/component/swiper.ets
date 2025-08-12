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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { VoidCallback, Length, ResourceColor, VP, Font, Font_serializer } from "./units"
import { Bindable_Number_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { IndicatorComponentController_serializer, IndicatorComponentController } from "./indicatorcomponent"
import { curves_ICurve_serializer, curves } from "./../generated/ohos.curves"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { EdgeEffect, PageFlipMode, Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
        if (animationMode !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animationModeTmpValue  = animationMode!
            if (animationModeTmpValue instanceof SwiperAnimationMode) {
                thisSerializer.writeInt8((0).toChar())
                const animationModeTmpValueForIdx0  = animationModeTmpValue as SwiperAnimationMode
                thisSerializer.writeInt32(TypeChecker.SwiperAnimationMode_ToNumeric(animationModeTmpValueForIdx0))
            } else if (animationModeTmpValue instanceof boolean) {
                thisSerializer.writeInt8((1).toChar())
                const animationModeTmpValueForIdx1  = animationModeTmpValue as boolean
                thisSerializer.writeBoolean(animationModeTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperController_changeIndex(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private finishAnimation_serialize(callback_?: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperController_finishAnimation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private preloadItems_serialize(indices: Array<number> | undefined): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (indices !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const indicesTmpValue  = indices!
            thisSerializer.writeInt32((indicesTmpValue.length).toInt())
            for (let indicesTmpValueCounterI = 0; indicesTmpValueCounterI < indicesTmpValue.length; indicesTmpValueCounterI++) {
                const indicesTmpValueTmpElement : number = indicesTmpValue[indicesTmpValueCounterI]
                thisSerializer.writeNumber(indicesTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const _peer  = new ArkSwiperPeer(_peerPtr, peerId, 'Swiper', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSwiperOptionsAttribute(controller?: SwiperController): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (controller !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const controllerTmpValue  = controller!
            SwiperController_serializer.write(thisSerializer, controllerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperInterface_setSwiperOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndexAttribute(value: number | Bindable<number> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<number>) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<number>
                Bindable_Number_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIntervalAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setInterval(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorAttribute(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof IndicatorComponentController) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as IndicatorComponentController
                IndicatorComponentController_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof DotIndicator) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as DotIndicator
                DotIndicator_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof DigitIndicator) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as DigitIndicator
                DigitIndicator_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SwiperAttribute_setLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDurationAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SwiperAttribute_setVertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemSpaceAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setItemSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisplayModeAttribute(value: SwiperDisplayMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SwiperDisplayMode)
            thisSerializer.writeInt32(TypeChecker.SwiperDisplayMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDisplayMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEffectModeAttribute(value: EdgeEffect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setEffectMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisableSwipeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDisableSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCurveAttribute(value: curves.Curve | string | curves.ICurve | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof curves.Curve) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as curves.Curve
                thisSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof curves.ICurve) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as curves.ICurve
                curves_ICurve_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setCurve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUnselectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnUnselected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAnimationStartAttribute(value: OnSwiperAnimationStartCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAnimationEndAttribute(value: OnSwiperAnimationEndCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGestureSwipeAttribute(value: OnSwiperGestureSwipeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNestedScrollAttribute(value: SwiperNestedScrollMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SwiperNestedScrollMode)
            thisSerializer.writeInt32(TypeChecker.SwiperNestedScrollMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomContentTransitionAttribute(value: SwiperContentAnimatedTransition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SwiperContentAnimatedTransition_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setCustomContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentDidScrollAttribute(value: ContentDidScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnContentDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorInteractiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setIndicatorInteractive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPageFlipModeAttribute(value: PageFlipMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as PageFlipMode)
            thisSerializer.writeInt32(TypeChecker.PageFlipMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setPageFlipMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentWillScrollAttribute(value: ContentWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setOnContentWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoPlayAttribute(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (autoPlay !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const autoPlayTmpValue  = autoPlay!
            thisSerializer.writeBoolean(autoPlayTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            AutoPlayOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setAutoPlay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisplayArrowAttribute(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ArrowStyle) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ArrowStyle
                ArrowStyle_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (isHoverShow !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const isHoverShowTmpValue  = isHoverShow!
            thisSerializer.writeBoolean(isHoverShowTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDisplayArrow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount1Attribute(count: number | undefined, isShown: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue  = count!
            thisSerializer.writeNumber(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (isShown !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const isShownTmpValue  = isShown!
            thisSerializer.writeBoolean(isShownTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setCachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisplayCountAttribute(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof SwiperAutoFill) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as SwiperAutoFill
                SwiperAutoFill_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (swipeByGroup !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const swipeByGroupTmpValue  = swipeByGroup!
            thisSerializer.writeBoolean(swipeByGroupTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setDisplayCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrevMarginAttribute(value: Length | undefined, ignoreBlank?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (ignoreBlank !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const ignoreBlankTmpValue  = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlankTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setPrevMargin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNextMarginAttribute(value: Length | undefined, ignoreBlank?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (ignoreBlank !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const ignoreBlankTmpValue  = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlankTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_setNextMargin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    index(value: number | Bindable<number> | undefined): this {
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
    attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSwiperStyle extends ArkCommonMethodStyle implements SwiperAttribute {
    index_value?: number | Bindable<number> | undefined
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
    public index(value: number | Bindable<number> | undefined): this {
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
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public index(value: number | Bindable<number> | undefined): this {
        if (this.checkPriority("index")) {
            const value_casted = value as (number | Bindable<number> | undefined)
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
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class SwiperModifier extends CommonMethodModifier implements SwiperAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _index_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _index_0_0value?: number | Bindable<number> | undefined
    _interval_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _interval_0_0value?: number | undefined
    _indicator_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _indicator_0_0value?: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined
    _loop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _loop_0_0value?: boolean | undefined
    _duration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _duration_0_0value?: number | undefined
    _vertical_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _vertical_0_0value?: boolean | undefined
    _itemSpace_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _itemSpace_0_0value?: number | string | undefined
    _displayMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _displayMode_0_0value?: SwiperDisplayMode | undefined
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_0_0value?: number | undefined
    _effectMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _effectMode_0_0value?: EdgeEffect | undefined
    _disableSwipe_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _disableSwipe_0_0value?: boolean | undefined
    _curve_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _curve_0_0value?: curves.Curve | string | curves.ICurve | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value0: number) => void) | undefined
    _onSelected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelected_0_0value?: ((value0: number) => void) | undefined
    _onUnselected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUnselected_0_0value?: ((value0: number) => void) | undefined
    _onAnimationStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAnimationStart_0_0value?: OnSwiperAnimationStartCallback | undefined
    _onAnimationEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAnimationEnd_0_0value?: OnSwiperAnimationEndCallback | undefined
    _onGestureSwipe_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGestureSwipe_0_0value?: OnSwiperGestureSwipeCallback | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: SwiperNestedScrollMode | undefined
    _customContentTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customContentTransition_0_0value?: SwiperContentAnimatedTransition | undefined
    _onContentDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentDidScroll_0_0value?: ContentDidScrollCallback | undefined
    _indicatorInteractive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _indicatorInteractive_0_0value?: boolean | undefined
    _pageFlipMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pageFlipMode_0_0value?: PageFlipMode | undefined
    _onContentWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentWillScroll_0_0value?: ContentWillScrollCallback | undefined
    _autoPlay_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoPlay_0_0value?: boolean | undefined
    _autoPlay_0_1value?: AutoPlayOptions | undefined
    _displayArrow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _displayArrow_0_0value?: ArrowStyle | boolean | undefined
    _displayArrow_0_1value?: boolean | undefined
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_1_0value?: number | undefined
    _cachedCount_1_1value?: boolean | undefined
    _displayCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _displayCount_0_0value?: number | string | SwiperAutoFill | undefined
    _displayCount_0_1value?: boolean | undefined
    _prevMargin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _prevMargin_0_0value?: Length | undefined
    _prevMargin_0_1value?: boolean | undefined
    _nextMargin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nextMargin_0_0value?: Length | undefined
    _nextMargin_0_1value?: boolean | undefined
    applyModifierPatch(peer: ArkSwiperPeer): void {
        super.applyModifierPatch(peer)
        if (this._index_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._index_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndexAttribute((this._index_0_0value as number | Bindable<number> | undefined));
                    this._index_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._index_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._index_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndexAttribute((undefined as number | Bindable<number> | undefined));
                }
            }
        }
        if (this._interval_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._interval_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIntervalAttribute((this._interval_0_0value as number | undefined));
                    this._interval_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._interval_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._interval_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIntervalAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._indicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._indicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndicatorAttribute((this._indicator_0_0value as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
                    this._indicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._indicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._indicator_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndicatorAttribute((undefined as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
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
        if (this._duration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._duration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDurationAttribute((this._duration_0_0value as number | undefined));
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._duration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDurationAttribute((undefined as number | undefined));
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
        if (this._itemSpace_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._itemSpace_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setItemSpaceAttribute((this._itemSpace_0_0value as number | string | undefined));
                    this._itemSpace_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._itemSpace_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._itemSpace_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setItemSpaceAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._displayMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._displayMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisplayModeAttribute((this._displayMode_0_0value as SwiperDisplayMode | undefined));
                    this._displayMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._displayMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._displayMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisplayModeAttribute((undefined as SwiperDisplayMode | undefined));
                }
            }
        }
        if (this._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as number | undefined));
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._effectMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._effectMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEffectModeAttribute((this._effectMode_0_0value as EdgeEffect | undefined));
                    this._effectMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._effectMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._effectMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEffectModeAttribute((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (this._disableSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._disableSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisableSwipeAttribute((this._disableSwipe_0_0value as boolean | undefined));
                    this._disableSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._disableSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._disableSwipe_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisableSwipeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._curve_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._curve_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCurveAttribute((this._curve_0_0value as curves.Curve | string | curves.ICurve | undefined));
                    this._curve_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._curve_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._curve_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCurveAttribute((undefined as curves.Curve | string | curves.ICurve | undefined));
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
        if (this._onSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSelectedAttribute((this._onSelected_0_0value as ((value0: number) => void) | undefined));
                    this._onSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSelectedAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onUnselected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onUnselected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnUnselectedAttribute((this._onUnselected_0_0value as ((value0: number) => void) | undefined));
                    this._onUnselected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUnselected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUnselected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnUnselectedAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onAnimationStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAnimationStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAnimationStartAttribute((this._onAnimationStart_0_0value as OnSwiperAnimationStartCallback | undefined));
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAnimationStartAttribute((undefined as OnSwiperAnimationStartCallback | undefined));
                }
            }
        }
        if (this._onAnimationEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAnimationEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAnimationEndAttribute((this._onAnimationEnd_0_0value as OnSwiperAnimationEndCallback | undefined));
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAnimationEndAttribute((undefined as OnSwiperAnimationEndCallback | undefined));
                }
            }
        }
        if (this._onGestureSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGestureSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGestureSwipeAttribute((this._onGestureSwipe_0_0value as OnSwiperGestureSwipeCallback | undefined));
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGestureSwipeAttribute((undefined as OnSwiperGestureSwipeCallback | undefined));
                }
            }
        }
        if (this._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as SwiperNestedScrollMode | undefined));
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNestedScrollAttribute((undefined as SwiperNestedScrollMode | undefined));
                }
            }
        }
        if (this._customContentTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomContentTransitionAttribute((this._customContentTransition_0_0value as SwiperContentAnimatedTransition | undefined));
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomContentTransitionAttribute((undefined as SwiperContentAnimatedTransition | undefined));
                }
            }
        }
        if (this._onContentDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContentDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContentDidScrollAttribute((this._onContentDidScroll_0_0value as ContentDidScrollCallback | undefined));
                    this._onContentDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentDidScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContentDidScrollAttribute((undefined as ContentDidScrollCallback | undefined));
                }
            }
        }
        if (this._indicatorInteractive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._indicatorInteractive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndicatorInteractiveAttribute((this._indicatorInteractive_0_0value as boolean | undefined));
                    this._indicatorInteractive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._indicatorInteractive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._indicatorInteractive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndicatorInteractiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._pageFlipMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pageFlipMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPageFlipModeAttribute((this._pageFlipMode_0_0value as PageFlipMode | undefined));
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPageFlipModeAttribute((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (this._onContentWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContentWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContentWillScrollAttribute((this._onContentWillScroll_0_0value as ContentWillScrollCallback | undefined));
                    this._onContentWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentWillScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContentWillScrollAttribute((undefined as ContentWillScrollCallback | undefined));
                }
            }
        }
        if (this._autoPlay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoPlay_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoPlayAttribute((this._autoPlay_0_0value as boolean | undefined), (this._autoPlay_0_1value as AutoPlayOptions | undefined));
                    this._autoPlay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoPlay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoPlay_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoPlayAttribute((undefined as boolean | undefined), (undefined as AutoPlayOptions | undefined));
                }
            }
        }
        if (this._displayArrow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._displayArrow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisplayArrowAttribute((this._displayArrow_0_0value as ArrowStyle | boolean | undefined), (this._displayArrow_0_1value as boolean | undefined));
                    this._displayArrow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._displayArrow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._displayArrow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisplayArrowAttribute((undefined as ArrowStyle | boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (this._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as number | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount1Attribute((undefined as number | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._displayCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._displayCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisplayCountAttribute((this._displayCount_0_0value as number | string | SwiperAutoFill | undefined), (this._displayCount_0_1value as boolean | undefined));
                    this._displayCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._displayCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._displayCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisplayCountAttribute((undefined as number | string | SwiperAutoFill | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (this._prevMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._prevMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrevMarginAttribute((this._prevMargin_0_0value as Length | undefined), (this._prevMargin_0_1value as boolean | undefined));
                    this._prevMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._prevMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._prevMargin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrevMarginAttribute((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (this._nextMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nextMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNextMarginAttribute((this._nextMargin_0_0value as Length | undefined), (this._nextMargin_0_1value as boolean | undefined));
                    this._nextMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nextMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nextMargin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNextMarginAttribute((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SwiperModifier): void {
        super.mergeModifier(modifier)
        if (modifier._index_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._index_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.index(modifier._index_0_0value);
                    break;
                }
                default: {
                    this.index((undefined as number | Bindable<number> | undefined));
                }
            }
        }
        if (modifier._interval_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._interval_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.interval(modifier._interval_0_0value);
                    break;
                }
                default: {
                    this.interval((undefined as number | undefined));
                }
            }
        }
        if (modifier._indicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._indicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.indicator(modifier._indicator_0_0value);
                    break;
                }
                default: {
                    this.indicator((undefined as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
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
        if (modifier._duration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._duration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.duration(modifier._duration_0_0value);
                    break;
                }
                default: {
                    this.duration((undefined as number | undefined));
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
        if (modifier._itemSpace_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._itemSpace_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.itemSpace(modifier._itemSpace_0_0value);
                    break;
                }
                default: {
                    this.itemSpace((undefined as number | string | undefined));
                }
            }
        }
        if (modifier._displayMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._displayMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.displayMode(modifier._displayMode_0_0value);
                    break;
                }
                default: {
                    this.displayMode((undefined as SwiperDisplayMode | undefined));
                }
            }
        }
        if (modifier._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_0_0value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as number | undefined));
                }
            }
        }
        if (modifier._effectMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._effectMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.effectMode(modifier._effectMode_0_0value);
                    break;
                }
                default: {
                    this.effectMode((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (modifier._disableSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._disableSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.disableSwipe(modifier._disableSwipe_0_0value);
                    break;
                }
                default: {
                    this.disableSwipe((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._curve_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._curve_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.curve(modifier._curve_0_0value);
                    break;
                }
                default: {
                    this.curve((undefined as curves.Curve | string | curves.ICurve | undefined));
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
        if (modifier._onSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelected(modifier._onSelected_0_0value);
                    break;
                }
                default: {
                    this.onSelected((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onUnselected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onUnselected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUnselected(modifier._onUnselected_0_0value);
                    break;
                }
                default: {
                    this.onUnselected((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onAnimationStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAnimationStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAnimationStart(modifier._onAnimationStart_0_0value);
                    break;
                }
                default: {
                    this.onAnimationStart((undefined as OnSwiperAnimationStartCallback | undefined));
                }
            }
        }
        if (modifier._onAnimationEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAnimationEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAnimationEnd(modifier._onAnimationEnd_0_0value);
                    break;
                }
                default: {
                    this.onAnimationEnd((undefined as OnSwiperAnimationEndCallback | undefined));
                }
            }
        }
        if (modifier._onGestureSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGestureSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGestureSwipe(modifier._onGestureSwipe_0_0value);
                    break;
                }
                default: {
                    this.onGestureSwipe((undefined as OnSwiperGestureSwipeCallback | undefined));
                }
            }
        }
        if (modifier._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as SwiperNestedScrollMode | undefined));
                }
            }
        }
        if (modifier._customContentTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customContentTransition(modifier._customContentTransition_0_0value);
                    break;
                }
                default: {
                    this.customContentTransition((undefined as SwiperContentAnimatedTransition | undefined));
                }
            }
        }
        if (modifier._onContentDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContentDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentDidScroll(modifier._onContentDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentDidScroll((undefined as ContentDidScrollCallback | undefined));
                }
            }
        }
        if (modifier._indicatorInteractive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._indicatorInteractive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.indicatorInteractive(modifier._indicatorInteractive_0_0value);
                    break;
                }
                default: {
                    this.indicatorInteractive((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._pageFlipMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pageFlipMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pageFlipMode(modifier._pageFlipMode_0_0value);
                    break;
                }
                default: {
                    this.pageFlipMode((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (modifier._onContentWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContentWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentWillScroll(modifier._onContentWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentWillScroll((undefined as ContentWillScrollCallback | undefined));
                }
            }
        }
        if (modifier._autoPlay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoPlay_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoPlay(modifier._autoPlay_0_0value, modifier._autoPlay_0_1value);
                    break;
                }
                default: {
                    this.autoPlay((undefined as boolean | undefined), (undefined as AutoPlayOptions | undefined));
                }
            }
        }
        if (modifier._displayArrow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._displayArrow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.displayArrow(modifier._displayArrow_0_0value, modifier._displayArrow_0_1value);
                    break;
                }
                default: {
                    this.displayArrow((undefined as ArrowStyle | boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (modifier._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as number | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (modifier._displayCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._displayCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.displayCount(modifier._displayCount_0_0value, modifier._displayCount_0_1value);
                    break;
                }
                default: {
                    this.displayCount((undefined as number | string | SwiperAutoFill | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (modifier._prevMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._prevMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.prevMargin(modifier._prevMargin_0_0value, modifier._prevMargin_0_1value);
                    break;
                }
                default: {
                    this.prevMargin((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (modifier._nextMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nextMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nextMargin(modifier._nextMargin_0_0value, modifier._nextMargin_0_1value);
                    break;
                }
                default: {
                    this.nextMargin((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    index(value: number | Bindable<number> | undefined): this {
        if (((this._index_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._index_0_flag = AttributeUpdaterFlag.UPDATE
            this._index_0_0value = value
        } else
        {
            this._index_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    interval(value: number | undefined): this {
        if (((this._interval_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._interval_0_0value) !== (value)))
        {
            this._interval_0_flag = AttributeUpdaterFlag.UPDATE
            this._interval_0_0value = value
        } else
        {
            this._interval_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        if (((this._indicator_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._indicator_0_flag = AttributeUpdaterFlag.UPDATE
            this._indicator_0_0value = value
        } else
        {
            this._indicator_0_flag = AttributeUpdaterFlag.SKIP
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
    duration(value: number | undefined): this {
        if (((this._duration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._duration_0_0value) !== (value)))
        {
            this._duration_0_flag = AttributeUpdaterFlag.UPDATE
            this._duration_0_0value = value
        } else
        {
            this._duration_0_flag = AttributeUpdaterFlag.SKIP
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
    itemSpace(value: number | string | undefined): this {
        if (((this._itemSpace_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._itemSpace_0_0value) !== (value)))
        {
            this._itemSpace_0_flag = AttributeUpdaterFlag.UPDATE
            this._itemSpace_0_0value = value
        } else
        {
            this._itemSpace_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    displayMode(value: SwiperDisplayMode | undefined): this {
        if (((this._displayMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._displayMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._displayMode_0_0value = value
        } else
        {
            this._displayMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(value: number | undefined): this {
        if (((this._cachedCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_0_0value) !== (value)))
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_0_0value = value
        } else
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    effectMode(value: EdgeEffect | undefined): this {
        if (((this._effectMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._effectMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._effectMode_0_0value = value
        } else
        {
            this._effectMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    disableSwipe(value: boolean | undefined): this {
        if (((this._disableSwipe_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._disableSwipe_0_0value) !== (value)))
        {
            this._disableSwipe_0_flag = AttributeUpdaterFlag.UPDATE
            this._disableSwipe_0_0value = value
        } else
        {
            this._disableSwipe_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    curve(value: curves.Curve | string | curves.ICurve | undefined): this {
        if (((this._curve_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._curve_0_flag = AttributeUpdaterFlag.UPDATE
            this._curve_0_0value = value
        } else
        {
            this._curve_0_flag = AttributeUpdaterFlag.SKIP
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
    onSelected(value: ((value0: number) => void) | undefined): this {
        if (((this._onSelected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelected_0_0value = value
        } else
        {
            this._onSelected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUnselected(value: ((value0: number) => void) | undefined): this {
        if (((this._onUnselected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onUnselected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUnselected_0_0value = value
        } else
        {
            this._onUnselected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        if (((this._onAnimationStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAnimationStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAnimationStart_0_0value = value
        } else
        {
            this._onAnimationStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        if (((this._onAnimationEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAnimationEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAnimationEnd_0_0value = value
        } else
        {
            this._onAnimationEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        if (((this._onGestureSwipe_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGestureSwipe_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGestureSwipe_0_0value = value
        } else
        {
            this._onGestureSwipe_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        if (((this._nestedScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._nestedScroll_0_0value = value
        } else
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        if (((this._customContentTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._customContentTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._customContentTransition_0_0value = value
        } else
        {
            this._customContentTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        if (((this._onContentDidScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContentDidScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentDidScroll_0_0value = value
        } else
        {
            this._onContentDidScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    indicatorInteractive(value: boolean | undefined): this {
        if (((this._indicatorInteractive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._indicatorInteractive_0_0value) !== (value)))
        {
            this._indicatorInteractive_0_flag = AttributeUpdaterFlag.UPDATE
            this._indicatorInteractive_0_0value = value
        } else
        {
            this._indicatorInteractive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        if (((this._pageFlipMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pageFlipMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._pageFlipMode_0_0value = value
        } else
        {
            this._pageFlipMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        if (((this._onContentWillScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContentWillScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentWillScroll_0_0value = value
        } else
        {
            this._onContentWillScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): this {
        if (((this._autoPlay_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoPlay_0_0value) !== (autoPlay)) || (true))
        {
            this._autoPlay_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoPlay_0_0value = autoPlay
            this._autoPlay_0_1value = options
        } else
        {
            this._autoPlay_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        if (((this._displayArrow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._displayArrow_0_1value) !== (isHoverShow)))
        {
            this._displayArrow_0_flag = AttributeUpdaterFlag.UPDATE
            this._displayArrow_0_0value = value
            this._displayArrow_0_1value = isHoverShow
        } else
        {
            this._displayArrow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(count: number | undefined, isShown: boolean | undefined): this {
        if (((this._cachedCount_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_1_0value) !== (count)) || ((this._cachedCount_1_1value) !== (isShown)))
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_1_0value = count
            this._cachedCount_1_1value = isShown
        } else
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    displayCount(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        if (((this._displayCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._displayCount_0_1value) !== (swipeByGroup)))
        {
            this._displayCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._displayCount_0_0value = value
            this._displayCount_0_1value = swipeByGroup
        } else
        {
            this._displayCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (((this._prevMargin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._prevMargin_0_1value) !== (ignoreBlank)))
        {
            this._prevMargin_0_flag = AttributeUpdaterFlag.UPDATE
            this._prevMargin_0_0value = value
            this._prevMargin_0_1value = ignoreBlank
        } else
        {
            this._prevMargin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (((this._nextMargin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._nextMargin_0_1value) !== (ignoreBlank)))
        {
            this._nextMargin_0_flag = AttributeUpdaterFlag.UPDATE
            this._nextMargin_0_0value = value
            this._nextMargin_0_1value = ignoreBlank
        } else
        {
            this._nextMargin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
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
        const valueHolderForCurrentOffset  = value.currentOffset
        valueSerializer.writeNumber(valueHolderForCurrentOffset)
        const valueHolderForTargetOffset  = value.targetOffset
        valueSerializer.writeNumber(valueHolderForTargetOffset)
        const valueHolderForVelocity  = value.velocity
        valueSerializer.writeNumber(valueHolderForVelocity)
    }
    public static read(buffer: DeserializerBase): SwiperAnimationEvent {
        let valueDeserializer : DeserializerBase = buffer
        const currentOffsetTmpResult : number = (valueDeserializer.readNumber() as number)
        const targetOffsetTmpResult : number = (valueDeserializer.readNumber() as number)
        const velocityTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : SwiperAnimationEvent = ({currentOffset: currentOffsetTmpResult, targetOffset: targetOffsetTmpResult, velocity: velocityTmpResult} as SwiperAnimationEvent)
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
        const valueHolderForCurrentIndex  = value.currentIndex
        valueSerializer.writeNumber(valueHolderForCurrentIndex)
        const valueHolderForComingIndex  = value.comingIndex
        valueSerializer.writeNumber(valueHolderForComingIndex)
        const valueHolderForOffset  = value.offset
        valueSerializer.writeNumber(valueHolderForOffset)
    }
    public static read(buffer: DeserializerBase): SwiperContentWillScrollResult {
        let valueDeserializer : DeserializerBase = buffer
        const currentIndexTmpResult : number = (valueDeserializer.readNumber() as number)
        const comingIndexTmpResult : number = (valueDeserializer.readNumber() as number)
        const offsetTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : SwiperContentWillScrollResult = ({currentIndex: currentIndexTmpResult, comingIndex: comingIndexTmpResult, offset: offsetTmpResult} as SwiperContentWillScrollResult)
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
        const valueHolderForStopWhenTouched  = value.stopWhenTouched
        valueSerializer.writeBoolean(valueHolderForStopWhenTouched)
    }
    public static read(buffer: DeserializerBase): AutoPlayOptions {
        let valueDeserializer : DeserializerBase = buffer
        const stopWhenTouchedTmpResult : boolean = valueDeserializer.readBoolean()
        let value : AutoPlayOptions = ({stopWhenTouched: stopWhenTouchedTmpResult} as AutoPlayOptions)
        return value
    }
}
export class SwiperAutoFill_serializer {
    public static write(buffer: SerializerBase, value: SwiperAutoFill): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMinSize  = value.minSize
        if (valueHolderForMinSize instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForMinSizeForIdx0  = valueHolderForMinSize as string
            valueSerializer.writeString(valueHolderForMinSizeForIdx0)
        } else if (valueHolderForMinSize instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForMinSizeForIdx1  = valueHolderForMinSize as number
            valueSerializer.writeNumber(valueHolderForMinSizeForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): SwiperAutoFill {
        let valueDeserializer : DeserializerBase = buffer
        const minSizeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let minSizeTmpBuf : string | number | undefined
        if (minSizeTmpBufUnionSelector == (0).toChar()) {
            minSizeTmpBuf = (valueDeserializer.readString() as string)
        } else if (minSizeTmpBufUnionSelector == (1).toChar()) {
            minSizeTmpBuf = (valueDeserializer.readNumber() as number)
        } else {
            throw new Error("One of the branches for minSizeTmpBuf has to be chosen through deserialisation.")
        }
        const minSizeTmpResult : VP = (minSizeTmpBuf as string | number)
        let value : SwiperAutoFill = ({minSize: minSizeTmpResult} as SwiperAutoFill)
        return value
    }
}
export class SwiperContentAnimatedTransition_serializer {
    public static write(buffer: SerializerBase, value: SwiperContentAnimatedTransition): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTimeout  = value.timeout
        if (valueHolderForTimeout !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTimeoutTmpValue  = valueHolderForTimeout!
            valueSerializer.writeNumber(valueHolderForTimeoutTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition  = value.transition
        valueSerializer.holdAndWriteCallback(valueHolderForTransition)
    }
    public static read(buffer: DeserializerBase): SwiperContentAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const timeoutTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeoutTmpBuf : number | undefined
        if ((timeoutTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeoutTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const timeoutTmpResult : number | undefined = timeoutTmpBuf
        const transitionTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const transitionTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const transitionTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const transitionTmpResult : ((value0: SwiperContentTransitionProxy) => void) = (value0: SwiperContentTransitionProxy):void => {
            const transitionTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            transitionTmpBufBufArgsSerializer.writeInt32(transitionTmpBufBufResource.resourceId);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCall);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCallSync);
            SwiperContentTransitionProxy_serializer.write(transitionTmpBufBufArgsSerializer, value0);
            InteropNativeModule._CallCallback(-416053361, transitionTmpBufBufArgsSerializer.asBuffer(), transitionTmpBufBufArgsSerializer.length());
            transitionTmpBufBufArgsSerializer.release();
            return;
        }
        let value : SwiperContentAnimatedTransition = ({timeout: timeoutTmpResult, transition: transitionTmpResult} as SwiperContentAnimatedTransition)
        return value
    }
}
export class ArrowStyle_serializer {
    public static write(buffer: SerializerBase, value: ArrowStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForShowBackground  = value.showBackground
        if (valueHolderForShowBackground !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowBackgroundTmpValue  = valueHolderForShowBackground!
            valueSerializer.writeBoolean(valueHolderForShowBackgroundTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsSidebarMiddle  = value.isSidebarMiddle
        if (valueHolderForIsSidebarMiddle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsSidebarMiddleTmpValue  = valueHolderForIsSidebarMiddle!
            valueSerializer.writeBoolean(valueHolderForIsSidebarMiddleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundSize  = value.backgroundSize
        if (valueHolderForBackgroundSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundSizeTmpValue  = valueHolderForBackgroundSize!
            if (valueHolderForBackgroundSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBackgroundSizeTmpValueForIdx0  = valueHolderForBackgroundSizeTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundSizeTmpValueForIdx0)
            } else if (valueHolderForBackgroundSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBackgroundSizeTmpValueForIdx1  = valueHolderForBackgroundSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundSizeTmpValueForIdx1)
            } else if (valueHolderForBackgroundSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForBackgroundSizeTmpValueForIdx2  = valueHolderForBackgroundSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBackgroundColorTmpValueForIdx0))
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForArrowSize  = value.arrowSize
        if (valueHolderForArrowSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForArrowSizeTmpValue  = valueHolderForArrowSize!
            if (valueHolderForArrowSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForArrowSizeTmpValueForIdx0  = valueHolderForArrowSizeTmpValue as string
                valueSerializer.writeString(valueHolderForArrowSizeTmpValueForIdx0)
            } else if (valueHolderForArrowSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForArrowSizeTmpValueForIdx1  = valueHolderForArrowSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForArrowSizeTmpValueForIdx1)
            } else if (valueHolderForArrowSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForArrowSizeTmpValueForIdx2  = valueHolderForArrowSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForArrowSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForArrowColor  = value.arrowColor
        if (valueHolderForArrowColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForArrowColorTmpValue  = valueHolderForArrowColor!
            if (valueHolderForArrowColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForArrowColorTmpValueForIdx0  = valueHolderForArrowColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForArrowColorTmpValueForIdx0))
            } else if (valueHolderForArrowColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForArrowColorTmpValueForIdx1  = valueHolderForArrowColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForArrowColorTmpValueForIdx1)
            } else if (valueHolderForArrowColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForArrowColorTmpValueForIdx2  = valueHolderForArrowColorTmpValue as string
                valueSerializer.writeString(valueHolderForArrowColorTmpValueForIdx2)
            } else if (valueHolderForArrowColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForArrowColorTmpValueForIdx3  = valueHolderForArrowColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForArrowColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ArrowStyle {
        let valueDeserializer : DeserializerBase = buffer
        const showBackgroundTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showBackgroundTmpBuf : boolean | undefined
        if ((showBackgroundTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showBackgroundTmpBuf = valueDeserializer.readBoolean()
        }
        const showBackgroundTmpResult : boolean | undefined = showBackgroundTmpBuf
        const isSidebarMiddleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isSidebarMiddleTmpBuf : boolean | undefined
        if ((isSidebarMiddleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isSidebarMiddleTmpBuf = valueDeserializer.readBoolean()
        }
        const isSidebarMiddleTmpResult : boolean | undefined = isSidebarMiddleTmpBuf
        const backgroundSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundSizeTmpBuf : Length | undefined
        if ((backgroundSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundSizeTmpBuf_ : string | number | Resource | undefined
            if (backgroundSizeTmpBuf_UnionSelector == (0).toChar()) {
                backgroundSizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundSizeTmpBuf_UnionSelector == (1).toChar()) {
                backgroundSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundSizeTmpBuf_UnionSelector == (2).toChar()) {
                backgroundSizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundSizeTmpBuf = (backgroundSizeTmpBuf_ as string | number | Resource)
        }
        const backgroundSizeTmpResult : Length | undefined = backgroundSizeTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const arrowSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let arrowSizeTmpBuf : Length | undefined
        if ((arrowSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const arrowSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let arrowSizeTmpBuf_ : string | number | Resource | undefined
            if (arrowSizeTmpBuf_UnionSelector == (0).toChar()) {
                arrowSizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (arrowSizeTmpBuf_UnionSelector == (1).toChar()) {
                arrowSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (arrowSizeTmpBuf_UnionSelector == (2).toChar()) {
                arrowSizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for arrowSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            arrowSizeTmpBuf = (arrowSizeTmpBuf_ as string | number | Resource)
        }
        const arrowSizeTmpResult : Length | undefined = arrowSizeTmpBuf
        const arrowColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let arrowColorTmpBuf : ResourceColor | undefined
        if ((arrowColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const arrowColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let arrowColorTmpBuf_ : Color | number | string | Resource | undefined
            if (arrowColorTmpBuf_UnionSelector == (0).toChar()) {
                arrowColorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (arrowColorTmpBuf_UnionSelector == (1).toChar()) {
                arrowColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (arrowColorTmpBuf_UnionSelector == (2).toChar()) {
                arrowColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (arrowColorTmpBuf_UnionSelector == (3).toChar()) {
                arrowColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for arrowColorTmpBuf_ has to be chosen through deserialisation.")
            }
            arrowColorTmpBuf = (arrowColorTmpBuf_ as Color | number | string | Resource)
        }
        const arrowColorTmpResult : ResourceColor | undefined = arrowColorTmpBuf
        let value : ArrowStyle = ({showBackground: showBackgroundTmpResult, isSidebarMiddle: isSidebarMiddleTmpResult, backgroundSize: backgroundSizeTmpResult, backgroundColor: backgroundColorTmpResult, arrowSize: arrowSizeTmpResult, arrowColor: arrowColorTmpResult} as ArrowStyle)
        return value
    }
}
export class DotIndicator_serializer {
    public static write(buffer: SerializerBase, value: DotIndicator): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderFor_left  = value._left
        if (valueHolderFor_left !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_leftTmpValue  = valueHolderFor_left!
            if (valueHolderFor_leftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_leftTmpValueForIdx0  = valueHolderFor_leftTmpValue as string
                valueSerializer.writeString(valueHolderFor_leftTmpValueForIdx0)
            } else if (valueHolderFor_leftTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_leftTmpValueForIdx1  = valueHolderFor_leftTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_leftTmpValueForIdx1)
            } else if (valueHolderFor_leftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_leftTmpValueForIdx2  = valueHolderFor_leftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_leftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_top  = value._top
        if (valueHolderFor_top !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_topTmpValue  = valueHolderFor_top!
            if (valueHolderFor_topTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_topTmpValueForIdx0  = valueHolderFor_topTmpValue as string
                valueSerializer.writeString(valueHolderFor_topTmpValueForIdx0)
            } else if (valueHolderFor_topTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_topTmpValueForIdx1  = valueHolderFor_topTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_topTmpValueForIdx1)
            } else if (valueHolderFor_topTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_topTmpValueForIdx2  = valueHolderFor_topTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_topTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_right  = value._right
        if (valueHolderFor_right !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_rightTmpValue  = valueHolderFor_right!
            if (valueHolderFor_rightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_rightTmpValueForIdx0  = valueHolderFor_rightTmpValue as string
                valueSerializer.writeString(valueHolderFor_rightTmpValueForIdx0)
            } else if (valueHolderFor_rightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_rightTmpValueForIdx1  = valueHolderFor_rightTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_rightTmpValueForIdx1)
            } else if (valueHolderFor_rightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_rightTmpValueForIdx2  = valueHolderFor_rightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_rightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_bottom  = value._bottom
        if (valueHolderFor_bottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_bottomTmpValue  = valueHolderFor_bottom!
            if (valueHolderFor_bottomTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_bottomTmpValueForIdx0  = valueHolderFor_bottomTmpValue as string
                valueSerializer.writeString(valueHolderFor_bottomTmpValueForIdx0)
            } else if (valueHolderFor_bottomTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_bottomTmpValueForIdx1  = valueHolderFor_bottomTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_bottomTmpValueForIdx1)
            } else if (valueHolderFor_bottomTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_bottomTmpValueForIdx2  = valueHolderFor_bottomTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_bottomTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_start  = value._start
        if (valueHolderFor_start !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_startTmpValue  = valueHolderFor_start!
            LengthMetrics_serializer.write(valueSerializer, valueHolderFor_startTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_end  = value._end
        if (valueHolderFor_end !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_endTmpValue  = valueHolderFor_end!
            LengthMetrics_serializer.write(valueSerializer, valueHolderFor_endTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_itemWidth  = value._itemWidth
        if (valueHolderFor_itemWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_itemWidthTmpValue  = valueHolderFor_itemWidth!
            if (valueHolderFor_itemWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_itemWidthTmpValueForIdx0  = valueHolderFor_itemWidthTmpValue as string
                valueSerializer.writeString(valueHolderFor_itemWidthTmpValueForIdx0)
            } else if (valueHolderFor_itemWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_itemWidthTmpValueForIdx1  = valueHolderFor_itemWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_itemWidthTmpValueForIdx1)
            } else if (valueHolderFor_itemWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_itemWidthTmpValueForIdx2  = valueHolderFor_itemWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_itemWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_itemHeight  = value._itemHeight
        if (valueHolderFor_itemHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_itemHeightTmpValue  = valueHolderFor_itemHeight!
            if (valueHolderFor_itemHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_itemHeightTmpValueForIdx0  = valueHolderFor_itemHeightTmpValue as string
                valueSerializer.writeString(valueHolderFor_itemHeightTmpValueForIdx0)
            } else if (valueHolderFor_itemHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_itemHeightTmpValueForIdx1  = valueHolderFor_itemHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_itemHeightTmpValueForIdx1)
            } else if (valueHolderFor_itemHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_itemHeightTmpValueForIdx2  = valueHolderFor_itemHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_itemHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_selectedItemWidth  = value._selectedItemWidth
        if (valueHolderFor_selectedItemWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_selectedItemWidthTmpValue  = valueHolderFor_selectedItemWidth!
            if (valueHolderFor_selectedItemWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_selectedItemWidthTmpValueForIdx0  = valueHolderFor_selectedItemWidthTmpValue as string
                valueSerializer.writeString(valueHolderFor_selectedItemWidthTmpValueForIdx0)
            } else if (valueHolderFor_selectedItemWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_selectedItemWidthTmpValueForIdx1  = valueHolderFor_selectedItemWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_selectedItemWidthTmpValueForIdx1)
            } else if (valueHolderFor_selectedItemWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_selectedItemWidthTmpValueForIdx2  = valueHolderFor_selectedItemWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_selectedItemWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_selectedItemHeight  = value._selectedItemHeight
        if (valueHolderFor_selectedItemHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_selectedItemHeightTmpValue  = valueHolderFor_selectedItemHeight!
            if (valueHolderFor_selectedItemHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_selectedItemHeightTmpValueForIdx0  = valueHolderFor_selectedItemHeightTmpValue as string
                valueSerializer.writeString(valueHolderFor_selectedItemHeightTmpValueForIdx0)
            } else if (valueHolderFor_selectedItemHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_selectedItemHeightTmpValueForIdx1  = valueHolderFor_selectedItemHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_selectedItemHeightTmpValueForIdx1)
            } else if (valueHolderFor_selectedItemHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_selectedItemHeightTmpValueForIdx2  = valueHolderFor_selectedItemHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_selectedItemHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_mask  = value._mask
        if (valueHolderFor_mask !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_maskTmpValue  = valueHolderFor_mask!
            valueSerializer.writeBoolean(valueHolderFor_maskTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_color  = value._color
        if (valueHolderFor_color !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_colorTmpValue  = valueHolderFor_color!
            if (valueHolderFor_colorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_colorTmpValueForIdx0  = valueHolderFor_colorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderFor_colorTmpValueForIdx0))
            } else if (valueHolderFor_colorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_colorTmpValueForIdx1  = valueHolderFor_colorTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_colorTmpValueForIdx1)
            } else if (valueHolderFor_colorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_colorTmpValueForIdx2  = valueHolderFor_colorTmpValue as string
                valueSerializer.writeString(valueHolderFor_colorTmpValueForIdx2)
            } else if (valueHolderFor_colorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderFor_colorTmpValueForIdx3  = valueHolderFor_colorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_colorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_selectedColor  = value._selectedColor
        if (valueHolderFor_selectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_selectedColorTmpValue  = valueHolderFor_selectedColor!
            if (valueHolderFor_selectedColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_selectedColorTmpValueForIdx0  = valueHolderFor_selectedColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderFor_selectedColorTmpValueForIdx0))
            } else if (valueHolderFor_selectedColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_selectedColorTmpValueForIdx1  = valueHolderFor_selectedColorTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_selectedColorTmpValueForIdx1)
            } else if (valueHolderFor_selectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_selectedColorTmpValueForIdx2  = valueHolderFor_selectedColorTmpValue as string
                valueSerializer.writeString(valueHolderFor_selectedColorTmpValueForIdx2)
            } else if (valueHolderFor_selectedColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderFor_selectedColorTmpValueForIdx3  = valueHolderFor_selectedColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_selectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_maxDisplayCount  = value._maxDisplayCount
        if (valueHolderFor_maxDisplayCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_maxDisplayCountTmpValue  = valueHolderFor_maxDisplayCount!
            valueSerializer.writeNumber(valueHolderFor_maxDisplayCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_space  = value._space
        if (valueHolderFor_space !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_spaceTmpValue  = valueHolderFor_space!
            LengthMetrics_serializer.write(valueSerializer, valueHolderFor_spaceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DotIndicator {
        throw new Error("Can not deserialize builder class")
    }
}
export class DigitIndicator_serializer {
    public static write(buffer: SerializerBase, value: DigitIndicator): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderFor_left  = value._left
        if (valueHolderFor_left !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_leftTmpValue  = valueHolderFor_left!
            if (valueHolderFor_leftTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_leftTmpValueForIdx0  = valueHolderFor_leftTmpValue as string
                valueSerializer.writeString(valueHolderFor_leftTmpValueForIdx0)
            } else if (valueHolderFor_leftTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_leftTmpValueForIdx1  = valueHolderFor_leftTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_leftTmpValueForIdx1)
            } else if (valueHolderFor_leftTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_leftTmpValueForIdx2  = valueHolderFor_leftTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_leftTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_top  = value._top
        if (valueHolderFor_top !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_topTmpValue  = valueHolderFor_top!
            if (valueHolderFor_topTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_topTmpValueForIdx0  = valueHolderFor_topTmpValue as string
                valueSerializer.writeString(valueHolderFor_topTmpValueForIdx0)
            } else if (valueHolderFor_topTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_topTmpValueForIdx1  = valueHolderFor_topTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_topTmpValueForIdx1)
            } else if (valueHolderFor_topTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_topTmpValueForIdx2  = valueHolderFor_topTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_topTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_right  = value._right
        if (valueHolderFor_right !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_rightTmpValue  = valueHolderFor_right!
            if (valueHolderFor_rightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_rightTmpValueForIdx0  = valueHolderFor_rightTmpValue as string
                valueSerializer.writeString(valueHolderFor_rightTmpValueForIdx0)
            } else if (valueHolderFor_rightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_rightTmpValueForIdx1  = valueHolderFor_rightTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_rightTmpValueForIdx1)
            } else if (valueHolderFor_rightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_rightTmpValueForIdx2  = valueHolderFor_rightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_rightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_bottom  = value._bottom
        if (valueHolderFor_bottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_bottomTmpValue  = valueHolderFor_bottom!
            if (valueHolderFor_bottomTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_bottomTmpValueForIdx0  = valueHolderFor_bottomTmpValue as string
                valueSerializer.writeString(valueHolderFor_bottomTmpValueForIdx0)
            } else if (valueHolderFor_bottomTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_bottomTmpValueForIdx1  = valueHolderFor_bottomTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_bottomTmpValueForIdx1)
            } else if (valueHolderFor_bottomTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_bottomTmpValueForIdx2  = valueHolderFor_bottomTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_bottomTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_start  = value._start
        if (valueHolderFor_start !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_startTmpValue  = valueHolderFor_start!
            LengthMetrics_serializer.write(valueSerializer, valueHolderFor_startTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_end  = value._end
        if (valueHolderFor_end !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_endTmpValue  = valueHolderFor_end!
            LengthMetrics_serializer.write(valueSerializer, valueHolderFor_endTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_fontColor  = value._fontColor
        if (valueHolderFor_fontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_fontColorTmpValue  = valueHolderFor_fontColor!
            if (valueHolderFor_fontColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_fontColorTmpValueForIdx0  = valueHolderFor_fontColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderFor_fontColorTmpValueForIdx0))
            } else if (valueHolderFor_fontColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_fontColorTmpValueForIdx1  = valueHolderFor_fontColorTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_fontColorTmpValueForIdx1)
            } else if (valueHolderFor_fontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_fontColorTmpValueForIdx2  = valueHolderFor_fontColorTmpValue as string
                valueSerializer.writeString(valueHolderFor_fontColorTmpValueForIdx2)
            } else if (valueHolderFor_fontColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderFor_fontColorTmpValueForIdx3  = valueHolderFor_fontColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_fontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_selectedFontColor  = value._selectedFontColor
        if (valueHolderFor_selectedFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_selectedFontColorTmpValue  = valueHolderFor_selectedFontColor!
            if (valueHolderFor_selectedFontColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderFor_selectedFontColorTmpValueForIdx0  = valueHolderFor_selectedFontColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderFor_selectedFontColorTmpValueForIdx0))
            } else if (valueHolderFor_selectedFontColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderFor_selectedFontColorTmpValueForIdx1  = valueHolderFor_selectedFontColorTmpValue as number
                valueSerializer.writeNumber(valueHolderFor_selectedFontColorTmpValueForIdx1)
            } else if (valueHolderFor_selectedFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderFor_selectedFontColorTmpValueForIdx2  = valueHolderFor_selectedFontColorTmpValue as string
                valueSerializer.writeString(valueHolderFor_selectedFontColorTmpValueForIdx2)
            } else if (valueHolderFor_selectedFontColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderFor_selectedFontColorTmpValueForIdx3  = valueHolderFor_selectedFontColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_selectedFontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_digitFont  = value._digitFont
        if (valueHolderFor_digitFont !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_digitFontTmpValue  = valueHolderFor_digitFont!
            Font_serializer.write(valueSerializer, valueHolderFor_digitFontTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_selectedDigitFont  = value._selectedDigitFont
        if (valueHolderFor_selectedDigitFont !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_selectedDigitFontTmpValue  = valueHolderFor_selectedDigitFont!
            Font_serializer.write(valueSerializer, valueHolderFor_selectedDigitFontTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DigitIndicator {
        throw new Error("Can not deserialize builder class")
    }
}
