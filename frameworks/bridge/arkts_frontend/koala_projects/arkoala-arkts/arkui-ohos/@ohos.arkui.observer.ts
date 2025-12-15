import { ResourceStr } from '/arkui/component/units';
import { NavPathStack, NavigationOperation, NavBar } from 'arkui/framework'
import { UIContext } from '@ohos/arkui/UIContext';
import UIAbilityContext from 'application.UIAbilityContext';
import { NavDestinationMode } from 'arkui/framework'
import { int32 } from "@koalaui/common"

declare namespace uiObserver {
    export class DensityInfo {
        density: double;
    }
    type Callback_<T,V = void> = (data: T) => V
      
    export class UIObserver {
        on(type: string, callback: object): void;
        off(type: string, callback?: object): void;

        on(type: string, options: NavDestinationSwitchObserverOptions, callback: object): void;
        off(type: string, options: NavDestinationSwitchObserverOptions, callback?: object): void;

        onScrollEvent(options: ObserverOptions, callback: Callback_<ScrollEventInfo>): void;
        offScrollEvent(options: ObserverOptions, callback: Callback_<ScrollEventInfo>): void;
        onScrollEvent(callback: Callback_<ScrollEventInfo>): void;
        offScrollEvent(callback: Callback_<ScrollEventInfo>): void;

        onNavDestinationUpdate(callback: Callback_<NavDestinationInfo>): void;

        offNavDestinationUpdate(callback?: Callback_<NavDestinationInfo>): void;
        onNavDestinationUpdate(
            options: NavDestinationSwitchObserverOptions,
            callback: Callback_<NavDestinationInfo>
        ): void;
        offNavDestinationUpdate(
            options: NavDestinationSwitchObserverOptions,
            callback?: Callback_<NavDestinationInfo>
        ): void;

        onRouterPageUpdate(callback: Callback_<RouterPageInfo>): void;
        offRouterPageUpdate(callback?: Callback_<RouterPageInfo>): void;

        onNavDestinationSwitch(callback: Callback_<NavDestinationSwitchInfo>): void;
        offNavDestinationSwitch(callback?: Callback_<NavDestinationSwitchInfo>): void;
        onNavDestinationSwitch(
            observerOptions: NavDestinationSwitchObserverOptions,
            callback: Callback_<NavDestinationSwitchInfo>
          ): void;
        offNavDestinationSwitch(
            observerOptions: NavDestinationSwitchObserverOptions,
            callback?: Callback_<NavDestinationSwitchInfo>
          ): void;

        onTabChange(callback: Callback_<TabContentInfo>): void;
        offTabChange(callback?: Callback_<TabContentInfo>): void;
        onTabChange(options: ObserverOptions, callback: Callback_<TabContentInfo>): void;
        offTabChange(options: ObserverOptions, callback?: Callback_<TabContentInfo>): void;

        onTabContentUpdate(callback: Callback_<TabContentInfo>): void;
        offTabContentUpdate(callback?: Callback_<TabContentInfo>): void;
        onTabContentUpdate(options: ObserverOptions, callback: Callback_<TabContentInfo>): void;
        offTabContentUpdate(options: ObserverOptions, callback?: Callback_<TabContentInfo>): void;

        onDensityUpdate(callback: Callback_<DensityInfo>): void;
        offDensityUpdate(callback?: Callback_<DensityInfo>): void;

        onWillDraw(callback: Callback_<void>): void;
        offWillDraw(callback?: Callback_<void>): void;

        onDidLayout(callback: Callback_<void>): void;
        offDidLayout(callback?: Callback_<void>): void;
    }
    export function createUIObserver(id: number): UIObserver;

    export enum NavDestinationState {
        ON_SHOWN = 0,
        ON_HIDDEN = 1,
        ON_APPEAR = 2,
        ON_DISAPPEAR = 3,
        ON_WILL_SHOW = 4,
        ON_WILL_HIDE = 5,
        ON_WILL_APPEAR = 6,
        ON_WILL_DISAPPEAR = 7,
        ON_BACKPRESS = 100
    }

    export interface NavigationInfo {
        navigationId: string;
        pathStack: NavPathStack;
        uniqueId: int32 | undefined;
    }

    export interface NavDestinationSwitchInfo {

        context: UIAbilityContext | UIContext;
        from: NavDestinationInfo | NavBar;
        to: NavDestinationInfo | NavBar;
        operation: NavigationOperation;
    }

    export class RouterPageInfo {
        context: UIAbilityContext | UIContext;
        index: int32;
        name: string;
        path: string;
        state: RouterPageState;
        pageId: string;
    }

    export interface NavDestinationInfo {
        navigationId: ResourceStr;
        name: ResourceStr;
        state: NavDestinationState;
        index: int32;
        param?: Object;
        navDestinationId: string;
        uniqueId?: int32;
        mode?: NavDestinationMode;
    }

    export enum RouterPageState {
        ABOUT_TO_APPEAR = 0,
        ABOUT_TO_DISAPPEAR = 1,
        ON_PAGE_SHOW = 2,
        ON_PAGE_HIDE = 3,
        ON_BACK_PRESS = 4
    }
    export interface NavDestinationSwitchObserverOptions {
        navigationId: ResourceStr;
    }

    export interface ScrollEventInfo {
        id: string;
        uniqueId: number;
        scrollEvent: ScrollEventType;
        offset: number;
        axis: Axis;
    }

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

    export interface ObserverOptions {
        id: string;
    }
}

export default uiObserver;
