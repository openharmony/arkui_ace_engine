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
import { SearchAttribute, ResourceColor, IconOptions, KeyboardOptions, CopyOptions,
    TextAlign, SearchSubmitCallback, CancelButtonOptions, CancelButtonSymbolOptions, CaretStyle, Dimension, Font,
    EnterKeyType, EditableTextOnChangeCallback, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback,
    TextDecorationOptions, SearchType, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode,
    EditableTextChangeValue, KeyboardAppearance, SearchButtonOptions, ResourceStr, CustomBuilder } from "../framework";
import { SymbolGlyphModifier } from "../SymbolGlyphModifier";
import { ArkSearchPeer, SearchOptions } from "../framework";
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
        this.getPeer().setFontColorAttribute(value);
        this.markDirty();
        return this;
    }
    searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        this.getPeer().setSearchIconAttribute(value);
        this.markDirty();
        return this;
    }
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        this.getPeer().setCancelButtonAttribute(value);
        this.markDirty();
        return this;
    }
    textIndent(value: Dimension | undefined): this {
        this.getPeer().setTextIndentAttribute(value);
        this.markDirty();
        return this;
    }
    onEditChange(value: ((isVisible: boolean) => void) | undefined): this {
        this.getPeer().setOnEditChangeAttribute(value);
        this.markDirty();
        return this;
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        this.getPeer().setSelectedBackgroundColorAttribute(value);
        this.markDirty();
        return this;
    }
    caretStyle(value: CaretStyle | undefined): this {
        this.getPeer().setCaretStyleAttribute(value);
        this.markDirty();
        return this;
    }
    placeholderColor(value: ResourceColor | undefined): this {
        this.getPeer().setPlaceholderColorAttribute(value);
        this.markDirty();
        return this;
    }
    placeholderFont(value: Font | undefined): this {
        this.getPeer().setPlaceholderFontAttribute(value);
        this.markDirty();
        return this;
    }
    textFont(value: Font | undefined): this {
        this.getPeer().setTextFontAttribute(value);
        this.markDirty();
        return this;
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        this.getPeer().setEnterKeyTypeAttribute(value);
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
    maxLength(value: int32 | undefined): this {
        this.getPeer().setMaxLengthAttribute(value);
        this.markDirty();
        return this;
    }
    textAlign(value: TextAlign | undefined): this {
        this.getPeer().setTextAlignAttribute(value);
        this.markDirty();
        return this;
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        this.getPeer().setEnableKeyboardOnFocusAttribute(value);
        this.markDirty();
        return this;
    }
    selectionMenuHidden(value: boolean | undefined): this {
        this.getPeer().setSelectionMenuHiddenAttribute(value);
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
    type(value: SearchType | undefined): this {
        this.getPeer().setTypeAttribute(value);
        this.markDirty();
        return this;
    }
    fontFeature(value: string | undefined): this {
        this.getPeer().setFontFeatureAttribute(value);
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
    searchButton(value: string | undefined, option?: SearchButtonOptions): this {
        this.getPeer().setSearchButtonAttribute(value);
        this.markDirty();
        return this;
    }
    inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void)): this {
        this.getPeer().setInputFilterAttribute(value, error);
        this.markDirty();
        return this;
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        this.getPeer().setCustomKeyboardAttribute(value, options);
        this.markDirty();
        return this;
    }
    onSubmit(value: SearchSubmitCallback | ((breakpoints: string) => void) | undefined): this {
        const value_casted = value as (SearchSubmitCallback | undefined)
        this.getPeer()?.setOnSubmitAttribute(value_casted)
        this.markDirty();
        return this;
    }
}