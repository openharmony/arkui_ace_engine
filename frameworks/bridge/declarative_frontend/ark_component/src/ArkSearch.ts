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

class SearchSelectionMenuHiddenModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('searchSelectionMenuHidden');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSelectionMenuHidden(node);
    } else {
      getUINativeModule().search.setSelectionMenuHidden(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class SearchCaretStyleModifier extends ModifierWithKey<CaretStyle> {
  constructor(value: CaretStyle) {
    super(value);
  }
  static identity = Symbol('searchCaretStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetCaretStyle(node);
    } else {
      getUINativeModule().search.setCaretStyle(node, this.value.width,
        this.value.color);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
  }
}

class SearchEnableKeyboardOnFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('searchEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetEnableKeyboardOnFocus(node);
    } else {
      getUINativeModule().search.setEnableKeyboardOnFocus(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class SearchSearchIconModifier extends ModifierWithKey<IconOptions> {
  constructor(value: IconOptions) {
    super(value);
  }
  static identity = Symbol('searchSearchIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSearchIcon(node);
    } else {
      getUINativeModule().search.setSearchIcon(node, this.value.size,
        this.value.color, this.value.src);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.src, this.value.src);
  }
}

class SearchPlaceholderFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity = Symbol('searchPlaceholderFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetPlaceholderFont(node);
    } else {
      getUINativeModule().search.setPlaceholderFont(node, this.value.size,
        this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue.weight !== this.value.weight ||
      this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
  }
}

class SearchSearchButtonModifier extends ModifierWithKey<ArkSearchButton> {
  constructor(value: ArkSearchButton) {
    super(value);
  }
  static identity = Symbol('searchSearchButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSearchButton(node);
    } else {
      getUINativeModule().search.setSearchButton(node, this.value.value,
        this.value.fontSize, this.value.fontColor, this.value.autoDisable);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue.value !== this.value.value ||
      !isBaseOrResourceEqual(this.stageValue.fontSize, this.value.fontSize) ||
      !isBaseOrResourceEqual(this.stageValue.fontColor, this.value.fontColor) ||
      !isBaseOrResourceEqual(this.stageValue.autoDisable, this.value.autoDisable);
  }
}

class SearchFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity = Symbol('searchFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetFontColor(node);
    } else {
      getUINativeModule().search.setFontColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchCopyOptionModifier extends ModifierWithKey<CopyOptions> {
  constructor(value: CopyOptions) {
    super(value);
  }
  static identity = Symbol('searchCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetCopyOption(node);
    } else {
      getUINativeModule().search.setCopyOption(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class SearchTextFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity = Symbol('searchTextFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetTextFont(node);
    } else {
      getUINativeModule().search.setTextFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue.weight !== this.value.weight ||
      this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
  }
}

class SearchPlaceholderColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity = Symbol('searchPlaceholderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetPlaceholderColor(node);
    } else {
      getUINativeModule().search.setPlaceholderColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchCancelButtonModifier extends ModifierWithKey<{ style?: CancelButtonStyle, icon?: IconOptions }> {
  constructor(value: { style?: CancelButtonStyle, icon?: IconOptions }) {
    super(value);
  }
  static identity = Symbol('searchCancelButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetCancelButton(node);
    } else {
      getUINativeModule().search.setCancelButton(node, this.value.style,
        this.value.icon?.size, this.value.icon?.color, this.value.icon?.src);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual(this.stageValue.icon?.size, this.value.icon?.size) ||
      !isBaseOrResourceEqual(this.stageValue.icon?.color, this.value.icon?.color) ||
      !isBaseOrResourceEqual(this.stageValue.icon?.src, this.value.icon?.src);
  }
}

class SearchTextAlignModifier extends ModifierWithKey<TextAlign> {
  constructor(value: TextAlign) {
    super(value);
  }
  static identity = Symbol('searchTextAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetTextAlign(node);
    } else {
      getUINativeModule().search.setTextAlign(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class SearchEnterKeyTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('searchEnterKeyType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSearchEnterKeyType(node);
    } else {
      getUINativeModule().search.setSearchEnterKeyType(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('searchHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSearchHeight(node);
    } else {
      getUINativeModule().search.setSearchHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchIdModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('searchId');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSearchInspectorId(node);
    } else {
      getUINativeModule().search.setSearchInspectorId(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchDecorationModifier extends ModifierWithKey<{ type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }> {
  constructor(value: { type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }) {
    super(value);
  }
  static identity: Symbol = Symbol('searchDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetDecoration(node);
    } else {
      getUINativeModule().search.setDecoration(node, this.value!.type, this.value!.color, this.value!.style);
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

class SearchLetterSpacingModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('searchLetterSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetLetterSpacing(node);
    } else {
      getUINativeModule().search.setLetterSpacing(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SearchMinFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('searchMinFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSearchMinFontSize(node);
    } else {
      getUINativeModule().search.setSearchMinFontSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchLineHeightModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('searchLineHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetLineHeight(node);
    } else {
      getUINativeModule().search.setLineHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchHalfLeadingModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('searchHalfLeading');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetHalfLeading(node);
    } else {
      getUINativeModule().search.setHalfLeading(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchMaxFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('searchMaxFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSearchMaxFontSize(node);
    } else {
      getUINativeModule().search.setSearchMaxFontSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchMinFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('searchMinFontScale');
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

class SearchMaxFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('searchMaxFontScale');
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

class SearchFontFeatureModifier extends ModifierWithKey<FontFeature> {
  constructor(value: FontFeature) {
    super(value);
  }
  static identity: Symbol = Symbol('searchFontFeature');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetFontFeature(node);
    } else {
      getUINativeModule().search.setFontFeature(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchSelectedBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('searchSelectedBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().search.setSelectedBackgroundColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchInputFilterModifier extends ModifierWithKey<ArkSearchInputFilter> {
  constructor(value: ArkSearchInputFilter) {
    super(value);
  }
  static identity: Symbol = Symbol('searchInputFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetInputFilter(node);
    } else {
      getUINativeModule().search.setInputFilter(node, this.value.value, this.value.error);
    }
  }
}
class SearchTextIndentModifier extends ModifierWithKey<Dimension> {
  constructor(value: Dimension) {
    super(value);
  }
  static identity: Symbol = Symbol('searchTextIndent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetTextIndent(node);
    } else {
      getUINativeModule().search.setTextIndent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SearchMaxLengthModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('searchMaxLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetMaxLength(node);
    } else {
      getUINativeModule().search.setMaxLength(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('searchType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetType(node);
    } else {
      getUINativeModule().search.setType(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchOnEditChangeModifier extends ModifierWithKey<(isEditing: boolean) => void> {
  constructor(value: (isEditing: boolean) => void) {
    super(value);
  }
  static identity = Symbol('searchOnEditChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnEditChange(node);
    } else {
      getUINativeModule().search.setOnEditChange(node, this.value);
    }
  }
}

class SearchOnSubmitModifier extends ModifierWithKey<(info: string, event?: SubmitEvent) => void> {
  constructor(value: (info: string, event?: SubmitEvent) => void) {
    super(value);
  }
  static identity = Symbol('searchOnSubmit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnSubmit(node);
    } else {
      getUINativeModule().search.setOnSubmit(node, this.value);
    }
  }
}

class SearchOnCopyModifier extends ModifierWithKey<(value: string) => void> {
  constructor(value: (value: string) => void) {
    super(value);
  }
  static identity = Symbol('searchOnCopy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnCopy(node);
    } else {
      getUINativeModule().search.setOnCopy(node, this.value);
    }
  }
}

class SearchOnCutModifier extends ModifierWithKey<(value: string) => void> {
  constructor(value: (value: string) => void) {
    super(value);
  }
  static identity = Symbol('searchOnCut');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnCut(node);
    } else {
      getUINativeModule().search.setOnCut(node, this.value);
    }
  }
}

class SearchOnPasteModifier extends ModifierWithKey<(value: string, event: PasteEvent) => void> {
  constructor(value: (value: string, event: PasteEvent) => void) {
    super(value);
  }
  static identity = Symbol('searchOnPaste');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnPaste(node);
    } else {
      getUINativeModule().search.setOnPaste(node, this.value);
    }
  }
}

class SearchOnChangeModifier extends ModifierWithKey<(value: ChangeValueInfo) => void> {
  constructor(value: (value: ChangeValueInfo) => void) {
    super(value);
  }
  static identity = Symbol('searchOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnChange(node);
    } else {
      getUINativeModule().search.setOnChange(node, this.value);
    }
  }
}

class SearchOnTextSelectionChangeModifier extends ModifierWithKey<(selectionStart: number, selectionEnd: number) => void> {
  constructor(value: (selectionStart: number, selectionEnd: number) => void) {
    super(value);
  }
  static identity = Symbol('searchOnTextSelectionChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnTextSelectionChange(node);
    } else {
      getUINativeModule().search.setOnTextSelectionChange(node, this.value);
    }
  }
}

class SearchOnContentScrollModifier extends ModifierWithKey<(totalOffsetX: number, totalOffsetY: number) => void> {
  constructor(value: (totalOffsetX: number, totalOffsetY: number) => void) {
    super(value);
  }
  static identity = Symbol('searchOnContentScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnContentScroll(node);
    } else {
      getUINativeModule().search.setOnContentScroll(node, this.value);
    }
  }
}

class SearchShowCounterModifier extends ModifierWithKey<ArkTextFieldShowCounter> {
  constructor(value: ArkTextFieldShowCounter) {
    super(value);
  }
  static identity = Symbol('searchShowCounter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetShowCounter(node);
    }
    else {
      getUINativeModule().search.setShowCounter(node, this.value.value!, this.value.highlightBorder, this.value.thresholdPercentage);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.highlightBorder, this.value.highlightBorder) ||
      !isBaseOrResourceEqual(this.stageValue.thresholdPercentage, this.value.thresholdPercentage);
  }
}

class SearchInitializeModifier extends ModifierWithKey<SearchParam> {
  constructor(value: SearchParam) {
    super(value);
  }
  static identity: Symbol = Symbol('searchInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSearchInitialize(node);
    } else {
      getUINativeModule().search.setSearchInitialize(node, this.value.value,
        this.value.placeholder, this.value.icon, this.value.controller);
    }
  }
}

class SearchOnWillChangeModifier extends ModifierWithKey<Callback<ChangeValueInfo, boolean>> {
  constructor(value: Callback<ChangeValueInfo, boolean>) {
    super(value);
  }
  static identity = Symbol('searchOnWillChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnWillChange(node);
    } else {
      getUINativeModule().search.setOnWillChange(node, this.value);
    }
  }
}

class SearchOnWillInsertModifier extends ModifierWithKey<Callback<InsertValue, boolean>> {
  constructor(value: Callback<InsertValue, boolean>) {
    super(value);
  }
  static identity = Symbol('searchOnWillInsert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnWillInsert(node);
    } else {
      getUINativeModule().search.setOnWillInsert(node, this.value);
    }
  }
}

class SearchOnDidInsertModifier extends ModifierWithKey<Callback<InsertValue>> {
  constructor(value: Callback<InsertValue>) {
    super(value);
  }
  static identity = Symbol('searchOnDidInsert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnDidInsert(node);
    } else {
      getUINativeModule().search.setOnDidInsert(node, this.value);
    }
  }
}

class SearchOnWillDeleteModifier extends ModifierWithKey<Callback<DeleteValue, boolean>> {
  constructor(value: Callback<DeleteValue, boolean>) {
    super(value);
  }
  static identity = Symbol('searchOnWillDelete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnWillDelete(node);
    } else {
      getUINativeModule().search.setOnWillDelete(node, this.value);
    }
  }
}

class SearchOnDidDeleteModifier extends ModifierWithKey<Callback<DeleteValue>> {
  constructor(value: Callback<DeleteValue>) {
    super(value);
  }
  static identity = Symbol('searchOnDidDelete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetOnDidDelete(node);
    } else {
      getUINativeModule().search.setOnDidDelete(node, this.value);
    }
  }
}

class SearchEnablePreviewTextModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('searchEnablePreviewText');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetEnablePreviewText(node);
    } else {
      getUINativeModule().search.setEnablePreviewText(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SearchEditMenuOptionsModifier extends ModifierWithKey<EditMenuOptions> {
  constructor(value: EditMenuOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textEditMenuOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetSelectionMenuOptions(node);
    } else {
      getUINativeModule().search.setSelectionMenuOptions(node, this.value);
    }
  }
}

class SearchEnableHapticFeedbackModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('searchEnableHapticFeedback');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetEnableHapticFeedback(node);
    } else {
      getUINativeModule().search.setEnableHapticFeedback(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

interface SearchParam {
  value?: string;
  placeholder?: ResourceStr;
  icon?: string;
  controller?: SearchController
}

class ArkSearchComponent extends ArkComponent implements CommonMethod<SearchAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): SearchAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, SearchInitializeModifier.identity,
        SearchInitializeModifier, (value[0] as SearchParam));
    } else {
      modifierWithKey(this._modifiersWithKeys, SearchInitializeModifier.identity,
        SearchInitializeModifier, null);
    }
    return this;
  }
  onEditChange(callback: (isEditing: boolean) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnEditChangeModifier.identity,
      SearchOnEditChangeModifier, callback);
    return this;
  }
  type(value: SearchType): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchTypeModifier.identity,
      SearchTypeModifier, value);
    return this;
  }
  maxLength(value: number): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchMaxLengthModifier.identity,
      SearchMaxLengthModifier, value);
    return this;
  }
  onEditChanged(callback: (isEditing: boolean) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnEditChangeModifier.identity,
      SearchOnEditChangeModifier, callback);
    return this;
  }
  customKeyboard(event: () => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  showUnit(event: () => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnContentScrollModifier.identity,
      SearchOnContentScrollModifier, callback);
    return this;
  }
  onChange(callback: (value: ChangeValueInfo) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnChangeModifier.identity,
      SearchOnChangeModifier, callback);
    return this;
  }
  onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnTextSelectionChangeModifier.identity,
      SearchOnTextSelectionChangeModifier, callback);
    return this;
  }
  onCopy(callback: (value: string) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnCopyModifier.identity,
      SearchOnCopyModifier, callback);
    return this;
  }
  onCut(callback: (value: string) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnCutModifier.identity,
      SearchOnCutModifier, callback);
    return this;
  }
  onSubmit(callback: (value: string, event?: SubmitEvent) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnSubmitModifier.identity,
      SearchOnSubmitModifier, callback);
    return this;
  }
  onPaste(callback: (value: string) => void): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchOnPasteModifier.identity,
      SearchOnPasteModifier, callback);
    return this;
  }
  showCounter(value: boolean, options?: InputCounterOptions): SearchAttribute {
    let arkValue: ArkTextFieldShowCounter = new ArkTextFieldShowCounter();
    arkValue.value = value;
    arkValue.highlightBorder = options?.highlightBorder;
    arkValue.thresholdPercentage = options?.thresholdPercentage;
    modifierWithKey(this._modifiersWithKeys, SearchShowCounterModifier.identity,
      SearchShowCounterModifier, arkValue);
    return this;
  }
  searchButton(value: string, option?: SearchButtonOptions): SearchAttribute {
    let searchButton = new ArkSearchButton();
    searchButton.value = value;
    searchButton.fontColor = option?.fontColor;
    searchButton.fontSize = option?.fontSize;
    searchButton.autoDisable = option?.autoDisable;
    modifierWithKey(this._modifiersWithKeys, SearchSearchButtonModifier.identity, SearchSearchButtonModifier, searchButton);
    return this;
  }
  selectionMenuHidden(value: boolean): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchSelectionMenuHiddenModifier.identity, SearchSelectionMenuHiddenModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value: boolean): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchEnableKeyboardOnFocusModifier.identity, SearchEnableKeyboardOnFocusModifier, value);
    return this;
  }
  caretStyle(value: CaretStyle): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchCaretStyleModifier.identity, SearchCaretStyleModifier, value);
    return this;
  }
  cancelButton(value: { style?: CancelButtonStyle, icon?: IconOptions }): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchCancelButtonModifier.identity, SearchCancelButtonModifier, value);
    return this;
  }
  searchIcon(value: IconOptions): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchSearchIconModifier.identity, SearchSearchIconModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchFontColorModifier.identity, SearchFontColorModifier, value);
    return this;
  }
  placeholderColor(value: ResourceColor): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchPlaceholderColorModifier.identity, SearchPlaceholderColorModifier, value);
    return this;
  }
  placeholderFont(value?: Font): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchPlaceholderFontModifier.identity, SearchPlaceholderFontModifier, value);
    return this;
  }
  textFont(value?: Font): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchTextFontModifier.identity, SearchTextFontModifier, value);
    return this;
  }
  copyOption(value: CopyOptions): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchCopyOptionModifier.identity, SearchCopyOptionModifier, value);
    return this;
  }
  textAlign(value: TextAlign): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchTextAlignModifier.identity, SearchTextAlignModifier, value);
    return this;
  }
  enterKeyType(value: EnterKeyType): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchEnterKeyTypeModifier.identity,
      SearchEnterKeyTypeModifier, value);
    return this;
  }
  fontFeature(value: FontFeature): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchFontFeatureModifier.identity, SearchFontFeatureModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, SearchHeightModifier.identity, SearchHeightModifier, value);
    return this;
  }
  id(value: string): this {
    modifierWithKey(this._modifiersWithKeys, SearchIdModifier.identity, SearchIdModifier, value);
    return this;
  }
  key(value: string): this {
    modifierWithKey(this._modifiersWithKeys, SearchIdModifier.identity, SearchIdModifier, value);
    return this;
  }
  decoration(value: { type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }): this {
    modifierWithKey(this._modifiersWithKeys, SearchDecorationModifier.identity, SearchDecorationModifier, value);
    return this;
  }
  letterSpacing(value: number | string): this {
    modifierWithKey(this._modifiersWithKeys, SearchLetterSpacingModifier.identity, SearchLetterSpacingModifier, value);
    return this;
  }
  lineHeight(value: number | string | Resource): this {
    modifierWithKey(this._modifiersWithKeys, SearchLineHeightModifier.identity, SearchLineHeightModifier, value);
    return this;
  }
  halfLeading(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SearchHalfLeadingModifier.identity, SearchHalfLeadingModifier, value);
    return this;
  }
  minFontSize(value: number | string | Resource): this {
    modifierWithKey(this._modifiersWithKeys, SearchMinFontSizeModifier.identity, SearchMinFontSizeModifier, value);
    return this;
  }
  maxFontSize(value: number | string | Resource): this {
    modifierWithKey(this._modifiersWithKeys, SearchMaxFontSizeModifier.identity, SearchMaxFontSizeModifier, value);
    return this;
  }
  minFontScale(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, SearchMinFontScaleModifier.identity, SearchMinFontScaleModifier, value);
    return this;
  }
  maxFontScale(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, SearchMaxFontScaleModifier.identity, SearchMaxFontScaleModifier, value);
    return this;
  }
  selectedBackgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, SearchSelectedBackgroundColorModifier.identity, SearchSelectedBackgroundColorModifier, value);
    return this;
  }
  textIndent(value: Dimension): this {
    modifierWithKey(this._modifiersWithKeys, SearchTextIndentModifier.identity, SearchTextIndentModifier, value);
    return this;
  }
  inputFilter(value: ResourceStr, error?: (value: string) => void): this {
    let searchInputFilter = new ArkSearchInputFilter();
    searchInputFilter.value = value;
    searchInputFilter.error = error;
    modifierWithKey(this._modifiersWithKeys, SearchInputFilterModifier.identity, SearchInputFilterModifier, searchInputFilter);
    return this;
  }
  onWillChange(callback: Callback<ChangeValueInfo, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, SearchOnWillChangeModifier.identity, SearchOnWillChangeModifier, callback);
    return this;
  }
  onWillInsert(callback: Callback<InsertValue, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, SearchOnWillInsertModifier.identity, SearchOnWillInsertModifier, callback);
    return this;
  }
  onDidInsert(callback: Callback<InsertValue>): this {
    modifierWithKey(this._modifiersWithKeys, SearchOnDidInsertModifier.identity, SearchOnDidInsertModifier, callback);
    return this;
  }
  onWillDelete(callback: Callback<DeleteValue, boolean>): this {
    modifierWithKey(this._modifiersWithKeys, SearchOnWillDeleteModifier.identity, SearchOnWillDeleteModifier, callback);
    return this;
  }
  onDidDelete(callback: Callback<DeleteValue>): this {
    modifierWithKey(this._modifiersWithKeys, SearchOnDidDeleteModifier.identity, SearchOnDidDeleteModifier, callback);
    return this;
  }
  enablePreviewText(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SearchEnablePreviewTextModifier.identity, SearchEnablePreviewTextModifier, value);
    return this;
  }
  editMenuOptions(value: EditMenuOptions): this {
    modifierWithKey(this._modifiersWithKeys, SearchEditMenuOptionsModifier.identity,
      SearchEditMenuOptionsModifier, value);
    return this;
  }
  enableHapticFeedback(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SearchEnableHapticFeedbackModifier.identity, SearchEnableHapticFeedbackModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Search.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkSearchComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.SearchModifier(nativePtr, classType);
  });
};
