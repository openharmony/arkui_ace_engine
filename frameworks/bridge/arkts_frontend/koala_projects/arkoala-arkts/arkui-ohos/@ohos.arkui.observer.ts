import { ResourceStr } from '/arkui/component/units';
import { NavPathStack } from 'arkui/component/navigation';
import { UIContext } from '@ohos/arkui/UIContext';
import UIAbilityContext from 'application.UIAbilityContext';
import { NavDestinationMode } from 'arkui/component/navDestination';

export declare namespace uiObserver {
    export class DensityInfo {
        density: number;
    }
    type Callback<T,V = void> = (data: T) => V
      
    export interface UIObserver {
        on(type: string, callback: object): void;
        off(type: string, callback?: object): void;
        
        on(type: string, options: NavDestinationSwitchObserverOptions, callback: object): void;
        off(type: string, options: NavDestinationSwitchObserverOptions, callback?: object): void;
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
    }

    export class RouterPageInfo {
        context: UIAbilityContext | UIContext;
        index: number;
        name: string;
        path: string;
        state: RouterPageState;
        pageId: string;
    }

    export interface NavDestinationInfo {
        navigationId: ResourceStr;
        name: ResourceStr;
        state: NavDestinationState;
        index: number;
        param?: Object;
        navDestinationId: string;
        uniqueId: number;
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
}
