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

import { DeserializerBase, KPointer, RuntimeType, SerializerBase } from "@koalaui/interop"
import { ColorMetrics, ColorMetrics_serializer, LengthMetrics, LengthMetrics_serializer } from "arkui/Graphics"
import { ArkCommonMethodPeer, ArkCommonMethodComponent, ArkCommonMethodStyle, AttributeModifier, ChildrenMainSize, ChildrenMainSize_serializer, CommonMethod, OnScrollCallback, OnWillScrollCallback } from "arkui/component/common"
import { int32 } from "@koalaui/common"
import { ComponentBase } from "arkui/ComponentBase"
import { PeerNode } from "arkui/PeerNode"
import { ArkUIGeneratedNativeModule } from "#components"
import { CrownSensitivity, BarState } from "arkui/component/enums"
import { ArcListExtender, ArcListItemExtender } from "arkui/component/idlize"
import { VoidCallback } from "arkui/component/units"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { Scroller, Scroller_serializer } from "arkui/component/scroll"
import { ComponentContentBase } from "arkui/ComponentContent"
import { SwipeActionOptions, SwipeActionOptions_serializer } from "arkui/component/listItem"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkArcListPeer extends ArkCommonMethodPeer {
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkArcListPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArcListExtender.arcListConstructor(peerId)
        const _peer  = new ArkArcListPeer(_peerPtr, peerId, 'ArcList', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setArcListOptionsAttribute(options?: ArkListOptions): void {
        ArcListExtender.setArkListOptions(this.peer.ptr, options);
    }
    setDigitalCrownSensitivityAttribute(sensitivity: CrownSensitivity | undefined): void {
        ArcListExtender.digitalCrownSensitivity(this.peer.ptr, sensitivity);
    }
    setSpaceAttribute(space: LengthMetrics | undefined): void {
        ArcListExtender.space(this.peer.ptr, space);
    }
    setScrollBarAttribute(status: BarState | undefined): void {
        ArcListExtender.scrollBar(this.peer.ptr, status);
    }
    setScrollBarColorAttribute(color: ColorMetrics | undefined): void {
        ArcListExtender.scrollBarColor(this.peer.ptr, color);
    }
    setScrollBarWidthAttribute(width: LengthMetrics | undefined): void {
        ArcListExtender.scrollBarWidth(this.peer.ptr, width);
    }
    setCachedCountAttribute(count: int | undefined): void {
        ArcListExtender.cachedCount(this.peer.ptr, count);
    }
    setChainAnimationAttribute(enable: boolean | undefined): void {
        ArcListExtender.chainAnimation(this.peer.ptr, enable);
    }
    setChildrenMainSizeAttribute(size: ChildrenMainSize | undefined): void {
        ArcListExtender.childrenMainSize(this.peer.ptr, size);
    }
    setEnableScrollInteractionAttribute(enable: boolean | undefined): void {
        ArcListExtender.enableScrollInteraction(this.peer.ptr, enable);
    }
    setFadingEdgeAttribute(enable: boolean | undefined): void {
        ArcListExtender.fadingEdge(this.peer.ptr, enable);
    }
    setFrictionAttribute(friction: double | undefined): void {
        ArcListExtender.friction(this.peer.ptr, friction);
    }
    setFlingSpeedLimitAttribute(speed: double | undefined): void {
        ArcListExtender.flingSpeedLimit(this.peer.ptr, speed);
    }
    setOnScrollIndexAttribute(handler: ArcScrollIndexHandler | undefined): void {
        ArcListExtender.onScrollIndex(this.peer.ptr, handler);
    }
    setOnReachStartAttribute(handler: VoidCallback | undefined): void {
        ArcListExtender.onReachStart(this.peer.ptr, handler);
    }
    setOnReachEndAttribute(handler: VoidCallback | undefined): void {
        ArcListExtender.onReachEnd(this.peer.ptr, handler);
    }
    setOnScrollStartAttribute(handler: VoidCallback | undefined): void {
        ArcListExtender.onScrollStart(this.peer.ptr, handler);
    }
    setOnScrollStopAttribute(handler: VoidCallback | undefined): void {
        ArcListExtender.onScrollStop(this.peer.ptr, handler);
    }
    setOnWillScrollAttribute(handler: OnWillScrollCallback | undefined): void {
        ArcListExtender.onWillScroll(this.peer.ptr, handler);
    }
    setOnDidScrollAttribute(handler: OnScrollCallback | undefined): void {
        ArcListExtender.onDidScroll(this.peer.ptr, handler);
    }
}

export type ArcScrollIndexHandler = (start: int, end: int, center: int) => void;
export interface ArkListOptions {
    initialIndex?: int;
    scroller?: Scroller;
    header?: ComponentContentBase;
}
export type ArcListInterface = (options?: ArkListOptions) => ArcListAttribute;
export interface ArcListAttribute extends CommonMethod {
    setArcListOptions(options?: ArkListOptions): this {
        return this;
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this;
    }
    space(value: LengthMetrics | undefined): this {
        return this;
    }
    scrollBar(value: BarState | undefined): this {
        return this;
    }
    scrollBarColor(value: ColorMetrics | undefined): this {
        return this;
    }
    scrollBarWidth(value: LengthMetrics | undefined): this {
        return this;
    }
    cachedCount(value: int | undefined): this {
        return this;
    }
    chainAnimation(value: boolean | undefined): this {
        return this;
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        return this;
    }
    enableScrollInteraction(value: boolean | undefined): this {
        return this;
    }
    fadingEdge(value: boolean | undefined): this {
        return this;
    }
    friction(value: double | undefined): this {
        return this;
    }
    flingSpeedLimit(value: double | undefined): this {
        return this;
    }
    onScrollIndex(value: ArcScrollIndexHandler | undefined): this {
        return this;
    }
    onReachStart(value: VoidCallback | undefined): this {
        return this;
    }
    onReachEnd(value: VoidCallback | undefined): this {
        return this;
    }
    onScrollStart(value: VoidCallback | undefined): this {
        return this;
    }
    onScrollStop(value: VoidCallback | undefined): this {
        return this;
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        return this;
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        return this;
    }
    attributeModifier(value: AttributeModifier<ArcListAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this;
    }
}
export class ArkArcListStyle extends ArkCommonMethodStyle implements ArcListAttribute {
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    space_value?: LengthMetrics | undefined
    scrollBar_value?: BarState | undefined
    scrollBarColor_value?: ColorMetrics | undefined
    scrollBarWidth_value?: LengthMetrics | undefined
    cachedCount_value?: int | undefined
    chainAnimation_value?: boolean | undefined
    childrenMainSize_value?: ChildrenMainSize | undefined
    enableScrollInteraction_value?: boolean | undefined
    fadingEdge_value?: boolean | undefined
    friction_value?: double | undefined
    flingSpeedLimit_value?: double | undefined
    onScrollIndex_value?: ArcScrollIndexHandler | undefined
    onReachStart_value?: VoidCallback | undefined
    onReachEnd_value?: VoidCallback | undefined
    onScrollStart_value?: VoidCallback | undefined
    onScrollStop_value?: VoidCallback | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
    attributeModifier_value?: AttributeModifier<ArcListAttribute> | AttributeModifier<CommonMethod> | undefined
    setArcListOptions(options?: ArkListOptions): this {
        return this;
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    space(value: LengthMetrics | undefined): this {
        return this
    }
    scrollBar(value: BarState | undefined): this {
        return this
    }
    scrollBarColor(value: ColorMetrics | undefined): this {
        return this
    }
    scrollBarWidth(value: LengthMetrics | undefined): this {
        return this
    }
    cachedCount(value: int | undefined): this {
        return this
    }
    chainAnimation(value: boolean | undefined): this {
        return this
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        return this
    }
    fadingEdge(value: boolean | undefined): this {
        return this
    }
    friction(value: double | undefined): this {
        return this
    }
    flingSpeedLimit(value: double | undefined): this {
        return this
    }
    onScrollIndex(value: ArcScrollIndexHandler | undefined): this {
        return this
    }
    onReachStart(value: VoidCallback | undefined): this {
        return this
    }
    onReachEnd(value: VoidCallback | undefined): this {
        return this
    }
    onScrollStart(value: VoidCallback | undefined): this {
        return this
    }
    onScrollStop(value: VoidCallback | undefined): this {
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ArcListAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkArcListComponent extends ArkCommonMethodComponent implements ArcListAttribute {
    getPeer(): ArkArcListPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkArcListPeer)
    }
    public setArcListOptions(options?: ArkListOptions): this {
        if (this.checkPriority("setArcListOptions")) {
            const options_casted = options as (ArkListOptions | undefined)
            this.getPeer()?.setArcListOptionsAttribute(options_casted)
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
    public space(value: LengthMetrics | undefined): this {
        if (this.checkPriority("space")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.setScrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarColor(value: ColorMetrics | undefined): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.setScrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarWidth(value: LengthMetrics | undefined): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setScrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(value: int | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const value_casted = value as (int | undefined)
            this.getPeer()?.setCachedCountAttribute(value_casted)
            return this
        }
        return this
    }
    public chainAnimation(value: boolean | undefined): this {
        if (this.checkPriority("chainAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setChainAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (this.checkPriority("childrenMainSize")) {
            const value_casted = value as (ChildrenMainSize | undefined)
            this.getPeer()?.setChildrenMainSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    public fadingEdge(value: boolean | undefined): this {
        if (this.checkPriority("fadingEdge")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setFadingEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    public friction(value: double | undefined): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setFrictionAttribute(value_casted)
            return this
        }
        return this
    }
    public flingSpeedLimit(value: double | undefined): this {
        if (this.checkPriority("flingSpeedLimit")) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setFlingSpeedLimitAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollIndex(value: ArcScrollIndexHandler | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (ArcScrollIndexHandler | undefined)
            this.getPeer()?.setOnScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public onReachStart(value: VoidCallback | undefined): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onReachEnd(value: VoidCallback | undefined): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStart(value: VoidCallback | undefined): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: VoidCallback | undefined): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (OnWillScrollCallback | undefined)
            this.getPeer()?.setOnWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (OnScrollCallback | undefined)
            this.getPeer()?.setOnDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ArcListAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function ArcListImpl(
    @memo
    style: ((attributes: ArcListAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkArcListComponent>((): ArkArcListComponent => {
        return new ArkArcListComponent()
    })
    NodeAttach<ArkArcListPeer>((): ArkArcListPeer => ArkArcListPeer.create(receiver), (peer: ArkArcListPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class ArkArcListItemPeer extends ArkCommonMethodPeer {
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkArcListItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArcListItemExtender.arcListItemConstructor(peerId)
        const _peer  = new ArkArcListItemPeer(_peerPtr, peerId, 'ArcListItem', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setAutoScaleAttribute(enable: boolean | undefined): void {
        ArcListItemExtender.autoScale(this.peer.ptr, enable)
    }
    setSwipeActionAttribute(options: SwipeActionOptions | undefined): void {
        ArcListItemExtender.swipeAction(this.peer.ptr, options)
    }
}

export type ArcListItemInterface = () => ArcListItemAttribute;
export interface ArcListItemAttribute extends CommonMethod {
    setArcListItemOptions(): this {
        return this;
    }
    autoScale(value: boolean | undefined): this {
        return this;
    }
    swipeAction(value: SwipeActionOptions | undefined): this {
        return this;
    }
    attributeModifier(value: AttributeModifier<ArcListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkArcListItemStyle extends ArkCommonMethodStyle implements ArcListItemAttribute {
    autoScale_value?: boolean | undefined
    swipeAction_value?: SwipeActionOptions | undefined
    attributeModifier_value?: AttributeModifier<ArcListItemAttribute> | AttributeModifier<CommonMethod> | undefined
    autoScale(value: boolean | undefined): this {
        return this;
    }
    swipeAction(value: SwipeActionOptions | undefined): this {
        return this;
    }
    public attributeModifier(value: AttributeModifier<ArcListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkArcListItemComponent extends ArkCommonMethodComponent implements ArcListItemAttribute {
    getPeer(): ArkArcListItemPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkArcListItemPeer)
    }
    public autoScale(value: boolean | undefined): this {
        if (this.checkPriority("autoScale")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public swipeAction(value: SwipeActionOptions | undefined): this {
        if (this.checkPriority("swipeAction")) {
            const value_casted = value as (SwipeActionOptions | undefined)
            this.getPeer()?.setSwipeActionAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ArcListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function ArcListItemImpl(
    @memo
    style: ((attributes: ArcListItemAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkArcListItemComponent>((): ArkArcListItemComponent => {
        return new ArkArcListItemComponent()
    })
    NodeAttach<ArkArcListItemPeer>((): ArkArcListItemPeer => ArkArcListItemPeer.create(receiver), (peer: ArkArcListItemPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}
