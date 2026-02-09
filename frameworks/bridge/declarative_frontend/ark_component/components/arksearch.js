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

/// <reference path='./import.ts' />
class SearchSelectionMenuHiddenModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSelectionMenuHidden(node);
    }
    else {
      getUINativeModule().search.setSelectionMenuHidden(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchSelectionMenuHiddenModifier.identity = Symbol('searchSelectionMenuHidden');
class SearchAutoCapitalizationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchAutoCapitalizationMode(node);
    }
    else {
      getUINativeModule().search.setSearchAutoCapitalizationMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchAutoCapitalizationModifier.identity = Symbol('SearchAutoCapitalization');
class SearchCaretStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetCaretStyle(node);
    }
    else {
      getUINativeModule().search.setCaretStyle(node, this.value.width, this.value.color);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
  }
}
SearchCaretStyleModifier.identity = Symbol('searchCaretStyle');
class SearchEnableKeyboardOnFocusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetEnableKeyboardOnFocus(node);
    }
    else {
      getUINativeModule().search.setEnableKeyboardOnFocus(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchEnableKeyboardOnFocusModifier.identity = Symbol('searchEnableKeyboardOnFocus');
class SearchSearchIconModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchIcon(node);
    }
    else {
      getUINativeModule().search.setSearchIcon(node, this.value.size, this.value.color, this.value.src);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.src, this.value.src);
  }
}
SearchSearchIconModifier.identity = Symbol('searchSearchIcon');
class SearchPlaceholderFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetPlaceholderFont(node);
    }
    else {
      getUINativeModule().search.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    return this.stageValue.weight !== this.value.weight ||
      this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
  }
}
SearchPlaceholderFontModifier.identity = Symbol('searchPlaceholderFont');
class SearchSearchButtonModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchButton(node);
    }
    else {
      getUINativeModule().search.setSearchButton(node, this.value.value, this.value.fontSize, this.value.fontColor,
        this.value.autoDisable);
    }
  }
  checkObjectDiff() {
    return this.stageValue.value !== this.value.value ||
      !isBaseOrResourceEqual(this.stageValue.fontSize, this.value.fontSize) ||
      !isBaseOrResourceEqual(this.stageValue.fontColor, this.value.fontColor) ||
      !isBaseOrResourceEqual(this.stageValue.autoDisable, this.value.autoDisable);
  }
}
SearchSearchButtonModifier.identity = Symbol('searchSearchButton');
class SearchDividerColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchDividerColor(node);
    } else {
      getUINativeModule().search.setSearchDividerColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchDividerColorModifier.identity = Symbol('dividerColor');
class SearchFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetFontColor(node);
    }
    else {
      getUINativeModule().search.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchFontColorModifier.identity = Symbol('searchFontColor');
class SearchFontFeatureModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetFontFeature(node);
    } else {
      getUINativeModule().search.setFontFeature(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchFontFeatureModifier.identity = Symbol('searchFontFeature');
class SearchCopyOptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetCopyOption(node);
    }
    else {
      getUINativeModule().search.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchCopyOptionModifier.identity = Symbol('searchCopyOption');
class SearchTextFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetTextFont(node);
    }
    else {
      getUINativeModule().search.setTextFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    return this.stageValue.weight !== this.value.weight ||
      this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
  }
}
SearchTextFontModifier.identity = Symbol('searchTextFont');
class SearchPlaceholderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetPlaceholderColor(node);
    }
    else {
      getUINativeModule().search.setPlaceholderColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchPlaceholderColorModifier.identity = Symbol('searchPlaceholderColor');
class SearchCancelButtonModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      getUINativeModule().search.resetCancelButton(node);
    }
    else {
      getUINativeModule().search.setCancelButton(node, this.value.style,
        (_a = this.value.icon) === null || _a === void 0 ? void 0 : _a.size,
        (_b = this.value.icon) === null || _b === void 0 ? void 0 : _b.color,
        (_c = this.value.icon) === null || _c === void 0 ? void 0 : _c.src);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f;
    return this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual((_a = this.stageValue.icon) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.icon) === null || _b === void 0 ? void 0 : _b.size) ||
      !isBaseOrResourceEqual((_c = this.stageValue.icon) === null || _c === void 0 ? void 0 : _c.color, (_d = this.value.icon) === null || _d === void 0 ? void 0 : _d.color) ||
      !isBaseOrResourceEqual((_e = this.stageValue.icon) === null || _e === void 0 ? void 0 : _e.src, (_f = this.value.icon) === null || _f === void 0 ? void 0 : _f.src);
  }
}
SearchCancelButtonModifier.identity = Symbol('searchCancelButton');
class SearchTextAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchTextAlign(node);
    }
    else {
      getUINativeModule().search.setSearchTextAlign(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchTextAlignModifier.identity = Symbol('searchTextAlign');
class SearchEnterKeyTypeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchEnterKeyType(node);
    } else {
      getUINativeModule().search.setSearchEnterKeyType(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchEnterKeyTypeModifier.identity = Symbol('searchEnterKeyType');
class SearchHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchHeight(node);
    } else {
      getUINativeModule().search.setSearchHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchHeightModifier.identity = Symbol('searchHeight');

class SearchIdModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchInspectorId(node);
    } else {
      getUINativeModule().search.setSearchInspectorId(node, this.value);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchIdModifier.identity = Symbol('searchId');
class SearchDecorationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetDecoration(node);
    }
    else {
      getUINativeModule().search.setDecoration(node, this.value.type, this.value.color, this.value.style);
    }
  }
  checkObjectDiff() {
    if (this.stageValue.type !== this.value.type || this.stageValue.style !== this.value.style) {
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
SearchDecorationModifier.identity = Symbol('searchDecoration');
class SearchLetterSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetLetterSpacing(node);
    }
    else {
      getUINativeModule().search.setLetterSpacing(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchLetterSpacingModifier.identity = Symbol('searchLetterSpacing');
class SearchLineHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetLineHeight(node);
    }
    else {
      getUINativeModule().search.setLineHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchLineHeightModifier.identity = Symbol('searchLineHeight');
class SearchHalfLeadingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetHalfLeading(node);
    }
    else {
      getUINativeModule().search.setHalfLeading(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchHalfLeadingModifier.identity = Symbol('searchHalfLeading');
class SearchMinFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchMinFontSize(node);
    }
    else {
      getUINativeModule().search.setSearchMinFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

SearchMinFontSizeModifier.identity = Symbol('searchMinFontSize');
class SearchMaxFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchMaxFontSize(node);
    }
    else {
      getUINativeModule().search.setSearchMaxFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchMaxFontSizeModifier.identity = Symbol('searchMaxFontSize');
class SearchMinFontScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetMinFontScale(node);
    }
    else {
      getUINativeModule().search.setMinFontScale(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchMinFontScaleModifier.identity = Symbol('searchMinFontScale');
class SearchMaxFontScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetMaxFontScale(node);
    }
    else {
      getUINativeModule().search.setMaxFontScale(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchMaxFontScaleModifier.identity = Symbol('searchMaxFontScale');
class SearchSelectedBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().search.setSelectedBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchSelectedBackgroundColorModifier.identity = Symbol('searchSelectedBackgroundColor');
class SearchTextIndentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetTextIndent(node);
    } else {
      getUINativeModule().search.setTextIndent(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchTextIndentModifier.identity = Symbol('searchTextIndent');
class SearchInputFilterModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetInputFilter(node);
    } else {
      getUINativeModule().search.setInputFilter(node, this.value.value, this.value.error);
    }
  }
}
SearchInputFilterModifier.identity = Symbol('searchInputFilter');
class SearchMaxLengthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetMaxLength(node);
    } else {
      getUINativeModule().search.setMaxLength(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchMaxLengthModifier.identity = Symbol('searchMaxLength');
class SearchTypeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetType(node);
    } else {
      getUINativeModule().search.setType(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchTypeModifier.identity = Symbol('searchType');
class SearchCustomKeyboardModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetCustomKeyboard(node);
    } else {
      getUINativeModule().search.setCustomKeyboard(node, this.value.value, this.value.supportAvoidance);
    }
  }
}
SearchCustomKeyboardModifier.identity = Symbol('searchCustomKeyboard');
class SearchOnEditChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnEditChange(node);
    } else {
      getUINativeModule().search.setOnEditChange(node, this.value);
    }
  }
}
SearchOnEditChangeModifier.identity = Symbol('searchOnEditChange');
class SearchOnSubmitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnSubmit(node);
    } else {
      getUINativeModule().search.setOnSubmit(node, this.value);
    }
  }
}
SearchOnSubmitModifier.identity = Symbol('searchOnSubmit');
class SearchOnCopyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnCopy(node);
    } else {
      getUINativeModule().search.setOnCopy(node, this.value);
    }
  }
}
SearchOnCopyModifier.identity = Symbol('searchOnCopy');
class SearchOnCutModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnCut(node);
    } else {
      getUINativeModule().search.setOnCut(node, this.value);
    }
  }
}
SearchOnCutModifier.identity = Symbol('searchOnCut');
class SearchOnPasteModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  static identity = Symbol('searchOnPaste');
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnPaste(node);
    } else {
      getUINativeModule().search.setOnPaste(node, this.value);
    }
  }
}
SearchOnPasteModifier.identity = Symbol('searchOnPaste');
class SearchOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnChange(node);
    } else {
      getUINativeModule().search.setOnChange(node, this.value);
    }
  }
}
SearchOnChangeModifier.identity = Symbol('searchOnChange');
class SearchOnTextSelectionChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnTextSelectionChange(node);
    } else {
      getUINativeModule().search.setOnTextSelectionChange(node, this.value);
    }
  }
}
SearchOnTextSelectionChangeModifier.identity = Symbol('searchOnTextSelectionChange');
class SearchOnContentScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnContentScroll(node);
    } else {
      getUINativeModule().search.setOnContentScroll(node, this.value);
    }
  }
}
SearchOnContentScrollModifier.identity = Symbol('searchOnContentScroll');
class SearchShowCounterModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetShowCounter(node);
    }
    else {
      getUINativeModule().search.setShowCounter(node, this.value.value, this.value.highlightBorder, this.value.thresholdPercentage);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.highlightBorder, this.value.highlightBorder) ||
      !isBaseOrResourceEqual(this.stageValue.thresholdPercentage, this.value.thresholdPercentage);
  }
}
SearchShowCounterModifier.identity = Symbol('searchShowCounter');
class SearchInitializeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchInitialize(node);
    } else {
      getUINativeModule().search.setSearchInitialize(node, this.value.value,
        this.value.placeholder, this.value.icon, this.value.controller);
    }
  }
}
SearchInitializeModifier.identity = Symbol('searchInitialize');
class SearchOnWillChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnWillChange(node);
    } else {
      getUINativeModule().search.setOnWillChange(node, this.value);
    }
  }
}
SearchOnWillChangeModifier.identity = Symbol('searchOnWillChange');
class SearchOnWillInsertModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnWillInsert(node);
    } else {
      getUINativeModule().search.setOnWillInsert(node, this.value);
    }
  }
}
SearchOnWillInsertModifier.identity = Symbol('searchOnWillInsert');
class SearchOnDidInsertModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnDidInsert(node);
    } else {
      getUINativeModule().search.setOnDidInsert(node, this.value);
    }
  }
}
SearchOnDidInsertModifier.identity = Symbol('searchOnDidInsert');
class SearchOnWillDeleteModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnWillDelete(node);
    } else {
      getUINativeModule().search.setOnWillDelete(node, this.value);
    }
  }
}
SearchOnWillDeleteModifier.identity = Symbol('searchOnWillDelete');
class SearchOnDidDeleteModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnDidDelete(node);
    } else {
      getUINativeModule().search.setOnDidDelete(node, this.value);
    }
  }
}
SearchOnDidDeleteModifier.identity = Symbol('searchOnDidDelete');
class SearchEnablePreviewTextModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetEnablePreviewText(node);
    }
    else {
      getUINativeModule().search.setEnablePreviewText(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchEnablePreviewTextModifier.identity = Symbol('searchEnablePreviewText');
class SearchEditMenuOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSelectionMenuOptions(node);
    } else {
      getUINativeModule().search.setSelectionMenuOptions(node, this.value);
    }
  }
}
SearchEditMenuOptionsModifier.identity = Symbol('searchEditMenuOptions');
class SearchEnableHapticFeedbackModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetEnableHapticFeedback(node);
    }
    else {
      getUINativeModule().search.setEnableHapticFeedback(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchEnableHapticFeedbackModifier.identity = Symbol('searchEnableHapticFeedback');

class SearchStopBackPressModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetStopBackPress(node);
    }
    else {
      getUINativeModule().search.setStopBackPress(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchStopBackPressModifier.identity = Symbol('searchStopBackPress');

class SearchKeyboardAppearanceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetKeyboardAppearance(node);
    }
    else {
      getUINativeModule().search.setKeyboardAppearance(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchKeyboardAppearanceModifier.identity = Symbol('searchKeyboardAppearance');

class SearchStrokeWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetStrokeWidth(node);
    }
    else if (!isObject(this.value)) {
      getUINativeModule().search.resetStrokeWidth(node);
    }
    else {
      getUINativeModule().search.setStrokeWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchStrokeWidthModifier.identity = Symbol('searchStrokeWidth');

class SearchStrokeColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetStrokeColor(node);
    }
    else {
      getUINativeModule().search.setStrokeColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchStrokeColorModifier.identity = Symbol('searchStrokeColor');

class SearchEnableAutoSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetEnableAutoSpacing(node);
    }
    else {
      getUINativeModule().search.setEnableAutoSpacing(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchEnableAutoSpacingModifier.identity = Symbol('searchEnableAutoSpacing');

class SearchCompressLeadingPunctuationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetCompressLeadingPunctuation(node);
    }
    else {
      getUINativeModule().search.setCompressLeadingPunctuation(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchCompressLeadingPunctuationModifier.identity = Symbol('searchCompressLeadingPunctuation');

class SearchIncludeFontPaddingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetIncludeFontPadding(node);
    }
    else {
      getUINativeModule().search.setIncludeFontPadding(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchIncludeFontPaddingModifier.identity = Symbol('searchIncludeFontPadding');

class SearchFallbackLineSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetFallbackLineSpacing(node);
    }
    else {
      getUINativeModule().search.setFallbackLineSpacing(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchFallbackLineSpacingModifier.identity = Symbol('searchIncludeFontPadding');

class SearchMarginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetMargin(node);
    }
    else {
      getUINativeModule().search.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}
SearchMarginModifier.identity = Symbol('searchMargin');

class SearchSelectDetectorEnableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSelectDetectorEnable(node);
    } else {
      getUINativeModule().search.setSelectDetectorEnable(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchSelectDetectorEnableModifier.identity = Symbol('searchSelectDetectorEnable');
class SearchOnWillAttachIMEModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetOnWillAttachIME(node);
    } else {
      getUINativeModule().search.setOnWillAttachIME(node, this.value);
    }
  }
}
SearchOnWillAttachIMEModifier.identity = Symbol('searchOnWillAttachIME');

class SearchTextDirectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetTextDirection(node);
    }
    else {
      getUINativeModule().search.setTextDirection(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchTextDirectionModifier.identity = Symbol('searchTextDirection');

class SearchSelectedDragPreviewStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSelectedDragPreviewStyle(node);
    }
    else {
      getUINativeModule().search.setSelectedDragPreviewStyle(node, this.value.color);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
  }
}
SearchSelectedDragPreviewStyleModifier.identity = Symbol('searchSelectedDragPreviewStyle');

class ArkSearchComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, SearchInitializeModifier.identity, SearchInitializeModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, SearchInitializeModifier.identity, SearchInitializeModifier, null);
    }
    return this;
  }
  onEditChange(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnEditChangeModifier.identity, SearchOnEditChangeModifier, callback);
    return this;
  }
  type(value) {
    modifierWithKey(this._modifiersWithKeys, SearchTypeModifier.identity, SearchTypeModifier, value);
    return this;
  }
  maxLength(value) {
    modifierWithKey(this._modifiersWithKeys, SearchMaxLengthModifier.identity, SearchMaxLengthModifier, value);
    return this;
  }
  onEditChanged(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnEditChangeModifier.identity, SearchOnEditChangeModifier, callback);
    return this;
  }
  customKeyboard(value, options) {
    let arkValue = new ArkCustomKeyboard();
    arkValue.value = value;
    arkValue.supportAvoidance = options?.supportAvoidance;
    modifierWithKey(this._modifiersWithKeys, SearchCustomKeyboardModifier.identity,
      SearchCustomKeyboardModifier, arkValue);
    return this;
  }
  showUnit(event) {
    throw new BusinessError(100201, 'showUnit function not supported in attributeModifier scenario.');
  }
  onContentScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnContentScrollModifier.identity,
      SearchOnContentScrollModifier, callback);
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnChangeModifier.identity, SearchOnChangeModifier, callback);
    return this;
  }
  onTextSelectionChange(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnTextSelectionChangeModifier.identity,
      SearchOnTextSelectionChangeModifier, callback);
    return this;
  }
  onCopy(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnCopyModifier.identity, SearchOnCopyModifier, callback);
    return this;
  }
  onCut(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnCutModifier.identity, SearchOnCutModifier, callback);
    return this;
  }
  onSubmit(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnSubmitModifier.identity, SearchOnSubmitModifier, callback);
    return this;
  }
  onPaste(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnPasteModifier.identity, SearchOnPasteModifier, callback);
    return this;
  }
  enableSelectedDataDetector(value) {
    modifierWithKey(this._modifiersWithKeys, SearchSelectDetectorEnableModifier.identity, SearchSelectDetectorEnableModifier, value);
    return this;
  }
  showCounter(value) {
    let arkValue = new ArkTextFieldShowCounter();
    arkValue.value = value;
    arkValue.highlightBorder = options?.highlightBorder;
    arkValue.thresholdPercentage = options?.thresholdPercentage;
    modifierWithKey(this._modifiersWithKeys, SearchShowCounterModifier.identity,
      SearchShowCounterModifier, arkValue);
    return this;
  }
  searchButton(value, option) {
    let searchButton = new ArkSearchButton();
    searchButton.value = value;
    searchButton.fontColor = option === null || option === void 0 ? void 0 : option.fontColor;
    searchButton.fontSize = option === null || option === void 0 ? void 0 : option.fontSize;
    searchButton.autoDisable = option === null || option === void 0 ? void 0 : option.autoDisable;
    modifierWithKey(this._modifiersWithKeys, SearchSearchButtonModifier.identity, SearchSearchButtonModifier, searchButton);
    return this;
  }
  dividerColor(value) {
    modifierWithKey(this._modifiersWithKeys, SearchDividerColorModifier.identity, SearchDividerColorModifier, value);
    return this;
  }
  selectionMenuHidden(value) {
    modifierWithKey(this._modifiersWithKeys, SearchSelectionMenuHiddenModifier.identity, SearchSelectionMenuHiddenModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value) {
    modifierWithKey(this._modifiersWithKeys, SearchEnableKeyboardOnFocusModifier.identity, SearchEnableKeyboardOnFocusModifier, value);
    return this;
  }
  caretStyle(value) {
    modifierWithKey(this._modifiersWithKeys, SearchCaretStyleModifier.identity, SearchCaretStyleModifier, value);
    return this;
  }
  cancelButton(value) {
    modifierWithKey(this._modifiersWithKeys, SearchCancelButtonModifier.identity, SearchCancelButtonModifier, value);
    return this;
  }
  searchIcon(value) {
    modifierWithKey(this._modifiersWithKeys, SearchSearchIconModifier.identity, SearchSearchIconModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, SearchFontColorModifier.identity, SearchFontColorModifier, value);
    return this;
  }
  fontFeature(value) {
    modifierWithKey(this._modifiersWithKeys, SearchFontFeatureModifier.identity, SearchFontFeatureModifier, value);
    return this;
  }
  placeholderColor(value) {
    modifierWithKey(this._modifiersWithKeys, SearchPlaceholderColorModifier.identity, SearchPlaceholderColorModifier, value);
    return this;
  }
  placeholderFont(value) {
    modifierWithKey(this._modifiersWithKeys, SearchPlaceholderFontModifier.identity, SearchPlaceholderFontModifier, value);
    return this;
  }
  textFont(value) {
    modifierWithKey(this._modifiersWithKeys, SearchTextFontModifier.identity, SearchTextFontModifier, value);
    return this;
  }
  copyOption(value) {
    modifierWithKey(this._modifiersWithKeys, SearchCopyOptionModifier.identity, SearchCopyOptionModifier, value);
    return this;
  }
  textAlign(value) {
    modifierWithKey(this._modifiersWithKeys, SearchTextAlignModifier.identity, SearchTextAlignModifier, value);
    return this;
  }
  enterKeyType(value) {
    modifierWithKey(this._modifiersWithKeys, SearchEnterKeyTypeModifier.identity, SearchEnterKeyTypeModifier, value);
    return this;
  }
  height(value) {
    modifierWithKey(this._modifiersWithKeys, SearchHeightModifier.identity, SearchHeightModifier, value);
    return this;
  }
  id(value) {
    modifierWithKey(this._modifiersWithKeys, SearchIdModifier.identity, SearchIdModifier, value);
    return this;
  }
  key(value) {
    modifierWithKey(this._modifiersWithKeys, SearchIdModifier.identity, SearchIdModifier, value);
    return this;
  }
  decoration(value) {
    modifierWithKey(this._modifiersWithKeys, SearchDecorationModifier.identity, SearchDecorationModifier, value);
    return this;
  }
  letterSpacing(value) {
    modifierWithKey(this._modifiersWithKeys, SearchLetterSpacingModifier.identity, SearchLetterSpacingModifier, value);
    return this;
  }
  lineHeight(value) {
    modifierWithKey(this._modifiersWithKeys, SearchLineHeightModifier.identity, SearchLineHeightModifier, value);
    return this;
  }
  halfLeading(value) {
    modifierWithKey(this._modifiersWithKeys, SearchHalfLeadingModifier.identity, SearchHalfLeadingModifier, value);
    return this;
  }
  minFontSize(value) {
    modifierWithKey(this._modifiersWithKeys, SearchMinFontSizeModifier.identity, SearchMinFontSizeModifier, value);
    return this;
  }
  maxFontSize(value) {
    modifierWithKey(this._modifiersWithKeys, SearchMaxFontSizeModifier.identity, SearchMaxFontSizeModifier, value);
    return this;
  }
  minFontScale(value) {
    modifierWithKey(this._modifiersWithKeys, SearchMinFontScaleModifier.identity, SearchMinFontScaleModifier, value);
    return this;
  }
  maxFontScale(value) {
    modifierWithKey(this._modifiersWithKeys, SearchMaxFontScaleModifier.identity, SearchMaxFontScaleModifier, value);
    return this;
  }
  selectedBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, SearchSelectedBackgroundColorModifier.identity, SearchSelectedBackgroundColorModifier, value);
    return this;
  }
  textIndent(value) {
    modifierWithKey(this._modifiersWithKeys, SearchTextIndentModifier.identity, SearchTextIndentModifier, value);
    return this;
  }
  inputFilter(value, error) {
    let searchInputFilter = new ArkSearchInputFilter();
    searchInputFilter.value = value;
    searchInputFilter.error = error;

    modifierWithKey(this._modifiersWithKeys, SearchInputFilterModifier.identity, SearchInputFilterModifier, searchInputFilter);
    return this;
  }
  onWillChange(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnWillChangeModifier.identity, SearchOnWillChangeModifier, callback);
    return this;
  }
  onWillInsert(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnWillInsertModifier.identity, SearchOnWillInsertModifier, callback);
    return this;
  }
  onDidInsert(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnDidInsertModifier.identity, SearchOnDidInsertModifier, callback);
    return this;
  }
  onWillDelete(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnWillDeleteModifier.identity, SearchOnWillDeleteModifier, callback);
    return this;
  }
  onDidDelete(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnDidDeleteModifier.identity, SearchOnDidDeleteModifier, callback);
    return this;
  }
  enablePreviewText(value) {
    modifierWithKey(this._modifiersWithKeys, SearchEnablePreviewTextModifier.identity, SearchEnablePreviewTextModifier, value);
    return this;
  }
  autoCapitalizationMode(value) {
    modifierWithKey(this._modifiersWithKeys, SearchAutoCapitalizationModifier.identity, SearchAutoCapitalizationModifier, value);
    return this;
  }
  editMenuOptions(value) {
    modifierWithKey(this._modifiersWithKeys, SearchEditMenuOptionsModifier.identity,
      SearchEditMenuOptionsModifier, value);
    return this;
  }
  enableHapticFeedback(value) {
    modifierWithKey(this._modifiersWithKeys, SearchEnableHapticFeedbackModifier.identity, SearchEnableHapticFeedbackModifier, value);
    return this;
  }
  stopBackPress(value) {
    modifierWithKey(this._modifiersWithKeys, SearchStopBackPressModifier.identity, SearchStopBackPressModifier, value);
    return this;
  }
  keyboardAppearance(value) {
    modifierWithKey(this._modifiersWithKeys, SearchKeyboardAppearanceModifier.identity, SearchKeyboardAppearanceModifier, value);
    return this;
  }
  strokeWidth(value) {
    modifierWithKey(this._modifiersWithKeys, SearchStrokeWidthModifier.identity, SearchStrokeWidthModifier, value);
    return this;
  }
  strokeColor(value) {
    modifierWithKey(this._modifiersWithKeys, SearchStrokeColorModifier.identity, SearchStrokeColorModifier, value);
    return this;
  }
  enableAutoSpacing(value) {
    modifierWithKey(this._modifiersWithKeys, SearchEnableAutoSpacingModifier.identity, SearchEnableAutoSpacingModifier, value);
    return this;
  }
  compressLeadingPunctuation(value) {
    modifierWithKey(this._modifiersWithKeys, SearchCompressLeadingPunctuationModifier.identity, SearchCompressLeadingPunctuationModifier, value);
    return this;
  }
  includeFontPadding(value) {
    modifierWithKey(this._modifiersWithKeys, SearchIncludeFontPaddingModifier.identity, SearchIncludeFontPaddingModifier, value);
    return this;
  }
  fallbackLineSpacing(value) {
    modifierWithKey(this._modifiersWithKeys, SearchFallbackLineSpacingModifier.identity, SearchFallbackLineSpacingModifier, value);
    return this;
  }
  margin(value) {
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
      modifierWithKey(this._modifiersWithKeys, SearchMarginModifier.identity, SearchMarginModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SearchMarginModifier.identity, SearchMarginModifier, undefined);
    }
    return this;
  }
  onWillAttachIME(callback) {
    modifierWithKey(this._modifiersWithKeys, SearchOnWillAttachIMEModifier.identity,
      SearchOnWillAttachIMEModifier, callback);
    return this;
  }
  textDirection(value) {
    modifierWithKey(this._modifiersWithKeys, SearchTextDirectionModifier.identity, SearchTextDirectionModifier, value);
    return this;
  }
  selectedDragPreviewStyle(value) {
    let arkSelectedDragPreviewStyle = new ArkSelectedDragPreviewStyle();
    arkSelectedDragPreviewStyle.color = value?.color;
    modifierWithKey(this._modifiersWithKeys, SearchSelectedDragPreviewStyleModifier.identity,
      SearchSelectedDragPreviewStyleModifier, arkSelectedDragPreviewStyle);
    return this;
  }
}

class JSSearch extends JSViewAbstract {
  static create(params) {
    getUINativeModule().search.jsCreate(params);
  }
  static allowChildCount() {
    return 0;
  }
  static searchButton(value, option) {
    getUINativeModule().search.setSearchButton(true, value,
      option === null || option === void 0 ? void 0 : option.fontSize,
      option === null || option === void 0 ? void 0 : option.fontColor,
      option === null || option === void 0 ? void 0 : option.autoDisable);
  }
  static searchIcon(value) {
    if (value) {
      if (value.fontColor === null || value.fontColor === undefined) {
        getUINativeModule().search.setSearchIcon(true,
          value.size, value.color, value.src);
      } else {
        getUINativeModule().search.setSearchSymbol(true, value);
      }
    } else {
      getUINativeModule().search.setSearchDefaultIcon(true);
    }
  }

  static cancelButton(value) {
    if (value) {
      if (value.icon !== null && value.icon !== undefined &&
        value.icon.fontColor !== null && value.icon.fontColor !== undefined) {
        getUINativeModule().search.setCancelSymbolButton(true, value.style, value.icon);
      } else if (!value.icon) {
        getUINativeModule().search.setJsDefaultCancelButton(true, value.style);
      } else {
        getUINativeModule().search.setJsCancelButton(true, value.style,
          value.icon === null || value.icon === void 0 ? void 0 : value.icon.size,
          value.icon === null || value.icon === void 0 ? void 0 : value.icon.color,
          value.icon === null || value.icon === void 0 ? void 0 : value.icon.src);
      }
    }
  }
  static fontColor(value) {
    getUINativeModule().search.setFontColor(true, value);
  }
  static backgroundColor(value) {
    getUINativeModule().search.setBackgroundColor(true, value);
  }
  static caretStyle(value) {
    if (value) {
      getUINativeModule().search.setCaretStyle(true, value.width, value.color);
    }
  }
  static placeholderColor(value) {
    getUINativeModule().search.setPlaceholderColor(true, value);
  }
  static placeholderFont(value) {
    if (value) {
      getUINativeModule().search.setPlaceholderFont(true, value.size, value.weight, value.family, value.style);
    }
  }
  static textFont(value) {
    if (value) {
      getUINativeModule().search.setTextFont(true, value.size, value.weight, value.family, value.style);
    } else {
      getUINativeModule().search.setTextFont(true, null, null, null, null);
    }
  }
  static textAlign(value) {
    getUINativeModule().search.setSearchTextAlign(true, value);
  }
  static textDirection(direction) {
    getUINativeModule().search.setTextDirection(true, direction);
  }
  static onSubmit(callback) {
    getUINativeModule().search.setOnSubmit(true, callback);
  }
  static onChange(callback) {
    getUINativeModule().search.setOnChange(true, callback);
  }
  static onTextSelectionChange(callback) {
    getUINativeModule().search.setOnTextSelectionChange(true, callback);
  }
  static onContentScroll(callback) {
    getUINativeModule().search.setOnContentScroll(true, callback);
  }
  static border(value) {
    JSViewAbstract.border(value);
    if (value && !isUndefined(value.radius)) {
      getUINativeModule().search.setBorderRadius(true);
    }
    getUINativeModule().search.setBackBorder(true);
  }
  static borderWidth(value) {
    JSViewAbstract.borderWidth(value);
    getUINativeModule().search.setBackBorder(true);
  }
  static borderColor(value) {
    JSViewAbstract.borderColor(value);
    getUINativeModule().search.setBackBorder(true);
  }
  static borderStyle(value) {
    JSViewAbstract.borderStyle(value);
    getUINativeModule().search.setBackBorder(true);
  }
  static borderRadius(value) {
    JSViewAbstract.borderRadius(value);
    getUINativeModule().search.setBackBorder(true);
  }
  static height(value) {
    JSViewAbstract.height(value);
    getUINativeModule().search.setSearchHeight(true, value);
  }
  static requestKeyboardOnFocus(value) {
    getUINativeModule().search.setEnableKeyboardOnFocus(true, value);
  }
  static enableKeyboardOnFocus(value) {
    getUINativeModule().search.setEnableKeyboardOnFocus(true, value);
  }
  static onCopy(callback) {
    getUINativeModule().search.setOnCopy(true, callback);
  }
  static onCut(callback) {
    getUINativeModule().search.setOnCut(true, callback);
  }
  static onPaste(callback) {
    getUINativeModule().search.setOnPaste(true, callback);
  }
  static copyOption(value) {
    getUINativeModule().search.setCopyOption(true, value);
  }
  static selectionMenuHidden(value) {
    getUINativeModule().search.setSelectionMenuHidden(true, value);
  }
  static customKeyboard(value, options) {
    getUINativeModule().search.setJsCustomKeyboard(true, value, options);
  }
  static enterKeyType(value) {
    getUINativeModule().search.setSearchEnterKeyType(true, value);
  }
  static maxLength(value) {
    getUINativeModule().search.setMaxLength(true, value);
  }
  static type(value) {
    getUINativeModule().search.setType(true, value);
  }
  static dragPreviewOptions(value, options) {
    getUINativeModule().search.setDragPreviewOptions(true, value, options);
  }
  static editMenuOptions(editMenu) {
    getUINativeModule().search.setSelectionMenuOptions(true, editMenu);
  }
  static strokeWidth(width) {
    getUINativeModule().search.setStrokeWidth(true, width);
  }
  static strokeColor(color) {
    getUINativeModule().search.setStrokeColor(true, color);
  }
  static margin(value) {
    JSViewAbstract.margin(value);
    getUINativeModule().search.setMargin(true);
  }
  static selectedDragPreviewStyle(value) {
    if (value) {
      getUINativeModule().search.setSelectedDragPreviewStyle(true, value.color);
    } else {
      getUINativeModule().search.setSelectedDragPreviewStyle(true, null);
    }
  }
  static decoration(value) {
    if (value) {
      getUINativeModule().search.setDecoration(true, value.type, value.color, value.style);
    } else {
      getUINativeModule().search.setDecoration(true, null, null, null);
    }
  }
  static minFontSize(value) {
    getUINativeModule().search.setJsSearchMinFontSize(true, value);
  }
  static maxFontSize(value) {
    getUINativeModule().search.setSearchMaxFontSize(true, value);
  }
  static minFontScale(scale) {
    getUINativeModule().search.setMinFontScale(true, scale);
  }
  static maxFontScale(scale) {
    getUINativeModule().search.setMaxFontScale(true, scale);
  }
  static dividerColor(color) {
    getUINativeModule().search.setSearchDividerColor(true, color);
  }
  static letterSpacing(value) {
    getUINativeModule().search.setLetterSpacing(true, value);
  }
  static lineHeight(value) {
    getUINativeModule().search.setLineHeight(true, value);
  }
  static halfLeading(halfLeading) {
    getUINativeModule().search.setHalfLeading(true, halfLeading);
  }
  static fontFeature(value) {
    getUINativeModule().search.setFontFeature(true, value);
  }
  static id(value) {
    JSViewAbstract.id(value);
    getUINativeModule().search.setSearchInspectorId(true, value);
  }
  static key(value) {
    JSViewAbstract.key(value);
    getUINativeModule().search.setSearchInspectorId(true, value);
  }
  static selectedBackgroundColor(value) {
    getUINativeModule().search.setSelectedBackgroundColor(true, value);
  }
  static inputFilter(value, error) {
    getUINativeModule().search.setJsInputFilter(true, value, error);
  }
  static onEditChange(callback) {
    getUINativeModule().search.setOnEditChange(true, callback);
  }
  static textIndent(value) {
    getUINativeModule().search.setTextIndent(true, value);
  }
  static onWillInsert(callback) {
    getUINativeModule().search.setOnWillInsert(true, callback);
  }
  static onDidInsert(callback) {
    getUINativeModule().search.setOnDidInsert(true, callback);
  }
  static onWillDelete(callback) {
    getUINativeModule().search.setOnWillDelete(true, callback);
  }
  static onDidDelete(callback) {
    getUINativeModule().search.setOnDidDelete(true, callback);
  }
  static enablePreviewText(enable) {
    getUINativeModule().search.setEnablePreviewText(true, enable);
  }
  static enableHapticFeedback(isEnabled) {
    getUINativeModule().search.setEnableHapticFeedback(true, isEnabled);
  }
  static autoCapitalizationMode(mode) {
    getUINativeModule().search.setSearchAutoCapitalizationMode(true, mode);
  }
  static stopBackPress(isStopped) {
    getUINativeModule().search.setStopBackPress(true, isStopped);
  }
  static keyboardAppearance(appearance) {
    getUINativeModule().search.setKeyboardAppearance(true, appearance);
  }
  static onWillChange(callback) {
    getUINativeModule().search.setOnWillChange(true, callback);
  }
  static enableAutoSpacing(enabled) {
    getUINativeModule().search.setEnableAutoSpacing(true, enabled);
  }
  static onWillAttachIME(callback) {
    getUINativeModule().search.setOnWillAttachIME(true, callback);
  }
  static enableSelectedDataDetector(enable) {
    getUINativeModule().search.setSelectDetectorEnable(true, enable);
  }
  static compressLeadingPunctuation(enabled) {
    getUINativeModule().search.setCompressLeadingPunctuation(true, enabled);
  }
  static includeFontPadding(include) {
    getUINativeModule().search.setIncludeFontPadding(true, include);
  }
  static fallbackLineSpacing(enabled) {
    getUINativeModule().search.setFallbackLineSpacing(true, enabled);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkSearchComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.SearchModifier(nativePtr, classType);
    });
  }

  static onKeyEvent(value) {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value) {
    __Common__.onDeleteEvent(value);
  }
  static onClick(value) {
    __Common__.onClick(value);
  }
  static onAttach(value) {
    __Common__.onAttach(value);
  }
  static onAppear(value) {
    __Common__.onAppear(value);
  }
  static onDetach(value) {
    __Common__.onDetach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkSearchComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkSearchComponent = ArkSearchComponent;
}

function exportView() {
  globalThis.Search = JSSearch;
}
function loadComponent() {}
export default { ArkSearchComponent, createComponent, exportComponent, exportView, loadComponent };