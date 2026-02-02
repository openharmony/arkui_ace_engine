/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
class ArkSymbolGlyphComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(
        this._modifiersWithKeys,
        SymbolContentModifier.identity,
        SymbolContentModifier,
        value[0]
      );
    } else {
      modifierWithKey(
        this._modifiersWithKeys,
        SymbolContentModifier.identity,
        SymbolContentModifier,
        undefined
      );
    }
    return this;
  }
  fontColor(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      SymbolFontColorModifier.identity,
      SymbolFontColorModifier,
      value
    );
    return this;
  }
  fontSize(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      SymbolFontSizeModifier.identity,
      SymbolFontSizeModifier,
      value
    );
    return this;
  }
  fontWeight(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      SymbolFontWeightModifier.identity,
      SymbolFontWeightModifier,
      value
    );
    return this;
  }
  renderingStrategy(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      RenderingStrategyModifier.identity,
      RenderingStrategyModifier,
      value
    );
    return this;
  }
  effectStrategy(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      EffectStrategyModifier.identity,
      EffectStrategyModifier,
      value
    );
    return this;
  }
  symbolEffect(effect, action) {
    let symbolEffect = new ArkSymbolEffect();
    symbolEffect.symbolEffect = effect;
    symbolEffect.action = action;
    modifierWithKey(
      this._modifiersWithKeys,
      SymbolEffectModifier.identity,
      SymbolEffectModifier,
      symbolEffect
    );
    return this;
  }
  shaderStyle(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      ShaderStyleModifier.identity,
      ShaderStyleModifier,
      value
    );
    return this;
  }
  symbolShadow(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      SymbolShadowModifier.identity,
      SymbolShadowModifier,
      value
    );
    return this;
  }
  minFontScale(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      SymbolMinFontScaleModifier.identity,
      SymbolMinFontScaleModifier,
      value
    );
    return this;
  }
  maxFontScale(value) {
    modifierWithKey(
      this._modifiersWithKeys,
      SymbolMaxFontScaleModifier.identity,
      SymbolMaxFontScaleModifier,
      value
    );
    return this;
  }
}

class SymbolFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetFontColor(node);
    } else {
      getUINativeModule().symbolGlyph.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SymbolFontColorModifier.identity = Symbol("symbolGlyphFontColor");

class SymbolFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetFontSize(node);
    } else {
      getUINativeModule().symbolGlyph.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SymbolFontSizeModifier.identity = Symbol("symbolGlyphFontSize");

class SymbolFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetFontWeight(node);
    } else {
      getUINativeModule().symbolGlyph.setFontWeight(node, this.value);
    }
  }
}
SymbolFontWeightModifier.identity = Symbol("symbolGlyphFontWeight");

class RenderingStrategyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetRenderingStrategy(node);
    } else {
      getUINativeModule().symbolGlyph.setRenderingStrategy(node, this.value);
    }
  }
}
RenderingStrategyModifier.identity = Symbol("symbolGlyphRenderingStrategy");

class EffectStrategyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetEffectStrategy(node);
    } else {
      getUINativeModule().symbolGlyph.setEffectStrategy(node, this.value);
    }
  }
}
EffectStrategyModifier.identity = Symbol("symbolGlyphEffectStrategy");

class SymbolContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetSymbolGlyphInitialize(node);
    } else {
      getUINativeModule().symbolGlyph.setSymbolGlyphInitialize(
        node,
        this.value
      );
    }
  }
}
SymbolContentModifier.identity = Symbol("symbolContent");

class SymbolEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetSymbolEffectOptions(node);
    } else {
      getUINativeModule().symbolGlyph.setSymbolEffectOptions(
        node,
        this.value.symbolEffect,
        this.value.action
      );
    }
  }
}
SymbolEffectModifier.identity = Symbol("symbolEffect");

class SymbolShadowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetSymbolShadow(node);
    } else {
      getUINativeModule().symbolGlyph.setSymbolShadow(node, this.value);
    }
  }
}
SymbolShadowModifier.identity = Symbol("symbolShadow");

class ShaderStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetShaderStyle(node);
    } else {
      getUINativeModule().symbolGlyph.setShaderStyle(node, this.value);
    }
  }
}
ShaderStyleModifier.identity = Symbol("shaderStyle");

class SymbolMinFontScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetMinFontScale(node);
    } else {
      getUINativeModule().symbolGlyph.setMinFontScale(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SymbolMinFontScaleModifier.identity = Symbol("symbolGlyphMinFontScale");

class SymbolMaxFontScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().symbolGlyph.resetMaxFontScale(node);
    } else {
      getUINativeModule().symbolGlyph.setMaxFontScale(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SymbolMaxFontScaleModifier.identity = Symbol("symbolGlyphMaxFontScale");

class JSSymbolGlyph extends JSViewAbstract {
  static create(params) {
    getUINativeModule().symbolGlyph.create(params);
  }
  static fontColor(value) {
    getUINativeModule().symbolGlyph.setFontColor(true, value);
  }
  static fontSize(value) {
    getUINativeModule().symbolGlyph.setFontSize(true, value);
  }
  static fontWeight(value) {
    getUINativeModule().symbolGlyph.setFontWeight(true, value);
  }
  static renderingStrategy(value) {
    getUINativeModule().symbolGlyph.setRenderingStrategy(true, value);
  }
  static effectStrategy(value) {
    getUINativeModule().symbolGlyph.setEffectStrategy(true, value);
  }
  static symbolEffect(effect, action) {
    getUINativeModule().symbolGlyph.setSymbolEffectOptions(true, effect, action);
  }
  static shaderStyle(value) {
    getUINativeModule().symbolGlyph.setShaderStyle(true, value);
  }
  static symbolShadow(value) {
    getUINativeModule().symbolGlyph.setSymbolShadow(true, value);
  }
  static minFontScale(value) {
    getUINativeModule().symbolGlyph.setMinFontScale(true, value);
  }
  static maxFontScale(value) {
    getUINativeModule().symbolGlyph.setMaxFontScale(true, value);
  }
  static clip(value) {
    JSViewAbstract.clip(value);
    getUINativeModule().symbolGlyph.clip(true, value);
  }
  static attributeModifier(modifier) {
 	  attributeModifierFunc.call(this, modifier, (nativePtr) => {
 	    return new ArkSymbolGlyphComponent(nativePtr);
 	  }, (nativePtr, classType, modifierJS) => {
 	    return new modifierJS.SymbolGlyphModifier(undefined, nativePtr, classType);
 	  });
 	}
  static onTouch(value) {
    __Common__.onTouch(value);
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
  
}

function createComponent(nativePtr, classType) {
  return new ArkSymbolGlyphComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkSymbolGlyphComponent = ArkSymbolGlyphComponent;
}

function exportView() {
  globalThis.SymbolGlyph = JSSymbolGlyph;
}

export default { ArkSymbolGlyphComponent, createComponent, exportComponent, exportView };