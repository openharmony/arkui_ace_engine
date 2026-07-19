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
    class ArkTextAreaComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      enableSelectedDataDetector(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaSelectDetectorEnableModifier.identity, TextAreaSelectDetectorEnableModifier, value);
        return this;
      }
      horizontalScrolling(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaHorizontalScrollingModifier.identity, TextAreaHorizontalScrollingModifier, value);
        return this;
      }
      allowChildCount(): number {
        return 0;
      }
      initialize(value: any): this {
        if (value.length === 1 && isObject(value[0])) {
          modifierWithKey(this._modifiersWithKeys, TextAreaInitializeModifier.identity, TextAreaInitializeModifier, value[0]);
        }
        return this;
      }
      type(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaTypeModifier.identity, TextAreaTypeModifier, value);
        return this;
      }
      placeholderColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaPlaceholderColorModifier.identity, TextAreaPlaceholderColorModifier, value);
        return this;
      }
      placeholderFont(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaPlaceholderFontModifier.identity, TextAreaPlaceholderFontModifier, value);
        return this;
      }
      textAlign(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaTextAlignModifier.identity, TextAreaTextAlignModifier, value);
        return this;
      }
      caretColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaCaretColorModifier.identity, TextAreaCaretColorModifier, value);
        return this;
      }
      fontColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaFontColorModifier.identity, TextAreaFontColorModifier, value);
        return this;
      }
      fontSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaFontSizeModifier.identity, TextAreaFontSizeModifier, value);
        return this;
      }
      fontStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaFontStyleModifier.identity, TextAreaFontStyleModifier, value);
        return this;
      }
      fontWeight(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaFontWeightModifier.identity, TextAreaFontWeightModifier, value);
        return this;
      }
      fontFamily(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaFontFamilyModifier.identity, TextAreaFontFamilyModifier, value);
        return this;
      }
      fontFeature(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaFontFeatureModifier.identity, TextAreaFontFeatureModifier, value);
        return this;
      }
      inputFilter(value: any, error: any): this {
        let arkValue = new ArkTextInputFilter();
        arkValue.value = value;
        arkValue.error = error;
        modifierWithKey(this._modifiersWithKeys, TextAreaInputFilterModifier.identity, TextAreaInputFilterModifier, arkValue);
        return this;
      }
      onChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnChangeModifier.identity, TextAreaOnChangeModifier, callback);
        return this;
      }
      onTextSelectionChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnTextSelectionChangeModifier.identity, TextAreaOnTextSelectionChangeModifier, callback);
        return this;
      }
      onContentScroll(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnContentScrollModifier.identity, TextAreaOnContentScrollModifier, callback);
        return this;
      }
      onEditChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnEditChangeModifier.identity, TextAreaOnEditChangeModifier, callback);
        return this;
      }
      onWillCopy(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnWillCopyModifier.identity, TextAreaOnWillCopyModifier, callback);
        return this;
      }
      onCopy(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnCopyModifier.identity, TextAreaOnCopyModifier, callback);
        return this;
      }
      onWillCut(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnWillCutModifier.identity, TextAreaOnWillCutModifier, callback);
        return this;
      }
      onCut(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnCutModifier.identity, TextAreaOnCutModifier, callback);
        return this;
      }
      onPaste(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnPasteModifier.identity, TextAreaOnPasteModifier, callback);
        return this;
      }
      copyOption(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaCopyOptionModifier.identity, TextAreaCopyOptionModifier, value);
        return this;
      }
      enableKeyboardOnFocus(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaEnableKeyboardOnFocusModifier.identity, TextAreaEnableKeyboardOnFocusModifier, value);
        return this;
      }
      maxLength(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaMaxLengthModifier.identity, TextAreaMaxLengthModifier, value);
        return this;
      }
      showCounter(value: any, options: any): this {
        let arkValue = new ArkTextFieldShowCounter();
        arkValue.value = value;
        arkValue.highlightBorder = options?.highlightBorder;
        arkValue.thresholdPercentage = options?.thresholdPercentage;
        arkValue.counterTextColor = options?.counterTextColor;
        arkValue.counterTextOverflowColor = options?.counterTextOverflowColor;
        modifierWithKey(this._modifiersWithKeys, TextAreaShowCounterModifier.identity, TextAreaShowCounterModifier, arkValue);
        return this;
      }
      style(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaStyleModifier.identity, TextAreaStyleModifier, value);
        return this;
      }
      barState(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaBarStateModifier.identity, TextAreaBarStateModifier, value);
        return this;
      }
      selectionMenuHidden(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaSelectionMenuHiddenModifier.identity, TextAreaSelectionMenuHiddenModifier, value);
        return this;
      }
      maxLines(value: any, options: any): this {
        let arkValue = new ArkTextFieldMaxLines();
        arkValue.value = value;
        arkValue.overflowMode = options?.overflowMode;
        modifierWithKey(this._modifiersWithKeys, TextAreaMaxLinesModifier.identity, TextAreaMaxLinesModifier, arkValue);
        return this;
      }
      minLines(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaMinLinesModifier.identity, TextAreaMinLinesModifier, value);
        return this;
      }
      customKeyboard(value: any, options: any): this {
        let arkValue = new ArkCustomKeyboard();
        arkValue.value = value;
        arkValue.supportAvoidance = options?.supportAvoidance;
        modifierWithKey(this._modifiersWithKeys, TextAreaCustomKeyboardModifier.identity,
          TextAreaCustomKeyboardModifier, arkValue);
        return this;
      }
      decoration(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaDecorationModifier.identity, TextAreaDecorationModifier, value);
        return this;
      }
      letterSpacing(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaLetterSpacingModifier.identity, TextAreaLetterSpacingModifier, value);
        return this;
      }
      lineSpacing(value: any, options: any): this {
        let arkLineSpacing = new ArkLineSpacing();
        arkLineSpacing.value = value;
        arkLineSpacing.onlyBetweenLines = options?.onlyBetweenLines;
        modifierWithKey(this._modifiersWithKeys, TextAreaLineSpacingModifier.identity, TextAreaLineSpacingModifier,
          arkLineSpacing);
        return this;
      }
      lineHeight(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaLineHeightModifier.identity, TextAreaLineHeightModifier, value);
        return this;
      }
      halfLeading(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaHalfLeadingModifier.identity, TextAreaHalfLeadingModifier, value);
        return this;
      }
      wordBreak(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaWordBreakModifier.identity, TextAreaWordBreakModifier, value);
        return this;
      }
      lineBreakStrategy(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaLineBreakStrategyModifier.identity,
          TextAreaLineBreakStrategyModifier, value);
        return this;
      }
      minFontSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaMinFontSizeModifier.identity, TextAreaMinFontSizeModifier, value);
        return this;
      }
      maxFontSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaMaxFontSizeModifier.identity, TextAreaMaxFontSizeModifier, value);
        return this;
      }
      minFontScale(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaMinFontScaleModifier.identity, TextAreaMinFontScaleModifier, value);
        return this;
      }
      maxFontScale(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaMaxFontScaleModifier.identity, TextAreaMaxFontScaleModifier, value);
        return this;
      }
      heightAdaptivePolicy(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaHeightAdaptivePolicyModifier.identity, TextAreaHeightAdaptivePolicyModifier, value);
        return this;
      }
      selectedBackgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaSelectedBackgroundColorModifier.identity, TextAreaSelectedBackgroundColorModifier, value);
        return this;
      }
      caretStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaCaretStyleModifier.identity, TextAreaCaretStyleModifier, value);
        return this;
      }
      textOverflow(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaTextOverflowModifier.identity, TextAreaTextOverflowModifier, value);
        return this;
      }
      textIndent(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaTextIndentModifier.identity, TextAreaTextIndentModifier, value);
        return this;
      }
      enterKeyType(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaEnterKeyTypeModifier.identity, TextAreaEnterKeyTypeModifier, value);
        return this;
      }
      padding(value: any): this {
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
      onSubmit(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnSubmitModifier.identity, TextAreaOnSubmitModifier, callback);
        return this;
      }
      contentType(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaContentTypeModifier.identity,
          TextAreaContentTypeModifier, value);
        return this;
      }
      enableAutoFill(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaEnableAutoFillModifier.identity,
          TextAreaEnableAutoFillModifier, value);
        return this;
      }
      border(value: any): this {
        let arkBorder = valueToArkBorder(value);
        modifierWithKey(this._modifiersWithKeys, TextAreaBorderModifier.identity, TextAreaBorderModifier, arkBorder);
        return this;
      }
      borderWidth(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaBorderWidthModifier.identity, TextAreaBorderWidthModifier, value);
        return this;
      }
      borderColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaBorderColorModifier.identity, TextAreaBorderColorModifier, value);
        return this;
      }
      borderStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaBorderStyleModifier.identity, TextAreaBorderStyleModifier, value);
        return this;
      }
      borderRadius(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaBorderRadiusModifier.identity, TextAreaBorderRadiusModifier, value);
        return this;
      }
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaBackgroundColorModifier.identity, TextAreaBackgroundColorModifier, value);
        return this;
      }
      margin(value: any): this {
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
          modifierWithKey(this._modifiersWithKeys, TextAreaMarginModifier.identity, TextAreaMarginModifier, arkValue);
        }
        else {
          modifierWithKey(this._modifiersWithKeys, TextAreaMarginModifier.identity, TextAreaMarginModifier, undefined);
        }
        return this;
      }
      onWillChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnWillChangeModifier.identity, TextAreaOnWillChangeModifier, callback);
        return this;
      }
      onWillInsert(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnWillInsertModifier.identity, TextAreaOnWillInsertModifier, callback);
        return this;
      }
      onDidInsert(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnDidInsertModifier.identity, TextAreaOnDidInsertModifier, callback);
        return this;
      }
      onWillDelete(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnWillDeleteModifier.identity, TextAreaOnWillDeleteModifier, callback);
        return this;
      }
      onDidDelete(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnDidDeleteModifier.identity, TextAreaOnDidDeleteModifier, callback);
        return this;
      }
      enablePreviewText(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaEnablePreviewTextModifier.identity, TextAreaEnablePreviewTextModifier, value);
        return this;
      }
      autoCapitalizationMode(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaAutoCapitalizationModifier.identity, TextAreaAutoCapitalizationModifier, value);
        return this;
      }
      editMenuOptions(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaEditMenuOptionsModifier.identity,
          TextAreaEditMenuOptionsModifier, value);
        return this;
      }
      width(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaWidthModifier.identity, TextAreaWidthModifier, value);
        return this;
      }
      enableHapticFeedback(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaEnableHapticFeedbackModifier.identity, TextAreaEnableHapticFeedbackModifier, value);
        return this;
      }
      ellipsisMode(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaEllipsisModeModifier.identity, TextAreaEllipsisModeModifier, value);
        return this;
      }
      stopBackPress(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaStopBackPressModifier.identity, TextAreaStopBackPressModifier, value);
        return this;
      }
      keyboardAppearance(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaKeyboardAppearanceModifier.identity, TextAreaKeyboardAppearanceModifier, value);
        return this;
      }
      strokeWidth(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaStrokeWidthModifier.identity, TextAreaStrokeWidthModifier, value);
        return this;
      }
      strokeColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaStrokeColorModifier.identity, TextAreaStrokeColorModifier, value);
        return this;
      }
      enableAutoSpacing(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaEnableAutoSpacingModifier.identity, TextAreaEnableAutoSpacingModifier, value);
        return this;
      }
      orphanCharOptimization(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOrphanCharOptimizationModifier.identity,
          TextAreaOrphanCharOptimizationModifier, value);
        return this;
      }
      compressLeadingPunctuation(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaCompressLeadingPunctuationModifier.identity, TextAreaCompressLeadingPunctuationModifier, value);
        return this;
      }
      punctuationOverflow(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaPunctuationOverflowModifier.identity, TextAreaPunctuationOverflowModifier, value);
        return this;
      }
      includeFontPadding(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaIncludeFontPaddingModifier.identity, TextAreaIncludeFontPaddingModifier, value);
        return this;
      }
      fallbackLineSpacing(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaFallbackLineSpacingModifier.identity, TextAreaFallbackLineSpacingModifier, value);
        return this;
      }
      scrollBarColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaScrollBarColorModifier.identity, TextAreaScrollBarColorModifier, value);
        return this;
      }
      onWillAttachIME(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaOnWillAttachIMEModifier.identity,
          TextAreaOnWillAttachIMEModifier, callback);
        return this;
      }
      textDirection(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaTextDirectionModifier.identity, TextAreaTextDirectionModifier, value);
        return this;
      }
      selectedDragPreviewStyle(value: any): this {
        let arkSelectedDragPreviewStyle = new ArkSelectedDragPreviewStyle();
        arkSelectedDragPreviewStyle.color = value?.color;
        modifierWithKey(this._modifiersWithKeys, TextAreaSelectedDragPreviewStyleModifier.identity,
          TextAreaSelectedDragPreviewStyleModifier, arkSelectedDragPreviewStyle);
        return this;
      }
      strokeJoinStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaStrokeJoinStyleModifier.identity,
          TextAreaStrokeJoinStyleModifier, value);
        return this;
      }
      shaderStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextAreaShaderStyleModifier.identity, TextAreaShaderStyleModifier, value);
        return this;
      }
    }

    class TextAreaFontStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetFontStyle(node);
        }
        else {
          getUINativeModule().textArea.setFontStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaFontStyleModifier as any).identity = Symbol('textAreaFontStyle');
    class TextAreaDecorationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetDecoration(node);
        }
        else {
          getUINativeModule().textArea.setDecoration(node, this.value.type, this.value.color,
            this.value.style, this.value.thicknessScale);
        }
      }
      checkObjectDiff(): boolean {
        if (this.stageValue.type !== this.value.type || this.stageValue.style !== this.value.style ||
            this.stageValue.thicknessScale !== this.value.thicknessScale) {
          return true;
        }
        if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
          return !(this.stageValue.color === this.value.color);
        }
        else {
          return true;
        }
      }
    }
    (TextAreaDecorationModifier as any).identity = Symbol('textAreaDecoration');
    class TextAreaLetterSpacingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetLetterSpacing(node);
        }
        else {
          getUINativeModule().textArea.setLetterSpacing(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaLetterSpacingModifier as any).identity = Symbol('textAreaLetterSpacing');
    class TextAreaLineSpacingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetLineSpacing(node);
        }
        else if (!isObject(this.value)) {
          getUINativeModule().textArea.resetLineSpacing(node);
        }
        else {
          getUINativeModule().textArea.setLineSpacing(node, this.value.value, this.value.onlyBetweenLines);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaLineSpacingModifier as any).identity = Symbol('textAreaLineSpacing');
    class TextAreaLineHeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetLineHeight(node);
        }
        else {
          getUINativeModule().textArea.setLineHeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaLineHeightModifier as any).identity = Symbol('textAreaLineHeight');
    class TextAreaHalfLeadingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetHalfLeading(node);
        }
        else {
          getUINativeModule().textArea.setHalfLeading(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaHalfLeadingModifier as any).identity = Symbol('textAreaHalfLeading');
    class TextAreaWordBreakModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetWordBreak(node);
        }
        else {
          getUINativeModule().textArea.setWordBreak(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaWordBreakModifier as any).identity = Symbol('textAreaWordBreak');

    class TextAreaLineBreakStrategyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetLineBreakStrategy(node);
        }
        else {
          getUINativeModule().textArea.setLineBreakStrategy(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaLineBreakStrategyModifier as any).identity = Symbol('textAreaLineBreakStrategy');
    class TextAreaSelectedBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetSelectedBackgroundColor(node);
        } else {
          getUINativeModule().textArea.setSelectedBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaSelectedBackgroundColorModifier as any).identity = Symbol('textAreaSelectedBackgroundColor');
    class TextAreaCaretStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetCaretStyle(node);
        } else {
          getUINativeModule().textArea.setCaretStyle(node, this.value.width, this.value.color);
        }
      }
      checkObjectDiff(): boolean {
        if (isObject(this.stageValue) && isObject(this.value)) {
          return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
            !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
        }
        else {
          return true;
        }
      }
    }
    (TextAreaCaretStyleModifier as any).identity = Symbol('textAreaCaretStyle');
    class TextAreaTextOverflowModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetTextOverflow(node);
        } else {
          getUINativeModule().textArea.setTextOverflow(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (TextAreaTextOverflowModifier as any).identity = Symbol('textAreaTextOverflow');
    class TextAreaTextIndentModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetTextIndent(node);
        } else {
          getUINativeModule().textArea.setTextIndent(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaTextIndentModifier as any).identity = Symbol('textAreaTextIndent');
    class TextAreaCopyOptionModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetCopyOption(node);
        }
        else {
          getUINativeModule().textArea.setCopyOption(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaCopyOptionModifier as any).identity = Symbol('textAreaCopyOption');
    class TextAreaMaxLinesModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetMaxLines(node);
        }
        else {
          getUINativeModule().textArea.setMaxLines(node, this.value.value, this.value.overflowMode);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
          !isBaseOrResourceEqual(this.stageValue.overflowMode, this.value.overflowMode);
      }
    }
    (TextAreaMaxLinesModifier as any).identity = Symbol('textAreaMaxLines');
    class TextAreaMinLinesModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetMinLines(node);
        }
        else {
          getUINativeModule().textArea.setMinLines(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaMinLinesModifier as any).identity = Symbol('textAreaMinLines');
    class TextAreaMinFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetMinFontSize(node);
        }
        else {
          getUINativeModule().textArea.setMinFontSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaMinFontSizeModifier as any).identity = Symbol('textAreaMinFontSize');
    class TextAreaMaxFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetMaxFontSize(node);
        }
        else {
          getUINativeModule().textArea.setMaxFontSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaMaxFontSizeModifier as any).identity = Symbol('textAreaMaxFontSize');
    class TextAreaMinFontScaleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetMinFontScale(node);
        }
        else {
          getUINativeModule().textArea.setMinFontScale(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaMinFontScaleModifier as any).identity = Symbol('textAreaMinFontScale');
    class TextAreaMaxFontScaleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetMaxFontScale(node);
        }
        else {
          getUINativeModule().textArea.setMaxFontScale(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaMaxFontScaleModifier as any).identity = Symbol('textAreaMaxFontScale');
    class TextAreaHeightAdaptivePolicyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetHeightAdaptivePolicy(node);
        }
        else {
          getUINativeModule().textArea.setHeightAdaptivePolicy(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaHeightAdaptivePolicyModifier as any).identity = Symbol('textAreaHeightAdaptivePolicy');
    class TextAreaFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetFontSize(node);
        }
        else {
          getUINativeModule().textArea.setFontSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaFontSizeModifier as any).identity = Symbol('textAreaFontSize');
    class TextAreaPlaceholderColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetPlaceholderColor(node);
        }
        else {
          getUINativeModule().textArea.setPlaceholderColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaPlaceholderColorModifier as any).identity = Symbol('textAreaPlaceholderColor');
    class TextAreaFontColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetFontColor(node);
        }
        else {
          getUINativeModule().textArea.setFontColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaFontColorModifier as any).identity = Symbol('textAreaFontColor');
    class TextAreaFontWeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetFontWeight(node);
        }
        else {
          getUINativeModule().textArea.setFontWeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaFontWeightModifier as any).identity = Symbol('textAreaFontWeight');
    class TextAreaBarStateModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetBarState(node);
        }
        else {
          getUINativeModule().textArea.setBarState(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaBarStateModifier as any).identity = Symbol('textAreaBarState');
    class TextAreaEnableKeyboardOnFocusModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetEnableKeyboardOnFocus(node);
        }
        else {
          getUINativeModule().textArea.setEnableKeyboardOnFocus(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaEnableKeyboardOnFocusModifier as any).identity = Symbol('textAreaEnableKeyboardOnFocus');
    class TextAreaFontFamilyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetFontFamily(node);
        }
        else {
          getUINativeModule().textArea.setFontFamily(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaFontFamilyModifier as any).identity = Symbol('textAreaFontFamily');
    class TextAreaFontFeatureModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetFontFeature(node);
        } else {
          getUINativeModule().textArea.setFontFeature(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaFontFeatureModifier as any).identity = Symbol('textAreaFontFeature');
    class TextAreaCaretColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetCaretColor(node);
        }
        else {
          getUINativeModule().textArea.setCaretColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaCaretColorModifier as any).identity = Symbol('textAreaCaretColor');
    class TextAreaMaxLengthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetMaxLength(node);
        }
        else {
          getUINativeModule().textArea.setMaxLength(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaMaxLengthModifier as any).identity = Symbol('textAreaMaxLength');
    class TextAreaStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetStyle(node);
        }
        else {
          getUINativeModule().textArea.setStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaStyleModifier as any).identity = Symbol('textAreaStyle');
    class TextAreaSelectionMenuHiddenModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetSelectionMenuHidden(node);
        }
        else {
          getUINativeModule().textArea.setSelectionMenuHidden(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaSelectionMenuHiddenModifier as any).identity = Symbol('textAreaSelectionMenuHidden');
    class TextAreaPlaceholderFontModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetPlaceholderFont(node);
        }
        else {
          getUINativeModule().textArea.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
      }
      checkObjectDiff(): boolean {
        if (!(this.stageValue.weight === this.value.weight &&
          this.stageValue.style === this.value.style)) {
          return true;
        }
        else {
          return !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
            !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
        }
      }
    }
    (TextAreaPlaceholderFontModifier as any).identity = Symbol('textAreaPlaceholderFont');
    class TextAreaTextAlignModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetTextAlign(node);
        }
        else {
          getUINativeModule().textArea.setTextAlign(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaTextAlignModifier as any).identity = Symbol('textAreaTextAlign');
    class TextAreaShowCounterModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetShowCounter(node);
        }
        else {
          getUINativeModule().textArea.setShowCounter(node, this.value.value, this.value.highlightBorder, this.value.thresholdPercentage, this.value.counterTextColor, this.value.counterTextOverflowColor);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
          !isBaseOrResourceEqual(this.stageValue.highlightBorder, this.value.highlightBorder) ||
          !isBaseOrResourceEqual(this.stageValue.thresholdPercentage, this.value.thresholdPercentage) ||
          !isBaseOrResourceEqual(this.stageValue.counterTextColor, this.value.counterTextColor) ||
          !isBaseOrResourceEqual(this.stageValue.counterTextOverflowColor, this.value.counterTextOverflowColor);
      }
    }
    (TextAreaShowCounterModifier as any).identity = Symbol('textAreaShowCounter');
    class TextAreaOnChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnChange(node);
        } else {
          getUINativeModule().textArea.setOnChange(node, this.value);
        }
      }
    }
    (TextAreaOnChangeModifier as any).identity = Symbol('textAreaOnChange');
    class TextAreaEnterKeyTypeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextAreaEnterKeyTypeModifier as any).identity = Symbol('textAreaEnterKeyType');
    class TextAreaAutoCapitalizationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetAutoCapitalizationMode(node);
        }
        else {
          getUINativeModule().textArea.setAutoCapitalizationMode(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaAutoCapitalizationModifier as any).identity = Symbol('textAreaAutoCapitalization');
    class TextAreaInputFilterModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextAreaInputFilterModifier as any).identity = Symbol('textAreaInputFilter');
    class TextAreaOnTextSelectionChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnTextSelectionChange(node);
        } else {
          getUINativeModule().textArea.setOnTextSelectionChange(node, this.value);
        }
      }
    }
    (TextAreaOnTextSelectionChangeModifier as any).identity = Symbol('textAreaOnTextSelectionChange');

    class TextAreaOnContentScrollModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnContentScroll(node);
        } else {
          getUINativeModule().textArea.setOnContentScroll(node, this.value);
        }
      }
    }
    (TextAreaOnContentScrollModifier as any).identity = Symbol('textAreaOnContentScroll');
    class TextAreaOnEditChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnEditChange(node);
        } else {
          getUINativeModule().textArea.setOnEditChange(node, this.value);
        }
      }
    }
    (TextAreaOnEditChangeModifier as any).identity = Symbol('textAreaOnEditChange');
    class TextAreaOnWillCopyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnWillCopy(node);
        } else {
          getUINativeModule().textArea.setOnWillCopy(node, this.value);
        }
      }
    }
    (TextAreaOnWillCopyModifier as any).identity = Symbol('textAreaOnWillCopy');
    class TextAreaOnCopyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnCopy(node);
        } else {
          getUINativeModule().textArea.setOnCopy(node, this.value);
        }
      }
    }
    (TextAreaOnCopyModifier as any).identity = Symbol('textAreaOnCopy');
    class TextAreaOnWillCutModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnWillCut(node);
        } else {
          getUINativeModule().textArea.setOnWillCut(node, this.value);
        }
      }
    }
    (TextAreaOnWillCutModifier as any).identity = Symbol('textAreaOnWillCut');
    class TextAreaOnCutModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnCut(node);
        } else {
          getUINativeModule().textArea.setOnCut(node, this.value);
        }
      }
    }
    (TextAreaOnCutModifier as any).identity = Symbol('textAreaOnCut');
    class TextAreaOnPasteModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnPaste(node);
        } else {
          getUINativeModule().textArea.setOnPaste(node, this.value);
        }
      }
    }
    (TextAreaOnPasteModifier as any).identity = Symbol('textAreaOnPaste');
    class TextAreaTypeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextAreaTypeModifier as any).identity = Symbol('textAreaType');
    class TextAreaCustomKeyboardModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetCustomKeyboard(node);
        } else {
          getUINativeModule().textArea.setCustomKeyboard(node, this.value.value, this.value.supportAvoidance);
        }
      }
    }
    (TextAreaCustomKeyboardModifier as any).identity = Symbol('textAreaCustomKeyboard');
    class TextAreaPaddingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextAreaPaddingModifier as any).identity = Symbol('textAreaPadding');
    class TextAreaOnSubmitModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnSubmit(node);
        } else {
          getUINativeModule().textArea.setOnSubmit(node, this.value);
        }
      }
    }
    (TextAreaOnSubmitModifier as any).identity = Symbol('textAreaOnSubmit');
    class TextAreaContentTypeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextAreaContentTypeModifier as any).identity = Symbol('textAreaContentType');
    class TextAreaEnableAutoFillModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetEnableAutoFill(node);
        } else {
          getUINativeModule().textArea.setEnableAutoFill(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaEnableAutoFillModifier as any).identity = Symbol('textAreaEnableAutoFill');
    class TextAreaBorderModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
        let emptyColor = new ArkBorderColor();
        let hasBorderColor = !this.stageValue.arkColor.isEqual(emptyColor) || !this.value.arkColor.isEqual(emptyColor);
        return hasBorderColor || this.value.checkObjectDiff(this.stageValue);
      }
    }
    (TextAreaBorderModifier as any).identity = Symbol('textAreaBorder');
    class TextAreaBorderWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetBorderWidth(node);
        }
        else {
          if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
            getUINativeModule().textArea.setBorderWidth(node, this.value, this.value, this.value, this.value);
          }
          else {
            if ((Object.keys(this.value).indexOf('start') >= 0) ||
              (Object.keys(this.value).indexOf('end') >= 0)) {
              getUINativeModule().textArea.setBorderWidth(node, this.value.top, this.value.end, this.value.bottom, this.value.start);
            } else {
              getUINativeModule().textArea.setBorderWidth(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
            }
          }
        }
      }
      checkObjectDiff(): boolean {
        if (!isResource(this.stageValue) && !isResource(this.value)) {
          if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
            return !(this.stageValue.start === this.value.start &&
              this.stageValue.end === this.value.end &&
              this.stageValue.top === this.value.top &&
              this.stageValue.bottom === this.value.bottom);
          }
          return !(this.stageValue.left === this.value.left &&
            this.stageValue.right === this.value.right &&
            this.stageValue.top === this.value.top &&
            this.stageValue.bottom === this.value.bottom);
        }
        else {
          return true;
        }
      }
    }
    (TextAreaBorderWidthModifier as any).identity = Symbol('textAreaBorderWidth');
    class TextAreaBorderColorModifier extends ModifierWithKey<any> {
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
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetBorderColor(node);
        }
        else {
          const valueType = typeof this.value;
          if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
            getUINativeModule().textArea.setBorderColor(node, this.value, this.value, this.value, this.value, false);
          }
          else {
            if ((Object.keys(this.value).indexOf('start') >= 0) ||
              (Object.keys(this.value).indexOf('end') >= 0)) {
              getUINativeModule().textArea.setBorderColor(node, this.value.top, this.value.end, this.value.bottom, this.value.start, true);
            } else {
              getUINativeModule().textArea.setBorderColor(node, this.value.top, this.value.right, this.value.bottom, this.value.left, false);
            }
          }
        }
      }
      checkObjectDiff(): boolean {
        if (!isResource(this.stageValue) && !isResource(this.value)) {
          if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
            return !(this.stageValue.start === this.value.start &&
              this.stageValue.end === this.value.end &&
              this.stageValue.top === this.value.top &&
              this.stageValue.bottom === this.value.bottom);
          }
          return !(this.stageValue.left === this.value.left &&
            this.stageValue.right === this.value.right &&
            this.stageValue.top === this.value.top &&
            this.stageValue.bottom === this.value.bottom);
        }
        else {
          return true;
        }
      }
    }
    (TextAreaBorderColorModifier as any).identity = Symbol('textAreaBorderColor');
    class TextAreaBorderStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetBorderStyle(node);
        } else {
          let type, style, top, right, bottom, left;
          if (isNumber(this.value)) {
            style = this.value;
            type = true;
          } else if (isObject(this.value)) {
            top = this.value?.top;
            right = this.value?.right;
            bottom = this.value?.bottom;
            left = this.value?.left;
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
        return !(this.value?.top === this.stageValue?.top &&
          this.value?.right === this.stageValue?.right &&
          this.value?.bottom === this.stageValue?.bottom &&
          this.value?.left === this.stageValue?.left);
      }
    }
    (TextAreaBorderStyleModifier as any).identity = Symbol('textAreaBorderStyle');
    class TextAreaBorderRadiusModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetBorderRadius(node);
        }
        else {
          if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
            getUINativeModule().textArea.setBorderRadius(node, this.value, this.value, this.value, this.value);
          }
          else {
            if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
              (Object.keys(this.value).indexOf('topEnd') >= 0) ||
              (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
              (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
              getUINativeModule().textArea.setBorderRadius(node, this.value.topStart, this.value.topEnd, this.value.bottomStart, this.value.bottomEnd);
            } else {
              getUINativeModule().textArea.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
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
            return !(this.stageValue.topStart === this.value.topStart &&
              this.stageValue.topEnd === this.value.topEnd &&
              this.stageValue.bottomStart === this.value.bottomStart &&
              this.stageValue.bottomEnd === this.value.bottomEnd);
          }
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
    (TextAreaBorderRadiusModifier as any).identity = Symbol('textAreaBorderRadius');
    class TextAreaBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextAreaBackgroundColorModifier as any).identity = Symbol('textAreaBackgroundColor');
    class TextAreaMarginModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetMargin(node);
        }
        else {
          getUINativeModule().textArea.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
          !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
          !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
          !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
      }
    }
    (TextAreaMarginModifier as any).identity = Symbol('textAreaMargin');
    class TextAreaOnWillChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnWillChange(node);
        } else {
          getUINativeModule().textArea.setOnWillChange(node, this.value);
        }
      }
    }
    (TextAreaOnWillChangeModifier as any).identity = Symbol('textAreaOnWillChange');
    class TextAreaOnWillInsertModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnWillInsert(node);
        } else {
          getUINativeModule().textArea.setOnWillInsert(node, this.value);
        }
      }
    }
    (TextAreaOnWillInsertModifier as any).identity = Symbol('textAreaOnWillInsert');
    class TextAreaOnDidInsertModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnDidInsert(node);
        } else {
          getUINativeModule().textArea.setOnDidInsert(node, this.value);
        }
      }
    }
    (TextAreaOnDidInsertModifier as any).identity = Symbol('textAreaOnDidInsert');
    class TextAreaOnWillDeleteModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnWillDelete(node);
        } else {
          getUINativeModule().textArea.setOnWillDelete(node, this.value);
        }
      }
    }
    (TextAreaOnWillDeleteModifier as any).identity = Symbol('textAreaOnWillDelete');
    class TextAreaOnDidDeleteModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnDidDelete(node);
        } else {
          getUINativeModule().textArea.setOnDidDelete(node, this.value);
        }
      }
    }
    (TextAreaOnDidDeleteModifier as any).identity = Symbol('textAreaOnDidDelete');
    class TextAreaEnablePreviewTextModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetEnablePreviewText(node);
        }
        else {
          getUINativeModule().textArea.setEnablePreviewText(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaEnablePreviewTextModifier as any).identity = Symbol('textAreaEnablePreviewText');
    class TextAreaEditMenuOptionsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetSelectionMenuOptions(node);
        } else {
          getUINativeModule().textArea.setSelectionMenuOptions(node, this.value);
        }
      }
    }
    (TextAreaEditMenuOptionsModifier as any).identity = Symbol('textAreaEditMenuOptions');
    class TextAreaInitializeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        var _a, _b, _c;
        if (reset) {
          getUINativeModule().textArea.setTextAreaInitialize(node, undefined, undefined, undefined);
        }
        else {
          getUINativeModule().textArea.setTextAreaInitialize(node,
            (_a = this.value) === null || _a === void 0 ? void 0 : _a.placeholder,
            (_b = this.value) === null || _b === void 0 ? void 0 : _b.text,
            (_c = this.value) === null || _c === void 0 ? void 0 : _c.controller);
        }
      }
      checkObjectDiff(): boolean {
        var _a, _b, _c, _d, _e, _f;
        return !isBaseOrResourceEqual((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.placeholder,
          (_b = this.value) === null || _b === void 0 ? void 0 : _b.placeholder) ||
          !isBaseOrResourceEqual((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.text,
            (_d = this.value) === null || _d === void 0 ? void 0 : _d.text) ||
          !isBaseOrResourceEqual((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.controller,
            (_f = this.value) === null || _f === void 0 ? void 0 : _f.controller);
      }
    }
    (TextAreaInitializeModifier as any).identity = Symbol('textAreaInitialize');

    class TextAreaWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetWidth(node);
        } else {
          getUINativeModule().textArea.setWidth(node, this.value);
        }
      }
    }
    (TextAreaWidthModifier as any).identity = Symbol('textAreaWidth');
    class TextAreaEnableHapticFeedbackModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetEnableHapticFeedback(node);
        }
        else {
          getUINativeModule().textArea.setEnableHapticFeedback(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaEnableHapticFeedbackModifier as any).identity = Symbol('textAreaEnableHapticFeedback');

    class TextAreaEllipsisModeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetEllipsisMode(node);
        }
        else {
          getUINativeModule().textArea.setEllipsisMode(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaEllipsisModeModifier as any).identity = Symbol('textEllipsisMode');

    class TextAreaStopBackPressModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetStopBackPress(node);
        }
        else {
          getUINativeModule().textArea.setStopBackPress(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaStopBackPressModifier as any).identity = Symbol('textAreaStopBackPress');

    class TextAreaKeyboardAppearanceModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetKeyboardAppearance(node);
        }
        else {
          getUINativeModule().textArea.setKeyboardAppearance(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaKeyboardAppearanceModifier as any).identity = Symbol('textAreaKeyboardAppearance');

    class TextAreaStrokeWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetStrokeWidth(node);
        }
        else if (!isObject(this.value)) {
          getUINativeModule().textArea.resetStrokeWidth(node);
        }
        else {
          getUINativeModule().textArea.setStrokeWidth(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaStrokeWidthModifier as any).identity = Symbol('textAreaStrokeWidth');

    class TextAreaStrokeColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetStrokeColor(node);
        }
        else {
          getUINativeModule().textArea.setStrokeColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaStrokeColorModifier as any).identity = Symbol('textAreaStrokeColor');

    class TextAreaEnableAutoSpacingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetEnableAutoSpacing(node);
        }
        else {
          getUINativeModule().textArea.setEnableAutoSpacing(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaEnableAutoSpacingModifier as any).identity = Symbol('textAreaEnableAutoSpacing');

    class TextAreaOrphanCharOptimizationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOrphanCharOptimization(node);
        } else {
          getUINativeModule().textArea.setOrphanCharOptimization(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaOrphanCharOptimizationModifier as any).identity = Symbol('textAreaOrphanCharOptimization');

    class TextAreaCompressLeadingPunctuationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetCompressLeadingPunctuation(node);
        }
        else {
          getUINativeModule().textArea.setCompressLeadingPunctuation(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaCompressLeadingPunctuationModifier as any).identity = Symbol('textAreaCompressLeadingPunctuation');

    class TextAreaPunctuationOverflowModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetPunctuationOverflow(node);
        }
        else {
          getUINativeModule().textArea.setPunctuationOverflow(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    TextAreaPunctuationOverflowModifier.identity = Symbol('textAreaPunctuationOverflow');

    class TextAreaIncludeFontPaddingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetIncludeFontPadding(node);
        }
        else {
          getUINativeModule().textArea.setIncludeFontPadding(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaIncludeFontPaddingModifier as any).identity = Symbol('textAreaIncludeFontPadding');

    class TextAreaFallbackLineSpacingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetFallbackLineSpacing(node);
        }
        else {
          getUINativeModule().textArea.setFallbackLineSpacing(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaFallbackLineSpacingModifier as any).identity = Symbol('textAreaFallbackLineSpacing');

    class TextAreaScrollBarColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetScrollBarColor(node);
        }
        else {
          getUINativeModule().textArea.setScrollBarColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaScrollBarColorModifier as any).identity = Symbol('textAreaBarColor');

    class TextAreaSelectDetectorEnableModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetSelectDetectorEnable(node);
        } else {
          getUINativeModule().textArea.setSelectDetectorEnable(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaSelectDetectorEnableModifier as any).identity = Symbol('textAreaSelectDetectorEnable');
    class TextAreaHorizontalScrollingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetHorizontalScrolling(node);
        } else {
          getUINativeModule().textArea.setHorizontalScrolling(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaHorizontalScrollingModifier as any).identity = Symbol('textAreaHorizontalScrolling');
    class TextAreaOnWillAttachIMEModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetOnWillAttachIME(node);
        } else {
          getUINativeModule().textArea.setOnWillAttachIME(node, this.value);
        }
      }
    }
    (TextAreaOnWillAttachIMEModifier as any).identity = Symbol('textAreaOnWillAttachIME');
    class TextAreaTextDirectionModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetTextDirection(node);
        }
        else {
          getUINativeModule().textArea.setTextDirection(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaTextDirectionModifier as any).identity = Symbol('textAreaTextDirection');

    class TextAreaSelectedDragPreviewStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetSelectedDragPreviewStyle(node);
        }
        else {
          getUINativeModule().textArea.setSelectedDragPreviewStyle(node, this.value.color);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value) ||
          !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
      }
    }
    (TextAreaSelectedDragPreviewStyleModifier as any).identity = Symbol('textAreaSelectedDragPreviewStyle');
    class TextAreaStrokeJoinStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetStrokeJoinStyle(node);
        }
        else {
          getUINativeModule().textArea.setStrokeJoinStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaStrokeJoinStyleModifier as any).identity = Symbol('textAreaStrokeJoinStyle');
    class TextAreaShaderStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textArea.resetShaderStyle(node, this.value);
        } else {
          if (this.value.options) {
            getUINativeModule().textArea.setShaderStyle(node, this.value.options.center, this.value.options.radius, this.value.options.angle,
              this.value.options.direction, this.value.options.repeating, this.value.options.colors, this.value.options.color);
          } else {
            getUINativeModule().textArea.setShaderStyle(node, this.value.center, this.value.radius, this.value.angle,
              this.value.direction, this.value.repeating, this.value.colors, this.value.color);
          }
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextAreaShaderStyleModifier as any).identity = Symbol('textAreaShaderStyle');

    loadComponent.componentObj = { 'component': ArkTextAreaComponent };
  }
  return loadComponent.componentObj;
}

class JSTextArea extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().textArea.create(params);
  }
  static placeholderColor(value: any): void {
    getUINativeModule().textArea.setPlaceholderColor(true, value);
  }
  static placeholderFont(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    getUINativeModule().textArea.setPlaceholderFont(true, value?.size, value?.weight, value?.family, value?.style);
  }
  static backgroundColor(value: any): void {
    getUINativeModule().textArea.setBackgroundColor(true, value);
  }
  static textAlign(value: any): void {
    getUINativeModule().textArea.setTextAlign(true, value);
  }
  static textDirection(value: any): void {
    getUINativeModule().textArea.setTextDirection(true, value);
  }
  static enableSelectedDataDetector(value: any): void {
    getUINativeModule().textArea.setSelectDetectorEnable(true, value);
  }
  static caretColor(value: any): void {
    getUINativeModule().textArea.setCaretColor(true, value);
  }
  static height(value: any): void {
    __Common__.height(value);
    getUINativeModule().textArea.setHeightJs(true, value);
  }
  static width(value: any): void {
    getUINativeModule().textArea.setWidthJs(true, value);
  }
  static padding(value: any): void {
    getUINativeModule().textArea.setPaddingJs(true, value);
  }

  static attributeModifier(modifier: any): void {
      attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
          return createComponent(nativePtr);
      }, (nativePtr: any, classType: any, modifierJS: any) => {
          return new modifierJS.TextAreaModifier(nativePtr, classType);
      });
  }

  static margin(value: any): void {
    __Common__.margin(value);
    getUINativeModule().textArea.setMargin(true);
  }
  static border(value: any): void {
    __Common__.border(value);
    if (value !== null && value !== undefined) {
      getUINativeModule().textArea.setBackBorder(true);
    }
  }
  static borderWidth(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    __Common__.borderWidth(value);
    getUINativeModule().textArea.setBackBorder(true);
  }
  static borderColor(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    __Common__.borderColor(value);
    getUINativeModule().textArea.setBackBorder(true);
  }
  static borderStyle(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    __Common__.borderStyle(value);
    getUINativeModule().textArea.setBackBorder(true);
  }
  static borderRadius(value: any): void {
    if (value === null || value === undefined) {
      getUINativeModule().textArea.resetBorderRadiusJS(true);
      return;
    }
    __Common__.borderRadius(value);
    getUINativeModule().textArea.setBackBorder(true);
  }
  static fontSize(value: any): void {
    getUINativeModule().textArea.setFontSize(true, value);
  }
  static fontColor(value: any): void {
    getUINativeModule().textArea.setFontColor(true, value);
  }
  static fontWeight(value: any): void {
    getUINativeModule().textArea.setFontWeight(true, value);
  }
  static fontStyle(value: any): void {
    getUINativeModule().textArea.setFontStyle(true, value);
  }
  static fontFamily(value: any): void {
    getUINativeModule().textArea.setFontFamily(true, value);
  }
  static minFontScale(value: any): void {
    getUINativeModule().textArea.setMinFontScale(true, value);
  }
  static maxFontScale(value: any): void {
    getUINativeModule().textArea.setMaxFontScale(true, value);
  }
  static inputFilter(value: any, error: any): void {
    getUINativeModule().textArea.setInputFilterJs(true, value, error);
  }
  static hoverEffect(value: any): void {
    getUINativeModule().textArea.setHoverEffect(true, value);
  }
  static maxLength(value: any): void {
    getUINativeModule().textArea.setMaxLength(true, value);
  }
  static showCounter(value: any, options: any): void {
    getUINativeModule().textArea.setShowCounter(true, value, options?.highlightBorder, options?.thresholdPercentage, options?.counterTextColor, options?.counterTextOverflowColor);
  }
  static barState(value: any): void {
    getUINativeModule().textArea.setBarState(true, value);
  }
  static maxLines(value: any, options: any): void {
    getUINativeModule().textArea.setMaxLinesJs(true, value, options);
  }
  static minLines(value: any): void {
    getUINativeModule().textArea.setMinLines(true, value);
  }
  static style(value: any): void {
    getUINativeModule().textArea.setStyle(true, value);
  }
  static onWillChange(callback: any): void {
    getUINativeModule().textArea.setOnWillChange(true, callback);
  }
  static onChange(callback: any): void {
    getUINativeModule().textArea.setOnChange(true, callback);
  }
  static onTextSelectionChange(callback: any): void {
    getUINativeModule().textArea.setOnTextSelectionChange(true, callback);
  }
  static onContentScroll(callback: any): void {
    getUINativeModule().textArea.setOnContentScroll(true, callback);
  }
  static onWillCopy(callback: any): void {
    getUINativeModule().textArea.setOnWillCopy(true, callback);
  }
  static onCopy(callback: any): void {
    getUINativeModule().textArea.setOnCopy(true, callback);
  }
  static onWillCut(callback: any): void {
    getUINativeModule().textArea.setOnWillCut(true, callback);
  }
  static onCut(callback: any): void {
    getUINativeModule().textArea.setOnCut(true, callback);
  }
  static onPaste(callback: any): void {
    getUINativeModule().textArea.setOnPaste(true, callback);
  }
  static onClick(callback: any): void {
    if (ViewStackProcessor.UsesNewPipeline()) {
      __Common__.onClick(callback);
    } else {
      getUINativeModule().textArea.setOnClick(true, callback);
    }
  }
  static onEditChange(callback: any): void {
    getUINativeModule().textArea.setOnEditChange(true, callback);
  }
  static copyOption(value: any): void {
    getUINativeModule().textArea.setCopyOption(true, value);
  }
  static foregroundColor(value: any): void {
    getUINativeModule().textArea.setForegroundColor(true, value);
  }
  static enableKeyboardOnFocus(value: any): void {
    getUINativeModule().textArea.setEnableKeyboardOnFocus(true, value);
  }
  static selectionMenuHidden(value: any): void {
    getUINativeModule().textArea.setSelectionMenuHidden(true, value);
  }
  static customKeyboard(value: any, options: any): void {
    getUINativeModule().textArea.setCustomKeyboardJs(true, value, options);
  }
  static onSubmit(callback: any): void {
    getUINativeModule().textArea.setOnSubmitJs(true, callback);
  }
  static enterKeyType(value: any): void {
    getUINativeModule().textArea.setEnterKeyType(true, value);
  }
  static type(value: any): void {
    getUINativeModule().textArea.setType(true, value);
  }
  static fontFeature(value: any): void {
    getUINativeModule().textArea.setFontFeature(true, value);
  }
  static lineBreakStrategy(value: any): void {
    getUINativeModule().textArea.setLineBreakStrategy(true, value);
  }
  static decoration(value: any): void {
    getUINativeModule().textArea.setDecoration(true, value?.type, value?.color, value?.style, value?.thicknessScale);
  }
  static minFontSize(value: any): void {
    getUINativeModule().textArea.setMinFontSize(true, value);
  }
  static maxFontSize(value: any): void {
    getUINativeModule().textArea.setMaxFontSize(true, value);
  }
  static heightAdaptivePolicy(value: any): void {
    getUINativeModule().textArea.setHeightAdaptivePolicy(true, value);
  }
  static letterSpacing(value: any): void {
    getUINativeModule().textArea.setLetterSpacing(true, value);
  }
  static lineHeight(value: any): void {
    getUINativeModule().textArea.setLineHeight(true, value);
  }
  static halfLeading(value: any): void {
    getUINativeModule().textArea.setHalfLeading(true, value);
  }
  static horizontalScrolling(value: any): void {
    getUINativeModule().textArea.setHorizontalScrolling(true, value);
  }
  static lineSpacing(value: any, options: any): void {
    let arkLineSpacing = new ArkLineSpacing();
    arkLineSpacing.value = value;
    arkLineSpacing.onlyBetweenLines = options?.onlyBetweenLines;
    getUINativeModule().textArea.setLineSpacing(true, arkLineSpacing.value, arkLineSpacing.onlyBetweenLines);
  }
  static wordBreak(value: any): void {
    getUINativeModule().textArea.setWordBreak(true, value);
  }
  static contentType(value: any): void {
    getUINativeModule().textArea.setContentType(true, value);
  }
  static enableAutoFill(value: any): void {
    getUINativeModule().textArea.setEnableAutoFill(true, value);
  }
  static selectedBackgroundColor(value: any): void {
    getUINativeModule().textArea.setSelectedBackgroundColor(true, value);
  }
  static caretStyle(value: any): void {
    getUINativeModule().textArea.setCaretStyleJs(true, value);
  }
  static textIndent(value: any): void {
    getUINativeModule().textArea.setTextIndent(true, value);
  }
  static textOverflow(value: any): void {
    getUINativeModule().textArea.setTextOverflow(true, value);
  }
  static onWillInsert(callback: any): void {
    getUINativeModule().textArea.setOnWillInsert(true, callback);
  }
  static onDidInsert(callback: any): void {
    getUINativeModule().textArea.setOnDidInsert(true, callback);
  }
  static onWillDelete(callback: any): void {
    getUINativeModule().textArea.setOnWillDelete(true, callback);
  }
  static onDidDelete(callback: any): void {
    getUINativeModule().textArea.setOnDidDelete(true, callback);
  }
  static editMenuOptions(value: any): void {
    getUINativeModule().textArea.setSelectionMenuOptions(true, value);
  }
  static enablePreviewText(value: any): void {
    getUINativeModule().textArea.setEnablePreviewText(true, value);
  }
  static enableHapticFeedback(value: any): void {
    getUINativeModule().textArea.setEnableHapticFeedback(true, value);
  }
  static autoCapitalizationMode(value: any): void {
    getUINativeModule().textArea.setAutoCapitalizationMode(true, value);
  }
  static ellipsisMode(value: any): void {
    getUINativeModule().textArea.setEllipsisMode(true, value);
  }
  static stopBackPress(value: any): void {
    getUINativeModule().textArea.setStopBackPress(true, value);
  }
  static keyboardAppearance(value: any): void {
    getUINativeModule().textArea.setKeyboardAppearance(true, value);
  }
  static strokeWidth(value: any): void {
    getUINativeModule().textArea.setStrokeWidth(true, value);
  }
  static strokeColor(value: any): void {
    getUINativeModule().textArea.setStrokeColor(true, value);
  }
  static strokeJoinStyle(value: any): void {
    getUINativeModule().textArea.setStrokeJoinStyle(true, value);
  }
  static shaderStyle(value: any): void {
    getUINativeModule().textArea.setShaderStyle(true, value);
  }
  static enableAutoSpacing(value: any): void {
    getUINativeModule().textArea.setEnableAutoSpacing(true, value);
  }
  static scrollBarColor(value: any): void {
    getUINativeModule().textArea.setScrollBarColor(true, value);
  }
  static onWillAttachIME(callback: any): void {
    getUINativeModule().textArea.setOnWillAttachIME(true, callback);
  }
  static orphanCharOptimization(value: any): void {
    getUINativeModule().textArea.setOrphanCharOptimization(true, value);
  }
  static compressLeadingPunctuation(value: any): void {
    getUINativeModule().textArea.setCompressLeadingPunctuation(true, value);
  }
  static punctuationOverflow(value: any): void {
    getUINativeModule().textArea.setPunctuationOverflow(true, value);
  }
  static includeFontPadding(value: any): void {
    getUINativeModule().textArea.setIncludeFontPadding(true, value);
  }
  static fallbackLineSpacing(value: any): void {
    getUINativeModule().textArea.setFallbackLineSpacing(true, value);
  }
  static selectedDragPreviewStyle(value: any): void {
    getUINativeModule().textArea.setSelectedDragPreviewStyle(true, value?.color);
  }
  static voiceButton(value: any): void {
    getUINativeModule().textArea.setVoiceButton(true, value);
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
}

function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkTextAreaComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.TextArea = JSTextArea;
}

export default { loadComponent, createComponent, exportComponent, exportView };
