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
import { AttributeModifier, extractors, hookSetNavDestination } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkNavigationPeer, NavBarPosition, NavigationMode, NavigationTitleMode, NavContentInfo, NavigationOperation, NavigationAnimatedTransition, SystemBarStyle, NavigationAttribute, NavigationCommonTitle, NavigationCustomTitle, NavigationTitleOptions, NavigationMenuItem, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions } from './component/navigation'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable, PixelMap, LayoutSafeAreaType, LayoutSafeAreaEdge } from './component/common'
import { Length, Resource as arkui_component_units_Resource, Dimension, ResourceStr as arkui_component_units_ResourceStr } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { PageMapBuilder, CustomBuilder } from './component/builder'
import { default as window } from '@ohos.window'
import { default as image } from '@ohos.multimedia.image'
import { SymbolGlyphModifier } from '@arkui.SymbolGlyphModifier'
export class NavigationModifier extends CommonMethodModifier implements NavigationAttribute,AttributeModifier<NavigationAttribute> {
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
    applyNormalAttribute(instance: NavigationAttribute): void { }
    applyPressedAttribute(instance: NavigationAttribute): void { }
    applyFocusedAttribute(instance: NavigationAttribute): void { }
    applyDisabledAttribute(instance: NavigationAttribute): void { }
    applySelectedAttribute(instance: NavigationAttribute): void { }
    public _navBarWidth_0_0value?: Length | Bindable<Length> | undefined
    public _navBarPosition_0_0value?: NavBarPosition | undefined
    public _navBarWidthRange_0_0value?: [ Dimension, Dimension ] | undefined
    public _minContentWidth_0_0value?: Dimension | undefined
    public _mode_0_0value?: NavigationMode | undefined
    public _hideNavBar_0_0value?: boolean | undefined
    public _hideTitleBar_0_0value?: boolean | undefined
    public _hideBackButton_0_0value?: boolean | undefined
    public _titleMode_0_0value?: NavigationTitleMode | undefined
    public _hideToolBar_0_0value?: boolean | undefined
    public _enableToolBarAdaptation_0_0value?: boolean | undefined
    public _onTitleModeChange_0_0value?: ((titleMode: NavigationTitleMode) => void) | undefined
    public _onNavBarStateChange_0_0value?: ((isSelected: boolean) => void) | undefined
    public _onNavigationModeChange_0_0value?: ((mode: NavigationMode) => void) | undefined
    public _navDestination_0_0value?: PageMapBuilder | undefined
    public _customNavContentTransition_0_0value?: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined
    public _systemBarStyle_0_0value?: SystemBarStyle | undefined
    public _recoverable_0_0value?: boolean | undefined
    public _enableDragBar_0_0value?: boolean | undefined
    public _enableModeChangeAnimation_0_0value?: boolean | undefined
    public _backButtonIcon_0_0value?: string | PixelMap | global_resource_Resource | SymbolGlyphModifier | undefined
    public _backButtonIcon_0_1value?: arkui_component_units_ResourceStr | undefined
    public _title_0_0value?: arkui_component_units_ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined
    public _title_0_1value?: NavigationTitleOptions | undefined
    public _hideTitleBar_1_0value?: boolean | undefined
    public _hideTitleBar_1_1value?: boolean | undefined
    public _menus_0_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    public _menus_0_1value?: NavigationMenuOptions | undefined
    public _toolbarConfiguration_0_0value?: Array<ToolbarItem> | CustomBuilder | undefined
    public _toolbarConfiguration_0_1value?: NavigationToolbarOptions | undefined
    public _hideToolBar_1_0value?: boolean | undefined
    public _hideToolBar_1_1value?: boolean | undefined
    public _ignoreLayoutSafeArea_0_0value?: Array<LayoutSafeAreaType> | undefined
    public _ignoreLayoutSafeArea_0_1value?: Array<LayoutSafeAreaEdge> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkNavigationPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkNavigationPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setNavBarWidthAttribute((this._navBarWidth_0_0value as Length | Bindable<Length> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setNavBarWidthAttribute((undefined as Length | Bindable<Length> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setNavBarPositionAttribute((this._navBarPosition_0_0value as NavBarPosition | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setNavBarPositionAttribute((undefined as NavBarPosition | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setNavBarWidthRangeAttribute((this._navBarWidthRange_0_0value as [ Dimension, Dimension ] | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setNavBarWidthRangeAttribute((undefined as [ Dimension, Dimension ] | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setMinContentWidthAttribute((this._minContentWidth_0_0value as Dimension | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setMinContentWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setModeAttribute((this._mode_0_0value as NavigationMode | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setModeAttribute((undefined as NavigationMode | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setHideNavBarAttribute((this._hideNavBar_0_0value as boolean | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setHideNavBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setHideTitleBar0Attribute((this._hideTitleBar_0_0value as boolean | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setHideTitleBar0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setHideBackButtonAttribute((this._hideBackButton_0_0value as boolean | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setHideBackButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setTitleModeAttribute((this._titleMode_0_0value as NavigationTitleMode | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setTitleModeAttribute((undefined as NavigationTitleMode | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setHideToolBar0Attribute((this._hideToolBar_0_0value as boolean | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setHideToolBar0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setEnableToolBarAdaptationAttribute((this._enableToolBarAdaptation_0_0value as boolean | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setEnableToolBarAdaptationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setOnTitleModeChangeAttribute((this._onTitleModeChange_0_0value as ((titleMode: NavigationTitleMode) => void) | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setOnTitleModeChangeAttribute((undefined as ((titleMode: NavigationTitleMode) => void) | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setOnNavBarStateChangeAttribute((this._onNavBarStateChange_0_0value as ((isSelected: boolean) => void) | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setOnNavBarStateChangeAttribute((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setOnNavigationModeChangeAttribute((this._onNavigationModeChange_0_0value as ((mode: NavigationMode) => void) | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setOnNavigationModeChangeAttribute((undefined as ((mode: NavigationMode) => void) | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    hookSetNavDestination(peer, (this._navDestination_0_0value as PageMapBuilder | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    hookSetNavDestination(peer, (undefined as PageMapBuilder | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setCustomNavContentTransitionAttribute((this._customNavContentTransition_0_0value as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setCustomNavContentTransitionAttribute((undefined as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setSystemBarStyleAttribute((this._systemBarStyle_0_0value as SystemBarStyle | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setSystemBarStyleAttribute((undefined as SystemBarStyle | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setRecoverableAttribute((this._recoverable_0_0value as boolean | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setRecoverableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setEnableDragBarAttribute((this._enableDragBar_0_0value as boolean | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setEnableDragBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setEnableModeChangeAnimationAttribute((this._enableModeChangeAnimation_0_0value as boolean | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setEnableModeChangeAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkNavigationPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setBackButtonIconAttribute((this._backButtonIcon_0_0value as string | PixelMap | global_resource_Resource | SymbolGlyphModifier | undefined), (this._backButtonIcon_0_1value as arkui_component_units_ResourceStr | undefined | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setBackButtonIconAttribute((undefined as string | PixelMap | global_resource_Resource | SymbolGlyphModifier | undefined), (undefined as arkui_component_units_ResourceStr | undefined | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setTitleAttribute((this._title_0_0value as arkui_component_units_ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (this._title_0_1value as NavigationTitleOptions | undefined | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setTitleAttribute((undefined as arkui_component_units_ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setHideTitleBar1Attribute((this._hideTitleBar_1_0value as boolean | undefined), (this._hideTitleBar_1_1value as boolean | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setHideTitleBar1Attribute((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setMenusAttribute((this._menus_0_0value as Array<NavigationMenuItem> | CustomBuilder | undefined), (this._menus_0_1value as NavigationMenuOptions | undefined | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setMenusAttribute((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined), (undefined as NavigationMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setToolbarConfigurationAttribute((this._toolbarConfiguration_0_0value as Array<ToolbarItem> | CustomBuilder | undefined), (this._toolbarConfiguration_0_1value as NavigationToolbarOptions | undefined | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setToolbarConfigurationAttribute((undefined as Array<ToolbarItem> | CustomBuilder | undefined), (undefined as NavigationToolbarOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setHideToolBar1Attribute((this._hideToolBar_1_0value as boolean | undefined), (this._hideToolBar_1_1value as boolean | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setHideToolBar1Attribute((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setIgnoreLayoutSafeAreaAttribute((this._ignoreLayoutSafeArea_0_0value as Array<LayoutSafeAreaType> | undefined | undefined), (this._ignoreLayoutSafeArea_0_1value as Array<LayoutSafeAreaEdge> | undefined | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setIgnoreLayoutSafeAreaAttribute((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: NavigationModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: NavigationModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.navBarWidth(modifier._navBarWidth_0_0value);
                    break;
                }
                default: {
                    this.navBarWidth((undefined as Length | Bindable<Length> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.navBarPosition(modifier._navBarPosition_0_0value);
                    break;
                }
                default: {
                    this.navBarPosition((undefined as NavBarPosition | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.navBarWidthRange(modifier._navBarWidthRange_0_0value);
                    break;
                }
                default: {
                    this.navBarWidthRange((undefined as [ Dimension, Dimension ] | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.minContentWidth(modifier._minContentWidth_0_0value);
                    break;
                }
                default: {
                    this.minContentWidth((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.mode(modifier._mode_0_0value);
                    break;
                }
                default: {
                    this.mode((undefined as NavigationMode | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.hideNavBar(modifier._hideNavBar_0_0value);
                    break;
                }
                default: {
                    this.hideNavBar((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
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
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
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
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.titleMode(modifier._titleMode_0_0value);
                    break;
                }
                default: {
                    this.titleMode((undefined as NavigationTitleMode | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.hideToolBar(modifier._hideToolBar_0_0value);
                    break;
                }
                default: {
                    this.hideToolBar((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.enableToolBarAdaptation(modifier._enableToolBarAdaptation_0_0value);
                    break;
                }
                default: {
                    this.enableToolBarAdaptation((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.onTitleModeChange(modifier._onTitleModeChange_0_0value);
                    break;
                }
                default: {
                    this.onTitleModeChange((undefined as ((titleMode: NavigationTitleMode) => void) | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.onNavBarStateChange(modifier._onNavBarStateChange_0_0value);
                    break;
                }
                default: {
                    this.onNavBarStateChange((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.onNavigationModeChange(modifier._onNavigationModeChange_0_0value);
                    break;
                }
                default: {
                    this.onNavigationModeChange((undefined as ((mode: NavigationMode) => void) | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.navDestination(modifier._navDestination_0_0value);
                    break;
                }
                default: {
                    this.navDestination((undefined as PageMapBuilder | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.customNavContentTransition(modifier._customNavContentTransition_0_0value);
                    break;
                }
                default: {
                    this.customNavContentTransition((undefined as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
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
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
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
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.enableDragBar(modifier._enableDragBar_0_0value);
                    break;
                }
                default: {
                    this.enableDragBar((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.enableModeChangeAnimation(modifier._enableModeChangeAnimation_0_0value);
                    break;
                }
                default: {
                    this.enableModeChangeAnimation((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: NavigationModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.backButtonIcon(modifier._backButtonIcon_0_0value, modifier._backButtonIcon_0_1value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as string | PixelMap | global_resource_Resource | SymbolGlyphModifier | undefined), (undefined as arkui_component_units_ResourceStr | undefined | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.title(modifier._title_0_0value, modifier._title_0_1value);
                    break;
                }
                default: {
                    this.title((undefined as arkui_component_units_ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
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
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
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
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
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
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.hideToolBar(modifier._hideToolBar_1_0value, modifier._hideToolBar_1_1value);
                    break;
                }
                default: {
                    this.hideToolBar((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
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
    }
    navBarWidth(value: Length | Bindable<Length> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._navBarWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    navBarPosition(value: NavBarPosition | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._navBarPosition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._navBarWidthRange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    minContentWidth(value: Dimension | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._minContentWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    mode(value: NavigationMode | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._mode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    hideNavBar(value: boolean | undefined): this {
        if (((this._flagArray[5]) == (0)) || ((this._hideNavBar_0_0value) !== (value))) {
            this._flagArray[5] = 1
            this._hideNavBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    hideTitleBar(value: boolean | undefined): this {
        if (((this._flagArray[6]) == (0)) || ((this._hideTitleBar_0_0value) !== (value))) {
            this._flagArray[6] = 1
            this._hideTitleBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    hideBackButton(value: boolean | undefined): this {
        if (((this._flagArray[7]) == (0)) || ((this._hideBackButton_0_0value) !== (value))) {
            this._flagArray[7] = 1
            this._hideBackButton_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    titleMode(value: NavigationTitleMode | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._titleMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    hideToolBar(value: boolean | undefined): this {
        if (((this._flagArray[9]) == (0)) || ((this._hideToolBar_0_0value) !== (value))) {
            this._flagArray[9] = 1
            this._hideToolBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    enableToolBarAdaptation(value: boolean | undefined): this {
        if (((this._flagArray[10]) == (0)) || ((this._enableToolBarAdaptation_0_0value) !== (value))) {
            this._flagArray[10] = 1
            this._enableToolBarAdaptation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._onTitleModeChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    onNavBarStateChange(value: ((isSelected: boolean) => void) | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._onNavBarStateChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._onNavigationModeChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    navDestination(value: PageMapBuilder | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._navDestination_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._customNavContentTransition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    systemBarStyle(value: SystemBarStyle | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._systemBarStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    recoverable(value: boolean | undefined): this {
        if (((this._flagArray[17]) == (0)) || ((this._recoverable_0_0value) !== (value))) {
            this._flagArray[17] = 1
            this._recoverable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    enableDragBar(value: boolean | undefined): this {
        if (((this._flagArray[18]) == (0)) || ((this._enableDragBar_0_0value) !== (value))) {
            this._flagArray[18] = 1
            this._enableDragBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    enableModeChangeAnimation(value: boolean | undefined): this {
        if (((this._flagArray[19]) == (0)) || ((this._enableModeChangeAnimation_0_0value) !== (value))) {
            this._flagArray[19] = 1
            this._enableModeChangeAnimation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    backButtonIcon(icon: string | PixelMap | global_resource_Resource | SymbolGlyphModifier | undefined, accessibilityText?: arkui_component_units_ResourceStr): this {
        if (((this._flagArray[20]) == (0)) || (true) || (true)) {
            this._flagArray[20] = 1
            this._backButtonIcon_0_0value = icon
            this._backButtonIcon_0_1value = accessibilityText
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    title(value: arkui_component_units_ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        if (((this._flagArray[21]) == (0)) || (true) || (true)) {
            this._flagArray[21] = 1
            this._title_0_0value = value
            this._title_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        if (((this._flagArray[22]) == (0)) || ((this._hideTitleBar_1_0value) !== (hide)) || ((this._hideTitleBar_1_1value) !== (animated))) {
            this._flagArray[22] = 1
            this._hideTitleBar_1_0value = hide
            this._hideTitleBar_1_1value = animated
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (((this._flagArray[23]) == (0)) || (true) || (true)) {
            this._flagArray[23] = 1
            this._menus_0_0value = items
            this._menus_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (((this._flagArray[24]) == (0)) || (true) || (true)) {
            this._flagArray[24] = 1
            this._toolbarConfiguration_0_0value = value
            this._toolbarConfiguration_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    hideToolBar(hide: boolean | undefined, animated: boolean | undefined): this {
        if (((this._flagArray[25]) == (0)) || ((this._hideToolBar_1_0value) !== (hide)) || ((this._hideToolBar_1_1value) !== (animated))) {
            this._flagArray[25] = 1
            this._hideToolBar_1_0value = hide
            this._hideToolBar_1_1value = animated
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (((this._flagArray[26]) == (0)) || (true) || (true)) {
            this._flagArray[26] = 1
            this._ignoreLayoutSafeArea_0_0value = types
            this._ignoreLayoutSafeArea_0_1value = edges
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
