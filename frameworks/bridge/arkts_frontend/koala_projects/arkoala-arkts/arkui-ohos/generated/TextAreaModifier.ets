/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkTextAreaPeer, TextAreaSubmitCallback, TextAreaType, TextAreaAttribute } from "./component/textArea"
import { int32 } from "@koalaui/common"
import { CommonMethod, TextDecorationOptions, InputCounterOptions } from "./component/common"
import { ResourceColor, Font, Length, ResourceStr, Dimension } from "./component/units"
import { Color, TextAlign, FontStyle, FontWeight, TextOverflow, CopyOptions, TextContentStyle, BarState, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode } from "./component/enums"
import { Resource } from "global.resource"
import { EnterKeyType, SubmitEvent, ContentType } from "./component/textInput"
import { CaretStyle, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode, EditableTextChangeValue, KeyboardAppearance, SelectedDragPreviewStyle, TextDirection } from "./component/textCommon"
import { PasteEvent, KeyboardOptions } from "./component/richEditor"
import { LengthMetrics } from "arkui.Graphics"
import { CustomBuilder } from "./component/builder"
export class TextAreaModifier extends CommonMethodModifier implements TextAreaAttribute,AttributeModifier<TextAreaAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TextAreaAttribute): void { }
    applyPressedAttribute(instance: TextAreaAttribute): void { }
    applyFocusedAttribute(instance: TextAreaAttribute): void { }
    applyDisabledAttribute(instance: TextAreaAttribute): void { }
    applySelectedAttribute(instance: TextAreaAttribute): void { }
    _placeholderColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _placeholderColor_0_0value?: ResourceColor | undefined
    _placeholderFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _placeholderFont_0_0value?: Font | undefined
    _enterKeyType_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enterKeyType_0_0value?: EnterKeyType | undefined
    _textAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textAlign_0_0value?: TextAlign | undefined
    _caretColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _caretColor_0_0value?: ResourceColor | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: Length | undefined
    _fontStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle_0_0value?: FontStyle | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: ResourceStr | undefined
    _textOverflow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textOverflow_0_0value?: TextOverflow | undefined
    _textIndent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textIndent_0_0value?: Dimension | undefined
    _caretStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _caretStyle_0_0value?: CaretStyle | undefined
    _selectedBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    _onSubmit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSubmit_0_0value?: TextAreaSubmitCallback | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: EditableTextOnChangeCallback | undefined
    _onTextSelectionChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTextSelectionChange_0_0value?: ((selectionStart: int32,selectionEnd: int32) => void) | undefined
    _onContentScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentScroll_0_0value?: ((totalOffsetX: double,totalOffsetY: double) => void) | undefined
    _onEditChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onEditChange_0_0value?: ((isEditing: boolean) => void) | undefined
    _onCopy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCopy_0_0value?: ((value: string) => void) | undefined
    _onCut_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCut_0_0value?: ((value: string) => void) | undefined
    _onPaste_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPaste_0_0value?: ((value: string,event: PasteEvent) => void) | undefined
    _copyOption_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOption_0_0value?: CopyOptions | undefined
    _enableKeyboardOnFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableKeyboardOnFocus_0_0value?: boolean | undefined
    _maxLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLength_0_0value?: int32 | undefined
    _style_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _style_0_0value?: TextContentStyle | undefined
    _barState_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barState_0_0value?: BarState | undefined
    _selectionMenuHidden_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectionMenuHidden_0_0value?: boolean | undefined
    _minFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontSize_0_0value?: double | string | Resource | undefined
    _maxFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontSize_0_0value?: double | string | Resource | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: double | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: double | Resource | undefined
    _heightAdaptivePolicy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _heightAdaptivePolicy_0_0value?: TextHeightAdaptivePolicy | undefined
    _maxLines_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLines_0_0value?: int32 | undefined
    _wordBreak_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _wordBreak_0_0value?: WordBreak | undefined
    _lineBreakStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineBreakStrategy_0_0value?: LineBreakStrategy | undefined
    _decoration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _decoration_0_0value?: TextDecorationOptions | undefined
    _letterSpacing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _letterSpacing_0_0value?: double | string | Resource | undefined
    _lineSpacing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineSpacing_0_0value?: LengthMetrics | undefined
    _lineHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineHeight_0_0value?: double | string | Resource | undefined
    _type_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _type_0_0value?: TextAreaType | undefined
    _enableAutoFill_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAutoFill_0_0value?: boolean | undefined
    _contentType_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentType_0_0value?: ContentType | undefined
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
    _ellipsisMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _ellipsisMode_0_0value?: EllipsisMode | undefined
    _stopBackPress_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stopBackPress_0_0value?: boolean | undefined
    _onWillChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillChange_0_0value?: ((value0: EditableTextChangeValue) => boolean) | undefined
    _keyboardAppearance_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _keyboardAppearance_0_0value?: KeyboardAppearance | undefined
    _textDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textDirection_0_0value?: TextDirection | undefined
    _compressLeadingPunctuation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _compressLeadingPunctuation_0_0value?: boolean | undefined
    _includeFontPadding_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _includeFontPadding_0_0value?: boolean | undefined
    _fallbackLineSpacing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fallbackLineSpacing_0_0value?: boolean | undefined
    _selectedDragPreviewStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedDragPreviewStyle_0_0value?: SelectedDragPreviewStyle | undefined
    _inputFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _inputFilter_0_0value?: ResourceStr | undefined
    _inputFilter_0_1value?: ((value: string) => void) | undefined
    _showCounter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showCounter_0_0value?: boolean | undefined
    _showCounter_0_1value?: InputCounterOptions | undefined
    _customKeyboard_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customKeyboard_0_0value?: CustomBuilder | undefined
    _customKeyboard_0_1value?: KeyboardOptions | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkTextAreaPeer;
        if (this._placeholderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._placeholderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPlaceholderColorAttribute((this._placeholderColor_0_0value as ResourceColor | undefined));
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPlaceholderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._placeholderFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._placeholderFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPlaceholderFontAttribute((this._placeholderFont_0_0value as Font | undefined));
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPlaceholderFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._enterKeyType_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enterKeyType_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnterKeyTypeAttribute((this._enterKeyType_0_0value as EnterKeyType | undefined));
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnterKeyTypeAttribute((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (this._textAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextAlignAttribute((this._textAlign_0_0value as TextAlign | undefined));
                    this._textAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextAlignAttribute((undefined as TextAlign | undefined));
                }
            }
        }
        if (this._caretColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._caretColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCaretColorAttribute((this._caretColor_0_0value as ResourceColor | undefined));
                    this._caretColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._caretColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._caretColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCaretColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (this._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as ResourceStr | undefined));
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontFamilyAttribute((undefined as ResourceStr | undefined));
                }
            }
        }
        if (this._textOverflow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textOverflow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextOverflowAttribute((this._textOverflow_0_0value as TextOverflow | undefined));
                    this._textOverflow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textOverflow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textOverflow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextOverflowAttribute((undefined as TextOverflow | undefined));
                }
            }
        }
        if (this._textIndent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textIndent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextIndentAttribute((this._textIndent_0_0value as Dimension | undefined));
                    this._textIndent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textIndent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textIndent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextIndentAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._caretStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._caretStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCaretStyleAttribute((this._caretStyle_0_0value as CaretStyle | undefined));
                    this._caretStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._caretStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._caretStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCaretStyleAttribute((undefined as CaretStyle | undefined));
                }
            }
        }
        if (this._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._onSubmit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSubmit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSubmitAttribute((this._onSubmit_0_0value as TextAreaSubmitCallback | undefined));
                    this._onSubmit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSubmit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSubmit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSubmitAttribute((undefined as TextAreaSubmitCallback | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as EditableTextOnChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as EditableTextOnChangeCallback | undefined));
                }
            }
        }
        if (this._onTextSelectionChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTextSelectionChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTextSelectionChangeAttribute((this._onTextSelectionChange_0_0value as ((selectionStart: int32,selectionEnd: int32) => void) | undefined));
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTextSelectionChangeAttribute((undefined as ((selectionStart: int32,selectionEnd: int32) => void) | undefined));
                }
            }
        }
        if (this._onContentScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContentScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContentScrollAttribute((this._onContentScroll_0_0value as ((totalOffsetX: double,totalOffsetY: double) => void) | undefined));
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContentScrollAttribute((undefined as ((totalOffsetX: double,totalOffsetY: double) => void) | undefined));
                }
            }
        }
        if (this._onEditChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onEditChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnEditChangeAttribute((this._onEditChange_0_0value as ((isEditing: boolean) => void) | undefined));
                    this._onEditChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onEditChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onEditChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnEditChangeAttribute((undefined as ((isEditing: boolean) => void) | undefined));
                }
            }
        }
        if (this._onCopy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCopy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCopyAttribute((this._onCopy_0_0value as ((value: string) => void) | undefined));
                    this._onCopy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCopy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCopy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCopyAttribute((undefined as ((value: string) => void) | undefined));
                }
            }
        }
        if (this._onCut_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCut_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCutAttribute((this._onCut_0_0value as ((value: string) => void) | undefined));
                    this._onCut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCut_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCutAttribute((undefined as ((value: string) => void) | undefined));
                }
            }
        }
        if (this._onPaste_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPaste_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPasteAttribute((this._onPaste_0_0value as ((value: string,event: PasteEvent) => void) | undefined));
                    this._onPaste_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPaste_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPaste_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPasteAttribute((undefined as ((value: string,event: PasteEvent) => void) | undefined));
                }
            }
        }
        if (this._copyOption_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCopyOptionAttribute((this._copyOption_0_0value as CopyOptions | undefined));
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCopyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (this._enableKeyboardOnFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableKeyboardOnFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableKeyboardOnFocusAttribute((this._enableKeyboardOnFocus_0_0value as boolean | undefined));
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableKeyboardOnFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._maxLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxLengthAttribute((this._maxLength_0_0value as int32 | undefined));
                    this._maxLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxLengthAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._style_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._style_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStyleAttribute((this._style_0_0value as TextContentStyle | undefined));
                    this._style_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._style_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._style_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStyleAttribute((undefined as TextContentStyle | undefined));
                }
            }
        }
        if (this._barState_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barState_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarStateAttribute((this._barState_0_0value as BarState | undefined));
                    this._barState_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barState_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barState_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarStateAttribute((undefined as BarState | undefined));
                }
            }
        }
        if (this._selectionMenuHidden_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectionMenuHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectionMenuHiddenAttribute((this._selectionMenuHidden_0_0value as boolean | undefined));
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectionMenuHiddenAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as double | string | Resource | undefined));
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontSizeAttribute((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (this._maxFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontSizeAttribute((this._maxFontSize_0_0value as double | string | Resource | undefined));
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontSizeAttribute((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (this._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | Resource | undefined));
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontScaleAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | Resource | undefined));
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontScaleAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._heightAdaptivePolicy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._heightAdaptivePolicy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHeightAdaptivePolicyAttribute((this._heightAdaptivePolicy_0_0value as TextHeightAdaptivePolicy | undefined));
                    this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHeightAdaptivePolicyAttribute((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (this._maxLines_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxLines_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxLinesAttribute((this._maxLines_0_0value as int32 | undefined));
                    this._maxLines_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLines_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLines_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxLinesAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._wordBreak_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._wordBreak_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWordBreakAttribute((this._wordBreak_0_0value as WordBreak | undefined));
                    this._wordBreak_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._wordBreak_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._wordBreak_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWordBreakAttribute((undefined as WordBreak | undefined));
                }
            }
        }
        if (this._lineBreakStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineBreakStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLineBreakStrategyAttribute((this._lineBreakStrategy_0_0value as LineBreakStrategy | undefined));
                    this._lineBreakStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineBreakStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineBreakStrategy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLineBreakStrategyAttribute((undefined as LineBreakStrategy | undefined));
                }
            }
        }
        if (this._decoration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._decoration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDecorationAttribute((this._decoration_0_0value as TextDecorationOptions | undefined));
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._decoration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDecorationAttribute((undefined as TextDecorationOptions | undefined));
                }
            }
        }
        if (this._letterSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._letterSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLetterSpacingAttribute((this._letterSpacing_0_0value as double | string | Resource | undefined));
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLetterSpacingAttribute((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (this._lineSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLineSpacingAttribute((this._lineSpacing_0_0value as LengthMetrics | undefined));
                    this._lineSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineSpacing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLineSpacingAttribute((undefined as LengthMetrics | undefined));
                }
            }
        }
        if (this._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLineHeightAttribute((this._lineHeight_0_0value as double | string | Resource | undefined));
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLineHeightAttribute((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (this._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTypeAttribute((this._type_0_0value as TextAreaType | undefined));
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._type_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTypeAttribute((undefined as TextAreaType | undefined));
                }
            }
        }
        if (this._enableAutoFill_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAutoFill_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableAutoFillAttribute((this._enableAutoFill_0_0value as boolean | undefined));
                    this._enableAutoFill_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAutoFill_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAutoFill_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableAutoFillAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._contentType_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentType_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentTypeAttribute((this._contentType_0_0value as ContentType | undefined));
                    this._contentType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentType_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentTypeAttribute((undefined as ContentType | undefined));
                }
            }
        }
        if (this._fontFeature_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFeature_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontFeatureAttribute((this._fontFeature_0_0value as string | undefined));
                    this._fontFeature_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFeature_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFeature_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontFeatureAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._onWillInsert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillInsertAttribute((this._onWillInsert_0_0value as ((value0: InsertValue) => boolean) | undefined));
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillInsertAttribute((undefined as ((value0: InsertValue) => boolean) | undefined));
                }
            }
        }
        if (this._onDidInsert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidInsertAttribute((this._onDidInsert_0_0value as ((value0: InsertValue) => void) | undefined));
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidInsertAttribute((undefined as ((value0: InsertValue) => void) | undefined));
                }
            }
        }
        if (this._onWillDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillDeleteAttribute((this._onWillDelete_0_0value as ((value0: DeleteValue) => boolean) | undefined));
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillDeleteAttribute((undefined as ((value0: DeleteValue) => boolean) | undefined));
                }
            }
        }
        if (this._onDidDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidDeleteAttribute((this._onDidDelete_0_0value as ((value0: DeleteValue) => void) | undefined));
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidDeleteAttribute((undefined as ((value0: DeleteValue) => void) | undefined));
                }
            }
        }
        if (this._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEditMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (this._enablePreviewText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enablePreviewText_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnablePreviewTextAttribute((this._enablePreviewText_0_0value as boolean | undefined));
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnablePreviewTextAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._autoCapitalizationMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoCapitalizationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoCapitalizationModeAttribute((this._autoCapitalizationMode_0_0value as AutoCapitalizationMode | undefined));
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoCapitalizationModeAttribute((undefined as AutoCapitalizationMode | undefined));
                }
            }
        }
        if (this._halfLeading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._halfLeading_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHalfLeadingAttribute((this._halfLeading_0_0value as boolean | undefined));
                    this._halfLeading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._halfLeading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._halfLeading_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHalfLeadingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._ellipsisMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._ellipsisMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEllipsisModeAttribute((this._ellipsisMode_0_0value as EllipsisMode | undefined));
                    this._ellipsisMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._ellipsisMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._ellipsisMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEllipsisModeAttribute((undefined as EllipsisMode | undefined));
                }
            }
        }
        if (this._stopBackPress_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stopBackPress_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStopBackPressAttribute((this._stopBackPress_0_0value as boolean | undefined));
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStopBackPressAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onWillChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillChangeAttribute((this._onWillChange_0_0value as ((value0: EditableTextChangeValue) => boolean) | undefined));
                    this._onWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillChangeAttribute((undefined as ((value0: EditableTextChangeValue) => boolean) | undefined));
                }
            }
        }
        if (this._keyboardAppearance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._keyboardAppearance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setKeyboardAppearanceAttribute((this._keyboardAppearance_0_0value as KeyboardAppearance | undefined));
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setKeyboardAppearanceAttribute((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (this._compressLeadingPunctuation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._compressLeadingPunctuation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCompressLeadingPunctuationAttribute((this._compressLeadingPunctuation_0_0value as boolean | undefined));
                    this._compressLeadingPunctuation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._compressLeadingPunctuation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._compressLeadingPunctuation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCompressLeadingPunctuationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._includeFontPadding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._includeFontPadding_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIncludeFontPaddingAttribute((this._includeFontPadding_0_0value as boolean | undefined));
                    this._includeFontPadding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._includeFontPadding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._includeFontPadding_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIncludeFontPaddingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fallbackLineSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fallbackLineSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFallbackLineSpacingAttribute((this._fallbackLineSpacing_0_0value as boolean | undefined));
                    this._fallbackLineSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fallbackLineSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fallbackLineSpacing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFallbackLineSpacingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._selectedDragPreviewStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedDragPreviewStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedDragPreviewStyleAttribute((this._selectedDragPreviewStyle_0_0value as SelectedDragPreviewStyle | undefined));
                    this._selectedDragPreviewStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedDragPreviewStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedDragPreviewStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedDragPreviewStyleAttribute((undefined as SelectedDragPreviewStyle | undefined));
                }
            }
        }
        if (this._textDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextDirectionAttribute((this._textDirection_0_0value as TextDirection | undefined));
                    this._textDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextDirectionAttribute((undefined as TextDirection | undefined));
                }
            }
        }
        if (this._inputFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._inputFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInputFilterAttribute((this._inputFilter_0_0value as ResourceStr | undefined), (this._inputFilter_0_1value as ((value: string) => void) | undefined | undefined));
                    this._inputFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._inputFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._inputFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInputFilterAttribute((undefined as ResourceStr | undefined), (undefined as ((value: string) => void) | undefined | undefined));
                }
            }
        }
        if (this._showCounter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showCounter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowCounterAttribute((this._showCounter_0_0value as boolean | undefined), (this._showCounter_0_1value as InputCounterOptions | undefined));
                    this._showCounter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showCounter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showCounter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowCounterAttribute((undefined as boolean | undefined), (undefined as InputCounterOptions | undefined));
                }
            }
        }
        if (this._customKeyboard_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customKeyboard_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomKeyboardAttribute((this._customKeyboard_0_0value as CustomBuilder | undefined), (this._customKeyboard_0_1value as KeyboardOptions | undefined));
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomKeyboardAttribute((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TextAreaModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._placeholderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._placeholderFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._enterKeyType_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._textAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._caretColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._caretColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.caretColor(modifier._caretColor_0_0value);
                    break;
                }
                default: {
                    this.caretColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as Length | undefined));
                }
            }
        }
        if (modifier._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontStyle(modifier._fontStyle_0_0value);
                    break;
                }
                default: {
                    this.fontStyle((undefined as FontStyle | undefined));
                }
            }
        }
        if (modifier._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (modifier._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as ResourceStr | undefined));
                }
            }
        }
        if (modifier._textOverflow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textOverflow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textOverflow(modifier._textOverflow_0_0value);
                    break;
                }
                default: {
                    this.textOverflow((undefined as TextOverflow | undefined));
                }
            }
        }
        if (modifier._textIndent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._caretStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._onSubmit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSubmit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSubmit(modifier._onSubmit_0_0value);
                    break;
                }
                default: {
                    this.onSubmit((undefined as TextAreaSubmitCallback | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._onTextSelectionChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTextSelectionChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTextSelectionChange(modifier._onTextSelectionChange_0_0value);
                    break;
                }
                default: {
                    this.onTextSelectionChange((undefined as ((selectionStart: int32,selectionEnd: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onContentScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContentScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentScroll(modifier._onContentScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentScroll((undefined as ((totalOffsetX: double,totalOffsetY: double) => void) | undefined));
                }
            }
        }
        if (modifier._onEditChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onEditChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onEditChange(modifier._onEditChange_0_0value);
                    break;
                }
                default: {
                    this.onEditChange((undefined as ((isEditing: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._onCopy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCopy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCopy(modifier._onCopy_0_0value);
                    break;
                }
                default: {
                    this.onCopy((undefined as ((value: string) => void) | undefined));
                }
            }
        }
        if (modifier._onCut_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCut_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCut(modifier._onCut_0_0value);
                    break;
                }
                default: {
                    this.onCut((undefined as ((value: string) => void) | undefined));
                }
            }
        }
        if (modifier._onPaste_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPaste_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPaste(modifier._onPaste_0_0value);
                    break;
                }
                default: {
                    this.onPaste((undefined as ((value: string,event: PasteEvent) => void) | undefined));
                }
            }
        }
        if (modifier._copyOption_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._enableKeyboardOnFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._maxLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLength(modifier._maxLength_0_0value);
                    break;
                }
                default: {
                    this.maxLength((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._style_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._style_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.style(modifier._style_0_0value);
                    break;
                }
                default: {
                    this.style((undefined as TextContentStyle | undefined));
                }
            }
        }
        if (modifier._barState_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barState_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barState(modifier._barState_0_0value);
                    break;
                }
                default: {
                    this.barState((undefined as BarState | undefined));
                }
            }
        }
        if (modifier._selectionMenuHidden_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontSize(modifier._maxFontSize_0_0value);
                    break;
                }
                default: {
                    this.maxFontSize((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (modifier._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._heightAdaptivePolicy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._heightAdaptivePolicy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.heightAdaptivePolicy(modifier._heightAdaptivePolicy_0_0value);
                    break;
                }
                default: {
                    this.heightAdaptivePolicy((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (modifier._maxLines_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxLines_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLines(modifier._maxLines_0_0value);
                    break;
                }
                default: {
                    this.maxLines((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._wordBreak_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._wordBreak_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.wordBreak(modifier._wordBreak_0_0value);
                    break;
                }
                default: {
                    this.wordBreak((undefined as WordBreak | undefined));
                }
            }
        }
        if (modifier._lineBreakStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineBreakStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineBreakStrategy(modifier._lineBreakStrategy_0_0value);
                    break;
                }
                default: {
                    this.lineBreakStrategy((undefined as LineBreakStrategy | undefined));
                }
            }
        }
        if (modifier._decoration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._letterSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._letterSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.letterSpacing(modifier._letterSpacing_0_0value);
                    break;
                }
                default: {
                    this.letterSpacing((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (modifier._lineSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineSpacing(modifier._lineSpacing_0_0value);
                    break;
                }
                default: {
                    this.lineSpacing((undefined as LengthMetrics | undefined));
                }
            }
        }
        if (modifier._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineHeight(modifier._lineHeight_0_0value);
                    break;
                }
                default: {
                    this.lineHeight((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (modifier._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.type(modifier._type_0_0value);
                    break;
                }
                default: {
                    this.type((undefined as TextAreaType | undefined));
                }
            }
        }
        if (modifier._enableAutoFill_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAutoFill_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAutoFill(modifier._enableAutoFill_0_0value);
                    break;
                }
                default: {
                    this.enableAutoFill((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._contentType_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentType_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentType(modifier._contentType_0_0value);
                    break;
                }
                default: {
                    this.contentType((undefined as ContentType | undefined));
                }
            }
        }
        if (modifier._fontFeature_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._onWillInsert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._onDidInsert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._onWillDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._onDidDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._enablePreviewText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._autoCapitalizationMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._halfLeading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._ellipsisMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._ellipsisMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.ellipsisMode(modifier._ellipsisMode_0_0value);
                    break;
                }
                default: {
                    this.ellipsisMode((undefined as EllipsisMode | undefined));
                }
            }
        }
        if (modifier._stopBackPress_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._onWillChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._keyboardAppearance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._compressLeadingPunctuation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._compressLeadingPunctuation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.compressLeadingPunctuation(modifier._compressLeadingPunctuation_0_0value);
                    break;
                }
                default: {
                    this.compressLeadingPunctuation((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._includeFontPadding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._includeFontPadding_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.includeFontPadding(modifier._includeFontPadding_0_0value);
                    break;
                }
                default: {
                    this.includeFontPadding((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fallbackLineSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fallbackLineSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fallbackLineSpacing(modifier._fallbackLineSpacing_0_0value);
                    break;
                }
                default: {
                    this.fallbackLineSpacing((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._selectedDragPreviewStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedDragPreviewStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedDragPreviewStyle(modifier._selectedDragPreviewStyle_0_0value);
                    break;
                }
                default: {
                    this.selectedDragPreviewStyle((undefined as SelectedDragPreviewStyle | undefined));
                }
            }
        }
        if (modifier._textDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textDirection(modifier._textDirection_0_0value);
                    break;
                }
                default: {
                    this.textDirection((undefined as TextDirection | undefined));
                }
            }
        }
        if (modifier._inputFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._inputFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.inputFilter(modifier._inputFilter_0_0value, modifier._inputFilter_0_1value);
                    break;
                }
                default: {
                    this.inputFilter((undefined as ResourceStr | undefined), (undefined as ((value: string) => void) | undefined | undefined));
                }
            }
        }
        if (modifier._showCounter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showCounter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showCounter(modifier._showCounter_0_0value, modifier._showCounter_0_1value);
                    break;
                }
                default: {
                    this.showCounter((undefined as boolean | undefined), (undefined as InputCounterOptions | undefined));
                }
            }
        }
        if (modifier._customKeyboard_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customKeyboard_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customKeyboard(modifier._customKeyboard_0_0value, modifier._customKeyboard_0_1value);
                    break;
                }
                default: {
                    this.customKeyboard((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined));
                }
            }
        }
    }
    placeholderColor(value: ResourceColor | undefined): this {
        if (((this._placeholderColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._placeholderColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._placeholderColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._placeholderColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    placeholderFont(value: Font | undefined): this {
        if (((this._placeholderFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._placeholderFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._placeholderFont_0_0value = value
            this._state.fireChange()
        } else
        {
            this._placeholderFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        if (((this._enterKeyType_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._enterKeyType_0_flag = AttributeUpdaterFlag.UPDATE
            this._enterKeyType_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enterKeyType_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textAlign(value: TextAlign | undefined): this {
        if (((this._textAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._textAlign_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    caretColor(value: ResourceColor | undefined): this {
        if (((this._caretColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._caretColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._caretColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._caretColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontSize(value: Length | undefined): this {
        if (((this._fontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._fontStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFamily(value: ResourceStr | undefined): this {
        if (((this._fontFamily_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textOverflow(value: TextOverflow | undefined): this {
        if (((this._textOverflow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textOverflow_0_flag = AttributeUpdaterFlag.UPDATE
            this._textOverflow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textOverflow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textIndent(value: Dimension | undefined): this {
        if (((this._textIndent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textIndent_0_flag = AttributeUpdaterFlag.UPDATE
            this._textIndent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textIndent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    caretStyle(value: CaretStyle | undefined): this {
        if (((this._caretStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._caretStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._caretStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._caretStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._selectedBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedBackgroundColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSubmit(value: TextAreaSubmitCallback | undefined): this {
        if (((this._onSubmit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSubmit_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSubmit_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onSubmit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTextSelectionChange(value: ((selectionStart: int32,selectionEnd: int32) => void) | undefined): this {
        if (((this._onTextSelectionChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTextSelectionChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContentScroll(value: ((totalOffsetX: double,totalOffsetY: double) => void) | undefined): this {
        if (((this._onContentScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContentScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentScroll_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onContentScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onEditChange(value: ((isEditing: boolean) => void) | undefined): this {
        if (((this._onEditChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onEditChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onEditChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onEditChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCopy(value: ((value: string) => void) | undefined): this {
        if (((this._onCopy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onCopy_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCopy_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onCopy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCut(value: ((value: string) => void) | undefined): this {
        if (((this._onCut_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onCut_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCut_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onCut_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPaste(value: ((value: string,event: PasteEvent) => void) | undefined): this {
        if (((this._onPaste_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPaste_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPaste_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onPaste_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._copyOption_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._copyOption_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOption_0_0value = value
            this._state.fireChange()
        } else
        {
            this._copyOption_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        if (((this._enableKeyboardOnFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableKeyboardOnFocus_0_0value) !== (value)))
        {
            this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableKeyboardOnFocus_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxLength(value: int32 | undefined): this {
        if (((this._maxLength_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxLength_0_0value) !== (value)))
        {
            this._maxLength_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxLength_0_0value = value
            this._state.fireChange()
        } else
        {
            this._maxLength_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    style(value: TextContentStyle | undefined): this {
        if (((this._style_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._style_0_flag = AttributeUpdaterFlag.UPDATE
            this._style_0_0value = value
            this._state.fireChange()
        } else
        {
            this._style_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barState(value: BarState | undefined): this {
        if (((this._barState_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barState_0_flag = AttributeUpdaterFlag.UPDATE
            this._barState_0_0value = value
            this._state.fireChange()
        } else
        {
            this._barState_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectionMenuHidden(value: boolean | undefined): this {
        if (((this._selectionMenuHidden_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._selectionMenuHidden_0_0value) !== (value)))
        {
            this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectionMenuHidden_0_0value = value
            this._state.fireChange()
        } else
        {
            this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontSize(value: double | string | Resource | undefined): this {
        if (((this._minFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontSize(value: double | string | Resource | undefined): this {
        if (((this._maxFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._maxFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontScale(value: double | Resource | undefined): this {
        if (((this._minFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale_0_0value = value
            this._state.fireChange()
        } else
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontScale(value: double | Resource | undefined): this {
        if (((this._maxFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale_0_0value = value
            this._state.fireChange()
        } else
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (((this._heightAdaptivePolicy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.UPDATE
            this._heightAdaptivePolicy_0_0value = value
            this._state.fireChange()
        } else
        {
            this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxLines(value: int32 | undefined): this {
        if (((this._maxLines_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxLines_0_0value) !== (value)))
        {
            this._maxLines_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxLines_0_0value = value
            this._state.fireChange()
        } else
        {
            this._maxLines_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    wordBreak(value: WordBreak | undefined): this {
        if (((this._wordBreak_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._wordBreak_0_flag = AttributeUpdaterFlag.UPDATE
            this._wordBreak_0_0value = value
            this._state.fireChange()
        } else
        {
            this._wordBreak_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (((this._lineBreakStrategy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._lineBreakStrategy_0_flag = AttributeUpdaterFlag.UPDATE
            this._lineBreakStrategy_0_0value = value
            this._state.fireChange()
        } else
        {
            this._lineBreakStrategy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    decoration(value: TextDecorationOptions | undefined): this {
        if (((this._decoration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._decoration_0_flag = AttributeUpdaterFlag.UPDATE
            this._decoration_0_0value = value
            this._state.fireChange()
        } else
        {
            this._decoration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    letterSpacing(value: double | string | Resource | undefined): this {
        if (((this._letterSpacing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._letterSpacing_0_flag = AttributeUpdaterFlag.UPDATE
            this._letterSpacing_0_0value = value
            this._state.fireChange()
        } else
        {
            this._letterSpacing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        if (((this._lineSpacing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._lineSpacing_0_flag = AttributeUpdaterFlag.UPDATE
            this._lineSpacing_0_0value = value
            this._state.fireChange()
        } else
        {
            this._lineSpacing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineHeight(value: double | string | Resource | undefined): this {
        if (((this._lineHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._lineHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._lineHeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._lineHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    type(value: TextAreaType | undefined): this {
        if (((this._type_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._type_0_flag = AttributeUpdaterFlag.UPDATE
            this._type_0_0value = value
            this._state.fireChange()
        } else
        {
            this._type_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAutoFill(value: boolean | undefined): this {
        if (((this._enableAutoFill_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAutoFill_0_0value) !== (value)))
        {
            this._enableAutoFill_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAutoFill_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableAutoFill_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentType(value: ContentType | undefined): this {
        if (((this._contentType_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentType_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentType_0_0value = value
            this._state.fireChange()
        } else
        {
            this._contentType_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFeature(value: string | undefined): this {
        if (((this._fontFeature_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fontFeature_0_0value) !== (value)))
        {
            this._fontFeature_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFeature_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontFeature_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        if (((this._onWillInsert_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillInsert_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillInsert_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillInsert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        if (((this._onDidInsert_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidInsert_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidInsert_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onDidInsert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        if (((this._onWillDelete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillDelete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillDelete_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillDelete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        if (((this._onDidDelete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidDelete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidDelete_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onDidDelete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._editMenuOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._editMenuOptions_0_0value = value
            this._state.fireChange()
        } else
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enablePreviewText(value: boolean | undefined): this {
        if (((this._enablePreviewText_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enablePreviewText_0_0value) !== (value)))
        {
            this._enablePreviewText_0_flag = AttributeUpdaterFlag.UPDATE
            this._enablePreviewText_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enablePreviewText_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        if (((this._autoCapitalizationMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoCapitalizationMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    halfLeading(value: boolean | undefined): this {
        if (((this._halfLeading_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._halfLeading_0_0value) !== (value)))
        {
            this._halfLeading_0_flag = AttributeUpdaterFlag.UPDATE
            this._halfLeading_0_0value = value
            this._state.fireChange()
        } else
        {
            this._halfLeading_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        if (((this._ellipsisMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._ellipsisMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._ellipsisMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._ellipsisMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stopBackPress(value: boolean | undefined): this {
        if (((this._stopBackPress_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stopBackPress_0_0value) !== (value)))
        {
            this._stopBackPress_0_flag = AttributeUpdaterFlag.UPDATE
            this._stopBackPress_0_0value = value
            this._state.fireChange()
        } else
        {
            this._stopBackPress_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        if (((this._onWillChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (((this._keyboardAppearance_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._keyboardAppearance_0_flag = AttributeUpdaterFlag.UPDATE
            this._keyboardAppearance_0_0value = value
            this._state.fireChange()
        } else
        {
            this._keyboardAppearance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    compressLeadingPunctuation(value: boolean | undefined): this {
        if (((this._compressLeadingPunctuation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._compressLeadingPunctuation_0_0value) !== (value)))
        {
            this._compressLeadingPunctuation_0_flag = AttributeUpdaterFlag.UPDATE
            this._compressLeadingPunctuation_0_0value = value
            this._state.fireChange()
        } else
        {
            this._compressLeadingPunctuation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    includeFontPadding(value: boolean | undefined): this {
        if (((this._includeFontPadding_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._includeFontPadding_0_0value) !== (value)))
        {
            this._includeFontPadding_0_flag = AttributeUpdaterFlag.UPDATE
            this._includeFontPadding_0_0value = value
            this._state.fireChange()
        } else
        {
            this._includeFontPadding_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fallbackLineSpacing(value: boolean | undefined): this {
        if (((this._fallbackLineSpacing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fallbackLineSpacing_0_0value) !== (value)))
        {
            this._fallbackLineSpacing_0_flag = AttributeUpdaterFlag.UPDATE
            this._fallbackLineSpacing_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fallbackLineSpacing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedDragPreviewStyle(value: SelectedDragPreviewStyle | undefined): this {
        if (((this._selectedDragPreviewStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedDragPreviewStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedDragPreviewStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._selectedDragPreviewStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textDirection(value: TextDirection | undefined): this {
        if (((this._textDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._textDirection_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    inputFilter(value: ResourceStr | undefined, error?: ((value: string) => void)): this {
        if (((this._inputFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._inputFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._inputFilter_0_0value = value
            this._inputFilter_0_1value = error
            this._state.fireChange()
        } else
        {
            this._inputFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    showCounter(value: boolean | undefined, options?: InputCounterOptions): this {
        if (((this._showCounter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._showCounter_0_0value) !== (value)) || (true))
        {
            this._showCounter_0_flag = AttributeUpdaterFlag.UPDATE
            this._showCounter_0_0value = value
            this._showCounter_0_1value = options
            this._state.fireChange()
        } else
        {
            this._showCounter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (((this._customKeyboard_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._customKeyboard_0_flag = AttributeUpdaterFlag.UPDATE
            this._customKeyboard_0_0value = value
            this._customKeyboard_0_1value = options
            this._state.fireChange()
        } else
        {
            this._customKeyboard_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
