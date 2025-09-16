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
import { AutoCapitalizationMode, FontWeight, Length, ResourceStr, Dimension, ResourceColor, BarState, CaretStyle, ContentType, CopyOptions, CustomBuilder, DeleteValue, EditMenuOptions, EditableTextChangeValue, EditableTextOnChangeCallback, EllipsisMode, EnterKeyType, Font, FontStyle, InputCounterOptions, InsertValue, KeyboardAppearance, KeyboardOptions, LineBreakStrategy, PasteEvent, TextAlign, TextAreaAttribute, TextAreaSubmitCallback, TextAreaType, TextContentStyle, TextDecorationOptions, TextHeightAdaptivePolicy, TextOverflow, WordBreak } from "../../component";
import { ArkTextAreaPeer, TextAreaOptions } from "../../component";
import { LengthMetrics } from "../../Graphics";
import { Resource } from "global.resource"

export class ArkTextAreaNode extends ArkBaseNode  implements TextAreaAttribute  {
    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog("textArea constructParam enter")
        return this;
    }
    getPeer() : ArkTextAreaPeer {
        return this.peer as ArkTextAreaPeer
    }
    initialize(options?: TextAreaOptions): this {
        const options_casted = options as (TextAreaOptions | undefined)
            this.getPeer()?.setTextAreaOptionsAttribute(options_casted)
        return this;
    }
    allowChildTypes(): string[] {
        return ["TextAreaItem", "TextAreaItemGroup"];
    }
    placeholderColor(value: ResourceColor | undefined): this {
        this.getPeer().placeholderColorAttribute(value);
        return this;
    }
    placeholderFont(value: Font | undefined): this {
        this.getPeer().placeholderFontAttribute(value);
        return this;
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        this.getPeer().enterKeyTypeAttribute(value);
        return this;
    }
    textAlign(value: TextAlign | undefined): this {
        this.getPeer().textAlignAttribute(value);
        return this;
    }
    caretColor(value: ResourceColor | undefined): this {
        this.getPeer().caretColorAttribute(value);
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        this.getPeer().fontColorAttribute(value);
        return this;
    }
    fontSize(value: Length | undefined): this {
        this.getPeer().fontSizeAttribute(value);
        return this;
    }
    fontStyle(value: FontStyle | undefined): this {
        this.getPeer().fontStyleAttribute(value);
        return this;
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        this.getPeer().fontWeightAttribute(value);
        return this;
    }
    fontFamily(value: ResourceStr | undefined): this {
        this.getPeer().fontFamilyAttribute(value);
        return this;
    }
    textOverflow(value: TextOverflow | undefined): this {
        this.getPeer().textOverflowAttribute(value);
        return this;
    }
    textIndent(value: Dimension | undefined): this {
        this.getPeer().textIndentAttribute(value);
        return this;
    }
    caretStyle(value: CaretStyle | undefined): this {
        this.getPeer().caretStyleAttribute(value);
        return this;
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        this.getPeer().selectedBackgroundColorAttribute(value);
        return this;
    }
    onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined): this {
        // todo: type check
        // this.getPeer().onSubmit0Attribute(value);
        // this.getPeer().onSubmit1Attribute(value);
        return this;
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        this.getPeer().onChangeAttribute(value);
        return this;
    }
    onTextSelectionChange(value: ((first: number, last: number) => void) | undefined): this {
        this.getPeer().onTextSelectionChangeAttribute(value);
        return this;
    }
    onContentScroll(value: ((first: number, last: number) => void) | undefined): this {
        this.getPeer().onContentScrollAttribute(value);
        return this;
    }
    onEditChange(value: ((isVisible: boolean) => void) | undefined): this {
        this.getPeer().onEditChangeAttribute(value);
        return this;
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().onCopyAttribute(value);
        return this;
    }
    onCut(value: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().onCutAttribute(value);
        return this;
    }
    onPaste(value: ((value: string, event: PasteEvent) => void) | undefined): this {
        this.getPeer().onPasteAttribute(value);
        return this;
    }
    copyOption(value: CopyOptions | undefined): this {
        this.getPeer().copyOptionAttribute(value);
        return this;
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        this.getPeer().enableKeyboardOnFocusAttribute(value);
        return this;
    }
    maxLength(value: number | undefined): this {
        this.getPeer().maxLengthAttribute(value);
        return this;
    }
    style(value: TextContentStyle | undefined): this {
        this.getPeer().styleAttribute(value);
        return this;
    }
    barState(value: BarState | undefined): this {
        this.getPeer().barStateAttribute(value);
        return this;
    }
    selectionMenuHidden(value: boolean | undefined): this {
        this.getPeer().selectionMenuHiddenAttribute(value);
        return this;
    }
    minFontSize(value: number | string | Resource | undefined): this {
        this.getPeer().minFontSizeAttribute(value);
        return this;
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        this.getPeer().maxFontSizeAttribute(value);
        return this;
    }
    minFontScale(value: number | Resource | undefined): this {
        this.getPeer().minFontScaleAttribute(value);
        return this;
    }
    maxFontScale(value: number | Resource | undefined): this {
        this.getPeer().maxFontScaleAttribute(value);
        return this;
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        this.getPeer().heightAdaptivePolicyAttribute(value);
        return this;
    }
    maxLines(value: number | undefined): this {
        this.getPeer().maxLinesAttribute(value);
        return this;
    }
    wordBreak(value: WordBreak | undefined): this {
        this.getPeer().wordBreakAttribute(value);
        return this;
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        this.getPeer().lineBreakStrategyAttribute(value);
        return this;
    }
    decoration(value: TextDecorationOptions | undefined): this {
        this.getPeer().decorationAttribute(value);
        return this;
    }
    letterSpacing(value: number | string | Resource | undefined): this {
        this.getPeer().letterSpacingAttribute(value);
        return this;
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        this.getPeer().lineSpacingAttribute(value);
        return this;
    }
    lineHeight(value: number | string | Resource | undefined): this {
        this.getPeer().lineHeightAttribute(value);
        return this;
    }
    type(value: TextAreaType | undefined): this {
        this.getPeer().typeAttribute(value);
        return this;
    }
    enableAutoFill(value: boolean | undefined): this {
        this.getPeer().enableAutoFillAttribute(value);
        return this;
    }
    contentType(value: ContentType | undefined): this {
        this.getPeer().contentTypeAttribute(value);
        return this;
    }
    fontFeature(value: string | undefined): this {
        this.getPeer().fontFeatureAttribute(value);
        return this;
    }
    onWillInsert(value: ((parameter: InsertValue) => boolean) | undefined): this {
        this.getPeer().onWillInsertAttribute(value);
        return this;
    }
    onDidInsert(value: ((parameter: InsertValue) => void) | undefined): this {
        this.getPeer().onDidInsertAttribute(value);
        return this;
    }
    onWillDelete(value: ((parameter: DeleteValue) => boolean) | undefined): this {
        this.getPeer().onWillDeleteAttribute(value);
        return this;
    }
    onDidDelete(value: ((parameter: DeleteValue) => void) | undefined): this {
        this.getPeer().onDidDeleteAttribute(value);
        return this;
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        this.getPeer().editMenuOptionsAttribute(value);
        return this;
    }
    enablePreviewText(value: boolean | undefined): this {
        this.getPeer().enablePreviewTextAttribute(value);
        return this;
    }
    enableHapticFeedback(value: boolean | undefined): this {
        this.getPeer().enableHapticFeedbackAttribute(value);
        return this;
    }
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        this.getPeer().autoCapitalizationModeAttribute(value);
        return this;
    }
    halfLeading(value: boolean | undefined): this {
        this.getPeer().halfLeadingAttribute(value);
        return this;
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        this.getPeer().ellipsisModeAttribute(value);
        return this;
    }
    stopBackPress(value: boolean | undefined): this {
        this.getPeer().stopBackPressAttribute(value);
        return this;
    }
    onWillChange(value: ((parameter: EditableTextChangeValue) => boolean) | undefined): this {
        this.getPeer().onWillChangeAttribute(value);
        return this;
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        this.getPeer().keyboardAppearanceAttribute(value);
        return this;
    }
    inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void) | undefined): this {
        this.getPeer().inputFilterAttribute(value, error);
        return this;
    }
    showCounter(value: boolean | undefined, options?: InputCounterOptions | undefined): this {
        this.getPeer().showCounterAttribute(value, options);
        return this;
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions | undefined): this {
        this.getPeer().customKeyboardAttribute(value, options);
        return this;
    }
    _onChangeEvent_text(callback: (text: ResourceStr) => void): void {
        this.getPeer()._onChangeEvent_textAttribute(callback);
        return;
    }
}