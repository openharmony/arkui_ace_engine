/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkTextAreaPeer, TextAreaSubmitCallback, TextAreaType, TextAreaAttribute } from './component/textArea'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, TextDecorationOptions, Callback as arkui_component_common_Callback, InputCounterOptions } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Font as arkui_component_units_Font, Length, ResourceStr, Dimension, LengthMetrics as arkui_component_units_LengthMetrics, ColorMetrics as arkui_component_units_ColorMetrics } from './component/units'
import { Color as arkui_component_enums_Color, TextAlign, FontStyle, FontWeight, TextOverflow, CopyOptions, TextContentStyle, BarState, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { EnterKeyType, SubmitEvent, ContentType } from './component/textInput'
import { CaretStyle, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode, EditableTextChangeValue, KeyboardAppearance, IMEClient, SelectedDragPreviewStyle, TextDirection, VoiceButtonOptions, MaxLinesOptions, LineSpacingOptions } from './component/textCommon'
import { PasteEvent, KeyboardOptions } from './component/richEditor'
import { LengthMetrics as arkui_Graphics_LengthMetrics, ColorMetrics as arkui_Graphics_ColorMetrics } from 'arkui.Graphics'
import { CustomBuilder } from './component/builder'
import { ComponentContentBase } from 'arkui.ComponentContent'
export class TextAreaModifier extends CommonMethodModifier implements TextAreaAttribute,AttributeModifier<TextAreaAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    private _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TextAreaAttribute): void { }
    applyPressedAttribute(instance: TextAreaAttribute): void { }
    applyFocusedAttribute(instance: TextAreaAttribute): void { }
    applyDisabledAttribute(instance: TextAreaAttribute): void { }
    applySelectedAttribute(instance: TextAreaAttribute): void { }
    public _placeholderColor_0_0value?: ResourceColor | undefined
    public _placeholderFont_0_0value?: arkui_component_units_Font | undefined
    public _enterKeyType_0_0value?: EnterKeyType | undefined
    public _textAlign_0_0value?: TextAlign | undefined
    public _caretColor_0_0value?: ResourceColor | undefined
    public _fontColor_0_0value?: ResourceColor | undefined
    public _fontSize_0_0value?: Length | undefined
    public _fontStyle_0_0value?: FontStyle | undefined
    public _fontWeight_0_0value?: int32 | FontWeight | ResourceStr | undefined
    public _fontFamily_0_0value?: ResourceStr | undefined
    public _textOverflow_0_0value?: TextOverflow | undefined
    public _textIndent_0_0value?: Dimension | undefined
    public _caretStyle_0_0value?: CaretStyle | undefined
    public _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    public _onSubmit_0_0value?: TextAreaSubmitCallback | undefined
    public _onChange_0_0value?: EditableTextOnChangeCallback | undefined
    public _onTextSelectionChange_0_0value?: ((first: int32,last: int32) => void) | undefined
    public _onContentScroll_0_0value?: ((totalOffsetX: double,totalOffsetY: double) => void) | undefined
    public _onEditChange_0_0value?: ((isSelected: boolean) => void) | undefined
    public _onCopy_0_0value?: ((breakpoints: string) => void) | undefined
    public _onCut_0_0value?: ((breakpoints: string) => void) | undefined
    public _onPaste_0_0value?: ((value: string,event: PasteEvent) => void) | undefined
    public _copyOption_0_0value?: CopyOptions | undefined
    public _enableKeyboardOnFocus_0_0value?: boolean | undefined
    public _maxLength_0_0value?: int32 | undefined
    public _style_0_0value?: TextContentStyle | undefined
    public _barState_0_0value?: BarState | undefined
    public _selectionMenuHidden_0_0value?: boolean | undefined
    public _minFontSize_0_0value?: double | string | global_resource_Resource | undefined
    public _maxFontSize_0_0value?: double | string | global_resource_Resource | undefined
    public _minFontScale_0_0value?: double | global_resource_Resource | undefined
    public _maxFontScale_0_0value?: double | global_resource_Resource | undefined
    public _heightAdaptivePolicy_0_0value?: TextHeightAdaptivePolicy | undefined
    public _wordBreak_0_0value?: WordBreak | undefined
    public _lineBreakStrategy_0_0value?: LineBreakStrategy | undefined
    public _decoration_0_0value?: TextDecorationOptions | undefined
    public _letterSpacing_0_0value?: double | string | global_resource_Resource | undefined
    public _lineHeight_0_0value?: double | string | global_resource_Resource | undefined
    public _type_0_0value?: TextAreaType | undefined
    public _enableAutoFill_0_0value?: boolean | undefined
    public _contentType_0_0value?: ContentType | undefined
    public _fontFeature_0_0value?: string | undefined
    public _onWillInsert_0_0value?: arkui_component_common_Callback<InsertValue, boolean> | undefined
    public _onDidInsert_0_0value?: arkui_component_common_Callback<InsertValue, void> | undefined
    public _onWillDelete_0_0value?: arkui_component_common_Callback<DeleteValue, boolean> | undefined
    public _onDidDelete_0_0value?: arkui_component_common_Callback<DeleteValue, void> | undefined
    public _editMenuOptions_0_0value?: EditMenuOptions | undefined
    public _enablePreviewText_0_0value?: boolean | undefined
    public _enableHapticFeedback_0_0value?: boolean | undefined
    public _autoCapitalizationMode_0_0value?: AutoCapitalizationMode | undefined
    public _halfLeading_0_0value?: boolean | undefined
    public _ellipsisMode_0_0value?: EllipsisMode | undefined
    public _stopBackPress_0_0value?: boolean | undefined
    public _onWillChange_0_0value?: arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined
    public _keyboardAppearance_0_0value?: KeyboardAppearance | undefined
    public _includeFontPadding_0_0value?: boolean | undefined
    public _fallbackLineSpacing_0_0value?: boolean | undefined
    public _minLines_0_0value?: int32 | undefined
    public _enableAutoSpacing_0_0value?: boolean | undefined
    public _strokeWidth_0_0value?: arkui_component_units_LengthMetrics | undefined
    public _strokeColor_0_0value?: ResourceColor | undefined
    public _onWillAttachIME_0_0value?: arkui_component_common_Callback<IMEClient, void> | undefined
    public _scrollBarColor_0_0value?: arkui_component_units_ColorMetrics | undefined
    public _enableSelectedDataDetector_0_0value?: boolean | undefined
    public _compressLeadingPunctuation_0_0value?: boolean | undefined
    public _selectedDragPreviewStyle_0_0value?: SelectedDragPreviewStyle | undefined
    public _textDirection_0_0value?: TextDirection | undefined
    public _voiceButton_0_0value?: VoiceButtonOptions | undefined
    public _horizontalScrolling_0_0value?: boolean | undefined
    public _inputFilter_0_0value?: ResourceStr | undefined
    public _inputFilter_0_1value?: ((breakpoints: string) => void) | undefined
    public _showCounter_0_0value?: boolean | undefined
    public _showCounter_0_1value?: InputCounterOptions | undefined
    public _maxLines_0_0value?: int32 | undefined
    public _maxLines_0_1value?: MaxLinesOptions | undefined
    public _customKeyboard_0_0value?: CustomBuilder | ComponentContentBase | undefined
    public _customKeyboard_0_1value?: KeyboardOptions | undefined
    public _lineSpacing_0_0value?: arkui_component_units_LengthMetrics | undefined
    public _lineSpacing_0_1value?: LineSpacingOptions | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTextAreaPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
        this.applyModifierPatch2(peer, flagArray);
        this.applyModifierPatch3(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTextAreaPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setPlaceholderColorAttribute((this._placeholderColor_0_0value as ResourceColor | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setPlaceholderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setPlaceholderFontAttribute((this._placeholderFont_0_0value as arkui_component_units_Font | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setPlaceholderFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setEnterKeyTypeAttribute((this._enterKeyType_0_0value as EnterKeyType | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setEnterKeyTypeAttribute((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setTextAlignAttribute((this._textAlign_0_0value as TextAlign | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setTextAlignAttribute((undefined as TextAlign | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setCaretColorAttribute((this._caretColor_0_0value as ResourceColor | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setCaretColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setFontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | ResourceStr | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | ResourceStr | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as ResourceStr | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setFontFamilyAttribute((undefined as ResourceStr | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setTextOverflowAttribute((this._textOverflow_0_0value as TextOverflow | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setTextOverflowAttribute((undefined as TextOverflow | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setTextIndentAttribute((this._textIndent_0_0value as Dimension | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setTextIndentAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setCaretStyleAttribute((this._caretStyle_0_0value as CaretStyle | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setCaretStyleAttribute((undefined as CaretStyle | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setSelectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setSelectedBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setOnSubmitAttribute((this._onSubmit_0_0value as TextAreaSubmitCallback | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setOnSubmitAttribute((undefined as TextAreaSubmitCallback | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as EditableTextOnChangeCallback | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setOnChangeAttribute((undefined as EditableTextOnChangeCallback | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setOnTextSelectionChangeAttribute((this._onTextSelectionChange_0_0value as ((first: int32,last: int32) => void) | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setOnTextSelectionChangeAttribute((undefined as ((first: int32,last: int32) => void) | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setOnContentScrollAttribute((this._onContentScroll_0_0value as ((totalOffsetX: double,totalOffsetY: double) => void) | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setOnContentScrollAttribute((undefined as ((totalOffsetX: double,totalOffsetY: double) => void) | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setOnEditChangeAttribute((this._onEditChange_0_0value as ((isSelected: boolean) => void) | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setOnEditChangeAttribute((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setOnCopyAttribute((this._onCopy_0_0value as ((breakpoints: string) => void) | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setOnCopyAttribute((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkTextAreaPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setOnCutAttribute((this._onCut_0_0value as ((breakpoints: string) => void) | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setOnCutAttribute((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setOnPasteAttribute((this._onPaste_0_0value as ((value: string,event: PasteEvent) => void) | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setOnPasteAttribute((undefined as ((value: string,event: PasteEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setCopyOptionAttribute((this._copyOption_0_0value as CopyOptions | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setCopyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setEnableKeyboardOnFocusAttribute((this._enableKeyboardOnFocus_0_0value as boolean | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setEnableKeyboardOnFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setMaxLengthAttribute((this._maxLength_0_0value as int32 | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setMaxLengthAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setStyleAttribute((this._style_0_0value as TextContentStyle | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setStyleAttribute((undefined as TextContentStyle | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setBarStateAttribute((this._barState_0_0value as BarState | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setBarStateAttribute((undefined as BarState | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setSelectionMenuHiddenAttribute((this._selectionMenuHidden_0_0value as boolean | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setSelectionMenuHiddenAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setMinFontSizeAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setMaxFontSizeAttribute((this._maxFontSize_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setMaxFontSizeAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | global_resource_Resource | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setMinFontScaleAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | global_resource_Resource | undefined));
                    flagArray[31] = 2;
                    break;
                }
                case 3: {
                    flagArray[31] = 2;
                    break;
                }
                default: {
                    flagArray[31] = 0;
                    peer.setMaxFontScaleAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1: {
                    peer.setHeightAdaptivePolicyAttribute((this._heightAdaptivePolicy_0_0value as TextHeightAdaptivePolicy | undefined));
                    flagArray[32] = 2;
                    break;
                }
                case 3: {
                    flagArray[32] = 2;
                    break;
                }
                default: {
                    flagArray[32] = 0;
                    peer.setHeightAdaptivePolicyAttribute((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1: {
                    peer.setWordBreakAttribute((this._wordBreak_0_0value as WordBreak | undefined));
                    flagArray[33] = 2;
                    break;
                }
                case 3: {
                    flagArray[33] = 2;
                    break;
                }
                default: {
                    flagArray[33] = 0;
                    peer.setWordBreakAttribute((undefined as WordBreak | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1: {
                    peer.setLineBreakStrategyAttribute((this._lineBreakStrategy_0_0value as LineBreakStrategy | undefined));
                    flagArray[34] = 2;
                    break;
                }
                case 3: {
                    flagArray[34] = 2;
                    break;
                }
                default: {
                    flagArray[34] = 0;
                    peer.setLineBreakStrategyAttribute((undefined as LineBreakStrategy | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1: {
                    peer.setDecorationAttribute((this._decoration_0_0value as TextDecorationOptions | undefined));
                    flagArray[35] = 2;
                    break;
                }
                case 3: {
                    flagArray[35] = 2;
                    break;
                }
                default: {
                    flagArray[35] = 0;
                    peer.setDecorationAttribute((undefined as TextDecorationOptions | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1: {
                    peer.setLetterSpacingAttribute((this._letterSpacing_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[36] = 2;
                    break;
                }
                case 3: {
                    flagArray[36] = 2;
                    break;
                }
                default: {
                    flagArray[36] = 0;
                    peer.setLetterSpacingAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1: {
                    peer.setLineHeightAttribute((this._lineHeight_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[37] = 2;
                    break;
                }
                case 3: {
                    flagArray[37] = 2;
                    break;
                }
                default: {
                    flagArray[37] = 0;
                    peer.setLineHeightAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1: {
                    peer.setTypeAttribute((this._type_0_0value as TextAreaType | undefined));
                    flagArray[38] = 2;
                    break;
                }
                case 3: {
                    flagArray[38] = 2;
                    break;
                }
                default: {
                    flagArray[38] = 0;
                    peer.setTypeAttribute((undefined as TextAreaType | undefined));
                }
            }
        }
        if (flagArray[39] != 0) {
            switch (flagArray[39]) {
                case 1: {
                    peer.setEnableAutoFillAttribute((this._enableAutoFill_0_0value as boolean | undefined));
                    flagArray[39] = 2;
                    break;
                }
                case 3: {
                    flagArray[39] = 2;
                    break;
                }
                default: {
                    flagArray[39] = 0;
                    peer.setEnableAutoFillAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch2(peer: ArkTextAreaPeer, flagArray: Uint8Array): void {
        if (flagArray[40] != 0) {
            switch (flagArray[40]) {
                case 1: {
                    peer.setContentTypeAttribute((this._contentType_0_0value as ContentType | undefined));
                    flagArray[40] = 2;
                    break;
                }
                case 3: {
                    flagArray[40] = 2;
                    break;
                }
                default: {
                    flagArray[40] = 0;
                    peer.setContentTypeAttribute((undefined as ContentType | undefined));
                }
            }
        }
        if (flagArray[41] != 0) {
            switch (flagArray[41]) {
                case 1: {
                    peer.setFontFeatureAttribute((this._fontFeature_0_0value as string | undefined));
                    flagArray[41] = 2;
                    break;
                }
                case 3: {
                    flagArray[41] = 2;
                    break;
                }
                default: {
                    flagArray[41] = 0;
                    peer.setFontFeatureAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[42] != 0) {
            switch (flagArray[42]) {
                case 1: {
                    peer.setOnWillInsertAttribute((this._onWillInsert_0_0value as arkui_component_common_Callback<InsertValue, boolean> | undefined));
                    flagArray[42] = 2;
                    break;
                }
                case 3: {
                    flagArray[42] = 2;
                    break;
                }
                default: {
                    flagArray[42] = 0;
                    peer.setOnWillInsertAttribute((undefined as arkui_component_common_Callback<InsertValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[43] != 0) {
            switch (flagArray[43]) {
                case 1: {
                    peer.setOnDidInsertAttribute((this._onDidInsert_0_0value as arkui_component_common_Callback<InsertValue, void> | undefined));
                    flagArray[43] = 2;
                    break;
                }
                case 3: {
                    flagArray[43] = 2;
                    break;
                }
                default: {
                    flagArray[43] = 0;
                    peer.setOnDidInsertAttribute((undefined as arkui_component_common_Callback<InsertValue, void> | undefined));
                }
            }
        }
        if (flagArray[44] != 0) {
            switch (flagArray[44]) {
                case 1: {
                    peer.setOnWillDeleteAttribute((this._onWillDelete_0_0value as arkui_component_common_Callback<DeleteValue, boolean> | undefined));
                    flagArray[44] = 2;
                    break;
                }
                case 3: {
                    flagArray[44] = 2;
                    break;
                }
                default: {
                    flagArray[44] = 0;
                    peer.setOnWillDeleteAttribute((undefined as arkui_component_common_Callback<DeleteValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[45] != 0) {
            switch (flagArray[45]) {
                case 1: {
                    peer.setOnDidDeleteAttribute((this._onDidDelete_0_0value as arkui_component_common_Callback<DeleteValue, void> | undefined));
                    flagArray[45] = 2;
                    break;
                }
                case 3: {
                    flagArray[45] = 2;
                    break;
                }
                default: {
                    flagArray[45] = 0;
                    peer.setOnDidDeleteAttribute((undefined as arkui_component_common_Callback<DeleteValue, void> | undefined));
                }
            }
        }
        if (flagArray[46] != 0) {
            switch (flagArray[46]) {
                case 1: {
                    peer.setEditMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    flagArray[46] = 2;
                    break;
                }
                case 3: {
                    flagArray[46] = 2;
                    break;
                }
                default: {
                    flagArray[46] = 0;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[47] != 0) {
            switch (flagArray[47]) {
                case 1: {
                    peer.setEnablePreviewTextAttribute((this._enablePreviewText_0_0value as boolean | undefined));
                    flagArray[47] = 2;
                    break;
                }
                case 3: {
                    flagArray[47] = 2;
                    break;
                }
                default: {
                    flagArray[47] = 0;
                    peer.setEnablePreviewTextAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[48] != 0) {
            switch (flagArray[48]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[48] = 2;
                    break;
                }
                case 3: {
                    flagArray[48] = 2;
                    break;
                }
                default: {
                    flagArray[48] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[49] != 0) {
            switch (flagArray[49]) {
                case 1: {
                    peer.setAutoCapitalizationModeAttribute((this._autoCapitalizationMode_0_0value as AutoCapitalizationMode | undefined));
                    flagArray[49] = 2;
                    break;
                }
                case 3: {
                    flagArray[49] = 2;
                    break;
                }
                default: {
                    flagArray[49] = 0;
                    peer.setAutoCapitalizationModeAttribute((undefined as AutoCapitalizationMode | undefined));
                }
            }
        }
        if (flagArray[50] != 0) {
            switch (flagArray[50]) {
                case 1: {
                    peer.setHalfLeadingAttribute((this._halfLeading_0_0value as boolean | undefined));
                    flagArray[50] = 2;
                    break;
                }
                case 3: {
                    flagArray[50] = 2;
                    break;
                }
                default: {
                    flagArray[50] = 0;
                    peer.setHalfLeadingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[51] != 0) {
            switch (flagArray[51]) {
                case 1: {
                    peer.setEllipsisModeAttribute((this._ellipsisMode_0_0value as EllipsisMode | undefined));
                    flagArray[51] = 2;
                    break;
                }
                case 3: {
                    flagArray[51] = 2;
                    break;
                }
                default: {
                    flagArray[51] = 0;
                    peer.setEllipsisModeAttribute((undefined as EllipsisMode | undefined));
                }
            }
        }
        if (flagArray[52] != 0) {
            switch (flagArray[52]) {
                case 1: {
                    peer.setStopBackPressAttribute((this._stopBackPress_0_0value as boolean | undefined));
                    flagArray[52] = 2;
                    break;
                }
                case 3: {
                    flagArray[52] = 2;
                    break;
                }
                default: {
                    flagArray[52] = 0;
                    peer.setStopBackPressAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[53] != 0) {
            switch (flagArray[53]) {
                case 1: {
                    peer.setOnWillChangeAttribute((this._onWillChange_0_0value as arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined));
                    flagArray[53] = 2;
                    break;
                }
                case 3: {
                    flagArray[53] = 2;
                    break;
                }
                default: {
                    flagArray[53] = 0;
                    peer.setOnWillChangeAttribute((undefined as arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[54] != 0) {
            switch (flagArray[54]) {
                case 1: {
                    peer.setKeyboardAppearanceAttribute((this._keyboardAppearance_0_0value as KeyboardAppearance | undefined));
                    flagArray[54] = 2;
                    break;
                }
                case 3: {
                    flagArray[54] = 2;
                    break;
                }
                default: {
                    flagArray[54] = 0;
                    peer.setKeyboardAppearanceAttribute((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (flagArray[55] != 0) {
            switch (flagArray[55]) {
                case 1: {
                    peer.setIncludeFontPaddingAttribute((this._includeFontPadding_0_0value as boolean | undefined));
                    flagArray[55] = 2;
                    break;
                }
                case 3: {
                    flagArray[55] = 2;
                    break;
                }
                default: {
                    flagArray[55] = 0;
                    peer.setIncludeFontPaddingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[56] != 0) {
            switch (flagArray[56]) {
                case 1: {
                    peer.setFallbackLineSpacingAttribute((this._fallbackLineSpacing_0_0value as boolean | undefined));
                    flagArray[56] = 2;
                    break;
                }
                case 3: {
                    flagArray[56] = 2;
                    break;
                }
                default: {
                    flagArray[56] = 0;
                    peer.setFallbackLineSpacingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[57] != 0) {
            switch (flagArray[57]) {
                case 1: {
                    peer.setMinLinesAttribute((this._minLines_0_0value as int32 | undefined));
                    flagArray[57] = 2;
                    break;
                }
                case 3: {
                    flagArray[57] = 2;
                    break;
                }
                default: {
                    flagArray[57] = 0;
                    peer.setMinLinesAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[58] != 0) {
            switch (flagArray[58]) {
                case 1: {
                    peer.setEnableAutoSpacingAttribute((this._enableAutoSpacing_0_0value as boolean | undefined));
                    flagArray[58] = 2;
                    break;
                }
                case 3: {
                    flagArray[58] = 2;
                    break;
                }
                default: {
                    flagArray[58] = 0;
                    peer.setEnableAutoSpacingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[59] != 0) {
            switch (flagArray[59]) {
                case 1: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as arkui_component_units_LengthMetrics | undefined));
                    flagArray[59] = 2;
                    break;
                }
                case 3: {
                    flagArray[59] = 2;
                    break;
                }
                default: {
                    flagArray[59] = 0;
                    peer.setStrokeWidthAttribute((undefined as arkui_component_units_LengthMetrics | undefined));
                }
            }
        }
    }
    applyModifierPatch3(peer: ArkTextAreaPeer, flagArray: Uint8Array): void {
        if (flagArray[60] != 0) {
            switch (flagArray[60]) {
                case 1: {
                    peer.setStrokeColorAttribute((this._strokeColor_0_0value as ResourceColor | undefined));
                    flagArray[60] = 2;
                    break;
                }
                case 3: {
                    flagArray[60] = 2;
                    break;
                }
                default: {
                    flagArray[60] = 0;
                    peer.setStrokeColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[61] != 0) {
            switch (flagArray[61]) {
                case 1: {
                    peer.setOnWillAttachIMEAttribute((this._onWillAttachIME_0_0value as arkui_component_common_Callback<IMEClient, void> | undefined));
                    flagArray[61] = 2;
                    break;
                }
                case 3: {
                    flagArray[61] = 2;
                    break;
                }
                default: {
                    flagArray[61] = 0;
                    peer.setOnWillAttachIMEAttribute((undefined as arkui_component_common_Callback<IMEClient, void> | undefined));
                }
            }
        }
        if (flagArray[62] != 0) {
            switch (flagArray[62]) {
                case 1: {
                    peer.setScrollBarColorAttribute((this._scrollBarColor_0_0value as arkui_component_units_ColorMetrics | undefined));
                    flagArray[62] = 2;
                    break;
                }
                case 3: {
                    flagArray[62] = 2;
                    break;
                }
                default: {
                    flagArray[62] = 0;
                    peer.setScrollBarColorAttribute((undefined as arkui_component_units_ColorMetrics | undefined));
                }
            }
        }
        if (flagArray[63] != 0) {
            switch (flagArray[63]) {
                case 1: {
                    peer.setEnableSelectedDataDetectorAttribute((this._enableSelectedDataDetector_0_0value as boolean | undefined));
                    flagArray[63] = 2;
                    break;
                }
                case 3: {
                    flagArray[63] = 2;
                    break;
                }
                default: {
                    flagArray[63] = 0;
                    peer.setEnableSelectedDataDetectorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[64] != 0) {
            switch (flagArray[64]) {
                case 1: {
                    peer.setCompressLeadingPunctuationAttribute((this._compressLeadingPunctuation_0_0value as boolean | undefined));
                    flagArray[64] = 2;
                    break;
                }
                case 3: {
                    flagArray[64] = 2;
                    break;
                }
                default: {
                    flagArray[64] = 0;
                    peer.setCompressLeadingPunctuationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[65] != 0) {
            switch (flagArray[65]) {
                case 1: {
                    peer.setSelectedDragPreviewStyleAttribute((this._selectedDragPreviewStyle_0_0value as SelectedDragPreviewStyle | undefined));
                    flagArray[65] = 2;
                    break;
                }
                case 3: {
                    flagArray[65] = 2;
                    break;
                }
                default: {
                    flagArray[65] = 0;
                    peer.setSelectedDragPreviewStyleAttribute((undefined as SelectedDragPreviewStyle | undefined));
                }
            }
        }
        if (flagArray[66] != 0) {
            switch (flagArray[66]) {
                case 1: {
                    peer.setTextDirectionAttribute((this._textDirection_0_0value as TextDirection | undefined));
                    flagArray[66] = 2;
                    break;
                }
                case 3: {
                    flagArray[66] = 2;
                    break;
                }
                default: {
                    flagArray[66] = 0;
                    peer.setTextDirectionAttribute((undefined as TextDirection | undefined));
                }
            }
        }
        if (flagArray[67] != 0) {
            switch (flagArray[67]) {
                case 1: {
                    peer.setVoiceButtonAttribute((this._voiceButton_0_0value as VoiceButtonOptions | undefined));
                    flagArray[67] = 2;
                    break;
                }
                case 3: {
                    flagArray[67] = 2;
                    break;
                }
                default: {
                    flagArray[67] = 0;
                    peer.setVoiceButtonAttribute((undefined as VoiceButtonOptions | undefined));
                }
            }
        }
        if (flagArray[68] != 0) {
            switch (flagArray[68]) {
                case 1: {
                    peer.setHorizontalScrollingAttribute((this._horizontalScrolling_0_0value as boolean | undefined));
                    flagArray[68] = 2;
                    break;
                }
                case 3: {
                    flagArray[68] = 2;
                    break;
                }
                default: {
                    flagArray[68] = 0;
                    peer.setHorizontalScrollingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[69] != 0) {
            switch (flagArray[69]) {
                case 1: {
                    peer.setInputFilterAttribute((this._inputFilter_0_0value as ResourceStr | undefined), (this._inputFilter_0_1value as ((breakpoints: string) => void) | undefined | undefined));
                    flagArray[69] = 2;
                    break;
                }
                case 3: {
                    flagArray[69] = 2;
                    break;
                }
                default: {
                    flagArray[69] = 0;
                    peer.setInputFilterAttribute((undefined as ResourceStr | undefined), (undefined as ((breakpoints: string) => void) | undefined | undefined));
                }
            }
        }
        if (flagArray[70] != 0) {
            switch (flagArray[70]) {
                case 1: {
                    peer.setShowCounterAttribute((this._showCounter_0_0value as boolean | undefined), (this._showCounter_0_1value as InputCounterOptions | undefined));
                    flagArray[70] = 2;
                    break;
                }
                case 3: {
                    flagArray[70] = 2;
                    break;
                }
                default: {
                    flagArray[70] = 0;
                    peer.setShowCounterAttribute((undefined as boolean | undefined), (undefined as InputCounterOptions | undefined));
                }
            }
        }
        if (flagArray[71] != 0) {
            switch (flagArray[71]) {
                case 1: {
                    peer.setMaxLinesAttribute((this._maxLines_0_0value as int32 | undefined), (this._maxLines_0_1value as MaxLinesOptions | undefined));
                    flagArray[71] = 2;
                    break;
                }
                case 3: {
                    flagArray[71] = 2;
                    break;
                }
                default: {
                    flagArray[71] = 0;
                    peer.setMaxLinesAttribute((undefined as int32 | undefined), (undefined as MaxLinesOptions | undefined));
                }
            }
        }
        if (flagArray[72] != 0) {
            switch (flagArray[72]) {
                case 1: {
                    peer.setCustomKeyboardAttribute((this._customKeyboard_0_0value as CustomBuilder | ComponentContentBase | undefined), (this._customKeyboard_0_1value as KeyboardOptions | undefined));
                    flagArray[72] = 2;
                    break;
                }
                case 3: {
                    flagArray[72] = 2;
                    break;
                }
                default: {
                    flagArray[72] = 0;
                    peer.setCustomKeyboardAttribute((undefined as CustomBuilder | ComponentContentBase | undefined), (undefined as KeyboardOptions | undefined));
                }
            }
        }
        if (flagArray[73] != 0) {
            switch (flagArray[73]) {
                case 1: {
                    peer.setLineSpacingAttribute((this._lineSpacing_0_0value as arkui_component_units_LengthMetrics | undefined), (this._lineSpacing_0_1value as LineSpacingOptions | undefined));
                    flagArray[73] = 2;
                    break;
                }
                case 3: {
                    flagArray[73] = 2;
                    break;
                }
                default: {
                    flagArray[73] = 0;
                    peer.setLineSpacingAttribute((undefined as arkui_component_units_LengthMetrics | undefined), (undefined as LineSpacingOptions | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TextAreaModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
        this.mergeModifier2(modifier, flagArray);
        this.mergeModifier3(modifier, flagArray);
    }
    mergeModifier0(modifier: TextAreaModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.placeholderColor((modifier._placeholderColor_0_0value as ResourceColor | undefined));
                    break;
                }
                default: {
                    this.placeholderColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.placeholderFont((modifier._placeholderFont_0_0value as arkui_component_units_Font | undefined));
                    break;
                }
                default: {
                    this.placeholderFont((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.enterKeyType((modifier._enterKeyType_0_0value as EnterKeyType | undefined));
                    break;
                }
                default: {
                    this.enterKeyType((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.textAlign((modifier._textAlign_0_0value as TextAlign | undefined));
                    break;
                }
                default: {
                    this.textAlign((undefined as TextAlign | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.caretColor((modifier._caretColor_0_0value as ResourceColor | undefined));
                    break;
                }
                default: {
                    this.caretColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.fontColor((modifier._fontColor_0_0value as ResourceColor | undefined));
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.fontSize((modifier._fontSize_0_0value as Length | undefined));
                    break;
                }
                default: {
                    this.fontSize((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.fontStyle((modifier._fontStyle_0_0value as FontStyle | undefined));
                    break;
                }
                default: {
                    this.fontStyle((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.fontWeight((modifier._fontWeight_0_0value as int32 | FontWeight | ResourceStr | undefined));
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | ResourceStr | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.fontFamily((modifier._fontFamily_0_0value as ResourceStr | undefined));
                    break;
                }
                default: {
                    this.fontFamily((undefined as ResourceStr | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.textOverflow((modifier._textOverflow_0_0value as TextOverflow | undefined));
                    break;
                }
                default: {
                    this.textOverflow((undefined as TextOverflow | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.textIndent((modifier._textIndent_0_0value as Dimension | undefined));
                    break;
                }
                default: {
                    this.textIndent((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.caretStyle((modifier._caretStyle_0_0value as CaretStyle | undefined));
                    break;
                }
                default: {
                    this.caretStyle((undefined as CaretStyle | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.selectedBackgroundColor((modifier._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    break;
                }
                default: {
                    this.selectedBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.onSubmit((modifier._onSubmit_0_0value as TextAreaSubmitCallback | undefined));
                    break;
                }
                default: {
                    this.onSubmit((undefined as TextAreaSubmitCallback | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.onChange((modifier._onChange_0_0value as EditableTextOnChangeCallback | undefined));
                    break;
                }
                default: {
                    this.onChange((undefined as EditableTextOnChangeCallback | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.onTextSelectionChange((modifier._onTextSelectionChange_0_0value as ((first: int32,last: int32) => void) | undefined));
                    break;
                }
                default: {
                    this.onTextSelectionChange((undefined as ((first: int32,last: int32) => void) | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.onContentScroll((modifier._onContentScroll_0_0value as ((totalOffsetX: double,totalOffsetY: double) => void) | undefined));
                    break;
                }
                default: {
                    this.onContentScroll((undefined as ((totalOffsetX: double,totalOffsetY: double) => void) | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.onEditChange((modifier._onEditChange_0_0value as ((isSelected: boolean) => void) | undefined));
                    break;
                }
                default: {
                    this.onEditChange((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.onCopy((modifier._onCopy_0_0value as ((breakpoints: string) => void) | undefined));
                    break;
                }
                default: {
                    this.onCopy((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: TextAreaModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.onCut((modifier._onCut_0_0value as ((breakpoints: string) => void) | undefined));
                    break;
                }
                default: {
                    this.onCut((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.onPaste((modifier._onPaste_0_0value as ((value: string,event: PasteEvent) => void) | undefined));
                    break;
                }
                default: {
                    this.onPaste((undefined as ((value: string,event: PasteEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.copyOption((modifier._copyOption_0_0value as CopyOptions | undefined));
                    break;
                }
                default: {
                    this.copyOption((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.enableKeyboardOnFocus((modifier._enableKeyboardOnFocus_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableKeyboardOnFocus((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.maxLength((modifier._maxLength_0_0value as int32 | undefined));
                    break;
                }
                default: {
                    this.maxLength((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.style((modifier._style_0_0value as TextContentStyle | undefined));
                    break;
                }
                default: {
                    this.style((undefined as TextContentStyle | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.barState((modifier._barState_0_0value as BarState | undefined));
                    break;
                }
                default: {
                    this.barState((undefined as BarState | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.selectionMenuHidden((modifier._selectionMenuHidden_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.selectionMenuHidden((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.minFontSize((modifier._minFontSize_0_0value as double | string | global_resource_Resource | undefined));
                    break;
                }
                default: {
                    this.minFontSize((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.maxFontSize((modifier._maxFontSize_0_0value as double | string | global_resource_Resource | undefined));
                    break;
                }
                default: {
                    this.maxFontSize((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
                    this.minFontScale((modifier._minFontScale_0_0value as double | global_resource_Resource | undefined));
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1:
                case 3: {
                    this.maxFontScale((modifier._maxFontScale_0_0value as double | global_resource_Resource | undefined));
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1:
                case 3: {
                    this.heightAdaptivePolicy((modifier._heightAdaptivePolicy_0_0value as TextHeightAdaptivePolicy | undefined));
                    break;
                }
                default: {
                    this.heightAdaptivePolicy((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1:
                case 3: {
                    this.wordBreak((modifier._wordBreak_0_0value as WordBreak | undefined));
                    break;
                }
                default: {
                    this.wordBreak((undefined as WordBreak | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1:
                case 3: {
                    this.lineBreakStrategy((modifier._lineBreakStrategy_0_0value as LineBreakStrategy | undefined));
                    break;
                }
                default: {
                    this.lineBreakStrategy((undefined as LineBreakStrategy | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1:
                case 3: {
                    this.decoration((modifier._decoration_0_0value as TextDecorationOptions | undefined));
                    break;
                }
                default: {
                    this.decoration((undefined as TextDecorationOptions | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1:
                case 3: {
                    this.letterSpacing((modifier._letterSpacing_0_0value as double | string | global_resource_Resource | undefined));
                    break;
                }
                default: {
                    this.letterSpacing((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1:
                case 3: {
                    this.lineHeight((modifier._lineHeight_0_0value as double | string | global_resource_Resource | undefined));
                    break;
                }
                default: {
                    this.lineHeight((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1:
                case 3: {
                    this.type((modifier._type_0_0value as TextAreaType | undefined));
                    break;
                }
                default: {
                    this.type((undefined as TextAreaType | undefined));
                }
            }
        }
        if (flagArray[39] != 0) {
            switch (flagArray[39]) {
                case 1:
                case 3: {
                    this.enableAutoFill((modifier._enableAutoFill_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableAutoFill((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier2(modifier: TextAreaModifier, flagArray: Uint8Array): void {
        if (flagArray[40] != 0) {
            switch (flagArray[40]) {
                case 1:
                case 3: {
                    this.contentType((modifier._contentType_0_0value as ContentType | undefined));
                    break;
                }
                default: {
                    this.contentType((undefined as ContentType | undefined));
                }
            }
        }
        if (flagArray[41] != 0) {
            switch (flagArray[41]) {
                case 1:
                case 3: {
                    this.fontFeature((modifier._fontFeature_0_0value as string | undefined));
                    break;
                }
                default: {
                    this.fontFeature((undefined as string | undefined));
                }
            }
        }
        if (flagArray[42] != 0) {
            switch (flagArray[42]) {
                case 1:
                case 3: {
                    this.onWillInsert((modifier._onWillInsert_0_0value as arkui_component_common_Callback<InsertValue, boolean> | undefined));
                    break;
                }
                default: {
                    this.onWillInsert((undefined as arkui_component_common_Callback<InsertValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[43] != 0) {
            switch (flagArray[43]) {
                case 1:
                case 3: {
                    this.onDidInsert((modifier._onDidInsert_0_0value as arkui_component_common_Callback<InsertValue, void> | undefined));
                    break;
                }
                default: {
                    this.onDidInsert((undefined as arkui_component_common_Callback<InsertValue, void> | undefined));
                }
            }
        }
        if (flagArray[44] != 0) {
            switch (flagArray[44]) {
                case 1:
                case 3: {
                    this.onWillDelete((modifier._onWillDelete_0_0value as arkui_component_common_Callback<DeleteValue, boolean> | undefined));
                    break;
                }
                default: {
                    this.onWillDelete((undefined as arkui_component_common_Callback<DeleteValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[45] != 0) {
            switch (flagArray[45]) {
                case 1:
                case 3: {
                    this.onDidDelete((modifier._onDidDelete_0_0value as arkui_component_common_Callback<DeleteValue, void> | undefined));
                    break;
                }
                default: {
                    this.onDidDelete((undefined as arkui_component_common_Callback<DeleteValue, void> | undefined));
                }
            }
        }
        if (flagArray[46] != 0) {
            switch (flagArray[46]) {
                case 1:
                case 3: {
                    this.editMenuOptions((modifier._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[47] != 0) {
            switch (flagArray[47]) {
                case 1:
                case 3: {
                    this.enablePreviewText((modifier._enablePreviewText_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enablePreviewText((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[48] != 0) {
            switch (flagArray[48]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback((modifier._enableHapticFeedback_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[49] != 0) {
            switch (flagArray[49]) {
                case 1:
                case 3: {
                    this.autoCapitalizationMode((modifier._autoCapitalizationMode_0_0value as AutoCapitalizationMode | undefined));
                    break;
                }
                default: {
                    this.autoCapitalizationMode((undefined as AutoCapitalizationMode | undefined));
                }
            }
        }
        if (flagArray[50] != 0) {
            switch (flagArray[50]) {
                case 1:
                case 3: {
                    this.halfLeading((modifier._halfLeading_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.halfLeading((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[51] != 0) {
            switch (flagArray[51]) {
                case 1:
                case 3: {
                    this.ellipsisMode((modifier._ellipsisMode_0_0value as EllipsisMode | undefined));
                    break;
                }
                default: {
                    this.ellipsisMode((undefined as EllipsisMode | undefined));
                }
            }
        }
        if (flagArray[52] != 0) {
            switch (flagArray[52]) {
                case 1:
                case 3: {
                    this.stopBackPress((modifier._stopBackPress_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.stopBackPress((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[53] != 0) {
            switch (flagArray[53]) {
                case 1:
                case 3: {
                    this.onWillChange((modifier._onWillChange_0_0value as arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined));
                    break;
                }
                default: {
                    this.onWillChange((undefined as arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[54] != 0) {
            switch (flagArray[54]) {
                case 1:
                case 3: {
                    this.keyboardAppearance((modifier._keyboardAppearance_0_0value as KeyboardAppearance | undefined));
                    break;
                }
                default: {
                    this.keyboardAppearance((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (flagArray[55] != 0) {
            switch (flagArray[55]) {
                case 1:
                case 3: {
                    this.includeFontPadding((modifier._includeFontPadding_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.includeFontPadding((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[56] != 0) {
            switch (flagArray[56]) {
                case 1:
                case 3: {
                    this.fallbackLineSpacing((modifier._fallbackLineSpacing_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.fallbackLineSpacing((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[57] != 0) {
            switch (flagArray[57]) {
                case 1:
                case 3: {
                    this.minLines((modifier._minLines_0_0value as int32 | undefined));
                    break;
                }
                default: {
                    this.minLines((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[58] != 0) {
            switch (flagArray[58]) {
                case 1:
                case 3: {
                    this.enableAutoSpacing((modifier._enableAutoSpacing_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableAutoSpacing((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[59] != 0) {
            switch (flagArray[59]) {
                case 1:
                case 3: {
                    this.strokeWidth((modifier._strokeWidth_0_0value as arkui_component_units_LengthMetrics | undefined));
                    break;
                }
                default: {
                    this.strokeWidth((undefined as arkui_component_units_LengthMetrics | undefined));
                }
            }
        }
    }
    mergeModifier3(modifier: TextAreaModifier, flagArray: Uint8Array): void {
        if (flagArray[60] != 0) {
            switch (flagArray[60]) {
                case 1:
                case 3: {
                    this.strokeColor((modifier._strokeColor_0_0value as ResourceColor | undefined));
                    break;
                }
                default: {
                    this.strokeColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[61] != 0) {
            switch (flagArray[61]) {
                case 1:
                case 3: {
                    this.onWillAttachIME((modifier._onWillAttachIME_0_0value as arkui_component_common_Callback<IMEClient, void> | undefined));
                    break;
                }
                default: {
                    this.onWillAttachIME((undefined as arkui_component_common_Callback<IMEClient, void> | undefined));
                }
            }
        }
        if (flagArray[62] != 0) {
            switch (flagArray[62]) {
                case 1:
                case 3: {
                    this.scrollBarColor((modifier._scrollBarColor_0_0value as arkui_component_units_ColorMetrics | undefined));
                    break;
                }
                default: {
                    this.scrollBarColor((undefined as arkui_component_units_ColorMetrics | undefined));
                }
            }
        }
        if (flagArray[63] != 0) {
            switch (flagArray[63]) {
                case 1:
                case 3: {
                    this.enableSelectedDataDetector((modifier._enableSelectedDataDetector_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableSelectedDataDetector((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[64] != 0) {
            switch (flagArray[64]) {
                case 1:
                case 3: {
                    this.compressLeadingPunctuation((modifier._compressLeadingPunctuation_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.compressLeadingPunctuation((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[65] != 0) {
            switch (flagArray[65]) {
                case 1:
                case 3: {
                    this.selectedDragPreviewStyle((modifier._selectedDragPreviewStyle_0_0value as SelectedDragPreviewStyle | undefined));
                    break;
                }
                default: {
                    this.selectedDragPreviewStyle((undefined as SelectedDragPreviewStyle | undefined));
                }
            }
        }
        if (flagArray[66] != 0) {
            switch (flagArray[66]) {
                case 1:
                case 3: {
                    this.textDirection((modifier._textDirection_0_0value as TextDirection | undefined));
                    break;
                }
                default: {
                    this.textDirection((undefined as TextDirection | undefined));
                }
            }
        }
        if (flagArray[67] != 0) {
            switch (flagArray[67]) {
                case 1:
                case 3: {
                    this.voiceButton((modifier._voiceButton_0_0value as VoiceButtonOptions | undefined));
                    break;
                }
                default: {
                    this.voiceButton((undefined as VoiceButtonOptions | undefined));
                }
            }
        }
        if (flagArray[68] != 0) {
            switch (flagArray[68]) {
                case 1:
                case 3: {
                    this.horizontalScrolling((modifier._horizontalScrolling_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.horizontalScrolling((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[69] != 0) {
            switch (flagArray[69]) {
                case 1:
                case 3: {
                    this.inputFilter((modifier._inputFilter_0_0value as ResourceStr | undefined), (modifier._inputFilter_0_1value as ((breakpoints: string) => void) | undefined));
                    break;
                }
                default: {
                    this.inputFilter((undefined as ResourceStr | undefined), (undefined as ((breakpoints: string) => void) | undefined | undefined));
                }
            }
        }
        if (flagArray[70] != 0) {
            switch (flagArray[70]) {
                case 1:
                case 3: {
                    this.showCounter((modifier._showCounter_0_0value as boolean | undefined), (modifier._showCounter_0_1value as InputCounterOptions | undefined));
                    break;
                }
                default: {
                    this.showCounter((undefined as boolean | undefined), (undefined as InputCounterOptions | undefined));
                }
            }
        }
        if (flagArray[71] != 0) {
            switch (flagArray[71]) {
                case 1:
                case 3: {
                    this.maxLines((modifier._maxLines_0_0value as int32 | undefined), (modifier._maxLines_0_1value as MaxLinesOptions | undefined));
                    break;
                }
                default: {
                    this.maxLines((undefined as int32 | undefined), (undefined as MaxLinesOptions | undefined));
                }
            }
        }
        if (flagArray[72] != 0) {
            switch (flagArray[72]) {
                case 1:
                case 3: {
                    this.customKeyboard((modifier._customKeyboard_0_0value as CustomBuilder | ComponentContentBase | undefined), (modifier._customKeyboard_0_1value as KeyboardOptions | undefined));
                    break;
                }
                default: {
                    this.customKeyboard((undefined as CustomBuilder | ComponentContentBase | undefined), (undefined as KeyboardOptions | undefined));
                }
            }
        }
        if (flagArray[73] != 0) {
            switch (flagArray[73]) {
                case 1:
                case 3: {
                    this.lineSpacing((modifier._lineSpacing_0_0value as arkui_component_units_LengthMetrics | undefined), (modifier._lineSpacing_0_1value as LineSpacingOptions | undefined));
                    break;
                }
                default: {
                    this.lineSpacing((undefined as arkui_component_units_LengthMetrics | undefined), (undefined as LineSpacingOptions | undefined));
                }
            }
        }
    }
    placeholderColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._placeholderColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    placeholderFont(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._placeholderFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._enterKeyType_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    textAlign(value: TextAlign | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._textAlign_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    caretColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._caretColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    fontSize(value: Length | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._fontStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | ResourceStr | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    fontFamily(value: ResourceStr | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    textOverflow(value: TextOverflow | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._textOverflow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    textIndent(value: Dimension | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._textIndent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    caretStyle(value: CaretStyle | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._caretStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._selectedBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    onSubmit(value: TextAreaSubmitCallback | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._onSubmit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    onTextSelectionChange(value: ((first: int32,last: int32) => void) | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._onTextSelectionChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    onContentScroll(value: ((totalOffsetX: double,totalOffsetY: double) => void) | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._onContentScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    onEditChange(value: ((isSelected: boolean) => void) | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._onEditChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._onCopy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    onCut(value: ((breakpoints: string) => void) | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._onCut_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    onPaste(value: ((value: string,event: PasteEvent) => void) | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._onPaste_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._copyOption_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        if (((this._flagArray[23]) == (0)) || ((this._enableKeyboardOnFocus_0_0value) !== (value))) {
            this._flagArray[23] = 1
            this._enableKeyboardOnFocus_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    maxLength(value: int32 | undefined): this {
        if (((this._flagArray[24]) == (0)) || ((this._maxLength_0_0value) !== (value))) {
            this._flagArray[24] = 1
            this._maxLength_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    style(value: TextContentStyle | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true)) {
            this._flagArray[25] = 1
            this._style_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    barState(value: BarState | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true)) {
            this._flagArray[26] = 1
            this._barState_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    selectionMenuHidden(value: boolean | undefined): this {
        if (((this._flagArray[27]) == (0)) || ((this._selectionMenuHidden_0_0value) !== (value))) {
            this._flagArray[27] = 1
            this._selectionMenuHidden_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    minFontSize(value: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[28]) == (0)) || (true)) {
            this._flagArray[28] = 1
            this._minFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    maxFontSize(value: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[29]) == (0)) || (true)) {
            this._flagArray[29] = 1
            this._maxFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    minFontScale(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[30]) == (0)) || (true)) {
            this._flagArray[30] = 1
            this._minFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    maxFontScale(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[31]) == (0)) || (true)) {
            this._flagArray[31] = 1
            this._maxFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[31] = 3
        }
        return this
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (((this._flagArray[32]) == (0)) || (true)) {
            this._flagArray[32] = 1
            this._heightAdaptivePolicy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[32] = 3
        }
        return this
    }
    wordBreak(value: WordBreak | undefined): this {
        if (((this._flagArray[33]) == (0)) || (true)) {
            this._flagArray[33] = 1
            this._wordBreak_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[33] = 3
        }
        return this
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (((this._flagArray[34]) == (0)) || (true)) {
            this._flagArray[34] = 1
            this._lineBreakStrategy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[34] = 3
        }
        return this
    }
    decoration(value: TextDecorationOptions | undefined): this {
        if (((this._flagArray[35]) == (0)) || (true)) {
            this._flagArray[35] = 1
            this._decoration_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[35] = 3
        }
        return this
    }
    letterSpacing(value: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[36]) == (0)) || (true)) {
            this._flagArray[36] = 1
            this._letterSpacing_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[36] = 3
        }
        return this
    }
    lineHeight(value: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[37]) == (0)) || (true)) {
            this._flagArray[37] = 1
            this._lineHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[37] = 3
        }
        return this
    }
    type(value: TextAreaType | undefined): this {
        if (((this._flagArray[38]) == (0)) || (true)) {
            this._flagArray[38] = 1
            this._type_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[38] = 3
        }
        return this
    }
    enableAutoFill(value: boolean | undefined): this {
        if (((this._flagArray[39]) == (0)) || ((this._enableAutoFill_0_0value) !== (value))) {
            this._flagArray[39] = 1
            this._enableAutoFill_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[39] = 3
        }
        return this
    }
    contentType(value: ContentType | undefined): this {
        if (((this._flagArray[40]) == (0)) || (true)) {
            this._flagArray[40] = 1
            this._contentType_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[40] = 3
        }
        return this
    }
    fontFeature(value: string | undefined): this {
        if (((this._flagArray[41]) == (0)) || ((this._fontFeature_0_0value) !== (value))) {
            this._flagArray[41] = 1
            this._fontFeature_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[41] = 3
        }
        return this
    }
    onWillInsert(value: arkui_component_common_Callback<InsertValue, boolean> | undefined): this {
        if (((this._flagArray[42]) == (0)) || (true)) {
            this._flagArray[42] = 1
            this._onWillInsert_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[42] = 3
        }
        return this
    }
    onDidInsert(value: arkui_component_common_Callback<InsertValue, void> | undefined): this {
        if (((this._flagArray[43]) == (0)) || (true)) {
            this._flagArray[43] = 1
            this._onDidInsert_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[43] = 3
        }
        return this
    }
    onWillDelete(value: arkui_component_common_Callback<DeleteValue, boolean> | undefined): this {
        if (((this._flagArray[44]) == (0)) || (true)) {
            this._flagArray[44] = 1
            this._onWillDelete_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[44] = 3
        }
        return this
    }
    onDidDelete(value: arkui_component_common_Callback<DeleteValue, void> | undefined): this {
        if (((this._flagArray[45]) == (0)) || (true)) {
            this._flagArray[45] = 1
            this._onDidDelete_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[45] = 3
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._flagArray[46]) == (0)) || (true)) {
            this._flagArray[46] = 1
            this._editMenuOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[46] = 3
        }
        return this
    }
    enablePreviewText(value: boolean | undefined): this {
        if (((this._flagArray[47]) == (0)) || ((this._enablePreviewText_0_0value) !== (value))) {
            this._flagArray[47] = 1
            this._enablePreviewText_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[47] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[48]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._flagArray[48] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[48] = 3
        }
        return this
    }
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        if (((this._flagArray[49]) == (0)) || (true)) {
            this._flagArray[49] = 1
            this._autoCapitalizationMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[49] = 3
        }
        return this
    }
    halfLeading(value: boolean | undefined): this {
        if (((this._flagArray[50]) == (0)) || ((this._halfLeading_0_0value) !== (value))) {
            this._flagArray[50] = 1
            this._halfLeading_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[50] = 3
        }
        return this
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        if (((this._flagArray[51]) == (0)) || (true)) {
            this._flagArray[51] = 1
            this._ellipsisMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[51] = 3
        }
        return this
    }
    stopBackPress(value: boolean | undefined): this {
        if (((this._flagArray[52]) == (0)) || ((this._stopBackPress_0_0value) !== (value))) {
            this._flagArray[52] = 1
            this._stopBackPress_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[52] = 3
        }
        return this
    }
    onWillChange(value: arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined): this {
        if (((this._flagArray[53]) == (0)) || (true)) {
            this._flagArray[53] = 1
            this._onWillChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[53] = 3
        }
        return this
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (((this._flagArray[54]) == (0)) || (true)) {
            this._flagArray[54] = 1
            this._keyboardAppearance_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[54] = 3
        }
        return this
    }
    includeFontPadding(value: boolean | undefined): this {
        if (((this._flagArray[55]) == (0)) || ((this._includeFontPadding_0_0value) !== (value))) {
            this._flagArray[55] = 1
            this._includeFontPadding_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[55] = 3
        }
        return this
    }
    fallbackLineSpacing(value: boolean | undefined): this {
        if (((this._flagArray[56]) == (0)) || ((this._fallbackLineSpacing_0_0value) !== (value))) {
            this._flagArray[56] = 1
            this._fallbackLineSpacing_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[56] = 3
        }
        return this
    }
    minLines(value: int32 | undefined): this {
        if (((this._flagArray[57]) == (0)) || ((this._minLines_0_0value) !== (value))) {
            this._flagArray[57] = 1
            this._minLines_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[57] = 3
        }
        return this
    }
    enableAutoSpacing(value: boolean | undefined): this {
        if (((this._flagArray[58]) == (0)) || ((this._enableAutoSpacing_0_0value) !== (value))) {
            this._flagArray[58] = 1
            this._enableAutoSpacing_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[58] = 3
        }
        return this
    }
    strokeWidth(value: arkui_component_units_LengthMetrics | undefined): this {
        if (((this._flagArray[59]) == (0)) || (true)) {
            this._flagArray[59] = 1
            this._strokeWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[59] = 3
        }
        return this
    }
    strokeColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[60]) == (0)) || (true)) {
            this._flagArray[60] = 1
            this._strokeColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[60] = 3
        }
        return this
    }
    onWillAttachIME(value: arkui_component_common_Callback<IMEClient, void> | undefined): this {
        if (((this._flagArray[61]) == (0)) || (true)) {
            this._flagArray[61] = 1
            this._onWillAttachIME_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[61] = 3
        }
        return this
    }
    scrollBarColor(value: arkui_component_units_ColorMetrics | undefined): this {
        if (((this._flagArray[62]) == (0)) || (true)) {
            this._flagArray[62] = 1
            this._scrollBarColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[62] = 3
        }
        return this
    }
    enableSelectedDataDetector(value: boolean | undefined): this {
        if (((this._flagArray[63]) == (0)) || ((this._enableSelectedDataDetector_0_0value) !== (value))) {
            this._flagArray[63] = 1
            this._enableSelectedDataDetector_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[63] = 3
        }
        return this
    }
    compressLeadingPunctuation(value: boolean | undefined): this {
        if (((this._flagArray[64]) == (0)) || ((this._compressLeadingPunctuation_0_0value) !== (value))) {
            this._flagArray[64] = 1
            this._compressLeadingPunctuation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[64] = 3
        }
        return this
    }
    selectedDragPreviewStyle(value: SelectedDragPreviewStyle | undefined): this {
        if (((this._flagArray[65]) == (0)) || (true)) {
            this._flagArray[65] = 1
            this._selectedDragPreviewStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[65] = 3
        }
        return this
    }
    textDirection(value: TextDirection | undefined): this {
        if (((this._flagArray[66]) == (0)) || (true)) {
            this._flagArray[66] = 1
            this._textDirection_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[66] = 3
        }
        return this
    }
    voiceButton(value: VoiceButtonOptions | undefined): this {
        if (((this._flagArray[67]) == (0)) || (true)) {
            this._flagArray[67] = 1
            this._voiceButton_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[67] = 3
        }
        return this
    }
    horizontalScrolling(value: boolean | undefined): this {
        if (((this._flagArray[68]) == (0)) || ((this._horizontalScrolling_0_0value) !== (value))) {
            this._flagArray[68] = 1
            this._horizontalScrolling_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[68] = 3
        }
        return this
    }
    inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void)): this {
        if (((this._flagArray[69]) == (0)) || (true) || (true)) {
            this._flagArray[69] = 1
            this._inputFilter_0_0value = value
            this._inputFilter_0_1value = error
            this._state.fireChange()
        } else {
            this._flagArray[69] = 3
        }
        return this
    }
    showCounter(value: boolean | undefined, options?: InputCounterOptions): this {
        if (((this._flagArray[70]) == (0)) || ((this._showCounter_0_0value) !== (value)) || (true)) {
            this._flagArray[70] = 1
            this._showCounter_0_0value = value
            this._showCounter_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[70] = 3
        }
        return this
    }
    maxLines(value: int32 | undefined, options?: MaxLinesOptions): this {
        if (((this._flagArray[71]) == (0)) || ((this._maxLines_0_0value) !== (value)) || (true)) {
            this._flagArray[71] = 1
            this._maxLines_0_0value = value
            this._maxLines_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[71] = 3
        }
        return this
    }
    customKeyboard(value: CustomBuilder | ComponentContentBase | undefined, options?: KeyboardOptions): this {
        if (((this._flagArray[72]) == (0)) || (true) || (true)) {
            this._flagArray[72] = 1
            this._customKeyboard_0_0value = value
            this._customKeyboard_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[72] = 3
        }
        return this
    }
    lineSpacing(value: arkui_component_units_LengthMetrics | undefined, options?: LineSpacingOptions): this {
        if (((this._flagArray[73]) == (0)) || (true) || (true)) {
            this._flagArray[73] = 1
            this._lineSpacing_0_0value = value
            this._lineSpacing_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[73] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
