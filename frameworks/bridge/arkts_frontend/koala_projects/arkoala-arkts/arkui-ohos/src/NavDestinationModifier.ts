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

import { AttributeModifier, CommonMethod, LayoutSafeAreaType, LayoutSafeAreaEdge, CustomBuilder, Callback } from "arkui/component/common"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { NavDestinationMode, NavDestinationContext, NavigationSystemTransitionType, NestedScrollInfo, NavDestinationActiveReason, NavDestinationTransitionDelegate, Orientation, NavDestinationAttribute, NavDestinationCommonTitle, NavDestinationCustomTitle, ArkNavDestinationPeer } from "arkui/component/navDestination"
import { ResourceStr } from "arkui/component/units"
import { Resource } from "global.resource"
import { PixelMap } from '#external';
import { NavigationMenuItem, NavigationOperation, NavigationTitleOptions, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions } from "arkui/component/navigation"
import { Scroller } from "arkui/component/scroll"
import { SystemBarStyle } from "./component/arkui-custom"
import { SymbolGlyphModifier } from "./SymbolGlyphModifier"
import { PeerNode } from './PeerNode'

export class NavDestinationModifier extends CommonMethodModifier implements NavDestinationAttribute,AttributeModifier<NavDestinationAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: NavDestinationAttribute): void { }
    applyPressedAttribute(instance: NavDestinationAttribute): void { }
    applyFocusedAttribute(instance: NavDestinationAttribute): void { }
    applyDisabledAttribute(instance: NavDestinationAttribute): void { }
    applySelectedAttribute(instance: NavDestinationAttribute): void { }
    _hideTitleBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_0_0value?: boolean | undefined
    _hideBackButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideBackButton_0_0value?: boolean | undefined
    _onShown_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onShown_0_0value?: (() => void) | undefined
    _onHidden_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHidden_0_0value?: (() => void) | undefined
    _onBackPressed_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onBackPressed_0_0value?: (() => boolean) | undefined
    _onResult_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onResult_0_0value?: ((value0: Object | undefined) => void) | undefined
    _mode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mode_0_0value?: NavDestinationMode | undefined
    _backButtonIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backButtonIcon_0_0value?: ResourceStr | PixelMap | SymbolGlyphModifier | undefined
    _menus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menus_0_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _onReady_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReady_0_0value?: ((value0: NavDestinationContext) => void) | undefined
    _onWillAppear_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillAppear_0_0value?: (() => void) | undefined
    _onWillDisappear_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillDisappear_0_0value?: (() => void) | undefined
    _onWillShow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillShow_0_0value?: (() => void) | undefined
    _onWillHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillHide_0_0value?: (() => void) | undefined
    _systemBarStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _systemBarStyle_0_0value?: SystemBarStyle | undefined
    _recoverable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _recoverable_0_0value?: boolean | undefined
    _systemTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _systemTransition_0_0value?: NavigationSystemTransitionType | undefined
    _bindToScrollable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindToScrollable_0_0value?: Array<Scroller> | undefined
    _bindToNestedScrollable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindToNestedScrollable_0_0value?: Array<NestedScrollInfo> | undefined
    _onActive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onActive_0_0value?: ((value0: NavDestinationActiveReason) => void) | undefined
    _onInactive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInactive_0_0value?: ((value0: NavDestinationActiveReason) => void) | undefined
    _customTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customTransition_0_0value?: NavDestinationTransitionDelegate | undefined
    _onNewParam_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNewParam_0_0value?: ((value0: Object | null | undefined) => void) | undefined
    _preferredOrientation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _preferredOrientation_0_0value?: Orientation | undefined
    _enableNavigationIndicator_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNavigationIndicator_0_0value?: boolean | undefined
    _title_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _title_0_0value?: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined
    _title_0_1value?: NavigationTitleOptions | undefined
    _hideTitleBar_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_1_0value?: boolean | undefined
    _hideTitleBar_1_1value?: boolean | undefined
    _backButtonIcon_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backButtonIcon_1_0value?: ResourceStr | PixelMap | SymbolGlyphModifier | undefined
    _backButtonIcon_1_1value?: ResourceStr | undefined
    _menus_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menus_1_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _menus_1_1value?: NavigationMenuOptions | undefined
    _toolbarConfiguration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _toolbarConfiguration_0_0value?: Array<ToolbarItem> | CustomBuilder | undefined
    _toolbarConfiguration_0_1value?: NavigationToolbarOptions | undefined
    _hideToolBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideToolBar_0_0value?: boolean | undefined
    _hideToolBar_0_1value?: boolean | undefined
    _ignoreLayoutSafeArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _ignoreLayoutSafeArea_0_0value?: Array<LayoutSafeAreaType> | undefined
    _ignoreLayoutSafeArea_0_1value?: Array<LayoutSafeAreaEdge> | undefined
    _enableStatusBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableStatusBar_0_0value?: boolean | undefined
    _enableStatusBar_0_1value?: boolean | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkNavDestinationPeer
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
        
        if (this._mode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.modeAttribute((this._mode_0_0value as NavDestinationMode | undefined));
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.modeAttribute((undefined as NavDestinationMode | undefined));
                }
            }
        }
        if (this._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.backButtonIcon0Attribute((this._backButtonIcon_0_0value as ResourceStr | PixelMap | SymbolGlyphModifier | undefined));
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.backButtonIcon0Attribute((undefined as ResourceStr | PixelMap | SymbolGlyphModifier | undefined));
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
        if (this._systemTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._systemTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.systemTransitionAttribute((this._systemTransition_0_0value as NavigationSystemTransitionType | undefined));
                    this._systemTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._systemTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._systemTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.systemTransitionAttribute((undefined as NavigationSystemTransitionType | undefined));
                }
            }
        }
        if (this._bindToScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindToScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.bindToScrollableAttribute((this._bindToScrollable_0_0value as Array<Scroller> | undefined));
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.bindToScrollableAttribute((undefined as Array<Scroller> | undefined));
                }
            }
        }
        if (this._bindToNestedScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindToNestedScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.bindToNestedScrollableAttribute((this._bindToNestedScrollable_0_0value as Array<NestedScrollInfo> | undefined));
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.bindToNestedScrollableAttribute((undefined as Array<NestedScrollInfo> | undefined));
                }
            }
        }
        if (this._customTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.customTransitionAttribute((this._customTransition_0_0value as NavDestinationTransitionDelegate | undefined));
                    this._customTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.customTransitionAttribute((undefined as NavDestinationTransitionDelegate | undefined));
                }
            }
        }
        if (this._preferredOrientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._preferredOrientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.preferredOrientationAttribute((this._preferredOrientation_0_0value as Orientation | undefined));
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.preferredOrientationAttribute((undefined as Orientation | undefined));
                }
            }
        }
        if (this._enableNavigationIndicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNavigationIndicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableNavigationIndicatorAttribute((this._enableNavigationIndicator_0_0value as boolean | undefined));
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableNavigationIndicatorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._title_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._title_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.titleAttribute((this._title_0_0value as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (this._title_0_1value as NavigationTitleOptions | undefined));
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._title_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.titleAttribute((undefined as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
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
        if (this._backButtonIcon_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backButtonIcon_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.backButtonIcon1Attribute((this._backButtonIcon_1_0value as ResourceStr | PixelMap | SymbolGlyphModifier | undefined), (this._backButtonIcon_1_1value as ResourceStr | undefined));
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.backButtonIcon1Attribute((undefined as ResourceStr | PixelMap | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
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
        if (this._hideToolBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideToolBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.hideToolBarAttribute((this._hideToolBar_0_0value as boolean | undefined), (this._hideToolBar_0_1value as boolean | undefined));
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.hideToolBarAttribute((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
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
        if (this._enableStatusBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableStatusBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableStatusBarAttribute((this._enableStatusBar_0_0value as boolean | undefined), (this._enableStatusBar_0_1value as boolean | undefined));
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableStatusBarAttribute((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof NavDestinationModifier)) {
            return;
        }
        const modifier = value as NavDestinationModifier;

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
        if (modifier._mode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mode(modifier._mode_0_0value);
                    break;
                }
                default: {
                    this.mode((undefined as NavDestinationMode | undefined));
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
                    this.backButtonIcon((undefined as ResourceStr | PixelMap | SymbolGlyphModifier | undefined));
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
        if (modifier._systemTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._systemTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.systemTransition(modifier._systemTransition_0_0value);
                    break;
                }
                default: {
                    this.systemTransition((undefined as NavigationSystemTransitionType | undefined));
                }
            }
        }
        if (modifier._bindToScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindToScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindToScrollable(modifier._bindToScrollable_0_0value);
                    break;
                }
                default: {
                    this.bindToScrollable((undefined as Array<Scroller> | undefined));
                }
            }
        }
        if (modifier._bindToNestedScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindToNestedScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindToNestedScrollable(modifier._bindToNestedScrollable_0_0value);
                    break;
                }
                default: {
                    this.bindToNestedScrollable((undefined as Array<NestedScrollInfo> | undefined));
                }
            }
        }
        if (modifier._customTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customTransition(modifier._customTransition_0_0value);
                    break;
                }
                default: {
                    this.customTransition((undefined as NavDestinationTransitionDelegate | undefined));
                }
            }
        }
        if (modifier._preferredOrientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._preferredOrientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.preferredOrientation(modifier._preferredOrientation_0_0value);
                    break;
                }
                default: {
                    this.preferredOrientation((undefined as Orientation | undefined));
                }
            }
        }
        if (modifier._enableNavigationIndicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableNavigationIndicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableNavigationIndicator(modifier._enableNavigationIndicator_0_0value);
                    break;
                }
                default: {
                    this.enableNavigationIndicator((undefined as boolean | undefined));
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
                    this.title((undefined as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
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
        if (modifier._backButtonIcon_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backButtonIcon_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backButtonIcon(modifier._backButtonIcon_1_0value, modifier._backButtonIcon_1_1value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as ResourceStr | PixelMap | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
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
        if (modifier._hideToolBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideToolBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideToolBar(modifier._hideToolBar_0_0value, modifier._hideToolBar_0_1value);
                    break;
                }
                default: {
                    this.hideToolBar((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
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
        if (modifier._enableStatusBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableStatusBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableStatusBar(modifier._enableStatusBar_0_0value, modifier._enableStatusBar_0_1value);
                    break;
                }
                default: {
                    this.enableStatusBar((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
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
    mode(value: NavDestinationMode | undefined): this {
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
    backButtonIcon(value: ResourceStr | PixelMap | SymbolGlyphModifier | undefined): this {
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
    systemTransition(value: NavigationSystemTransitionType | undefined): this {
        if (((this._systemTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._systemTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._systemTransition_0_0value = value
        } else
        {
            this._systemTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindToScrollable(value: Array<Scroller> | undefined): this {
        if (((this._bindToScrollable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._bindToScrollable_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindToScrollable_0_0value = value
        } else
        {
            this._bindToScrollable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        if (((this._bindToNestedScrollable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindToNestedScrollable_0_0value = value
        } else
        {
            this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    
    customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        if (((this._customTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._customTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._customTransition_0_0value = value
        } else
        {
            this._customTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    preferredOrientation(value: Orientation | undefined): this {
        if (((this._preferredOrientation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._preferredOrientation_0_flag = AttributeUpdaterFlag.UPDATE
            this._preferredOrientation_0_0value = value
        } else
        {
            this._preferredOrientation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableNavigationIndicator(value: boolean | undefined): this {
        if (((this._enableNavigationIndicator_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableNavigationIndicator_0_0value) !== (value)))
        {
            this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableNavigationIndicator_0_0value = value
        } else
        {
            this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this {
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
    backButtonIcon(icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
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
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (((this._toolbarConfiguration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.UPDATE
            this._toolbarConfiguration_0_0value = toolbarParam
            this._toolbarConfiguration_0_1value = options
        } else
        {
            this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        if (((this._hideToolBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideToolBar_0_0value) !== (hide)) || ((this._hideToolBar_0_1value) !== (animated)))
        {
            this._hideToolBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._hideToolBar_0_0value = hide
            this._hideToolBar_0_1value = animated
        } else
        {
            this._hideToolBar_0_flag = AttributeUpdaterFlag.SKIP
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
    enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        if (((this._enableStatusBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableStatusBar_0_0value) !== (enabled)) || ((this._enableStatusBar_0_1value) !== (animated)))
        {
            this._enableStatusBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableStatusBar_0_0value = enabled
            this._enableStatusBar_0_1value = animated
        } else
        {
            this._enableStatusBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    onWillAppear(value: Callback<void> | undefined): this {
        throw new Error("Not implemented")
    }
    onReady(value: ((value0: NavDestinationContext) => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onShown(value: (() => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onHidden(value: (() => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onBackPressed(value: (() => boolean) | undefined): this {
        throw new Error("Not implemented")
    }
    onResult(value: ((value0: Object) => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onWillDisappear(value: Callback<void> | undefined): this {
        throw new Error("Not implemented")
    }
    onWillShow(value: Callback<void> | undefined): this {
        throw new Error("Not implemented")
    }
    onWillHide(value: Callback<void> | undefined): this {
        throw new Error("Not implemented")
    }
    onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onNewParam(value: ((value0: Object | null | undefined) => void) | undefined): this {
        throw new Error("Not implemented")
    }
}
