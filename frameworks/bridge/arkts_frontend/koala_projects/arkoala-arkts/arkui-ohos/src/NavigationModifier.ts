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

import { AttributeModifier, CommonMethod, Bindable, LayoutSafeAreaType, LayoutSafeAreaEdge, CustomBuilder } from "arkui/component/common"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Length, Dimension, ResourceStr } from "arkui/component/units"
import { Resource } from "global.resource"
import { NavBarPosition, NavigationMode, NavigationTitleMode, NavigationMenuItem, NavContentInfo, NavigationOperation, NavigationAnimatedTransition, NavigationAttribute, NavigationCommonTitle, NavigationCustomTitle, NavigationTitleOptions, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions, ArkNavigationPeer } from "arkui/component/navigation"
import { PixelMap } from '#external';
import { SymbolGlyphModifier } from "./SymbolGlyphModifier"
import { PeerNode } from './PeerNode'
import { SystemBarStyle } from "./component/arkui-custom"

export class NavigationModifier extends CommonMethodModifier implements NavigationAttribute,AttributeModifier<NavigationAttribute> {
    _instanceId: number = -1;
    instanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
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
    _backButtonIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backButtonIcon_0_0value?: string | PixelMap | Resource | SymbolGlyphModifier | undefined
    _hideNavBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideNavBar_0_0value?: boolean | undefined
    _hideTitleBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_0_0value?: boolean | undefined
    _hideBackButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideBackButton_0_0value?: boolean | undefined
    _titleMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _titleMode_0_0value?: NavigationTitleMode | undefined
    _menus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menus_0_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
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
    _systemBarStyle_0_0value?: SystemBarStyle | undefined
    _recoverable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _recoverable_0_0value?: boolean | undefined
    _enableDragBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableDragBar_0_0value?: boolean | undefined
    _enableModeChangeAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableModeChangeAnimation_0_0value?: boolean | undefined
    _backButtonIcon_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backButtonIcon_1_0value?: string | PixelMap | Resource | SymbolGlyphModifier | undefined
    _backButtonIcon_1_1value?: ResourceStr | undefined
    _title_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _title_0_0value?: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined
    _title_0_1value?: NavigationTitleOptions | undefined
    _hideTitleBar_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_1_0value?: boolean | undefined
    _hideTitleBar_1_1value?: boolean | undefined
    _menus_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menus_1_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _menus_1_1value?: NavigationMenuOptions | undefined
    _toolbarConfiguration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _toolbarConfiguration_0_0value?: Array<ToolbarItem> | CustomBuilder | undefined
    _toolbarConfiguration_0_1value?: NavigationToolbarOptions | undefined
    _hideToolBar_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideToolBar_1_0value?: boolean | undefined
    _hideToolBar_1_1value?: boolean | undefined
    _toolBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _toolBar_0_0value: CustomBuilder | undefined
    _ignoreLayoutSafeArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _ignoreLayoutSafeArea_0_0value?: Array<LayoutSafeAreaType> | undefined
    _ignoreLayoutSafeArea_0_1value?: Array<LayoutSafeAreaEdge> | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkNavigationPeer
        if (this._navBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._navBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.navBarWidthAttribute((this._navBarWidth_0_0value as Length | undefined));
                    this._navBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._navBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._navBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.navBarWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._navBarPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._navBarPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.navBarPositionAttribute((this._navBarPosition_0_0value as NavBarPosition | undefined));
                    this._navBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._navBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._navBarPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.navBarPositionAttribute((undefined as NavBarPosition | undefined));
                }
            }
        }
        if (this._navBarWidthRange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._navBarWidthRange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.navBarWidthRangeAttribute((this._navBarWidthRange_0_0value as [ Dimension, Dimension ] | undefined));
                    this._navBarWidthRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._navBarWidthRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._navBarWidthRange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.navBarWidthRangeAttribute((undefined as [ Dimension, Dimension ] | undefined));
                }
            }
        }
        if (this._minContentWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minContentWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minContentWidthAttribute((this._minContentWidth_0_0value as Dimension | undefined));
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minContentWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._mode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.modeAttribute((this._mode_0_0value as NavigationMode | undefined));
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.modeAttribute((undefined as NavigationMode | undefined));
                }
            }
        }
        if (this._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.backButtonIcon0Attribute((this._backButtonIcon_0_0value as string | PixelMap | Resource | SymbolGlyphModifier | undefined));
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.backButtonIcon0Attribute((undefined as string | PixelMap | Resource | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (this._hideNavBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideNavBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.hideNavBarAttribute((this._hideNavBar_0_0value as boolean | undefined));
                    this._hideNavBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideNavBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideNavBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.hideNavBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._hideTitleBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideTitleBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.hideTitleBar0Attribute((this._hideTitleBar_0_0value as boolean | undefined));
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.hideTitleBar0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._hideBackButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideBackButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.hideBackButtonAttribute((this._hideBackButton_0_0value as boolean | undefined));
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.hideBackButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._titleMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._titleMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.titleModeAttribute((this._titleMode_0_0value as NavigationTitleMode | undefined));
                    this._titleMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._titleMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._titleMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.titleModeAttribute((undefined as NavigationTitleMode | undefined));
                }
            }
        }
        if (this._menus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.menus0Attribute((this._menus_0_0value as Array<NavigationMenuItem> | CustomBuilder | undefined));
                    this._menus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.menus0Attribute((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined));
                }
            }
        }
        if (this._hideToolBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideToolBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.hideToolBar0Attribute((this._hideToolBar_0_0value as boolean | undefined));
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.hideToolBar0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableToolBarAdaptation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableToolBarAdaptation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableToolBarAdaptationAttribute((this._enableToolBarAdaptation_0_0value as boolean | undefined));
                    this._enableToolBarAdaptation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableToolBarAdaptation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableToolBarAdaptation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableToolBarAdaptationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._systemBarStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._systemBarStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.systemBarStyleAttribute((this._systemBarStyle_0_0value as SystemBarStyle | undefined));
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.systemBarStyleAttribute((undefined as SystemBarStyle | undefined));
                }
            }
        }
        if (this._recoverable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._recoverable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.recoverableAttribute((this._recoverable_0_0value as boolean | undefined));
                    this._recoverable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._recoverable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._recoverable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.recoverableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableDragBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableDragBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableDragBarAttribute((this._enableDragBar_0_0value as boolean | undefined));
                    this._enableDragBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableDragBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableDragBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableDragBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableModeChangeAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableModeChangeAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableModeChangeAnimationAttribute((this._enableModeChangeAnimation_0_0value as boolean | undefined));
                    this._enableModeChangeAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableModeChangeAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableModeChangeAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableModeChangeAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._backButtonIcon_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backButtonIcon_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.backButtonIcon1Attribute((this._backButtonIcon_1_0value as string | PixelMap | Resource | SymbolGlyphModifier | undefined), (this._backButtonIcon_1_1value as ResourceStr | undefined));
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.backButtonIcon1Attribute((undefined as string | PixelMap | Resource | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
        if (this._title_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._title_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.titleAttribute((this._title_0_0value as ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (this._title_0_1value as NavigationTitleOptions | undefined));
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._title_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.titleAttribute((undefined as ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (this._hideTitleBar_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideTitleBar_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.hideTitleBar1Attribute((this._hideTitleBar_1_0value as boolean | undefined), (this._hideTitleBar_1_1value as boolean | undefined));
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.hideTitleBar1Attribute((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._menus_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menus_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.menus1Attribute((this._menus_1_0value as Array<NavigationMenuItem> | CustomBuilder | undefined), (this._menus_1_1value as NavigationMenuOptions | undefined));
                    this._menus_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menus_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menus_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.menus1Attribute((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined), (undefined as NavigationMenuOptions | undefined | undefined));
                }
            }
        }
        if (this._toolbarConfiguration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._toolbarConfiguration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.toolbarConfigurationAttribute((this._toolbarConfiguration_0_0value as Array<ToolbarItem> | CustomBuilder | undefined), (this._toolbarConfiguration_0_1value as NavigationToolbarOptions | undefined));
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.toolbarConfigurationAttribute((undefined as Array<ToolbarItem> | CustomBuilder | undefined), (undefined as NavigationToolbarOptions | undefined | undefined));
                }
            }
        }
        if (this._hideToolBar_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideToolBar_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.hideToolBar1Attribute((this._hideToolBar_1_0value as boolean | undefined), (this._hideToolBar_1_1value as boolean | undefined));
                    this._hideToolBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideToolBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideToolBar_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.hideToolBar1Attribute((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._ignoreLayoutSafeArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._ignoreLayoutSafeArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.ignoreLayoutSafeAreaAttribute((this._ignoreLayoutSafeArea_0_0value as Array<LayoutSafeAreaType> | undefined), (this._ignoreLayoutSafeArea_0_1value as Array<LayoutSafeAreaEdge> | undefined));
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.ignoreLayoutSafeAreaAttribute((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof NavigationModifier)) {
            return;
        }
        const modifier = value as NavigationModifier;
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
        if (modifier._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backButtonIcon(modifier._backButtonIcon_0_0value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as string | PixelMap | Resource | SymbolGlyphModifier | undefined));
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
        if (modifier._menus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menus(modifier._menus_0_0value);
                    break;
                }
                default: {
                    this.menus((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined));
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
        if (modifier._systemBarStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._systemBarStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.systemBarStyle(modifier._systemBarStyle_0_0value);
                    break;
                }
                default: {
                    this.systemBarStyle((undefined as SystemBarStyle | undefined));
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
        if (modifier._backButtonIcon_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backButtonIcon_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backButtonIcon(modifier._backButtonIcon_1_0value, modifier._backButtonIcon_1_1value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as string | PixelMap | Resource | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
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
        if (modifier._menus_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menus_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menus(modifier._menus_1_0value, modifier._menus_1_1value);
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
    toolBar(value: CustomBuilder | undefined): this {
        throw new Error("Not implemented")
    }
    backButtonIcon(value: string | PixelMap | Resource | SymbolGlyphModifier | undefined): this {
        if (((this._backButtonIcon_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backButtonIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._backButtonIcon_0_0value = value
        } else
        {
            this._backButtonIcon_0_flag = AttributeUpdaterFlag.SKIP
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
    menus(value: Array<NavigationMenuItem> | CustomBuilder | undefined): this {
        if (((this._menus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menus_0_flag = AttributeUpdaterFlag.UPDATE
            this._menus_0_0value = value
        } else
        {
            this._menus_0_flag = AttributeUpdaterFlag.SKIP
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

    systemBarStyle(value: SystemBarStyle | undefined): this {
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
    backButtonIcon(icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (((this._backButtonIcon_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._backButtonIcon_1_flag = AttributeUpdaterFlag.UPDATE
            this._backButtonIcon_1_0value = icon
            this._backButtonIcon_1_1value = accessibilityText
        } else
        {
            this._backButtonIcon_1_flag = AttributeUpdaterFlag.SKIP
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
        if (((this._menus_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._menus_1_flag = AttributeUpdaterFlag.UPDATE
            this._menus_1_0value = items
            this._menus_1_1value = options
        } else
        {
            this._menus_1_flag = AttributeUpdaterFlag.SKIP
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
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        throw new Error("Not implemented")
    }
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        throw new Error("Not implemented")
    }
    subTitle(value: string | undefined): this {
        throw new Error("Not implemented")
    }
    navDestination(
        /** @memo */
        value: ((name: string,param: Object | null | undefined) => void) | undefined): this {
        throw new Error("Not implemented")
    }
}
