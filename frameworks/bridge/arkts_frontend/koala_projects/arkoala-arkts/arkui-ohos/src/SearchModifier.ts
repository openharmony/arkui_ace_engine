/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import { int32 } from '@koalaui/common';
import { KPointer, RuntimeType, runtimeType } from '@koalaui/interop';
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { AttributeModifier, CommonMethod, TextDecorationOptions } from './component/common';
import { ResourceColor, Dimension, Font, ResourceStr } from './component/units';
import { Color, CopyOptions, TextAlign } from './component/enums';
import { Resource } from 'global.resource';
import { IconOptions, CancelButtonOptions, CancelButtonSymbolOptions, SearchSubmitCallback, SearchType, SearchAttribute, SearchButtonOptions } from './component/search';
import { SymbolGlyphModifier } from './SymbolGlyphModifier';
import { CaretStyle, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode, EditableTextChangeValue, KeyboardAppearance } from './component/textCommon';
import { EnterKeyType, SubmitEvent, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback } from './component/textInput';
import { PasteEvent, KeyboardOptions } from './component/richEditor';
import { ShadowOptions, CustomBuilder } from './component/common';
import { ArkSearchPeer, SearchOptions } from './component/search';
import { PeerNode } from './PeerNode';

export class SearchModifier extends CommonMethodModifier implements SearchAttribute, AttributeModifier<SearchAttribute> {

    applyNormalAttribute(instance: SearchAttribute): void { }
    applyPressedAttribute(instance: SearchAttribute): void { }
    applyFocusedAttribute(instance: SearchAttribute): void { }
    applyDisabledAttribute(instance: SearchAttribute): void { }
    applySelectedAttribute(instance: SearchAttribute): void { }

    _setSearchOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setSearchOptions_0_0value?: SearchOptions | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _searchIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _searchIcon_0_0value?: IconOptions | SymbolGlyphModifier | undefined
    _cancelButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cancelButton_0_0value?: CancelButtonOptions | CancelButtonSymbolOptions | undefined
    _textIndent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textIndent_0_0value?: Dimension | undefined
    _onEditChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onEditChange_0_0value?: ((value0: boolean) => void) | undefined
    _selectedBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    _caretStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _caretStyle_0_0value?: CaretStyle | undefined
    _placeholderColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _placeholderColor_0_0value?: ResourceColor | undefined
    _placeholderFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _placeholderFont_0_0value?: Font | undefined
    _textFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textFont_0_0value?: Font | undefined
    _enterKeyType_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enterKeyType_0_0value?: EnterKeyType | undefined
    _onSubmit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSubmit_0_0value?: ((value0: string) => void) | SearchSubmitCallback | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: EditableTextOnChangeCallback | undefined
    _onTextSelectionChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTextSelectionChange_0_0value?: OnTextSelectionChangeCallback | undefined
    _onContentScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentScroll_0_0value?: OnContentScrollCallback | undefined
    _onCopy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCopy_0_0value?: ((value0: string) => void) | undefined
    _onCut_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCut_0_0value?: ((value0: string) => void) | undefined
    _onPaste_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPaste_0_0value?: OnPasteCallback | undefined
    _copyOption_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOption_0_0value?: CopyOptions | undefined
    _maxLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLength_0_0value?: number | undefined
    _textAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textAlign_0_0value?: TextAlign | undefined
    _enableKeyboardOnFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableKeyboardOnFocus_0_0value?: boolean | undefined
    _selectionMenuHidden_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectionMenuHidden_0_0value?: boolean | undefined
    _minFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontSize_0_0value?: number | string | Resource | undefined
    _maxFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontSize_0_0value?: number | string | Resource | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: number | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: number | Resource | undefined
    _decoration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _decoration_0_0value?: TextDecorationOptions | undefined
    _letterSpacing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _letterSpacing_0_0value?: number | string | Resource | undefined
    _lineHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineHeight_0_0value?: number | string | Resource | undefined
    _type_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _type_0_0value?: SearchType | undefined
    _fontFeature_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFeature_0_0value?: string | undefined
    _onWillInsert_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillInsert_0_0value?: ((value0: InsertValue) => boolean) | undefined
    _onDidInsert_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidInsert_0_0value?: ((value0: InsertValue) => void) | undefined
    _onWillDelete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillDelete_0_0value?: ((value0: DeleteValue) => boolean) | undefined
    _onDidDelete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidDelete_0_0value?: ((value0: DeleteValue) => void) | undefined
    _editMenuOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMenuOptions_0_0value?: EditMenuOptions | undefined
    _enablePreviewText_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enablePreviewText_0_0value?: boolean | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _autoCapitalizationMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoCapitalizationMode_0_0value?: AutoCapitalizationMode | undefined
    _halfLeading_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _halfLeading_0_0value?: boolean | undefined
    _stopBackPress_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stopBackPress_0_0value?: boolean | undefined
    _onWillChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillChange_0_0value?: ((value0: EditableTextChangeValue) => boolean) | undefined
    _keyboardAppearance_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _keyboardAppearance_0_0value?: KeyboardAppearance | undefined
    _searchButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _searchButton_0_0value?: string | undefined
    _searchButton_0_1value?: SearchButtonOptions | undefined
    _inputFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _inputFilter_0_0value?: ResourceStr | undefined
    _inputFilter_0_1value?: ((value0: string) => void) | undefined
    _customKeyboard_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customKeyboard_0_0value?: CustomBuilder | undefined
    _customKeyboard_0_1value?: KeyboardOptions | undefined

    _onChangeEvent_value(callback: ((breakpoints: string) => void)): void {
        // todo
    }

    public setSearchOptions(value: SearchOptions | undefined): this {
        if (((this._setSearchOptions_0_flag) == (AttributeUpdaterFlag.INITIAL))  ||
            this._setSearchOptions_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._setSearchOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._setSearchOptions_0_0value = value
        } else {
            this._setSearchOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._fontColor_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        if (((this._searchIcon_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._searchIcon_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._searchIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._searchIcon_0_0value = value
        } else {
            this._searchIcon_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        if (((this._cancelButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._cancelButton_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._cancelButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._cancelButton_0_0value = value
        } else {
            this._cancelButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public textIndent(value: Dimension | undefined): this {
        if (((this._textIndent_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._textIndent_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._textIndent_0_flag = AttributeUpdaterFlag.UPDATE
            this._textIndent_0_0value = value
        } else {
            this._textIndent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onEditChange(value: ((value0: boolean) => void) | undefined): this {
        if (((this._onEditChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onEditChange_0_0value !== value) {
            this._onEditChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onEditChange_0_0value = value
        } else {
            this._onEditChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._selectedBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._selectedBackgroundColor_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedBackgroundColor_0_0value = value
        } else {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public caretStyle(value: CaretStyle | undefined): this {
        if (((this._caretStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._caretStyle_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._caretStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._caretStyle_0_0value = value
        } else {
            this._caretStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public placeholderColor(value: ResourceColor | undefined): this {
        if (((this._placeholderColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._placeholderColor_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._placeholderColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._placeholderColor_0_0value = value
        } else {
            this._placeholderColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public placeholderFont(value: Font | undefined): this {
        if (((this._placeholderFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._placeholderFont_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._placeholderFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._placeholderFont_0_0value = value
        } else {
            this._placeholderFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public textFont(value: Font | undefined): this {
        if (((this._textFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._textFont_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._textFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._textFont_0_0value = value
        } else {
            this._textFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public enterKeyType(value: EnterKeyType | undefined): this {
        if (((this._enterKeyType_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._enterKeyType_0_0value !== value) {
            this._enterKeyType_0_flag = AttributeUpdaterFlag.UPDATE
            this._enterKeyType_0_0value = value
        } else {
            this._enterKeyType_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        if (((this._onSubmit_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onSubmit_0_0value !== value) {
            this._onSubmit_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSubmit_0_0value = value
        } else {
            this._onSubmit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onChange_0_0value !== value) {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        if (((this._onTextSelectionChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onTextSelectionChange_0_0value !== value) {
            this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTextSelectionChange_0_0value = value
        } else {
            this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onContentScroll(value: OnContentScrollCallback | undefined): this {
        if (((this._onContentScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onContentScroll_0_0value !== value) {
            this._onContentScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentScroll_0_0value = value
        } else {
            this._onContentScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onCopy(value: ((value0: string) => void) | undefined): this {
        if (((this._onCopy_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onCopy_0_0value !== value) {
            this._onCopy_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCopy_0_0value = value
        } else {
            this._onCopy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onCut(value: ((value0: string) => void) | undefined): this {
        if (((this._onCut_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onCut_0_0value !== value) {
            this._onCut_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCut_0_0value = value
        } else {
            this._onCut_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onPaste(value: OnPasteCallback | undefined): this {
        if (((this._onPaste_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onPaste_0_0value !== value) {
            this._onPaste_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPaste_0_0value = value
        } else {
            this._onPaste_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public copyOption(value: CopyOptions | undefined): this {
        if (((this._copyOption_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._copyOption_0_0value !== value) {
            this._copyOption_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOption_0_0value = value
        } else {
            this._copyOption_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public maxLength(value: number | undefined): this {
        if (((this._maxLength_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._maxLength_0_0value) !== (value))) {
            this._maxLength_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxLength_0_0value = value
        } else {
            this._maxLength_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public textAlign(value: TextAlign | undefined): this {
        if (((this._textAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._textAlign_0_0value !== value) {
            this._textAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._textAlign_0_0value = value
        } else {
            this._textAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public enableKeyboardOnFocus(value: boolean | undefined): this {
        if (((this._enableKeyboardOnFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._enableKeyboardOnFocus_0_0value) !== (value))) {
            this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableKeyboardOnFocus_0_0value = value
        } else {
            this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public selectionMenuHidden(value: boolean | undefined): this {
        if (((this._selectionMenuHidden_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._selectionMenuHidden_0_0value) !== (value))) {
            this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectionMenuHidden_0_0value = value
        } else {
            this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public minFontSize(value: number | string | Resource | undefined): this {
        if (((this._minFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._minFontSize_0_0value) !== (value)) || !Type.of(value).isPrimitive()) {
            this._minFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontSize_0_0value = value
        } else {
            this._minFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public maxFontSize(value: number | string | Resource | undefined): this {
        if (((this._maxFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._maxFontSize_0_0value) !== (value)) || !Type.of(value).isPrimitive()) {
            this._maxFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontSize_0_0value = value
        } else {
            this._maxFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public minFontScale(value: number | Resource | undefined): this {
        if (((this._minFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._minFontScale_0_0value) !== (value)) || !Type.of(value).isPrimitive()) {
            this._minFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale_0_0value = value
        } else {
            this._minFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public maxFontScale(value: number | Resource | undefined): this {
        if (((this._maxFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._maxFontScale_0_0value) !== (value)) || !Type.of(value).isPrimitive()) {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale_0_0value = value
        } else {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public decoration(value: TextDecorationOptions | undefined): this {
        if (((this._decoration_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._decoration_0_0value) !== (value)) || !Type.of(value).isPrimitive()) {
            this._decoration_0_flag = AttributeUpdaterFlag.UPDATE
            this._decoration_0_0value = value
        } else {
            this._decoration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public letterSpacing(value: number | string | Resource | undefined): this {
        if (((this._letterSpacing_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._letterSpacing_0_0value) !== (value)) || !Type.of(value).isPrimitive()) {
            this._letterSpacing_0_flag = AttributeUpdaterFlag.UPDATE
            this._letterSpacing_0_0value = value
        } else {
            this._letterSpacing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public lineHeight(value: number | string | Resource | undefined): this {
        if (((this._lineHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._lineHeight_0_0value) !== (value)) || !Type.of(value).isPrimitive()) {
            this._lineHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._lineHeight_0_0value = value
        } else {
            this._lineHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public type(value: SearchType | undefined): this {
        if (((this._type_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._type_0_0value) !== (value))) {
            this._type_0_flag = AttributeUpdaterFlag.UPDATE
            this._type_0_0value = value
        } else {
            this._type_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontFeature(value: string | undefined): this {
        if (((this._fontFeature_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._fontFeature_0_0value) !== (value))) {
            this._fontFeature_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFeature_0_0value = value
        } else {
            this._fontFeature_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        if (((this._onWillInsert_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._onWillInsert_0_0value) !== (value))) {
            this._onWillInsert_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillInsert_0_0value = value
        } else {
            this._onWillInsert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        if (((this._onDidInsert_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._onDidInsert_0_0value) !== (value))) {
            this._onDidInsert_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidInsert_0_0value = value
        } else {
            this._onDidInsert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        if (((this._onWillDelete_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._onWillDelete_0_0value) !== (value))) {
            this._onWillDelete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillDelete_0_0value = value
        } else {
            this._onWillDelete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        if (((this._onDidDelete_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._onDidDelete_0_0value) !== (value))) {
            this._onDidDelete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidDelete_0_0value = value
        } else {
            this._onDidDelete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._editMenuOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._editMenuOptions_0_0value) !== (value)) || !Type.of(value).isPrimitive()) {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._editMenuOptions_0_0value = value
        } else {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public enablePreviewText(value: boolean | undefined): this {
        if (((this._enablePreviewText_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._enablePreviewText_0_0value) !== (value))) {
            this._enablePreviewText_0_flag = AttributeUpdaterFlag.UPDATE
            this._enablePreviewText_0_0value = value
        } else {
            this._enablePreviewText_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        if (((this._autoCapitalizationMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._autoCapitalizationMode_0_0value) !== (value))) {
            this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoCapitalizationMode_0_0value = value
        } else {
            this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public halfLeading(value: boolean | undefined): this {
        if (((this._halfLeading_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._halfLeading_0_0value) !== (value))) {
            this._halfLeading_0_flag = AttributeUpdaterFlag.UPDATE
            this._halfLeading_0_0value = value
        } else {
            this._halfLeading_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public stopBackPress(value: boolean | undefined): this {
        if (((this._stopBackPress_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._stopBackPress_0_0value) !== (value))) {
            this._stopBackPress_0_flag = AttributeUpdaterFlag.UPDATE
            this._stopBackPress_0_0value = value
        } else {
            this._stopBackPress_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        if (((this._onWillChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._onWillChange_0_0value) !== (value))) {
            this._onWillChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillChange_0_0value = value
        } else {
            this._onWillChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (((this._keyboardAppearance_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._keyboardAppearance_0_0value) !== (value))) {
            this._keyboardAppearance_0_flag = AttributeUpdaterFlag.UPDATE
            this._keyboardAppearance_0_0value = value
        } else {
            this._keyboardAppearance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public searchButton(value: string | undefined, option?: SearchButtonOptions): this {
        if (((this._searchButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._searchButton_0_0value) !== (value)) || (this._searchButton_0_1value) !== (option) ||
            !Type.of(option).isPrimitive()) {
            this._searchButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._searchButton_0_0value = value
            this._searchButton_0_1value = option
        } else {
            this._searchButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        if (((this._inputFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._inputFilter_0_0value) !== (value)) || (this._inputFilter_0_1value) !== (error) ||
            !Type.of(value).isPrimitive()) {
            this._inputFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._inputFilter_0_0value = value
            this._inputFilter_0_1value = error
        } else {
            this._inputFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (((this._customKeyboard_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            ((this._customKeyboard_0_0value) !== (value)) || (this._customKeyboard_0_1value) !== (options) ||
            !Type.of(options).isPrimitive()) {
            this._customKeyboard_0_flag = AttributeUpdaterFlag.UPDATE
            this._customKeyboard_0_0value = value
            this._customKeyboard_0_1value = options
        } else {
            this._customKeyboard_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer: ArkSearchPeer = peerNode as ArkSearchPeer
        if (this._setSearchOptions_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._setSearchOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSearchOptionsAttribute((this._setSearchOptions_0_0value as SearchOptions | undefined));
                    this._setSearchOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setSearchOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._setSearchOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSearchOptionsAttribute((undefined as SearchOptions | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._searchIcon_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._searchIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.searchIconAttribute((this._searchIcon_0_0value as IconOptions | SymbolGlyphModifier | undefined));
                    this._searchIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._searchIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._searchIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.searchIconAttribute((undefined as IconOptions | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (this._cancelButton_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._cancelButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.cancelButtonAttribute((this._cancelButton_0_0value as CancelButtonOptions | CancelButtonSymbolOptions | undefined));
                    this._cancelButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cancelButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cancelButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.cancelButtonAttribute((undefined as CancelButtonOptions | CancelButtonSymbolOptions | undefined));
                }
            }
        }
        if (this._textIndent_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._textIndent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textIndentAttribute((this._textIndent_0_0value as Dimension | undefined));
                    this._textIndent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textIndent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textIndent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textIndentAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._onEditChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onEditChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onEditChangeAttribute((this._onEditChange_0_0value as ((value0: boolean) => void) | undefined));
                    this._onEditChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onEditChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onEditChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onEditChangeAttribute((undefined as ((value0: boolean) => void) | undefined));
                }
            }
        }
        if (this._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._caretStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._caretStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.caretStyleAttribute((this._caretStyle_0_0value as CaretStyle | undefined));
                    this._caretStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._caretStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._caretStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.caretStyleAttribute((undefined as CaretStyle | undefined));
                }
            }
        }
        if (this._placeholderColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._placeholderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.placeholderColorAttribute((this._placeholderColor_0_0value as ResourceColor | undefined));
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.placeholderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._placeholderFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._placeholderFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.placeholderFontAttribute((this._placeholderFont_0_0value as Font | undefined));
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.placeholderFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._textFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._textFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textFontAttribute((this._textFont_0_0value as Font | undefined));
                    this._textFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._enterKeyType_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._enterKeyType_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enterKeyTypeAttribute((this._enterKeyType_0_0value as EnterKeyType | undefined));
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enterKeyTypeAttribute((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (this._onSubmit_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onSubmit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onSubmit1Attribute((this._onSubmit_0_0value as ((value0: string) => void) | SearchSubmitCallback | undefined));
                    this._onSubmit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSubmit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSubmit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onSubmit1Attribute((undefined as ((value0: string) => void) | SearchSubmitCallback | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChangeAttribute((this._onChange_0_0value as EditableTextOnChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChangeAttribute((undefined as EditableTextOnChangeCallback | undefined));
                }
            }
        }
        if (this._onTextSelectionChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onTextSelectionChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onTextSelectionChangeAttribute((this._onTextSelectionChange_0_0value as OnTextSelectionChangeCallback | undefined));
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onTextSelectionChangeAttribute((undefined as OnTextSelectionChangeCallback | undefined));
                }
            }
        }
        if (this._onContentScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onContentScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onContentScrollAttribute((this._onContentScroll_0_0value as OnContentScrollCallback | undefined));
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onContentScrollAttribute((undefined as OnContentScrollCallback | undefined));
                }
            }
        }
        if (this._onCopy_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onCopy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onCopyAttribute((this._onCopy_0_0value as ((value0: string) => void) | undefined));
                    this._onCopy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCopy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCopy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onCopyAttribute((undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (this._onCut_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onCut_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onCutAttribute((this._onCut_0_0value as ((value0: string) => void) | undefined));
                    this._onCut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCut_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onCutAttribute((undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (this._onPaste_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onPaste_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onPasteAttribute((this._onPaste_0_0value as OnPasteCallback | undefined));
                    this._onPaste_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPaste_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPaste_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onPasteAttribute((undefined as OnPasteCallback | undefined));
                }
            }
        }
        if (this._copyOption_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.copyOptionAttribute((this._copyOption_0_0value as CopyOptions | undefined));
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.copyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (this._maxLength_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._maxLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxLengthAttribute((this._maxLength_0_0value as number | undefined));
                    this._maxLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxLengthAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._textAlign_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._textAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textAlignAttribute((this._textAlign_0_0value as TextAlign | undefined));
                    this._textAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textAlignAttribute((undefined as TextAlign | undefined));
                }
            }
        }
        if (this._enableKeyboardOnFocus_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._enableKeyboardOnFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableKeyboardOnFocusAttribute((this._enableKeyboardOnFocus_0_0value as boolean | undefined));
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableKeyboardOnFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._selectionMenuHidden_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._selectionMenuHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectionMenuHiddenAttribute((this._selectionMenuHidden_0_0value as boolean | undefined));
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectionMenuHiddenAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minFontSizeAttribute((this._minFontSize_0_0value as number | string | Resource | undefined));
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minFontSizeAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._maxFontSize_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._maxFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxFontSizeAttribute((this._maxFontSize_0_0value as number | string | Resource | undefined));
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxFontSizeAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minFontScaleAttribute((this._minFontScale_0_0value as number | Resource | undefined));
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minFontScaleAttribute((undefined as number | Resource | undefined));
                }
            }
        }
        if (this._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxFontScaleAttribute((this._maxFontScale_0_0value as number | Resource | undefined));
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxFontScaleAttribute((undefined as number | Resource | undefined));
                }
            }
        }
        if (this._decoration_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._decoration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.decorationAttribute((this._decoration_0_0value as TextDecorationOptions | undefined));
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._decoration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.decorationAttribute((undefined as TextDecorationOptions | undefined));
                }
            }
        }
        if (this._letterSpacing_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._letterSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.letterSpacingAttribute((this._letterSpacing_0_0value as number | string | Resource | undefined));
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.letterSpacingAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.lineHeightAttribute((this._lineHeight_0_0value as number | string | Resource | undefined));
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.lineHeightAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._type_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.typeAttribute((this._type_0_0value as SearchType | undefined));
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._type_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.typeAttribute((undefined as SearchType | undefined));
                }
            }
        }
        if (this._fontFeature_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._fontFeature_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontFeatureAttribute((this._fontFeature_0_0value as string | undefined));
                    this._fontFeature_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFeature_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFeature_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontFeatureAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._onWillInsert_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onWillInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onWillInsertAttribute((this._onWillInsert_0_0value as ((value0: InsertValue) => boolean) | undefined));
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onWillInsertAttribute((undefined as ((value0: InsertValue) => boolean) | undefined));
                }
            }
        }
        if (this._onDidInsert_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onDidInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onDidInsertAttribute((this._onDidInsert_0_0value as ((value0: InsertValue) => void) | undefined));
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onDidInsertAttribute((undefined as ((value0: InsertValue) => void) | undefined));
                }
            }
        }
        if (this._onWillDelete_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onWillDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onWillDeleteAttribute((this._onWillDelete_0_0value as ((value0: DeleteValue) => boolean) | undefined));
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onWillDeleteAttribute((undefined as ((value0: DeleteValue) => boolean) | undefined));
                }
            }
        }
        if (this._onDidDelete_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onDidDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onDidDeleteAttribute((this._onDidDelete_0_0value as ((value0: DeleteValue) => void) | undefined));
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onDidDeleteAttribute((undefined as ((value0: DeleteValue) => void) | undefined));
                }
            }
        }
        if (this._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.editMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.editMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (this._enablePreviewText_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._enablePreviewText_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enablePreviewTextAttribute((this._enablePreviewText_0_0value as boolean | undefined));
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enablePreviewTextAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._autoCapitalizationMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._autoCapitalizationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.autoCapitalizationModeAttribute((this._autoCapitalizationMode_0_0value as AutoCapitalizationMode | undefined));
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.autoCapitalizationModeAttribute((undefined as AutoCapitalizationMode | undefined));
                }
            }
        }
        if (this._halfLeading_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._halfLeading_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.halfLeadingAttribute((this._halfLeading_0_0value as boolean | undefined));
                    this._halfLeading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._halfLeading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._halfLeading_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.halfLeadingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._stopBackPress_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._stopBackPress_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stopBackPressAttribute((this._stopBackPress_0_0value as boolean | undefined));
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stopBackPressAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onWillChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onWillChangeAttribute((this._onWillChange_0_0value as ((value0: EditableTextChangeValue) => boolean) | undefined));
                    this._onWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onWillChangeAttribute((undefined as ((value0: EditableTextChangeValue) => boolean) | undefined));
                }
            }
        }
        if (this._keyboardAppearance_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._keyboardAppearance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.keyboardAppearanceAttribute((this._keyboardAppearance_0_0value as KeyboardAppearance | undefined));
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.keyboardAppearanceAttribute((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (this._searchButton_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._searchButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.searchButtonAttribute((this._searchButton_0_0value as string | undefined), (this._searchButton_0_1value as SearchButtonOptions | undefined));
                    this._searchButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._searchButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._searchButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.searchButtonAttribute((undefined as string | undefined), (undefined as SearchButtonOptions | undefined | undefined));
                }
            }
        }
        if (this._inputFilter_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._inputFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.inputFilterAttribute((this._inputFilter_0_0value as ResourceStr | undefined), (this._inputFilter_0_1value as ((value0: string) => void) | undefined));
                    this._inputFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._inputFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._inputFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.inputFilterAttribute((undefined as ResourceStr | undefined), (undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (this._customKeyboard_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._customKeyboard_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.customKeyboardAttribute((this._customKeyboard_0_0value as CustomBuilder | undefined), (this._customKeyboard_0_1value as KeyboardOptions | undefined));
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.customKeyboardAttribute((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof SearchModifier)) {
            return
        }
        const modifier = value as SearchModifier
        if (modifier._setSearchOptions_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._setSearchOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.setSearchOptions(modifier._setSearchOptions_0_0value);
                    break;
                }
                default: {
                    this.setSearchOptions((undefined as SearchOptions | undefined));
                }
            }
        }
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._searchIcon_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._searchIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.searchIcon(modifier._searchIcon_0_0value);
                    break;
                }
                default: {
                    this.searchIcon((undefined as IconOptions | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (modifier._cancelButton_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._cancelButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cancelButton(modifier._cancelButton_0_0value);
                    break;
                }
                default: {
                    this.cancelButton((undefined as CancelButtonOptions | CancelButtonSymbolOptions | undefined));
                }
            }
        }
        if (modifier._textIndent_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._textIndent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textIndent(modifier._textIndent_0_0value);
                    break;
                }
                default: {
                    this.textIndent((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._onEditChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onEditChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onEditChange(modifier._onEditChange_0_0value);
                    break;
                }
                default: {
                    this.onEditChange((undefined as ((value0: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedBackgroundColor(modifier._selectedBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.selectedBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._caretStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._caretStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.caretStyle(modifier._caretStyle_0_0value);
                    break;
                }
                default: {
                    this.caretStyle((undefined as CaretStyle | undefined));
                }
            }
        }
        if (modifier._placeholderColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._placeholderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.placeholderColor(modifier._placeholderColor_0_0value);
                    break;
                }
                default: {
                    this.placeholderColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._placeholderFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._placeholderFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.placeholderFont(modifier._placeholderFont_0_0value);
                    break;
                }
                default: {
                    this.placeholderFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._textFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._textFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textFont(modifier._textFont_0_0value);
                    break;
                }
                default: {
                    this.textFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._enterKeyType_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._enterKeyType_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enterKeyType(modifier._enterKeyType_0_0value);
                    break;
                }
                default: {
                    this.enterKeyType((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (modifier._onSubmit_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onSubmit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSubmit(modifier._onSubmit_0_0value);
                    break;
                }
                default: {
                    this.onSubmit((undefined as ((value0: string) => void) | SearchSubmitCallback | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as EditableTextOnChangeCallback | undefined));
                }
            }
        }
        if (modifier._onTextSelectionChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onTextSelectionChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTextSelectionChange(modifier._onTextSelectionChange_0_0value);
                    break;
                }
                default: {
                    this.onTextSelectionChange((undefined as OnTextSelectionChangeCallback | undefined));
                }
            }
        }
        if (modifier._onContentScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onContentScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentScroll(modifier._onContentScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentScroll((undefined as OnContentScrollCallback | undefined));
                }
            }
        }
        if (modifier._onCopy_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onCopy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCopy(modifier._onCopy_0_0value);
                    break;
                }
                default: {
                    this.onCopy((undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (modifier._onCut_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onCut_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCut(modifier._onCut_0_0value);
                    break;
                }
                default: {
                    this.onCut((undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (modifier._onPaste_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onPaste_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPaste(modifier._onPaste_0_0value);
                    break;
                }
                default: {
                    this.onPaste((undefined as OnPasteCallback | undefined));
                }
            }
        }
        if (modifier._copyOption_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.copyOption(modifier._copyOption_0_0value);
                    break;
                }
                default: {
                    this.copyOption((undefined as CopyOptions | undefined));
                }
            }
        }
        if (modifier._maxLength_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._maxLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLength(modifier._maxLength_0_0value);
                    break;
                }
                default: {
                    this.maxLength((undefined as number | undefined));
                }
            }
        }
        if (modifier._textAlign_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._textAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textAlign(modifier._textAlign_0_0value);
                    break;
                }
                default: {
                    this.textAlign((undefined as TextAlign | undefined));
                }
            }
        }
        if (modifier._enableKeyboardOnFocus_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._enableKeyboardOnFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableKeyboardOnFocus(modifier._enableKeyboardOnFocus_0_0value);
                    break;
                }
                default: {
                    this.enableKeyboardOnFocus((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._selectionMenuHidden_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._selectionMenuHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectionMenuHidden(modifier._selectionMenuHidden_0_0value);
                    break;
                }
                default: {
                    this.selectionMenuHidden((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontSize_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._maxFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontSize(modifier._maxFontSize_0_0value);
                    break;
                }
                default: {
                    this.maxFontSize((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as number | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as number | Resource | undefined));
                }
            }
        }
        if (modifier._decoration_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._decoration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.decoration(modifier._decoration_0_0value);
                    break;
                }
                default: {
                    this.decoration((undefined as TextDecorationOptions | undefined));
                }
            }
        }
        if (modifier._letterSpacing_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._letterSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.letterSpacing(modifier._letterSpacing_0_0value);
                    break;
                }
                default: {
                    this.letterSpacing((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineHeight(modifier._lineHeight_0_0value);
                    break;
                }
                default: {
                    this.lineHeight((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._type_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.type(modifier._type_0_0value);
                    break;
                }
                default: {
                    this.type((undefined as SearchType | undefined));
                }
            }
        }
        if (modifier._fontFeature_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._fontFeature_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFeature(modifier._fontFeature_0_0value);
                    break;
                }
                default: {
                    this.fontFeature((undefined as string | undefined));
                }
            }
        }
        if (modifier._onWillInsert_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onWillInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillInsert(modifier._onWillInsert_0_0value);
                    break;
                }
                default: {
                    this.onWillInsert((undefined as ((value0: InsertValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._onDidInsert_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onDidInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidInsert(modifier._onDidInsert_0_0value);
                    break;
                }
                default: {
                    this.onDidInsert((undefined as ((value0: InsertValue) => void) | undefined));
                }
            }
        }
        if (modifier._onWillDelete_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onWillDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillDelete(modifier._onWillDelete_0_0value);
                    break;
                }
                default: {
                    this.onWillDelete((undefined as ((value0: DeleteValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._onDidDelete_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onDidDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidDelete(modifier._onDidDelete_0_0value);
                    break;
                }
                default: {
                    this.onDidDelete((undefined as ((value0: DeleteValue) => void) | undefined));
                }
            }
        }
        if (modifier._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMenuOptions(modifier._editMenuOptions_0_0value);
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (modifier._enablePreviewText_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._enablePreviewText_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enablePreviewText(modifier._enablePreviewText_0_0value);
                    break;
                }
                default: {
                    this.enablePreviewText((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._autoCapitalizationMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._autoCapitalizationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoCapitalizationMode(modifier._autoCapitalizationMode_0_0value);
                    break;
                }
                default: {
                    this.autoCapitalizationMode((undefined as AutoCapitalizationMode | undefined));
                }
            }
        }
        if (modifier._halfLeading_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._halfLeading_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.halfLeading(modifier._halfLeading_0_0value);
                    break;
                }
                default: {
                    this.halfLeading((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._stopBackPress_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._stopBackPress_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stopBackPress(modifier._stopBackPress_0_0value);
                    break;
                }
                default: {
                    this.stopBackPress((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onWillChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillChange(modifier._onWillChange_0_0value);
                    break;
                }
                default: {
                    this.onWillChange((undefined as ((value0: EditableTextChangeValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._keyboardAppearance_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._keyboardAppearance_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.keyboardAppearance(modifier._keyboardAppearance_0_0value);
                    break;
                }
                default: {
                    this.keyboardAppearance((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (modifier._searchButton_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._searchButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.searchButton(modifier._searchButton_0_0value, modifier._searchButton_0_1value);
                    break;
                }
                default: {
                    this.searchButton((undefined as string | undefined), (undefined as SearchButtonOptions | undefined | undefined));
                }
            }
        }
        if (modifier._inputFilter_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._inputFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.inputFilter(modifier._inputFilter_0_0value, modifier._inputFilter_0_1value);
                    break;
                }
                default: {
                    this.inputFilter((undefined as ResourceStr | undefined), (undefined as ((value0: string) => void) | undefined | undefined));
                }
            }
        }
        if (modifier._customKeyboard_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._customKeyboard_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customKeyboard(modifier._customKeyboard_0_0value, modifier._customKeyboard_0_1value);
                    break;
                }
                default: {
                    this.customKeyboard((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined | undefined));
                }
            }
        }
    }
}