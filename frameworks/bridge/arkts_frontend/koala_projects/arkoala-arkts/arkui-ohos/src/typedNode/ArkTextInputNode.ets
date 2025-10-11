/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { int32 } from "@koalaui/common"
import { InteropNativeModule } from "@koalaui/interop";

import { ArkBaseNode } from "./ArkBaseNode";
import { AutoCapitalizationMode, FontWeight, UnderlineColor, Length, ResourceStr, Dimension, ResourceColor, BarState, CancelButtonOptions, CancelButtonSymbolOptions, CaretStyle, ContentType, CopyOptions, CustomBuilder, DeleteValue, EditMenuOptions, EditableTextChangeValue, EditableTextOnChangeCallback, EllipsisMode, EnterKeyType, Font, FontStyle, InputCounterOptions, InputType, InsertValue, KeyboardAppearance, KeyboardOptions, LineBreakStrategy, OnContentScrollCallback, OnPasteCallback, OnSubmitCallback, OnTextSelectionChangeCallback, PasswordIcon, TextAlign, TextContentStyle, TextDecorationOptions, TextHeightAdaptivePolicy, TextInputAttribute, TextInputStyle, TextOverflow, WordBreak } from "../framework";
import { ArkTextInputPeer, TextInputOptions } from "../framework";
import { LengthMetrics } from "../Graphics";
import { Resource } from "global.resource"

export class ArkTextInputNode extends ArkBaseNode  implements TextInputAttribute  {
    onstructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog("textInput constructParam enter")
        return this;
    }
    getPeer() : ArkTextInputPeer {
        return this.peer as ArkTextInputPeer
    }
    initialize(options?: TextInputOptions): this {
        const options_casted = options as (TextInputOptions | undefined)
            this.getPeer()?.setTextInputOptionsAttribute(options_casted)
        this.markDirty();
        return this;
    }
    allowChildTypes(): string[] {
        return ["TextInputItem", "TextInputItemGroup"];
    }
    type(value: InputType | undefined): this {
        this.getPeer().setTypeAttribute(value);
        this.markDirty();
        return this;
    }
    contentType(value: ContentType | undefined): this {
        this.getPeer().setContentTypeAttribute(value);
        this.markDirty();
        return this;
    }
    placeholderColor(value: ResourceColor | undefined): this {
        this.getPeer().setPlaceholderColorAttribute(value);
        this.markDirty();
        return this;
    }
    textOverflow(value: TextOverflow | undefined): this {
        this.getPeer().setTextOverflowAttribute(value);
        this.markDirty();
        return this;
    }
    textIndent(value: Dimension | undefined): this {
        this.getPeer().setTextIndentAttribute(value);
        this.markDirty();
        return this;
    }
    placeholderFont(value: Font | undefined): this {
        this.getPeer().setPlaceholderFontAttribute(value);
        this.markDirty();
        return this;
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        this.getPeer().setEnterKeyTypeAttribute(value);
        this.markDirty();
        return this;
    }
    caretColor(value: ResourceColor | undefined): this {
        this.getPeer().setCaretColorAttribute(value);
        this.markDirty();
        return this;
    }
    onEditChange(value: ((isVisible: boolean) => void) | undefined): this {
        this.getPeer().setOnEditChangeAttribute(value);
        this.markDirty();
        return this;
    }
    onSubmit(value: OnSubmitCallback | undefined): this {
        this.getPeer().setOnSubmitAttribute(value);
        this.markDirty();
        return this;
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        this.getPeer().setOnChangeAttribute(value);
        this.markDirty();
        return this;
    }
    onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        this.getPeer().setOnTextSelectionChangeAttribute(value);
        this.markDirty();
        return this;
    }
    onContentScroll(value: OnContentScrollCallback | undefined): this {
        this.getPeer().setOnContentScrollAttribute(value);
        this.markDirty();
        return this;
    }
    maxLength(value: int32 | undefined): this {
        this.getPeer().setMaxLengthAttribute(value);
        this.markDirty();
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        this.getPeer().setFontColorAttribute(value);
        this.markDirty();
        return this;
    }
    fontSize(value: Length | undefined): this {
        this.getPeer().setFontSizeAttribute(value);
        this.markDirty();
        return this;
    }
    fontStyle(value: FontStyle | undefined): this {
        this.getPeer().setFontStyleAttribute(value);
        this.markDirty();
        return this;
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        this.getPeer().setFontWeightAttribute(value);
        this.markDirty();
        return this;
    }
    fontFamily(value: ResourceStr | undefined): this {
        this.getPeer().setFontFamilyAttribute(value);
        this.markDirty();
        return this;
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().setOnCopyAttribute(value);
        this.markDirty();
        return this;
    }
    onCut(value: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().setOnCutAttribute(value);
        this.markDirty();
        return this;
    }
    onPaste(value: OnPasteCallback | undefined): this {
        this.getPeer().setOnPasteAttribute(value);
        this.markDirty();
        return this;
    }
    copyOption(value: CopyOptions | undefined): this {
        this.getPeer().setCopyOptionAttribute(value);
        this.markDirty();
        return this;
    }
    showPasswordIcon(value: boolean | undefined): this {
        this.getPeer().setShowPasswordIconAttribute(value);
        this.markDirty();
        return this;
    }
    textAlign(value: TextAlign | undefined): this {
        this.getPeer().setTextAlignAttribute(value);
        this.markDirty();
        return this;
    }
    style(value: TextContentStyle | TextInputStyle | undefined): this {
        this.getPeer().setStyleAttribute(value);
        this.markDirty();
        return this;
    }
    caretStyle(value: CaretStyle | undefined): this {
        this.getPeer().setCaretStyleAttribute(value);
        this.markDirty();
        return this;
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        this.getPeer().setSelectedBackgroundColorAttribute(value);
        this.markDirty();
        return this;
    }
    caretPosition(value: int32 | undefined): this {
        this.getPeer().setCaretPositionAttribute(value);
        this.markDirty();
        return this;
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        this.getPeer().setEnableKeyboardOnFocusAttribute(value);
        this.markDirty();
        return this;
    }
    passwordIcon(value: PasswordIcon | undefined): this {
        this.getPeer().setPasswordIconAttribute(value);
        this.markDirty();
        return this;
    }
    showError(value: ResourceStr | undefined): this {
        this.getPeer().setShowErrorAttribute(value);
        this.markDirty();
        return this;
    }
    showUnit(value: CustomBuilder | undefined): this {
        this.getPeer().setShowUnitAttribute(value);
        this.markDirty();
        return this;
    }
    showUnderline(value: boolean | undefined): this {
        this.getPeer().setShowUnderlineAttribute(value);
        this.markDirty();
        return this;
    }
    underlineColor(value: ResourceColor | UnderlineColor | undefined): this {
        this.getPeer().setUnderlineColorAttribute(value);
        this.markDirty();
        return this;
    }
    selectionMenuHidden(value: boolean | undefined): this {
        this.getPeer().setSelectionMenuHiddenAttribute(value);
        this.markDirty();
        return this;
    }
    barState(value: BarState | undefined): this {
        this.getPeer().setBarStateAttribute(value);
        this.markDirty();
        return this;
    }
    maxLines(value: int32 | undefined): this {
        this.getPeer().setMaxLinesAttribute(value);
        this.markDirty();
        return this;
    }
    wordBreak(value: WordBreak | undefined): this {
        this.getPeer().setWordBreakAttribute(value);
        this.markDirty();
        return this;
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        this.getPeer().setLineBreakStrategyAttribute(value);
        this.markDirty();
        return this;
    }
    cancelButton(value: CancelButtonOptions | undefined): this {
        const value_casted = value as (CancelButtonOptions | undefined)
        this.getPeer()?.setCancelButton0Attribute(value_casted)
        this.markDirty();
        return this
    }
    cancelButton(value: CancelButtonSymbolOptions | undefined): this {
        const value_casted = value as (CancelButtonSymbolOptions | undefined)
        this.getPeer()?.setCancelButton1Attribute(value_casted)
        this.markDirty();
        return this
    }
    selectAll(value: boolean | undefined): this {
        this.getPeer().setSelectAllAttribute(value);
        this.markDirty();
        return this;
    }
    minFontSize(value: double | string | Resource | undefined): this {
        this.getPeer().setMinFontSizeAttribute(value);
        this.markDirty();
        return this;
    }
    maxFontSize(value: double | string | Resource | undefined): this {
        this.getPeer().setMaxFontSizeAttribute(value);
        this.markDirty();
        return this;
    }
    minFontScale(value: double | Resource | undefined): this {
        this.getPeer().setMinFontScaleAttribute(value);
        this.markDirty();
        return this;
    }
    maxFontScale(value: double | Resource | undefined): this {
        this.getPeer().setMaxFontScaleAttribute(value);
        this.markDirty();
        return this;
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        this.getPeer().setHeightAdaptivePolicyAttribute(value);
        this.markDirty();
        return this;
    }
    enableAutoFill(value: boolean | undefined): this {
        this.getPeer().setEnableAutoFillAttribute(value);
        this.markDirty();
        return this;
    }
    decoration(value: TextDecorationOptions | undefined): this {
        this.getPeer().setDecorationAttribute(value);
        this.markDirty();
        return this;
    }
    letterSpacing(value: double | string | Resource | undefined): this {
        this.getPeer().setLetterSpacingAttribute(value);
        this.markDirty();
        return this;
    }
    lineHeight(value: double | string | Resource | undefined): this {
        this.getPeer().setLineHeightAttribute(value);
        this.markDirty();
        return this;
    }
    passwordRules(value: string | undefined): this {
        this.getPeer().setPasswordRulesAttribute(value);
        this.markDirty();
        return this;
    }
    fontFeature(value: string | undefined): this {
        this.getPeer().setFontFeatureAttribute(value);
        this.markDirty();
        return this;
    }
    showPassword(value: boolean | undefined): this {
        this.getPeer().setShowPasswordAttribute(value);
        this.markDirty();
        return this;
    }
    onSecurityStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        this.getPeer().setOnSecurityStateChangeAttribute(value);
        this.markDirty();
        return this;
    }
    onWillInsert(value: ((parameter: InsertValue) => boolean) | undefined): this {
        this.getPeer().setOnWillInsertAttribute(value);
        this.markDirty();
        return this;
    }
    onDidInsert(value: ((parameter: InsertValue) => void) | undefined): this {
        this.getPeer().setOnDidInsertAttribute(value);
        this.markDirty();
        return this;
    }
    onWillDelete(value: ((parameter: DeleteValue) => boolean) | undefined): this {
        this.getPeer().setOnWillDeleteAttribute(value);
        this.markDirty();
        return this;
    }
    onDidDelete(value: ((parameter: DeleteValue) => void) | undefined): this {
        this.getPeer().setOnDidDeleteAttribute(value);
        this.markDirty();
        return this;
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        this.getPeer().setEditMenuOptionsAttribute(value);
        this.markDirty();
        return this;
    }
    enablePreviewText(value: boolean | undefined): this {
        this.getPeer().setEnablePreviewTextAttribute(value);
        this.markDirty();
        return this;
    }
    enableHapticFeedback(value: boolean | undefined): this {
        this.getPeer().setEnableHapticFeedbackAttribute(value);
        this.markDirty();
        return this;
    }
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        this.getPeer().setAutoCapitalizationModeAttribute(value);
        this.markDirty();
        return this;
    }
    halfLeading(value: boolean | undefined): this {
        this.getPeer().setHalfLeadingAttribute(value);
        this.markDirty();
        return this;
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        this.getPeer().setEllipsisModeAttribute(value);
        this.markDirty();
        return this;
    }
    stopBackPress(value: boolean | undefined): this {
        this.getPeer().setStopBackPressAttribute(value);
        this.markDirty();
        return this;
    }
    onWillChange(value: ((parameter: EditableTextChangeValue) => boolean) | undefined): this {
        this.getPeer().setOnWillChangeAttribute(value);
        this.markDirty();
        return this;
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        this.getPeer().setKeyboardAppearanceAttribute(value);
        this.markDirty();
        return this;
    }
    inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().setInputFilterAttribute(value, error);
        this.markDirty();
        return this;
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions | undefined): this {
        this.getPeer().setCustomKeyboardAttribute(value, options);
        this.markDirty();
        return this;
    }
    showCounter(value: boolean | undefined, options?: InputCounterOptions | undefined): this {
        this.getPeer().setShowCounterAttribute(value, options);
        this.markDirty();
        return this;
    }
}