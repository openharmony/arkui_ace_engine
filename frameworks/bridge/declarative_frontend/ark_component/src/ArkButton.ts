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
};

class ArkButtonComponent extends ArkComponent implements ButtonAttribute {
  builder: WrappedBuilder<Object[]> | null = null;
  buttonNode: BuilderNode<[ButtonConfiguration]> | null = null;
  modifier: ContentModifier<ButtonConfiguration>;
  needRebuild: boolean = false;
  applyContent: WrappedBuilder<[ButtonConfiguration]>;
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
    this._needDiff = false;
  }
  allowChildCount(): number {
    return 1;
  }
  initialize(value: Object[]): this {
    if (value.length >= 1 && (isResource(value[0]) || isString(value[0]))) {
      modifierWithKey(this._modifiersWithKeys, ButtonCreateTypeModifier.identity, ButtonCreateTypeModifier, true);
    } else {
      modifierWithKey(this._modifiersWithKeys, ButtonCreateTypeModifier.identity, ButtonCreateTypeModifier, false);
    }
    if (value.length === 1) {
      if (!isNull(value[0]) && isObject(value[0])) {
        modifierWithKey(this._modifiersWithKeys, ButtonOptionsModifier.identity, ButtonOptionsModifier, value[0]);
      } else if (isResource(value[0]) || isString(value[0])) {
        modifierWithKey(this._modifiersWithKeys, ButtonLabelModifier.identity, ButtonLabelModifier, value[0]);
      } else {
        modifierWithKey(this._modifiersWithKeys, ButtonLabelModifier.identity, ButtonLabelModifier, undefined);
        modifierWithKey(this._modifiersWithKeys, ButtonOptionsModifier.identity, ButtonOptionsModifier, undefined);
      }
    } else if (value.length === 2) {
      modifierWithKey(this._modifiersWithKeys, ButtonLabelModifier.identity, ButtonLabelModifier, value[0]);
      modifierWithKey(this._modifiersWithKeys, ButtonOptionsModifier.identity, ButtonOptionsModifier, value[1]);
    } else {
      modifierWithKey(this._modifiersWithKeys, ButtonLabelModifier.identity, ButtonLabelModifier, undefined);
      modifierWithKey(this._modifiersWithKeys, ButtonOptionsModifier.identity, ButtonOptionsModifier, undefined);
    }
    return this;
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ButtonBackgroundColorModifier.identity, ButtonBackgroundColorModifier, value);
    return this;
  }
  type(value: ButtonType): this {
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
    modifierWithKey(this._modifiersWithKeys, ButtonLabelStyleModifier.identity, ButtonLabelStyleModifier, value);
    return this;
  }
  borderRadius(value: Length | BorderRadiuses): this {
    modifierWithKey(this._modifiersWithKeys, ButtonBorderRadiusModifier.identity, ButtonBorderRadiusModifier, value);
    return this;
  }
  border(value: BorderOptions): this {
    modifierWithKey(this._modifiersWithKeys, ButtonBorderModifier.identity, ButtonBorderModifier, value);
    return this;
  }
  size(value: SizeOptions): this {
    modifierWithKey(this._modifiersWithKeys, ButtonSizeModifier.identity, ButtonSizeModifier, value);
    return this;
  }
  contentModifier(value: ContentModifier<ButtonConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, ButtonContentModifier.identity, ButtonContentModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<ButtonConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().button.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    this.applyContent = modifier.applyContent();
    if (this.builder !== this.applyContent) {
      this.needRebuild = true;
    }
    this.builder = this.applyContent;
    this.modifier = modifier;
    getUINativeModule().button.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, buttonConfiguration: ButtonConfiguration): FrameNode | null {
    buttonConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.buttonNode) || this.needRebuild) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.buttonNode = new xNode.BuilderNode(context);
      this.buttonNode.build(this.builder, buttonConfiguration);
      this.needRebuild = false;
    } else {
      this.buttonNode.update(buttonConfiguration);
    }
    return this.buttonNode.getFrameNode();
  }
  role(value: ButtonRole): this {
    modifierWithKey(this._modifiersWithKeys, ButtonRoleModifier.identity, ButtonRoleModifier, value);
    return this;
  }
  buttonStyle(value: ButtonStyleMode): this {
    modifierWithKey(this._modifiersWithKeys, ButtonStyleModifier.identity, ButtonStyleModifier, value);
    return this;
  }
  controlSize(value: ControlSize): this {
    modifierWithKey(this._modifiersWithKeys, ButtonControlSizeModifier.identity, ButtonControlSizeModifier, value);
    return this;
  }
  minFontScale(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, ButtonMinFontScaleModifier.identity, ButtonMinFontScaleModifier, value);
    return this;
  }
  maxFontScale(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, ButtonMaxFontScaleModifier.identity, ButtonMaxFontScaleModifier, value);
    return this;
  }
}
class ButtonBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetBackgroundColor(node);
    } else {
      getUINativeModule().button.setBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ButtonStateEffectModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonStateEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetStateEffect(node);
    } else {
      getUINativeModule().button.setStateEffect(node, this.value);
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
      getUINativeModule().button.resetFontStyle(node);
    } else {
      getUINativeModule().button.setFontStyle(node, this.value);
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
      getUINativeModule().button.resetFontFamily(node);
    } else {
      getUINativeModule().button.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ButtonLabelStyleModifier extends ModifierWithKey<LabelStyle> {
  constructor(value: LabelStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonLabelStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetLabelStyle(node);
    } else {
      let textOverflow = this.value.overflow; // number(enum) -> Ace::TextOverflow
      let maxLines = this.value.maxLines; // number -> uint32_t
      let minFontSize = this.value.minFontSize; // number | string | Resource -> Dimension
      let maxFontSize = this.value.maxFontSize; // number | string | Resource -> Dimension
      let heightAdaptivePolicy = this.value.heightAdaptivePolicy; // number(enum) -> Ace::TextHeightAdaptivePolicy
      let fontSize; // number | string | Resource -> Dimension
      let fontWeight; // number | string | Ace::FontWeight -> string -> Ace::FontWeight
      let fontStyle; // number(enum) -> Ace::FontStyle
      let fontFamily; // string -> std::vector<std::string>
      if (isObject(this.value.font)) {
        fontSize = this.value.font.size;
        fontStyle = this.value.font.style;
        fontFamily = this.value.font.family;
        fontWeight = this.value.font.weight;
      }
      getUINativeModule().button.setLabelStyle(node, textOverflow, maxLines, minFontSize, maxFontSize,
        heightAdaptivePolicy, fontSize, fontWeight, fontStyle, fontFamily);
    }
  }
  checkObjectDiff(): boolean {
     if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.value.overflow === this.stageValue.overflow &&
        this.value.maxLines === this.stageValue.maxLines &&
        this.value.minFontSize === this.stageValue.minFontSize &&
        this.value.maxFontSize === this.stageValue.maxFontSize &&
        this.value.heightAdaptivePolicy === this.stageValue.heightAdaptivePolicy &&
        this.value.font === this.stageValue.font);
    } else {
      return true;
    }
  }
}
class ButtonTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonType');
  applyStage(node: KNode, component?: ArkComponent): boolean {
    if (this.stageValue === undefined || this.stageValue === null) {
      this.value = this.stageValue;
      this.applyPeer(node, true, component);
      return true;
    }
    this.value = this.stageValue;
    this.applyPeer(node, false, component);
    return false;
  }
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetType(node);
    } else {
      getUINativeModule().button.setType(node, this.value);
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
      getUINativeModule().button.resetFontColor(node);
    } else {
      getUINativeModule().button.setFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ButtonFontSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetFontSize(node);
    } else {
      getUINativeModule().button.setFontSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ButtonFontWeightModifier extends ModifierWithKey<string | number | FontWeight> {
  constructor(value: string | number | FontWeight) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetFontWeight(node);
    } else {
      getUINativeModule().button.setFontWeight(node, this.value);
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
      getUINativeModule().button.resetButtonBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().button.setButtonBorderRadius(node, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().button.setButtonBorderRadius(node,
          (this.value as BorderRadiuses).topLeft,
          (this.value as BorderRadiuses).topRight,
          (this.value as BorderRadiuses).bottomLeft,
          (this.value as BorderRadiuses).bottomRight);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
    } else {
      return true;
    }
  }
}

class ButtonBorderModifier extends ModifierWithKey<BorderOptions> {
  constructor(value: BorderOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonBorder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetButtonBorder(node);
    } else {
      let widthLeft;
      let widthRight;
      let widthTop;
      let widthBottom;
      if (!isUndefined(this.value.width) && this.value.width !== null) {
        if (isNumber(this.value.width) || isString(this.value.width) || isResource(this.value.width)) {
          widthLeft = this.value.width;
          widthRight = this.value.width;
          widthTop = this.value.width;
          widthBottom = this.value.width;
        } else {
          widthLeft = (this.value.width as EdgeWidths).left;
          widthRight = (this.value.width as EdgeWidths).right;
          widthTop = (this.value.width as EdgeWidths).top;
          widthBottom = (this.value.width as EdgeWidths).bottom;
        }
      }
      let leftColor;
      let rightColor;
      let topColor;
      let bottomColor;
      if (!isUndefined(this.value.color) && this.value.color !== null) {
        if (isNumber(this.value.color) || isString(this.value.color) || isResource(this.value.color)) {
          leftColor = this.value.color;
          rightColor = this.value.color;
          topColor = this.value.color;
          bottomColor = this.value.color;
        } else {
          leftColor = (this.value.color as EdgeColors).left;
          rightColor = (this.value.color as EdgeColors).right;
          topColor = (this.value.color as EdgeColors).top;
          bottomColor = (this.value.color as EdgeColors).bottom;
        }
      }
      let topLeft;
      let topRight;
      let bottomLeft;
      let bottomRight;
      if (!isUndefined(this.value.radius) && this.value.radius !== null) {
        if (isNumber(this.value.radius) || isString(this.value.radius) || isResource(this.value.radius)) {
          topLeft = this.value.radius;
          topRight = this.value.radius;
          bottomLeft = this.value.radius;
          bottomRight = this.value.radius;
        } else {
          topLeft = (this.value.radius as BorderRadiuses).topLeft;
          topRight = (this.value.radius as BorderRadiuses).topRight;
          bottomLeft = (this.value.radius as BorderRadiuses).bottomLeft;
          bottomRight = (this.value.radius as BorderRadiuses).bottomRight;
        }
      }
      let styleTop;
      let styleRight;
      let styleBottom;
      let styleLeft;
      if (!isUndefined(this.value.style) && this.value.style !== null) {
        if (isNumber(this.value.style) || isString(this.value.style) || isResource(this.value.style)) {
          styleTop = this.value.style;
          styleRight = this.value.style;
          styleBottom = this.value.style;
          styleLeft = this.value.style;
        } else {
          styleTop = (this.value.style as EdgeStyles).top;
          styleRight = (this.value.style as EdgeStyles).right;
          styleBottom = (this.value.style as EdgeStyles).bottom;
          styleLeft = (this.value.style as EdgeStyles).left;
        }
      }
      getUINativeModule().button.setButtonBorder(
        node,
        widthLeft,
        widthRight,
        widthTop,
        widthBottom,
        leftColor,
        rightColor,
        topColor,
        bottomColor,
        topLeft,
        topRight,
        bottomLeft,
        bottomRight,
        styleTop,
        styleRight,
        styleBottom,
        styleLeft
      );
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
           !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
           !isBaseOrResourceEqual(this.stageValue.radius, this.value.radius) ||
           !isBaseOrResourceEqual(this.stageValue.style, this.value.style);
  }
}

class ButtonSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetButtonSize(node);
    } else {
      getUINativeModule().button.setButtonSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    return (
      !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height)
    );
  }
}

class ButtonRoleModifier extends ModifierWithKey<ButtonRole> {
  constructor(value: ButtonRole) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonRole');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetButtonRole(node);
    } else {
      getUINativeModule().button.setButtonRole(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return (
      !isBaseOrResourceEqual(this.stageValue, this.value)
    );
  }
}

class ButtonStyleModifier extends ModifierWithKey<ButtonStyleMode> {
  constructor(value: ButtonStyleMode) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetButtonStyle(node);
    } else {
      getUINativeModule().button.setButtonStyle(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return (
      !isBaseOrResourceEqual(this.stageValue, this.value)
    );
  }
}

class ButtonControlSizeModifier extends ModifierWithKey<ControlSize> {
  constructor(value: ControlSize) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonControlSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetControlSize(node);
    } else {
      getUINativeModule().button.setControlSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return (
      !isBaseOrResourceEqual(this.stageValue, this.value)
    );
  }
}

class ButtonLabelModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonLabel');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetLabel(node);
    } else {
      getUINativeModule().button.setLabel(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ButtonOptionsModifier extends ModifierWithKey<ButtonOptions> {
  static identity: Symbol = Symbol('buttonOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetOptions(node);
    } else {
      getUINativeModule().button.setOptions(node, this.value.type, this.value.stateEffect,
        this.value.buttonStyle, this.value.controlSize, this.value.role);
    }
  }
  checkObjectDiff(): boolean {
    return (
      !isBaseOrResourceEqual(this.stageValue.type, this.value.type) ||
      !isBaseOrResourceEqual(this.stageValue.stateEffect, this.value.stateEffect) ||
      !isBaseOrResourceEqual(this.stageValue.buttonStyle, this.value.buttonStyle) ||
      !isBaseOrResourceEqual(this.stageValue.controlSize, this.value.controlSize) ||
      !isBaseOrResourceEqual(this.stageValue.role, this.value.role)
    );
  }
}

class ButtonCreateTypeModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('buttonCreateType');
  applyPeer(node: KNode, reset: boolean): void {
    if (!reset) {
      getUINativeModule().button.setCreateWithLabel(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ButtonContentModifier extends ModifierWithKey<ContentModifier<ButtonConfiguration>> {
  constructor(value: ContentModifier<ButtonConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent) {
    let buttonComponent = component as ArkButtonComponent;
    buttonComponent.setContentModifier(this.value);
  }
}

class ButtonMinFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonMinFontScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetMinFontScale(node);
    } else if (!isNumber(this.value) && !isResource(this.value)) {
      getUINativeModule().button.resetMinFontScale(node);
    } else {
      getUINativeModule().button.setMinFontScale(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ButtonMaxFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('buttonMaxFontScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().button.resetMaxFontScale(node);
    } else if (!isNumber(this.value) && !isResource(this.value)) {
      getUINativeModule().button.resetMaxFontScale(node);
    } else {
      getUINativeModule().button.setMaxFontScale(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.Button.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkButtonComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ButtonModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.Button.contentModifier = function (modifier: ContentModifier<ButtonConfiguration>): void {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkButtonComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};
