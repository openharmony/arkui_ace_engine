/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import {
    setEventDeliverer, PeerNode, PeerEvent, Properties, SinglePointerPeerEvent, SwiperChangePeerEvent, TabsChangePeerEvent,
    AppearPeerEvent, DisappearPeerEvent, VisibleAreaChangePeerEvent, ScrollIndexPeerEvent, NavigatorClickPeerEvent, TextInputEvent,
    GesturePeerEvent, ListScrollPeerEvent, ListScrollIndexPeerEvent, ListScrollStartPeerEvent, ListScrollStopPeerEvent,
    SwiperAnimationPeerEvent, SliderChangePeerEvent, AreaChangePeerEvent, BlurPeerEvent, HoverPeerEvent, MousePeerEvent, KeyPeerEvent,
    ImageCompletePeerEvent, ImageErrorPeerEvent, RefreshStateChangePeerEvent, OnRefreshingPeerEvent, OnRadioChangePeerEvent,
    GridScrollPeerEvent, GridScrollStartPeerEvent, GridScrollStopPeerEvent, SideBarChangePeerEvent, XComponentLoadPeerEvent,
    XComponentDestroyPeerEvent,
    CanvasReadyPeerEvent,
    NavBarStateChangePeerEvent,
    NavDestinationPeerEvent
} from "@koalaui/arkoala"

interface EventListenerOptions {
    capture?: boolean;
}
interface AddEventListenerOptions extends EventListenerOptions {
    once?: boolean;
    passive?: boolean;
}

export interface BaseEventTarget {
    area: Area;
}

export interface BaseEvent {
    target: BaseEventTarget;
    timestamp: number;
    source: SourceType;
    pressure: number;
    tiltX: number;
    tiltY: number;
    sourceTool: SourceTool;
}

export interface EventListener {
    (evt: BaseEvent): void;
}

export interface EventListenerObject {
    handleEvent(object: BaseEvent): void;
}

type EventListenerOrEventListenerObject = EventListener | EventListenerObject

export class EventTargetImpl implements BaseEventTarget {
    addEventListener(type: string, listener: EventListenerOrEventListenerObject, options?: boolean | AddEventListenerOptions | undefined): void {
        throw new Error("Method not implemented.")
    }
    dispatchEvent(event: BaseEvent): boolean {
        throw new Error("Method not implemented.")
    }
    removeEventListener(type: string, listener: EventListenerOrEventListenerObject, options?: boolean | EventListenerOptions | undefined): void {
        throw new Error("Method not implemented.")
    }
    area: Area

    constructor(area: Area) {
        this.area = area
    }
}

export function makeEventTarget(area: Area): EventTarget {
    // TODO: type hack, as we leak Node.js DOM types here.
    // For proper fix make empty types to avoid Node types import in TS compiler root config.
    return new EventTargetImpl(area) as unknown as EventTarget
}

setEventDeliverer((node: PeerNode, peerEvent: PeerEvent, props: Partial<Properties>) => {
    if (props.onClick && peerEvent instanceof SinglePointerPeerEvent) {
        props.onClick(peerEvent)
        return
    }
    if (props.onSwiperChange && peerEvent instanceof SwiperChangePeerEvent) {
        props.onSwiperChange(peerEvent.index)
        return
    }
    if (props.onTabsChange && peerEvent instanceof TabsChangePeerEvent) {
        props.onTabsChange(peerEvent.index)
        return
    }
    if (props.onAppear && peerEvent instanceof AppearPeerEvent) {
        props.onAppear()
        return
    }
    if (props.onDisappear && peerEvent instanceof DisappearPeerEvent) {
        props.onDisappear()
        return
    }
    if (props.onVisibleAreaChange && peerEvent instanceof VisibleAreaChangePeerEvent) {
        props.onVisibleAreaChange(peerEvent.isVisible, peerEvent.currentRatio)
        return
    }
    if (props.onScrollIndex && peerEvent instanceof ScrollIndexPeerEvent) {
        props.onScrollIndex(peerEvent.first, peerEvent.last)
        return
    }
    if (props.onNavigatorClick && peerEvent instanceof NavigatorClickPeerEvent) {
        props.onNavigatorClick()
        return
    }
    if (props.onAction && peerEvent instanceof GesturePeerEvent) {
        props.onAction(peerEvent)
        return
    }
    if (props.onActionStart && peerEvent instanceof GesturePeerEvent) {
        props.onActionStart(peerEvent)
        return
    }
    if (props.onActionUpdate && peerEvent instanceof GesturePeerEvent) {
        props.onActionUpdate(peerEvent)
        return
    }
    if (props.onActionEnd && peerEvent instanceof GesturePeerEvent) {
        props.onActionEnd(peerEvent)
        return
    }
    if (props.onActionCancel) {
        props.onActionCancel()
    }
    if (props.onTextInput && peerEvent instanceof TextInputEvent) {
        props.onTextInput(peerEvent.text)
    }
    if (props.onListScroll && peerEvent instanceof ListScrollPeerEvent) {
        props.onListScroll(peerEvent.scrollOffset, peerEvent.scrollState)
        return
    }
    if (props.onListScrollIndex && peerEvent instanceof ListScrollIndexPeerEvent) {
        props.onListScrollIndex(peerEvent.start, peerEvent.end, peerEvent.center)
        return
    }
    if (props.onListScrollStart && peerEvent instanceof ListScrollStartPeerEvent) {
        props.onListScrollStart()
        return
    }
    if (props.onListScrollStop && peerEvent instanceof ListScrollStopPeerEvent) {
        props.onListScrollStop()
        return
    }
    if (props.onSwiperAnimationStart && peerEvent instanceof SwiperAnimationPeerEvent) {
        props.onSwiperAnimationStart(peerEvent.index, peerEvent.targetIndex, peerEvent.currentOffset, peerEvent.targetOffset, peerEvent.velocity)
        return
    }
    if (props.onSwiperAnimationEnd && peerEvent instanceof SwiperAnimationPeerEvent) {
        props.onSwiperAnimationEnd(peerEvent.index, peerEvent.currentOffset, peerEvent.targetOffset, peerEvent.velocity)
        return
    }
    if (props.onSwiperGestureSwipe && peerEvent instanceof SwiperAnimationPeerEvent) {
        props.onSwiperGestureSwipe(peerEvent.index, peerEvent.currentOffset, peerEvent.targetOffset, peerEvent.velocity)
        return
    }
    if (props.onSliderChange && peerEvent instanceof SliderChangePeerEvent) {
        props.onSliderChange(peerEvent.value, peerEvent.mode)
        return
    }
    if (props.onAreaChange && peerEvent instanceof AreaChangePeerEvent) {
        props.onAreaChange(peerEvent)
        return
    }
    if (props.onBlur && peerEvent instanceof BlurPeerEvent) {
        props.onBlur()
        return
    }
    if (props.onHover && peerEvent instanceof HoverPeerEvent) {
        props.onHover(peerEvent.isHover)
        return
    }
    if (props.onKeyEvent && peerEvent instanceof KeyPeerEvent) {
        props.onKeyEvent(peerEvent)
        return
    }
    if (props.onMouse && peerEvent instanceof MousePeerEvent) {
        props.onMouse(peerEvent)
        return
    }
    if (props.onImageComplete && peerEvent instanceof ImageCompletePeerEvent) {
        props.onImageComplete(new ImageCompletePeerEvent(
            node.getId(),
            peerEvent.width,
            peerEvent.height,
            peerEvent.componentWidth,
            peerEvent.componentHeight,
            peerEvent.loadingStatus,
            peerEvent.contentWidth,
            peerEvent.contentHeight,
            peerEvent.contentOffsetX,
            peerEvent.contentOffsetY))
        return
    }
    if (props.onImageError && peerEvent instanceof ImageErrorPeerEvent) {
        props.onImageError(new ImageErrorPeerEvent(
            node.getId(),
            peerEvent.componentWidth,
            peerEvent.componentHeight,
            peerEvent.message))
        return
    }
    if (props.onRefreshStateChange && peerEvent instanceof RefreshStateChangePeerEvent) {
        props.onRefreshStateChange(peerEvent.state)
        return
    }
    if (props.onRefreshing && peerEvent instanceof OnRefreshingPeerEvent) {
        props.onRefreshing()
        return
    }
    if (props.onRadioChange && peerEvent instanceof OnRadioChangePeerEvent) {
        props.onRadioChange(peerEvent.isChecked)
        return
    }
    if (props.onGridScroll && peerEvent instanceof GridScrollPeerEvent) {
        props.onGridScroll(peerEvent.scrollOffset, peerEvent.scrollState)
        return
    }
    if (props.onGridScrollStart && peerEvent instanceof GridScrollStartPeerEvent) {
        props.onGridScrollStart()
        return
    }
    if (props.onGridScrollStop && peerEvent instanceof GridScrollStopPeerEvent) {
        props.onGridScrollStop()
        return
    }
    if  (props.onSideBarChange && peerEvent instanceof SideBarChangePeerEvent){
        props.onSideBarChange(peerEvent.isChanged)
        return
    }
    if (props.onXComponentLoad && peerEvent instanceof XComponentLoadPeerEvent) {
        props.onXComponentLoad(peerEvent)
        return
    }
    if (props.onXComponentDestroy && peerEvent instanceof XComponentDestroyPeerEvent) {
        props.onXComponentDestroy()
        return
    }
    if  (props.onCanvasReady && peerEvent instanceof CanvasReadyPeerEvent){
        props.onCanvasReady()
        return
    } 
    if (props.onNavBarStateChange && peerEvent instanceof NavBarStateChangePeerEvent) {
        props.onNavBarStateChange(peerEvent.onVisible)
        return
    }
    if (props.navDestination && peerEvent instanceof NavDestinationPeerEvent) {
        props.navDestination(peerEvent.name, peerEvent.param)
        return
    }      
})
