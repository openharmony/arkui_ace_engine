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
class TextAreaFontStyleModifier extends ModifierWithKey<FontStyle> {
  constructor(value: FontStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetFontStyle(node);
    } else {
      getUINativeModule().textArea.setFontStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaDecorationModifier extends ModifierWithKey<{ type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }> {
  constructor(value: { type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetDecoration(node);
    } else {
      getUINativeModule().textArea.setDecoration(node, this.value!.type, this.value!.color, this.value!.style);
    }
  }
  
  checkObjectDiff(): boolean {
    if (this.stageValue.type !== this.value.type || this.stageValue.style !== this.value.style) {
      return true;
    }
    if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
      return !(this.stageValue.color === this.value.color);
    } else {
      return true;
    }
  }
}

class TextAreaLetterSpacingModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaLetterSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetLetterSpacing(node);
    } else {
      getUINativeModule().textArea.setLetterSpacing(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaLineSpacingModifier extends ModifierWithKey<LengthMetrics> {
  constructor(value: LengthMetrics) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaLineSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetLineSpacing(node);
    } else if (!isObject(this.value)) {
      getUINativeModule().textArea.resetLineSpacing(node);
    } else {
      getUINativeModule().textArea.setLineSpacing(node, this.value.value, this.value.unit);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaLineHeightModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaLineHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetLineHeight(node);
    } else {
      getUINativeModule().textArea.setLineHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaHalfLeadingModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaHalfLeading');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetHalfLeading(node);
    } else {
      getUINativeModule().textArea.setHalfLeading(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaWordBreakModifier extends ModifierWithKey<WordBreak> {
  constructor(value: WordBreak) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaWordBreak');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetWordBreak(node);
    } else {
      getUINativeModule().textArea.setWordBreak(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaLineBreakStrategyModifier extends ModifierWithKey<LineBreakStrategy> {
  constructor(value: LineBreakStrategy) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaLineBreakStrategy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetLineBreakStrategy(node);
    } else {
      getUINativeModule().textArea.setLineBreakStrategy(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaCopyOptionModifier extends ModifierWithKey<CopyOptions> {
  constructor(value: CopyOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetCopyOption(node);
    } else {
      getUINativeModule().textArea.setCopyOption(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaMaxLinesModifier extends ModifierWithKey<number | undefined> {
  constructor(value: number | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetMaxLines(node);
    } else {
      getUINativeModule().textArea.setMaxLines(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaMinFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMinFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetMinFontSize(node);
    } else {
      getUINativeModule().textArea.setMinFontSize(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaMaxFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMaxFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetMaxFontSize(node);
    } else {
      getUINativeModule().textArea.setMaxFontSize(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaMinFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMinFontScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetMinFontScale(node);
    } else {
      getUINativeModule().textArea.setMinFontScale(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaMaxFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMaxFontScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetMaxFontScale(node);
    } else {
      getUINativeModule().textArea.setMaxFontScale(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaHeightAdaptivePolicyModifier extends ModifierWithKey<TextHeightAdaptivePolicy> {
  constructor(value: TextHeightAdaptivePolicy) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaHeightAdaptivePolicy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetHeightAdaptivePolicy(node);
    } else {
      getUINativeModule().textArea.setHeightAdaptivePolicy(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaFontSizeModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetFontSize(node);
    } else {
      getUINativeModule().textArea.setFontSize(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaPlaceholderColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaPlaceholderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetPlaceholderColor(node);
    } else {
      getUINativeModule().textArea.setPlaceholderColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetFontColor(node);
    } else {
      getUINativeModule().textArea.setFontColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaFontWeightModifier extends ModifierWithKey<number | FontWeight | string> {
  constructor(value: number | FontWeight | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetFontWeight(node);
    } else {
      getUINativeModule().textArea.setFontWeight(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaBarStateModifier extends ModifierWithKey<BarState> {
  constructor(value: BarState) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaBarState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetBarState(node);
    } else {
      getUINativeModule().textArea.setBarState(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaEnableKeyboardOnFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetEnableKeyboardOnFocus(node);
    } else {
      getUINativeModule().textArea.setEnableKeyboardOnFocus(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaFontFamilyModifier extends ModifierWithKey<ResourceColor | string> {
  constructor(value: ResourceColor | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetFontFamily(node);
    } else {
      getUINativeModule().textArea.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaCaretColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaCaretColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetCaretColor(node);
    } else {
      getUINativeModule().textArea.setCaretColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaMaxLengthModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMaxLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetMaxLength(node);
    } else {
      getUINativeModule().textArea.setMaxLength(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaStyleModifier extends ModifierWithKey<TextContentStyle> {
  constructor(value: TextContentStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetStyle(node);
    } else {
      getUINativeModule().textArea.setStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaSelectionMenuHiddenModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaSelectionMenuHidden');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetSelectionMenuHidden(node);
    } else {
      getUINativeModule().textArea.setSelectionMenuHidden(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaPlaceholderFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaPlaceholderFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetPlaceholderFont(node);
    } else {
      getUINativeModule().textArea.setPlaceholderFont(node, this.value.size,
        this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue.weight === this.value.weight &&
      this.stageValue.style === this.value.style)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
        !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    }
  }
}

class TextAreaTextAlignModifier extends ModifierWithKey<TextAlign> {
  constructor(value: TextAlign) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaTextAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetTextAlign(node);
    } else {
      getUINativeModule().textArea.setTextAlign(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaShowCounterModifier extends ModifierWithKey<ArkTextFieldShowCounter> {
  constructor(value: ArkTextFieldShowCounter) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaShowCounter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetShowCounter(node);
    } else {
      getUINativeModule().textArea.setShowCounter(node, this.value.value!, this.value.highlightBorder, this.value.thresholdPercentage);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.highlightBorder, this.value.highlightBorder) ||
      !isBaseOrResourceEqual(this.stageValue.thresholdPercentage, this.value.thresholdPercentage);
  }
}

class TextAreaFontFeatureModifier extends ModifierWithKey<FontFeature> {
  constructor(value: FontFeature) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontFeature');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetFontFeature(node);
    } else {
      getUINativeModule().textArea.setFontFeature(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaSelectedBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaSelectedBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().textArea.setSelectedBackgroundColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaCaretStyleModifier extends ModifierWithKey<CaretStyle> {
  constructor(value: CaretStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaCaretStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetCaretStyle(node);
    } else {
      getUINativeModule().textArea.setCaretStyle(node, this.value.width!,
        this.value.color);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class TextAreaTextOverflowModifier extends ModifierWithKey<TextOverflow> {
  constructor(value: TextOverflow) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaTextOverflow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetTextOverflow(node);
    } else {
      getUINativeModule().textArea.setTextOverflow(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class TextAreaTextIndentModifier extends ModifierWithKey<Dimension> {
  constructor(value: Dimension) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaTextIndent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetTextIndent(node);
    } else {
      getUINativeModule().textArea.setTextIndent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaOnChangeModifier extends ModifierWithKey<(value: ChangeValueInfo) => void> {
  constructor(value: (value: ChangeValueInfo) => void) {
    super(value);
  }
  static identity = Symbol('textAreaOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnChange(node);
    } else {
      getUINativeModule().textArea.setOnChange(node, this.value);
    }
  }
}

class TextAreaEnterKeyTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaEnterKeyType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetEnterKeyType(node);
    } else {
      getUINativeModule().textArea.setEnterKeyType(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaInputFilterModifier extends ModifierWithKey<ArkTextInputFilter> {
  constructor(value: ArkTextInputFilter) {
    super(value);
  }
  static identity = Symbol('textAreaInputFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetInputFilter(node);
    }
    else {
      getUINativeModule().textArea.setInputFilter(node, this.value.value, this.value.error);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.error, this.value.error);
  }
}

class TextAreaOnTextSelectionChangeModifier extends ModifierWithKey<(selectionStart: number, selectionEnd: number) => void> {
  constructor(value: (selectionStart: number, selectionEnd: number) => void) {
    super(value);
  }
  static identity = Symbol('textAreaOnTextSelectionChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnTextSelectionChange(node);
    } else {
      getUINativeModule().textArea.setOnTextSelectionChange(node, this.value);
    }
  }
}

class TextAreaOnContentScrollModifier extends ModifierWithKey<(totalOffsetX: number, totalOffsetY: number) => void> {
  constructor(value: (totalOffsetX: number, totalOffsetY: number) => void) {
    super(value);
  }
  static identity = Symbol('textAreaOnContentScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnContentScroll(node);
    } else {
      getUINativeModule().textArea.setOnContentScroll(node, this.value);
    }
  }
}

class TextAreaOnEditChangeModifier extends ModifierWithKey<(isEditing: boolean) => void> {
  constructor(value: (isEditing: boolean) => void) {
    super(value);
  }
  static identity = Symbol('textAreaOnEditChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnEditChange(node);
    } else {
      getUINativeModule().textArea.setOnEditChange(node, this.value);
    }
  }
}

class TextAreaOnCopyModifier extends ModifierWithKey<(value: string) => void> {
  constructor(value: (value: string) => void) {
    super(value);
  }
  static identity = Symbol('textAreaOnCopy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnCopy(node);
    } else {
      getUINativeModule().textArea.setOnCopy(node, this.value);
    }
  }
}

class TextAreaOnCutModifier extends ModifierWithKey<(value: string) => void> {
  constructor(value: (value: string) => void) {
    super(value);
  }
  static identity = Symbol('textAreaOnCut');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnCut(node);
    } else {
      getUINativeModule().textArea.setOnCut(node, this.value);
    }
  }
}

class TextAreaOnPasteModifier extends ModifierWithKey<(value: string, event: PasteEvent) => void> {
  constructor(value: (value: string, event: PasteEvent) => void) {
    super(value);
  }
  static identity = Symbol('textAreaOnPaste');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnPaste(node);
    } else {
      getUINativeModule().textArea.setOnPaste(node, this.value);
    }
  }
}

class TextAreaTypeModifier extends ModifierWithKey<TextAreaType> {
  constructor(value: TextAreaType) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetType(node);
    }
    else {
      getUINativeModule().textArea.setType(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaPaddingModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaPadding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetPadding(node);
    }
    else {
      getUINativeModule().textArea.setPadding(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}

class TextAreaOnSubmitModifier extends ModifierWithKey<(enterKey: EnterKeyType, event: SubmitEvent) => void> {
  constructor(value: (enterKey: EnterKeyType, event: SubmitEvent) => void) {
    super(value);
  }
  static identity = Symbol('textAreaOnSubmit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnSubmit(node);
    } else {
      getUINativeModule().textArea.setOnSubmit(node, this.value);
    }
  }
}

class TextAreaContentTypeModifier extends ModifierWithKey<ContentType> {
  constructor(value: ContentType) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaContentType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetContentType(node);
    }
    else {
      getUINativeModule().textArea.setContentType(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaEnableAutoFillModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaEnableAutoFill');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetEnableAutoFill(node);
    } else {
      getUINativeModule().textArea.setEnableAutoFill(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaBorderModifier extends ModifierWithKey<ArkBorder> {
  constructor(value: ArkBorder) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaBorder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetBorder(node);
    } else {
      getUINativeModule().textArea.setBorder(node,
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

class TextAreaBorderWidthModifier extends ModifierWithKey<Length | EdgeWidths> {
  constructor(value: Length | EdgeWidths | LocalizedEdgeWidths) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaBorderWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetBorderWidth(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().textArea.setBorderWidth(node, this.value, this.value, this.value, this.value);
      } else {
        if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
          getUINativeModule().textArea.setBorderWidth(node,
            (this.value as LocalizedEdgeWidths).top,
            (this.value as LocalizedEdgeWidths).end,
            (this.value as LocalizedEdgeWidths).bottom,
            (this.value as LocalizedEdgeWidths).start);
        } else {
          getUINativeModule().textArea.setBorderWidth(node,
            (this.value as EdgeWidths).top,
            (this.value as EdgeWidths).right,
            (this.value as EdgeWidths).bottom,
            (this.value as EdgeWidths).left);
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
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

class TextAreaBorderColorModifier extends ModifierWithKey<ResourceColor | EdgeColors> {
  constructor(value: ResourceColor | EdgeColors | LocalizedEdgeColors) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaBorderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetBorderColor(node);
    } else {
      const valueType: string = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().textArea.setBorderColor(node, this.value, this.value, this.value, this.value);
      } else {
        if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
          getUINativeModule().textArea.setBorderColor(node,
            (this.value as LocalizedEdgeColors).top,
            (this.value as LocalizedEdgeColors).end,
            (this.value as LocalizedEdgeColors).bottom,
            (this.value as LocalizedEdgeColors).start,
            true);
        } else {
          getUINativeModule().textArea.setBorderColor(node,
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
    if (!isResource(this.stageValue) && !isResource(this.value)) {
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

class TextAreaBorderStyleModifier extends ModifierWithKey<BorderStyle | EdgeStyles> {
  constructor(value: BorderStyle | EdgeStyles) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaBorderStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetBorderStyle(node);
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
        getUINativeModule().textArea.setBorderStyle(node, type, style, top, right, bottom, left);
      } else {
        getUINativeModule().textArea.resetBorderStyle(node);
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

class TextAreaBorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses> {
  constructor(value: Length | BorderRadiuses | LocalizedBorderRadius) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaBorderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().textArea.setBorderRadius(node, this.value, this.value, this.value, this.value);
      } else {
        if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
            (Object.keys(this.value).indexOf('topEnd') >= 0) ||
            (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
            (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
          getUINativeModule().textArea.setBorderRadius(node,
            (this.value as LocalizedBorderRadius).topStart,
            (this.value as LocalizedBorderRadius).topEnd,
            (this.value as LocalizedBorderRadius).bottomStart,
            (this.value as LocalizedBorderRadius).bottomEnd);
        } else {
          getUINativeModule().textArea.setBorderRadius(node,
            (this.value as BorderRadiuses).topLeft,
            (this.value as BorderRadiuses).topRight,
            (this.value as BorderRadiuses).bottomLeft,
            (this.value as BorderRadiuses).bottomRight);
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
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

class TextAreaBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetBackgroundColor(node);
    } else {
      getUINativeModule().textArea.setBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaMarginModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMargin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetMargin(node);
    } else {
      getUINativeModule().textArea.setMargin(node, this.value.top,
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

class TextAreaOnWillChangeModifier extends ModifierWithKey<Callback<ChangeValueInfo, boolean>> {
  constructor(value: Callback<ChangeValueInfo, boolean>) {
    super(value);
  }
  static identity = Symbol('textAreaOnWillChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnWillChange(node);
    } else {
      getUINativeModule().textArea.setOnWillChange(node, this.value);
    }
  }
}

class TextAreaOnWillInsertModifier extends ModifierWithKey<Callback<InsertValue, boolean>> {
  constructor(value: Callback<InsertValue, boolean>) {
    super(value);
  }
  static identity = Symbol('textAreaOnWillInsert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnWillInsert(node);
    } else {
      getUINativeModule().textArea.setOnWillInsert(node, this.value);
    }
  }
}

class TextAreaOnDidInsertModifier extends ModifierWithKey<Callback<InsertValue>> {
  constructor(value: Callback<InsertValue>) {
    super(value);
  }
  static identity = Symbol('textAreaOnDidInsert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnDidInsert(node);
    } else {
      getUINativeModule().textArea.setOnDidInsert(node, this.value);
    }
  }
}

class TextAreaOnWillDeleteModifier extends ModifierWithKey<Callback<DeleteValue, boolean>> {
  constructor(value: Callback<DeleteValue, boolean>) {
    super(value);
  }
  static identity = Symbol('textAreaOnWillDelete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnWillDelete(node);
    } else {
      getUINativeModule().textArea.setOnWillDelete(node, this.value);
    }
  }
}

class TextAreaOnDidDeleteModifier extends ModifierWithKey<Callback<DeleteValue>> {
  constructor(value: Callback<DeleteValue>) {
    super(value);
  }
  static identity = Symbol('textAreaOnDidDelete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetOnDidDelete(node);
    } else {
      getUINativeModule().textArea.setOnDidDelete(node, this.value);
    }
  }
}

class TextAreaEnablePreviewTextModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaEnablePreviewText');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetEnablePreviewText(node);
    } else {
      getUINativeModule().textArea.setEnablePreviewText(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaEditMenuOptionsModifier extends ModifierWithKey<EditMenuOptions> {
  constructor(value: EditMenuOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textEditMenuOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetSelectionMenuOptions(node);
    } else {
      getUINativeModule().textArea.setSelectionMenuOptions(node, this.value);
    }
  }
}

class TextAreaInitializeModifier extends ModifierWithKey<TextAreaOptions> {
  constructor(value: TextAreaOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.setTextAreaInitialize(node, undefined, undefined, undefined);
    } else {
      getUINativeModule().textArea.setTextAreaInitialize(node, this.value?.placeholder, this.value?.text, this.value?.controller);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.placeholder, this.value?.placeholder) ||
      !isBaseOrResourceEqual(this.stageValue?.text, this.value?.text) ||
      !isBaseOrResourceEqual(this.stageValue?.controller, this.value?.controller);
  }
}

class TextAreaEnableHapticFeedbackModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaEnableHapticFeedback');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetEnableHapticFeedback(node);
    } else {
      getUINativeModule().textArea.setEnableHapticFeedback(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaEllipsisModeModifier extends ModifierWithKey<EllipsisMode> {
  constructor(value: EllipsisMode) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaEllipsisMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetEllipsisMode(node);
    } else {
      getUINativeModule().text.setEllipsisMode(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkTextAreaComponent extends ArkComponent implements CommonMethod<TextAreaAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  initialize(value: Object[]): TextAreaAttribute {
    if (value.length === 1 && isObject(value[0])) {
      modifierWithKey(this._modifiersWithKeys, TextAreaInitializeModifier.identity, TextAreaInitializeModifier, value[0]);
    }
    return this;
  }
  type(value: TextAreaType): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaTypeModifier.identity, TextAreaTypeModifier, value);
    return this;
  }
  placeholderColor(value: ResourceColor): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaPlaceholderColorModifier.identity, TextAreaPlaceholderColorModifier, value);
    return this;
  }
  placeholderFont(value: Font): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaPlaceholderFontModifier.identity, TextAreaPlaceholderFontModifier, value);
    return this;
  }

  textAlign(value: TextAlign): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaTextAlignModifier.identity, TextAreaTextAlignModifier, value);
    return this;
  }
  caretColor(value: ResourceColor): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaCaretColorModifier.identity, TextAreaCaretColorModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontColorModifier.identity, TextAreaFontColorModifier, value);
    return this;
  }
  fontSize(value: Length): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontSizeModifier.identity, TextAreaFontSizeModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontStyleModifier.identity, TextAreaFontStyleModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontWeightModifier.identity, TextAreaFontWeightModifier, value);
    return this;
  }
  fontFamily(value: ResourceStr): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontFamilyModifier.identity, TextAreaFontFamilyModifier, value);
    return this;
  }
  inputFilter(value: ResourceStr, error?: (value: string) => void): TextAreaAttribute {
    let arkValue = new ArkTextInputFilter();
    arkValue.value = value;
    arkValue.error = error;
    modifierWithKey(this._modifiersWithKeys, TextAreaInputFilterModifier.identity, TextAreaInputFilterModifier, arkValue);
    return this;
  }
  onChange(callback: (value: ChangeValueInfo) => void): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnChangeModifier.identity,
      TextAreaOnChangeModifier, callback);
    return this;
  }
  onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnTextSelectionChangeModifier.identity,
      TextAreaOnTextSelectionChangeModifier, callback);
    return this;
  }
  onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnContentScrollModifier.identity,
      TextAreaOnContentScrollModifier, callback);
    return this;
  }
  onEditChange(callback: (isEditing: boolean) => void): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnEditChangeModifier.identity,
      TextAreaOnEditChangeModifier, callback);
    return this;
  }
  onCopy(callback: (value: string) => void): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnCopyModifier.identity,
      TextAreaOnCopyModifier, callback);
    return this;
  }
  onCut(callback: (value: string) => void): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnCutModifier.identity,
      TextAreaOnCutModifier, callback);
    return this;
  }
  onPaste(callback: (value: string) => void): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnPasteModifier.identity,
      TextAreaOnPasteModifier, callback);
    return this;
  }
  copyOption(value: CopyOptions): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaCopyOptionModifier.identity, TextAreaCopyOptionModifier, value);
    return this;
  }

  enableKeyboardOnFocus(value: boolean): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaEnableKeyboardOnFocusModifier.identity, TextAreaEnableKeyboardOnFocusModifier, value);
    return this;
  }

  maxLength(value: number): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaMaxLengthModifier.identity, TextAreaMaxLengthModifier, value);
    return this;
  }
  showCounter(value: boolean, options?: InputCounterOptions): TextAreaAttribute {
    let arkValue: ArkTextFieldShowCounter = new ArkTextFieldShowCounter();
    arkValue.value = value;
    arkValue.highlightBorder = options?.highlightBorder;
    arkValue.thresholdPercentage = options?.thresholdPercentage;
    modifierWithKey(this._modifiersWithKeys, TextAreaShowCounterModifier.identity, TextAreaShowCounterModifier, arkValue);
    return this;
  }
  style(value: TextContentStyle): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaStyleModifier.identity, TextAreaStyleModifier, value);
    return this;
  }
  barState(value: BarState): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaBarStateModifier.identity, TextAreaBarStateModifier, value);
    return this;
  }
  selectionMenuHidden(value: boolean): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaSelectionMenuHiddenModifier.identity, TextAreaSelectionMenuHiddenModifier, value);
    return this;
  }
  maxLines(value: number): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaMaxLinesModifier.identity, TextAreaMaxLinesModifier, value);
    return this;
  }
  fontFeature(value: FontFeature): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontFeatureModifier.identity, TextAreaFontFeatureModifier, value);
    return this;
  }
  customKeyboard(value: CustomBuilder): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  decoration(value: { type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaDecorationModifier.identity, TextAreaDecorationModifier, value);
    return this;
  }
  letterSpacing(value: number | string): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaLetterSpacingModifier.identity, TextAreaLetterSpacingModifier, value);
    return this;
  }
  lineHeight(value: number | string | Resource): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaLineHeightModifier.identity, TextAreaLineHeightModifier, value);
    return this;
  }
  halfLeading(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaHalfLeadingModifier.identity, TextAreaHalfLeadingModifier, value);
    return this;
  }
  lineSpacing(value: LengthMetrics): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaLineSpacingModifier.identity, TextAreaLineSpacingModifier, value);
    return this;
  }
  wordBreak(value: WordBreak): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaWordBreakModifier.identity, TextAreaWordBreakModifier, value);
    return this;
  }
  lineBreakStrategy(value: LineBreakStrategy): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaLineBreakStrategyModifier.identity,
      TextAreaLineBreakStrategyModifier, value);
    return this;
  }
  minFontSize(value: number | string | Resource): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaMinFontSizeModifier.identity, TextAreaMinFontSizeModifier, value);
    return this;
  }
  maxFontSize(value: number | string | Resource): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaMaxFontSizeModifier.identity, TextAreaMaxFontSizeModifier, value);
    return this;
  }
  minFontScale(value: number | Resource): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaMinFontScaleModifier.identity, TextAreaMinFontScaleModifier, value);
    return this;
  }
  maxFontScale(value: number | Resource): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaMaxFontScaleModifier.identity, TextAreaMaxFontScaleModifier, value);
    return this;
  }
  heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaHeightAdaptivePolicyModifier.identity, TextAreaHeightAdaptivePolicyModifier, value);
    return this;
  }
  selectedBackgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaSelectedBackgroundColorModifier.identity, TextAreaSelectedBackgroundColorModifier, value);
    return this;
  }
  caretStyle(value: CaretStyle): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaCaretStyleModifier.identity, TextAreaCaretStyleModifier, value);
    return this;
  }
  textOverflow(value: TextOverflow): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaTextOverflowModifier.identity, TextAreaTextOverflowModifier, value);
    return this;
  }
  textIndent(value: Dimension): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaTextIndentModifier.identity, TextAreaTextIndentModifier, value);
    return this;
  }
  enterKeyType(value: EnterKeyType): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaEnterKeyTypeModifier.identity,
      TextAreaEnterKeyTypeModifier, value);
    return this;
  }
  ellipsisMode(value: EllipsisMode): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaEllipsisModeModifier.identity, TextAreaEllipsisModeModifier, value);
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
      modifierWithKey(this._modifiersWithKeys, TextAreaPaddingModifier.identity, TextAreaPaddingModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, TextAreaPaddingModifier.identity, TextAreaPaddingModifier, undefined);
    }
    return this;
  }
  onSubmit(callback: (enterKey: EnterKeyType, event: SubmitEvent) => void): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnSubmitModifier.identity,
      TextAreaOnSubmitModifier, callback);
    return this;
  }
  contentType(value: ContentType): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaContentTypeModifier.identity,
      TextAreaContentTypeModifier, value);
    return this;
  }
  enableAutoFill(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaEnableAutoFillModifier.identity,
      TextAreaEnableAutoFillModifier, value);
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
        borderValue.arkDashWidth.start = (value.dashWidth as LocalizedEdgeWidths).start;
        borderValue.arkDashWidth.end = (value.dashWidth as LocalizedEdgeWidths).end;
      }
    }
    modifierWithKey(this._modifiersWithKeys, TextAreaBorderModifier.identity, TextAreaBorderModifier, borderValue);
    return this;
  }
  borderWidth(value: Length | EdgeWidths): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaBorderWidthModifier.identity, TextAreaBorderWidthModifier, value);
    return this;
  }
  borderColor(value: ResourceColor | EdgeColors): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaBorderColorModifier.identity, TextAreaBorderColorModifier, value);
    return this;
  }
  borderStyle(value: BorderStyle | EdgeStyles): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaBorderStyleModifier.identity, TextAreaBorderStyleModifier, value);
    return this;
  }
  borderRadius(value: Length | BorderRadiuses): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaBorderRadiusModifier.identity, TextAreaBorderRadiusModifier, value);
    return this;
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaBackgroundColorModifier.identity, TextAreaBackgroundColorModifier, value);
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
      modifierWithKey(this._modifiersWithKeys, TextAreaMarginModifier.identity, TextAreaMarginModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, TextAreaMarginModifier.identity, TextAreaMarginModifier, undefined);
    }
    return this;
  }
  onWillChange(callback: Callback<ChangeValueInfo, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnWillChangeModifier.identity, TextAreaOnWillChangeModifier, callback);
    return this;
  }
  onWillInsert(callback: Callback<InsertValue, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnWillInsertModifier.identity, TextAreaOnWillInsertModifier, callback);
    return this;
  }
  onDidInsert(callback: Callback<InsertValue>): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnDidInsertModifier.identity, TextAreaOnDidInsertModifier, callback);
    return this;
  }
  onWillDelete(callback: Callback<DeleteValue, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnWillDeleteModifier.identity, TextAreaOnWillDeleteModifier, callback);
    return this;
  }
  onDidDelete(callback: Callback<DeleteValue>): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaOnDidDeleteModifier.identity, TextAreaOnDidDeleteModifier, callback);
    return this;
  }
  enablePreviewText(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaEnablePreviewTextModifier.identity, TextAreaEnablePreviewTextModifier, value);
    return this;
  }
  editMenuOptions(value: EditMenuOptions): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaEditMenuOptionsModifier.identity,
      TextAreaEditMenuOptionsModifier, value);
    return this;
  }
  enableHapticFeedback(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextAreaEnableHapticFeedbackModifier.identity, TextAreaEnableHapticFeedbackModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.TextArea.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkTextAreaComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TextAreaModifier(nativePtr, classType);
  });
};
