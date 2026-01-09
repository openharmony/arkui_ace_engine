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
import { ModifierState } from './CommonModifier'
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkNavDestinationPeer, VisibilityChangeReason, NavDestinationMode, NavDestinationContext, NavigationSystemTransitionType, NestedScrollInfo, NavDestinationActiveReason, NavDestinationTransitionDelegate, NavDestinationCommonTitle, NavDestinationCustomTitle, NavDestinationAttribute } from "./component/navDestination"
import { int32 } from "@koalaui/common"
import { CommonMethod, LayoutSafeAreaType, LayoutSafeAreaEdge } from "./component/common"
import { default as window } from "@ohos.window"
import { Scroller } from "./component/scroll"
import { NavigationOperation, NavigationTitleOptions, NavigationMenuItem, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions } from "./component/navigation"
import { CustomBuilder } from "./component/builder"
import { Resource } from "global.resource"
import { ResourceStr } from "./component/units"
import { default as image } from "@ohos.multimedia.image"
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"

export class NavDestinationModifier extends CommonMethodModifier implements NavDestinationAttribute,AttributeModifier<NavDestinationAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
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
    _onShown_0_0value?: ((value0: VisibilityChangeReason) => void) | undefined
    _onHidden_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHidden_0_0value?: ((value0: VisibilityChangeReason) => void) | undefined
    _onBackPressed_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onBackPressed_0_0value?: (() => boolean) | undefined
    _onResult_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onResult_0_0value?: ((value0: Object | null | undefined) => void) | undefined
    _mode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mode_0_0value?: NavDestinationMode | undefined
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
    _systemBarStyle_0_0value?: window.SystemBarStyle | undefined
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
    _preferredOrientation_0_0value?: window.Orientation | undefined
    _enableNavigationIndicator_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNavigationIndicator_0_0value?: boolean | undefined
    _title_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _title_0_0value?: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined
    _title_0_1value?: NavigationTitleOptions | undefined
    _hideTitleBar_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_1_0value?: boolean | undefined
    _hideTitleBar_1_1value?: boolean | undefined
    _backButtonIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backButtonIcon_0_0value?: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined
    _backButtonIcon_0_1value?: ResourceStr | undefined
    _menus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menus_0_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _menus_0_1value?: NavigationMenuOptions | undefined
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
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkNavDestinationPeer;
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
        if (this._onShown_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onShown_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnShownAttribute((this._onShown_0_0value as ((value0: VisibilityChangeReason) => void) | undefined));
                    this._onShown_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onShown_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onShown_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnShownAttribute((undefined as ((value0: VisibilityChangeReason) => void) | undefined));
                }
            }
        }
        if (this._onHidden_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHiddenAttribute((this._onHidden_0_0value as ((value0: VisibilityChangeReason) => void) | undefined));
                    this._onHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHidden_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHiddenAttribute((undefined as ((value0: VisibilityChangeReason) => void) | undefined));
                }
            }
        }
        if (this._onBackPressed_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onBackPressed_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnBackPressedAttribute((this._onBackPressed_0_0value as (() => boolean) | undefined));
                    this._onBackPressed_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onBackPressed_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onBackPressed_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnBackPressedAttribute((undefined as (() => boolean) | undefined));
                }
            }
        }
        if (this._onResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnResultAttribute((this._onResult_0_0value as ((value0: Object | null | undefined) => void) | undefined));
                    this._onResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onResult_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnResultAttribute((undefined as ((value0: Object | null | undefined) => void) | undefined));
                }
            }
        }
        if (this._mode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setModeAttribute((this._mode_0_0value as NavDestinationMode | undefined));
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setModeAttribute((undefined as NavDestinationMode | undefined));
                }
            }
        }
        if (this._onReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReadyAttribute((this._onReady_0_0value as ((value0: NavDestinationContext) => void) | undefined));
                    this._onReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReady_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReadyAttribute((undefined as ((value0: NavDestinationContext) => void) | undefined));
                }
            }
        }
        if (this._onWillAppear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillAppear_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillAppearAttribute((this._onWillAppear_0_0value as (() => void) | undefined));
                    this._onWillAppear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillAppear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillAppear_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillAppearAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onWillDisappear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillDisappear_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillDisappearAttribute((this._onWillDisappear_0_0value as (() => void) | undefined));
                    this._onWillDisappear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillDisappear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillDisappear_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillDisappearAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onWillShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillShowAttribute((this._onWillShow_0_0value as (() => void) | undefined));
                    this._onWillShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillShow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillShowAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onWillHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillHideAttribute((this._onWillHide_0_0value as (() => void) | undefined));
                    this._onWillHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillHideAttribute((undefined as (() => void) | undefined));
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
        if (this._systemTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._systemTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSystemTransitionAttribute((this._systemTransition_0_0value as NavigationSystemTransitionType | undefined));
                    this._systemTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._systemTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._systemTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSystemTransitionAttribute((undefined as NavigationSystemTransitionType | undefined));
                }
            }
        }
        if (this._bindToScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindToScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindToScrollableAttribute((this._bindToScrollable_0_0value as Array<Scroller> | undefined));
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindToScrollableAttribute((undefined as Array<Scroller> | undefined));
                }
            }
        }
        if (this._bindToNestedScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindToNestedScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindToNestedScrollableAttribute((this._bindToNestedScrollable_0_0value as Array<NestedScrollInfo> | undefined));
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindToNestedScrollableAttribute((undefined as Array<NestedScrollInfo> | undefined));
                }
            }
        }
        if (this._onActive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onActive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnActiveAttribute((this._onActive_0_0value as ((value0: NavDestinationActiveReason) => void) | undefined));
                    this._onActive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onActive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onActive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnActiveAttribute((undefined as ((value0: NavDestinationActiveReason) => void) | undefined));
                }
            }
        }
        if (this._onInactive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInactive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnInactiveAttribute((this._onInactive_0_0value as ((value0: NavDestinationActiveReason) => void) | undefined));
                    this._onInactive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInactive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInactive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnInactiveAttribute((undefined as ((value0: NavDestinationActiveReason) => void) | undefined));
                }
            }
        }
        if (this._customTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomTransitionAttribute((this._customTransition_0_0value as NavDestinationTransitionDelegate | undefined));
                    this._customTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomTransitionAttribute((undefined as NavDestinationTransitionDelegate | undefined));
                }
            }
        }
        if (this._onNewParam_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNewParam_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNewParamAttribute((this._onNewParam_0_0value as ((value0: Object | null | undefined) => void) | undefined));
                    this._onNewParam_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNewParam_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNewParam_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNewParamAttribute((undefined as ((value0: Object | null | undefined) => void) | undefined));
                }
            }
        }
        if (this._preferredOrientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._preferredOrientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPreferredOrientationAttribute((this._preferredOrientation_0_0value as window.Orientation | undefined));
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPreferredOrientationAttribute((undefined as window.Orientation | undefined));
                }
            }
        }
        if (this._enableNavigationIndicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNavigationIndicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableNavigationIndicatorAttribute((this._enableNavigationIndicator_0_0value as boolean | undefined));
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableNavigationIndicatorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._title_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._title_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTitleAttribute((this._title_0_0value as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (this._title_0_1value as NavigationTitleOptions | undefined | undefined));
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._title_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTitleAttribute((undefined as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
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
        if (this._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackButtonIconAttribute((this._backButtonIcon_0_0value as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined), (this._backButtonIcon_0_1value as ResourceStr | undefined | undefined));
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackButtonIconAttribute((undefined as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
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
        if (this._hideToolBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideToolBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideToolBarAttribute((this._hideToolBar_0_0value as boolean | undefined), (this._hideToolBar_0_1value as boolean | undefined | undefined));
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideToolBarAttribute((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
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
        if (this._enableStatusBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableStatusBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableStatusBarAttribute((this._enableStatusBar_0_0value as boolean | undefined), (this._enableStatusBar_0_1value as boolean | undefined | undefined));
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableStatusBarAttribute((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: NavDestinationModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
        if (modifier._onShown_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onShown_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onShown(modifier._onShown_0_0value);
                    break;
                }
                default: {
                    this.onShown((undefined as ((value0: VisibilityChangeReason) => void) | undefined));
                }
            }
        }
        if (modifier._onHidden_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHidden(modifier._onHidden_0_0value);
                    break;
                }
                default: {
                    this.onHidden((undefined as ((value0: VisibilityChangeReason) => void) | undefined));
                }
            }
        }
        if (modifier._onBackPressed_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onBackPressed_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onBackPressed(modifier._onBackPressed_0_0value);
                    break;
                }
                default: {
                    this.onBackPressed((undefined as (() => boolean) | undefined));
                }
            }
        }
        if (modifier._onResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onResult(modifier._onResult_0_0value);
                    break;
                }
                default: {
                    this.onResult((undefined as ((value0: Object | null | undefined) => void) | undefined));
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
        if (modifier._onReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReady(modifier._onReady_0_0value);
                    break;
                }
                default: {
                    this.onReady((undefined as ((value0: NavDestinationContext) => void) | undefined));
                }
            }
        }
        if (modifier._onWillAppear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillAppear_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillAppear(modifier._onWillAppear_0_0value);
                    break;
                }
                default: {
                    this.onWillAppear((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onWillDisappear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillDisappear_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillDisappear(modifier._onWillDisappear_0_0value);
                    break;
                }
                default: {
                    this.onWillDisappear((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onWillShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillShow(modifier._onWillShow_0_0value);
                    break;
                }
                default: {
                    this.onWillShow((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onWillHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillHide(modifier._onWillHide_0_0value);
                    break;
                }
                default: {
                    this.onWillHide((undefined as (() => void) | undefined));
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
        if (modifier._onActive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onActive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onActive(modifier._onActive_0_0value);
                    break;
                }
                default: {
                    this.onActive((undefined as ((value0: NavDestinationActiveReason) => void) | undefined));
                }
            }
        }
        if (modifier._onInactive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInactive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInactive(modifier._onInactive_0_0value);
                    break;
                }
                default: {
                    this.onInactive((undefined as ((value0: NavDestinationActiveReason) => void) | undefined));
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
        if (modifier._onNewParam_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNewParam_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNewParam(modifier._onNewParam_0_0value);
                    break;
                }
                default: {
                    this.onNewParam((undefined as ((value0: Object | null | undefined) => void) | undefined));
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
                    this.preferredOrientation((undefined as window.Orientation | undefined));
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
        if (modifier._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backButtonIcon(modifier._backButtonIcon_0_0value, modifier._backButtonIcon_0_1value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._hideBackButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onShown(value: ((value0: VisibilityChangeReason) => void) | undefined): this {
        if (((this._onShown_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onShown_0_flag = AttributeUpdaterFlag.UPDATE
            this._onShown_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onShown_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHidden(value: ((value0: VisibilityChangeReason) => void) | undefined): this {
        if (((this._onHidden_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHidden_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHidden_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onHidden_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onBackPressed(value: (() => boolean) | undefined): this {
        if (((this._onBackPressed_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onBackPressed_0_flag = AttributeUpdaterFlag.UPDATE
            this._onBackPressed_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onBackPressed_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onResult(value: ((value0: Object | null | undefined) => void) | undefined): this {
        if (((this._onResult_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onResult_0_flag = AttributeUpdaterFlag.UPDATE
            this._onResult_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onResult_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mode(value: NavDestinationMode | undefined): this {
        if (((this._mode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mode_0_flag = AttributeUpdaterFlag.UPDATE
            this._mode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._mode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReady(value: ((value0: NavDestinationContext) => void) | undefined): this {
        if (((this._onReady_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReady_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReady_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onReady_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillAppear(value: (() => void) | undefined): this {
        if (((this._onWillAppear_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillAppear_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillAppear_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillAppear_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillDisappear(value: (() => void) | undefined): this {
        if (((this._onWillDisappear_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillDisappear_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillDisappear_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillDisappear_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillShow(value: (() => void) | undefined): this {
        if (((this._onWillShow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillShow_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillShow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillShow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillHide(value: (() => void) | undefined): this {
        if (((this._onWillHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillHide_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    systemBarStyle(value: window.SystemBarStyle | undefined): this {
        if (((this._systemBarStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._systemBarStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._systemBarStyle_0_0value = value
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        if (((this._onActive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onActive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onActive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onActive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        if (((this._onInactive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInactive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInactive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onInactive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        if (((this._customTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._customTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._customTransition_0_0value = value
            this._state.fireChange()
        } else
        {
            this._customTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNewParam(value: ((value0: Object | null | undefined) => void) | undefined): this {
        if (((this._onNewParam_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNewParam_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNewParam_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onNewParam_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    preferredOrientation(value: window.Orientation | undefined): this {
        if (((this._preferredOrientation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._preferredOrientation_0_flag = AttributeUpdaterFlag.UPDATE
            this._preferredOrientation_0_0value = value
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._hideTitleBar_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backButtonIcon(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (((this._backButtonIcon_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._backButtonIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._backButtonIcon_0_0value = icon
            this._backButtonIcon_0_1value = accessibilityText
            this._state.fireChange()
        } else
        {
            this._backButtonIcon_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (((this._menus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._menus_0_flag = AttributeUpdaterFlag.UPDATE
            this._menus_0_0value = items
            this._menus_0_1value = options
            this._state.fireChange()
        } else
        {
            this._menus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (((this._toolbarConfiguration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.UPDATE
            this._toolbarConfiguration_0_0value = toolbarParam
            this._toolbarConfiguration_0_1value = options
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._enableStatusBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
