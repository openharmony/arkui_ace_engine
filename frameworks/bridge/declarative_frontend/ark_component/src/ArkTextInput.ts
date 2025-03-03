/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
class TextInputStyleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetStyle(node);
    } else {
      getUINativeModule().textInput.setStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputMaxLengthModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMaxLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetMaxLength(node);
    } else {
      getUINativeModule().textInput.setMaxLength(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputMaxLinesModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetMaxLines(node);
    } else {
      getUINativeModule().textInput.setMaxLines(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputDecorationModifier extends ModifierWithKey<{ type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }> {
  constructor(value: { type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetDecoration(node);
    } else {
      getUINativeModule().textInput.setDecoration(node, this.value!.type, this.value!.color, this.value!.style);
    }
  }

  checkObjectDiff(): boolean {
    if (this.stageValue.type !== this.value.type || this.stageValue.style !== this.value.style) {
      return true;
    }
    if (isResource(this.stageValue.color) && isResource(this.value.color)) {
      return !isResourceEqual(this.stageValue.color, this.value.color);
    } else if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
      return !(this.stageValue.color === this.value.color);
    } else {
      return true;
    }
  }
}

class TextInputLetterSpacingModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputLetterSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetLetterSpacing(node);
    } else {
      getUINativeModule().textInput.setLetterSpacing(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputLineHeightModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputLineHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetLineHeight(node);
    } else {
      getUINativeModule().textInput.setLineHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputHalfLeadingModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputHalfLeading');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetHalfLeading(node);
    } else {
      getUINativeModule().textInput.setHalfLeading(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputUnderlineColorModifier extends ModifierWithKey<ResourceColor | UnderlineColor | undefined> {
  constructor(value: ResourceColor | UnderlineColor | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputUnderlineColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetUnderlineColor(node);
    } else {
      const valueType: string = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().textInput.setUnderlineColor(node, this.value, undefined, undefined, undefined, undefined);
      } else {
        getUINativeModule().textInput.setUnderlineColor(node, undefined, (this.value as UnderlineColor).normal,
          (this.value as UnderlineColor).typing, (this.value as UnderlineColor).error, (this.value as UnderlineColor).disable);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isBaseOrResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as UnderlineColor).normal === (this.value as UnderlineColor).normal &&
        (this.stageValue as UnderlineColor).typing === (this.value as UnderlineColor).typing &&
        (this.stageValue as UnderlineColor).error === (this.value as UnderlineColor).error &&
        (this.stageValue as UnderlineColor).disable === (this.value as UnderlineColor).disable);
    } else {
      return true;
    }
  }
}

class TextInputWordBreakModifier extends ModifierWithKey<WordBreak> {
  constructor(value: WordBreak) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputWordBreak');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetWordBreak(node);
    } else {
      getUINativeModule().textInput.setWordBreak(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputLineBreakStrategyModifier extends ModifierWithKey<LineBreakStrategy> {
  constructor(value: LineBreakStrategy) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputLineBreakStrategy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetLineBreakStrategy(node);
    } else {
      getUINativeModule().textInput.setLineBreakStrategy(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputMinFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMinFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetMinFontSize(node);
    } else {
      getUINativeModule().textInput.setMinFontSize(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputMaxFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMaxFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetMaxFontSize(node);
    } else {
      getUINativeModule().textInput.setMaxFontSize(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputMinFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMinFontScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetMinFontScale(node);
    } else {
      getUINativeModule().textInput.setMinFontScale(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputMaxFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMaxFontScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetMaxFontScale(node);
    } else {
      getUINativeModule().textInput.setMaxFontScale(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputHeightAdaptivePolicyModifier extends ModifierWithKey<TextHeightAdaptivePolicy> {
  constructor(value: TextHeightAdaptivePolicy) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputHeightAdaptivePolicy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetHeightAdaptivePolicy(node);
    } else {
      getUINativeModule().textInput.setHeightAdaptivePolicy(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputTextOverflowModifier extends ModifierWithKey<TextOverflow> {
  constructor(value: TextOverflow) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputTextOverflow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetTextOverflow(node);
    } else {
      getUINativeModule().textInput.setTextOverflow(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class TextInputTextIndentModifier extends ModifierWithKey<Dimension> {
  constructor(value: Dimension) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputTextIndent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetTextIndent(node);
    } else {
      getUINativeModule().textInput.setTextIndent(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputShowPasswordIconModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputShowPasswordIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetShowPasswordIcon(node);
    } else {
      getUINativeModule().textInput.setShowPasswordIcon(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputShowPasswordModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputShowPassword');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetShowPassword(node);
    } else {
      getUINativeModule().textInput.setShowPassword(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputTextAlignModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputTextAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetTextAlign(node);
    } else {
      getUINativeModule().textInput.setTextAlign(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputPlaceholderFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPlaceholderFont');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetPlaceholderFont(node);
    } else {
      getUINativeModule().textInput.setPlaceholderFont(node, this.value.size,
        this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue.weight === this.value.weight &&
      this.stageValue.style === this.value.style)) {
      return true;
    } else {
      if (((isResource(this.stageValue.size) && isResource(this.value.size) &&
        isResourceEqual(this.stageValue.size, this.value.size)) ||
        (!isResource(this.stageValue.size) && !isResource(this.value.size) &&
          this.stageValue.size === this.value.size)) &&
        ((isResource(this.stageValue.family) && isResource(this.value.family) &&
          isResourceEqual(this.stageValue.family, this.value.family)) ||
          (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
            this.stageValue.family === this.value.family))) {
        return false;
      } else {
        return true;
      }
    }
  }
}

class TextInputPlaceholderColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPlaceholderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetPlaceholderColor(node);
    } else {
      getUINativeModule().textInput.setPlaceholderColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputPasswordIconModifier extends ModifierWithKey<PasswordIcon> {
  constructor(value: PasswordIcon) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPasswordIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetPasswordIcon(node);
    } else {
      getUINativeModule().textInput.setPasswordIcon(node, this.value.onIconSrc, this.value.offIconSrc);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.onIconSrc, this.value.onIconSrc) ||
      !isBaseOrResourceEqual(this.stageValue.offIconSrc, this.value.offIconSrc);
  }
}

class TextInputSelectedBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputSelectedBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().textInput.setSelectedBackgroundColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputSelectionMenuHiddenModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputSelectionMenuHidden');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetSelectionMenuHidden(node);
    } else {
      getUINativeModule().textInput.setSelectionMenuHidden(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputShowUnderlineModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputShowUnderLine');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetShowUnderline(node);
    } else {
      getUINativeModule().textInput.setShowUnderline(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputPasswordRulesModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPasswordRules');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetPasswordRules(node);
    } else {
      getUINativeModule().textInput.setPasswordRules(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputEnableAutoFillModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputEnableAutoFill');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetEnableAutoFill(node);
    } else {
      getUINativeModule().textInput.setEnableAutoFill(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputShowErrorModifier extends ModifierWithKey<ResourceStr | undefined> {
  constructor(value: ResourceStr | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputShowError');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetShowError(node);
    } else {
      getUINativeModule().textInput.setShowError(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetType(node);
    } else {
      getUINativeModule().textInput.setType(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCaretPositionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputCaretPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetCaretPosition(node);
    } else {
      getUINativeModule().textInput.setCaretPosition(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCopyOptionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetCopyOption(node);
    } else {
      getUINativeModule().textInput.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputEnableKeyboardOnFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetEnableKeyboardOnFocus(node);
    } else {
      getUINativeModule().textInput.setEnableKeyboardOnFocus(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCaretStyleModifier extends ModifierWithKey<CaretStyle> {
  constructor(value: CaretStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputCaretStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetCaretStyle(node);
    } else {
      getUINativeModule().textInput.setCaretStyle(node, this.value!.width,
        this.value.color);
    }
  }

  checkObjectDiff(): boolean {
    if (isObject(this.stageValue) && isObject(this.value)) {
      return !isBaseOrResourceEqual(this.stageValue.width, this.value.width);
    } else {
      return true;
    }
  }
}

class TextInputEnterKeyTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputEnterKeyType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetEnterKeyType(node);
    } else {
      getUINativeModule().textInput.setEnterKeyType(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputBarStateModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputBarState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetBarState(node);
    } else {
      getUINativeModule().textInput.setBarState(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCaretColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textinputCaretColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetCaretColor(node);
    } else {
      getUINativeModule().textInput.setCaretColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetFontColor(node);
    } else {
      getUINativeModule().textInput.setFontColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}


class TextInputFontSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontSize');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetFontSize(node);
    } else {
      getUINativeModule().textInput.setFontSize(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputFontStyleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetFontStyle(node);
    } else {
      getUINativeModule().textInput.setFontStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputFontWeightModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetFontWeight(node);
    } else {
      getUINativeModule().textInput.setFontWeight(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputFontFamilyModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetFontFamily(node);
    } else {
      getUINativeModule().textInput.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputFontFeatureModifier extends ModifierWithKey<FontFeature> {
  constructor(value: FontFeature) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontFeature');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetFontFeature(node);
    } else {
      getUINativeModule().textInput.setFontFeature(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCancelButtonModifier extends ModifierWithKey<{ style?: CancelButtonStyle, icon?: IconOptions }> {
  constructor(value: { style?: CancelButtonStyle, icon?: IconOptions }) {
    super(value);
  }
  static identity = Symbol('textInputCancelButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetCancelButton(node);
    } else {
      getUINativeModule().textInput.setCancelButton(node, this.value.style,
        this.value.icon);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual(this.stageValue.icon?.size, this.value.icon?.size) ||
      !isBaseOrResourceEqual(this.stageValue.icon?.color, this.value.icon?.color) ||
      !isBaseOrResourceEqual(this.stageValue.icon?.src, this.value.icon?.src);
  }
}

class TextInputSelectAllModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('textInputSelectAll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetSelectAll(node);
    }
    else {
      getUINativeModule().textInput.setSelectAll(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputShowCounterModifier extends ModifierWithKey<ArkTextFieldShowCounter> {
  constructor(value: ArkTextFieldShowCounter) {
    super(value);
  }
  static identity = Symbol('textInputShowCounter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetShowCounter(node);
    }
    else {
      getUINativeModule().textInput.setShowCounter(node, this.value.value!, this.value.highlightBorder, this.value.thresholdPercentage);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.highlightBorder, this.value.highlightBorder) ||
      !isBaseOrResourceEqual(this.stageValue.thresholdPercentage, this.value.thresholdPercentage);
  }
}

class TextInputOnEditChangeModifier extends ModifierWithKey<(isEditing: boolean) => void> {
  constructor(value: (isEditing: boolean) => void) {
    super(value);
  }
  static identity = Symbol('textInputOnEditChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnEditChange(node);
    } else {
      getUINativeModule().textInput.setOnEditChange(node, this.value);
    }
  }
}

class TextInputFilterModifier extends ModifierWithKey<ArkTextInputFilter> {
  constructor(value: ArkTextInputFilter) {
    super(value);
  }
  static identity = Symbol('textInputFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetInputFilter(node);
    }
    else {
      getUINativeModule().textInput.setInputFilter(node, this.value.value, this.value.error);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.error, this.value.error);
  }
}

class TextInputOnSubmitModifier extends ModifierWithKey<(enterKey: EnterKeyType, event: SubmitEvent) => void> {
  constructor(value: (enterKey: EnterKeyType, event: SubmitEvent) => void) {
    super(value);
  }
  static identity = Symbol('textInputOnSubmit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnSubmit(node);
    } else {
      getUINativeModule().textInput.setOnSubmit(node, this.value);
    }
  }
}

class TextInputOnChangeModifier extends ModifierWithKey<(value: ChangeValueInfo) => void> {
  constructor(value: (value: ChangeValueInfo) => void) {
    super(value);
  }
  static identity = Symbol('textInputOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnChange(node);
    } else {
      getUINativeModule().textInput.setOnChange(node, this.value);
    }
  }
}

class TextInputOnTextSelectionChangeModifier extends ModifierWithKey<(selectionStart: number, selectionEnd: number) => void> {
  constructor(value: (selectionStart: number, selectionEnd: number) => void) {
    super(value);
  }
  static identity = Symbol('textInputOnTextSelectionChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnTextSelectionChange(node);
    } else {
      getUINativeModule().textInput.setOnTextSelectionChange(node, this.value);
    }
  }
}

class TextInputOnContentScrollModifier extends ModifierWithKey<(totalOffsetX: number, totalOffsetY: number) => void> {
  constructor(value: (totalOffsetX: number, totalOffsetY: number) => void) {
    super(value);
  }
  static identity = Symbol('textInputOnContentScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnContentScroll(node);
    } else {
      getUINativeModule().textInput.setOnContentScroll(node, this.value);
    }
  }
}

class TextInputOnCopyModifier extends ModifierWithKey<(value: string) => void> {
  constructor(value: (value: string) => void) {
    super(value);
  }
  static identity = Symbol('textInputOnCopy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnCopy(node);
    } else {
      getUINativeModule().textInput.setOnCopy(node, this.value);
    }
  }
}

class TextInputOnCutModifier extends ModifierWithKey<(value: string) => void> {
  constructor(value: (value: string) => void) {
    super(value);
  }
  static identity = Symbol('textInputOnCut');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnCut(node);
    } else {
      getUINativeModule().textInput.setOnCut(node, this.value);
    }
  }
}

class TextInputOnPasteModifier extends ModifierWithKey<(value: string, event: PasteEvent) => void> {
  constructor(value: (value: string, event: PasteEvent) => void) {
    super(value);
  }
  static identity = Symbol('textInputOnPaste');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnPaste(node);
    } else {
      getUINativeModule().textInput.setOnPaste(node, this.value);
    }
  }
}

class TextInputPaddingModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPadding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetPadding(node);
    }
    else {
      getUINativeModule().textInput.setPadding(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}

class TextInputContentTypeModifier extends ModifierWithKey<ContentType> {
  constructor(value: ContentType) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputContentType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetContentType(node);
    }
    else {
      getUINativeModule().textInput.setContentType(node, this.value);
    }
  }
}

class TextInputTextModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputText');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetText(node);
    } else {
      getUINativeModule().textInput.setText(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputBorderModifier extends ModifierWithKey<ArkBorder> {
  constructor(value: ArkBorder) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputBorder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetBorder(node);
    } else {
      getUINativeModule().textInput.setBorder(node,
        this.value.arkWidth.left, this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom,
        this.value.arkColor.leftColor, this.value.arkColor.rightColor, this.value.arkColor.topColor, this.value.arkColor.bottomColor,
        this.value.arkRadius.topLeft, this.value.arkRadius.topRight, this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight,
        this.value.arkStyle.top, this.value.arkStyle.right, this.value.arkStyle.bottom, this.value.arkStyle.left,
        this.value.arkDashGap.left, this.value.arkDashGap.right, this.value.arkDashGap.top, this.value.arkDashGap.bottom,
        this.value.arkDashWidth.left, this.value.arkDashWidth.right, this.value.arkDashWidth.top, this.value.arkDashWidth.bottom,
        this.value.arkDashGap.start, this.value.arkDashGap.end, this.value.arkDashWidth.start, this.value.arkDashWidth.end);
    }
  }
  checkObjectDiff(): boolean {
    return this.value.checkObjectDiff(this.stageValue);
  }
}

class TextInputBorderWidthModifier extends ModifierWithKey<Length | EdgeWidths> {
  constructor(value: Length | EdgeWidths | LocalizedEdgeWidths) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputBorderWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetBorderWidth(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().textInput.setBorderWidth(node, this.value, this.value, this.value, this.value);
      } else {
        if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
          getUINativeModule().textInput.setBorderWidth(node,
            (this.value as LocalizedEdgeWidths).top,
            (this.value as LocalizedEdgeWidths).end,
            (this.value as LocalizedEdgeWidths).bottom,
            (this.value as LocalizedEdgeWidths).start);
        } else {
          getUINativeModule().textInput.setBorderWidth(node,
            (this.value as EdgeWidths).top,
            (this.value as EdgeWidths).right,
            (this.value as EdgeWidths).bottom,
            (this.value as EdgeWidths).left);
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('start') >= 0) ||
          (Object.keys(this.value).indexOf('end') >= 0)) {
        return !((this.stageValue as LocalizedEdgeWidths).start === (this.value as LocalizedEdgeWidths).start &&
          (this.stageValue as LocalizedEdgeWidths).end === (this.value as LocalizedEdgeWidths).end &&
          (this.stageValue as LocalizedEdgeWidths).top === (this.value as LocalizedEdgeWidths).top &&
          (this.stageValue as LocalizedEdgeWidths).bottom === (this.value as LocalizedEdgeWidths).bottom);
      }
      return !((this.stageValue as EdgeWidths).left === (this.value as EdgeWidths).left &&
        (this.stageValue as EdgeWidths).right === (this.value as EdgeWidths).right &&
        (this.stageValue as EdgeWidths).top === (this.value as EdgeWidths).top &&
        (this.stageValue as EdgeWidths).bottom === (this.value as EdgeWidths).bottom);
    } else {
      return true;
    }
  }
}

class TextInputBorderColorModifier extends ModifierWithKey<ResourceColor | EdgeColors> {
  constructor(value: ResourceColor | EdgeColors | LocalizedEdgeColors) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputBorderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetBorderColor(node);
    } else {
      const valueType: string = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().textInput.setBorderColor(node, this.value, this.value, this.value, this.value);
      } else {
        if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
          getUINativeModule().textInput.setBorderColor(node,
            (this.value as LocalizedEdgeColors).top,
            (this.value as LocalizedEdgeColors).end,
            (this.value as LocalizedEdgeColors).bottom,
            (this.value as LocalizedEdgeColors).start,
            true);
        } else {
          getUINativeModule().textInput.setBorderColor(node,
            (this.value as EdgeColors).top,
            (this.value as EdgeColors).right,
            (this.value as EdgeColors).bottom,
            (this.value as EdgeColors).left,
            false);
        }
      }

    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('start') >= 0) ||
          (Object.keys(this.value).indexOf('end') >= 0)) {
        return !((this.stageValue as LocalizedEdgeColors).start === (this.value as LocalizedEdgeColors).start &&
          (this.stageValue as LocalizedEdgeColors).end === (this.value as LocalizedEdgeColors).end &&
          (this.stageValue as LocalizedEdgeColors).top === (this.value as LocalizedEdgeColors).top &&
          (this.stageValue as LocalizedEdgeColors).bottom === (this.value as LocalizedEdgeColors).bottom);
      }
      return !((this.stageValue as EdgeColors).left === (this.value as EdgeColors).left &&
        (this.stageValue as EdgeColors).right === (this.value as EdgeColors).right &&
        (this.stageValue as EdgeColors).top === (this.value as EdgeColors).top &&
        (this.stageValue as EdgeColors).bottom === (this.value as EdgeColors).bottom);
    } else {
      return true;
    }
  }
}

class TextInputBorderStyleModifier extends ModifierWithKey<BorderStyle | EdgeStyles> {
  constructor(value: BorderStyle | EdgeStyles) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputBorderStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetBorderStyle(node);
    } else {
      let type: boolean;
      let style: BorderStyle;
      let top: BorderStyle;
      let right: BorderStyle;
      let bottom: BorderStyle;
      let left: BorderStyle;
      if (isNumber(this.value)) {
        style = this.value as BorderStyle;
        type = true;
      } else if (isObject(this.value)) {
        top = (this.value as EdgeStyles)?.top;
        right = (this.value as EdgeStyles)?.right;
        bottom = (this.value as EdgeStyles)?.bottom;
        left = (this.value as EdgeStyles)?.left;
        type = true;
      }
      if (type === true) {
        getUINativeModule().textInput.setBorderStyle(node, type, style, top, right, bottom, left);
      } else {
        getUINativeModule().textInput.resetBorderStyle(node);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !((this.value as EdgeStyles)?.top === (this.stageValue as EdgeStyles)?.top &&
      (this.value as EdgeStyles)?.right === (this.stageValue as EdgeStyles)?.right &&
      (this.value as EdgeStyles)?.bottom === (this.stageValue as EdgeStyles)?.bottom &&
      (this.value as EdgeStyles)?.left === (this.stageValue as EdgeStyles)?.left);
  }
}

class TextInputBorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses> {
  constructor(value: Length | BorderRadiuses | LocalizedBorderRadius) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputBorderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().textInput.setBorderRadius(node, this.value, this.value, this.value, this.value);
      } else {
        if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
            (Object.keys(this.value).indexOf('topEnd') >= 0) ||
            (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
            (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
          getUINativeModule().textInput.setBorderRadius(node,
            (this.value as LocalizedBorderRadius).topStart,
            (this.value as LocalizedBorderRadius).topEnd,
            (this.value as LocalizedBorderRadius).bottomStart,
            (this.value as LocalizedBorderRadius).bottomEnd);
        } else {
          getUINativeModule().textInput.setBorderRadius(node,
            (this.value as BorderRadiuses).topLeft,
            (this.value as BorderRadiuses).topRight,
            (this.value as BorderRadiuses).bottomLeft,
            (this.value as BorderRadiuses).bottomRight);
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
          (Object.keys(this.value).indexOf('topEnd') >= 0) ||
          (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
          (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
        return !((this.stageValue as LocalizedBorderRadius).topStart === (this.value as LocalizedBorderRadius).topStart &&
          (this.stageValue as LocalizedBorderRadius).topEnd === (this.value as LocalizedBorderRadius).topEnd &&
          (this.stageValue as LocalizedBorderRadius).bottomStart === (this.value as LocalizedBorderRadius).bottomStart &&
          (this.stageValue as LocalizedBorderRadius).bottomEnd === (this.value as LocalizedBorderRadius).bottomEnd);
      }
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
    } else {
      return true;
    }
  }
}


class TextInputBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetBackgroundColor(node);
    } else {
      getUINativeModule().textInput.setBackgroundColor(node, this.value);
    }
  }
}

class TextInputPlaceholderModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPlaceholder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetPlaceholder(node);
    } else {
      getUINativeModule().textInput.setPlaceholder(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}


class TextInputMarginModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMargin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetMargin(node);
    } else {
      getUINativeModule().textInput.setMargin(node, this.value.top,
        this.value.right, this.value.bottom, this.value.left);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}

class TextInputControllerModifier extends ModifierWithKey<TextInputController> {
  constructor(value: TextInputController) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputController');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetController(node);
    } else {
      getUINativeModule().textInput.setController(node, this.value!);
    }
  }

}

class TextInputOnWillChangeModifier extends ModifierWithKey<Callback<ChangeValueInfo, boolean>> {
  constructor(value: Callback<ChangeValueInfo, boolean>) {
    super(value);
  }
  static identity = Symbol('textInputOnWillChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnWillChange(node);
    } else {
      getUINativeModule().textInput.setOnWillChange(node, this.value);
    }
  }
}

class TextInputOnWillInsertModifier extends ModifierWithKey<Callback<InsertValue, boolean>> {
  constructor(value: Callback<InsertValue, boolean>) {
    super(value);
  }
  static identity = Symbol('textInputOnWillInsert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnWillInsert(node);
    } else {
      getUINativeModule().textInput.setOnWillInsert(node, this.value);
    }
  }
}

class TextInputOnDidInsertModifier extends ModifierWithKey<Callback<InsertValue>> {
  constructor(value: Callback<InsertValue>) {
    super(value);
  }
  static identity = Symbol('textInputOnDidInsert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnDidInsert(node);
    } else {
      getUINativeModule().textInput.setOnDidInsert(node, this.value);
    }
  }
}

class TextInputOnWillDeleteModifier extends ModifierWithKey<Callback<DeleteValue, boolean>> {
  constructor(value: Callback<DeleteValue, boolean>) {
    super(value);
  }
  static identity = Symbol('textInputOnWillDelete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnWillDelete(node);
    } else {
      getUINativeModule().textInput.setOnWillDelete(node, this.value);
    }
  }
}

class TextInputOnDidDeleteModifier extends ModifierWithKey<Callback<DeleteValue>> {
  constructor(value: Callback<DeleteValue>) {
    super(value);
  }
  static identity = Symbol('textInputOnDidDelete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetOnDidDelete(node);
    } else {
      getUINativeModule().textInput.setOnDidDelete(node, this.value);
    }
  }
}

class TextInputEnablePreviewTextModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputEnablePreviewText');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetEnablePreviewText(node);
    } else {
      getUINativeModule().textInput.setEnablePreviewText(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputEditMenuOptionsModifier extends ModifierWithKey<EditMenuOptions> {
  constructor(value: EditMenuOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textEditMenuOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetSelectionMenuOptions(node);
    } else {
      getUINativeModule().textInput.setSelectionMenuOptions(node, this.value);
    }
  }
}

class TextInputEnableHapticFeedbackModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputEnableHapticFeedback');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetEnableHapticFeedback(node);
    } else {
      getUINativeModule().textInput.setEnableHapticFeedback(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputEllipsisModeModifier extends ModifierWithKey<EllipsisMode> {
  constructor(value: EllipsisMode) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputEllipsisMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetEllipsisMode(node);
    } else {
      getUINativeModule().textInput.setEllipsisMode(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

interface TextInputParam {
  placeholder?: ResourceStr;
  text?: ResourceStr;
  controller?: TextInputController;
}

class ArkTextInputComponent extends ArkComponent implements CommonMethod<TextInputAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): TextInputAttribute {
    if (value[0] !== undefined) {
      this.setPlaceholder((value[0] as TextInputParam).placeholder);
      this.setText((value[0] as TextInputParam).text);
      this.setController((value[0] as TextInputParam).controller);
    }
    return this;
  }
  setText(value: ResourceStr): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputTextModifier.identity,
      TextInputTextModifier, value);
    return this;
  }
  setPlaceholder(value: ResourceStr): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderModifier.identity,
      TextInputPlaceholderModifier, value);
    return this;
  }
  setController(value: TextInputController): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputControllerModifier.identity,
      TextInputControllerModifier, value);
    return this;
  }
  cancelButton(value: { style?: CancelButtonStyle, icon?: IconOptions }): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputCancelButtonModifier.identity,
      TextInputCancelButtonModifier, value);
    return this;
  }
  selectAll(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputSelectAllModifier.identity,
      TextInputSelectAllModifier, value);
    return this;
  }
  enableAutoFill(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputEnableAutoFillModifier.identity,
      TextInputEnableAutoFillModifier, value);
    return this;
  }
  passwordRules(value: string): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPasswordRulesModifier.identity,
      TextInputPasswordRulesModifier, value);
    return this;
  }
  showCounter(value: boolean, options?: InputCounterOptions): TextInputAttribute {
    let arkValue: ArkTextFieldShowCounter = new ArkTextFieldShowCounter();
    arkValue.value = value;
    arkValue.highlightBorder = options?.highlightBorder;
    arkValue.thresholdPercentage = options?.thresholdPercentage;
    modifierWithKey(this._modifiersWithKeys, TextInputShowCounterModifier.identity,
      TextInputShowCounterModifier, arkValue);
    return this;
  }

  type(value: InputType): TextInputAttribute {

    modifierWithKey(this._modifiersWithKeys, TextInputTypeModifier.identity,
      TextInputTypeModifier, value);
    return this;
  }

  placeholderColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderColorModifier.identity,
      TextInputPlaceholderColorModifier, value);
    return this;
  }

  placeholderFont(value?: Font): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderFontModifier.identity,
      TextInputPlaceholderFontModifier, value);
    return this;
  }
  enterKeyType(value: EnterKeyType): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputEnterKeyTypeModifier.identity,
      TextInputEnterKeyTypeModifier, value);
    return this;
  }
  caretColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretColorModifier.identity,
      TextInputCaretColorModifier, value);
    return this;
  }
  onEditChanged(callback: (isEditing: boolean) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnEditChangeModifier.identity,
      TextInputOnEditChangeModifier, callback);
    return this;
  }
  onEditChange(callback: (isEditing: boolean) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnEditChangeModifier.identity,
      TextInputOnEditChangeModifier, callback);
    return this;
  }
  onSubmit(callback: (enterKey: EnterKeyType, event: SubmitEvent) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnSubmitModifier.identity,
      TextInputOnSubmitModifier, callback);
    return this;
  }
  onChange(callback: (value: ChangeValueInfo) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnChangeModifier.identity,
      TextInputOnChangeModifier, callback);
    return this;
  }
  onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnTextSelectionChangeModifier.identity,
      TextInputOnTextSelectionChangeModifier, callback);
    return this;
  }
  onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnContentScrollModifier.identity,
      TextInputOnContentScrollModifier, callback);
    return this;
  }
  maxLength(value: number): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputMaxLengthModifier.identity,
      TextInputMaxLengthModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontColorModifier.identity,
      TextInputFontColorModifier, value);
    return this;
  }

  fontSize(value: Length): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontSizeModifier.identity,
      TextInputFontSizeModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontStyleModifier.identity,
      TextInputFontStyleModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontWeightModifier.identity,
      TextInputFontWeightModifier, value);
    return this;
  }

  fontFamily(value: ResourceStr): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontFamilyModifier.identity,
      TextInputFontFamilyModifier, value);
    return this;
  }
  inputFilter(value: ResourceStr, error?: (value: string) => void): TextInputAttribute {
    let arkValue = new ArkTextInputFilter();
    arkValue.value = value;
    arkValue.error = error;
    modifierWithKey(this._modifiersWithKeys, TextInputFilterModifier.identity,
      TextInputFilterModifier, arkValue);
    return this;
  }
  onCopy(callback: (value: string) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnCopyModifier.identity,
      TextInputOnCopyModifier, callback);
    return this;
  }
  onCut(callback: (value: string) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnCutModifier.identity,
      TextInputOnCutModifier, callback);
    return this;
  }
  onPaste(callback: (value: string) => void): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputOnPasteModifier.identity,
      TextInputOnPasteModifier, callback);
    return this;
  }
  copyOption(value: CopyOptions): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputCopyOptionModifier.identity,
      TextInputCopyOptionModifier, value);
    return this;
  }

  showPasswordIcon(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputShowPasswordIconModifier.identity,
      TextInputShowPasswordIconModifier, value);
    return this;
  }
  showPassword(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputShowPasswordModifier.identity,
      TextInputShowPasswordModifier, value);
    return this;
  }
  textAlign(value: TextAlign): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputTextAlignModifier.identity,
      TextInputTextAlignModifier, value);
    return this;
  }
  style(value: TextInputStyle | TextContentStyle): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputStyleModifier.identity,
      TextInputStyleModifier, value);
    return this;
  }
  caretStyle(value: CaretStyle) {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretStyleModifier.identity,
      TextInputCaretStyleModifier, value);
    return this;
  }

  selectedBackgroundColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputSelectedBackgroundColorModifier.identity,
      TextInputSelectedBackgroundColorModifier, value);
    return this;
  }
  caretPosition(value: number): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretPositionModifier.identity,
      TextInputCaretPositionModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputEnableKeyboardOnFocusModifier.identity,
      TextInputEnableKeyboardOnFocusModifier, value);
    return this;
  }

  passwordIcon(value: PasswordIcon): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPasswordIconModifier.identity,
      TextInputPasswordIconModifier, value);
    return this;
  }
  showError(value: ResourceStr | undefined): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputShowErrorModifier.identity,
      TextInputShowErrorModifier, value);
    return this;
  }
  showUnit(event: () => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  showUnderline(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputShowUnderlineModifier.identity,
      TextInputShowUnderlineModifier, value);
    return this;
  }
  selectionMenuHidden(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputSelectionMenuHiddenModifier.identity, TextInputSelectionMenuHiddenModifier, value);
    return this;
  }
  barState(value: BarState): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputBarStateModifier.identity, TextInputBarStateModifier, value);
    return this;
  }
  maxLines(value: number): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputMaxLinesModifier.identity, TextInputMaxLinesModifier, value);
    return this;
  }
  fontFeature(value: FontFeature): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontFeatureModifier.identity, TextInputFontFeatureModifier, value);
    return this;
  }
  customKeyboard(event: () => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  decoration(value: { type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputDecorationModifier.identity, TextInputDecorationModifier, value);
    return this;
  }
  letterSpacing(value: number | string): this {
    modifierWithKey(this._modifiersWithKeys, TextInputLetterSpacingModifier.identity, TextInputLetterSpacingModifier, value);
    return this;
  }
  lineHeight(value: number | string | Resource): this {
    modifierWithKey(this._modifiersWithKeys, TextInputLineHeightModifier.identity, TextInputLineHeightModifier, value);
    return this;
  }
  halfLeading(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextInputHalfLeadingModifier.identity, TextInputHalfLeadingModifier, value);
    return this;
  }
  underlineColor(value: ResourceColor | UnderlineColor | undefined): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputUnderlineColorModifier.identity, TextInputUnderlineColorModifier, value);
    return this;
  }
  wordBreak(value: WordBreak): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputWordBreakModifier.identity, TextInputWordBreakModifier, value);
    return this;
  }
  lineBreakStrategy(value: LineBreakStrategy): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputLineBreakStrategyModifier.identity,
      TextInputLineBreakStrategyModifier, value);
    return this;
  }
  minFontSize(value: number | string | Resource): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputMinFontSizeModifier.identity, TextInputMinFontSizeModifier, value);
    return this;
  }
  maxFontSize(value: number | string | Resource): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputMaxFontSizeModifier.identity, TextInputMaxFontSizeModifier, value);
    return this;
  }
  minFontScale(value: number | Resource): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputMinFontScaleModifier.identity, TextInputMinFontScaleModifier, value);
    return this;
  }
  maxFontScale(value: number | Resource): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputMaxFontScaleModifier.identity, TextInputMaxFontScaleModifier, value);
    return this;
  }
  heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputHeightAdaptivePolicyModifier.identity, TextInputHeightAdaptivePolicyModifier, value);
    return this;
  }
  textOverflow(value: TextOverflow): this {
    modifierWithKey(this._modifiersWithKeys, TextInputTextOverflowModifier.identity, TextInputTextOverflowModifier, value);
    return this;
  }
  textIndent(value: Dimension): this {
    modifierWithKey(this._modifiersWithKeys, TextInputTextIndentModifier.identity, TextInputTextIndentModifier, value);
    return this;
  }
  ellipsisMode(value: EllipsisMode): this {
    modifierWithKey(this._modifiersWithKeys, TextInputEllipsisModeModifier.identity, TextInputEllipsisModeModifier, value);
    return this;
  }
  padding(value: Padding | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = value;
        arkValue.right = value;
        arkValue.bottom = value;
        arkValue.left = value;
      }
      else {
        arkValue.top = value.top;
        arkValue.bottom = value.bottom;
        if (Object.keys(value).indexOf('right') >= 0) {
          arkValue.right = value.right;
        }
        if (Object.keys(value).indexOf('end') >= 0) {
          arkValue.right = value.end;
        }
        if (Object.keys(value).indexOf('left') >= 0) {
          arkValue.left = value.left;
        }
        if (Object.keys(value).indexOf('start') >= 0) {
          arkValue.left = value.start;
        }
      }
      modifierWithKey(this._modifiersWithKeys, TextInputPaddingModifier.identity, TextInputPaddingModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, TextInputPaddingModifier.identity, TextInputPaddingModifier, undefined);
    }
    return this;
  }
  contentType(value: ContentType): this {
    modifierWithKey(this._modifiersWithKeys, TextInputContentTypeModifier.identity, TextInputContentTypeModifier, value);
    return this;
  }
  border(value: BorderOptions): this {
    let borderValue = new ArkBorder();
    if (isUndefined(value)) {
      borderValue = undefined;
    }

    if (!isUndefined(value?.width) && value?.width !== null) {
      if (isNumber(value.width) || isString(value.width) || isResource(value.width)) {
        borderValue.arkWidth.left = value.width;
        borderValue.arkWidth.right = value.width;
        borderValue.arkWidth.top = value.width;
        borderValue.arkWidth.bottom = value.width;
      } else {
        borderValue.arkWidth.left = (value.width as EdgeWidths).left;
        borderValue.arkWidth.right = (value.width as EdgeWidths).right;
        borderValue.arkWidth.top = (value.width as EdgeWidths).top;
        borderValue.arkWidth.bottom = (value.width as EdgeWidths).bottom;
      }
    }
    if (!isUndefined(value?.color) && value?.color !== null) {
      if (isNumber(value.color) || isString(value.color) || isResource(value.color)) {
        borderValue.arkColor.leftColor = value.color;
        borderValue.arkColor.rightColor = value.color;
        borderValue.arkColor.topColor = value.color;
        borderValue.arkColor.bottomColor = value.color;
      } else {
        borderValue.arkColor.leftColor = (value.color as EdgeColors).left;
        borderValue.arkColor.rightColor = (value.color as EdgeColors).right;
        borderValue.arkColor.topColor = (value.color as EdgeColors).top;
        borderValue.arkColor.bottomColor = (value.color as EdgeColors).bottom;
      }
    }
    if (!isUndefined(value?.radius) && value?.radius !== null) {
      if (isNumber(value.radius) || isString(value.radius) || isResource(value.radius)) {
        borderValue.arkRadius.topLeft = value.radius;
        borderValue.arkRadius.topRight = value.radius;
        borderValue.arkRadius.bottomLeft = value.radius;
        borderValue.arkRadius.bottomRight = value.radius;
      } else {
        borderValue.arkRadius.topLeft = (value.radius as BorderRadiuses)?.topLeft;
        borderValue.arkRadius.topRight = (value.radius as BorderRadiuses)?.topRight;
        borderValue.arkRadius.bottomLeft = (value.radius as BorderRadiuses)?.bottomLeft;
        borderValue.arkRadius.bottomRight = (value.radius as BorderRadiuses)?.bottomRight;
      }
    }
    if (!isUndefined(value?.style) && value?.style !== null) {
      let arkBorderStyle = new ArkBorderStyle();
      if (arkBorderStyle.parseBorderStyle(value.style)) {
        if (!isUndefined(arkBorderStyle.style)) {
          borderValue.arkStyle.top = arkBorderStyle.style;
          borderValue.arkStyle.left = arkBorderStyle.style;
          borderValue.arkStyle.bottom = arkBorderStyle.style;
          borderValue.arkStyle.right = arkBorderStyle.style;
        } else {
          borderValue.arkStyle.top = arkBorderStyle.top;
          borderValue.arkStyle.left = arkBorderStyle.left;
          borderValue.arkStyle.bottom = arkBorderStyle.bottom;
          borderValue.arkStyle.right = arkBorderStyle.right;
        }
      }
    }
    if (!isUndefined(value?.dashGap) && value?.dashGap !== null) {
      if (isNumber(value.dashGap) || isString(value.dashGap) || isResource(value.dashGap) ||
        isObject(value.dashGap) && isNumber(value.dashGap.value)) {
        borderValue.arkDashGap.left = value.dashGap;
        borderValue.arkDashGap.right = value.dashGap;
        borderValue.arkDashGap.top = value.dashGap;
        borderValue.arkDashGap.bottom = value.dashGap;
      } else {
        borderValue.arkDashGap.left = (value.dashGap as EdgeWidths).left;
        borderValue.arkDashGap.right = (value.dashGap as EdgeWidths).right;
        borderValue.arkDashGap.top = (value.dashGap as EdgeWidths).top;
        borderValue.arkDashGap.bottom = (value.dashGap as EdgeWidths).bottom;
        borderValue.arkDashGap.start = (value.dashGap as LocalizedEdgeWidths).start;
        borderValue.arkDashGap.end = (value.dashGap as LocalizedEdgeWidths).end;
      }
    }
    if (!isUndefined(value?.dashWidth) && value?.dashWidth !== null) {
      if (isNumber(value.dashWidth) || isString(value.dashWidth) || isResource(value.dashWidth) ||
        isObject(value.dashWidth) && isNumber(value.dashWidth.value)) {
        borderValue.arkDashWidth.left = value.dashWidth;
        borderValue.arkDashWidth.right = value.dashWidth;
        borderValue.arkDashWidth.top = value.dashWidth;
        borderValue.arkDashWidth.bottom = value.dashWidth;
      } else {
        borderValue.arkDashWidth.left = (value.dashWidth as EdgeWidths).left;
        borderValue.arkDashWidth.right = (value.dashWidth as EdgeWidths).right;
        borderValue.arkDashWidth.top = (value.dashWidth as EdgeWidths).top;
        borderValue.arkDashWidth.bottom = (value.dashWidth as EdgeWidths).bottom;
        borderValue.arkDashWidth.start = (value.dashWidth as EdgeWidths).start;
        borderValue.arkDashWidth.end = (value.dashWidth as EdgeWidths).end;
      }
    }
    modifierWithKey(this._modifiersWithKeys, TextInputBorderModifier.identity, TextInputBorderModifier, borderValue);
    return this;
  }
  borderWidth(value: Length | EdgeWidths): this {
    modifierWithKey(this._modifiersWithKeys, TextInputBorderWidthModifier.identity, TextInputBorderWidthModifier, value);
    return this;
  }
  borderColor(value: ResourceColor | EdgeColors): this {
    modifierWithKey(this._modifiersWithKeys, TextInputBorderColorModifier.identity, TextInputBorderColorModifier, value);
    return this;
  }
  borderStyle(value: BorderStyle | EdgeStyles): this {
    modifierWithKey(this._modifiersWithKeys, TextInputBorderStyleModifier.identity, TextInputBorderStyleModifier, value);
    return this;
  }
  borderRadius(value: Length | BorderRadiuses): this {
    modifierWithKey(this._modifiersWithKeys, TextInputBorderRadiusModifier.identity, TextInputBorderRadiusModifier, value);
    return this;
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, TextInputBackgroundColorModifier.identity, TextInputBackgroundColorModifier, value);
    return this;
  }
  margin(value: Margin | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = <Length>value;
        arkValue.right = <Length>value;
        arkValue.bottom = <Length>value;
        arkValue.left = <Length>value;
      } else {
        arkValue.top = value.top;
        arkValue.bottom = value.bottom;
        if (Object.keys(value).indexOf('right') >= 0) {
          arkValue.right = value.right;
        }
        if (Object.keys(value).indexOf('end') >= 0) {
          arkValue.right = value.end;
        }
        if (Object.keys(value).indexOf('left') >= 0) {
          arkValue.left = value.left;
        }
        if (Object.keys(value).indexOf('start') >= 0) {
          arkValue.left = value.start;
        }
      }
      modifierWithKey(this._modifiersWithKeys, TextInputMarginModifier.identity, TextInputMarginModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, TextInputMarginModifier.identity, TextInputMarginModifier, undefined);
    }
    return this;
  }
  onWillChange(callback: Callback<ChangeValueInfo, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, TextInputOnWillChangeModifier.identity, TextInputOnWillChangeModifier, callback);
    return this;
  }
  onWillInsert(callback: Callback<InsertValue, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, TextInputOnWillInsertModifier.identity, TextInputOnWillInsertModifier, callback);
    return this;
  }
  onDidInsert(callback: Callback<InsertValue>): this {
    modifierWithKey(this._modifiersWithKeys, TextInputOnDidInsertModifier.identity, TextInputOnDidInsertModifier, callback);
    return this;
  }
  onWillDelete(callback: Callback<DeleteValue, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, TextInputOnWillDeleteModifier.identity, TextInputOnWillDeleteModifier, callback);
    return this;
  }
  onDidDelete(callback: Callback<DeleteValue>): this {
    modifierWithKey(this._modifiersWithKeys, TextInputOnDidDeleteModifier.identity, TextInputOnDidDeleteModifier, callback);
    return this;
  }
  enablePreviewText(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextInputEnablePreviewTextModifier.identity, TextInputEnablePreviewTextModifier, value);
    return this;
  }
  editMenuOptions(value: EditMenuOptions): this {
    modifierWithKey(this._modifiersWithKeys, TextInputEditMenuOptionsModifier.identity,
      TextInputEditMenuOptionsModifier, value);
    return this;
  }
  enableHapticFeedback(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextInputEnableHapticFeedbackModifier.identity, TextInputEnableHapticFeedbackModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.TextInput.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkTextInputComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TextInputModifier(nativePtr, classType);
  });
};
