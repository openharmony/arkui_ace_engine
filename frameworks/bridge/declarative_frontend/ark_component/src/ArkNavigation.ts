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
  navBarPosition(value: NavBarPosition): NavigationAttribute {
    modifier(this._modifiers, NavBarPositionModifier, value);
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
  mode(value: NavigationMode): NavigationAttribute {
    modifier(this._modifiers, ModeModifier, value);
    return this;
  }
  backButtonIcon(value: any): NavigationAttribute {
    modifierWithKey(this._modifiersWithKeys, BackButtonIconModifier.identity, BackButtonIconModifier, value);
    return this;
  }
  hideNavBar(value: boolean): NavigationAttribute {
    modifier(this._modifiers, HideNavBarModifier, isBoolean(value) ? value : false);
    return this;
  }
  title(value: any): NavigationAttribute {
    throw new Error('Method not implemented.');
  }
  subTitle(value: string): NavigationAttribute {
    modifier(this._modifiers, SubTitleModifier, value);
    return this;
  }
  hideTitleBar(value: boolean): NavigationAttribute {
    modifier(this._modifiers, NavigationHideTitleBarModifier, isBoolean(value) ? value : false);
    return this;
  }
  hideBackButton(value: boolean): NavigationAttribute {
    modifier(this._modifiers, HideBackButtonModifier, isBoolean(value) ? value : false);
    return this;
  }
  titleMode(value: NavigationTitleMode): NavigationAttribute {
    modifier(this._modifiers, TitleModeModifier, value);
    return this;
  }
  menus(value: any): NavigationAttribute {
    throw new Error('Method not implemented.');
  }
  toolBar(value: any): NavigationAttribute {
    throw new Error('Method not implemented.');
  }
  toolbarConfiguration(value: any): NavigationAttribute {
    throw new Error('Method not implemented.');
  }
  hideToolBar(value: boolean): NavigationAttribute {
    modifier(this._modifiers, HideToolBarModifier, isBoolean(value) ? value : false);
    return this;
  }
  onTitleModeChange(callback: (titleMode: NavigationTitleMode) => void): NavigationAttribute {
    throw new Error('Method not implemented.');
  }
  onNavBarStateChange(callback: (isVisible: boolean) => void): NavigationAttribute {
    throw new Error('Method not implemented.');
  }
  onNavigationModeChange(callback: (mode: NavigationMode) => void): NavigationAttribute {
    throw new Error('Method not implemented.');
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
}

class BackButtonIconModifier extends ModifierWithKey<boolean | object> {
  static identity: Symbol = Symbol('backButtonIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetBackButtonIcon(node);
    } else {
      getUINativeModule().navigation.setBackButtonIcon(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class NavBarWidthRangeModifier extends ModifierWithKey<[Dimension, Dimension]> {
  static identity: Symbol = Symbol('navBarWidthRange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetNavBarWidthRange(node);
    } else {
      getUINativeModule().navigation.setNavBarWidthRange(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class MinContentWidthModifier extends ModifierWithKey<Dimension> {
  static identity: Symbol = Symbol('minContentWidth');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetMinContentWidth(node);
    } else {
      getUINativeModule().navigation.setMinContentWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class NavBarWidthModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('navBarWidth');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetNavBarWidth(node);
    } else {
      getUINativeModule().navigation.setNavBarWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class NavBarPositionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('navBarPosition');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetNavBarPosition(node);
    } else {
      getUINativeModule().navigation.setNavBarPosition(node, this.value);
    }
  }
}

class ModeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('mode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetMode(node);
    } else {
      getUINativeModule().navigation.setMode(node, this.value);
    }
  }
}

class HideToolBarModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('hideToolBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetHideToolBar(node);
    } else {
      getUINativeModule().navigation.setHideToolBar(node, this.value);
    }
  }
}

class TitleModeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('titleMode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetTitleMode(node);
    } else {
      getUINativeModule().navigation.setTitleMode(node, this.value);
    }
  }
}

class HideBackButtonModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('hideBackButton');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetHideBackButton(node);
    } else {
      getUINativeModule().navigation.setHideBackButton(node, this.value);
    }
  }
}

class SubTitleModifier extends Modifier<string> {
  static identity: Symbol = Symbol('subTitle');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetSubTitle(node);
    } else {
      getUINativeModule().navigation.setSubTitle(node, this.value);
    }
  }
}

class NavigationHideTitleBarModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('hideTitleBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigation.resetHideTitleBar(node);
    } else {
      getUINativeModule().navigation.setHideTitleBar(node, this.value);
    }
  }
}

class HideNavBarModifier extends Modifier<boolean> {
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

// @ts-ignore
globalThis.Navigation.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkNavigationComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.NavigationModifier(nativePtr, classType);
  });
};
