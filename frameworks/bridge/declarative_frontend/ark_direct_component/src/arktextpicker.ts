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
    class ArkTextPickerComponent extends ArkComponent {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      defaultPickerItemHeight(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerDefaultPickerItemHeightModifier.identity, TextpickerDefaultPickerItemHeightModifier, value);
        return this;
      }
      canLoop(value: boolean): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerCanLoopModifier.identity, TextpickerCanLoopModifier, value);
        return this;
      }
      digitalCrownSensitivity(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerDigitalCrownSensitivityModifier.identity, TextpickerDigitalCrownSensitivityModifier, value);
        return this;
      }
      disappearTextStyle(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerDisappearTextStyleModifier.identity, TextpickerDisappearTextStyleModifier, value);
        return this;
      }
      textStyle(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerTextStyleModifier.identity, TextpickerTextStyleModifier, value);
        return this;
      }
      selectedTextStyle(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerSelectedTextStyleModifier.identity, TextpickerSelectedTextStyleModifier, value);
        return this;
      }
      onAccept(callback: (value: string, index: number) => void): this {
        throw new BusinessError(100201, 'onAccept function not supported in attributeModifier scenario.');
      }
      onCancel(callback: () => void): this {
        throw new BusinessError(100201, 'onCancel function not supported in attributeModifier scenario.');
      }
      onChange(callback: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerOnChangeModifier.identity, TextpickerOnChangeModifier, callback);
        return this;
      }
      selectedIndex(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerSelectedIndexModifier.identity, TextpickerSelectedIndexModifier, value);
        return this;
      }
      divider(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerDividerModifier.identity, TextpickerDividerModifier, value);
        return this;
      }
      gradientHeight(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerGradientHeightModifier.identity, TextpickerGradientHeightModifier, value);
        return this;
      }
      disableTextStyleAnimation(value: boolean): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerDisableTextStyleAnimationModifier.identity, TextpickerDisableTextStyleAnimationModifier, value);
        return this;
      }
      defaultTextStyle(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerDefaultTextStyleModifier.identity, TextpickerDefaultTextStyleModifier, value);
        return this;
      }
      enableHapticFeedback(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, TextpickerEnableHapticFeedbackModifier.identity, TextpickerEnableHapticFeedbackModifier, value);
        return this;
      }
      selectedBackgroundStyle(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerSelectedBackgroundStyleModifier.identity, TextpickerSelectedBackgroundStyleModifier, value);
        return this;
      }
      onScrollStop(callback: (value: any, index: any) => void): this {
        modifierWithKey(
          this._modifiersWithKeys, TextpickerOnScrollStopModifier.identity, TextpickerOnScrollStopModifier, callback);
        return this;
      }
    }

    class TextpickerCanLoopModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetCanLoop(node);
        }
        else {
          getUINativeModule().textpicker.setCanLoop(node, this.value);
        }
      }
    }
    (TextpickerCanLoopModifier.identity as any) = Symbol('textpickerCanLoop');

    class TextpickerDigitalCrownSensitivityModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetDigitalCrownSensitivity(node);
        }
        else {
          getUINativeModule().textpicker.setDigitalCrownSensitivity(node, this.value);
        }
      }
    }
    (TextpickerDigitalCrownSensitivityModifier.identity as any) = Symbol('TextpickerDigitalCrownSensitivity');

    class TextpickerSelectedIndexModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetSelectedIndex(node);
        }
        else {
          getUINativeModule().textpicker.setSelectedIndex(node, this.value);
        }
      }
      checkObjectDiff() {
        if (Array.isArray(this.stageValue) && Array.isArray(this.value)) {
          return !deepCompareArrays(this.stageValue, this.value);
        }
        else if (Array.isArray(this.stageValue) || Array.isArray(this.value)) {
          return true;
        }
        else {
          return this.stageValue !== this.value;
        }
      }
    }
    (TextpickerSelectedIndexModifier.identity as any) = Symbol('textpickerSelectedIndex');
    class TextpickerDividerModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        var _a, _b, _c, _d;
        if (reset) {
          getUINativeModule().textpicker.resetDivider(node, this.value);
        }
        else {
          getUINativeModule().textpicker.setDivider(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.strokeWidth, (_b = this.value) === null || _b === void 0 ? void 0 : _b.color, (_c = this.value) === null || _c === void 0 ? void 0 : _c.startMargin, (_d = this.value) === null || _d === void 0 ? void 0 : _d.endMargin);
        }
      }
      checkObjectDiff() {
        var _a, _b, _c, _d, _e, _f, _g, _h;
        return !(((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.strokeWidth) === ((_b = this.value) === null || _b === void 0 ? void 0 : _b.strokeWidth) &&
          ((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.color) === ((_d = this.value) === null || _d === void 0 ? void 0 : _d.color) &&
          ((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.startMargin) === ((_f = this.value) === null || _f === void 0 ? void 0 : _f.startMargin) &&
          ((_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.endMargin) === ((_h = this.value) === null || _h === void 0 ? void 0 : _h.endMargin));
      }
    }
    (TextpickerDividerModifier.identity as any) = Symbol('textpickerDivider');

    class TextpickerGradientHeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetGradientHeight(node);
        }
        else {
          getUINativeModule().textpicker.setGradientHeight(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextpickerGradientHeightModifier.identity as any) = Symbol('textpickerGradientHeight');
    class TextpickerDisableTextStyleAnimationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetDisableTextStyleAnimation(node);
        }
        else {
          getUINativeModule().textpicker.setDisableTextStyleAnimation(node, this.value);
        }
      }
    }
    (TextpickerDisableTextStyleAnimationModifier.identity as any) = Symbol('textpickerDisableTextStyleAnimation');
    class TextpickerDefaultTextStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        var _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t, _u, _v;
        if (reset) {
          getUINativeModule().textpicker.resetDefaultTextStyle(node);
        }
        else {
          getUINativeModule().textpicker.setDefaultTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined, (_r = (_q = this.value) === null || _q === void 0 ? void 0 : _q.minFontSize) !== null && _r !== void 0 ? _r : undefined, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.maxFontSize) !== null && _t !== void 0 ? _t : undefined, (_v = (_u = this.value) === null || _u === void 0 ? void 0 : _u.overflow) !== null && _v !== void 0 ? _v : undefined);
        }
      }
      checkObjectDiff() {
        return true;
      }
    }
    (TextpickerDefaultTextStyleModifier.identity as any) = Symbol('textpickerDefaultTextStyle');
    class TextpickerTextStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        var _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t, _u, _v;
        if (reset) {
          getUINativeModule().textpicker.resetTextStyle(node);
        }
        else {
          getUINativeModule().textpicker.setTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined, (_r = (_q = this.value) === null || _q === void 0 ? void 0 : _q.minFontSize) !== null && _r !== void 0 ? _r : undefined, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.maxFontSize) !== null && _t !== void 0 ? _t : undefined, (_v = (_u = this.value) === null || _u === void 0 ? void 0 : _u.overflow) !== null && _v !== void 0 ? _v : undefined);
        }
      }
      checkObjectDiff() {
        return true;
      }
    }
    (TextpickerTextStyleModifier.identity as any) = Symbol('textpickerTextStyle');
    class TextpickerSelectedTextStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        var _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t, _u, _v;
        if (reset) {
          getUINativeModule().textpicker.resetSelectedTextStyle(node);
        }
        else {
          getUINativeModule().textpicker.setSelectedTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined, (_r = (_q = this.value) === null || _q === void 0 ? void 0 : _q.minFontSize) !== null && _r !== void 0 ? _r : undefined, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.maxFontSize) !== null && _t !== void 0 ? _t : undefined, (_v = (_u = this.value) === null || _u === void 0 ? void 0 : _u.overflow) !== null && _v !== void 0 ? _v : undefined);
        }
      }
      checkObjectDiff() {
        return true;
      }
    }
    (TextpickerSelectedTextStyleModifier.identity as any) = Symbol('textpickerSelectedTextStyle');
    class TextpickerDisappearTextStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        var _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t, _u, _v;
        if (reset) {
          getUINativeModule().textpicker.resetDisappearTextStyle(node);
        }
        else {
          getUINativeModule().textpicker.setDisappearTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined, (_r = (_q = this.value) === null || _q === void 0 ? void 0 : _q.minFontSize) !== null && _r !== void 0 ? _r : undefined, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.maxFontSize) !== null && _t !== void 0 ? _t : undefined, (_v = (_u = this.value) === null || _u === void 0 ? void 0 : _u.overflow) !== null && _v !== void 0 ? _v : undefined);
        }
      }
      checkObjectDiff() {
        return true;
      }
    }
    (TextpickerDisappearTextStyleModifier.identity as any) = Symbol('textpickerDisappearTextStyle');
    class TextpickerDefaultPickerItemHeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetDefaultPickerItemHeight(node);
        }
        else {
          getUINativeModule().textpicker.setDefaultPickerItemHeight(node, this.value);
        }
      }
    }
    (TextpickerDefaultPickerItemHeightModifier.identity as any) = Symbol('textpickerDefaultPickerItemHeight');
    class TextpickerEnableHapticFeedbackModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetTextpickerEnableHapticFeedback(node);
        }
        else {
          getUINativeModule().textpicker.setTextpickerEnableHapticFeedback(node, this.value);
        }
      }
    }
    (TextpickerEnableHapticFeedbackModifier.identity as any) = Symbol('textpickerEnableHapticFeedback');

    class TextpickerSelectedBackgroundStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetTextpickerSelectedBackgroundStyle(node);
        } else if (this.value == null) {
          getUINativeModule().textpicker.setTextpickerSelectedBackgroundStyle(node, undefined, undefined, undefined,
            undefined, undefined);
        } else {
          const { color, borderRadius } = this.value;
          if (borderRadius != null) {
            const borderRadiusKeys = Object.keys(borderRadius);
            let topLeft;
            let topRight;
            let bottomLeft;
            let bottomRight;
            if (borderRadiusKeys.indexOf('value') >= 0) {
              topLeft = topRight = bottomLeft = bottomRight = borderRadius;
            } else if (borderRadiusKeys.indexOf('topLeft') >= 0) {
              topLeft = borderRadius.topLeft;
              topRight = borderRadius.topRight;
              bottomLeft = borderRadius.bottomLeft;
              bottomRight = borderRadius.bottomRight;
            } else if (borderRadiusKeys.indexOf('topStart') >= 0) {
              topLeft = borderRadius.topStart;
              topRight = borderRadius.topEnd;
              bottomLeft = borderRadius.bottomStart;
              bottomRight = borderRadius.bottomEnd;
            }
            getUINativeModule().textpicker.setTextpickerSelectedBackgroundStyle(node, color, topLeft, topRight, bottomLeft,
              bottomRight);
          } else {
            getUINativeModule().textpicker.setTextpickerSelectedBackgroundStyle(node, color, undefined, undefined,
              undefined, undefined);
          }
        }
      }
      checkObjectDiff() {
        if (!(this.stageValue.color === this.value.color)) {
          return true;
        } else if (this.stageValue.borderRadius != null && this.value.borderRadius != null) {
          if (Object.keys(this.value.borderRadius).indexOf('value') >= 0) {
            return !(
              this.stageValue.borderRadius.value === this.value.borderRadius.value &&
              this.stageValue.borderRadius.unit === this.value.borderRadius.unit);
          } else if (Object.keys(this.value.borderRadius).indexOf('topLeft') >= 0) {
            return !(
              this.stageValue.borderRadius.topLeft === this.value.borderRadius.topLeft &&
              this.stageValue.borderRadius.topRight === this.value.borderRadius.topRight &&
              this.stageValue.borderRadius.bottomLeft === this.value.borderRadius.bottomLeft &&
              this.stageValue.borderRadius.bottomRight === this.value.borderRadius.bottomRight);
          } else if (Object.keys(this.value.borderRadius).indexOf('topStart') >= 0) {
            return !(
              this.stageValue.borderRadius.topStart === this.value.borderRadius.topStart &&
              this.stageValue.borderRadius.topEnd === this.value.borderRadius.topEnd &&
              this.stageValue.borderRadius.bottomStart === this.value.borderRadius.bottomStart &&
              this.stageValue.borderRadius.bottomEnd === this.value.borderRadius.bottomEnd);
          }
        }
        return true;
      }
    }
    (TextpickerSelectedBackgroundStyleModifier.identity as any) = Symbol('textpickerSelectedBackgroundStyle');

    class TextpickerOnChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetOnChange(node);
        } else {
          getUINativeModule().textpicker.setOnChange(node, this.value);
        }
      }
    }
    (TextpickerOnChangeModifier.identity as any) = Symbol('textpickerOnChange');

    class TextpickerOnScrollStopModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textpicker.resetOnScrollStop(node);
        } else {
          getUINativeModule().textpicker.setOnScrollStop(node, this.value);
        }
      }
    }
    (TextpickerOnScrollStopModifier.identity as any) = Symbol('textpickerOnScrollStop');

    loadComponent.componentObj = { 'component': ArkTextPickerComponent };
  }
  return loadComponent.componentObj;
}

class JSTextPicker extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().textpicker.create(params);//
  }
  static defaultPickerItemHeight(value: any): void {
    getUINativeModule().textpicker.setDefaultPickerItemHeight(true, value);
  }
  static canLoop(value: any): void {
    getUINativeModule().textpicker.setCanLoop(true, value);
  }
  static digitalCrownSensitivity(value: any): void {
    getUINativeModule().textpicker.setDigitalCrownSensitivity(true, value);
  }
  static disappearTextStyle(value: any): void {
    getUINativeModule().textpicker.setJsDisappearTextStyle(true, value);
  }
  static textStyle(value: any): void {
    getUINativeModule().textpicker.setJsTextStyle(true, value);
  }
  static selectedTextStyle(value: any): void {
    getUINativeModule().textpicker.setJsSelectedTextStyle(true, value);
  }
  static selectedIndex(value: any): void {
    getUINativeModule().textpicker.setJsSelectedIndex(true, value);
  }
  static divider(value: any): void {
    getUINativeModule().textpicker.setJsDivider(true, value);
  }
  static opacity(value: any): void {
    JSViewAbstract.opacity(value);
    getUINativeModule().textpicker.setOpacity(true, value);
  }
  static disableTextStyleAnimation(value: any): void {
    getUINativeModule().textpicker.setDisableTextStyleAnimation(true, value);
  }
  static defaultTextStyle(value: any): void {
    getUINativeModule().textpicker.setJsDefaultTextStyle(true, value);
  }
  static onAccept(value: any): void {
  }
  static onCancel(value: any): void {
  }
  static onChange(value: any): void {
    getUINativeModule().textpicker.setOnChange(true, value);
  }
  static onScrollStop(value: any): void {
    getUINativeModule().textpicker.setOnScrollStop(true, value);
  }
  static onEnterSelectedArea(value: any): void {
    getUINativeModule().textpicker.setOnEnterSelectedArea(true, value);
  }
  static backgroundColor(value: any): void {
    JSViewAbstract.backgroundColor(value);
    getUINativeModule().textpicker.setJsBackgroundColor(true, value);
  }
  static gradientHeight(value: any): void {
    getUINativeModule().textpicker.setGradientHeight(true, value);
  }
  static enableHapticFeedback(value: any): void {
    getUINativeModule().textpicker.setTextpickerEnableHapticFeedback(true, value);
  }
  static selectedBackgroundStyle(value: any): void {
    getUINativeModule().textpicker.setJsSelectedBackgroundStyle(true, value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.TextPickerModifier(nativePtr, classType);
    });
  }
  static onClick(value: any): void {
    __Common__.onClick(value);
  }
  static onTouch(value: any): void {
    __Common__.onTouch(value);
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
}

class JSTextPickerDialog extends JSViewAbstract {
  static show(value: any): void {
    getUINativeModule().textPickerDialog.show(value);
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
  globalThis.ArkTextPickerComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.TextPicker = JSTextPicker;
}

function exportViewDialog(): void {
  globalThis.TextPickerDialog = JSTextPickerDialog;
}

export default {  createComponent, exportComponent, exportView, exportViewDialog,
    loadComponent };
