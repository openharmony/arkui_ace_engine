/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

class ArkLazyColumnLayoutComponent extends ArkComponent implements LazyColumnLayoutAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  space(value: LengthMetrics | undefined): this {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutSpaceModifier.identity, LazyColumnLayoutSpaceModifier, value);
    return this;
  }
  alignItems(value: HorizontalAlign | undefined): this {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutAlignItemsModifier.identity, LazyColumnLayoutAlignItemsModifier, value);
    return this;
  }
  sticky(value: StickyStyle): this {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutStickyModifier.identity, LazyColumnLayoutStickyModifier, value);
    return this;
  }
  header(value: CustomBuilder | ComponentContent | undefined): this {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutHeaderModifier.identity, LazyColumnLayoutHeaderModifier, value);
    return this;
  }
  footer(value: CustomBuilder | ComponentContent | undefined): this {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutFooterModifier.identity, LazyColumnLayoutFooterModifier, value);
    return this;
  }
  onVisibleIndexesChange(callback: ((start: number, end: number) => void) | undefined): this {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutOnVisibleIndexesChangeModifier.identity,
      LazyColumnLayoutOnVisibleIndexesChangeModifier, callback);
    return this;
  }
}

class LazyColumnLayoutSpaceModifier extends ModifierWithKey<LengthMetrics | undefined> {
  constructor(value: LengthMetrics | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyColumnLayoutSpace');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().lazyColumnLayout.resetSpace(node);
    } else {
      getUINativeModule().lazyColumnLayout.setSpace(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LazyColumnLayoutAlignItemsModifier extends ModifierWithKey<HorizontalAlign | undefined> {
  constructor(value: HorizontalAlign | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyColumnLayoutAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !isNumber(this.value)) {
      getUINativeModule().lazyColumnLayout.resetAlignItems(node);
    } else {
      getUINativeModule().lazyColumnLayout.setAlignItems(node, this.value);
    }
  }
}

class LazyColumnLayoutStickyModifier extends ModifierWithKey<StickyStyle> {
  constructor(value: StickyStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyColumnLayoutSticky');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !isNumber(this.value)) {
      getUINativeModule().lazyColumnLayout.resetSticky(node);
    } else {
      getUINativeModule().lazyColumnLayout.setSticky(node, this.value);
    }
  }
}

class LazyColumnLayoutHeaderModifier extends ModifierWithKey<CustomBuilder | ComponentContent | undefined> {
  constructor(value: CustomBuilder | ComponentContent | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyColumnLayoutHeader');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || (!isObject(this.value) && !isFunction(this.value))) {
      getUINativeModule().lazyColumnLayout.resetHeader(node);
    } else {
      getUINativeModule().lazyColumnLayout.setHeader(node, this.value);
    }
  }
}

class LazyColumnLayoutFooterModifier extends ModifierWithKey<CustomBuilder | ComponentContent | undefined> {
  constructor(value: CustomBuilder | ComponentContent | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyColumnLayoutFooter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || (!isObject(this.value) && !isFunction(this.value))) {
      getUINativeModule().lazyColumnLayout.resetFooter(node);
    } else {
      getUINativeModule().lazyColumnLayout.setFooter(node, this.value);
    }
  }
}

class LazyColumnLayoutOnVisibleIndexesChangeModifier extends ModifierWithKey<((start: number, end: number) => void) | undefined> {
  constructor(value: ((start: number, end: number) => void) | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyColumnLayoutOnVisibleIndexesChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !isFunction(this.value)) {
      getUINativeModule().lazyColumnLayout.resetOnVisibleIndexesChange(node);
    } else {
      getUINativeModule().lazyColumnLayout.setOnVisibleIndexesChange(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.LazyColumnLayout.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkLazyColumnLayoutComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.LazyColumnLayoutModifier(nativePtr, classType);
  });
};
