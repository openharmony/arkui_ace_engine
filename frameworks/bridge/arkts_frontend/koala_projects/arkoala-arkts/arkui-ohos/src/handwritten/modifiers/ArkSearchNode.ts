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
import { SearchAttribute, ResourceColor, IconOptions, KeyboardOptions, CopyOptions,
    TextAlign, SearchSubmitCallback, CancelButtonOptions, CancelButtonSymbolOptions, CaretStyle, Dimension, Font,
    EnterKeyType, EditableTextOnChangeCallback, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback,
    TextDecorationOptions, SearchType, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode,
    EditableTextChangeValue, KeyboardAppearance, SearchButtonOptions, ResourceStr, CustomBuilder } from "../../component";
import { SymbolGlyphModifier } from "../../SymbolGlyphModifier";
import { ArkSearchPeer, SearchOptions } from "../../component";
import { Resource } from "global.resource"

export class ArkSearchNode extends ArkBaseNode  implements SearchAttribute  {
    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog("search constructParam enter")
        return this;
    }
    getPeer() : ArkSearchPeer {
        return this.peer as ArkSearchPeer
    }
    initialize(options?: SearchOptions): this {
        const options_casted = options as (SearchOptions | undefined)
            this.getPeer()?.setSearchOptionsAttribute(options_casted)
        this.markDirty();
        return this;
    }
    allowChildTypes(): string[] {
        return ["SearchItem", "SearchItemGroup"];
    }
    setSearchOptions(options?: SearchOptions): this {
        this.getPeer().setSearchOptionsAttribute(options);
        this.markDirty();
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        this.getPeer().fontColorAttribute(value);
        this.markDirty();
        return this;
    }
    searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        this.getPeer().searchIconAttribute(value);
        this.markDirty();
        return this;
    }
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        this.getPeer().cancelButtonAttribute(value);
        this.markDirty();
        return this;
    }
    textIndent(value: Dimension | undefined): this {
        this.getPeer().textIndentAttribute(value);
        this.markDirty();
        return this;
    }
    onEditChange(value: ((isVisible: boolean) => void) | undefined): this {
        this.getPeer().onEditChangeAttribute(value);
        this.markDirty();
        return this;
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        this.getPeer().selectedBackgroundColorAttribute(value);
        this.markDirty();
        return this;
    }
    caretStyle(value: CaretStyle | undefined): this {
        this.getPeer().caretStyleAttribute(value);
        this.markDirty();
        return this;
    }
    placeholderColor(value: ResourceColor | undefined): this {
        this.getPeer().placeholderColorAttribute(value);
        this.markDirty();
        return this;
    }
    placeholderFont(value: Font | undefined): this {
        this.getPeer().placeholderFontAttribute(value);
        this.markDirty();
        return this;
    }
    textFont(value: Font | undefined): this {
        this.getPeer().textFontAttribute(value);
        this.markDirty();
        return this;
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        this.getPeer().enterKeyTypeAttribute(value);
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
    maxLength(value: number | undefined): this {
        this.getPeer().maxLengthAttribute(value);
        this.markDirty();
        return this;
    }
    textAlign(value: TextAlign | undefined): this {
        this.getPeer().textAlignAttribute(value);
        this.markDirty();
        return this;
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        this.getPeer().enableKeyboardOnFocusAttribute(value);
        this.markDirty();
        return this;
    }
    selectionMenuHidden(value: boolean | undefined): this {
        this.getPeer().selectionMenuHiddenAttribute(value);
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
    type(value: SearchType | undefined): this {
        this.getPeer().typeAttribute(value);
        this.markDirty();
        return this;
    }
    fontFeature(value: string | undefined): this {
        this.getPeer().fontFeatureAttribute(value);
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
    searchButton(value: string | undefined, option?: SearchButtonOptions): this {
        this.getPeer().searchButtonAttribute(value);
        this.markDirty();
        return this;
    }
    inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void)): this {
        this.getPeer().inputFilterAttribute(value, error);
        this.markDirty();
        return this;
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        this.getPeer().customKeyboardAttribute(value, options);
        this.markDirty();
        return this;
    }
    onSubmit(value: SearchSubmitCallback | ((breakpoints: string) => void) | undefined): this {
        const value_casted = value as (SearchSubmitCallback | undefined)
        this.getPeer()?.onSubmit1Attribute(value_casted)
        this.markDirty();
        return this;
    }
    _onChangeEvent_value(callback: (breakpoints: string) => void): void {
        this.getPeer()._onChangeEvent_valueAttribute(callback);
        this.markDirty();
        return;
    }
}