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

class LazyArkRichEditorComponent extends ArkComponent {
  static module: RichEditorComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkRichEditorComponent.module === undefined) {
     LazyArkRichEditorComponent.module = globalThis.requireNapi('arkui.components.arkricheditor');
   }

   this.lazyComponent = LazyArkRichEditorComponent.module.createComponent(nativePtr, classType);
   console.log('LazyArkRichEditorComponent lazyload nativeModule');
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  enableDataDetector(value: boolean): LazyArkRichEditorComponent {
   this.lazyComponent.enableDataDetector(value);
   return this;
  }

  dataDetectorConfig(config: TextDataDetectorConfig): LazyArkRichEditorComponent {
   this.lazyComponent.dataDetectorConfig(config);
   return this;
  }

  copyOptions(value: CopyOptions): LazyArkRichEditorComponent {
   this.lazyComponent.copyOptions(value);
   return this;
  }

  caretColor(value: ResourceColor): LazyArkRichEditorComponent {
   this.lazyComponent.caretColor(value);
   return this;
  }

  onSelectionChange(callback: Callback<RichEditorRange>): LazyArkRichEditorComponent {
   this.lazyComponent.onSelectionChange(callback);
   return this;
  }

  selectedBackgroundColor(value: ResourceColor): LazyArkRichEditorComponent {
   this.lazyComponent.selectedBackgroundColor(value);
   return this;
  }

  enterKeyType(value: EnterKeyType): LazyArkRichEditorComponent {
   this.lazyComponent.enterKeyType(value);
   return this;
  }

  onPaste(callback: PasteEventCallback): LazyArkRichEditorComponent {
   this.lazyComponent.onPaste(callback);
   return this;
  }

  onReady(callback: Callback<void>): LazyArkRichEditorComponent {
   this.lazyComponent.onReady(callback);
   return this;
  }

  onSelect(callback: Callback<RichEditorSelection>): LazyArkRichEditorComponent {
   this.lazyComponent.onSelect(callback);
   return this;
  }

  onSubmit(callback: SubmitCallback): LazyArkRichEditorComponent {
   this.lazyComponent.onSubmit(callback);
   return this;
  }

  aboutToIMEInput(callback: Callback<RichEditorInsertValue, boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.aboutToIMEInput(callback);
   return this;
  }

  onIMEInputComplete(callback: Callback<RichEditorTextSpanResult>): LazyArkRichEditorComponent {
   this.lazyComponent.onIMEInputComplete(callback);
   return this;
  }

  onWillChange(callback: Callback<RichEditorChangeValue, boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.onWillChange(callback);
   return this;
  }

  onDidChange(callback: OnDidChangeCallback): LazyArkRichEditorComponent {
   this.lazyComponent.onDidChange(callback);
   return this;
  }

  placeholder(value: ResourceStr, style?: PlaceholderStyle): LazyArkRichEditorComponent {
   this.lazyComponent.placeholder(value, style);
   return this;
  }

  aboutToDelete(callback: Callback<RichEditorDeleteValue, boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.aboutToDelete(callback);
   return this;
  }

  onDeleteComplete(callback: Callback<void>): LazyArkRichEditorComponent {
   this.lazyComponent.onDeleteComplete(callback);
   return this;
  }

  bindSelectionMenu(spanType: RichEditorSpanType, content: CustomBuilder, responseType: ResponseType | RichEditorResponseType, options?: SelectionMenuOptions): LazyArkRichEditorComponent {
   throw new Error('Method not implemented.');
  }

  customKeyboard(value: CustomBuilder | ComponentContent | undefined, options?: KeyboardOptions | undefined): LazyArkRichEditorComponent {
   this.lazyComponent.customKeyboard(value, options);
   return this;
  }

  onEditingChange(callback: Callback<boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.onEditingChange(callback);
   return this;
  }

  onCut(callback: Callback<CutEvent>): LazyArkRichEditorComponent {
   this.lazyComponent.onCut(callback);
   return this;
  }

  onCopy(callback: Callback<CopyEvent>): LazyArkRichEditorComponent {
   this.lazyComponent.onCopy(callback);
   return this;
  }

  enableKeyboardOnFocus(value: boolean): LazyArkRichEditorComponent {
   this.lazyComponent.enableKeyboardOnFocus(value);
   return this;
  }

  enablePreviewText(value: boolean): LazyArkRichEditorComponent {
   this.lazyComponent.enablePreviewText(value);
   return this;
  }

  editMenuOptions(value: EditMenuOptions): LazyArkRichEditorComponent {
   this.lazyComponent.editMenuOptions(value);
   return this;
  }

  barState(value: BarState): LazyArkRichEditorComponent {
   this.lazyComponent.barState(value);
   return this;
  }

  maxLength(value: Optional<number>): LazyArkRichEditorComponent {
   this.lazyComponent.maxLength(value);
   return this;
  }

  maxLines(value: Optional<number>): LazyArkRichEditorComponent {
   this.lazyComponent.maxLines(value);
   return this;
  }

  stopBackPress(value: Optional<boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.stopBackPress(value);
   return this;
  }

  keyboardAppearance(value: Optional<KeyboardAppearance>): LazyArkRichEditorComponent {
   this.lazyComponent.keyboardAppearance(value);
   return this;
  }

  onDidIMEInput(callback: Callback<TextRange>): LazyArkRichEditorComponent {
   this.lazyComponent.onDidIMEInput(callback);
   return this;
  }

  onWillAttachIME(callback: Callback<IMEClient> | undefined): LazyArkRichEditorComponent {
   this.lazyComponent.onWillAttachIME(callback);
   return this;
  }

  enableHapticFeedback(value: boolean): LazyArkRichEditorComponent {
   this.lazyComponent.enableHapticFeedback(value);
   return this;
  }

  enableAutoSpacing(enable: Optional<boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.enableAutoSpacing(enable);
   return this;
  }

  compressLeadingPunctuation(enable: Optional<boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.compressLeadingPunctuation(enable);
   return this;
  }

  undoStyle(style: Optional<UndoStyle>): LazyArkRichEditorComponent {
   this.lazyComponent.undoStyle(style);
   return this;
  }

  scrollBarColor(style: Optional<ColorMetrics>): LazyArkRichEditorComponent {
   this.lazyComponent.scrollBarColor(style);
   return this;
  }

  selectedDragPreviewStyle(value: SelectedDragPreviewStyle | undefined): LazyArkRichEditorComponent {
   this.lazyComponent.selectedDragPreviewStyle(value);
   return this;
  }

  includeFontPadding(enable: Optional<boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.includeFontPadding(enable);
   return this;
  }

  fallbackLineSpacing(enable: Optional<boolean>): LazyArkRichEditorComponent {
   this.lazyComponent.fallbackLineSpacing(enable);
   return this;
  }

  singleLine(value: boolean | undefined): LazyArkRichEditorComponent {
   this.lazyComponent.singleLine(value);
   return this;
  }
}

class RichEditorModifier extends LazyArkRichEditorComponent implements AttributeModifier<RichEditorAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: RichEditorAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<RichEditorAttribute, ArkRichEditorComponent, ArkComponent>(instance, this);
  }
}
