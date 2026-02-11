/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { memo_stable } from '@koalaui/runtime/annotations';
import { KPointer } from '@koalaui/interop';
import { int32 } from '@koalaui/compat';
import { ComponentBase } from 'arkui/ComponentBase';
import {
    ArkCommonMethodPeer,
    CommonMethod,
    ArkCommonMethodComponent,
    ArkCommonMethodStyle,
} from 'arkui/component/common';
import { LayoutSafeAreaType, LayoutSafeAreaEdge, Callback } from 'arkui.component.common';
import { CustomBuilder } from 'arkui.component.builder';
import {
    NavigationMenuItem,
    NavigationTitleOptions,
    NavigationMenuOptions,
    ToolbarItem,
    NavigationToolbarOptions,
} from 'arkui.component.navigation';
import {
    NavDestinationTransitionDelegate,
    NavDestinationActiveReason,
    NavDestinationAttribute,
    NavDestinationMode,
    NavDestinationContext,
    NavigationSystemTransitionType,
    NestedScrollInfo,
    Orientation,
    NavDestinationCommonTitle,
    NavDestinationCustomTitle,
    VisibilityChangeReason,
} from 'arkui.component.navDestination';
import { ResourceStr } from 'arkui.component.units';
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import window from '@ohos.window';
import { Scroller } from 'arkui.component.scroll';
import { Resource } from 'global.resource';
import image from '@ohos.multimedia.image';

type PixelMap = image.PixelMap;
type SystemBarStyle = window.SystemBarStyle;

export interface NavDestinationModuleInfo {
    moduleName: string;
    pagePath: string;
}

export declare class ArkNavDestinationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0);
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavDestinationPeer;
    public setNavDestinationOptionsAttribute(moduleInfo?: NavDestinationModuleInfo): void;
    public setHideTitleBar0Attribute(value: boolean | undefined): void;
    public setHideBackButtonAttribute(value: boolean | undefined): void;
    public setOnShownAttribute(value: ((value0: VisibilityChangeReason) => void) | undefined): void;
    public setOnHiddenAttribute(value: ((value0: VisibilityChangeReason) => void) | undefined): void;
    public setOnBackPressedAttribute(value: (() => boolean) | undefined): void;
    public setOnResultAttribute(value: ((value0: Object | null | undefined) => void) | undefined): void;
    public setModeAttribute(value: NavDestinationMode | undefined): void;
    public setOnReadyAttribute(value: ((value0: NavDestinationContext) => void) | undefined): void;
    public setOnWillAppearAttribute(value: (() => void) | undefined): void;
    public setOnWillDisappearAttribute(value: (() => void) | undefined): void;
    public setOnWillShowAttribute(value: (() => void) | undefined): void;
    public setOnWillHideAttribute(value: (() => void) | undefined): void;
    public setSystemBarStyleAttribute(value: window.SystemBarStyle | undefined): void;
    public setRecoverableAttribute(value: boolean | undefined): void;
    public setSystemTransitionAttribute(value: NavigationSystemTransitionType | undefined): void;
    public setBindToScrollableAttribute(value: Array<Scroller> | undefined): void;
    public setBindToNestedScrollableAttribute(value: Array<NestedScrollInfo> | undefined): void;
    public setOnActiveAttribute(value: ((value0: NavDestinationActiveReason) => void) | undefined): void;
    public setOnInactiveAttribute(value: ((value0: NavDestinationActiveReason) => void) | undefined): void;
    public setCustomTransitionAttribute(value: NavDestinationTransitionDelegate | undefined): void;
    public setOnNewParamAttribute(value: ((value0: Object | null | undefined) => void) | undefined): void;
    public setPreferredOrientationAttribute(value: window.Orientation | undefined): void;
    public setEnableNavigationIndicatorAttribute(value: boolean | undefined): void;
    public setTitleAttribute(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): void;
    public setHideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void;
    public setBackButtonIconAttribute(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void;
    public setMenusAttribute(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): void;
    public setToolbarConfigurationAttribute(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void;
    public setHideToolBarAttribute(hide: boolean | undefined, animated?: boolean): void;
    public setIgnoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void;
    public setEnableStatusBarAttribute(enabled: boolean | undefined, animated?: boolean): void;
}

export interface NavDestinationAttribute extends CommonMethod {
    hideTitleBar(hide: boolean | undefined, animated?: boolean): this;
    hideBackButton(value: boolean | undefined): this;
    onShown(callback: ((reason: VisibilityChangeReason) => void) | undefined): this;
    onHidden(callback: ((reason: VisibilityChangeReason) => void) | undefined): this;
    onBackPressed(value: (() => boolean) | undefined): this;
    onResult(value: ((parameter: Object) => void) | undefined): this;
    mode(value: NavDestinationMode | undefined): this;
    backButtonIcon(
        icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): this;
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this;
    onReady(value: Callback<NavDestinationContext> | undefined): this;
    onWillAppear(value: Callback<void> | undefined): this;
    onWillDisappear(value: Callback<void> | undefined): this;
    onWillShow(value: Callback<void> | undefined): this;
    onWillHide(value: Callback<void> | undefined): this;
    systemBarStyle(value: SystemBarStyle | undefined): this;
    recoverable(value: boolean | undefined): this;
    systemTransition(value: NavigationSystemTransitionType | undefined): this;
    bindToScrollable(value: Array<Scroller> | undefined): this;
    bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this;
    onActive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this;
    onInactive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this;
    customTransition(value: NavDestinationTransitionDelegate | undefined): this;
    onNewParam(value: ((parameter: Object | null | undefined) => void) | undefined): this;
    preferredOrientation(value: Orientation | undefined): this;
    enableNavigationIndicator(value: boolean | undefined): this;
    title(
        value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined,
        options?: NavigationTitleOptions
    ): this;
    toolbarConfiguration(
        toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions
    ): this;
    hideToolBar(hide: boolean | undefined, animated?: boolean): this;
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this;
    enableStatusBar(enabled: boolean | undefined, animated?: boolean): this;
}

@memo_stable() export declare class ArkNavDestinationComponent extends ArkCommonMethodComponent
        implements NavDestinationAttribute {
    public getPeer(): ArkNavDestinationPeer;
    public setNavDestinationOptions(moduleInfo?: NavDestinationModuleInfo): this;
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this;
    public hideBackButton(value: boolean | undefined): this;
    public onShown(callback: ((reason: VisibilityChangeReason) => void) | undefined): this;
    public onHidden(callback: ((reason: VisibilityChangeReason) => void) | undefined): this;
    public onBackPressed(value: (() => boolean) | undefined): this;
    public onResult(value: ((parameter: Object) => void) | undefined): this;
    public mode(value: NavDestinationMode | undefined): this;
    public backButtonIcon(
        icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): this;
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this;
    public onReady(value: Callback<NavDestinationContext> | undefined): this;
    public onWillAppear(value: Callback<void> | undefined): this;
    public onWillDisappear(value: Callback<void> | undefined): this;
    public onWillShow(value: Callback<void> | undefined): this;
    public onWillHide(value: Callback<void> | undefined): this;
    public systemBarStyle(value: SystemBarStyle | undefined): this;
    public recoverable(value: boolean | undefined): this;
    public systemTransition(value: NavigationSystemTransitionType | undefined): this;
    public bindToScrollable(value: Array<Scroller> | undefined): this;
    public bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this;
    public onActive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this;
    public onInactive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this;
    public customTransition(value: NavDestinationTransitionDelegate | undefined): this;
    public onNewParam(value: ((parameter: Object | null | undefined) => void) | undefined): this;
    public preferredOrientation(value: Orientation | undefined): this;
    public enableNavigationIndicator(value: boolean | undefined): this;
    public title(
        value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined,
        options?: NavigationTitleOptions
    ): this;
    public toolbarConfiguration(
        toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions
    ): this;
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this;
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this;
    public enableStatusBar(enabled: boolean | undefined, animated?: boolean): this;
    public applyAttributesFinish(): void;
}
