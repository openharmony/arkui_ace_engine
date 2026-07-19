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
    class ArkTextInputComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      initialize(value: any): this {
        if (value[0] !== undefined) {
          this.setPlaceholder(value[0].placeholder);
          this.setText(value[0].text);
          this.setController(value[0].controller);
        }
        return this;
      }
      enableSelectedDataDetector(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputSelectDetectorEnableModifier.identity, TextInputSelectDetectorEnableModifier, value);
        return this;
      }
      setText(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputTextModifier.identity,
          TextInputTextModifier, value);
        return this;
      }
      setPlaceholder(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderModifier.identity,
          TextInputPlaceholderModifier, value);
        return this;
      }
      setController(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputControllerModifier.identity,
          TextInputControllerModifier, value);
        return this;
      }

      cancelButton(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputCancelButtonModifier.identity, TextInputCancelButtonModifier, value);
        return this;
      }
      selectAll(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputSelectAllModifier.identity, TextInputSelectAllModifier, value);
        return this;
      }
      enableAutoFill(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEnableAutoFillModifier.identity, TextInputEnableAutoFillModifier, value);
        return this;
      }
      enableAutoFillAnimation(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEnableAutoFillAnimationModifier.identity, TextInputEnableAutoFillAnimationModifier, value);
        return this;
      }
      passwordRules(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputPasswordRulesModifier.identity, TextInputPasswordRulesModifier, value);
        return this;
      }
      showCounter(value: any, options: any): this {
        let arkValue = new ArkTextFieldShowCounter();
        arkValue.value = value;
        arkValue.highlightBorder = options?.highlightBorder;
        arkValue.thresholdPercentage = options?.thresholdPercentage;
        arkValue.counterTextColor = options?.counterTextColor;
        arkValue.counterTextOverflowColor = options?.counterTextOverflowColor;
        modifierWithKey(this._modifiersWithKeys, TextInputShowCounterModifier.identity, TextInputShowCounterModifier, arkValue);
        return this;
      }
      type(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputTypeModifier.identity, TextInputTypeModifier, value);
        return this;
      }
      placeholderColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderColorModifier.identity, TextInputPlaceholderColorModifier, value);
        return this;
      }
      placeholderFont(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderFontModifier.identity, TextInputPlaceholderFontModifier, value);
        return this;
      }
      enterKeyType(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEnterKeyTypeModifier.identity, TextInputEnterKeyTypeModifier, value);
        return this;
      }
      caretColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputCaretColorModifier.identity, TextInputCaretColorModifier, value);
        return this;
      }
      onEditChanged(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnEditChangeModifier.identity, TextInputOnEditChangeModifier, callback);
        return this;
      }
      onEditChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnEditChangeModifier.identity, TextInputOnEditChangeModifier, callback);
        return this;
      }
      onSubmit(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnSubmitModifier.identity, TextInputOnSubmitModifier, callback);
        return this;
      }
      onChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnChangeModifier.identity, TextInputOnChangeModifier, callback);
        return this;
      }
      onTextSelectionChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnTextSelectionChangeModifier.identity, TextInputOnTextSelectionChangeModifier, callback);
        return this;
      }
      onContentScroll(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnContentScrollModifier.identity, TextInputOnContentScrollModifier, callback);
        return this;
      }
      maxLength(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputMaxLengthModifier.identity, TextInputMaxLengthModifier, value);
        return this;
      }
      fontColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputFontColorModifier.identity, TextInputFontColorModifier, value);
        return this;
      }
      fontSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputFontSizeModifier.identity, TextInputFontSizeModifier, value);
        return this;
      }
      fontStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputFontStyleModifier.identity, TextInputFontStyleModifier, value);
        return this;
      }
      fontWeight(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputFontWeightModifier.identity, TextInputFontWeightModifier, value);
        return this;
      }
      fontFamily(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputFontFamilyModifier.identity, TextInputFontFamilyModifier, value);
        return this;
      }
      inputFilter(value: any, error: any): this {
        let arkValue = new ArkTextInputFilter();
        arkValue.value = value;
        arkValue.error = error;
        modifierWithKey(this._modifiersWithKeys, TextInputFilterModifier.identity, TextInputFilterModifier, arkValue);
        return this;
      }
      onWillCopy(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnWillCopyModifier.identity, TextInputOnWillCopyModifier, callback);
        return this;
      }
      onCopy(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnCopyModifier.identity, TextInputOnCopyModifier, callback);
        return this;
      }
      onWillCut(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnWillCutModifier.identity, TextInputOnWillCutModifier, callback);
        return this;
      }
      onCut(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnCutModifier.identity, TextInputOnCutModifier, callback);
        return this;
      }
      onPaste(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnPasteModifier.identity, TextInputOnPasteModifier, callback);
        return this;
      }
      copyOption(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputCopyOptionModifier.identity, TextInputCopyOptionModifier, value);
        return this;
      }
      showPasswordIcon(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputShowPasswordIconModifier.identity, TextInputShowPasswordIconModifier, value);
        return this;
      }
      showPassword(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputShowPasswordModifier.identity, TextInputShowPasswordModifier, value);
        return this;
      }
      textAlign(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputTextAlignModifier.identity, TextInputTextAlignModifier, value);
        return this;
      }
      style(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputStyleModifier.identity, TextInputStyleModifier, value);
        return this;
      }
      caretStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputCaretStyleModifier.identity, TextInputCaretStyleModifier, value);
        return this;
      }
      selectedBackgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputSelectedBackgroundColorModifier.identity, TextInputSelectedBackgroundColorModifier, value);
        return this;
      }
      caretPosition(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputCaretPositionModifier.identity, TextInputCaretPositionModifier, value);
        return this;
      }
      enableKeyboardOnFocus(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEnableKeyboardOnFocusModifier.identity, TextInputEnableKeyboardOnFocusModifier, value);
        return this;
      }
      passwordIcon(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputPasswordIconModifier.identity, TextInputPasswordIconModifier, value);
        return this;
      }
      showError(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputShowErrorModifier.identity, TextInputShowErrorModifier, value);
        return this;
      }
      showUnit(event: any): void {
        throw new BusinessError(100201, 'showUnit function not supported in attributeModifier scenario.');
      }
      showUnderline(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputShowUnderlineModifier.identity, TextInputShowUnderlineModifier, value);
        return this;
      }
      fontFeature(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputFontFeatureModifier.identity, TextInputFontFeatureModifier, value);
        return this;
      }
      selectionMenuHidden(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputSelectionMenuHiddenModifier.identity, TextInputSelectionMenuHiddenModifier, value);
        return this;
      }
      barState(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputBarStateModifier.identity, TextInputBarStateModifier, value);
        return this;
      }
      maxLines(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputMaxLinesModifier.identity, TextInputMaxLinesModifier, value);
        return this;
      }
      customKeyboard(value: any, options: any): this {
        let arkValue = new ArkCustomKeyboard();
        arkValue.value = value;
        arkValue.supportAvoidance = options?.supportAvoidance;
        modifierWithKey(this._modifiersWithKeys, TextInputCustomKeyboardModifier.identity,
          TextInputCustomKeyboardModifier, arkValue);
        return this;
      }
      decoration(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputDecorationModifier.identity, TextInputDecorationModifier, value);
        return this;
      }
      letterSpacing(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputLetterSpacingModifier.identity, TextInputLetterSpacingModifier, value);
        return this;
      }
      lineHeight(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputLineHeightModifier.identity, TextInputLineHeightModifier, value);
        return this;
      }
      halfLeading(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputHalfLeadingModifier.identity, TextInputHalfLeadingModifier, value);
        return this;
      }
      underlineColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputUnderlineColorModifier.identity, TextInputUnderlineColorModifier, value);
        return this;
      }
      wordBreak(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputWordBreakModifier.identity, TextInputWordBreakModifier, value);
        return this;
      }
      lineBreakStrategy(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputLineBreakStrategyModifier.identity,
          TextInputLineBreakStrategyModifier, value);
        return this;
      }
      minFontSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputMinFontSizeModifier.identity, TextInputMinFontSizeModifier, value);
        return this;
      }
      maxFontSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputMaxFontSizeModifier.identity, TextInputMaxFontSizeModifier, value);
        return this;
      }
      minFontScale(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputMinFontScaleModifier.identity, TextInputMinFontScaleModifier, value);
        return this;
      }
      maxFontScale(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputMaxFontScaleModifier.identity, TextInputMaxFontScaleModifier, value);
        return this;
      }
      heightAdaptivePolicy(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputHeightAdaptivePolicyModifier.identity, TextInputHeightAdaptivePolicyModifier, value);
        return this;
      }
      textOverflow(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputTextOverflowModifier.identity, TextInputTextOverflowModifier, value);
        return this;
      }
      textIndent(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputTextIndentModifier.identity, TextInputTextIndentModifier, value);
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
          modifierWithKey(this._modifiersWithKeys, TextInputPaddingModifier.identity, TextInputPaddingModifier, arkValue);
        }
        else {
          modifierWithKey(this._modifiersWithKeys, TextInputPaddingModifier.identity, TextInputPaddingModifier, undefined);
        }
        return this;
      }
      contentType(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputContentTypeModifier.identity, TextInputContentTypeModifier, value);
        return this;
      }
      border(value: any): this {
        let arkBorder = valueToArkBorder(value);
        modifierWithKey(this._modifiersWithKeys, TextInputBorderModifier.identity, TextInputBorderModifier, arkBorder);
        return this;
      }
      borderWidth(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputBorderWidthModifier.identity, TextInputBorderWidthModifier, value);
        return this;
      }
      borderColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputBorderColorModifier.identity, TextInputBorderColorModifier, value);
        return this;
      }
      borderStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputBorderStyleModifier.identity, TextInputBorderStyleModifier, value);
        return this;
      }
      borderRadius(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputBorderRadiusModifier.identity, TextInputBorderRadiusModifier, value);
        return this;
      }
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputBackgroundColorModifier.identity, TextInputBackgroundColorModifier, value);
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
          modifierWithKey(this._modifiersWithKeys, TextInputMarginModifier.identity, TextInputMarginModifier, arkValue);
        }
        else {
          modifierWithKey(this._modifiersWithKeys, TextInputMarginModifier.identity, TextInputMarginModifier, undefined);
        }
        return this;
      }
      onWillChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnWillChangeModifier.identity, TextInputOnWillChangeModifier, callback);
        return this;
      }
      onWillInsert(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnWillInsertModifier.identity, TextInputOnWillInsertModifier, callback);
        return this;
      }
      onDidInsert(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnDidInsertModifier.identity, TextInputOnDidInsertModifier, callback);
        return this;
      }
      onWillDelete(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnWillDeleteModifier.identity, TextInputOnWillDeleteModifier, callback);
        return this;
      }
      onDidDelete(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnDidDeleteModifier.identity, TextInputOnDidDeleteModifier, callback);
        return this;
      }
      enablePreviewText(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEnablePreviewTextModifier.identity, TextInputEnablePreviewTextModifier, value);
        return this;
      }
      autoCapitalizationMode(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputAutoCapitalizationModifier.identity, TextInputAutoCapitalizationModifier, value);
        return this;
      }
      editMenuOptions(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEditMenuOptionsModifier.identity,
          TextInputEditMenuOptionsModifier, value);
        return this;
      }
      width(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputWidthModifier.identity, TextInputWidthModifier, value);
        return this;
      }
      enableHapticFeedback(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEnableHapticFeedbackModifier.identity, TextInputEnableHapticFeedbackModifier, value);
        return this;
      }
      ellipsisMode(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEllipsisModeModifier.identity, TextInputEllipsisModeModifier, value);
        return this;
      }
      stopBackPress(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputStopBackPressModifier.identity, TextInputStopBackPressModifier, value);
        return this;
      }
      keyboardAppearance(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputKeyboardAppearanceModifier.identity, TextInputKeyboardAppearanceModifier, value);
        return this;
      }
      strokeWidth(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputStrokeWidthModifier.identity, TextInputStrokeWidthModifier, value);
        return this;
      }
      strokeColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputStrokeColorModifier.identity, TextInputStrokeColorModifier, value);
        return this;
      }
      enableAutoSpacing(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputEnableAutoSpacingModifier.identity, TextInputEnableAutoSpacingModifier, value);
        return this;
      }
      orphanCharOptimization(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOrphanCharOptimizationModifier.identity,
          TextInputOrphanCharOptimizationModifier, value);
        return this;
      }
      compressLeadingPunctuation(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputCompressLeadingPunctuationModifier.identity, TextInputCompressLeadingPunctuationModifier, value);
        return this;
      }
      punctuationOverflow(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputPunctuationOverflowModifier.identity, TextInputPunctuationOverflowModifier, value);
        return this;
      }
      includeFontPadding(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputIncludeFontPaddingModifier.identity, TextInputIncludeFontPaddingModifier, value);
        return this;
      }
      fallbackLineSpacing(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputFallbackLineSpacingModifier.identity, TextInputFallbackLineSpacingModifier, value);
        return this;
      }
      onSecurityStateChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnSecurityStateChangeModifier.identity,
          TextInputOnSecurityStateChangeModifier, callback);
        return this;
      }
      onWillAttachIME(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputOnWillAttachIMEModifier.identity,
          TextInputOnWillAttachIMEModifier, callback);
        return this;
      }
      textDirection(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputTextDirectionModifier.identity, TextInputTextDirectionModifier, value);
        return this;
      }
      selectedDragPreviewStyle(value: any): this {
        let arkSelectedDragPreviewStyle = new ArkSelectedDragPreviewStyle();
        arkSelectedDragPreviewStyle.color = value?.color;
        modifierWithKey(this._modifiersWithKeys, TextInputSelectedDragPreviewStyleModifier.identity,
          TextInputSelectedDragPreviewStyleModifier, arkSelectedDragPreviewStyle);
        return this;
      }
      strokeJoinStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputStrokeJoinStyleModifier.identity,
          TextInputStrokeJoinStyleModifier, value);
        return this;
      }
      shaderStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextInputShaderStyleModifier.identity, TextInputShaderStyleModifier, value);
        return this;
      }
    }

    class TextInputStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetStyle(node);
        }
        else {
          getUINativeModule().textInput.setStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputStyleModifier as any).identity = Symbol('textInputStyle');
    class TextInputMaxLengthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetMaxLength(node);
        }
        else {
          getUINativeModule().textInput.setMaxLength(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputMaxLengthModifier as any).identity = Symbol('textInputMaxLength');
    class TextInputMaxLinesModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetMaxLines(node);
        }
        else {
          getUINativeModule().textInput.setMaxLines(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputMaxLinesModifier as any).identity = Symbol('textInputMaxLines');
    class TextInputDecorationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetDecoration(node);
        }
        else {
          getUINativeModule().textInput.setDecoration(node, this.value.type, this.value.color,
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
    (TextInputDecorationModifier as any).identity = Symbol('textInputDecoration');
    class TextInputLetterSpacingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetLetterSpacing(node);
        }
        else {
          getUINativeModule().textInput.setLetterSpacing(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputLetterSpacingModifier as any).identity = Symbol('textInputLetterSpacing');
    class TextInputLineHeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetLineHeight(node);
        }
        else {
          getUINativeModule().textInput.setLineHeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputLineHeightModifier as any).identity = Symbol('textInputLineHeight');
    class TextInputHalfLeadingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetHalfLeading(node);
        }
        else {
          getUINativeModule().textInput.setHalfLeading(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputHalfLeadingModifier as any).identity = Symbol('textInputHalfLeading');
    class TextInputUnderlineColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetUnderlineColor(node);
        }
        else {
          const valueType = typeof this.value;
          if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
            getUINativeModule().textInput.setUnderlineColor(node, this.value, undefined, undefined, undefined, undefined);
          }
          else {
            getUINativeModule().textInput.setUnderlineColor(node, undefined, this.value.normal, this.value.typing, this.value.error, this.value.disable);
          }
        }
      }
      checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
          return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
        else if (!isResource(this.stageValue) && !isResource(this.value)) {
          return !(this.stageValue.normal === this.value.normal &&
            this.stageValue.typing === this.value.typing &&
            this.stageValue.error === this.value.error &&
            this.stageValue.disable === this.value.disable);
        }
        else {
          return true;
        }
      }
    }
    (TextInputUnderlineColorModifier as any).identity = Symbol('textInputUnderlineColor');
    class TextInputWordBreakModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetWordBreak(node);
        }
        else {
          getUINativeModule().textInput.setWordBreak(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputWordBreakModifier as any).identity = Symbol('textInputWordBreak');

    class TextInputLineBreakStrategyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetLineBreakStrategy(node);
        }
        else {
          getUINativeModule().textInput.setLineBreakStrategy(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputLineBreakStrategyModifier as any).identity = Symbol('textInputLineBreakStrategy');

    class TextInputMinFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetMinFontSize(node);
        }
        else {
          getUINativeModule().textInput.setMinFontSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputMinFontSizeModifier as any).identity = Symbol('textInputMinFontSize');
    class TextInputMaxFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetMaxFontSize(node);
        }
        else {
          getUINativeModule().textInput.setMaxFontSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputMaxFontSizeModifier as any).identity = Symbol('textInputMaxFontSize');

    class TextInputMinFontScaleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetMinFontScale(node);
        }
        else {
          getUINativeModule().textInput.setMinFontScale(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputMinFontScaleModifier as any).identity = Symbol('textInputMinFontScale');
    class TextInputMaxFontScaleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetMaxFontScale(node);
        }
        else {
          getUINativeModule().textInput.setMaxFontScale(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputMaxFontScaleModifier as any).identity = Symbol('textInputMaxFontScale');

    class TextInputHeightAdaptivePolicyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetHeightAdaptivePolicy(node);
        }
        else {
          getUINativeModule().textInput.setHeightAdaptivePolicy(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputHeightAdaptivePolicyModifier as any).identity = Symbol('textInputHeightAdaptivePolicy');
    class TextInputTextOverflowModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetTextOverflow(node);
        } else {
          getUINativeModule().textInput.setTextOverflow(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (TextInputTextOverflowModifier as any).identity = Symbol('textInputTextOverflow');
    class TextInputTextIndentModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetTextIndent(node);
        } else {
          getUINativeModule().textInput.setTextIndent(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputTextIndentModifier as any).identity = Symbol('textInputTextIndent');
    class TextInputShowPasswordIconModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetShowPasswordIcon(node);
        }
        else {
          getUINativeModule().textInput.setShowPasswordIcon(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputShowPasswordIconModifier as any).identity = Symbol('textInputShowPasswordIcon');
    class TextInputShowPasswordModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetShowPassword(node);
        }
        else {
          getUINativeModule().textInput.setShowPassword(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputShowPasswordModifier as any).identity = Symbol('textInputShowPassword');
    class TextInputTextAlignModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetTextAlign(node);
        }
        else {
          getUINativeModule().textInput.setTextAlign(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputTextAlignModifier as any).identity = Symbol('textInputTextAlign');
    class TextInputPlaceholderFontModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetPlaceholderFont(node);
        }
        else {
          getUINativeModule().textInput.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
      }
      checkObjectDiff(): boolean {
        if (!(this.stageValue.weight === this.value.weight &&
          this.stageValue.style === this.value.style)) {
          return true;
        }
        else {
          if ((!isResource(this.stageValue.size) && !isResource(this.value.size) &&
            this.stageValue.size === this.value.size) &&
            (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
              this.stageValue.family === this.value.family)) {
            return false;
          }
          else {
            return true;
          }
        }
      }
    }
    (TextInputPlaceholderFontModifier as any).identity = Symbol('textInputPlaceholderFont');
    class TextInputPlaceholderColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetPlaceholderColor(node);
        }
        else {
          getUINativeModule().textInput.setPlaceholderColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputPlaceholderColorModifier as any).identity = Symbol('textInputPlaceholderColor');
    class TextInputPasswordIconModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetPasswordIcon(node);
        }
        else {
          getUINativeModule().textInput.setPasswordIcon(node, this.value.onIconSrc, this.value.offIconSrc);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.onIconSrc, this.value.onIconSrc) ||
          !isBaseOrResourceEqual(this.stageValue.offIconSrc, this.value.offIconSrc);
      }
    }
    (TextInputPasswordIconModifier as any).identity = Symbol('textInputPasswordIcon');
    class TextInputSelectedBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetSelectedBackgroundColor(node);
        }
        else {
          getUINativeModule().textInput.setSelectedBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputSelectedBackgroundColorModifier as any).identity = Symbol('textInputSelectedBackgroundColor');
    class TextInputSelectionMenuHiddenModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetSelectionMenuHidden(node);
        }
        else {
          getUINativeModule().textInput.setSelectionMenuHidden(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputSelectionMenuHiddenModifier as any).identity = Symbol('textInputSelectionMenuHidden');
    class TextInputShowUnderlineModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetShowUnderline(node);
        }
        else {
          getUINativeModule().textInput.setShowUnderline(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputShowUnderlineModifier as any).identity = Symbol('textInputShowUnderLine');
    class TextInputPasswordRulesModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetPasswordRules(node);
        } else {
          getUINativeModule().textInput.setPasswordRules(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputPasswordRulesModifier as any).identity = Symbol('textInputPasswordRules');
    class TextInputEnableAutoFillModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetEnableAutoFill(node);
        } else {
          getUINativeModule().textInput.setEnableAutoFill(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputEnableAutoFillModifier as any).identity = Symbol('textInputEnableAutoFill');
    class TextInputEnableAutoFillAnimationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetEnableAutoFillAnimation(node);
        } else {
          getUINativeModule().textInput.setEnableAutoFillAnimation(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputEnableAutoFillAnimationModifier as any).identity = Symbol('textInputEnableAutoFillAnimation');
    class TextInputFontFeatureModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetFontFeature(node);
        } else {
          getUINativeModule().textInput.setFontFeature(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputFontFeatureModifier as any).identity = Symbol('textInputFontFeature');
    class TextInputShowErrorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetShowError(node);
        }
        else {
          getUINativeModule().textInput.setShowError(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputShowErrorModifier as any).identity = Symbol('textInputShowError');
    class TextInputTypeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetType(node);
        }
        else {
          getUINativeModule().textInput.setType(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputTypeModifier as any).identity = Symbol('textInputType');
    class TextInputCustomKeyboardModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetCustomKeyboard(node);
        } else {
          getUINativeModule().textInput.setCustomKeyboard(node, this.value.value, this.value.supportAvoidance);
        }
      }
    }
    (TextInputCustomKeyboardModifier as any).identity = Symbol('TextInputCustomKeyboard');
    class TextInputCaretPositionModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetCaretPosition(node);
        }
        else {
          getUINativeModule().textInput.setCaretPosition(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputCaretPositionModifier as any).identity = Symbol('textInputCaretPosition');
    class TextInputCopyOptionModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetCopyOption(node);
        }
        else {
          getUINativeModule().textInput.setCopyOption(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputCopyOptionModifier as any).identity = Symbol('textInputCopyOption');
    class TextInputEnableKeyboardOnFocusModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetEnableKeyboardOnFocus(node);
        }
        else {
          getUINativeModule().textInput.setEnableKeyboardOnFocus(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputEnableKeyboardOnFocusModifier as any).identity = Symbol('textInputEnableKeyboardOnFocus');
    class TextInputCaretStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetCaretStyle(node);
        }
        else {
          getUINativeModule().textInput.setCaretStyle(node, this.value.width, this.value.color);
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
    (TextInputCaretStyleModifier as any).identity = Symbol('textInputCaretStyle');
    class TextInputEnterKeyTypeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetEnterKeyType(node);
        }
        else {
          getUINativeModule().textInput.setEnterKeyType(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputEnterKeyTypeModifier as any).identity = Symbol('textInputEnterKeyType');
    class TextInputAutoCapitalizationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetAutoCapitalizationMode(node);
        }
        else {
          getUINativeModule().textInput.setAutoCapitalizationMode(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputAutoCapitalizationModifier as any).identity = Symbol('textInputAutoCapitalization');
    class TextInputBarStateModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetBarState(node);
        }
        else {
          getUINativeModule().textInput.setBarState(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputBarStateModifier as any).identity = Symbol('textInputBarState');
    class TextInputCaretColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetCaretColor(node);
        }
        else {
          getUINativeModule().textInput.setCaretColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputCaretColorModifier as any).identity = Symbol('textinputCaretColor');
    class TextInputFontColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetFontColor(node);
        }
        else {
          getUINativeModule().textInput.setFontColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputFontColorModifier as any).identity = Symbol('textInputFontColor');
    class TextInputFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetFontSize(node);
        }
        else {
          getUINativeModule().textInput.setFontSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputFontSizeModifier as any).identity = Symbol('textInputFontSize');
    class TextInputFontStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetFontStyle(node);
        }
        else {
          getUINativeModule().textInput.setFontStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputFontStyleModifier as any).identity = Symbol('textInputFontStyle');
    class TextInputFontWeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetFontWeight(node);
        }
        else {
          getUINativeModule().textInput.setFontWeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputFontWeightModifier as any).identity = Symbol('textInputFontWeight');
    class TextInputFontFamilyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetFontFamily(node);
        }
        else {
          getUINativeModule().textInput.setFontFamily(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputFontFamilyModifier as any).identity = Symbol('textInputFontFamily');
    class TextInputCancelButtonModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetCancelButton(node);
        }
        else {
          getUINativeModule().textInput.setCancelButton(node, this.value.style,
            this.value.icon);
        }
      }
      checkObjectDiff(): boolean {
        let _a, _b, _c, _d, _e, _f;
        return this.stageValue.style !== this.value.style ||
          !isBaseOrResourceEqual((_a = this.stageValue.icon) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.icon) === null || _b === void 0 ? void 0 : _b.size) ||
          !isBaseOrResourceEqual((_c = this.stageValue.icon) === null || _c === void 0 ? void 0 : _c.color, (_d = this.value.icon) === null || _d === void 0 ? void 0 : _d.color) ||
          !isBaseOrResourceEqual((_e = this.stageValue.icon) === null || _e === void 0 ? void 0 : _e.src, (_f = this.value.icon) === null || _f === void 0 ? void 0 : _f.src);
      }
    }
    (TextInputCancelButtonModifier as any).identity = Symbol('textInputCancelButton');
    class TextInputSelectAllModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextInputSelectAllModifier as any).identity = Symbol('textInputSelectAll');
    class TextInputShowCounterModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetShowCounter(node);
        }
        else {
          getUINativeModule().textInput.setShowCounter(node, this.value.value, this.value.highlightBorder, this.value.thresholdPercentage, this.value.counterTextColor, this.value.counterTextOverflowColor);
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
    (TextInputShowCounterModifier as any).identity = Symbol('textInputShowCounter');
    class TextInputOnEditChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnEditChange(node);
        } else {
          getUINativeModule().textInput.setOnEditChange(node, this.value);
        }
      }
    }
    (TextInputOnEditChangeModifier as any).identity = Symbol('textInputOnEditChange');
    class TextInputFilterModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextInputFilterModifier as any).identity = Symbol('textInputFilter');
    class TextInputOnSubmitModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnSubmit(node);
        } else {
          getUINativeModule().textInput.setOnSubmit(node, this.value);
        }
      }
    }
    (TextInputOnSubmitModifier as any).identity = Symbol('textInputOnSubmit');
    class TextInputOnChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnChange(node);
        } else {
          getUINativeModule().textInput.setOnChange(node, this.value);
        }
      }
    }
    (TextInputOnChangeModifier as any).identity = Symbol('textInputOnChange');
    class TextInputOnTextSelectionChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnTextSelectionChange(node);
        } else {
          getUINativeModule().textInput.setOnTextSelectionChange(node, this.value);
        }
      }
    }
    (TextInputOnTextSelectionChangeModifier as any).identity = Symbol('textInputOnTextSelectionChange');
    class TextInputOnContentScrollModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnContentScroll(node);
        } else {
          getUINativeModule().textInput.setOnContentScroll(node, this.value);
        }
      }
    }
    (TextInputOnContentScrollModifier as any).identity = Symbol('textInputOnContentScroll');
    class TextInputOnWillCopyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnWillCopy(node);
        } else {
          getUINativeModule().textInput.setOnWillCopy(node, this.value);
        }
      }
    }
    (TextInputOnWillCopyModifier as any).identity = Symbol('textInputOnWillCopy');
    class TextInputOnCopyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnCopy(node);
        } else {
          getUINativeModule().textInput.setOnCopy(node, this.value);
        }
      }
    }
    (TextInputOnCopyModifier as any).identity = Symbol('textInputOnCopy');
    class TextInputOnWillCutModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnWillCut(node);
        } else {
          getUINativeModule().textInput.setOnWillCut(node, this.value);
        }
      }
    }
    (TextInputOnWillCutModifier as any).identity = Symbol('textInputOnWillCut');
    class TextInputOnCutModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnCut(node);
        } else {
          getUINativeModule().textInput.setOnCut(node, this.value);
        }
      }
    }
    (TextInputOnCutModifier as any).identity = Symbol('textInputOnCut');
    class TextInputOnPasteModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnPaste(node);
        } else {
          getUINativeModule().textInput.setOnPaste(node, this.value);
        }
      }
    }
    (TextInputOnPasteModifier as any).identity = Symbol('textInputOnPaste');
    class TextInputPaddingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (TextInputPaddingModifier as any).identity = Symbol('textInputPadding');

    class TextInputTextModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }

      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetText(node);
        } else {
          getUINativeModule().textInput.setText(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputTextModifier as any).identity = Symbol('textInputText');

    class TextInputPlaceholderModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetPlaceholder(node);
        } else {
          getUINativeModule().textInput.setPlaceholder(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputPlaceholderModifier as any).identity = Symbol('textInputPlaceholder');

    class TextInputControllerModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }

      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetController(node);
        } else {
          getUINativeModule().textInput.setController(node, this.value);
        }
      }

    }
    (TextInputControllerModifier as any).identity = Symbol('textInputController');


    class TextInputContentTypeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetContentType(node);
        }
        else {
          getUINativeModule().textInput.setContentType(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputContentTypeModifier as any).identity = Symbol('textInputContentType');
    class TextInputBorderModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
        let emptyColor = new ArkBorderColor();
        let hasBorderColor = !this.stageValue.arkColor.isEqual(emptyColor) || !this.value.arkColor.isEqual(emptyColor);
        return hasBorderColor || this.value.checkObjectDiff(this.stageValue);
      }
    }
    (TextInputBorderModifier as any).identity = Symbol('textInputBorder');
    class TextInputBorderWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetBorderWidth(node);
        }
        else {
          if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
            getUINativeModule().textInput.setBorderWidth(node, this.value, this.value, this.value, this.value);
          }
          else {
            if ((Object.keys(this.value).indexOf('start') >= 0) ||
              (Object.keys(this.value).indexOf('end') >= 0)) {
              getUINativeModule().textInput.setBorderWidth(node, this.value.top, this.value.end, this.value.bottom, this.value.start);
            } else {
              getUINativeModule().textInput.setBorderWidth(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
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
    (TextInputBorderWidthModifier as any).identity = Symbol('textInputBorderWidth');
    class TextInputBorderColorModifier extends ModifierWithKey<any> {
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
          getUINativeModule().textInput.resetBorderColor(node);
        }
        else {
          const valueType = typeof this.value;
          if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
            getUINativeModule().textInput.setBorderColor(node, this.value, this.value, this.value, this.value, false);
          }
          else {
            if ((Object.keys(this.value).indexOf('start') >= 0) ||
              (Object.keys(this.value).indexOf('end') >= 0)) {
              getUINativeModule().textInput.setBorderColor(node, this.value.top, this.value.end, this.value.bottom, this.value.start, true);
            } else {
              getUINativeModule().textInput.setBorderColor(node, this.value.top, this.value.right, this.value.bottom, this.value.left, false);
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
    (TextInputBorderColorModifier as any).identity = Symbol('textInputBorderColor');
    class TextInputBorderStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetBorderStyle(node);
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
            getUINativeModule().textInput.setBorderStyle(node, type, style, top, right, bottom, left);
          } else {
            getUINativeModule().textInput.resetBorderStyle(node);
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
    (TextInputBorderStyleModifier as any).identity = Symbol('textInputBorderStyle');
    class TextInputBorderRadiusModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetBorderRadius(node);
        }
        else {
          if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
            getUINativeModule().textInput.setBorderRadius(node, this.value, this.value, this.value, this.value);
          }
          else {
            if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
              (Object.keys(this.value).indexOf('topEnd') >= 0) ||
              (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
              (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
              getUINativeModule().textInput.setBorderRadius(node, this.value.topStart, this.value.topEnd, this.value.bottomStart, this.value.bottomEnd);
            } else {
              getUINativeModule().textInput.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
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
    (TextInputBorderRadiusModifier as any).identity = Symbol('textInputBorderRadius');
    class TextInputBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetBackgroundColor(node);
        } else {
          getUINativeModule().textInput.setBackgroundColor(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputBackgroundColorModifier as any).identity = Symbol('textInputBackgroundColor');
    class TextInputMarginModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetMargin(node);
        }
        else {
          getUINativeModule().textInput.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
          !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
          !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
          !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
      }
    }
    (TextInputMarginModifier as any).identity = Symbol('textInputMargin');
    class TextInputOnWillChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnWillChange(node);
        } else {
          getUINativeModule().textInput.setOnWillChange(node, this.value);
        }
      }
    }
    (TextInputOnWillChangeModifier as any).identity = Symbol('textInputOnWillChange');
    class TextInputOnWillInsertModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnWillInsert(node);
        } else {
          getUINativeModule().textInput.setOnWillInsert(node, this.value);
        }
      }
    }
    (TextInputOnWillInsertModifier as any).identity = Symbol('textInputOnWillInsert');

    class TextInputOnDidInsertModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnDidInsert(node);
        } else {
          getUINativeModule().textInput.setOnDidInsert(node, this.value);
        }
      }
    }
    (TextInputOnDidInsertModifier as any).identity = Symbol('textInputOnDidInsert');

    class TextInputOnWillDeleteModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnWillDelete(node);
        } else {
          getUINativeModule().textInput.setOnWillDelete(node, this.value);
        }
      }
    }
    (TextInputOnWillDeleteModifier as any).identity = Symbol('textInputOnWillDelete');

    class TextInputOnDidDeleteModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnDidDelete(node);
        } else {
          getUINativeModule().textInput.setOnDidDelete(node, this.value);
        }
      }
    }
    (TextInputOnDidDeleteModifier as any).identity = Symbol('textInputOnDidDelete');
    class TextInputEnablePreviewTextModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetEnablePreviewText(node);
        }
        else {
          getUINativeModule().textInput.setEnablePreviewText(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputEnablePreviewTextModifier as any).identity = Symbol('textInputEnablePreviewText');
    class TextInputEditMenuOptionsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetSelectionMenuOptions(node);
        } else {
          getUINativeModule().textInput.setSelectionMenuOptions(node, this.value);
        }
      }
    }
    (TextInputEditMenuOptionsModifier as any).identity = Symbol('textInputEditMenuOptions');

    class TextInputWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetWidth(node);
        } else {
          getUINativeModule().textInput.setWidth(node, this.value);
        }
      }
    }
    (TextInputWidthModifier as any).identity = Symbol('textInputWidth');
    class TextInputEnableHapticFeedbackModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetEnableHapticFeedback(node);
        }
        else {
          getUINativeModule().textInput.setEnableHapticFeedback(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputEnableHapticFeedbackModifier as any).identity = Symbol('textInputEnableHapticFeedback');

    class TextInputEllipsisModeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetEllipsisMode(node);
        }
        else {
          getUINativeModule().textInput.setEllipsisMode(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputEllipsisModeModifier as any).identity = Symbol('textInputEllipsisMode');

    class TextInputStopBackPressModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetStopBackPress(node);
        }
        else {
          getUINativeModule().textInput.setStopBackPress(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputStopBackPressModifier as any).identity = Symbol('textInputStopBackPress');

    class TextInputKeyboardAppearanceModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetKeyboardAppearance(node);
        }
        else {
          getUINativeModule().textInput.setKeyboardAppearance(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputKeyboardAppearanceModifier as any).identity = Symbol('textInputKeyboardAppearance');

    class TextInputStrokeWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetStrokeWidth(node);
        }
        else if (!isObject(this.value)) {
          getUINativeModule().textInput.resetStrokeWidth(node);
        }
        else {
          getUINativeModule().textInput.setStrokeWidth(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputStrokeWidthModifier as any).identity = Symbol('textInputStrokeWidth');

    class TextInputStrokeColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetStrokeColor(node);
        }
        else {
          getUINativeModule().textInput.setStrokeColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputStrokeColorModifier as any).identity = Symbol('textInputStrokeColor');

    class TextInputEnableAutoSpacingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetEnableAutoSpacing(node);
        }
        else {
          getUINativeModule().textInput.setEnableAutoSpacing(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputEnableAutoSpacingModifier as any).identity = Symbol('textInputEnableAutoSpacing');

    class TextInputOrphanCharOptimizationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOrphanCharOptimization(node);
        } else {
          getUINativeModule().textInput.setOrphanCharOptimization(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputOrphanCharOptimizationModifier as any).identity = Symbol('textInputOrphanCharOptimization');

    class TextInputCompressLeadingPunctuationModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetCompressLeadingPunctuation(node);
        }
        else {
          getUINativeModule().textInput.setCompressLeadingPunctuation(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputCompressLeadingPunctuationModifier as any).identity = Symbol('textInputCompressLeadingPunctuation');

    class TextInputPunctuationOverflowModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetPunctuationOverflow(node);
        }
        else {
          getUINativeModule().textInput.setPunctuationOverflow(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    TextInputPunctuationOverflowModifier.identity = Symbol('textInputPunctuationOverflow');

    class TextInputIncludeFontPaddingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetIncludeFontPadding(node);
        }
        else {
          getUINativeModule().textInput.setIncludeFontPadding(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputIncludeFontPaddingModifier as any).identity = Symbol('textInputIncludeFontPadding');

    class TextInputFallbackLineSpacingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetFallbackLineSpacing(node);
        }
        else {
          getUINativeModule().textInput.setFallbackLineSpacing(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputFallbackLineSpacingModifier as any).identity = Symbol('textInputFallbackLineSpacing');

    class TextInputOnSecurityStateChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnSecurityStateChange(node);
        }
        else {
          getUINativeModule().textInput.setOnSecurityStateChange(node, this.value);
        }
      }
    }
    (TextInputOnSecurityStateChangeModifier as any).identity = Symbol('textInputOnSecurityStateChange');

    class TextInputSelectDetectorEnableModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetSelectDetectorEnable(node);
        } else {
          getUINativeModule().textInput.setSelectDetectorEnable(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputSelectDetectorEnableModifier as any).identity = Symbol('textInputSelectDetectorEnable');

    class TextInputOnWillAttachIMEModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetOnWillAttachIME(node);
        } else {
          getUINativeModule().textInput.setOnWillAttachIME(node, this.value);
        }
      }
    }
    (TextInputOnWillAttachIMEModifier as any).identity = Symbol('textInputOnWillAttachIME');

    class TextInputTextDirectionModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetTextDirection(node);
        }
        else {
          getUINativeModule().textInput.setTextDirection(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputTextDirectionModifier as any).identity = Symbol('textInputTextDirection');

    class TextInputSelectedDragPreviewStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetSelectedDragPreviewStyle(node);
        }
        else {
          getUINativeModule().textInput.setSelectedDragPreviewStyle(node, this.value.color);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value) ||
          !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
      }
    }
    (TextInputSelectedDragPreviewStyleModifier as any).identity = Symbol('textInputSelectedDragPreviewStyle');

    class TextInputStrokeJoinStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textInput.resetStrokeJoinStyle(node);
        }
        else {
          getUINativeModule().textInput.setStrokeJoinStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextInputStrokeJoinStyleModifier as any).identity = Symbol('textInputStrokeJoinStyle');

    loadComponent.componentObj = { 'component': ArkTextInputComponent };
  }
  return loadComponent.componentObj;
}

class JSTextInput extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().textInput.create(params);
  }
  static type(value: any): void {
    getUINativeModule().textInput.setType(true, value);
  }
  static contentType(value: any): void {
    getUINativeModule().textInput.setContentType(true, value);
  }
  static placeholderColor(value: any): void {
    getUINativeModule().textInput.setPlaceholderColor(true, value);
  }
  static placeholderFont(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    getUINativeModule().textInput.setPlaceholderFont(true, value?.size, value?.weight, value?.family, value?.style);
  }
  static backgroundColor(value: any): void {
    getUINativeModule().textInput.setBackgroundColor(true, value);
  }
  static enterKeyType(value: any): void {
    getUINativeModule().textInput.setEnterKeyType(true, value);
  }
  static caretColor(value: any): void {
    getUINativeModule().textInput.setCaretColor(true, value);
  }
  static caretPosition(value: any): void {
    getUINativeModule().textInput.setCaretPosition(true, value);
  }
  static selectedBackgroundColor(value: any): void {
    getUINativeModule().textInput.setSelectedBackgroundColor(true, value);
  }
  static caretStyle(value: any): void {
    getUINativeModule().textInput.setCaretStyleJs(true, value);
  }
  static hoverEffect(value: any): void {
    getUINativeModule().textInput.setHoverEffect(true, value);
  }
  static maxLength(value: any): void {
    getUINativeModule().textInput.setMaxLength(true, value);
  }
  static width(value: any): void {
    getUINativeModule().textInput.setWidthJs(true, value);
  }
  static height(value: any): void {
    __Common__.height(value);
    getUINativeModule().textInput.setHeightJs(true, value);
  }
  static padding(value: any): void {
    getUINativeModule().textInput.setPaddingJs(true, value);
  }

  static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.TextInputModifier(nativePtr, classType);
        });
    }

  static margin(value: any): void {
    __Common__.margin(value);
    getUINativeModule().textInput.setMargin(true);
  }
  static border(value: any): void {
    __Common__.border(value);
    if (value !== null && value !== undefined) {
      getUINativeModule().textInput.setBackBorder(true);
    }
  }
  static borderWidth(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    __Common__.borderWidth(value);
    getUINativeModule().textInput.setBackBorder(true);
  }
  static borderColor(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    __Common__.borderColor(value);
    getUINativeModule().textInput.setBackBorder(true);
  }
  static borderStyle(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    __Common__.borderStyle(value);
    getUINativeModule().textInput.setBackBorder(true);
  }
  static borderRadius(value: any): void {
    if (value === null || value === undefined) {
      getUINativeModule().textInput.resetBorderRadiusJS(true);
      return;
    }
    __Common__.borderRadius(value);
    getUINativeModule().textInput.setBackBorder(true);
  }
  static fontSize(value: any): void {
    getUINativeModule().textInput.setFontSize(true, value);
  }
  static fontColor(value: any): void {
    getUINativeModule().textInput.setFontColor(true, value);
  }
  static fontWeight(value: any): void {
    getUINativeModule().textInput.setFontWeight(true, value);
  }
  static fontStyle(value: any): void {
    getUINativeModule().textInput.setFontStyle(true, value);
  }
  static fontFamily(value: any): void {
    getUINativeModule().textInput.setFontFamily(true, value);
  }
  static minFontScale(value: any): void {
    getUINativeModule().textInput.setMinFontScale(true, value);
  }
  static maxFontScale(value: any): void {
    getUINativeModule().textInput.setMaxFontScale(true, value);
  }
  static inputFilter(value: any, error: any): void {
    getUINativeModule().textInput.setInputFilterJs(true, value, error);
  }
  static showPasswordIcon(value: any): void {
    getUINativeModule().textInput.setShowPasswordIcon(true, value);
  }
  static textAlign(value: any): void {
    getUINativeModule().textInput.setTextAlign(true, value);
  }
  static textDirection(value: any): void {
    getUINativeModule().textInput.setTextDirection(true, value);
  }
  static style(value: any): void {
    getUINativeModule().textInput.setStyle(true, value);
  }
  static copyOption(value: any): void {
    getUINativeModule().textInput.setCopyOption(true, value);
  }
  static foregroundColor(value: any): void {
    getUINativeModule().textInput.setForegroundColor(true, value);
  }
  static showUnit(event: any): void {
    getUINativeModule().textInput.setShowUnit(true, event);
  }
  static showError(value: any): void {
    getUINativeModule().textInput.setShowError(true, value);
  }
  static barState(value: any): void {
    getUINativeModule().textInput.setBarState(true, value);
  }
  static maxLines(value: any): void {
    getUINativeModule().textInput.setMaxLines(true, value);
  }
  static wordBreak(value: any): void {
    getUINativeModule().textInput.setWordBreak(true, value);
  }
  static ellipsisMode(value: any): void {
    getUINativeModule().textInput.setEllipsisMode(true, value);
  }
  static onEditChanged(callback: any): void {
    getUINativeModule().textInput.setOnEditChange(true, callback);
  }
  static onEditChange(callback: any): void {
    getUINativeModule().textInput.setOnEditChange(true, callback);
  }
  static onSecurityStateChange(callback: any): void {
    getUINativeModule().textInput.setOnSecurityStateChange(true, callback);
  }
  static onSubmit(callback: any): void {
    getUINativeModule().textInput.setOnSubmitJs(true, callback);
  }
  static onWillChange(callback: any): void {
    getUINativeModule().textInput.setOnWillChange(true, callback);
  }
  static onChange(callback: any): void {
    getUINativeModule().textInput.setOnChange(true, callback);
  }
  static onTextSelectionChange(callback: any): void {
    getUINativeModule().textInput.setOnTextSelectionChange(true, callback);
  }
  static onContentScroll(callback: any): void {
    getUINativeModule().textInput.setOnContentScroll(true, callback);
  }
  static onWillCopy(callback: any): void {
    getUINativeModule().textInput.setOnWillCopy(true, callback);
  }
  static onCopy(callback: any): void {
    getUINativeModule().textInput.setOnCopy(true, callback);
  }
  static onWillCut(callback: any): void {
    getUINativeModule().textInput.setOnWillCut(true, callback);
  }
  static onCut(callback: any): void {
    getUINativeModule().textInput.setOnCut(true, callback);
  }
  static onPaste(callback: any): void {
    getUINativeModule().textInput.setOnPaste(true, callback);
  }
  static onClick(callback: any): void {
    if (ViewStackProcessor.UsesNewPipeline()) {
      __Common__.onClick(callback);
    } else {
      getUINativeModule().textInput.setOnClick(true, callback);
    }
  }
  static requestKeyboardOnFocus(callback: any): void {
    getUINativeModule().textInput.setEnableKeyboardOnFocus(true, callback);
  }
  static passwordIcon(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    getUINativeModule().textInput.setPasswordIcon(true, value.onIconSrc, value.offIconSrc);
  }
  static showUnderline(value: any): void {
    getUINativeModule().textInput.setShowUnderline(true, value);
  }
  static underlineColor(value: any): void {
    if (value === null || value === undefined) {
      getUINativeModule().textInput.resetUnderlineColor(true);
      return;
    }
    const valueType = typeof value;
    if (valueType === 'number' || valueType === 'string' || isResource(value)) {
      getUINativeModule().textInput.setUnderlineColor(true, value, undefined, undefined, undefined, undefined);
    }
    else {
      getUINativeModule().textInput.setUnderlineColor(true, undefined, value.normal, value.typing, value.error, value.disable);
    }
  }
  static enableKeyboardOnFocus(value: any): void {
    getUINativeModule().textInput.setEnableKeyboardOnFocus(true, value);
  }
  static selectionMenuHidden(value: any): void {
    getUINativeModule().textInput.setSelectionMenuHidden(true, value);
  }
  static customKeyboard(value: any, options: any): void {
    getUINativeModule().textInput.setCustomKeyboardJs(true, value, options);
  }
  static passwordRules(value: any): void {
    getUINativeModule().textInput.setPasswordRules(true, value);
  }
  static enableAutoFill(value: any): void {
    getUINativeModule().textInput.setEnableAutoFill(true, value);
  }
  static enableSelectedDataDetector(value: any): void {
    getUINativeModule().textInput.setSelectDetectorEnable(true, value);
  }
  static enableAutoFillAnimation(value: any): void {
    getUINativeModule().textInput.setEnableAutoFillAnimation(true, value);
  }
  static cancelButton(value: any): void {
    if (value === null || value === undefined) {
      return;
    }
    getUINativeModule().textInput.setCancelButton(true, value.style, value.icon);
  }
  static voiceButton(value: any): void {
    getUINativeModule().textInput.setVoiceButton(true, value);
  }
  static selectAll(value: any): void {
    getUINativeModule().textInput.setSelectAll(true, value);
  }
  static lineBreakStrategy(value: any): void {
    getUINativeModule().textInput.setLineBreakStrategy(true, value);
  }
  static showCounter(value: any, options: any): void {
    getUINativeModule().textInput.setShowCounter(true, value, options?.highlightBorder, options?.thresholdPercentage, options?.counterTextColor, options?.counterTextOverflowColor);
  }
  static fontFeature(value: any): void {
    getUINativeModule().textInput.setFontFeature(true, value);
  }
  static decoration(value: any): void {
    getUINativeModule().textInput.setDecoration(true, value?.type, value?.color, value?.style, value?.thicknessScale);
  }
  static minFontSize(value: any): void {
    getUINativeModule().textInput.setMinFontSize(true, value);
  }
  static maxFontSize(value: any): void {
    getUINativeModule().textInput.setMaxFontSize(true, value);
  }
  static heightAdaptivePolicy(value: any): void {
    getUINativeModule().textInput.setHeightAdaptivePolicy(true, value);
  }
  static letterSpacing(value: any): void {
    getUINativeModule().textInput.setLetterSpacing(true, value);
  }
  static lineHeight(value: any): void {
    getUINativeModule().textInput.setLineHeight(true, value);
  }
  static halfLeading(value: any): void {
    getUINativeModule().textInput.setHalfLeading(true, value);
  }
  static textOverflow(value: any): void {
    getUINativeModule().textInput.setTextOverflow(true, value);
  }
  static textIndent(value: any): void {
    getUINativeModule().textInput.setTextIndent(true, value);
  }
  static showPassword(value: any): void {
    getUINativeModule().textInput.setShowPassword(true, value);
  }
  static onWillInsert(callback: any): void {
    getUINativeModule().textInput.setOnWillInsert(true, callback);
  }
  static onDidInsert(callback: any): void {
    getUINativeModule().textInput.setOnDidInsert(true, callback);
  }
  static onWillDelete(callback: any): void {
    getUINativeModule().textInput.setOnWillDelete(true, callback);
  }
  static onDidDelete(callback: any): void {
    getUINativeModule().textInput.setOnDidDelete(true, callback);
  }
  static editMenuOptions(value: any): void {
    getUINativeModule().textInput.setSelectionMenuOptions(true, value);
  }
  static enablePreviewText(value: any): void {
    getUINativeModule().textInput.setEnablePreviewText(true, value);
  }
  static enableHapticFeedback(value: any): void {
    getUINativeModule().textInput.setEnableHapticFeedback(true, value);
  }
  static autoCapitalizationMode(value: any): void {
    getUINativeModule().textInput.setAutoCapitalizationMode(true, value);
  }
  static stopBackPress(value: any): void {
    getUINativeModule().textInput.setStopBackPress(true, value);
  }
  static keyboardAppearance(value: any): void {
    getUINativeModule().textInput.setKeyboardAppearance(true, value);
  }
  static strokeWidth(value: any): void {
    getUINativeModule().textInput.setStrokeWidth(true, value);
  }
  static strokeColor(value: any): void {
    getUINativeModule().textInput.setStrokeColor(true, value);
  }
  static strokeJoinStyle(value: any): void {
    getUINativeModule().textInput.setStrokeJoinStyle(true, value);
  }
  static shaderStyle(value: any): void {
    getUINativeModule().textInput.setShaderStyle(true, value);
  }
  static enableAutoSpacing(value: any): void {
    getUINativeModule().textInput.setEnableAutoSpacing(true, value);
  }
  static onWillAttachIME(callback: any): void {
    getUINativeModule().textInput.setOnWillAttachIME(true, callback);
  }
  static orphanCharOptimization(value: any): void {
    getUINativeModule().textInput.setOrphanCharOptimization(true, value);
  }
  static compressLeadingPunctuation(value: any): void {
    getUINativeModule().textInput.setCompressLeadingPunctuation(true, value);
  }
  static punctuationOverflow(value: any): void {
    getUINativeModule().textInput.setPunctuationOverflow(true, value);
  }
  static includeFontPadding(value: any): void {
    getUINativeModule().textInput.setIncludeFontPadding(true, value);
  }
  static fallbackLineSpacing(value: any): void {
    getUINativeModule().textInput.setFallbackLineSpacing(true, value);
  }
  static selectedDragPreviewStyle(value: any): void {
    getUINativeModule().textInput.setSelectedDragPreviewStyle(true, value?.color);
  }
  static accessibilityText(value: any): void {
    JSViewAbstract.accessibilityText(value);
    getUINativeModule().textInput.setAccessibilityText(true, value);
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
  globalThis.ArkTextInputComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.TextInput = JSTextInput;
}

export default { loadComponent, createComponent, exportComponent, exportView };
