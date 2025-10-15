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
} from 'arkui.component.navDestination';
import { ResourceStr } from 'arkui.component.units';
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import window from '@ohos.window';
import { Scroller } from 'arkui.component.scroll';
import { Resource } from 'global.resource';
import image from '@ohos.multimedia.image';

type PixelMap = image.PixelMap;
type SystemBarStyle = window.SystemBarStyle;

export declare class ArkNavDestinationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name?: string, flags?: int32);
    public static create(component: ComponentBase | undefined, flags?: int32): ArkNavDestinationPeer;
    public setNavDestinationOptionsAttribute(): void;
    public hideTitleBar0Attribute(value: boolean | undefined): void;
    public hideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void;
    public hideBackButtonAttribute(value: boolean | undefined): void;
    public onShownAttribute(value: (() => void) | undefined): void;
    public onHiddenAttribute(value: (() => void) | undefined): void;
    public onBackPressedAttribute(value: (() => boolean) | undefined): void;
    public onResultAttribute(value: ((parameter: Object) => void) | undefined): void;
    public modeAttribute(value: NavDestinationMode | undefined): void;
    public backButtonIcon0Attribute(value: ResourceStr | PixelMap | SymbolGlyphModifier | undefined): void;
    public backButtonIcon1Attribute(
        icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): void;
    public menus0Attribute(value: Array<NavigationMenuItem> | CustomBuilder | undefined): void;
    public menus1Attribute(
        items: Array<NavigationMenuItem> | CustomBuilder | undefined,
        options?: NavigationMenuOptions
    ): void;
    public onReadyAttribute(value: Callback<NavDestinationContext> | undefined): void;
    public onWillAppearAttribute(value: (() => void) | undefined): void;
    public onWillDisappearAttribute(value: (() => void) | undefined): void;
    public onWillShowAttribute(value: (() => void) | undefined): void;
    public onWillHideAttribute(value: (() => void) | undefined): void;
    public systemBarStyleAttribute(value: SystemBarStyle | undefined): void;
    public recoverableAttribute(value: boolean | undefined): void;
    public systemTransitionAttribute(value: NavigationSystemTransitionType | undefined): void;
    public bindToScrollableAttribute(value: Array<Scroller> | undefined): void;
    public bindToNestedScrollableAttribute(value: Array<NestedScrollInfo> | undefined): void;
    public onActiveAttribute(value: ((parameter: NavDestinationActiveReason) => void) | undefined): void;
    public onInactiveAttribute(value: ((parameter: NavDestinationActiveReason) => void) | undefined): void;
    public customTransitionAttribute(value: NavDestinationTransitionDelegate | undefined): void;
    public onNewParamAttribute(value: ((parameter: Object | null | undefined) => void) | undefined): void;
    public preferredOrientationAttribute(value: Orientation | undefined): void;
    public enableNavigationIndicatorAttribute(value: boolean | undefined): void;
    public titleAttribute(
        value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined,
        options?: NavigationTitleOptions
    ): void;
    public toolbarConfigurationAttribute(
        toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions
    ): void;
    public hideToolBarAttribute(hide: boolean | undefined, animated?: boolean): void;
    public ignoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void;
    public enableStatusBarAttribute(enabled: boolean | undefined, animated?: boolean): void;
}

export interface NavDestinationAttribute extends CommonMethod {
    hideTitleBar(hide: boolean | undefined, animated?: boolean): this;
    hideBackButton(value: boolean | undefined): this;
    onShown(value: (() => void) | undefined): this;
    onHidden(value: (() => void) | undefined): this;
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
export declare class ArkNavDestinationStyle extends ArkCommonMethodStyle implements NavDestinationAttribute {
    public hideTitleBar_value?: boolean | undefined;
    public hideBackButton_value?: boolean | undefined;
    public onShown_value?: (() => void) | undefined;
    public onHidden_value?: (() => void) | undefined;
    public onBackPressed_value?: (() => boolean) | undefined;
    public onResult_value?: ((parameter: Object) => void) | undefined;
    public mode_value?: NavDestinationMode | undefined;
    public backButtonIcon_value?: ResourceStr | PixelMap | SymbolGlyphModifier | undefined;
    public menus_value?: Array<NavigationMenuItem> | CustomBuilder | undefined;
    public onReady_value?: Callback<NavDestinationContext> | undefined;
    public onWillAppear_value?: Callback<void> | undefined;
    public onWillDisappear_value?: Callback<void> | undefined;
    public onWillShow_value?: Callback<void> | undefined;
    public onWillHide_value?: Callback<void> | undefined;
    public systemBarStyle_value?: SystemBarStyle | undefined;
    public recoverable_value?: boolean | undefined;
    public systemTransition_value?: NavigationSystemTransitionType | undefined;
    public bindToScrollable_value?: Array<Scroller> | undefined;
    public bindToNestedScrollable_value?: Array<NestedScrollInfo> | undefined;
    public onActive_value?: ((parameter: NavDestinationActiveReason) => void) | undefined;
    public onInactive_value?: ((parameter: NavDestinationActiveReason) => void) | undefined;
    public customTransition_value?: NavDestinationTransitionDelegate | undefined;
    public onNewParam_value?: ((parameter: Object | null | undefined) => void) | undefined;
    public preferredOrientation_value?: Orientation | undefined;
    public enableNavigationIndicator_value?: boolean | undefined;
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this;
    public hideBackButton(value: boolean | undefined): this;
    public onShown(value: (() => void) | undefined): this;
    public onHidden(value: (() => void) | undefined): this;
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
}

@memo_stable() export declare class ArkNavDestinationComponent extends ArkCommonMethodComponent
        implements NavDestinationAttribute {
    public getPeer(): ArkNavDestinationPeer;
    public setNavDestinationOptions(): this;
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this;
    public hideBackButton(value: boolean | undefined): this;
    public onShown(value: (() => void) | undefined): this;
    public onHidden(value: (() => void) | undefined): this;
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
