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
class PatternLockActiveColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetActiveColor(node);
    }
    else {
      getUINativeModule().patternlock.setActiveColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockActiveColorModifier.identity = Symbol('patternLockActiveColor');
class PatternLockSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetSelectedColor(node);
    }
    else {
      getUINativeModule().patternlock.setSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockSelectedColorModifier.identity = Symbol('patternLockSelectedColor');
class PatternLockPathColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetPathColor(node);
    }
    else {
      getUINativeModule().patternlock.setPathColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockPathColorModifier.identity = Symbol('patternLockPathColor');
class PatternLockRegularColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetRegularColor(node);
    }
    else {
      getUINativeModule().patternlock.setRegularColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockRegularColorModifier.identity = Symbol('patternLockRegularColor');
class PatternLockSideLengthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetSideLength(node);
    }
    else {
      getUINativeModule().patternlock.setSideLength(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockSideLengthModifier.identity = Symbol('patternLockSideLength');
class PatternLockPathStrokeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetPathStrokeWidth(node);
    }
    else {
      getUINativeModule().patternlock.setPathStrokeWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
PatternLockPathStrokeModifier.identity = Symbol('patternLockPathStroke');
class PatternLockCircleRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetCircleRadius(node);
    }
    else {
      getUINativeModule().patternlock.setCircleRadius(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockCircleRadiusModifier.identity = Symbol('patternLockCircleRadius');
class PatternLockAutoResetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetAutoReset(node);
    }
    else {
      getUINativeModule().patternlock.setAutoReset(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
PatternLockAutoResetModifier.identity = Symbol('patternlockautoreset');
class PatternLockActivateCircleStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetActivateCircleStyle(node);
    }
    else {
      getUINativeModule().patternlock.setActivateCircleStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockActivateCircleStyleModifier.identity = Symbol('patternLockActivateCircleStyle');
class PatternLockSkipUnselectedPointModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetSkipUnselectedPoint(node);
    }
    else {
      getUINativeModule().patternlock.setSkipUnselectedPoint(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
PatternLockSkipUnselectedPointModifier.identity = Symbol('patternlockSkipUnselectedPoint');
class PatternLockBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBackgroundColor(node);
    }
    else {
      getUINativeModule().common.setBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockBackgroundColorModifier.identity = Symbol('patternLockBackgroundColor');

class PatternLockOnPatternCompleteModifer extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetPatternLockOnPatternComplete(node);
    } else {
      getUINativeModule().patternlock.setPatternLockOnPatternComplete(node, this.value);
    }
  }
}
PatternLockOnPatternCompleteModifer.identity = Symbol('patternLockOnPatternComplete');

class PatternLockOnDotConnectModifer extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternlock.resetPatternLockOnDotConnect(node);
    } else {
      getUINativeModule().patternlock.setPatternLockOnDotConnect(node, this.value);
    }
  }
}
PatternLockOnDotConnectModifer.identity = Symbol('patternLockOnDotConnect');

class ArkPatternLockComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  sideLength(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockSideLengthModifier.identity, PatternLockSideLengthModifier, value);
    return this;
  }
  circleRadius(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockCircleRadiusModifier.identity, PatternLockCircleRadiusModifier, value);
    return this;
  }
  regularColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockRegularColorModifier.identity, PatternLockRegularColorModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockSelectedColorModifier.identity, PatternLockSelectedColorModifier, value);
    return this;
  }
  activeColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockActiveColorModifier.identity, PatternLockActiveColorModifier, value);
    return this;
  }
  pathColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockPathColorModifier.identity, PatternLockPathColorModifier, value);
    return this;
  }
  pathStrokeWidth(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockPathStrokeModifier.identity, PatternLockPathStrokeModifier, value);
    return this;
  }
  autoReset(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockAutoResetModifier.identity, PatternLockAutoResetModifier, value);
    return this;
  }
  activateCircleStyle(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockActivateCircleStyleModifier.identity, PatternLockActivateCircleStyleModifier, value);
    return this;
  }
  skipUnselectedPoint(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockSkipUnselectedPointModifier.identity, PatternLockSkipUnselectedPointModifier, value);
    return this;
  }
  backgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockBackgroundColorModifier.identity,
        PatternLockBackgroundColorModifier, value);
    return this;
  }
  onPatternComplete(callback) {
    modifierWithKey(this._modifiersWithKeys, PatternLockOnPatternCompleteModifer.identity, PatternLockOnPatternCompleteModifer, callback);
    return this;
  }
  onDotConnect(callback) {
    modifierWithKey(this._modifiersWithKeys, PatternLockOnDotConnectModifer.identity, PatternLockOnDotConnectModifer, callback);
    return this;
  }
}

class JSPatternLock extends JSViewAbstract {
    static create(value) {
        getUINativeModule().patternlock.create(value);
    }

    static sideLength(value) {
        getUINativeModule().patternlock.setSideLength(true, value);
    }
    static circleRadius(value) {
        getUINativeModule().patternlock.setCircleRadius(true, value);
    }
    static regularColor(value) {
        getUINativeModule().patternlock.setRegularColor(true, value);
    }
    static selectedColor(value) {
        getUINativeModule().patternlock.setSelectedColor(true, value);
    }
    static activeColor(value) {
        getUINativeModule().patternlock.setActiveColor(true, value);
    }
    static pathColor(value) {
        getUINativeModule().patternlock.setPathColor(true, value);
    }
    static pathStrokeWidth(value) {
        getUINativeModule().patternlock.setPathStrokeWidth(true, value);
    }
    static autoReset(value) {
        getUINativeModule().patternlock.setAutoReset(true, value);
    }
    static activateCircleStyle(value) {
        getUINativeModule().patternlock.setActivateCircleStyle(true, value);
    }
    static skipUnselectedPoint(value) {
        getUINativeModule().patternlock.setSkipUnselectedPoint(true, value);
    }
    static onPatternComplete(callback) {
        getUINativeModule().patternlock.setPatternLockOnPatternComplete(true, callback);
    }
    static onDotConnect(callback) {
        getUINativeModule().patternlock.setPatternLockOnDotConnect(true, callback);
    }

    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArkPatternLockComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.PatternLockModifier(nativePtr, classType);
        });
    }

    static onAttach(value) {
        __Common__.onAttach(value);
    }
    static onAppear(value) {
        __Common__.onAppear(value);
    }
    static onDetach(value) {
        __Common__.onAttach(value);
    }
    static onDisAppear(value) {
        __Common__.onDisAppear(value);
    }

    static onTouch(value) {
        __Common__.onTouch(value);
    }
}

function createComponent(nativePtr, classType) {
    return new ArkPatternLockComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkPatternLockComponent = ArkPatternLockComponent;
}

function exportView() {
    globalThis.PatternLock = JSPatternLock;
}
function loadComponent() {}
export default { ArkPatternLockComponent, createComponent, exportComponent, exportView, loadComponent };