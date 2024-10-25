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
class TextEnableDataDetectorModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textEnableDataDetector');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetEnableDataDetector(node);
    } else {
      getUINativeModule().text.setEnableDataDetector(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class FontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetFontColor(node);
    } else {
      getUINativeModule().text.setFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextForegroundColorModifier extends ModifierWithKey<ResourceColor | ColoringStrategy> {
  constructor(value: ResourceColor | ColoringStrategy) {
    super(value);
  }
  static identity: Symbol = Symbol('textForegroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetTextForegroundColor(node);
    } else {
      getUINativeModule().text.setTextForegroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class FontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetFontSize(node);
    } else {
      getUINativeModule().text.setFontSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class FontWeightModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('textFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetFontWeight(node);
    } else {
      getUINativeModule().text.setFontWeight(node, this.value);
    }
  }
}

class FontStyleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetFontStyle(node);
    } else {
      getUINativeModule().text.setFontStyle(node, this.value);
    }
  }
}

class TextAlignModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetTextAlign(node);
    } else {
      getUINativeModule().text.setTextAlign(node, this.value);
    }
  }
}

class TextHeightAdaptivePolicyModifier extends ModifierWithKey<TextHeightAdaptivePolicy> {
  constructor(value: TextHeightAdaptivePolicy) {
    super(value);
  }
  static identity: Symbol = Symbol('textHeightAdaptivePolicy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetHeightAdaptivePolicy(node);
    } else {
      getUINativeModule().text.setHeightAdaptivePolicy(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextDraggableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textDraggable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetDraggable(node);
    } else {
      getUINativeModule().text.setDraggable(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextPrivacySensitiveModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textPrivacySensitive');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetPrivacySensitive(node);
    } else {
      getUINativeModule().text.setPrivacySensitive(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextWordBreakModifier extends ModifierWithKey<WordBreak> {
  constructor(value: WordBreak) {
    super(value);
  }
  static identity: Symbol = Symbol('textWordBreak');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetWordBreak(node);
    } else {
      getUINativeModule().text.setWordBreak(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextLineBreakStrategyModifier extends ModifierWithKey<LineBreakStrategy> {
  constructor(value: LineBreakStrategy) {
    super(value);
  }
  static identity: Symbol = Symbol('textLineBreakStrategy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetLineBreakStrategy(node);
    } else {
      getUINativeModule().text.setLineBreakStrategy(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextEllipsisModeModifier extends ModifierWithKey<EllipsisMode> {
  constructor(value: EllipsisMode) {
    super(value);
  }
  static identity: Symbol = Symbol('textEllipsisMode');
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

class TextMinFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textMinFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetMinFontSize(node);
    } else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetMinFontSize(node);
    } else {
      getUINativeModule().text.setMinFontSize(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextMaxFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textMaxFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetMaxFontSize(node);
    } else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetMaxFontSize(node);
    } else {
      getUINativeModule().text.setMaxFontSize(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextMinFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textMinFontScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetMinFontScale(node);
    } else if (!isNumber(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetMinFontScale(node);
    } else {
      getUINativeModule().text.setMinFontScale(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextMaxFontScaleModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textMaxFontScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetMaxFontScale(node);
    } else if (!isNumber(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetMaxFontScale(node);
    } else {
      getUINativeModule().text.setMaxFontScale(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextLineHeightModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textLineHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetLineHeight(node);
    } else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetLineHeight(node);
    } else {
      getUINativeModule().text.setLineHeight(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextCopyOptionModifier extends ModifierWithKey<CopyOptions> {
  constructor(value: CopyOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetCopyOption(node);
    } else {
      getUINativeModule().text.setCopyOption(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextFontFamilyModifier extends ModifierWithKey<string | Resource> {
  constructor(value: string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetFontFamily(node);
    } else if (!isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetFontFamily(node);
    } else {
      getUINativeModule().text.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextMaxLinesModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetMaxLines(node);
    } else if (!isNumber(this.value)) {
      getUINativeModule().text.resetMaxLines(node);
    } else {
      getUINativeModule().text.setMaxLines(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextLetterSpacingModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textLetterSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetLetterSpacing(node);
    } else if (!isNumber(this.value) && !isString(this.value)) {
      getUINativeModule().text.resetLetterSpacing(node);
    } else {
      getUINativeModule().text.setLetterSpacing(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextLineSpacingModifier extends ModifierWithKey<LengthMetrics> {
  constructor(value: LengthMetrics) {
    super(value);
  }
  static identity: Symbol = Symbol('textLineSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetLineSpacing(node);
    } else if (!isObject(this.value)) {
      getUINativeModule().text.resetLineSpacing(node);
    } else {
      getUINativeModule().text.setLineSpacing(node, this.value.value, this.value.unit);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextTextOverflowModifier extends ModifierWithKey<{ overflow: TextOverflow }> {
  constructor(value: { overflow: TextOverflow }) {
    super(value);
  }
  static identity: Symbol = Symbol('textTextOverflow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetTextOverflow(node);
    } else {
      getUINativeModule().text.setTextOverflow(node, this.value.overflow);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.overflow, this.value.overflow);
  }
}

class TextBaselineOffsetModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: symbol = Symbol('textBaselineOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetBaselineOffset(node);
    } else if (!isNumber(this.value) && !isString(this.value)) {
      getUINativeModule().text.resetBaselineOffset(node);
    } else {
      getUINativeModule().text.setBaselineOffset(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextTextCaseModifier extends ModifierWithKey<TextCase> {
  constructor(value: TextCase) {
    super(value);
  }
  static identity: symbol = Symbol('textTextCase');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetTextCase(node);
    } else {
      getUINativeModule().text.setTextCase(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextTextIndentModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: symbol = Symbol('textTextIndent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetTextIndent(node);
    } else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetTextIndent(node);
    } else {
      getUINativeModule().text.setTextIndent(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextTextShadowModifier extends ModifierWithKey<ShadowOptions | Array<ShadowOptions>> {
  constructor(value: ShadowOptions | Array<ShadowOptions>) {
    super(value);
  }
  static identity: Symbol = Symbol('textTextShadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetTextShadow(node);
    } else {
      let shadow: ArkShadowInfoToArray = new ArkShadowInfoToArray();
      if (!shadow.convertShadowOptions(this.value)) {
        getUINativeModule().text.resetTextShadow(node);
      } else {
        getUINativeModule().text.setTextShadow(node, shadow.radius,
          shadow.type, shadow.color, shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
      }
    }
  }

  checkObjectDiff(): boolean {
    let checkDiff = true;
    let arkShadow = new ArkShadowInfoToArray();
    if (Object.getPrototypeOf(this.stageValue).constructor === Object &&
      Object.getPrototypeOf(this.value).constructor === Object) {
      checkDiff = arkShadow.checkDiff(<ShadowOptions> this.stageValue, <ShadowOptions> this.value);
    } else if (Object.getPrototypeOf(this.stageValue).constructor === Array &&
      Object.getPrototypeOf(this.value).constructor === Array &&
      (<Array<ShadowOptions>> this.stageValue).length === (<Array<ShadowOptions>> this.value).length) {
      let isDiffItem = false;
      for (let i: number = 0; i < (<Array<ShadowOptions>> this.value).length; i++) {
        if (arkShadow.checkDiff(this.stageValue[i], this.value[1])) {
          isDiffItem = true;
          break;
        }
      }
      if (!isDiffItem) {
        checkDiff = false;
      }
    }
    return checkDiff;
  }
}

class TextDecorationModifier extends ModifierWithKey<{ type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }> {
  constructor(value: { type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }) {
    super(value);
  }
  static identity: Symbol = Symbol('textDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetDecoration(node);
    } else {
      getUINativeModule().text.setDecoration(node, this.value!.type, this.value!.color, this.value!.style);
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

class TextFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('textFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetFont(node);
    } else {
      getUINativeModule().text.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style) {
      return true;
    }
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

class TextClipModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('textClip');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetClipWithEdge(node);
    } else {
      getUINativeModule().common.setClipWithEdge(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return true;
  }
}

class TextFontFeatureModifier extends ModifierWithKey<FontFeature> {
  constructor(value: FontFeature) {
    super(value);
  }
  static identity: Symbol = Symbol('textFontFeature');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetFontFeature(node);
    } else {
      getUINativeModule().text.setFontFeature(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextContentModifier extends ModifierWithKey<string | Resource> {
  constructor(value: string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('textContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.setContent(node, '');
    }
    else {
      getUINativeModule().text.setContent(node, this.value);
    }
  }
}

class TextSelectionModifier extends ModifierWithKey<ArkSelection> {
  constructor(value: ArkSelection) {
    super(value);
  }
  static identity: Symbol = Symbol('textSelection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetSelection(node);
    } else {
      getUINativeModule().text.setSelection(node, this.value.selectionStart, this.value.selectionEnd);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.selectionStart, this.value.selectionStart) ||
    !isBaseOrResourceEqual(this.stageValue.selectionEnd, this.value.selectionEnd);
  }
}

class TextSelectableModifier extends ModifierWithKey<TextSelectableMode> {
  constructor(value: TextSelectableMode) {
    super(value);
  }
  static identity: Symbol = Symbol('textTextSelectable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetTextSelectableMode(node);
    } else {
      getUINativeModule().text.setTextSelectableMode(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextCaretColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textCaretColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetCaretColor(node);
    } else {
      getUINativeModule().text.setCaretColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextSelectedBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textSelectedBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().text.setSelectedBackgroundColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextDataDetectorConfigModifier extends ModifierWithKey<TextDataDetectorConfig> {
  constructor(value: TextDataDetectorConfig) {
    super(value);
  }
  static identity: Symbol = Symbol('textDataDetectorConfig');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetDataDetectorConfig(node);
    } else {
      getUINativeModule().text.setDataDetectorConfig(node, this.value.types, this.value.onDetectResultUpdate);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.types, this.value.types) ||
    !isBaseOrResourceEqual(this.stageValue.onDetectResultUpdate, this.value.onDetectResultUpdate);
  }
}

class TextOnCopyModifier extends ModifierWithKey<(value: string) => void> {
  constructor(value: (value: string) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('textOnCopy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetOnCopy(node);
    } else {
      getUINativeModule().text.setOnCopy(node, this.value);
    }
  }
}

class TextOnTextSelectionChangeModifier extends ModifierWithKey<(selectionStart: number,
    selectionEnd: number) => void> {
  constructor(value: (selectionStart: number, selectionEnd: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('textOnTextSelectionChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetOnTextSelectionChange(node);
    } else {
      getUINativeModule().text.setOnTextSelectionChange(node, this.value);
    }
  }
}

class TextControllerModifier extends ModifierWithKey<TextOptions> {
  constructor(value: TextOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textController');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.setTextController(node, '');
    }
    else {
      getUINativeModule().text.setTextController(node, this.value);
    }
  }
}

class TextEditMenuOptionsModifier extends ModifierWithKey<EditMenuOptions> {
  constructor(value: EditMenuOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textEditMenuOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetSelectionMenuOptions(node);
    } else {
      getUINativeModule().text.setSelectionMenuOptions(node, this.value);
    }
  }
}

class TextHalfLeadingModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textHalfLeading');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().text.resetHalfLeading(node);
    } else {
      getUINativeModule().text.setHalfLeading(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkTextComponent extends ArkComponent implements TextAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildTypes(): string[] {
    return ['Span', 'ImageSpan', 'SymbolSpan', 'ContainerSpan'];
  }
  initialize(value: Object[]): void {
    modifierWithKey(this._modifiersWithKeys, TextContentModifier.identity, TextContentModifier, value[0]);
    modifierWithKey(this._modifiersWithKeys, TextControllerModifier.identity, TextControllerModifier, value[1]);
    return this;
  }
  enableDataDetector(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextEnableDataDetectorModifier.identity, TextEnableDataDetectorModifier, value);
    return this;
  }
  dataDetectorConfig(config: TextDataDetectorConfig): this {
    let detectorConfig = new TextDataDetectorConfig();
    detectorConfig.types = config.types;
    detectorConfig.onDetectResultUpdate = config.onDetectResultUpdate;
    modifierWithKey(this._modifiersWithKeys, TextDataDetectorConfigModifier.identity, TextDataDetectorConfigModifier, detectorConfig);
    return this;
  }
  font(value: Font): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextFontModifier.identity, TextFontModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, FontColorModifier.identity, FontColorModifier, value);
    return this;
  }
  fontSize(value: number | string | Resource): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, FontSizeModifier.identity, FontSizeModifier, value);
    return this;
  }
  minFontSize(value: number | string | Resource): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextMinFontSizeModifier.identity, TextMinFontSizeModifier, value);
    return this;
  }
  maxFontSize(value: number | string | Resource): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextMaxFontSizeModifier.identity, TextMaxFontSizeModifier, value);
    return this;
  }
  minFontScale(value: number | Resource): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextMinFontScaleModifier.identity, TextMinFontScaleModifier, value);
    return this;
  }
  maxFontScale(value: number | Resource): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextMaxFontScaleModifier.identity, TextMaxFontScaleModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, FontStyleModifier.identity, FontStyleModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string): TextAttribute {
    let fontWeightStr: string = '400';
    if (isNumber(value)) {
      fontWeightStr = value.toString();
    } else if (isString(value)) {
      fontWeightStr = String(value);
    }
    modifierWithKey(this._modifiersWithKeys, FontWeightModifier.identity, FontWeightModifier, fontWeightStr);
    return this;
  }
  textAlign(value: TextAlign): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAlignModifier.identity, TextAlignModifier, value);
    return this;
  }
  lineHeight(value: number | string | Resource): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextLineHeightModifier.identity, TextLineHeightModifier, value);
    return this;
  }
  textOverflow(value: { overflow: TextOverflow }): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextTextOverflowModifier.identity, TextTextOverflowModifier, value);
    return this;
  }
  fontFamily(value: string | Resource): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextFontFamilyModifier.identity, TextFontFamilyModifier, value);
    return this;
  }
  maxLines(value: number): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextMaxLinesModifier.identity, TextMaxLinesModifier, value);
    return this;
  }
  decoration(value: { type: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle }): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextDecorationModifier.identity, TextDecorationModifier, value);
    return this;
  }
  letterSpacing(value: number | string): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextLetterSpacingModifier.identity, TextLetterSpacingModifier, value);
    return this;
  }
  lineSpacing(value: LengthMetrics): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextLineSpacingModifier.identity, TextLineSpacingModifier, value);
    return this;
  }
  textCase(value: TextCase): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextTextCaseModifier.identity, TextTextCaseModifier, value);
    return this;
  }
  baselineOffset(value: number | string): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextBaselineOffsetModifier.identity, TextBaselineOffsetModifier, value);
    return this;
  }
  copyOption(value: CopyOptions): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextCopyOptionModifier.identity, TextCopyOptionModifier, value);
    return this;
  }
  draggable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextDraggableModifier.identity, TextDraggableModifier, value);
    return this;
  }
  privacySensitive(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, TextPrivacySensitiveModifier.identity, TextPrivacySensitiveModifier, value);
    return this;
  }
  textShadow(value: ShadowOptions | Array<ShadowOptions>): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextTextShadowModifier.identity, TextTextShadowModifier, value);
    return this;
  }
  heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextHeightAdaptivePolicyModifier.identity, TextHeightAdaptivePolicyModifier, value);
    return this;
  }
  textIndent(value: Length): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextTextIndentModifier.identity, TextTextIndentModifier, value);
    return this;
  }
  wordBreak(value: WordBreak): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextWordBreakModifier.identity, TextWordBreakModifier, value);
    return this;
  }
  lineBreakStrategy(value: LineBreakStrategy): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextLineBreakStrategyModifier.identity,
      TextLineBreakStrategyModifier, value);
    return this;
  }
  onCopy(callback: (value: string) => void): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextOnCopyModifier.identity,
      TextOnCopyModifier, callback);
    return this;
  }
  selection(selectionStart: number, selectionEnd: number): TextAttribute {
    let arkSelection = new ArkSelection();
    arkSelection.selectionStart = selectionStart;
    arkSelection.selectionEnd = selectionEnd;
    modifierWithKey(this._modifiersWithKeys, TextSelectionModifier.identity, TextSelectionModifier, arkSelection);
    return this;
  }
  textSelectable(value: TextSelectableMode): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextSelectableModifier.identity, TextSelectableModifier, value);
    return this;
  }
  caretColor(value: ResourceColor): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextCaretColorModifier.identity, TextCaretColorModifier, value);
    return this;
  }
  selectedBackgroundColor(value: ResourceColor): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextSelectedBackgroundColorModifier.identity,
      TextSelectedBackgroundColorModifier, value);
    return this;
  }
  ellipsisMode(value: EllipsisMode): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextEllipsisModeModifier.identity, TextEllipsisModeModifier, value);
    return this;
  }
  fontFeature(value: FontFeature): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextFontFeatureModifier.identity, TextFontFeatureModifier, value);
    return this;
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    modifierWithKey(this._modifiersWithKeys, TextClipModifier.identity, TextClipModifier, value);
    return this;
  }
  foregroundColor(value: ResourceColor | ColoringStrategy): void {
    modifierWithKey(
      this._modifiersWithKeys, TextForegroundColorModifier.identity, TextForegroundColorModifier, value);
    return this;
  }
  onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void) {
    modifierWithKey(this._modifiersWithKeys, TextOnTextSelectionChangeModifier.identity,
      TextOnTextSelectionChangeModifier, callback);
    return this;
  }
  editMenuOptions(value: EditMenuOptions): this {
    modifierWithKey(this._modifiersWithKeys, TextEditMenuOptionsModifier.identity,
      TextEditMenuOptionsModifier, value);
    return this;
  }
  halfLeading(value: boolean): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, TextHalfLeadingModifier.identity,
      TextHalfLeadingModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Text.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkTextComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TextModifier(nativePtr, classType);
  });
};
