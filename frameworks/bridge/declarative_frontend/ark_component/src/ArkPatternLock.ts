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

/// <reference path="./import.ts" />
class PatternLockActiveColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('patternLockActiveColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetActiveColor(node);
    } else {
      GetUINativeModule().patternLock.setActiveColor(node, this.value!);
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
      GetUINativeModule().patternLock.resetSelectedColor(node);
    } else {
      GetUINativeModule().patternLock.setSelectedColor(node, this.value!);
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
      GetUINativeModule().patternLock.resetPathColor(node);
    } else {
      GetUINativeModule().patternLock.setPathColor(node, this.value!);
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
      GetUINativeModule().patternLock.resetRegularColor(node);
    } else {
      GetUINativeModule().patternLock.setRegularColor(node, this.value!);
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
      GetUINativeModule().patternLock.resetSideLength(node);
    } else {
      GetUINativeModule().patternLock.setSideLength(node, this.value!);
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
      GetUINativeModule().patternLock.resetPathStrokeWidth(node);
    } else {
      GetUINativeModule().patternLock.setPathStrokeWidth(node, this.value!);
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
      GetUINativeModule().patternLock.resetCircleRadius(node);
    } else {
      GetUINativeModule().patternLock.setCircleRadius(node, this.value!);
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
      GetUINativeModule().patternLock.resetAutoReset(node);
    } else {
      GetUINativeModule().patternLock.setAutoReset(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArkPatternLockComponent extends ArkComponent implements PatternLockAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
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
  onPatternComplete(callback: (input: Array<number>) => void): PatternLockAttribute {
    throw new Error('Method not implemented.');
  }
  onDotConnect(callback: any): PatternLockAttribute {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.PatternLock.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPatternLockComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
