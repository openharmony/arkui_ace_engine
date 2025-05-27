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

import { VoidCallback, Length, ResourceColor, VP, Font } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ICurve, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { IndicatorComponentController } from "./indicatorcomponent"
import { EdgeEffect, Curve, Color } from "./enums"
import { Callback_Number_Void } from "./alphabet_indexer"
import { IndicatorStyle } from "./arkui-external"
import { Resource } from "./resource"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics } from "./arkui-graphics"
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
    public finishAnimation(callback_?: VoidCallback): void {
        const callback__casted = callback_ as (VoidCallback | undefined)
        this.finishAnimation_serialize(callback__casted)
        return
    }
    private showNext_serialize(): void {
        ArkUIGeneratedNativeModule._SwiperController_showNext(this.peer!.ptr)
    }
    private showPrevious_serialize(): void {
        ArkUIGeneratedNativeModule._SwiperController_showPrevious(this.peer!.ptr)
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
        ArkUIGeneratedNativeModule._SwiperController_changeIndex(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private finishAnimation_serialize(callback_?: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._SwiperController_finishAnimation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSwiperPeer {
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
    indexAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_index(this.peer.ptr, value)
    }
    autoPlayAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_autoPlay(this.peer.ptr, value ? 1 : 0)
    }
    intervalAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_interval(this.peer.ptr, value)
    }
    indicator0Attribute(value: DotIndicator | DigitIndicator | boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isDotIndicator(value))) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as DotIndicator
            thisSerializer.writeDotIndicator(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isDigitIndicator(value))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as DigitIndicator
            thisSerializer.writeDigitIndicator(value_1)
        }
        else if (RuntimeType.BOOLEAN == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as boolean
            thisSerializer.writeBoolean(value_2)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicator0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicator1Attribute(value: IndicatorComponentController): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_indicator1(this.peer.ptr, toPeerPtr(value))
    }
    loopAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_loop(this.peer.ptr, value ? 1 : 0)
    }
    durationAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_duration(this.peer.ptr, value)
    }
    verticalAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_vertical(this.peer.ptr, value ? 1 : 0)
    }
    itemSpaceAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_itemSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    displayModeAttribute(value: SwiperDisplayMode): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_displayMode(this.peer.ptr, TypeChecker.SwiperDisplayMode_ToNumeric(value))
    }
    cachedCountAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_cachedCount(this.peer.ptr, value)
    }
    effectModeAttribute(value: EdgeEffect): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_effectMode(this.peer.ptr, TypeChecker.EdgeEffect_ToNumeric(value))
    }
    disableSwipeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_disableSwipe(this.peer.ptr, value ? 1 : 0)
    }
    curveAttribute(value: Curve | string | ICurve): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isCurve(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Curve
            thisSerializer.writeInt32(TypeChecker.Curve_ToNumeric(value_0))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as ICurve
            thisSerializer.writeICurve(value_2)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_curve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    onAnimationStartAttribute(value: OnSwiperAnimationStartCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationEndAttribute(value: OnSwiperAnimationEndCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureSwipeAttribute(value: OnSwiperGestureSwipeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: SwiperNestedScrollMode): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_nestedScroll(this.peer.ptr, TypeChecker.SwiperNestedScrollMode_ToNumeric(value))
    }
    customContentTransitionAttribute(value: SwiperContentAnimatedTransition): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSwiperContentAnimatedTransition(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_customContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentDidScrollAttribute(value: ContentDidScrollCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onContentDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorInteractiveAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_indicatorInteractive(this.peer.ptr, value ? 1 : 0)
    }
    displayArrowAttribute(value: ArrowStyle | boolean, isHoverShow?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ArrowStyle
            thisSerializer.writeArrowStyle(value_0)
        }
        else if (RuntimeType.BOOLEAN == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as boolean
            thisSerializer.writeBoolean(value_1)
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
    displayCountAttribute(value: number | string | SwiperAutoFill, swipeByGroup?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as SwiperAutoFill
            thisSerializer.writeSwiperAutoFill(value_2)
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
    prevMarginAttribute(value: Length, ignoreBlank?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
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
    nextMarginAttribute(value: Length, ignoreBlank?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
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
    _onChangeEvent_indexAttribute(callback: ((index: number) => void)): void {
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

export interface SwiperAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
export enum SwiperNestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1
}
export type OnSwiperAnimationStartCallback = (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void;
export type OnSwiperAnimationEndCallback = (index: number, extraInfo: SwiperAnimationEvent) => void;
export type OnSwiperGestureSwipeCallback = (index: number, extraInfo: SwiperAnimationEvent) => void;
export interface SwiperAttribute extends CommonMethod {
    index(value: number): this
    autoPlay(value: boolean): this
    interval(value: number): this
    indicator(value: DotIndicator | DigitIndicator | boolean | IndicatorComponentController): this
    loop(value: boolean): this
    duration(value: number): this
    vertical(value: boolean): this
    itemSpace(value: number | string): this
    displayMode(value: SwiperDisplayMode): this
    cachedCount(value: number): this
    effectMode(value: EdgeEffect): this
    disableSwipe(value: boolean): this
    curve(value: Curve | string | ICurve): this
    onChange(value: ((index: number) => void)): this
    indicatorStyle(value: IndicatorStyle | undefined): this
    onAnimationStart(value: OnSwiperAnimationStartCallback): this
    onAnimationEnd(value: OnSwiperAnimationEndCallback): this
    onGestureSwipe(value: OnSwiperGestureSwipeCallback): this
    nestedScroll(value: SwiperNestedScrollMode): this
    customContentTransition(value: SwiperContentAnimatedTransition): this
    onContentDidScroll(value: ContentDidScrollCallback): this
    indicatorInteractive(value: boolean): this
    displayArrow(value: ArrowStyle | boolean, isHoverShow?: boolean): this
    displayCount(value: number | string | SwiperAutoFill, swipeByGroup?: boolean): this
    prevMargin(value: Length, ignoreBlank?: boolean): this
    nextMargin(value: Length, ignoreBlank?: boolean): this
    _onChangeEvent_index(callback: ((index: number) => void)): void
    attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UISwiperAttribute extends UICommonMethod {
    /** @memo */
    index(value: number): this
    /** @memo */
    autoPlay(value: boolean): this
    /** @memo */
    interval(value: number): this
    /** @memo */
    indicator(value: DotIndicator | DigitIndicator | boolean | IndicatorComponentController): this
    /** @memo */
    loop(value: boolean): this
    /** @memo */
    duration(value: number): this
    /** @memo */
    vertical(value: boolean): this
    /** @memo */
    itemSpace(value: number | string): this
    /** @memo */
    displayMode(value: SwiperDisplayMode): this
    /** @memo */
    cachedCount(value: number): this
    /** @memo */
    effectMode(value: EdgeEffect): this
    /** @memo */
    disableSwipe(value: boolean): this
    /** @memo */
    curve(value: Curve | string | ICurve): this
    /** @memo */
    onChange(value: ((index: number) => void)): this
    /** @memo */
    indicatorStyle(value: IndicatorStyle | undefined): this
    /** @memo */
    onAnimationStart(value: OnSwiperAnimationStartCallback): this
    /** @memo */
    onAnimationEnd(value: OnSwiperAnimationEndCallback): this
    /** @memo */
    onGestureSwipe(value: OnSwiperGestureSwipeCallback): this
    /** @memo */
    nestedScroll(value: SwiperNestedScrollMode): this
    /** @memo */
    customContentTransition(value: SwiperContentAnimatedTransition): this
    /** @memo */
    onContentDidScroll(value: ContentDidScrollCallback): this
    /** @memo */
    indicatorInteractive(value: boolean): this
    /** @memo */
    displayArrow(value: ArrowStyle | boolean, isHoverShow?: boolean): this
    /** @memo */
    displayCount(value: number | string | SwiperAutoFill, swipeByGroup?: boolean): this
    /** @memo */
    prevMargin(value: Length, ignoreBlank?: boolean): this
    /** @memo */
    nextMargin(value: Length, ignoreBlank?: boolean): this
    /** @memo */
    _onChangeEvent_index(callback: ((index: number) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSwiperStyle extends ArkCommonMethodStyle implements SwiperAttribute {
    index_value?: number
    autoPlay_value?: boolean
    interval_value?: number
    indicator_value?: DotIndicator | DigitIndicator | boolean
    loop_value?: boolean
    duration_value?: number
    vertical_value?: boolean
    itemSpace_value?: number | string
    displayMode_value?: SwiperDisplayMode
    cachedCount_value?: number
    effectMode_value?: EdgeEffect
    disableSwipe_value?: boolean
    curve_value?: Curve | string | ICurve
    onChange_value?: ((index: number) => void)
    indicatorStyle_value?: IndicatorStyle
    onAnimationStart_value?: OnSwiperAnimationStartCallback
    onAnimationEnd_value?: OnSwiperAnimationEndCallback
    onGestureSwipe_value?: OnSwiperGestureSwipeCallback
    nestedScroll_value?: SwiperNestedScrollMode
    customContentTransition_value?: SwiperContentAnimatedTransition
    onContentDidScroll_value?: ContentDidScrollCallback
    indicatorInteractive_value?: boolean
    public index(value: number): this {
        return this
    }
    public autoPlay(value: boolean): this {
        return this
    }
    public interval(value: number): this {
        return this
    }
    public indicator(value: DotIndicator | DigitIndicator | boolean | IndicatorComponentController): this {
        return this
    }
    public loop(value: boolean): this {
        return this
    }
    public duration(value: number): this {
        return this
    }
    public vertical(value: boolean): this {
        return this
    }
    public itemSpace(value: number | string): this {
        return this
    }
    public displayMode(value: SwiperDisplayMode): this {
        return this
    }
    public cachedCount(value: number): this {
        return this
    }
    public effectMode(value: EdgeEffect): this {
        return this
    }
    public disableSwipe(value: boolean): this {
        return this
    }
    public curve(value: Curve | string | ICurve): this {
        return this
    }
    public onChange(value: ((index: number) => void)): this {
        return this
    }
    public indicatorStyle(value: IndicatorStyle | undefined): this {
        return this
    }
    public onAnimationStart(value: OnSwiperAnimationStartCallback): this {
        return this
    }
    public onAnimationEnd(value: OnSwiperAnimationEndCallback): this {
        return this
    }
    public onGestureSwipe(value: OnSwiperGestureSwipeCallback): this {
        return this
    }
    public nestedScroll(value: SwiperNestedScrollMode): this {
        return this
    }
    public customContentTransition(value: SwiperContentAnimatedTransition): this {
        return this
    }
    public onContentDidScroll(value: ContentDidScrollCallback): this {
        return this
    }
    public indicatorInteractive(value: boolean): this {
        return this
    }
    public displayArrow(value: ArrowStyle | boolean, isHoverShow?: boolean): this {
        return this
    }
    public displayCount(value: number | string | SwiperAutoFill, swipeByGroup?: boolean): this {
        return this
    }
    public prevMargin(value: Length, ignoreBlank?: boolean): this {
        return this
    }
    public nextMargin(value: Length, ignoreBlank?: boolean): this {
        return this
    }
    public _onChangeEvent_index(callback: ((index: number) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export type Callback_SwiperContentTransitionProxy_Void = (parameter: SwiperContentTransitionProxy) => void;
export interface SwiperContentAnimatedTransition {
    timeout?: number;
    transition: ((parameter: SwiperContentTransitionProxy) => void);
}
export type ContentDidScrollCallback = (selectedIndex: number, index: number, position: number, mainAxisLength: number) => void;
/** @memo:stable */
export class ArkSwiperComponent extends ArkCommonMethodComponent implements UISwiperAttribute {
    getPeer(): ArkSwiperPeer {
        return (this.peer as ArkSwiperPeer)
    }
    /** @memo */
    public setSwiperOptions(controller?: SwiperController): this {
        if (this.checkPriority("setSwiperOptions")) {
            const controller_casted = controller as (SwiperController | undefined)
            this.getPeer()?.setSwiperOptionsAttribute(controller_casted)
            return this
        }
        return this
    }
    /** @memo */
    public index(value: number): this {
        if (this.checkPriority("index")) {
            const value_casted = value as (number)
            this.getPeer()?.indexAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoPlay(value: boolean): this {
        if (this.checkPriority("autoPlay")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoPlayAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public interval(value: number): this {
        if (this.checkPriority("interval")) {
            const value_casted = value as (number)
            this.getPeer()?.intervalAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean): this {
        if (this.checkPriority("indicator")) {
            const value_type = runtimeType(value)
            if (TypeChecker.isIndicatorComponentController(value)) {
                const value_casted = value as (IndicatorComponentController)
                this.getPeer()?.indicator1Attribute(value_casted)
                return this
            }
            if ((((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isDotIndicator(value))) || (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isDigitIndicator(value))) || (RuntimeType.BOOLEAN == value_type)) {
                const value_casted = value as (DotIndicator | DigitIndicator | boolean)
                this.getPeer()?.indicator0Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public loop(value: boolean): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean)
            this.getPeer()?.loopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public duration(value: number): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (number)
            this.getPeer()?.durationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public vertical(value: boolean): this {
        if (this.checkPriority("vertical")) {
            const value_casted = value as (boolean)
            this.getPeer()?.verticalAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public itemSpace(value: number | string): this {
        if (this.checkPriority("itemSpace")) {
            const value_casted = value as (number | string)
            this.getPeer()?.itemSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public displayMode(value: SwiperDisplayMode): this {
        if (this.checkPriority("displayMode")) {
            const value_casted = value as (SwiperDisplayMode)
            this.getPeer()?.displayModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public cachedCount(value: number): this {
        if (this.checkPriority("cachedCount")) {
            const value_casted = value as (number)
            this.getPeer()?.cachedCountAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public effectMode(value: EdgeEffect): this {
        if (this.checkPriority("effectMode")) {
            const value_casted = value as (EdgeEffect)
            this.getPeer()?.effectModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public disableSwipe(value: boolean): this {
        if (this.checkPriority("disableSwipe")) {
            const value_casted = value as (boolean)
            this.getPeer()?.disableSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public curve(value: Curve | string | ICurve): this {
        if (this.checkPriority("curve")) {
            const value_casted = value as (Curve | string | ICurve)
            this.getPeer()?.curveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((index: number) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public indicatorStyle(value: IndicatorStyle | undefined): this {
        if (this.checkPriority("indicatorStyle")) {
            const value_casted = value as (IndicatorStyle | undefined)
            this.getPeer()?.indicatorStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAnimationStart(value: OnSwiperAnimationStartCallback): this {
        if (this.checkPriority("onAnimationStart")) {
            const value_casted = value as (OnSwiperAnimationStartCallback)
            this.getPeer()?.onAnimationStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAnimationEnd(value: OnSwiperAnimationEndCallback): this {
        if (this.checkPriority("onAnimationEnd")) {
            const value_casted = value as (OnSwiperAnimationEndCallback)
            this.getPeer()?.onAnimationEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onGestureSwipe(value: OnSwiperGestureSwipeCallback): this {
        if (this.checkPriority("onGestureSwipe")) {
            const value_casted = value as (OnSwiperGestureSwipeCallback)
            this.getPeer()?.onGestureSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nestedScroll(value: SwiperNestedScrollMode): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (SwiperNestedScrollMode)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customContentTransition(value: SwiperContentAnimatedTransition): this {
        if (this.checkPriority("customContentTransition")) {
            const value_casted = value as (SwiperContentAnimatedTransition)
            this.getPeer()?.customContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onContentDidScroll(value: ContentDidScrollCallback): this {
        if (this.checkPriority("onContentDidScroll")) {
            const value_casted = value as (ContentDidScrollCallback)
            this.getPeer()?.onContentDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public indicatorInteractive(value: boolean): this {
        if (this.checkPriority("indicatorInteractive")) {
            const value_casted = value as (boolean)
            this.getPeer()?.indicatorInteractiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public displayArrow(value: ArrowStyle | boolean, isHoverShow?: boolean): this {
        if (this.checkPriority("displayArrow")) {
            const value_casted = value as (ArrowStyle | boolean)
            const isHoverShow_casted = isHoverShow as (boolean | undefined)
            this.getPeer()?.displayArrowAttribute(value_casted, isHoverShow_casted)
            return this
        }
        return this
    }
    /** @memo */
    public displayCount(value: number | string | SwiperAutoFill, swipeByGroup?: boolean): this {
        if (this.checkPriority("displayCount")) {
            const value_casted = value as (number | string | SwiperAutoFill)
            const swipeByGroup_casted = swipeByGroup as (boolean | undefined)
            this.getPeer()?.displayCountAttribute(value_casted, swipeByGroup_casted)
            return this
        }
        return this
    }
    /** @memo */
    public prevMargin(value: Length, ignoreBlank?: boolean): this {
        if (this.checkPriority("prevMargin")) {
            const value_casted = value as (Length)
            const ignoreBlank_casted = ignoreBlank as (boolean | undefined)
            this.getPeer()?.prevMarginAttribute(value_casted, ignoreBlank_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nextMargin(value: Length, ignoreBlank?: boolean): this {
        if (this.checkPriority("nextMargin")) {
            const value_casted = value as (Length)
            const ignoreBlank_casted = ignoreBlank as (boolean | undefined)
            this.getPeer()?.nextMarginAttribute(value_casted, ignoreBlank_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_index(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_index")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_indexAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkSwiper(
    /** @memo */
    style: ((attributes: UISwiperAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    controller?: SwiperController,
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
