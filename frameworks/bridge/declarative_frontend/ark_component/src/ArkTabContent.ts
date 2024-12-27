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
class ArkTabContentComponent extends ArkComponent implements TabContentAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  tabBar(value: SubTabBarStyle | BottomTabBarStyle | ComponentContent): this {
    modifierWithKey(this._modifiersWithKeys, TabContentTabBarModifier.identity, TabContentTabBarModifier, value);
    return this;
  }
  size(value: SizeOptions): this {
    modifierWithKey(this._modifiersWithKeys, TabContentSizeModifier.identity, TabContentSizeModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, TabContentWidthModifier.identity, TabContentWidthModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, TabContentHeightModifier.identity, TabContentHeightModifier, value);
    return this;
  }
}

class TabContentTabBarModifier extends ModifierWithKey<SubTabBarStyle | BottomTabBarStyle> {
  constructor(value: SubTabBarStyle | BottomTabBarStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('tabContentTabBar');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabContent.resetTabBar(node);
    } else {
      getUINativeModule().tabContent.setTabBar(this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TabContentWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('tabcontentwidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabContent.resetTabContentWidth(node);
    } else {
      getUINativeModule().tabContent.setTabContentWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TabContentHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('tabcontentheight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabContent.resetTabContentHeight(node);
    } else {
      getUINativeModule().tabContent.setTabContentHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TabContentSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('tabcontentsize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabContent.resetTabContentSize(node);
    } else {
      getUINativeModule().tabContent.setTabContentSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}

// @ts-ignore
globalThis.TabContent.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkTabContentComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TabContentModifier(nativePtr, classType);
  });
};
