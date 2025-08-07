/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

/// <reference path='./import.ts' />
const TITLE_MODE_RANGE = 2;
const NAV_BAR_POSITION_RANGE = 1;
const NAVIGATION_MODE_RANGE = 2;
const DEFAULT_NAV_BAR_WIDTH = 240;
const MIN_NAV_BAR_WIDTH_DEFAULT = '240vp';
const MAX_NAV_BAR_WIDTH_DEFAULT = '40%';
const NAVIGATION_TITLE_MODE_DEFAULT = 0;
const DEFAULT_UNIT = 'vp';
const NAV_SAFE_AREA_TYPE_LIMIT = 3;
const NAV_SAFE_AREA_EDGE_LIMIT = 4;
const NAV_SAFE_AREA_LOWER_LIMIT = 0;

class ArkNavigationComponent extends ArkComponent implements NavigationAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  navBarWidth(value: Length): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, NavBarWidthModifier.identity, NavBarWidthModifier, value);
    return this;
  }
  navBarPosition(value: number): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, NavBarPositionModifier.identity, NavBarPositionModifier, value);
    return this;
  }
  navBarWidthRange(value: [Dimension, Dimension]): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, NavBarWidthRangeModifier.identity, NavBarWidthRangeModifier, value);
    return this;
  }
  minContentWidth(value: Dimension): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, MinContentWidthModifier.identity, MinContentWidthModifier, value);

    return this;
  }
  mode(value: number): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, ModeModifier.identity, ModeModifier, value);
    return this;
  }
  backButtonIcon(value: any): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, BackButtonIconModifier.identity, BackButtonIconModifier, value);
    return this;
  }
  hideNavBar(value: boolean): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, HideNavBarModifier.identity, HideNavBarModifier, value);
    return this;
  }
  title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined,
    options?: NavigationTitleOptions): NavigationAttribute {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, TitleModifier.identity,
        TitleModifier, undefined);
      return this;
    }
    let arkNavigationTitle = new ArkNavigationTitle();
    arkNavigationTitle.value = value;
    if (!isUndefined(options) && !isNull(options) && isObject(options)) {
      if (Object.keys(options).length !== 0) {
        arkNavigationTitle.navigationTitleOptions = options;
      }
    }
    modifierWithKey(this._modifiersWithKeys, TitleModifier.identity,
      TitleModifier, arkNavigationTitle);
    return this;
  }
  subTitle(value: string): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, SubTitleModifier.identity, SubTitleModifier, value);
    return this;
  }
  enableModeChangeAnimation(value: boolean): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, EnableModeChangeAnimationModifier.identity, EnableModeChangeAnimationModifier, value);
    return this;
  }
  splitPlaceholder(placeholder: ComponentContent): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, SplitPlaceholderModifier.identity, SplitPlaceholderModifier, placeholder);
    return this;
  }
  hideTitleBar(isHide: boolean, animated?: boolean): NavigationAttribute {
    let arkNavigationHideTitleBar = new ArkNavHideTitleBarOrToolBar();
    if (!isUndefined(isHide) && !isNull(isHide)) {
      arkNavigationHideTitleBar.isHide = isHide;
    }
    if (!isUndefined(animated) && !isNull(animated)) {
      arkNavigationHideTitleBar.animated = animated;
    }
    if (arkNavigationHideTitleBar.isHide === undefined && arkNavigationHideTitleBar.animated === undefined) {
        modifierWithKey(this._modifiersWithKeys, NavigationHideTitleBarModifier.identity, NavigationHideTitleBarModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, NavigationHideTitleBarModifier.identity, NavigationHideTitleBarModifier, arkNavigationHideTitleBar);
    }
    return this;
  }
  hideBackButton(value: boolean): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, HideBackButtonModifier.identity, HideBackButtonModifier, value);
    return this;
  }
  titleMode(value: NavigationTitleMode): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, TitleModeModifier.identity, TitleModeModifier, value);
    return this;
  }
  menus(value: Array<NavigationMenuItem> | undefined): NavigationAttribute {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, MenusModifier.identity, MenusModifier, undefined);
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, MenusModifier.identity, MenusModifier, value);
    return this;
  }
  toolBar(value: object | undefined): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, ToolBarModifier.identity, ToolBarModifier, callback);
    return this;
  }
  toolbarConfiguration(value: Array<ToolbarItem> | undefined, options?: NavigationToolbarOptions | undefined): NavigationAttribute {
    let configuration = new ArkNavigationToolBarConfiguration();
    configuration.value = value;
    if (!isNull(options)) {
      configuration.options = options;
    }
    modifierWithKey(this._modifiersWithKeys, ToolBarConfigurationModifier.identity,
      ToolBarConfigurationModifier, configuration);
    return this;
  }
  hideToolBar(isHide: boolean, animated?: boolean): NavigationAttribute {
    let arkNavigationHideToolBar = new ArkNavHideTitleBarOrToolBar();
    if (!isUndefined(isHide) && !isNull(isHide)) {
      arkNavigationHideToolBar.isHide = isHide;
    }
    if (!isUndefined(animated) && !isNull(animated)) {
      arkNavigationHideToolBar.animated = animated;
    }
    if (arkNavigationHideToolBar.isHide === undefined && arkNavigationHideToolBar.animated === undefined) {
        modifierWithKey(this._modifiersWithKeys, HideToolBarModifier.identity, HideToolBarModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, HideToolBarModifier.identity, HideToolBarModifier, arkNavigationHideToolBar);
    }
    return this;
  }
  onTitleModeChange(callback: (titleMode: NavigationTitleMode) => void): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, OnTitleModeChangeModifier.identity, OnTitleModeChangeModifier, callback);
    return this;
  }
  onNavBarStateChange(callback: (isVisible: boolean) => void): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, OnNavBarStateChangeModifier.identity,
      OnNavBarStateChangeModifier, callback);
    return this;
  }
  onNavigationModeChange(callback: (mode: NavigationMode) => void): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, OnNavigationModeChange.identity, OnNavigationModeChange, callback);
    return this;
  }
  customNavContentTransition(delegate:(from: NavContentInfo, to: NavContentInfo,
    operation: NavigationOperation) => NavigationAnimatedTransition | undefined): NavigationAttribute {
      modifierWithKey(this._modifiersWithKeys, CustomNavContentTransition.identity,
        CustomNavContentTransition, delegate);
    return this;
  }
  navDestination(builder: (name: string, param: unknown) => void): NavigationAttribute {
    throw new Error('Method not implemented.');
  }
  ignoreLayoutSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): NavigationAttribute {
    let opts = new ArkSafeAreaExpandOpts();
    if (types && types.length >= 0) {
      let safeAreaType: string | number = '';
      for (let param of types) {
        if (!isNumber(param) || param >= NAV_SAFE_AREA_TYPE_LIMIT || param < NAV_SAFE_AREA_LOWER_LIMIT) {
          safeAreaType = undefined;
          break;
        }
        if (safeAreaType) {
          safeAreaType += '|';
          safeAreaType += param.toString();
        } else {
          safeAreaType += param.toString();
        }
      }
      opts.type = safeAreaType;
    }
    if (edges && edges.length >= 0) {
      let safeAreaEdge: string | number = '';
      for (let param of edges) {
        if (!isNumber(param) || param >= NAV_SAFE_AREA_EDGE_LIMIT || param < NAV_SAFE_AREA_LOWER_LIMIT) {
          safeAreaEdge = undefined;
          break;
        }
        if (safeAreaEdge) {
          safeAreaEdge += '|';
          safeAreaEdge += param.toString();
        } else {
          safeAreaEdge += param.toString();
        }
      }
      opts.edges = safeAreaEdge;
    }
    if (opts.type === undefined && opts.edges === undefined) {
      modifierWithKey(this._modifiersWithKeys, IgnoreNavLayoutSafeAreaModifier.identity, IgnoreNavLayoutSafeAreaModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, IgnoreNavLayoutSafeAreaModifier.identity, IgnoreNavLayoutSafeAreaModifier, opts);
    }
    return this;
  }
  recoverable(value: boolean | undefined): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, NavigationRecoverableModifier.identity, NavigationRecoverableModifier, value);
    return this;
  }

  enableDargBar(value: boolean | undefined): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, NavigationEnableDragBarModifier.identity, NavigationEnableDragBarModifier, value);
    return this;
  }

  enableToolBarAdaptation(value: boolean | undefined): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, NavigationEnableToolBarAdaptationModifier.identity, NavigationEnableToolBarAdaptationModifier, value);
    return this;
  }

  systemBarStyle(style: Optional<SystemBarStyle>): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, NavigationSystemBarStyleModifier.identity, NavigationSystemBarStyleModifier, style);
    return this;
  }
} 

class OnTitleModeChangeModifier extends ModifierWithKey<((titleMode: NavigationTitleMode) => void)> {
  constructor(value: (titleMode: NavigationTitleMode) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onTitleModeChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetOnTitleModeChange(node);
    } else {
      getUINativeModule().navigation.setOnTitleModeChange(node, this.value);
    }
  }
}

class OnNavigationModeChange extends ModifierWithKey<((mode: NavigationMode) => void)> {
  constructor(value: ((mode: NavigationMode) => void)) {
    super(value);
  }
  static identity: Symbol = Symbol('onNavigationModeChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetOnNavigationModeChange(node);
    } else {
      getUINativeModule().navigation.setOnNavigationModeChange(node, this.value);
    }
  }
}

class CustomNavContentTransition extends ModifierWithKey<(from: NavContentInfo, to: NavContentInfo,
  operation: NavigationOperation) => NavigationAnimatedTransition | undefined> {
  constructor(value: (from: NavContentInfo, to: NavContentInfo,
    operation: NavigationOperation) => NavigationAnimatedTransition | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('customNavContentTransition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetCustomNavContentTransition(node);
    } else {
      getUINativeModule().navigation.setCustomNavContentTransition(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ToolBarModifier extends ModifierWithKey<object | undefined> {
  constructor(value: object | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('toolBar');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetToolBar(node);
    } else {
      getUINativeModule().navigation.setToolBar(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ToolBarConfigurationModifier extends ModifierWithKey<ArkNavigationToolBarConfiguration> {
  constructor(value: ArkNavigationToolBarConfiguration) {
    super(value);
  }
  static identity: Symbol = Symbol('toolbarConfiguration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().navigation.resetToolBarConfiguration(node);
    } else {
      getUINativeModule().navigation.setToolBarConfiguration(node, this.value.value, this.value.options);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class OnNavBarStateChangeModifier extends ModifierWithKey<((isVisible: boolean) => void)> {
  constructor(value: (isVisible: boolean) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onNavBarStateChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetOnNavBarStateChange(node);
    } else {
      getUINativeModule().navigation.setOnNavBarStateChange(node, this.value);
    }
  }
}

class BackButtonIconModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('backButtonIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetBackButtonIcon(node);
    } else {
      getUINativeModule().navigation.setBackButtonIcon(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class NavBarWidthRangeModifier extends ModifierWithKey<[Dimension, Dimension]> {
  constructor(value: [Dimension, Dimension]) {
    super(value);
  }
  static identity: Symbol = Symbol('navBarWidthRange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetNavBarWidthRange(node);
    } else {
      getUINativeModule().navigation.setNavBarWidthRange(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class MinContentWidthModifier extends ModifierWithKey<Dimension> {
  constructor(value: Dimension) {
    super(value);
  }
  static identity: Symbol = Symbol('minContentWidth');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetMinContentWidth(node);
    } else {
      getUINativeModule().navigation.setMinContentWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class NavBarWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('navBarWidth');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetNavBarWidth(node);
    } else {
      getUINativeModule().navigation.setNavBarWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class NavBarPositionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('navBarPosition');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetNavBarPosition(node);
    } else {
      getUINativeModule().navigation.setNavBarPosition(node, this.value);
    }
  }
}

class ModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('mode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetMode(node);
    } else {
      getUINativeModule().navigation.setMode(node, this.value);
    }
  }
}

class HideToolBarModifier extends ModifierWithKey<ArkNavHideTitleBarOrToolBar | undefined> {
  constructor(value: ArkNavHideTitleBarOrToolBar) {
    super(value);
  }
  static identity: Symbol = Symbol('hideToolBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetHideToolBar(node);
    } else {
      getUINativeModule().navigation.setHideToolBar(node, this.value?.isHide, this.value?.animated);
    }
  }
}

class TitleModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('titleMode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetTitleMode(node);
    } else {
      getUINativeModule().navigation.setTitleMode(node, this.value);
    }
  }
}

class MenusModifier extends ModifierWithKey<Array<NavigationMenuItem> | undefined> {
  constructor(value: Array<NavigationMenuItem> | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('menus');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetMenus(node);
    } else {
      getUINativeModule().navigation.setMenus(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (!Array.isArray(this.value) || !Array.isArray(this.stageValue)) {
      return true;
    }
    if (this.value.length !== this.stageValue.length) {
      return true;
    }
    for (let i = 0; i < this.value.length; i++) {
      if (!(isBaseOrResourceEqual(this.stageValue[i].value, this.value[i].value) &&
        isBaseOrResourceEqual(this.stageValue[i].icon, this.value[i].icon) &&
        isBaseOrResourceEqual(this.stageValue[i].isEnabled, this.value[i].isEnabled) &&
        isBaseOrResourceEqual(this.stageValue[i].action, this.value[i].action) &&
        isBaseOrResourceEqual(this.stageValue[i].symbolIcon, this.value[i].symbolIcon)
      )) {
        return true;
      }
    }
    return false;
  }
}

class HideBackButtonModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('hideBackButton');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetHideBackButton(node);
    } else {
      getUINativeModule().navigation.setHideBackButton(node, this.value);
    }
  }
}

class TitleModifier extends ModifierWithKey<ArkNavigationTitle | undefined> {
  constructor(value: ArkNavigationTitle | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('title');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetTitle(node);
    } else {
      getUINativeModule().navigation.setTitle(node, this.value?.value, this.value?.navigationTitleOptions);
    }
  }
  checkObjectDiff(): boolean {
    return !this.value.isEqual(this.stageValue);
  }
}

class SubTitleModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('subTitle');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetSubTitle(node);
    } else {
      getUINativeModule().navigation.setSubTitle(node, this.value);
    }
  }
}

class NavigationHideTitleBarModifier extends ModifierWithKey<ArkNavHideTitleBarOrToolBar | undefined> {
  constructor(value: ArkNavHideTitleBarOrToolBar) {
    super(value);
  }
  static identity: Symbol = Symbol('hideTitleBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetHideTitleBar(node);
    } else {
      getUINativeModule().navigation.setHideTitleBar(node, this.value?.isHide, this.value?.animated);
    }
  }
}

class SplitPlaceholderModifier extends ModifierWithKey<ComponentContent> {
  constructor(value: ComponentContent) {
    super(value);
  }
  static identity: Symbol = Symbol('splitPlaceholder');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetSplitPlaceholder(node);
    } else {
      getUINativeModule().navigation.setSplitPlaceholder(node, this.value);
    }
  }
}

class EnableModeChangeAnimationModifier extends ModifierWithKey<boolean | undefined> {
  constructor(value: boolean | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('enableModeChangeAnimation');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetEnableModeChangeAnimation(node);
    } else {
      getUINativeModule().navigation.setEnableModeChangeAnimation(node, this.value);
    }
  }
}

class HideNavBarModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('hideNavBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetHideNavBar(node);
    } else {
      getUINativeModule().navigation.setHideNavBar(node, this.value);
    }
  }
}

class IgnoreNavLayoutSafeAreaModifier extends ModifierWithKey<ArkSafeAreaExpandOpts | undefined> {
  constructor(value: ArkSafeAreaExpandOpts | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('ignoreLayoutSafeArea');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetIgnoreLayoutSafeArea(node);
    } else {
      getUINativeModule().navigation.setIgnoreLayoutSafeArea(node, this.value.type, this.value.edges);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.type, this.value.type) ||
      !isBaseOrResourceEqual(this.stageValue.edges, this.value.edges);
  }
}

class NavigationRecoverableModifier extends ModifierWithKey<boolean | undefined> {
  constructor(value: boolean | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('recoverable');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetRecoverable(node);
    } else {
      getUINativeModule().navigation.setRecoverable(node, this.value);
    }
  }
}

class NavigationEnableDragBarModifier extends ModifierWithKey<boolean | undefined> {
  constructor(value: boolean | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('enableDragBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetEnableDragBar(node);
    } else {
      getUINativeModule().navigation.setEnableDragBar(node, this.value);
    }
  }
}

class NavigationEnableToolBarAdaptationModifier extends ModifierWithKey<boolean | undefined> {
  constructor(value: boolean | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('enableToolBarAdaptation');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetEnableToolBarAdaptation(node);
    } else {
      getUINativeModule().navigation.setEnableToolBarAdaptation(node, this.value);
    }
  }
}

class NavigationSystemBarStyleModifier extends ModifierWithKey<Optional<SystemBarStyle>> {
  constructor(value: Optional<SystemBarStyle>) {
    super(value);
  }
  static identity: Symbol = Symbol('systemBarStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().navigation.resetSystemBarStyle(node);
    } else {
      getUINativeModule().navigation.setSystemBarStyle(node, this.value.statusBarContentColor);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.stageValue.statusBarContentColor === this.value.statusBarContentColor);
  }
}
// @ts-ignore
globalThis.Navigation.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkNavigationComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.NavigationModifier(nativePtr, classType);
  });
};
