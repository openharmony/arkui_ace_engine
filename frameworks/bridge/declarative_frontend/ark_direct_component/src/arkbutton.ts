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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkButtonComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
        this._needDiff = false;
      }
      allowChildCount(): number {
        return 1;
      }
      initialize(value: any[]): this {
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
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonBackgroundColorModifier.identity, ButtonBackgroundColorModifier, value);
        return this;
      }
      type(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonTypeModifier.identity, ButtonTypeModifier, value);
        return this;
      }
      stateEffect(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonStateEffectModifier.identity, ButtonStateEffectModifier, value);
        return this;
      }
      fontColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonFontColorModifier.identity, ButtonFontColorModifier, value);
        return this;
      }
      fontSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonFontSizeModifier.identity, ButtonFontSizeModifier, value);
        return this;
      }
      fontWeight(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonFontWeightModifier.identity, ButtonFontWeightModifier, value);
        return this;
      }
      fontStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonFontStyleModifier.identity, ButtonFontStyleModifier, value);
        return this;
      }
      fontFamily(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonFontFamilyModifier.identity, ButtonFontFamilyModifier, value);
        return this;
      }
      labelStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonLabelStyleModifier.identity, ButtonLabelStyleModifier, value);
        return this;
      }
      borderRadius(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonBorderRadiusModifier.identity, ButtonBorderRadiusModifier, value);
        return this;
      }
      border(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonBorderModifier.identity, ButtonBorderModifier, value);
        return this;
      }
      size(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonSizeModifier.identity, ButtonSizeModifier, value);
        return this;
      }
      contentModifier(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonContentModifier.identity, ButtonContentModifier, value);
        return this;
      }
      setContentModifier(modifier: any): this {
        if (modifier === undefined || modifier === null) {
          getUINativeModule().button.setContentModifierBuilder(this.nativePtr, false);
          return this;
        }
        this.needRebuild = false;
        this.applyContent = modifier.applyContent();
        if (this.builder !== this.applyContent) {
        this.needRebuild = true;
        }
        this.builder = this.applyContent;
        this.modifier = modifier;
        getUINativeModule().button.setContentModifierBuilder(this.nativePtr, this);
        return this;
      }
      makeContentModifierNode(context: any, buttonConfiguration: any): any {
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
      role(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonRoleModifier.identity, ButtonRoleModifier, value);
        return this;
      }
      buttonStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonStyleModifier.identity, ButtonStyleModifier, value);
        return this;
      }
      controlSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonControlSizeModifier.identity, ButtonControlSizeModifier, value);
        return this;
      }
      minFontScale(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonMinFontScaleModifier.identity, ButtonMinFontScaleModifier, value);
        return this;
      }
      maxFontScale(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ButtonMaxFontScaleModifier.identity, ButtonMaxFontScaleModifier, value);
        return this;
      }
    }

    class ButtonBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetBackgroundColor(node);
        } else {
          getUINativeModule().button.setBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ButtonBackgroundColorModifier as any).identity = Symbol('buttonBackgroundColor');

    class ButtonRoleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetButtonRole(node);
        } else {
          getUINativeModule().button.setButtonRole(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ButtonRoleModifier as any).identity = Symbol('buttonRole');

    class ButtonStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetButtonStyle(node);
        } else {
          getUINativeModule().button.setButtonStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ButtonStyleModifier as any).identity = Symbol('buttonStyle');

    class ButtonControlSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetButtonControlSize(node);
        } else {
          getUINativeModule().button.setButtonControlSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ButtonControlSizeModifier as any).identity = Symbol('buttonControlSize');

    class ButtonMinFontScaleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
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
    (ButtonMinFontScaleModifier as any).identity = Symbol('buttonMinFontScale');

    class ButtonMaxFontScaleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
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
    (ButtonMaxFontScaleModifier as any).identity = Symbol('buttonMaxFontScale');

    class ButtonStateEffectModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetStateEffect(node);
        } else {
          getUINativeModule().button.setStateEffect(node, this.value);
        }
      }
    }
    (ButtonStateEffectModifier as any).identity = Symbol('buttonStateEffect');

    class ButtonFontStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetFontStyle(node);
        } else {
          getUINativeModule().button.setFontStyle(node, this.value);
        }
      }
    }
    (ButtonFontStyleModifier as any).identity = Symbol('buttonFontStyle');

    class ButtonFontFamilyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
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
    (ButtonFontFamilyModifier as any).identity = Symbol('buttonFontFamily');

    class ButtonLabelStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
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
          let textAlign = this.value.textAlign; // number(enum) -> Ace::TextAlign
          getUINativeModule().button.setLabelStyle(node, textOverflow, maxLines, minFontSize,
            maxFontSize, heightAdaptivePolicy, fontSize, fontWeight, fontStyle, fontFamily, textAlign);
        }
      }
      checkObjectDiff(): boolean {
        if (!isResource(this.stageValue) && !isResource(this.value)) {
          return !(this.value.overflow === this.stageValue.overflow &&
            this.value.maxLines === this.stageValue.maxLines &&
            this.value.minFontSize === this.stageValue.minFontSize &&
            this.value.maxFontSize === this.stageValue.maxFontSize &&
            this.value.heightAdaptivePolicy === this.stageValue.heightAdaptivePolicy &&
            this.value.font === this.stageValue.font &&
            this.value.textAlign === this.stageValue.textAlign);
        }
        return true;
      }
    }
    (ButtonLabelStyleModifier as any).identity = Symbol('buttonLabelStyle');

    class ButtonTypeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyStage(node: any, component: any): boolean {
        if (this.stageValue === undefined || this.stageValue === null) {
          this.value = this.stageValue;
          this.applyPeer(node, true, component);
          return true;
        }
        this.value = this.stageValue;
        this.applyPeer(node, false, component);
        return false;
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetType(node);
        } else {
          getUINativeModule().button.setType(node, this.value);
        }
      }
    }
    (ButtonTypeModifier as any).identity = Symbol('buttonType');

    class ButtonFontColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
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
    (ButtonFontColorModifier as any).identity = Symbol('buttonFontColor');

    class ButtonFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
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
    (ButtonFontSizeModifier as any).identity = Symbol('buttonFontSize');

    class ButtonFontWeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetFontWeight(node);
        } else {
          getUINativeModule().button.setFontWeight(node, this.value);
        }
      }
    }
    (ButtonFontWeightModifier as any).identity = Symbol('buttonFontWeight');

    class ButtonBorderRadiusModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetButtonBorderRadius(node);
        }
        else {
          if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
            getUINativeModule().button.setButtonBorderRadius(node, this.value, this.value, this.value, this.value);
          }
          else {
            getUINativeModule().button.setButtonBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
          }
        }
      }
      checkObjectDiff(): boolean {
        if (!isResource(this.stageValue) && !isResource(this.value)) {
          return !(this.stageValue.topLeft === this.value.topLeft &&
            this.stageValue.topRight === this.value.topRight &&
            this.stageValue.bottomLeft === this.value.bottomLeft &&
            this.stageValue.bottomRight === this.value.bottomRight);
        }
        else {
          return true;
        }
      }
    }
    (ButtonBorderRadiusModifier as any).identity = Symbol('buttonBorderRadius');

    class ButtonBorderModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
        if (reset) {
          getUINativeModule().button.resetButtonBorder(node);
        } else {
          let widthLeft;
          let widthRight;
          let widthTop;
          let widthBottom;
          if (!isUndefined(this.value.width) && this.value.width != null) {
            if (isNumber(this.value.width) || isString(this.value.width) || isResource(this.value.width)) {
              widthLeft = this.value.width;
              widthRight = this.value.width;
              widthTop = this.value.width;
              widthBottom = this.value.width;
            } else {
              widthLeft = this.value.width.left;
              widthRight = this.value.width.right;
              widthTop = this.value.width.top;
              widthBottom = this.value.width.bottom;
            }
          }
          let leftColor;
          let rightColor;
          let topColor;
          let bottomColor;
          if (!isUndefined(this.value.color) && this.value.color != null) {
            if (isNumber(this.value.color) || isString(this.value.color) || isResource(this.value.color)) {
              leftColor = this.value.color;
              rightColor = this.value.color;
              topColor = this.value.color;
              bottomColor = this.value.color;
            } else {
              leftColor = this.value.color.left;
              rightColor = this.value.color.right;
              topColor = this.value.color.top;
              bottomColor = this.value.color.bottom;
            }
          }
          let topLeft;
          let topRight;
          let bottomLeft;
          let bottomRight;
          if (!isUndefined(this.value.radius) && this.value.radius != null) {
            if (isNumber(this.value.radius) || isString(this.value.radius) || isResource(this.value.radius)) {
              topLeft = this.value.radius;
              topRight = this.value.radius;
              bottomLeft = this.value.radius;
              bottomRight = this.value.radius;
            } else {
              topLeft = this.value.radius.topLeft;
              topRight = this.value.radius.topRight;
              bottomLeft = this.value.radius.bottomLeft;
              bottomRight = this.value.radius.bottomRight;
            }
          }
          let styleTop;
          let styleRight;
          let styleBottom;
          let styleLeft;
          if (!isUndefined(this.value.style) && this.value.style != null) {
            if (isNumber(this.value.style) || isString(this.value.style) || isResource(this.value.style)) {
              styleTop = this.value.style;
              styleRight = this.value.style;
              styleBottom = this.value.style;
              styleLeft = this.value.style;
            } else {
              styleTop = this.value.style.top;
              styleRight = this.value.style.right;
              styleBottom = this.value.style.bottom;
              styleLeft = this.value.style.left;
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
        return (
          !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
          !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
          !isBaseOrResourceEqual(this.stageValue.radius, this.value.radius) ||
          !isBaseOrResourceEqual(this.stageValue.style, this.value.style)
        );
      }
    }
    (ButtonBorderModifier as any).identity = Symbol('buttonBorder');

    class ButtonSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
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
    (ButtonSizeModifier as any).identity = Symbol('buttonSize');

    class ButtonLabelModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any): void {
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
    (ButtonLabelModifier as any).identity = Symbol('buttonLabel');

    class ButtonOptionsModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: any): void {
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
    (ButtonOptionsModifier as any).identity = Symbol('buttonOptions');

    class ButtonCreateTypeModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: any): void {
        if (!reset) {
          getUINativeModule().button.setCreateWithLabel(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ButtonCreateTypeModifier as any).identity = Symbol('buttonCreateType');

    class ButtonContentModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: any, component: any): void {
        let buttonComponent = component;
        buttonComponent.setContentModifier(this.value);
      }
    }
    (ButtonContentModifier as any).identity = Symbol('buttonContentModifier');

    loadComponent.componentObj = { 'component': ArkButtonComponent };
  }
  return loadComponent.componentObj;
}

class JSButton extends JSContainerBase {
  static createWithLabel(...args: any[]): void {
    getUINativeModule().button.createWithLabel(...args);
  }

  static createWithChild(...args: any[]): void {
    getUINativeModule().button.createWithChild(...args);
  }

  static allowChildCount(): number {
    return 1;
  }

  static fontColor(value: any): void {
    getUINativeModule().button.setFontColor(true, value);
  }

  static fontSize(value: any): void {
    getUINativeModule().button.setFontSize(true, value);
  }

  static fontWeight(value: any): void {
    getUINativeModule().button.setFontWeight(true, value);
  }

  static fontStyle(value: any): void {
    getUINativeModule().button.setFontStyle(true, value);
  }

  static fontFamily(value: any): void {
    getUINativeModule().button.setFontFamily(true, value);
  }

  static type(value: any): void {
    getUINativeModule().button.setType(true, value);
  }

  static stateEffect(value: any): void {
    getUINativeModule().button.setStateEffect(true, value);
  }

  static labelStyle(value: any): void {
    getUINativeModule().button.setLabelStyle(true, value);
  }

  static onClick(value: any): void {
    getUINativeModule().button.setOnClick(true, value);
  }

  static remoteMessage(value: any): void {
    getUINativeModule().button.setRemoteMessage(true, value);
  }

  static backgroundColor(value: any): void {
    getUINativeModule().button.setBackgroundColor(true, value);
  }

  static width(value: any): void {
    JSViewAbstract.width(value);
    getUINativeModule().button.setWidth(true, value);
  }

  static height(value: any): void {
    JSViewAbstract.height(value);
    getUINativeModule().button.setHeight(true, value);
  }

  static aspectRatio(value: any): void {
    JSViewAbstract.aspectRatio(value);
    getUINativeModule().button.setAspectRatio(true, value);
  }

  static borderRadius(value: any): void {
    getUINativeModule().button.setButtonBorderRadius(true, value);
  }

  static border(value: any): void {
    JSViewAbstract.border(value);
    getUINativeModule().button.setJsButtonBorder(true, value);
  }

  static size(value: any): void {
    if (!isObject(value)) {
      JSViewAbstract.width(undefined);
      JSViewAbstract.height(undefined);
      return;
    }
    JSViewAbstract.width(value.width);
    JSViewAbstract.height(value.height);
  }

  static padding(value: any): void {
    getUINativeModule().button.setPadding(true, value);
  }

  static buttonStyle(value: any): void {
    getUINativeModule().button.setButtonStyle(true, value);
  }

  static controlSize(value: any): void {
    getUINativeModule().button.setButtonControlSize(true, value);
  }

  static role(value: any): void {
    getUINativeModule().button.setButtonRole(true, value);
  }

  static minFontScale(value: any): void {
    getUINativeModule().button.setMinFontScale(true, value);
  }

  static maxFontScale(value: any): void {
    getUINativeModule().button.setMaxFontScale(true, value);
  }

  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }

  static onHover(value: any): void {
    __Common__.onHover(value);
  }

  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }

  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }

  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }

  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }

  static onDetach(value: any): void {
    __Common__.onDetach(value);
  }

  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return createComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ButtonModifier(nativePtr, classType);
    });
  }

  static contentModifier(modifier: any): void {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'button');
    });
    component.setContentModifier(modifier);
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
    globalThis.ArkButtonComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Button = JSButton;
}

export default { createComponent, exportComponent, exportView, loadComponent };