/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkPatternLockComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      sideLength(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockSideLengthModifier.identity, PatternLockSideLengthModifier, value);
        return this;
      }
      circleRadius(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockCircleRadiusModifier.identity, PatternLockCircleRadiusModifier, value);
        return this;
      }
      regularColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockRegularColorModifier.identity, PatternLockRegularColorModifier, value);
        return this;
      }
      selectedColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockSelectedColorModifier.identity, PatternLockSelectedColorModifier, value);
        return this;
      }
      activeColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockActiveColorModifier.identity, PatternLockActiveColorModifier, value);
        return this;
      }
      pathColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockPathColorModifier.identity, PatternLockPathColorModifier, value);
        return this;
      }
      pathStrokeWidth(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockPathStrokeModifier.identity, PatternLockPathStrokeModifier, value);
        return this;
      }
      autoReset(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockAutoResetModifier.identity, PatternLockAutoResetModifier, value);
        return this;
      }
      activateCircleStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockActivateCircleStyleModifier.identity, PatternLockActivateCircleStyleModifier, value);
        return this;
      }
      skipUnselectedPoint(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockSkipUnselectedPointModifier.identity, PatternLockSkipUnselectedPointModifier, value);
        return this;
      }
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockBackgroundColorModifier.identity, PatternLockBackgroundColorModifier, value);
        return this;
      }
      onPatternComplete(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockOnPatternCompleteModifer.identity, PatternLockOnPatternCompleteModifer, callback);
        return this;
      }
      onDotConnect(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, PatternLockOnDotConnectModifer.identity, PatternLockOnDotConnectModifer, callback);
        return this;
      }
    }

    class PatternLockActiveColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetActiveColor(node);
        }
        else {
          getUINativeModule().patternlock.setActiveColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PatternLockActiveColorModifier as any).identity = Symbol('patternLockActiveColor');

    class PatternLockSelectedColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetSelectedColor(node);
        }
        else {
          getUINativeModule().patternlock.setSelectedColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PatternLockSelectedColorModifier as any).identity = Symbol('patternLockSelectedColor');

    class PatternLockPathColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetPathColor(node);
        }
        else {
          getUINativeModule().patternlock.setPathColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PatternLockPathColorModifier as any).identity = Symbol('patternLockPathColor');

    class PatternLockRegularColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetRegularColor(node);
        }
        else {
          getUINativeModule().patternlock.setRegularColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PatternLockRegularColorModifier as any).identity = Symbol('patternLockRegularColor');

    class PatternLockSideLengthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetSideLength(node);
        }
        else {
          getUINativeModule().patternlock.setSideLength(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PatternLockSideLengthModifier as any).identity = Symbol('patternLockSideLength');

    class PatternLockPathStrokeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetPathStrokeWidth(node);
        }
        else {
          getUINativeModule().patternlock.setPathStrokeWidth(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (PatternLockPathStrokeModifier as any).identity = Symbol('patternLockPathStroke');

    class PatternLockCircleRadiusModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetCircleRadius(node);
        }
        else {
          getUINativeModule().patternlock.setCircleRadius(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PatternLockCircleRadiusModifier as any).identity = Symbol('patternLockCircleRadius');

    class PatternLockAutoResetModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetAutoReset(node);
        }
        else {
          getUINativeModule().patternlock.setAutoReset(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (PatternLockAutoResetModifier as any).identity = Symbol('patternlockautoreset');

    class PatternLockActivateCircleStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetActivateCircleStyle(node);
        }
        else {
          getUINativeModule().patternlock.setActivateCircleStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PatternLockActivateCircleStyleModifier as any).identity = Symbol('patternLockActivateCircleStyle');

    class PatternLockSkipUnselectedPointModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetSkipUnselectedPoint(node);
        }
        else {
          getUINativeModule().patternlock.setSkipUnselectedPoint(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (PatternLockSkipUnselectedPointModifier as any).identity = Symbol('patternlockSkipUnselectedPoint');

    class PatternLockBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().common.resetBackgroundColor(node);
        }
        else {
          getUINativeModule().common.setBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PatternLockBackgroundColorModifier as any).identity = Symbol('patternLockBackgroundColor');

    class PatternLockOnPatternCompleteModifer extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetPatternLockOnPatternComplete(node);
        } else {
          getUINativeModule().patternlock.setPatternLockOnPatternComplete(node, this.value);
        }
      }
    }
    (PatternLockOnPatternCompleteModifer as any).identity = Symbol('patternLockOnPatternComplete');

    class PatternLockOnDotConnectModifer extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().patternlock.resetPatternLockOnDotConnect(node);
        } else {
          getUINativeModule().patternlock.setPatternLockOnDotConnect(node, this.value);
        }
      }
    }
    (PatternLockOnDotConnectModifer as any).identity = Symbol('patternLockOnDotConnect');

    loadComponent.componentObj = {'component' : ArkPatternLockComponent };
  }
  return loadComponent.componentObj;
}

class JSPatternLock extends JSViewAbstract {
  static create(value: any): void {
    getUINativeModule().patternlock.create(value);
  }
  static sideLength(value: any): void {
    getUINativeModule().patternlock.setSideLength(true, value);
  }
  static circleRadius(value: any): void {
    getUINativeModule().patternlock.setCircleRadius(true, value);
  }
  static regularColor(value: any): void {
    getUINativeModule().patternlock.setRegularColor(true, value);
  }
  static selectedColor(value: any): void {
    getUINativeModule().patternlock.setSelectedColor(true, value);
  }
  static activeColor(value: any): void {
    getUINativeModule().patternlock.setActiveColor(true, value);
  }
  static pathColor(value: any): void {
    getUINativeModule().patternlock.setPathColor(true, value);
  }
  static pathStrokeWidth(value: any): void {
    getUINativeModule().patternlock.setPathStrokeWidth(true, value);
  }
  static autoReset(value: any): void {
    getUINativeModule().patternlock.setAutoReset(true, value);
  }
  static activateCircleStyle(value: any): void {
    getUINativeModule().patternlock.setActivateCircleStyle(true, value);
  }
  static skipUnselectedPoint(value: any): void {
    getUINativeModule().patternlock.setSkipUnselectedPoint(true, value);
  }
  static onPatternComplete(callback: any): void {
    getUINativeModule().patternlock.setPatternLockOnPatternComplete(true, callback);
  }
  static onDotConnect(callback: any): void {
    getUINativeModule().patternlock.setPatternLockOnDotConnect(true, callback);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return new (loadComponent as any).componentObj?.component(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.PatternLockModifier(nativePtr, classType);
    });
  }
  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }
  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }
  static onDetach(value: any): void {
    __Common__.onAttach(value);
  }
  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }
  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }
}

function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkPatternLockComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.PatternLock = JSPatternLock;
}

export default { loadComponent, createComponent, exportComponent, exportView };
