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
/// <reference path="./ArkComponent.ts" />
const FontWeightMap = {
  0: 'lighter',
  1: 'normal',
  2: 'regular',
  3: 'medium',
  4: 'bold',
  5: 'bolder',
  100: '100',
  200: '200',
  300: '300',
  400: '400',
  500: '500',
  600: '600',
  700: '700',
  800: '800',
  900: '900',
}

class ArkButtonComponent extends ArkComponent implements ButtonAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ButtonBackgroundColorModifier.identity, ButtonBackgroundColorModifier, value);
    return this;
  }
  type (value: ButtonType): this {
    modifierWithKey(this._modifiersWithKeys, ButtonTypeModifier.identity, ButtonTypeModifier, value);
    return this;
  }
  stateEffect(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ButtonStateEffectModifier.identity, ButtonStateEffectModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ButtonFontColorModifier.identity, ButtonFontColorModifier, value);
    return this;
  }
  fontSize(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, ButtonFontSizeModifier.identity, ButtonFontSizeModifier, value);
    return this;
  }
  fontWeight(value: string | number | FontWeight): this {
    modifierWithKey(this._modifiersWithKeys, ButtonFontWeightModifier.identity, ButtonFontWeightModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): this {
    modifierWithKey(this._modifiersWithKeys, ButtonFontStyleModifier.identity, ButtonFontStyleModifier, value);
    return this;
  }
  fontFamily(value: string | Resource): this {
    modifierWithKey(this._modifiersWithKeys, ButtonFontFamilyModifier.identity, ButtonFontFamilyModifier, value);
    return this;
  }
  labelStyle(value: LabelStyle): this {
    modifierWithKey(this._modifiersWithKeys, ButtonLabelStyleModifier.identity,ButtonLabelStyleModifier, value);
    return this;
  }
  borderRadius(value: Length | BorderRadiuses): this {
    modifierWithKey(this._modifiersWithKeys, ButtonBorderRadiusModifier.identity, ButtonBorderRadiusModifier, value);
    return this;
  }
}
class ButtonBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("buttonBackgroundColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetBackgroundColor(node);
    } else {
      GetUINativeModule().button.setBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}
class ButtonStateEffectModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonStateEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetStateEffect(node);
    }
    else {
      GetUINativeModule().button.setStateEffect(node, this.value);
    }
  }
}
class ButtonFontStyleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetFontStyle(node);
    }
    else {
      GetUINativeModule().button.setFontStyle(node, this.value);
    }
  }
}
class ButtonFontFamilyModifier extends ModifierWithKey<string | Resource> {
  constructor(value: string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
        GetUINativeModule().button.resetFontFamily(node);
      }
      else {
        GetUINativeModule().button.setFontFamily(node, this.value);
      }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else {
      return true;
    }
  }
}
class ButtonLabelStyleModifier extends ModifierWithKey<LabelStyle> {
  constructor(value: LabelStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonLabelStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
        GetUINativeModule().button.resetLabelStyle(node);
    }
    else {
      let textOverflow = this.value.overflow; // number(enum) -> Ace::TextOverflow
      let maxLines = this.value.maxLines; // number -> uint32_t
      let minFontSize = this.value.minFontSize; // number | string | Resource -> Dimension
      let maxFontSize = this.value.maxFontSize; // number | string | Resource -> Dimension
      let heightAdaptivePolicy = this.value.heightAdaptivePolicy; // number(enum) -> Ace::TextHeightAdaptivePolicy
      let fontSize = undefined; // number | string | Resource -> Dimension
      let fontWeight = undefined; // number | string | Ace::FontWeight -> string -> Ace::FontWeight
      let fontStyle = undefined; // number(enum) -> Ace::FontStyle
      let fontFamily = undefined; // string -> std::vector<std::string>
      if (isObject(this.value.font))
      {
        fontSize = this.value.font.size;
        fontStyle = this.value.font.style;
        fontFamily = this.value.font.family;
        fontWeight = this.value.font.weight;
      }
      GetUINativeModule().button.setLabelStyle(node, textOverflow, maxLines, minFontSize, maxFontSize,
        heightAdaptivePolicy, fontSize, fontWeight, fontStyle, fontFamily);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }else if(!isResource(this.stageValue) && !isResource(this.value)){
      return !(this.value.overflow === this.stageValue.overflow &&
        this.value.maxLines === this.stageValue.maxLines &&
        this.value.minFontSize === this.stageValue.minFontSize &&
        this.value.maxFontSize === this.stageValue.maxFontSize  &&
        this.value.heightAdaptivePolicy === this.stageValue.heightAdaptivePolicy &&
        this.value.font === this.stageValue.font)
    }
    else {
      return true;
    }
  }
}
class ButtonTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetType(node);
    }
    else {
      GetUINativeModule().button.setType(node, this.value);
    }
  }
}
class ButtonFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetFontColor(node);
    }
    else {
      GetUINativeModule().button.setFontColor(node, this.value);
    }
  }
  
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } 
    else {
      return true;
    }
  }
}
class ButtonFontSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetFontSize(node);
    }
    else {
      GetUINativeModule().button.setFontSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else {
      return true;
    }
  }
}
class ButtonFontWeightModifier extends ModifierWithKey<string | number | FontWeight> {
  constructor(value: string | number | FontWeight) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetFontWeight(node);
    }
    else {
      GetUINativeModule().button.setFontWeight(node, this.value);
    }
  }
}

class ButtonBorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses> {
  constructor(value: Length | BorderRadiuses) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonBorderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetButtonBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        GetUINativeModule().button.setButtonBorderRadius(node, this.value, this.value, this.value, this.value);
      } else {
        GetUINativeModule().button.setButtonBorderRadius(node,
          (this.value as BorderRadiuses).topLeft,
          (this.value as BorderRadiuses).topRight,
          (this.value as BorderRadiuses).bottomLeft,
          (this.value as BorderRadiuses).bottomRight);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
    } else {
      return true;
    }
  }
}
// @ts-ignore
globalThis.Button.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkButtonComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
