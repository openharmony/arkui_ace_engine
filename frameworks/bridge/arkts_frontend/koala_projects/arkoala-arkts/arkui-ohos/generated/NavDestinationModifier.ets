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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkNavDestinationPeer, NavDestinationMode, NavDestinationContext, NavigationSystemTransitionType, NestedScrollInfo, NavDestinationActiveReason, NavDestinationTransitionDelegate, Orientation, NavDestinationAttribute, NavDestinationCommonTitle, NavDestinationCustomTitle } from './component/navDestination'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback, PixelMap, LayoutSafeAreaType, LayoutSafeAreaEdge } from './component/common'
import { VoidCallback, ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource } from './component/units'
import { SystemBarStyle, NavigationOperation, NavigationTitleOptions, NavigationMenuItem, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions } from './component/navigation'
import { default as window } from '@ohos.window'
import { Scroller } from './component/scroll'
import { CustomBuilder } from './component/builder'
import { Resource as global_resource_Resource } from 'global.resource'
import { default as image } from '@ohos.multimedia.image'
import { SymbolGlyphModifier } from '@arkui.SymbolGlyphModifier'
export class NavDestinationModifier extends CommonMethodModifier implements NavDestinationAttribute,AttributeModifier<NavDestinationAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: NavDestinationAttribute): void { }
    applyPressedAttribute(instance: NavDestinationAttribute): void { }
    applyFocusedAttribute(instance: NavDestinationAttribute): void { }
    applyDisabledAttribute(instance: NavDestinationAttribute): void { }
    applySelectedAttribute(instance: NavDestinationAttribute): void { }
    public _hideTitleBar_0_0value?: boolean | undefined
    public _hideBackButton_0_0value?: boolean | undefined
    public _onShown_0_0value?: (() => void) | undefined
    public _onHidden_0_0value?: (() => void) | undefined
    public _onBackPressed_0_0value?: (() => boolean) | undefined
    public _onResult_0_0value?: arkui_component_common_Callback<Object | null | undefined, void> | undefined
    public _mode_0_0value?: NavDestinationMode | undefined
    public _onReady_0_0value?: arkui_component_common_Callback<NavDestinationContext, void> | undefined
    public _onWillAppear_0_0value?: VoidCallback | undefined
    public _onWillDisappear_0_0value?: VoidCallback | undefined
    public _onWillShow_0_0value?: VoidCallback | undefined
    public _onWillHide_0_0value?: VoidCallback | undefined
    public _systemBarStyle_0_0value?: SystemBarStyle | undefined
    public _recoverable_0_0value?: boolean | undefined
    public _systemTransition_0_0value?: NavigationSystemTransitionType | undefined
    public _bindToScrollable_0_0value?: Array<Scroller> | undefined
    public _bindToNestedScrollable_0_0value?: Array<NestedScrollInfo> | undefined
    public _onActive_0_0value?: arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined
    public _onInactive_0_0value?: arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined
    public _customTransition_0_0value?: NavDestinationTransitionDelegate | undefined
    public _onNewParam_0_0value?: arkui_component_common_Callback<Object | null | undefined, void> | undefined
    public _preferredOrientation_0_0value?: Orientation | undefined
    public _enableNavigationIndicator_0_0value?: boolean | undefined
    public _title_0_0value?: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | global_resource_Resource | undefined
    public _title_0_1value?: NavigationTitleOptions | undefined
    public _hideTitleBar_1_0value?: boolean | undefined
    public _hideTitleBar_1_1value?: boolean | undefined
    public _backButtonIcon_0_0value?: arkui_component_units_ResourceStr | PixelMap | SymbolGlyphModifier | undefined
    public _backButtonIcon_0_1value?: arkui_component_units_ResourceStr | undefined
    public _menus_0_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    public _menus_0_1value?: NavigationMenuOptions | undefined
    public _toolbarConfiguration_0_0value?: Array<ToolbarItem> | CustomBuilder | undefined
    public _toolbarConfiguration_0_1value?: NavigationToolbarOptions | undefined
    public _hideToolBar_0_0value?: boolean | undefined
    public _hideToolBar_0_1value?: boolean | undefined
    public _ignoreLayoutSafeArea_0_0value?: Array<LayoutSafeAreaType> | undefined
    public _ignoreLayoutSafeArea_0_1value?: Array<LayoutSafeAreaEdge> | undefined
    public _enableStatusBar_0_0value?: boolean | undefined
    public _enableStatusBar_0_1value?: boolean | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkNavDestinationPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkNavDestinationPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setHideTitleBar0Attribute((this._hideTitleBar_0_0value as boolean | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setHideTitleBar0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setHideBackButtonAttribute((this._hideBackButton_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setHideBackButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setOnShownAttribute((this._onShown_0_0value as (() => void) | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setOnShownAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setOnHiddenAttribute((this._onHidden_0_0value as (() => void) | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setOnHiddenAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setOnBackPressedAttribute((this._onBackPressed_0_0value as (() => boolean) | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setOnBackPressedAttribute((undefined as (() => boolean) | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setOnResultAttribute((this._onResult_0_0value as arkui_component_common_Callback<Object | null | undefined, void> | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setOnResultAttribute((undefined as arkui_component_common_Callback<Object | null | undefined, void> | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setModeAttribute((this._mode_0_0value as NavDestinationMode | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setModeAttribute((undefined as NavDestinationMode | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnReadyAttribute((this._onReady_0_0value as arkui_component_common_Callback<NavDestinationContext, void> | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnReadyAttribute((undefined as arkui_component_common_Callback<NavDestinationContext, void> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnWillAppearAttribute((this._onWillAppear_0_0value as VoidCallback | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnWillAppearAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOnWillDisappearAttribute((this._onWillDisappear_0_0value as VoidCallback | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOnWillDisappearAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setOnWillShowAttribute((this._onWillShow_0_0value as VoidCallback | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setOnWillShowAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setOnWillHideAttribute((this._onWillHide_0_0value as VoidCallback | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setOnWillHideAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setSystemBarStyleAttribute((this._systemBarStyle_0_0value as SystemBarStyle | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setSystemBarStyleAttribute((undefined as SystemBarStyle | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setRecoverableAttribute((this._recoverable_0_0value as boolean | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setRecoverableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setSystemTransitionAttribute((this._systemTransition_0_0value as NavigationSystemTransitionType | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setSystemTransitionAttribute((undefined as NavigationSystemTransitionType | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setBindToScrollableAttribute((this._bindToScrollable_0_0value as Array<Scroller> | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setBindToScrollableAttribute((undefined as Array<Scroller> | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setBindToNestedScrollableAttribute((this._bindToNestedScrollable_0_0value as Array<NestedScrollInfo> | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setBindToNestedScrollableAttribute((undefined as Array<NestedScrollInfo> | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setOnActiveAttribute((this._onActive_0_0value as arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setOnActiveAttribute((undefined as arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setOnInactiveAttribute((this._onInactive_0_0value as arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setOnInactiveAttribute((undefined as arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setCustomTransitionAttribute((this._customTransition_0_0value as NavDestinationTransitionDelegate | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setCustomTransitionAttribute((undefined as NavDestinationTransitionDelegate | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkNavDestinationPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setOnNewParamAttribute((this._onNewParam_0_0value as arkui_component_common_Callback<Object | null | undefined, void> | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setOnNewParamAttribute((undefined as arkui_component_common_Callback<Object | null | undefined, void> | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setPreferredOrientationAttribute((this._preferredOrientation_0_0value as Orientation | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setPreferredOrientationAttribute((undefined as Orientation | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setEnableNavigationIndicatorAttribute((this._enableNavigationIndicator_0_0value as boolean | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setEnableNavigationIndicatorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setTitleAttribute((this._title_0_0value as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | global_resource_Resource | undefined), (this._title_0_1value as NavigationTitleOptions | undefined | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setTitleAttribute((undefined as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | global_resource_Resource | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setHideTitleBar1Attribute((this._hideTitleBar_1_0value as boolean | undefined), (this._hideTitleBar_1_1value as boolean | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setHideTitleBar1Attribute((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setBackButtonIconAttribute((this._backButtonIcon_0_0value as arkui_component_units_ResourceStr | PixelMap | SymbolGlyphModifier | undefined), (this._backButtonIcon_0_1value as arkui_component_units_ResourceStr | undefined | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setBackButtonIconAttribute((undefined as arkui_component_units_ResourceStr | PixelMap | SymbolGlyphModifier | undefined), (undefined as arkui_component_units_ResourceStr | undefined | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setMenusAttribute((this._menus_0_0value as Array<NavigationMenuItem> | CustomBuilder | undefined), (this._menus_0_1value as NavigationMenuOptions | undefined | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setMenusAttribute((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined), (undefined as NavigationMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setToolbarConfigurationAttribute((this._toolbarConfiguration_0_0value as Array<ToolbarItem> | CustomBuilder | undefined), (this._toolbarConfiguration_0_1value as NavigationToolbarOptions | undefined | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setToolbarConfigurationAttribute((undefined as Array<ToolbarItem> | CustomBuilder | undefined), (undefined as NavigationToolbarOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setHideToolBarAttribute((this._hideToolBar_0_0value as boolean | undefined), (this._hideToolBar_0_1value as boolean | undefined | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setHideToolBarAttribute((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setIgnoreLayoutSafeAreaAttribute((this._ignoreLayoutSafeArea_0_0value as Array<LayoutSafeAreaType> | undefined | undefined), (this._ignoreLayoutSafeArea_0_1value as Array<LayoutSafeAreaEdge> | undefined | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setIgnoreLayoutSafeAreaAttribute((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setEnableStatusBarAttribute((this._enableStatusBar_0_0value as boolean | undefined), (this._enableStatusBar_0_1value as boolean | undefined | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setEnableStatusBarAttribute((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: NavDestinationModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: NavDestinationModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.hideTitleBar(modifier._hideTitleBar_0_0value);
                    break;
                }
                default: {
                    this.hideTitleBar((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.hideBackButton(modifier._hideBackButton_0_0value);
                    break;
                }
                default: {
                    this.hideBackButton((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.onShown(modifier._onShown_0_0value);
                    break;
                }
                default: {
                    this.onShown((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.onHidden(modifier._onHidden_0_0value);
                    break;
                }
                default: {
                    this.onHidden((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.onBackPressed(modifier._onBackPressed_0_0value);
                    break;
                }
                default: {
                    this.onBackPressed((undefined as (() => boolean) | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.onResult(modifier._onResult_0_0value);
                    break;
                }
                default: {
                    this.onResult((undefined as arkui_component_common_Callback<Object | null | undefined, void> | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.mode(modifier._mode_0_0value);
                    break;
                }
                default: {
                    this.mode((undefined as NavDestinationMode | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onReady(modifier._onReady_0_0value);
                    break;
                }
                default: {
                    this.onReady((undefined as arkui_component_common_Callback<NavDestinationContext, void> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onWillAppear(modifier._onWillAppear_0_0value);
                    break;
                }
                default: {
                    this.onWillAppear((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.onWillDisappear(modifier._onWillDisappear_0_0value);
                    break;
                }
                default: {
                    this.onWillDisappear((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.onWillShow(modifier._onWillShow_0_0value);
                    break;
                }
                default: {
                    this.onWillShow((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.onWillHide(modifier._onWillHide_0_0value);
                    break;
                }
                default: {
                    this.onWillHide((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.systemBarStyle(modifier._systemBarStyle_0_0value);
                    break;
                }
                default: {
                    this.systemBarStyle((undefined as SystemBarStyle | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.recoverable(modifier._recoverable_0_0value);
                    break;
                }
                default: {
                    this.recoverable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.systemTransition(modifier._systemTransition_0_0value);
                    break;
                }
                default: {
                    this.systemTransition((undefined as NavigationSystemTransitionType | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.bindToScrollable(modifier._bindToScrollable_0_0value);
                    break;
                }
                default: {
                    this.bindToScrollable((undefined as Array<Scroller> | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.bindToNestedScrollable(modifier._bindToNestedScrollable_0_0value);
                    break;
                }
                default: {
                    this.bindToNestedScrollable((undefined as Array<NestedScrollInfo> | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.onActive(modifier._onActive_0_0value);
                    break;
                }
                default: {
                    this.onActive((undefined as arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.onInactive(modifier._onInactive_0_0value);
                    break;
                }
                default: {
                    this.onInactive((undefined as arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.customTransition(modifier._customTransition_0_0value);
                    break;
                }
                default: {
                    this.customTransition((undefined as NavDestinationTransitionDelegate | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: NavDestinationModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.onNewParam(modifier._onNewParam_0_0value);
                    break;
                }
                default: {
                    this.onNewParam((undefined as arkui_component_common_Callback<Object | null | undefined, void> | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.preferredOrientation(modifier._preferredOrientation_0_0value);
                    break;
                }
                default: {
                    this.preferredOrientation((undefined as Orientation | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.enableNavigationIndicator(modifier._enableNavigationIndicator_0_0value);
                    break;
                }
                default: {
                    this.enableNavigationIndicator((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.title(modifier._title_0_0value, modifier._title_0_1value);
                    break;
                }
                default: {
                    this.title((undefined as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | global_resource_Resource | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.hideTitleBar(modifier._hideTitleBar_1_0value, modifier._hideTitleBar_1_1value);
                    break;
                }
                default: {
                    this.hideTitleBar((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.backButtonIcon(modifier._backButtonIcon_0_0value, modifier._backButtonIcon_0_1value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as arkui_component_units_ResourceStr | PixelMap | SymbolGlyphModifier | undefined), (undefined as arkui_component_units_ResourceStr | undefined | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.menus(modifier._menus_0_0value, modifier._menus_0_1value);
                    break;
                }
                default: {
                    this.menus((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined), (undefined as NavigationMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.toolbarConfiguration(modifier._toolbarConfiguration_0_0value, modifier._toolbarConfiguration_0_1value);
                    break;
                }
                default: {
                    this.toolbarConfiguration((undefined as Array<ToolbarItem> | CustomBuilder | undefined), (undefined as NavigationToolbarOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.hideToolBar(modifier._hideToolBar_0_0value, modifier._hideToolBar_0_1value);
                    break;
                }
                default: {
                    this.hideToolBar((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.ignoreLayoutSafeArea(modifier._ignoreLayoutSafeArea_0_0value, modifier._ignoreLayoutSafeArea_0_1value);
                    break;
                }
                default: {
                    this.ignoreLayoutSafeArea((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
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
        if (((this._flagArray[0]) == (0)) || ((this._hideTitleBar_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._hideTitleBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    hideBackButton(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._hideBackButton_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._hideBackButton_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    onShown(value: (() => void) | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._onShown_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    onHidden(value: (() => void) | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._onHidden_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    onBackPressed(value: (() => boolean) | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._onBackPressed_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    onResult(value: arkui_component_common_Callback<Object | null | undefined, void> | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._onResult_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    mode(value: NavDestinationMode | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._mode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onReady(value: arkui_component_common_Callback<NavDestinationContext, void> | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onReady_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onWillAppear(value: VoidCallback | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onWillAppear_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    onWillDisappear(value: VoidCallback | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._onWillDisappear_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    onWillShow(value: VoidCallback | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._onWillShow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    onWillHide(value: VoidCallback | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._onWillHide_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    systemBarStyle(value: SystemBarStyle | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._systemBarStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    recoverable(value: boolean | undefined): this {
        if (((this._flagArray[13]) == (0)) || ((this._recoverable_0_0value) !== (value))) {
            this._flagArray[13] = 1
            this._recoverable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    systemTransition(value: NavigationSystemTransitionType | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._systemTransition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    bindToScrollable(value: Array<Scroller> | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._bindToScrollable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._bindToNestedScrollable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    onActive(value: arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._onActive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    onInactive(value: arkui_component_common_Callback<NavDestinationActiveReason, void> | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._onInactive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._customTransition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    onNewParam(value: arkui_component_common_Callback<Object | null | undefined, void> | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._onNewParam_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    preferredOrientation(value: Orientation | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._preferredOrientation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    enableNavigationIndicator(value: boolean | undefined): this {
        if (((this._flagArray[22]) == (0)) || ((this._enableNavigationIndicator_0_0value) !== (value))) {
            this._flagArray[22] = 1
            this._enableNavigationIndicator_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | global_resource_Resource | undefined, options?: NavigationTitleOptions): this {
        if (((this._flagArray[23]) == (0)) || (true) || (true)) {
            this._flagArray[23] = 1
            this._title_0_0value = value
            this._title_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        if (((this._flagArray[24]) == (0)) || ((this._hideTitleBar_1_0value) !== (hide)) || ((this._hideTitleBar_1_1value) !== (animated))) {
            this._flagArray[24] = 1
            this._hideTitleBar_1_0value = hide
            this._hideTitleBar_1_1value = animated
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    backButtonIcon(icon: arkui_component_units_ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: arkui_component_units_ResourceStr): this {
        if (((this._flagArray[25]) == (0)) || (true) || (true)) {
            this._flagArray[25] = 1
            this._backButtonIcon_0_0value = icon
            this._backButtonIcon_0_1value = accessibilityText
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (((this._flagArray[26]) == (0)) || (true) || (true)) {
            this._flagArray[26] = 1
            this._menus_0_0value = items
            this._menus_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (((this._flagArray[27]) == (0)) || (true) || (true)) {
            this._flagArray[27] = 1
            this._toolbarConfiguration_0_0value = toolbarParam
            this._toolbarConfiguration_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        if (((this._flagArray[28]) == (0)) || ((this._hideToolBar_0_0value) !== (hide)) || ((this._hideToolBar_0_1value) !== (animated))) {
            this._flagArray[28] = 1
            this._hideToolBar_0_0value = hide
            this._hideToolBar_0_1value = animated
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (((this._flagArray[29]) == (0)) || (true) || (true)) {
            this._flagArray[29] = 1
            this._ignoreLayoutSafeArea_0_0value = types
            this._ignoreLayoutSafeArea_0_1value = edges
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        if (((this._flagArray[30]) == (0)) || ((this._enableStatusBar_0_0value) !== (enabled)) || ((this._enableStatusBar_0_1value) !== (animated))) {
            this._flagArray[30] = 1
            this._enableStatusBar_0_0value = enabled
            this._enableStatusBar_0_1value = animated
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
