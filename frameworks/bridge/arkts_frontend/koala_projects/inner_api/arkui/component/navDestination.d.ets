/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
    public setHideBackButtonAttribute(value: boolean | undefined): void;
    public setOnShownAttribute(value: Callback<VisibilityChangeReason, void> | undefined): void;
    public setOnHiddenAttribute(value: Callback<VisibilityChangeReason, void> | undefined): void;
    public setOnBackPressedAttribute(value: (() => boolean) | undefined): void;
    public setOnResultAttribute(value: Callback<Object | null | undefined, void> | undefined): void;
    public setModeAttribute(value: NavDestinationMode | undefined): void;
    public setOnReadyAttribute(value: Callback<NavDestinationContext, void> | undefined): void;
    public setOnWillAppearAttribute(value: Callback<void> | undefined): void;
    public setOnWillDisappearAttribute(value: Callback<void> | undefined): void;
    public setOnWillShowAttribute(value: Callback<void> | undefined): void;
    public setOnWillHideAttribute(value: Callback<void> | undefined): void;
    public setSystemBarStyleAttribute(value: SystemBarStyle | undefined): void;
    public setRecoverableAttribute(value: boolean | undefined): void;
    public setSystemTransitionAttribute(value: NavigationSystemTransitionType | undefined): void;
    public setBindToScrollableAttribute(value: Array<Scroller> | undefined): void;
    public setBindToNestedScrollableAttribute(value: Array<NestedScrollInfo> | undefined): void;
    public setOnActiveAttribute(value: Callback<NavDestinationActiveReason, void> | undefined): void;
    public setOnInactiveAttribute(value: Callback<NavDestinationActiveReason, void> | undefined): void;
    public setCustomTransitionAttribute(value: NavDestinationTransitionDelegate | undefined): void;
    public setOnNewParamAttribute(value: Callback<Object | null | undefined, void> | undefined): void;
    public setPreferredOrientationAttribute(value: Orientation | undefined): void;
    public setEnableNavigationIndicatorAttribute(value: boolean | undefined): void;
    public setTitleAttribute(
        value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined,
        options?: NavigationTitleOptions): void;
    public setBackButtonIconAttribute(
        icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void;
    public setMenusAttribute(
        items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): void;
    public setToolbarConfigurationAttribute(
        toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void;
    public setHideToolBarAttribute(hide: boolean | undefined, animated?: boolean): void;
    public setIgnoreLayoutSafeAreaAttribute(
        types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void;
    public setEnableStatusBarAttribute(enabled: boolean | undefined, animated?: boolean): void;
}

@memo_stable() export declare class ArkNavDestinationComponent extends ArkCommonMethodComponent
        implements NavDestinationAttribute {
    public getPeer(): ArkNavDestinationPeer;
    public setNavDestinationOptions(moduleInfo?: NavDestinationModuleInfo): this;
    public hideTitleBar(value: boolean | undefined): this;
    public hideBackButton(value: boolean | undefined): this;
    public onShown(value: Callback<VisibilityChangeReason, void> | undefined): this;
    public onHidden(value: Callback<VisibilityChangeReason, void> | undefined): this;
    public onBackPressed(value: (() => boolean) | undefined): this;
    public onResult(value: Callback<Object | null | undefined, void> | undefined): this;
    public mode(value: NavDestinationMode | undefined): this;
    public onReady(value: Callback<NavDestinationContext, void> | undefined): this;
    public onWillAppear(value: Callback<void> | undefined): this;
    public onWillDisappear(value: Callback<void> | undefined): this;
    public onWillShow(value: Callback<void> | undefined): this;
    public onWillHide(value: Callback<void> | undefined): this;
    public systemBarStyle(value: SystemBarStyle | undefined): this;
    public recoverable(value: boolean | undefined): this;
    public systemTransition(value: NavigationSystemTransitionType | undefined): this;
    public bindToScrollable(value: Array<Scroller> | undefined): this;
    public bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this;
    public onActive(value: Callback<NavDestinationActiveReason, void> | undefined): this;
    public onInactive(value: Callback<NavDestinationActiveReason, void> | undefined): this;
    public customTransition(value: NavDestinationTransitionDelegate | undefined): this;
    public onNewParam(value: Callback<Object | null | undefined, void> | undefined): this;
    public preferredOrientation(value: Orientation | undefined): this;
    public enableNavigationIndicator(value: boolean | undefined): this;
    public title(
        value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined,
        options?: NavigationTitleOptions
    ): this;
    public hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this;
    public backButtonIcon(
        icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): this;
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this;
    public toolbarConfiguration(
        toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions
    ): this;
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this;
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this;
    public enableStatusBar(enabled: boolean | undefined, animated?: boolean): this;
    public applyAttributesFinish(): void;
}
