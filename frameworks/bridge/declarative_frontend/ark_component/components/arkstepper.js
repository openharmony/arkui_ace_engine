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
class ArkStepperComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onFinish(callback) {
    modifierWithKey(this._modifiersWithKeys, StepperOnFinishModifier.identity, StepperOnFinishModifier, callback);
    return this;
  }
  onSkip(callback) {
    modifierWithKey(this._modifiersWithKeys, StepperOnSkipModifier.identity, StepperOnSkipModifier, callback);
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, StepperOnChangeModifier.identity, StepperOnChangeModifier, callback);
    return this;
  }
  onNext(callback) {
    modifierWithKey(this._modifiersWithKeys, StepperOnNextModifier.identity, StepperOnNextModifier, callback);
    return this;
  }
  onPrevious(callback) {
    modifierWithKey(this._modifiersWithKeys, StepperOnPreviousModifier.identity, StepperOnPreviousModifier, callback);
    return this;
  }
}

class StepperOnFinishModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepper.resetOnFinish(node);
    }
    else {
      getUINativeModule().stepper.setOnFinish(node, this.value);
    }
  }
}
StepperOnFinishModifier.identity = Symbol('onFinish');

class StepperOnSkipModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepper.resetOnSkip(node);
    }
    else {
      getUINativeModule().stepper.setOnSkip(node, this.value);
    }
  }
}
StepperOnSkipModifier.identity = Symbol('onSkip');

class StepperOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepper.resetOnChange(node);
    }
    else {
      getUINativeModule().stepper.setOnChange(node, this.value);
    }
  }
}
StepperOnChangeModifier.identity = Symbol('onChange');

class StepperOnNextModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepper.resetOnNext(node);
    }
    else {
      getUINativeModule().stepper.setOnNext(node, this.value);
    }
  }
}
StepperOnNextModifier.identity = Symbol('onNext');

class StepperOnPreviousModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepper.resetOnPrevious(node);
    }
    else {
      getUINativeModule().stepper.setOnPrevious(node, this.value);
    }
  }
}
StepperOnPreviousModifier.identity = Symbol('onPrevious');

class JSStepper extends JSViewAbstract {
    static create(params) {
        getUINativeModule().stepper.create(params);
    }

    static onFinish(callback) {
        getUINativeModule().stepper.setOnFinish(true, callback);
        return this;
    }
    static onSkip(callback) {
        getUINativeModule().stepper.setOnSkip(true, callback);
        return this;
    }
    static onChange(callback) {
        getUINativeModule().stepper.setOnChange(true, callback);
        return this;
    }
    static onNext(callback) {
        getUINativeModule().stepper.setOnNext(true, callback);
        return this;
    }
    static onPrevious(callback) {
        getUINativeModule().stepper.setOnPrevious(true, callback);
        return this;
    }
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArkStepperComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.StepperModifier(nativePtr, classType);
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
    return new ArkStepperComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkStepperComponent = ArkStepperComponent;
}

function exportView() {
    globalThis.Stepper = JSStepper;
}

export default { ArkStepperComponent, createComponent, exportComponent, exportView };