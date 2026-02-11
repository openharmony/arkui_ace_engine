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

/// <reference path='./import.ts' />
function loadComponent() {
  if (globalThis.__ArkComponent__ !== undefined && loadComponent.componentObj === undefined) {
    class ArkCounterComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr, classType) {
        super(nativePtr, classType);
      }
      onInc(event) {
        modifierWithKey(this._modifiersWithKeys, CounterOnIncModifier.identity, CounterOnIncModifier, event);
        return this;
      }
      onDec(event) {
        modifierWithKey(this._modifiersWithKeys, CounterOnDecModifier.identity, CounterOnDecModifier, event);
        return this;
      }
      enableDec(value) {
        modifierWithKey(this._modifiersWithKeys, EnableDecModifier.identity, EnableDecModifier, value);
        return this;
      }
      enableInc(value) {
        modifierWithKey(this._modifiersWithKeys, EnableIncModifier.identity, EnableIncModifier, value);
        return this;
      }
      backgroundColor(value) {
        modifierWithKey(this._modifiersWithKeys, CounterBackgroundColorModifier.identity, CounterBackgroundColorModifier, value);
        return this;
      }
      width(value) {
        modifierWithKey(this._modifiersWithKeys, CounterWidthModifier.identity, CounterWidthModifier, value);
        return this;
      }
      height(value) {
        modifierWithKey(this._modifiersWithKeys, CounterHeightModifier.identity, CounterHeightModifier, value);
        return this;
      }
      size(value) {
        modifierWithKey(this._modifiersWithKeys, CounterSizeModifier.identity, CounterSizeModifier, value);
        return this;
      }
    }
    
    class CounterOnIncModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().counter.resetCounterOnInc(node);
        } else {
          getUINativeModule().counter.setCounterOnInc(node, this.value);
        }
      }
    }
    CounterOnIncModifier.identity = Symbol('counterOnInc');
    
    class CounterOnDecModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().counter.resetCounterOnDec(node);
        } else {
          getUINativeModule().counter.setCounterOnDec(node, this.value);
        }
      }
    }
    CounterOnDecModifier.identity = Symbol('counterOnDec');
    
    class CounterHeightModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().counter.resetCounterHeight(node);
        }
        else {
          getUINativeModule().counter.setCounterHeight(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    CounterHeightModifier.identity = Symbol('CounterHeight');
    class CounterWidthModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().counter.resetCounterWidth(node);
        }
        else {
          getUINativeModule().counter.setCounterWidth(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    CounterWidthModifier.identity = Symbol('CounterWidth');
    class CounterBackgroundColorModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().counter.resetCounterBackgroundColor(node);
        }
        else {
          getUINativeModule().counter.setCounterBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    CounterBackgroundColorModifier.identity = Symbol('CounterBackgroundColor');
    class CounterSizeModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().counter.resetCounterSize(node);
        }
        else {
          getUINativeModule().counter.setCounterSize(node, this.value.width, this.value.height);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
          !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
      }
    }
    CounterSizeModifier.identity = Symbol('CounterSize');
    class EnableIncModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().counter.resetEnableInc(node);
        }
        else {
          getUINativeModule().counter.setEnableInc(node, this.value);
        }
      }
    }
    EnableIncModifier.identity = Symbol('enableInc');
    class EnableDecModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().counter.resetEnableDec(node);
        }
        else {
          getUINativeModule().counter.setEnableDec(node, this.value);
        }
      }
    }
    EnableDecModifier.identity = Symbol('enableDec');
    loadComponent.componentObj = {'component' : ArkCounterComponent };
  }
}

class JSCounter extends JSViewAbstract {
    static create(params) {
        if (params !== undefined) {
            getUINativeModule().counter.create();
        } else {
            getUINativeModule().counter.create();
        }
    }

    static onInc(event) {
        getUINativeModule().counter.setCounterOnInc(true, event);
    }
    static onDec(event) {
        getUINativeModule().counter.setCounterOnDec(true, event);
    }

    static enableDec(value) {
        getUINativeModule().counter.setEnableDec(true, value);
    }

    static enableInc(value) {
        getUINativeModule().counter.setEnableInc(true, value);
    }

    static backgroundColor(value) {
        getUINativeModule().counter.setCounterBackgroundColor(true, value);
    }

    static width(value) {
        getUINativeModule().counter.setCounterWidth(true, value);
    }

    static height(value) {
        getUINativeModule().counter.setCounterHeight(true, value);
    }

    static size(value) {
        if (value !== undefined && value !== null) {
            getUINativeModule().counter.setCounterSize(true, value.width, value.height);
        }
    }

    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return createComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.CounterModifier(nativePtr, classType);
        });
    }

    static onAttach(value) {
        __Common__.onAttach(value);
    }
    static onAppear(value) {
        __Common__.onAppear(value);
    }
    static onDetach(value) {
        __Common__.onDetach(value);
    }
    static onDisAppear(value) {
        __Common__.onDisAppear(value);
    }
    static onTouch(value) {
        __Common__.onTouch(value);
    }
}

function createComponent(nativePtr, classType) {
 	if (loadComponent.componentObj !== undefined) {
 	    return new loadComponent.componentObj.component(nativePtr, classType);
 	}
    return undefined;
}

function exportComponent() {
    globalThis.ArkCounterComponent = ArkCounterComponent;
}

function exportView() {
    globalThis.Counter = JSCounter;
}

export default { loadComponent, createComponent, exportComponent, exportView };
