/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkNavigationPeer, NavBarPosition, NavigationMode, NavigationTitleMode, NavContentInfo, NavigationOperation, NavigationAnimatedTransition, NavigationCommonTitle, NavigationCustomTitle, NavigationTitleOptions, NavigationMenuItem, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions, NavigationAttribute } from "./component/navigation"
import { int32 } from "@koalaui/common"
import { CommonMethod, Bindable, LayoutSafeAreaType, LayoutSafeAreaEdge } from "./component/common"
import { Length, Dimension, ResourceStr } from "./component/units"
import { Resource } from "global.resource"
import { PageMapBuilder, CustomBuilder } from "./component/builder"
import { default as window } from "@ohos.window"
import { default as image } from "@ohos.multimedia.image"
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { ModifierState } from "./CommonModifier"
export class NavigationModifier extends CommonMethodModifier implements NavigationAttribute,AttributeModifier<NavigationAttribute> {
    _instanceId: number = -1;
     _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: NavigationAttribute): void { }
    applyPressedAttribute(instance: NavigationAttribute): void { }
    applyFocusedAttribute(instance: NavigationAttribute): void { }
    applyDisabledAttribute(instance: NavigationAttribute): void { }
    applySelectedAttribute(instance: NavigationAttribute): void { }
    _navBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _navBarWidth_0_0value?: Length | Bindable<Length> | undefined
    _navBarPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _navBarPosition_0_0value?: NavBarPosition | undefined
    _navBarWidthRange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _navBarWidthRange_0_0value?: [ Dimension, Dimension ] | undefined
    _minContentWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minContentWidth_0_0value?: Dimension | undefined
    _mode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mode_0_0value?: NavigationMode | undefined
    _hideNavBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideNavBar_0_0value?: boolean | undefined
    _hideTitleBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_0_0value?: boolean | undefined
    _hideBackButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideBackButton_0_0value?: boolean | undefined
    _titleMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _titleMode_0_0value?: NavigationTitleMode | undefined
    _hideToolBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideToolBar_0_0value?: boolean | undefined
    _enableToolBarAdaptation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableToolBarAdaptation_0_0value?: boolean | undefined
    _onTitleModeChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTitleModeChange_0_0value?: ((titleMode: NavigationTitleMode) => void) | undefined
    _onNavBarStateChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNavBarStateChange_0_0value?: ((isVisible: boolean) => void) | undefined
    _onNavigationModeChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNavigationModeChange_0_0value?: ((mode: NavigationMode) => void) | undefined
    _customNavContentTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customNavContentTransition_0_0value?: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined
    _systemBarStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _systemBarStyle_0_0value?: window.SystemBarStyle | undefined
    _recoverable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _recoverable_0_0value?: boolean | undefined
    _enableDragBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableDragBar_0_0value?: boolean | undefined
    _enableModeChangeAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableModeChangeAnimation_0_0value?: boolean | undefined
    _backButtonIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backButtonIcon_0_0value?: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined
    _backButtonIcon_0_1value?: ResourceStr | undefined
    _title_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _title_0_0value?: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined
    _title_0_1value?: NavigationTitleOptions | undefined
    _hideTitleBar_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_1_0value?: boolean | undefined
    _hideTitleBar_1_1value?: boolean | undefined
    _menus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menus_0_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _menus_0_1value?: NavigationMenuOptions | undefined
    _toolbarConfiguration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _toolbarConfiguration_0_0value?: Array<ToolbarItem> | CustomBuilder | undefined
    _toolbarConfiguration_0_1value?: NavigationToolbarOptions | undefined
    _hideToolBar_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideToolBar_1_0value?: boolean | undefined
    _hideToolBar_1_1value?: boolean | undefined
    _ignoreLayoutSafeArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _ignoreLayoutSafeArea_0_0value?: Array<LayoutSafeAreaType> | undefined
    _ignoreLayoutSafeArea_0_1value?: Array<LayoutSafeAreaEdge> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkNavigationPeer;
        if (this._navBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._navBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNavBarWidthAttribute((this._navBarWidth_0_0value as Length | Bindable<Length> | undefined));
                    this._navBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._navBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._navBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNavBarWidthAttribute((undefined as Length | Bindable<Length> | undefined));
                }
            }
        }
        if (this._navBarPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._navBarPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNavBarPositionAttribute((this._navBarPosition_0_0value as NavBarPosition | undefined));
                    this._navBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._navBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._navBarPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNavBarPositionAttribute((undefined as NavBarPosition | undefined));
                }
            }
        }
        if (this._navBarWidthRange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._navBarWidthRange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNavBarWidthRangeAttribute((this._navBarWidthRange_0_0value as [ Dimension, Dimension ] | undefined));
                    this._navBarWidthRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._navBarWidthRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._navBarWidthRange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNavBarWidthRangeAttribute((undefined as [ Dimension, Dimension ] | undefined));
                }
            }
        }
        if (this._minContentWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minContentWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinContentWidthAttribute((this._minContentWidth_0_0value as Dimension | undefined));
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinContentWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._mode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setModeAttribute((this._mode_0_0value as NavigationMode | undefined));
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setModeAttribute((undefined as NavigationMode | undefined));
                }
            }
        }
        if (this._hideNavBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideNavBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideNavBarAttribute((this._hideNavBar_0_0value as boolean | undefined));
                    this._hideNavBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideNavBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideNavBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideNavBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._hideTitleBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideTitleBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideTitleBar0Attribute((this._hideTitleBar_0_0value as boolean | undefined));
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideTitleBar0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._hideBackButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideBackButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideBackButtonAttribute((this._hideBackButton_0_0value as boolean | undefined));
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideBackButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._titleMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._titleMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTitleModeAttribute((this._titleMode_0_0value as NavigationTitleMode | undefined));
                    this._titleMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._titleMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._titleMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTitleModeAttribute((undefined as NavigationTitleMode | undefined));
                }
            }
        }
        if (this._hideToolBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideToolBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideToolBar0Attribute((this._hideToolBar_0_0value as boolean | undefined));
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideToolBar0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableToolBarAdaptation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableToolBarAdaptation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableToolBarAdaptationAttribute((this._enableToolBarAdaptation_0_0value as boolean | undefined));
                    this._enableToolBarAdaptation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableToolBarAdaptation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableToolBarAdaptation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableToolBarAdaptationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onTitleModeChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTitleModeChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTitleModeChangeAttribute((this._onTitleModeChange_0_0value as ((titleMode: NavigationTitleMode) => void) | undefined));
                    this._onTitleModeChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTitleModeChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTitleModeChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTitleModeChangeAttribute((undefined as ((titleMode: NavigationTitleMode) => void) | undefined));
                }
            }
        }
        if (this._onNavBarStateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNavBarStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNavBarStateChangeAttribute((this._onNavBarStateChange_0_0value as ((isVisible: boolean) => void) | undefined));
                    this._onNavBarStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNavBarStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNavBarStateChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNavBarStateChangeAttribute((undefined as ((isVisible: boolean) => void) | undefined));
                }
            }
        }
        if (this._onNavigationModeChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNavigationModeChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNavigationModeChangeAttribute((this._onNavigationModeChange_0_0value as ((mode: NavigationMode) => void) | undefined));
                    this._onNavigationModeChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNavigationModeChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNavigationModeChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNavigationModeChangeAttribute((undefined as ((mode: NavigationMode) => void) | undefined));
                }
            }
        }
        if (this._customNavContentTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customNavContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomNavContentTransitionAttribute((this._customNavContentTransition_0_0value as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined));
                    this._customNavContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customNavContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customNavContentTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomNavContentTransitionAttribute((undefined as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined));
                }
            }
        }
        if (this._systemBarStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._systemBarStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSystemBarStyleAttribute((this._systemBarStyle_0_0value as window.SystemBarStyle | undefined));
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSystemBarStyleAttribute((undefined as window.SystemBarStyle | undefined));
                }
            }
        }
        if (this._recoverable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._recoverable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRecoverableAttribute((this._recoverable_0_0value as boolean | undefined));
                    this._recoverable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._recoverable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._recoverable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRecoverableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableDragBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableDragBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableDragBarAttribute((this._enableDragBar_0_0value as boolean | undefined));
                    this._enableDragBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableDragBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableDragBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableDragBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableModeChangeAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableModeChangeAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableModeChangeAnimationAttribute((this._enableModeChangeAnimation_0_0value as boolean | undefined));
                    this._enableModeChangeAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableModeChangeAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableModeChangeAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableModeChangeAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackButtonIconAttribute((this._backButtonIcon_0_0value as string | image.PixelMap | Resource | SymbolGlyphModifier | undefined), (this._backButtonIcon_0_1value as ResourceStr | undefined | undefined));
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackButtonIconAttribute((undefined as string | image.PixelMap | Resource | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
        if (this._title_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._title_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTitleAttribute((this._title_0_0value as ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (this._title_0_1value as NavigationTitleOptions | undefined | undefined));
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._title_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTitleAttribute((undefined as ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (this._hideTitleBar_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideTitleBar_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideTitleBar1Attribute((this._hideTitleBar_1_0value as boolean | undefined), (this._hideTitleBar_1_1value as boolean | undefined));
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideTitleBar1Attribute((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._menus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenusAttribute((this._menus_0_0value as Array<NavigationMenuItem> | CustomBuilder | undefined), (this._menus_0_1value as NavigationMenuOptions | undefined | undefined));
                    this._menus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenusAttribute((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined), (undefined as NavigationMenuOptions | undefined | undefined));
                }
            }
        }
        if (this._toolbarConfiguration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._toolbarConfiguration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setToolbarConfigurationAttribute((this._toolbarConfiguration_0_0value as Array<ToolbarItem> | CustomBuilder | undefined), (this._toolbarConfiguration_0_1value as NavigationToolbarOptions | undefined | undefined));
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setToolbarConfigurationAttribute((undefined as Array<ToolbarItem> | CustomBuilder | undefined), (undefined as NavigationToolbarOptions | undefined | undefined));
                }
            }
        }
        if (this._hideToolBar_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideToolBar_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideToolBar1Attribute((this._hideToolBar_1_0value as boolean | undefined), (this._hideToolBar_1_1value as boolean | undefined));
                    this._hideToolBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideToolBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideToolBar_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideToolBar1Attribute((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._ignoreLayoutSafeArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._ignoreLayoutSafeArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIgnoreLayoutSafeAreaAttribute((this._ignoreLayoutSafeArea_0_0value as Array<LayoutSafeAreaType> | undefined | undefined), (this._ignoreLayoutSafeArea_0_1value as Array<LayoutSafeAreaEdge> | undefined | undefined));
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIgnoreLayoutSafeAreaAttribute((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: NavigationModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._navBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._navBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.navBarWidth(modifier._navBarWidth_0_0value);
                    break;
                }
                default: {
                    this.navBarWidth((undefined as Length | Bindable<Length> | undefined));
                }
            }
        }
        if (modifier._navBarPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._navBarPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.navBarPosition(modifier._navBarPosition_0_0value);
                    break;
                }
                default: {
                    this.navBarPosition((undefined as NavBarPosition | undefined));
                }
            }
        }
        if (modifier._navBarWidthRange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._navBarWidthRange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.navBarWidthRange(modifier._navBarWidthRange_0_0value);
                    break;
                }
                default: {
                    this.navBarWidthRange((undefined as [ Dimension, Dimension ] | undefined));
                }
            }
        }
        if (modifier._minContentWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minContentWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minContentWidth(modifier._minContentWidth_0_0value);
                    break;
                }
                default: {
                    this.minContentWidth((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._mode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mode(modifier._mode_0_0value);
                    break;
                }
                default: {
                    this.mode((undefined as NavigationMode | undefined));
                }
            }
        }
        if (modifier._hideNavBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideNavBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideNavBar(modifier._hideNavBar_0_0value);
                    break;
                }
                default: {
                    this.hideNavBar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._hideTitleBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideTitleBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideTitleBar(modifier._hideTitleBar_0_0value);
                    break;
                }
                default: {
                    this.hideTitleBar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._hideBackButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideBackButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideBackButton(modifier._hideBackButton_0_0value);
                    break;
                }
                default: {
                    this.hideBackButton((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._titleMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._titleMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.titleMode(modifier._titleMode_0_0value);
                    break;
                }
                default: {
                    this.titleMode((undefined as NavigationTitleMode | undefined));
                }
            }
        }
        if (modifier._hideToolBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideToolBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideToolBar(modifier._hideToolBar_0_0value);
                    break;
                }
                default: {
                    this.hideToolBar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableToolBarAdaptation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableToolBarAdaptation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableToolBarAdaptation(modifier._enableToolBarAdaptation_0_0value);
                    break;
                }
                default: {
                    this.enableToolBarAdaptation((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onTitleModeChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTitleModeChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTitleModeChange(modifier._onTitleModeChange_0_0value);
                    break;
                }
                default: {
                    this.onTitleModeChange((undefined as ((titleMode: NavigationTitleMode) => void) | undefined));
                }
            }
        }
        if (modifier._onNavBarStateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNavBarStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNavBarStateChange(modifier._onNavBarStateChange_0_0value);
                    break;
                }
                default: {
                    this.onNavBarStateChange((undefined as ((isVisible: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._onNavigationModeChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNavigationModeChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNavigationModeChange(modifier._onNavigationModeChange_0_0value);
                    break;
                }
                default: {
                    this.onNavigationModeChange((undefined as ((mode: NavigationMode) => void) | undefined));
                }
            }
        }
        if (modifier._customNavContentTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customNavContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customNavContentTransition(modifier._customNavContentTransition_0_0value);
                    break;
                }
                default: {
                    this.customNavContentTransition((undefined as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined));
                }
            }
        }
        if (modifier._systemBarStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._systemBarStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.systemBarStyle(modifier._systemBarStyle_0_0value);
                    break;
                }
                default: {
                    this.systemBarStyle((undefined as window.SystemBarStyle | undefined));
                }
            }
        }
        if (modifier._recoverable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._recoverable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.recoverable(modifier._recoverable_0_0value);
                    break;
                }
                default: {
                    this.recoverable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableDragBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableDragBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableDragBar(modifier._enableDragBar_0_0value);
                    break;
                }
                default: {
                    this.enableDragBar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableModeChangeAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableModeChangeAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableModeChangeAnimation(modifier._enableModeChangeAnimation_0_0value);
                    break;
                }
                default: {
                    this.enableModeChangeAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backButtonIcon(modifier._backButtonIcon_0_0value, modifier._backButtonIcon_0_1value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as string | image.PixelMap | Resource | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
        if (modifier._title_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._title_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.title(modifier._title_0_0value, modifier._title_0_1value);
                    break;
                }
                default: {
                    this.title((undefined as ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (modifier._hideTitleBar_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideTitleBar_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideTitleBar(modifier._hideTitleBar_1_0value, modifier._hideTitleBar_1_1value);
                    break;
                }
                default: {
                    this.hideTitleBar((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (modifier._menus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menus(modifier._menus_0_0value, modifier._menus_0_1value);
                    break;
                }
                default: {
                    this.menus((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined), (undefined as NavigationMenuOptions | undefined | undefined));
                }
            }
        }
        if (modifier._toolbarConfiguration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._toolbarConfiguration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.toolbarConfiguration(modifier._toolbarConfiguration_0_0value, modifier._toolbarConfiguration_0_1value);
                    break;
                }
                default: {
                    this.toolbarConfiguration((undefined as Array<ToolbarItem> | CustomBuilder | undefined), (undefined as NavigationToolbarOptions | undefined | undefined));
                }
            }
        }
        if (modifier._hideToolBar_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideToolBar_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideToolBar(modifier._hideToolBar_1_0value, modifier._hideToolBar_1_1value);
                    break;
                }
                default: {
                    this.hideToolBar((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (modifier._ignoreLayoutSafeArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._ignoreLayoutSafeArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.ignoreLayoutSafeArea(modifier._ignoreLayoutSafeArea_0_0value, modifier._ignoreLayoutSafeArea_0_1value);
                    break;
                }
                default: {
                    this.ignoreLayoutSafeArea((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
    }
    navBarWidth(value: Length | Bindable<Length> | undefined): this {
        if (((this._navBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._navBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._navBarWidth_0_0value = value
        } else
        {
            this._navBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    navBarPosition(value: NavBarPosition | undefined): this {
        if (((this._navBarPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._navBarPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._navBarPosition_0_0value = value
        } else
        {
            this._navBarPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        if (((this._navBarWidthRange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._navBarWidthRange_0_flag = AttributeUpdaterFlag.UPDATE
            this._navBarWidthRange_0_0value = value
        } else
        {
            this._navBarWidthRange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minContentWidth(value: Dimension | undefined): this {
        if (((this._minContentWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minContentWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._minContentWidth_0_0value = value
        } else
        {
            this._minContentWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mode(value: NavigationMode | undefined): this {
        if (((this._mode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mode_0_flag = AttributeUpdaterFlag.UPDATE
            this._mode_0_0value = value
        } else
        {
            this._mode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideNavBar(value: boolean | undefined): this {
        if (((this._hideNavBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideNavBar_0_0value) !== (value)))
        {
            this._hideNavBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._hideNavBar_0_0value = value
        } else
        {
            this._hideNavBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideTitleBar(value: boolean | undefined): this {
        if (((this._hideTitleBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideTitleBar_0_0value) !== (value)))
        {
            this._hideTitleBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._hideTitleBar_0_0value = value
        } else
        {
            this._hideTitleBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideBackButton(value: boolean | undefined): this {
        if (((this._hideBackButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideBackButton_0_0value) !== (value)))
        {
            this._hideBackButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._hideBackButton_0_0value = value
        } else
        {
            this._hideBackButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    titleMode(value: NavigationTitleMode | undefined): this {
        if (((this._titleMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._titleMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._titleMode_0_0value = value
        } else
        {
            this._titleMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideToolBar(value: boolean | undefined): this {
        if (((this._hideToolBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideToolBar_0_0value) !== (value)))
        {
            this._hideToolBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._hideToolBar_0_0value = value
        } else
        {
            this._hideToolBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableToolBarAdaptation(value: boolean | undefined): this {
        if (((this._enableToolBarAdaptation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableToolBarAdaptation_0_0value) !== (value)))
        {
            this._enableToolBarAdaptation_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableToolBarAdaptation_0_0value = value
        } else
        {
            this._enableToolBarAdaptation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        if (((this._onTitleModeChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTitleModeChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTitleModeChange_0_0value = value
        } else
        {
            this._onTitleModeChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (((this._onNavBarStateChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNavBarStateChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNavBarStateChange_0_0value = value
        } else
        {
            this._onNavBarStateChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        if (((this._onNavigationModeChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNavigationModeChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNavigationModeChange_0_0value = value
        } else
        {
            this._onNavigationModeChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        if (((this._customNavContentTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._customNavContentTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._customNavContentTransition_0_0value = value
        } else
        {
            this._customNavContentTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    systemBarStyle(value: window.SystemBarStyle | undefined): this {
        if (((this._systemBarStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._systemBarStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._systemBarStyle_0_0value = value
        } else
        {
            this._systemBarStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    recoverable(value: boolean | undefined): this {
        if (((this._recoverable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._recoverable_0_0value) !== (value)))
        {
            this._recoverable_0_flag = AttributeUpdaterFlag.UPDATE
            this._recoverable_0_0value = value
        } else
        {
            this._recoverable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableDragBar(value: boolean | undefined): this {
        if (((this._enableDragBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableDragBar_0_0value) !== (value)))
        {
            this._enableDragBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableDragBar_0_0value = value
        } else
        {
            this._enableDragBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableModeChangeAnimation(value: boolean | undefined): this {
        if (((this._enableModeChangeAnimation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableModeChangeAnimation_0_0value) !== (value)))
        {
            this._enableModeChangeAnimation_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableModeChangeAnimation_0_0value = value
        } else
        {
            this._enableModeChangeAnimation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (((this._backButtonIcon_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._backButtonIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._backButtonIcon_0_0value = icon
            this._backButtonIcon_0_1value = accessibilityText
        } else
        {
            this._backButtonIcon_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        if (((this._title_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._title_0_flag = AttributeUpdaterFlag.UPDATE
            this._title_0_0value = value
            this._title_0_1value = options
        } else
        {
            this._title_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        if (((this._hideTitleBar_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideTitleBar_1_0value) !== (hide)) || ((this._hideTitleBar_1_1value) !== (animated)))
        {
            this._hideTitleBar_1_flag = AttributeUpdaterFlag.UPDATE
            this._hideTitleBar_1_0value = hide
            this._hideTitleBar_1_1value = animated
        } else
        {
            this._hideTitleBar_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (((this._menus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._menus_0_flag = AttributeUpdaterFlag.UPDATE
            this._menus_0_0value = items
            this._menus_0_1value = options
        } else
        {
            this._menus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (((this._toolbarConfiguration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.UPDATE
            this._toolbarConfiguration_0_0value = value
            this._toolbarConfiguration_0_1value = options
        } else
        {
            this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideToolBar(hide: boolean | undefined, animated: boolean | undefined): this {
        if (((this._hideToolBar_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideToolBar_1_0value) !== (hide)) || ((this._hideToolBar_1_1value) !== (animated)))
        {
            this._hideToolBar_1_flag = AttributeUpdaterFlag.UPDATE
            this._hideToolBar_1_0value = hide
            this._hideToolBar_1_1value = animated
        } else
        {
            this._hideToolBar_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (((this._ignoreLayoutSafeArea_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.UPDATE
            this._ignoreLayoutSafeArea_0_0value = types
            this._ignoreLayoutSafeArea_0_1value = edges
        } else
        {
            this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
