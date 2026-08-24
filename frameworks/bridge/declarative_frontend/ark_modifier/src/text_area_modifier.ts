/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

class LazyArkTextAreaComponent extends ArkComponent {
  static module: TextAreaComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkTextAreaComponent.module === undefined) {
      LazyArkTextAreaComponent.module = globalThis.requireNapi('arkui.components.arktextarea');
    }

    this.lazyComponent = LazyArkTextAreaComponent.module!.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  enableSelectedDataDetector(value: any): this {
    this.lazyComponent.enableSelectedDataDetector(value);
    return this;
  }

  horizontalScrolling(value: any): this {
    this.lazyComponent.horizontalScrolling(value);
    return this;
  }

  allowChildCount(): this {
    this.lazyComponent.allowChildCount();
    return this;
  }

  initialize(value: any): this {
    this.lazyComponent.initialize(value);
    return this;
  }

  type(value: any): this {
    this.lazyComponent.type(value);
    return this;
  }

  placeholderColor(value: any): this {
    this.lazyComponent.placeholderColor(value);
    return this;
  }

  placeholderFont(value: any): this {
    this.lazyComponent.placeholderFont(value);
    return this;
  }

  textAlign(value: any): this {
    this.lazyComponent.textAlign(value);
    return this;
  }

  caretColor(value: any): this {
    this.lazyComponent.caretColor(value);
    return this;
  }

  fontColor(value: any): this {
    this.lazyComponent.fontColor(value);
    return this;
  }

  fontSize(value: any): this {
    this.lazyComponent.fontSize(value);
    return this;
  }

  fontStyle(value: any): this {
    this.lazyComponent.fontStyle(value);
    return this;
  }

  fontWeight(value: any): this {
    this.lazyComponent.fontWeight(value);
    return this;
  }

  fontFamily(value: any): this {
    this.lazyComponent.fontFamily(value);
    return this;
  }

  fontFeature(value: any): this {
    this.lazyComponent.fontFeature(value);
    return this;
  }

  inputFilter(value: any, error: any): this {
    this.lazyComponent.inputFilter(value, error);
    return this;
  }

  onChange(callback: any): this {
    this.lazyComponent.onChange(callback);
    return this;
  }

  onTextSelectionChange(callback: any): this {
    this.lazyComponent.onTextSelectionChange(callback);
    return this;
  }

  onContentScroll(callback: any): this {
    this.lazyComponent.onContentScroll(callback);
    return this;
  }

  onEditChange(callback: any): this {
    this.lazyComponent.onEditChange(callback);
    return this;
  }

  onWillCopy(callback: any): this {
    this.lazyComponent.onWillCopy(callback);
    return this;
  }

  onCopy(callback: any): this {
    this.lazyComponent.onCopy(callback);
    return this;
  }

  onWillCut(callback: any): this {
    this.lazyComponent.onWillCut(callback);
    return this;
  }

  onCut(callback: any): this {
    this.lazyComponent.onCut(callback);
    return this;
  }

  onPaste(callback: any): this {
    this.lazyComponent.onPaste(callback);
    return this;
  }

  copyOption(value: any): this {
    this.lazyComponent.copyOption(value);
    return this;
  }

  enableKeyboardOnFocus(value: any): this {
    this.lazyComponent.enableKeyboardOnFocus(value);
    return this;
  }

  maxLength(value: any): this {
    this.lazyComponent.maxLength(value);
    return this;
  }

  showCounter(value: any, options: any): this {
    this.lazyComponent.showCounter(value, options);
    return this;
  }

  style(value: any): this {
    this.lazyComponent.style(value);
    return this;
  }

  barState(value: any): this {
    this.lazyComponent.barState(value);
    return this;
  }

  selectionMenuHidden(value: any): this {
    this.lazyComponent.selectionMenuHidden(value);
    return this;
  }

  maxLines(value: any, options: any): this {
    this.lazyComponent.maxLines(value, options);
    return this;
  }

  minLines(value: any): this {
    this.lazyComponent.minLines(value);
    return this;
  }

  customKeyboard(value: any, options: any): this {
    this.lazyComponent.customKeyboard(value, options);
    return this;
  }

  decoration(value: any): this {
    this.lazyComponent.decoration(value);
    return this;
  }

  letterSpacing(value: any): this {
    this.lazyComponent.letterSpacing(value);
    return this;
  }

  lineSpacing(value: any, options: any): this {
    this.lazyComponent.lineSpacing(value, options);
    return this;
  }

  lineHeight(value: any): this {
    this.lazyComponent.lineHeight(value);
    return this;
  }

  halfLeading(value: any): this {
    this.lazyComponent.halfLeading(value);
    return this;
  }

  wordBreak(value: any): this {
    this.lazyComponent.wordBreak(value);
    return this;
  }

  lineBreakStrategy(value: any): this {
    this.lazyComponent.lineBreakStrategy(value);
    return this;
  }

  minFontSize(value: any): this {
    this.lazyComponent.minFontSize(value);
    return this;
  }

  maxFontSize(value: any): this {
    this.lazyComponent.maxFontSize(value);
    return this;
  }

  minFontScale(value: any): this {
    this.lazyComponent.minFontScale(value);
    return this;
  }

  maxFontScale(value: any): this {
    this.lazyComponent.maxFontScale(value);
    return this;
  }

  heightAdaptivePolicy(value: any): this {
    this.lazyComponent.heightAdaptivePolicy(value);
    return this;
  }

  selectedBackgroundColor(value: any): this {
    this.lazyComponent.selectedBackgroundColor(value);
    return this;
  }

  caretStyle(value: any): this {
    this.lazyComponent.caretStyle(value);
    return this;
  }

  textOverflow(value: any): this {
    this.lazyComponent.textOverflow(value);
    return this;
  }

  textIndent(value: any): this {
    this.lazyComponent.textIndent(value);
    return this;
  }

  enterKeyType(value: any): this {
    this.lazyComponent.enterKeyType(value);
    return this;
  }

  padding(value: any): this {
    this.lazyComponent.padding(value);
    return this;
  }

  onSubmit(callback: any): this {
    this.lazyComponent.onSubmit(callback);
    return this;
  }

  contentType(value: any): this {
    this.lazyComponent.contentType(value);
    return this;
  }

  enableAutoFill(value: any): this {
    this.lazyComponent.enableAutoFill(value);
    return this;
  }

  border(value: any): this {
    this.lazyComponent.border(value);
    return this;
  }

  borderWidth(value: any): this {
    this.lazyComponent.borderWidth(value);
    return this;
  }

  borderColor(value: any): this {
    this.lazyComponent.borderColor(value);
    return this;
  }

  borderStyle(value: any): this {
    this.lazyComponent.borderStyle(value);
    return this;
  }

  borderRadius(value: any): this {
    this.lazyComponent.borderRadius(value);
    return this;
  }

  backgroundColor(value: any): this {
    this.lazyComponent.backgroundColor(value);
    return this;
  }

  margin(value: any): this {
    this.lazyComponent.margin(value);
    return this;
  }

  onWillChange(callback: any): this {
    this.lazyComponent.onWillChange(callback);
    return this;
  }

  onWillInsert(callback: any): this {
    this.lazyComponent.onWillInsert(callback);
    return this;
  }

  onDidInsert(callback: any): this {
    this.lazyComponent.onDidInsert(callback);
    return this;
  }

  onWillDelete(callback: any): this {
    this.lazyComponent.onWillDelete(callback);
    return this;
  }

  onDidDelete(callback: any): this {
    this.lazyComponent.onDidDelete(callback);
    return this;
  }

  enablePreviewText(value: any): this {
    this.lazyComponent.enablePreviewText(value);
    return this;
  }

  autoCapitalizationMode(value: any): this {
    this.lazyComponent.autoCapitalizationMode(value);
    return this;
  }

  editMenuOptions(value: any): this {
    this.lazyComponent.editMenuOptions(value);
    return this;
  }

  width(value: any): this {
    this.lazyComponent.width(value);
    return this;
  }

  enableHapticFeedback(value: any): this {
    this.lazyComponent.enableHapticFeedback(value);
    return this;
  }

  ellipsisMode(value: any): this {
    this.lazyComponent.ellipsisMode(value);
    return this;
  }

  stopBackPress(value: any): this {
    this.lazyComponent.stopBackPress(value);
    return this;
  }

  keyboardAppearance(value: any): this {
    this.lazyComponent.keyboardAppearance(value);
    return this;
  }

  strokeWidth(value: any): this {
    this.lazyComponent.strokeWidth(value);
    return this;
  }

  strokeColor(value: any): this {
    this.lazyComponent.strokeColor(value);
    return this;
  }

  enableAutoSpacing(value: any): this {
    this.lazyComponent.enableAutoSpacing(value);
    return this;
  }

  orphanCharOptimization(value: any): this {
    this.lazyComponent.orphanCharOptimization(value);
    return this;
  }

  compressLeadingPunctuation(value: any): this {
    this.lazyComponent.compressLeadingPunctuation(value);
    return this;
  }

  punctuationOverflow(value: any): this {
    this.lazyComponent.punctuationOverflow(value);
    return this;
  }

  includeFontPadding(value: any): this {
    this.lazyComponent.includeFontPadding(value);
    return this;
  }

  fallbackLineSpacing(value: any): this {
    this.lazyComponent.fallbackLineSpacing(value);
    return this;
  }

  scrollBarColor(value: any): this {
    this.lazyComponent.scrollBarColor(value);
    return this;
  }

  onWillAttachIME(callback: any): this {
    this.lazyComponent.onWillAttachIME(callback);
    return this;
  }

  textDirection(value: any): this {
    this.lazyComponent.textDirection(value);
    return this;
  }

  selectedDragPreviewStyle(value: any): this {
    this.lazyComponent.selectedDragPreviewStyle(value);
    return this;
  }

  strokeJoinStyle(value: any): this {
    this.lazyComponent.strokeJoinStyle(value);
    return this;
  }

  shaderStyle(value: any): this {
    this.lazyComponent.shaderStyle(value);
    return this;
  }
}

class TextAreaModifier extends LazyArkTextAreaComponent implements AttributeModifier<TextAreaAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: TextAreaAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<TextAreaAttribute, ArkTextAreaComponent, ArkComponent>(instance, this);
  }
}
