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
class ArkStepperItemComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  prevLabel(value) {
    modifierWithKey(this._modifiersWithKeys, PrevLabelModifier.identity, PrevLabelModifier, value);
    return this;
  }
  nextLabel(value) {
    modifierWithKey(this._modifiersWithKeys, NextLabelModifier.identity, NextLabelModifier, value);
    return this;
  }
  status(value) {
    modifierWithKey(this._modifiersWithKeys, StatusModifier.identity, StatusModifier, value);
    return this;
  }
}
class NextLabelModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepperItem.resetNextLabel(node);
    }
    else {
      getUINativeModule().stepperItem.setNextLabel(node, this.value);
    }
  }
}
NextLabelModifier.identity = Symbol('NextLabel');

class PrevLabelModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  static identity = Symbol('prevLabel');
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepperItem.resetPrevLabel(node);
    }
    else {
      getUINativeModule().stepperItem.setPrevLabel(node, this.value);
    }
  }
}

class StatusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  static identity = Symbol('status');
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepperItem.resetStatus(node);
    }
    else {
      getUINativeModule().stepperItem.setStatus(node, this.value);
    }
  }
}

class JSStepperItem extends JSContainerBase {
    static create() {
        getUINativeModule().stepperItem.create();
    }

    static prevLabel(value) {
        getUINativeModule().stepperItem.setPrevLabel(true, value);
    }
    static nextLabel(value) {
        getUINativeModule().stepperItem.setNextLabel(true, value);
    }
    static status(value) {
        getUINativeModule().stepperItem.setStatus(true, value);
    }
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArkStepperItemComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.StepperItemModifier(nativePtr, classType);
        });
    }

    static onClick(value) {
        __Common__.onClick(value);
    }
    static onTouch(value) {
        __Common__.onTouch(value);
    }
    static onKeyEvent(value) {
        __Common__.onKeyEvent(value);
    }
    static onDeleteEvent(value) {
        __Common__.onDeleteEvent(value);
    }
    static onDetach(value) {
        __Common__.onDetach(value);
    }
    static onDisAppear(value) {
        __Common__.onDisAppear(value);
    }
    static onAttach(value) {
        __Common__.onAttach(value);
    }
    static onAppear(value) {
        __Common__.onAppear(value);
    }
}

function createComponent(nativePtr, classType) {
    return new ArkStepperItemComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkStepperItemComponent = ArkStepperItemComponent;
}

function exportView() {
    globalThis.StepperItem = JSStepperItem;
}
function loadComponent() {}
export default { ArkStepperItemComponent, createComponent, exportComponent, exportView, loadComponent };