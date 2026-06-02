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

class BlankColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('blankColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().blank.resetColor(node);
    } else {
      getUINativeModule().blank.setColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BlankHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('blankHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().blank.resetBlankHeight(node);
    } else {
      getUINativeModule().blank.setBlankHeight(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}


class BlankMinModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('blankMin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().blank.resetBlankMin(node);
    } else {
      getUINativeModule().blank.setBlankMin(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkBlankComponent extends ArkComponent {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  color(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, BlankColorModifier.identity, BlankColorModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, BlankHeightModifier.identity, BlankHeightModifier, value);
    return this;
  }

  initialize(value : Object[]): this{
    if (value[0] !== undefined){
      modifierWithKey(this._modifiersWithKeys, BlankMinModifier.identity, BlankMinModifier, value[0]);
    }
    return this;
  }

  allowChildCount(): number {
    return 0;
  }
}

// @ts-ignore
if (globalThis.Blank !== undefined) {
  (globalThis as any).Blank.attributeModifier = function (modifier: ArkComponent): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
      return new ArkBlankComponent(nativePtr);
    }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
      return new modifierJS.BlankModifier(nativePtr, classType);
    });
  };
}

// @ts-ignore
globalThis.applySymbolGlyphModifierToNode = function (modifier: ArkComponent, nodePtr: KNode): void {
  getUINativeModule().loadNativeModule('SymbolGlyph');
  let module = globalThis.requireNapi('arkui.components.arksymbolglyph');
  let component = module.createComponent(nodePtr);
  applyUIAttributes(modifier as any, nodePtr, component);
  component.applyModifierPatch();
};

// @ts-ignore
globalThis.applyImageModifierToNode = function (modifier: ArkComponent, nodePtr: KNode): void {
  let component = new ArkImageComponent(nodePtr);
  applyUIAttributes(modifier as any, nodePtr, component);
  component.applyModifierPatch();
};

// @ts-ignore
globalThis.applyTextModifierToNode = function (modifier: ArkComponent, nodePtr: KNode): void {
  let component = new ArkTextComponent(nodePtr);
  applyUIAttributes(modifier as any, nodePtr, component);
  component.applyModifierPatch();
};

// @ts-ignore
globalThis.applyCommonModifierToNode = function (modifier: ArkComponent, nodePtr: KNode): void {
  let component = new ArkComponent(nodePtr);
  applyUIAttributes(modifier as any, nodePtr, component);
  component.applyModifierPatch();
};
