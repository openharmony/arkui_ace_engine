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
class PatternLockActiveColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockActiveColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetActiveColor(node);
    } else {
      getUINativeModule().patternLock.setActiveColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PatternLockSelectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockSelectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetSelectedColor(node);
    } else {
      getUINativeModule().patternLock.setSelectedColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PatternLockPathColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockPathColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetPathColor(node);
    } else {
      getUINativeModule().patternLock.setPathColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PatternLockRegularColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockRegularColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetRegularColor(node);
    } else {
      getUINativeModule().patternLock.setRegularColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PatternLockSideLengthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockSideLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetSideLength(node);
    } else {
      getUINativeModule().patternLock.setSideLength(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PatternLockPathStrokeModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockPathStroke');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetPathStrokeWidth(node);
    } else {
      getUINativeModule().patternLock.setPathStrokeWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class PatternLockCircleRadiusModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockCircleRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetCircleRadius(node);
    } else {
      getUINativeModule().patternLock.setCircleRadius(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PatternLockAutoResetModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('patternlockautoreset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetAutoReset(node);
    } else {
      getUINativeModule().patternLock.setAutoReset(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class PatternLockActivateCircleStyleModifier extends ModifierWithKey<CircleStyleOptions> {
  constructor(value: CircleStyleOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockActivateCircleStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetActivateCircleStyle(node);
    } else {
      getUINativeModule().patternLock.setActivateCircleStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PatternLockBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundColor(node);
    } else {
      getUINativeModule().common.setBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

declare type OnPatternCompleteFunc = (input: Array<number>) => void
class PatternLockOnPatternCompleteModifer extends ModifierWithKey<OnPatternCompleteFunc> {
  constructor(value: OnPatternCompleteFunc) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockOnPatternComplete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetPatternLockOnPatternComplete(node);
    } else {
      getUINativeModule().patternLock.setPatternLockOnPatternComplete(node, this.value);
    }
  }
}

declare type OnDotConnectFunc = (input: Array<number>) => void
class PatternLockOnDotConnectModifer extends ModifierWithKey<OnDotConnectFunc> {
  constructor(value: OnDotConnectFunc) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockOnDotConnect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().patternLock.resetPatternLockOnDotConnect(node);
    } else {
      getUINativeModule().patternLock.setPatternLockOnDotConnect(node, this.value);
    }
  }
}

class ArkPatternLockComponent extends ArkComponent implements PatternLockAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  sideLength(value: Length): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockSideLengthModifier.identity,
      PatternLockSideLengthModifier, value);
    return this;
  }
  circleRadius(value: Length): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockCircleRadiusModifier.identity,
      PatternLockCircleRadiusModifier, value);
    return this;
  }
  regularColor(value: ResourceColor): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockRegularColorModifier.identity,
      PatternLockRegularColorModifier, value);
    return this;
  }
  selectedColor(value: ResourceColor): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockSelectedColorModifier.identity,
      PatternLockSelectedColorModifier, value);
    return this;
  }
  activeColor(value: ResourceColor): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockActiveColorModifier.identity,
      PatternLockActiveColorModifier, value);
    return this;
  }
  pathColor(value: ResourceColor): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockPathColorModifier.identity,
      PatternLockPathColorModifier, value);
    return this;
  }
  pathStrokeWidth(value: number | string): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockPathStrokeModifier.identity,
      PatternLockPathStrokeModifier, value);
    return this;
  }
  autoReset(value: boolean): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockAutoResetModifier.identity,
      PatternLockAutoResetModifier, value);
    return this;
  }
  activateCircleStyle(value: CircleStyleOptions): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockActivateCircleStyleModifier.identity,
      PatternLockActivateCircleStyleModifier, value);
    return this;
  }
  onPatternComplete(callback: (input: Array<number>) => void): this {
    modifierWithKey(this._modifiersWithKeys, PatternLockOnPatternCompleteModifer.identity,
      PatternLockOnDotConnectModifer, callback);
    return this;
  }
  onDotConnect(callback: any): this {
    modifierWithKey(this._modifiersWithKeys, PatternLockOnDotConnectModifer.identity,
      PatternLockOnDotConnectModifer, callback);
    return this;
  }
  backgroundColor(value: ResourceColor): PatternLockAttribute {
    modifierWithKey(this._modifiersWithKeys, PatternLockBackgroundColorModifier.identity,
      PatternLockBackgroundColorModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.PatternLock.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkPatternLockComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.PatternLockModifier(nativePtr, classType);
  });
};
