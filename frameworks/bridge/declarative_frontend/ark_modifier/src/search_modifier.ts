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

class LazyArkSearchComponent extends ArkComponent {
  static module: SearchComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkSearchComponent.module === undefined) {
     LazyArkSearchComponent.module = globalThis.requireNapi('arkui.components.arksearch');
   }

   this.lazyComponent = LazyArkSearchComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  searchButton(value: ResourceStr, option?: SearchButtonOptions): LazyArkSearchComponent {
   this.lazyComponent.searchButton(value, option);
   return this;
  }

  searchIcon(value: IconOptions | SymbolGlyphModifier): LazyArkSearchComponent {
   this.lazyComponent.searchIcon(value);
   return this;
  }

  cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): LazyArkSearchComponent {
   this.lazyComponent.cancelButton(value);
   return this;
  }

  fontColor(value: ResourceColor): LazyArkSearchComponent {
   this.lazyComponent.fontColor(value);
   return this;
  }

  caretStyle(value: CaretStyle): LazyArkSearchComponent {
   this.lazyComponent.caretStyle(value);
   return this;
  }

  placeholderColor(value: ResourceColor): LazyArkSearchComponent {
   this.lazyComponent.placeholderColor(value);
   return this;
  }

  placeholderFont(value?: Font): LazyArkSearchComponent {
   this.lazyComponent.placeholderFont(value);
   return this;
  }

  textFont(value?: Font): LazyArkSearchComponent {
   this.lazyComponent.textFont(value);
   return this;
  }

  textAlign(value: TextAlign): LazyArkSearchComponent {
   this.lazyComponent.textAlign(value);
   return this;
  }

  textDirection(direction: TextDirection | undefined): LazyArkSearchComponent {
   this.lazyComponent.textDirection(direction);
   return this;
  }

  onSubmit(callback: SearchSubmitCallback): LazyArkSearchComponent {
   this.lazyComponent.onSubmit(callback);
   return this;
  }

  onChange(callback: EditableTextOnChangeCallback): LazyArkSearchComponent {
   this.lazyComponent.onChange(callback);
   return this;
  }

  onTextSelectionChange(callback: OnTextSelectionChangeCallback): LazyArkSearchComponent {
   this.lazyComponent.onTextSelectionChange(callback);
   return this;
  }

  onContentScroll(callback: OnContentScrollCallback): LazyArkSearchComponent {
   this.lazyComponent.onContentScroll(callback);
   return this;
  }

  height(value: Length): this {
    this.lazyComponent.height(value);
    return this;
  }

  enableKeyboardOnFocus(value: boolean): LazyArkSearchComponent {
   this.lazyComponent.enableKeyboardOnFocus(value);
   return this;
  }

  onCopy(callback: Callback<string>): LazyArkSearchComponent {
   this.lazyComponent.onCopy(callback);
   return this;
  }

  onCut(callback: Callback<string>): LazyArkSearchComponent {
   this.lazyComponent.onCut(callback);
   return this;
  }

  onPaste(callback: OnPasteCallback): LazyArkSearchComponent {
   this.lazyComponent.onPaste(callback);
   return this;
  }

  copyOption(value: CopyOptions): LazyArkSearchComponent {
   this.lazyComponent.copyOption(value);
   return this;
  }

  selectionMenuHidden(value: boolean): LazyArkSearchComponent {
   this.lazyComponent.selectionMenuHidden(value);
   return this;
  }

  customKeyboard(value: CustomBuilder | ComponentContent | undefined, options?: KeyboardOptions): LazyArkSearchComponent {
   this.lazyComponent.customKeyboard(value, options);
   return this;
  }

  enterKeyType(value: EnterKeyType): LazyArkSearchComponent {
   this.lazyComponent.enterKeyType(value);
   return this;
  }

  maxLength(value: number): LazyArkSearchComponent {
   this.lazyComponent.maxLength(value);
   return this;
  }

  type(value: SearchType): LazyArkSearchComponent {
   this.lazyComponent.type(value);
   return this;
  }

  editMenuOptions(editMenu: EditMenuOptions): LazyArkSearchComponent {
   this.lazyComponent.editMenuOptions(editMenu);
   return this;
  }

  strokeWidth(width: Optional<LengthMetrics>): LazyArkSearchComponent {
   this.lazyComponent.strokeWidth(width);
   return this;
  }

  strokeColor(color: Optional<ResourceColor>): LazyArkSearchComponent {
   this.lazyComponent.strokeColor(color);
   return this;
  }

  margin(value: Margin | Length): this {
    this.lazyComponent.margin(value);
    return this;
  }

  selectedDragPreviewStyle(value: SelectedDragPreviewStyle | undefined): LazyArkSearchComponent {
   this.lazyComponent.selectedDragPreviewStyle(value);
   return this;
  }

  decoration(value: TextDecorationOptions): LazyArkSearchComponent {
   this.lazyComponent.decoration(value);
   return this;
  }

  minFontSize(value: number | string | Resource): LazyArkSearchComponent {
   this.lazyComponent.minFontSize(value);
   return this;
  }

  maxFontSize(value: number | string | Resource): LazyArkSearchComponent {
   this.lazyComponent.maxFontSize(value);
   return this;
  }

  minFontScale(scale: Optional<number | Resource>): LazyArkSearchComponent {
   this.lazyComponent.minFontScale(scale);
   return this;
  }

  maxFontScale(scale: Optional<number | Resource>): LazyArkSearchComponent {
   this.lazyComponent.maxFontScale(scale);
   return this;
  }

  dividerColor(color: Optional<ColorMetrics>): LazyArkSearchComponent {
   this.lazyComponent.dividerColor(color);
   return this;
  }

  letterSpacing(value: number | string | Resource): LazyArkSearchComponent {
   this.lazyComponent.letterSpacing(value);
   return this;
  }

  lineHeight(value: number | string | Resource): LazyArkSearchComponent {
   this.lazyComponent.lineHeight(value);
   return this;
  }

  halfLeading(halfLeading: Optional<boolean>): LazyArkSearchComponent {
   this.lazyComponent.halfLeading(halfLeading);
   return this;
  }

  fontFeature(value: string): LazyArkSearchComponent {
   this.lazyComponent.fontFeature(value);
   return this;
  }

  id(value: string): this {
    this.lazyComponent.id(value);
    return this;
  }

  key(value: string): this {
    this.lazyComponent.key(value);
    return this;
  }

  selectedBackgroundColor(value: ResourceColor): LazyArkSearchComponent {
   this.lazyComponent.selectedBackgroundColor(value);
   return this;
  }

  inputFilter(value: ResourceStr, error?: Callback<string>): LazyArkSearchComponent {
   this.lazyComponent.inputFilter(value, error);
   return this;
  }

  onEditChange(callback: Callback<boolean>): LazyArkSearchComponent {
   this.lazyComponent.onEditChange(callback);
   return this;
  }

  textIndent(value: Dimension): LazyArkSearchComponent {
   this.lazyComponent.textIndent(value);
   return this;
  }

  onWillInsert(callback: Callback<InsertValue, boolean>): LazyArkSearchComponent {
   this.lazyComponent.onWillInsert(callback);
   return this;
  }

  onDidInsert(callback: Callback<InsertValue>): LazyArkSearchComponent {
   this.lazyComponent.onDidInsert(callback);
   return this;
  }

  onWillDelete(callback: Callback<DeleteValue, boolean>): LazyArkSearchComponent {
   this.lazyComponent.onWillDelete(callback);
   return this;
  }

  onDidDelete(callback: Callback<DeleteValue>): LazyArkSearchComponent {
   this.lazyComponent.onDidDelete(callback);
   return this;
  }

  enablePreviewText(enable: boolean): LazyArkSearchComponent {
   this.lazyComponent.enablePreviewText(enable);
   return this;
  }

  enableHapticFeedback(isEnabled: boolean): LazyArkSearchComponent {
   this.lazyComponent.enableHapticFeedback(isEnabled);
   return this;
  }

  autoCapitalizationMode(mode: AutoCapitalizationMode): LazyArkSearchComponent {
   this.lazyComponent.autoCapitalizationMode(mode);
   return this;
  }

  stopBackPress(isStopped: Optional<boolean>): LazyArkSearchComponent {
   this.lazyComponent.stopBackPress(isStopped);
   return this;
  }

  keyboardAppearance(appearance: Optional<KeyboardAppearance>): LazyArkSearchComponent {
   this.lazyComponent.keyboardAppearance(appearance);
   return this;
  }

  onWillChange(callback: Callback<EditableTextChangeValue, boolean>): LazyArkSearchComponent {
   this.lazyComponent.onWillChange(callback);
   return this;
  }

  enableAutoSpacing(enabled: Optional<boolean>): LazyArkSearchComponent {
   this.lazyComponent.enableAutoSpacing(enabled);
   return this;
  }

  onWillAttachIME(callback: Callback<IMEClient>): LazyArkSearchComponent {
   this.lazyComponent.onWillAttachIME(callback);
   return this;
  }

  enableSelectedDataDetector(enable: boolean | undefined): LazyArkSearchComponent {
   this.lazyComponent.enableSelectedDataDetector(enable);
   return this;
  }

  compressLeadingPunctuation(enabled: Optional<boolean>): LazyArkSearchComponent {
   this.lazyComponent.compressLeadingPunctuation(enabled);
   return this;
  }

  includeFontPadding(include: Optional<boolean>): LazyArkSearchComponent {
   this.lazyComponent.includeFontPadding(include);
   return this;
  }

  fallbackLineSpacing(enabled: Optional<boolean>): LazyArkSearchComponent {
   this.lazyComponent.fallbackLineSpacing(enabled);
   return this;
  }
}

class SearchModifier extends LazyArkSearchComponent implements AttributeModifier<SearchAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: SearchAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<SearchAttribute, ArkSearchComponent, ArkComponent>(instance, this);
  }
}
