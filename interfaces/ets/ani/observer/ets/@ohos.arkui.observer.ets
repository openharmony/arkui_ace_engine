/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { NavPathStack, NavigationOperation, NavBar, ResourceStr, Resource, NavDestinationMode,
HeightBreakpoint, WidthBreakpoint } from "@ohos.arkui.component"
import { UIContext } from "@ohos.arkui.UIContext"
import UIAbilityContext from 'application.UIAbilityContext';
import transfer from '@ohos.transfer';
import type { Callback } from '@ohos.base';
import hilog from '@ohos.hilog'
import { Size } from '@ohos.arkui.node'

 export default namespace uiObserver {
    loadLibrary("observer_ani");
    export native function createUIObserver(id: number): UIObserver;
    export native function onRouterPageUpdate(
        context: UIAbilityContext | UIContext,
        callback: Callback<RouterPageInfo>
    ): void;
    export native function offRouterPageUpdate(
        context: UIAbilityContext | UIContext,
        callback?: Callback<RouterPageInfo>
    ): void;
    export native function onNavDestinationUpdate(callback: Callback<NavDestinationInfo>): void;
    export native function offNavDestinationUpdate(callback?: Callback<NavDestinationInfo>): void;
    export native function onNavDestinationUpdate(
        options: NavDestinationSwitchObserverOptions,
        callback: Callback<NavDestinationInfo>
    ): void;
    export native function offNavDestinationUpdate(
        options: NavDestinationSwitchObserverOptions,
        callback?: Callback<NavDestinationInfo>
    ): void;
    export native function onNavDestinationSwitch(callback: Callback<NavDestinationSwitchInfo>): void;
    export native function offNavDestinationSwitch(callback?: Callback<NavDestinationSwitchInfo>): void;
    export native function onNavDestinationSwitch(
        observerOptions: NavDestinationSwitchObserverOptions,
        callback: Callback<NavDestinationSwitchInfo>
    ): void;
    export native function offNavDestinationSwitch(
        observerOptions: NavDestinationSwitchObserverOptions,
        callback?: Callback<NavDestinationSwitchInfo>
    ): void;

    export native function onTabChange(callback: Callback<ObserverOptions>): void;
    export native function offTabChange(callback?: Callback<ObserverOptions>): void;
    export native function onTabChange(options: ObserverOptions, callback: Callback<ObserverOptions>): void;
    export native function offTabChange(options: ObserverOptions, callback?: Callback<ObserverOptions>): void;

    export class DensityInfo {
        density: number;
    }
    export class UIObserver
    {
        private nativeObserverAddr:long = 0;
        
        constructor(nativeAddr:long) {
            if (this.nativeObserverAddr == 0) {
                this.nativeObserverAddr = nativeAddr;
            }
        }

        public native on(type: string, callback: object) : void;
        public native off(type: string, callback?: object) : void;

        public native on(type: string, options: NavDestinationSwitchObserverOptions, callback: object): void;
        public native off(type: string, options: NavDestinationSwitchObserverOptions, callback?: object): void;

        public native onScrollEvent(options: ObserverOptions, callback: Callback<ScrollEventInfo>): void;
        public native offScrollEvent(options: ObserverOptions, callback: Callback<ScrollEventInfo>): void;
        public native onScrollEvent(callback: Callback<ScrollEventInfo>): void;
        public native offScrollEvent(callback: Callback<ScrollEventInfo>): void;

        public native onNavDestinationUpdate(callback: Callback<NavDestinationInfo>): void;

        public native offNavDestinationUpdate(callback?: Callback<NavDestinationInfo>): void;
        public native onNavDestinationUpdate(
            options: NavDestinationSwitchObserverOptions,
            callback: Callback<NavDestinationInfo>
        ): void;
        public native offNavDestinationUpdate(
            options: NavDestinationSwitchObserverOptions,
            callback?: Callback<NavDestinationInfo>
        ): void;

        public native onRouterPageUpdate(callback: Callback<RouterPageInfo>): void;
        public native offRouterPageUpdate(callback?: Callback<RouterPageInfo>): void;

        public native onNavDestinationSwitch(callback: Callback<NavDestinationSwitchInfo>): void;
        public native offNavDestinationSwitch(callback?: Callback<NavDestinationSwitchInfo>): void;
        public native onNavDestinationSwitch(
            observerOptions: NavDestinationSwitchObserverOptions,
            callback: Callback<NavDestinationSwitchInfo>
          ): void;
        public native offNavDestinationSwitch(
            observerOptions: NavDestinationSwitchObserverOptions,
            callback?: Callback<NavDestinationSwitchInfo>
          ): void;

        public native onTabChange(callback: Callback<TabContentInfo>): void;
        public native offTabChange(callback?: Callback<TabContentInfo>): void;
        public native onTabChange(options: ObserverOptions, callback: Callback<TabContentInfo>): void;
        public native offTabChange(options: ObserverOptions, callback?: Callback<TabContentInfo>): void;

        public native onTabContentUpdate(callback: Callback<TabContentInfo>): void;
        public native offTabContentUpdate(callback?: Callback<TabContentInfo>): void;
        public native onTabContentUpdate(options: ObserverOptions, callback: Callback<TabContentInfo>): void;
        public native offTabContentUpdate(options: ObserverOptions, callback?: Callback<TabContentInfo>): void;

        public native onDensityUpdate(callback: Callback<DensityInfo>): void;
        public native offDensityUpdate(callback?: Callback<DensityInfo>): void;
        public native onWillDraw(callback: Callback<void>): void;
        public native offWillDraw(callback?: Callback<void>): void;
        public native onDidLayout(callback: Callback<void>): void;
        public native offDidLayout(callback?: Callback<void>): void;

        public native onRouterPageSizeChange(callback: Callback<RouterPageInfo>): void;
        public native offRouterPageSizeChange(callback?: Callback<RouterPageInfo>): void;
        public native onNavDestinationSizeChange(callback: Callback<NavDestinationInfo>): void;
        public native offNavDestinationSizeChange(callback?: Callback<NavDestinationInfo>): void;
        public native onNavDestinationSizeChangeByUniqueId(
            navigationUniqueId: int, callback: Callback<NavDestinationInfo>): void;
        public native offNavDestinationSizeChangeByUniqueId(
            navigationUniqueId: int, callback?: Callback<NavDestinationInfo>): void;
    }

    export interface NavigationInfo {
        navigationId: string;
        pathStack: NavPathStack;
        uniqueId?: int;
    }
    export class WindowSizeLayoutBreakpointInfo {
        widthBreakpoint: WidthBreakpoint;
        heightBreakpoint: HeightBreakpoint;
    }

    export class NavigationInfoImpl implements NavigationInfo {
        navigationId: string;
        pathStack: NavPathStack;
        uniqueId?: int;
        static transferStatic(input: Any): Object {
            let dynamicValue = ESValue.wrap(input);
            let staticValue = new NavigationInfoImpl();
            if (dynamicValue.isUndefined() || dynamicValue.isNull()) {
                return staticValue;
            }
            let navigationId = dynamicValue.getProperty("navigationId");
            if (navigationId.isString()) {
                staticValue.navigationId = navigationId.toString();
            }
            let navPathStack = dynamicValue.getProperty("pathStack");
            if (navPathStack.typeOf() !== 'undefined' && navPathStack.typeOf() !== 'null')  {
                // pathStack needs analysis to static NavPathStack
            }
            let uniqueId =dynamicValue.getProperty('uniqueId');
            if (uniqueId.typeOf() !== 'undefined' && uniqueId.typeOf() !== 'null' && uniqueId.isNumber()) {
                let id = uniqueId.toNumber();
                staticValue.uniqueId = Double.toInt(id);
            }
            return staticValue;
        }

        static transferDynamic(input: Object): Any {
            let dynamicValue = ESValue.instantiateEmptyObject();
            if (input == null || input == undefined) {
                return dynamicValue;
            }
            let staticValue = input as NavigationInfo;
            if (staticValue == null || staticValue == undefined) {
                return dynamicValue;
            }
            dynamicValue.setProperty('navigationId', ESValue.wrap(staticValue.navigationId));
            dynamicValue.setProperty('pathStack', ESValue.wrap(staticValue.pathStack));
            if (staticValue.uniqueId != undefined && staticValue.uniqueId != null) {
                dynamicValue.setProperty('uniqueId', ESValue.wrap(staticValue.uniqueId));
            }
            return dynamicValue as Any;
        }
    }

    export enum NavDestinationState {
        ON_SHOWN = 0,
        ON_HIDDEN = 1,
        ON_APPEAR = 2,
        ON_DISAPPEAR = 3,
        ON_WILL_SHOW = 4,
        ON_WILL_HIDE = 5,
        ON_WILL_APPEAR = 6,
        ON_WILL_DISAPPEAR = 7,
        ON_ACTIVE = 8,
        ON_INACTIVE = 9,
        ON_BACKPRESS = 100
    }

    export class SizeInner implements Size {
        width: number;
        height: number;
        constructor(width: number, height: number) {
            this.width = width;
            this.height = height;
        }
    }

    export interface NavDestinationInfo {
        navigationId: ResourceStr;
        name: ResourceStr;
        state: NavDestinationState;
        index: int;
        param?: Object;
        navDestinationId: string;
        uniqueId?: int;
        mode?: NavDestinationMode;
        size?: Size;
    }

    export class NavDestinationInfoImpl implements NavDestinationInfo {
        navigationId: ResourceStr;
        name: ResourceStr;
        state: NavDestinationState;
        index: int;
        param?: Object;
        navDestinationId: string;
        uniqueId?: int;
        mode?: NavDestinationMode;
        size?: Size;
        static castToNavDestinationInfo(value: number): NavDestinationState {
            if (value === 0) {
                return NavDestinationState.ON_SHOWN;
            } else if (value === 1) {
                return NavDestinationState.ON_HIDDEN;
            } else if (value === 2) {
                return NavDestinationState.ON_APPEAR;
            } else if (value === 3) {
                return NavDestinationState.ON_DISAPPEAR;
            } else if (value === 4) {
                return NavDestinationState.ON_WILL_SHOW;
            } else if (value === 5) {
                return NavDestinationState.ON_WILL_HIDE;
            } else if (value === 6) {
                return NavDestinationState.ON_WILL_APPEAR;
            } else if (value === 7) {
                return NavDestinationState.ON_WILL_DISAPPEAR;
            } else if (value === 8) {
                return NavDestinationState.ON_ACTIVE;
            } else if (value === 9) {
                return NavDestinationState.ON_INACTIVE;
            } else if (value === 100) {
                return NavDestinationState.ON_BACKPRESS;
            } else {
                throw Error("state in NavDestinationInfo type Error");
            }
        }
        static castToNavDestinationMode(value: number): NavDestinationMode {
            if (value === 0) {
                return NavDestinationMode.STANDARD;
            } else if (value === 1) {
                return NavDestinationMode.DIALOG;
            } else {
                throw Error("mode in NavDestinationInfo type Error");
            }
        }
        static transferStatic(input: Any): Object {
            let dynamicValue = ESValue.wrap(input);
            let staticValue = new NavDestinationInfoImpl();
            if (dynamicValue.isUndefined() || dynamicValue.isNull()) {
                return staticValue;
            }
            let navigationId = dynamicValue.getProperty("navigationId");
            if (navigationId.isString()) {
                staticValue.navigationId = navigationId.toString();
            } else if (navigationId.isObject()) {
                staticValue.navigationId = navigationId.toStaticObject() as Resource;
            }

            let name = dynamicValue.getProperty("name");
            if (name.isString()) {
                staticValue.name = name.toString();
            } else if (name.isObject()) {
                staticValue.name = name.toStaticObject() as Resource;
            }

            let state = dynamicValue.getProperty("state");
            if (state.isNumber()) {
                staticValue.state = NavDestinationInfoImpl.castToNavDestinationInfo(state.toNumber());
            }

            let index = dynamicValue.getProperty("index");
            if (index.isNumber()) {
                staticValue.index = index.toNumber() as int;
            }

            let param = dynamicValue.getProperty("param");
            if (param.isObject()) {
                staticValue.param = param.toStaticObject();
            }

            let navDestinationId = dynamicValue.getProperty("navDestinationId");
            if (navDestinationId.isString()) {
                staticValue.navDestinationId = navDestinationId.toString();
            }

            let uniqueId = dynamicValue.getProperty("uniqueId");
            if (uniqueId.isNumber()) {
                staticValue.uniqueId = uniqueId.toNumber() as int;
            }

            let mode = dynamicValue.getProperty("mode");
            if (mode.isNumber()) {
                staticValue.mode = NavDestinationInfoImpl.castToNavDestinationMode(mode.toNumber());
            }

            return staticValue;
        }

        static transferDynamic(input: Object): Any {
            let dynamicValue = ESValue.instantiateEmptyObject();
            if (input == null || input == undefined) {
                return dynamicValue;
            }
            let staticValue = input as NavDestinationInfo;
            if (staticValue == null || staticValue == undefined) {
                return dynamicValue;
            }
            dynamicValue.setProperty('navigationId', ESValue.wrap(staticValue.navigationId));
            dynamicValue.setProperty('name', ESValue.wrap(staticValue.name));
            dynamicValue.setProperty('state', ESValue.wrapNumber(staticValue.state));
            dynamicValue.setProperty('index', ESValue.wrap(staticValue.index));
            if (staticValue.param === null || staticValue.param === undefined) {
                dynamicValue.setProperty('param', ESValue.Null);
            } else {
                dynamicValue.setProperty('param', ESValue.wrap(staticValue.param));
            }
            dynamicValue.setProperty('navDestinationId', ESValue.wrap(staticValue.navDestinationId));
            if (staticValue.uniqueId === null || staticValue.uniqueId === undefined) {
                dynamicValue.setProperty('uniqueId', ESValue.Null);
            } else {
                dynamicValue.setProperty('uniqueId', ESValue.wrap(staticValue.uniqueId));
            }
            if (staticValue.mode === null || staticValue.mode === undefined) {
                dynamicValue.setProperty('mode', ESValue.Null);
            } else {
                dynamicValue.setProperty('mode', ESValue.wrapNumber(staticValue.mode!));
            }
            return dynamicValue as Any;
        }
    }

    export enum RouterPageState {
        ABOUT_TO_APPEAR = 0,
        ABOUT_TO_DISAPPEAR = 1,
        ON_PAGE_SHOW = 2,
        ON_PAGE_HIDE = 3,
        ON_BACK_PRESS = 4
    }

    export class RouterPageInfo {
        context: UIAbilityContext | UIContext;
        index: int;
        name: string;
        path: string;
        state: RouterPageState;
        pageId: string;
        size?: Size;

        static castToRouterPageState(value: number): RouterPageState {
            if (value === 0) {
                return RouterPageState.ABOUT_TO_APPEAR;
            } else if (value === 1) {
                return RouterPageState.ABOUT_TO_DISAPPEAR;
            } else if (value === 2) {
                return RouterPageState.ON_PAGE_SHOW;
            } else if (value === 3) {
                return RouterPageState.ON_PAGE_HIDE;
            } else if (value === 4) {
                return RouterPageState.ON_BACK_PRESS;
            } else {
                throw Error("state in RouterPageInfo type Error");
            }
        }
        static transferStatic(input: Any): Object {
            let dynamicValue =  ESValue.wrap(input)
            let staticValue = new RouterPageInfo()
            if (dynamicValue.isUndefined() || dynamicValue.isNull()) {
                return staticValue;
            }
            let context = dynamicValue.getProperty('context');
            if (context.typeOf() !== 'undefined' && context.typeOf() !== 'null') {
                // context needs analysis to static UIContext and UIAbilityContext
            }

            let index = dynamicValue.getProperty('index');
            if (index.isNumber()) {
                staticValue.index = index.toNumber() as int;
            }

            let name = dynamicValue.getProperty('name');
            if (name.isString()) {
                staticValue.name = name.toString();
            }

            let path = dynamicValue.getProperty('path');
            if (path.isString()) {
                staticValue.path = path.toString();
            }

            let pageId = dynamicValue.getProperty('pageId');
            if (pageId.isString()) {
                staticValue.pageId = pageId.toString();
            }

            let state = dynamicValue.getProperty('state');
            if (state.isNumber()) {
                staticValue.state = RouterPageInfo.castToRouterPageState(state.toNumber());
            }

            return staticValue;
        }

        static transferDynamic(input: Object): Any {
            let dynamicValue = ESValue.instantiateEmptyObject()
            if (input == null || input == undefined) {
                return dynamicValue;
            }
            let staticValue = input as RouterPageInfo
            if (staticValue == null || staticValue == undefined) {
                return dynamicValue;
            }
            if (staticValue.context === null || staticValue.context === undefined) {
                dynamicValue.setProperty('context', ESValue.Null);
            } else {
                dynamicValue.setProperty('context', ESValue.wrap(staticValue.context));
            }
            dynamicValue.setProperty('index', ESValue.wrap(staticValue.index));
            dynamicValue.setProperty('name', ESValue.wrap(staticValue.name));
            dynamicValue.setProperty('path', ESValue.wrap(staticValue.path));
            dynamicValue.setProperty('state', ESValue.wrapNumber(staticValue.state));
            dynamicValue.setProperty('pageId', ESValue.wrap(staticValue.pageId));
            return dynamicValue as Any;
        }
    }

    export interface NavDestinationSwitchObserverOptions {}

    export interface ObserverOptions {}

    export enum ScrollEventType {
      SCROLL_START = 0,
      SCROLL_STOP = 1
    }

    export enum Axis {
        VERTICAL = 0,
        Vertical = 0,
        HORIZONTAL = 1,
        Horizontal = 1
    }

    export interface ScrollEventInfo {
        id: string;
        uniqueId: number;
        scrollEvent: ScrollEventType;
        offset: number;
        axis: Axis;
    }

    export class ScrollEventInfoImpl implements ScrollEventInfo{
        id: string;
        uniqueId: number;
        scrollEvent: ScrollEventType;
        offset: number;
        axis: Axis;

        static castToScrollEventType(value: number): ScrollEventType {
            if (value === 0) {
                return ScrollEventType.SCROLL_START;
            } else if (value === 1) {
                return ScrollEventType.SCROLL_STOP;
            } else {
                throw Error("mode in ScrollEventInfo type Error");
            }
        }

        static castToAxis(value: number): Axis {
            if (value === 0) {
                return Axis.Vertical;
            } else if (value === 1) {
                return Axis.Horizontal;
            } else {
                throw Error("mode in ScrollEventInfo type Error");
            }
        }
        
        static transferStatic(input: Any): Object {
            let dynamicValue = ESValue.wrap(input);
            let staticValue = new ScrollEventInfoImpl();
            if (dynamicValue.isUndefined() || dynamicValue.isNull()) {
                return staticValue;
            }
            let id = dynamicValue.getProperty("id");
            if (!id.isString()) {
                throw Error("id in ScrollEventInfo type Error");
            }

            let uniqueId = dynamicValue.getProperty("uniqueId");
            if (!uniqueId.isNumber()) {
                throw Error("uniqueId in ScrollEventInfo type Error");
            }
            staticValue.uniqueId = uniqueId.toNumber();

            let scrollEvent = dynamicValue.getProperty("scrollEvent");
            if (!scrollEvent.isNumber()) {
                throw Error("scrollEvent in ScrollEventInfo type Error");
            }
            staticValue.scrollEvent = ScrollEventInfoImpl.castToScrollEventType(scrollEvent.toNumber());

            let offset = dynamicValue.getProperty("offset");
            if (!offset.isNumber()) {
                throw Error("offset in ScrollEventInfo type Error");
            }
            staticValue.offset = offset.toNumber();

            let axis = dynamicValue.getProperty("axis");
            if (!axis.isNumber()) {
                throw Error("axis in ScrollEventInfo type Error");
            }
            staticValue.axis = ScrollEventInfoImpl.castToAxis(axis.toNumber());

            return staticValue;
        }

        static transferDynamic(input: Object): Any {
            let dynamicValue = ESValue.instantiateEmptyObject();
            if (input == null || input == undefined) {
                return dynamicValue;
            }
            let staticValue = input as ScrollEventInfoImpl;
            if (staticValue == null || staticValue == undefined) {
                return dynamicValue;
            }
            dynamicValue.setProperty('id', ESValue.wrap(staticValue.id));
            dynamicValue.setProperty('uniqueId', ESValue.wrap(staticValue.uniqueId));
            dynamicValue.setProperty('scrollEvent', ESValue.wrapNumber(staticValue.scrollEvent));
            dynamicValue.setProperty('offset', ESValue.wrap(staticValue.offset));
            dynamicValue.setProperty('axis', ESValue.wrapNumber(staticValue.axis));


            return dynamicValue as Any;
        }
    }

    export interface NavDestinationSwitchInfo {
        context: UIAbilityContext | UIContext;
        from: NavDestinationInfo | NavBar;
        to: NavDestinationInfo | NavBar;
        operation: NavigationOperation;
    }

    export class NavDestinationSwitchInfoImpl implements NavDestinationSwitchInfo {
        context: UIAbilityContext | UIContext;
        from: NavDestinationInfo | NavBar;
        to: NavDestinationInfo | NavBar;
        operation: NavigationOperation;
    }

    export enum TabContentState {
        ON_SHOW = 0,
        ON_HIDE = 1
    }

    export interface TabContentInfo {
        tabContentId: string;
        tabContentUniqueId: int;
        state: TabContentState;
        index: int;
        id: string;
        uniqueId: int;
        lastIndex?: int;
    }

    export class TabContentInfoImpl implements TabContentInfo {
        tabContentId: string;
        tabContentUniqueId: int;
        state: TabContentState;
        index: int;
        id: string;
        uniqueId: int;
        lastIndex?: int;
        static setTabContentInfoImplLastIndex(contentInfo: TabContentInfoImpl, value: int): void {
            contentInfo.lastIndex = value;
        }
        static castToTabContentState(value: number): TabContentState {
            if (value === 0) {
                return TabContentState.ON_SHOW;
            } else if (value === 1) {
                return TabContentState.ON_HIDE;
            } else {
                throw Error("state in TabContentState type Error");
            }
        }
    }
 }
