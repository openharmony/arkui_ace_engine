/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

import {
    __memo_context_type as __memo_context_type,
    __memo_id_type as __memo_id_type,
} from 'arkui.incremental.runtime.state';
import { memo } from '@koalaui/runtime/annotations';
import {
    ArkCommonMethodPeer,
    CommonMethod,
    ArkCommonMethodStyle,
    ArkCommonMethodComponent,
} from 'arkui/component/common';
import { KPointer } from '@koalaui/interop';
import { int32 } from '@koalaui/compat';
import { ComponentBase } from 'arkui/ComponentBase';
import { LayoutSafeAreaEdge, LayoutSafeAreaType, Bindable } from 'arkui.component.common';
import { CustomBuilder, PageMapBuilder } from 'arkui.component.builder';
import {
    NavBarPosition,
    NavigationMenuItem,
    NavigationOperation,
    NavigationTitleOptions,
    NavigationMenuOptions,
    ToolbarItem,
    NavigationToolbarOptions,
    NavigationAttribute,
    NavigationMode,
    NavigationTitleMode,
    NavContentInfo,
    NavigationAnimatedTransition,
    NavigationCommonTitle,
    NavigationCustomTitle,
    NavPathStack,
    NavigationDividerStyle,
} from 'arkui.component.navigation';
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import { ComponentContent } from 'arkui.ComponentContent';
import window from '@ohos.window';
import { Length, ResourceStr, Dimension } from 'arkui.component.units';
import { Resource } from 'global.resource';
import image from '@ohos.multimedia.image';

type PixelMap = image.PixelMap;
type SystemBarStyle = window.SystemBarStyle;

export interface NavigationModuleInfo {
    moduleName: string;
    pagePath: string;
    isUserCreateStack?: boolean;
}

export interface HomePathInfo {
    name: string;
    param?: Object;
}

export declare class ArkNavigationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0);
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavigationPeer;
    public setNavigationOptions0Attribute(pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo): void;
    public setNavigationOptions1Attribute(pathInfos?: NavPathStack, homeDestination?: HomePathInfo,
        moduleInfo?: NavigationModuleInfo): void;
    public setNavBarWidthAttribute(value: Length | undefined): void;
    public setNavBarPositionAttribute(value: NavBarPosition | undefined): void;
    public setNavBarWidthRangeAttribute(value: [ Dimension, Dimension ] | undefined): void;
    public setMinContentWidthAttribute(value: Dimension | undefined): void;
    public setModeAttribute(value: NavigationMode | undefined): void;
    public setHideNavBarAttribute(value: boolean | undefined): void;
    public setHideTitleBar0Attribute(value: boolean | undefined): void;
    public setHideBackButtonAttribute(value: boolean | undefined): void;
    public setTitleModeAttribute(value: NavigationTitleMode | undefined): void;
    public setHideToolBar0Attribute(value: boolean | undefined): void;
    public setEnableToolBarAdaptationAttribute(value: boolean | undefined): void;
    public setOnTitleModeChangeAttribute(value: ((titleMode: NavigationTitleMode) => void) | undefined): void;
    public setOnNavBarStateChangeAttribute(value: ((isSelected: boolean) => void) | undefined): void;
    public setOnNavigationModeChangeAttribute(value: ((mode: NavigationMode) => void) | undefined): void;
    public setCustomNavContentTransitionAttribute(
        value: ((
            from: NavContentInfo,
            to: NavContentInfo,
            operation: NavigationOperation) => NavigationAnimatedTransition | undefined
        ) | undefined
    ): void;
    public setSystemBarStyleAttribute(value: SystemBarStyle | undefined): void;
    public setRecoverableAttribute(value: boolean | undefined): void;
    public setEnableDragBarAttribute(value: boolean | undefined): void;
    public setDividerAttribute(value: NavigationDividerStyle | null): void;
    public setEnableModeChangeAnimationAttribute(value: boolean | undefined): void;
    public setEnableVisibilityLifecycleWithContentCoverAttribute(value: boolean | undefined): void;
    public setBackButtonIconAttribute(
        icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr): void;
    public setTitleAttribute(
        value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined,
        options?: NavigationTitleOptions
    ): void;
    public setHideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void;
    public setMenusAttribute(items: Array<NavigationMenuItem> | CustomBuilder | undefined,
        options?: NavigationMenuOptions): void;
    public setToolbarConfigurationAttribute(value: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions): void;
    public setHideToolBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void;
    public setIgnoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>,
        edges?: Array<LayoutSafeAreaEdge>): void;
}

export declare class ArkNavigationComponent extends ArkCommonMethodComponent implements NavigationAttribute {
    @memo()  public _navDestination: (__memo_context: __memo_context_type, __memo_id: __memo_id_type,
        name: string, param: (Object | null | undefined)) => void;
    public _needSync: boolean;
    public getPeer(): ArkNavigationPeer;
    public setNavigationOptions(pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo): this;
    public setNavigationOptions(pathInfos?: NavPathStack, homeDestination?: HomePathInfo,
        moduleInfo?: NavigationModuleInfo): this;
    public navBarWidth(value: Length | Bindable<Length> | undefined): this;
    public navBarPosition(value: NavBarPosition | undefined): this;
    public navBarWidthRange(value: [Dimension, Dimension] | undefined): this;
    public minContentWidth(value: Dimension | undefined): this;
    public mode(value: NavigationMode | undefined): this;
    public backButtonIcon(
        icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): this;
    public hideNavBar(value: boolean | undefined): this;
    public hideTitleBar(value: boolean | undefined): this;
    public hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this;
    public hideBackButton(value: boolean | undefined): this;
    public titleMode(value: NavigationTitleMode | undefined): this;
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this;
    public hideToolBar(value: boolean | undefined): this;
    public hideToolBar(hide: boolean | undefined, animated: boolean | undefined): this;
    public enableToolBarAdaptation(value: boolean | undefined): this;
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this;
    public onNavBarStateChange(value: ((isSelected: boolean) => void) | undefined): this;
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this;
    public navDestination(value: PageMapBuilder | undefined): this;
    public customNavContentTransition(
        value: ((
            from: NavContentInfo,
            to: NavContentInfo,
            operation: NavigationOperation) => NavigationAnimatedTransition | undefined
        ) | undefined
    ): this;
    public systemBarStyle(value: SystemBarStyle | undefined): this;
    public recoverable(value: boolean | undefined): this;
    public enableDragBar(value: boolean | undefined): this;
    public divider(value: NavigationDividerStyle | null): this;
    public enableModeChangeAnimation(value: boolean | undefined): this;
    public title(
        value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined,
        options?: NavigationTitleOptions
    ): this;
    public toolbarConfiguration(
        value: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions
    ): this;
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this;
    public splitPlaceholder(placeholder: ComponentContent): this;
    public enableVisibilityLifecycleWithContentCover(value: boolean | undefined): this;
    public applyAttributesFinish(): void;
    public updateNeedSync(needSync: boolean): void;
    public isNeedSync(): boolean;
    public updateNavDestination(navdestination: PageMapBuilder): void;
}
