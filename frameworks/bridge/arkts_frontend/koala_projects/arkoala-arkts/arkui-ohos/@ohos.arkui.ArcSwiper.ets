/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { VoidCallback, Length, ResourceColor, Font } from '/arkui/component/units';
import { SwiperAnimationEvent, SwiperContentAnimatedTransition, SwiperContentTransitionProxy, OnSwiperAnimationStartCallback, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback } from 'arkui/component/swiper'
import { CrownSensitivity, EdgeEffect } from 'arkui/component/enums'
import { LinearGradient } from 'arkui/component/dataPanel'
import { CommonMethod, Callback, ArkCommonMethodPeer, ArkCommonMethodComponent, ArkCommonMethodStyle } from 'arkui/component/common'
import { Finalizable, runtimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, InteropNativeModule} from '@koalaui/interop'
import { TypeChecker, ArkUIGeneratedNativeModule } from '#components'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ComponentBase } from "arkui/ComponentBase"
import { PeerNode } from "arkui/PeerNode"
import { ArcSwiperExtender, ArcSwiperControllerHelper, ArcDirectionInner, ArcDotIndicatorInner } from 'arkui/component/idlize';
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArcSwiperController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ArcSwiperController.getFinalizer())
    }
    constructor() {
        this(ArcSwiperController.construct())
    }
    static construct(): KPointer {
        const retval  = ArcSwiperControllerHelper.construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArcSwiperControllerHelper.getFinalizer()
    }
    public showNext(): void {
        ArcSwiperControllerHelper.showNext(this.peer!.ptr)
        return
    }
    public showPrevious(): void {
        ArcSwiperControllerHelper.showPrevious(this.peer!.ptr)
        return
    }
    public finishAnimation(callback_?: VoidCallback): void {
        const callback__casted = callback_ as (VoidCallback | undefined)
        ArcSwiperControllerHelper.finishAnimation(this.peer!.ptr, callback__casted)
        return
    }
}

class ArcSwiperControllerInnerHelper {
    static ConvertArcSwiperController(input: ArcSwiperController | undefined): ArcSwiperControllerHelper | undefined {
        if (input === undefined) {
            return input;
        }
        let peerInner = input.getPeer();
        return { peer: peerInner };
    }
}

export enum ArcDirection {
    THREE_CLOCK_DIRECTION = 0,
    SIX_CLOCK_DIRECTION = 1,
    NINE_CLOCK_DIRECTION = 2
}

export class ArcDotIndicator {
    _arcDirection?: ArcDirection;
    _itemColor?: ResourceColor;
    _selectedItemColor?: ResourceColor;
    _backgroundColor?: ResourceColor;
    _maskColor?: LinearGradient;
    constructor() {
    }
    arcDirection(value: ArcDirection): this {
        this._arcDirection = value
        return this
    }
    itemColor(value: ResourceColor): this {
        this._itemColor = value
        return this
    }
    selectedItemColor(value: ResourceColor): this {
        this._selectedItemColor = value
        return this
    }
    backgroundColor(value: ResourceColor): this {
        this._backgroundColor = value
        return this
    }
    maskColor(value: LinearGradient): this {
        this._maskColor = value
        return this
    }
}

export class ArcDotIndicatorInnerHelper {
    static ConvertArcDotIndicator(input: ArcDotIndicator | boolean | undefined): ArcDotIndicatorInner | boolean | undefined {
        if (input instanceof ArcDotIndicator) {
            return { 
                _arcDirection: ArcDotIndicatorInnerHelper.ConvertArcDirection(input._arcDirection),
                _itemColor: input!._itemColor,
                _selectedItemColor: input!._selectedItemColor,
                _backgroundColor: input!._backgroundColor,
                _maskColor: input!._maskColor,
            };
        }
        return input;
    }
    static ConvertArcDirection(input: ArcDirection | undefined): ArcDirectionInner | undefined {
        if (input === undefined) {
            return input;
        }
        switch (input) {
            case ArcDirection.THREE_CLOCK_DIRECTION:
                return ArcDirectionInner.THREE_CLOCK_DIRECTION;
            case ArcDirection.SIX_CLOCK_DIRECTION:
                return ArcDirectionInner.SIX_CLOCK_DIRECTION;
            case ArcDirection.NINE_CLOCK_DIRECTION:
                return ArcDirectionInner.NINE_CLOCK_DIRECTION;
            default:
                return ArcDirectionInner.SIX_CLOCK_DIRECTION;
        }
        
    }
}

export type IndexChangedHandler = (index: int32) => void;
export type AnimationStartHandler = (index: int32, targetIndex: int32, event: SwiperAnimationEvent) => void;
export type AnimationEndHandler = (index: int32, event: SwiperAnimationEvent) => void;
export type GestureSwipeHandler = (index: int32, event: SwiperAnimationEvent) => void;
export type ArcSwiperContentAnimatedTransition = SwiperContentAnimatedTransition;
export type ArcSwiperContentTransitionProxy = SwiperContentTransitionProxy;

export interface ArcSwiperAttribute extends CommonMethod {
    setArcSwiperOptions(controller?: ArcSwiperController): this {
        throw new Error("Unimplemented method setArcSwiperOptions")
    }
    index(value: int32 | undefined): this {
        throw new Error("Unimplemented method index")
    }
    indicator(value: ArcDotIndicator | boolean | undefined): this {
        throw new Error("Unimplemented method indicator")
    }
    duration(value: int32 | undefined): this {
        throw new Error("Unimplemented method duration")
    }
    vertical(value: boolean | undefined): this {
        throw new Error("Unimplemented method vertical")
    }
    disableSwipe(value: boolean | undefined): this {
        throw new Error("Unimplemented method disableSwipe")
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error("Unimplemented method digitalCrownSensitivity")
    }
    onChange(value: IndexChangedHandler | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onAnimationStart(value: AnimationStartHandler | undefined): this {
        throw new Error("Unimplemented method onAnimationStart")
    }
    onAnimationEnd(value: AnimationEndHandler | undefined): this {
        throw new Error("Unimplemented method onAnimationEnd")
    }
    onGestureSwipe(value: GestureSwipeHandler | undefined): this {
        throw new Error("Unimplemented method onGestureSwipe")
    }
    effectMode(value: EdgeEffect | undefined): this {
        throw new Error("Unimplemented method effectMode")
    }
    customContentTransition(value: ArcSwiperContentAnimatedTransition | undefined): this {
        throw new Error("Unimplemented method customContentTransition")
    }
    disableTransitionAnimation(value: boolean | undefined): this {
        throw new Error("Unimplemented method disableTransitionAnimation")
    }
}

export class ArkArcSwiperPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkArcSwiperPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArcSwiperExtender.arcSwiperConstruct(peerId, flags)
        const _peer  = new ArkArcSwiperPeer(_peerPtr, peerId, 'ArcSwiper', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setArcSwiperOptionsAttribute(controller?: ArcSwiperController): void {
        const controller_casted = ArcSwiperControllerInnerHelper.ConvertArcSwiperController(controller);
        ArcSwiperExtender.setConstructInfo(this.peer.ptr, controller_casted)
    }
    setIndexAttribute(value: int32| undefined): void {
        ArcSwiperExtender.index(this.peer.ptr, value)
    }
    setIndicatorAttribute(value: ArcDotIndicator | boolean | undefined): void {
        const valueInner = ArcDotIndicatorInnerHelper.ConvertArcDotIndicator(value);
        ArcSwiperExtender.indicator(this.peer.ptr, valueInner)
    }
    setDurationAttribute(value: int32 | undefined): void {
        ArcSwiperExtender.duration(this.peer.ptr, value)
    }
    setVerticalAttribute(value: boolean | undefined): void {
        ArcSwiperExtender.vertical(this.peer.ptr, value)
    }
    setDisableSwipeAttribute(value: boolean | undefined): void {
        ArcSwiperExtender.disableSwipe(this.peer.ptr, value)
    }
    setDigitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        ArcSwiperExtender.digitalCrownSensitivity(this.peer.ptr, value)
    }
    setOnChangeAttribute(value: IndexChangedHandler | undefined): void {
        ArcSwiperExtender.onChange(this.peer.ptr, value)
    }
    setOnAnimationStartAttribute(value: AnimationStartHandler | undefined): void {
        ArcSwiperExtender.onAnimationStart(this.peer.ptr, value)
    }
    setOnAnimationEndAttribute(value: AnimationEndHandler | undefined): void {
        ArcSwiperExtender.onAnimationEnd(this.peer.ptr, value)
    }
    setOnGestureSwipeAttribute(value: GestureSwipeHandler | undefined): void {
        ArcSwiperExtender.onGestureSwipe(this.peer.ptr, value)
    }
    setEffectModeAttribute(value: EdgeEffect | undefined): void {
        ArcSwiperExtender.effectMode(this.peer.ptr, value)
    }
    setCustomContentTransitionAttribute(value: SwiperContentAnimatedTransition | undefined): void {
        ArcSwiperExtender.customContentTransition(this.peer.ptr, value)
    }
    setDisableTransitionAnimationAttribute(value: boolean | undefined): void {
        ArcSwiperExtender.disableTransitionAnimation(this.peer.ptr, value)
    }
}

export class ArkArcSwiperComponent extends ArkCommonMethodComponent implements ArcSwiperAttribute {
    getPeer(): ArkArcSwiperPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkArcSwiperPeer)
    }
    public setArcSwiperOptions(controller?: ArcSwiperController): this {
        if (this.checkPriority("setArcSwiperOptions")) {
            const controller_casted = controller as (ArcSwiperController | undefined)
            this.getPeer()?.setArcSwiperOptionsAttribute(controller_casted)
            this.applyOptionsFinish('SwiperAttribute');
            return this
        }
        return this
    }
    public index(value: int32 | undefined): this {
        if (this.checkPriority("index")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public indicator(value: ArcDotIndicator | boolean | undefined): this {
        if (this.checkPriority("indicator")) {
            const value_casted = value as (ArcDotIndicator | boolean | undefined)
            this.getPeer()?.setIndicatorAttribute(value_casted)
            return this
        }
        return this
    }
    public duration(value: int32 | undefined): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (int32 | undefined)
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
    public disableSwipe(value: boolean | undefined): this {
        if (this.checkPriority("disableSwipe")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDisableSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority("digitalCrownSensitivity")) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: IndexChangedHandler | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (IndexChangedHandler | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationStart(value: AnimationStartHandler | undefined): this {
        if (this.checkPriority("onAnimationStart")) {
            const value_casted = value as (AnimationStartHandler | undefined)
            this.getPeer()?.setOnAnimationStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationEnd(value: AnimationEndHandler | undefined): this {
        if (this.checkPriority("onAnimationEnd")) {
            const value_casted = value as (AnimationEndHandler | undefined)
            this.getPeer()?.setOnAnimationEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onGestureSwipe(value: GestureSwipeHandler | undefined): this {
        if (this.checkPriority("onGestureSwipe")) {
            const value_casted = value as (GestureSwipeHandler | undefined)
            this.getPeer()?.setOnGestureSwipeAttribute(value_casted)
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
    public customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        if (this.checkPriority("customContentTransition")) {
            const value_casted = value as (SwiperContentAnimatedTransition | undefined)
            this.getPeer()?.setCustomContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public disableTransitionAnimation(value: boolean | undefined): this {
        if (this.checkPriority("disableTransitionAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDisableTransitionAnimationAttribute(value_casted)
            return this
        }
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
export function ArcSwiperImpl(
    @memo
    style: ((attributes: ArcSwiperAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkArcSwiperComponent>((): ArkArcSwiperComponent => {
        return new ArkArcSwiperComponent()
    })
    NodeAttach<ArkArcSwiperPeer>((): ArkArcSwiperPeer => ArkArcSwiperPeer.create(receiver), (peer: ArkArcSwiperPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export type ArcSwiperInterface = (controller?: ArcSwiperController) => ArcSwiperAttribute;
