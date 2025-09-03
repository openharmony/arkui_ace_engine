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

import { InteropNativeModule } from "@koalaui/interop";

import { ArkBaseNode } from "./ArkBaseNode";
import { AutoCapitalizationMode, FontWeight, UnderlineColor, Length, ResourceStr, Dimension, ResourceColor, BarState, CancelButtonOptions, CancelButtonSymbolOptions, CaretStyle, ContentType, CopyOptions, CustomBuilder, DeleteValue, EditMenuOptions, EditableTextChangeValue, EditableTextOnChangeCallback, EllipsisMode, EnterKeyType, Font, FontStyle, InputCounterOptions, InputType, InsertValue, KeyboardAppearance, KeyboardOptions, LineBreakStrategy, OnContentScrollCallback, OnPasteCallback, OnSubmitCallback, OnTextSelectionChangeCallback, PasswordIcon, TextAlign, TextContentStyle, TextDecorationOptions, TextHeightAdaptivePolicy, TextInputAttribute, TextInputStyle, TextOverflow, WordBreak } from "../../component";
import { ArkTextInputPeer, TextInputOptions } from "../../component";
import { LengthMetrics } from "../../Graphics";
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
        this.getPeer().typeAttribute(value);
        this.markDirty();
        return this;
    }
    contentType(value: ContentType | undefined): this {
        this.getPeer().contentTypeAttribute(value);
        this.markDirty();
        return this;
    }
    placeholderColor(value: ResourceColor | undefined): this {
        this.getPeer().placeholderColorAttribute(value);
        this.markDirty();
        return this;
    }
    textOverflow(value: TextOverflow | undefined): this {
        this.getPeer().textOverflowAttribute(value);
        this.markDirty();
        return this;
    }
    textIndent(value: Dimension | undefined): this {
        this.getPeer().textIndentAttribute(value);
        this.markDirty();
        return this;
    }
    placeholderFont(value: Font | undefined): this {
        this.getPeer().placeholderFontAttribute(value);
        this.markDirty();
        return this;
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        this.getPeer().enterKeyTypeAttribute(value);
        this.markDirty();
        return this;
    }
    caretColor(value: ResourceColor | undefined): this {
        this.getPeer().caretColorAttribute(value);
        this.markDirty();
        return this;
    }
    onEditChanged(value: ((isVisible: boolean) => void) | undefined): this {
        this.getPeer().onEditChangedAttribute(value);
        this.markDirty();
        return this;
    }
    onEditChange(value: ((isVisible: boolean) => void) | undefined): this {
        this.getPeer().onEditChangeAttribute(value);
        this.markDirty();
        return this;
    }
    onSubmit(value: OnSubmitCallback | undefined): this {
        this.getPeer().onSubmitAttribute(value);
        this.markDirty();
        return this;
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        this.getPeer().onChangeAttribute(value);
        this.markDirty();
        return this;
    }
    onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        this.getPeer().onTextSelectionChangeAttribute(value);
        this.markDirty();
        return this;
    }
    onContentScroll(value: OnContentScrollCallback | undefined): this {
        this.getPeer().onContentScrollAttribute(value);
        this.markDirty();
        return this;
    }
    maxLength(value: number | undefined): this {
        this.getPeer().maxLengthAttribute(value);
        this.markDirty();
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        this.getPeer().fontColorAttribute(value);
        this.markDirty();
        return this;
    }
    fontSize(value: Length | undefined): this {
        this.getPeer().fontSizeAttribute(value);
        this.markDirty();
        return this;
    }
    fontStyle(value: FontStyle | undefined): this {
        this.getPeer().fontStyleAttribute(value);
        this.markDirty();
        return this;
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        this.getPeer().fontWeightAttribute(value);
        this.markDirty();
        return this;
    }
    fontFamily(value: ResourceStr | undefined): this {
        this.getPeer().fontFamilyAttribute(value);
        this.markDirty();
        return this;
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().onCopyAttribute(value);
        this.markDirty();
        return this;
    }
    onCut(value: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().onCutAttribute(value);
        this.markDirty();
        return this;
    }
    onPaste(value: OnPasteCallback | undefined): this {
        this.getPeer().onPasteAttribute(value);
        this.markDirty();
        return this;
    }
    copyOption(value: CopyOptions | undefined): this {
        this.getPeer().copyOptionAttribute(value);
        this.markDirty();
        return this;
    }
    showPasswordIcon(value: boolean | undefined): this {
        this.getPeer().showPasswordIconAttribute(value);
        this.markDirty();
        return this;
    }
    textAlign(value: TextAlign | undefined): this {
        this.getPeer().textAlignAttribute(value);
        this.markDirty();
        return this;
    }
    style(value: TextContentStyle | TextInputStyle | undefined): this {
        this.getPeer().styleAttribute(value);
        this.markDirty();
        return this;
    }
    caretStyle(value: CaretStyle | undefined): this {
        this.getPeer().caretStyleAttribute(value);
        this.markDirty();
        return this;
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        this.getPeer().selectedBackgroundColorAttribute(value);
        this.markDirty();
        return this;
    }
    caretPosition(value: number | undefined): this {
        this.getPeer().caretPositionAttribute(value);
        this.markDirty();
        return this;
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        this.getPeer().enableKeyboardOnFocusAttribute(value);
        this.markDirty();
        return this;
    }
    passwordIcon(value: PasswordIcon | undefined): this {
        this.getPeer().passwordIconAttribute(value);
        this.markDirty();
        return this;
    }
    showError(value: ResourceStr | undefined): this {
        this.getPeer().showErrorAttribute(value);
        this.markDirty();
        return this;
    }
    showUnit(value: CustomBuilder | undefined): this {
        this.getPeer().showUnitAttribute(value);
        this.markDirty();
        return this;
    }
    showUnderline(value: boolean | undefined): this {
        this.getPeer().showUnderlineAttribute(value);
        this.markDirty();
        return this;
    }
    underlineColor(value: ResourceColor | UnderlineColor | undefined): this {
        this.getPeer().underlineColorAttribute(value);
        this.markDirty();
        return this;
    }
    selectionMenuHidden(value: boolean | undefined): this {
        this.getPeer().selectionMenuHiddenAttribute(value);
        this.markDirty();
        return this;
    }
    barState(value: BarState | undefined): this {
        this.getPeer().barStateAttribute(value);
        this.markDirty();
        return this;
    }
    maxLines(value: number | undefined): this {
        this.getPeer().maxLinesAttribute(value);
        this.markDirty();
        return this;
    }
    wordBreak(value: WordBreak | undefined): this {
        this.getPeer().wordBreakAttribute(value);
        this.markDirty();
        return this;
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        this.getPeer().lineBreakStrategyAttribute(value);
        this.markDirty();
        return this;
    }
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        if ((value === undefined) || (value instanceof CancelButtonOptions)) {
            const value_casted = value as (CancelButtonOptions | undefined)
            this.getPeer()?.cancelButton0Attribute(value_casted)
            this.markDirty();
            return this
        }
        if ((value === undefined) || (value instanceof CancelButtonSymbolOptions)) {
            const value_casted = value as (CancelButtonSymbolOptions | undefined)
            this.getPeer()?.cancelButton1Attribute(value_casted)
            this.markDirty();
            return this
        }
        return this;
    }
    selectAll(value: boolean | undefined): this {
        this.getPeer().selectAllAttribute(value);
        this.markDirty();
        return this;
    }
    minFontSize(value: number | string | Resource | undefined): this {
        this.getPeer().minFontSizeAttribute(value);
        this.markDirty();
        return this;
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        this.getPeer().maxFontSizeAttribute(value);
        this.markDirty();
        return this;
    }
    minFontScale(value: number | Resource | undefined): this {
        this.getPeer().minFontScaleAttribute(value);
        this.markDirty();
        return this;
    }
    maxFontScale(value: number | Resource | undefined): this {
        this.getPeer().maxFontScaleAttribute(value);
        this.markDirty();
        return this;
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        this.getPeer().heightAdaptivePolicyAttribute(value);
        this.markDirty();
        return this;
    }
    enableAutoFill(value: boolean | undefined): this {
        this.getPeer().enableAutoFillAttribute(value);
        this.markDirty();
        return this;
    }
    decoration(value: TextDecorationOptions | undefined): this {
        this.getPeer().decorationAttribute(value);
        this.markDirty();
        return this;
    }
    letterSpacing(value: number | string | Resource | undefined): this {
        this.getPeer().letterSpacingAttribute(value);
        this.markDirty();
        return this;
    }
    lineHeight(value: number | string | Resource | undefined): this {
        this.getPeer().lineHeightAttribute(value);
        this.markDirty();
        return this;
    }
    passwordRules(value: string | undefined): this {
        this.getPeer().passwordRulesAttribute(value);
        this.markDirty();
        return this;
    }
    fontFeature(value: string | undefined): this {
        this.getPeer().fontFeatureAttribute(value);
        this.markDirty();
        return this;
    }
    showPassword(value: boolean | undefined): this {
        this.getPeer().showPasswordAttribute(value);
        this.markDirty();
        return this;
    }
    onSecurityStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        this.getPeer().onSecurityStateChangeAttribute(value);
        this.markDirty();
        return this;
    }
    onWillInsert(value: ((parameter: InsertValue) => boolean) | undefined): this {
        this.getPeer().onWillInsertAttribute(value);
        this.markDirty();
        return this;
    }
    onDidInsert(value: ((parameter: InsertValue) => void) | undefined): this {
        this.getPeer().onDidInsertAttribute(value);
        this.markDirty();
        return this;
    }
    onWillDelete(value: ((parameter: DeleteValue) => boolean) | undefined): this {
        this.getPeer().onWillDeleteAttribute(value);
        this.markDirty();
        return this;
    }
    onDidDelete(value: ((parameter: DeleteValue) => void) | undefined): this {
        this.getPeer().onDidDeleteAttribute(value);
        this.markDirty();
        return this;
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        this.getPeer().editMenuOptionsAttribute(value);
        this.markDirty();
        return this;
    }
    enablePreviewText(value: boolean | undefined): this {
        this.getPeer().enablePreviewTextAttribute(value);
        this.markDirty();
        return this;
    }
    enableHapticFeedback(value: boolean | undefined): this {
        this.getPeer().enableHapticFeedbackAttribute(value);
        this.markDirty();
        return this;
    }
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        this.getPeer().autoCapitalizationModeAttribute(value);
        this.markDirty();
        return this;
    }
    halfLeading(value: boolean | undefined): this {
        this.getPeer().halfLeadingAttribute(value);
        this.markDirty();
        return this;
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        this.getPeer().ellipsisModeAttribute(value);
        this.markDirty();
        return this;
    }
    stopBackPress(value: boolean | undefined): this {
        this.getPeer().stopBackPressAttribute(value);
        this.markDirty();
        return this;
    }
    onWillChange(value: ((parameter: EditableTextChangeValue) => boolean) | undefined): this {
        this.getPeer().onWillChangeAttribute(value);
        this.markDirty();
        return this;
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        this.getPeer().keyboardAppearanceAttribute(value);
        this.markDirty();
        return this;
    }
    inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().inputFilterAttribute(value, error);
        this.markDirty();
        return this;
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions | undefined): this {
        this.getPeer().customKeyboardAttribute(value, options);
        this.markDirty();
        return this;
    }
    showCounter(value: boolean | undefined, options?: InputCounterOptions | undefined): this {
        this.getPeer().showCounterAttribute(value, options);
        this.markDirty();
        return this;
    }
    _onChangeEvent_text(callback: (text: ResourceStr) => void): void {
        this.getPeer()._onChangeEvent_textAttribute(callback);
        this.markDirty();
        return;
    }
}