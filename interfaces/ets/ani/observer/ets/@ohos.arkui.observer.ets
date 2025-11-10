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
    export class DensityInfo {
        density: number;
    }
    export default interface UIObserver
    {
        on(type: string, callback: object) : void;
        off(type: string, callback?: object) : void;
        on(type: string, options: NavDestinationSwitchObserverOptions, callback: object): void;
        off(type: string, options: NavDestinationSwitchObserverOptions, callback?: object): void;

        onNavDestinationUpdate(callback: Callback<NavDestinationInfo>): void;

        offNavDestinationUpdate(callback?: Callback<NavDestinationInfo>): void;
        onNavDestinationUpdate(
            options: NavDestinationSwitchObserverOptions,
            callback: Callback<NavDestinationInfo>
        ): void;
        offNavDestinationUpdate(
            options: NavDestinationSwitchObserverOptions,
            callback?: Callback<NavDestinationInfo>
        ): void;
        onRouterPageUpdate(callback: Callback<RouterPageInfo>): void;
        offRouterPageUpdate(callback?: Callback<RouterPageInfo>): void;
        onNavDestinationSwitch(callback: Callback<NavDestinationSwitchInfo>): void;
        offNavDestinationSwitch(callback?: Callback<NavDestinationSwitchInfo>): void;
        onNavDestinationSwitch(
            observerOptions: NavDestinationSwitchObserverOptions,
            callback: Callback<NavDestinationSwitchInfo>
          ): void;
        offNavDestinationSwitch(
            observerOptions: NavDestinationSwitchObserverOptions,
            callback?: Callback<NavDestinationSwitchInfo>
          ): void;

        onTabChange(callback: object): void;
        offTabChange(callback?: object): void;
        onTabChange(options: ObserverOptions, callback: object): void;
        offTabChange(options: ObserverOptions, callback?: object): void;

        onTabContentUpdate(callback: Callback<TabContentInfo>): void;
        offTabContentUpdate(callback?: Callback<TabContentInfo>): void;
        onTabContentUpdate(options: ObserverOptions, callback: Callback<TabContentInfo>): void;
        offTabContentUpdate(options: ObserverOptions, callback?: Callback<TabContentInfo>): void;
    }
    
    class UIObserverImpl implements UIObserver
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

        public native onTabChange(callback: object): void;
        public native offTabChange(callback?: object): void;
        public native onTabChange(options: ObserverOptions, callback: object): void;
        public native offTabChange(options: ObserverOptions, callback?: object): void;

        public native onTabContentUpdate(callback: Callback<TabContentInfo>): void;
        public native offTabContentUpdate(callback?: Callback<TabContentInfo>): void;
        public native onTabContentUpdate(options: ObserverOptions, callback: Callback<TabContentInfo>): void;
        public native offTabContentUpdate(options: ObserverOptions, callback?: Callback<TabContentInfo>): void;
    }

    export interface NavigationInfo {
        navigationId: string;
        pathStack: NavPathStack;
    }
    export class WindowSizeLayoutBreakpointInfo {
        widthBreakpoint: WidthBreakpoint;
        heightBreakpoint: HeightBreakpoint;
    }

    export class NavigationInfoImpl implements NavigationInfo {
        navigationId: string;
        pathStack: NavPathStack;
        static transferStatic(input: Any): Object {
            let dynamicValue = ESValue.wrap(input);
            let staticValue = new NavigationInfoImpl();
            if (dynamicValue.isUndefined() || dynamicValue.isNull()) {
                return staticValue;
            }
            let navigationId = dynamicValue.getProperty("navigationId");
            if (!navigationId.isString()) {
                throw Error("navigationId in NavigationInfo type Error");
            }
            staticValue.navigationId = navigationId.toString();
            let navPathStack = dynamicValue.getProperty("pathStack");
            if (navPathStack.typeOf() !== 'undefined' && navPathStack.typeOf() !== 'null')  {
                staticValue.pathStack = navPathStack.unwrap() as NavPathStack;
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

    export interface NavDestinationInfo {
        navigationId: ResourceStr;
        name: ResourceStr;
        state: NavDestinationState;
        index: int;
        param?: Object;
        navDestinationId: string;
        uniqueId?: int;
        mode?: NavDestinationMode;
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
            } else {
                throw Error("navigationId in NavDestinationInfo type Error");
            }

            let name = dynamicValue.getProperty("name");
            if (name.isString()) {
                staticValue.name = name.toString();
            } else if (name.isObject()) {
                staticValue.name = name.toStaticObject() as Resource;
            } else {
                throw Error("name in NavDestinationInfo type Error");
            }

            let state = dynamicValue.getProperty("state");
            if (!state.isNumber()) {
                throw Error("state in NavDestinationInfo type Error");
            }
            staticValue.state = NavDestinationInfoImpl.castToNavDestinationInfo(state.toNumber());

            let index = dynamicValue.getProperty("index");
            if (!index.isNumber()) {
                throw Error("index in NavDestinationInfo type Error");
            }
            staticValue.index = index.toNumber() as int;

            let param = dynamicValue.getProperty("param");
            if (param.isString()) {
                staticValue.param = param.toStaticObject();
            } else if (!(param.isUndefined() || param.isNull())) {
                throw Error("param in NavDestinationInfo type Error");
            }   
            
            let navDestinationId = dynamicValue.getProperty("navDestinationId");
            if (!navDestinationId.isString()) {
                throw Error("navDestinationId in NavDestinationInfo type Error");
            }
            staticValue.navDestinationId = navDestinationId.toString();

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
                throw Error("state in NavDestinationInfo type Error");
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
                staticValue.context = context.unwrap() as UIContext | UIAbilityContext;
            }

            let index = dynamicValue.getProperty('index');
            if (!index.isNumber()) {
                throw Error("index in RouterPageInfo type Error");
            }
            staticValue.index = index.toNumber() as int;

            let name = dynamicValue.getProperty('name');
            if (!name.isString()) {
                throw Error("name in RouterPageInfo type Error");
            }
            staticValue.name = name.toString();

            let path = dynamicValue.getProperty('path');
            if (!path.isString()) {
                throw Error("path in RouterPageInfo type Error");
            }
            staticValue.path = path.toString();

            let pageId = dynamicValue.getProperty('pageId');
            if (!pageId.isString()) {
                throw Error("pageId in RouterPageInfo type Error");
            }
            staticValue.pageId = pageId.toString();

            let state = dynamicValue.getProperty('state');
            if (!state.isNumber()) {
                throw Error("state in RouterPageInfo type Error");
            }
            staticValue.state = RouterPageInfo.castToRouterPageState(state.toNumber());
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

    export interface ScrollEventInfo {}

    export interface NavDestinationSwitchInfo {}

    export enum TabContentState {
        ON_SHOW = 0,
        ON_HIDE = 1
    }

    export interface TabContentInfo {
        tabContentId: string;
        tabContentUniqueId: number;
        state: TabContentState;
        index: number;
        id: string;
        uniqueId: number;
        lastIndex?: int;
    }

    export class TabContentInfoImpl implements TabContentInfo {
        tabContentId: string;
        tabContentUniqueId: number;
        state: TabContentState;
        index: number;
        id: string;
        uniqueId: number;
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
