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

const NAVDES_SAFE_AREA_TYPE_LIMIT = 3;
const NAVDES_SAFE_AREA_EDGE_LIMIT = 4;
const NAVDES_SAFE_AREA_LOWER_LIMIT = 0;
class ArkNavDestinationComponent extends ArkComponent implements NavDestinationAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined,
    options?: NavigationTitleOptions): this {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, NavDestinationTitleModifier.identity,
        NavDestinationTitleModifier, undefined);
      return this;
    }
    let arkNavigationTitle = new ArkNavigationTitle();
    arkNavigationTitle.value = value;
    if (!isUndefined(options) && !isNull(options) && isObject(options)) {
      if (Object.keys(options).length !== 0) {
        arkNavigationTitle.navigationTitleOptions = options;
      }
    }
    modifierWithKey(this._modifiersWithKeys, NavDestinationTitleModifier.identity,
      NavDestinationTitleModifier, arkNavigationTitle);
    return this;
  }
  menus(value: Array<NavigationMenuItem> | undefined): this {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, NavDestinationMenusModifier.identity,
        NavDestinationMenusModifier, undefined);
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, NavDestinationMenusModifier.identity,
        NavDestinationMenusModifier, value);
    return this;
  }
  hideTitleBar(isHide: boolean, animated?: boolean): this {
    let arkNavDestinationHideTitleBar = new ArkNavHideTitleBarOrToolBar();
    if (!isUndefined(isHide) && !isNull(isHide)) {
      arkNavDestinationHideTitleBar.isHide = isHide;
    }
    if (!isUndefined(animated) && !isNull(animated)) {
      arkNavDestinationHideTitleBar.animated = animated;
    }
    if (arkNavDestinationHideTitleBar.isHide === undefined && arkNavDestinationHideTitleBar.animated === undefined) {
        modifierWithKey(this._modifiersWithKeys, HideTitleBarModifier.identity, HideTitleBarModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, HideTitleBarModifier.identity, HideTitleBarModifier, arkNavDestinationHideTitleBar);
    }
    return this;
  }
  hideToolBar(isHide: boolean, animated?: boolean): this {
    let arkNavDestinationHideToolBar = new ArkNavHideTitleBarOrToolBar();
    if (!isUndefined(isHide) && !isNull(isHide)) {
      arkNavDestinationHideToolBar.isHide = isHide;
    }
    if (!isUndefined(animated) && !isNull(animated)) {
      arkNavDestinationHideToolBar.animated = animated;
    }
    if (arkNavDestinationHideToolBar.isHide === undefined && arkNavDestinationHideToolBar.animated === undefined) {
        modifierWithKey(this._modifiersWithKeys, NavDestinationHideToolBarModifier.identity,
          NavDestinationHideToolBarModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, NavDestinationHideToolBarModifier.identity,
          NavDestinationHideToolBarModifier, arkNavDestinationHideToolBar);
    }
    return this;
  }
  toolbarConfiguration(value: any): this {
    throw new Error('Method not implemented.');
  }
  backButtonIcon(value: any): this {
    modifierWithKey(this._modifiersWithKeys, NavDestinationBackButtonIconModifier.identity,
      NavDestinationBackButtonIconModifier, value);
    return this;
  }
  mode(value: number): this {
    modifierWithKey(this._modifiersWithKeys, NavDestinationModeModifier.identity,
      NavDestinationModeModifier, value);
    return this;
  }
  onShown(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onHidden(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onBackPressed(callback: () => boolean): this {
    throw new Error('Method not implemented.');
  }
  ignoreLayoutSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
    let opts = new ArkSafeAreaExpandOpts();
    if (types && types.length >= 0) {
      let safeAreaType: string | number = '';
      for (let param of types) {
        if (!isNumber(param) || param >= NAVDES_SAFE_AREA_TYPE_LIMIT || param < NAVDES_SAFE_AREA_LOWER_LIMIT) {
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
        if (!isNumber(param) || param >= NAVDES_SAFE_AREA_EDGE_LIMIT || param < NAVDES_SAFE_AREA_LOWER_LIMIT) {
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
      modifierWithKey(this._modifiersWithKeys, IgnoreLayoutSafeAreaModifier.identity, IgnoreLayoutSafeAreaModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, IgnoreLayoutSafeAreaModifier.identity, IgnoreLayoutSafeAreaModifier, opts);
    }
    return this;
  }
  recoverable(value: boolean | undefined): this {
    modifierWithKey(this._modifiersWithKeys, NavDestinationRecoverableModifier.identity, NavDestinationRecoverableModifier, value);
    return this;
  }
}

class NavDestinationTitleModifier extends ModifierWithKey<ArkNavigationTitle | undefined> {
  constructor(value: ArkNavigationTitle | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('title');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetTitle(node);
    } else {
      getUINativeModule().navDestination.setTitle(node, this.value?.value, this.value?.navigationTitleOptions);
    }
  }
  checkObjectDiff(): boolean {
    return !this.value.isEqual(this.stageValue);
  }
}

class NavDestinationMenusModifier extends ModifierWithKey<Array<NavigationMenuItem> | undefined> {
  constructor(value: Array<NavigationMenuItem> | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('menus');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetMenus(node);
    } else {
      getUINativeModule().navDestination.setMenus(node, this.value);
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

class HideTitleBarModifier extends ModifierWithKey<ArkNavHideTitleBarOrToolBar | undefined> {
  constructor(value: ArkNavHideTitleBarOrToolBar | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('hideTitleBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetHideTitleBar(node);
    } else {
      getUINativeModule().navDestination.setHideTitleBar(node, this.value?.isHide, this.value?.animated);
    }
  }
}

class NavDestinationHideToolBarModifier extends ModifierWithKey<ArkNavHideTitleBarOrToolBar | undefined> {
  constructor(value: ArkNavHideTitleBarOrToolBar | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('hideToolBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetHideToolBar(node);
    } else {
      getUINativeModule().navDestination.setHideToolBar(node, this.value?.isHide, this.value?.animated);
    }
  }
}

class NavDestinationBackButtonIconModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('backButtonIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetBackButtonIcon(node);
    } else {
      getUINativeModule().navDestination.setBackButtonIcon(node, this.value);
    }
  }
}

class NavDestinationModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('mode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetMode(node);
    } else {
      getUINativeModule().navDestination.setMode(node, this.value);
    }
  }
}

class IgnoreLayoutSafeAreaModifier extends ModifierWithKey<ArkSafeAreaExpandOpts | undefined> {
  constructor(value: ArkSafeAreaExpandOpts | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('ignoreLayoutSafeArea');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetIgnoreLayoutSafeArea(node);
    } else {
      getUINativeModule().navDestination.setIgnoreLayoutSafeArea(node, this.value.type, this.value.edges);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.type, this.value.type) ||
      !isBaseOrResourceEqual(this.stageValue.edges, this.value.edges);
  }
}

class NavDestinationRecoverableModifier extends ModifierWithKey<boolean | undefined> {
  constructor(value: boolean | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('recoverable');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetRecoverable(node);
    } else {
      getUINativeModule().navDestination.setRecoverable(node, this.value);
    }
  }
}

//@ts-ignore
globalThis.NavDestination.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkNavDestinationComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.NavDestinationModifier(nativePtr, classType);
  });
};
