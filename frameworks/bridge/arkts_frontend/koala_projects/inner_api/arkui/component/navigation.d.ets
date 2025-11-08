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
import { LayoutSafeAreaEdge, LayoutSafeAreaType } from 'arkui.component.common';
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
} from 'arkui.component.navigation';
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import window from '@ohos.window';
import { Length, ResourceStr, Dimension } from 'arkui.component.units';
import { Resource } from 'global.resource';
import image from '@ohos.multimedia.image';

type PixelMap = image.PixelMap;
type SystemBarStyle = window.SystemBarStyle;

export declare class ArkNavigationPeer extends ArkCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string);
    constructor(peerPtr: KPointer, id: int32);
    protected constructor(peerPtr: KPointer, id: int32, name: string, flags: int32);
    public static create(component: ComponentBase | undefined, flags?: int32): ArkNavigationPeer;
    public setNavigationOptions0Attribute(): void;
    public setNavigationOptions1Attribute(pathInfos: NavPathStack): void;
    public navBarWidthAttribute(value: Length | undefined): void;
    public navBarPositionAttribute(value: NavBarPosition | undefined): void;
    public navBarWidthRangeAttribute(value: [Dimension, Dimension] | undefined): void;
    public minContentWidthAttribute(value: Dimension | undefined): void;
    public modeAttribute(value: NavigationMode | undefined): void;
    public backButtonIcon0Attribute(value: string | PixelMap | Resource | SymbolGlyphModifier | undefined): void;
    public backButtonIcon1Attribute(
        icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): void;
    public hideNavBarAttribute(value: boolean | undefined): void;
    public subTitleAttribute(value: string | undefined): void;
    public hideTitleBar0Attribute(value: boolean | undefined): void;
    public hideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void;
    public hideBackButtonAttribute(value: boolean | undefined): void;
    public titleModeAttribute(value: NavigationTitleMode | undefined): void;
    public menus0Attribute(value: Array<NavigationMenuItem> | CustomBuilder | undefined): void;
    public menus1Attribute(
        items: Array<NavigationMenuItem> | CustomBuilder | undefined,
        options?: NavigationMenuOptions
    ): void;
    public toolBarAttribute(value: CustomBuilder | undefined): void;
    public hideToolBar0Attribute(value: boolean | undefined): void;
    public hideToolBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void;
    public enableToolBarAdaptationAttribute(value: boolean | undefined): void;
    public onTitleModeChangeAttribute(value: ((titleMode: NavigationTitleMode) => void) | undefined): void;
    public onNavBarStateChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void;
    public onNavigationModeChangeAttribute(value: ((mode: NavigationMode) => void) | undefined): void;
    public navDestinationAttribute(value: ((name: string, param: Object | null | undefined) => void) | undefined): void;
    public customNavContentTransitionAttribute(
        value:
            ((
                  from: NavContentInfo,
                  to: NavContentInfo,
                  operation: NavigationOperation
              ) => NavigationAnimatedTransition | undefined)
            | undefined
    ): void;
    public systemBarStyleAttribute(value: SystemBarStyle | undefined): void;
    public recoverableAttribute(value: boolean | undefined): void;
    public enableDragBarAttribute(value: boolean | undefined): void;
    public enableModeChangeAnimationAttribute(value: boolean | undefined): void;
    public titleAttribute(
        value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined,
        options?: NavigationTitleOptions
    ): void;
    public toolbarConfigurationAttribute(
        value: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions
    ): void;
    public ignoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void;
}

export interface NavigationAttribute extends CommonMethod {
    navBarWidth(value: Length | undefined): this;
    navBarPosition(value: NavBarPosition | undefined): this;
    navBarWidthRange(value: [Dimension, Dimension] | undefined): this;
    minContentWidth(value: Dimension | undefined): this;
    mode(value: NavigationMode | undefined): this;
    backButtonIcon(
        icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): this;
    hideNavBar(value: boolean | undefined): this;
    subTitle(value: string | undefined): this;
    hideTitleBar(hide: boolean | undefined, animated?: boolean): this;
    hideBackButton(value: boolean | undefined): this;
    titleMode(value: NavigationTitleMode | undefined): this;
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this;
    toolBar(value: CustomBuilder | undefined): this;
    hideToolBar(hide: boolean | undefined, animated?: boolean): this;
    enableToolBarAdaptation(value: boolean | undefined): this;
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this;
    onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this;
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this;
    navDestination(value: (PageMapBuilder | undefined)): this;
    customNavContentTransition(
        value:
            ((
                  from: NavContentInfo,
                  to: NavContentInfo,
                  operation: NavigationOperation
              ) => NavigationAnimatedTransition | undefined)
            | undefined
    ): this;
    systemBarStyle(value: SystemBarStyle | undefined): this;
    recoverable(value: boolean | undefined): this;
    enableDragBar(value: boolean | undefined): this;
    enableModeChangeAnimation(value: boolean | undefined): this;
    title(
        value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined,
        options?: NavigationTitleOptions
    ): this;
    toolbarConfiguration(
        value: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions
    ): this;
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this;
}
export declare class ArkNavigationStyle extends ArkCommonMethodStyle implements NavigationAttribute {
    public navBarWidth_value?: Length | undefined;
    public navBarPosition_value?: NavBarPosition | undefined;
    public navBarWidthRange_value?: [Dimension, Dimension] | undefined;
    public minContentWidth_value?: Dimension | undefined;
    public mode_value?: NavigationMode | undefined;
    public backButtonIcon_value?: string | PixelMap | Resource | SymbolGlyphModifier | undefined;
    public hideNavBar_value?: boolean | undefined;
    public subTitle_value?: string | undefined;
    public hideTitleBar_value?: boolean | undefined;
    public hideBackButton_value?: boolean | undefined;
    public titleMode_value?: NavigationTitleMode | undefined;
    public menus_value?: Array<NavigationMenuItem> | CustomBuilder | undefined;
    public toolBar_value?: CustomBuilder | undefined;
    public toolbarConfiguration_value?: Array<ToolbarItem> | CustomBuilder | undefined;
    public hideToolBar_value?: boolean | undefined;
    public enableToolBarAdaptation_value?: boolean | undefined;
    public onTitleModeChange_value?: ((titleMode: NavigationTitleMode) => void) | undefined;
    public onNavBarStateChange_value?: ((isVisible: boolean) => void) | undefined;
    public onNavigationModeChange_value?: ((mode: NavigationMode) => void) | undefined;
    public navDestination_value?: ((name: string, param: Object | undefined) => void) | undefined;
    public customNavContentTransition_value?:
        ((
              from: NavContentInfo,
              to: NavContentInfo,
              operation: NavigationOperation
          ) => NavigationAnimatedTransition | undefined)
        | undefined;
    public systemBarStyle_value?: SystemBarStyle | undefined;
    public recoverable_value?: boolean | undefined;
    public enableDragBar_value?: boolean | undefined;
    public enableModeChangeAnimation_value?: boolean | undefined;
    public navBarWidth(value: Length | undefined): this;
    public navBarPosition(value: NavBarPosition | undefined): this;
    public navBarWidthRange(value: [Dimension, Dimension] | undefined): this;
    public minContentWidth(value: Dimension | undefined): this;
    public mode(value: NavigationMode | undefined): this;
    public backButtonIcon(
        icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): this;
    public hideNavBar(value: boolean | undefined): this;
    public subTitle(value: string | undefined): this;
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this;
    public hideBackButton(value: boolean | undefined): this;
    public titleMode(value: NavigationTitleMode | undefined): this;
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this;
    public toolBar(value: CustomBuilder | undefined): this;
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this;
    public enableToolBarAdaptation(value: boolean | undefined): this;
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this;
    public onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this;
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this;
    navDestination(value: (PageMapBuilder | undefined)): this;
    public customNavContentTransition(
        value:
            ((
                  from: NavContentInfo,
                  to: NavContentInfo,
                  operation: NavigationOperation
              ) => NavigationAnimatedTransition | undefined)
            | undefined
    ): this;
    public systemBarStyle(value: SystemBarStyle | undefined): this;
    public recoverable(value: boolean | undefined): this;
    public enableDragBar(value: boolean | undefined): this;
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
}

export declare class ArkNavigationComponent extends ArkCommonMethodComponent implements NavigationAttribute {
    @memo()  public _navDestination: (__memo_context: __memo_context_type, __memo_id: __memo_id_type,
        name: string, param: (Object | null | undefined)) => void;
    public _needSync: boolean;
    public getPeer(): ArkNavigationPeer;
    public setNavigationOptions(pathInfos?: NavPathStack): this;
    public navBarWidth(value: Length | undefined): this;
    public navBarPosition(value: NavBarPosition | undefined): this;
    public navBarWidthRange(value: [Dimension, Dimension] | undefined): this;
    public minContentWidth(value: Dimension | undefined): this;
    public mode(value: NavigationMode | undefined): this;
    public backButtonIcon(
        icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined,
        accessibilityText?: ResourceStr
    ): this;
    public hideNavBar(value: boolean | undefined): this;
    public subTitle(value: string | undefined): this;
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this;
    public hideBackButton(value: boolean | undefined): this;
    public titleMode(value: NavigationTitleMode | undefined): this;
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this;
    public toolBar(value: CustomBuilder | undefined): this;
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this;
    public enableToolBarAdaptation(value: boolean | undefined): this;
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this;
    public onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this;
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this;
    navDestination(value: (PageMapBuilder | undefined)): this;
    public customNavContentTransition(
        value:
            ((
                  from: NavContentInfo,
                  to: NavContentInfo,
                  operation: NavigationOperation
              ) => NavigationAnimatedTransition | undefined)
            | undefined
    ): this;
    public systemBarStyle(value: SystemBarStyle | undefined): this;
    public recoverable(value: boolean | undefined): this;
    public enableDragBar(value: boolean | undefined): this;
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
    public applyAttributesFinish(): void;
    public updateNeedSync(needSync: boolean): void;
    public isNeedSync(): boolean;
}
